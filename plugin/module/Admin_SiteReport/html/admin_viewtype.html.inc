<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * Camyks Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Apr 2007
 * Last Modif Date	: Apr 2007
 * 
 * Admin_SiteReport Module Admin Layout : view a type
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title);?>
<?=$this->theme->get_boxContent2Header();?>
<div class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
<tr>
  <td class="listline0">
<?=$camyks->get_translation ('name')?> :
  </td>
  <td class="listline0">
<?=$this->rtype->vars['name']?>
  </td>
</tr>
<?php $alt=1; ?>
<?php foreach ( $camyks->site_conf['editing_languages'] as $l ) : ?>
<tr>
  <td class="listline<?=$alt;?>">
<?=$this->get_translation ('localetitle', $l)?> :
  </td>
  <td class="listline<?=$alt;?>">
    <?=$this->rtype->vars['title_'.$l]?>
  </td>
</tr>
<?php $alt=abs($alt-1);?>
<?php endforeach; ?>
</table>
</div>
<?=$this->theme->get_boxContent2Footer();?>
<?=$this->theme->get_boxButtonsBar($this->buttons);?>
<?=$this->theme->get_boxFooter();?>