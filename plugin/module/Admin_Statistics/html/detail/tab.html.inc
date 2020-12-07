<?php
/**
 * @brief Admin_Statistics Module admin detail tab sublayout
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.1
 * @date Creation: Sep 2020
 * @date Modification: Dec 2020
 * @copyright 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;

/* detail bar values */
$detail_bar_width = 100;
?>
<div id="itemDetail" style="display:<?= $this->tabBuilder->get_tabDisplay('Detail'); ?>;" class="adminContentPanel">

    <div class="eTitle3" style="margin-bottom:8px;">
        <?= $this->statobject->vars['title']; ?> - <?= $camyks->get_translation('module').$camyks->get_translation('formitem_separator').$this->statobject->vars['plugintitle']; ?>
    </div>

    <div class="eTitle4" style="margin-bottom:8px;">
        <?= $this->statsdetaildesc; ?>
    </div>

    <table cellspacing="0" style="width:100%">
        <tr>
            <td class="eTableLine0" style="width:<?= $detail_bar_width+50; ?>px; padding-left:0px;">
                <?= $this->get_translation('total'); ?>
            </td>
            <td class="eTableLine0">
                <?= $this->statsdetailtotal ?> <?= $this->statobject->vars['item']; ?>
            </td>
        </tr>

        <?php $alt = 1; ?>
        <?php foreach ($this->statsdetaillist as $stat => $value) : ?>
            <?php $title = isset($this->detailtitles[$stat])? $this->detailtitles[$stat] : $stat; ?>

            <tr>
                <td class="eTableLine<?= $alt; ?> eContent1">
                    <div style="width:<?= $this->statsdetailmax == 0 ? 0 : (int)($detail_bar_width*$value/$this->statsdetailmax); ?>px; height:14px; background:#<?= $this->config->vars['coloralternate'.$alt]; ?>; border:solid 1px #888888; float:left; display:inline-block; margin-right: 4px;">
                        &nbsp;
                    </div>
                    <div style="display:inline-block;">
                        <?= $this->get_optimisedValue($value); ?>
                    </div>
                </td>
                <?php if (string_isHTML($title)) : ?>
                    <td class="eTableLine<?= $alt; ?> eContent1" title="<?= string_stripTags($title); ?>">
                        <?= $title; ?>
                    </td>
                <?php else : ?>
                    <td class="eTableLine<?= $alt; ?> eContent1" title="<?= string_text2html($title); ?>">
                        <?= string_getShortenedSentence($title, 72); ?>
                    </td>
                <?php endif; ?>
            </tr>
            <?php $alt = abs($alt-1); ?>
        <?php endforeach; ?>
    </table>
</div>

<?php
/**
 * @endcond Exclude
 */
?>
