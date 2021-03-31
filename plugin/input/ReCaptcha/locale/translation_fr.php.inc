<?php
/**
 * @brief ReCaptcha Input french dictionary
 * @details Plugin / Input Dictionary
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: Mar 2016
 * @date Modification: Mar 2021
 * @copyright 2016 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/* Errors */
$this->trads['input_recaptcha_error_captcha_missing'] = 'Captcha manquant, impossible de valider le formulaire.';
$this->trads['input_recaptcha_error_missing_input_secret'] = 'Configuration du Captcha erron&eacute;e, impossible de valider le formulaire.';
$this->trads['input_recaptcha_error_invalid_input_secret'] = 'Configuration du Captcha erron&eacute;e, impossible de valider le formulaire.';
$this->trads['input_recaptcha_error_missing_input_response'] = 'Merci de cliquer le Captcha pour v&eacute;rifier que vous &ecirc;tes bien un humain.';
$this->trads['input_recaptcha_error_invalid_input_response'] = 'Configuration du Captcha erron&eacute;e, impossible de valider le formulaire.';
$this->trads['input_recaptcha_error_timeout_or_duplicate'] = 'D&eacute;lai d&eacute;pass&eacute; ou captcha dupliqu&eacute;.';

/* Configuration */
$this->trads['input_recaptcha_formitem_publickey'] = 'Cl&eacute; publique : ';
$this->trads['input_recaptcha_formitem_privatekey'] = 'Cl&eacute; priv&eacute;e : ';

/* Cookie */
$this->trads['input_recaptcha_cookie_title'] = 'ReCaptcha';
$this->trads['input_recaptcha_cookie_purpose'] = 'Permet de valider que les visiteurs sont bien des humains lorsqu\'ils valident des formulaires.';

/* Unavailable service message */
$this->trads['input_recaptcha_message_unavailable_title'] = 'Captcha indisponible';
$this->trads['input_recaptcha_message_unavailable_content'] = 'Pour valider le formulaire, vous devez confirmer que vous &ecirc;tes bien une personne. Actuellement, la fonctionnalit&eacute; est indisponible. Vous devez activer le service <strong>ReCaptcha</strong> dans <a href="%s" class="eLink1">le gestionnaire des cookies</a>, et donc consentir &agrave; l\'utilisation de ses cookies.';
?>
