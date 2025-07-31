<?php
/**
 * @brief Content_GooglePoIMapViewer module.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Jun 2010
 * @date Modification: Jul 2025
 * @copyright 2010 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_GooglePoIMapViewer class.
 */
final class Content_GooglePoIMapViewer extends Module {
    /**
     * var Object $contentItem
     * @brief Content object.
     */
    protected $contentItem;

    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('Content_GooglePoIMapViewer', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'Google';

        /* Override Module variables */
        $this->type = 'content';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Load plugin libraries */
        $this->load_library('Content_GooglePoIMapViewerItem');

        /* Initialise plugin libraries */
        $this->contentItem = new Content_GooglePoIMapViewerItem(0, $this);
    }

    /* Mark: Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return $this->contentItem->install() and parent::install();
    }

    /**
     * Uninstall module.
     * @return boolean success
     */
    public function uninstall() {
        return $this->contentItem->uninstall() and parent::uninstall();
    }

    /**
     * Check module installation.
     * @return boolean result
     */
    public function is_installed() {
        return $this->contentItem->is_installed();
    }

    /**
     * Return available content id/name as list.
     * @return array
     */
    public function get_contentList() {
        return $this->contentItem->get_nameList();
    }

    /**
     * Initialise module object when in admin mode.
     * @return void
     */
    public function init_admin() {
        global $camyks;

        /* Generic pre-initialisation */
        parent::preInit_admin();

        /* Check user permission for this page */
        if ($this->check_right($this->page_id) === false)
            return $this->init_admin_pageAccessDenied();

        /* Check dependencies */
        if (!isset($camyks->inputs['TabBuilder']))
            return $this->init_admin_missingPlugin('Input', 'TabBuilder');
        if (!isset($camyks->inputs['TinyMCEv3']))
            return $this->init_admin_missingPlugin('Input', 'TinyMCEv3');
        if (!isset($camyks->modules['Admin_GooglePoIMapManager']))
            return $this->init_admin_missingPlugin('Module', 'Admin_GooglePoIMapManager');

        /* Load content object id */
        $this->contentItem->id = $this->id;

        /* Load mode to execute */
        $this->mode = isset ($_REQUEST['mode']) ? $_REQUEST['mode'] : 'modify';

        /* Initialise mode */
        switch ($this->mode) {
            case 'save':
                /* mode == save */
                $this->init_admin_save();
                break;
            case 'modify':
            default:
                /* mode == modify */
                $this->init_admin_modify();
                break;
        }

        /* Generic admin initialisation */
        parent::init_admin();
    }

    /**
     * Initialise module object in site mode.
     * @param integer $content
     * @param array $params
     * @param integer $mindex
     * @return void
     */
    public function init_site($content=1, $params=array(), $mindex=null) {
        global $camyks;

        /* Check manager */
        if (!isset($camyks->modules['Admin_GooglePoIMapManager'])) {
            $this->selected_layout = 'null';
            return;
        }

        /* Load manager */
        $this->load_mapManager();
        $this->pointItem = &$this->mapManager->pointItem;

        /* Load content */
        $this->contentItem->id = $content;
        $this->contentItem->get($camyks->current_language);
        $this->contentItem->get_fromItems();

        /* Load category list */
        $cParams = array('status'=>1, '_all'=>true);
        if ($this->contentItem->vars['categories'] != '')
            $cParams['ids'] = $this->contentItem->vars['categories_'];
        $this->categoryList = $this->mapManager->get_categoryTitleList($cParams);

        /* Initialise list params */
        $lp = array();
        $lp['status'] = 1;
        $lp['language'] = $camyks->current_language;

        /* Check selected category */
        if (isset($params['category']) and $params['category'] > 0 and ($this->contentItem->vars['categories']== '' or in_array($params['category'], $this->contentItem->vars['categories_'])))
            $lp['categories'] = $params['category'];
        else
            $lp['categories'] = array_keys($this->categoryList);

        /* Check selected country */
        if (isset($params['country']))
            $lp['country'] = $params['country'];

        /* Load point list */
        $this->pointList = $this->mapManager->get_pointList($lp);

        /* Load icon list */
        $icons = array();
        foreach ($this->pointList as $p)
            if (!in_array($p->vars['icon'], $icons))
                $icons[] = $p->vars['icon'];
        if ($this->contentItem->vars['geo_status'] == 1 and $this->contentItem->vars['geo_icon'] > 0 and !in_array($this->contentItem->vars['geo_icon'], $icons))
            $icons[] = $this->contentItem->vars['geo_icon'];
        $ip = array('ids'=>$icons, '_sized'=>true);
        $this->iconList = $this->mapManager->get_iconList($ip);

        /* Build javascript object */
        $this->add_JSEngineFile('tool/mail.js');
        $this->add_JSEngineFile('tool/html.js');
        $this->add_JSEngineFile('tool/xml.js');
        $this->add_JSExternFile('http://maps.google.com/maps?file=api&v=2&key='.$this->mapManager->config->vars['google_mapapikey'].'&sensor=false');
        $this->add_JSEngineFile('object/cajaxrequest.js');
        $this->add_JSFile('mapviewer.js');
        //$this->add_JSFile('markermanager.js');
        $this->add_JSScript('var pmv = new PoIMapViewer("pmv");');
        $this->add_JSLoadScript('pmv.initialise();');
        $this->add_JSUnloadScript('GUnload();');

        /* Add javascript params */
        $this->add_JSScript('pmv.set_param("ajaxBaseURL", "request.php?module='.$this->name.'");');
        $this->add_JSScript('pmv.set_param("loadingImageURL", "'.$this->get_fileURL('img/loading.gif').'");');
        $this->add_JSScript('pmv.set_param("GMapDefZoom", '.$this->contentItem->vars['default_zoom'].');');

        /* Add locale */
        $this->add_JSScript('pmv.add_locale("your_location", "'.$this->get_translation('js_your_location').'");');

        /* Add point list */
        $cnt = 0;
        foreach($this->pointList as $id => $a) {
            $p = '{title:"'.addslashes($a->vars['title']).'"';
            $p .= ', icon:'.$a->vars['icon'];
            if ($a->vars['latitude'] == '' or $a->vars['longitude'] == '') {
                unset($this->pointList[$id]);
            } else {
                $p .= ', lat:"'.$a->vars['latitude'].'"';
                $p .= ', lng:"'.$a->vars['longitude'].'"';
            }
            $p .= '}';
            $this->add_JSScript('pmv.add_mapPoint('.$a->id.', '.$p.');');
        }

         if (isset($params['point']) and isset($this->pointList[$params['point']]))
             $this->add_JSLoadScript('pmv.select_point('.$params['point'].');');
         else
             foreach ($this->pointList as $id => $a) {
                 $this->add_JSLoadScript('pmv.select_point('.$id.');');
                 break;
         }

        /* Add icon list */
        $cnt = 0;
        foreach($this->iconList as $id => $a) {
            $p = '{mainImg:"'.$a->vars['mainImg'].'"';
            $p .= ', rollImg:"'.$a->vars['rollImg'].'"';
            $p .= ', slctImg:"'.$a->vars['slctImg'].'"';
            $p .= ', shdwImg:"'.$a->vars['shdwImg'].'"';
            $p .= ', mainWidth:'.$a->vars['mainWidth'].'';
            $p .= ', mainHeight:'.$a->vars['mainHeight'].'';
            $p .= ', shdwWidth:'.$a->vars['shdwWidth'].'';
            $p .= ', shdwHeight:'.$a->vars['shdwHeight'].'';
            $p .= ', anchorX:'.$a->vars['anchorLocX'].'';
            $p .= ', anchorY:'.$a->vars['anchorLocY'].'';
            $p .= '}';
            $this->add_JSScript('pmv.add_mapIcon('.$a->id.', '.$p.');');
        }

        /* Check for selectors */
        if ($this->contentItem->vars['category_select'] == 1 or $this->contentItem->vars['country_select'] == 1) {
            $this->has_selector = true;

            /* Build form */
            $this->form = new HTMLForm('pointlist', null, 'post');

            /* Load category values */
            if ($this->contentItem->vars['category_select'] == 1) {
                $this->selCategory = isset($params['category'])?(int)$params['category']:0;
                $this->add_JSScript('pmv.set_param("updateCategoryURL", "'.$this->get_pageLink(array('category'=>'_c_'), $params).'");');
            }

            /* Load country values */
            if ($this->contentItem->vars['country_select'] == 1) {
                countries_loadLocales();
                $this->selCountry = isset($params['country'])?$params['country']:'';
                $this->countryList = array();
                $this->countryList[''] = $this->get_translation('countries_all');
                foreach ($this->pointList as $point) {
                    if (!isset($this->countryList[$point->vars['country']]))
                        $this->countryList[$point->vars['country']] = countries_getTranslation($point->vars['country']);
                }
                $this->add_JSScript('pmv.set_param("updateCountryURL", "'.$this->get_pageLink(array('country'=>'_c_'), $params).'");');
            }
        } else {
            $this->has_selector = false;
        }

        /* Check mobile */
        if ($camyks->deviceMode == 'mobile') {
            $layout = '_mobile';
            $this->add_JSScript('pmv.set_param("hasTabs", 1);');
        } else {
            $layout = '';
            $this->add_JSScript('pmv.set_param("hasTabs", 0);');
        }

        $this->add_JSScript('pmv.set_param("GooglePoIMapGeoStatus", '.$this->contentItem->vars['geo_status'].');');
        if ($this->contentItem->vars['geo_status'] == 1) {
                $this->add_JSScript('pmv.set_param("GooglePoIMapGeoIcon", '.$this->contentItem->vars['geo_icon'].');');
                $this->add_JSScript('pmv.set_param("GooglePoIMapGeoZoom", '.$this->contentItem->vars['geo_zoom'].');');
        }

        /* Update layout */
        $this->set_selectedLayout('site_'.$this->contentItem->vars['layout'].$layout.'.html.inc');
    }

    /**
     * Execute module object in request mode.
     * @return void
     */
    public function execute_request() {
        global $camyks;

        /* Load action to execute */
        $action = isset($_REQUEST['action']) ? $_REQUEST['action'] : '';
        switch ($action) {
            case 'loadpoint':
                $this->execute_request_loadpoint();
                break;
        }

        /* Return undefined action error */
        $result = array();
        $result['status'] = 'failed';
        $result['error'] = $this->get_translation('error_undefinedaction');
        header("Content-type: text/xml");
        die(xml_serialize2XML($result));
    }

    /* Mark: Admin initialise mode sub methods */

    /**
     * Initialise object when in admin / modify mode.
     * @return void
     */
    private function init_admin_modify() {
        global $camyks;

        /* Load help files */
        $this->get_help();

        /* Load map manager */
        $this->load_mapManager();

        /* Load object values */
        $this->contentItem->get();
        $this->contentItem->get_fromItems();

        /* Load data */
        $this->categoryList = $this->mapManager->get_categoryTitleList(array('status'=>1));

        /* Load editor input */
        $this->editor = &$camyks->inputs['TinyMCEv3'];
        $this->editor->initialise();

        /* Load editing languages */
        $this->elgs = $camyks->get_confValue('editing_languages');

        /* Build tabs */
        $this->tabBuilder = $camyks->get_input('TabBuilder');

        /* Add definitions tab */
        $this->tabBuilder->add_tab(array(
            'name'  => 'properties',
            'title' => $this->get_translation('tabproperties'),
        ));
        if (count($this->elgs) == 1)
            $this->tabBuilder->add_tab(array(
                'name'  => $this->elgs[0],
                'title' => $this->get_translation('tabcontent'),
            ));
        else
            foreach($this->elgs as $l)
                $this->tabBuilder->add_tab(array(
                    'name'  => $l,
                    'title' => language_getIcon($l),
                ));

        /* Add help tab */
        if ($this->help != null)
            $this->tabBuilder(array(
                'name'=>'help',
                'title'=>$camyks->get_translation('help'),
            ));

        /* Initialise tabs */
        $this->tabBuilder->initialise(array('default'=>'properties'));

        /* Create html form */
        $this->form = new HTMLForm('edit_form', $this->get_adminlink(array('mode'=>'save')), 'POST');
        $this->form->set_object($this->contentItem);
        $this->form->add_hidden('page_id', $this->page_id);
        $this->form->add_hidden('module_index', $this->module_index);
        $this->form->add_hidden('id', $this->contentItem->id);
        $this->form->add_hidden('category_cnt', count($this->categoryList));

        /* Add scripts */
        $this->add_JSFile('poimapviewer_admin.js');
        $this->add_JSScript('var formName = "'.$this->form->name.'";');

        /* Build interface button */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'  => $camyks->get_adminLink('Admin_ContentPage', array(
                    'mode'      => 'modify',
                    'page_id'   => $this->page_id,
                    'openTab'   => 'content',
                )),
            ),
            array(
                'title' => $camyks->get_translation('valid'),
                'link'  => $this->form->get_HTMLSubmitLink(),
            ),
        );
    }

    /**
     * Initialise object when in admin / save mode.
     * @return void
     */
    private function init_admin_save() {
        global $camyks;

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Load editing languages */
        $this->elgs = $camyks->get_confValue('editing_languages');

        /* save content */
        $this->contentItem->get_fromHeader();
        if ($this->contentItem->save()) {
            if ($this->contentItem->id == 0 and $this->page_id > 0) {
                /* Update page information with object id for new content */
                $this->add_moduleContentToPage($this->page_id, $this->module_index, $this->contentItem->id);
            }
            $this->text = $camyks->get_translation('savedone');
        } else {
            $this->text = $camyks->get_translation('savefailed');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('mode'=>'modify', 'id'=>$this->contentItem->id)));
    }

    /* Mark: Request mode sub methods */

    /**
     * Execute module object in load point mode.
     * @return void
     */
    private function execute_request_loadpoint() {
        global $camyks;

        /* Load CaMykS basis */
        $camyks->get_databaseConnection();
        $camyks->get_currentLanguage('site');

        /* Initialise result */
        $result = array();

        /* Check obj and type */
        if (!isset($_REQUEST['point'])) {
            $result['status'] = 'failed';
            $result['error'] = $this->get_translation('error_undefinedobject');
            header("Content-type: text/xml");
            die(xml_serialize2XML($result));
        }

        $result['status'] = 'success';
        $result['action'] = 'updateSelectedPoint';

        /* Load params */
        $pointManager = module_get('Admin_GooglePoIMapManager', 'camyks');

        $pointItem = &$pointManager->pointItem;
        $pointItem->id = $_REQUEST['point'];
        $pointItem->get($camyks->current_language);
        $pointItem->get_fromItems();

        $result['title'] = $pointItem->vars['title'];
        $result['desc'] = $pointItem->vars['description'];

        /* send result as XML */
        header("Content-type: text/xml");
        die (xml_serialize2XML($result, 'request'));
    }

    /* Mark: Specific tool methods */

    /**
     * Load map manager.
     * @return void
     */
    private function load_mapManager() {
        global $camyks;

        $this->mapManager = $camyks->get_module('Admin_GooglePoIMapManager');
        if ($this->mapManager !== false)
            $this->mapManager->config->get();
    }


    /**
     * Return layout list.
     * @return array
     */
    protected function get_layoutList() {
        return array(
            'nobox'     => $this->get_translation('layout_nobox'),
            'largebox'  => $this->get_translation('layout_largebox'),
        );
    }

    /**
     * Return geolocalisation status list.
     * @return array
     */
    protected function get_geoStatusList() {
        return array(
            0 => $this->get_translation('geostatus_disabled'),
            1 => $this->get_translation('geostatus_enabled'),
        );
    }

    /**
     * Return icon title list.
     * @return array
     */
    protected function get_iconTitleList() {
        return $this->mapManager->get_iconNameList();
    }


    /**
     * Return page link.
     * @param array $newParams
     * @param array $oldParams
     * @return string
     */
    protected function get_pageLink($newParams=array(), $oldParams=array()) {
        global $camyks;
        $params = array();

        if (isset($oldParams['point']))
            $params['point'] = $oldParams['point'];
        if (isset($oldParams['country']))
            $params['country'] = $oldParams['country'];
        if (isset($oldParams['category']))
            $params['category'] = $oldParams['category'];

        if (count($camyks->get_confValue('site_languages')) > 1)
            $lg = $camyks->current_language;
        else
            $lg = null;

        $params = array_merge($params, $newParams);
        return $camyks->get_siteLink($camyks->contentPage->id,'', $lg, $params);
    }
}
?>
