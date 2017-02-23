<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a2
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Dec 2007
 * Last Modif Date	: Apr 2009
 *
 * Content_GenericHTMLNews Module admin layout : edit news item
*/		
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title . ' : ' . $this->get_translation('editanews'));?>
<?=$this->theme->get_boxTabsBar($this->tabBuilder->tabs, 
				$this->tabBuilder->jsParams);?>
<?=$this->theme->get_boxContent2Header(); ?>
<?=$this->form->display_header()?>
<?=$this->form->display_hiddens()?>
<div id="itemproperties" style="display:<?=$this->tabBuilder->get_tabDisplay('properties');?>;" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%">
<tr>
  <td class="eTableLine1 eContent2">
    <?=$camyks->get_translation('formitem_title')?>
  </td>
  <td class="eTableLine1">
<?=$this->form->display_textInput('title');?>
  </td>
</tr>
<tr>
  <td class="eTableLine0 eContent2">
    <?=$camyks->get_translation('formitem_status')?>
  </td>
  <td class="eTableLine0">
<?=$this->form->display_selectInput(array('name'=>'status', 'values'=>$this->get_newsStatusList()));?>
  </td>
</tr>
<tr>
  <td class="eTableLine1 eContent2">
    <?=$this->get_translation('language')?>
  </td>
  <td class="eTableLine1">
  <?=$this->form->display_selectInput(array('name'=>'language', 'values'=>$this->get_newsLanguageList()));?>
  </td>
</tr>
<tr>
  <td class="eTableLine0 eContent2">
    <?=$camyks->get_translation('formitem_date')?>
  </td>
  <td class="eTableLine0">  
    <?=$this->form->display_dateInput(array('name'=>'ndate'));?>
  </td>
</tr>

<tr>
  <td class="eTableLine1 eContent2">
    <?=$this->get_translation('summary')?>
  </td>
  <td class="eTableLine1">
    <?=$this->form->display_textareaInput(array('name'=>'summary', 'class'=>'mceNoEditor vlinputs'));?>
   </td>
</tr>

<tr>
  <td class="eTableLine0 eContent2">
    <?=$this->get_translation('source_title')?>
  </td>
  <td class="eTableLine0">
   <?=$this->form->display_textInput('source_title');?>
  </td>
</tr>

<tr>
  <td class="eTableLine1 eContent2">
    <?=$this->get_translation('source_url')?>
  </td>
  <td class="eTableLine1">
  <?=$this->form->display_textInput('source_url');?>
  </td>
</tr>
</table>
</div>
<div id="itemcontent" style="display:none;" class="adminContentPanel">
<?php $this->input->display();?>
</div>
<?=$this->form->display_footer()?>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?=$this->theme->get_boxFooter(); ?>