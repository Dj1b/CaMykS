<?php
/**
 * @brief Content_GoogleMapsViewer module.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Jul 2008
 * @date Modification: Jul 2021
 * @copyright 2008 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_GoogleMapsViewer class.
 */
final class Content_GoogleMapsViewer extends Module {
    /**
     * var Object $mapItem
     * @brief Content object.
     */
    protected $mapItem;

    /**
     * var array $mapList
     * @brief Content list.
     */
    protected $mapList = array();

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('Content_GoogleMapsViewer', $path_type);

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
        $this->load_library('Content_GoogleMapsViewerItem');

        /* Initialise plugin libraries */
        $this->mapItem = new Content_GoogleMapsViewerItem(0, $this);
    }

    /* Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return $this->mapItem->install() and parent::install();
    }

    /**
     * Uninstall module.
     * @return boolean success
     */
    public function uninstall() {
        return $this->mapItem->uninstall();
    }

    /**
     * Check module installation.
     * @return boolean result
     */
    public function is_installed() {
        return $this->mapItem->is_installed();
    }

    /**
     * Return available content ids as list.
     * @return array
     */
    public function get_contentList() {
        return $this->mapItem->get_namelist();
    }

    /**
     * Initialise module object in admin mode.
     * @return void
     */
    public function init_admin() {
        /* Generic pre-initialisation */
        parent::preInit_admin();

        /* Check permission for this page */
        if ($this->check_right($this->page_id) === false)
            return $this->init_admin_pageAccessDenied();

        /* Load mode to execute */
        $this->mode = isset ($_REQUEST['mode']) ? $_REQUEST['mode'] : 'edit';

        /* Execute mode initialisation */
        switch ($this->mode) {
            case 'save' :
                /* mode == save */
                $this->init_admin_save();
                break;
            case 'edit' :
            default:
                /* mode == edit */
                $this->init_admin_edit();
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

        if (count($this->mapList) == 0) {
            /* Add theme editor styles */
            $camyks->theme->get_editor_css();
            /* Add email management javascripts */
            $this->add_JSEngineFile('tool/mail.js');
        }

        /* Load content item */
        $mapItem = new Content_GoogleMapsViewerItem($content, $this);
        $mapItem->get($camyks->current_language);
        $mapItem->get_fromItems();

        /* Add content to list */
        $this->mapList[$mindex] = $mapItem;

        /* Generic site initialisation */
        parent::init_site();
    }

    /**
     * Display module object in site mode.
     * @return void
     */
    public function display_site($mindex=null) {
        /* Load content */
        $this->mapItem = &$this->mapList[$mindex];

        /* Update layout */
        $this->set_selectedLayout('site_'.($this->check_layout($this->mapItem->vars['layout']) ? $this->mapItem->vars['layout'] : 'classic').'.html.inc');

        /* Generic site display */
        parent::display_site();
    }

    /* Specific mode methods */

    /**
     * Initialise module in admin / edit mode.
     * @return void
     */
    private function init_admin_edit() {
        global $camyks;

        /* Load object data */
        $this->mapItem->id = isset ($_REQUEST['id']) ? (int)$_REQUEST['id'] : 0;
        $this->mapItem->get();
        $this->mapItem->get_fromItems();

        /* Build form object */
        $this->form = new HTMLForm('maps_form', $this->get_adminlink(array('mode'=>'save')), 'POST');
        $this->form->add_hidden('id', $this->mapItem->id);
        $this->form->add_hidden('page_id', $this->page_id);
        $this->form->add_hidden('module_index', $this->module_index);

        /* Build tabs object */
        $this->tabObject = 'maps_tabObject';
        $this->add_JSEngineFile ('object/ctab.js');
        $this->add_JSScript($this->tabObject.' = new CTab();');
        $this->add_JSScript($this->tabObject.'.init("properties", "'.$camyks->theme->parts['boxTabCSSStandart'].'","'.$camyks->theme->parts['boxTabCSSSelected'].'","'.$camyks->theme->parts['boxTabCSSRollover'].'");');
        $this->tabs = array(
            array(
                'name'  => 'properties',
                'title' => $this->get_translation('tab_properties'),
            )
        );
        foreach($camyks->get_confValue('editing_languages') as $l) {
            $this->tabs[] = array(
                'name'  => 'desc_'.$l,
                'title' => '<img src="'.language_getIcon($l, false).'" border="0" alt="'.$l.'" style="" />'
            );
        }

        /* Load web editor */
        if (isset($camyks->inputs['TinyMCEv3'])) {
            $this->webEditor = &$camyks->inputs['TinyMCEv3'];
        } elseif (isset($camyks->inputs['TinyMCE'])) {
            $this->webEditor = &$camyks->inputs['TinyMCE'];
        } else {
            $this->webEditor = false;
        }

        /* Initialise web editor */
        if ($this->webEditor !== false){
            $this->webEditor->set_textareaInfos('content', '100%', '400px');
            $this->webEditor->initialise();
        }

        /* Load color picker */
        if (isset($camyks->inputs['ColorPicker'])) {
            $this->colorPicker = &$camyks->inputs['ColorPicker'];
            $this->colorPicker->initialise('link_color', 'default', 'modal');
        } else {
            $this->colorPicker = false;
        }

        /* Add form relative scripts */
        $this->add_JSScript('var googlemapsviewer_form = null;');
        $this->add_JSLoadScript('googlemapsviewer_form=document.'.$this->form->name.';');
        $this->add_JSLoadScript('googlemapsviewer_initialise();');
        $this->add_JSFile('googlemapsviewer.js');
        $this->add_JSScript('var locales = {};', true);
        $this->add_JSScript('locales["googlemapsviewer_invalidcode"]="'.string_html2text($this->get_translation('js_invalidcode')).'";', true);
        $this->add_JSScript('locales["googlemapsviewer_resetmap"]="'.string_html2text($this->get_translation('js_resetmap')).'";', true);
        $this->add_JSEngineFile('object/ctransition.js');

        /* Build interface buttons */
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
     * Initialise module in admin / save mode.
     * @return void
     */
    public function init_admin_save() {
        global $camyks;

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Check object id */
        if (!(isset($_REQUEST['id'])))
            $this->init_admin_edit();

        /* Load object */
        $this->mapItem->id = (int)$_REQUEST['id'];
        $this->mapItem->get_fromHeader();

        /* Save object */
        if ($this->mapItem->save()) {
            /* Update page information with object id for new content */
            if ($this->mapItem->id == 0 and $this->page_id > 0)
                $this->add_moduleContentToPage($this->page_id, $this->module_index, $this->mapItem->id);

            $this->text = $this->get_translation('savedone');
        } else {
            $this->text = $this->get_translation('savefailed');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('mode'=>'edit', 'id'=>$this->mapItem->id, 'page_id'=>$this->page_id, 'module_index'=>$this->module_index)));
    }

    /* Specific methods */

    /**
     * Return layouts list.
     * @return array
     */
    protected function get_layouts() {
        return array(
            'classic'   => $this->get_translation('layout_classic'),
            'boxed'     => $this->get_translation('layout_boxed'),
        );
    }

    /**
     * Check given layout.
     * @param string $layout
     * @return boolean result
     */
    protected function check_layout($layout='') {
        $l = $this->get_layouts();
        return isset($l[$layout]);
    }
}
?>
