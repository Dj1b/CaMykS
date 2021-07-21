<?php
/**
 * @brief Content_GoogleSearchResultsViewer module.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Sep 2008
 * @date Modification: Jul 2021
 * @copyright 2008 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_GoogleSearchResultsViewer class.
 */
final class Content_GoogleSearchResultsViewer extends Module {
    /**
     * var Object $gsrItem
     * @brief Content object.
     */
    protected $gsrItem;

    /**
     * var array $gsrList
     * @brief Content list.
     */
    protected $gsrList = array();

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('Content_GoogleSearchResultsViewer', $path_type);

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
        $this->load_library('Content_GoogleSearchResultsViewerItem');

        /* Initialise plugin libraries */
        $this->gsrItem = new Content_GoogleSearchResultsViewerItem(0, $this);
    }

    /* Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return $this->gsrItem->install() and parent::install();
    }

    /**
     * Uninstall module.
     * @return boolean success
     */
    public function uninstall() {
        return $this->gsrItem->uninstall();
    }

    /**
     * Check module installation.
     * @return boolean result
     */
    public function is_installed() {
        return $this->gsrItem->is_installed();
    }

    /**
     * Return available content ids as list.
     * @return array
     */
    public function get_contentList() {
        return $this->gsrItem->get_namelist();
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
        $this->mode = isset($_REQUEST['mode']) ? $_REQUEST['mode'] : 'edit';

        /* Initialise module with mode */
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

        /* Generic module initialisation */
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

        /* Load content item */
        $this->gsrItem->id = $content;
        $this->gsrItem->get();
        $this->gsrItem->get_fromItems();

        /* Update layout */
        $this->selected_layout = 'site_'.$this->gsrItem->vars['layout'].'.html.inc';

        /* Generic site initialisation */
        parent::init_site();
    }

    /* Specific mode methods */

    /**
     * Initialise module in admin / edit mode.
     * @return void
     */
    private function init_admin_edit() {
        global $camyks;

        /* Load object data */
        $this->gsrItem->id = isset ($_REQUEST['id']) ? (int)$_REQUEST['id'] : 0;
        $this->gsrItem->get();
        $this->gsrItem->get_fromItems();

        /* Build form object */
        $this->form = new HTMLForm('gsr_form', $this->get_adminlink(array('mode'=>'save')), 'POST');
        $this->form->add_hidden('id', $this->gsrItem->id);
        $this->form->add_hidden('page_id', $this->page_id);
        $this->form->add_hidden('module_index', $this->module_index);

        /* Add form relative scripts */
        $this->add_JSScript('var googlesearchresultsviewer_form = null;');
        $this->add_JSLoadScript('googlesearchresultsviewer_form=document.'.$this->form->name.';');
        $this->add_JSLoadScript('googlesearchresultsviewer_initialise();');
        $this->add_JSFile('googlesearchresultsviewer.js');
        $this->add_JSScript('var locales={};');
        $this->add_JSScript('locales["googlesearchresultsviewer_invalidcode"]="'.string_html2text($this->get_translation('js_invalidcode')).'";', true);
        $this->add_JSScript('locales["googlesearchresultsviewer_resetgsr"]="'.string_html2text($this->get_translation('js_resetgsr')).'";', true);
        $this->add_JSEngineFile('object/ctransition.js');

        /* Build interface buttons */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'  => $camyks->get_adminLink('Admin_ContentPage', array(
                    'mode'=>'modify',
                    'page_id'=> $this->page_id,
                    'openTab'=>'content',
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
        $this->gsrItem->id = (int)$_REQUEST['id'];;
        $this->gsrItem->get_fromHeader();

        /* Save object */
        if ($this->gsrItem->save()) {
            /* Update page information with object id for new content */
            if ($this->gsrItem->id == 0 and $this->page_id > 0)
                $this->add_moduleContentToPage($this->page_id, $this->module_index, $this->gsrItem->id);

            $this->text = $this->get_translation('savedone');
        } else {
            $this->text = $this->get_translation('savefailed');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('mode'=>'edit', 'id'=>$this->gsrItem->id, 'page_id'=>$this->page_id, 'module_index'=>$this->module_index)));
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
