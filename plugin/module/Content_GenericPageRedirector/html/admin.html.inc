<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a2
 * Object Version	: 1.0
 * Object Type		: Plugin / Module Layout
 * Create Date		: Sep 2009
 * Last Modif Date	: Sep 2009
 *
 * Content_medianPageRedirector Module admin layout
 */
global $camyks;

$file = $this->theme->get_pictURL('file', 12, 'std');
$file_ = $this->theme->get_pictURL('file', 12, 'ovr');

?>
<?=$this->theme->get_boxHeader('width:700px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title 
				 .' : '. $this->pritem->vars['name']
				 .' [ ' .$this->pritem->id . ' ] ');?>
<?=$this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams);?>
<?=$this->theme->get_boxContent2Header(); ?>
<?=$this->form->display_header()?>
<?=$this->form->display_hiddens()?>
<div id="itemproperties" style="display:<?=$this->tabBuilder->get_tabDisplay('properties')?>;" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
<tr>
<td class="eTableLine0 eContent2" style="width:150px">
<?=$camyks->get_translation('formitem_name')?>
</td>
<td class="eTableLine0 eContent1">
<?=$this->form->display_textInput('name');?>
</td>
</tr>

<tr>
<td class="eTableLine1 eContent2">
<?=$this->get_translation('formitem_method');?>
</td>
<td class="eTableLine1 eContent1">
<?=$this->form->display_selectInput(array('name'=>'method', 'values'=>$this->get_redirectorMethodList(), 'onchange'=>'update_formFromMethod()'));?>
</td>
</tr>

<tr>
<td class="eTableLine0 eContent2">
<?=$this->get_translation('formitem_url');?>
</td>
<td class="eTableLine0 eContent1">
<?=$this->form->display_textInput('url');?>
<?php if ($this->pc) : ?>
  <a href="javascript:open_pageChooser();">
	<img src="<?=$file?>" border="0"
	     alt="<?=$this->get_translation('select_sitepage');?>"
	     title="<?=$this->get_translation('select_sitepage');?>"
	     onmouseover="this.src='<?=$file_?>';"
	     onmouseout="this.src='<?=$file?>';" />
  </a>
<?php endif; ?>
</td>
</tr>
</table>
<div id="delay_block">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
<tr>
<td class="eTableLine1 eContent2">
<?=$this->get_translation('formitem_layout');?>
</td>
<td class="eTableLine1 eContent1">
  <?=$this->form->display_selectInput(array('name'=>'layout', 'values'=>$this->get_redirectorLayoutList()));?>
</td>
</tr>
<tr>
<td class="eTableLine0 eContent2" style="width:150px;">
<?=$this->get_translation('formitem_delay')?>
</td>
<td class="eTableLine0 eContent1">
<?=$this->form->display_textInput(array('name'=>'delay', 'class'=>'sinputs'));?>
<?=$this->get_translation('formitem_delay_desc')?>
</td>
</tr>
</table>
</div>
</div>
<?php foreach ( $camyks->_conf['editing_languages'] as $l ) : ?>
<div id="item<?=$l?>" style="display:<?=$this->tabBuilder->get_tabDisplay($l);?>;" class="adminContentPanel">
<?php $this->editor->set_contentInfos ('file', $this->pritem->vars['message_'.$l] ); ?>
<?php $this->editor->set_textareaInfos ('message_'.$l, '100%', '400px'); ?>
<?php $this->editor->display();?>
</div>
<?php endforeach; ?>

<?$this->form->display_footer()?>

<?php if ( $this->help != null ) : ?>
<div id="itemhelp" class="adminContentPanel" style="display:none;">
<?php $this->display_help() ?>
</div>

<?php endif; ?>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons );?>
<?=$this->theme->get_boxFooter(); ?>
