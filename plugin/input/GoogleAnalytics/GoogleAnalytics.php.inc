<?php
/**
 * @brief GoogleAnalytics Input
 * <br /> Adds Google Analytics snippet on page
 * @details Plugin / Input Engine
 * @file plugin/input/GoogleAnalytics/GoogleAnalytics.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Sep 2018
 * @date Modification: Sep 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * GoogleAnalytics Input class.
 */
final class GoogleAnalytics extends Input {
    /**
     * var Object $config
     * @brief Input configuration.
     */
    protected $config;

    /**
     * var boolean $status
     * @brief Snippet insertion status
     */
    private $status = 'enabled';

    /**
     * var boolean $isLive
     * @brief Snippet code is already written.
     */
    private $isLive = false;

    /**
     * var array $extraData
     * @brief Store additional code to insert in snipper.
     */
    protected $extraData = array();

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('GoogleAnalytics', $path_type);

        /* overwrite Plugin information */
        $this->version = '1.0';
        $this->plugin_package = 'Google';

        /* author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* register plugin as Admin_Site extension */
        $this->register_asExtension('Admin_Site');

        /* automatically insert it in the page */
        $this->register_asCaMykSEventHandler('onPageLoad');
        $this->register_asCaMykSEventHandler('onBodyOpen');
    }

    /* overwrite input methods */

    /**
     * Initialise input.
     * @param array $params
     * @return void
     */
    public function initialise($params=array()) {
        global $camyks;

        /* load configuration */
        $this->load_configuration();

        /* Input generic initialization */
        parent::initialise();

        $this->add_trackingCode($this->get_configValue('trackingId'), $this->get_configValue('trackingParams'));
    }

    /**
     * Display input.
     * @return void
     */
    public function display() {
        global $camyks;

        /* check status */
        if ($this->status == 'disabled')
            return;

        /* check admin visits */
        if ($this->get_configValue('enableAdminStats') == 0 and $camyks->check_adminUser())
            return;

        /* display snippet */
        parent::display();

        /* mark snippet as live */
        $this->isLive = true;
    }

    /* External action methods */

    /**
     * Mark plugin as disabled
     * @return void
     */
    public function disable() {
        $this->status = 'disabled';
    }

    /**
     * Add a tracking code.
     * @param string $trackingId
     * @param mixed $params
     * @return void
     */
    public function add_trackingCode($trackingId, $params=null) {
        $this->add_extraData('config', $trackingId, $params);
    }

    /**
     * Add extra data.
     * @param string $type
     * @param string $value
     * @param mixed $params
     * @return void
     */
    public function add_extraData($type='', $value='', $params=null) {
        /* check parameters */
        $type = trim($type); if ($type == '') return;
        $value = trim($value); if ($value == '') return;

        /* display tracking code or add it to init list */
        if ($this->isLive)
            $this->display_extra(array('type'=>$type, 'value'=>$value, 'params'=>$params), true);
        else
            $this->extraData[] = array('type'=>$type, 'value'=>$value, 'params'=>$params);
    }

    /* Specific tool methods */

    /**
     * Load configuration.
     * @return void
     */
    private function load_configuration() {
        $this->load_library('GoogleAnalyticsConfig');
        $this->config = new GoogleAnalyticsConfig('config', $this);
        $this->config->get();
    }

    /**
     * Return configuration value.
     * @param string $name
     * @return mixed
     */
    protected function get_configValue($name='') {
        return $this->config->get_value($name);
    }

    /**
     * Display extra code
     * @param array $extra
     * @param boolean $addTags
     * @return void
     */
    protected function display_extra($extra, $addTags=false) {
        if ($addTags) print_r('<script>'."\n");

        print_r('gtag(\''.$extra['type'].'\', \''.$extra['value'].'\'');
        if (is_array($extra['params']))
            print_r(', '.json_encode($extra['params']));
        elseif (is_string($extra['params']) and trim($extra['params']) != '')
            print_r(', '.$extra['params']);
        print_r(');'."\n");

        if ($addTags) print_r('</script>'."\n");
    }

    /* CaMykS page event methods */

    /**
     * Execute handler on page loading.
     * @return void
     */
    public function execute_onCaMykSPageLoad() {
        $this->initialise();
    }

    /**
     * Execute handler on body opening.
     * @return void
     */
    public function execute_onCaMykSBodyOpen() {
        $this->display();
    }

    /* Admin_Site extension configuration methods */

    /**
     * Initialise object in Admin_Site / view configuration mode.
     * @return void
     */
    public function initialise_configDisplay() {
        /* load plugin configuration */
        $this->load_configuration();
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
        $this->load_configuration();

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
        $this->load_configuration();
        $this->config->get_fromHeader();
        return $this->config->save();
    }
}
?>
