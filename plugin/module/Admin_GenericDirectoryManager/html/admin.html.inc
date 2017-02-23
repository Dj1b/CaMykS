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
 * Admin_GenericGlossaryManager Module Admin Layout : main
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title) ?>
<?=$this->theme->get_boxTabsBar($this->tabBuilder->tabs,
				$this->tabBuilder->jsParams);?>
<?=$this->theme->get_boxContent2Header( )?>
<div id="itemcontacts" style="display:<?=$this->tabBuilder->get_tabDisplay('contacts')?>;" class="adminContentPanel">

<?=$this->listContact->display('head');?>

<?=$this->listContact->display('list');?>

</div>

<?php if( $this->check_right(1) === true) : ?>
<div id="itemcategories" style="display:<?=$this->tabBuilder->get_tabDisplay('categories')?>;" class="adminContentPanel">

<?=$this->listCategory->display('head');?>

<?=$this->listCategory->display('list');?>

</div>
<?php endif; ?>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?=$this->theme->get_boxFooter(); ?>
