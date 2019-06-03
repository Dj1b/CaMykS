<?php
/**
 * @brief Admin_SystemNotifications Module admin view configuration sub layout
 * @details Plugin / Module layout
 * @file plugin/module/Admin_SystemNotifications/html/configuration/view.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: May 2019
 * @date Modification: May 2019
 * @copyright 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/
global $camyks;
?>

<?php if (isset($this->isConfig) and $this->isConfig) : ?>

    <?= $camyks->theme->get_boxContent2Header(); ?>
    <div class="adminContentPanel">

<?php endif; ?>

        <table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
            <tr>
                <td class="eTableHeader" colspan="2">
                    <?= $this->get_translation('formtitle_module'); ?>
                </td>
            </tr>
            <tr>
                <td class="eTableLine0 eContent2" style="width:160px;">
                    <?= $this->get_translation('formitem_mode'); ?>
                </td>
                <td class="eTableLine0 eContent1">
                    <?= $this->moduleModeList[$this->config->vars['module_mode']]; ?>
                </td>
            </tr>

            <?php if ($this->config->vars['module_mode'] == 1) : ?>
            <tr>
                <td class="eTableLine1 eContent2">
                    <?= $this->get_translation('formitem_delay'); ?>
                </td>
                <td class="eTableLine1 eContent1">
                    <?= $this->config->vars['module_checkDelay'].$this->get_translation('unit_minutes'); ?>
                </td>
            </tr>
            <?php endif; ?>

            <tr>
                <td class="eTableLine0" colspan="2">
                    &nbsp;
                </td>
            </tr>
            <tr>
                <td class="eTableHeader" colspan="2">
                    <?= $this->get_translation('formtitle_access'); ?>
                </td>
            </tr>

            <tr>
                <td class="eTableLine0 eContent2">
                    <?= $this->get_translation('formitem_status'); ?>
                </td>
                <td class="eTableLine0 eContent1">
                    <?= $this->accessStatusList[$this->config->vars['access_status']]; ?>
                </td>
            </tr>

            <tr>
                <td class="eTableLine1 eContent2">
                    <?= $this->get_translation('formitem_authentication'); ?>
                </td>
                <td class="eTableLine1 eContent1">
                    <?= $this->accessAuthenticationList[$this->config->vars['access_authentication']]; ?>
                </td>
            </tr>

            <?php if ($this->config->vars['access_authentication'] == 1) : ?>

                <tr>
                    <td class="eTableLine0 eContent2">
                        <?= $this->get_translation('formitem_login'); ?>
                    </td>
                    <td class="eTableLine0 eContent1">
                        <?= $this->adminList[$this->config->vars['access_authLogin']]; ?>
                    </td>
                </tr>

            <?php endif; ?>

            <?php if ($this->config->vars['access_authentication'] == 2) : ?>

                <tr>
                    <td class="eTableLine0 eContent2">
                        <?= $this->get_translation('formitem_ipaddress'); ?>
                    </td>
                    <td class="eTableLine0 eContent1">
                        <?php if ($this->config->vars['access_authIP'] != '') : ?>
                            <?= $this->config->vars['access_authIP']; ?>
                        <?php else : ?>
                            <?= $this->get_translation('addressip_sameserver'); ?>
                        <?php endif; ?>
                    </td>
                </tr>

            <?php endif; ?>

            <?php if ($this->isConfig == false and $this->check_right(1)) : ?>
                <tr>
                    <td colspan="2">
                        &nbsp;
                    </tr>
                </tr>

                <tr>
                    <td colspan="2">
                        <?= $this->theme->get_button(array(
                            'title' => $this->get_translation('edit_configuration'),
                            'url'   => $this->get_adminLink(array('mode'=>'edit_config')),
                        )); ?>
                    </td>
                </tr>
            <?php endif; ?>
        </table>

<?php if ($this->isConfig):?>

    </div>
    <?= $camyks->theme->get_boxContent2Footer(); ?>

<?php endif; ?>
