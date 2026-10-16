<?php
/**
 * @brief TrustIndexCustomerReviews input, configuration view layout.
 * @details Plugin / Input Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Oct 2026
 * @date Modification: Oct 2026
 * @copyright 2026 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;
?>
<?= $camyks->theme->get_boxContent2Header(); ?>
<div class="adminContentPanel">
    <table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td colspan="2" class="eTableHeader">
                <?= $this->get_translation('formtitle_general'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2" style="width:180px;">
                <?= $this->get_translation('formitem_integrationmode'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->config->get_integrationModeTitle(); ?>
            </td>
        </tr>

        <?php if ($this->config->vars['integrationMode'] === 'loader') : ?>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_widgetid'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= htmlspecialchars($this->config->vars['widgetId']); ?>
            </td>
        </tr>
        <?php else : ?>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_rawcode'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <pre style="max-height:120px; overflow:auto; margin:0;"><?= htmlspecialchars($this->config->vars['rawCode']); ?></pre>
            </td>
        </tr>
        <?php endif; ?>

        <tr>
            <td colspan="2" class="eTableHeader">
                <?= $this->get_translation('formtitle_display'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2" style="width:180px;">
                <?= $this->get_translation('formitem_alignment'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->config->get_alignmentTitle(); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_containerclass'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= htmlspecialchars($this->config->vars['containerClass']); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_containerstyle'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= htmlspecialchars($this->config->vars['containerStyle']); ?>
            </td>
        </tr>

        <tr>
            <td colspan="2" class="eTableHeader">
                <?= $this->get_translation('formtitle_privacy'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2" style="width:180px;">
                <?= $this->get_translation('formitem_enablecookieconsent'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->config->get_enableCookieConsentTitle(); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_showconsentmessage'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->config->get_showConsentMessageTitle(); ?>
            </td>
        </tr>
    </table>
</div>
<?= $camyks->theme->get_boxContent2Footer(); ?>
<?php
/**
 * @endcond Exclude
 */
?>
