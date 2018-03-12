<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Layout
 * Create Date      : May 2008
 * Last Modif Date  : Mar 2018
 *
 * Content_GenericHTMLContent module site 'largebox' layout
*/
?>
<?=$this->theme->get_boxHeader('width:100%;');?>
<?=$this->theme->get_boxContent1Header(); ?>

<?php $this->content->write_content(); ?>

<?=$this->theme->get_boxContent1Footer(); ?>
<?=$this->theme->get_boxFooter(); ?>
