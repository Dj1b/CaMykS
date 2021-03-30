<?php
/**
 * @brief StripePayment Input english dictionnary
 * @details Plugin / Input Dictionnary
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: May 2020
 * @date Modification: Mar 2021
 * @copyright 2020 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/* running mode values */
$this->trads['input_stripepayment_runningmode_test'] = 'Test';
$this->trads['input_stripepayment_runningmode_production'] = 'Production';

/* configuration */
$this->trads['input_stripepayment_formtitle_operation'] = 'Operation';
$this->trads['input_stripepayment_formitem_runningmode'] = 'Operation mode : ';
$this->trads['input_stripepayment_formtitle_authentication_test'] = 'Authentication - Test mode';
$this->trads['input_stripepayment_formtitle_authentication_production'] = 'Authentication - Production mode';
$this->trads['input_stripepayment_formitem_apikey_public'] = 'Public API key: ';
$this->trads['input_stripepayment_formitem_apikey_private'] = 'Private API key: ';
$this->trads['input_stripepayment_formitem_displaytestcard'] = 'Display test information: ';

/* site */
$this->trads['input_stripepayment_action_pay'] = 'Pay';
$this->trads['input_stripepayment_message_payment_completed'] = 'Payment completed';

/* site - test mode */
$this->trads['input_stripepayment_testmode_title'] = 'Stripe is operating in test mode';
$this->trads['input_stripepayment_testmode_desc'] = 'No real payment will be registered.';
$this->trads['input_stripepayment_testmode_fakecardnumbers'] = '<strong>Test card:</strong> 4242 4242 4242 4242';
$this->trads['input_stripepayment_testmode_fakecarddate'] = '<strong>Expiration:</strong> any date in futur';
$this->trads['input_stripepayment_testmode_fakecardccv'] = '<strong>Code:</strong> any 3-numbers code';
?>
