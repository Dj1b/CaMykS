<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * Camyks Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Jul 2007
 * Last Modif Date	: Jul 2007
 * 
 * Content_GenericMenu Module admin layout : modify
 */
global $camyks;

$add = $this->theme->get_pictURL('plus', 12, 'std');
$add_ = $this->theme->get_pictURL('plus', 12, 'ovr');

$edit = $this->theme->get_pictURL('edit', 12, 'std');
$edit_ = $this->theme->get_pictURL('edit', 12, 'ovr');

$del = $this->theme->get_pictURL('cross', 12, 'std');
$del_ = $this->theme->get_pictURL('cross', 12, 'ovr');
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title 
				 .' : '. $this->menuitem->vars['name']
				 .' [ ' .$this->menuitem->id . ' ] ');?>
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
	<td class="eTableLine0 eContent2" style="width:150px">
	  <?=$this->get_translation('itemname')?>
	</td>
	<td class="eTableLine0">
	  <input type="text" name="name" value="<?=$this->menuitem->vars['name'];?>" maxlength="32" class="inputs" />
	</td>
      </tr>
      
      <tr>
	<td class="eTableLine1 eContent2">
	  <?=$this->get_translation('layout')?>
	</td>
	<td class="eTableLine1">
	  <select name="layout" class="inputs">
	    <?php foreach ( $this->layouts as $name=>$title ) : ?>
	    <option value="<?=$name?>"<?=$name==$this->menuitem->vars['layout']?' selected="selected"':''?>>
	      <?=$title?>
	    </option>
	    <?php endforeach; ?>
	  </select>
	</td>
      </tr>

	  <tr>
	<td class="eTableLine0 eContent2">
	  <?=$this->get_translation('root')?>
	</td>
	<td class="eTableLine0">
	  <input type="text" name="root" value="<?=$this->menuitem->vars['root'];?>" maxlength="5" class="inputs" />
	</td>
      </tr>


      <tr>
	<td class="eTableLine1 eContent2">
	  <?=$this->get_translation('levelcount')?>
	</td>
	<td class="eTableLine1">
	  <select name="levels" class="inputs">
	  <?php for ( $i=1; $i<4; $i++ ) : ?>
	  <option value="<?=$i?>"<?= $i == $this->menuitem->vars['levels']?' selected="selected"':''?>><?=$i?></options>

	  <?php endfor; ?>
	  </select>
	</td>
      </tr>
  </table>
  </div>

  <?php if ( $this->help != null ) : ?>
  <div id="itemhelp" style="display:none;" class="adminContentPanel">
    <?php $this->display_help() ?>
  </div>
  <?php endif; ?>
<?=$this->form->display_footer()?>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar($this->buttons);?>
<?=$this->theme->get_boxFooter(); ?>
