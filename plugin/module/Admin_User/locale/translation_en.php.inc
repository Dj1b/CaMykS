<?php
/**
 * @brief Admin_User Module english dictionnary.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.3
 * @date Creation: Nov 2012
 * @date Modification: Jul 2021
 * @copyright 2012 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
$this->trads['mod_admin_user_title'] = 'Users';
$this->trads['mod_admin_user_desc'] = 'Manage administrators';

/* users status list */
$this->trads['mod_admin_user_users_all'] = 'All';
$this->trads['mod_admin_user_users_disabled'] = 'Disabled';
$this->trads['mod_admin_user_users_enabled'] = 'Enabled';

/* 2FA status */
$this->trads['mod_admin_user_2fastatus_configured'] = 'Configured';
$this->trads['mod_admin_user_2fastatus_notconfigured'] = 'Non configured';

/* admin list */
$this->trads['mod_admin_user_formitem_search'] = 'Search: ';
$this->trads['mod_admin_user_adduser'] = 'Add a new administrator';
$this->trads['mod_admin_user_select'] = 'Select an user';
$this->trads['mod_admin_user_doesn_t_exist'] = 'This user account doesn\'t exist.';
$this->trads['mod_admin_user_pwd_conf'] = 'Confirmation';
$this->trads['mod_admin_user_pwd_change'] = 'Modify password: ';
$this->trads['mod_admin_user_is_active'] = 'Is enabled';

/* list translations */
$this->trads['mod_admin_user_viewuser'] = 'View this user';
$this->trads['mod_admin_user_edituser'] = 'Edit this user';
$this->trads['mod_admin_user_deleteuser'] = 'Delete this user';
$this->trads['mod_admin_user_personalinfos'] = 'Personal information';
$this->trads['mod_admin_user_rights'] = 'Permissions';
$this->trads['mod_admin_user_user'] = 'User';

/* View user */
$this->trads['mod_admin_user_formitem_2faauthentication'] = '2-factor authentication: ';
$this->trads['mod_admin_user_reset_2fawarning'] = 'Are you sure to want to reset the 2-factor authentication for this administrator ?';

/* message */
$this->trads['mod_admin_user_usermodificationnotallowed'] = 'You are not allowed to modify this user account.';

/* Reset 2FA */
$this->trads['mod_admin_user_2faconfigurationreset'] = '2-factor authentication reset.';
$this->trads['mod_admin_user_2faconfigurationnotreset'] = 'An error has occured while reseting the 2-factor authentication.';

/* errors */
$this->trads['mod_admin_user_erroremptylogin'] = 'Login can\'t be empty.';
$this->trads['mod_admin_user_errorbadlogin'] = 'Login contains invalid characters.';
$this->trads['mod_admin_user_errorshortlogin'] = 'Login must have at least 3 characters.';
$this->trads['mod_admin_user_errorexistinglogin'] = 'Login already exists.';
$this->trads['mod_admin_user_erroremptymail'] = 'Email address can\'t be empty.';
$this->trads['mod_admin_user_errorbadmail'] = 'Email address must be valid.';
$this->trads['mod_admin_user_erroremptypwd'] = 'Password can\'t be empty.';
$this->trads['mod_admin_user_errorshortpwd'] = 'Password must have at least 3 characters.';
$this->trads['mod_admin_user_errorconfpwd'] = 'Password confirmation is not correct.';

/* Configuration */
$this->trads['mod_admin_user_formtitle_authentication'] = 'Autentication';
$this->trads['mod_admin_user_formitem_2factorinput'] = '2FA Plugin: ';
$this->trads['mod_admin_user_formitem_2factorstatus'] = '2FA usage: ';

/* Configuration values */
$this->trads['mod_admin_user_config_authentication_no2fa'] = 'None';
$this->trads['mod_admin_user_config_authentication_optionnal'] = 'Optional';
$this->trads['mod_admin_user_config_authentication_mandatory'] = 'Mandatory';
?>
