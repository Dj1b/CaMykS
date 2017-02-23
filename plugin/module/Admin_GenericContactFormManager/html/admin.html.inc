<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type	    : Plugin / Module Layout
 * Creation Date    : Sep 2010
 * Last Modif Date  : Sep 2010
 * 
 * Admin_GenericGuestBookManager Module admin layout : main
*/
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->adminTitle) ?>

<?php if ($this->check_right(2) === false) : ?> 
<?=$this->theme->get_boxContent1Header('height:16px;')?>
<?=$this->msgList->display('head');?>
<?=$this->theme->get_boxContent1Footer(); ?>
<?=$this->theme->get_boxContent2Header()?>
<div class="adminContentPanel">
<?=$this->msgList->display('list');?>
</div>
<?=$this->theme->get_boxContent2Footer(); ?>

<?php else : ?>
<?=$this->theme->get_boxTabsBar($this->tabBuilder->tabs,
				$this->tabBuilder->jsParams);?>
<?=$this->theme->get_boxContent2Header()?>
<div id="itemconfig" style="display:<?=$this->tabBuilder->get_tabDisplay('config')?>;" class="adminContentPanel">
<?=$this->load_file('html/admin_view_config.html.inc');?>
</div>
<div id="itemmessages" style="display:<?=$this->tabBuilder->get_tabDisplay('messages')?>;" class="adminContentPanel">
<?=$this->msgList->display('head');?>
<?=$this->msgList->display('list');?>
</div>
<?=$this->theme->get_boxContent2Footer(); ?>
<?php endif; ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?=$this->theme->get_boxFooter(); ?>
