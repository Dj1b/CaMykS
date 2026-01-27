<?php
/**
 * @brief AdvancedSMTPSettings input.
 * @details Plugin / Input Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Jan 2026
 * @date Modification: Jan 2026
 * @copyright 2026 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * AdvancedSMTPSettings Input class.
 */
final class AdvancedSMTPSettings extends Input {
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
     * @var integer $lastError
     * @brief Last error.
     */
    private $lastError = 0;

    /**
     * @var string $configAction
     * @brief Action to execute in configuration.
     */
    private $configAction;

    /**
     * @var string $configActionMessage
     * @brief Message to display after configAction execution.
     */
    protected $configActionMessage;

    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('AdvancedSMTPSettings', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* Define author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Register plugin as extension */
        $this->register_asExtension('Admin_Site');

        /* Load configuration */
        $this->load_configuration();

        /* Check for configuration */
        if ($this->config->get_value('Plugin_Insertion') == 1)
            $this->config->apply_configuration();
    }

    /* Mark: Override input methods */

    /**
     * Initialise input.
     * @param array $params
     * @return void
     */
    public function initialise($params=array()) {
        global $camyks;

        /* Apply SMTP configuration */
        $this->config->apply_configuration();

        /* Input generic initialization */
        parent::initialise();
    }

    /* Mark: Configuration methods */

    /**
     * Load configuration.
     * @return void
     */
    private function load_configuration() {
        /* Check configuration is already loaded */
        if ($this->isConfigLoaded)
            return;

        /* Load configuration */
        $this->load_library('AdvancedSMTPSettingsConfig');
        $this->config = new AdvancedSMTPSettingsConfig('config', $this);
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

    /* Mark: Admin_Site extension configuration methods */

    /**
     * Initialise object in Admin_Site / view configuration mode.
     * @return void
     */
    public function initialise_configDisplay() {

        $this->configAction = isset($_REQUEST['configAction']) ? $_REQUEST['configAction'] : '';

        if ($this->configAction == 'RequestNewToken') {
            if (!$this->config->request_refreshToken()) {
                /* Display modify button */
                $camyks->adminUser->rights['Admin_Site'][3] = 0;

                /* Set up text to display */
                $this->configActionMessage = $this->config->_libError;
            }

        } elseif ($this->configAction == 'UpdateNewToken') {
            /* Display modify button */
            $camyks->adminUser->rights['Admin_Site'][3] = 0;

            /* Check and display result */
            if (!$this->config->update_refreshToken()) {
                $this->configActionMessage = $this->config->_libError;
            } else
                $this->configActionMessage = $this->get_translation('refreshtokenupdated');
        }
    }

    /**
     * Display object in Admin_Site / view configuration mode.
     * @return void
     */
    public function display_configDisplay() {
        if ($this->configAction == 'RequestNewToken') {
            $this->load_file('html/Configuration/Message.html.inc');
        } elseif ($this->configAction == 'UpdateNewToken') {
            $this->load_file('html/Configuration/Message.html.inc');
        } else {
            $this->load_file('html/Configuration/View.html.inc');
        }
    }

    /**
     * Initialise object in Admin_Site / edit configuration mode.
     * @param Object $form
     * @return void
     */
    public function initialise_configEdition($form) {
        /* Update form */
        $this->form = &$form;
        $this->form->set_object($this->config);

        /* Load scripts */
        $this->add_JSFile('AdvancedSMTPSettingsConfigurationEditor.js?v=1.0');
        $this->add_JSLoadScript('AdvancedSMTPSettingsConfigurationEditor.set_param("form", "'.$this->form->name.'");');
        $this->add_JSLoadScript('AdvancedSMTPSettingsConfigurationEditor.initialise();');
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
     * @return void
     */
    public function save_configuration() {
        $this->config->get_fromHeader();
        return $this->config->save();
    }
}
?>
