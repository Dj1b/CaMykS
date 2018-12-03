<?php
/**
 * @brief Admin_SecurityTools Module admin main layout
 * @details Plugin / Module layout
 * @file plugin/module/Admin_SecurityTools/html/admin.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: Oct 2007
 * @date Modification: Jun 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;

$view = $this->theme->get_pictURL('view', 12, 'std');
$view_ = $this->theme->get_pictURL('view', 12, 'ovr');

$edit = $this->theme->get_pictURL('edit', 12, 'std');
$edit_ = $this->theme->get_pictURL('edit', 12, 'ovr');

$del = $this->theme->get_pictURL('cross', 12, 'std');
$del_ = $this->theme->get_pictURL('cross', 12, 'ovr');

$add = $this->theme->get_pictURL('plus', 12, 'std');
$add_ = $this->theme->get_pictURL('plus', 12, 'ovr');

$file = $this->theme->get_pictURL('file', 12, 'std');
$file_ = $this->theme->get_pictURL('file', 12, 'ovr');

$valid = $this->theme->get_pictURL('valid', 12, 'std');
$empty = $this->theme->get_pictURL('empty', 12, 'std');
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title); ?>
<?= $this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams); ?>
<?= $this->theme->get_boxContent2Header(); ?>

<div id="itemConfiguration" style="display:<?= $this->tabBuilder->get_tabDisplay('Configuration'); ?>;" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0">
        <tr>
            <td class="eTitle3" colspan="4">
                <?= $this->get_translation('availabletools'); ?>
            </td>
        </tr>

        <?php foreach ($this->tools as $tool) : ?>
        <tr>
            <td class="eTableLine0 eContent1" style="width:12px;">
                &nbsp;
            </td>
            <td class="eTableLine0 eContent1">
                <img src="<?= $this->get_fileURL('img/'.($this->config->vars[$tool]?'enabled':'disabled').'.gif'); ?>" alt="" border="0" />
            </td>
            <td class="eTableLine0 eContent1" style="padding:0 8px;">
                <?= $this->get_translation('tool_'.$tool); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?php if ($this->check_right(1)) : ?>
                    <?php $action = $this->config->vars[$tool]?'disable':'enable'; ?>
                    <?= $this->theme->get_button(array('title'=>$this->get_translation($action), 'url'=>$camyks->get_adminLink($this->name, array('mode'=>'update_config','action'=>$action, 'item'=>$tool)))); ?>
                <?php endif; ?>
            </td>
        </tr>
        <?php endforeach; ?>
    </table>
</div>

<?php if ($this->config->vars['ipfilter']) : ?>
    <div id="itemIPFilter" style="display:<?= $this->tabBuilder->get_tabDisplay('IPFilter'); ?>;" class="adminContentPanel">

        <div class="eTableLine1" style="height:32px; padding:4px; vertical-align:middle; margin-bottom:8px;">
            <input type="text" id="IPAddress" maxlength="16" class="sinputs" />
            <select id="section" class="sinputs">
                <option value="1"><?= $this->get_translation('ipfilterrulesite_visit'); ?></option>
                <option value="2"><?= $this->get_translation('ipfilterrulesite_admin'); ?></option>
            </select>
            <?= $this->theme->get_button(array(
                'title' => $this->get_translation('verify_ipaddress'),
                'url'   => 'javascript:SecurityTools.check_ipAddress();',
            )); ?>
            <span class="eContent2" id="IPAddressCheckResult"></span>
        </div>

        <?= $this->ipFilterRuleList->display('head'); ?>
        <?= $this->ipFilterRuleList->display('list'); ?>
    </div>
<?php endif; ?>

<?php if ($this->config->vars['backup']) : ?>
    <div id="itemBackup" style="display:<?= $this->tabBuilder->get_tabDisplay('Backup'); ?>;" class="adminContentPanel">
        <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
            <tr>
                <td class="eTitle3" colspan="3">
                    <?= $this->get_translation('backup_configuration'); ?>
                </td>
            </tr>

            <tr>
                <td class="eTableLine1 eContent2">
                    <?= $this->get_translation('backup_method'); ?>
                </td>
                <td class="eTableLine1 eContent1">
                    <?= $this->get_translation('backup_method_'.$this->config->vars['backup_method']); ?>
                </td>
            </tr>

            <tr>
                <td class="eTableLine0 eContent2">
                    <?= $this->get_translation('backup_compression'); ?>
                </td>
                <td class="eTableLine0 eContent1">
                    <?= $this->get_translation('backup_compression_'.$this->config->vars['backup_compression']); ?>
                </td>
            </tr>

            <tr>
                <td class="eTableLine1 eContent2">
                    <?= $this->get_translation('backup_type'); ?>
                </td>
                <td class="eTableLine1 eContent1">
                    <?= $this->get_translation('backup_type_'.$this->config->vars['backup_type']); ?>
                </td>
            </tr>

            <tr>
                <td class="eTableLine0 eContent2">
                    <?= $this->get_translation('backup_temp'); ?>
                </td>
                <td class="eTableLine0 eContent1">
                    <?= $this->config->vars['backup_temp'] == '' ? $this->get_translation('backup_systempfolder') : $this->config->vars['backup_temp'] ?>
                </td>
            </tr>

            <tr>
                <td class="eTableLine1 eContent2">
                    <?= $this->get_translation('backup_nextdate'); ?>
                </td>
                <td class="eTableLine1 eContent1">
                    <?php if ($this->config->vars['backup_nextdate'] == 0) : ?>
                        --
                    <?php else : ?>
                        <?= date_displayShortDayDate($this->config->vars['backup_nextdate']); ?>
                    <?php endif; ?>
                </td>
            </tr>

            <tr>
                <td class="" colspan="3">
                    &nbsp;
                </td>
            </tr>

            <tr>
                <td class="eTableLine1" colspan="2">
                    <?= $this->theme->get_button($this->get_translation('backup_modify'), $camyks->get_adminLink($this->name, array('mode'=>'edit_backupconfig'))); ?>
                    &nbsp;
                    <?= $this->theme->get_button($this->get_translation('backup_newbackup'), $camyks->get_adminLink($this->name, array('mode'=>'edit_newbackupfile'))); ?>
                </td>
            </tr>
        </table>

        <div style="clear:both">
            &nbsp;
        </div>

        <table cellspacing="0" cellpadding="0" border="0" style="width:100%">
            <tr>
                <td class="eTitle3" colspan="6">
                    <?= $this->get_translation('backup_files'); ?>
                </td>
            </tr>

            <?php if (count ($this->backupfiles) > 0) : ?>
            <tr>
                <td class="eTableHeader">
                   &nbsp;
                </td>
                <td class="eTableHeader">
                    <?= $camyks->get_translation('date'); ?>
                </td>
                <td class="eTableHeader">
                    <?= $camyks->get_translation('type'); ?>
                </td>
                <td class="eTableHeader">
                    <?= $this->get_translation('backup_size'); ?>
                </td>
                <td class="eTableHeader" style="width:12px;">
                    &nbsp;
                </td>
                <td class="eTableHeader" style="width:12px;">
                    &nbsp;
                </td>
            </tr>
            <?php $alt=0; ?>
            <?php foreach ($this->backupfiles as $backupfile) : ?>
                <tr>
                    <td class="eTableLine<?= $alt?> eContent1">
                        &nbsp;
                    </td>
                    <td class="eTableLine<?= $alt?> eContent1">
                        <?= date_displayShortDayDateHour($backupfile->vars['ndate']); ?>
                    </td>
                    <td class="eTableLine<?= $alt?> eContent1">
                        <?= $this->get_translation('backup_type_'.$backupfile->vars['type']); ?>
                    </td>
                    <td class="eTableLine<?= $alt?> eContent1">
                        <?= $backupfile->get_fileSize(); ?>
                    </td>
                    <td class="eTableLine<?= $alt?> eContent1">
                        <a href="<?= $this->get_varFileUrl('backups/'.$backupfile->vars['name']); ?>">
                            <img src="<?= $file; ?>" border="0"
                                alt="<?= $this->get_translation('backup_download'); ?>"
                                title="<?= $this->get_translation('backup_download'); ?>"
                                onmouseover="this.src='<?= $file_; ?>';" onmouseout="this.src='<?= $file; ?>';" />
                        </a>
                    </td>
                    <td class="eTableLine<?= $alt?> eContent1">
                        <a href="javascript:admin_securitytools_deleteBackUp(<?= $backupfile->id; ?>);">
                            <img src="<?= $del?>" border="0"
                                alt="<?= $this->get_translation('backup_delete'); ?>"
                                title="<?= $this->get_translation('backup_delete'); ?>"
                                onmouseover="this.src='<?= $del_; ?>';" onmouseout="this.src='<?= $del; ?>';" />
                        </a>
                    </td>
                </tr>

                <?php $alt=abs($alt-1); ?>
            <?php endforeach; ?>
            <?php else : ?>
            <tr>
                <td class="eTableline0 eContent1" colspan="2">
                    <?= $this->get_translation('backup_nofile'); ?>
                </td>
            </tr>
            <?php endif; ?>
        </table>
    </div>
<?php endif; ?>

<?php if ($this->help) : ?>
    <div id="itemhelp" style="display:none;" class="adminContentPanel">
        <?= $this->display_help(); ?>
    </div>
<?php endif; ?>

<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>

<?php
/**
 * @endcond Exclude
 */
?>
