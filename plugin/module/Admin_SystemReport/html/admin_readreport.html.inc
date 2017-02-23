<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0b
 * Object Version	: 1.0
 * Object Type	    : Plugin / Module Engine
 * Create Date		: May 2008
 * Last Modif Date	: Mar 2009
 *
 * Admin_SystemReport Module Layout
 */
global $camyks;
?>
<?=$this->theme->get_boxHeader(array('style'=>'width:600px;', 'class'=>'adminEditorModule'));?>
<?=$this->theme->get_boxTitleBar($this->adminTitle);?>
<?=$this->theme->get_boxContent2Header();?>
<div class="adminContentPanel">
<table cellspacing="0" style="width:100%;">
<tr>
 <td class="eTableHeader" colspan="2">
<?=$camyks->get_translation('formtitle_properties');?>
</td>
</tr>

  <tr>
    <td class="eTableLine0 eContent2" style="width:150px;">
      <?=$camyks->get_translation('formitem_type');?>
    </td>
    <td class="eTableLine0 eContent1" style="text-align:left;">
      <?=$this->reportItem->vars['type']?>
    </td>
  </tr>
  <tr>
    <td class="eTableLine1 eContent2">
      <?=$camyks->get_translation('formitem_date');?>
    </td>
    <td class="eTableLine1 eContent1" style="text-align:left;">
      <?=date_displayLongDayDateHour($this->reportItem->vars['_date']);?>
    </td>
  </tr>
  <tr>
    <td class="eTableLine0 eContent2">
      <?=$this->get_translation('formitem_url');?>
    </td>
    <td class="eTableLine0 eContent1" style="text-align:left;">
      <?=$this->reportItem->vars['url']?>
    </td>
  </tr>
  <tr>
    <td class="eTableLine1 eContent2">
      <?=$this->get_translation('formitem_object');?>
    </td>
    <td class="eTableLine1 eContent1" style="text-align:left;">
      <?=ucfirst($this->reportItem->vars['objecttype']).' '.$this->reportItem->vars['objectname']?>
    </td>
  </tr>
  <tr>
    <td class="eTableLine0 eContent2">
      <?=$camyks->get_translation('formitem_description');?>
    </td>
    <td class="eTableLine0 eContent1" style="text-align:left;">
      <?=string_text2html($this->reportItem->vars['errordesc1']);?>
    </td>
  </tr>
  <?php if ( $this->reportItem->vars['errordesc2'] != '' ) : ?>
  <tr>
    <td>
      &nbsp;
    </td>
    <td class="eTableLine0 eContent1" style="text-align:left;">
      <?=$this->reportItem->vars['errordesc2']?>
    </td>
  </tr>
  <?php endif; ?>
  
  <?php if ( $this->reportItem->vars['errorline'] > 0 and $this->reportItem->vars['errorfile'] != '' ) : ?>
  <tr>
    <td class="eTableLine1 eContent2">
      <?=$this->get_translation('formitem_file');?>
    </td>
    <td class="eTableLine1 eContent1" style="text-align:left;">
      <?=$this->reportItem->vars['errorfile']?>
    </td>
  </tr>
  <tr>
    <td class="eTableLine0 eContent2">
      <?=$this->get_translation('formitem_line');?>
    </td>
    <td class="eTableLine0 eContent1" style="text-align:left;">
      <?=$this->reportItem->vars['errorline']?>
    </td>
  </tr>
  <?php endif; ?>

  <tr>
    <td class="eTableLine0" colspan="2">
      &nbsp;
    </td>
  </tr>

  <tr>
    <td class="eTableHeader" colspan="2">
    <?=$this->get_translation('formtitle_validation');?>
    </td>
  </tr>
  
  <?php if ( $this->reportItem->vars['status'] == 1 ) :?> 
  <tr>
    <td class="eTableLine0 eContent2">
      <?=$this->get_translation('formitem_answerby');?>
    </td>
    <td class="eTableLine0 eContent1">
      <?=$this->reportItem->vars['answeruser']?>
    </td>
  </tr>
  <tr>
    <td class="eTableLine1 eContent2">
      <?=$camyks->get_translation('formitem_date');?>
    </td>
    <td class="eTableLine1 eContent1">
      <?=date_displayLongDayDatehour($this->reportItem->vars['answerdate'])?>
    </td>
  </tr>

  <tr>
    <td class="eTableLine0 eContent2" style="vertical-align:top;">
      <?=$this->get_translation('formitem_answercomment');?>
    </td>
    <td class="eTableLine0 eContent1">
      <?=nl2br($this->reportItem->vars['answercomment'])?>
    </td>
  </tr>
    
  <?php elseif ( isset($this->markform) and $this->check_right(1) ) : ?>
  <tr>
    <td class="eTableLine0 eContent2" style="vertical-align:top;">
      <?=$this->get_translation('formitem_answercomment');?>
    </td>
    <td class="eTableLine0 eContent1">
      <?=$this->markform->display_header();?>
      <?=$this->markform->display_hiddens();?>
      <textarea name="answercomment" cols="40" rows="8" style="width:100%;"></textarea>
	<?=$this->markform->display_footer();?>
    </td>
  </tr>
  <tr>
    <td>
      &nbsp;
    </td>
  </tr>
  
  <tr>
    <td>
      &nbsp;
    </td>
  </tr>
  
  <?php endif; ?>
  
</table>
</div>
<?=$this->theme->get_boxContent2Footer();?>
<?=$this->theme->get_boxButtonsBar( $this->buttons );?>
<?=$this->theme->get_boxFooter( );?>
