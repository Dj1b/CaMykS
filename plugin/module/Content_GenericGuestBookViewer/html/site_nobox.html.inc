<?php
/**
 * @brief Content_GenericGuestBookViewer module, site main nobox layout.
 * @details Plugin / Module Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Sep 2010
 * @date Modification: May 2021
 * @copyright 2010 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->configItem->vars['description']; ?>
<div class="eContent1">
    <?= $this->theme->get_button(array(
        'url'   => $this->get_newMessageLink(),
        'title' => $this->get_translation('addmymessage'),
    )); ?>
</div>

<?php foreach($this->msgList as $message) : ?>
    <?php if ($message->vars['website'] == '') : ?>
        <?php $author = $message->vars['author']; ?>
    <?php else : ?>
        <?php $author = $message->vars['website']; ?>
        <?php if (preg_match('/^http:\/\//i', $author) == false) : ?>
            <?php $author = 'http://'.$author; ?>
        <?php endif; ?>
        <?php $author = '<a href="'.$author.'" target="_blank" class="eLink2">'; ?>
        <?php $author .= $message->vars['author'].'</a>' ?>
    <?php endif; ?>

    <p class="eContent2">
        <?= $this->get_translation('messagepostedbyxaty', array($author, date_displayLongDayDateHour($message->vars['edate']))); ?>
    </p>
    <p class="eContent1">
        <?= nl2br($message->vars['message']); ?>
    </p>
    <p class="eContent1">
        &nbsp;
    </p>
<?php endforeach; ?>

<?php if ($this->pageController !== false): ?>
    <?= $this->pageController->display(); ?>
<?php endif; ?>

<?php if ($this->configItem->vars['formlayout'] == 1) : ?>
    <div id="msgpopup" style="width:400px; background:white; display:none; padding:8px 16px;">
        <?= $this->msgform->display_header(); ?>
        <?= $this->msgform->display_hiddens(); ?>
        <div class="eTitle1">
            <?= $this->get_translation('msgpopup_title'); ?>
        </div>

        <div class="error">
            <?= $this->msgItem->_libError; ?>
        </div>

        <table cellspacing="0" cellpadding="0" border="0" style="width:400px;">
            <tr>
                <td class="eTableLine0 eContent2">
                    <?= $camyks->get_translation('formitem_name'); ?>
                </td>
                <td class="eTableLine0 eContent1">
                    <?= $this->msgform->display_textInput('author'); ?>
                </td>
            </tr>
            <tr>
                <td class="eTableLine0 eContent2">
                    <?= $camyks->get_translation('formitem_email'); ?>
                </td>
                <td class="eTableLine0 eContent1">
                    <?= $this->msgform->display_textInput('email'); ?>
                </td>
            </tr>
            <tr>
                <td class="eTableLine0 eContent2">
                    <?= $camyks->get_translation('formitem_website'); ?>
                </td>
                <td class="eTableLine0 eContent1">
                    <?= $this->msgform->display_textInput('website'); ?>
                </td>
            </tr>
            <tr>
                <td class="eTableLine0 eContent2">
                    <?= $this->get_translation('formitem_message'); ?>
                </td>
                <td class="eTableLine0 eContent1">
                    <?= $this->msgform->display_textAreaInput(array('name'=>'message', 'class'=>'inputs')); ?>
                </td>
            </tr>
            <tr>
                <td class="eTableLine0 eContent2" colspan="2">
                    <?= $this->theme->get_button(array('url'=>$this->msgform->get_HTMLSubmitLink(), 'title'=>$this->get_translation('msgpopup_valid'))); ?>
                        &nbsp; &nbsp; &nbsp;
                    <?= $this->theme->get_button(array('url'=>'javascript:popup_closeModal(\'msgpopup\');', 'title'=>$camyks->get_translation('close'))); ?>
                </td>
            </tr>
        </table>
        <?= $this->msgform->display_footer(); ?>
    </div>
<?php endif; ?>
