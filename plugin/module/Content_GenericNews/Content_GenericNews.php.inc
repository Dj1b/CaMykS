<?php
/**
 * @brief Content_GenericNews module.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Mar 2007
 * @date Modification: Jul 2025
 * @copyright 2007 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_GenericNews class.
 */
final class Content_GenericNews extends Module {
    /**
     * var array $layouts_list
     * @brief List of available layouts to display lists.
     */
    protected $layouts_list = array('box_list_titleonly', 'box_list_complete', 'box_list_completebyday', 'box_list_completebymonth', 'box_list_completebyyear', 'custom');

    /**
     * var array $layouts_item
     * @brief List of available layouts to display items.
     */
    protected $layouts_item = array('box_item_complete');

    /**
     * var integer $newsbypage
     * @brief Stores how many news to display in admin page.
     */
    protected $newsbypage = 16;

    /**
     * var array $status
     * @brief Available statuses for items.
     */
    protected $status = array(0 => 'inedition', 1 => 'inline');

    /**
     * var array $status
     * @brief Available statuses for items.
     */
    protected $newspage;

    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('Content_GenericNews', $path_type);

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
        $this->load_library('Content_GenericNewsList');
        $this->load_library('Content_GenericNewsItem');

        /* Initialise plugin libaries */
        $this->newslist = new Content_GenericNewsList(0, $this);
        $this->newsitem = new Content_GenericNewsItem(0, $this);
    }

    /* Mark: Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return ($this->newslist->install() and $this->newsitem->install() and parent::install());
    }

    /**
     * Uninstall module.
     * @return boolean success
     */
    public function uninstall() {
        return $this->newsitem->uninstall() and $this->newslist->uninstall();
    }

    /**
     * Check module installation.
     * @return boolean result
     */
    public function is_installed() {
        return $this->newsitem->is_installed();
    }

    /**
     * Return available content id/name as list.
     * @return array
     */
    public function get_contentList() {
        return $this->newslist->get_namelist();
    }

    /**
     * Initialise objects when in admin mode.
     * @return void
     */
    public function init_admin() {
        /* Pre-initialise module */
        parent::preInit_admin();

        /* Check permission for this page */
        if ($this->check_right($this->page_id) === false)
            return $this->init_admin_pageAccessDenied();

        /* Load mode to execute */
        $this->mode = isset($_REQUEST['mode']) ? $_REQUEST['mode'] : 'modify';

        /* Initialise module with mode */
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
            case 'edit_list':
            case 'modify' :
            default:
                /* mode == edit_list */
                $this->init_admin_edit_list();
                break;
        }

        /* Generic module Initialise */
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

        /* Add email management javascripts */
        $this->add_JSEngineFile('tool/mail.js');

        /* get news list to display */
        $this->newslist->id = $content;
        $this->newslist->get();
        $this->newslist->get_fromItems();

        if (isset ($params['newsitem']) and $params['newsitem'] >= 0) {
            /* get single item initialisation */
            $this->init_site_item($params);
        } else {
            /* get news list initialisation */
            $this->init_site_list($params);
        }

        /* Generic module Initialise */
        parent::init_site();
    }

    /* Mark: Admin initialise mode sub methods */

    /**
     * Initialise admin page when mode is save_list.
     * @return void
     */
    private function init_admin_save_list() {
        global $camyks;

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Load object */
        $this->newslist->id = isset($_REQUEST['id']) ? (int)$_REQUEST['id'] : 0;
        $this->newslist->get_fromHeader();

        /* Save object */
        if ($this->newslist->save()) {
            /* Update page information with object id for new content */
            if ($id == 0 and $this->page_id > 0)
                $this->add_moduleContentToPage($this->page_id, $this->module_index, $this->newslist->id);
            $this->text = $this->get_translation('newslistsaved');
        } else {
            $this->text = $this->get_translation('newslistnotsaved');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('id'=>$this->newslist->id, 'mode'=>'modify')));
    }

    /**
     * Initialise admin page when mode is save_item.
     * @return void
     */
    private function init_admin_save_item() {
        global $camyks;

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Load object */
        $this->newsitem->id = isset($_REQUEST['id']) ? (int)$_REQUEST['id'] : 0;
        $this->newsitem->get_fromHeader();

        /* Save object */
        if ($this->newsitem->save()) {
            $this->newsitem->get_fromItems();
            /* Redirect save page */
            $this->text = $this->get_translation('newsitemsaved');
        } else {
            $this->text = $this->get_translation('newsitemsaved');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('id'=>$this->newslist->vars['listid'], 'mode'=>'modify')));
    }

    /**
     * Initialise admin page when mode is edit_item.
     * @return void
     */
    private function init_admin_edit_item() {
        global $camyks;

        /* Load object data */
        $this->newsitem->id = isset($_REQUEST['newsitemid']) ? (int)$_REQUEST['newsitemid'] : 0;
        $this->newsitem->get();
        $this->newsitem->get_fromItems();

        if ($this->newsitem->id == 0)
            $this->newsitem->vars['listid'] = isset($_REQUEST['listid']) ? (int)$_REQUEST['listid']:0;

        /* Build form object */
        $this->form = new HTMLForm('newsitem_form', $this->get_adminlink(array('mode'=>'save_item')), 'POST');
        $this->form->add_hidden('id', $this->newsitem->id);
        $this->form->add_hidden('listid', $this->newsitem->vars['listid']);
        $this->form->add_hidden('author', $this->newsitem->vars['author']);
        $this->form->add_hidden('page_id', $this->page_id);
        $this->form->add_hidden('module_index', $this->module_index);

        /* Build buttons list */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'  => $this->get_adminLink(array(
                    'mode'      => 'edit_list',
                    'page_id'   => $this->page_id,
                    'id'        => $this->newsitem->vars['listid'],
                )),
            ),
            array(
                'title' => $camyks->get_translation('valid'),
                'link'  => $this->form->get_HTMLSubmitLink(),
            )
        );

        /* Update layout */
        $this->set_selectedLayout('admin_edit_item.html.inc');
    }

    /**
     * Initialise admin page when mode is edit_list.
     * @return void
     */
    private function init_admin_edit_list() {
        global $camyks;

        /* Load object data */
        $this->newslist->id = isset($_REQUEST['id']) ? (int)$_REQUEST['id'] : 0;
        $this->newslist->get();
        $this->newslist->get_fromItems();
        if ($id > 0) {
            /* Load tabs javascript engine */
            $this->openTab = isset ($_REQUEST['openTab']) ? $_REQUEST['openTab'] : 'newsitems';
            $this->tabObject = 'newslist_tabObject';
            $this->add_JSEngineFile ('object/ctab.js');
            $this->add_JSScript($this->tabObject.' = new CTab();');
            $this->add_JSScript($this->tabObject.'.init("properties", "'.$camyks->theme->parts['boxTabCSSStandart'].'","'.$camyks->theme->parts['boxTabCSSSelected'].'","'.$camyks->theme->parts['boxTabCSSRollover'].'");');
            $this->add_JSLoadScript($this->tabObject.'.mouseclick(\''.$this->openTab.'\');');

            /* Load news list */
            $this->newspage = isset($_REQUEST['newspage']) ? (int)$_REQUEST['newspage'] : 0;
            if (!($this->newspage >= 0))
                $this->newspage = 0;
            $this->newsitems = $this->newsitem->get_adminlist($this->newslist->id, $this->newspage, $this->newsbypage);
            $this->newscount = $this->newsitem->get_listcount ($this->newslist->id);

            /* Build news list link */
            $this->linknext = $this->get_adminLink(array(
                'mode'      => $this->mode,
                'id'        => $this->newslist->id,
                'openTab'   => 'newsitems',
                'newspage'  => $this->newspage+1,
            ));
            $this->linkprevious = $this->get_adminLink(array(
                'mode'      => $this->mode,
                'id'        => $this->newslist->id,
                'openTab'   => 'newsitems',
                'newspage'  => $this->newspage-1,
            ));
            $this->linkedit = $this->get_adminLink(array(
                'mode'          => 'edit_item',
                'listid'        => $this->newslist->id,
                'newsitemid'    => '',
            ));
            $this->linknew = $this->get_adminLink(array(
                'mode'          => 'edit_item',
                'listid'        => $this->newslist->id,
                'newsitemid'    => 0,
            ));
        }

        /* Build form object */
        $this->form = new HTMLForm('newslist_form', $this->get_adminlink(array('mode'=>'save_list')), 'POST');
        $this->form->add_hidden('id', $this->newslist->id);
        $this->form->add_hidden('page_id', $this->page_id);
        $this->form->add_hidden('module_index', $this->module_index);

        if ($this->newslist->id > 0) {
            /* tab list for tabs list */
            $this->tabs = array(
                array(
                    'name'  => 'properties',
                    'title' => $this->get_translation('tabproperties'),
                ),
                array(
                    'name'  => 'newsitems',
                    'title' => $this->get_translation('tabnewsitems'),
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
                    'openTab'   => 'content'
                )),
            ),
            array(
                'title' => $camyks->get_translation('valid'),
                'link'  => $this->form->get_HTMLSubmitLink()
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('admin_edit_list.html.inc');
    }

    /* Specific site mode methods */

    /**
     * Initialise module object in site/list mode
     * @param array $params
     * @return void
     */
    private function init_site_list($params) {
        global $camyks;

        /* Load news page to display */
        if (isset ($params['newspage']) and $params['newspage'] >= 0)
            $this->newspage = $params['newspage'];
        else
            $this->newspage = 0;

        /* Load news items to display from news list */
        $this->newsitems = $this->newsitem->get_siteList($this->newslist->id, $this->newspage, $this->newslist->vars['count_list']);
        $this->newscount = $this->newsitem->get_listcount($this->newslist->id, 1, $camyks->current_language, true);

        /* Build link */
        if (($this->newspage+1)*$this->newslist->vars['count_list'] < $this->newscount)
            $this->nextnews = $camyks->get_siteLink($camyks->contentPage->id, $camyks->contentPage->name, '', array('newspage'=> $this->newspage+1));
        else
            $this->nextnews = '';

        if ($this->newspage > 0)
            $this->prevnews = $camyks->get_siteLink($camyks->contentPage->id, $camyks->contentPage->name, '', array('newspage'=> $this->newspage-1));
        else
            $this->prevnews = '';


        /* Build buttons list */
        $this->buttons = array(
            array(
                'title' => $this->get_translation('previousnews'),
                'link'  => $this->prevnews,
            ),
            array(
                'title' => $this->get_translation('page', array($this->newspage+1)),
                'link'  => '',
            ),
            array(
                'title' => $this->get_translation('nextnews'),
                'link'  => $this->nextnews,
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('site_'.$this->newslist->vars['layout_list'].'.html.inc');
    }

    /**
     * Initialise module object in site/item mode
     * @param array $params
     * @return void
     */
    private function init_site_item($params) {
        global $camyks;

        /* Load news item object */
        $this->newsitem->id = (int)$params['newsitem'];
        if ($this->newsitem->get() === false)
            $this->init_site_list();
        $this->newsitem->get_fromItems();

        /* Check if object is valid */
        if (($this->newsitem->vars['language'] != $camyks->current_language) or ($this->newsitem->vars['status'] == 0) or ($this->newsitem->vars['listid'] != $this->newslist->id))
            return $this->init_site_list();

        /* Build buttons list */
        $this->buttons = array(
            array(
                'title' => $this->get_translation('back'),
                'link' => $camyks->get_siteLink($camyks->contentPage->id, $camyks->contentPage->name),
            )
        );

        /* set layout to display */
        $this->set_selectedLayout('site_'.$this->newslist->vars['layout_item'].'.html.inc');
        return true;
    }

    /* Specific site tool methods */

    /**
     * Return current page site link for given news item.
     * @param integer $id
     * @return string
     */
    protected function get_singlenewslink($id) {
        global $camyks;

        return $camyks->get_siteLink($camyks->contentPage->id, $camyks->contentPage->name, '', array('newsitem'=>$id));
    }
}
?>
