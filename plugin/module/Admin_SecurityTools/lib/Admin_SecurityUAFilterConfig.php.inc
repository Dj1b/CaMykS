<?php
/**
 * @brief Admin_SecurityTools Module User Agent configuration object
 * @details Plugin / Module Library
 * @file plugin/module/Admin_SecurityTools/lib/Admin_SecurityUAFilterConfig.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jan 2019
 * @date Modification: Jan 2019
 * @copyright 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_SecurityUAFilterConfig PluginConfig class.
 */
final class Admin_SecurityUAFilterConfig extends PluginConfig {
    /**
     * Class constructor.
     * @param string $name
     * @param Module $parent
     * @return void
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* object items */
        $this->add_newItem('block_hacks', 'boolean', true);
        $this->add_newItem('block_fakes', 'boolean', false);

        /* generic initialisation */
        parent::init_config();
    }

    /* Specific methods */

    /**
     * Check UA Filter security.
     * @return void
     */
    public function check_security() {
        global $camyks;

        /* Load client UA */
        $ua = client_getUAInfos();

        /* Set up refused UA */
        $refused = array();
        if ($this->vars['block_hacks'] == true)
            $refused[] = 'hack';
        if ($this->vars['block_fakes'] == true)
            $refused[] = 'fake';

        /* Check client type */
        if (in_array($ua['platform_type'], $refused)) {
            $camyks->log('Security', 'Connection refused', 'Bad user agent ('.$ua['platform_type'].')');
            $error = array(
                'title'         => 'Security: Access denied',
                'description'   => '',
                'content1'      => 'Your connection doesn\'t seem to be legit.',
                'content2'      => 'Your access has blocked.',
                'content3'      => 'If you think it is an error, please contact the website administrator.',
            );
            header('HTTP/1.1 403 Forbidden');
            $camyks->throwFatalError($error);
            return;
        }
    }
}
?>
