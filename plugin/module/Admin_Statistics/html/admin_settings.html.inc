<?php
/**
 * @brief Admin_Statistics Module admin settings layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: May 2007
 * @date Modification: Sep 2020
 * @copyright 2007 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;

$plus = $this->theme->get_pictURL('plus', 12, 'std');
$plus_ = $this->theme->get_pictURL('plus', 12, 'ovr');

$minus = $this->theme->get_pictURL('minus', 12, 'std');
$minus_ = $this->theme->get_pictURL('minus', 12, 'ovr');
?>
<div class="adminContentPanel statistics_display">
    <?= $this->form->display_header(); ?>
    <?= $this->form->display_hiddens(); ?>

    <table cellspacing="0" cellpadding="0" border="0" style="width:100%">
        <tr>
            <td class="eTableHeader" style="width:49%;">
                <?= $this->get_translation('enabledstatistics'); ?>
            </td>
            <td rowspan="2" style="width:2%; font-size:0;">
                &nbsp;
            </td>
            <td class="eTableHeader" style="width:49%;">
                <?= $this->get_translation('filteredips'); ?>
            </td>
        </tr>
        <tr>
            <td style="vertical-align:top;">
                <table cellspacing="0" cellpadding="0" border="0" style="width:100%">
                    <tr>
                        <td class="eTableLine1 eContent2">
                            <?= $camyks->get_translation('mod_admin_contentpage_stat_visits').$camyks->get_translation('formitem_separator'); ?>
                        </td>
                        <td class="eTableLine1 eContent1">
                            <?= $this->form->display_selectInput(array('name'=>'stat_visits', 'values'=>$this->statusList, 'class'=>'sinputs')); ?>
                        </td>
                    </tr>
                    <tr>
                        <td class="eTableLine0 eContent2">
                            <?= $camyks->get_translation('mod_admin_contentpage_stat_sitepage').$camyks->get_translation('formitem_separator'); ?>
                        </td>
                        <td class="eTableLine0 eContent1">
                            <?= $this->form->display_selectInput(array('name'=>'stat_sitepage', 'values'=>$this->statusList, 'class'=>'sinputs')); ?>
                        </td>
                    </tr>
                    <tr>
                        <td class="eTableLine1 eContent2">
                            <?= $camyks->get_translation('mod_admin_contentpage_stat_firstpage').$camyks->get_translation('formitem_separator'); ?>
                        </td>
                        <td class="eTableLine1 eContent1">
                            <?= $this->form->display_selectInput(array('name'=>'stat_firstpage', 'values'=>$this->statusList, 'class'=>'sinputs')); ?>
                        </td>
                    </tr>
                    <tr>
                        <td class="eTableLine0 eContent2">
                            <?= $camyks->get_translation('mod_admin_contentpage_stat_referer').$camyks->get_translation('formitem_separator'); ?>
                        </td>
                        <td class="eTableLine0 eContent1">
                            <?= $this->form->display_selectInput(array('name'=>'stat_referer', 'values'=>$this->statusList, 'class'=>'sinputs')); ?>
                        </td>
                    </tr>
                    <tr>
                        <td class="eTableLine1 eContent2">
                            <?= $this->get_translation('stat_webbots').$camyks->get_translation('formitem_separator'); ?>
                        </td>
                        <td class="eTableLine1 eContent1">
                            <?= $this->form->display_selectInput(array('name'=>'stat_webbots', 'values'=>$this->statusList, 'class'=>'sinputs')); ?>
                        </td>
                    </tr>

                    <tr>
                        <td class="eTableLine0 eContent2">
                            <?= $this->get_translation('stat_webtools').$camyks->get_translation('formitem_separator'); ?>
                        </td>
                        <td class="eTableLine0 eContent1">
                            <?= $this->form->display_selectInput(array('name'=>'stat_webtools', 'values'=>$this->statusList, 'class'=>'sinputs')); ?>
                        </td>
                    </tr>
                </table>
            </td>
            <td style="vertical-align:top;">
                <table cellspacing="0" cellpadding="0" border="0" style="width:100%">
                    <tbody id="filteredips">
                        <?php foreach($this->settings->vars['stat_filteredips'] as $c => $ip) : ?>
                            <tr id="filteredipline<?= $c; ?>">
                                <td class="eTableLineAuto">
                                    <input type="hidden" name="stat_filteredips_<?= $c; ?>" value="<?= $ip; ?>" />
                                    <?= $ip; ?>
                                </td>
                                <td class="eTableLineAuto" style="width:12px;">
                                    <img src="<?= $minus?>" alt="<?= $this->get_translation('remove_filteredip'); ?>" title="<?= $this->get_translation('remove_filteredip'); ?>"
                                        onclick="sse.remove_filteredIp(<?= $c; ?>);" onmouseover="this.src='<?= $minus_; ?>';" onmouseout="this.src='<?= $minus; ?>';" />
                                </td>
                            </tr>
                        <?php endforeach; ?>
                    </tbody>
                </table>
                <table cellspacing="0" cellpadding="0" border="0" style="width:100%" id="filteredipadder">
                    <tr>
                        <td class="eTableSubHeader">
                             <input type="text" name="ipadder" value="" class="inputs" />
                        </td>
                        <td class="eTableSubHeader" style="width:12px;">
                            <img src="<?= $plus; ?>" alt="<?= $this->get_translation('add_filteredip'); ?>" title="<?= $this->get_translation('add_filteredip'); ?>"
                                onclick="sse.add_filteredIp();" onmouseover="this.src='<?= $plus_?>';" onmouseout="this.src='<?= $plus?>';" />
                        </td>
                    </tr>
                </table>
            </td>
        </tr>
    </table>
    <?= $this->form->display_footer(); ?>
</div>
<?php
/**
 * @endcond Exclude
 */
?>
