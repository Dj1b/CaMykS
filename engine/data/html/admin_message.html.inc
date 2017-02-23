<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type		: Engine / Generic Layout
 * Create Date		: Feb 2007
 * Last Modif Date	: Jul 2007
 *
 * Admin Generic Layout : display a message
*/
global $camyks;
?>
<div style="margin:0 auto; width:330px; padding-top:100px;">
<?=$camyks->theme->get_boxHeader('width:100%');?>
<?=$camyks->theme->get_boxTitleBar(isset($this->title)?$this->title:'');?>
<?=$camyks->theme->get_boxContent1Header('padding:20px 8px;');?>
<div id="adminMessage" class="eContent1">
<?=isset($this->text)?$this->text:''?>
</div>
<?=$camyks->theme->get_boxContent1Footer();?>
<?=$camyks->theme->get_boxFooter( );?>
</div>