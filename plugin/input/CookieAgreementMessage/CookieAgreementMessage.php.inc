<?php
/**
 * @brief CookieAgreementMessage Input
 * <br /> Automatic cookie agremement message displayed in site mode.
 * @details Plugin / Input Engine
 * @file plugin/input/CookieAgreementMessage/CookieAgreementMessage.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: May 2017
 * @date Modification: Feb 2020
 * @copyright 2017 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * CookieAgreementMessage Input class.
 * @author CaMykS Team <camyks.contact@gmail.com>
 */
final class CookieAgreementMessage extends Input {
    /**
     * var Object $config
     * @brief Input configuration.
     */
    protected $config;

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

        /* set plugin version */
        $this->version = '1.0';

        /* set plugin package */
        $this->plugin_package = 'Default';

        /* set plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* load configuration library */
        $this->load_library('CookieAgreementMessageConfig');

        /* register plugin as Admin_Site extension */
        $this->register_asExtension('Admin_Site');

        /* load config */
        $this->config = new CookieAgreementMessageConfig('config', $this);
        $this->config->get();

        /* check for automatique adding */
        if ($camyks->mode == CAMYKS_MODE_SITE and $this->config->vars['insertion'] == 1) {
            $this->register_asCaMykSEventHandler('onPageLoad');
            $this->register_asCaMykSEventHandler('onBodyClose');
        }
    }

    /* overwrite input methods */

    /**
     * Initialise input.
     * @param array $params
     * @return void
     */
    function initialise($params=array()) {
        global $camyks;

        /* check params */
        $this->check_params($params);

        /* check if cookie message has to be displayed */
        if ($camyks->get_sessionValue('cookieAccepted', 0) == 1) {
            $this->params['status'] = 'disabled';
            return;
        } elseif ($this->params['remindTTL'] > 0 and cookie_get('cookieAccepted') == 1) {
            $this->params['status'] = 'disabled';
            return;
        }

        /* add styles */
        if ($this->params['styleSource'] == 'plugin') {
            $this->add_styleFile('css/styles.css');
        }

        /* add scripts */
        $this->add_JSFile('CookieAgreementMessage.js');
        $this->add_JSEngineFile('tool/cookie.js');
        $this->add_JSLoadScript('CookieAgreementMessage.set_param("cookieTTL", '.$this->params['remindTTL'].');');
        $this->add_JSLoadScript('CookieAgreementMessage.initialise();');

        /* remove cookie for other pages of the same session */
        $camyks->set_sessionValue('cookieAccepted', 1);

        /* Input generic initialization */
        parent::initialise();
    }

    /**
     * Display input.
     * @return void
     */
    public function display() {
        if ($this->params['status'] == 'enabled')
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

    /* specific tool methods */

    /**
     * Check parameters from current parameters and configuration.
     * @param array $params
     * @return void
     */
    private function check_params($params=array()) {
        global $camyks;

        /* build internal params list */
        $this->params = array_merge($this->params, $this->config->vars);

        /* check for single language message */
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

        /* check params */
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
