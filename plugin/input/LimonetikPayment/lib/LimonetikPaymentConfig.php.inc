<?php
/**
 * @brief LimonetikPayment input, configuration library.
 * @details Plugin / Input Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2.1
 * @date Creation: Oct 2020
 * @date Modification: Jul 2025
 * @copyright 2020 - 2025 CaMykS Team
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
     * @param Plugin $parent
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* Operation */
        $this->add_newItem('runningMode', 'string', 'test');

        /* Limonetik configuration */
        $this->add_newItem('APIKey', 'string', '');
        $this->add_newItem('APIKey-Test', 'string', '');
        $this->add_newItem('MerchantId', 'string', '');
        $this->add_newItem('EnableCreditCard', 'integer', 1);
        $this->add_newItem('EnableConecs', 'integer', 0);
        $this->add_newItem('EnablePassRestaurant', 'integer', 0);
        $this->add_newItem('EnableUpChequeDejeuner', 'integer', 0);
        $this->add_newItem('EnableApetiz', 'integer', 0);
        $this->add_newItem('EnableSwile', 'integer', 0);

        /* Generic initialisation */
        parent::init_config();
    }

    /* Mark: Data related methods */

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
     * @param string $payment
     * @return string
     */
    public function get_paymentPageId($payment=null) {
        /* Payments with auto select if no payment was provided */
        if ($payment == 'CreditCard' or (is_null($payment) and $this->get_value('EnableCreditCard') == true))
            return 'creditcard';
        if ($payment == 'Conecs' or (is_null($payment) and $this->get_value('EnableConecs') == true))
            return 'conecs';

        /* Payments without auto select */
        if ($payment == 'PassRestaurant')
            return 'passrestaurant';
        if ($payment == 'UpChequeDejeuner')
            return 'upchequedejeuner';
        if ($payment == 'Apetiz')
            return 'apetiz';
        if ($payment == 'Swile')
            return 'swile';
        return '';
    }
}
?>
