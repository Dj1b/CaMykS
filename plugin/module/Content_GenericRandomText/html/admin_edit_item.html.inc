<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Mar 2007
 * Last Modif Date	: Mar 2007
 *
 * Content_GenericRandomText module admin layout
 */		
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title);?>
<?=$this->theme->get_boxContent2Header(); ?>
<?=$this->form->display_header()?>
<?=$this->form->display_hiddens()?>
<div class="adminContentPanel">
<table cellspacing="0" style="width:100%;">
  <tr>
    <td class="eTableLine0 eContent2" style="width:150px;">
      <?=$this->get_translation('formitem_name')?>
    </td>
    <td class="eTableLine0 eContent1" colspan="2">
      <input type="text" name="name" value="<?=$this->gitem->vars['name']?>" class="inputs" />
    </td>
  </tr>
  <tr>
    <td class="eTableLine1 eContent2">
      <?=$this->get_translation('formitem_weight')?>
    </td>
    <td class="eTableLine1 eContent1">
      <input type="text" name="weight" value="<?=$this->gitem->vars['weight']?>" class="inputs" />
    </td>
    <td class="eTableLine1 eContent1">
      <?=$this->get_translation('itemweightalt');?>
    </td>
  </tr>
  <tr>
    <td class="eTableLine0 eContent2">
      <?=$this->get_translation('formitem_content')?>
    </td>
    <td class="eTableLine0 eContent1" colspan="2">
      <textarea name="content" cols="40" rows="8" class="vlinputs"><?=$this->gitem->vars['content']?></textarea>
    </td>
  </tr>
</table>
</div>
<?=$this->form->display_footer()?>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar($this->buttons); ?>
<?=$this->theme->get_boxFooter(); ?>
