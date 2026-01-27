<?php
/**
 * @brief AdvancedSMTPSettings input, configuration library.
 * @details Plugin / Input Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Jan 2026
 * @date Modification: Jan 2026
 * @copyright 2026 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

use PHPMailer\PHPMailer\Exception;
use PHPMailer\PHPMailer\OAuth;
use PHPMailer\PHPMailer\PHPMailer;
use PHPMailer\PHPMailer\SMTP;
use Greew\OAuth2\Client\Provider\Azure;

/**
 * AdvancedSMTPSettingsConfig PluginConfig class.
 */
final class AdvancedSMTPSettingsConfig extends PluginConfig {
    /**
     * Class constructor.
     * @param string $name
     * @param Plugin $parent
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* Plugin configuration attributes */
        $this->add_newItem('Plugin_Insertion', 'integer', 0);
        $this->add_newItem('Plugin_EmailLibrary', 'string', 'auto');

        /* SMTP configuration attributes */
        $this->add_newItem('SMTP_Host', 'string', '');
        $this->add_newItem('SMTP_Port', 'integer', 25);
        $this->add_newItem('SMTP_Secure', 'string', '');
        $this->add_newItem('SMTP_Auth', 'string', '');

        /* SMTP Basic authentication attributes */
        $this->add_newItem('AuthBasic_UserName', 'string', '');
        $this->add_newItem('AuthBasic_Password', 'string', '');

        /* SMTP Auth Provider configuration attributes */
        $this->add_newItem('AuthProvider', 'string', '');
        $this->add_newItem('AuthProvider_Email', 'string', '');
        $this->add_newItem('AuthProvider_ClientId', 'string', '');
        $this->add_newItem('AuthProvider_TenantId', 'string', '');
        $this->add_newItem('AuthProvider_ClientSecret', 'string', '');
        $this->add_newItem('AuthProvider_RefreshToken', 'string', '');
        $this->add_newItem('AuthProvider_RefreshTokenExpiracyDate', 'date', 0);

        /* generic initialisation */
        parent::init_config();
    }

    /* Mark: Attribute data methods */

    /**
     * Return Plugin insertion value list.
     * @return array
     */
    public function get_PluginInsertionList() {
        return array(
            0   => $this->get_translation('plugininsertion_ondemand'),
            1   => $this->get_translation('plugininsertion_onpageload'),
        );
    }

    /**
     * Return Plugin insertion value.
     * @return string
     */
    public function get_PluginInsertionTitle() {
        $l = $this->get_PluginInsertionList();
        if (isset($l[$this->vars['Plugin_Insertion']]))
            return $l[$this->vars['Plugin_Insertion']];
        return $l[0];
    }

    /**
     * Return Plugin email library value list.
     * @return array
     */
    public function get_PluginEmailLibraryList() {
        return array(
            'auto'      => $this->get_translation('pluginemaillibrary_auto'),
            'PEAR/Mail' => 'PEAR/Mail',
            'PHPMailer' => 'PHPMailer',
        );
    }

    /**
     * Return Plugin email library value.
     * @return string
     */
    public function get_PluginEmailLibraryTitle() {
        $l = $this->get_PluginEmailLibraryList();
        if (isset($l[$this->vars['Plugin_EmailLibrary']]))
            return $l[$this->vars['Plugin_EmailLibrary']];
        return $l[0];
    }

    /**
     * Return SMTP Secure value list.
     * @return array
     */
    public function get_SMTPSecureList() {
        return array(
            ''      => $this->get_translation('smtpsecure_none'),
            'SSL'   => 'SSL',
            'tls'   => 'TLS',
        );
    }

    /**
     * Return SMTP Secure value.
     * @return string
     */
    public function get_SMTPSecureTitle() {
        $l = $this->get_SMTPSecureList();
        if (isset($l[$this->vars['SMTP_Secure']]))
            return $l[$this->vars['SMTP_Secure']];
        return $l[0];
    }

    /**
     * Return SMTP Auth value list.
     * @return array
     */
    public function get_SMTPAuthList() {
        return array(
            ''          => $this->get_translation('smtpauth_none'),
            'Basic'     => $this->get_translation('smtpauth_basic'),
            'XOAUTH2'   => $this->get_translation('smtpauth_xoauth2'),
        );
    }

    /**
     * Return SMTP Auth value.
     * @return string
     */
    public function get_SMTPAuthTitle() {
        $l = $this->get_SMTPAuthList();
        if (isset($l[$this->vars['SMTP_Auth']]))
            return $l[$this->vars['SMTP_Auth']];
        return $l[0];
    }

    /**
     * Return SMTP Auth Provider value list.
     * @return array
     */
    public function get_SMTPAuthProviderList() {
        return array(
            'Azure'   => 'Azure',
        );
    }

    /**
     * Return SMTP Auth Provider value.
     * @return string
     */
    public function get_SMTPAuthProviderTitle() {
        $l = $this->get_SMTPAuthProviderList();
        if (isset($l[$this->vars['AuthProvider']]))
            return $l[$this->vars['AuthProvider']];
        return $l[0];
    }

    /* Mark: Action methods */

    /**
     * Apply configuration to CMS.
     * @return void
     */
    public function apply_configuration() {
        global $camyks;

        /* Set up send with SMTP */
        $camyks->set_confValue('PEARMailDriver', 'smtp');

        /* Set up SMTP library */
        if ($this->vars['SMTP_Auth'] == '' and $this->vars['Plugin_EmailLibrary'] == 'PEAR/Mail')
            $camyks->set_confValue('email_defaultLibrary', 'PEAR/Mail');
        else
            $camyks->set_confValue('email_defaultLibrary', 'PHPMailer');

        /* Buid advanced configuration */
        if ($this->vars['SMTP_Auth'] == 'XOAUTH2' and $this->vars['AuthProvider'] == 'Azure') {
            $conf = array(
                'host' => 'smtp.office365.com',
                'port' => 587,
                'secure' => 'tls',
                'auth' => true,
                'authType' => 'XOAUTH2',
                'authProvider' => 'Azure',
                'authProviderClientId' => $this->vars['AuthProvider_ClientId'],
                'authProviderTenantId' => $this->vars['AuthProvider_TenantId'],
                'authProviderClientSecret' => $this->vars['AuthProvider_ClientSecret'],
                'authProviderRefreshToken' => $this->vars['AuthProvider_RefreshToken'],
                'authProviderEmail' => $this->vars['AuthProvider_Email'],
            );
        } else {
            $conf = array(
                'host' => $this->vars['SMTP_Host'],
                'port' => $this->vars['SMTP_Port'],
                'secure' => $this->vars['SMTP_Secure'],
            );
            if ($this->vars['SMTP_Auth'] == '')
                $conf['auth'] = false;
            else if ($this->vars['SMTP_Auth'] == 'Basic') {
                $conf['auth'] = true;
                $conf['username'] = $this->vars['AuthBasic_UserName'];
                $conf['password'] = $this->vars['AuthBasic_Password'];
            }
        }
        /* Set up advanced configuration */
        $camyks->set_confValue('PEARMailConfig', $conf);
    }

    /**
     * Return new token request URL.
     * @return string
     */
    public function get_newTokenRequestURL() {
        global $camyks;

        /* Load site configuration module */
        $siteConfiguration = $camyks->get_module('Admin_Site');

        /* Return */
        return $siteConfiguration->get_adminLink(array('mode'=>'viewPluginConfig', 'plugin'=>$this->_libParent->name, 'configAction'=>'RequestNewToken'));
    }

    /**
     * Request new refresh token.
     * @return boolean sucess
     */
    public function request_refreshToken() {
        global $camyks;

        /* Load authentication provider */
        $provider = $this->load_authenticationProvider();
        if ($provider === false)
            return false;

        /* Load authentication provider options */
        $options = $this->load_authenticationProviderOptions();

        /* Build authorisation url */
        $url = $provider->getAuthorizationUrl($options);

        /* Save state from provider */
        $camyks->set_sessionValue('oauth2state', $provider->getState());

        /* Redirect to authorisation url */
        header('Location: ' . $url);
        die();
    }

    /**
     * Update refresh token.
     * @return boolean success
     */
    public function update_refreshToken() {
        global $camyks;

        /* Check given state against previously stored one to mitigate CSRF attack */
        if (empty($_GET['state']) || ($_GET['state'] !== $camyks->get_sessionValue('oauth2state'))) {
            $camyks->set_sessionValue('oauth2state', null);
            $this->_libError = $this->get_translation('error_invalidstate');
            return false;
        }

        /* Load authentication provider */
        $provider = $this->load_authenticationProvider();
        if ($provider === false)
            return false;

        /* Load token */
        $token = $provider->getAccessToken('authorization_code', array(
            'code' => $_GET['code'],
        ));
        $this->vars['AuthProvider_RefreshToken'] = $token->getRefreshToken();

        /* Update expiracy date if needed */
        if ($this->get_value('AuthProvider') == 'Azure')
            $this->vars['AuthProvider_RefreshTokenExpiracyDate'] = mktime(0, 0, 0, date("m"), date("d")+90, date("Y"));

        /* Save config */
        if (!$this->save()) {
            $this->_libError = $this->get_translation('error_configsavefailed');
            return false;
        }
        return true;
    }

    /* Mark: Private methods */

    /**
     * Load authentication provider.
     * @return mixed
     */
    private function load_authenticationProvider() {
        global $camyks;

        /* Load external libraries */
        include_once 'PHPMailer/autoloader.php';
        include_once 'Guzzle/autoloader.php';
        include_once 'League/OAuth2/autoloader.php';
        include_once 'Greew/OAuth2/autoloader.php';

        /* Load site configuration module */
        $siteConfiguration = $camyks->get_module('Admin_Site');

        /* Set up redirectUrl */
        $redirectUri = $camyks->get_rootBaseURL('absolute').$siteConfiguration->get_adminJSLink(array('mode'=>'viewPluginConfig', 'plugin'=>$this->_libParent->name, 'configAction'=>'UpdateNewToken'));

        /* Build provider params */
        $params = array(
            'clientId' => $this->get_value('AuthProvider_ClientId'),
            'clientSecret' => $this->get_value('AuthProvider_ClientSecret'),
            'redirectUri' => $redirectUri,
            'accessType' => 'offline'
        );

        /* Load provider */
        $provider = null;

        switch ($this->get_value('AuthProvider')) {
            case 'Azure':
                /* Add Azure requires tenant id value */
                $params['tenantId'] = $this->get_value('AuthProvider_TenantId');

                /* Load Azure provider */
                $provider = new Azure($params);
                break;
            default:
                $this->_libError = $this->get_translation('error_providermissing');
                return false;
        }

        /* Return provider */
        return $provider;
    }

    /**
     * Load authentication provider options.
     * @return mixed
     */
    private function load_authenticationProviderOptions() {
        switch ($this->get_value('AuthProvider')) {
            case 'Azure':
                return array(
                    'scope' => array(
                        'https://outlook.office.com/SMTP.Send',
                        'offline_access',
                    ),
                );
                break;
        }

        /* Return empty options */
        return array();
    }
}
?>
