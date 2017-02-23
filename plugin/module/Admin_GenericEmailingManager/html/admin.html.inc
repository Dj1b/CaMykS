<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author			: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0b
 * Object Version	: 1.0
 * Object Type	    : Plugin / Module Layout
 * Creation Date    : Dec 2012
 * Last Modif Date	: Dec 2012
 * 
 * Admin_amadeusEmailingManager Module Admin Layout : main
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader(array('style'=>'width:800px;margin:0 auto;', 'class'=>'adminEditorModule'));?>
<?=$this->theme->get_boxTitleBar($this->title) ?>
<?=$this->theme->get_boxTabsBar($this->tabBuilder->tabs,$this->tabBuilder->jsParams);?>
<?=$this->theme->get_boxContent2Header( )?>
<div id="itemcontacts" style="display:<?=$this->tabBuilder->get_tabDisplay('contacts')?>;" class="adminContentPanel">
	<?=$this->contactList->display('head');?>
	<?=$this->contactList->display('list');?>
</div>

<?php if ($this->check_right(2)) : ?>
<div id="itememailings" style="display:<?=$this->tabBuilder->get_tabDisplay('emailings')?>;" class="adminContentPanel">
	<?=$this->emailingList->display('head');?>
	<?=$this->emailingList->display('list');?>
</div>
<?php endif; ?>

<?php if ($this->check_right(5)) : ?>
<div id="itemconfig" style="display:<?=$this->tabBuilder->get_tabDisplay('config')?>;" class="adminContentPanel">
	<?php $this->load_file('html/configuration/view.html.inc');?>
</div>
<?php endif; ?>

<?php if ( $this->help != null ) : ?>
<div id="itemhelp" style="display:<?=$this->tabBuilder->get_tabDisplay('help')?>;" class="adminContentPanel">
<?php $this->display_help(); ?>
</div>
<?php endif; ?>

<?=$this->theme->get_boxContent2Footer( )?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?=$this->theme->get_boxFooter(); ?>