<?php
/**
 * @brief GoogleAnalytics Input
 * <br /> Adds Google Analytics snippet on page
 * @details Plugin / Input Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2.1
 * @date Creation: Sep 2018
 * @date Modification: Jul 2025
 * @copyright 2018 - 2025 CaMykS Team
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
     * var boolean isConfigLoaded
     * @brief Stores if the configuration is loaded
     */
    protected $isConfigLoaded = false;

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
     */
    public function __construct($path_type) {
        parent::__construct('GoogleAnalytics', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'Google';

        /* Define author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Register plugin as Admin_Site extension */
        $this->register_asExtension('Admin_Site');
        $this->register_asExtension('CookieAgreementMessage');

        /* Automatically insert it in the page */
        $this->register_asCaMykSEventHandler('onPageLoad');
        $this->register_asCaMykSEventHandler('onBodyOpen');
    }

    /* Mark: Override input methods */

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

        /* Check for Google Tag Manager insertion */
        if ($this->get_configValue('enableAdminStats') == 0 and $camyks->check_adminUser())
            return;
        if ($this->get_configValue('trackingMode') == 1) {
            $this->add_JSScript("/* Google Tag Manager */");
            $this->add_JSScript("(function(w,d,s,l,i){w[l]=w[l]||[];w[l].push({'gtm.start':\nnew Date().getTime(),event:'gtm.js'});var f=d.getElementsByTagName(s)[0],\nj=d.createElement(s),dl=l!='dataLayer'?'&l='+l:'';j.async=true;j.src=\n'https://www.googletagmanager.com/gtm.js?id='+i+dl;f.parentNode.insertBefore(j,f);\n})(window,document,'script','dataLayer','".$this->get_configValue('trackingId')."');");
            $this->add_JSScript("/* End Google Tag Manager */");
        }
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

        /* Check method */
        if ($this->get_configValue('trackingMode') == 1) {
            $this->set_selectedLayout('input_gtm.html.inc');
        }

        /* display snippet */
        parent::display();

        /* mark snippet as live */
        $this->isLive = true;
    }

    /* Mark: External action methods */

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

    /* Mark: Specific tool methods */

    /**
     * Load configuration.
     * @return void
     */
    private function load_configuration() {
        /* Check configuration is already loaded */
        if ($this->isConfigLoaded)
            return;

        /* Load configuration */
        $this->load_library('GoogleAnalyticsConfig');
        $this->config = new GoogleAnalyticsConfig('config', $this);
        $this->config->get();

        /* Save configuration is loaded */
        $this->isConfigLoaded = true;
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

    /* Mark: CaMykS page event methods */

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

    /* Mark: Admin_Site extension configuration methods */

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

    /* mark: CookieAgreementMessage extension methods */

    /**
     * Return plugin information related to cookies.
     * @return void
     */
    public function get_cookieInformationData() {
        /* Load configuration */
        $this->load_configuration();

        /* Return plugin information */
        if ($this->config->get_value('trackingId') !== '' and $this->get_configValue('trackingMode') == 0)
            return array(
                'GoogleAnalytics' => array(
                    'title' => $this->get_translation('cookie_title'),
                    'purpose' => $this->get_translation('cookie_purpose'),
                    'usage' => '',
                    'duration' => '',
                    'aboutURL' => 'https://policies.google.com/privacy',
                    'isMandatory' => false,
                ),
            );

        /* Return default value */
        return array();
    }

    /**
     * Check if plugin is cookie accepted.
     * @return boolean
     */
    private function is_cookieAccepted() {
        global $camyks;

        /* Check Google Tag Manager auto acceptation */
        if ($this->get_configValue('trackingMode') == 1)
            return true;

        /* Check acceptation from CookieAgreementMessage */
        $input = $camyks->get_input('CookieAgreementMessage');
        if ($input === false)
            return true;
        return $input->check_serviceIsAccepted('GoogleAnalytics');
    }
}
?>
