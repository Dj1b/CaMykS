<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Creation Date	: Apr 2008
 * Last Modif Date	: Mar 2009
 * 
 * Admin_GenericBlogsManager Module Admin Layout : edit link
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title.$this->get_translation('editlink_editortitle') ) ?>
<?=$this->theme->get_boxContent2Header( )?>

<?=$this->form->display_header(); ?>
<?=$this->form->display_hiddens(); ?>
<div class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%">
<tr>
  <td class="eTableLine0 eContent2">
<?=$this->get_translation('editlink_'.($this->linkItem->id==0?'createobject':'objectid'), $this->linkItem->id);?>
  </td>
</tr>

<tr>
  <td class="eTableLine1 eContent2">
  <?=$this->get_translation('editlink_author');?>
  </td>
  <td class="eTableLine1 eContent1">
  <?=$this->linkItem->vars['author'];?>
  </td>
</tr>

  <?php $alt=0; ?>
  <?php if ( $this->linkItem->id > 0 ) : ?>

<tr>
  <td class="eTableLine<?=$alt?> eContent2">
  <?=$this->get_translation('editlink_ndate');?>
  </td>
  <td class="eTableLine<?=$alt?> eContent1">
  <?=date_displayLongDayDateHour($this->linkItem->vars['ndate']);?>
  </td>
</tr>
  <?php $alt=abs($alt-1);?>
  <?php endif; ?>

<tr>
  <td class="eTableLine<?=$alt?> eContent2">
  <?=$this->get_translation('editlink_title');?>
</td>
<td class="eTableLine<?=$alt?> eContent1">
<input type="text" name="title" value="<?=$this->linkItem->vars['title']?>" maxlength="32" class="inputs" />
</td>
</tr>

  <?php $alt=abs($alt-1);?>

<tr>
  <td class="eTableLine<?=$alt?> eContent2">
<?=$this->get_translation('editlink_url');?>
</td>
<td class="eTableLine<?=$alt?> eContent1">
<input type="text" name="link" value="<?=$this->linkItem->vars['link']?>" maxlength="254" class="inputs" />
</td>
</tr>

</table>
</div>
<?=$this->form->display_footer(); ?>

<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar($this->buttons); ?>
<?=$this->theme->get_boxFooter(); ?>