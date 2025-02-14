<?php
/**
 * @brief SpamChecker input, edit configuration layout.
 * @details Plugin / Input layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jun 2021
 * @date Modification: Feb 2025
 * @copyright 2021 - 2025 CaMykS Team
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
                <?= $this->get_translation('formtitle_params'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_enablelogs'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->form->display_selectInput(array('name'=>'enableLogs', 'class'=>'sinputs', 'values'=>$this->config->get_enableLogsList())); ?>
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
                <?= $this->form->display_textInput(array('name'=>'isProbablySpamScore', 'class'=>'sinputs')); ?>
            </td>
            <td class="eTableLine0 eContent2" style="width:150px;">
                <?= $this->get_translation('formitem_markedasspamfrom'); ?>
            </td>
            <td class="eTableLine0 eContent1" style="width:230px;">
                <?= $this->form->display_textInput(array('name'=>'isSpamScore', 'class'=>'sinputs')); ?>
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
                <?= $this->form->display_checkboxInput(array('name'=>'checkSimilarNamesEnabled', 'value'=>true, 'labelClass'=>'eContent2', 'label'=>$this->get_translation('formitem_checksimilarnames'), 'onchange'=>'SpamCheckerConfig.check_linearRuleIsEnabled(\'SimilarNames\');')); ?>
            </td>
            <td class="eTableLine0">
                <?= $this->form->display_textInput(array('name'=>'checkSimilarNamesScore', 'class'=>'sinputs')); ?>
            </td>
        </tr>

        <tr>
            <td colspan="3" class="eTableLine0">
                <?= $this->form->display_checkboxInput(array('name'=>'checkRandomNamesEnabled', 'value'=>true, 'labelClass'=>'eContent2', 'label'=>$this->get_translation('formitem_checkrandomnames'), 'onchange'=>'SpamCheckerConfig.check_linearRuleIsEnabled(\'RandomNames\');')); ?>
            </td>
            <td class="eTableLine0">
                <?= $this->form->display_textInput(array('name'=>'checkRandomNamesScore', 'class'=>'sinputs')); ?>
            </td>
        </tr>

        <tr>
            <td colspan="4" class="eTableLine1">
                <?= $this->form->display_checkboxInput(array('name'=>'checkEmailEnabled', 'value'=>true, 'labelClass'=>'eContent2', 'label'=>$this->get_translation('formitem_checkemail'), 'onchange'=>'SpamCheckerConfig.check_blockRuleIsEnabled(\'Email\');')); ?>

                <div id="checkEmailRuleList" style="display:none;">
                    <?php if (count($this->get_configValue('checkEmailRules')) == 0) : ?>
                        <div style="display:flex; margin:4px 0 4px 40px;">
                            <div style="flex:1;">
                                <?= $this->form->display_textInput(array('name'=>'checkEmailRulesValues[]', 'default'=>'', 'class'=>'linputs', 'onfocus'=>'SpamCheckerConfig.check_blockRuleInsert(\'Email\', this);', 'onblur'=>'SpamCheckerConfig.check_blockRuleRemove(\'Email\', this);')); ?>
                            </div>
                            <div style="min-width:215px;">
                                <?= $this->form->display_textInput(array('name'=>'checkEmailRulesScores[]', 'default'=>0, 'class'=>'sinputs')); ?>
                            </div>
                        </div>
                    <?php else : ?>
                        <?php foreach ($this->get_configValue('checkEmailRules') as $rule) : ?>
                        <div style="display:flex; margin:4px 0 4px 40px;">
                            <div style="flex:1;">
                                <?= $this->form->display_textInput(array('name'=>'checkEmailRulesValues[]', 'default'=>$rule['rule'], 'class'=>'linputs', 'onfocus'=>'SpamCheckerConfig.check_blockRuleInsert(\'Email\', this);', 'onblur'=>'SpamCheckerConfig.check_blockRuleRemove(\'Email\', this);')); ?>
                            </div>
                            <div style="min-width:215px;">
                                <?= $this->form->display_textInput(array('name'=>'checkEmailRulesScores[]', 'default'=>$rule['score'], 'class'=>'sinputs')); ?>
                            </div>
                        </div>
                        <?php endforeach; ?>
                    <?php endif; ?>
                </div>
            </td>
        </tr>

        <tr>
            <td colspan="4" class="eTableLine0">
                <?= $this->form->display_checkboxInput(array('name'=>'checkCompanyEnabled', 'value'=>true, 'labelClass'=>'eContent2', 'label'=>$this->get_translation('formitem_checkcompany'), 'onchange'=>'SpamCheckerConfig.check_blockRuleIsEnabled(\'Company\');')); ?>

                <div id="checkCompanyRuleList" style="display:none;">
                    <?php if (count($this->get_configValue('checkCompanyRules')) == 0) : ?>
                        <div style="display:flex; margin:4px 0 4px 40px;">
                            <div style="flex:1;">
                                <?= $this->form->display_textInput(array('name'=>'checkCompanyRulesValues[]', 'default'=>'', 'class'=>'linputs', 'onfocus'=>'SpamCheckerConfig.check_blockRuleInsert(\'Company\', this);', 'onblur'=>'SpamCheckerConfig.check_blockRuleRemove(\'Company\', this);')); ?>
                            </div>
                            <div style="min-width:215px;">
                                <?= $this->form->display_textInput(array('name'=>'checkCompanyRulesScores[]', 'default'=>0, 'class'=>'sinputs')); ?>
                            </div>
                        </div>
                    <?php else : ?>
                        <?php foreach ($this->get_configValue('checkCompanyRules') as $rule) : ?>
                        <div style="display:flex; margin:4px 0 4px 40px;">
                            <div style="flex:1;">
                                <?= $this->form->display_textInput(array('name'=>'checkCompanyRulesValues[]', 'default'=>$rule['rule'], 'class'=>'linputs', 'onfocus'=>'SpamCheckerConfig.check_blockRuleInsert(\'Company\', this);', 'onblur'=>'SpamCheckerConfig.check_blockRuleRemove(\'Company\', this);')); ?>
                            </div>
                            <div style="min-width:215px;">
                                <?= $this->form->display_textInput(array('name'=>'checkCompanyRulesScores[]', 'default'=>$rule['score'], 'class'=>'sinputs')); ?>
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
                <?= $this->form->display_checkboxInput(array('name'=>'checkHTMLEnabled', 'value'=>true, 'labelClass'=>'eContent2', 'label'=>$this->get_translation('formitem_checkhtml'), 'onchange'=>'SpamCheckerConfig.check_linearRuleIsEnabled(\'HTML\');')); ?>
            </td>
            <td class="eTableLine0">
                <?= $this->form->display_textInput(array('name'=>'checkHTMLScore', 'class'=>'sinputs')); ?>
            </td>
        </tr>

        <tr>
            <td colspan="3" class="eTableLine1">
                <?= $this->form->display_checkboxInput(array('name'=>'checkJavascriptEnabled', 'value'=>true, 'labelClass'=>'eContent2', 'label'=>$this->get_translation('formitem_checkjavascript'), 'onchange'=>'SpamCheckerConfig.check_linearRuleIsEnabled(\'Javascript\');')); ?>
            </td>
            <td class="eTableLine1">
                <?= $this->form->display_textInput(array('name'=>'checkJavascriptScore', 'class'=>'sinputs')); ?>
            </td>
        </tr>

        <tr>
            <td colspan="4" class="eTableLine0">
                <?= $this->form->display_checkboxInput(array('name'=>'checkWordEnabled', 'value'=>true, 'labelClass'=>'eContent2', 'label'=>$this->get_translation('formitem_checkword'), 'onchange'=>'SpamCheckerConfig.check_blockRuleIsEnabled(\'Word\');')); ?>

                <div id="checkWordRuleList" style="display:none;">
                    <?php if (count($this->get_configValue('checkWordRules')) == 0) : ?>
                        <div style="display:flex; margin:4px 0 4px 40px;">
                            <div style="flex:1;">
                                <?= $this->form->display_textInput(array('name'=>'checkWordRulesValues[]', 'default'=>'', 'class'=>'linputs', 'onfocus'=>'SpamCheckerConfig.check_blockRuleInsert(\'Word\', this);', 'onblur'=>'SpamCheckerConfig.check_blockRuleRemove(\'Word\', this);')); ?>
                            </div>
                            <div style="min-width:215px;">
                                <?= $this->form->display_textInput(array('name'=>'checkWordRulesScores[]', 'default'=>0, 'class'=>'sinputs')); ?>
                            </div>
                        </div>
                    <?php else : ?>
                        <?php foreach ($this->get_configValue('checkWordRules') as $rule) : ?>
                        <div style="display:flex; margin:4px 0 4px 40px;">
                            <div style="flex:1;">
                                <?= $this->form->display_textInput(array('name'=>'checkWordRulesValues[]', 'default'=>$rule['rule'], 'class'=>'linputs', 'onfocus'=>'SpamCheckerConfig.check_blockRuleInsert(\'Word\', this);', 'onblur'=>'SpamCheckerConfig.check_blockRuleRemove(\'Word\', this);')); ?>
                            </div>
                            <div style="min-width:215px;">
                                <?= $this->form->display_textInput(array('name'=>'checkWordRulesScores[]', 'default'=>$rule['score'], 'class'=>'sinputs')); ?>
                            </div>
                        </div>
                        <?php endforeach; ?>
                    <?php endif; ?>
                </div>
            </td>
        </tr>

        <tr>
            <td colspan="4" class="eTableLine1">
                <?= $this->form->display_checkboxInput(array('name'=>'checkLanguageScriptEnabled', 'value'=>true, 'labelClass'=>'eContent2', 'label'=>$this->get_translation('formitem_checklanguagescript'), 'onchange'=>'SpamCheckerConfig.check_blockRuleIsEnabled(\'LanguageScript\');')); ?>

                <div id="checkLanguageScriptRuleList" style="display:none;">
                    <?php if (count($this->get_configValue('checkLanguageScriptRules')) > 0) : ?>
                        <?php foreach ($this->get_configValue('checkLanguageScriptRules') as $rule) : ?>
                        <div style="display:flex; margin:4px 0 4px 40px;">
                            <div style="flex:1;">
                                <?= $this->form->display_selectInput(array('name'=>'checkLanguageScriptRulesValues[]', 'default'=>$rule['rule'], 'values'=>$this->scriptList, 'class'=>'linputs', 'hasEmptyFirstOption'=>$this->get_translation('nolanguagescript'), 'onchange'=>'SpamCheckerConfig.check_blockRuleSelectChange(\'LanguageScript\', this);')); ?>
                            </div>
                            <div style="min-width:215px;">
                                <?= $this->form->display_textInput(array('name'=>'checkLanguageScriptRulesScores[]', 'default'=>$rule['score'], 'class'=>'sinputs')); ?>
                            </div>
                        </div>
                        <?php endforeach; ?>
                    <?php endif; ?>
                    <div style="display:flex; margin:4px 0 4px 40px;">
                        <div style="flex:1;">
                                <?= $this->form->display_selectInput(array('name'=>'checkLanguageScriptRulesValues[]', 'default'=>'', 'values'=>$this->scriptList, 'class'=>'linputs', 'hasEmptyFirstOption'=>$this->get_translation('nolanguagescript'), 'onchange'=>'SpamCheckerConfig.check_blockRuleSelectChange(\'LanguageScript\', this);')); ?>
                        </div>
                        <div style="min-width:215px;">
                            <?= $this->form->display_textInput(array('name'=>'checkLanguageScriptRulesScores[]', 'default'=>0, 'class'=>'sinputs')); ?>
                        </div>
                    </div>
                </div>
            </td>
        </tr>

        <tr>
            <td colspan="4" class="eTableLine0">
                <?= $this->form->display_checkboxInput(array('name'=>'checkLinkEnabled', 'value'=>true, 'labelClass'=>'eContent2', 'label'=>$this->get_translation('formitem_checklink'), 'onchange'=>'SpamCheckerConfig.check_blockRuleIsEnabled(\'Link\');')); ?>

                <div id="checkLinkRuleList" style="display:none; margin:4px 0 4px 40px;">
                    <table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
                        <tr>
                            <td class="eTableLine0 eContent2">
                                <?= $this->get_translation('formitem_checkeachlink'); ?>
                            </td>
                            <td class="eTableLine0 eContent2" style="width:220px;">
                                <?= $this->form->display_textInput(array('name'=>'checkLinkScore', 'class'=>'sinputs')); ?>
                            </td>
                        </tr>
                        <tr>
                            <td class="eTableLine0 eContent2">
                                <?= $this->get_translation('formitem_checksinglelink'); ?>
                            </td>
                            <td class="eTableLine0 eContent2" style="width:220px;">
                                <?= $this->form->display_textInput(array('name'=>'checkLinkWithoutContentScore', 'class'=>'sinputs')); ?>
                            </td>
                        </tr>
                    </table>
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
                <?= $this->form->display_checkboxInput(array('name'=>'checkCountryEnabled', 'value'=>true, 'labelClass'=>'eContent2', 'disabled'=> ($IPGeolocator === false), 'label'=>$this->get_translation('formitem_checkcountry'), 'onchange'=>'SpamCheckerConfig.check_blockRuleIsEnabled(\'Country\');')); ?>
                <span class="eContent3">(<?= $this->get_translation('formitem_checkcountrydesc'); ?>)</span>

                <div id="checkCountryRuleList" style="display:none;">
                    <?php if (count($this->get_configValue('checkCountryRules')) > 0) : ?>
                        <?php foreach ($this->get_configValue('checkCountryRules') as $rule) : ?>
                        <div style="display:flex; margin:4px 0 4px 40px;">
                            <div style="flex:1;">
                                <?= $this->form->display_countrySelectInput(array('name'=>'checkCountryRulesValues[]', 'default'=>$rule['rule'], 'class'=>'linputs', 'hasEmptyFirstOption'=>$this->get_translation('nocountry'), 'onchange'=>'SpamCheckerConfig.check_blockRuleSelectChange(\'Country\', this);')); ?>
                            </div>
                            <div style="min-width:215px;">
                                <?= $this->form->display_textInput(array('name'=>'checkCountryRulesScores[]', 'default'=>$rule['score'], 'class'=>'sinputs')); ?>
                            </div>
                        </div>
                        <?php endforeach; ?>
                    <?php endif; ?>
                    <div style="display:flex; margin:4px 0 4px 40px;">
                        <div style="flex:1;">
                            <?= $this->form->display_countrySelectInput(array('name'=>'checkCountryRulesValues[]', 'default'=>'', 'class'=>'linputs', 'hasEmptyFirstOption'=>$this->get_translation('nocountry'), 'onchange'=>'SpamCheckerConfig.check_blockRuleSelectChange(\'Country\', this);')); ?>
                        </div>
                        <div style="min-width:215px;">
                            <?= $this->form->display_textInput(array('name'=>'checkCountryRulesScores[]', 'default'=>0, 'class'=>'sinputs')); ?>
                        </div>
                    </div>
                </div>
            </td>
        </tr>

        <tr>
            <td colspan="4" class="eTableLine1">
                <?= $this->form->display_checkboxInput(array('name'=>'checkHostnameEnabled', 'value'=>true, 'labelClass'=>'eContent2', 'label'=>$this->get_translation('formitem_checkhostname'), 'onchange'=>'SpamCheckerConfig.check_blockRuleIsEnabled(\'Hostname\');')); ?>

                <div id="checkHostnameRuleList" style="display:none;">
                    <?php if (count($this->get_configValue('checkHostnameRules')) == 0) : ?>
                        <div style="display:flex; margin:4px 0 4px 40px;">
                            <div style="flex:1;">
                                <?= $this->form->display_textInput(array('name'=>'checkHostnameRulesValues[]', 'default'=>'', 'class'=>'linputs', 'onfocus'=>'SpamCheckerConfig.check_blockRuleInsert(\'Hostname\', this);', 'onblur'=>'SpamCheckerConfig.check_blockRuleRemove(\'Hostname\', this);')); ?>
                            </div>
                            <div style="min-width:215px;">
                                <?= $this->form->display_textInput(array('name'=>'checkHostnameRulesScores[]', 'default'=>0, 'class'=>'sinputs')); ?>
                            </div>
                        </div>
                    <?php else : ?>
                        <?php foreach ($this->get_configValue('checkHostnameRules') as $rule) : ?>
                        <div style="display:flex; margin:4px 0 4px 40px;">
                            <div style="flex:1;">
                                <?= $this->form->display_textInput(array('name'=>'checkHostnameRulesValues[]', 'default'=>$rule['rule'], 'class'=>'linputs', 'onfocus'=>'SpamCheckerConfig.check_blockRuleInsert(\'Hostname\', this);', 'onblur'=>'SpamCheckerConfig.check_blockRuleRemove(\'Hostname\', this);')); ?>
                            </div>
                            <div style="min-width:215px;">
                                <?= $this->form->display_textInput(array('name'=>'checkHostnameRulesScores[]', 'default'=>$rule['score'], 'class'=>'sinputs')); ?>
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
