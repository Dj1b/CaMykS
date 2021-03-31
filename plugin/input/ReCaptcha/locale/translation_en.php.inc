<?php
/**
 * @brief ReCaptcha Input english dictionary
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
$this->trads['input_recaptcha_error_captcha_missing'] = 'Missing captcha, we can\'t validate the form.';
$this->trads['input_recaptcha_error_missing_input_secret'] = 'Captcha configuration error, we can\'t validate the form.';
$this->trads['input_recaptcha_error_invalid_input_secret'] = 'Captcha configuration error, we can\'t validate the form.';
$this->trads['input_recaptcha_error_missing_input_response'] = 'Please confirm you are a real human, by clicking the captcha box.';
$this->trads['input_recaptcha_error_invalid_input_response'] = 'Captcha configuration error, we can\'t validate the form.';
$this->trads['input_recaptcha_error_timeout_or_duplicate'] = 'Timeout or duplicate.';

/* Configuration */
$this->trads['input_recaptcha_formitem_publickey'] = 'Public key: ';
$this->trads['input_recaptcha_formitem_privatekey'] = 'Private key: ';

/* Cookie */
$this->trads['input_recaptcha_cookie_title'] = 'ReCaptcha';
$this->trads['input_recaptcha_cookie_purpose'] = 'Allows to verify that visitors are humain while submitting forms.';

/* Unavailable service message */
$this->trads['input_recaptcha_message_unavailable_title'] = 'Captcha unavailable';
$this->trads['input_recaptcha_message_unavailable_content'] = 'To valid this form, you have to confirm that you are a real person. Currently this feature is unavailable. You should enable the <strong>ReCaptcha</strong> service in the <a href="%s" class="eLink1">cookie manager</a>, and then consent to the use of their cookies.';
?>
