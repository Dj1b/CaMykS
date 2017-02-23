<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Jul 2008
 * Last Modif Date	: Jul 2008
 * 
 * Content_SimpleText Module admin layout
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title 
				 .' : '. $this->smItem->vars['name']
				 .' [ ' .$this->smItem->id . ' ] ');?>
<?=$this->theme->get_boxContent2Header(); ?>
<?=$this->form->display_header()?>
<?=$this->form->display_hiddens()?>
<div class="adminContentPanel">
  <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
    <tr>
      <td class="listline1" style="width:150px">
	     <?=$this->get_translation('itemname')?>
      </td>
      <td class="listline1">
	<input type="text" name="name" value="<?=$this->smItem->vars['name'];?>" maxlength="32" class="inputs" />
      </td>
    </tr>
    <tr>
      <td class="listline0" style="width:150px;">
	   <?=$this->get_translation('itemlayout')?>
      </td>
      <td class="listline0">
	<select name="layout" class="inputs">
	  <?php foreach ( $this->layouts as $name=>$title ) : ?>
	  <option value="<?=$name?>"<?=$name==$this->smItem->vars['layout']?' selected="selected"':''?>>
	    <?=$title?>
	  </option>
	  <?php endforeach; ?>
	</select>
      </td>
    </tr>
    <tr>
      <td class="listline1" style="width:150px;">
	<?=$this->get_translation('itemcolumns')?>
      </td>
      <td class="listline1">
	<input type="text" name="columns" value="<?=$this->smItem->vars['columns'];?>" maxlength="1" class="inputs" />
      </td>
    </tr>
  </table>
</div>
<?=$this->form->display_footer()?>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons );?>
<?=$this->theme->get_boxFooter(); ?>
