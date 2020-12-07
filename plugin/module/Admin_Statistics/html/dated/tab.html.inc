<?php
/**
 * @brief Admin_Statistics Module admin dated tab sublayout
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

/* main bar values */
$main_bar_width = 30;
$main_bar_height = 60;
?>
<div id="itemDisplay" style="display:<?= $this->tabBuilder->get_tabDisplay('Display'); ?>;" class="adminContentPanel">
    <div class="eTitle3" style="margin-bottom:8px;">
        <?= $this->statobject->vars['title']?> - <?= $camyks->get_translation('module').$camyks->get_translation('formitem_separator').$this->statobject->vars['plugintitle']; ?>
    </div>

    <div class="eTitle4" style="margin-bottom:8px;">
        <?= $this->get_translation('firstrecorddate', date_displayShortDateHour($this->statobject->vars['register_date'])); ?>
    </div>

    <div class="eContent1">
        <?= $this->get_translation('total'); ?> <?= $this->statsmaintotal ?> <?= $this->statobject->vars['item']; ?>
    </div>

    <div>
        &nbsp;
    </div>

    <table cellspacing="0" style="width:100%">
        <tr>
            <td class="adminStatisticsByDateTitle" colspan="2">
                <?= $this->get_translation('thexlastdays', $this->displayedItems['day']); ?>
            </td>
        </tr>

        <tr>
            <td class="adminStatisticsByDateContent" colspan="2" align="center">
                <table cellspacing="0">
                    <tr>
                        <td class="adminStatisticsByDatePreBox">
                            &nbsp;
                        </td>
                        <?php $alt = 0; ?>
                        <?php for ($i = $this->displayedItems['day']-1; $i >= 0; $i--) : ?>
                            <?php $mydate = mktime(0, 0, 0, date('m'), date('d')-$i, date('Y')); ?>
                            <?php $myvalue = isset($this->statsmainbyday['values'][$mydate]) ? $this->statsmainbyday['values'][$mydate] : 0; ?>
                            <td class="adminStatisticsByDateBox" style="height:<?= $main_bar_height+20; ?>px;">
                                <?= $this->get_optimisedValue($myvalue); ?>
                                <div class="adminStatisticsByDateBox2" style="height:<?= $this->statsmainbyday['max'] == 0 ? 0 : (int)($main_bar_height*$myvalue/$this->statsmainbyday['max']); ?>px;background:#<?= $this->config->vars['coloralternate'.$alt]; ?>;">
                                </div>
                            </td>
                            <?php $alt = abs($alt-1); ?>
                        <?php endfor; ?>
                        <td class="adminStatisticsByDatePostBox">
                            &nbsp;
                        </td>
                    </tr>
                    <tr>
                        <td class="adminStatisticsByDateTxt">
                            &nbsp;
                        </td>
                        <?php for ($i = $this->displayedItems['day']-1; $i >= 0; $i--) : ?>
                            <?php $mydate = mktime(0, 0, 0, date('m'), date('d')-$i, date('Y')); ?>
                            <td class="adminStatisticsByDateTxt">
                                <?= strftime('%d/%m', $mydate); ?>
                            </td>
                        <?php endfor; ?>
                        <td class="adminStatisticsByDateTxt">
                            &nbsp;
                        </td>
                    </tr>
                </table>
                </td>
            </tr>

            <tr>
                <td class="adminStatisticsByDateTitle" colspan="2">
                <?= $this->get_translation('thexlastmonths', $this->displayedItems['month']); ?>
                </td>
            </tr>

            <tr>
                <td class="adminStatisticsByDateContent" colspan="2" align="center">
                <table cellspacing="0">
                    <tr>
                        <td class="adminStatisticsByDatePreBox">
                            &nbsp;
                        </td>
                        <?php $alt = 0; ?>
                        <?php for ($i = $this->displayedItems['month']-1; $i >= 0; $i--) : ?>
                            <?php $mydate = mktime(0, 0, 0, date('m')-$i, 1, date('Y')); ?>
                            <?php $myvalue = isset($this->statsmainbymonth['values'][$mydate]) ? $this->statsmainbymonth['values'][$mydate] : 0; ?>
                            <td class="adminStatisticsByDateBox" style="height:<?= $main_bar_height+20; ?>px;">
                                <?= $this->get_optimisedValue($myvalue); ?>
                                <div class="adminStatisticsByDateBox2" style="height:<?= $this->statsmainbymonth['max'] == 0 ? 0 : (int)($main_bar_height*$myvalue/$this->statsmainbymonth['max']); ?>px; background:#<?= $this->config->vars['coloralternate'.$alt]; ?>;">
                                </div>
                            </td>
                            <?php $alt = abs($alt-1); ?>
                        <?php endfor; ?>
                        <td class="adminStatisticsByDatePostBox">
                            &nbsp;
                        </td>
                    </tr>
                    <tr>
                        <td class="adminStatisticsByDateTxt">
                            &nbsp;
                        </td>
                        <?php for ($i = $this->displayedItems['month']-1; $i >= 0; $i--) : ?>
                            <?php $mydate = mktime(0, 0, 0, date('m')-$i, 1, date('Y')); ?>
                            <td class="adminStatisticsByDateTxt">
                                <?= strftime('%m/%y', $mydate); ?>
                            </td>
                        <?php endfor; ?>
                        <td class="adminStatisticsByDateTxt">
                            &nbsp;
                        </td>
                    </tr>
                </table>
                </td>
            </tr>

            <tr>
                <td class="adminStatisticsByDateTitle" colspan="2">
                <?= $this->get_translation('thexlastyears', $this->displayedItems['year']); ?>
                </td>
            </tr>

            <tr>
                <td class="adminStatisticsByDateContent" colspan="2" align="center">
                <table cellspacing="0">
                    <tr>
                        <td class="adminStatisticsByDatePreBox">
                            &nbsp;
                        </td>
                        <?php $alt = 0; ?>
                        <?php for ($i = $this->displayedItems['year']-1; $i >= 0; $i--) : ?>
                            <?php $mydate = mktime(0, 0, 0, 1, 1, date('Y')-$i); ?>
                            <?php $myvalue = isset($this->statsmainbyyear['values'][$mydate])? $this->statsmainbyyear['values'][$mydate]:0; ?>
                            <td class="adminStatisticsByDateBox" style="height:<?= $main_bar_height+20?>px;">
                                <?= $this->get_optimisedValue($myvalue); ?>
                                <div class="adminStatisticsByDateBox2" style="height:<?= $this->statsmainbyyear['max'] == 0 ? 0 : (int)($main_bar_height*$myvalue/$this->statsmainbyyear['max']); ?>px;background:#<?= $this->config->vars['coloralternate'.$alt]; ?>;"></div>
                            </td>
                            <?php $alt = abs($alt-1); ?>
                        <?php endfor; ?>
                        <td class="adminStatisticsByDatePostBox">
                            &nbsp;
                        </td>
                    </tr>
                    <tr>
                        <td class="adminStatisticsByDateTxt">
                            &nbsp;
                        </td>
                        <?php for ($i = $this->displayedItems['year']-1; $i >= 0; $i--) : ?>
                            <?php $mydate = mktime(0, 0, 0, 1, 1, date('Y')-$i); ?>
                            <td class="adminStatisticsByDateTxt">
                                <?= strftime('%Y', $mydate); ?>
                            </td>
                        <?php endfor; ?>
                        <td class="adminStatisticsByDateTxt">
                            &nbsp;
                        </td>
                    </tr>
                </table>
            </td>
        </tr>
    </table>
</div>

<?php
/**
 * @endcond Exclude
 */
?>
