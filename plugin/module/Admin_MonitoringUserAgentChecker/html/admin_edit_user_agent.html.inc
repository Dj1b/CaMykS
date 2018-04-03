<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Layout
 * Creation Date    : Dec 2014
 * Last Modif Date  : Mar 2018
 *
 * Admin_MonitoringUserAgentChecker Module Admin Layout : edit record
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader(array('class'=>'adminEditorModule'));?>
<?=$this->theme->get_boxTitleBar($this->adminTitle);?>
<?=$this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams);?>
<?=$this->theme->get_boxContent2Header();?>
<?=$this->editform->display_header();?>
<?=$this->editform->display_hiddens();?>
<div id="itemProperties" style="display:<?=$this->tabBuilder->get_tabDisplay('Properties')?>;" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableLine0 eContent2">
                <?=$this->get_translation('user_agent')?>
            </td>
            <td class="eTableLine0 eContent1">
                <?=$this->editform->display_textAreaInput(array('name'=>'user_agent', 'class'=>'vlinputs')); ?>
                &nbsp;
            </td>
        </tr>
    </table>
</div>
<?=$this->editform->display_footer();?>
<?=$this->theme->get_boxContent2Footer();?>
<?=$this->theme->get_boxButtonsBar($this->buttons);?>
<?=$this->theme->get_boxFooter();?>
