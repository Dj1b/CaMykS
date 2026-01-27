<?php
/**
 * @brief AdvancedSMTPSettings input, view configuration layout.
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
                <?= $this->config->get_PluginInsertionTitle(); ?>
            </td>
            <td class="eTableLine0 eContent2" style="width:160px;">
                <?= $this->get_translation('formitem_emaillibrary'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->config->get_PluginEmailLibraryTitle(); ?>
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
                <?= $this->config->get_value('SMTP_Host'); ?>
            </td>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_port'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->config->get_value('SMTP_Port'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_secure'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->config->get_SMTPSecureTitle(); ?>
            </td>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_authentication'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->config->get_SMTPAuthTitle(); ?>
            </td>
        </tr>
    </table>

    <?php if ($this->config->get_value('SMTP_Auth') == 'Basic') : ?>
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
                <?= $this->config->get_value('AuthBasic_UserName'); ?>
            </td>
            <td class="eTableLine0 eContent2" style="width:160px;">
                <?= $this->get_translation('formitem_password'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->config->get_value('AuthBasic_Password'); ?>
            </td>
        </tr>
    </table>
    <?php elseif ($this->config->get_value('SMTP_Auth') == 'XOAUTH2') : ?>
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
                <?= $this->config->get_SMTPAuthProviderTitle(); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_email'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->config->get_value('AuthProvider_Email'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_clientid'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->config->get_value('AuthProvider_ClientId'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_tenantid'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->config->get_value('AuthProvider_TenantId'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_clientsecret'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->config->get_value('AuthProvider_ClientSecret'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_refreshtoken'); ?>
            </td>
            <td class="eTableLine1 eContent1" style="word-break: break-all;">
                <?= $this->config->get_value('AuthProvider_RefreshToken'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_refreshtokenexpiracydate'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?php if ($this->config->get_value('AuthProvider_RefreshTokenExpiracyDate') < 3600) : ?>
                    --
                <?php else : ?>
                    <?= date_displayLongDate($this->config->get_value('AuthProvider_RefreshTokenExpiracyDate')); ?>
                <?php endif; ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                &nbsp;
            </td>
            <td class="eTableLine1 eContent1" style="word-break: break-all;">
                <?= $camyks->theme->get_button(array(
                    'title' => $this->get_translation('getnewtoken'),
                    'url'   => $this->config->get_newTokenRequestURL(),
                )); ?>
            </td>
        </tr>
    </table>
    <?php endif; ?>
</div>
<?= $camyks->theme->get_boxContent2Footer(); ?>
