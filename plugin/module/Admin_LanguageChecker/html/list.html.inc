<?php
/**
 * @brief Admin_LanguageChecker Input list layout
 * @details Plugin / Input layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Nov 2006
 * @date Modification: Jan 2021
 * @copyright 2006 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule', 'style'=>'width:600px; margin:0 auto;')); ?>
<?= $this->theme->get_boxTitleBar($this->title); ?>
<?= $this->theme->get_boxContent1Header(); ?>
<div class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%">
        <?php $alt = 0; ?>
        <?php foreach ($this->list as $l => $v) :?>
            <tr>
                <td class="eTableLine<?= $alt; ?>">
                    <a href="<?= $this->get_adminLink(array('mode'=>'checker', 'type'=>$v['type'], 'view'=>$l)); ?>" class="eLink2">
                        <?= $this->get_translation($v['type'], $v['title']); ?>
                    </a>
                </td>
            </tr>
            <?php $alt = abs($alt-1); ?>
        <?php endforeach; ?>
    </table>
</div>
<?= $this->theme->get_boxContent1Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
