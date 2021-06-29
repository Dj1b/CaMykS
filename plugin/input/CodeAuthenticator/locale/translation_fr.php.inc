<?php
/**
 * @brief CodeAuthenticator Input, french dictionary.
 * @details Plugin / Input Dictionary
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Jun 2021
 * @date Modification: Jun 2021
 * @copyright 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
$this->trads['input_codeauthenticator_title'] = 'Authentification 2 facteurs par code';

/* Configuration */
$this->trads['input_codeauthenticator_formtitle_codeparams'] = 'Param&egrave;tres du code';
$this->trads['input_codeauthenticator_formtitle_secretparams'] = 'Param&egrave;tres du secret';
$this->trads['input_codeauthenticator_formitem_length'] = 'Longueur : ';
$this->trads['input_codeauthenticator_formunit_characters'] = ' caract&egrave;res';
$this->trads['input_codeauthenticator_formunit_bits'] = ' bits';

/* User configuration */
$this->trads['input_codeauthenticator_instructions1'] = 'Pour activer l\'authentification &agrave; deux facteurs par code, veuillez flasher le QR Code ci-dessus dans votre application Authenticator favorite.';
$this->trads['input_codeauthenticator_instructions2'] = 'Puis, ins&eacute;rer dans le champ ci-dessous, le code fourni par l\'application, afin de confirmer la bonne configuration de votre compte.';

/* User login */
$this->trads['input_codeauthenticator_loginmessage'] = 'Merci d\'indiquer le code de votre application Authenticator';

/* Errors */
$this->trads['input_codeauthenticator_error_none'] = 'Aucune erreur';
$this->trads['input_codeauthenticator_error_secretisnomoreavailable'] = 'Le secret n\'est plus disponible.';
$this->trads['input_codeauthenticator_error_codenotfound'] = 'Aucun code trouv&eacute;';
$this->trads['input_codeauthenticator_error_codenotvalid'] = 'Code non conforme';
$this->trads['input_codeauthenticator_error_codeincorrect'] = 'Code incorrect';
$this->trads['input_codeauthenticator_error_unknown'] = 'Erreur inconnue';
?>
