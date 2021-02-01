<?php
/**
 * @brief LimonetikPayment Input configuration object
 * @details Plugin / Input Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Oct 2020
 * @date Modification: Oct 2020
 * @copyright 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * LimonetikPaymentConfig PluginConfig class.
 */
final class LimonetikPaymentConfig extends PluginConfig {
    /**
     * Class constructor.
     * @param string $name
     * @param Module $parent
     * @return void
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* Operation */
        $this->add_newItem('runningMode', 'string', 'test');

        /* Limonetik configuration */
        $this->add_newItem('APIKey', 'string', '');
        $this->add_newItem('MerchantId', 'string', '');
        $this->add_newItem('EnableCreditCard', 'integer', 1);
        $this->add_newItem('EnableConecs', 'integer', 0);

        /* Generic initialisation */
        parent::init_config();
    }

    /* Data related methods */

    /**
     * Return running mode value list.
     * @return array
     */
    public function get_modeList() {
        return array(
            'test'  => $this->get_translation('mode_test'),
            'live'  => $this->get_translation('mode_live'),
        );
    }

    /**
     * Return mode value title.
     * @return string
     */
    public function get_modeTitle() {
        $l = $this->get_modeList();
        return $l[$this->vars['runningMode']];
    }

    /**
     * Return payment page id.
     * @return string
     */
    public function get_paymentPageId($payment=null) {
        if ($payment == 'CreditCard' or (is_null($payment) and $this->get_value('EnableCreditCard') == true))
            return 'creditcard';
        if ($payment == 'Conecs' or (is_null($payment) and $this->get_value('EnableConecs') == true))
            return 'conecs';
        return '';
    }
}
?>
