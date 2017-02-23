<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * Camyks Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Jul 2007
 * Last Modif Date	: Jul 2007
 * 
 * Admin_ThemeChecker Module Layout : list action
 */
global $camyks;
?>      
<?=$this->theme->get_boxHeader('width:500px; margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar( $this->title );?>
<?=$this->theme->get_boxContent1Header();?>
<div class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%">
<?php $alt = 0; ?>
<?php foreach ( $camyks->themes as $v ) :?>
<tr>
<td class="listline<?=$alt;?>">
<a href="<?=$camyks->get_adminLink($this->name.'&amp;mode=checker&amp;view='.$v->name)?>">
<?=$v->title?>
</a>
</td>
</tr>
<?php $alt = abs($alt-1); ?>
<?php endforeach; ?>
</table>
</div>
<?=$this->theme->get_boxContent1Footer();?>
<?=$this->theme->get_boxButtonsBar( $this->buttons );?>
<?=$this->theme->get_boxFooter();?>

