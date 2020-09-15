<?php
/**
 * @brief Admin_Statistics Module admin single object layout
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: May 2007
 * @date Modification: Sep 2020
 * @copyright 2007 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;
?>
<div class="statistics_display">
    <?= $this->theme->get_boxHeader(); ?>
    <?= $this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams); ?>
    <?= $this->theme->get_boxContent2Header(); ?>

    <div id="itemDisplay" style="display:<?= $this->tabBuilder->get_tabDisplay('Display'); ?>;" class="adminContentPanel">
        <div class="eTitle3" style="margin-bottom:8px;">
            <?= $this->statobject->vars['title']; ?> - <?= $camyks->get_translation('module').$camyks->get_translation('formitem_separator').$this->statobject->vars['plugintitle']; ?>
        </div>

        <div class="eTitle4" style="margin-bottom:8px;">
            <?= $this->get_translation('firstrecorddate' , date_displayShortDateHour($this->statobject->vars['register_date'])); ?>
        </div>

        <div class="eContent2">
            <?= $this->statsdesc; ?>
        </div>

        <div>
            &nbsp;
        </div>

        <table style="width:100%;">
            <?php $alt = 1; ?>
            <?php foreach ($this->statslist as $stat) : ?>
                <tr>
                    <td class="eTableLine<?= $alt; ?>" style="width:30px;">
                        <div style="width:25px; height:14px; background:#<?= $this->config->vars['coloralternate'.$alt]; ?>; border:solid 1px black;">
                            &nbsp;
                        </div>
                    </td>
                    <td class="eTableLine<?= $alt; ?> eContent1" style="width:110px;">
                        <?= date_displayShortDateHour($stat->vars['statdate']); ?>
                    </td>
                    <td class="eTableLine<?= $alt; ?> eContent1">
                        : <?= isset($this->maintitles[$stat->vars['main']])? $this->maintitles[$stat->vars['main']] : $stat->vars['main']; ?>
                        <?php if ($stat->vars['data1'] != '' or $stat->vars['data2'] != '') : ?>
                            &nbsp;( <?= $stat->vars['data1']; ?>
                            <?php if ($stat->vars['data2'] != '') : ?>
                                , <?= $stat->vars['data2']; ?>
                            <?php endif; ?>)
                        <?php endif; ?>
                    </td>
                </tr>
                <?php $alt = abs($alt-1); ?>
            <?php endforeach; ?>
        </table>
    </div>

    <?php $this->load_file('html/options/tab.html.inc'); ?>

    <?= $this->theme->get_boxContent2Footer(); ?>
    <?= $this->theme->get_boxFooter(); ?>
</div>

<?php
/**
 * @endcond Exclude
 */
?>
