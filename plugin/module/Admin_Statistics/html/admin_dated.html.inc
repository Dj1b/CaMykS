<?php
/**
 * @brief Admin_Statistics Module admin dated object layout
 * @details Plugin / Module layout
 * @file plugin/module/Admin_Statistics/html/admin_dated.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: May 2007
 * @date Modification: Apr 2019
 * @copyright 2007 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;

/* detail bar values */
$detail_bar_width = 100;

/* main bar values */
$main_bar_width = 30;
$main_bar_height = 58;
?>
<?= $this->theme->get_lightBoxHeader('width:100%;'); ?>
<?= $this->theme->get_boxTabsBar($this->tabs,
                                $this->tabObject.'.mouseclick',
                                $this->tabObject.'.mouseover',
                                $this->tabObject.'.mouseout',
                                'display'); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<div id="itemdisplay" style="display: block;" class="adminContentPanel">
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
                <?= $this->get_translation('thexlastdays', $this->config->vars['mainbydaycount']); ?>
            </td>
        </tr>

        <tr>
            <td class="adminStatisticsByDateContent" colspan="2" align="center">
        <table cellspacing="0">
            <tr>
                <td class="adminStatisticsByDatePreBox">
                    &nbsp;
                </td>
                <?php $alt=0; ?>
                <?php for($i=$this->config->vars['mainbydaycount']-1; $i>=0; $i--) : ?>
                <?php $mydate = mktime(0, 0, 0, date('m'), date('d')-$i, date('Y')); ?>
                <?php $myvalue = isset ($this->statsmainbyday['values'][$mydate])? $this->statsmainbyday['values'][$mydate]:0; ?>
                <td class="adminStatisticsByDateBox" style="height:<?= $main_bar_height+20?>px;">
                    <?= $myvalue ?>
                    <div class="adminStatisticsByDateBox2"
                    style="height:<?=(int)($main_bar_height*$myvalue/$this->statsmainbyday['max']); ?>px;background:#<?= $this->config->vars['coloralternate'.$alt]?>;"></div>
                </td>
                <?php $alt=abs($alt-1); ?>
                <?php endfor; ?>
                <td class="adminStatisticsByDatePostBox">
                    &nbsp;
                </td>
            </tr>
            <tr>
                <td class="adminStatisticsByDateTxt">
                    &nbsp;
                </td>
                <?php for($i=$this->config->vars['mainbydaycount']-1; $i>=0; $i--) : ?>
                <?php $mydate = mktime(0, 0, 0, date('m'), date('d')-$i, date('Y')); ?>
                <td class="adminStatisticsByDateTxt">
                    <?=strftime('%d/%m', $mydate); ?>
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
        <?= $this->get_translation('thexlastmonths', $this->config->vars['mainbymonthcount']); ?>
            </td>
        </tr>

        <tr>
            <td class="adminStatisticsByDateContent" colspan="2" align="center">
        <table cellspacing="0">
            <tr>
                <td class="adminStatisticsByDatePreBox">
                    &nbsp;
                </td>
                <?php $alt=0; ?>
                <?php for($i=$this->config->vars['mainbymonthcount']-1; $i>=0; $i--) : ?>
                <?php $mydate = mktime(0, 0, 0, date('m')-$i, 1, date('Y')); ?>
                <?php $myvalue = isset ($this->statsmainbymonth['values'][$mydate])? $this->statsmainbymonth['values'][$mydate]:0; ?>
                <td class="adminStatisticsByDateBox" style="height:<?= $main_bar_height+20?>px;">
                    <?= $myvalue ?>
                    <div class="adminStatisticsByDateBox2"
                    style="height:<?=(int)($main_bar_height*$myvalue/$this->statsmainbymonth['max']); ?>px;
                    background:#<?= $this->config->vars['coloralternate'.$alt]?>;"></div>
                </td>
                <?php $alt=abs($alt-1); ?>
                <?php endfor; ?>
                <td class="adminStatisticsByDatePostBox">
                    &nbsp;
                </td>
            </tr>
            <tr>
                <td class="adminStatisticsByDateTxt">
                    &nbsp;
                </td>
                <?php for($i=$this->config->vars['mainbymonthcount']-1; $i>=0; $i--) : ?>
                <?php $mydate = mktime(0, 0, 0, date('m')-$i, 1, date('Y')); ?>
                <td class="adminStatisticsByDateTxt">
                    <?=strftime('%m/%y', $mydate); ?>
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
        <?= $this->get_translation('thexlastyears', $this->config->vars['mainbyyearcount']); ?>
            </td>
        </tr>

        <tr>
            <td class="adminStatisticsByDateContent" colspan="2" align="center">
        <table cellspacing="0">
            <tr>
                <td class="adminStatisticsByDatePreBox">
                    &nbsp;
                </td>
                <?php $alt=0; ?>
                <?php for($i=$this->config->vars['mainbyyearcount']-1; $i>=0; $i--) : ?>
                <?php $mydate = mktime(0, 0, 0, 1, 1, date('Y')-$i); ?>
                <?php $myvalue = isset ($this->statsmainbyyear['values'][$mydate])? $this->statsmainbyyear['values'][$mydate]:0; ?>
                <td class="adminStatisticsByDateBox" style="height:<?= $main_bar_height+20?>px;">
                    <?= $myvalue ?>
                    <div class="adminStatisticsByDateBox2"
                    style="height:<?=(int)($main_bar_height*$myvalue/$this->statsmainbyyear['max']); ?>px;background:#<?= $this->config->vars['coloralternate'.$alt]?>;"></div>
                </td>
                <?php $alt=abs($alt-1); ?>
                <?php endfor; ?>
                <td class="adminStatisticsByDatePostBox">
                    &nbsp;
                </td>
            </tr>
            <tr>
                <td class="adminStatisticsByDateTxt">
                    &nbsp;
                </td>
                <?php for($i=$this->config->vars['mainbyyearcount']-1; $i>=0; $i--) : ?>
                <?php $mydate = mktime(0, 0, 0, 1, 1, date('Y')-$i); ?>
                <td class="adminStatisticsByDateTxt">
                    <?=strftime('%Y', $mydate); ?>
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

<div id="itemoptions" style="display:none;" class="adminContentPanel">
    <?= $this->form->display_header(); ?>
    <?= $this->form->display_hiddens(); ?>
    <table cellspacing="0" style="width:100%;">
        <tr>
            <td class="eTableLine0 eTitle3" colspan="2">
        <?= $this->statobject->vars['title']?> - <?= $camyks->get_translation('module').$camyks->get_translation('formitem_separator').$this->statobject->vars['plugintitle']; ?>
            </td>
        </tr>
        <tr>
            <td class="" style="border-right: solid 1px #888888; width:60%; vertical-align:top;">
        <table cellspacing="0" style="width:100%;">
            <tr>
                <td>
                    &nbsp;
                </td>
            </tr>
        </table>
            </td>
            <td class="" style="vertical-align:top;">
        <table cellspacing="0" style="width:100%;">
            <tr>
                <td class="eTableHeader" colspan="2">
                    <?= $this->get_translation('colorselection'); ?>
                </td>
            </tr>
            <tr>
                <td class="eTableLine0 eContent2" style="width:100px;">
                    <?= $this->get_translation('coloralternate1'); ?>
                </td>
                <td class="eTableLine0 eContent1">
                    <?= $this->display_colorPicker('coloralternate0'); ?>
                </td>
            </tr>
            <tr>
                <td class="eTableLine1 eContent2">
                    <?= $this->get_translation('coloralternate2'); ?>
                </td>
                <td class="eTableLine1 eContent1">
                    <?= $this->display_colorPicker('coloralternate1'); ?>
                </td>
            </tr>
        </table>
            </td>
        </tr>
    </table>
    <?= $this->form->display_footer(); ?>
</div>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_lightBoxFooter(); ?>


<?php
/**
 * @endcond Exclude
 */
?>
