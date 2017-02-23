<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * Camyks Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Nov 2006
 * Last Modif Date	: Nov 2006
 * 
 * Admin_LanguageChecker Module Layout : checker
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title);?>
<?=$this->theme->get_boxTabsBar($this->tabs,
				$this->tabObject.'.mouseclick',
				$this->tabObject.'.mouseover',
				$this->tabObject.'.mouseout',
				$this->defaultTab);?>
<?=$this->theme->get_boxContent2Header();?>
<?php foreach ( $this->locales as $l=>$v ) : ?>
<div id="itemlang<?=$l?>" style="display:<?=('lang'.$l==$this->defaultTab?'bloc':'none')?>;" class="adminContentPanel">
  <table cellspacing="0" cellpadding="0" border="0" style="width:100%">
    <tr>
      <td class="listheader" style="width:50%;">
	<?=$this->get_translation('item')?>
      </td>
      <td class="listheader" style="width:50%;">
	<?=$this->get_translation('value')?>
      </td>
    </tr>
    
    <?php $alt=0; ?>
    <?php foreach ( $this->items as $item ) : ?>
    <tr>
      <td class="listline<?=$alt?>">
	<?=substr($item, strlen($this->prefix), strlen($item))?>
      </td>
      <?php if ( isset ( $v->trads[$item] ) ) : ?>
      <td class="listline<?=$alt?>">
	<?=$v->trads[$item]?>
      </td>
      <?php else : ?>
      <td style="background:#CC3333;color:white;" align="center">
	<?=$this->get_translation('unset');?>
      </td>
      <?php endif; ?>
      <?php $alt = abs($alt-1); ?>
      <?php endforeach; ?>
    </tr>
  </table>
</div>
<?php endforeach; ?>
<?=$this->theme->get_boxContent2Footer();?>
<?=$this->theme->get_boxButtonsBar($this->buttons);?>
<?=$this->theme->get_boxFooter();?>