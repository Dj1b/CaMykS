<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author			: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0
 * Object Version	: 1.0
 * Object Type	    : Plugin / Input Layout
 * Creation Date    : Jan 2018
 * Last Modif Date	: Jan 2018
 * 
 * ReCaptcha special layout : edit configuration
*/
global $camyks;
?>
<?=$camyks->theme->get_boxContent2Header();?>
<div class="adminContentPanel">
<table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
  <tr>
    <td class="eTableLine0 eContent2" style="width:160px;">
      <?=$this->get_translation('formitem_publickey');?>
    </td>
    <td class="eTableLine0 eContent1">
      <?=$this->form->display_textInput(array('name'=>'publicKey', 'class'=>'linputs', 'maxlength'=>48));?>
    </td>
  </tr>

  <tr>
    <td class="eTableLine1 eContent2">
      <?=$this->get_translation('formitem_privatekey');?>
    </td>
    <td class="eTableLine1 eContent1">
      <?=$this->form->display_textInput(array('name'=>'privateKey', 'class'=>'linputs', 'maxlength'=>48));?>
    </td>
  </tr>
</table>
</div>
<?=$camyks->theme->get_boxContent2Footer();?>