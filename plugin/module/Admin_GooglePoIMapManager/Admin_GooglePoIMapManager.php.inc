<?php
/**
 * @brief Admin_GooglePoIMapManager module.
 * <br /> Manages points of interest for a Google Map.
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
 * Admin_GooglePoIMapManager class.
 */
final class Admin_GooglePoIMapManager extends Module {
    /**
     * var Object $pointItem
     * @brief Point object.
     */
    public $pointItem;

    /**
     * var array $pointList
     * @brief Point list.
     */
    public $pointList = null;

    /**
     * var Object $categoryItem
     * @brief Category object.
     */
    public $categoryItem;

    /**
     * var array $catList
     * @brief Category list.
     */
    public $catList = null;

    /**
     * var Object $iconItem
     * @brief Icon object.
     */
    public $iconItem;

    /**
     * var array $iconList
     * @brief Icon list.
     */
    public $iconList = null;

    /**
     * var Object $config
     * @brief Plugin configuration.
     */
    protected $config;

    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('Admin_GooglePoIMapManager', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'Google';

        /* Override Module variables */
        $this->type = 'admin';
        $this->admin_type = 'content';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Load plugin libraries */
        $this->load_library('Admin_GooglePoIMapManagerPoint');
        $this->load_library('Admin_GooglePoIMapManagerCategory');
        $this->load_library('Admin_GooglePoIMapManagerIcon');
        $this->load_library('Admin_GooglePoIMapManagerConfig');

        /* Initialise plugin libraries */
        $this->pointItem = new Admin_GooglePoIMapManagerPoint(0, $this);
        $this->categoryItem = new Admin_GooglePoIMapManagerCategory(0, $this);
        $this->iconItem = new Admin_GooglePoIMapManagerIcon(0, $this);
        $this->config = new Admin_GooglePoIMapManagerConfig('config', $this);
    }

    /* Mark: Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return ($this->pointItem->install() and $this->categoryItem->install()
            and $this->iconItem->install() and $this->config->install()
            and parent::install());
    }

    /**
     * Check module installation.
     * @return boolean result
     */
    public function is_installed() {
        return $this->iconItem->is_installed();
    }

    /**
     * Define module permissions.
     * @return void
     */
    public function get_rights() {
        global $camyks;
        $this->rights[0] = array(
            'name'      => 'read',
            'title'     => $camyks->get_translation('read'),
            'default'   => false,
        );
        $this->rights[1] = array(
            'name'      => 'edit_point',
            'title'     => $camyks->get_translation('right_editpoint'),
            'default'   => false,
        );
        $this->rights[2] = array(
            'name'      => 'edit_data',
            'title'     => $this->get_translation('right_editdata'),
            'default'   => false,
        );
        $this->rights[3] = array(
            'name'      => 'edit_config',
            'title'     => $this->get_translation('right_editconfig'),
            'default'   => false,
        );
    }

    /**
     * Initialise module object in admin mode.
     * @return void
     */
    public function init_admin() {
        global $camyks;

        /* Check read permission */
        if ($this->check_right(0) === false)
            return $this->init_admin_accessDenied();

        /* Check dependencies */
        if (!isset($camyks->inputs['TabBuilder']))
            return $this->init_admin_missingPlugin('Input', 'TabBuilder');
        if (!isset($camyks->inputs['AdminItemListViewer']))
            return $this->init_admin_missingPlugin('Input', 'AdminItemListViewer');

        /* Load action to execute */
        $this->mode = (isset ($_REQUEST['mode']) ? $_REQUEST['mode'] : 'main');

        /* Execute action */
        switch ($this->mode) {
            case 'edit_point':
                /* mode == edit_point */
                $this->init_admin_edit_point();
                break;
            case 'save_point':
                /* mode == save_point */
                $this->init_admin_save_point();
                break;
            case 'delete_point':
                /* mode == delete_point */
                $this->init_admin_delete_point();
                break;
            case 'edit_cat':
                /* mode == edit_cat */
                $this->init_admin_edit_category();
                break;
            case 'save_cat':
                /* mode == save_cat */
                $this->init_admin_save_category();
                break;
            case 'delete_cat':
                /* mode == delete_cat */
                $this->init_admin_delete_category();
                break;
            case 'edit_icon':
                /* mode == edit_icon */
                $this->init_admin_edit_icon();
                break;
            case 'save_icon':
                /* mode == save_icon */
                $this->init_admin_save_icon();
                break;
            case 'delete_icon':
                /* mode == delete_icon */
                $this->init_admin_delete_icon();
                break;
            case 'edit_config':
                /* mode == edit_config */
                $this->init_admin_edit_config();
                break;
            case 'save_config':
                /* mode == save_config */
                $this->init_admin_save_config();
                break;
            case 'main':
            default:
                /* mode == main */
                $this->init_admin_main();
        }

        /* Generic initialisation */
        parent::init_admin();
    }

    /* Mark: Admin initialise mode sub methods */

    /**
     * Initialise module object in admin/main mode.
     * @return void
     */
    private function init_admin_main() {
        global $camyks;

        /* Load help */
        $this->get_help();

        /* Load language to use with content */
        $this->language = $this->get_adminEditionLanguage();
        countries_loadLocales();

        /* Build point tab */
        $this->load_library('Admin_GooglePoIMapManagerPointListParams');
        $this->pointList = $camyks->get_input('AdminItemListViewer');
        $this->pointList->set_params($this->pointListParams);
        $this->pointList->initialise();

        /* build category tab */
        $this->load_library('Admin_GooglePoIMapManagerCategoryListParams');
        $this->catList = new AdminItemListViewer('camyks');
        $this->catList->set_params($this->catListParams);
        $this->catList->initialise();

        $catIDs = array_keys($this->catList->objectList);
        $cnts = $this->pointItem->get_pointCountByCategories($catIDs);
        foreach($this->catList->objectList as $id => $cat)
            $this->catList->objectList[$id]->vars['points'] = isset($cnts[$id])?$cnts[$id]:0;

        /* Build icon tab */
        $this->load_library('Admin_GooglePoIMapManagerIconListParams');
        $this->iconList = new AdminItemListViewer('camyks');
        $this->iconList->set_params($this->iconListParams);
        $this->iconList->initialise();

        /* Load tabs */
        $this->tabBuilder = $camyks->get_input('TabBuilder');
        $this->tabBuilder->add_tabs(array(
            array(
                'name'=>'points',
                'title'=>$this->get_translation('tabpoints')
            ),
            array(
                'name'=>'categories',
                'title'=>$this->get_translation('tabcategories'),
            ),
            array(
                'name'=>'icons',
                'title'=>$this->get_translation('tabicons'),
            ),
        ));

        /* Check for config tab */
        if ($this->check_right(3)) {
            $this->config->get();
            $this->tabBuilder->add_tab(array(
                'name'  => 'config',
                'title' => $this->get_translation('tabconfig'),
            ));
        }

        /* Check for help tab */
        if ($this->help != null)
            $this->tabBuilder->add_tab(array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help'),
            ));

        /* Initialise tabs */
        $this->tabBuilder->initialise(array('default'=>'points'));

        /* Build interface buttons */
        $this->buttons = array(
            array(
                'link'  => $camyks->get_adminLink(),
                'title' => $camyks->get_translation('back'),
            )
        );
    }

    /**
     * Initialise module object in admin/edit_point mode
     * @return void
     */
    private function init_admin_edit_point() {
        global $camyks;

        /* Check edit point permission */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* Load config */
        $this->config->get();

        /* Load edition language list */
        $this->elg = $camyks->get_confValue('editing_languages');

        /* Load point item */
        $this->pointItem->id = isset($_REQUEST['point_id']) ? $_REQUEST['point_id'] : 0;
        $this->pointItem->get();
        $this->pointItem->get_fromItems();

        /* Build form */
        $this->editform = new HTMLForm('edit_point', $this->get_adminlink(array('mode'=>'save_point')), 'POST');
        $this->editform->add_hidden('point_id', $this->pointItem->id);
        $this->editform->set_object($this->pointItem);

        /* Load google map */
        $this->add_JSExternFile('http://maps.google.com/maps?file=api&v=2&key='.$this->config->vars['google_mapapikey'].'&sensor=false');
        $this->add_JSFile('pointeditor.js');
        $this->add_JSScript('var pe = new PointEditor("pe");');
        $this->add_JSLoadScript('pe.initialise("'.$this->editform->name.'");');
        $this->add_JSUnloadScript('GUnload();');

        /* Add javascript params */
        $this->add_JSScript('pe.set_param("GMapDefZoom", 14);');

        $p = '{title:"'.addslashes($this->pointItem->vars['title']).'"';
        if ($this->pointItem->vars['latitude'] == '' or $this->pointItem->vars['longitude'] == '') {
            $p .= ', address:"'.$this->pointItem->vars['address1'].' ';
            $p .= $this->pointItem->vars['address2'].' ';
            $p .= $this->pointItem->vars['address3'].'"';
        } else {
            $p .= ', lat:"'.$this->pointItem->vars['latitude'].'"';
            $p .= ', lng:"'.$this->pointItem->vars['longitude'].'"';
        }
        $p.= '}';
        $this->add_JSScript('pe.set_param("Point", '.$p.');');

        /* Add javascript locales */
        $this->add_JSScript('pe.add_locale("address_undefined", "'.string_html2text($this->get_translation('js_address_undefined')).'");');

        /* Build interface tabs */
        $this->tabBuilder = $camyks->get_input('TabBuilder');
        $this->tabBuilder->add_tabs(array(array(
            'name'  => 'properties',
            'title' => $this->get_translation('tabproperties')),
        ));
        if (count($this->elg) > 1)
            foreach ($this->elg as $l)
                $this->tabBuilder->add_tab(array(
                    'name'  => $l,
                    'title' => language_getIcon($l),
                ));
        else
            $this->tabBuilder->add_tab(array(
                'name'  => $this->elg[0],
                'title' => $this->get_translation('tabcontent'),
            ));
        $this->tabBuilder->initialise();

        /* Load editor input */
        $this->input = $camyks->get_input('TinyMCEv3');
        $this->input->initialise();

        /* Build title */
        $this->adminTitle = $this->title;
        $this->adminTitle .= $camyks->get_translation('formitem_separator');
        if ($this->pointItem->id == 0)
            $this->adminTitle .= $this->get_translation('pointnew');
        else
            $this->adminTitle .= $this->get_translation('pointid', $this->pointItem->id);

        /* Build interface buttons */
        $this->buttons = array(
            array(
                'link'  => $this->get_adminLink(),
                'title' => $camyks->get_translation('back'),
            ),
            array(
                'link'  => $this->editform->get_HTMLSubmitLink(),
                'title' => $camyks->get_translation('valid'),
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('admin_edit_point.html.inc');
    }

    /**
     * Initialise module object in admin/save_point mode.
     * @return void
     */
    private function init_admin_save_point() {
        global $camyks;

        /* Check user permission */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Save object */
        $this->pointItem->id = isset($_REQUEST['point_id']) ? (int)$_REQUEST['point_id'] : 0;
        $this->pointItem->get_fromHeader();
        if ($this->pointItem->save()) {
            $this->text = $this->get_translation('point_saved');
        } else {
            $this->text = $this->get_translation('point_notsaved');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /**
     * Initialise module object in admin/delete_point mode.
     * @return void
     */
    private function init_admin_delete_point() {
        global $camyks;

        /* Check user rights */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* Check point id */
        if (!isset($_REQUEST['point_id']))
            return $this->init_admin_main();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Load object id */
        $this->pointItem->id = (int)$_REQUEST['point_id'];

        /* Delete object */
        if ($this->pointItem->delete()) {
            $this->text = $this->get_translation('point_deleted');
         } else {
            $this->text = $this->get_translation('point_notdeleted');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /**
     * Initialise module object in admin/edit_cat mode.
     * @return void
     */
    private function init_admin_edit_category() {
        global $camyks;

        /* Check edit category permission */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* Load category item */
        $this->categoryItem->id = isset($_REQUEST['cat_id']) ? (int)$_REQUEST['cat_id'] : 0;
        $this->categoryItem->get();
        $this->categoryItem->get_fromItems();

        /* Build interface form */
        $this->editform = new HTMLForm('edit_cat', $this->get_adminlink(array('mode'=>'save_cat')), 'POST');
        $this->editform->add_hidden('cat_id', $this->categoryItem->id);
        $this->editform->set_object($this->categoryItem);

        /* Build title */
        $this->adminTitle = $this->title;
        $this->adminTitle .= $camyks->get_translation('formitem_separator');
        if ($this->categoryItem->id == 0)
            $this->adminTitle .= $this->get_translation('catnew');
        else
            $this->adminTitle .= $this->get_translation('catid', $this->categoryItem->id);

        /* Build interface buttons */
        $this->buttons = array(
            array(
                'link'  => $this->get_adminLink(array('openTab'=>'categories')),
                'title' => $camyks->get_translation('back')
            ),
            array(
                'link'  => $this->editform->get_HTMLSubmitLink(),
                'title' => $camyks->get_translation('valid'),
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('admin_edit_category.html.inc');
    }

    /**
     * Initialise module object in admin/save_cat mode.
     * @return void
     */
    private function init_admin_save_category() {
        global $camyks;

        /* Check user permission */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Save object */
        $this->categoryItem->id = isset($_REQUEST['cat_id']) ? (int)$_REQUEST['cat_id'] : 0;
        $this->categoryItem->get_fromHeader();
        if ($this->categoryItem->save()) {
            $this->text = $this->get_translation('cat_saved');
        } else {
            $this->text = $this->get_translation('cat_notsaved');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('openTab'=>'categories')));
    }

    /**
     * Initialise module object in admin/delete_cat mode.
     * @return void
     */
    private function init_admin_delete_category() {
        global $camyks;

        /* Check user permission */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* Check category id */
        if (!isset($_REQUEST['cat_id']))
            return $this->init_admin_main();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Load object id */
        $this->categoryItem->id = (int)$_REQUEST['cat_id'];

        /* Delete object */
        if ($this->categoryItem->delete()) {
            $this->text = $this->get_translation('cat_deleted');
         } else {
            $this->text = $this->get_translation('cat_notdeleted');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('openTab'=>'categories')));
    }

    /**
     * Initialise module object in admin/edit_icon mode.
     * @return void
     */
    private function init_admin_edit_icon() {
        global $camyks;

        /* Check edit category permission */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* Load icon item */
        $this->iconItem->id = isset($_REQUEST['icon_id']) ? (int)$_REQUEST['icon_id'] : 0;
        $this->iconItem->get();
        $this->iconItem->get_fromItems();

        /* Build interface form */
        $this->editform = new HTMLForm('edit_icon', $this->get_adminlink(array('mode'=>'save_icon')), 'POST');
        $this->editform->allow_files(true, 512*1024);
        $this->editform->add_hidden('icon_id', $this->iconItem->id);
        $this->editform->set_object($this->iconItem);

        /* Build interface title */
        $this->adminTitle = $this->title;
        $this->adminTitle .= $camyks->get_translation('formitem_separator');
        if ($this->iconItem->id == 0)
            $this->adminTitle .= $this->get_translation('iconnew');
        else
            $this->adminTitle .= $this->get_translation('iconid', $this->iconItem->id);

        /* Build interface buttons */
        $this->buttons = array(
            array(
                'link'  => $this->get_adminLink(array('openTab'=>'icons')),
                'title' => $camyks->get_translation('back'),
            ),
            array(
                'link'  => $this->editform->get_HTMLSubmitLink(),
                'title' => $camyks->get_translation('valid'),
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('admin_edit_icon.html.inc');
    }

    /**
     * Initialise module object in admin/save_icon mode.
     * @return void
     */
    private function init_admin_save_icon() {
        global $camyks;

        /* Check user permission */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Save object */
        $this->iconItem->id = isset($_REQUEST['icon_id']) ? (int)$_REQUEST['icon_id'] : 0;
        $this->iconItem->get_fromHeader();
        if ($this->iconItem->save()) {
             $this->text = $this->get_translation('icon_saved');
        } else {
            $this->text = $this->get_translation('icon_notsaved');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('openTab'=>'icons')));
    }

    /**
     * Initialise module object in admin/delete_icon mode.
     * @return void
     */
    private function init_admin_delete_icon() {
        global $camyks;

        /* Check user permission */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* Check icon id */
        if (!isset($_REQUEST['icon_id']))
            return $this->init_admin_main();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Load object id */
        $this->iconItem->id = (int)$_REQUEST['icon_id'];

        /* Delete object */
        if ($this->iconItem->delete()) {
            $this->text = $this->get_translation('icon_deleted');
         } else {
            $this->text = $this->get_translation('icon_notdeleted');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('openTab'=>'categories')));
    }

    /**
     * Initialise module object in admin/edit_config mode.
     * @return void
     */
    private function init_admin_edit_config() {
        global $camyks;

        /* Check user permission */
        if ($this->check_right(3) === false)
            return $this->init_admin_actionNotAllowed();

        /* Load config */
        $this->config->get();

        /* Build interface form */
        $this->configform = new HTMLForm('configform', $this->get_adminLink(array('mode' => 'save_config')), 'POST');
        $this->configform->set_object($this->config);

        /* Build interface title */
        $this->adminTitle = $this->title;
        $this->adminTitle .= $camyks->get_translation('formitem_separator');
        $this->adminTitle .= $this->get_translation('configuration');

        /* build button list */
        $this->buttons = array(
            array(
                'link'  => $camyks->get_adminLink(),
                'title' => $camyks->get_translation('back'),
            ),
            array(
                'link'  => $this->configform->get_HTMLSubmitLink(),
                'title' => $camyks->get_translation('valid'),
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('admin_edit_config.html.inc');
    }

    /**
     * Initialise module object in admin/save_config mode.
     * @return void
     */
    private function init_admin_save_config() {
        global $camyks;

        /* Check user permission */
        if ($this->check_right(3) === false)
            return $this->init_admin_actionNotAllowed();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Save config */
        $this->config->get_fromHeader();
        if ($this->config->save()) {
            $this->text = $this->get_translation('config_saved');
        } else {
            $this->text = $this->get_translation('config_notsaved');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('openTab'=>'config')));
    }

    /* Mark: Specific admin tool methods */

    /**
     * Return point status list.
     * @return array
     */
    public function get_pointStatusList() {
        return $this->pointItem->get_statusList();
    }

    /**
     * Return points status list.
     * @param boolean $full
     * @return array
     */
    public function get_pointsStatusList($full=false) {
        return $this->pointItem->get_multiStatusList($full);
    }

    /**
     * Return point country list.
     * @param array $params
     * @return array
     */
    public function get_pointCountryList($params=array()) {
        return $this->pointItem->get_countryList($params);
    }

    /**
     * Return point list from given params.
     * @param array $params
     * @return array
     */
    public function get_pointList($params=array()) {
        return $this->pointItem->get_list($params);
    }

    /**
     * Return category status list.
     * @return array
     */
    public function get_categoryStatusList() {
        return $this->categoryItem->get_statusList();
    }

    /**
     * Return categories status list.
     * @param boolean $full
     * @return array
     */
    public function get_categoriesStatusList($full=false) {
        return $this->categoryItem->get_multiStatusList($full);
    }

    /**
     * Return category title list.
     * @param array $params
     * @return array
     */
    public function get_categoryTitleList($params=array()) {
        if (!isset($params['language']) or $params['language'] == '')
            $params['language'] = $this->get_adminEditionLanguage();
        return $this->categoryItem->get_titleList($params);
    }

    /**
     * Return icon name list.
     * @param array $params
     * @return array
     */
    public function get_iconNameList($params=array()) {
        return $this->iconItem->get_objectNameList($params);
    }

    /**
     * Return icon list from given params.
     * @param array $params
     * @return array
     */
    public function get_iconList($params=array()) {
        return $this->iconItem->get_list($params);
    }
}
?>
