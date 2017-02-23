<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author			: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0b
 * Object Version	: 1.0
 * Object Type	    : Plugin / Module Layout
 * Creation Date    : Jan 2013
 * Last Modif Date	: Jan 2013
 * 
 * Admin_GenericEmailingManager Module Admin Layout : edit configuration
*/
global $camyks;

$file = $this->theme->get_pictURL('file', 12, 'std');
$file_ = $this->theme->get_pictURL('file', 12, 'ovr');
?>

<table cellspacing="2" cellpadding="0" border="0" style="width:100%;">

<tr>
  <td class="eTableHeader" colspan="4">
    <?=$this->get_translation('formtitle_unsubscribe'); ?>
  </td>
</tr>

<tr>
    <td class="eTableLine0 eContent2" style="width:150px;">
        <?=$this->get_translation('formitem_backpage');?>
    </td>
    <td class="eTableLine0 eContent1" colspan="3">
      <?=$this->editform->display_textInput(array('name'=>'unsubscribe_backpage')); ?>
      <?php if ($this->pc) : ?>
  <a href="javascript:open_pageChooser('unsubscribe_backpage');">
	<img src="<?=$file?>" border="0"
	     alt="<?=$this->get_translation('select_sitepage');?>"
	     title="<?=$this->get_translation('select_sitepage');?>"
	     onmouseover="this.src='<?=$file_?>';"
	     onmouseout="this.src='<?=$file?>';" />
  </a>
  <?php endif; ?>
    </td>
</tr>

</table>