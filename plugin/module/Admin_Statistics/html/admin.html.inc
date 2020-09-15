<?php
/**
 * @brief Admin_Statistics Module admin main layout.
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
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule', 'style'=>'width:800px;')); ?>
<?= $this->theme->get_boxTitleBar($this->adminTitle); ?>
<?= $this->theme->get_boxContent1Header(); ?>
<div class="statistics">
<?php $this->load_file('html/admin_menu.html.inc'); ?>
<?php $this->display_statistic(); ?>
</div>
<?= $this->theme->get_boxContent1Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
<?php
/**
 * @endcond Exclude
 */
?>
