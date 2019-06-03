<?php
/**
 * @brief Admin_MonitoringUserAgentChecker Module
 * <br /> Monitor and check user agent of visitors and bots.
 * @details Plugin, Module Engine
 * @file plugin/module/Admin_MonitoringUserAgentChecker/Admin_MonitoringUserAgentChecker.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.4
 * @date Creation: Dec 2014
 * @date Modification: Jan 2019
 * @copyright 2014 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_MonitoringUserAgentChecker class.
 */
final class Admin_MonitoringUserAgentChecker extends Module {
    /**
     * var Object $recordItem
     * @brief Record object.
     */
    public $recordItem;

    /**
     * var array $recordList
     * @brief Record list.
     */
    public $recordList = null;

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        global $camyks;
        parent::__construct('Admin_MonitoringUserAgentChecker', $path_type);

        /* Override Plugin variables */
        $this->plugin_package = 'Monitoring';
        $this->version = '1.0';

        /* Override Module variables */
        $this->type = 'admin';
        $this->admin_type = 'monitoring';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Load plugin libraries */
        $this->load_library('Admin_MonitoringUserAgentCheckerRecord');

        /* Initialise plugin libraries */
        $this->recordItem = new Admin_MonitoringUserAgentCheckerRecord(0, $this);

        /* Save user agent */
        if ($camyks->mode == CAMYKS_MODE_SITE and $camyks->get_sessionValue('UAChecker', 0) == 0) {
            $this->save_visit();
            $camyks->set_sessionValue('UAChecker', 1);
        }
    }

    /* overwrite Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return ($this->recordItem->install() and parent::install());
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
        return $this->recordItem->is_installed();
    }

    /**
     * Return module permissions.
     * @return void
     */
    public function get_rights() {
        global $camyks;
        $this->rights[0] = array(
            'name'      => 'read',
            'title'     => $camyks->get_translation('read'),
            'default'   => false,
        );
    }

    /**
     * Register a menu in admin interface.
     * @return array
     */
    function get_adminEngineSpecificMenus() {

        /* Load mode from header */
        $this->mode = isset($_REQUEST['mode']) ? $_REQUEST['mode'] : 'main';

        /* Return menus */
        if ($this->mode == 'main') {
            return array(
                array(
                    'name'  => 'useragentchecker',
                    'title' => $this->get_translation('title'),
                ),
            );
        }

        /* Return default result */
        return array();
    }

    /**
     * Register menu items in admin interface.
     * @return array
     */
    function get_adminEngineSpecificMenuItems() {
        global $camyks;

        /* Return menu items */
        if ($this->mode == 'main') {
            return array(
                array(
                    'name'  => 'markselected',
                    'title' => $this->get_translation('markitemsasverified'),
                    'icon'  => $this->theme->get_pictURL('valid', 12, 'std'),
                    'menu'  => 'useragentchecker',
                    'url'   => 'javascript:UARecordList.mark_recordsAsVerified();',
                ),
                array(
                    'name'  => 'markinspected',
                    'title' => $this->get_translation('markitemsasinspected'),
                    'icon'  => $this->theme->get_pictURL('target', 12, 'std'),
                    'menu'  => 'useragentchecker',
                    'url'   => 'javascript:UARecordList.mark_recordsAsInspected();',
                ),
            );
        }
        return array();
    }

    /**
     * Update description in control panel.
     * @return void
     */
    public function get_adminControlPanelAction() {
        global $camyks;
        $n = $this->count_records(array('status'=>0));
        if ($n == 1)
            $camyks->trads['mod_admin_monitoringuseragentchecker_desc'] = $this->get_translation('desc1');
        elseif ($n > 1)
            $camyks->trads['mod_admin_monitoringuseragentchecker_desc'] = $this->get_translation('descx', $n);
    }

    /**
     * Return notified items for module.
     * @return Array
     */
    public function get_adminInternalNotifications() {
        /* load reports count */
        $cnt = $this->count_records(array('status'=>0));
        if ($cnt == 0)
            return array();

        /* initialise result */
        $result = array($this->name => array(
            'title' => $this->title,
            'items' => array(
                array(
                    'title'     => $this->get_translation('recordsstatus_notverified'),
                    'cnt'       => $cnt,
                    'priority'  => 0,
                )
            )
        ));

        /* send result */
        return $result;
    }

    /**
     * Initialise module object in admin mode.
     * @return void
     */
    public function init_admin() {
        global $camyks;

        /* check user rights */
        if ($this->check_right(0) === false)
            return $this->init_admin_accessDenied();

        /* check dependencies */
        if (!isset($camyks->inputs['TabBuilder']))
            return $this->init_admin_missingPlugin('Input', 'TabBuilder');
        if (!isset($camyks->inputs['AdminItemListViewer']))
            return $this->init_admin_missingPlugin('Input', 'AdminItemListViewer');

        /* get informations */
        $this->mode = isset ($_REQUEST['mode']) ? $_REQUEST['mode'] : 'main';

        switch ($this->mode) {
            case 'view_record':
                /* mode == view_record */
                $this->init_admin_view_record();
                break;
            case 'edit_record':
                /* mode == edit_record */
                $this->init_admin_edit_record();
                break;
            case 'save_record':
                /* mode == save_record */
                $this->init_admin_save_record();
                break;
            case 'delete_record':
                /* mode == delete_record */
                $this->init_admin_delete_record();
                break;
            case 'update_recordType':
                /* mode == update_recordType */
                $this->init_admin_update_recordType();
                break;
            case 'mark_recordAsVerified':
                /* mode == mark_recordAsVerified */
                $this->init_admin_mark_recordAsVerified();
                break;
            case 'mark_recordAsUnverified':
                /* mode == mark_recordAsUnverified */
                $this->init_admin_mark_recordAsUnverified();
                break;
            case 'mark_recordAsInspected':
                /* mode == mark_recordAsInspected */
                $this->init_admin_mark_recordAsInspected();
                break;
            case 'mark_recordsAsVerified':
                /* mode == mark_recordsAsVerified */
                $this->init_admin_mark_recordsAsVerified();
                break;
            case 'mark_recordsAsInspected':
                /* mode == mark_recordsAsInspected */
                $this->init_admin_mark_recordsAsInspected();
                break;
            case 'main':
            default:
                /* mode == main */
                $this->init_admin_main();
        }

        /* generic initialisatin */
        parent::init_admin();
    }

    /* specific admin mode methods */

    /**
     * Initialise module object in admin/main mode.
     * @return void
     */
    private function init_admin_main() {
        global $camyks;

        /* get help */
        $this->get_help();

        /* get language to use with content */
        $this->language = $this->get_adminEditionLanguage();

        /* build record tab */
        $this->load_library('Admin_MonitoringUserAgentCheckerRecordListParams');
        $this->recordList = new AdminItemListViewer('camyks');
        $this->recordList->set_params($this->recordListParams);
        $this->recordList->initialise();

        /* load tabs */
        $this->tabBuilder = &$camyks->inputs['TabBuilder'];

        /* add records tab */
        $this->tabBuilder->add_tab(array(
            'name'  => 'Records',
            'title' => $this->get_translation('tabrecords'),
        ));

        /* add help tab */
        if ($this->help != null)
            $this->tabBuilder(array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help'),
            ));

        /* initialise tabs */
        $this->tabBuilder->initialise(array('default'=>'Records'));

        /* build multi selection form */
        $this->selectionForm = new HTMLForm('recordSelection', $this->get_adminLink(), 'POST');
        $this->selectionForm->add_hidden('mode', 'main');
        $this->selectionForm->add_hidden('ids', '');

        /* add scripts */
        $this->add_JSFIle('UARecordList.js');
        $this->add_JSLoadScript('UARecordList.set_param("form", "'.$this->selectionForm->name.'");');
        $this->add_JSLoadScript('UARecordList.set_locale("confirmvalidate_message", "'.string_html2Text($this->get_translation('validaterecordsmessage')).'");');
        $this->add_JSLoadScript('UARecordList.set_locale("confirminspect_message", "'.string_html2Text($this->get_translation('inspectrecordsmessage')).'");');
        $this->add_JSLoadScript('UARecordList.initialise();');

        /* get buttons */
        $this->buttons = array(array(
            'link'  => $camyks->get_adminLink(),
            'title' => $camyks->get_translation('back'),
        ));

        /* build record insertion form */
        $this->addform = new HTMLForm('edit_record', $this->get_adminlink(array('mode'=>'save_record')), 'POST');
        $this->addform->add_hidden('record_id', 0);

        /* build popup buttons */
        $this->popupbuttons = array(
            array(
                'title' => $camyks->get_translation('close'),
                'link'  => 'javascript:adminengine_modalPopupClose(\'admin_genericuseragentmanager_addpopup\')',
            ),
            array(
                'title' => $camyks->get_translation('add'),
                'link'  => $this->addform->get_HTMLSubmitLink(),
            ),
        );
    }

    /**
     * Initialise module object in admin/view record mode.
     * @return void
     */
    private function init_admin_view_record() {
        global $camyks;

        /* get record item */
        $this->recordItem->id = isset($_REQUEST['record_id']) ? (int)$_REQUEST['record_id'] : 0;
        if ($this->recordItem->id == 0 or !$this->recordItem->get())
            return $this->init_admin_main();
        $this->recordItem->get_fromItems();

        /* load user agent information from client library */
        $this->uaInfos = client_getUAInfos($this->recordItem->vars['user_agent']);

        /* load tabs */
        $this->tabBuilder = &$camyks->inputs['TabBuilder'];

        /* add records tab */
        $this->tabBuilder->add_tab(array(
            'name'  => 'Properties',
            'title' => $this->get_translation('tabproperties'),
        ));

        /* add help tab */
        if ($this->help != null)
            $this->tabBuilder->add_tab(array(
                'name'=>'help',
                'title'=>$camyks->get_translation('help'),
            ));

        /* initialise tabs */
        $this->tabBuilder->initialise(array('default'=>'Properties'));

        /* load data */
        $this->recordPlatformFormats = $this->get_recordPlatformFormatList();

        /* build title */
        $this->adminTitle = $this->title;
        $this->adminTitle .= $camyks->get_translation('formitem_separator');
        if ($this->recordItem->id == 0)
            $this->adminTitle .= $this->get_translation('recordnew');
        else
            $this->adminTitle .= $this->get_translation('recordid', $this->recordItem->id);

        /* build button list */
        $this->buttons = array(
            array(
                'link'  => $this->get_adminLink(),
                'title' => $camyks->get_translation('back'),
            ),
            array(
                'link'  => $this->get_adminLink(array('mode'=>'update_recordType', 'record_id'=>$this->recordItem->id)),
                'title' => $camyks->get_translation('update'),
            ),
        );
        if ($this->recordItem->vars['status'] == 1)
            $this->buttons[] = array(
                'link'  => $this->get_adminLink(array('mode'=>'mark_recordAsUnverified', 'record_id'=>$this->recordItem->id)),
                'title' => $this->get_translation('markasunverified'),
            );
        else {
            $this->buttons[] = array(
                'link'  => $this->get_adminLink(array('mode'=>'mark_recordAsVerified', 'record_id'=>$this->recordItem->id)),
                'title' => $this->get_translation('markasverified'),
            );
            if ($this->recordItem->vars['status'] == 0)
                $this->buttons[] = array(
                    'link'  => $this->get_adminLink(array('mode'=>'mark_recordAsInspected', 'record_id'=>$this->recordItem->id)),
                    'title' => $this->get_translation('inspect'),
                );
        }

        /* update layout */
        $this->set_selectedLayout('admin_view_user_agent.html.inc');
    }

    /**
     * Initialise module object in admin/edit_record mode.
     * @return void
     */
    private function init_admin_edit_record() {
        global $camyks;

        /* get record item */
        $this->recordItem->id = isset($_REQUEST['record_id']) ? (int)$_REQUEST['record_id'] : 0;
        if (!$this->recordItem->get())
            return $this->init_admin_main();
        $this->recordItem->get_fromItems();

        /* get form */
        $this->editform = new HTMLForm('edit_record', $this->get_adminlink(array('mode'=>'save_record')), 'POST');
        $this->editform->set_object($this->recordItem);
        $this->editform->add_hidden('record_id', $this->recordItem->id);

        /* load tabs */
        $this->tabBuilder = &$camyks->inputs['TabBuilder'];

        /* add records tab */
        $this->tabBuilder->add_tab(array(
            'name'  => 'Properties',
            'title' => $this->get_translation('tabproperties'),
        ));

        /* add help tab */
        if ($this->help != null)
            $this->tabBuilder->add_tab(array('name'=>'help', 'title'=>$camyks->get_translation('help')));

        /* initialise tabs */
        $this->tabBuilder->initialise(array('default'=>'Properties'));

        /* build title */
        $this->adminTitle = $this->title;
        $this->adminTitle .= $camyks->get_translation('formitem_separator');
        if ($this->recordItem->id == 0)
            $this->adminTitle .= $this->get_translation('recordnew');
        else
            $this->adminTitle .= $this->get_translation('recordid', $this->recordItem->id);

        /* build button list */
        $this->buttons = array(
            array(
                'link'  => $this->get_adminLink(),
                'title' => $camyks->get_translation('back')
            ),
            array(
                'link'  => $this->editform->get_HTMLSubmitLink(),
                'title' => $camyks->get_translation('valid'),
            ),
        );

        /* update layout */
        $this->set_selectedLayout('admin_edit_user_agent.html.inc');
    }

    /**
     * Initialise module object in admin/save_record mode.
     * @return void
     */
    private function init_admin_save_record() {
        global $camyks;

        $_REQUEST['platform_type'] = 'other';
        if (isset($_REQUEST['user_agent']) && $_REQUEST['user_agent'] != '') {
            $uaInfos = client_getUAInfos($_REQUEST['user_agent']);
            if (isset($uaInfos['platform_type']) && $uaInfos['platform_type'] != '')
                $_REQUEST['platform_type'] = $uaInfos['platform_type'];
        }

        /* check user rights */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* check record id */
        if (!isset($_REQUEST['record_id']))
            return $this->init_admin_main();

        /* disable admin menu */
        $this->disable_adminEngineMenus();

        /* save record */
        $this->recordItem->id = (int)$_REQUEST['record_id'];
        $this->recordItem->get_fromHeader();

        /* verify duplicate */
        if ($this->recordItem->count($_REQUEST) == 0) {
            if ($this->recordItem->save())
                $this->text = $this->get_translation('record_saved');
            else
                $this->text = $this->get_translation('record_notsaved');
            $this->set_redirect($this->get_adminLink(array('mode'=>'view_record', 'record_id'=>$this->recordItem->id)));
        } else {
            $this->text = $this->get_translation('record_duplicated');
            $this->set_redirect($this->get_adminLink());
        }

        /* update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');

    }

    /**
     * Initialise module object in admin/delete_record mode.
     * @return void
     */
    private function init_admin_delete_record() {
        global $camyks;

        /* check record id */
        if (!isset($_REQUEST['record_id']))
            return $this->init_admin_main();

        /* disable admin menu */
        $this->disable_adminEngineMenus();

        /* delete record */
        $this->recordItem->id = (int)$_REQUEST['record_id'];
        if ($this->recordItem->delete())
            $this->text = $this->get_translation('record_deleted');
        else
            $this->text = $this->get_translation('record_notdeleted');

        /* update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /**
     * Initialise module object in admin/update_recordType mode.
     * @return void
     */
    private function init_admin_update_recordType() {
        global $camyks;

        /* check record id */
        if (!isset($_REQUEST['record_id']))
            return $this->init_admin_main();

        /* disable admin menu */
        $this->disable_adminEngineMenus();

        /* load and update record */
        $this->recordItem->id = (int)$_REQUEST['record_id'];
        if ($this->recordItem->get() and $this->recordItem->update_type())
            $this->text = $this->get_translation('record_updated');
        else
            $this->text = $this->get_translation('record_notupdated');

        /* update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('mode'=>'view_record', 'record_id'=>$this->recordItem->id)));
    }

    /**
     * Initialise module object in admin/mark_recordAsVerified mode.
     * @return void
     */
    private function init_admin_mark_recordAsVerified() {
        global $camyks;

        /* check record id */
        if (!isset($_REQUEST['record_id']))
            return $this->init_admin_main();

        /* disable admin menu */
        $this->disable_adminEngineMenus();

        /* load and update record */
        $this->recordItem->id = (int)$_REQUEST['record_id'];
        if ($this->recordItem->get() and $this->recordItem->mark_asVerified())
            $this->text = $this->get_translation('record_updated');
        else
            $this->text = $this->get_translation('record_notupdated');

        /* update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('mode'=>'view_record', 'record_id'=>$this->recordItem->id)));
    }

    /**
     * Initialise module object in admin/mark_recordAsUnverified mode.
     * @return void
     */
    private function init_admin_mark_recordAsUnverified() {
        global $camyks;

        /* check record id */
        if (!isset($_REQUEST['record_id']))
            return $this->init_admin_main();

        /* disable admin menu */
        $this->disable_adminEngineMenus();

        /* load and update record */
        $this->recordItem->id = (int)$_REQUEST['record_id'];
        if ($this->recordItem->get() and $this->recordItem->mark_asUnverified())
            $this->text = $this->get_translation('record_updated');
        else
            $this->text = $this->get_translation('record_notupdated');

        /* update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('mode'=>'view_record', 'record_id'=>$this->recordItem->id)));
    }

    /**
     * Initialise module object in admin/mark_recordAsInspected mode.
     * @return void
     */
    private function init_admin_mark_recordAsInspected() {
        global $camyks;

        /* check record id */
        if (!isset($_REQUEST['record_id']))
            return $this->init_admin_main();

        /* disable admin menu */
        $this->disable_adminEngineMenus();

        /* load and update record */
        $this->recordItem->id = (int)$_REQUEST['record_id'];
        if ($this->recordItem->get() and $this->recordItem->mark_asInspected())
            $this->text = $this->get_translation('record_updated');
        else
            $this->text = $this->get_translation('record_notupdated');

        /* update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('mode'=>'view_record', 'record_id'=>$this->recordItem->id)));
    }

    /**
     * Initialise module object in admin/mark_recordsAsVerified mode.
     * @return void
     */
    private function init_admin_mark_recordsAsVerified() {
        global $camyks;

        /* disable admin menu */
        $this->disable_adminEngineMenus();

        /* load and update record */
        $list = $this->get_selectedItems();
        if ($this->recordItem->mark_recordsAsVerified($list))
            $this->text = $this->get_translation('records_updated');
        else
            $this->text = $this->get_translation('records_notupdated');

        /* update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /**
     * Initialise module object in admin/mark_recordsAsInspected mode.
     * @return void
     */
    private function init_admin_mark_recordsAsInspected() {
        global $camyks;

        /* disable admin menu */
        $this->disable_adminEngineMenus();

        /* load and update record */
        $list = $this->get_selectedItems();
        if ($this->recordItem->mark_recordsAsInspected($list))
            $this->text = $this->get_translation('records_updated');
        else
            $this->text = $this->get_translation('records_notupdated');

        /* update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /* specific tool methods */

    /**
     * Update record with given user agent.
     * @param string $ua
     * @return boolean success
     */
    private function save_visit($ua=null) {
        /* define params */
        $params = array('user_agent'=>isset($ua) ? $ua : $_SERVER['HTTP_USER_AGENT']);

        /* initialise new object */
        $this->recordItem->initialise();

        /* try to load from existing user agent */
        if ($this->recordItem->get_fromUserAgent($params['user_agent']))
            return $this->recordItem->update_visitCount();

        /* create new entry */
        $this->recordItem->_libItems['user_agent']->value = $params['user_agent'];
        $uaInfos = client_getUAInfos($params['user_agent']);
        if ($uaInfos['platform_type'] != '')
            $this->recordItem->_libItems['platform_type']->value = $uaInfos['platform_type'];
        else
            $this->recordItem->_libItems['platform_type']->value = 'undefined';
        return $this->recordItem->save();
    }

    /**
     * Return selected item list.
     * @return array
     */
    private function get_selectedItems() {
        $list = array();

        $ids = isset($_REQUEST['ids']) ? $_REQUEST['ids'] : '';

        if ($ids == '')
            return $list;

        $list = explode(',', $ids);
        foreach ($list as $id)
            $id = (int)$id;

        return $list;
    }

    /**
     * Return records platform type list.
     * @return array
     */
    public function get_multiPlatformTypesList() {
        return $this->recordItem->get_platformTypesList(true);
    }

    /**
     * Return record plateform type list/
     * @return array
     */
    public function get_singlePlatformTypesList() {
        return $this->recordItem->get_platformTypesList(false);
    }

    /**
     * Return record status list.
     * @return array
     */
    public function get_recordStatusList() {
        return $this->recordItem->get_statusList();
    }

    /**
     * Return record status icon list.
     * @return array
     */
    public function get_recordStatusIconList() {
        return $this->recordItem->get_statusIconList();
    }

    /**
     * Return record platform format list.
     * @return array
     */
    public function get_recordPlatformFormatList() {
        return $this->recordItem->get_platformFormatList();
    }

    /**
     * Return record count.
     * @param array $params
     * @return array
     */
    public function count_records($params=array()) {
        return $this->recordItem->count($params);
    }

    /**
     * Return record list.
     * @param array $params
     * @return array
     */
    public function list_records($params=array()) {
        return $this->recordItem->get_list($params);
    }
}
?>
