<?php
/**
 * @brief SiteMonitoringToolbar Input
 * <br /> Display a monitoring toolbar on website.
 * <br /> Available tools
 * <br /> + CaMykS Main button to open/close toolbar
 * <br /> - Publish / Unpublish (Currently no done)
 * <br /> - Edit (Currently no done)
 * <br /> - Add (Currently no done)
 * <br /> - Statistics (Currently no done)
 * <br /> ----
 * <br /> - Messages (start / enabled status) (Currently no done)
 * <br /> + dB Stats (start / enabled status)
 * <br /> + Page bench (start / enabled status)
 * <br /> ---
 * <br /> + Configuration
 * <br /> + Reload
 * <br /> + Disconnect
 * @details Plugin / Input Engine
 * @file plugin/input/SiteMonitoringToolbar/SiteMonitoringToolbar.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Nov 2017
 * @date Modification: Jul 2018
 * @copyright 2017 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @todo Add missing features and extension management.
 */

/**
 * SiteMonitoringToolbar Input class.
 */
final class SiteMonitoringToolbar extends Input {

    /**
     * @var boolean $loaded
     * @brief Is plugin loaded.
     */
    private $loaded = false;

    /**
     * @var array $extensions
     * @brief Extension list.
     */
    private $extensions = null;

    /**
     * Class cconstructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        global $camyks;
        parent::__construct('SiteMonitoringToolbar', $path_type);

        /* overwrite Plugin information */
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* load configuration library */
        $this->load_library('SiteMonitoringToolbarConfig');

        /* register plugin as CaMykS event handler */
        if ($camyks->mode == CAMYKS_MODE_SITE) {
            $this->register_asCaMykSEventHandler('onPageLoad');
            $this->register_asCaMykSEventHandler('onTerminate');
        }

        /* register plugin as Admin_Site extension */
        $this->register_asExtension('Admin_Site');
    }

    /* overwrite input methods */

    /**
     * Initialise input.
     * @param array $params
     * @return void
     */
    public function initialise($params=array()) {
        global $camyks;

        /* check locale */
        $locale = in_array($camyks->current_language, array('fr', 'en')) ? $camyks->current_language : 'en';

        /* load styles */
        $this->add_styleFile('SiteMonitoringToolbar.css');

        /* load scripts */
        $this->add_JSEngineFile('tool/xml.js');
        $this->add_JSEngineFile('tool/htmlelement.js');
        $this->add_JSEngineFile('object/cajaxrequest.js');
        $this->add_JSFile('SiteMonitoringToolbar.js');
        $this->add_JSLoadScript('SiteMonitoringToolbar.initialise();');
        $this->add_JSWindowEventScript('resize', 'SiteMonitoringToolbar.resize_toolbar();');
        $this->add_JSScript('SiteMonitoringToolbar.set_param("pluginURL", "'.$this->plugin_url.'");');
        $this->add_JSScript('SiteMonitoringToolbar.set_param("locale", "'.$locale.'");');
        $this->add_JSScript('SiteMonitoringToolbar.set_param("pictureBaseURL", "'.$this->get_fileURL('img').'");');
        $this->add_JSScript('SiteMonitoringToolbar.set_param("requestBaseURL", "request.php?input='.$this->name.'");');

        /* clean session value */
        $camyks->set_sessionValue('SMTBench', false);
        $camyks->set_sessionValue('SMTDBStats', false);
        $camyks->set_sessionValue('SMTSDBQueries', false);
        $camyks->set_sessionValue('SMTStatItems', false);
        $camyks->set_sessionValue('SMTEditItems', false);

        /* set as loaded */
        $this->loaded = true;

        /* Input generic initialization */
        parent::initialise();
    }

    /**
     * Execute input in request mode.
     * @return void
     */
    public function execute_request() {
        global $camyks;

        /* load camyks in site mode */
        $camyks->get_siteInit();

        /* load plugin configuration */
        $this->config = new SiteMonitoringToolbarConfig('config', $this);
        $this->config->get();

        /* build error message */
        $error = array(
            'title'         => $this->get_translation('requestfailed'),
            'description'   => $this->get_translation('requestfailed'),
            'content1'      => $this->get_translation('requestfailed2'),
        );

        /* check access restriction */
        if ($this->config->vars['accessRestriction'] == 0 and ($camyks->check_adminUser() === false or $camyks->adminUser->webmaster == 0))
            $camyks->throwFatalError($error);
        elseif ($this->config->vars['accessRestriction'] == 1 and $camyks->check_adminUser() === false)
            $camyks->throwFatalError($error);

        /* load mode to execute */
        $mode = isset($_REQUEST['mode'])?$_REQUEST['mode']:'';

        /* check file value */
        switch ($mode) {
            case 'loadConfig':
                $this->execute_request_loadConfig();
                break;
            case 'displayPHPStats':
                $this->execute_request_displayPHPStats();
                break;
            case 'startDBStats':
                $this->execute_request_startDBStats();
                break;
            case 'stopDBStats':
                $this->execute_request_stopDBStats();
                break;
            case 'displayDBStats':
                $this->execute_request_displayDBStats();
                break;
            case 'startBench':
                $this->execute_request_startBench();
                break;
            case 'stopBench':
                $this->execute_request_stopBench();
                break;
            case 'displayBench':
                $this->execute_request_displayBench();
                break;
            case 'displayConfiguration':
                $this->execute_request_displayConfiguration();
                break;
            case 'saveConfiguration':
                $this->execute_request_saveConfiguration();
                break;
            case 'disconnect':
                $this->execute_request_disconnect();
                break;
            default:
                /* throw fatal error */
                $camyks->throwFatalError($error);
        }
    }

    /* overwrite plugin methods */

    /**
     * Execute handler on CaMykS page load.
     * @return void
     */
    public function execute_onCaMykSPageLoad() {
        global $camyks;

        /* load plugin configuration */
        $this->config = new SiteMonitoringToolbarConfig('config', $this);
        $this->config->get();

        /* check rights */
        if ($this->config->vars['accessRestriction'] == 0 and ($camyks->check_adminUser() === false or $camyks->adminUser->webmaster == 0))
            return;
        elseif ($this->config->vars['accessRestriction'] == 1 and $camyks->check_adminUser() === false)
            return;

        /* start initialisation */
        $this->initialise();
    }

    /**
     * Execute handler on camyks terminate.
     * @return void
     */
    public function execute_onCaMykSTerminate() {
        global $camyks;

        /* check if plugin is loaded */
        if ($this->loaded == false)
            return;

        /* load extensions */
        $this->load_registeredExtensions();

        /* check for bench values loading */
        if ($camyks->get_executionVariable('_cBench') == 'shared')
            $camyks->set_sessionValue('SMTBench', $camyks->get_sharedData('_cBenchResult'));

        /* check for DB statistics values loading */
        if ($camyks->get_executionVariable('_cDBQueries') == 'shared') {
            $camyks->set_sessionValue('SMTDBStats', $camyks->get_sharedData('_cDBStatsResult'));
            $camyks->set_sessionValue('SMTDBQueries', $camyks->get_sharedData('_cDBQueriesResult'));
        }

        /* check for registered statistics items */
        $statItems = array();
        $statItems[] = array('objectName'=>'visits', 'objectId'=>0);
        if (isset($camyks->contentPage) and $camyks->contentPage->id > 0)
            $statItems[] = array('objectName'=>'sitepage', 'objectId'=>$camyks->contentPage->id);
        /* load registered statistics items from extensions */
        foreach ($this->extensions as &$plugin)
            $statItems += $plugin->get_SMTStatItems();

        /* check for edit action items */
        /* TO DO */

        /* build PHP stats */
        $PHPStats = array(
                /* memory */
                'memoryEnd'     => file_getFileSize(memory_get_usage()),
                'memoryPeak'    => file_getFileSize(memory_get_peak_usage()),
                'memoryLimit'   => ini_get('memory_limit').language_getFileUnit(),

                /* files */
                'includedFiles' => count(get_included_files()),

                /* request values */
                'requestData'   => $_REQUEST,

                /* cookies values */
                'cookieData'    => $_COOKIE,

                /* shared objects */
                'sharedObjects' => $camyks->get_sharedObjectList(),

                /* shared data */
                'sharedData'    => $camyks->get_sharedData(),
       );
        $camyks->set_sessionValue('SMTPHPStats', $PHPStats);
    }

    /* request mode methods */

    /**
     * Execute input in request/loadConfig mode.
     * @return void
     */
    private function execute_request_loadConfig() {
        global $camyks;

        $config = array(
                /* plugin configuration */
                'buttonLocation'        => $this->config->vars['buttonLocation'],
                'appliedTheme'          => $this->config->vars['appliedTheme'],

                /* admin specific */
                'allowConfiguration'    => $camyks->check_adminUser() ? $camyks->adminUser->webmaster : 0,
                'allowLogout'           => $camyks->check_adminUser(),

                /* live settings */
                'DBStatsStatus'         => $camyks->get_executionVariable('_cDBQueries') == 'shared' ? 1 : 0,
                'BenchStatus'           => $camyks->get_executionVariable('_cBench') == 'shared' ? 1 : 0,
        );

        /* prepare answer */
        $result = new CRequestAnswer(array('action'=>'loadConfig'));
        $result->update_param('config', $config);

        /* send answer */
        $result->set_asSuccess();
        $result->send_asJSON();
    }

    /**
     * Execute input in request/displayPHPStats mode.
     * @return void
     */
    private function execute_request_displayPHPStats() {
        global $camyks;

        /* prepare answer */
        $result = new CRequestAnswer(array('action'=>'displayPHPStats'));
        $result->update_param('PHPStats', $camyks->get_sessionValue('SMTPHPStats', false));

        /* send answer */
        $result->set_asSuccess();
        $result->send_asJSON();
    }

    /**
     * Execute input in request/startDBStats mode.
     * @return void
     */
    private function execute_request_startDBStats() {
        global $camyks;

        $camyks->set_executionVariable('_cDBQueries', 'shared');
        $camyks->set_executionVariable('_cDBStats', 'shared');

        /* prepare answer */
        $result = new CRequestAnswer(array('action'=>'startDBStats'));

        /* send answer */
        $result->set_asSuccess();
        $result->send_asJSON();
    }

    /**
     * Execute input in request/stopDBStats mode.
     * @return void
     */
    private function execute_request_stopDBStats() {
        global $camyks;

        $camyks->set_executionVariable('_cDBQueries', 'false');
        $camyks->set_executionVariable('_cDBStats', 'false');

        /* prepare answer */
        $result = new CRequestAnswer(array('action'=>'stopDBStats'));

        /* send answer */
        $result->set_asSuccess();
        $result->send_asJSON();
    }

    /**
     * Execute input in request/displayDBStats mode.
     * @return void
     */
    private function execute_request_displayDBStats() {
        global $camyks;

        /* prepare answer */
        $result = new CRequestAnswer(array('action'=>'displayDBStats'));
        $result->update_param('DBStats', $camyks->get_sessionValue('SMTDBStats', false));
        $result->update_param('DBQueries', $camyks->get_sessionValue('SMTDBQueries', false));

        /* send answer */
        $result->set_asSuccess();
        $result->send_asJSON();
    }

    /**
     * Execute input in request/startBench mode.
     * @return void
     */
    private function execute_request_startBench() {
        global $camyks;

        $camyks->set_executionVariable('_cBench', 'shared');

        /* prepare answer */
        $result = new CRequestAnswer(array('action'=>'startBench'));

        /* send answer */
        $result->set_asSuccess();
        $result->send_asJSON();
    }

    /**
     * Execute input in request/stopBench mode.
     * @return void
     */
    private function execute_request_stopBench() {
        global $camyks;

        $camyks->set_executionVariable('_cBench', 'false');

        /* prepare answer */
        $result = new CRequestAnswer(array('action'=>'stopBench'));

        /* send answer */
        $result->set_asSuccess();
        $result->send_asJSON();
    }

    /**
     * Execute input in request/displayBench mode.
     * @return void
     */
    private function execute_request_displayBench() {
        global $camyks;

        /* prepare answer */
        $result = new CRequestAnswer(array('action'=>'displayBench'));
        $result->update_param('Bench', $camyks->get_sessionValue('SMTBench', false));

        /* send answer */
        $result->set_asSuccess();
        $result->send_asJSON();
    }

    /**
     * Execute input in request/displayConfiguration mode.
     * @return void
     */
    private function execute_request_displayConfiguration() {
        global $camyks;

        /* prepare answer */
        $result = new CRequestAnswer(array('action'=>'displayConfiguration'));

        /* check admin user */
        if (!$camyks->check_adminUser() or !$camyks->adminUser->webmaster) {
            $result->set_asFailure();
            $result->send_asJSON();
        }

        /* load values and encode them to JS */
        $lAR = $this->config->get_accessRestrictionList();
        foreach ($lAR as $index => $value)
            $lAR[$index] = string_html2Text($value);

        $lBL = $this->config->get_buttonLocationList();
        foreach ($lBL as $index => $value)
            $lBL[$index] = string_html2Text($value);

        $lAT = $this->config->get_availableThemeList();
        foreach ($lAT as $index => $value)
            $lAT[$index] = string_html2Text($value);


        /* add configuration data to answer */
        $data = array(
            'accessRestrictionList' => $lAR,
            'buttonLocationList'    => $lBL,
            'availableThemeList'    => $lAT,
            'default'               => array(
                'accessRestriction' => $this->config->vars['accessRestriction'],
            ),
        );
        $result->update_param('ConfigurationData', $data);

        /* send answer */
        $result->set_asSuccess();
        $result->send_asJSON();
    }

    /**
     * Execute input in request/saveConfiguration mode.
     * @return void
     */
    private function execute_request_saveConfiguration() {
        global $camyks;

        /* prepare answer */
        $result = new CRequestAnswer(array('action'=>'saveConfiguration'));

        /* check admin user */
        if (!$camyks->check_adminUser() or !$camyks->adminUser->webmaster) {
            $result->set_asFailure();
            $result->send_asJSON();
        }

        /* save configuration */
        $this->config->get_fromHeader();
        $this->config->save();

        /* send answer */
        $result->set_asSuccess();
        $result->send_asJSON();
    }

    /**
     * Execute input in request/disconnect mode.
     * @return void
     */
    private function execute_request_disconnect() {
        global $camyks;

        /* disconnect admin user */
        $camyks->kill_session();

        /* prepare answer */
        $result = new CRequestAnswer(array('action'=>'disconnect'));

        /* send answer */
        $result->set_asSuccess();
        $result->send_asJSON();
    }

    /* specific tool methods */

    /**
     * Load registered extensions.
     * @return void
     */
    private function load_registeredExtensions() {
        $this->extensions = $this->get_registeredExtensions();
    }

    /* Admin_Site extension configuration methods */

    /**
     * Initialise object in Admin_Site / view configuration mode.
     * @return void
     */
    public function initialise_configDisplay() {
        /* load plugin configuration */
        $this->config = new SiteMonitoringToolbarConfig('config', $this);
        $this->config->get();
    }

    /**
     * Display object in Admin_Site / view configuration mode.
     * @return void
     */
    public function display_configDisplay() {
        $this->load_file('html/configuration/view.html.inc');
    }

    /**
     * Initialise object in Admin_Site / edit configuration mode.
     * @param Object $form
     * @return void
     */
    public function initialise_configEdition($form) {
        /* load plugin configuration */
        $this->config = new SiteMonitoringToolbarConfig('config', $this);
        $this->config->get();

        /* update form */
        $this->form = &$form;
        $this->form->set_object($this->config);
    }

    /**
     * Display object in Admin_Site / edit configuration mode.
     * @return void
     */
    public function display_configEdition() {
        $this->load_file('html/configuration/edit.html.inc');
    }

    /**
     * Execute object in Admin_Site / save configuration mode.
     * @return void
     */
    public function save_configuration() {
        $this->config = new SiteMonitoringToolbarConfig('config', $this);
        $this->config->get();
        $this->config->get_fromHeader();
        return $this->config->save();
    }
}
?>
