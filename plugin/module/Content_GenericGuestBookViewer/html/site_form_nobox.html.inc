<?php
/**
 * @brief Content_GenericGuestBookViewer module, site form nobox layout.
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
            <?= $this->theme->get_button(array('url'=>$this->get_messageListLink(), 'title'=>$camyks->get_translation('back'))); ?>
        </td>
    </tr>
</table>
<?= $this->msgform->display_footer(); ?>
