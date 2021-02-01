<?php
/**
 * @brief Admin_MyMessages Module admin main layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jun 2007
 * @date Modification: Jan 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title); ?>
<?= $this->theme->get_boxTabsBar($this->tabs, $this->tabObject.'.mouseclick', $this->tabObject.'.mouseover', $this->tabObject.'.mouseout', 'receivedbox'); ?>
<?= $this->theme->get_boxContent2Header(); ?>

<div id="itemreceivedbox" style="display:block;" class="adminContentPanel">
    <?= $this->rboxform->display_header(); ?>
    <?= $this->rboxform->display_hiddens(); ?>
    <table cellspacing="0" style="width:100%;">
        <tr>
            <td style="padding:4px 0px;">
                <table cellspacing="0" style="width:100%;">
                    <tr>
                        <td class="eTitle3">
                            <?php if (count($this->receivedbox) > 1) : ?>
                                <?= $this->get_translation('xmessagesofy', array(count($this->receivedbox), $this->maxmessages)); ?>
                            <?php else : ?>
                                <?= $this->get_translation('xmessageofy', array(count($this->receivedbox), $this->maxmessages)); ?>
                            <?php endif; ?>
                        </td>
                        <td align="right">
                            <?= $this->theme->get_barLeft(); ?>
                            <?= $this->theme->get_barItem('<div style="width:200px; height:15px; padding:0;"> <div style="width:'.floor(count($this->receivedbox)*100/$this->maxmessages).'%;height:15px;background:#CC3333;"> &nbsp; </div> </div>'); ?>
                            <?= $this->theme->get_barRight(); ?>
                        </td>
                    </tr>
                </table>
            </td>
        </tr>
        <tr>
            <td style="padding:4px 0px;">
                <table cellspacing="0" style="width:100%;">
                    <tr>
                        <td class="eTableHeader">
                            <?= $this->get_translation('pm_title'); ?>
                        </td>
                        <td class="eTableHeader">
                            <?= $this->get_translation('from'); ?>
                        </td>
                        <td class="eTableHeader">
                            <?= $this->get_translation('date'); ?>
                        </td>
                        <td class="eTableHeader">
                            &nbsp;
                        </td>
                    </tr>
                    <?php $alt= 0; ?>
                    <?php foreach ($this->receivedbox as $m) : ?>
                        <?php $style = $m->vars['tostatus'] == 2 ? 'style="font-weight:bold;"':''; ?>
                        <tr>
                            <td class="eTableLine<?= $alt; ?>" <?= $style; ?>>
                                <a href="<?= $this->get_adminLink(array('mode'=>'read', 'pm_id'=>$m->id)); ?>" <?= $style; ?>>
                                    <?= $m->vars['title']; ?>
                                </a>
                            </td>
                            <td class="eTableLine<?= $alt; ?>" <?= $style; ?>>
                                <?= $m->vars['fromuser']; ?>
                            </td>
                            <td class="eTableLine<?= $alt; ?>" <?= $style; ?>>
                                <?= date_displayQuickFormat ($m->vars['senddate']); ?>
                            </td>
                            <td class="eTableLine<?= $alt; ?>" style="width:12px;">
                                <input type="checkbox" name="pm_<?= $m->id; ?>" value="1" />
                            </td>
                        </tr>
                        <?php $alt = abs ($alt-1); ?>
                    <?php endforeach; ?>
                </table>
            </td>
        </tr>
        <tr>
            <td align="right">
                <table cellspacing="0" cellpadding="4" border="0">
                    <tr>
                        <td style="padding-right:12px;">
                            <select name="action">
                                <option value=""> ----- </option>
                                <option value="0"><?= $this->get_translation('delete'); ?></option>
                                <option value="1"><?= $this->get_translation('setasread'); ?></option>
                                <option value="2"><?= $this->get_translation('setasunread'); ?></option>
                            </select>
                        </td>
                        <td class="eTitle3" style="padding-right:12px;">
                            <?= $this->get_translation('selectedmessages'); ?>
                        </td>
                        <td style="padding-right:12px;">
                            <?= $this->theme->get_button ($this->get_translation('ok'), $this->rboxform->get_HTMLSubmitLink()); ?>
                        </td>
                    </tr>
                </table>
            </td>
        </tr>
    </table>
    <?= $this->rboxform->display_footer(); ?>
</div>

<div id="itemsentbox" style="display:none;" class="adminContentPanel">
    <?= $this->sboxform->display_header(); ?>
    <?= $this->sboxform->display_hiddens(); ?>
    <table cellspacing="0" style="width:100%;">
        <tr>
            <td style="padding:4px 0px;">
                <table cellspacing="0" style="width:100%;">
                    <tr>
                        <td class="eTitle3">
                            <?php if (count($this->sentbox) > 1) : ?>
                                <?= $this->get_translation('xmessagesofy', array(count($this->sentbox), $this->maxmessages)); ?>
                            <?php else : ?>
                                <?= $this->get_translation('xmessageofy', array(count($this->sentbox), $this->maxmessages)); ?>
                            <?php endif; ?>
                        </td>
                        <td align="right">
                            <?= $this->theme->get_barLeft(); ?>
                            <?= $this->theme->get_barItem('<div style="width:200px;height:15px;vertical-align:middle;padding:0;"> <div style="width:'.floor(count($this->sentbox)*100/$this->maxmessages).'%;height:15px;background:#CC3333;"> &nbsp; </div></div>'); ?>
                            <?= $this->theme->get_barRight(); ?>
                        </td>
                    </tr>
                </table>
            </td>
        </tr>
        <tr>
            <td style="padding:4px 0px;">
                <table cellspacing="0" style="width:100%;">
                    <tr>
                        <td class="eTableHeader">
                            <?= $this->get_translation('pm_title'); ?>
                        </td>
                        <td class="eTableHeader">
                            <?= $this->get_translation('to'); ?>
                        </td>
                        <td class="eTableHeader">
                            <?= $this->get_translation('date'); ?>
                        </td>
                        <td class="eTableHeader">
                            &nbsp;
                        </td>
                    </tr>
                    <?php $alt= 0; ?>
                    <?php foreach ($this->sentbox as $m) : ?>
                        <?php $style = $m->vars['fromstatus'] == 2 ? 'style="font-weight:bold;"' : ''; ?>
                        <tr>
                            <td class="eTableLine<?= $alt; ?>">
                                <a href="<?= $this->get_adminLink(array('mode'=>'read', 'pm_id'=>$m->id)); ?>" <?= $style; ?>>
                                    <?= $m->vars['title']; ?>
                                </a>
                            </td>
                            <td class="eTableLine<?= $alt; ?>" <?= $style; ?>>
                                <?= $m->vars['touser']; ?>
                            </td>
                            <td class="eTableLine<?= $alt; ?>" <?= $style; ?>>
                                <?= date_displayQuickFormat ($m->vars['senddate']); ?>
                            </td>
                            <td class="eTableLine<?= $alt; ?>" style="width:12px">
                                <input type="checkbox" name="pm_<?= $m->id?>" value="1" />
                            </td>
                        </tr>
                        <?php $alt = abs ($alt-1); ?>
                    <?php endforeach; ?>
                </table>
            </td>
        </tr>
        <tr>
            <td align="right">
                <table cellspacing="0" cellpadding="4" border="0">
                    <tr>
                        <td style="padding-right:12px;">
                            <select name="action">
                                <option value=""> ----- </option>
                                <option value="0"><?= $this->get_translation('delete'); ?></option>
                                <option value="1"><?= $this->get_translation('setasread'); ?></option>
                                <option value="2"><?= $this->get_translation('setasunread'); ?></option>
                            </select>
                        </td>
                        <td class="eTitle3" style="padding-right:12px;">
                            <?= $this->get_translation('selectedmessages'); ?>
                        </td>
                        <td style="padding-right:12px;">
                            <?= $this->theme->get_button ($this->get_translation('ok'), $this->sboxform->get_HTMLSubmitLink()); ?>
                        </td>
                    </tr>
                </table>
            </td>
        </tr>
    </table>
    <?= $this->sboxform->display_footer(); ?>
</div>

<div id="itemwrite" style="display:none;" class="adminContentPanel">
    <?php if (count($this->sentbox) >= $this->maxmessages) : ?>
        <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
            <tr>
                <td class="eTitle3">
                    <?= $this->get_translation('sentboxisfull'); ?>
                </td>
            </tr>
            <tr>
                <td>
                    &nbsp;
                </td>
            </tr>
            <tr>
                <td class="eContent1">
                    <?= $this->get_translation('sentboxisfull2'); ?>
                </td>
            </tr>
        </table>
    <?php else : ?>
        <?= $this->writeform->display_header(); ?>
        <?= $this->writeform->display_hiddens(); ?>
        <table cellpadding="4" cellspacing="0" border="0" width="100%;">
            <tr>
                <td class="eTitle3">
                    <?= $this->get_translation('receiptuser'); ?>
                </td>
                <td class="eContent1">
                    <input type="text" name="touser" value="<?= $this->message->vars['touser']; ?>" maxlength="16" class="inputs" />
                </td>
            </tr>
            <tr>
                <td class="eTitle3">
                    <?= $this->get_translation('pm_title'); ?> :
                </td>
                <td class="eContent1">
                    <input type="text" name="title" value="<?= $this->message->vars['title']; ?>" maxlength="64" class="inputs" />
                </td>
            </tr>
            <tr>
                <td class="eTitle3" style="vertical-align:top;padding-top:4px;">
                    <?= $this->get_translation('pm_content'); ?> :
                </td>
                <td class="eContent1">
                    <textarea cols="40" rows="12" name="content"><?= $this->message->vars['content']; ?></textarea>
                </td>
            </tr>
            <tr>
                <td colspan="3" class="eTitle3" style="padding-right:12px;">
                    <input type="checkbox" name="fromstatus" value="1" checked="checked" />
                    <?= $this->get_translation('saveinsentbox'); ?>
                </td>
            </tr>
            <tr>
                <td style="padding-right:16px;" colspan="2" align="right">
                    <?= $this->theme->get_button($this->get_translation('send'), $this->writeform->get_HTMLSubmitLink()); ?>
                </td>
            </tr>
        </table>
        <?= $this->writeform->display_footer(); ?>
    <?php endif; ?>
</div>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
