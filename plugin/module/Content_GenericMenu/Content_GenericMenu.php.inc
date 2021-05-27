<?php
/**
 * @brief Content_GenericMenu module.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jul 2007
 * @date Modification: May 2021
 * @copyright 2007 - 2021 Ideogram Design
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_GenericMenu class.
 */
final class Content_GenericMenu extends Module {
    /**
     * var Object $menuitem
     * @brief Menu item.
     */
    protected $menuitem;

    /**
     * var array $layouts
     * @brief List of layouts.
     */
    protected $layouts = array();

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('Content_GenericMenu', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'Generic';

        /* Override Module variables */
        $this->type = 'content';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* load plugin libraries */
        $this->load_library('Content_GenericMenuItem');

        /* Initialise plugin libraries */
        $this->menuitem = new Content_GenericMenuItem(0, $this);

        /* Initialise plugin variables */
        foreach (array('horizontal_bottomlayers', 'vertical_rightlayers', 'vertical_leftlayers', 'vertical_inline', 'custom') as $l) {
            $this->layouts[$l] = $this->get_translation('layout_'.$l);
        }
    }

    /* Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return $this->menuitem->install() and parent::install();
    }

    /**
     * Uninstall module.
     * @return boolean success
     */
    public function uninstall() {
        if ($this->menuitem->uninstall()) {
            return parent::uninstall();
        }
        return false;
    }

    /**
     * Check module installation.
     * @return boolean result
     */
    public function is_installed() {
        return $this->menuitem->is_installed();
    }

    /**
     * Return available content ids as list.
     * @return array
     */
    public function get_contentList() {
        return $this->menuitem->get_nameList();
    }

    /**
     * Initialise module object in admin mode.
     * @return void
     */
    public function init_admin() {
        global $camyks;

        /* Generic pre-initialisation */
        parent::preInit_admin();

        /* Check right for this page */
        if ($this->check_right($this->page_id) === false)
            return $this->init_admin_pageAccessDenied();

        /* Load menu item */
        $this->menuid = isset($_REQUEST['id']) ? (int)$_REQUEST['id'] : 0;
        $this->menuitem->id = $this->menuid;

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
            /* get site pages */
            $this->pages = $camyks->modules['Admin_ContentPage']->get_sitePages();

            /* update styles */
            $this->add_styleFile('genericmenu.css');

            /* get contents list */
            $this->contents = array();
        }

        /* Load item */
        $this->contents[$mindex] = new Content_GenericMenuItem($content, $this);
        $this->contents[$mindex]->get();
        $this->contents[$mindex]->get_fromItems();

        /* Check if "root" page exits */
        if (isset ($this->pages[$this->contents[$mindex]->vars['root']])) {
            /* Load root page */
            $this->contents[$mindex]->vars['rootpage'] = &$this->pages[$this->contents[$mindex]->vars['root']];

            /* Specific layout initialisation */
            switch ($this->contents[$mindex]->vars['layout']) {
                case 'horizontal_bottomlayers':
                    $this->contents[$mindex]->vars['layeredMenu'] = $this->init_site_buildlayers($mindex, 'bottom');
                    break;
                case 'vertical_rightlayers':
                    $this->contents[$mindex]->vars['layeredMenu'] = $this->init_site_buildlayers($mindex, 'right');
                    break;
                case 'vertical_leftlayers':
                    $this->contents[$mindex]->vars['layeredMenu'] = $this->init_site_buildlayers($mindex, 'left');
                    break;
                case 'vertical_inline':
                case 'custom':
                default:

            }
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
        $this->mindex = $mindex;
        $this->layeredMenu = &$this->contents[$mindex]->vars['layeredMenu'];
        $this->root = &$this->contents[$mindex]->vars['rootpage'];

        /* Update layout */
        $this->set_selectedLayout('site_'.$this->contents[$mindex]->vars['layout'].'.html.inc');

        /* Execute generic display */
        parent::display_site();
    }

    /* Specific admin mode methods */

    /**
     * Initialise module object in admin/modify_item mode.
     * @return void
     */
    private function init_admin_modify_item() {
        global $camyks;

        /* Load help */
        $this->get_help();

        /* Load object */
        $this->menuitem->get(true);
        $this->menuitem->get_fromItems();

        /* Load tabs */
        $this->tabs = array(
            array(
                'name'  => 'general',
                'title' => $this->get_translation('tabgeneral'),
            ),
        );

        if ($this->help != null) {
            $this->tabs[] = array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help'),
            );
        }

        /* Insert tabs javascript */
        $this->tabObject = 'menu_tabObject';
        $this->add_JSEngineFile ('object/ctab.js');
        $this->add_JSScript($this->tabObject.' = new CTab();');
        $this->add_JSScript($this->tabObject.'.init("general", "'.$this->theme->parts['boxTabCSSStandart'].'","'.$this->theme->parts['boxTabCSSSelected'].'","'.$this->theme->parts['boxTabCSSRollover'].'");');

        /* Build form */
        $this->form = new HTMLForm('genericmenu_form', $this->get_adminlink(array('mode'=>'save_item')), 'POST');
        $this->form->add_hidden('page_id', $this->page_id);
        $this->form->add_hidden('module_index', $this->module_index);
        $this->form->add_hidden('id', $this->menuitem->id);

        /* Build interface buttons */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'  => $camyks->get_adminLink('Admin_ContentPage', array('mode'=>'modify', 'page_id'=>$this->page_id, 'openTab'=>'content')),
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
    public function init_admin_save_item() {
        global $camyks;

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Save menu */
        $this->menuitem->get_fromHeader();
        if ($this->menuitem->save()) {
            if ($this->menuid == 0 and $this->page_id > 0)
                /* Update page information with object id for new content */
                $this->add_moduleContentToPage($this->page_id, $this->module_index, $this->menuitem->id);
            $this->text = $camyks->get_translation('savedone');
        } else {
            $this->text = $camyks->get_translation('savefailed');
        }
        $this->menuitem->get_fromItems();

        /* Update layout */
        $this->selected_layout = 'admin_message.html.inc';
        $this->selected_layout_location = 'camyks';
        $this->set_redirect($camyks->get_adminLink(array('mode'=>'modify_item', 'id'=>$this->menuitem->id)));
    }

    /* Specific site tool methods */

    /**
     * Initialise module object in site mode.
     * @param integer $mindex
     * @param string $location
     * @return void
     */
    private function init_site_buildlayers($mindex, $location) {
        /* Insert layered engine */
        $this->add_JSEngineFile('tool/htmlelement.js');
        $this->add_JSEngineFile('tool/clientenv.js');
        $this->add_JSEngineFile('object/cmenu.js');
        $this->add_JSLoadScript('globalCMenu.init();');

        /* Initialise layered menu */
        $layeredMenu = array();

        /* Build menu */
        if ($this->contents[$mindex]->vars['levels'] > 1) {
            foreach ($this->contents[$mindex]->vars['rootpage']->children as $p) {
                $page = $this->pages[$p];
                if (count($page->children) > 0) {
                    $this->add_JSScript('var cgm'.$mindex.'_'.$page->name.'Menu = new CMenu("cgm'.$mindex.'_'.$page->name.'Menu", null, "cgm'.$mindex.'_'.$page->name.'Button", "'.$location.'");');
                    $this->add_JSScript('globalCMenu.registerMenu(cgm'.$mindex.'_'.$page->name.'Menu);');
                    $m = array();
                    foreach ($page->children as $_p) {
                        $_page = $this->pages[$_p];
                        if ((!isset($_page->metas['menu']) or $_page->metas['menu']['content'] != 'hidden') and $_page->active == 1)
                            $m[] = array('menu' => 'cgm_'.$_page->name.'Menu',
                                'name'      => $_page->name,
                                'title'     => $_page->shorttitle != '' ? $_page->shorttitle : ($_page->title != '' ? $_page->title : $_page->name),
                                'icon'      => '',
                                'url'       => $_page->get_siteLink(),
                                'children'  => array(),
                            );
                    }
                    $layeredMenu['cgm'.$mindex.'_'.$page->name.'Menu'] = $m;
                }
            }
        }
        return $layeredMenu;
    }
}
?>
