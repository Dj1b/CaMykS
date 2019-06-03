<?php
/**
 * @brief Admin_SystemLogManager Module
 * <br /> Store and display logs.
 * @details Plugin / Input Engine
 * @file plugin/module/Admin_SystemLogManager/Admin_SystemLogManager.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jun 2018
 * @date Modification: Jun 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_SystemLogManager Module class.
 */
final class Admin_SystemLogManager extends Module {
    /**
     * var Object $config
     * @brief Module configuration object.
     */
    protected $config;

    /**
     * var boolean $isConfig
     * @brief Is in configuration mode.
     */
    protected $isConfig = false;

    /**
     * var array $logList
     * @brief Log list.
     */
    protected $logList = array();

    /**
     * var array $logFileList
     * @brief Log file list.
     */
    protected $logFileList = array();

    /**
     * var array $selection
     * @brief Selection values.
     */
    protected $selection = array();

    /**
     * var string $currentFileContent
     * @brief Selected file content.
     */
    protected $currentFileContent;

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('Admin_SystemLogManager', $path_type);

        /* set module type */
        $this->type = 'admin';
        $this->admin_type = 'monitoring';

        /* set plugin version */
        $this->version = '1.0';

        /* set plugin package */
        $this->plugin_package = 'System';

        /* set plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* load plugin libraries */
        $this->load_library('Admin_SystemLogManagerConfig');

        /* initialise plugin libraries */
        $this->config = new Admin_SystemLogManagerConfig('config', $this);

        /* register plugin as Admin_Site extension */
        $this->register_asExtension('Admin_Site');
    }

    /* overwrite Module methods */

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

        $this->rights[1] = array(
            'name'      => 'write',
            'title'     => $camyks->get_translation('configuration'),
            'default'   => false,
        );
    }

    /*
     * Initialise module object in admin mode
     * @return void
     */
    public function init_admin() {
        global $camyks;

        /* check read rights */
        if ($this->check_right(0) === false)
            return $this->init_admin_accessDenied();

        /* check dependencies */
        if (!isset($camyks->inputs['TabBuilder']))
            return $this->init_admin_missingPlugin('Input', 'TabBuilder');
        if (!isset($camyks->inputs['AdminItemListViewer']))
            return $this->init_admin_missingPlugin('Input', 'AdminItemListViewer');

        /* load config */
        $this->config->get();

        /* get informations */
        $this->mode = (isset($_REQUEST['mode']) ? $_REQUEST['mode'] : 'main');

        switch ($this->mode) {
            case 'update_selection':
                /* mode == update_selection */
                $this->init_admin_update_selection();
                break;
            case 'edit_config':
                /* mode == edit_config */
                $this->init_admin_edit_config();
                break;
            case 'save_config':
                /* mode == save_config */
                $this->init_admin_save_config();
                break;
            case 'main':
            default:
                /* mode == main */
                $this->init_admin_main();
        }

        parent::init_admin();
    }

    /*
     * execute module object in request mode
     * @return void
     * @access private
     */
    public function execute_request() {
        global $camyks;

        /* build error message */
        $error = array(
            'title'         => $this->get_translation('requesterror_requestfailed'),
            'description'   => $this->get_translation('requesterror_undefinedaction'),
        );

        /* load mode to execute */
        $mode = isset($_REQUEST['mode'])?$_REQUEST['mode']:'';

        /* execute mode */
        switch ($mode) {
            case 'downloadLogFile':
                $this->execute_request_downloadLogFile();
            default :
                /* throw fatal error */
                $camyks->throwFatalError($error);
        }
    }

    /* specific admin mode methods */

    /**
     * Initialise module object in admin/main mode
     * @return void
     */
    private function init_admin_main() {
        global $camyks;

        /* get help */
        $this->get_help();

        /* load specific CSS */
        $this->add_styleFile('styles.css');

        /* get language to use with content */
        $this->language = $this->get_adminEditionLanguage();

        /* build tabs */
        $this->tabBuilder = $camyks->get_input('TabBuilder');
        $this->tabBuilder->add_tab(array(
            'name'  => 'Logs',
            'title' => $this->get_translation('logs'),
        ));

        /* check for configuration permission */
        if ($this->check_right(1) == true) {

            /* add configuration tab */
            $this->tabBuilder->add_tab(array(
                'name'  => 'Configuration',
                'title' => $this->get_translation('configuration'),
            ));

            /* load configuration */
            $this->config->get();

            /* load data */
            $this->loggingPeriodList = $this->get_configurationLoggingPeriodList();
        }

        /* finalise tabs */
        if ($this->help != null)
            $this->tabBuilder->add_tab(array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help'))
        );

        /* initialise tabs */
        $this->tabBuilder->initialise(array('default'=>'Logs'));

        /* load log list */
        $this->logList = $this->get_logList();

        /* load selection */
        $this->selection = $camyks->get_sessionValue('logManagerSelection', array('log'=>'', 'file'=>'', 'filter'=>''));

        /* load selected log */
        if (!isset($this->logList[$this->selection['log']]))
            $this->selection['log'] = '';

        if ($this->selection['log'] != '') {
            /* load selected log file list */
            $this->logFileList = $this->get_logFileList($this->selection['log']);

            /* load selected log file */
            if (!isset($this->logFileList[$this->selection['file']]))
                $this->selection['file'] = '';
            else {
                $this->currentFileContent = file_getContent($this->get_varFilePath('logs/'.$this->selection['log'].'/'.$this->selection['file'].'.log.inc'));

                if ($this->selection['filter'] != '') {

                    $filter = string_escape4Regex($this->selection['filter']);

                    preg_match_all('/^.*'.$filter.'.*$/mi', $this->currentFileContent, $matches);

                    $this->currentFileContent = implode("\n", $matches[0]);
                }
            }
        }

        /* build log selection form */
        $this->logForm = new HTMLForm(
            'log_selection',
            $this->get_adminlink(array('mode'=>'update_selection')),
            'POST'
        );
        $this->logForm->add_hidden('file', $this->selection['file']);

        /* load scripts */
        $this->add_JSFile('LogViewer.js');
        $this->add_JSLoadScript('LogViewer.set_param("form", "'.$this->logForm->name.'")');
        $this->add_JSLoadScript('LogViewer.initialise();');

        /* get buttons */
        $this->buttons = array(array(
            'link'  => $camyks->get_adminLink(),
            'title' => $camyks->get_translation('back'),
        ));
    }

    /**
     * Initialise module object in admin/update_selection mode
     * @return void
     */
    private function init_admin_update_selection() {
        global $camyks;

        $selection = array();
        $selection['log'] = isset($_REQUEST['log'])?$_REQUEST['log']:'';
        if ($selection['log'] == '')
            $selection['file'] = '';
        else
            $selection['file'] = isset($_REQUEST['file'])?$_REQUEST['file']:'';
        $selection['filter'] = isset($_REQUEST['filter'])?addslashes(trim($_REQUEST['filter'])):'';

        $camyks->set_sessionValue('logManagerSelection', $selection);

        header('Location:'.$camyks->get_rootBaseURL('absolute').$this->get_adminLink());
    }

    /**
     * Initialise module object in admin/edit_config mode
     * @return void
     */
    private function init_admin_edit_config() {
        global $camyks;

        /* check admin write rights */
        if ($this->check_right(1) === false)
            return $this->init_admin_accessDenied();

        /* get help */
        $this->get_help();

        /* build tabs */
        $this->tabBuilder = &$camyks->inputs['TabBuilder'];
        $this->tabBuilder->add_tab(array(
            'name'  => 'Configuration',
            'title' => $this->get_translation('configuration'))
        );
        if ($this->help != null)
            $this->tabBuilder->add_tab(array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help')
        ));
        $this->tabBuilder->initialise(array('default'=>'Configuration'));

        /* load data */
        $this->loggingPeriodList = $this->get_configurationLoggingPeriodList();

        /* build form */
        $this->editform = new HTMLForm(
            'edit_config',
            $this->get_adminlink(array('mode'=>'save_config')),
            'POST'
        );
        $this->editform->set_object($this->config);

        /* build interface title */
        $this->adminTitle = $this->title;
        $this->adminTitle .= $camyks->get_translation('formitem_separator');
        $this->adminTitle .= $camyks->get_translation('configuration');

        /* build interface buttons */
        $this->buttons = array(
            array(
                'link'=>$this->get_adminLink(array('openTab'=>'Configuration')),
                'title'=>$camyks->get_translation('back'),
            ),
            array(
                'link'=>$this->editform->get_HTMLSubmitLink(),
                'title'=>$camyks->get_translation('valid'),
            ),
        );

        /* update layout */
        $this->selected_layout = 'admin_edit_config.html.inc';
    }

    /**
     * Initialise module object in admin/save_config mode
     * @return void
     */
    private function init_admin_save_config() {
        global $camyks;

        /* check admin write rights */
        if ($this->check_right(1) === false)
            return $this->init_admin_accessDenied();

        /* disable admin menu */
        $this->disable_adminEngineMenus();

        /* save config object */
        $this->config->get_fromHeader();
        if ($this->config->save()) {
            $this->text = $this->get_translation('config_saved');
        } else {
            $this->text = $this->get_translation('config_notsaved');
        }

        /* update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('openTab'=>'Configuration')));
    }

    /* request mode methods */

    /**
     * Execute module object in request/downloadLogFile mode.
     * @return void
     */
    private function execute_request_downloadLogFile() {
        global $camyks;

        /* initialise CaMykS in site mode */
        $camyks->get_adminInit();

        /* check admin user */
        if ($camyks->check_adminUser() === false)
            return false;

        /* check admin user permissions */
        if ($this->check_right(1) === false)
            return false;

        /* load file params from session */
        $this->selection = $camyks->get_sessionValue('logManagerSelection', array('log'=>'', 'file'=>'', 'filter'=>''));

        /* build file path */
        $file = new FSFile($this->get_varFilePath('logs/'.$this->selection['log'].'/'.$this->selection['file'].'.log.inc'));
        if (!$file->exists)
          return false;

        /* Send file to visitor */
        $file->download($this->selection['file'].'.log');
    }

    /* configuration specific methods */

    /**
     * Return configuration logging period list
     * @return array
     */
    private function get_configurationLoggingPeriodList() {
        return $this->config->get_loggingPeriodList();
    }

    /* log specific methods */

    /**
     * Return available log list
     * @return array
     */
    private function get_logList() {
        $folders = folder_listFolders($this->get_varFilePath('logs'));
        $list = array();
        foreach ($folders as $folder)
            $list[$folder] = $folder;
        return $list;
    }

    /**
     * Return available log file list for give log.
     * @param string $log
     * @return array
     */
    private function get_logFileList($log) {
        $files = folder_listFiles($this->get_varFilePath('logs/'.$log));
        $temp = array();
        foreach ($files as $file) {
            $temp[$file] = filectime($this->get_varFilePath('logs/'.$log.'/'.$file));
        }
        arsort($temp);

        $result = array();
        foreach ($temp as $file => $mtime) {
            $f = explode('.', $file);
            $result[$f[0]] = $this->get_logFileTitle($f[0]);
        }
        return $result;
    }

    /**
     * Return current log file path.
     * @param string $log
     * @return string
     */
    private function get_logFilePath($log) {
        /* load period logging mode */
        $period = $this->get_configValue('logging_period');

        /* prepare path */
        folder_completePath($this->get_varFilePath().'logs/'.$log);
        $path = $this->get_varFilePath('logs/'.$log).'/';

        /* complete path with period mode */
        if ($period == 0) /* daily */
            $path .= strftime('%Y-%m-%d');
        elseif ($period == 1) /* weekly */
            $path .= strftime('%Y-W%W');
        elseif ($period == 2) /* monthly */
            $path .= strftime('%Y-M%m');
        $path .= '.log.inc';

        /* return complete path */
        return $path;
    }

    /**
     * Return log file title from its name.
     * @param string $name
     * @return string
     */
    private function get_logFileTitle($name) {
        if (preg_match('/^([0-9]{4})\-([0-9]{2})\-([0-9]{2})$/', $name, $matches))
            return date('Y M d', mktime(0, 0, 0, $matches[2], $matches[3], $matches[1]));
        elseif (preg_match('/^([0-9]{4})\-W([0-9]{2})$/', $name, $matches))
            return $matches[1].' Week '.$matches[2];
        elseif (preg_match('/^([0-9]{4})\-M([0-9]{2})$/', $name, $matches))
            return date('Y M', mktime(0, 0, 0, $matches[2], 1, $matches[1]));

        /* by default return file name */
        return $name;
    }

    /**
     * Write log information to log file
     * @param string $log
     * @param string $action
     * @param string $message
     * @return boolean result
     */
    public function write_log($log, $action, $message='') {
        global $camyks;

        /* check log */
        $log = trim($log);
        if ($log == '' or !preg_match('/^[0-9A-Za-z]*$/', $log))
            return false;

        /* build file path */
        $file = $this->get_logFilePath($log);

        /* prepare log line */
        $line = client_getIP();
        $line .= ' ['.date('d/M/Y:G:i:s O').']';
        $line .= ' '.($camyks->check_adminUser() ? $camyks->adminUser->login : 'visitor');
        $line .= ' - '.$this->clean_value($action);
        $line .= ' - '.$this->clean_value($message);

        /* write line */
        if (@file_put_contents($file, $line."\n", FILE_APPEND)) {
            $this->prune_oldFiles($log);
            return true;
        }
        return false;
    }

    /**
     * Prune all old files for given log
     * @param string $log
     * @return boolean result
     */
    private function prune_oldFiles($log) {
        /* do not prune each time */
        if (rand(0,10) != 1)
            return true;

        /* check configuration value */
        if ($this->get_configValue('logging_lastFilesKept') == 0)
            return true;

        /* load log files */
        $files = $this->get_logFileList($log);

        /* check if some files have to be deleted */
        if (count($files) <= $this->get_configValue('logging_lastFilesKept'))
            return true;

        /* remove files */
        for ($i = $this->get_configValue('logging_lastFilesKept'); $i < count($files); $i++) {
            $k = array_keys($files);
            @unlink($this->get_varFilePath('logs/'.$log.'/'.$k[$i].'.log.inc'));
        }

        /* return as success */
        return true;
    }

    /* specific tool methods */

    /**
     * Return given config item value
     * @param string $item
     * @return mixed
     */
    private function get_configValue($item) {
        return $this->config->get_value($item);
    }

    /**
     * Returned clean value (to avoid PHP/JS injection in logs)
     * @param string $value
     * @return value
     */
    private function clean_value($value='') {
        $value = string_stripPHPTags($value);
        $value = string_stripScriptTags($value);
        return $value;
    }

    /* Admin_Site extension configuration methods */

    /**
     * Initialise object in Admin_Site / view configuration mode
     * @return void
     */
    public function initialise_configDisplay() {
        $this->isConfig = true;

        /* load configuration */
        $this->config->get();

        /* load data */
        $this->loggingPeriodList = $this->get_configurationLoggingPeriodList();
    }

    /**
     * Display object in Admin_Site / view configuration mode
     * @return void
     */
    public function display_configDisplay() {
        $this->load_file('html/configuration/view.html.inc');
    }

    /**
     * Initialise object in Admin_Site / edit configuration mode
     * @param Object $form
     * @return void
     */
    public function initialise_configEdition($form) {
        global $camyks;

        $this->isConfig = true;

        /* load configuration */
        $this->config->get();

        /* load data */
        $this->loggingPeriodList = $this->get_configurationLoggingPeriodList();

        /* update form */
        $this->editform = &$form;
        $this->editform->set_object($this->config);
    }

    /**
     * Display object in Admin_Site / edit configuration mode
     * @return void
     */
    public function display_configEdition() {
        $this->load_file('html/configuration/edit.html.inc');
    }

    /*
     * Execute object in Admin_Site / save configuration mode
     * @return void
     */
    public function save_configuration() {
        $this->config->get_fromHeader();
        return $this->config->save();
    }
}
?>
