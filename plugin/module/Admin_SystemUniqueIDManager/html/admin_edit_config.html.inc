<?php
/*
 * CaMykS Engine
 * Developed by	    : Ideogram Design
 * Author	    	: JB Lebrun <jb.lebrun@ideogram-design.fr>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type	    : Plugin / Module Layout
 * Creation Date    : Apr 2016
 * Last Modif Date  : Apr 2016
 * 
 * Admin_SystemUniqueIDManager Module Admin Layout : main
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:800px; margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title) ?>
<?=$this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams);?>
<?=$this->theme->get_boxContent2Header( )?>

<?=$this->editform->display_header(); ?>
<?=$this->editform->display_hiddens(); ?>

<div id="itemConfiguration" style="display:<?=$this->tabBuilder->get_tabDisplay('Configuration')?>;" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
<tr>
  <td class="eTableHeader" colspan="2">
    <?=$this->get_translation('formtitle_configuration'); ?>
  </td>
</tr>

<tr>
  <td class="eTableSubHeader" colspan="2">
    <?=$this->get_translation('formtitle_generating'); ?>
  </td>
</tr>

<tr>
    <td class="eTableLine0 eContent2" style="width:150px;">
        <?=$this->get_translation('formitem_method');?>
    </td>
    <td class="eTableLine0 eContent1">
      <?=$this->editform->display_selectInput(array('name'=>'generating_method', 'values'=>$this->generatingMethodList)); ?>
    </td>
</tr>

<tr>
    <td class="eTableLine1 eContent2"">
        <?=$this->get_translation('formitem_keylength');?>
    </td>
    <td class="eTableLine1 eContent1">
      <?=$this->editform->display_textInput(array('name'=>'generating_length')); ?>
    </td>
</tr>

<tr>
    <td class="eTableLine0 eContent2"">
        <?=$this->get_translation('formitem_maxattempts');?>
    </td>
    <td class="eTableLine0 eContent1">
      <?=$this->editform->display_textInput(array('name'=>'generating_maxAttempts')); ?>
    </td>
</tr>
</table>
</div>

<?=$this->editform->display_footer(); ?>

<?php if ( $this->help != null ) : ?>
<div id="itemhelp" style="display:<?=$this->tabBuilder->get_tabDisplay('help')?>;" class="adminContentPanel">
<?php $this->display_help(); ?>
</div>
<?php endif; ?>

<?=$this->theme->get_boxContent2Footer( )?>
<?=$this->theme->get_boxButtonsBar($this->buttons); ?>
<?=$this->theme->get_boxFooter(); ?>
