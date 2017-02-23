<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0b
 * Object Version	: 1.0
 * Object Type	    : Plugin / Module Layout
 * Creation Date	: Apr 2015
 * Last Modif Date	: Apr 2015
 * 
 * Admin_GenericMediaLibraryManager Module Admin Layout : main
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:800px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title) ?>
<?=$this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams);?>
<?=$this->theme->get_boxContent2Header()?>

<div id="itemPictureGalleries" style="display:<?=$this->tabBuilder->get_tabDisplay('PictureGalleries');?>;" class="adminContentPanel">
<?=$this->pictureGalleryList->display('head');?>
<?=$this->pictureGalleryList->display('list');?>
</div>

<?php if ( $this->check_right(1) === true ) : ?>
<div id="itemConfiguration" style="display:<?=$this->tabBuilder->get_tabDisplay('Configuration');?>;" class="adminContentPanel">
<?php $this->load_file('html/configuration/admin_view.html.inc');?>
</div>
<?php endif; ?>

<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar($this->buttons); ?>
<?=$this->theme->get_boxFooter(); ?>
