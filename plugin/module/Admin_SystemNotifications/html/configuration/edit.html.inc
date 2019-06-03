<?php
/**
 * @brief Admin_SystemNotifications Module admin edit configuration sub layout
 * @details Plugin / Module layout
 * @file plugin/module/Admin_SystemNotifications/html/configuration/edit.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: May 2019
 * @date Modification: May 2019
 * @copyright 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/
global $camyks;

$width = 160;
?>
<?php if ($this->isConfig):?>

    <?= $camyks->theme->get_boxContent2Header(); ?>
    <div class="adminContentPanel">

<?php endif; ?>

<table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
    <tr>
        <td class="eTableHeader" colspan="2">
            <?= $this->get_translation('formtitle_module'); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0 eContent2" style="width:<?= $width; ?>px;">
            <?= $this->get_translation('formitem_mode'); ?>
        </td>
        <td class="eTableLine0 eContent1">
            <?= $this->editForm->display_selectInput(array('name'=>'module_mode', 'values'=>$this->moduleModeList, 'onchange'=>'ce.onModuleModeChange();')); ?>
        </td>
    </tr>
</table>

<div id="moduleCheckDelay" style="display:<?= $this->config->vars['module_mode'] == 1?'block':'none'; ?>">
    <table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableLine1 eContent2" style="width:<?= $width; ?>px;">
                <?= $this->get_translation('formitem_delay'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->editForm->display_textInput(array('name'=>'module_checkDelay', 'class'=>'vsinputs')); ?> <?= $this->get_translation('unit_minutes'); ?>
            </td>
        </tr>
    </table>
</div>

<table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
    <tr>
        <td    class="eTableLine0" colspan="2">
            &nbsp;
        </td>
    </tr>
    <tr>
        <td class="eTableHeader" colspan="2">
            <?= $this->get_translation('formtitle_access'); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0 eContent2" style="width:<?= $width; ?>px;">
            <?= $this->get_translation('formitem_status'); ?>
        </td>
        <td class="eTableLine0 eContent1">
            <?= $this->editForm->display_selectInput(array('name'=>'access_status', 'values'=>$this->accessStatusList)); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine1 eContent2">
            <?= $this->get_translation('formitem_authentication'); ?>
        </td>
        <td class="eTableLine1 eContent1">
            <?= $this->editForm->display_selectInput(array('name'=>'access_authentication', 'values'=>$this->accessAuthenticationList, 'onchange'=>'ce.onAuthenticationChange();')); ?>
        </td>
    </tr>
</table>

<div id="accessCredentials" style="display:<?= $this->config->vars['access_authentication'] == 1?'block':'none'; ?>">
    <table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableLine0 eContent2" style="width:<?= $width; ?>px;">
                <?= $this->get_translation('formitem_login'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->editForm->display_selectInput(array('name'=>'access_authLogin', 'values'=>$this->adminList)); ?>
            </td>
        </tr>
    </table>
</div>

<div id="accessAddressIP" style="display:<?= $this->config->vars['access_authentication'] == 2?'block':'none'; ?>">
    <table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableLine0 eContent2" style="width:<?= $width; ?>px;">
                <?= $this->get_translation('formitem_ipaddress'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->editForm->display_textInput(array('name'=>'access_authIP', 'placeholder'=>$this->get_translation('addressip_sameserver'))); ?>
            </td>
        </tr>
    </table>
</div>

<?php if ($this->isConfig):?>

    </div>
    <?= $camyks->theme->get_boxContent2Footer(); ?>

<?php endif; ?>
