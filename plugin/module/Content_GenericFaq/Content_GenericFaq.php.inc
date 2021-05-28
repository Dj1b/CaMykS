<?php
/**
 * @brief Content_GenericFaq module.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Apr 2007
 * @date Modification: May 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_GenericFaq class.
 */
final class Content_GenericFaq extends Module {
    /**
     * var array $layouts_list
     * @brief List of client side layouts.
     */
    protected $layouts_list = array('box_list', 'box_listindex', 'box_listprefix');

    /**
     * var integer $faqpage
     * @brief Faq page id.
     */
    protected $faqpage;

    /**
     * var integer $faqsbypage
     * @brief Faq count in list page.
     */
    protected $faqsbypage = 20;

    /**
     * var array $status
     * @brief Faq status values.
     */
    protected $status = array(0 => 'inedition', 1 => 'inline');

    /**
     * var array $faqlist
     * @brief Faq list.
     */
    public $faqlist;

    /**
     * var Object $faqitem
     * @brief Faq item.
     */
    public $faqitem;

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('Content_GenericFaq', $path_type);

         /* Override Plugin variables */
        $this->plugin_package = 'Generic';
        $this->version = '1.0';

        /* Override Module variables */
        $this->type = 'content';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Load plugin libraries */
        $this->load_library('Content_GenericFaqList');
        $this->load_library('Content_GenericFaqItem');

        /* Initialise plugin libraries */
        $this->faqlist = new Content_GenericFaqList(0, $this);
        $this->faqitem = new Content_GenericFaqItem(0, $this);
    }

    /* Override Module methods */

    /**
     * Install module
     * @return boolean success
     */
    public function install() {
        return ($this->faqlist->install() and $this->faqitem->install() and parent::install());
    }

    /**
     * Uninstall module
     * @return boolean success
     */
    public function uninstall() {
        return $this->faqitem->uninstall() and $this->faqlist->uninstall();
    }

    /**
     * Check module installation.
     * @return boolean result
     */
    public function is_installed() {
        return $this->faqitem->is_installed();
    }

    /**
     * Return available content id/name as list.
     * @return array
     */
    public function get_contentList() {
        return $this->faqlist->get_namelist();
    }

    /**
     * Initialise module object in admin mode.
     * @return array
     */
    public function init_admin() {
        /* Generic pre-initialisation */
        parent::preInit_admin();

        /* Check right for this page */
        if ($this->check_right($this->page_id) === false)
            return $this->init_admin_pageAccessDenied();

        /* Load object data */
        $this->faqlist->id = isset ($_REQUEST['id']) ? (int)$_REQUEST['id'] : 0;

        /* Load mode to execute */
        $this->mode = isset ($_REQUEST['mode']) ? $_REQUEST['mode'] : 'modify';

        /* Execute mode */
        switch ($this->mode) {
            case 'save_list' :
                /* mode == save_list */
                $this->init_admin_save_list();
                break;
            case 'save_item' :
                /* mode == save_item */
                $this->init_admin_save_item();
                break;
            case 'edit_item' :
                /* mode == edit_item */
                $this->init_admin_edit_item();
                break;
            case 'move_item_up' :
                /* mode == move_item_up */
                $this->init_admin_move_item_up();
                $this->init_admin_edit_list();
                break;
            case 'move_item_down':
                /* mode == move_item_down */
                $this->init_admin_move_item_down();
                $this->init_admin_edit_list();
                break;
            case 'delete_item':
                /* mode == delete_item */
                $this->init_admin_delete_item();
                break;
            case 'edit_list':
            case 'modify' :
            default:
                /* mode == edit_list */
                $this->init_admin_edit_list();
                break;
        }

        /* Generic module init */
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

        /* Load faq list to display */
        $this->faqlist->id = $content;
        $this->faqlist->get();
        $this->faqlist->get_fromItems();

        /* Faq list initialisation */
        $this->init_site_list($params);

        /* Parent site initialisation */
        parent::init_site();
    }

    /* Specific admin mode methods */

    /**
     * Initialise module object in admin / save_list mode.
     * @return void
     */
    private function init_admin_save_list() {
        global $camyks;

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Load object */
        $this->faqlist->id = isset ($_REQUEST['id']) ? (int)$_REQUEST['id'] : 0;
        $this->faqlist->get_fromHeader();

        /* Save Object */
        if ($this->faqlist->save()) {
            /* Update page information with object id for new content */
            if ($id == 0 and $this->page_id > 0)
                $this->add_moduleContentToPage($this->page_id, $this->module_index, $this->faqlist->id);
            $this->text = $this->get_translation('listsaved');
        } else {
            $this->text = $this->get_translation('listnotsaved');
        }

        /* Redirect save page */
        $this->set_redirect ($this->get_adminLink(array('mode'=>'modify', 'id'=>$this->faqlist->id, 'page_id'=>$this->page_id, 'module_index'=>$this->module_index)));

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
    }

    /**
     * Initialise module object in admin / save_item mode.
     * @return void
     */
    private function init_admin_save_item() {
        global $camyks;

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Load object */
        $this->faqitem->id = isset ($_REQUEST['itemid']) ? (int)$_REQUEST['itemid'] : 0;
        $this->faqitem->get_fromHeader();

        /* Save object */
        if ($this->faqitem->save()) {
            $this->faqitem->get_fromItems();
            $this->text = $this->get_translation('itemsaved');
        } else {
            $this->text = $this->get_translation('itemnotsaved');
        }

        /* Redirect save page */
        $this->set_redirect ($this->get_adminLink(array('mode'=>'modify', 'id'=>$this->faqlist->id, 'page_id'=>$this->page_id, 'module_index'=>$this->module_index)));

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
    }

    /**
     * Init module object in admin / edit_item mode
     * @return void
     */
    private function init_admin_edit_item() {
        global $camyks;

        /* Load object data */
        $this->faqitem->id = isset ($_REQUEST['itemid']) ? (int)$_REQUEST['itemid'] : 0;
        $this->faqitem->get();
        $this->faqitem->get_fromItems();

        /* Set list id */
        if ($this->faqitem->id == 0)
            $this->faqitem->vars['listid'] = $this->faqlist->id;

        /* Build form object */
        $this->form = new HTMLForm('faqitem_form', $this->get_adminlink(array('mode'=>'save_item')), 'POST');
        $this->form->add_hidden('id', $this->faqitem->vars['listid']);
        $this->form->add_hidden('page_id', $this->page_id);
        $this->form->add_hidden('module_index', $this->module_index);
        $this->form->add_hidden('itemid', $this->faqitem->id);
        $this->form->add_hidden('listid', $this->faqitem->vars['listid']);

        /* Build buttons list */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'  => $camyks->get_adminLink(array(
                    'mode'      => 'edit_list',
                    'page_id'   => $this->page_id,
                    'id'        => $this->faqitem->vars['listid'],
                )),
            ),
            array(
                'title' => $camyks->get_translation('valid'),
                'link'  => $this->form->get_HTMLSubmitLink(),
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('admin_edit_item.html.inc');
    }

    /**
     * Initialise module object in admin / edit_list mode.
     * @return void
     */
    private function init_admin_edit_list() {
        global $camyks;

        /* Load object */
        $this->faqlist->get();
        $this->faqlist->get_fromItems();

        if ($this->faqlist->id != 0) {
            /* Load tabs javascript engine */
            $this->openTab = isset ($_REQUEST['openTab']) ? $_REQUEST['openTab'] : 'items';
            $this->tabObject = 'faqlist_tabObject';
            $this->add_JSEngineFile('object/ctab.js');
            $this->add_JSScript($this->tabObject.'= new CTab();');
            $this->add_JSScript($this->tabObject.'.init("properties", "'
                .$camyks->theme->parts['boxTabCSSStandart'].'","'
                .$camyks->theme->parts['boxTabCSSSelected'].'","'
                .$camyks->theme->parts['boxTabCSSRollover'].'");');
            $this->add_JSLoadScript($this->tabObject.'.mouseclick(\''.$this->openTab.'\');');

            $this->faqitems = $this->faqitem->get_adminlist($this->faqlist->id);
            $this->faqcount = $this->faqitem->get_listcount($this->faqlist->id);

            /* Build faq list links */
            $this->linkedit = $this->get_adminLink(array(
                'mode'          => 'edit_item',
                'id'            => $this->faqlist->id,
                'page_id'       => $this->page_id,
                'module_index'  => $this->module_index,
                'itemid'        => '',
            ));
            $this->linknew = $this->get_adminLink(array(
                'mode'          => 'edit_item',
                'id'            => $this->faqlist->id,
                'page_id'       => $this->page_id,
                'module_index'  => $this->module_index,
                'itemid'        => 0,
            ));
            $this->linkup = $this->get_adminLink(array(
                'mode'          => 'move_item_up',
                'id'            => $this->faqlist->id,
                'page_id'       => $this->page_id,
                'module_index'  => $this->module_index,
                'itemid'        => '',
            ));
            $this->linkdown = $this->get_adminLink(array(
                'mode'          => 'move_item_down',
                'id'            => $this->faqlist->id,
                'page_id'       => $this->page_id,
                'module_index'  => $this->module_index,
                'itemid'        => '',
            ));
            $this->linkdelete = $this->get_adminLink(array(
                'mode'          => 'delete_item',
                'id'            => $this->faqlist->id,
                'page_id'       => $this->page_id,
                'module_index'  => $this->module_index,
                'itemid'        => '',
            ));
        }

        /* Build form object */
        $this->form = new HTMLForm('faqlist_form', $this->get_adminlink(array('mode'=>'save_list')), 'POST');
        $this->form->add_hidden('id', $this->faqlist->id);
        $this->form->add_hidden('page_id', $this->page_id);
        $this->form->add_hidden('module_index', $this->module_index);

        if ($this->faqlist->id > 0) {
            /* Build tab list */
            $this->tabs = array(
                array(
                    'name'  => 'properties',
                    'title' => $this->get_translation('tabproperties'),
                ),
                array(
                    'name'  => 'items',
                    'title' => $this->get_translation('tabitems'),
                ),
            );
        }

        /* Build buttons list */
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

        /* Update layout */
        $this->set_selectedLayout('admin_edit_list.html.inc');
    }

    /**
     * Initialise module object in admin / move_item_up mode.
     * @return void
     */
    private function init_admin_move_item_up() {
        if (isset($_REQUEST['itemid'])) {
            $this->faqitem->id = (int)$_REQUEST['itemid'];
            $this->faqitem->get();
            $this->faqitem->move_up();
        }
    }

    /**
     * Initialise module object in admin / move_item_down mode.
     * @return void
     */
    private function init_admin_move_item_down() {
        if (isset($_REQUEST['itemid'])) {
            $this->faqitem->id = (int)$_REQUEST['itemid'];
            $this->faqitem->get();
            $this->faqitem->move_down();
        }
    }

    /**
     * Initialise module object in admin / delete_item mode.
     * @return void
     */
    private function init_admin_delete_item() {
        global $camyks;

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Delete object */
        $this->faqitem->id = isset ($_REQUEST['itemid']) ? (int)$_REQUEST['itemid'] : 0;
        if ($this->faqitem->delete()) {
            $this->text = $camyks->get_translation('deletedone');
        } else {
            $this->text = $camyks->get_translation('deletefailed');
        }

        /* Redirect save page */
        $this->set_redirect($this->get_adminLink(array(
            'mode'          => 'modify',
            'id'            => $this->faqlist->id,
            'page_id'       => $this->page_id,
            'module_index'  => $this->module_index,
        )));

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
    }

    /* Specific site mode methods */

    /**
     * Initialise module object in site / list mode.
     * @param array $params
     * @return void
     */
    public function init_site_list($params) {
        global $camyks;

        /* Load faq page to display */
        if (isset ($params['faqpage']) and $params['faqpage'] >= 0) {
            $this->faqpage = $params['faqpage'];
        } else {
            $this->faqpage = 0;
        }

        /* Load faq items to display from news list */
        $this->faqitems = $this->faqitem->get_siteList($this->faqlist->id, $this->faqpage, $this->faqlist->vars['count_list']);
        $this->faqcount = $this->faqitem->get_listcount($this->faqlist->id, 1, $camyks->current_language);

        /* Build link */
        if (($this->faqpage+1)*$this->faqlist->vars['count_list'] < $this->faqcount)
            $this->nextfaqs = $camyks->get_siteLink($camyks->contentPage->id, $camyks->contentPage->name, '', array('faqpage'=> $this->faqpage+1));
        else
            $this->nextfaqs = '';

        if ($this->faqpage > 0)
            $this->prevfaqs = $camyks->get_siteLink($camyks->contentPage->id, $camyks->contentPage->name, '', array('faqpage'=> $this->faqpage-1));
        else
            $this->prevfaqs = '';

        /* Build buttons */
        $this->buttons = array(
            array(
                'title' => $this->get_translation('previousfaqs'),
                'link' => $this->prevfaqs,
            ),
            array(
                'title' => $this->get_translation('page', array($this->faqpage+1)),
                'link' => '',
            ),
            array(
                'title' => $this->get_translation('nextfaqs'),
                'link' => $this->nextfaqs,
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('site_'.$this->faqlist->vars['layout_list'].'.html.inc');
    }
}
?>
