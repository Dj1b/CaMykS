<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version       : 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Dec 2007
 * Last Modif Date	: Dec 2007
 *
 * Content_SystemSiteReport Module Site Layout : send action simple layout
 */
global $camyks;
?>
<div style="width:300px; margin:0 auto;">
<?php if ( $this->rfitem->title_mode > 0 ) : ?>
<div class="title1">
<?=$this->rfitem->get_siteTitle();?>
</div>
<?php endif; ?>
<div class="content2" style="margin:8px;">
<?=$this->get_translation('requestsent')?>
</div>
<div style="margin:8px" align="center">
<?=$this->theme->get_button( $this->get_translation('backtohome'),
			     $camyks->get_siteHomepageLink()); ?>
</div>
</div>