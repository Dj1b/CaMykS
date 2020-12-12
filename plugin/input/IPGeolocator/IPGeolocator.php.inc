<?php
/**
 * @brief IPGeolocator Input
 * <br /> Adds Crisp.chat snippet on page.
 * @details Plugin / Input Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Dec 2020
 * @date Modification: Dec 2020
 * @copyright 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * IPGeolocator Input class.
 */
final class IPGeolocator extends Input {
    /**
     * var Object $config
     * @brief Input configuration.
     */
    protected $config;

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('IPGeolocator', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* Define author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Register plugin as Admin_Site extension */
        $this->register_asExtension('Admin_Site');
    }

    /* Execute methods */

    /**
     * Execute input and return ip location.
     * @param array $params
     * @return mixed
     */
    public function execute($params=array()) {

        /* Load configuration */
        $this->load_configuration();

        /* Check params */
        $defaultParams = array('addressIp'=>null, 'service'=>null, 'output'=>'CountryAlpha2');
        $params = array_merge($this->config->vars, $defaultParams, $params);

        /* Check address ip */
        if ($params['addressIp'] == null)
            $params['addressIp'] = client_getIp();

        /* Check service */
        if ($params['service'] == null)
            $params['service'] = $this->get_configValue('service');

        /* Load library from source */
        $library = 'IPGeolocator_'.$params['service'];
        $this->load_library('Services/'.$library);
        if (!class_exists($library)) {
            return false;
        }
        $tool = new $library;

        /* Execute IP geolocation */
        $result = $tool->execute($params);

        /* Check result */
        if ($result == false)
            return false;

        /* Merge result with default answer */
        $result = array_merge(array(
            /* Address data */
            'Address' => '',
            'AddressZipcode' => '',
            'AddressCity' => '',

            /* Region / state */
            'RegionCode' => '',
            'RegionName' => '',

            /* Country data */
            'CountryAlpha2' => '',
            'CountryAlpha3' => '',
            'CountryName' => '',

            /* Continent data */
            'ContinentCode' => '',
            'ContinentName' => '',

            /* Geolocalisation */
            'Latitude' => '',
            'Longitude' => '',
        ), $result);

        /* Return result */
        if ($params['output'] == 'full')
            return $result;
        if (isset($result[$params['output']]))
            return $result[$params['output']];
        return false;
    }

    /* Configuration related methods */

    /**
     * Load configuration.
     * @return void
     */
    private function load_configuration() {
        $this->load_library('IPGeolocatorConfig');
        $this->config = new IPGeolocatorConfig('config', $this);
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
        /* Load plugin configuration */
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
