<?php
/**
 * @brief Admin_SecurityTools Module french dictionary
 * @details Plugin / Module Dictionary
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Jul 2021
 * @date Modification: Jul 2021
 * @copyright 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
$this->trads['mod_admin_securitytools_title'] = 'Security tools';
$this->trads['mod_admin_securitytools_desc'] = 'Filters, backup, ... ';

/* Objects */
$this->trads['mod_admin_securitytools_ipfilterrule'] = 'IP filter rule';
$this->trads['mod_admin_securitytools_ipfilterrules'] = 'IP filter rules';
$this->trads['mod_admin_securitytools_ipfilterrules_all'] = 'All';

$this->trads['mod_admin_securitytools_urlfilterrule'] = 'URL filter rule';
$this->trads['mod_admin_securitytools_urlfilterrules'] = 'URL filter rules';
$this->trads['mod_admin_securitytools_urlfilterrules_all'] = 'All';

$this->trads['mod_admin_securitytools_backup'] = 'Backup';
$this->trads['mod_admin_securitytools_backups'] = 'Backups';
$this->trads['mod_admin_securitytools_backups_all'] = 'All';

/* rights */
$this->trads['mod_admin_securitytools_right_config'] = 'Configuration';
$this->trads['mod_admin_securitytools_right_ipfilter'] = 'IP filter rules';
$this->trads['mod_admin_securitytools_right_urlfilter'] = 'URL filter rules';
$this->trads['mod_admin_securitytools_right_backup'] = 'Backups';

/* IP Filter rule status values */
$this->trads['mod_admin_securitytools_ipfilterrulestatus_disabled'] = 'Disabled';
$this->trads['mod_admin_securitytools_ipfilterrulestatus_enabled'] = 'Enabled';

/* IP Filter rules status values */
$this->trads['mod_admin_securitytools_ipfilterrulesstatus_disabled'] = 'Disabled';
$this->trads['mod_admin_securitytools_ipfilterrulesstatus_enabled'] = 'Enabled';

/* IP Filter rule permission values */
$this->trads['mod_admin_securitytools_ipfilterrulepermission_deny'] = 'Deny';
$this->trads['mod_admin_securitytools_ipfilterrulepermission_allow'] = 'Allow';

/* IP Filter rule site mode values */
$this->trads['mod_admin_securitytools_ipfilterrulesitemode_both'] = 'Visit and admin';
$this->trads['mod_admin_securitytools_ipfilterrulesitemode_admin'] = 'Admin only';
$this->trads['mod_admin_securitytools_ipfilterrulesitemode_visit'] = 'Visit only';
$this->trads['mod_admin_securitytools_ipfilterrulesite_admin'] = 'Admin';
$this->trads['mod_admin_securitytools_ipfilterrulesite_visit'] = 'Visit';

/* URL Filter rule status values */
$this->trads['mod_admin_securitytools_urlfilterrulestatus_disabled'] = 'Disabled';
$this->trads['mod_admin_securitytools_urlfilterrulestatus_enabled'] = 'Enabled';

/* URL Filter rules status values */
$this->trads['mod_admin_securitytools_urlfilterrulesstatus_disabled'] = 'Disabled';
$this->trads['mod_admin_securitytools_urlfilterrulesstatus_enabled'] = 'Enabled';

/* main: settings tab */
$this->trads['mod_admin_securitytools_tabmain'] = 'Security';
$this->trads['mod_admin_securitytools_disable'] = 'Disable';
$this->trads['mod_admin_securitytools_enable'] = 'Enable';
$this->trads['mod_admin_securitytools_configure'] = 'Configure';

$this->trads['mod_admin_securitytools_availableactions'] = 'Checks: ';
$this->trads['mod_admin_securitytools_action_checkcamyksintegrity'] = 'Check CaMykS integrity';
$this->trads['mod_admin_securitytools_availabletools'] = 'Available tools: ';
$this->trads['mod_admin_securitytools_tool_ipfilter'] = 'IP filter';
$this->trads['mod_admin_securitytools_tool_urlfilter'] = 'URL filter';
$this->trads['mod_admin_securitytools_tool_uafilter'] = 'User agent filter';
$this->trads['mod_admin_securitytools_tool_backup'] = 'Backup';

/* main: ip filter tab */
$this->trads['mod_admin_securitytools_verify_ipaddress'] = 'Check IP address';
$this->trads['mod_admin_securitytools_addnewipfilterrule'] = 'Add a IP filter rule';
$this->trads['mod_admin_securitytools_ipfilter_editrule'] = 'Edit this rule';
$this->trads['mod_admin_securitytools_ipfilter_deleterule'] = 'Delete this rule';
$this->trads['mod_admin_securitytools_deletefilteriprule'] = 'Are you sure to want to delete this rule ? This action can\'t be undone.';
$this->trads['mod_admin_securitytools_ipaddress'] = 'IP address';
$this->trads['mod_admin_securitytools_sitemode'] = 'Location';
$this->trads['mod_admin_securitytools_comment'] = 'Comment';

/* main: url filter tab */
$this->trads['mod_admin_securitytools_addnewurlfilterrule'] = 'Add a URL filter rule';
$this->trads['mod_admin_securitytools_urlfilter_editrule'] = 'Edit this rule';
$this->trads['mod_admin_securitytools_urlfilter_deleterule'] = 'Delete this rule';
$this->trads['mod_admin_securitytools_deletefilteriprule'] = 'Are you sure to want to delete this rule ? This action can\'t be undone.';
$this->trads['mod_admin_securitytools_pattern'] = 'Pattern';

/* main: backup tab */
$this->trads['mod_admin_securitytools_ipfilter_unauthorizedip'] = 'Unauthorised IP addresses';
$this->trads['mod_admin_securitytools_ipfilter_authorizedip'] = 'Authorised IP addresses';

/* edit/view ip filter rules */
$this->trads['mod_admin_securitytools_ipfilter_rulenew'] = 'New rule';
$this->trads['mod_admin_securitytools_ipfilter_ruleid'] = 'Rule #%s';
$this->trads['mod_admin_securitytools_ipfilter_ipaddress'] = 'IP address: ';
$this->trads['mod_admin_securitytools_ipfilter_permission'] = 'Permission: ';
$this->trads['mod_admin_securitytools_ipfilter_mode'] = 'Mode: ';
$this->trads['mod_admin_securitytools_ipfilter_comment'] = 'Comment: ';

$this->trads['mod_admin_securitytools_error_nonvalidipaddress'] = 'IP address is not valid.';

/* edit/view url filter rules */
$this->trads['mod_admin_securitytools_urlfilter_rulenew'] = 'New rule';
$this->trads['mod_admin_securitytools_urlfilter_ruleid'] = 'Rule #%s';
$this->trads['mod_admin_securitytools_formitem_pattern'] = 'Pattern: ';

/* edit ua filter configuration */
$this->trads['mod_admin_securitytools_uafilter_configuration'] = 'User agent filter configuration';
$this->trads['mod_admin_securitytools_formitem_blockhacks'] = 'Deny visits from hacks: ';
$this->trads['mod_admin_securitytools_formitem_blockfakes'] = 'Deny fake visits: ';

/* edit/view backup */
$this->trads['mod_admin_securitytools_backup_configuration'] = 'Configuration: ' ;
$this->trads['mod_admin_securitytools_backup_files'] = 'Available backups: ';
$this->trads['mod_admin_securitytools_backup_method'] = 'Backup: ';
$this->trads['mod_admin_securitytools_backup_method_manual'] = 'Manual';
$this->trads['mod_admin_securitytools_backup_method_daily'] = 'Daily';
$this->trads['mod_admin_securitytools_backup_method_weekly'] = 'Weekly';
$this->trads['mod_admin_securitytools_backup_method_monthly'] = 'Monthly';
$this->trads['mod_admin_securitytools_backup_compression'] = 'File format: ';
$this->trads['mod_admin_securitytools_backup_compression_tar'] = 'Tar Archive (no compression)';
$this->trads['mod_admin_securitytools_backup_compression_tgz'] = 'Tar Archive (GZip compression)';
$this->trads['mod_admin_securitytools_backup_compression_tbz'] = 'Tar Archive (BZip2 compression)';
$this->trads['mod_admin_securitytools_backup_compression_zip'] = 'Zip Archive';
$this->trads['mod_admin_securitytools_backup_type'] = 'Type: ';
$this->trads['mod_admin_securitytools_backup_type_complete'] = 'Full';
$this->trads['mod_admin_securitytools_backup_type_data'] = 'Data only';
$this->trads['mod_admin_securitytools_backup_type_file'] = 'Files only';
$this->trads['mod_admin_securitytools_backup_nextdate'] = 'Next backup: ';
$this->trads['mod_admin_securitytools_backup_modify'] = 'Modify';
$this->trads['mod_admin_securitytools_backup_nofile'] = 'No file';
$this->trads['mod_admin_securitytools_backup_modifyconfig'] = 'Edit backup configuration';
$this->trads['mod_admin_securitytools_backup_download'] = 'Download this backup';
$this->trads['mod_admin_securitytools_backup_delete'] = 'Delete this backup';
$this->trads['mod_admin_securitytools_backup_size'] = 'Size';
$this->trads['mod_admin_securitytools_backup_deletebackup'] = 'Are you sure to want to delete this backup?';
$this->trads['mod_admin_securitytools_backup_newbackup'] = 'Create a new backup';
$this->trads['mod_admin_securitytools_backup_createbackup'] = 'Create backup';
$this->trads['mod_admin_securitytools_backup_temp'] = 'Temporary folder: ';
$this->trads['mod_admin_securitytools_backup_systempfolder'] = 'System\'s temporary folder';
$this->trads['mod_admin_securitytools_backup_nulltempissystemfolder'] = 'Let this field empty to use the system\'s temporary folder.';

/* save configuration */
$this->trads['mod_admin_securitytools_config_saved'] = 'Configuration saved.';
$this->trads['mod_admin_securitytools_config_notsaved'] = 'Configuration not saved.';

/* save rule */
$this->trads['mod_admin_securitytools_rule_saved'] = 'Rule saved.';
$this->trads['mod_admin_securitytools_rule_notsaved'] = 'Rule not saved.';

/* delete rule */
$this->trads['mod_admin_securitytools_rule_deleted'] = 'Rule deleted.';
$this->trads['mod_admin_securitytools_rule_notdeleted'] = 'Rule not deleted.';

/* delete backup */
$this->trads['mod_admin_securitytools_backup_deleted'] = 'Backup deleted.';
$this->trads['mod_admin_securitytools_backup_notdeleted'] = 'Backup not deleted.';

/* save backup */
$this->trads['mod_admin_securitytools_backup_saved'] = 'Backup created.';
$this->trads['mod_admin_securitytools_backup_failed'] = 'An error has occured while creating the backup. Please consult internal logs to check the errors.';

/* check camyks integrity */
$this->trads['mod_admin_securitytools_formtitle_checkcamyksintegrity'] = 'Check CaMykS integrity';
$this->trads['mod_admin_securitytools_formtitle_integritysummary'] = 'Summary';
$this->trads['mod_admin_securitytools_formitem_integrityfiledate'] = 'File check date: ';
$this->trads['mod_admin_securitytools_formitem_lastgitcommit'] = 'Last Git commit date: ';
$this->trads['mod_admin_securitytools_formitem_filecountindesc'] = 'Files in check: ';
$this->trads['mod_admin_securitytools_formitem_filecountlocal'] = 'Local files: ';
$this->trads['mod_admin_securitytools_formtitle_errors'] = 'Errors';
$this->trads['mod_admin_securitytools_formitem_errorextrafiles'] = 'Extra file errors: ';
$this->trads['mod_admin_securitytools_formitem_errormissingfiles'] = 'Missing file errors: ';
$this->trads['mod_admin_securitytools_formitem_errorchecksum'] = 'Checksum errors: ';
$this->trads['mod_admin_securitytools_formitem_errormime'] = 'MIME errors: ';
$this->trads['mod_admin_securitytools_formitem_errorheader'] = 'Header errors: ';
$this->trads['mod_admin_securitytools_formitem_errorversion'] = 'Version errors: ';
$this->trads['mod_admin_securitytools_formtitle_integritydetails'] = 'Errors detail';
$this->trads['mod_admin_securitytools_formitem_file'] = 'File';
$this->trads['mod_admin_securitytools_formitem_checkvalue'] = 'Checked value';
$this->trads['mod_admin_securitytools_formitem_localvalue'] = 'Local value';

$this->trads['mod_admin_securitytools_integrity_error_extra'] = 'File has been found in local CaMykS folder, but is not avaialable in check data.';
$this->trads['mod_admin_securitytools_integrity_error_missing'] = 'File has been found in check data, but is not avaialable in local CaMykS folder.';
$this->trads['mod_admin_securitytools_integrity_error_checksum'] = 'File checksums are different. <br />Check value: <strong>%s</strong> <br /> Local value: <strong>%s</strong>';
$this->trads['mod_admin_securitytools_integrity_error_mime'] = 'File MIME are different. Check data: <strong>%s</strong> - Local value: <strong>%s</strong>';
$this->trads['mod_admin_securitytools_integrity_error_header'] = 'File headers are different.';
$this->trads['mod_admin_securitytools_integrity_error_version'] = 'File versions are different. Check value: <strong>%s</strong> - Local value: <strong>%s</strong>';
?>
