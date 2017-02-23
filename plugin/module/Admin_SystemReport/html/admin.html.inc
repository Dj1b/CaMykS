<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Engine
 * Create Date		: May 2007
 * Last Modif Date	: May 2008
 *
 * Admin_SystemReport Module Layout
 */
global $camyks;

$plus = $this->theme->get_pictURL('plus', 12, 'std' );
$plus_ = $this->theme->get_pictURL('plus', 12, 'ovr' );

$minus = $this->theme->get_pictURL('minus', 12, 'std' );
$minus_ = $this->theme->get_pictURL('minus', 12, 'ovr' );

$view = $this->theme->get_pictURL('view', 12, 'std');
$view_ = $this->theme->get_pictURL('view', 12, 'ovr');

$cross = $this->theme->get_pictURL('cross', 12, 'std');
$cross_ = $this->theme->get_pictURL('cross', 12, 'ovr');

$valid = $this->theme->get_pictURL('valid', 12, 'std');
$empty = $this->theme->get_pictURL('empty', 12, 'std');

?>
<?=$this->itemform->display_header();?>
<?=$this->itemform->display_hiddens();?>
<?=$this->itemform->display_footer();?>

<?=$this->theme->get_boxHeader(array('style'=>'width:700px;margin:0 auto;', 'class'=>'adminEditorModule'));?>
<?=$this->theme->get_boxTitleBar($this->title );?>
<?=$this->theme->get_boxContent1Header();?>

<?=$this->reportList->display('head');?>

<?=$this->theme->get_boxContent1Footer();?>
<?=$this->theme->get_boxContent2Header();?>

<div class="adminContentPanel">
<?=$this->reportList->display('list');?>
</div>
<?=$this->theme->get_boxContent2Footer();?>
<?=$this->theme->get_boxButtonsBar( $this->buttons );?>
<?=$this->theme->get_boxFooter();?>