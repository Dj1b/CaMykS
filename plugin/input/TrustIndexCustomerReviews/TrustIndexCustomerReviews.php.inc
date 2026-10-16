<?php
/**
 * @brief TrustIndexCustomerReviews input.
 * <br /> Display TrustIndex customer reviews widget.
 * @details Plugin / Input Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Oct 2026
 * @date Modification: Oct 2026
 * @copyright 2026 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * TrustIndexCustomerReviews Input class.
 */
final class TrustIndexCustomerReviews extends Input {
    /**
     * @var Object $config
     * @brief Input configuration.
     */
    protected $config;

    /**
     * @var boolean $isConfigLoaded
     * @brief Stores if the configuration is loaded.
     */
    protected $isConfigLoaded = false;

    /**
     * @var boolean $isInitialised
     * @brief Stores if the input is initialised.
     */
    protected $isInitialised = false;

    /**
     * @var array $params
     * @brief Input parameters.
     */
    public $params = array(
        'widgetId'              => '',
        'integrationMode'       => 'loader',
        'rawCode'               => '',
        'alignment'             => 'none',
        'containerClass'        => 'trustindex-widget-container',
        'containerStyle'        => '',
        'enableCookieConsent'   => 1,
        'showConsentMessage'    => 0,
    );

    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('TrustIndexCustomerReviews', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0.0';
        $this->plugin_package = 'Default';

        /* Define author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Register plugin as Admin_Site extension */
        $this->register_asExtension('Admin_Site');

        /* Register plugin as CookieAgreementMessage extension */
        $this->register_asExtension('CookieAgreementMessage');
    }

    /* Mark: Override input methods */

    /**
     * Initialise input.
     * @param array $params
     * @return void
     */
    public function initialise($params=array()) {
        /* Load configuration */
        $this->load_configuration();

        /* Check and merge parameters */
        $this->check_params($params);

        /* Mark as initialised */
        $this->isInitialised = true;

        /* Input generic initialization */
        parent::initialise();
    }

    /**
     * Display input.
     * @param array $params
     * @return void
     */
    public function display($params=array()) {
        if (!$this->isInitialised or count($params) > 0)
            $this->initialise($params);

        /* Check cookie consent */
        if ($this->params['enableCookieConsent'] == 1 and !$this->is_cookieAccepted()) {
            if ($this->params['showConsentMessage'] == 1) {
                $this->set_selectedLayout('input_consent.html.inc');
                parent::display();
            }
            return;
        }

        /* Check if widget has content to render */
        if ($this->params['integrationMode'] === 'loader' and trim($this->params['widgetId']) === '')
            return;

        if ($this->params['integrationMode'] === 'raw' and trim($this->params['rawCode']) === '')
            return;

        $this->set_selectedLayout('input.html.inc');
        parent::display();
    }

    /* Mark: Specific public helper methods */

    /**
     * Return container inline CSS styles.
     * @return string
     */
    public function get_containerStyle() {
        $styles = array();

        /* Add alignment style */
        switch ($this->params['alignment']) {
            case 'center':
                $styles[] = 'text-align:center;';
                $styles[] = 'margin-left:auto;';
                $styles[] = 'margin-right:auto;';
                break;
            case 'left':
                $styles[] = 'text-align:left;';
                break;
            case 'right':
                $styles[] = 'text-align:right;';
                break;
            default:
                break;
        }

        /* Add custom user style */
        if (!empty($this->params['containerStyle'])) {
            $styles[] = rtrim(trim($this->params['containerStyle']), ';').';';
        }

        return implode(' ', $styles);
    }

    /**
     * Return loader script URL.
     * @return string
     */
    public function get_loaderUrl() {
        return 'https://cdn.trustindex.io/loader.js?'.urlencode($this->params['widgetId']);
    }

    /* Mark: Internal configuration & parameter methods */

    /**
     * Load configuration.
     * @return void
     */
    private function load_configuration() {
        if ($this->isConfigLoaded)
            return;

        $this->load_library('TrustIndexCustomerReviewsConfig');
        $this->config = new TrustIndexCustomerReviewsConfig('config', $this);
        $this->config->get();

        $this->isConfigLoaded = true;
    }

    /**
     * Return configuration value.
     * @param string $name
     * @return mixed
     */
    protected function get_configValue($name='') {
        $this->load_configuration();
        return $this->config->get_value($name);
    }

    /**
     * Merge and sanitize runtime parameters.
     * @param array $params
     * @return void
     */
    private function check_params($params=array()) {
        /* Merge defaults, stored configuration, and caller overrides */
        $this->params = array_merge($this->params, $this->config->vars, $params);

        /* Normalize integration mode */
        if (!in_array($this->params['integrationMode'], array('loader', 'raw')))
            $this->params['integrationMode'] = 'loader';

        /* Normalize alignment */
        if (!in_array($this->params['alignment'], array('none', 'left', 'center', 'right')))
            $this->params['alignment'] = 'none';

        /* Normalize boolean parameters */
        $this->params['enableCookieConsent'] = (int)$this->params['enableCookieConsent'] ? 1 : 0;
        $this->params['showConsentMessage'] = (int)$this->params['showConsentMessage'] ? 1 : 0;

        /* Clean strings */
        $this->params['widgetId'] = trim((string)$this->params['widgetId']);
        $this->params['containerClass'] = trim((string)$this->params['containerClass']);
        $this->params['containerStyle'] = trim((string)$this->params['containerStyle']);
    }

    /* Mark: Admin_Site extension configuration methods */

    /**
     * Initialise object in Admin_Site / view configuration mode.
     * @return void
     */
    public function initialise_configDisplay() {
        $this->load_configuration();
    }

    /**
     * Display object in Admin_Site / view configuration mode.
     * @return void
     */
    public function display_configDisplay() {
        $this->load_file('html/Configuration/View.html.inc');
    }

    /**
     * Initialise object in Admin_Site / edit configuration mode.
     * @param Object $form
     * @return void
     */
    public function initialise_configEdition($form) {
        $this->load_configuration();

        /* Update form */
        $this->form = &$form;
        $this->form->set_object($this->config);
    }

    /**
     * Display object in Admin_Site / edit configuration mode.
     * @return void
     */
    public function display_configEdition() {
        $this->load_file('html/Configuration/Edit.html.inc');
    }

    /**
     * Execute object in Admin_Site / save configuration mode.
     * @return boolean
     */
    public function save_configuration() {
        $this->load_configuration();
        $this->config->get_fromHeader();
        return $this->config->save();
    }

    /* Mark: CookieAgreementMessage extension methods */

    /**
     * Return plugin information related to cookies.
     * @return array
     */
    public function get_cookieInformationData() {
        $this->load_configuration();

        if ($this->config->get_value('enableCookieConsent') == 1) {
            return array(
                'TrustIndexCustomerReviews' => array(
                    'title'         => $this->get_translation('cookie_title'),
                    'purpose'       => $this->get_translation('cookie_purpose'),
                    'usage'         => '',
                    'duration'      => '',
                    'aboutURL'      => 'https://www.trustindex.io/privacy-policy/',
                    'isMandatory'   => false,
                ),
            );
        }

        return array();
    }

    /**
     * Check if plugin service is cookie accepted.
     * @return boolean
     */
    private function is_cookieAccepted() {
        global $camyks;

        $input = $camyks->get_input('CookieAgreementMessage');
        if ($input === false)
            return true;
        return $input->check_serviceIsAccepted('TrustIndexCustomerReviews');
    }
}
?>
