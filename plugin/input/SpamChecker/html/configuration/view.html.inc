<?php
/**
 * @brief SpamChecker Input view configuration layout
 * @details Plugin / Input layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Jun 2021
 * @date Modification: Jun 2021
 * @copyright 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
$this->form = new HTMLForm('temp', '#');
$this->form->set_object($this->config);
?>
<?= $camyks->theme->get_boxContent2Header(); ?>
<div class="adminContentPanel">
    <table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td colspan="4" class="eTableHeader">
                <?= $this->get_translation('formtitle_params'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_enablelogs'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->config->get_enableLogsTitle(); ?>
            </td>
            <td class="eTableLine0 eContent1" colspan="2">
                &nbsp;
            </td>

            <?php /*
            <td class="eTableLine0 eContent2" style="width:175px;">
                <?= $this->get_translation('formitem_autobanipaddresses'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->form->display_booleanSelectInput(array('name'=>'autoBanIpAddress', 'class'=>'sinputs')); ?>
            </td>
            */ ?>
        </tr>

        <tr>
            <td colspan="4" class="eTableLine0">
                &nbsp;
            </td>
        </tr>

        <tr>
            <td colspan="4" class="eTableHeader">
                <?= $this->get_translation('formtitle_spamscores'); ?>
            </td>
        </tr>

        <tr>
            <td colspan="4" class="eTableLine0 eContent3">
                <?= $this->get_translation('formdesc_spamscores'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2" style="width:150px;">
                <?= $this->get_translation('formitem_markedasprobablyspamfrom'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->config->get_value('isProbablySpamScore'); ?>
            </td>
            <td class="eTableLine0 eContent2" style="width:150px;">
                <?= $this->get_translation('formitem_markedasspamfrom'); ?>
            </td>
            <td class="eTableLine0 eContent1" style="width:230px;">
                <?= $this->config->get_value('isSpamScore'); ?>
            </td>
        </tr>

        <tr>
            <td colspan="4" class="eTableLine0">
                &nbsp;
            </td>
        </tr>

        <tr>
            <td colspan="4" class="eTableHeader">
                <?= $this->get_translation('formtitle_metadatarules'); ?>
            </td>
        </tr>
        <tr>
            <td colspan="3" class="eTableSubHeader">
                <?= $this->get_translation('formitem_enable'); ?>
            </td>
            <td class="eTableSubHeader">
                <?= $this->get_translation('formitem_score'); ?>
            </td>
        </tr>

        <tr>
            <td colspan="3" class="eTableLine0">
                <?= $this->form->display_checkboxInput(array('name'=>'checkSimilarNamesEnabled', 'disabled'=>true, 'value'=>true, 'labelClass'=>'eContent2', 'label'=>$this->get_translation('formitem_checksimilarnames'))); ?>
            </td>
            <td class="eTableLine0">
                <?php if ($this->get_configValue('checkSimilarNamesEnabled') == 1) : ?>
                    <?= $this->config->get_value('checkSimilarNamesScore'); ?>
                <?php else : ?>
                    &nbsp;
                <?php endif; ?>
            </td>
        </tr>

        <tr>
            <td colspan="4" class="eTableLine1">
                <?= $this->form->display_checkboxInput(array('name'=>'checkEmailEnabled', 'disabled'=>true, 'value'=>true, 'labelClass'=>'eContent2', 'label'=>$this->get_translation('formitem_checkemail'))); ?>

                <div id="checkEmailRuleList">
                    <?php if ($this->get_configValue('checkEmailEnabled') == 1 and count($this->get_configValue('checkEmailRules')) > 0) : ?>
                        <?php foreach ($this->get_configValue('checkEmailRules') as $rule) : ?>
                        <div style="display:flex; margin:4px 0 4px 40px;">
                            <div style="flex:1;">
                                <?= $rule['rule']; ?>
                            </div>
                            <div style="min-width:215px;">
                                <?= $rule['score']; ?>
                            </div>
                        </div>
                        <?php endforeach; ?>
                    <?php endif; ?>
                </div>
            </td>
        </tr>

        <tr>
            <td colspan="4" class="eTableLine0">
                <?= $this->form->display_checkboxInput(array('name'=>'checkCompanyEnabled', 'disabled'=>true, 'value'=>true, 'labelClass'=>'eContent2', 'label'=>$this->get_translation('formitem_checkcompany'))); ?>

                <div id="checkCompanyRuleList">
                    <?php if ($this->get_configValue('checkCompanyEnabled') == 1 and count($this->get_configValue('checkCompanyRules')) > 0) : ?>
                        <?php foreach ($this->get_configValue('checkCompanyRules') as $rule) : ?>
                        <div style="display:flex; margin:4px 0 4px 40px;">
                            <div style="flex:1;">
                                <?= $rule['rule']; ?>
                            </div>
                            <div style="min-width:215px;">
                                <?= $rule['score']; ?>
                            </div>
                        </div>
                        <?php endforeach; ?>
                    <?php endif; ?>
                </div>
            </td>
        </tr>

        <tr>
            <td colspan="4" class="eTableLine0">
                &nbsp;
            </td>
        </tr>

        <tr>
            <td colspan="4" class="eTableHeader">
                <?= $this->get_translation('formtitle_contentrules'); ?>
            </td>
        </tr>
        <tr>
            <td colspan="3" class="eTableSubHeader">
                <?= $this->get_translation('formitem_enable'); ?>
            </td>
            <td class="eTableSubHeader">
                <?= $this->get_translation('formitem_score'); ?>
            </td>
        </tr>


        <tr>
            <td colspan="3" class="eTableLine0">
                <?= $this->form->display_checkboxInput(array('name'=>'checkHTMLEnabled', 'disabled'=>true, 'value'=>true, 'labelClass'=>'eContent2', 'label'=>$this->get_translation('formitem_checkhtml'))); ?>
            </td>
            <td class="eTableLine0">
                <?php if ($this->get_configValue('checkHTMLEnabled') == 1) : ?>
                    <?= $this->get_configValue('checkHTMLScore'); ?>
                <?php else : ?>
                    &nbsp;
                <?php endif; ?>
            </td>
        </tr>

        <tr>
            <td colspan="3" class="eTableLine1">
                <?= $this->form->display_checkboxInput(array('name'=>'checkJavascriptEnabled', 'disabled'=>true, 'value'=>true, 'labelClass'=>'eContent2', 'label'=>$this->get_translation('formitem_checkjavascript'))); ?>
            </td>
            <td class="eTableLine1">
                <?php if ($this->get_configValue('checkJavascriptEnabled') == 1) : ?>
                    <?= $this->get_configValue('checkJavascriptScore'); ?>
                <?php else : ?>
                    &nbsp;
                <?php endif; ?>
            </td>
        </tr>

        <tr>
            <td colspan="4" class="eTableLine0">
                <?= $this->form->display_checkboxInput(array('name'=>'checkWordEnabled', 'disabled'=>true, 'value'=>true, 'labelClass'=>'eContent2', 'label'=>$this->get_translation('formitem_checkword'))); ?>

                <div id="checkWordRuleList">
                    <?php if ($this->get_configValue('checkWordEnabled') == 1 and count($this->get_configValue('checkWordRules')) > 0) : ?>
                        <?php foreach ($this->get_configValue('checkWordRules') as $rule) : ?>
                        <div style="display:flex; margin:4px 0 4px 40px;">
                            <div style="flex:1;">
                                <?= $rule['rule']; ?>
                            </div>
                            <div style="min-width:215px;">
                                <?= $rule['score']; ?>
                            </div>
                        </div>
                        <?php endforeach; ?>
                    <?php endif; ?>
                </div>
            </td>
        </tr>

        <tr>
            <td colspan="4" class="eTableLine1">
                <?= $this->form->display_checkboxInput(array('name'=>'checkLanguageScriptEnabled', 'disabled'=>true, 'value'=>true, 'labelClass'=>'eContent2', 'label'=>$this->get_translation('formitem_checklanguagescript'))); ?>

                <div id="checkLanguageScriptRuleList">
                    <?php if ($this->get_configValue('checkLanguageScriptEnabled') == 1 and count($this->get_configValue('checkLanguageScriptRules')) > 0) : ?>
                        <?php foreach ($this->get_configValue('checkLanguageScriptRules') as $rule) : ?>
                        <div style="display:flex; margin:4px 0 4px 40px;">
                            <div style="flex:1;">
                                <?= language_getScriptTitle($rule['rule']); ?>
                            </div>
                            <div style="min-width:215px;">
                                <?= $rule['score']; ?>
                            </div>
                        </div>
                        <?php endforeach; ?>
                    <?php endif; ?>
                </div>
            </td>
        </tr>

        <tr>
            <td colspan="4" class="eTableLine0">
                <?= $this->form->display_checkboxInput(array('name'=>'checkLinkEnabled', 'disabled'=>true, 'value'=>true, 'labelClass'=>'eContent2', 'label'=>$this->get_translation('formitem_checklink'))); ?>

                <?php if ($this->get_configValue('checkLinkEnabled') == 1) : ?>
                <div id="checkLinkRuleList" style="display:none; margin:4px 0 4px 40px;">
                    <table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
                        <tr>
                            <td class="eTableLine0 eContent2">
                                <?= $this->get_translation('formitem_checkeachlink'); ?>
                            </td>
                            <td class="eTableLine0 eContent2" style="width:220px;">
                                <?= $this->get_configValue('checkLinkScore'); ?>
                            </td>
                        </tr>
                        <tr>
                            <td class="eTableLine0 eContent2">
                                <?= $this->get_translation('formitem_checksinglelink'); ?>
                            </td>
                            <td class="eTableLine0 eContent2" style="width:220px;">
                                <?= $this->get_configValue('checkLinkWithoutContentScore'); ?>
                            </td>
                        </tr>
                    </table>
                </div>
                <?php endif; ?>
            </td>
        </tr>

        <tr>
            <td colspan="4" class="eTableLine0">
                &nbsp;
            </td>
        </tr>

        <tr>
            <td colspan="4" class="eTableHeader">
                <?= $this->get_translation('formtitle_originrules'); ?>
            </td>
        </tr>
        <tr>
            <td colspan="3" class="eTableSubHeader">
                <?= $this->get_translation('formitem_enable'); ?>
            </td>
            <td class="eTableSubHeader">
                <?= $this->get_translation('formitem_score'); ?>
            </td>
        </tr>

        <tr>
            <td colspan="4" class="eTableLine0">
                <?php $IPGeolocator = $camyks->get_input('IPGeolocator'); ?>
                <?= $this->form->display_checkboxInput(array('name'=>'checkCountryEnabled', 'disabled'=>true, 'value'=>true, 'labelClass'=>'eContent2', 'label'=>$this->get_translation('formitem_checkcountry'))); ?>
                <span class="eContent3">(<?= $this->get_translation('formitem_checkcountrydesc'); ?>)</span>

                <div id="checkCountryRuleList">
                    <?php if ($this->get_configValue('checkCountryEnabled') == 1 and $IPGeolocator !== false and count($this->get_configValue('checkCountryRules')) > 0) : ?>
                        <?php foreach ($this->get_configValue('checkCountryRules') as $rule) : ?>
                        <div style="display:flex; margin:4px 0 4px 40px;">
                            <div style="flex:1;">
                                <?= countries_getTranslation($rule['rule']); ?>
                            </div>
                            <div style="min-width:215px;">
                                <?= $rule['score']; ?>
                            </div>
                        </div>
                        <?php endforeach; ?>
                    <?php endif; ?>
                </div>
            </td>
        </tr>

        <tr>
            <td colspan="4" class="eTableLine1">
                <?= $this->form->display_checkboxInput(array('name'=>'checkHostnameEnabled', 'disabled'=>true, 'value'=>true, 'labelClass'=>'eContent2', 'label'=>$this->get_translation('formitem_checkhostname'))); ?>
                <div id="checkHostnameRuleList">
                    <?php if ($this->get_configValue('checkHostnameEnabled') == 1 and count($this->get_configValue('checkHostnameRules')) > 0) : ?>
                        <?php foreach ($this->get_configValue('checkHostnameRules') as $rule) : ?>
                        <div style="display:flex; margin:4px 0 4px 40px;">
                            <div style="flex:1;">
                                <?= $rule['rule']; ?>
                            </div>
                            <div style="min-width:215px;">
                                <?= $rule['score']; ?>
                            </div>
                        </div>
                        <?php endforeach; ?>
                    <?php endif; ?>
                </div>
            </td>
        </tr>

    </table>
</div>
<?= $camyks->theme->get_boxContent2Footer(); ?>
