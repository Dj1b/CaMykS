<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author	    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type	    : Plugin / Module Layout
 * Creation Date    : Sep 2010
 * Last Modif Date  : Sep 2010
 * 
 * Admin_GenericPetitionManager Module Admin Layout : edit_petition
 */
global $camyks;

$flags = array();
$lgs = $camyks->get_confValue('editing_languages');
if ( count($lgs) == 1) {
  $flags[$lgs[0]] = '';
} else {
  foreach ($lgs as $l)
    $flags[$l] = '<img src="'.language_getIcon($l, false).'" alt="" border="0" style="float:right" />';
}
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
<td class="eTableLine0">
<?=$this->editform->display_selectInput(array('name'=>'status', 'values'=>$this->get_petitionStatusList()));?>
</td>
</tr>

<?php  $alt=1; ?>
<?php foreach ( $lgs as $l ) : ?>
<tr>
<td class="eTableLine<?=$alt?> eContent2">
<?=$flags[$l];?>
<?=$camyks->get_translation('formitem_title')?>
</td>
<td class="eTableLine<?=$alt?> eContent1">
<?=$this->editform->display_textInput(array('name'=>'title', 'language'=>$l));?>
</td>
</tr>
<?php $alt=abs($alt-1);?>
<?php endforeach; ?>

<tr>
<td class="eTableLine<?=$alt?> eContent2">
<?=$this->get_translation('formitem_cdate')?>
</td>
<td class="eTableLine<?=$alt?>">
<?=$this->editform->display_dateInput(array('name'=>'cdate'));?>
</td>
</tr>

</table>
</div>



<?php foreach ($lgs as $l) : ?>
<div id="item<?=$l?>" style="display:<?=$this->tabBuilder->get_tabDisplay($l)?>;" class="adminContentPanel">

<?php $this->editor->set_contentInfos('text', $this->petitionItem->vars['description_'.$l] ); ?>
<?php $this->editor->set_textareaInfos('description_'.$l, '100%', '400px'); ?>
<?php $this->editor->display();?>
</div>

<?php endforeach; ?>

<?=$this->editform->display_footer(); ?>

<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?=$this->theme->get_boxFooter(); ?>