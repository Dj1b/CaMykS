<?php
/**
 * @brief DemoPayment input.
 * @details Plugin / Input Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Mar 2024
 * @date Modification: Mar 2024
 * @copyright 2024 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * DemoPayment Input class.
 */
final class DemoPayment extends Input {
    /**
     * var integer $_lastErrorCode
     * @brief Last error identifier.
     */
    private $_lastErrorCode = 0;

    /**
     * var string $_lastErrorMsg
     * @brief Last error description.
     */
    private $_lastErrorMsg = '';

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('DemoPayment', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'eCommerce';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';
    }

    /* Mark: Override input methods */

    /**
     * Initialise input.
     * @param array $params
     * @return void
     */
    public function initialise($params=array()) {
        global $camyks;

        /* Merge $params */
        $defaultParams = array(
            /* modes : form / checkout */
            'mode'=>'',
        );
        $this->params = array_merge($defaultParams, $params);

        /* Check action to execute */
        switch ($this->params['mode']) {
            case 'form' :
                $this->initialise_form();
                break;
            case 'checkout' :
                break;
        }

        /* Input generic initialization */
        parent::initialise();
    }

    /* Mark: Initialise mode sub methods */

    /**
     * Initialise input in form mode.
     * @return void
     */
    private function initialise_form() {

        /* Build inner form */
        $this->siteForm = new HTMLForm('siteForm', $this->params['url'], 'POST');

        /* Load scripts */
        $this->add_JSFile('DemoPayment.js');
        $this->add_JSLoadScript('DemoPayment.initialise();');

        /* select layout */
        $this->set_selectedLayout('input.html.inc');
    }

    /* Mark: Payment related methods */

    /**
     * Prepare payment.
     * @return void
     */
    public function prepare_forPayment() {

    }

    /**
     * Initialise input in checkout mode.
     * @return void
     */
    public function execute_checkout() {
        return true;
    }

    /**
     * Load payment confirmation.
     * @return boolean success
     */
    public function load_paymentConfirmation() {
        return true;
    }

    /**
     * Get payment confirmation data from response.
     * @return array
     */
    public function get_paymentConfirmationData() {
        return array(
            'uniqueId'      => '',
            'transaction'   => '',
        );
    }

    /* Tool methods */

    /**
     * Return transaction id.
     * @return void
     */
    public function get_transactionId() {
        return 'demo-'.strftime('%d%m%Y');
    }

    /**
     * Return payment mode list.
     * @return void
     */
    public function get_paymentMethodList() {
        /* Initialise list */
        $list = array();

        /* Complete list */
        $list[] = array(
            'title'         => $this->get_translation('creditcard'),
            'mode'          => $this->name.':creditcard',
            'description'   => $this->get_translation('creditcard_desc'),
        );

        /* Return list */
        return $list;
    }

    /**
     * Return payment mode title.
     * @param array $method
     * @return void
     */
    public function get_paymentMethodTitle($method='') {
        return $this->get_translation('creditcard');
    }

    /**
     * Return payment mode description.
     * @param array $method
     * @return void
     */
    public function get_paymentMethodDescription($method='') {
        return $this->get_translation('creditcard_desc');
    }

    /**
     * Return payment mode email details.
     * @param array $method
     * @return void
     */
    public function get_paymentMethodEmailDetails($method='') {
        return '';
    }

    /* Mark: Error handling methods */

    /**
     * Define last error.
     * @param string $errorCode
     * @param string $errorMsg
     * @return void
     */
    private function set_lastError($errorCode, $errorMsg) {
        $this->_lastErrorCode = $errorCode;
        $this->_lastErrorMsg = $errorMsg;
    }

    /**
     * Return last error as code.
     * @return string
     */
    public function get_lastError() {
        return $this->_lastErrorCode;
    }

    /**
     * Return last error as text.
     * @return string
     */
    public function get_lastErrorMessage() {
        if ($this->_lastErrorMsg == '')
            return '';
        return $this->_lastErrorMsg;
    }
}
?>
