<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type	    : Plugin / Module Layout
 * Create Date	    : Mar 2007
 * Last Modif Date	: Mar 2007
 *	
 * Content_SystemSiteReport Module Admin Layout
 */		
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title .' : '.
				 $this->rfitem->name .' ['.
				 $this->rfitem->id . ']');?>
<?=$this->theme->get_boxTabsBar($this->tabs,
				$this->tabObject.'.mouseclick',
				$this->tabObject.'.mouseover',
				$this->tabObject.'.mouseout',
				'properties');?>
<?=$this->theme->get_boxContent2Header(); ?>
<?=$this->form->display_header()?>
<?=$this->form->display_hiddens()?>
<div id="itemproperties" style="display:block;" class="adminContentPanel">
  <table cellspacing="0" cellpadding="0" border="0" width="100%">
    <tr>
      <td class="listline1 eContent2" style="width:200px;">
	<?=$this->get_translation('name')?> : 
      </td>
      <td class="listline1">
	<input type="text" name="name" value="<?=$this->rfitem->name?>" maxlength="64" class="inputs" />
      </td>
    </tr>
    <tr>
      <td class="listline0 eContent2">
	<?=$this->get_translation('layout_name')?> : 
      </td>
      <td class="listline0">
	<select name="layout_name" class="inputs">
	  <?php foreach ( $this->layouts_list as $l ) : ?>
	  <option value="<?=$l?>"<?=( $this->rfitem->layout_name == $l ? ' selected="selected"':'')?>>
	    <?=$this->get_translation($l) ?>
	  </option>
	  <?php endforeach; ?>
	</select>
      </td>
    </tr>
    <tr>
      <td class="listline1 eContent2">
	<?=$this->get_translation('title_mode')?> : 
      </td>
      <td class="listline1">
	<select name="title_mode" class="inputs" onChange="sitereport_modeObject.selectChange(this);">
	  <?php foreach ( $this->title_modes as $n => $l ) : ?>
	  <option value="<?=$n?>"<?=( $this->rfitem->title_mode == $n ? ' selected="selected"':'')?>>
	    <?=$this->get_translation($l) ?>
	  </option>
	  <?php endforeach; ?>
	</select>
      </td>
    </tr>
    <tr>
      <td colspan="2">
	<div id="title_mode_page0" style="display:none;">
	  &nbsp;
	</div>
	<div id="title_mode_page1" style="display:none;">
	  <table cellspacing="0" cellpadding="0" border="0" width="100%">
	    <tr>
	      <td class="listline0 eContent2" style="width:200px;">
		<?=$this->get_translation('title_title'); ?> :
	      </td>
	      <td class="listline0">
		<input type="text" name="title_text_gen" value="<?=(isset($this->rfitem->title_texts['gen']) ? $this->rfitem->title_texts['gen'] : '' )?>" maxlength="64" class="inputs" />
	      </td>
	    </tr>
	  </table>
	</div>
	<div id="title_mode_page2" style="display:none;">
	  <table cellspacing="0" cellpadding="0" border="0" style="width:100%">
	    <tr>
	      <td class="listline0 eContent2" style="width:200px;">
		<?=$this->get_translation('title_image'); ?> :
	      </td>
	      <td class="listline0">
		<?php if (isset($this->rfitem->title_imgs['gen']) and $this->rfitem->title_imgs['gen'] != "") : ?>
		<div id="title_imgs_gendiv">
		  <?= $this->rfitem->title_imgs['gen'] ?>
		  <img src="<?=$this->theme->get_pictURL('cross', 12, 'std')?>" alt="" border="0" style="cursor:pointer"
		    onmouseover="this.src='<?=$this->theme->get_pictURL('cross', 12, 'ovr')?>';"
		    onmouseout="this.src='<?=$this->theme->get_pictURL('cross', 12, 'std')?>';"
		    onclick="document.getElementById('title_imgs_gendiv').style.display='none';
		    document.getElementById('title_imgs_genup').style.display='block';
		    document.sitereport_form.title_img_gen.value = '';" />
		</div>
		<input type="hidden" name="title_img_gen" value="<?=$this->rfitem->title_imgs['gen'];?>" />
		<input type="file" name="up_title_img_gen" id="title_imgs_genup" style="display:none;" />
		<?php else :?>
		<input type="file" name="up_title_img_gen"/>
		<?php endif; ?>
	      </td>
	    </tr>
	  </table>    
	</div>
	<div id="title_mode_page3" style="display:none;width:100%;">
	  <table cellspacing="0" cellpadding="0" border="0" width="100%">
	    <?php $alt = 0; ?>
	    <?php foreach ( $camyks->site_conf['editing_languages'] as $l ) : ?> 
	    <tr>
	      <td class="listline<?=$alt?> eContent2" style="width:200px;">
		<?=$this->get_translation('title_title'); ?>(<?=$l?>) :
	      </td>
	      <td class="listline<?=$alt?>">
		<input type="text" name="title_text_<?=$l?>" value="<?=(isset($this->rfitem->title_texts[$l]) ? $this->rfitem->title_texts[$l] : '' )?>" maxlength="64" class="inputs" />
	      </td>
	    </tr>
	    <?php $alt = abs( $alt -1 ); ?>
	    <?php endforeach; ?>
	  </table>
	</div>
	<div id="title_mode_page4" style="display:none;width:100%;">
	  <table cellspacing="0" cellpadding="0" border="0" width="100%">
	    <?php $alt = 0; ?>
	    <?php foreach ( $camyks->site_conf['editing_languages'] as $l ) : ?> 
	    <tr>
	      <td class="listline<?=$alt;?> eContent2" style="width:200px;">
		<?=$this->get_translation('title_image'); ?>(<?=$l?>) :
	      </td>
	      <td class="listline<?=$alt?>">
		<?php if ( isset($this->rfitem->title_imgs[$l]) and $this->rfitem->title_imgs[$l] != "" ) : ?>
		<div id="title_imgs_<?=$l?>div">
		  <?= $this->rfitem->title_imgs[$l] ?>
		  <img src="<?=$this->theme->get_pictURL('cross', 12, 'std')?>" alt="" border="0" style="cursor:pointer"
		    onmouseover="this.src='<?=$this->theme->get_pictURL('cross', 12, 'ovr')?>';"
		    onmouseout="this.src='<?=$this->theme->get_pictURL('cross', 12, 'std')?>';"
		    onclick="document.getElementById('title_imgs_<?=$l?>div').style.display='none';
		    document.getElementById('title_imgs_<?=$l?>up').style.display='block';
		    document.sitereport_form.title_img_<?=$l?>.value = '';" />
		</div>
		<input type="hidden" name="title_img_<?=$l?>" value="<?=$this->rfitem->title_imgs[$l];?>"/>
		<input type="file" name="up_title_img_<?=$l?>" id="title_imgs_<?=$l?>up" style="display:none;"/>
		<?php else :?>
		<input type="file" name="up_title_img_<?=$l?>"/>
		<?php endif; ?>
	      </td>
	    </tr>
	    <?php $alt = abs( $alt -1 ); ?>
	    <?php endforeach; ?>
	  </table>
	</div>
      </td>
    </tr>
    <tr>
      <td colspan="2">
	  &nbsp;
      </td>
    </tr>
    <tr>
      <td class="eTitle3" colspan="2">
	<?=$this->get_translation('admin_formdata');?>      
      </td>
    </tr>
    <tr>
      <td class="listline1 eContent2">
	<?=$this->get_translation('admin_fileallowed');?>
      </td>
      <td class="listline1">
        <input type="checkbox" name="file_allowed" value="1" <?=($this->rfitem->file_allowed==1?' checked="checked"':'').($this->config->vars['file_allowed']==1?'':' disabled="disabled"') ?>/>
      </td>
    </tr>
  </table>
</div>

<div id="itemtypes" style="display:none;" class="adminContentPanel">
  <table cellspacing="0" cellpadding="0" border="0" width="100%">
    <?php $alt=0; ?>
    <?php $cnt=0; ?>
    <?php foreach ( $this->rtypelist as $t ) : ?>
    <?php /* $t->get_fromItems(); */?>
    <tr>
      <td class="listline<?=$alt?>" style="width:20px;">
	<input type="checkbox" name="type_<?=$cnt?>" value="<?=$t->id?>"<?= in_array( $t->id, $this->rfitem->type_list)?' checked="checked"':''?> />
      </td>
      <td class="listline<?=$alt?>">
	<?= $t->vars['name'] ?>
      </td>
    </tr>
    <?php $cnt++; ?>
    <?php $alt = abs( $alt-1 ); ?>
    <?php endforeach; ?>
  </table>
</div>

<?php foreach ( $camyks->site_conf['editing_languages'] as $l ) : ?>
<div id="itemdesc<?=$l?>" style="display:none;" class="adminContentPanel">
  <div class="listline0">
    <?= $this->get_translation('localedesc', $l) ?> :
  </div>
  <div>
    <?php $this->input->set_contentInfos ('file', $this->rfitem->descriptions[$l] ); ?>
    <?php $this->input->set_textareaInfos ('description_'.$l, '100%', '400px'); ?>
    <?php $this->input->display();?>
  </div>
</div>
<?php endforeach ?>


<?php if ( $this->help != null ) : ?>
<div id="itemhelp" style="display:none;" class="adminContentPanel">
  <?php $this->display_help(); ?>
</div>
<?php endif; ?>

<?=$this->form->display_footer()?>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?=$this->theme->get_boxFooter(); ?>
