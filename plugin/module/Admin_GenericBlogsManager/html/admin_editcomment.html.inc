<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Creation Date	: Apr 2008
 * Last Modif Date	: Jul 2008
 * 
 * Admin_GenericBlogsManager Module Admin Layout : edit news
*/
global $camyks;

/* get some theme buttons */
$plus = $this->theme->get_pictURL('plus', 12, 'std');
$plus_ = $this->theme->get_pictURL('plus', 12, 'ovr');

$minus = $this->theme->get_pictURL('minus', 12, 'std');
$minus_ = $this->theme->get_pictURL('minus', 12, 'ovr');
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title.$this->get_translation('editcomment_editortitle') ) ?>
<?=$this->theme->get_boxContent2Header( )?>
<?=$this->form->display_header(); ?>
<?=$this->form->display_hiddens(); ?>
<div class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%">
<tr>
  <td class="eTableLine0 eContent2" colspan="2">
<?=$this->get_translation('editcomment_'.($this->commentItem->id==0?'createobject':'objectid'), $this->commentItem->id);?>
  </td>
</tr>

<tr>
  <td class="eTableLine1 eContent2">
  <?=$this->get_translation('editcomment_parentnews');?>
  </td>
  <td class="eTableLine1 eContent1">
  <?=$this->newsItem->vars['title'].' ('.$this->newsItem->id.')';?>
  </td>
</tr>

<tr>
  <td class="eTableLine0 eContent2">
  <?=$this->get_translation('editcomment_date');?>
  </td>
  <td class="eTableLine0 eContent1">
  <?=date_displayLongDayDateHour($this->commentItem->vars['ndate']); ?>
  </td>
</tr>

<tr>
  <td class="eTableLine1 eContent2">
  <?=$this->get_translation('editcomment_ipaddress');?>
  </td>
  <td class="eTableLine1 eContent1">
  <?=$this->commentItem->vars['ipaddress'];?>
  </td>
</tr>



<tr>
  <td class="eTableLine0 eContent2">
  <?=$this->get_translation('editcomment_status');?>
  </td>
  <td class="eTableLine0 eContent1">
  <?=$this->form->display_selectInput(array('name'=>'status', 'default'=>$this->commentItem->vars['status'], 'values'=>$this->commentItem->get_statusList())); ?>
  </td>
</tr>

<tr>
  <td class="eTableLine1 eContent2">
  <?=$this->get_translation('editcomment_author');?>
  </td>
  <td class="eTableLine1 eContent1">
  <input type="text" name="author" value="<?=$this->commentItem->vars['author'];?>" maxlength="32" class="inputs" />
  </td>
</tr>

<tr>
  <td class="eTableLine0 eContent2">
  <?=$this->get_translation('editcomment_email');?>
  </td>
  <td class="eTableLine0 eContent1">
<a href="mailto:<?=$this->commentItem->vars['email'];?>"><?=$this->commentItem->vars['email'];?></a>
  </td>
</tr>

<tr>
  <td class="eTableLine1 eContent2">
  <?=$this->get_translation('editcomment_website');?>
  </td>
  <td class="eTableLine1 eContent1">
  <input type="text" name="website" value="<?=$this->commentItem->vars['website'];?>" maxlength="128" class="inputs" />
  </td>
</tr>

<tr>
  <td class="eTableLine0 eContent2">
  <?=$this->get_translation('editcomment_title');?>
</td>
<td class="eTableLine0 eContent1">
<input type="text" name="title" value="<?=$this->commentItem->vars['title']?>" maxlength="128" class="inputs" />
</td>
</tr>

<tr>
  <td class="eTableLine1 eContent2">
  <?=$this->get_translation('editcomment_content');?>
</td>
<td class="eTableLine1 eContent1">
<textarea  name="content" rows="8" cols="40" style="width:90%"><?=$this->commentItem->vars['content']?></textarea>
</td>
</tr>
</table>
</div>
<?=$this->form->display_footer(); ?>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar($this->buttons); ?>
<?=$this->theme->get_boxFooter(); ?>