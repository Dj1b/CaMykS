<?php
/**
 * @brief Admin_SecurityTools Module IPFilter library.
 * @details Plugin / Module Library
 * @file plugin/module/Admin_SecurityTools/lib/Admin_SecurityIPFilterRule.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Oct 2007
 * @date Modification: Jun 2018
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
        $this->add_newItem('permission', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('sitemode', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('comment', 'db', 'text', 'varchar', 255, '');

        /* generic library initialisation */
        parent::init_library();
    }

    /* overwrite ModuleLibrary methods */

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
                if ($rule->vars['sitemode'] == 0
                        or ($rule->vars['sitemode'] == 1 and $camyks->mode == CAMYKS_MODE_SITE)
                        or ($rule->vars['sitemode'] == 2 and $camyks->mode == CAMYKS_MODE_ADMIN)) {
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
