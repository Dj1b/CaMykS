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
 * Admin_GenericEmailingManager Module Admin Layout : view configuration
*/
global $camyks;
?>

<table cellspacing="2" cellpadding="0" border="0" style="width:100%;">

<tr>
  <td class="eTableHeader" colspan="2">
    <?=$this->get_translation('formtitle_unsubscribe'); ?>
  </td>
</tr>

<tr>
    <td class="eTableLine0 eContent2" style="width:150px">
        <?=$this->get_translation('formitem_backpage');?>
    </td>
    <td class="eTableLine0 eContent1">
      <?=$this->config->vars['unsubscribe_backpage']; ?>
    </td>
</tr>

<tr>
    <td class="eTableLine0 eContent2" coslpan="2">
        <?=$this->theme->get_button(array('url'=>$this->get_adminLink(array('mode'=>'edit_config')), 'title'=>$camyks->get_translation('modify')));?>
    </td>
</tr>

</table>