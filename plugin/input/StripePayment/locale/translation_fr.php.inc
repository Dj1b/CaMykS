<?php
/**
 * @brief StripePayment Input french dictionnary
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
$this->trads['input_stripepayment_formtitle_operation'] = 'Fonctionnement';
$this->trads['input_stripepayment_formitem_runningmode'] = 'Mode de fonctionnement : ';
$this->trads['input_stripepayment_formtitle_authentication_test'] = 'Mode test';
$this->trads['input_stripepayment_formtitle_authentication_production'] = 'Mode production';
$this->trads['input_stripepayment_formitem_apikey_public'] = 'Cl&eacute; API publique : ';
$this->trads['input_stripepayment_formitem_apikey_private'] = 'Cl&eacute; API priv&eacute;e : ';
$this->trads['input_stripepayment_formitem_displaytestcard'] = 'Afficher les informations de test : ';

/* site */
$this->trads['input_stripepayment_action_pay'] = 'Payer';
$this->trads['input_stripepayment_message_payment_completed'] = 'Paiement termin&eacute;';

/* site - test mode */
$this->trads['input_stripepayment_testmode_title'] = 'Stripe fonctionne actuellement en mode test';
$this->trads['input_stripepayment_testmode_desc'] = 'Aucun paiement r&eacute;el ne sera enregistr&eacute;.';
$this->trads['input_stripepayment_testmode_fakecardnumbers'] = '<strong>Carte de test :</strong> 4242 4242 4242 4242';
$this->trads['input_stripepayment_testmode_fakecarddate'] = '<strong>Expiration :</strong> n\'importe quelle date dans le futur';
$this->trads['input_stripepayment_testmode_fakecardccv'] = '<strong>Code :</strong> n\'importe quel code &agrave; 3 chiffres';
?>
