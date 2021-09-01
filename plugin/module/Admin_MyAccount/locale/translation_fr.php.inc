<?php
/**
 * @brief Admin_MyAccount Module french dictionary.
 * @details Plugin / Module Dictionary
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.3
 * @date Creation: Jun 2005
 * @date Modification: Jul 2021
 * @copyright 2005 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
$this->trads['mod_admin_myaccount_title'] = 'Mon compte';
$this->trads['mod_admin_myaccount_desc'] = 'Gestion de votre compte';

/* admin message */
$this->trads['mod_admin_myaccount_savedone'] = 'Votre compte est en cours de sauvegarde...';
$this->trads['mod_admin_myaccount_savefailed'] = 'La modification de votre compte a &eacute;chou&eacute;.';

/* actions */
$this->trads['mod_admin_myaccount_configure_2fa'] = 'Configurer l\'authentification &agrave; 2 facteurs';
$this->trads['mod_admin_myaccount_reset_2fa'] = 'R&eacute;initialiser l\'authentification &agrave; 2 facteurs';

/* view mode */
$this->trads['mod_admin_myaccount_formitem_2faauthentication'] = 'Authentification 2 facteurs : ';

/* edit mode */
$this->trads['mod_admin_myaccount_formitem_changepwd'] = 'Changer de mot de passe : ';

/* edit 2FA mode */
$this->trads['mod_admin_myaccount_2faauthentication'] = 'Authentification 2 facteurs';

/* save errors */
$this->trads['mod_admin_myaccount_erroremptymail'] = 'L\'e-mail ne doit pas &ecirc;tre vide.';
$this->trads['mod_admin_myaccount_errorbadmail'] = 'L\'e-mail doit &ecirc;tre valide.';
$this->trads['mod_admin_myaccount_erroremptypwd'] = 'Le mot de passe ne doit pas &ecirc;tre vide.';
$this->trads['mod_admin_myaccount_errorshortpwd'] = 'Le mot de passe doit avoir une longueur sup&eacute;rieure &agrave; 3 caract&egrave;res.';
$this->trads['mod_admin_myaccount_errorconfpwd'] = 'Le mot de passe ne se confirme pas.';

/* edit 2FA messages */
$this->trads['mod_admin_myaccount_error_no2faplugindefined'] = 'Aucun plugin d&eacute;fini pour l\'authentification &agrave; deux facteurs.';
$this->trads['mod_admin_myaccount_error_2fapluginnomoreavailable'] = 'Le plugin d&eacute;fini pour l\'authentification &agrave; deux facteurs n\'est plus disponible.';

/* save 2FA messages */
$this->trads['mod_admin_myaccount_2faconfigurationupdated'] = 'Configuration de l\'authentification &agrave; deux facteurs effectu&eacute;e.';
$this->trads['mod_admin_myaccount_2faconfigurationnotupdated'] = 'Une erreur est survenue lors de l\'enregistrement des donn&eacute;es de l\'authentification &agrave; deux facteurs.';
$this->trads['mod_admin_myaccount_2faconfigurationnotconfirmed'] = 'Une erreur est survenue lors de la configuration de l\'authentification &agrave; deux facteurs.';

/* reset 2FA messages */
$this->trads['mod_admin_myaccount_2faconfigurationreset'] = 'Configuration de l\'authentification &agrave; deux facteurs r&eacute;initialis&eacute;e.';
$this->trads['mod_admin_myaccount_2faconfigurationnotreset'] = 'Une erreur est survenue lors de la r&eacute;initialisation de l\'authentification &agrave; deux facteurs r&eacute;initialis&eacute;e.';

/* 2FA status */
$this->trads['mod_admin_myaccount_2fastatus_unavailable'] = 'Indisponible';
$this->trads['mod_admin_myaccount_2fastatus_configured'] = 'Configur&eacute;e';
$this->trads['mod_admin_myaccount_2fastatus_notconfigured'] = 'Non configur&eacute;e';
?>
