<?php
/**
 * @brief Admin_SecurityTools Module IPFilter library.
 * @details Plugin / Module Library
 * @file plugin/module/Admin_SecurityTools/lib/Admin_SecurityIPFilterRule.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: Oct 2007
 * @date Modification: Nov 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_SecurityIPFilterRule ModuleLibrary class.
 * @author CaMykS Team <camyks.contact@gmail.com>
 */
final class Admin_SecurityIPFilterRule extends ModuleLibrary {
    /*
     * Class Constructor
     * @param integer $id
     * @param Module $parent
     * @return void
     */
    public function __construct($id, &$parent) {
        parent::__construct($id, $parent);
        /* library items */
        $this->add_newItem('ipaddress', 'db', 'text', 'varchar', 16, '');
        $this->add_newItem('active', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('permission', 'db', 'int', 'tinyint unsigned', '', 1);
        $this->add_newItem('sitemode', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('comment', 'db', 'text', 'varchar', 255, '');

        /* generic library initialisation */
        parent::init_library();
    }

    /* Override ModuleLibrary methods */

    /**
     * Check library data.
     * @return boolean result
     */
    public function check_data() {
        /* check if ip is valid */
        if (string_isValidIPv4($this->_libItems['ipaddress']->value, true) === false) {
            $this->_libError = $this->get_translation('error_nonvalidipaddress');
            return false;
        }
        return true;
    }

    /* Specific properties definition method */

    /**
     * Return status list.
     * @return array
     */
    public function get_statusList() {
        return array(
            0 => $this->get_translation('ipfilterrulestatus_disabled'),
            1 => $this->get_translation('ipfilterrulestatus_enabled'),
        );
    }

    /**
     * Return multi object status list.
     * @param array $params
     * @return array
     */
    public function get_multiStatusList($params=array()) {

        /* check params */
        $defaultParams = array('addAll'=>false);
        $params = array_merge($defaultParams, $params);

        /* build list */
        $list = array();
        if ($params['addAll'])
            $list['-1'] = $this->get_translation('ipfilterrules_all');
        $list['0'] = $this->get_translation('ipfilterrulesstatus_disabled');
        $list['1'] = $this->get_translation('ipfilterrulesstatus_enabled');

        /* send list */
        return $list;
    }

    /**
     * Return permission list.
     * @return array
     */
    public function get_permissionList() {
        return array(
            0 => $this->get_translation('ipfilterrulepermission_allow'),
            1 => $this->get_translation('ipfilterrulepermission_deny'),
        );
    }

    /**
     * Return multi object permission list.
     * @param array $params
     * @return array
     */
    public function get_multiPermissionList($params=array()) {

        /* check params */
        $defaultParams = array('addAll'=>false);
        $params = array_merge($defaultParams, $params);

        /* build list */
        $list = array();
        if ($params['addAll'])
            $list['-1'] = $this->get_translation('ipfilterrules_all');
        $list['0'] = $this->get_translation('ipfilterrulespermission_allow');
        $list['1'] = $this->get_translation('ipfilterrulespermission_deny');

        /* send list */
        return $list;
    }

    /**
     * Return permission list.
     * @return array
     */
    public function get_permissionIconList() {
        $l = $this->get_permissionList();
        return array(
            0 => '<img src="'.$this->get_fileURL('img/enabled.gif').'" alt="'.$l[0].'" title="'.$l[0].'" />',
            1 => '<img src="'.$this->get_fileURL('img/disabled.gif').'" alt="'.$l[1].'" title="'.$l[1].'" />',
        );
    }

    /**
     * Return site mode list.
     * @return array
     */
    public function get_siteModeList() {
        return array(
            0 => $this->get_translation('ipfilterrulesitemode_both'),
            1 => $this->get_translation('ipfilterrulesitemode_visit'),
            2 => $this->get_translation('ipfilterrulesitemode_admin'),
        );
    }

    /* specific tool methods */

    /**
     * Check IP Filter security.
     * @return boolean result
     */
    public function check_security() {
        global $camyks;

        /* init result */
        $allow = true;

        /* get client IP */
        $ip = client_getIp();

        /* get all rules */
        $this->rules = $this->get_objectList(false, 'active=1', -1, -1);

        /* check if IP match a rule */
        foreach ($this->rules as $rule) {
            $pattern = $this->update_matching_ip($rule->vars['ipaddress']);
            if (preg_match($pattern, $ip)) {
                /* ip match to a rule ip address */
                if ($rule->vars['sitemode'] == 0 or ($rule->vars['sitemode'] == 1 and $camyks->mode == CAMYKS_MODE_SITE) or ($rule->vars['sitemode'] == 2 and $camyks->mode == CAMYKS_MODE_ADMIN)) {
                    if ($rule->vars['permission'] == 0) {
                        $allow = true;
                        break;
                    } else {
                        $allow = false;
                        $reason = $rule->vars['comment'];
                    }
                }
            }
        }

        /* kill navigator session if IP is not allowed */
        if (!$allow) {
            $camyks->log('Security', 'Connection refused', 'Black listed IP ('.$reason.')');
            $error = array(
                'title'         => 'Security: Access denied',
                'description'   => '',
                'content1'      => 'This website has an active IP Filter.',
                'content2'      => 'Your IP is currently into the blacklist.',
                'content3'      => 'If you think, it is an error, please contact the website administrator.',
            );
            header('HTTP/1.1 403 Forbidden');
            $camyks->throwFatalError($error);
        }
    }

    /**
     * Check IP address
     * @param string $ip
     * @param string $section
     * @return boolean array
     */
    public function check_IPAddress($ip, $section=1) {
        /* init result */
        $result = array('result' => 'allow');

        /* check IP */
        if (string_isValidIPv4($ip, false) === false) {
            $result['result'] = 'deny';
            $result['reason'] = $this->get_translation('error_nonvalidipaddress');
            return $result;
        }

        /* get all rules */
        $this->rules = $this->get_objectList(false, 'active=1', -1, -1);

        /* check if IP match a rule */
        foreach ($this->rules as $rule) {
            $pattern = $this->update_matching_ip($rule->vars['ipaddress']);
            if (preg_match($pattern, $ip)) {
                /* ip match to a rule ip address */
                if ($rule->vars['sitemode'] == 0 or $rule->vars['sitemode'] == $section) {
                    if ($rule->vars['permission'] == 0) {
                        $result['result'] = 'allow';
                        break;
                    } else {
                        $result['result'] = 'deny';
                        $result['reason'] = $rule->vars['comment'];
                    }
                }
            }
        }

        /* Return result */
        return $result;
    }

    /*
     * Transform ip to regexp matching expression.
     * @param string $ip the IP to transform
     * @return string updated IP
     */
    private function update_matching_ip($ip) {
        $replace = '/\*/';
        $by = '([0-9]{1,3})';
        return '/\A'.preg_replace($replace, $by, $ip).'\Z/';
    }
}
?>
