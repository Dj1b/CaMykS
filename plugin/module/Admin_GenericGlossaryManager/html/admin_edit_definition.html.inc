<?php
/*
 * CaMykS Engine
 * Developed by			: camyks.net
 * Author						: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version		: 1.0b
 * Object Version		: 1.0
 * Object Type	    : Plugin / Module Layout
 * Creation Date   	: May 2010
 * Last Modif Date	: May 2010
 * 
 * Admin_GenericGlossaryManager Module Admin Layout : edit_definition
*/
global $camyks;
$file = $this->theme->get_pictURL('file', 12, 'std');
$file_ = $this->theme->get_pictURL('file', 12, 'ovr');
?>
<?=$this->theme->get_boxHeader('width:610px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->adminTitle);?>
<?=$this->theme->get_boxTabsBar($this->tabBuilder->tabs,
				$this->tabBuilder->jsParams);?>
<?=$this->theme->get_boxContent2Header( )?>
<?=$this->editform->display_header(); ?>
<?=$this->editform->display_hiddens(); ?>
<div id="itemproperties" style="display:<?=$this->tabBuilder->get_tabDisplay('properties')?>;" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">

<tr>
<td class="eTableLine0 eContent2" style="width:150px;">
<?=$camyks->get_translation('formitem_status')?>
</td>
<td class="eTableLine0 eContent1">
<?=$this->editform->display_selectInput(array('name'=>'status', 'values'=>$this->get_definitionStatusList()));?>
</td>
</tr>

<tr>
<td class="eTableLine1 eContent2">
<?=$this->get_translation('formitem_category')?>
</td>
<td class="eTableLine1 eContent1">
<?=$this->editform->display_selectInput(array('name'=>'category', 'values'=>$this->categoryList));?>
</td>
</tr>

<tr>
<td class="eTableLine0 eContent2">
<?=$this->get_translation('formitem_link')?>
</td>
<td class="eTableLine0 eContent1">
<?=$this->editform->display_textInput('link');?>
&nbsp;
<a href="javascript:glossarymanager_selectButtonLink(<?=$i?>);" class="img">
<img src="<?=$file?>" border="0"
  alt="<?=$this->get_translation('select_sitepage');?>"
  title="<?=$this->get_translation('select_sitepage');?>"
  onmouseover="this.src='<?=$file_?>';"
  onmouseout="this.src='<?=$file?>';" />
</a>
</td>
</tr>

</table>
</div>

<?php foreach ( $this->lgs as $l ) : ?>

<div id="item<?=$l?>" style="display:<?=$this->tabBuilder->get_tabDisplay($l)?>;" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">

<tr>
<td class="eTableLine0 eContent2" style="width:150px;">
<?=$this->get_translation('formitem_word')?>
</td>
<td class="eTableLine0 eContent1">
<?=$this->editform->display_textInput(array('name'=>'word', 'language'=>$l));?>
</td>
</tr>

<tr>
<td class="eTableLine1 eContent2" colspan="2">
<?=$camyks->get_translation('formitem_description')?>
</td>
</tr>
<tr>
<td class="eTableLine1 eContent1" colspan="2">
<?php $this->editor->set_contentInfos('text', $this->definitionItem->vars['description_'.$l] ); ?>
<?php $this->editor->set_textareaInfos('description_'.$l, '100%', '300px'); ?>
<?php $this->editor->display();?>
</td>
</tr>

</table>
</div>

<?php endforeach; ?>

<?=$this->editform->display_footer(); ?>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?=$this->theme->get_boxFooter(); ?>