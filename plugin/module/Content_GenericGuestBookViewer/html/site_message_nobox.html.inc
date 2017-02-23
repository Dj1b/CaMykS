<?php
/*
 * CaMykS Engine
 * Developed by		: skymac.org
 * Author		: sky <skymac.contact@gmail.com>
 * CaMykS Version	: 1.0a2
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Mar 2009
 * Last Modif Date	: Mar 2009
 *
 * Content_GenericGuestBookViewer module site layout
 */
global $camyks;
?>
<p class="eContent1">
<?=$this->get_translation('message_submitted'); ?>
</p>

<p class="eContent1">
<?=$this->theme->get_button(array('title'=>$camyks->get_translation('back'),
				  'url'=>$camyks->get_siteLink($camyks->contentPage->id)));?>
</p>