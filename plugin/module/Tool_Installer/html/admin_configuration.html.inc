<?php
/**
 * @brief Tool_Installer Module configuration layout
 * @details Plugin / Module Layout
 * @file plugin/module/Tool_Installer/html/admin_configuration.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Oct 2017
 * @date Modification: May 2019
 * @copyright 2017 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $camyks->theme->get_boxHeader(array('class'=>'adminEditorModule', 'style'=>'width:700px; margin:30px auto;')); ?>
<?= $camyks->theme->get_boxTitleBar($this->title); ?>
<?= $camyks->theme->get_boxContent2Header(); ?>

<?= $this->configForm->display_header(); ?>
<?= $this->configForm->display_hiddens(); ?>

    <div class="eTableHeader">
        <?= $this->get_translation('formtitle_configuration'); ?>
    </div>

    <div id="tabWebsite" class="eTableSubHeader" style="cursor:pointer" onclick="cTabs.mouseclick('Website');">
        <?= $this->get_translation('formtitle_website'); ?>
    </div>

    <div id="itemWebsite" class="adminContentPanel" style="display:none;">
        <table cellspacing="0" cellpadding="0" style="width:100%;">
            <tr>
                <td class="eTableLine0 eContent2" style="width:150px;">
                    <?= $this->get_translation('formitem_title'); ?>
                </td>
                <td class="eTableLine0">
                    <?= $this->configForm->display_textInput('site_title'); ?>
                </td>
            </tr>
            <tr>
                <td class="eTableLine1 eContent2">
                    <?= $this->get_translation('formitem_version'); ?>
                </td>
                <td class="eTableLine1">
                    <?= $this->configForm->display_textInput('version'); ?>
                </td>
            </tr>
            <tr>
                <td class="eTableLine0 eContent2">
                    <?= $this->get_translation('formitem_encoding'); ?>
                </td>
                <td class="eTableLine0">
                    <?= $this->configForm->display_selectInput(array('name'=>'encoding', 'values'=>$this->encodingList)); ?>
                </td>
            </tr>
            <tr>
                <td class="eTableLine1 eContent2">
                    <?= $this->get_translation('formitem_author'); ?>
                </td>
                <td class="eTableLine1">
                    <?= $this->configForm->display_textInput(array('name'=>'site_author', 'maxlength'=>256)); ?>
                </td>
            </tr>
            <tr>
                <td class="eTableLine0 eContent2">
                    <?= $this->get_translation('formitem_company'); ?>
                </td>
                <td class="eTableLine0">
                    <?= $this->configForm->display_textInput(array('name'=>'site_company', 'maxlength'=>256)); ?>
                </td>
            </tr>
            <tr>
                <td colspan="2" class="eTableLine0">
                    &nbsp;
                </td>
            </tr>
        </table>
    </div>

    <div id="tabAdmin" class="eTableSubHeader" style="cursor:pointer" onclick="cTabs.mouseclick('Admin');">
        <?= $this->get_translation('formtitle_admin'); ?>
    </div>

    <div id="itemAdmin" class="adminContentPanel" style="display:none;">
        <table cellspacing="0" cellpadding="0" style="width:100%;">
            <tr>
                <td class="eTableLine0 eContent2" style="width:150px;">
                    <?= $this->get_translation('formitem_languages'); ?>
                </td>
                <td class="eTableLine0">
                    <?php foreach ($this->languages as $l => $title ) : ?>
                        <div style="display:inline-block; width:150px;">
                            <?= $this->configForm->display_checkboxInput(array('name'=>'admin_languages', 'multiValues'=>true, 'value'=>$l, 'label'=>$title)); ?>
                        </div>
                    <?php endforeach; ?>
                </td>
            </tr>
            <tr>
                <td class="eTableLine1 eContent2">
                    <?= $this->get_translation('formitem_default_language'); ?>
                </td>
                <td class="eTableLine1">
                    <?= $this->configForm->display_selectInput(array('name'=>'admin_default_language', 'values'=>$this->languages)); ?>
                </td>
            </tr>
            <tr>
                <td class="eTableLine0 eContent2">
                    <?= $this->get_translation('formitem_editing_languages'); ?>
                </td>
                <td class="eTableLine0">
                    <?php foreach ($this->languages as $l => $title ) : ?>
                        <div style="display:inline-block; width:150px;">
                            <?= $this->configForm->display_checkboxInput(array('name'=>'editing_languages', 'multiValues'=>true, 'value'=>$l, 'label'=>$title)); ?>
                        </div>
                    <?php endforeach; ?>
                </td>
            </tr>
            <tr>
                <td class="eTableLine1 eContent2">
                    <?= $this->get_translation('formitem_theme'); ?>
                </td>
                <td class="eTableLine1">
                    <?= $this->configForm->display_selectInput(array('name'=>'admin_default_theme', 'values'=>$this->adminThemeList)); ?>
                </td>
            </tr>
            <tr>
                <td class="eTableLine0 eContent2">
                    <?= $this->get_translation('formitem_ssl'); ?>
                </td>
                <td class="eTableLine0">
                    <?= $this->configForm->display_selectInput(array('name'=>'admin_ssl', 'values'=>$this->SSLModeList)); ?>
                </td>
            </tr>
            <tr>
                <td colspan="2" class="eTableLine0">
                    &nbsp;
                </td>
            </tr>
        </table>
    </div>

    <div id="tabSite" class="eTableSubHeader" style="cursor:pointer" onclick="cTabs.mouseclick('Site');">
        <?= $this->get_translation('formtitle_visitor'); ?>
    </div>

    <div id="itemSite" class="adminContentPanel" style="display:none;">
        <table cellspacing="0" cellpadding="0" style="width:100%;">
            <tr>
                <td class="eTableLine0 eContent2" style="width:150px;">
                    <?= $this->get_translation('formitem_languages'); ?>
                </td>
                <td class="eTableLine0" style="font-size:0;">
                    <?php foreach ($this->languages as $l => $title ) : ?>
                        <div style="display:inline-block; width:150px;">
                            <?= $this->configForm->display_checkboxInput(array('name'=>'site_languages', 'multiValues'=>true, 'value'=>$l, 'label'=>$title)); ?>
                        </div>
                    <?php endforeach; ?>
                </td>
            </tr>
            <tr>
                <td class="eTableLine1 eContent2">
                    <?= $this->get_translation('formitem_default_language'); ?>
                </td>
                <td class="eTableLine1">
                    <?= $this->configForm->display_selectInput(array('name'=>'site_default_language', 'values'=>$this->languages)); ?>
                </td>
            </tr>
            <tr>
                <td class="eTableLine0 eContent2">
                    <?= $this->get_translation('formitem_template'); ?>
                </td>
                <td class="eTableLine0">
                    <?= $this->configForm->display_selectInput(array('name'=>'site_default_template', 'values'=>$this->templateList)); ?>
                </td>
            </tr>
            <tr>
                <td class="eTableLine1 eContent2">
                    <?= $this->get_translation('formitem_theme'); ?>
                </td>
                <td class="eTableLine1">
                    <?= $this->configForm->display_selectInput(array('name'=>'site_default_theme', 'values'=>$this->siteThemeList)); ?>
                </td>
            </tr>
            <tr>
                <td class="eTableLine0 eContent2">
                    <?= $this->get_translation('formitem_ssl'); ?>
                </td>
                <td class="eTableLine0">
                    <?= $this->configForm->display_selectInput(array('name'=>'site_ssl', 'values'=>$this->SSLModeList)); ?>
                </td>
            </tr>
            <tr>
                <td class="eTableLine1 eContent2">
                    <?= $this->get_translation('formitem_maxmodules'); ?>
                </td>
                <td class="eTableLine1">
                    <?= $this->configForm->display_textInput('page_maxmodules'); ?>
                </td>
            </tr>
            <tr>
                <td colspan="2" class="eTableLine0">
                    &nbsp;
                </td>
            </tr>
        </table>
    </div>

    <div id="tabDatabase" class="eTableSubHeader" style="cursor:pointer" onclick="cTabs.mouseclick('Database');">
        <?= $this->get_translation('formtitle_database'); ?>
    </div>

    <div id="itemDatabase" class="adminContentPanel" style="display:none;">
        <table cellspacing="0" cellpadding="0" style="width:100%;">
            <tr>
                <td class="eTableLine0 eContent2" style="width:150px;">
                    <?= $this->get_translation('formitem_driver'); ?>
                </td>
                <td class="eTableLine0">
                    <?= $this->configForm->display_selectInput(array('name'=>'database_driver', 'values'=>$this->driverList)); ?>
                </td>
            </tr>
            <tr>
                <td class="eTableLine1 eContent2">
                    <?= $this->get_translation('formitem_host'); ?>
                </td>
                <td class="eTableLine1">
                    <?= $this->configForm->display_textInput('database_host'); ?>
                </td>
            </tr>
            <tr>
                <td class="eTableLine0 eContent2">
                    <?= $this->get_translation('formitem_name'); ?>
                </td>
                <td class="eTableLine0">
                    <?= $this->configForm->display_textInput('database_name'); ?>
                </td>
            </tr>
            <tr>
                <td class="eTableLine1 eContent2">
                    <?= $this->get_translation('formitem_login'); ?>
                </td>
                <td class="eTableLine1">
                    <?= $this->configForm->display_textInput('database_login'); ?>
                </td>
            </tr>
            <tr>
                <td class="eTableLine0 eContent2">
                    <?= $this->get_translation('formitem_password'); ?>
                </td>
                <td class="eTableLine0">
                    <?= $this->configForm->display_passwordInput('database_pwd'); ?>
                </td>
            </tr>
            <tr>
                <td colspan="2" class="eTableLine0">
                    &nbsp;
                </td>
            </tr>
        </table>
    </div>

    <div id="tabWebmaster" class="eTableSubHeader" style="cursor:pointer" onclick="cTabs.mouseclick('Webmaster');">
        <?= $this->get_translation('formtitle_webmaster'); ?>
    </div>

    <div id="itemWebmaster" class="adminContentPanel" style="display:none;">
        <table cellspacing="0" cellpadding="0" style="width:100%;">
            <tr>
                <td colspan="2" class="eTableLine0 eContent3">
                    <?= $this->get_translation('formdesc_webmaster'); ?>
                </td>
            </tr>
            <tr>
                <td class="eTableLine1 eContent2" style="width:150px;">
                    <?= $this->get_translation('formitem_login'); ?>
                </td>
                <td class="eTableLine1">
                    <?= $this->configForm->display_textInput('webmaster_login'); ?>
                </td>
            </tr>
            <tr>
                <td class="eTableLine0 eContent2">
                    <?= $this->get_translation('formitem_password'); ?>
                </td>
                <td class="eTableLine0">
                    <?= $this->configForm->display_passwordInput('webmaster_password'); ?>
                </td>
            </tr>
            <tr>
                <td class="eTableLine1 eContent2">
                    <?= $camyks->get_translation('formitem_email'); ?>
                </td>
                <td class="eTableLine1">
                    <?= $this->configForm->display_textInput('webmaster_email'); ?>
                </td>
            </tr>
            <tr>
                <td colspan="2" class="eTableLine0">
                    &nbsp;
                </td>
            </tr>
        </table>
    </div>

    <div id="tabOptions" class="eTableSubHeader" style="cursor:pointer" onclick="cTabs.mouseclick('Options');">
        <?= $this->get_translation('formtitle_options'); ?>
    </div>

    <div id="itemOptions" class="adminContentPanel" style="display:none;">
        <table cellspacing="0" cellpadding="0" style="width:100%;">
            <tr>
                <td class="eTableLine0 eContent2">
                    <?= $this->get_translation('formitem_mobilemode'); ?>
                </td>
                <td class="eTableLine0">
                    <?= $this->configForm->display_selectInput(array('name'=>'mobileMode', 'values'=>$this->mobileModeList)); ?>
                </td>
            </tr>
            <tr>
                <td colspan="2" class="eTableLine0">
                    &nbsp;
                </td>
            </tr>
        </table>
    </div>

<?= $this->configForm->display_footer(); ?>

<?= $camyks->theme->get_boxContent2Footer(); ?>
<?= $camyks->theme->get_boxButtonsBar($this->buttons); ?>
<?= $camyks->theme->get_boxFooter(); ?>
