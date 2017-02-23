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
 * Content_GenericNews Module Admin  Layout : edit news item
*/		
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar( $this->title . ' : ' . $this->get_translation('editanews'));?>
<?=$this->theme->get_boxContent2Header(); ?>
<?=$this->form->display_header()?>
<?=$this->form->display_hiddens()?>
<div id="itemproperties" style="display:block;" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" width="100%">
<tr>
  <td class="listline0">
    <?=$this->get_translation('newstitle')?> : 
  </td>
  <td class="listline0">
    <input type="text" name="title" value="<?=$this->newsitem->vars['title']?>" maxlength="64" class="inputs" />
  </td>
</tr>
<tr>
  <td class="listline1">
    <?=$this->get_translation('status')?> : 
  </td>
  <td class="listline1">
    <select name="status" class="inputs">
<?php foreach ( $this->status as $i => $v ) : ?>
<option value="<?=$i?>"<?= ($i==$this->newsitem->vars['status']? 'selected="selected"':'')?>> <?=$this->get_translation($v)?> </option>
<?php endforeach; ?>
    </select>
  </td>
</tr>
<tr>
  <td class="listline0">
    <?=$this->get_translation('language')?> : 
  </td>
  <td class="listline0">
    <select name="language">
<?php foreach ( $camyks->site_conf['editing_languages'] as $l ) : ?>
<option value="<?=$l?>"<?= ($l==$this->newsitem->vars['language']? 'selected="selected"':'')?>> <?=$l?> </option>
<?php endforeach; ?>
    </select>
  </td>
</tr>
<tr>
  <td class="listline1">
    <?=$this->get_translation('date')?> : 
  </td>
  <td class="listline1">
    <?=$this->form->display_dateInput($this->newsitem->vars['ndate'],
				      'ndate');?>
</td>
</tr>
<tr>
  <td class="listline0">
    <?=$this->get_translation('content')?> : 
  </td>
  <td class="listline0">
    <textarea name="content" cols="40" rows="8"><?=$this->newsitem->vars['content']?></textarea>
  </td>
</tr>

<tr>
  <td class="listline1">
    <?=$this->get_translation('source_title')?> : 
  </td>
  <td class="listline1">
    <input type="text" name="source_title" value="<?=$this->newsitem->vars['source_title']?>" maxlength="254" class="inputs"/>
  </td>
</tr>

<tr>
  <td class="listline0">
    <?=$this->get_translation('source_url')?> : 
  </td>
  <td class="listline0">
    <input type="text" name="source_url" value="<?=$this->newsitem->vars['source_url']?>" maxlength="254" class="inputs"/>
  </td>
</tr>

</table>
</div>
<?=$this->form->display_footer()?>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar($this->buttons); ?>
<?=$this->theme->get_boxFooter(); ?>