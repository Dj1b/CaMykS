<?php
/**
 * @brief Admin_MyMessages Module
 * <br /> Manages messages sent between admin users.
 * @details Plugin, Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jun 2007
 * @date Modification: Jan 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_MyMessages class.
 */
final class Admin_MyMessages extends Module {
    /**
    * var Object $message
    * @brief Message object.
    */
    protected $message;

    /**
    * var integer $maxmessages
    * @brief Maximum amount of message stored in database.
    */
    public $maxmessages = 20;

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('Admin_MyMessages', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* Override Module variables */
        $this->type = 'admin';
        $this->admin_type = 'personal';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Load plugin libraries */
        $this->load_library('Admin_InternalMessage');

        /* Load library object */
        $this->message = new Admin_InternalMessage(0, $this);
    }

    /* Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return $this->message->install() and parent::install();
    }

    /**
     * Uninstall module.
     * @return boolean success
     */
    public function uninstall() {
        return $this->message->uninstall();
    }

    /**
     * Check module installation.
     * @return boolean result
     */
    public function is_installed() {
        return $this->message->is_installed();
    }

    /**
     * Define module permissions.
     * @return void
     */
    public function get_rights() {
       global $camyks;
       $this->rights[0] = array(
          'name'     => 'read',
          'title'    => $camyks->get_translation('read'),
          'default'   => true,
       );
       $this->rights[1] = array(
          'name'     => 'write',
          'title'    => $camyks->get_translation('write'),
          'default'   => true,
       );
    }

    /**
     * Update description in control panel.
     * @return void
     */
    public function get_adminControlPanelAction() {
        global $camyks;
        $n = $this->message->get_objectCount('touser="'.$camyks->adminUser->login.'" and tostatus=2');
        $camyks->trads['mod_admin_mymessages_desc'] = $camyks->get_translation('mod_admin_mymessages_desc_', $n);
    }

    /**
     * Initialise module object when in admin mode.
     * @return void
     */
    public function init_admin() {
        /* Check read permission */
        if ($this->check_right(0) === false)
            return $this->init_admin_accessDenied();

        /* Load action to execute */
        $mode = isset ($_REQUEST['mode']) ? $_REQUEST['mode'] : 'list';

        /* Execute action */
        switch ($mode) {
            case 'update' :
                /* mode == update */
                $this->init_admin_update();
                break;
            case 'send' :
                /* mode == send */
                $this->init_admin_send();
                break;
            case 'read':
                /* mode == read */
                $this->init_admin_read();
                break;
            case 'list':
            default:
                /* mode == list */
                $this->init_admin_list();
                break;
        }

        /* Perform generic initialisation */
        parent::init_admin();
    }

    /* Specific admin mode methods */

    /**
     * Initialise module object in admin/update mode
     * @return void
     */
    private function init_admin_update() {
        global $camyks;

        /* Load pm ids */
        $pmslist = isset ($_REQUEST['pms']) ? explode(',', $_REQUEST['pms']) : array();
        $pms = array();
        foreach ($pmslist as $p) {
            if (isset ($_REQUEST['pm_'.$p]) and $_REQUEST['pm_'.$p] == 1) {
                $pms[] = $p;
            }
        }

        /* Load other data */
        $action = isset($_REQUEST['action']) ? $_REQUEST['action'] : '';
        $view = isset($_REQUEST['view']) ? $_REQUEST['view'] : '';

        if ($action == 0) {
            $this->message->delete_messages($pms, $view);
        } else if ($action > 0) {
            $this->message->update_messagesStatus($pms, $view, $action);
        }

        /* Update layout */
        $this->text = $this->get_translation($view.'box_messages_updated');
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /**
     * Initialise module object in admin/send mode.
     * @return void
     */
    private function init_admin_send() {
        global $camyks;

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Load message data */
        $this->message->get_fromHeader();

        /* Save message */
        if ($this->message->save()) {
            $this->text = $this->get_translation('pmsent');
        } else {
            $this->text = $this->get_translation($this->message->_libError);
        }
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /**
     * Initialise module object in admin/read mode.
     * @return void
     */
    private function init_admin_read() {
        global $camyks;

        /* check private message */
        if (!isset ($_REQUEST['pm_id'])) {
            return $this->init_admin_list();
        }

        /* get message */
        $this->message->id = (int)$_REQUEST['pm_id'];
        if ($this->message->get() === false)
            return $this->init_admin_list();
        $this->message->get_fromItems();

        /* Build interface buttons */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'  => $this->get_adminLink(),
            ),
        );

        /* Update message status and set view value */
        if ($camyks->adminUser->login == $this->message->vars['fromuser']) {
            $this->message->update_messagesStatus(array($this->message->id), 'from');
            $this->ouser = $this->message->vars['touser'];
            $this->view = 'to';
        } else if ($camyks->adminUser->login == $this->message->vars['touser']) {
            $this->message->update_messagesStatus(array($this->message->id), 'to');
            $this->ouser = $this->message->vars['fromuser'];
            $this->view = 'from';

            /* Update button with "answer" one */
            $this->buttons[] = array(
                'title' => $this->get_translation('answer'),
                'link'  => $this->get_adminLink(array('openTab'=>'write', 'touser'=>$this->ouser, 'title'=>'RE : '.$this->message->vars['title'])));
        }

        /* Update layout */
        $this->set_selectedLayout('admin_read.html.inc');
    }

    /**
     * Initialise pm lists display action.
     * @return void
     */
    private function init_admin_list() {
        global $camyks;

        /* Load received pms */
        $this->receivedbox = $this->message->get_reveivedBoxMessageList();

        /* Load sent pms */
        $this->sentbox = $this->message->get_sentBoxMessageList();

        /* Build tabs */
        $this->openTab = isset ($_REQUEST['openTab']) ? $_REQUEST['openTab'] : 'receivedbox';
        $this->tabObject = 'privatemessage_tabObject';
        $this->add_JSEngineFile('object/ctab.js');
        $this->add_JSScript($this->tabObject.' = new CTab();');
        $this->add_JSScript($this->tabObject.'.init("receivedbox", "'
                             .$this->theme->parts['boxTabCSSStandart'].'","'
                             .$this->theme->parts['boxTabCSSSelected'].'","'
                             .$this->theme->parts['boxTabCSSRollover'].'");');
        if ($this->openTab != 'receivedbox')
            $this->add_JSLoadScript($this->tabObject.'.mouseclick(\''.$this->openTab.'\');');

        $this->tabs = array(
            array(
                'name'  => 'receivedbox',
                'title' => $this->get_translation('tabreceivedbox'),
            ),
            array(
                'name'  => 'sentbox',
                'title' => $this->get_translation('tabsentbox'),
            ),
            array(
                'name'  => 'write',
                'title' => $this->get_translation('tabwritemessage'),
            ),
        );

        /* Add form for pm writing */
        $this->writeform = new HTMLForm('privatemessage_form', $this->get_adminLink(), 'POST');
        $this->writeform->add_hidden('mode', 'send');

        /* Add form for received pm management */
        $this->rboxform = new HTMLForm('privatemessage_rboxform', $this->get_adminLink(), 'POST');
        $this->rboxform->add_hidden('mode', 'update');
        $this->rboxform->add_hidden('view', 'to');
        $pms = array();
        foreach ($this->receivedbox as $pm) {
            $pms[] = $pm->id;
        }
        $this->rboxform->add_hidden('pms', implode(',', $pms));

        /* Add form for received pm management */
        $this->sboxform = new HTMLForm('privatemessage_sboxform', $this->get_adminLink(), 'POST');
        $this->sboxform->add_hidden('mode', 'update');
        $this->sboxform->add_hidden('view', 'from');
        $pms = array();
        foreach ($this->sentbox as $pm) {
            $pms[] = $pm->id;
        }
        $this->sboxform->add_hidden('pms', implode(',', $pms));

        /* Load some values */
        $this->message->get();
        $this->message->get_fromHeader();
        $this->message->get_fromitems();

        /* Build interface buttons */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'  => $camyks->get_adminLink(),
            )
        );
    }
}
?>
