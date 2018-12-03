<?php
/**
 * @brief Admin_SecurityTools Module french dictionnary
 * @details Plugin / Module Dictionnary
 * @file plugin/module/Admin_SecurityTools/locale/translation_fr.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: Oct 2007
 * @date Modification: Nov 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

$this->trads['mod_admin_securitytools_title'] = 'Outils S&eacute;curit&eacute;';
$this->trads['mod_admin_securitytools_desc'] = 'Filtre IP, Sauvegarde, ... ';

/* Objects */
$this->trads['mod_admin_securitytools_ipfilterrule'] = 'R&egrave;gle du filtre IP';
$this->trads['mod_admin_securitytools_ipfilterrules'] = 'R&egrave;gles du filtre IP';
$this->trads['mod_admin_securitytools_ipfilterrules_all'] = 'Toutes';

$this->trads['mod_admin_securitytools_backup'] = 'Sauvegarde';
$this->trads['mod_admin_securitytools_backups'] = 'Sauvegardes';
$this->trads['mod_admin_securitytools_backups_all'] = 'Toutes';

/* rights */
$this->trads['mod_admin_securitytools_right_config'] = 'Configuration';
$this->trads['mod_admin_securitytools_right_ipfilter'] = 'R&egrave;gle du filtre IP';
$this->trads['mod_admin_securitytools_right_backup'] = 'Sauvegarde';

/* IP Filter rule status values */
$this->trads['mod_admin_securitytools_ipfilterrulestatus_disabled'] = 'D&eacute;sactiv&eacute;e';
$this->trads['mod_admin_securitytools_ipfilterrulestatus_enabled'] = 'Activ&eacute;e';

/* IP Filter rules status values */
$this->trads['mod_admin_securitytools_ipfilterrulesstatus_disabled'] = 'D&eacute;sactiv&eacute;es';
$this->trads['mod_admin_securitytools_ipfilterrulesstatus_enabled'] = 'Activ&eacute;es';

/* IP Filter rule permission values */
$this->trads['mod_admin_securitytools_ipfilterrulepermission_deny'] = 'Refuser';
$this->trads['mod_admin_securitytools_ipfilterrulepermission_allow'] = 'Autoriser';

/* IP Filter rule site mode values */
$this->trads['mod_admin_securitytools_ipfilterrulesitemode_both'] = 'Visite et administration';
$this->trads['mod_admin_securitytools_ipfilterrulesitemode_admin'] = 'Administration seulement';
$this->trads['mod_admin_securitytools_ipfilterrulesitemode_visit'] = 'Visite seulement';
$this->trads['mod_admin_securitytools_ipfilterrulesite_admin'] = 'Admin.';
$this->trads['mod_admin_securitytools_ipfilterrulesite_visit'] = 'Visite';

/* tabs */
$this->trads['mod_admin_securitytools_tabmain'] = 'S&eacute;curit&eacute;';

/* main */
$this->trads['mod_admin_securitytools_disable'] = 'D&eacute;sactiver';
$this->trads['mod_admin_securitytools_enable'] = 'Activer';

$this->trads['mod_admin_securitytools_availabletools'] = 'Outils disponibles : ';
$this->trads['mod_admin_securitytools_tool_ipfilter'] = 'Filtre IP';
$this->trads['mod_admin_securitytools_tool_backup'] = 'Sauvegarde';

/* ip filter tab */
$this->trads['mod_admin_securitytools_verify_ipaddress'] = 'V&eacute;rifier l\'adresse IP';
$this->trads['mod_admin_securitytools_addnewipfilterrule'] = 'Ajouter une r&egrave;gle de filtre IP';
$this->trads['mod_admin_securitytools_ipfilter_editrule'] = 'Editer cette r&egrave;gle';
$this->trads['mod_admin_securitytools_ipfilter_deleterule'] = 'Supprimer cette r&egrave;gle';
$this->trads['mod_admin_securitytools_ipaddress'] = 'Adresse IP';
$this->trads['mod_admin_securitytools_sitemode'] = 'Espace';
$this->trads['mod_admin_securitytools_comment'] = 'Commentaire';

/* backup tab */
$this->trads['mod_admin_securitytools_ipfilter_unauthorizedip'] = 'Adresses IP non-autoris&eacute;es';
$this->trads['mod_admin_securitytools_ipfilter_authorizedip'] = 'Adresses IP autoris&eacute;es';

/* edit/view ip filter rules */
$this->trads['mod_admin_securitytools_ipfilter_rulenew'] = 'Nouvelle r&egrave;gle';
$this->trads['mod_admin_securitytools_ipfilter_ruleid'] = 'R&egrave;gle n&deg;%s';
$this->trads['mod_admin_securitytools_ipfilter_ipaddress'] = 'Adresse IP : ';
$this->trads['mod_admin_securitytools_ipfilter_permission'] = 'Permission : ';
$this->trads['mod_admin_securitytools_ipfilter_mode'] = 'Mode : ';
$this->trads['mod_admin_securitytools_ipfilter_comment'] = 'Commentaire : ';

$this->trads['mod_admin_securitytools_error_nonvalidipaddress'] = 'L\'adresse IP donn&eacute;e n\'est pas valide.';
$this->trads['mod_admin_securitytools_deletefilteriprule'] = 'Etes vous sur de vouloir supprimer cette r&egrave;gle ? Cette action est irr&eacute;versible.';

/* edit/view backup */
$this->trads['mod_admin_securitytools_backup_configuration'] = 'Configuration : ' ;
$this->trads['mod_admin_securitytools_backup_files'] = 'Sauvegardes disponibles : ';
$this->trads['mod_admin_securitytools_backup_method'] = 'Sauvegarde : ';
$this->trads['mod_admin_securitytools_backup_method_manual'] = 'Manuelle';
$this->trads['mod_admin_securitytools_backup_method_daily'] = 'Journali&egrave;re';
$this->trads['mod_admin_securitytools_backup_method_weekly'] = 'Hebdomadaire';
$this->trads['mod_admin_securitytools_backup_method_monthly'] = 'Mensuelle';
$this->trads['mod_admin_securitytools_backup_compression'] = 'Format de fichier : ';
$this->trads['mod_admin_securitytools_backup_compression_tar'] = 'Archive Tar (sans compression)';
$this->trads['mod_admin_securitytools_backup_compression_tgz'] = 'Archive Tar (compression GZip)';
$this->trads['mod_admin_securitytools_backup_compression_tbz'] = 'Archive Tar (compression BZip2)';
$this->trads['mod_admin_securitytools_backup_compression_zip'] = 'Archive Zip';
$this->trads['mod_admin_securitytools_backup_type'] = 'Type : ';
$this->trads['mod_admin_securitytools_backup_type_complete'] = 'Complet';
$this->trads['mod_admin_securitytools_backup_type_data'] = 'Donn&eacute;es seulement';
$this->trads['mod_admin_securitytools_backup_type_file'] = 'Fichiers seulement';
$this->trads['mod_admin_securitytools_backup_nextdate'] = 'Prochaine sauvegarde : ';
$this->trads['mod_admin_securitytools_backup_modify'] = 'Modifier';
$this->trads['mod_admin_securitytools_backup_nofile'] = 'Aucune';
$this->trads['mod_admin_securitytools_backup_modifyconfig'] = 'Modifier la configuration des sauvegardes';
$this->trads['mod_admin_securitytools_backup_download'] = 'T&eacute;l&eacute;charger cette sauvegarde';
$this->trads['mod_admin_securitytools_backup_delete'] = 'Supprimer cette sauvegarde';
$this->trads['mod_admin_securitytools_backup_size'] = 'Taille';
$this->trads['mod_admin_securitytools_backup_deletebackup'] = 'Etes vous sur de vouloir supprimer cette sauvegarde?';
$this->trads['mod_admin_securitytools_backup_newbackup'] = 'Cr&eacute;er une sauvegarde';
$this->trads['mod_admin_securitytools_backup_createbackup'] = 'Cr&eacute;er la sauvegarde';
$this->trads['mod_admin_securitytools_backup_temp'] = 'Dossier temporaire : ';
$this->trads['mod_admin_securitytools_backup_systempfolder'] = 'Dossier temporaire syst&egrave;me';
$this->trads['mod_admin_securitytools_backup_nulltempissystemfolder'] = 'Laissez le champs vide pour utiliser le dossier temporaire syst&egrave;me.';

/* messages */
$this->trads['mod_admin_securitytools_config_saved'] = 'Configuration sauvegard&eacute;e.';
$this->trads['mod_admin_securitytools_config_notsaved'] = 'Configuration non sauvegard&eacute;e.';
$this->trads['mod_admin_securitytools_rule_saved'] = 'R&egrave;gle sauvegard&eacute;e.';
$this->trads['mod_admin_securitytools_rule_notsaved'] = 'R&egrave;gle non sauvegard&eacute;e.';
$this->trads['mod_admin_securitytools_rule_deleted'] = 'R&egrave;gle supprim&eacute;e.';
$this->trads['mod_admin_securitytools_rule_notdeleted'] = 'R&egrave;gle non supprim&eacute;e.';
$this->trads['mod_admin_securitytools_backup_deleted'] = 'Sauvegarde supprim&eacute;e.';
$this->trads['mod_admin_securitytools_backup_notdeleted'] = 'Sauvegarde non supprim&eacute;e.';
$this->trads['mod_admin_securitytools_backup_saved'] = 'Sauvegarde manuelle cr&eacute;&eacute;e.';
$this->trads['mod_admin_securitytools_backup_failed'] = 'Une erreur est survenue pendant la sauvegarde, consulter les rapports internes pour en voir la cause.';
?>
