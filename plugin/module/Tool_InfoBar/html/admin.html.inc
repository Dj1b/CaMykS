<?php
/**
 * @brief Tool_InfoBar Module no admin user logged layout
 * @details Plugin / Module Layout
 * @file plugin/module/Tool_InfoBar/html/admin.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Oct 2005
 * @date Modification: May 2019
 * @copyright 2005 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->theme->get_barLeft('width:700px;'); ?>
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
    <tr>
        <td align="left">
            <table cellspacing="0" cellpadding="0">
                <tr>
                    <?php foreach ($this->barMenu as $name => $menu) : ?>
                        <?php if (count($menu['content']) > 0) : ?>
                            <td id="<?= $name?>Button">
                                <?= $camyks->theme->get_barButton($menu['title'],
                                    'javascript:globalCMenu.select(\''.$name.'Menu\');',
                                    '_'.$name.'_'); ?>
                            </td>
                        <?php endif; ?>
                    <?php endforeach; ?>
                </tr>
            </table>
        </td>
        <td align="right">
            <table cellspacing="0" cellpadding="0">
                <tr>
                    <td>
                        <?= $camyks->theme->get_barItem('', 'infobar_daytime'); ?>
                    </td>
                    <td>
                        <?= $camyks->theme->get_barItem('0m.', 'infobar_pagetime'); ?>
                    </td>
                    <?php if (isset($this->languageMenu)) : ?>
                    <td id="languageButton">
                        <?= $camyks->theme->get_barButton($this->languageMenu['title'],
                            'javascript:globalCMenu.select(\'languageMenu\');',
                            '_language_'); ?>
                    </td>
                    <?php endif; ?>
                </tr>
            </table>
        </td>
    </tr>
</table>
<?= $camyks->theme->get_barRight(); ?>

<?php foreach ($this->barMenu as $name => $menu) : ?>
<?php if (count($menu['content']) > 0) : ?>
<?= $camyks->theme->get_layeredMenu ($name.'Menu', 'globalCMenu', $menu['content']); ?>
<?php endif; ?>
<?php endforeach; ?>

<?php if (isset($this->languageMenu)) : ?>
<?= $camyks->theme->get_layeredMenu ('languageMenu', 'globalCMenu', $this->languageMenu['content']); ?>
<?php endif; ?>

<?php foreach ($camyks->modules as $module) : ?>
<?php $module->get_adminEngineGenericDisplay(); ?>
<?php endforeach; ?>
