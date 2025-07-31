<?php
/**
 * @brief Content_GenericPageList module.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.2
 * @date Creation: Nov 2007
 * @date Modification: Jul 2025
 * @copyright 2007 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_GenericPageList class.
 */
final class Content_GenericPageList extends Module {
    /**
     * var Object $plitem
     * @brief Page list item.
     */
    protected $plitem;

    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('Content_GenericPageList', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'Generic';

        /* Override Module variables */
        $this->type = 'content';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Load plugin libraries */
        $this->load_library('Content_GenericPageListItem');
        $this->plitem = new Content_GenericPageListItem(0, $this);
    }

    /* Mark: Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return $this->plitem->install() and parent::install();
    }

    /**
     * Uninstall module.
     * @return boolean success
     */
    public function uninstall() {
        return $this->plitem->uninstall() and parent::uninstall();
    }

    /**
     * Check module installation.
     * @return boolean result
     */
    public function is_installed() {
        return $this->plitem->is_installed();
    }

    /**
     * Return available content id/names as list.
     * @return array
     */
    public function get_contentList() {
        return $this->plitem->get_nameList();
    }

    /**
     * Initialise module object in admin mode.
     * @return void
     */
    public function init_admin() {
        global $camyks;

        /* Generic pre-initialisation */
        parent::preInit_admin();

        /* Check permission for this page */
        if ($this->check_right($this->page_id) === false)
            return $this->init_admin_pageAccessDenied();

        /* Load page list item */
        $this->plid = isset($_REQUEST['id']) ? (int)$_REQUEST['id'] : 0;
        $this->plitem->id = $this->plid;

        /* Load action to execute */
        $this->mode = isset($_REQUEST['mode']) ? $_REQUEST['mode'] : '';

        /* Execute action */
        switch ($this->mode) {
            case 'save_item':
                /* mode == save_item */
                $this->init_admin_save_item();
                break;
            case 'modify_item':
            default:
                /* mode == modify_item */
                $this->init_admin_modify_item();
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

        if (!isset($this->contents)) {
            /* Load pages */
            $this->pages = $camyks->modules['Admin_ContentPage']->get_sitePages(null, 'active=1');

            /* Create contents list */
            $this->contents = array();
        }

        $this->contents[$mindex] = new Content_GenericPageListItem($content, $this);
        $this->contents[$mindex]->get($camyks->current_language);
        $this->contents[$mindex]->get_fromItems();

        /* Check if "root" page exits */
        if (isset ($this->pages[ $this->contents[$mindex]->vars['root']])) {
            /* Load root page */
            $this->contents[$mindex]->vars['pages'] = $this->pages[$this->contents[$mindex]->vars['root']]->children;
        } else {
            foreach ($this->pages as $p) {
                $this->contents[$mindex]->vars['pages'] = $this->pages[$p->id]->children;
                break;
            }
        }

        /* Check for reverse display */
        if ($this->contents[$mindex]->vars['listorder'] == 'reverse') {
            $this->contents[$mindex]->vars['pages'] = array_reverse($this->contents[$mindex]->vars['pages']);
        }

        parent::init_site();
    }

    /**
     * Display module object in site mode.
     * @param integer $mindex
     * @return void
     */
    public function display_site($mindex=null) {
        /* Load selected content */
        $this->plitem = $this->contents[$mindex];

        /* Update layout */
        $this->set_selectedLayout('site_'.$this->plitem->vars['layout'].'.html.inc');

        /* Execute generic display */
        parent::display_site();
    }

    /* Mark: Admin initialise mode sub methods */

    /**
     * Initialise module object in admin/modify_item mode.
     * @return void
     */
    private function init_admin_modify_item() {
        global $camyks;

        /* Load help */
        $this->get_help();

        /* Load object */
        $this->plitem->get(true);
        $this->plitem->get_fromItems();

        /* Load tabs */
        $this->tabs = array(
            array(
                'name'  => 'properties',
                'title' =>  $this->get_translation('tabproperties'),
            ),
        );

        if ($this->help != null) {
            $this->tabs[] = array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help'),
            );
        }

        /* Insert tabs javascript */
        $this->tabObject = 'pagelist_tabObject';
        $this->add_JSEngineFile ('object/ctab.js');
        $this->add_JSScript($this->tabObject.' = new CTab();');
        $this->add_JSScript($this->tabObject.'.init("general", "'.$this->theme->parts['boxTabCSSStandart'].'","'.$this->theme->parts['boxTabCSSSelected'].'","'.$this->theme->parts['boxTabCSSRollover'].'");');

        /* Build form */
        $this->form = new HTMLForm('genericpl_form', $this->get_adminlink(array('mode'=>'save_item')), 'POST');
        $this->form->add_hidden('page_id', $this->page_id);
        $this->form->add_hidden('module_index', $this->module_index);
        $this->form->add_hidden('id', $this->plitem->id);

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
     * Initialise module object in admin/save_item mode.
     * @return void
     */
    private function init_admin_save_item() {
        global $camyks;

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Load object */
        $this->plitem->get_fromHeader();

        /* Save object */
        if ($this->plitem->save()) {
            if ($this->plid == 0 and $this->page_id > 0)
                /* update page information with object id for new content */
                $this->add_moduleContentToPage($this->page_id, $this->module_index, $this->plitem->id);
            $this->text = $camyks->get_translation('savedone');
        } else {
            $this->text = $camyks->get_translation('savefailed');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('mode'=>'modify_item', 'id'=>$this->plitem->id)));
    }
}
?>
