<?php
/**
 * @brief Admin_SiteReport Module admin view and answer request layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Apr 2007
 * @date Modification: May 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

$view = $this->theme->get_pictURL('view', 12, 'std');
$view_ = $this->theme->get_pictURL('view', 12, 'ovr');

$cross = $this->theme->get_pictURL('cross', 12, 'std');
$cross_ = $this->theme->get_pictURL('cross', 12, 'ovr');

$file = $this->theme->get_pictURL('file', 12, 'std');
$file_ = $this->theme->get_pictURL('file', 12, 'ovr');
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title); ?>
<?= $this->theme->get_boxTabsBar($this->tabs, $this->tabObject.'.mouseclick', $this->tabObject.'.mouseover', $this->tabObject.'.mouseout', 'request'); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<div id="itemrequest" style="display:block;" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" style="width:100%;">
        <tr>
            <td class="eTableLine0 eContent2" style="width:120px;">
                <?= $this->get_translation('requestid'); ?>
            </td>
            <td class="eTableLine0">
                <?= $this->ritem->id; ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('requestdate'); ?>
            </td>
            <td class="eTableLine1">
                <?= date_displayLongFormat($this->ritem->vars['creation_date']); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('requesttype'); ?>
            </td>
            <td class="eTableLine0">
                <?= $this->rtype->vars['title_'.$camyks->current_language]; ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('requesttitle'); ?>
            </td>
            <td class="eTableLine1">
                <?= $this->ritem->vars['title']; ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('requestcontent'); ?>
            </td>
            <td class="eTableLine0" rowspan="2">
                <?= nl2br($this->ritem->vars['content']); ?>
            </td>
        </tr>

        <tr>
            <td>
                &nbsp;
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('requestlink'); ?>
            </td>
            <td class="eTableLine1">
                <?php if ($this->ritem->vars['link'] == '') : ?>
                    <?= $this->get_translation('nolink'); ?>
                <?php else : ?>
                    <a href="<?= $this->ritem->vars['link']; ?>" target="_blank">
                        <?= $this->ritem->vars['link']; ?>
                    </a>
                <?php endif; ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('requestattachedfile'); ?>
            </td>
            <td class="eTableLine0">
                <?php if ($this->ritem->vars['attached_file'] == ''   ) : ?>
                    <?= $this->get_translation('nofile'); ?>
                <?php elseif ($this->ritem->attachedFile !== false) : ?>
                    <div style="float:left;">
                        <?= $this->get_translation('admin_attachedfile', array($this->ritem->attachedFile->mime, $this->ritem->attachedFile->hsize)); ?>
                    </div>
                    <?php if ($this->ritem->attachedFile->type == 'image') : ?>
                        <a href="<?= $this->ritem->attachedFile->fullpath?>" target="_blank">
                            <img src="<?= $view; ?>" alt="<?= $this->get_translation('admin_attachedfileview'); ?>" style="margin:1px; float:left;" onmouseover="this.src='<?= $view_; ?>';" onmouseout="this.src='<?= $view; ?>';" />
                        </a>
                        <a href="<?= $this->downloadFileLink; ?>">
                            <img src="<?= $file; ?>" alt="<?= $this->get_translation('admin_attachedfiledownload'); ?>" style="margin:1px; float:left;" onmouseover="this.src='<?= $file_; ?>';" onmouseout="this.src='<?= $file; ?>';" />
                        </a>
                        <a href="javascript:adminengine_confirmRedirect(deletefilelink, deletefilemessage);">
                            <img src="<?= $cross; ?>" alt="<?= $this->get_translation('admin_attachedfiledelete'); ?>" style="margin:1px; float:left;" onmouseover="this.src='<?= $cross_; ?>';" onmouseout="this.src='<?= $cross; ?>';" />
                        </a>
                    <?php endif; ?>
                <?php endif; ?>
            </td>
        </tr>
    </table>
</div>

<div id="itemanswer" style="display:none;" class="adminContentPanel">
    <?php if ($this->answermode == 'none') : ?>
        <table cellspacing="0" cellpadding="0" style="width:100%;">
            <tr>
                <td class="eTableLine1">
                    <?= $this->get_translation('noanswerbynow'); ?>
                </td>
            </tr>
        </table>
    <?php elseif ($this->answermode == 'answered') : ?>
        <table cellspacing="0" cellpadding="0" style="width:100%;">
            <tr>
                <td class="eTableLine0" style="width:120px;">
                    <?= $this->get_translation('answeradmin'); ?> :
                </td>
                <td class="eTableLine0">
                    <?= $this->ritem->vars['answer_admin']; ?>
                </td>
            </tr>

            <tr>
                <td class="eTableLine1">
                    <?= $this->get_translation('answerdate'); ?> :
                </td>
                <td class="eTableLine1">
                    <?= date_displayLongFormat($this->ritem->vars['answer_date']); ?>
                </td>
            </tr>

            <tr>
                <td class="eTableLine0">
                    <?= $this->get_translation('answercomment'); ?> :
                </td>
                <td class="eTableLine0" rowspan="2" style="vertical-align:top;">
                    <?=nl2br($this->ritem->vars['answer_comment']); ?>
                </td>
            </tr>

            <tr>
                <td>
                    &nbsp;
                </td>
            </tr>
        </table>
    <?php else : ?>
        <?= $this->form->display_header(); ?>
        <?= $this->form->display_hiddens(); ?>
        <table cellspacing="0" cellpadding="0" style="width:100%;">
            <tr>
                <td class="eTableLine0">
                    <?= $this->get_translation('answertarget'); ?>
                </td>
                <td class="eTableLine0">
                    <?php if ($this->ritem->vars['answer_target'] == '') : ?>
                        --
                    <?php else : ?>
                        <a href="mailto:<?= $this->ritem->vars['answer_target']; ?>"><?= $this->ritem->vars['answer_target']; ?></a>
                    <?php endif; ?>
                </td>
            </tr>

            <tr>
                <td class="eTableLine1">
                    <?= $this->get_translation('isanswered'); ?>
                </td>
                <td class="eTableLine1">
                    <input type="checkbox" name="answer_date" value="1" onclick="admin_sitereport_anwsercheck();" />
                </td>
            </tr>

            <tr>
                <td class="eTableLine0">
                    <?= $this->get_translation('answercomment'); ?> :
                </td>
                <td class="eTableLine0" rowspan="2">
                    <textarea name="answer_comment" cols="40" rows="6" disabled="disabled"></textarea>
                </td>
            </tr>

            <tr>
                <td>
                    &nbsp;
                </td>
            </tr>
        </table>
        <?= $this->form->display_footer(); ?>
    <?php endif; ?>
</div>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
