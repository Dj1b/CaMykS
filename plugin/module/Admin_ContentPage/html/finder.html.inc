<?php
/**
 * @brief Admin_ContentPage Module finder layout
 * @details Plugin / Module layout
 * @file plugin/module/Admin_ContentPage/html/finder.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jun 2005
 * @date Modification: Sep 2018
 * @copyright 2005 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule', 'style'=>'width:800px;')); ?>
<?= $this->theme->get_boxTitleBar($this->title); ?>
<?= $this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<div id="itemfinder" style="display:<?= $this->tabBuilder->get_tabDisplay('finder'); ?>; width:784px; overflow-x:auto;">
<table cellspacing="0" cellpadding="0" border="0" style="width:<?=count($this->htmlcols)*150?>px;">
<tr>
<?php for ($i = 0; $i< count($this->htmlcols); $i++) : ?>
<td class="contentpagetcol">
  <?= $this->get_translation('level', $i+1); ?>
</td>
<?php endfor; ?>
</tr>
<tr>
<?php foreach ($this->htmlcols as $h) :?>
<td class="contentpageacol">
<?= $h?>
</td>
<?php endforeach; ?>
</tr>
</table>
</div>

<?php if ($this->check_right(8)) : ?>
<div id="itemConfiguration" style="display:<?= $this->tabBuilder->get_tabDisplay('Configuration'); ?>;" class="adminContentPanel">
<?php $this->load_file('html/configuration/view.html.inc'); ?>

<div>
  &nbsp;
</div>

<div>
  <?= $this->theme->get_button(array('url'=>$this->get_adminLink(array('mode'=>'edit_config')), 'title'=>$camyks->get_translation('modify'))); ?>
</div>

</div>
<?php endif; ?>

<?php if ($this->help != null) : ?>
<div id="itemhelp" style="display:<?= $this->tabBuilder->get_tabDisplay('help'); ?>;" class="adminContentPanel">
<?php $this->display_help(); ?>
</div>
<?php endif; ?>


<!-- menu -->

<?= $this->theme->get_layeredMenu('pageActionsMenu', 'globalCMenu', $this->pageActionsMenu); ?>

<?= $this->theme->get_layeredMenu('columnActionsMenu', 'globalCMenu', $this->columnActionsMenu); ?>

<?= $this->theme->get_layeredMenu('modelActionsMenu', 'globalCMenu', $this->modelActionsMenu); ?>

<!-- /menu -->

<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
<?php
/**
 * @endcond Exclude
 */
?>
