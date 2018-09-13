<?php
/**
 * @brief Admin_ContentPage Module page browser layout
 * @details Plugin / Module layout
 * @file plugin/module/Admin_ContentPage/html/request.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Oct 2005
 * @date Modification: Sep 2018
 * @copyright 2005 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
?>
<div class="adminPopupFrame">
<?=$this->theme->get_boxHeader('height:100%; width:100%;');?>
<?=$this->theme->get_boxTitleBar($this->title);?>
<?=$this->theme->get_boxContent2Header();?>

<table cellspacing="0" cellpadding="0" border="0" style="width:<?=count( $this->htmlcols )*150?>px;">
<tr>
<?php for ( $i = 0; $i< count( $this->htmlcols ); $i++ ) : ?>
<td class="contentpagetcol">
  <?=$this->get_translation('level', $i+1)?>
</td>
<?php endfor; ?>
</tr>
<tr>
<?php foreach ( $this->htmlcols as $h ) :?>
<td class="contentpageacol">
<?=$h?>
</td>
<?php endforeach; ?>
</tr>
</table>

<!-- menu -->

<?=$this->theme->get_layeredMenu ('pageActionsMenu', 'globalCMenu', $this->pageActionsMenu );?>

<?=$this->theme->get_layeredMenu ('columnActionsMenu', 'globalCMenu', $this->columnActionsMenu );?>

<!-- /menu -->

<?=$this->theme->get_boxContent2Footer();?>
<?=$this->theme->get_boxButtonsBar( $this->buttons );?>
<?=$this->theme->get_boxFooter();?>
</div>
<?php
/**
 * @endcond Exclude
 */
?>
