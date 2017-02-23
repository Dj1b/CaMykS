<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: May 2008
 * Last Modif Date	: May 2008
 *
 * Content_GenericHTMLContent Module Admin Layout : modify
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:700px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title 
				 .' : '. $this->content->vars['name']
				 .' [ ' .$this->content->id . ' ] ');?>
<?=$this->theme->get_boxTabsBar($this->tabs,
				$this->tabObject.'.mouseclick',
				$this->tabObject.'.mouseover',
				$this->tabObject.'.mouseout',
				'general');?>
<?=$this->theme->get_boxContent2Header(); ?>
<?=$this->form->display_header();?>
<?=$this->form->display_hiddens();?>
<div id="itemgeneral" style="display:block;" class="adminContentPanel">
  <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
    <tr>
      <td class="eTableLine0 eContent2" style="width:100px">
	<?=$this->get_translation('itemname')?>
      </td>
      <td class="eTableLine0">
	<input type="text" name="name" value="<?=$this->content->vars['name'];?>" maxlength="32" class="inputs"/>
      </td>
    </tr>
    <tr>
      <td class="eTableLine1 eContent2">
	<?=$this->get_translation('itemlayout')?>
      </td>
      <td class="eTableLine1">
	<select name="layout" class="inputs">
	  <?php foreach ( $this->layouts as $name => $title ) : ?>
	  <option value="<?=$name?>"<?=($name==$this->content->vars['layout']?' selected="selected"':'')?>>
	    <?=$title?>
	  </option>
	  <?php endforeach; ?>
	</select>
      </td>
    </tr>
  </table>
</div>
<?php foreach ( $camyks->_conf['editing_languages'] as $l ) : ?>
<div id="item<?=$l?>" style="display:none;" class="adminContentPanel">
<?php $this->input->set_contentInfos ('file', $this->content->vars['content_'.$l] ); ?>
<?php $this->input->set_textareaInfos ('content_'.$l, '100%', '400px'); ?>
<?php $this->input->display();?>
</div>
  <?php endforeach; ?>
  
<?php if ( $this->help != null ) : ?>
<div id="itemhelp" style="display:none;">
  <?php $this->display_help() ?>
</div>
<?php endif; ?>

<?=$this->form->display_footer();?>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar($this->buttons);?>
<?=$this->theme->get_boxFooter(); ?>