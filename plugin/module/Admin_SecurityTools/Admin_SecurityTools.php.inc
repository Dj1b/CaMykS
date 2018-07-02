<?php
/**
 * @brief Admin_SecurityTools Module
 * <br /> Provides some security tools:
 * <br /> - IP Filter : Done
 * <br /> - BackUp : Done (based on register_shutdown_function method)
 * <br /> - Flood (POST) Control : ?
 * @details Plugin / Module Engine
 * @file plugin/module/Admin_SecurityTools/Admin_SecurityTools.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Oct 2007
 * @date Modification: Jun 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @todo - remove cdata & cplugin folders sym links from "complete" backup
 * <br /> - fully display the page before starting a new "automatic" backup
 * <br /> - allow to cp, ftp, scp, ... automatic backups
 * <br /> - add script timeout extension as parameter into the backup config file
 */

/**
 * Admin_SecurityTools Module class.
 * @author CaMykS Team <camyks.contact@gmail.com>
 */
final class Admin_SecurityTools extends Module {
    /**
     * Class constructor
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        global $camyks;
        parent::__construct('Admin_SecurityTools', $path_type);
        
        /* set module type */
        $this->type = 'admin';
        $this->admin_type = 'configuration';
        
        /* set plugin version */
        $this->version = '1.0.1';
        
        /* set plugin package */
        $this->plugin_package = 'Default';
        
        /* set plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* get module libs */
        $this->load_library('Admin_SecurityToolsConfig');
        $this->load_library('Admin_SecurityIPFilterRule');
        $this->load_library('Admin_SecurityBackUpFile');

        /* get lib objects */
        $this->config = new Admin_SecurityToolsConfig('config', $this);
        $this->ipfilterrule = new Admin_SecurityIPFilterRule(0, $this);
        $this->backupfile = new Admin_SecurityBackUpFile(0, $this);

        /* load config */
        $this->config->get();

        /* check security */
        if ($camyks->mode == CAMYKS_MODE_ADMIN)
            $this->check_security();
        else
            $this->register_asCaMykSEventHandler('onInitialise');

        /* list tools */
        $this->tools = array('ipfilter', 'backup');
    }
    
    /* overwrite Module Methods */

    /**
     * Install module object
     * @return boolean success
     */
    public function install() {
        return $this->ipfilterrule->install() and $this->backupfile->install() and parent::install();
    }
    
    /**
     * Uninstall module object
     * @return boolean success
     */
    public function uninstall() {
        return $this->ipfilterrule->uninstall() and $this->backupfile->uninstall() and parent::uninstall();
    }

    /**
     * Check module installation
     * @return boolean result
     */
    public function is_installed() {
        return $this->backupfile->is_installed();
    }

    /**
     * Returns available permissions
     * @return void
     */
    public function get_rights() {
        global $camyks;
        $this->rights[0] = array(
            'name'      => 'read',
            'title'     => $camyks->get_translation('read'),
            'default'   => false,
       );
        $this->rights[1] = array(
            'name'      => 'config',
            'title'     => $this->get_translation('right_config'),
            'default'   => false,
       );
        $this->rights[2] = array(
            'name'      => 'ipfilter',
            'title'     => $this->get_translation('right_ipfilter'),
            'default'   => false,
       );
        $this->rights[3] = array(
            'name'      => 'backup',
            'title'     => $this->get_translation('right_backup'),
            'default'   => false,
       );
    }
    
    /**
     * Execute handler on CaMykS initialise.
     * @return void
     */
    public function execute_onCaMykSInitialise() {
        $this->check_security();
    }

    /**
     * Initialise module object in admin mode.
     * @return void
     */
    public function init_admin() {
        global $camyks;
        
        /* check read rights */
        if ($this->check_right(0) === false) {
            return $this->init_admin_accessDenied();
        }
        
        /* check dependancies */
        if (!isset($camyks->inputs['TabBuilder']))
            return $this->init_admin_missingPlugin('Input', 'TabBuilder');

        /* load mode */
        $this->mode = isset($_REQUEST['mode'])?$_REQUEST['mode']:'main';

        /* execute mode */
        switch ($this->mode) {
            case 'update_config':
                /* mode == update_config */
                $this->init_admin_updateConfig();
                break;
            case 'edit_ipfilter':
                /* mode == edit_ipfilter */
                $this->init_admin_editIPFilter();
                break;
            case 'save_ipfilter':
                /* mode == save_ipfilter */
                $this->init_admin_saveIPFilter();
                break;
            case 'delete_ipfilter':
                /* mode == delete_ipfilter */
                $this->init_admin_deleteIPFilter();
                break;
            case 'edit_backupconfig':
                /* mode == edit_backupconfig */
                $this->init_admin_editBackUpConfig();
                break;
            case 'save_backupconfig':
                /* mode == save_backupconfig */
                $this->init_admin_saveBackUpConfig();
                break;
            case 'delete_backupfile':
                /* mode == delete_backupfile */
                $this->init_admin_deleteBackUpFile();
                break;
            case 'edit_newbackupfile':
                /* mode == edit_newbackupfile */
                $this->init_admin_editNewBackUpFile();
                break;
            case 'save_newbackupfile':
                /* mode == save_newbackupfile */
                $this->init_admin_saveNewBackUpFile();
                break;
            case 'main':
                /* mode == main */
                $this->init_admin_main();
                break;
            }
            /* generic initialisation */
            parent::init_admin();
        }

        /* specific admin mode methods */

        /*
         * Initialise module object in admin/main mode
         * @return void
         */
        private function init_admin_main() {
            global $camyks;

            /* add needed JS */
            $this->add_JSFile('admin_securitytools.js');
        
            /* get tabs */
            $this->tabBuilder = &$camyks->inputs['TabBuilder'];
            $this->tabBuilder->add_tab(array(
                'name'  => 'Configuration',
                'title' => $this->get_translation('tabmain'),
            ));
            if ($this->help != null)
                $this->tabBuilder->add_tab(array(
                    'name'  => 'help',
                    'title' => $camyks->get_translation('help'),
            ));

            /* check for available tools */
            if ($this->config->vars['ipfilter']) {
                /* add tab */
                $this->tabBuilder->add_tab(array(
                    'name'  => 'IPFilter',
                    'title' => $this->get_translation('tool_ipfilter')
                ));
                                
                /* add needed JS for ipfilter tool */
                $this->add_JSScript('deletefiprmessage="'.string_HTML2Text($this->get_translation('deletefilteriprule')).'";');
                $this->add_JSScript('deletefiprurl="'.$this->get_adminJSLink(array('mode'=>'delete_ipfilter', 'ruleid'=>'')).'";');
            
            /* get filter ip rules */
            $this->get_IPFilterRules();
        }

        if ($this->config->vars['backup'] and $this->check_right(3)) {
            /* add tab */
            $this->tabBuilder->add_tab(array(
                'name'    => 'Backup',
                'title' => $this->get_translation('tool_backup')
           ));
            
            /* add needed JS for ipfilter tool */
            $this->add_JSScript('deletebackupmessage="'.string_HTML2Text($this->get_translation('backup_deletebackup')).'";');
            $this->add_JSScript('deletebackupurl="'.$this->get_adminJSLink(array('mode'=>'delete_backupfile', 'backup_id'=>'')).'";');
            
            /* get backup files */
            $this->get_backUpFiles();
        }
        
        /* Initialise tabs */
        $this->tabBuilder->initialise(array('default'=>'Configuration'));

        /* load plugin help */
        $this->get_help();
        if ($this->help) {
            $this->tabBuilder->add_tab(array(
                'name'    =>'help',
                'title' =>$camyks->get_translation('help')
           ));
        }

        /* build buttons */
        $this->buttons = array(array(
            'link'  => $camyks->get_adminLink(),
            'title' => $camyks->get_translation('back')
       ));
    }

    /**
     * Initialise module object in admin/edit_ipfilter mode.
     * @return void
     */
    private function init_admin_editIPFilter() {
        global $camyks;
        
        /* check rights */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();
        
        /* load object */
        $this->ipfilterrule->id = isset($_REQUEST['ruleid']) ? (int)$_REQUEST['ruleid'] : 0;
        $this->ipfilterrule->get();
        $this->ipfilterrule->get_fromItems();
        
        /* get form */
        $this->init_admin_editIPFilterForm();
    }

    /*
     * Complete module object init in admin/edit_ipfilter
     * @return void
     */
    private function init_admin_editIPFilterForm() {
        global $camyks;
        
        /* build form */
        $this->form = new HTMLForm(
            'edit_ipfilter',
            $this->get_adminLink(array('mode'=>'save_ipfilter')),
            'POST');
        $this->form->add_hidden('ruleid', $this->ipfilterrule->id);
        
        /* build interface title */
        $this->adminTitle = $this->title.$camyks->get_translation('formitem_separator');
        if ($this->ipfilterrule->id == 0)
            $this->adminTitle .= $this->get_translation('ipfilter_rulenew');
        else
            $this->adminTitle .= $this->get_translation('ipfilter_ruleid', $this->ipfilterrule->id);

        /* build buttons */
        $this->buttons = array(
            array(
                'link'  => $this->get_adminLink(array('openTab'=>'IPFilter')),
                'title' => $camyks->get_translation('back'),
               ),
            array(
                'link'  => $this->form->get_HTMLSubmitLink(),
                'title' => $camyks->get_translation('valid'),
            )
       );
    
        /* update layout */
        $this->set_selectedLayout('admin_editipfilter.html.inc');
    }

    /*
     * Initialise module object in admin/save_ipfilter mode.
     * @return void
     */
    private function init_admin_saveIPFilter() {
        global $camyks;
        
        /* check rights */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* disable admin menu */
        $this->disable_adminEngineMenus();

        /* save rule */
        $this->ipfilterrule->id = isset($_REQUEST['ruleid']) ? (int)$_REQUEST['ruleid'] : 0;
        $this->ipfilterrule->get_fromHeader();
        if ($this->ipfilterrule->save()) {
            $this->text = $this->get_translation('rule_saved');
            $this->set_selectedLayout('admin_message.html.inc', 'camyks');
            $this->set_redirect($this->get_adminLink(array('openTab'=>'IPFilter')));
        } else {
            $this->ipfilterrule->get_fromItems();
            $this->init_admin_editIPFilterForm();
        }
    }

    /*
     * Initialise module object in admin/delete_ipfilter mode.
     * @return void
     */
    private function init_admin_deleteIPFilter() {
        global $camyks;
        
        /* check rights */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* disable admin menu */
        $this->disable_adminEngineMenus();

        /* delete rule */
        $this->ipfilterrule->id = isset($_REQUEST['ruleid']) ? (int)$_REQUEST['ruleid'] : 0;
        if ($this->ipfilterrule->delete()) {
            $this->text = $this->get_translation('rule_deleted');
        } else {
            $this->text = $this->get_translation('rule_notdeleted');
        }
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('openTab'=>'IPFilter')));
    }

    /*
     * Initialise module object in admin/update_config mode.
     * @return void
     */
    private function init_admin_updateConfig() {
        global $camyks;
        
        /* check rights */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* disable admin menu */
        $this->disable_adminEngineMenus();

        /* get update values */
        if (isset($_REQUEST['action']) and in_array($_REQUEST['action'], array('enable', 'disable'))
                and isset($_REQUEST['item']) and isset($this->config->vars[$_REQUEST['item']])) {
            $this->config->vars[$_REQUEST['item']] = ($_REQUEST['action'] == 'enable');
            if ($this->config->save()) {
                $this->text = $this->get_translation('config_saved');
            } else {
                $this->text = $this->get_translation('config_notsaved');
            }
        } else {
            $this->text = $this->get_translation('config_notsaved');
        }
        
        /* update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /*
     * Initialise module object in admin/edit_backupconfig mode
     * @return void
     */
    private function init_admin_editBackUpConfig() {
        global $camyks;
        
        /* check rights */
        if ($this->check_right(3) === false)
            return $this->init_admin_actionNotAllowed();
        
        /* get values lists for backup tool */
        $this->get_backUpValues();
        
        /* get form */
        $this->form = new HTMLForm(
            'edit_backupconfig',
            $this->get_adminLink(array('mode'=>'save_backupconfig')),
            'POST');
        
        /* get buttons */
        $this->buttons = array(
            array(
                'link'  => $camyks->get_adminLink($this->name, array('openTab'=>'Backup')),
                'title' => $camyks->get_translation('back'),
            ),
            array(
                'link'  => $this->form->get_HTMLSubmitLink(),
                'title' => $camyks->get_translation('valid'),
            )
        );
        
        /* update layout */
        $this->set_selectedLayout('admin_editbackupconfig.html.inc');
    }
    
    /**
     * Initialise module object in admin/save_backupconfig mode.
     * @return void
     */
    private function init_admin_saveBackUpConfig() {
        global $camyks;
        
        /* check rights */
        if ($this->check_right(3) === false)
            return $this->init_admin_actionNotAllowed();

        /* disable admin menu */
        $this->disable_adminEngineMenus();
        
        /* get values lists for backup tool */
        $this->get_backUpValues();
        
        /* get method value */
        $this->config->vars['backup_method'] = (isset($_REQUEST['backup_method']) and isset($this->backup_methods[$_REQUEST['backup_method']])) ? $_REQUEST['backup_method']:'manual';
        
        /* get compression value */
        $this->config->vars['backup_compression'] = (isset($_REQUEST['backup_compression']) and isset($this->backup_compressions[$_REQUEST['backup_compression']])) ? $_REQUEST['backup_compression']:'tar';
        
        /* get type value */
        $this->config->vars['backup_type'] = (isset($_REQUEST['backup_type']) and isset($this->backup_types[$_REQUEST['backup_type']]))? $_REQUEST['backup_type']:'complete';
        
        /* get temp folder value */
        $this->config->vars['backup_temp'] = (isset($_REQUEST['backup_temp']) ? $_REQUEST['backup_temp'] : '');

        /* get nextdate value */
        switch ($this->config->vars['backup_method']) {
            case 'daily':
                $this->config->vars['backup_nextdate'] = mktime(0, 0, 0, date('m'), date('d')+1, date('Y'));
                break; 
            case 'weekly':
                if (date('w') == 0) {
                    $d = 6;
                } else {
                    $d = date('w')-1;
                }
                $this->config->vars['backup_nextdate'] = mktime(0, 0, 0, date('m'), date('d')-$d+7, date('Y'));
                break;
            case 'monthly':
                $this->config->vars['backup_nextdate'] = mktime(0, 0, 0, date('m')+1, 1, date('Y'));
                break;
            default:
                $this->config->vars['backup_nextdate'] = 0;
                break;
        }
     
        /* save config file */
        if ($this->config->save()) {
            $this->text = $this->get_translation('config_saved');
        } else {
            $this->text = $this->get_translation('config_notsaved');
        }
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('openTab'=>'Backup')));
    }

    /**
     * Initialise module object in admin/save_backupconfig mode.
     * @return void
     */
    private function init_admin_deleteBackUpFile() {
        global $camyks;
        
        /* check rights */
        if ($this->check_right(3) === false)
            return $this->init_admin_actionNotAllowed();
        
        /* disable admin menu */
        $this->disable_adminEngineMenus();

        /* get backup */
        $this->backupfile->id = isset($_REQUEST['backup_id'])?(int)$_REQUEST['backup_id']:0;
        if ($bid > 0 and $this->backupfile->get()) {
            $this->backupfile->get_fromItems();
            
            /* try to delete file */
            if (file_exists($this->plugin_var_path.'/'.$this->backupfile->backupdir.'/'.$this->backupfile->vars['name']))
                unlink($this->plugin_var_path.'/'.$this->backupfile->backupdir.'/'.$this->backupfile->vars['name']);
                
            /* delete database informations */
            $this->backupfile->delete();
            $this->text = $this->get_translation('backup_deleted');
        } else {
            $this->text = $this->get_translation('backup_notdeleted');
        }
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('openTab'=>'Backup')));
    }

    /**
     * Initialise module object in admin/edit_newbackupfile mode
     * @return void
     */
    private function init_admin_editNewBackUpFile() {
        global $camyks;
        
        /* check rights */
        if ($this->check_right(3) === false) 
            return $this->init_admin_actionNotAllowed();
        
        /* get values lists for backup tool */
        $this->get_backUpValues();
        
        /* get form */
        $this->form = new HTMLForm(
                'edit_newbackupfile',
                $this->get_adminLink(array('mode'=>'save_newbackupfile')),
                'POST');
        
        /* get buttons */
        $this->buttons = array(
            array(
                'link'  => $camyks->get_adminLink($this->name, array('openTab'=>'Backup')),
                'title' => $camyks->get_translation('back'),
            ),
            array(
                'link'  => $this->form->get_HTMLSubmitLink(),
                'title' => $this->get_translation('backup_createbackup'),
            ),
       );
        
        /* update layout */
        $this->set_selectedLayout('admin_editnewbackupfile.html.inc');
    }

    /**
     * Initialise module object in admin/save_newbackupfile mode.
     * @return void
     */
    private function init_admin_saveNewBackUpFile() {
        global $camyks;
        
        /* check rights */
        if ($this->check_right(3) === false)
            return $this->init_admin_actionNotAllowed();

        /* disable admin menu */
        $this->disable_adminEngineMenus();

        $compression = isset($_REQUEST['backup_compression'])?$_REQUEST['backup_compression']:null;
        $type = isset($_REQUEST['backup_type'])?$_REQUEST['backup_type']:null;

        if ($this->backupfile->backup('manual', $type, $compression)) {
            $this->text = $this->get_translation('backup_saved');
        } else {
            $this->text = $this->get_translation('backup_failed');
        }
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('openTab'=>'Backup')));
    }

    /* specific tool methods */

    /**
     * Check all security tools.
     * @return void
     */
    private function check_security() {
        global $camyks;

        /* IP Filter */
        if ($this->config->vars['ipfilter'])
            $this->ipfilterrule->check_security();

        /* BackUp */
        if ($this->config->vars['backup']) {
            if ($camyks->mode == CAMYKS_MODE_ADMIN
             and $this->config->vars['backup_method'] != 'manual'
             and mktime() > $this->config->vars['backup_nextdate']) {
                /* call backup method at the end of the whole script */
                register_shutdown_function('_Admin_Securitytools_execute_backup');
            }
        }
    }

    /**
     * Load IP Filter rules
     * @return void
     */
    private function get_IPFilterRules() {
        $this->ipfilterrules = $this->ipfilterrule->get_objectList();
    }

    /**
     * Load back up files.
     * @return void
     */
    private function get_backUpFiles() {
        $this->backupfiles = $this->backupfile->get_objectList();
    }

    /**
     * Load all needed backup values.
     * @return void
     */
    private function get_backUpValues() {
        $this->backup_methods = $this->get_backupMethodsList();
        $this->backup_compressions = $this->get_backupCompressionsList();
        $this->backup_types = $this->get_backupTypesList();
    }

    /**
     * Return backup methods list.
     * @return array
     */
    private function get_backupMethodsList() {
        $list = array();
        $list['manual'] = $this->get_translation('backup_method_manual');
        $list['daily'] = $this->get_translation('backup_method_daily');
        $list['weekly'] = $this->get_translation('backup_method_weekly');
        $list['monthly'] = $this->get_translation('backup_method_monthly');
        return $list;
    }

    /**
     * Return backup compressions list
     * @return array
     */
    private function get_backupCompressionsList() {
        $list = array();
        $list['tar'] = $this->get_translation('backup_compression_tar');
        $list['tgz'] = $this->get_translation('backup_compression_tgz');
        $list['tbz'] = $this->get_translation('backup_compression_tbz');
        $list['zip'] = $this->get_translation('backup_compression_zip');
        return $list;
    }

    /**
     * Return backup types list.
     * @return array
     */
    private function get_backupTypesList() {
        $list = array();
        $list['complete'] = $this->get_translation('backup_type_complete');
        $list['data'] = $this->get_translation('backup_type_data');
        $list['file'] = $this->get_translation('backup_type_file');
        return $list;
    }
}

/* static methods */

/**
 * Execute backup.
 * @return void
 * @private
 */
function _Admin_Securitytools_execute_backup() {
    global $camyks;
    
    /* get Admin_SecurityTool module */
    $_this = $camyks->modules['Admin_SecurityTools'];
    
    /* update next backup date */
    switch ($_this->config->vars['backup_method']) {
        case 'daily':
            $_this->config->vars['backup_nextdate'] = mktime(0, 0, 0, date('m'), date('d')+1, date('Y'));
            break; 
        case 'weekly':
            if (date('w') == 0) {
                $d = 6;
            } else {
                $d = date('w')-1;
            }
            $_this->config->vars['backup_nextdate'] = mktime(0, 0, 0, date('m'), date('d')-$d+7, date('Y'));
            break;
        case 'monthly':
            $_this->config->vars['backup_nextdate'] = mktime(0, 0, 0, date('m')+1, 1, date('Y'));
            break;
        default:
            $_this->config->vars['backup_nextdate'] = 0;
            break;
    }
    $_this->config->save();
    
    /* backup */
    return $_this->backupfile->backup();
}
?>