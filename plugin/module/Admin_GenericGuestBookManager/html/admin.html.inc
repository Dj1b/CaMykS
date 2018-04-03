<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Layout
 * Creation Date    : Sep 2010
 * Last Modif Date  : Mar 2018
 * 
 * Admin_GenericGuestBookManager Module admin layout : main
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader(array('class'=>'adminEditorModule'));?>
<?=$this->theme->get_boxTitleBar($this->adminTitle) ?>
<?=$this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams);?>
<?=$this->theme->get_boxContent2Header()?>

<?php if ($this->check_right(2) !== false) : ?> 
    <div id="itemConfig" style="display:<?=$this->tabBuilder->get_tabDisplay('Config')?>;" class="adminContentPanel">
        <?php $this->load_file('html/configuration/view.html.inc');?>
        <div>
            &nbsp;
        </div>
        <div>
            <?=$this->theme->get_button(array(
                'url'   => $this->get_adminLink(array('mode'=>'edit_config')),
                'title' => $camyks->get_translation('modify')
            ));?>
        </div>
    </div>
<?php endif; ?>
<div id="itemMessages" style="display:<?=$this->tabBuilder->get_tabDisplay('Messages')?>;" class="adminContentPanel">
    <?=$this->msgList->display('head');?>
    <?=$this->msgList->display('list');?>
</div>

<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar($this->buttons); ?>
<?=$this->theme->get_boxFooter(); ?>
