<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a2
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: May 2007
 * Last Modif Date	: Sep 2008
 *
 * Admin_Statistics Module Admin Layout
*/
?>

<?=$this->theme->get_boxHeader('width:800px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->adminTitle);?>
<?=$this->theme->get_boxContent1Header();?>

<div style="width:220px; float:left;">
<?php $this->load_file('html/admin_menu.html.inc');?>
</div>

<div style="margin-left:220px;">
<?php $this->display_statistic(); ?>
</div>

<?=$this->theme->get_boxContent1Footer();?>
<?=$this->theme->get_boxButtonsBar( $this->buttons );?>
<?=$this->theme->get_boxFooter();?>