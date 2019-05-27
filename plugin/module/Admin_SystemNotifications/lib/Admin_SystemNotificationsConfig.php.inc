<?php
/**
 * @brief Admin_SystemNotifications Module configuration library
 * @details Plugin / Module Library
 * @file plugin/module/Admin_SystemNotifications/lib/Admin_SystemNotificationsConfig.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jul 2017
 * @date Modification: May 2019
 * @copyright 2017 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @note Access authentication values <br />
 * * 0 : None - Not recommended    <br />
 * * 1 : Login - Using an account (result may be restricted by user rights) <br />
 * * 2 : IP - Limited to given IP <br />
 */

/**
 * Admin_SystemNotificationsConfig class.
 */
final class Admin_SystemNotificationsConfig extends ModuleConfig {
    /**
     * Class constructor.
     * @param string $name
     * @param Module $parent
     * @return void
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* Runnings variables */
        $this->add_newItem('running_lastCheck', 'date', 0);
        $this->add_newItem('running_cache', 'array', array());

        /* Module variables */
        $this->add_newItem('module_mode', 'integer', 0); // 0: slave | 1: master
        $this->add_newItem('module_checkDelay', 'integer', 15);

        /* Access variables */
        $this->add_newItem('access_status', 'integer', 1);
        $this->add_newItem('access_authentication', 'integer', 2);
        $this->add_newItem('access_authLogin', 'string', '');
        $this->add_newItem('access_authIP', 'string', '');

        /* generic initialisation */
        parent::init_config();
    }

    /* Override Module Config methods */

    /**
     * Load object from header.
     * @return void
     */
    public function get_fromHeader() {
        /* backup running vars */
        $lastCheck = $this->vars['running_lastCheck'];
        $cache = $this->vars['running_cache'];

        /* load vars from header */
        parent::get_fromHeader();

        /* reinject running vars */
        $this->vars['running_lastCheck'] = $lastCheck;
        $this->vars['running_cache'] = $cache;
    }

    /* Specific methods */

    /**
     * Return module mode values.
     * @return array
     */
    public function get_moduleModeList() {
        return array(
            0 => $this->get_translation('modulemode_slave'),
            1 => $this->get_translation('modulemode_master'),
        );
    }

    /**
     * Return access status values.
     * @return array
     */
    public function get_accessStatusList() {
        return array(
            0 => $this->get_translation('accessstatus_disabled'),
            1 => $this->get_translation('accessstatus_enabled'),
        );
    }

    /**
     * Return access authentication values.
     * @return array
     */
    public function get_accessAuthenticationList() {
        return array(
            0 => $this->get_translation('accessauthentication_none'),
            1 => $this->get_translation('accessauthentication_credentials'),
            2 => $this->get_translation('accessauthentication_ipaddress'),
        );
    }
}
?>
