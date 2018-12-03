<?php
/**
 * @brief Admin_MonitoringUserAgentChecker Module admin edit user agent layout.
 * @details Plugin / Module layout
 * @file plugin/module/Admin_MonitoringUserAgentChecker/html/admin_edit_user_agent.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Dec 2014
 * @date Modification: Nov 2018
 * @copyright 2014 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->adminTitle); ?>
<?= $this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<?= $this->editform->display_header(); ?>
<?= $this->editform->display_hiddens(); ?>
<div id="itemProperties" style="display:<?= $this->tabBuilder->get_tabDisplay('Properties'); ?>;" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('user_agent'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->editform->display_textAreaInput(array('name'=>'user_agent', 'class'=>'vlinputs')); ?>
                &nbsp;
            </td>
        </tr>
    </table>
</div>
<?= $this->editform->display_footer(); ?>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
<?php
/**
 * @endcond Exclude
 */
?>
