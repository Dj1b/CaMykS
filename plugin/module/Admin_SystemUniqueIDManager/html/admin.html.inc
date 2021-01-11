<?php
/**
 * @brief Admin_SystemUniqueIDManager Module admin main layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Jan 2015
 * @date Modification: Jan 2021
 * @copyright 2015 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title); ?>
<?= $this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<div id="itemSummary" style="display:<?= $this->tabBuilder->get_tabDisplay('Summary'); ?>;" class="adminContentPanel">
    <table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableHeader" colspan="3">
                <?= $this->get_translation('formtitle_configuration'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableSubHeader" colspan="3">
                <?= $this->get_translation('formtitle_generating'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2" style="width:150px;">
                <?= $this->get_translation('formitem_method'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                  <?= $this->generatingMethodList[$this->config->vars['generating_method']]; ?>
            </td>
            <td class="eTableLine0" rowspan="3" style="vertical-align:top; width:170px;">
                <?= $this->theme->get_button(array(
                    'title' => $camyks->get_translation('modify'),
                    'url'   => $this->get_adminLink(array('mode'=>'edit_config')),
                )); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_keylength'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->config->vars['generating_length']; ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_maxattempts'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->config->vars['generating_maxAttempts']; ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0" colspan="3">
                &nbsp;
            </td>
        </tr>

        <tr>
            <td class="eTableHeader" colspan="3">
                <?= $this->get_translation('formtitle_summary'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2"">
                <?= $this->get_translation('formitem_generatedkeys'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                  <?= $this->totalGeneratedKeys; ?>
            </td>
            <td class="eTableLine0" rowspan="2" style="vertical-align:top; width:170px;">
                  <?php /*
                  <?= $this->theme->get_button(array('title'=>$this->get_translation('generate_freekeys'),
                    'url'=>$this->get_adminLink(array('mode'=>'generate_keys')))); ?>
                */ ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_freegeneratedkeys'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->freeGeneratedKeys; ?>
            </td>
        </tr>
    </table>
</div>

<div id="itemKeys" style="display:<?= $this->tabBuilder->get_tabDisplay('Keys'); ?>;" class="adminContentPanel">
    <?= $this->keyList->display('head'); ?>
    <?= $this->keyList->display('list'); ?>
</div>

<?php if ($this->help != null) : ?>
    <div id="itemhelp" style="display:<?= $this->tabBuilder->get_tabDisplay('help'); ?>;" class="adminContentPanel">
        <?php $this->display_help(); ?>
    </div>
<?php endif; ?>

<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
