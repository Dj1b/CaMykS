<?php
/**
 * @brief CodeAuthenticator Input, english dictionary.
 * @details Plugin / Input Dictionary
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Jul 2021
 * @date Modification: Jul 2021
 * @copyright 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
$this->trads['input_codeauthenticator_title'] = '2-Factor authentication with code';

/* Configuration */
$this->trads['input_codeauthenticator_formtitle_codeparams'] = 'Code parameters';
$this->trads['input_codeauthenticator_formtitle_secretparams'] = 'Secret parameters';
$this->trads['input_codeauthenticator_formitem_length'] = 'Length: ';
$this->trads['input_codeauthenticator_formunit_characters'] = ' characters';
$this->trads['input_codeauthenticator_formunit_bits'] = ' bits';

/* User configuration */
$this->trads['input_codeauthenticator_instructions1'] = 'To enable 2-factor authentication with code, please flash the following QR Code with you favorite Authenticator app.';
$this->trads['input_codeauthenticator_instructions2'] = 'Then use the code given by the app to fill the field below.';

/* User login */
$this->trads['input_codeauthenticator_loginmessage'] = 'Please insert the code given by you Authenticator app.';

/* Errors */
$this->trads['input_codeauthenticator_error_none'] = 'No error';
$this->trads['input_codeauthenticator_error_secretisnomoreavailable'] = 'Secret is no more available.';
$this->trads['input_codeauthenticator_error_codenotfound'] = 'No code found';
$this->trads['input_codeauthenticator_error_codenotvalid'] = 'Code is not valid';
$this->trads['input_codeauthenticator_error_codeincorrect'] = 'Code is not correct';
$this->trads['input_codeauthenticator_error_unknown'] = 'Unknown error';
?>
