<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0
 * Object Version	: 1.0
 * Object Type	    : Plugin / Module Layout
 * Creation Date	: May 2008
 * Last Modif Date	: Mar 2018
 *
 * Content_GenericHTMLContent Module Admin Layout : modify
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader(array('class'=>'adminEditorModule'));?>
<?=$this->theme->get_boxTitleBar($this->title 
				 .' : '. $this->content->vars['name']
				 .' [ ' .$this->content->id . ' ] ');?>
<?=$this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams);?>
<?=$this->theme->get_boxContent2Header(); ?>
<?=$this->form->display_header();?>
<?=$this->form->display_hiddens();?>
<div id="itemProperties" style="display:<?=$this->tabBuilder->get_tabDisplay('Properties')?>;" class="adminContentPanel">
  <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
    <tr>
      <td class="eTableLine0 eContent2" style="width:100px">
	    <?=$this->get_translation('itemname')?>
      </td>
      <td class="eTableLine0">
        <?=$this->form->display_textInput('name'); ?>
      </td>
    </tr>
    <tr>
      <td class="eTableLine1 eContent2">
	    <?=$this->get_translation('itemlayout')?>
      </td>
      <td class="eTableLine1">
        <?=$this->form->display_selectInput(array('name'=>'layout', 'values'=>$this->layouts)); ?>
      </td>
    </tr>
  </table>
</div>
<?php foreach ($camyks->get_confValue('editing_languages') as $l) : ?>
    <div id="item<?=$l?>" style="display:<?=$this->tabBuilder->get_tabDisplay($l)?>" class="adminContentPanel">
        <?php $this->input->set_contentInfos('file', $this->content->vars['content_'.$l]); ?>
        <?php $this->input->set_textareaInfos('content_'.$l, '100%', '400px'); ?>
        <?php $this->input->display();?>
    </div>
<?php endforeach; ?>
  
<?php if ( $this->help != null ) : ?>
<div id="itemhelp" style="display:none;">
  <?php $this->display_help() ?>
</div>
<?php endif; ?>

<?=$this->form->display_footer();?>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar($this->buttons);?>
<?=$this->theme->get_boxFooter(); ?>