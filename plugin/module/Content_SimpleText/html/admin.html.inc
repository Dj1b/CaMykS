<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Jul 2007
 * Last Modif Date	: Oct 2007
 * 
 * Content_SimpleText Module admin layout
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title 
				 .' : '. $this->textitem->vars['name']
				 .' [ ' .$this->textitem->id . ' ] ');?>
<?=$this->theme->get_boxTabsBar($this->tabs,
				$this->tabObject.'.mouseclick',
				$this->tabObject.'.mouseover',
				$this->tabObject.'.mouseout',
				'general');?>
<?=$this->theme->get_boxContent2Header(); ?>
<?=$this->form->display_header()?>
<?=$this->form->display_hiddens()?>
<div id="itemgeneral" style="display:block;" class="adminContentPanel">
  <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
    <tr>
      <td class="eTableLine1 eContent2" style="width:150px">
	<?=$this->get_translation('itemname')?>
      </td>
      <td class="eTableLine1">
	<input type="text" name="name" value="<?=$this->textitem->vars['name'];?>" maxlength="32" class="inputs" />
      </td>
    </tr>
    <tr>
      <td class="eTableLine0 eContent2" style="width:150px;">
	<?=$this->get_translation('itemlayout')?>
      </td>
      <td class="eTableLine0">
	<select name="layout">
	  <?php foreach ( $this->layouts as $name=>$title ) : ?>
	  <option value="<?=$name?>"<?=$name==$this->textitem->vars['layout']?' selected="selected"':''?>>
	    <?=$title?>
	  </option>
	  <?php endforeach; ?>
	</select>
      </td>
    </tr>
    <tr>
      <td class="eTableLine1 eContent2">
	<?=$this->get_translation('itemhtmlencode');?>
      </td>
      <td class="eTableLine1">
        <input type="checkbox" name="htmlencode" value="1"<?=$this->textitem->vars['htmlencode']==1?' checked="checked"':''?> />
      </td>
    </tr>
  </table>
</div>
  <?php foreach ( $camyks->site_conf['editing_languages'] as $l ) : ?>
  <div id="item<?=$l?>" style="display:none;" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
      <tr>
	<td class="eTableLine1 eContent2" style="width:150px">
	  <?=$this->get_translation('itemtitle')?>
	</td>
	<td class="eTableLine1">
	  <input type="text" name="title_<?=$l?>" value="<?=$this->textitem->vars['title_'.$l]?>" maxlength="128" class="inputs" />
	</td>
      </tr>
      <tr>
	<td class="eTableLine0 eContent2">
	  <?=$this->get_translation('itemcontent')?>
	</td>
	<td class="eTableLine0">                                      
	  <textarea cols="24" rows="8" name="content_<?=$l?>" style="width:100%;"><?= $this->textitem->vars['content_'.$l] ?></textarea>
	</td>
      </tr>
    </table>
  </div>
  <?php endforeach; ?>
  
  <?php if ( $this->help != null ) : ?>
  <div id="itemhelp" style="display:none;" class="adminContentPanel">
    <?php $this->display_help() ?>
  </div>
  <?php endif; ?>  
<?=$this->form->display_footer()?>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons );?>
<?=$this->theme->get_boxFooter(); ?>
