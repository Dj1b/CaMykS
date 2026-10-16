<?php
/**
 * @brief TrustIndexCustomerReviews input, configuration edit layout.
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
                <?= $this->form->display_selectInput(array('name'=>'integrationMode', 'class'=>'inputs', 'values'=>$this->config->get_integrationModeList())); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_widgetid'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->form->display_textInput(array('name'=>'widgetId', 'class'=>'linputs', 'maxlength'=>128)); ?>
                <div class="eContent3" style="margin-top:4px; font-style:italic;">
                    <?= $this->get_translation('formdesc_widgetid'); ?>
                </div>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_rawcode'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->form->display_textAreaInput(array('name'=>'rawCode', 'class'=>'linputs', 'style'=>'width:95%; height:90px;')); ?>
                <div class="eContent3" style="margin-top:4px; font-style:italic;">
                    <?= $this->get_translation('formdesc_rawcode'); ?>
                </div>
            </td>
        </tr>

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
                <?= $this->form->display_selectInput(array('name'=>'alignment', 'class'=>'inputs', 'values'=>$this->config->get_alignmentList())); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_containerclass'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->form->display_textInput(array('name'=>'containerClass', 'class'=>'linputs', 'maxlength'=>64)); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_containerstyle'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->form->display_textInput(array('name'=>'containerStyle', 'class'=>'vlinputs', 'maxlength'=>255)); ?>
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
                <?= $this->form->display_booleanSelectInput(array('name'=>'enableCookieConsent')); ?>
                <div class="eContent3" style="margin-top:4px; font-style:italic;">
                    <?= $this->get_translation('formdesc_enablecookieconsent'); ?>
                </div>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_showconsentmessage'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->form->display_booleanSelectInput(array('name'=>'showConsentMessage')); ?>
                <div class="eContent3" style="margin-top:4px; font-style:italic;">
                    <?= $this->get_translation('formdesc_showconsentmessage'); ?>
                </div>
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
