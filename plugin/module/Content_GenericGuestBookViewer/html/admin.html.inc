<?php
/*
 * CaMyks Engine
 * Developed by	    : camyks.net
 * Author	    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type	    : Plugin / Module Layout
 * Creation Date    : Sep 2010
 * Last Modif Date  : Sep 2010
 * 
 * Content_GenericGuestBookViewer Module Admin Layout
*/		
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:610px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title .' : '.
				 $this->configItem->vars['name'] .' ['.
				 $this->configItem->id . ']');?>
<?=$this->theme->get_boxTabsBar($this->tabBuilder->tabs,
				$this->tabBuilder->jsParams);?>
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
    <?=$this->form->display_selectInput(array('name'=>'layout', 'values'=>$this->get_configLayoutList()));?>
  </td>
</tr>

  <tr>
    <td class="eTableLine0 eContent2">
  <?=$this->get_translation('formitem_formlayout')?>
    </td>
  <td class="eTableLine0 eContent1">
  <?=$this->form->display_selectInput(array('name'=>'formlayout', 'values'=>$this->get_configFormLayoutList()));?>
  </td>
</tr>

  <tr>
    <td class="eTableLine1 eContent2">
      <?=$this->get_translation('formitem_msgbypage')?>
    </td>
  <td class="eTableLine1 eContent1">
    <?=$this->form->display_textInput('msgcount');?>
  </td>
</tr>

  <tr>
    <td class="eTableLine0 eContent2">
      <?=$this->get_translation('formitem_gpcstyle')?>
    </td>
  <td class="eTableLine0 eContent1">
    <?=$this->form->display_selectInput(array('name'=>'gpcstyle', 'values'=>$this->get_configGPCStyleList()));?>
  </td>
</tr>

</table>
</div>

<?php foreach ( $this->lgs as $l ) : ?>
<div id="item<?=$l?>" style="display:<?=$this->tabBuilder->get_tabDisplay($l)?>;" class="adminContentPanel">
<?php $this->editor->set_contentInfos('text', $this->configItem->vars['description_'.$l]); ?>
<?php $this->editor->set_textareaInfos('description_'.$l, '100%', '400px'); ?>
<?php $this->editor->display();?>
</div>
<?php endforeach; ?>

<?=$this->form->display_footer()?>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?=$this->theme->get_boxFooter(); ?>