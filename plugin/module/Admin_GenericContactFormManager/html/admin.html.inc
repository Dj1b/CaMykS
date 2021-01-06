<?php
/**
 * @brief Admin_GenericContactFormManager Module admin main layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Nov 2010
 * @date Modification: Jan 2021
 * @copyright 2010 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->adminTitle) ?>
<?php if ($this->check_right(2) === false) : ?>
    <?= $this->theme->get_boxContent1Header('height:16px;')?>
    <?= $this->msgList->display('head'); ?>
    <?= $this->theme->get_boxContent1Footer(); ?>
    <?= $this->theme->get_boxContent2Header()?>
    <div class="adminContentPanel">
        <?= $this->msgList->display('list'); ?>
    </div>
    <?= $this->theme->get_boxContent2Footer(); ?>
<?php else : ?>
    <?= $this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams); ?>
    <?= $this->theme->get_boxContent2Header()?>
    <div id="itemconfig" style="display:<?= $this->tabBuilder->get_tabDisplay('config'); ?>;" class="adminContentPanel">
        <?= $this->load_file('html/admin_view_config.html.inc'); ?>
    </div>
    <div id="itemmessages" style="display:<?= $this->tabBuilder->get_tabDisplay('messages'); ?>;" class="adminContentPanel">
        <?= $this->msgList->display('head'); ?>
        <?= $this->msgList->display('list'); ?>
    </div>
    <?= $this->theme->get_boxContent2Footer(); ?>
<?php endif; ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
