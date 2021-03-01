<?php
/**
 * @brief Admin_GooglePoIMapManager Module admin main layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jun 2010
 * @date Modification: Jan 2021
 * @copyright 2010 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title); ?>
<?= $this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<div id="itempoints" style="display:<?= $this->tabBuilder->get_tabDisplay('points'); ?>;" class="adminContentPanel">
    <?= $this->pointList->display('head'); ?>
    <?= $this->pointList->display('list'); ?>
</div>

<div id="itemcategories" style="display:<?= $this->tabBuilder->get_tabDisplay('categories'); ?>;" class="adminContentPanel">
    <?= $this->catList->display('head'); ?>
    <?= $this->catList->display('list'); ?>
</div>

<div id="itemicons" style="display:<?= $this->tabBuilder->get_tabDisplay('icons'); ?>;" class="adminContentPanel">
    <?= $this->iconList->display('head'); ?>
    <?= $this->iconList->display('list'); ?>
</div>

<?php if ($this->check_right(3)) : ?>
<div id="itemconfig" style="display:<?= $this->tabBuilder->get_tabDisplay('config'); ?>;" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableLine0 eContent2" style="width:150px;">
                <?= $this->get_translation('formitem_googlemapapikey'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?php if ($this->config->vars['google_mapapikey'] == '') : ?>
                    <?= $this->get_translation('noapikey'); ?>
                <?php else : ?>
                    <?= $this->config->vars['google_mapapikey']; ?>
                <?php endif; ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0" colspan="2">
                <?= $this->theme->get_button(array('title'=>$camyks->get_translation('edit'), 'url'=>$this->get_adminLink(array('mode'=>'edit_config')))); ?>
            </td>
        </tr>
    </table>
</div>
<?php endif; ?>

<?php if ($this->help != null) : ?>
    <div id="itemhelp" style="display:<?= $this->tabBuilder->get_tabDisplay('help'); ?>;" class="adminContentPanel">
        <?php $this->display_help(); ?>
    </div>
<?php endif; ?>

<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
