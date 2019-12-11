<?php
/**
 * @brief Admin_Statistics Module admin detailed object layout
 * @details Plugin / Module layout
 * @file plugin/module/Admin_Statistics/html/admin_detail.html.inc
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
        <?= $this->statsdetaildesc; ?>
    </div>

    <table cellspacing="0" style="width:100%">
        <tr>
            <td class="eTableLine0" style="width:<?= $detail_bar_width+40; ?>px; padding-left:0px;">
                <?= $this->get_translation('total'); ?>
            </td>
            <td class="eTableLine0">
                <?= $this->statsdetailtotal ?> <?= $this->statobject->vars['item']?>
            </td>
        </tr>

        <?php $alt = 1; ?>
        <?php foreach ($this->statsdetaillist as $stat=>$value) : ?>
        <?php $title = isset ($this->detailtitles[$stat])? $this->detailtitles[$stat] : $stat; ?>

        <tr>
            <td class="eTableLine<?= $alt?> eContent1">
                <div style="width:<?= (int)($detail_bar_width*$value/$this->statsdetailmax); ?>px; height:14px ;background:#<?= $this->config->vars['coloralternate'.$alt]?>; border:solid 1px black; float:left; display:inline-block; margin-right: 4px;">
                    &nbsp;
                </div>
                <div style="display:inline-block;">
                    <?= $value; ?>
                </div>
            </td>
            <td class="eTableLine<?= $alt?> eContent1" title="<?= $title; ?>">
                <?= string_getShortenedSentence($title, 72); ?>
            </td>
        </tr>
        <?php $alt = abs($alt-1); ?>
        <?php endforeach; ?>
    </table>
</div>

<div id="itemoptions" style="display: none;" class="adminContentPanel">
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
                <td class="eTableHeader" colspan="2">
                    <?= $this->get_translation('value2selection'); ?>
                </td>
            </tr>
            <tr>
                <td class="eTableLine0 eContent2">
                    <input type="radio" name="displaymode" value="0" <?= $this->config->vars['displaymode']==0?' checked="checked"':''; ?> id="displaymode0" />
                </td>
                <td class="eTableLine0 eContent1">
                    <label for="displaymode0">
                        <?= $camyks->get_translation('today'); ?>
                            </label>
                </td>
            </tr>
            <tr>
                <td class="eTableLine1 eContent2">
                    <input type="radio" name="displaymode" value="1" <?= $this->config->vars['displaymode']==1?' checked="checked"':''; ?> id="displaymode1" />
                </td>
                <td class="eTableLine1 eContent1">
                            <label for="displaymode1">
                    <?= $camyks->get_translation('yesterday'); ?>
                            </label>
                </td>
            </tr>
            <tr>
                <td class="eTableLine0 eContent2">
                    <input type="radio" name="displaymode" value="2" <?= $this->config->vars['displaymode']==2?' checked="checked"':''; ?> id="displaymode2" />
                </td>
                <td class="eTableLine0 eContent1">
                            <label for="displaymode2">
                    <?= $camyks->get_translation('thisweek'); ?>
                    </label>
                </td>
            </tr>
            <tr>
                <td class="eTableLine1 eContent2">
                    <input type="radio" name="displaymode" value="3" <?= $this->config->vars['displaymode']==3?' checked="checked"':''; ?> id="displaymode3" />
                </td>
                <td class="eTableLine1 eContent1">
                    <label for="displaymode3">
                    <?= $camyks->get_translation('lastweek'); ?>
                    </label>
                </td>
            </tr>
            <tr>
                <td class="eTableLine0 eContent2">
                    <input type="radio" name="displaymode" value="9" <?= $this->config->vars['displaymode']==9?' checked="checked"':''; ?> id="displaymode9" />
                </td>
                <td class="eTableLine0 eContent1">
                    <label for="displaymode9">
                    <?= $camyks->get_translation('thismonth'); ?>
                    </label>
                </td>
            </tr>
            <tr>
                <td class="eTableLine1 eContent2">
                    <input type="radio" name="displaymode" value="10" <?= $this->config->vars['displaymode']==10?' checked="checked"':''; ?> id="displaymode10" />
                </td>
                <td class="eTableLine1 eContent1">
                    <label for="displaymode10">
                    <?= $camyks->get_translation('lastmonth'); ?>
                    </label>
                </td>
            </tr>
            <tr>
                <td class="eTableLine0 eContent2">
                    <input type="radio" name="displaymode" value="4" <?= $this->config->vars['displaymode']==4?' checked="checked"':''; ?> id="displaymode4" />
                </td>
                <td class="eTableLine0 eContent1">
                    <label for="displaymode4">
                    <?= $camyks->get_translation('thisyear'); ?>
                    </label>
                </td>
            </tr>
            <tr>
                <td class="eTableLine1 eContent2">
                    <input type="radio" name="displaymode" value="5" <?= $this->config->vars['displaymode']==5?' checked="checked"':''; ?> id="displaymode5" />
                </td>
                <td class="eTableLine1 eContent1">
                    <label for="displaymode5">
                    <?= $camyks->get_translation('lastyear'); ?>
                    </label>
                </td>
            </tr>
            <tr>
                <td class="eTableLine0 eContent2">
                    <input type="radio" name="displaymode" value="6" <?= $this->config->vars['displaymode']==6?' checked="checked"':''; ?> id="displaymode6" />
                </td>
                    <td class="eTableLine0 eContent1">
                    <?= $camyks->get_translation('dayx', $this->form->display_dateInput($this->config->vars['displayday'],
                 'displayday',
                 array('day', 'month', 'year'),
                 $this->get_dateInputButtons())); ?>
                </td>
            </tr>
            <tr>
                <td class="eTableLine1 eContent2">
                    <input type="radio" name="displaymode" value="7" <?= $this->config->vars['displaymode']==7?' checked="checked"':''; ?> id="displaymode7" />
                </td>
                <td class="eTableLine1 eContent1">
                    <?= $camyks->get_translation('fromx', $this->form->display_dateInput($this->config->vars['displayfrom'],
                    'displayfrom',
                    array('day', 'month', 'year'),
                    $this->get_dateInputButtons())); ?>
                </td>
            </tr>
            <tr>
                <td class="eTableLine1 eConten2">
                    &nbsp;
                </td>
                <td class="eTableLine1 eContent1">
                    <?= $camyks->get_translation('toy', $this->form->display_dateInput($this->config->vars['displayto'],
                    'displayto',
                    array('day', 'month', 'year'),
                    $this->get_dateInputButtons())); ?>
                </td>
            </tr>
            <tr>
                <td class="eTableLine0" colspan="2">
                    &nbsp;
                </td>
            </tr>
            <tr>
                <td class="eTableHeader" colspan="2">
                    <?= $this->get_translation('value3selection'); ?>
                </td>
            </tr>

            <tr>
                <td class="eTableLine0 eContent1">
                    &nbsp;
                </td>
                <td class="eTableLine0 eContent1">
                    <?= $this->get_translation('thefirstxstats', '<input type="text" name="displaycount" value="'.$this->config->vars['displaycount'].'" maxlength="3" size="4" />'); ?>
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
