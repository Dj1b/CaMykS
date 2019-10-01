<?php
/**
 * @brief Admin_Site Module admin view site configuration layout.
 * @details Plugin / Module layout
 * @file plugin/module/Admin_Site/html/admin_view_site_config.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: Jan 2005
 * @date Modification: Sep 2019
 * @copyright 2005 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
$view = $this->theme->get_pictURL('view', 12, 'std');
$view_ = $this->theme->get_pictURL('view', 12, 'ovr');
$cnfg = $this->theme->get_pictURL('action', 12, 'std');
$cnfg_ = $this->theme->get_pictURL('action', 12, 'ovr');

global $camyks;
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule', 'style'=>'width:500px; margin:0 auto;')); ?>
<?= $this->theme->get_boxTitleBar($this->title); ?>
<?= $this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<div id="itemProperties" style="display:<?= $this->tabBuilder->get_tabDisplay('Properties'); ?>;" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableHeader" colspan="3">
                <?= $this->get_translation('formtitle_general'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2" style="width:175px;">
                <?= $this->get_translation('formitem_sitetitle'); ?>
            </td>
            <td class="eTableLine0 eContent1" colspan="2">
                <?= $camyks->get_confValue('site_title'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_sitename'); ?>
            </td>
            <td class="eTableLine1 eContent1" colspan="2">
                <?= $camyks->get_confValue('site_name'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_url'); ?>
            </td>
            <td class="eTableLine0 eContent1" colspan="2">
                <?= $camyks->get_confValue('url'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_version'); ?>
            </td>
            <td class="eTableLine1 eContent1" colspan="2">
                <?= $camyks->get_confValue('version'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0" colspan="3">
                &nbsp;
            </td>
        </tr>

        <tr>
            <td class="eTableHeader" colspan="3">
                <?= CAMYKS_NAME; ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_version'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $camyks->version; ?>
            </td>
            <td class="eTableLine0 eContent1" rowspan="3" style="width:250px; vertical-align:top; text-align:center;">
                <?php if ($this->securityTools !== false and $this->securityTools->check_right(1)) : ?>
                <?= $this->theme->get_button(array(
                    'title' => $this->get_translation('action_checkcamyksintegrity'),
                    'url'   => $this->securityTools->get_adminLink(array('mode'=>'checkCaMykSIntegrity'))
                )); ?>
                <?php endif; ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_installation'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->get_translation('camyksinstallation_'.$camyks->_installationMode); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_path'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $camyks->get_confValue('engine_path'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0" colspan="3">
                &nbsp;
            </td>
        </tr>
        <tr>
            <td class="eTableHeader" colspan="3">
                <?= $this->get_translation('formtitle_contacts'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_author'); ?>
            </td>
            <td class="eTableLine0 eContent1" colspan="2">
                <?= $camyks->get_confValue('site_author'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_company'); ?>
            </td>
            <td class="eTableLine1 eContent1" colspan="2">
                <?= $camyks->get_confValue('site_company'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0" colspan="3">
                &nbsp;
            </td>
        </tr>
        <tr>
            <td class="eTableHeader" colspan="3">
                <?= $this->get_translation('formtitle_settings'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_friendlyurls'); ?>
            </td>
            <td class="eTableLine0 eContent1" colspan="2">
                <?php if ($camyks->get_confValue('friendlyurls')==1) : ?>
                    <?= $this->get_translation('friendlyurls_legacy'); ?>
                <?php elseif ($camyks->get_confValue('friendlyurls') == 'modern') : ?>
                    <?= $this->get_translation('friendlyurls_modern'); ?>
                <?php elseif ($camyks->get_confValue('friendlyurls') == 'modern2') : ?>
                    <?= $this->get_translation('friendlyurls_modern2'); ?>
                <?php else :  ?>
                    N/A
                <?php endif; ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_encoding'); ?>
            </td>
            <td class="eTableLine1 eContent1" colspan="2">
                <?= $camyks->get_confValue('encoding'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_htmlversion'); ?>
            </td>
            <td class="eTableLine0 eContent1" colspan="2">
                <?= $camyks->get_confValue('html_version'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0" colspan="3">
                &nbsp;
            </td>
        </tr>
        <tr>
            <td class="eTableHeader" colspan="3">
                <?= $this->get_translation('formtitle_caches'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_serverside'); ?>
            </td>
            <td class="eTableLine0 eContent1" colspan="2">
                <?= $camyks->get_confValue('cache_server_side') == 'enabled' ? $this->get_translation('cache_enabled') : $this->get_translation('cache_none'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_clientside'); ?>
            </td>
            <td class="eTableLine1 eContent1" colspan="2">
                <?= $camyks->get_confValue('cache_client_side') == 'disabled' ? $this->get_translation('cache_disabled') : $this->get_translation('cache_default'); ?>
            </td>
        </tr>
    </table>
</div>

<div id="itemDatabase" style="display:<?= $this->tabBuilder->get_tabDisplay('Database'); ?>;" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('formtitle_connection'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2" style="width:175px;">
                <?= $this->get_translation('formitem_version'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->dbSummary['version']; ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_databasedriver'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $camyks->get_confValue('database_driver'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_databasehost'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $camyks->get_confValue('database_host'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_databasename'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $camyks->get_confValue('database_name'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0" colspan="2">
                &nbsp;
            </td>
        </tr>
        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('formtitle_statistics'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_databasesize'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= file_getFileSize($this->dbSummary['size']); ?>
            </td>
        </tr>

        <?php $alt = 1; ?>
        <?php if (isset($this->dbSummary['tables'])) : ?>
        <tr>
            <td class="eTableLine<?= $alt; ?> eContent2">
                <?= $this->get_translation('formitem_tables'); ?>
            </td>
            <td class="eTableLine<?= $alt; ?> eContent1">
                <?= count($this->dbSummary['tables']); ?>
            </td>
        </tr>
        <?php $alt=abs($alt-1); ?>
        <?php endif; ?>

        <?php if (isset($this->dbSummary['tables'])) : ?>
        <tr>
            <td class="eTableLine<?= $alt; ?> eContent2">
                <?= $this->get_translation('formitem_lines'); ?>
            </td>
            <td class="eTableLine<?= $alt; ?> eContent1">
                <?= $this->dbSummary['lineCount']; ?>
            </td>
        </tr>
        <?php $alt=abs($alt-1); ?>
        <?php endif; ?>

        <?php if (isset($this->dbSummary['tables'])) : ?>
        <tr>
            <td class="eTableLine<?= $alt; ?> eContent2">
                <?= $this->get_translation('formitem_connections'); ?>
            </td>
            <td class="eTableLine<?= $alt; ?> eContent1">
                <?= $this->dbSummary['connections']; ?>
            </td>
        </tr>
        <?php $alt=abs($alt-1); ?>
        <?php endif; ?>

        <?php if (isset($this->dbSummary['tablesStatus'])) : ?>
        <tr>
            <td class="eTableLine0" colspan="2">
                &nbsp;
            </td>
        </tr>
        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('formtitle_status'); ?>
            </td>
        </tr>

        <?php if (isset($this->dbSummary['tablesStatus']['status'])) : ?>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_tablesok'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->dbSummary['tablesStatus']['status']['OK']; ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_tablesnotok'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->dbSummary['tablesStatus']['status']['NotOK']; ?>
            </td>
        </tr>
        <?php endif; ?>

        <?php foreach (array('error', 'info', 'note', 'warning') as $type) : ?>
        <tr>
            <td class="eTableLine0 eContent4" colspan="2">
                <?= $this->get_translation('formtitle_'.$type); ?>
            </td>
        </tr>
        <?php if (!isset($this->dbSummary['tablesStatus'][$type]) or count($this->dbSummary['tablesStatus'][$type]) == 0) : ?>
        <tr>
            <td class="eTableLine0 eContent2" colspan="2" style="padding-left:30px;">
                <?= $this->get_translation('formdesc_nomessage'); ?>
            </td>
        </tr>
        <?php else : ?>

            <?php $alt = 0; ?>

            <?php foreach ($this->dbSummary['tablesStatus'][$type] as $message) : ?>
                <tr>
                    <td class="eTableLine<?= $alt; ?> eContent2">
                        <?= $message['table']; ?>
                    </td>
                    <td class="eTableLine<?= $alt; ?> eContent1">
                        <?= $message['message']; ?>
                    </td>
                </tr>
            <?php $alt = abs($alt-1); ?>
            <?php endforeach; ?>

            <tr>
                <td class="eTableLine0" colspan="2">
                    &nbsp;
                </td>
            </tr>
        <?php endif; ?>
        <?php endforeach; ?>
        <?php endif; ?>

    </table>
</div>

<div id="itemAdminMode" style="display:<?= $this->tabBuilder->get_tabDisplay('AdminMode'); ?>;" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('formtitle_general'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2" style="width:175px;">
                <?= $this->get_translation('formitem_ssl'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->get_SSLValueDescription($camyks->get_confValue('admin_ssl')); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_adminentry'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $camyks->get_confValue('admin_entry'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_theme'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $camyks->get_confValue('admin_default_theme'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0" colspan="2">
                &nbsp;
            </td>
        </tr>
        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('formtitle_languages'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2" colspan="2">
                <?= $this->get_translation('formitem_adminlanguages'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent1" colspan="2" style="font-size:0;">
                <?php foreach ($camyks->get_confValue('admin_languages') as $language) : ?>
                <div style="width:33%; display:inline-block;">
                    <input type="checkbox" <?= $camyks->get_confValue('admin_default_language') == $language ? 'checked' : ''; ?> disabled="disabled" style="margin-right:4px;"/>
                    <img src="<?= language_getIcon($language, false) ?>" alt="<?= $camyks->get_translation('lang_'.$language); ?>" style="margin-right:4px;" />
                    <?= $camyks->get_translation('lang_'.$language); ?>
                </div>
                <?php endforeach; ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2" colspan="2">
                <?= $this->get_translation('formitem_editinglanguages'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent1" colspan="2" style="font-size:0;">
                <?php foreach ($camyks->get_confValue('admin_languages') as $language) : ?>
                    <div style="width:33%; display:inline-block;">
                    <input type="checkbox" disabled="disabled" style="margin-right:4px; visibility:hidden;"/>
                    <img src="<?= language_getIcon($language, false) ?>" alt="<?= $camyks->get_translation('lang_'.$language); ?>" style="margin-right:4px;" />
                    <?= $camyks->get_translation('lang_'.$language); ?>
                    </div>
                <?php endforeach; ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0" colspan="2">
                &nbsp;
            </td>
        </tr>
        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('formtitle_lists'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_items'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $camyks->get_confValue('admin_itemsbypage'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0" colspan="2">
                &nbsp;
            </td>
        </tr>
        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('formtitle_files'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_uploadmaxsize'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= file_getFileSize($camyks->get_confValue('admin_maxfilesize')); ?>
            </td>
        </tr>
    </table>
</div>

<div id="itemSiteMode" style="display:<?= $this->tabBuilder->get_tabDisplay('SiteMode'); ?>;" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('formtitle_general'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2" style="width:175px;">
                <?= $this->get_translation('formitem_ssl'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->get_SSLValueDescription($camyks->get_confValue('site_ssl')); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_defaulttheme'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $camyks->get_confValue('site_default_theme'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_defaulttemplate'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $camyks->get_confValue('site_default_template'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_pagemaxmodules'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $camyks->get_confValue('page_maxmodules'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0" colspan="2">
                &nbsp;
            </td>
        </tr>
        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('formtitle_languages'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent1" colspan="2" style="font-size:0;">
                <?php foreach ($camyks->get_confValue('site_languages') as $language) : ?>
                <div style="width:33%; display:inline-block;">
                    <input type="checkbox" <?= $camyks->get_confValue('site_default_language') == $language ? 'checked' : ''; ?> disabled="disabled" style="margin-right:4px;"/>
                    <img src="<?= language_getIcon($language, false); ?>" alt="<?= $camyks->get_translation('lang_'.$language); ?>" style="margin-right:4px;" />
                    <?= $camyks->get_translation('lang_'.$language); ?>
                </div>
                <?php endforeach; ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0" colspan="2">
                &nbsp;
            </td>
        </tr>
        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('formtitle_handheld'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_responsive'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <input type="checkbox"<?= $camyks->get_confValue('enable_responsiveDesign')==1?' checked="checked"': ''; ?> disabled="disabled" />
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_declination'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <input type="checkbox"<?= $camyks->get_confValue('enable_handheldVersion')==1?' checked="checked"': ''; ?> disabled="disabled" />
            </td>
        </tr>
        <tr>
            <td class="eTableLine0" colspan="2">
                &nbsp;
            </td>
        </tr>
        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('formtitle_statistics'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_google_analytics'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?php if ($camyks->get_confValue('google_analytics') == '') : ?>
                    <?= $this->get_translation('stats_none'); ?>
                <?php else : ?>
                    <?= $camyks->get_confValue('google_analytics'); ?>
                    <?php if ($camyks->get_confValue('google_analytics_domain') != '') : ?>
                        <?= $this->get_translation('formitem_domain'); ?>
                        <?= $camyks->get_confValue('google_analytics_domain'); ?>
                    <?php endif; ?>
                <?php endif; ?>
            </td>
        </tr>
    </table>
</div>

<div id="itemServer" style="display:<?= $this->tabBuilder->get_tabDisplay('Server'); ?>;" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('formtitle_operatingsystem'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_version'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= php_uname('s').' '.php_uname('r').' ('.php_uname('m').')'; ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0" colspan="2">
                &nbsp;
            </td>
        </tr>
        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('formtitle_httpserver'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2" style="width:175px;">
                <?= $this->get_translation('formitem_version'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $_SERVER['SERVER_SOFTWARE']; ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0" colspan="2">
                &nbsp;
            </td>
        </tr>
        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('formtitle_php'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2" style="width:175px;">
                <?= $this->get_translation('formitem_version'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= phpversion(); ?>
            </td>
        </tr>
    </table>
</div>

<?php if ($this->check_right(2)) : ?>
<div id="itemPlugins" style="display:<?= $this->tabBuilder->get_tabDisplay('Plugins'); ?>;" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <?php foreach ($this->plugins as $type => $list) : ?>
            <?php if (count($list) == 0) continue; ?>
            <tr>
                <td class="eTableHeader" colspan="3">
                    <?= $camyks->get_translation($type); ?>
                </td>
            </tr>

            <?php $alt = 0; ?>
            <?php foreach ($list as $name => $title) : ?>
                <tr>
                    <td class="eTableLine<?= $alt; ?> eContent2">
                        <?= $title; ?>
                    </td>
                    <td class="eTableLine<?= $alt; ?> eTableIconCell">
                        <a href="<?= $this->get_adminLink(array('mode'=>'viewPluginConfig', 'plugin'=>$name)); ?>" class="img">
                            <img src="<?= $view; ?>" alt="<?= $this->get_translation('viewthispluginconfig'); ?>" title="<?= $this->get_translation('viewthispluginconfig'); ?>"
                                onmouseover="this.src='<?= $view_; ?>';" onmouseout="this.src='<?= $view; ?>';" />
                        </a>
                    </td>
                    <td class="eTableLine<?= $alt; ?> eTableIconCell">
                        <?php if ($this->check_right(2)) : ?>
                            <a href="<?= $this->get_adminLink(array('mode'=>'editPluginConfig', 'plugin'=>$name)); ?>" class="img">
                                <img src="<?= $cnfg; ?>" alt="<?= $this->get_translation('editthispluginconfig'); ?>" title="<?= $this->get_translation('editthispluginconfig'); ?>"
                                    onmouseover="this.src='<?= $cnfg_; ?>';" onmouseout="this.src='<?= $cnfg; ?>';" />
                             </a>
                        <?php else : ?>
                            &nbsp;
                        <?php endif; ?>
                    </td>
                </tr>

                <?php $alt = abs($alt-1); ?>
            <?php endforeach; ?>

            <tr>
                <td class="eTableLine0" colspan="3">
                    &nbsp;
                </td>
            </tr>
        <?php endforeach; ?>
    </table>
</div>
<?php endif; ?>

<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
