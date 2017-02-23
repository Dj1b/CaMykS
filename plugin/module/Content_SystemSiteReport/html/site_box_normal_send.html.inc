<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version       : 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Apr 2007
 * Last Modif Date	: Apr 2007
 *
 * Content_SystemSiteReport Module Site Layout : send action normal box layout
 */
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:300px; margin0 auto;');?>
<?php if ( $this->rfitem->title_mode > 0 ) : ?>
<?=$this->theme->get_boxTitleBar( $this->rfitem->get_siteTitle());?>
<?php endif; ?>
<?=$this->theme->get_boxContent2Header();?>
<table cellspacing="0" cellpadding="4" border="0">
<tr>
<td colspan="2" class="">
<?=$this->get_translation('requestsent')?>
</td>
</tr>
</table>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( array( array( 'title'=> $this->get_translation('backtohome'),
						 'link'=> $camyks->get_siteHomepageLink())), 1); ?>
<?=$this->theme->get_boxFooter(); ?>
