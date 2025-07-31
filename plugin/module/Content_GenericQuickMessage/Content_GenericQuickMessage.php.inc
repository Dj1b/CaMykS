<?php
/**
 * @brief Content_GenericQuickMessage module.
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
 * Content_GenericQuickMessage class.
 */
final class Content_GenericQuickMessage extends Module {
    /**
     * var Object $qmitem
     * @brief Quick message object.
     */
    public $qmitem;

    /**
     * var array $qmlist
     * @brief Quick message list.
     */
    protected $qmlist;

    /**
     * var integer $itemsbypage
     * @brief Indicates how many messages are visible in admin page.
     */
    protected $itemsbypage = 20;

    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('Content_GenericQuickMessage', $path_type);

        /* Overide Plugin variables */
        $this->plugin_package = 'Generic';
        $this->version = '1.0';

        /* Override Module variables */
        $this->type = 'content';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Load plugin libraries */
        $this->load_library('Content_GenericQuickMessageList');
        $this->load_library('Content_GenericQuickMessageItem');

        /* Initialise plugin libraries */
        $this->qmlist = new Content_GenericQuickMessageList(0, $this);
        $this->qmitem = new Content_GenericQuickMessageItem(0, $this);
    }

    /* Mark: Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return $this->qmitem->install() and $this->qmlist->install()
            and parent::install();
    }

    /**
     * Uninstall module.
     * @return boolean success
     */
    public function uninstall() {
        return $this->qmlist->uninstall() and $this->qmitem->uninstall()
            and parent::uninstall();
    }

    /**
     * Check module installation.
     * @return boolean result
     */
    public function is_installed() {
        return $this->qmlist->is_installed();
    }

    /**
     * Return available content id/name as list.
     * @return array
     */
    public function get_contentList() {
        return $this->qmlist->get_nameList();
    }

    /**
     * Initialise module object in admin mode
     * @return void
     */
    public function init_admin() {
        global $camyks;

        /* Generic pre-initialisation */
        parent::preInit_admin();

        /* Check permission for this page */
        if ($this->check_right($this->page_id) === false)
            return $this->init_admin_pageAccessDenied();

        /* Load item id */
        $this->listid = isset($_REQUEST['id']) ? (int)$_REQUEST['id'] : 0;
        $this->qmlist->id = $this->listid;

        /* Load action to execute */
        $this->mode = isset($_REQUEST['mode']) ? $_REQUEST['mode'] : '';

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
            case 'save_list':
                /* mode == save_list */
                $this->init_admin_save_list();
                break;
            case 'edit_list':
            default:
                /* mode == edit_list */
                $this->init_admin_edit_list();
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

        if (!isset($this->content)) {
            /* Add js to the page */
            $this->add_JSEngineFile('tool/mail.js');
            $this->add_JSFile('content_genericquickmessage.js');

            /* Create content list */
            $this->contents = array();
            $this->forms = array();
        }

        /* Add contents to list */
        $this->contents[$mindex] = new Content_GenericQuickMessageList($content, $this);
        $this->contents[$mindex]->get();
        $this->contents[$mindex]->get_fromItems();

        $this->forms[$mindex] = '';

        $this->contents[$mindex]->vars['panel'] = 'Messages'.$mindex;
        $this->add_JSScript('cgqm_panels["'.$mindex.'"] = "Messages'.$mindex.'";');

        if ($this->contents[$mindex]->vars['status'] == 0) {
            /* Deny new message */
            $this->contents[$mindex]->vars['save_message'] = $this->get_translation('message_closed');

        } else if ($this->contents[$mindex]->vars['status'] == 1 and (!isset($camyks->modules['Admin_GUAEManager']) or (($this->account = $camyks->modules['Admin_GUAEManager']->get_currentUser()) !== false and $this->account->id == 0)))    {
            /* Must be connected and registered to post message */
            $this->contents[$mindex]->vars['save_message'] = $this->get_translation('message_registered');
        } else if (isset($_REQUEST['qmsave']) and isset($_REQUEST['listid']) and $_REQUEST['listid'] == $content) {
            /* Save message */
            $this->qmitem->get_fromHeader();
            if ($this->qmitem->save()) {
                if ($this->contents[$mindex]->vars['validation'] == 0)
                    $this->contents[$mindex]->vars['save_message'] = $this->get_translation('message_saved');
                else
                    $this->contents[$mindex]->vars['save_message'] = $this->get_translation('message_savedadmin');
            } else {
                $this->contents[$mindex]->vars['save_message'] = $this->get_translation('message_notsaved');
            }
            $this->contents[$mindex]->vars['panel'] = 'Form'.$mindex;
            $this->add_JSScript('cgqm_panels["'.$mindex.'"] = "Form'.$mindex.'";');
            $this->add_JSLoadScript('setTimeout("content_genericquickmessage_swapPanels(\'Messages\', '.$mindex.');", 6000);');
        } else {
            /* Add form */
            $this->forms[$mindex] = new HTMLForm('qmf'.$this->contents[$mindex]->id, $camyks->get_siteCurrentLink(), 'POST');
            $this->forms[$mindex]->add_hidden('listid', $this->contents[$mindex]->id);
            $this->forms[$mindex]->add_hidden('qmsave', 1);
        }

        /* Get messages list */
        $this->contents[$mindex]->get_validatedMessages();

        /* Generic initialisation */
        parent::init_site();
    }

    /**
     * Display module object in site mode.
     * @param integer $mindex
     * @return void
     */
    public function display_site($mindex=null) {
        /* get module content */
        $this->content = $this->contents[$mindex];
        $this->form = $this->forms[$mindex];
        $this->mindex = $mindex;
        parent::display_site();
    }

    /* Mark: Admin initialise mode sub methods */

    /**
     * Initialise module object in admin/edit_list mode.
     * @return void
     */
    private function init_admin_edit_list() {
        global $camyks;

        /* Load help */
        $this->get_help();

        /* Load object */
        $this->qmlist->get();
        $this->qmlist->get_fromItems();

        /* Load tabs description */
        $this->tabs = array(array(
            'name'  => 'general',
            'title' => $this->get_translation('tabgeneral'),
        ));

        if ($this->qmlist->id > 0) {
            $this->tabs[] = array(
                'name'  => 'messages',
                'title' => $this->get_translation('tabmessages'),
            );
        }

        if ($this->help != null) {
            $this->tabs[] = array('name'=> 'help',
                                'title'=> $camyks->get_translation('help'));
        }

        /* Load tabs javascript engine */
        $this->tabObject = 'qml_tabObject';
        $this->add_JSEngineFile ('object/ctab.js');
        $this->add_JSScript($this->tabObject.' = new CTab();');
        $this->add_JSScript($this->tabObject.'.init("general", "'.$this->theme->parts['boxTabCSSStandart'].'","'.$this->theme->parts['boxTabCSSSelected'].'","'.$this->theme->parts['boxTabCSSRollover'].'");');
        $this->openTab = isset($_REQUEST['openTab'])?$_REQUEST['openTab']:'';
        if ($this->openTab != '')
            $this->add_JSLoadScript($this->tabObject.'.mouseclick("'.$this->openTab.'");');

        /* Build form */
        $this->form = new HTMLForm('qml_form', $this->get_adminlink(array('mode'=>'save_list')), 'POST');
        $this->form->add_hidden('page_id', $this->page_id);
        $this->form->add_hidden('module_index', $this->module_index);
        $this->form->add_hidden('id', $this->qmlist->id);

        /* Build interface buttons */
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
                'link'  => $this->form->get_HTMLSubmitLink(),
            ),
        );

        /* Build message list */
        if ($this->qmlist->id > 0) {
            /* Build list form */
            $this->listform = new HTMLForm('qml_listform', $this->get_adminLink(), 'POST');
            $this->listform->add_hidden('page_id', $this->page_id);
            $this->listform->add_hidden('module_index', $this->module_index);
            $this->listform->add_hidden('id', $this->qmlist->id);
            $this->listform->add_hidden('openTab', 'messages');

            /* Load header values */
            $this->listpage = isset ($_REQUEST['listpage']) ? $_REQUEST['listpage'] : 0;
            $this->liststatus = isset ($_REQUEST['liststatus']) ? $_REQUEST['liststatus'] : -1;

            /* Build query */
            $query = 'listid='.$this->qmlist->id;
            if ($this->liststatus >= 0) {
                $query .= ' and status='.$this->liststatus;
            }

            /* Load report list */
            $this->qmcount = $this->qmitem->get_objectCount($query);
            $this->pages = ceil($this->qmcount / $this->itemsbypage);
            $this->listpage = min($this->listpage, $this->pages);
            $this->qmitems = $this->qmitem->get_objectList(false, $query, $this->listpage*$this->itemsbypage, $this->itemsbypage, 'ndate', 'desc');

            /* Build edit item link */
            $this->editItemLink = $this->get_adminLink(array('id'=>$this->qmlist->id, 'page_id'=>$this->page_id, 'module_index'=>$this->module_index, 'mode'=>'edit_item', 'messageid'=>''));
        }
    }

    /**
     * Initialise module object in admin/save_list mode.
     * @return void
     */
    private function init_admin_save_list() {
        global $camyks;

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Save list */
        $this->qmlist->get_fromHeader();
        if ($this->qmlist->save()) {
            /* Update page information with object id for new content */
            if ($this->listid == 0 and $this->page_id > 0)
                $this->add_moduleContentToPage($this->page_id, $this->module_index, $this->qmlist->id);
            $this->text = $camyks->get_translation('savedone');
        } else {
            $this->text = $camyks->get_translation('savefailed');
        }
        $this->qmlist->get_fromItems();

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($camyks->get_adminLink(array('mode'=>'edit_list', 'id'=>$this->qmlist->id, 'page_id'=>$this->page_id, 'module_index'=>$this->module_index)));
    }

    /**
     * Initialise module object in admin/edit_item mode.
     * @return void
     */
    private function init_admin_edit_item() {
        global $camyks;

        /* Load list linfos */
        $this->qmlist->get();
        $this->qmlist->get_fromItems();

        /* Load item */
        $this->qmitem->id = isset($_REQUEST['messageid']) ? (int)$_REQUEST['messageid'] : 0;
        $this->qmitem->get();
        $this->qmitem->get_fromItems();

        /* Load form */
        $this->form = new HTMLForm('qmi_form', $camyks->get_adminlink(array('mode'=>'save_item')), 'POST');
        $this->form->add_hidden('page_id', $this->page_id);
        $this->form->add_hidden('module_index', $this->module_index);
        $this->form->add_hidden('id', $this->qmlist->id);
        $this->form->add_hidden('listid', $this->qmlist->id);
        $this->form->add_hidden('messageid', $this->qmitem->id);

        /* Build  buttons */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'  => $camyks->get_adminLink(array(
                    'mode'          => 'edit_list',
                    'id'            => $this->qmlist->id,
                    'page_id'       => $this->page_id,
                    'module_index'  => $this->module_index,
                    'openTab'       => 'messages'
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
     * Initialise module object in admin/save_item mode.
     * @return void
     */
    private function init_admin_save_item() {
        global $camyks;

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Save item */
        $this->qmitem->id = isset($_REQUEST['messageid']) ? (int)$_REQUEST['messageid'] : 0;
        $this->qmitem->get_fromHeader();
        if ($this->qmitem->save())
            $this->text = $camyks->get_translation('savedone');
        else
            $this->text = $camyks->get_translation('savefailed');
        $this->qmitem->get_fromItems();

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($camyks->get_adminLink(array('mode'=>'edit_list', 'id'=>$this->qmlist->id, 'page_id'=>$this->page_id, 'module_index'=>$this->module_index, 'openTab'=>'messages')));
    }

    /* Mark: Specific site tool methods */

    /**
     * Return list object validation value.
     * @param integer $listid
     * @return integer
     */
    protected function get_listObject($listid) {
        if ($this->qmlist->id != $listid and $this->qmlist->id != 0) {
            $qml = new Content_GenericQuickMessageList($listid, $this);
            $qml->get();
            $qml->get_fromItems();
            return $qml;
        } else {
            if ($this->qmlist->id == 0) {
                $this->qmlist->id = $listid;
            }
            if (!isset($this->qmlist->vars['validation'])) {
                $this->qmlist->get();
                $this->qmlist->get_fromItems();
            }
            return $this->qmlist;
        }
    }
}
?>
