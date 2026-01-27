<?php
/**
 * @brief AdvancedSMTPSettings input, edit configuration layout.
 * @details Plugin / Input Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Jan 2026
 * @date Modification: Jan 2026
 * @copyright 2026 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $camyks->theme->get_boxContent2Header(); ?>
<div class="adminContentPanel">
    <table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td colspan="4" class="eTableHeader">
                <?= $this->get_translation('formtitle_pluginparams'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2" style="width:160px;">
                <?= $this->get_translation('formitem_execution'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->form->display_selectInput(array('name'=>'Plugin_Insertion', 'values'=>$this->config->get_PluginInsertionList())); ?>
            </td>
            <td class="eTableLine0 eContent2" style="width:160px;">
                <?= $this->get_translation('formitem_emaillibrary'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->form->display_selectInput(array('name'=>'Plugin_EmailLibrary', 'values'=>$this->config->get_PluginEmailLibraryList())); ?>
            </td>
        </tr>

        <tr>
            <td colspan="4" class="eTableLine0">
                &nbsp;
            </td>
        </tr>

        <tr>
            <td colspan="4" class="eTableHeader">
                <?= $this->get_translation('formtitle_smtpparams'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_host'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->form->display_textInput(array('name'=>'SMTP_Host')); ?>
            </td>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_port'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->form->display_numberInput(array('name'=>'SMTP_Port')); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_secure'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->form->display_selectInput(array('name'=>'SMTP_Secure', 'values'=>$this->config->get_SMTPSecureList())); ?>
            </td>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_authentication'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->form->display_selectInput(array('name'=>'SMTP_Auth', 'values'=>$this->config->get_SMTPAuthList(), 'onchange'=>'AdvancedSMTPSettingsConfigurationEditor.check_SMTPAuthValue();')); ?>
            </td>
        </tr>
    </table>
    <div id="AuthBasic" style="display:none;">
    <table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td colspan="4" class="eTableLine0">
                &nbsp;
            </td>
        </tr>

        <tr>
            <td colspan="4" class="eTableHeader">
                <?= $this->get_translation('formtitle_basicauthenticationparams'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2" style="width:160px;">
                <?= $this->get_translation('formitem_username'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->form->display_textInput(array('name'=>'AuthBasic_UserName')); ?>
            </td>
            <td class="eTableLine0 eContent2" style="width:160px;">
                <?= $this->get_translation('formitem_password'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->form->display_textInput(array('name'=>'AuthBasic_Password')); ?>
            </td>
        </tr>
    </table>
    </div>

    <div id="AuthXOAUTH2" style="display:none;">
        <table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td colspan="4" class="eTableLine0">
                &nbsp;
            </td>
        </tr>

        <tr>
            <td colspan="4" class="eTableHeader">
                <?= $this->get_translation('formtitle_xoauth2authenticationparams'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2" style="width:160px;">
                <?= $this->get_translation('formitem_provider'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->form->display_selectInput(array('name'=>'AuthProvider', 'values'=>$this->config->get_SMTPAuthProviderList())); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_email'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->form->display_textInput(array('name'=>'AuthProvider_Email', 'maxlength'=>'255', 'class'=>'vlinputs')); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_clientid'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->form->display_textInput(array('name'=>'AuthProvider_ClientId', 'maxlength'=>'255', 'class'=>'vlinputs')); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_tenantid'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->form->display_textInput(array('name'=>'AuthProvider_TenantId', 'maxlength'=>'255', 'class'=>'vlinputs')); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_clientsecret'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->form->display_textInput(array('name'=>'AuthProvider_ClientSecret', 'maxlength'=>'255', 'class'=>'vlinputs')); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_refreshtoken'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->form->display_textAreaInput(array('name'=>'AuthProvider_RefreshToken')); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_refreshtokenexpiracydate'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->form->display_dateInput(array('name'=>'AuthProvider_RefreshTokenExpiracyDate', 'objects'=>array('day','month', 'year'), 'buttons'=>array())); ?>
            </td>
        </tr>
    </table>
    </div>
</div>
<?= $camyks->theme->get_boxContent2Footer(); ?>
