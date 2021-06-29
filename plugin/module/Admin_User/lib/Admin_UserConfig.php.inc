<?php
/**
 * @brief Admin_User Module configuration library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Jun 2021
 * @date Modification: Jun 2021
 * @copyright 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_UserConfig class.
 */
final class Admin_UserConfig extends PluginConfig {
    /**
     * Class constructor.
     * @param string $name
     * @param Module $parent
     * @return void
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* Authentication values */
        $this->add_newItem('authentication_2factorInput', 'string', '');
        $this->add_newItem('authentication_2factorStatus', 'int', 0);

        /* Generic initialisation */
        parent::init_config();
    }

    /* Admin management dedicated methods */

    /**
     * Return available 2 factor input list for authentication.
     * @return array
     */
    public function get_authentication2FactorInputList() {
        return array_merge(array('' => $this->get_translation('config_authentication_no2fa')),
            $this->_libParent->get_registeredExtensionTitleList());
    }

    /**
     * Return 2 factor input title.
     * @return array
     */
    public function get_authentication2FactorInputTitle() {
        $list = $this->get_authentication2FactorInputList();
        if (isset($list[$this->vars['authentication_2factorInput']]))
            return $list[$this->vars['authentication_2factorInput']];
        return $list[''];

    }

    /**
     * Return 2 factor authentication status list.
     * @return array
     */
    public function get_authentication2FactorStatusList() {
        return array(
            0 => $this->get_translation('config_authentication_optionnal'),
            1 => $this->get_translation('config_authentication_mandatory'),
        );
    }

    /**
     * Return 2 factor authentication status title.
     * @return array
     */
    public function get_authentication2FactorStatusTitle() {
        $list = $this->get_authentication2FactorStatusList();
        if (isset($list[$this->vars['authentication_2factorStatus']]))
            return $list[$this->vars['authentication_2factorStatus']];
        return $list[0];
    }
}
?>
