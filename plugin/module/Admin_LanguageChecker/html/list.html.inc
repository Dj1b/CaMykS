<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Nov 2006
 * Last Modif Date	: Sep 2007
 * 
 * Admin_LanguageChecker Module Layout : list
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar( $this->title );?>
<?=$this->theme->get_boxContent1Header();?>
<div class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%">
  <?php $alt = 0; ?>
  <?php foreach ( $this->list as $l => $v ) :?>
  <tr>
    <td class="listline<?=$alt;?>">
      <a href="<?=$camyks->get_adminLink($this->name.'&amp;action=checker&amp;type='.$v['type'].'&amp;view='.$l)?>">
	<?=$this->get_translation($v['type'], $v['title'])?>
      </a>
    </td>
  </tr>
  <?php $alt = abs($alt-1); ?>
  <?php endforeach; ?>
</table>
</div>
<?=$this->theme->get_boxContent1Footer();?>
<?=$this->theme->get_boxButtonsBar($this->buttons);?>
<?=$this->theme->get_boxFooter();?>
  