<?php
/**
 * @brief Admin_MyAccount Module english dictionary.
 * @details Plugin / Module Dictionary
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: Jun 2005
 * @date Modification: Jul 2021
 * @copyright 2005 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
$this->trads['mod_admin_myaccount_title'] = 'My account';
$this->trads['mod_admin_myaccount_desc'] = 'Edit your account';

/* admin message */
$this->trads['mod_admin_myaccount_savedone'] = 'Saving your account...';
$this->trads['mod_admin_myaccount_savefailed'] = 'An error occurred while saving your account.';

/* actions */
$this->trads['mod_admin_myaccount_configure_2fa'] = 'Configure 2-factor authentication';
$this->trads['mod_admin_myaccount_reset_2fa'] = 'Reset 2-factor authentication';

/* view mode */
$this->trads['mod_admin_myaccount_formitem_2faauthentication'] = '2-factor authentication: ';

/* edit mode */
$this->trads['mod_admin_myaccount_formitem_changepwd'] = 'Change your password : ';

/* edit 2FA mode */
$this->trads['mod_admin_myaccount_2faauthentication'] = '2-factor authentication';

/* save errors */
$this->trads['mod_admin_myaccount_erroremptymail'] = 'The email cannot be empty.';
$this->trads['mod_admin_myaccount_errorbadmail'] = 'The email must be valid.';
$this->trads['mod_admin_myaccount_erroremptypwd'] = 'Password cannot be empty';
$this->trads['mod_admin_myaccount_errorshortpwd'] = 'Password must be longer than 3 caracters.';
$this->trads['mod_admin_myaccount_errorconfpwd'] = 'Password must be confirmed.';

/* edit 2FA messages */
$this->trads['mod_admin_myaccount_error_no2faplugindefined'] = 'No plugin defined for 2-factor authentication.';
$this->trads['mod_admin_myaccount_error_2fapluginnomoreavailable'] = 'Plugin defined for 2-factor authentication is no more available.';

/* save 2FA messages */
$this->trads['mod_admin_myaccount_2faconfigurationupdated'] = 'Configuration for 2-factor authentication done.';
$this->trads['mod_admin_myaccount_2faconfigurationnotupdated'] = 'An error has occured while saving configuration for 2-factor authentication.';
$this->trads['mod_admin_myaccount_2faconfigurationnotconfirmed'] = 'An error has occured while configuring 2-factor authentication.';

/* reset 2FA messages */
$this->trads['mod_admin_myaccount_2faconfigurationreset'] = 'Configuration for 2-factor authentication reset.';
$this->trads['mod_admin_myaccount_2faconfigurationnotreset'] = 'An error has occured while reseting configuration for 2-factor authentication';

/* 2FA status */
$this->trads['mod_admin_myaccount_2fastatus_unavailable'] = 'Unavailable';
$this->trads['mod_admin_myaccount_2fastatus_configured'] = 'Configured';
$this->trads['mod_admin_myaccount_2fastatus_notconfigured'] = 'Not configured';
?>
