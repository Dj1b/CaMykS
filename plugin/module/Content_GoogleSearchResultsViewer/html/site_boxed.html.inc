<?php
/*
 * CaMyks Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Sep 2008
 * Last Modif Date	: Sep 2008
 * 
 * Content_GoogleSearchResultsViewer Module Site Layout : site boxed layout
 */
?>
<?=$this->theme->get_boxHeader()?>
<?=$this->theme->get_boxTitlebar($this->get_translation('site_title'))?>
<?=$this->theme->get_boxContent1Header();?>
<?=$this->load_file('html/_site_gsr.html.inc');?>
<?=$this->theme->get_boxContent1Footer();?>
<?=$this->theme->get_boxFooter();?>