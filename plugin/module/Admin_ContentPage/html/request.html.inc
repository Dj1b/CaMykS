<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0b
 * Object Version	: 1.0
 * Object Type      : Plugin / Module Engine
 * Creation Date	: Oct 2005
 * Last Modif Date  : Jul 2008
 *
 * Admin_ContentPage Module Layout : page browser
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