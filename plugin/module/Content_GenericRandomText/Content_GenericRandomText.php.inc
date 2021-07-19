<?php
/**
 * @brief Content_GenericRandomText module.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Mar 2007
 * @date Modification: Jul 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_GenericRandomText class.
 */
final class Content_GenericRandomText extends Module {
    /**
     * var Object $gitem
     * @brief Text object.
     */
    protected $gitem;

    /**
     * var array $glist
     * @brief Text list.
     */
    protected $glist;

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('Content_GenericRandomText', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'Generic';

        /* Override Module variables */
        $this->type = 'content';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'skymac.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Load plugin libraries */
        $this->load_library('GenericRandomTextItem');
        $this->load_library('GenericRandomTextList');

        /* Initialise plugin libraries */
        $this->gitem = new GenericRandomTextItem(0, $this);
        $this->glist = new GenericRandomTextList(0, $this);
    }

    /* Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return $this->glist->install() and $this->gitem->install()
            and parent::install();
    }

    /**
     * Uninstall module.
     * @return boolean success
     */
    public function uninstall() {
        return $this->glist->uninstall() and $this->gitem->uninstall() and parent::uninstall();
    }

    /**
     * Check module installation.
     * @return boolean result
     */
    public function is_installed() {
        return $this->gitem->is_installed();
    }

    /**
     * Return available content id/name as list.
     * @return array
     */
    public function get_contentList() {
        return $this->glist->get_namelist();
    }

    /**
     * Initialise objects when in admin mode.
     * @return void
     */
    function init_admin() {
        /* Generic pre-initialisation */
        parent::preInit_admin();

        /* Check permission for this page */
        if ($this->check_right($this->page_id) === false)
            return $this->init_admin_pageAccessDenied();

        /* Load mode to execute */
        $this->mode = isset ($_REQUEST['mode']) ? $_REQUEST['mode'] : 'edit_list';

        /* Execute action */
        switch ($this->mode) {
            case 'save_item':
                /* mode == save_item */
                $this->init_admin_save_item();
                break;
            case 'edit_item':
                /* mode == edit_item */
                $this->init_admin_edit_item();
                break;
            case 'delete_item':
                /* mode == delete_item */
                $this->init_admin_delete_item();
                break;
            case 'save_list' :
                /* mode == save_list */
                $this->init_admin_save_list();
            break;
            case 'edit_list' :
            default:
                /* mode == edit_list */
                $this->init_admin_edit_list();
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
        global $camyks;

        /* Load layout list */
        $this->get_layoutlist();

        /* Check for session values */
        if ($camyks->get_sessionValue('grt'.$content.'_layout') != null) {
            $this->selected_layout = 'site_'.$camyks->get_sessionValue('grt'.$content.'_layout').'html.inc';
            $this->text = $camyks->get_sessionValue('grt'.$content.'_content');
        } else {
            /* Load object */
            $this->glist->id = $content;
            $this->glist->get();
            $this->glist->get_fromItems();
            $this->glist->get_itemList();

            /* Update layout */
            $this->selected_layout = 'site_'.$this->glist->vars['layout'].'.html.inc';

            /* Get text to display */
            $randoms = array();
            foreach ($this->glist->vars['items'] as $items) {
                for($i=0; $i< $items->vars['weight']; $i++) {
                    $randoms[] = $items->id;
                }
            }

            /* Execute random check */
            $selected = $randoms[rand(0, count($randoms)-1)];

            /* Load text to display */
            $this->text = $this->glist->vars['items'][$selected]->vars['content'];

            if ($this->glist->vars['sessionkeep'] == 1) {
                $camyks->set_sessionValue('grt'.$content.'_layout', $this->glist->vars['layout']);
                $camyks->set_sessionValue('grt'.$content.'_content', $this->text);
            }
        }

        /* Generic module initialisation */
        parent::init_site();
    }

    /* specific admin mode methods */

    /**
     * Initialise module object in admin/save_list mode.
     * @return void
     */
    private function init_admin_save_list() {
        global $camyks;

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Save list */
        $this->glist->id = isset($_REQUEST['id']) ? (int)$_REQUEST['id'] : 0;
        $this->glist->get_fromHeader();
        if ($this->glist->save()) {
            $this->text = $camyks->get_translation('savedone');
            /* Update page information with object id for new content */
            if ($id == 0 and $this->page_id > 0)
                $this->add_moduleContentToPage($this->page_id, $this->module_index, $this->glist->id);
        } else {
            $this->text = $camyks->get_translation('savefailed');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('id' => $this->glist->id, 'page_id'=>$this->page_id, 'module_index'=>$this->module_index)));
    }

    /**
     * Initialise module object in admin/edit_list mode.
     * @return void
     */
    private function init_admin_edit_list() {
        global $camyks;

        $this->get_layoutlist();

        $this->glist->id = isset($_REQUEST['id']) ? $_REQUEST['id'] : 0;
        $this->glist->get();
        $this->glist->get_fromItems();
        $this->glist->get_itemList();

        /* Build form */
        $this->form = new HTMLForm('genericrandomtextlist', $this->get_adminLink(), 'POST');
        $this->form->add_hidden('mode', 'save_list');
        $this->form->add_hidden('id', $this->glist->id);
        $this->form->add_hidden('module_index', $this->module_index);
        $this->form->add_hidden('page_id', $this->page_id);

        /* Build tabs */
        if ($this->glist->id > 0) {
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

            /* Add javascript files and scripts */
            $this->add_JSEngineFile('object/ctab.js');
            $this->tabObject = 'randomText_tabObject';
            $this->add_JSScript($this->tabObject.' = new CTab();');
            $this->add_JSScript($this->tabObject.'.init("properties", "'.$this->theme->parts['boxTabCSSStandart'].'","'.$this->theme->parts['boxTabCSSSelected'].'","'.$this->theme->parts['boxTabCSSRollover'].'");');
        }

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

        /* Build links */
        $this->edittextlink = $this->get_adminLink(array('mode'=>'edit_item', 'listid'=>$this->glist->id, 'page_id'=>$this->page_id, 'module_index'=>$this->module_index, 'textid'=>''));
        $this->add_JSScript('var deleteTextLink="'.$this->get_adminJSLink(array('mode'=>'delete_item', 'listid'=>$this->glist->id, 'page_id'=>$this->page_id, 'module_index'=>$this->module_index, 'textid'=>'')).'";');
        $this->add_JSScript('var deleteTextMessage="'.string_html2Text($this->get_translation('deletemessage')).'";');
        $this->deleteTextLink = 'javascript:adminengine_confirmRedirect(deleteTextLink+%s, deleteTextMessage);';
    }

    /**
     * Initialise module object in admin/save_item mode.
     * @return void
     */
    private function init_admin_save_item() {
        global $camyks;

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Ssave list */
        $this->gitem->id = isset($_REQUEST['textid']) ? (int)$_REQUEST['textid'] : 0;
        $this->gitem->get_fromHeader();
        $this->gitem->get_fromItems();
        if ($this->gitem->save()) {
            $this->text = $camyks->get_translation('savedone');
        } else {
            $this->text = $camyks->get_translation('savefailed');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('id' => $this->gitem->vars['listid'], 'page_id'=>$this->page_id, 'module_index'=>$this->module_index)));
    }

    /**
     * Initialise module object in admin/edit_item mode.
     * @return void
     */
    private function init_admin_edit_item() {
        global $camyks;

        /* Load item object */
        $this->gitem->id = isset($_REQUEST['textid']) ? (int)$_REQUEST['textid'] : 0;
        $this->gitem->get();
        $this->gitem->get_fromItems();
        $this->gitem->vars['listid'] = isset($_REQUEST['listid']) ? (int)$_REQUEST['listid'] : 0;

        /* Build form */
        $this->form = new HTMLForm('genericrandomtextlist', $camyks->get_adminLink($this->name), 'POST');
        $this->form->add_hidden('mode', 'save_item');
        $this->form->add_hidden('textid', $this->gitem->id);
        $this->form->add_hidden('module_index', $this->module_index);
        $this->form->add_hidden('page_id', $this->page_id);
        $this->form->add_hidden('listid', $this->gitem->vars['listid']);

        /* Build interface buttons */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'  => $this->get_adminLink(array('mode'=>'edit_list', 'id'=>$this->gitem->vars['listid'], 'page_id'=> $this->page_id, 'module_index'=>$this->module_index))
            ),
            array(
                'title'=>$camyks->get_translation('valid'),
                'link'=> $this->form->get_HTMLSubmitLink(),
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('admin_edit_item.html.inc');
    }

    /**
     * Initialise module object in admin/delete_item mode.
     * @return void
     */
    private function init_admin_delete_item() {
        global $camyks;

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Load item object */
        $this->gitem->id = isset($_REQUEST['textid']) ? (int)$_REQUEST['textid'] : 0;
        $this->gitem->get();
        $listid = $this->gitem->_libItems['listid']->value;

        /* Delete object */
        if ($this->gitem->delete() >= 1) {
            $this->text = $camyks->get_translation('deletedone');
        } else {
            $this->text = $camyks->get_translation('deletefailed');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($camyks->get_adminLink(array('id'=>$listid, 'page_id'=>$this->page_id, 'module_index'=>$this->module_index)));
    }

    /* Specific tool methods */

    /**
     * Return layout list.
     * @return void
     */
    private function get_layoutList() {
        $this->layoutlist = array(
            'classic'   => $this->get_translation('layout_classic'),
            'boxed'     => $this->get_translation('layout_boxed'),
        );
    }
}
?>
