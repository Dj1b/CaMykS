<?php
/**
 * @brief Admin_Statistics module.
 * <br /> Records and displays website statistics.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2.1
 * @date Creation: May 2007
 * @date Modification: Jul 2025
 * @copyright 2007 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @note Available types :
 * - single : each update create an entry - display each entry
 * - mixed : each item is saved by day and values - display by date and detail values
 * - dated : each item is save by day and values - display by date only
 * - detail : each item is save by day and values - display detail values only
 * - total : only one entry per object (date is first entry value)
 */

/**
 * Admin_Statistics class.
 */
final class Admin_Statistics extends Module {
    /**
     * var Object $statobject
     * @brief Statistic object.
     */
    public $statobject;

    /**
     * var Object $statdata
     * @brief Statistic data object.
     */
    public $statdata;

    /**
     * var Object $registered_stats
     * @brief Already registered statistics.
     */
    protected $registered_stats = null;

    /**
     * var Object $stattypes
     * @brief Statistic type list.
     */
    private $stattypes = array('single', 'mixed', 'dated', 'detail', 'total');

    /**
     * var array $statslist
     * @brief Statistic object list.
     */
    protected $statslist;

    /**
     * var array $displayedItems
     * @brief Stores how many day/month/year to display.
     */
    protected $displayedItems = array('day'=>16, 'month'=>16, 'year'=>8);

    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('Admin_Statistics', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* Override Module variables */
        $this->type = 'admin';
        $this->admin_type = 'monitoring';

        /* Define Plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Load plugin libraries */
        $this->load_library('Admin_Statistic');
        $this->load_library('Admin_StatisticData');
        $this->load_library('Admin_StatisticConfig');
        $this->load_library('Admin_StatisticSingleOptions');
        $this->load_library('Admin_StatisticMixedOptions');
        $this->load_library('Admin_StatisticDatedOptions');
        $this->load_library('Admin_StatisticDetailOptions');
        $this->load_library('Admin_StatisticsSettings');

        /* Initialise plugin libraries */
        $this->statconfig = new Admin_StatisticConfig(0, $this);
        $this->statdata = new Admin_StatisticData(0, $this);
        $this->statobject = new Admin_Statistic(0, $this);
        $this->settings = new Admin_StatisticsSettings('settings', $this);
    }

    /* Mark: Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return $this->statobject->install() and $this->statdata->install()
            and $this->statconfig->install() and $this->settings->install()
            and parent::install();
    }

    /**
     * Uninstall module.
     * @return boolean success
     */
    public function uninstall() {
        return $this->statobject->uninstall()
            and $this->statdata->uninstall()
            and $this->statconfig->uninstall()
            and $this->settings->uninstall();
    }

    /**
     * Check module installation.
     * @return boolean result
     */
    public function is_installed() {
        return $this->statconfig->is_installed();
    }

    /**
     * Define module permissions.
     * @return void
     */
    public function get_rights() {
        global $camyks;
        $this->rights[0] = array(
            'name'      => 'read',
            'title'     => $camyks->get_translation('read'),
            'default'   => false
        );
        $this->rights[1] = array(
            'name'      => 'configuration',
            'title'     => $this->get_translation('rights_configuration'),
            'default'   => false
        );
    }

    /**
     * Return statistic titles
     * @param array $data
     * @param string $type
     * @return array
     */
    public function get_adminStatisticsValueTitles($data, $type=null) {
        switch ($type) {
            case 'webbots':
            case 'webtools':
                foreach ($data as $bot) {
                    if (($botTitle = $this->get_botTitle($bot, $type)) != null)
                        $data[$bot] = $botTitle;
                }
                return $data;
                break;
            default:
                return $data;
        }
    }

    /**
     * Initialise module object in admin mode
     * @return void
     */
    public function init_admin() {
        global $camyks;

        /* Check access rights */
        if ($this->check_right(0) === false)
            return $this->init_admin_accessDenied();

        /* Check dependencies */
        if (!isset($camyks->inputs['TabBuilder']))
            return $this->init_admin_missingPlugin('Input', 'TabBuilder');

        /* Load settings */
        $this->settings->get();

        /* Load registered stats */
        $this->get_registeredStats();

        /* Load statistics styles */
        $this->add_styleFile('admin_statistics.css?v=1.0.0.3');

        /* Load statistics scripts */
        $this->add_JSFile('admin_statistics.js');

        /* Define admin title */
        $this->adminTitle = $this->title;

        /* Build buttons list */
        $this->buttons = array(array(
            'title' => $camyks->get_translation('back'),
            'link'  => $camyks->get_adminLink(),
        ));

        /* Load object to display */
        if (isset($_REQUEST['object'])) {
            $object = $_REQUEST['object'];

            if ($object == '_settings' and $this->check_right(1)) {
                $mode = isset($_REQUEST['mode']) ? $_REQUEST['mode'] : '';
                if ($mode == 'save')
                    $this->init_admin_saveSettings();
                else
                    $this->init_admin_editSettings();
            } elseif (isset($this->registered_stats[$object])) {
                $this->statobject = $this->registered_stats[$object];
                $this->adminTitle .= $camyks->get_translation('formitem_separator');
                $this->adminTitle .= $this->statobject->vars['title'];

                switch ($this->statobject->vars['type']) {
                    case 'single':
                        $this->init_admin_singleObject();
                        break;
                    case 'mixed':
                        $this->init_admin_mixedObject();
                        break;
                    case 'dated':
                        $this->init_admin_datedObject();
                        break;
                    case 'detail':
                        $this->init_admin_detailObject();
                        break;
                    case 'total':
                        $this->init_admin_totalObject();
                        break;
                }

                /* Load tabs */
                $this->load_tabs();
            }
        }

        /* Generic initialisatin */
        parent::init_admin();
    }

    /* Mark: Admin initialise mode sub methods */

    /**
     * Initialise module object in admin/edit settings mode
     * @return void
     */
    private function init_admin_editSettings() {
        global $camyks;

        /* Check configuration permission */
        if ($this->check_right(1) === false)
            return $this->init_admin_accessDenied();

        /* Set admin title */
        $this->adminTitle .= $camyks->get_translation('formitem_separator');
        $this->adminTitle .= $this->get_translation('settings');

        /* Define object */
        $this->object = 'settings';

        /* Build form */
        $this->form = new HTMLForm('editsettings', $this->get_adminLink(array('object'=>'_settings', 'mode'=>'save')), 'POST');
        $this->form->set_object($this->settings);
        $this->form->add_hidden('stat_filteredips_count_', count($this->settings->vars['stat_filteredips']));

        /* Load data */
        $this->statusList = $this->get_settingsStatusList();

        /* Load scripts */
        $this->add_JSEngineFile('tool/html.js');
        $this->add_JSFile('admin_statisticssettings.js?v=1.0.1');
        $this->add_JSScript('var sse = new StatisticsSettingsEditor("sse");');
        $this->add_JSScript('sse.bttn = "'.$this->theme->get_pictURL('minus', 12, 'std').'";');
        $this->add_JSScript('sse.bttn_ = "'.$this->theme->get_pictURL('minus', 12, 'ovr').'";');
        $this->add_JSLoadScript('sse.initialise("'.$this->form->name.'");');

        /* Build buttons list */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'  => $camyks->get_adminLink()
            ),
            array(
                'title' => $camyks->get_translation('valid'),
                'link'  => $this->form->get_HTMLSubmitLink(),
            )
        );
    }

    /**
     * Initialise module object in admin/save settings mode.
     * @return void
     */
    private function init_admin_saveSettings() {
        global $camyks;

        /* Check configuration permission */
        if ($this->check_right(1) === false)
            return $this->init_admin_accessDenied();

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Save settings */
        $this->settings->get_fromHeader();
        if ($this->settings->save()) {
            $this->text = $this->get_translation('configuration_saved');
        } else {
            $this->text = $this->get_translation('configuration_notsaved');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /**
     * Initialise module object in admin/single object mode.
     * @return void
     */
    private function init_admin_singleObject() {
        /* Load options */
        $this->init_admin_getsingleoptions();
        /* Load form */
        $this->init_admin_optionsForm();
        /* Load stats list */
        $this->init_admin_getSingleStatisticValues();
        /* Load color input */
        $this->init_admin_colorPickerInput();
    }

    /**
     * Initialise module object in admin/mixed object mode.
     * @return void
     */
    private function init_admin_mixedObject() {
        /* Load options */
        $this->init_admin_getMixedOptions();
        /* Load form */
        $this->init_admin_optionsForm();
        /* Load stats list */
        $this->init_admin_getDatedStatisticValues();
        $this->init_admin_getDetailStatisticValues();
        /* Load color input */
        $this->init_admin_colorPickerInput();
    }

    /**
     * Initialise module object in admin/detail object mode.
     * @return void
     */
    private function init_admin_detailObject() {
        /* Load options */
        $this->init_admin_getDetailOptions();
        /* Load form */
        $this->init_admin_optionsForm();
        /* Load stats list */
        $this->init_admin_getDetailStatisticValues();
        /* Load color input */
        $this->init_admin_colorPickerInput();
    }

    /**
     * Initialise module object in admin/dated object mode.
     * @return void
     */
    private function init_admin_datedObject() {
        /* Load options */
        $this->init_admin_getDatedOptions();
        /* Load form */
        $this->init_admin_optionsForm();
        /* Load stats list */
        $this->init_admin_getDatedStatisticValues();
        /* Load color input */
        $this->init_admin_colorPickerInput();
    }

    /**
     * Initialise module object in admin/total object mode.
     * @return void
     */
    private function init_admin_totalObject() {
        /* to do */
    }

    /* Mark: Specific public methods */

    /**
     * Update statistic.
     * @param string $name
     * @param string $plugin
     * @param string $type
     * @param string $main
     * @param string $data1
     * @param string $data2
     * @param array $params
     * @return void
     */
    public function update_statistic($name='', $plugin='', $type='', $main='', $data1='', $data2='', $params = array()) {
        global $camyks;

        /* Merge params */
        $params = array_merge(array('checkIPFilter'=>1, 'checkAdmin'=>1, 'checkBot'=>1), $params);

        /* Check variables */
        $data1 = substr($data1, 0, 64);
        $data2 = substr($data2, 0, 64);

        /* Check admin connection */
        if ($params['checkAdmin'] and $camyks->check_adminUser())
            return;

        /* Check IP Filter */
        if ($params['checkIPFilter'] and $this->check_filteredIp(client_getIP()))
            return;

        /* Check web bots */
        if ($params['checkBot'] == 1 and !$camyks->is_visitorHuman())
            return;

        /* Check name */
        if ($name == '') {
            /* Log error */
            $camyks->log_executionerror($this, 'Could not save statistic: null name', 'Module:'.$plugin.' - type:'.$type.' - data1:'.$data1.' - data2:'.$data2);
            return;
        }

        /* Check plugin */
        if ($plugin == '' or !isset($camyks->modules[$plugin])) {
            /* Log error */
            $camyks->log_executionerror($this, 'Could not save statistic: null or inexistant plugin', 'Name:'.$name.' - type:'.$type.' - data1:'.$data1.' - data2:'.$data2);
            return;
        }

        /* Check type */
        if ($type == '' or !in_array($type, $this->stattypes)) {
            /* Log error */
            $camyks->log_executionerror($this, 'Could not save statistic: null or inexistant type', 'Module:'.$plugin.' - type:'.$type.' - data1:'.$data1.' - data2:'.$data2);
            return;
        }

        /* Load registered stats */
        $this->get_registeredStats();

        /* Check is stat is already registered */
        if (isset ($this->registered_stats[$name])) {
            /* Object exists, check if object is the same */
            $s = &$this->registered_stats[$name];
            if ($s->vars['plugin'] == $plugin and $s->vars['type'] == $type) {
                $s->update_statistic($main, $data1, $data2);
            } else {
                /* Log error */
                $camyks->log_executionerror($this, 'Could not save statistic: stat with same name already exists', 'Name:'.$name.' - Module:'.$plugin.' - type:'.$type);
                return;
            }
        } else {
            /* Create stat object */
            $this->statobject->id = 0;
            $this->statobject->_libItems['name']->value = $name;
            $this->statobject->_libItems['plugin']->value = $plugin;
            $this->statobject->_libItems['type']->value = $type;
            $this->statobject->_libItems['register_date']->value = time();
            $this->statobject->save();
            $camyks->log_information($this, 'New '.$type.' statistic named '.$name.' registered by module '.$plugin);

            /* Update data */
            $this->statobject->update_statistic($main, $data1, $data2);
        }
    }

    /**
     * Return statistic values.
     * @param string $plugin
     * @param string $statName
     * @param array $params
     * @return array
     */
    public function get_statistics($plugin, $statName, $params=array()) {
        global $camyks;

        /* Load stat id */
        $statId = $this->statobject->get_idFromPluginAndName($plugin, $statName);
        if ($statId === false)
            return array();

        /* Load and return stat data */
        return $this->statdata->get_statistics($statId, $params);
    }

    /**
     * Update site statistics.
     * @return void
     */
    public function update_siteStatistics() {
        global $camyks;

        /* Load settings */
        $this->settings->get();

        /* Check filtered ip */
        if ($this->check_filteredIp(client_getIP()))
            return;

        /* Check contected admin */
        if ($camyks->check_adminUser())
            return;

        /* Load visitor information */
        $visitor = $camyks->get_visitorInformation();

        /* Build update params */
        $params = array('IPFilter'=>0, 'checkAdmin'=>0, 'checkBot'=>0);

        /* Check web bots */
        if ($visitor['platform_type'] === 'bot' and $this->settings->vars['stat_webbots'] == 1)
            return $this->update_statistic('webbots', $this->name, 'mixed', $visitor['bot_name'], '', '', $params);

        /* Check web tools */
        if ($visitor['platform_type'] === 'tool' and $this->settings->vars['stat_webtools'] == 1)
            return $this->update_statistic('webtools', $this->name, 'mixed', $visitor['tool_name'], '', '', $params);

        /* Do not continue for non visitor */
        if (!$camyks->is_visitorHuman())
            return;

        /* Add current page */
        if ($this->settings->vars['stat_sitepage'] == 2)
            $this->update_statistic('sitepage', 'Admin_ContentPage', 'mixed', $camyks->contentPage->id, $camyks->contentPage->params_, $camyks->current_language, $params);
        elseif ($this->settings->vars['stat_sitepage'] == 1)
            $this->update_statistic('sitepage', 'Admin_ContentPage', 'mixed', $camyks->contentPage->id, '', '', $params);

        /* Check for new visitor */
        if ($camyks->get_sessionValue('mysession') != 1) {
            /* Add visit */
            if ($this->settings->vars['stat_visits'] == 1)
                $this->update_statistic('visits', 'Admin_ContentPage', 'dated', '', '', '', $params);

            /* Add referer : (remove http:// from url, and compare to current site url) */
            if ($this->settings->vars['stat_referer'] == 1) {
                $rsite = trim(client_getRefererSite());
                if ($rsite != '' and !url_areInSameDomain(array($rsite, $camyks->get_confValue('url')), true)) {
                    $rsite = parse_url($rsite);
                    if (!in_array($rsite['scheme'], array('http', 'https')))
                        $domain = $rsite['host'].' ('.$rsite['scheme'].')';
                    else
                        $domain = $rsite['host'];
                    $this->update_statistic('referer', 'Admin_ContentPage', 'detail', $domain, '', '', $params);
                }
            }

            /* Add first page */
            if ($this->settings->vars['stat_firstpage'] == 1)
                $this->update_statistic('firstpage', 'Admin_ContentPage', 'detail', $camyks->contentPage->id, $camyks->contentPage->params_, $camyks->current_language, $params);

            /* Update session value */
            $camyks->set_sessionValue('mysession', 1);
        }
    }

    /**
     * Return displayed item for the given period.
     * @param string $period
     * @return integer
     */
    public function get_displayItems($period) {
        if (!isset($this->displayedItems[$period]))
            return 0;
        return $this->displayedItems[$period];
    }

    /* Mark: Specific private methods */

    /**
     * Display statistic.
     * @return void
     */
    protected function display_statistic() {
        /* Check layout to load */
        if (isset ($this->statobject->vars['type']))
            $layout = 'admin_'.$this->statobject->vars['type'].'.html.inc';
        else if (isset($this->object))
            $layout = 'admin_'.$this->object.'.html.inc';
        else
            $layout = 'admin_none.html.inc';

        /* Load layout */
        $this->load_file('html/'.$layout);
    }

    /**
     * Load registered statistic list.
     * @return boolean success
     */
    private function get_registeredStats() {
        global $camyks;

        /* Check if registered stats list already exists */
        if (isset($this->registered_stats))
            return true;

        /* Load complete list */
        $list = $this->statobject->get_objectList(false);

        /* Remove disabled module stats objects */
        $this->registered_stats = array();
        foreach ($list as $s) {
            if (isset($camyks->modules[$s->vars['plugin']])) {
                $s->get_statisticTitle();
                $this->registered_stats[$s->vars['name']] = $s;
            }
        }

        /* Return success */
        return true;
    }

    /**
     * Build tabs.
     * @return void
     */
    private function load_tabs() {
        global $camyks;

        $mode = $this->statobject->vars['type'];

        /* Load tabs */
        $this->tabBuilder = &$camyks->inputs['TabBuilder'];

        /* Add tabs */
        if (in_array($mode, array('single', 'mixed', 'dated')))
            $this->tabBuilder->add_tab(array(
                'name'  => 'Display',
                'title' => $this->get_translation('tabdisplay'),
            ));
        if (in_array($mode, array('mixed', 'detail')))
            $this->tabBuilder->add_tab(array(
                'name'  => 'Detail',
                'title' => $this->get_translation('tabdetail'),
            ));
        $this->tabBuilder->add_tab(array(
            'name'  => 'Options',
            'title' => $this->get_translation('taboptions'),
        ));

        /* Add help tab */
        if ($this->help != null)
            $this->tabBuilder->add_tab(array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help'),
            ));

        /* Initialise tabs */
        if ($mode == 'detail')
            $this->tabBuilder->initialise(array('default'=>'Detail'));
        else
            $this->tabBuilder->initialise(array('default'=>'Display'));
    }

    /**
     * Build tabs in single type stats.
     * @return void
     */
    private function init_admin_singleStatisticsTabs() {
        global $camyks;

        /* Load tabs */
        $this->tabBuilder = &$camyks->inputs['TabBuilder'];

        /* Add tabs */
        $this->tabBuilder->add_tabs(array(
            array(
                'name'  => 'Display',
                'title' => $this->get_translation('tabdisplay'),
            ),
            array(
                'name'  => 'Options',
                'title' => $this->get_translation('taboptions'),
            ),
        ));

        /* Add help tab */
        if ($this->help != null)
            $this->tabBuilder->add_tab(array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help'),
            ));

        /* Initialise tabs */
        $this->tabBuilder->initialise(array('default'=>'Display'));
    }

    /**
     * Build tabs in mixed type stats.
     * @return void
     */
    private function init_admin_mixedStatisticsTabs() {
        global $camyks;

        /* Load tabs */
        $this->tabBuilder = &$camyks->inputs['TabBuilder'];

        /* Add tabs */
        $this->tabBuilder->add_tabs(array(
            array(
                'name'  => 'Display',
                'title' => $this->get_translation('tabdisplay'),
            ),
            array(
                'name'  => 'Detail',
                'title' => $this->get_translation('tabdetail'),
            ),
            array(
                'name'  => 'Options',
                'title' => $this->get_translation('taboptions'),
            ),
        ));

        /* Initialise tabs */
        $this->tabBuilder->initialise(array('default'=>'Display'));
    }

    /**
     * Build option form.
     * @return void
     */
    private function init_admin_optionsForm() {
        global $camyks;

        /* Build form object */
        $this->form = new HTMLForm('admin_statistics_form', $this->get_adminLink(), 'POST');
        $this->form->add_hidden('update_config', 1);
        $this->form->add_hidden('openTab', 'Detail');
        $this->form->add_hidden('object', $this->statobject->vars['name']);

        /* Add form name into javascript */
        $this->add_JSScript('admin_statistics_form = "'.$this->form->name.'";');

        /* Build button list */
        $this->optionsButtons = array(array(
            'title' => $this->get_translation('computeagain'),
            'url'   => $this->form->get_HTMLSubmitLink(),
        ));
    }

    /**
     * Load color picker.
     * @return void
     */
    private function init_admin_colorPickerInput(){
        global $camyks;
        if (isset($camyks->inputs['ColorPicker'])) {
            $this->colorPicker = &$camyks->inputs['ColorPicker'];
            $this->colorPicker->initialise('cp', 'default', 'modal');
        } else {
            $this->colorPicker = false;
        }
    }

    /**
     * Build option in single type stats.
     * @return void
     */
    private function init_admin_getSingleOptions() {
        global $camyks;

        $this->config = new Admin_StatisticSingleOptions(0, $this);
        if (isset ($_REQUEST['update_config'])) {
            /* Load new config from header */
            $this->config->get_fromHeader();

            /* Save new config : colors */
            $this->statconfig->_libItems['user']->value = $camyks->adminUser->login;
            $this->statconfig->_libItems['object']->value = 'colors';
            $this->statconfig->_libItems['mode']->value = '';
            $this->statconfig->_libItems['value']->value = $this->config->get_colorsAsProperties();
            $this->statconfig->save();

            /* Save new config : values */
            $this->statconfig->_libItems['object']->value = $this->statobject->vars['name'];
            $this->statconfig->_libItems['value']->value = $this->config->get_valuesAsProperties();
            $this->statconfig->save();
        } else {
            /* Load config from database */
            $this->config->get();
            $savedconfigs = $this->statconfig->get_configs ($this->statobject->vars['name']);
            if (isset ($savedconfigs['colors']))
                $this->config->get_colorsFromProperties($savedconfigs['colors']->vars['value']);
            if (isset ($savedconfigs[$this->statobject->vars['name']]))
                $this->config->get_valuesFromProperties($savedconfigs[$this->statobject->vars['name']]->vars['value']);
        }
        $this->config->get_fromItems();
    }

    /**
     * Load values in single type stats.
     * @return void
     */
    private function init_admin_getSingleStatisticValues() {
        global $camyks;

        /* Load config */
        $config = $this->config->build_config($this->statobject->id);

        /* Load statistics description */
        $this->statsdesc = $config['desc'];

        /* Load statistics list */
        $this->statslist = $this->statdata->get_objectList(false, $config['where'], 0, $config['limit'], 'statdate', 'desc');

        /* Load titles */
        $list = array();
        foreach ($this->statslist as $stat)
            if (!isset ($list[$stat->vars['main']]))
        $list[$stat->vars['main']] = $stat->vars['main'];
        $this->maintitles = $camyks->modules[$this->statobject->vars['plugin']]->get_adminStatisticsValueTitles($list, $this->statobject->vars['name']);
    }


    /**
     * Build option in mixed type stats.
     * @return void
     */
    private function init_admin_getMixedOptions() {
        global $camyks;

        $this->config = new Admin_StatisticMixedOptions(0, $this);
        if (isset ($_REQUEST['update_config'])) {
            /* Load new config from header */
            $this->config->get_fromHeader();

            /* Save new config : colors */
            $this->statconfig->_libItems['user']->value = $camyks->adminUser->login;
            $this->statconfig->_libItems['object']->value = 'colors';
            $this->statconfig->_libItems['mode']->value = '';
            $this->statconfig->_libItems['value']->value = $this->config->get_colorsAsProperties();
            $this->statconfig->save();

            /* Save new config : values */
            $this->statconfig->_libItems['object']->value = $this->statobject->vars['name'];
            $this->statconfig->_libItems['value']->value = $this->config->get_valuesAsProperties();
            $this->statconfig->save();
        } else {
            /* Load config from database */
            $this->config->get();
            $savedconfigs = $this->statconfig->get_configs ($this->statobject->vars['name']);
            if (isset ($savedconfigs['colors']))
                $this->config->get_colorsFromProperties($savedconfigs['colors']->vars['value']);
            if (isset ($savedconfigs[$this->statobject->vars['name']]))
                $this->config->get_valuesFromProperties($savedconfigs[$this->statobject->vars['name']]->vars['value']);
        }
        $this->config->get_fromItems();

        /* Load config */
        $this->c_config = $this->config->build_config($this->statobject->id);
    }

    /**
     * Build option in dated type stats.
     * @return void
     */
    private function init_admin_getDatedOptions() {
        global $camyks;

        $this->config = new Admin_StatisticDatedOptions(0, $this);
        if (isset ($_REQUEST['update_config'])) {
            /* Load new config from header */
            $this->config->get_fromHeader();

            /* Save new config : colors */
            $this->statconfig->_libItems['user']->value = $camyks->adminUser->login;
            $this->statconfig->_libItems['object']->value = 'colors';
            $this->statconfig->_libItems['mode']->value = '';
            $this->statconfig->_libItems['value']->value = $this->config->get_colorsAsProperties();
            $this->statconfig->save();

            /* Save new config : values */
            $this->statconfig->_libItems['object']->value = $this->statobject->vars['name'];
            $this->statconfig->_libItems['value']->value = $this->config->get_valuesAsProperties();
            $this->statconfig->save();
        } else {
            /* Load config from database */
            $this->config->get();
            $savedconfigs = $this->statconfig->get_configs ($this->statobject->vars['name']);
            if (isset ($savedconfigs['colors']))
                $this->config->get_colorsFromProperties($savedconfigs['colors']->vars['value']);
            if (isset ($savedconfigs[$this->statobject->vars['name']]))
                $this->config->get_valuesFromProperties($savedconfigs[$this->statobject->vars['name']]->vars['value']);
        }
        $this->config->get_fromItems();

        /* Load config */
        $this->c_config = $this->config->build_config($this->statobject->id);
    }

    /**
     * Build option in detail type stats.
     * @return void
     */
    private function init_admin_getDetailOptions() {
        global $camyks;

        $this->config = new Admin_StatisticDetailOptions(0, $this);
        if (isset ($_REQUEST['update_config'])) {
            /* Load new config from header */
            $this->config->get_fromHeader();

            /* Save new config : colors */
            $this->statconfig->_libItems['user']->value = $camyks->adminUser->login;
            $this->statconfig->_libItems['object']->value = 'colors';
            $this->statconfig->_libItems['mode']->value = '';
            $this->statconfig->_libItems['value']->value = $this->config->get_colorsAsProperties();
            $this->statconfig->save();

            /* Save new config : values */
            $this->statconfig->_libItems['object']->value = $this->statobject->vars['name'];
            $this->statconfig->_libItems['value']->value = $this->config->get_valuesAsProperties();
            $this->statconfig->save();
        } else {
            /* Load config from database */
            $this->config->get();
            $savedconfigs = $this->statconfig->get_configs ($this->statobject->vars['name']);
            if (isset ($savedconfigs['colors']))
                $this->config->get_colorsFromProperties($savedconfigs['colors']->vars['value']);
            if (isset ($savedconfigs[$this->statobject->vars['name']]))
                $this->config->get_valuesFromProperties($savedconfigs[$this->statobject->vars['name']]->vars['value']);
        }
        $this->config->get_fromItems();

        /* Load config */
        $this->c_config = $this->config->build_config($this->statobject->id);
    }


    /**
     * Load value in dated type stats.
     * @return void
     */
    private function init_admin_getDatedStatisticValues() {
        /* Load main tab statistics total */
        $this->statsmaintotal = $this->statdata->get_statisticsTotalValue($this->c_config['maintotalwhere']);

        /* Load main tab statistics by day */
        $this->statsmainbyday = $this->statdata->get_statisticsByDayValue($this->c_config['mainbydaywhere']);

        /* Load main tab statistics by month */
        $this->statsmainbymonth = $this->statdata->get_statisticsByMonthValue($this->c_config['mainbymonthwhere']);

        /* Load main tab statistics by year */
        $this->statsmainbyyear = $this->statdata->get_statisticsByYearValue($this->c_config['mainbyyearwhere']);
    }

    /**
     * Load value in detail type stats.
     * @return void
     */
    private function init_admin_getDetailStatisticValues() {
        global $camyks;

        /* Load detail tab statistics description */
        $this->statsdetaildesc = $this->c_config['detaildesc'];

        /* Load detail tab statistics total */
        $this->statsdetailtotal = $this->statdata->get_statisticsTotalValue($this->c_config['detailwhere']);

        if ($this->statsdetailtotal > 0) {
            /* Load detail tab statistics list */
            $this->statsdetaillist = $this->statdata->get_mixedStatisticList($this->c_config['detailwhere'], $this->c_config['detaillimit']);

            /* Load detail tab statistics max value */
            foreach ($this->statsdetaillist as $stat) {
                $this->statsdetailmax = $stat;
                break;
            }

            /* Load combined titles */
            $list = array();
            foreach ($this->statsdetaillist as $stat=>$value)
                if (!isset($list[$stat]))
                    $list[$stat] = $stat;

            $this->detailtitles = $camyks->modules[$this->statobject->vars['plugin']]->get_adminStatisticsValueTitles ($list, $this->statobject->vars['name']);
        } else {
            $this->statsdetaillist = array();
        }
    }

    /**
     * Display color picker.
     * @param string $name
     * @return void
     */
    protected function display_colorPicker($name) {
        /* Check config color value */
        if (isset($this->config->vars[$name])) {
            $color = $this->config->vars[$name];
            /* Check if color picker is available */
            if ($this->colorPicker !== false) {
                $this->colorPicker->display($name, $color);
            } else {
                $this->colorPickerValue = $color;
                $this->load_file('html/admin_colorpicker.html.inc');
            }
        }
    }

    /**
     * Return settings status list.
     * @return array
     */
    private function get_settingsStatusList() {
        return array(
            0 => $this->get_translation('status_disabled'),
            1 => $this->get_translation('status_enabled')
        );
    }

    /**
     * Check given ip in filtered ip list.
     * @param string $ip
     * @return boolean result
     */
    private function check_filteredIP($ip) {
        if (!isset($this->settings->vars))
            $this->settings->get();
        return (in_array($ip, $this->settings->vars['stat_filteredips']));
    }

    /**
     * Return optimised value.
     * @param integer $value
     * @return string
     */
    protected function get_optimisedValue($value) {
        if ($value < 1000)
            return ''.$value;
        if ($value < 10000)
            return round($value/1000, 1).'k';
        if ($value < 1000000)
            return (int)($value/1000).'k';
        if ($value < 10000000)
            return round($value/1000000, 1).'M';
        return (int)($value/1000000).'M';
    }

    /**
     * Return bot title
     * @param string $bot
     * @param string $type
     * @return string
     */
    private function get_botTitle($bot, $type) {
        /* Check bot */
        if ($bot == null or $bot == '')
            return null;

        /* Convert type */
        if ($type == 'webbots') {
            $type = 'bot';
            $botInfo = client_getBotInfos($bot);
            if ($botInfo == array())
                $botInfo = client_getBeforeBotInfos($bot);
            if ($botInfo == array())
                $botInfo = client_getBeforeBotInfos($bot);
            if ($botInfo == array())
                $botInfo = client_getUnknownInfos($bot);
            if ($botInfo == array())
                $botInfo = client_getGenericInfos($bot);
        } elseif ($type == 'webtools') {
            $type = 'tool';
            $botInfo = client_getToolInfos($bot);
            if ($botInfo == array())
                $botInfo = client_getGenericInfos($bot);
        } else
            return null;

        /* Check data */
        if ($botInfo == null)
            return null;

        /* Build bot title */
        if ($botInfo['engine_title'] == '') {
            /* Add bot title */
            if ($botInfo[$type.'_url'] == '')
                $botTitle = $botInfo[$type.'_title'];
            else
                $botTitle = '<a href="'.$botInfo[$type.'_url'].'" target="_blank" rel="noopener, noreferrer">'.$botInfo[$type.'_title'].'</a>';
        } else {
            /* Add engine title */
            if ($botInfo['engine_url'] == '')
                $botTitle = $botInfo['engine_title'];
            else
                $botTitle = '<a href="'.$botInfo['engine_url'].'" target="_blank" rel="noopener, noreferrer">'.$botInfo['engine_title'].'</a>';
            /* Add bot title */
            if ($botInfo[$type.'_title'] != '')
                if ($botInfo[$type.'_url'] == '')
                    $botTitle .= ' ('.$botInfo[$type.'_title'].')';
                else
                    $botTitle .= ' (<a href="'.$botInfo[$type.'_url'].'" target="_blank" rel="noopener, noreferrer">'.$botInfo[$type.'_title'].'</a>)';
        }
        return $botTitle;
    }
}
?>
