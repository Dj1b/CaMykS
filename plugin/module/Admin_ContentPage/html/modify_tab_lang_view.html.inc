<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0b
 * Object Version	: 1.0
 * Object Type      : Plugin / Module Layout
 * Creation Date	: Nov 2006
 * Last Modif Date  : Sep 2009
 *
 * Admin_ContentPage Module Layout : Page editor languages tabs
 */
 global $camyks;
?>
<?php foreach ( $camyks->_conf['editing_languages'] as $l ) : ?>
<div id="item<?=$l?>"  style="display:<?=$this->tabBuilder->get_tabDisplay($l)?>;" class="adminControlPanel">
  <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
    <tr>
      <td class="eTableLine0 eContent2" style="width:150px">
	<?=$this->get_translation('formitem_pagetitle')?>
      </td>
      <td class="eTableLine0 eContent1">
	<?=( isset ($this->page->trads[$l]['title'])?$this->page->trads[$l]['title']:'')?>
      </td>
    </tr>
    <tr>
      <td class="eTableLine1 eContent2">
	<?=$camyks->get_translation('formitem_description')?>
      </td>
      <td class="eTableLine1 eContent1">
	<?= nl2br(isset( $this->page->trads[$l]['description'] ) ? $this->page->trads[$l]['description'] : '') ?>
      </td>
    </tr>
    <tr>
      <td class="eTableLine0 eContent2">
        <?=$this->get_translation('formitem_keywords');?>
      </td>
      <td class="eTableLine0 eContent1">
	<?= nl2br(isset ( $this->page->trads[$l]['keywords'] ) ? $this->page->trads[$l]['keywords'] : '') ?>
      </td>
    </tr>
  </table>
</div>
<?php endforeach; ?>