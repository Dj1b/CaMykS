<?php
/**
 * @brief ExternalCustomerReviews Input edit configuration layout.
 * @details Plugin / Input layout
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

/* Load source list */
$sources = $this->config->get_sourceList();
?>
<?= $camyks->theme->get_boxContent2Header(); ?>
<div class="adminContentPanel">
    <table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td colspan="3" class="eTableHeader">
                <?= $this->get_translation('formtitle_params'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2" style="width:200px;">
                <?= $this->get_translation('formitem_stylesource'); ?>
            </td>
            <td class="eTableLine0 eContent1" colspan="2">
                <?= $this->form->display_selectInput(array('name'=>'styleSource', 'class'=>'inputs', 'values'=>$this->config->get_styleSourceList())); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_source'); ?>
            </td>
            <td class="eTableLine1 eContent1" colspan="2">
                <?= $this->form->display_selectInput(array('name'=>'source', 'class'=>'inputs', 'values'=>$this->config->get_sourceTitleList())); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_layout'); ?>
            </td>
            <td class="eTableLine0 eContent1" colspan="2">
                <?= $this->form->display_selectInput(array('name'=>'layout', 'class'=>'inputs', 'values'=>$this->config->get_layoutList())); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_showsummary'); ?>
            </td>
            <td class="eTableLine1 eContent1" colspan="2">
                <?= $this->form->display_selectInput(array('name'=>'showSummary', 'class'=>'inputs', 'values'=>$this->config->get_showSummaryList())); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_maxreviews'); ?>
            </td>
            <td class="eTableLine0 eContent1" colspan="2">
                <?= $this->form->display_textInput(array('name'=>'maxReviews', 'class'=>'sinputs', 'maxlength'=>3)); ?>
                <span class="eContent3">&nbsp;(0 = <?= $this->get_translation('maxreviews_all'); ?>)</span>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_minrating'); ?>
            </td>
            <td class="eTableLine1 eContent1" colspan="2">
                <?= $this->form->display_selectInput(array('name'=>'minRating', 'class'=>'inputs', 'values'=>$this->config->get_minRatingList())); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_cachettl'); ?>
            </td>
            <td class="eTableLine0 eContent1" colspan="2">
                <?= $this->form->display_textInput(array('name'=>'cacheTTL', 'class'=>'sinputs', 'maxlength'=>8)); ?>
                &nbsp;<?= $this->get_translation('formdesc_seconds'); ?>
            </td>
        </tr>

        <tr>
            <td colspan="3" class="eTableLine0">
                &nbsp;
            </td>
        </tr>

        <tr>
            <td colspan="3" class="eTableHeader">
                <?= $this->get_translation('formtitle_credentials'); ?>
            </td>
        </tr>

        <?php $lineAlt = 0; ?>
        <?php foreach ($sources as $sourceId => $sourceInfo) : ?>
            <tr>
                <td colspan="2" class="eTableSubHeader">
                    <?= $sourceInfo['Title']; ?>
                </td>
                <td class="eTableSubHeader" style="width:160px; text-align:right;">
                    <?php if ($sourceInfo['PortalURL'] != '') : ?>
                        <?= $camyks->theme->get_button(array(
                            'title'     => $this->get_translation('getcredentials'),
                            'url'       => $sourceInfo['PortalURL'],
                            'target'    => '_blank',
                        )); ?>
                    <?php endif; ?>
                </td>
            </tr>
            <?php foreach ($sourceInfo['Fields'] as $fieldName) : ?>
                <tr>
                    <td class="eTableLine<?= $lineAlt; ?> eContent2" style="width:200px;">
                        <?= $this->get_translation('formitem_'.$fieldName); ?>
                    </td>
                    <td class="eTableLine<?= $lineAlt; ?> eContent1" colspan="2">
                        <?= $this->form->display_textInput(array('name'=>$fieldName, 'class'=>'linputs', 'maxlength'=>255)); ?>
                    </td>
                </tr>
                <?php $lineAlt = 1 - $lineAlt; ?>
            <?php endforeach; ?>
        <?php endforeach; ?>
    </table>
</div>
<?= $camyks->theme->get_boxContent2Footer(); ?>
<?php
/**
 * @endcond Exclude
 */
?>
