<?php
/**
 * @brief Admin_LanguageChecker Input checker layout
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
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title); ?>
<?= $this->theme->get_boxTabsBar($this->tabs, $this->tabObject.'.mouseclick', $this->tabObject.'.mouseover', $this->tabObject.'.mouseout', $this->defaultTab); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<?php foreach ($this->locales as $l=>$v) : ?>
    <div id="itemlang<?= $l?>" style="display:<?=('lang'.$l==$this->defaultTab?'bloc':'none'); ?>;" class="adminContentPanel">
        <table cellspacing="0" cellpadding="0" border="0" style="width:100%">
            <tr>
                <td class="eTableHeader" style="width:50%;">
                    <?= $this->get_translation('item'); ?>
                </td>
                <td class="eTableHeader" style="width:50%;">
                    <?= $this->get_translation('value'); ?>
                </td>
            </tr>

            <?php $alt=0; ?>
            <?php foreach ($this->items as $item) : ?>
                <tr>
                    <td class="eTableLine<?= $alt; ?>">
                        <?= substr($item, strlen($this->prefix), strlen($item)); ?>
                    </td>
                    <?php if (isset($v->trads[$item])) : ?>
                        <td class="eTableLine<?= $alt; ?>">
                            <?= $v->trads[$item]; ?>
                        </td>
                    <?php else : ?>
                        <td style="background:#CC3333;color:white;" align="center">
                            <?= $this->get_translation('unset'); ?>
                        </td>
                    <?php endif; ?>
                    <?php $alt = abs($alt-1); ?>
                </tr>
            <?php endforeach; ?>
        </table>
    </div>
<?php endforeach; ?>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>

