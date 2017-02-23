<?php
/*
 * CaMyks Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0b
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: May 2010
 * Last Modif Date	: May 2010
 * 
 * Content_GenericGlossaryViewer Module Admin Layout
*/		
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:610px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title .' : '.
				 $this->configItem->vars['name'] .' ['.
				 $this->configItem->id . ']');?>
<?=$this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams);?>
<?=$this->theme->get_boxContent2Header(); ?>
<?=$this->form->display_header()?>
<?=$this->form->display_hiddens()?>
<div id="itemproperties" style="display:<?=$this->tabBuilder->get_tabDisplay('properties')?>;" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
  <tr>
    <td class="eTableLine0 eContent2" style="width:150px;">
      <?=$camyks->get_translation('formitem_name')?>
    </td>
  <td class="eTableLine0" colspan="2">
    <?=$this->form->display_textInput('name');?>
  </td>
</tr>

  <tr>
    <td class="eTableLine1 eContent2">
      <?=$this->get_translation('formitem_layout')?>
    </td>
  <td class="eTableLine1" colspan="2">
    <?=$this->form->display_selectInput(array('name'=>'layout', 'values'=>$this->get_layoutList()));?>
  </td>
</tr>

  <tr>
    <td class="eTableLine0 eContent2">
      <?=$this->get_translation('formitem_displayed_categories')?>
    </td>
    <td class="eTableLine0" colspan="2">
    <input type="checkbox" name="categoryall" id="categoryall" value="1" <?=$this->configItem->vars['categories'] == ''?'checked="checked"':''?> onchange="genericglossaryviewer_checkAllCategories();" /> 
    <label for="categoryall">
    <?=$this->get_translation('categories_all');?>
    </label>
  </td>
</tr>

<?php $cnt = 0; ?>
<?php $alt = 0; ?>
<?php foreach ($this->categoryList as $cid => $cname) : ?>
<?php if ($alt == 0 ) : ?>
  <tr>
    <td class="eTableLine0 eContent2">
      &nbsp;    
    </td>
<?php endif; ?> 
    <td class="eTableLine0">
      <input type="checkbox" name="category<?=$cnt;?>" id="category<?=$cnt;?>" value="<?=$cid?>" 
    <?=(in_array($cid, $this->configItem->vars['categories_']) or $this->configItem->vars['categories'] == '') ?'checked="checked"':''?>
    <?=$this->configItem->vars['categories'] == '' ?'disabled="disabled"':''?> />
    <label for="category<?=$cnt++?>">
    <?=$cname;?>
    </label>
    </td>
    <?php if ($alt==1) : ?>
  </tr>
      <?php endif; ?>
<?php $alt = abs($alt-1);?>
<?php endforeach; ?>

<?php if ($alt==1) : ?>
    <td class="eTableLine0">
       &nbsp;
    </td>
  </tr>
<?php endif; ?>


  <tr>
    <td class="eTableLine1 eContent2">
      <?=$this->get_translation('formitem_pagemode')?>
    </td>
    <td class="eTableLine1" colspan="2">
    <?=$this->form->display_selectInput(array('name'=>'pagemode', 'values'=>$this->get_pageModeList($this->gpcAvailable), 'onchange'=>'genericglossaryviewer_swapModePanels(this);'));?>
  </td>
</tr>

</table>

<div id="glossary_pagemodepage" style="display:<?=$this->configItem->vars['pagemode']==0?'block':'none';?>">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
  <tr>
    <td class="eTableLine0 eContent2" style="width:150px;">
      <?=$this->get_translation('formitem_wordbypage')?>
    </td>
  <td class="eTableLine0">
    <?=$this->form->display_textInput('wordcount');?>
  </td>
</tr>
  <tr>
    <td class="eTableLine1 eContent2" style="width:150px;">
      <?=$this->get_translation('formitem_gpcsource')?>
    </td>
    <td class="eTableLine1">
      <?=$this->form->display_selectInput(array('name'=>'gpc_source', 'values'=>$this->get_configGPCSourceList()));?>
    </td>
  </tr>
</table>
</div>
</div>

<?php foreach ( $camyks->get_confValue('editing_languages') as $l ) : ?>
<div id="item<?=$l?>" style="display:<?=$this->tabBuilder->get_tabDisplay($l);?>;" class="adminContentPanel">
<?php $this->editor->set_contentInfos('text', $this->configItem->vars['content_'.$l] ); ?>
<?php $this->editor->set_textareaInfos('content_'.$l, '100%', '400px'); ?>
<?php $this->editor->display();?>
</div>
<?php endforeach; ?>

<?=$this->form->display_footer()?>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?=$this->theme->get_boxFooter(); ?>