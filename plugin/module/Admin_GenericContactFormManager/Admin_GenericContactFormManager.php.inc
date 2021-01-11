<?php
/**
 * @brief Admin_GenericContactFormManager Module
 * <br /> Manages sent contact form requests.
 * @details Plugin, Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Nov 2010
 * @date Modification: Jan 2021
 * @copyright 2010 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GenericContactFormManager class.
 */
final class Admin_GenericContactFormManager extends Module {
    /**
     * var Object $formItem
     * @brief Form request object.
     */
    public $formItem;

    /**
     * var array $formList
     * @brief Form request list.
     */
    public $formList = null;

    /**
     * var Object $subjectItem
     * @brief Form subject object.
     */
    public $subjectItem;

    /**
     * var array $subjectList
     * @brief Form subject list.
     */
    public $subjectList = null;

    /**
     * var Object $config
     * @brief Plugin configuration.
     */
    protected $config;

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('Admin_GenericContactFormManager', $path_type);

        /* Override Plugin variables */
        $this->plugin_package = 'Generic';
        $this->version = '1.0';

        /* Override Module variables */
        $this->type = 'admin';
        $this->admin_type = 'content';

        /* Define plugin author */
        $this->author_name = 'CaMykS';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Load plugin libaries */
        $this->load_library('Admin_GenericContactFormManagerForm');
        $this->load_library('Admin_GenericContactFormManagerSubject');
        $this->load_library('Admin_GenericContactFormManagerConfig');

        /* Initialise plugin libraries */
        $this->formItem = new Admin_GenericContactFormManagerForm(0, $this);
        $this->subjectItem = new Admin_GenericContactFormManagerSubject(0, $this);
        $this->config = new Admin_GenericContactFormManagerConfig('config', $this);
    }

    /* Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return ($this->formItem->install() and $this->subjectItem->install()
            and $this->config->install() and parent::install());
    }

    /**
     * Unintall module.
     * @return boolean success
     */
    public function uninstall() {
        return parent::uninstall();
    }

    /**
     * Check module installation.
     * @return boolean result
     */
    public function is_installed() {
        return $this->formItem->is_installed();
    }

    /**
     * Define module permission.
     * @return void
     */
    public function get_rights() {
        global $camyks;
        $this->rights[0] = array(
            'name'      => 'read',
            'title'     => $camyks->get_translation('read'),
            'default'   => true,
        );
        $this->rights[1] = array(
            'name'      => 'edit_forms',
            'title'     => $this->get_translation('rights_editforms'),
            'default'   => false,
        );
        $this->rights[2] = array(
            'name'      => 'edit_subject',
            'title'     => $this->get_translation('rights_editsubjects'),
            'default'   => false,
        );
        $this->rights[3] = array(
            'name'      => 'edit_config',
            'title'     => $this->get_translation('rights_editconfig'),
            'default'   => false,
        );
    }

    /**
     * Update control panel description.
     * @return void
     */
    public function get_adminControlPanelAction() {
        global $camyks;
        $n = $this->formItem->get_objectCount('status=0');
        if ($n == 1)
            $camyks->trads['mod_admin_genericcontactformmanager_desc'] = $camyks->trads['mod_admin_genericcontactformmanager_desc1'];
        elseif ($n > 1)
            $camyks->trads['mod_admin_genericcontactformmanager_desc'] = vsprintf($camyks->trads['mod_admin_genericcontactformmanager_descx'], $n);
    }

    /**
     * Initialise module object in admin mode.
     * @return void
     */
    public function init_admin() {
        global $camyks;

        /* Check read rights */
        if ($this->check_right(0) === false)
            return $this->init_admin_accessDenied();

        /* Check dependencies */
        if (!isset($camyks->inputs['AdminItemListViewer']))
            return $this->init_admin_missingPlugin('Input', 'AdminItemListViewer');
        if (!isset($camyks->inputs['TabBuilder']))
            return $this->init_admin_missingPlugin('Input', 'TabBuilder');

        /* Load configuration */
        $this->config->get();

        /* Load action to execute */
        $this->mode = isset ($_REQUEST['mode']) ? $_REQUEST['mode'] : 'main';

        /* Execute action */
        switch ($this->mode) {
            case 'view_form':
                /* mode == view_form */
                $this->init_admin_viewForm();
                break;
            case 'edit_form':
                /* mode == edit_form */
                $this->init_admin_editForm();
                break;
            case 'save_form':
                /* mode == save_form */
                $this->init_admin_saveForm();
                break;
            case 'delete_form':
                /* mode == delete_form */
                $this->init_admin_deleteForm();
                break;
            case 'view_subject':
                /* mode == view_subject */
                $this->init_admin_viewSubject();
                break;
            case 'edit_subject':
                /* mode == edit_subject */
                $this->init_admin_editSubject();
                break;
            case 'save_subject':
                /* mode == save_subject */
                $this->init_admin_saveSubject();
                break;
            case 'delete_subject':
                /* mode == delete_subject */
                $this->init_admin_deleteSubject();
                break;
            case 'edit_config':
                /* mode == edit_config */
                $this->init_admin_editConfig();
                break;
            case 'save_config':
                /* mode == save_config */
                $this->init_admin_saveConfig();
                break;
            case 'main':
            default:
                /* mode == main */
                $this->init_admin_main();
        }

        /* Perform generic initialisation */
        parent::init_admin();
    }

    /* Specific admin mode methods */

    /**
     * Initialise module object in admin/main mode.
     * @return void
     */
    private function init_admin_main() {
        global $camyks;

        /* Load list parameters*/
        $this->load_library('Admin_GenericContactFormManagerFormListParams');

        /* Initialise object list input */
        $this->formList = &$camyks->inputs['AdminItemListViewer'];
        $this->formList->set_params($this->formListParams);
        $this->formList->initialise();

        /* Check for config panel */
        if ($this->check_right(2) !== false) {
            /* Load tabs */
            $this->tabBuilder = &$camyks->inputs['TabBuilder'];
            $this->tabBuilder->add_tabs(array(
                array(
                    'name'  => 'config',
                    'title' => $this->get_translation('tabconfig'),
                ),
                array(
                    'name'  => 'forms',
                    'title' => $this->get_translation('tabforms'),
                ),
            ));
            $this->tabBuilder->initialise(array('default'=>'forms'));
        }

        /* Build interface title */
        $this->adminTitle = $this->title;

        /* Build interface buttons */
        $this->buttons = array(
            array(
                'link'  => $camyks->get_adminLink(),
                'title' => $camyks->get_translation('back'),
            ),
        );
    }

    /**
     * Initialise module object in admin/view_form mode.
     * @return void
     */
    private function init_admin_viewForm() {
        global $camyks;

        /* Check item id */
        if (!isset($_REQUEST['form_id']))
            return $this->init_admin_main();

        /* Load form */
        $this->formItem->id = (int)$_REQUEST['form_id'];
        $this->formItem->get();
        $this->formItem->get_fromItems();

        /* Load interface title */
        $this->adminTitle = $this->get_translation('title_formid', $this->formItem->id);

        /* Build buttons list */
        $this->buttons = array(
            array(
                'link'  => $this->get_adminLink(),
                'title' => $camyks->get_translation('back'),
            ),
        );

        /* Update layout */
        $this->selected_layout = 'admin_view_form.html.inc';
    }

    /**
     * Initialise module object in admin/edit_form mode.
     * @return void
     */
    private function init_admin_editForm() {
        global $camyks;

        /* Check edition permission */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* Load object */
        $this->formItem->id = isset($_REQUEST['form_id']) ? (int)$_REQUEST['form_id'] : 0;
        $this->formItem->get();
        $this->formItem->get_fromItems();

        /* Build edition form */
        $this->editform = new HTMLForm('editform', $this->get_adminLink(array('mode'=>'save_form')), 'POST');
        $this->editform->set_object($this->formItem);
        $this->editform->add_hidden('form_id', $this->formItem->id);
        $this->editform->add_hidden('locale', $this->formItem->vars['locale']);
        $this->editform->add_hidden('ipaddress', $this->formItem->vars['ipaddress']);

        /* Load interface title */
        if ($this->formItem->id == 0)
            $this->adminTitle = $this->get_translation('title_newform');
        else
            $this->adminTitle = $this->get_translation('title_formid', $this->formItem->id);

        /* Build buttons list */
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
        $this->set_selectedLayout('admin_edit_form.html.inc');
    }

    /**
     * Initialise module object in admin/save_form mode.
     * @return void
     */
    private function init_admin_saveForm() {
        global $camyks;

        /* Check edition permission */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Check item id */
        if (!isset($_REQUEST['form_id']))
            return $this->init_admin_main();

        /* Try to save item */
        $this->formItem->id = (int)$_REQUEST['form_id'];
        $this->formItem->get_fromHeader();
        if ($this->formItem->save()) {
            $this->text = $this->get_translation('form_saved');
        } else {
            $this->text = $this->get_translation('form_notsaved');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_form.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /**
     * Initialise module object in admin/delete_form mode.
     * @return void
     */
    private function init_admin_deleteForm() {
        global $camyks;

        /* Check edition permission */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Check item id */
        if (!isset($_REQUEST['form_id']))
            return $this->init_admin_main();

        /* Try to delete item */
        $this->formItem->id = (int)$_REQUEST['form_id'];
        if ($this->formItem->delete()){
            $this->text = $this->get_translation('form_deleted');
        } else {
            $this->text = $this->get_translation('form_notdeleted');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_form.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /**
     * Initialise module object in admin/edit_config mode.
     * @return void
     */
    private function init_admin_editConfig() {
        global $camyks;

        /* Check edit configuration permission */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* Load config */
        $this->config->get();

        /* Load external data */
        $this->userList = $camyks->modules['Admin_User']->get_activeUserList(true);

        /* Build configuration form */
        $this->configform = new HTMLForm('configform', $this->get_adminLink(array('mode' => 'save_config')), 'POST');
        $this->configform->set_object($this->config);
        $this->configform->add_hidden('notification_recipients_count_', count($this->userList));

        /* Build window title */
        $this->adminTitle = $this->title;
        $this->adminTitle .= $camyks->get_translation('formitem_separator');
        $this->adminTitle .= $this->get_translation('title_config');

        /* Build button list */
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
    private function init_admin_saveConfig() {
        global $camyks;

        /* Check edit configuration permission */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Save config */
        $this->config->get_fromHeader();
        if ($this->config->save())
            $this->text = $this->get_translation('config_saved');
        else
            $this->text = $this->get_translation('config_notsaved');

        /* Update layout */
        $this->set_selectedLayout('admin_form.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /* Specific tool methods */

    /**
     * Return forms status list.
     * @param boolean $full
     * @return array
     */
    public function get_formsStatusList($full=false) {
        return $this->formItem->get_multiStatusList($full);
    }

    /**
     * Return form status list.
     * @return array
     */
    public function get_formStatusList() {
        return $this->formItem->get_statusList();
    }

    /**
     * Return form status icon list.
     * @return array
     */
    public function get_formStatusIconList() {
        return $this->formItem->get_statusIconList();
    }

    /**
     * Send notification emails.
     * @return void
     */
    private function send_notifications() {
        global $camyks;

        /* Check for notifications status */
        if($this->get_configValue('notification_status') == 0)
            return true;

        /* Load sender & recipients */
        $sender = $this->get_configValue('notification_sender');
        $recipients = $this->get_configValue('notification_recipients');

        /* Check sender & recipients */
        if ($sender == '' or count($recipients) == 0)
            return true;

        /* Load content */
        $subject = string_html2Text($this->get_translation('notification_emailsubject'));

        /* Send email */
        foreach ($recipients as $rec) {
            $this->admin = new AdminUser($rec);
            $this->admin->get();
            $content = $this->get_notificationContent();
            mail_sendHTMLMail(array(
                'to'        => $this->admin->email,
                'from'      => $sender,
                'subject'   => $subject,
                'content'   => $content,
            ));
        }
    }

    /**
     * Return admin email content.
     * @return string
     */
    private function get_notificationContent() {
        global $camyks;
        /* Load CSS */
        $css = $camyks->themes[$camyks->get_confValue('site_default_theme')]->get_filePath('email.css');

        /* Build html page */
        ob_start();
        $page = new HTMLPage();
        $page->add_styleIncludedFile($css);
        $page->add_HTMLHeader();
        $this->load_file('html/email_notification.html.inc');
        $page->add_HTMLFooter();

        $c = ob_get_contents();
        ob_end_clean();
        return $c;
    }

    /**
     * Update statistics.
     * @return boolean success
     */
    private function update_statistics() {
        global $camyks;

        /* Check for statistics status */
        if($this->get_configValue('statistic_status') == 0)
            return true;

        /* Update statistics */
        return $camyks->update_statistic('contact_form', $this->name, 'dated', '', '', '');
    }

    /**
     * Return configuration value.
     * @param string $item
     * @return mixed
     */
    public function get_configValue($item) {
        if (!isset($this->config->vars))
            $this->config->get();
        return $this->config->vars[$item];
    }

    /* Specific public methods */

    /**
     * Return form list.
     * @param array $params
     * @return array
     */
    public function get_formList($params) {
        return $this->formItem->get_list($params);
    }

    /**
     * Save form from site.
     * @return boolean success
     */
    public function save_siteForm() {
        $this->formItem->id = 0;
        $this->formItem->get_fromHeader();
        if($this->formItem->save()) {
            $this->send_notifications();
            $this->update_statistics();
            return true;
        }
        $this->formItem->get_fromItems();
        return false;
    }

    /**
     * Return form object.
     * @return object
     */
    public function get_formObject() {
        return $this->formItem;
    }

    /**
     * Return form count.
     * @param array $params
     * @return integer
     */
    public function count_forms($params=array()) {
        return $this->formItem->count($params);
    }
}
?>
