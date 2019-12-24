<?php
/**
 * @brief Admin_SystemReport Module
 * <br /> Monitor and log reports.
 * @details Plugin, Module Engine
 * @file plugin/module/Admin_SystemReport/Admin_SystemReport.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.3
 * @date Creation: May 2007
 * @date Modification: Dec 2019
 * @copyright 2007 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_SystemReport class.
 */
final class Admin_SystemReport extends Module {
    /**
     * var Object $reportItem
     * @brief Record object.
     */
    public $reportItem;

    /**
     * var array $reportList
     * @brief Record list.
     */
    public $reportList = array();


    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('Admin_SystemReport', $path_type);

        /* Override Plugin variables */
        $this->plugin_package = 'System';
        $this->version = '1.0';

        /* Override Module variables */
        $this->type = 'admin';
        $this->admin_type = 'monitoring';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'skymac.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Load plugin libraries */
        $this->load_library('Admin_SystemReportItem');

        /* Initialise plugin libraries */
        $this->reportItem = new Admin_SystemReportItem(0, $this);
    }

    /* Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return ($this->reportItem->install() and parent::install());
    }

    /**
     * Uninstall module.
     * @return boolean success
     */
    public function uninstall() {
         return ($this->reportItem->uninstall() and parent::uninstall());
    }

    /**
     * Check module installation
     * @return boolean result
     */
    public function is_installed() {
        return $this->reportItem->is_installed();
    }

    /**
     * Register a menu in admin interface.
     * @return array
     */
    public function get_adminEngineSpecificMenus() {
        if ($this->check_right(1) === true) {
            return array(array(
                'name'  => 'systemreport',
                'title' => $this->get_translation('title')
            ));
        }
        return array();
    }

    /**
     * Register menu items in admin interface
     * @return array
     */
    public function get_adminEngineSpecificMenuItems() {
        global $camyks;

        /* Load mode */
        $mode = isset($_REQUEST['mode']) ? $_REQUEST['mode'] : 'display';

        /* set menus */
        if ($this->check_right(1)===true and $mode == 'display') {
            return array(
                array(
                    'name'  => 'markselected',
                    'title' => $this->get_translation('markitemsasread'),
                    'icon'  => $this->get_fileURL('img/valid12.gif'),
                    'menu'  => 'systemreport',
                    'url'   => 'javascript:admin_systemreport_marklogsasread();',
                ),
                array(
                    'name'  => 'deleteselected',
                    'title' => $this->get_translation('deleteitems'),
                    'icon'  => $this->get_fileURL('img/clean12.gif'),
                    'menu'  => 'systemreport',
                    'url'   => 'javascript:admin_systemreport_deletelogs();',
                ),
            );
        }
        return array();
    }

    /**
     * Build module rights.
     * @return void
     */
    public function get_rights() {
        global $camyks;
        $this->rights[0] = array(
            'name'      =>'read',
            'title'     => $camyks->get_translation('read'),
            'default'   => false,
        );
        $this->rights[1] = array(
            'name'      => 'write',
            'title'     => $camyks->get_translation('write'),
            'default'   => false,
        );
    }

    /**
     * Update description in control panel.
     * @return void
     */
    public function get_adminControlPanelAction() {
        global $camyks;
        $n = $this->reportItem->get_objectCount('status=0');
        $camyks->trads['mod_admin_systemreport_desc'] = $this->get_translation('desc_', $n);
    }

    /**
     * Return notified items for module.
     * @return array
     */
    public function get_adminInternalNotifications() {
        /* Load reports count by type */
        $cnts = $this->reportItem->count_reportsByType(array('status'=>0));
        if (count($cnts) == 0)
            return array();

        /* Initialise result */
        $result = array(
            $this->name => array(
                'title' => $this->title,
                'items' => array(),
            ),
        );

        /* Add types to results */
        foreach ($cnts as $type => $cnt) {
            $result[$this->name]['items'][] = array(
                'title'     => $type,
                'cnt'       => $cnt,
                'priority'  => $type == 'Information' ? 0 : 2,
             );
        }

        /* Return result */
        return $result;
    }

    /**
     * Initialise object when in admin mode.
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

        /* Load mode */
        $this->mode = isset($_REQUEST['mode']) ? $_REQUEST['mode'] : 'display';

        /* Execute mode */
        switch ($this->mode) {
            case 'deletesingle':
                $this->init_admin_deletesingle();
                break;
            case 'markasreadsingle':
                $this->init_admin_markasreadsingle();
                break;
            case 'deletemulti':
                $this->init_admin_deletemulti();
                break;
            case 'markasreadmulti':
                $this->init_admin_markasreadmulti();
                break;
            case 'readreport':
                $this->init_admin_readReport();
                break;
            case 'display':
            default:
                $this->init_admin_main();
                break;
        }

        /* generic initialisation */
        parent::init_admin();
    }

    /* Specific admin mode methods */

    /**
     * Initialise module object in admin/display mode
     * @return void
     */
    private function init_admin_main() {
        global $camyks;

        /* Build report list tab */
        $this->load_library('Admin_SystemReportItemListParams');
        $this->reportList = &$camyks->inputs['AdminItemListViewer'];
        $this->reportList->set_params($this->reportListParams);
        $this->reportList->initialise();

        /* Build multi selection form */
        $this->itemform = new HTMLForm('admin_systemreport_selection', $this->get_adminLink(), 'POST');
        $this->itemform->add_hidden('mode', 'display');
        $this->itemform->add_hidden('ids', '');

        /* Add delete log javascripts */
        $this->add_JSFile('admin_systemreport.js');
        $this->add_JSScript('admin_systemreport_selectionform="'.$this->itemform->name.'";');
        $this->add_JSScript('admin_systemreport_deletelogsmessage="'.string_html2Text($this->get_translation('deletelogsmessage')).'";');
        $this->add_JSScript('admin_systemreport_marklogsmessage="'.string_html2Text($this->get_translation('marklogsmessage')).'";');

        /* Build interface buttons */
        $this->buttons = array(array(
            'title' => $camyks->get_translation('back'),
            'link'  => $camyks->get_adminLink(),
        ));
    }

    /**
     * Initialise module object in admin/readreport mode
     * @return void
     */
    private function init_admin_readReport() {
        global $camyks;

        /* Load report */
        $this->reportItem->id = isset($_REQUEST['report_id']) ? (int)$_REQUEST['report_id'] : -1;
        if ($this->reportItem->get() === false)
            return $this->init_admin_display();
        $this->reportItem->get_fromItems();

        /* Build interface title */
        $this->adminTitle = $this->title.$camyks->get_translation('formitem_separator').$this->get_translation('reportid', $this->reportItem->id);

        /* Build interface buttons */
        $this->buttons = array(array(
            'title' => $camyks->get_translation('back'),
            'link'  => $this->get_adminLink(),
        ));

        /* Insert mark report form if user has permission */
        if ($this->check_right(1) === true) {
            if ($this->reportItem->vars['status'] == 0) {

                /* Build list form */
                $this->markform = new HTMLForm('admin_systemreport_markform', $this->get_adminLink(array('mode'=>'markasreadsingle')), 'POST');
                $this->markform->add_hidden('report', $this->reportItem->id);

                /* Adds button to interface */
                $this->buttons[] = array(
                    'title' => $this->get_translation('markasread'),
                    'link'  => $this->markform->get_HTMLSubmitLink(),
                );
            }
        }

        /* Update layout */
        $this->set_selectedLayout('admin_readreport.html.inc');
    }

    /**
     * Initialise module object in admin/deletesingle mode.
     * @return void
     */
    private function init_admin_deleteSingle() {
        global $camyks;

        /* Check permission */
        if ($this->check_right(1) === false)
            return $this->init_admin_accessDenied();

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Load item */
        $this->reportItem->id = isset($_REQUEST['report']) ? (int)$_REQUEST['report'] : 0;
        if ($this->reportItem->id > 0) {
            $this->reportItem->delete();
            $this->text = $camyks->get_translation('deletedone');
        } else {
            $this->text = $this->get_translation('reportdoesntexist');
        }

        /* Update layout and insert redirection */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /**
     * Initialise module object in admin/markasreadsingle mode.
     * @return void
     */
    private function init_admin_markasreadsingle() {
        /* Check permission */
        if ($this->check_right(1) === false)
            return $this->init_admin_accessDenied();

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Load item */
        $this->reportItem->id = isset($_REQUEST['report']) ? (int)$_REQUEST['report'] : 0;
        if ($this->reportItem->id > 0 and $this->reportItem->update_withAnswer()) {
            $this->text = $this->get_translation('markeddone');
        } else {
            $this->text = $this->get_translation('reportdoesntexist');
        }

        /* Update layout and insert redirection */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /**
     * Initialise module object in admin/markasreadmulti mode.
     * @return void
     */
    private function init_admin_markasreadmulti() {

        /* Check permission */
        if ($this->check_right(1) === false)
            return $this->init_admin_accessDenied();

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Load item selection */
        $list = $this->get_selectedItems();

        /* Update items */
        if ($this->reportItem->update_reports($list)) {
            $this->text = $this->get_translation('multimarkeddone');
        } else {
            $this->text = $this->get_translation('erroroccured');
        }

        /* Update layout and insert redirection */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /**
     * Initialise module object in admin/deletemulti mode.
     * @return void
     */
    private function init_admin_deletemulti() {
        /* Check permission */
        if ($this->check_right(1) === false)
            return $this->init_admin_accessDenied();

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Load item selection */
        $list = $this->get_selecteditems();

        /* Delete items */
        if ($this->reportItem->delete_reports($list)) {
            $this->text = $this->get_translation('multideletedone');
        } else {
            $this->text = $this->get_translation('erroroccured');
        }

        /* Update layout and insert redirection */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /* specific tool methods */

    /**
     * Create and save a new report.
     * @param string $type
     * @param object $object
     * @param string $desc1
     * @param string $desc2
     * @param string $file
     * @param string $line
     * @return boolean success
     */
    public function add_newReport($type, &$object, $desc1='', $desc2='', $file='', $line='') {
        /* check if object is not this module to kill loop script */
        if (strtolower(get_class($object)) == strtolower(get_class($this->reportItem))) {
            return false;
        }
        $this->reportItem->update_values($type, $object, $desc1, $desc2, $file, $line);
        return $this->reportItem->save();
    }

    /**
     * Return selected item list.
     * @return array
     */
    private function get_selecteditems() {
        $list = array();

        $ids = isset($_REQUEST['ids'])?$_REQUEST['ids']:'';

        if ($ids == '')
            return $list;

        $list = explode(',', $ids);
        foreach ($list as $id)
            $id = (int)$id;

        return $list;
    }

    /* specific content management methods */

    /**
     * Return single report status list.
     * @return array
     */
    public function get_reportStatusList() {
        return $this->reportItem->get_statusList();
    }

    /**
     * Return report status list.
     * @param boolean $more
     * @return array
     */
    public function get_reportsStatusList($more=false) {
            return $this->reportItem->get_multiStatusList($more);
    }

    /**
     * Return report type list
     * @param boolean $more
     * @return array
     */
    public function get_reportTypeList($more=false) {
        return $this->reportItem->get_typelist($more);
    }
}
?>
