<?php
/**
 * @brief Admin_MyMessages Module admin read message layout.
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
<?= $this->theme->get_boxContent1Header(); ?>
<div class="adminContentPanel">
    <table cellspacing="0" style="width:100%;">
        <tr>
            <td class="eTitle3">
                <?= $this->get_translation('read'.$this->view, array($this->ouser, date_displayLongFormat($this->message->vars['senddate']))); ?>
            </td>
        </tr>
        <tr>
            <td class="eTitle4">
                <?= $this->message->vars['title']; ?>
            </td>
        </tr>
        <tr>
            <td class="eContent1">
                <?= nl2br($this->message->vars['content']); ?>
            </td>
        </tr>
    </table>
</div>
<?= $this->theme->get_boxContent1Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter( ); ?>
