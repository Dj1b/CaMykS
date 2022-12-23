<?php
/**
 * @brief CookieAgreementMessage input.
 * <br /> Automatic cookie agremement message displayed in site mode.
 * @details Plugin / Input Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.1.0.6
 * @date Creation: May 2017
 * @date Modification: Dec 2022
 * @copyright 2017 - 2022 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * CookieAgreementMessage Input class.
 */
final class CookieAgreementMessage extends Input {
    /**
     * var Object $config
     * @brief Input configuration.
     */
    protected $config;

    /**
     * var array $serviceInformation
     * @brief Store services information from extenstions.
     */
    protected $serviceInformation = array();

    /**
     * var array $cookieData
     * @brief Store data from cookie
     */
    protected $cookieData;

    /**
     * var boolean $isDataLoaded
     * @brief Store data have been loaded.
     */
    private $isDataLoaded = false;

    /**
     * var array $params
     * @brief Input parameters.
     */
    public $params = array(
        'status'        => 'enabled',
        'message'       => '',
        'aboutCookie'   => false,
        'styleSource'   => 'plugin',
        'location'      => 'top',
        'remindTTL'     => 365,
    );

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        global $camyks;
        parent::__construct('CookieAgreementMessage', $path_type);

        /* Override plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Load configuration library */
        $this->load_library('CookieAgreementMessageConfig');

        /* Register plugin as Admin_Site extension */
        $this->register_asExtension('Admin_Site');

        /* Load configuration */
        $this->config = new CookieAgreementMessageConfig('config', $this);
        $this->config->get();

        /* Check for automatic insertion */
        if ($camyks->mode == CAMYKS_MODE_SITE and $this->config->vars['insertion'] == 1) {
            $this->register_asCaMykSEventHandler('onPageLoad');
            $this->register_asCaMykSEventHandler('onBodyClose');
        }
    }

    /* Override input methods */

    /**
     * Initialise input.
     * @param array $params
     * @return void
     */
    public function initialise($params=array()) {
        global $camyks;

        /* Load data */
        $this->load_data();

        /* Check params */
        $this->check_params($params);

        /* Check if cookie message has to be displayed */
        if ($this->params['remindTTL'] > 0 and !is_null($this->cookieData)) {
            $this->params['status'] = 'minimised';
        }

        /* Check all services have been accepted */
        foreach ($this->serviceInformation as $name => $service) {
            if (!isset($this->cookieData[$name])) {
                $this->params['status'] = "enabled";
                break;
            }
        }

        /* Add styles */
        if ($this->params['styleSource'] == 'plugin') {
            $this->add_styleFile('css/styles.css?v=1.1.0.3');
        }

        /* Add scripts */
        $this->add_JSFile('CookieAgreementMessage.js?v=1.1.0.1');
        $this->add_JSEngineFile('tool/cookie.js');
        $this->add_JSLoadScript('CookieAgreementMessage.set_param("cookieTTL", '.$this->params['remindTTL'].');');
        foreach ($this->serviceInformation as $name => $service) {
            if ($service['isMandatory'] == 1)
                $value = 2;
            else
                $value = $this->get_serviceStatus($name);
            $this->add_JSLoadScript('CookieAgreementMessage.services["'.$name.'"] = '.$value.';');
        }
        $this->add_JSLoadScript('CookieAgreementMessage.set_locale("unavailable_title", "'.string_HTML2Text($this->get_translation('message_unavailable_title')).'");');
        $this->add_JSLoadScript('CookieAgreementMessage.set_locale("unavailable_content", "'.string_HTML2Text($this->get_translation('message_unavailable_content')).'");');
        $this->add_JSLoadScript('CookieAgreementMessage.initialise();');

        /* Input generic initialization */
        parent::initialise();
    }

    /**
     * Display input.
     * @return void
     */
    public function display() {
        if ($this->params['status'] !== 'disabled')
            parent::display();
    }

    /**
     * Execute handler on page load.
     * @return string
     */
    public function execute_onCaMykSPageLoad() {
        $this->initialise();
    }

    /**
     * Execute handler on body closing.
     * @return string
     */
    public function execute_onCaMykSBodyClose() {
        $this->display();
        return '';
    }

    /* Specific public methods */

    /**
     * Check service is cookie accepted.
     * @param string $service
     * @return boolean
     */
    public function check_serviceIsAccepted($service) {
        $this->load_data();

        /* Check service exists */
        if (!isset($this->serviceInformation[$service]))
            return true;

        /* Check service status */
        if (!isset($this->cookieData[$service]) or $this->cookieData[$service] === 0)
            return false;
        return true;
    }

    /**
     * Return services list with details.
     * @return array
     */
    public function get_servicesList() {
        return $this->serviceInformation;
    }

    /**
     * Return cookie management panel, open link.
     * @return array
     */
    public function get_cookieManagementPanelOpenLink() {
        return 'javascript:CookieAgreementMessage.expand_panel();';
    }

    /* Specific tool methods */

    /**
     * Return cookie status for service.
     * @param string $service
     * @return integer
     */
    protected function get_serviceStatus($service) {
        return isset($this->cookieData[$service]) ? $this->cookieData[$service] : -1;
    }

    /**
     * Load cookie data and information.
     * @return void
     */
    private function load_data() {
        global $camyks;

        /* Check plugin data is already loaded */
        if ($this->isDataLoaded)
            return;

        /* Load cookie data */
        $this->cookieData = cookie_get('cookieAccepted');
        if (!is_null($this->cookieData)) {
            /* Read JSON */
            $data = json_decode($this->cookieData, true);
            if (json_last_error() !== JSON_ERROR_NONE or !is_array($data)) {
                /* $this->add_error(json_last_error(), json_last_error_msg(), __FILE__, __LINE__); */
                $this->cookieData = null;
            } else
                $this->cookieData = $data;
        }

        /* Initialise service array */
        $this->serviceInformation = array();

        /* Adds CMS internal cookie */
        $internal = array(
            'title'         => $this->get_translation('navigationcookie_title'),
            'purpose'       => $this->get_translation('navigationcookie_purpose'),
            'usage'         => $this->get_translation('navigationcookie_usage'),
            'duration'      => $this->get_translation('navigationcookie_duration', ((float)ini_get('session.gc_maxlifetime')) / 60),
            'aboutURL'      => '',
            'isMandatory'   => true,
        );
        if (($u = $camyks->get_siteKeypageLink('LegalMentions')) != '')
            $internal['aboutURL'] = $u.'#LM-Cookies';
        $this->serviceInformation['Navigation'] = $internal;

        /* Load extensions */
        $this->extensions = $this->get_registeredExtensions();

        /* Load data from extensions */
        foreach ($this->extensions as $extension)
            $this->serviceInformation = array_merge($this->serviceInformation, $extension->get_cookieInformationData());

        /* Save plugin data is loaded */
        $this->isDataLoaded = true;
    }

    /**
     * Check parameters from current parameters and configuration.
     * @param array $params
     * @return void
     */
    private function check_params($params=array()) {
        global $camyks;

        /* build internal params list */
        $this->params = array_merge($this->params, $this->config->vars);

        /* Check for single language message */
        if (is_array($this->params['message'])) {
            if (isset($this->params['message'][$camyks->current_language]))
                $this->params['message'] = $this->params['message'][$camyks->current_language];
            else {
                if (count($this->params['message']) > 0)
                    foreach ($this->params['message'] as $l => $m) {
                        $this->params['message'] = $m;
                        break;
                    }
                else
                    $this->params['message'] = '';
            }
        }

        /* merge params */
        $this->params = array_merge($this->params, $params);

        /* Check params */
        if ($this->params['message'] == '') $this->params['message'] = $this->get_translation('defaultmessage');

        if ($this->params['aboutCookie'] === true or $this->params['aboutCookie'] === 'true') {
            if (($u = $camyks->get_siteKeypageLink('LegalMentions')) != '')
                $this->params['aboutCookie'] = $u.'#LM-Cookies';
            else
                $this->params['aboutCookie'] = $this->get_translation('aboutcookieurl');
        }
    }

    /* Admin_Site extension configuration methods */

    /**
     * Initialise object in Admin_Site / view configuration mode.
     * @return void
     */
    public function initialise_configDisplay() {}

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
        /* update form */
        $this->form = &$form;
        $this->form->set_object($this->config);

        /* add scripts */
        $this->add_JSFile('CookieAgreementMessageConfig.js');
        $this->add_JSLoadScript('CookieAgreementMessageConfig.set_param("form", '.$this->form->name.');');
        $this->add_JSLoadScript('CookieAgreementMessageConfig.initialise();');
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
        $this->config->get_fromHeader();
        return $this->config->save();
    }
}
?>
