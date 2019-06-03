<?php
/**
 * @brief Tool_ControlPanel Module main layout
 * @details Plugin / Module Layout
 * @file plugin/module/Tool_ControlPanel/html/admin.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Sep 2005
 * @date Modification: May 2019
 * @copyright 2005 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;

$default = $camyks->site_data_url.'/img/module/default_icon32.gif';

?>
<div style="width:600px;" class="adminControlPanel">
    <?php foreach ($this->admin_modules as $g => $group) : ?>
    <?php if (count ($group)) : ?>
        <h1 class="eTitle2 adminControlPanelTitle">
            <?= $this->get_translation('g'.$g); ?>
        </h1>
        <table cellspacing="0" style="width:100%" class="adminControlPanelGroup">
        <?php $col = 0; ?>
        <?php foreach ($group as $mod) : ?>
            <?php $mod_lk = $camyks->get_adminLink($mod); ?>
            <?php if ($col == 0) : ?>
                <tr>
            <?php endif; ?>
            <td class="adminControlPanelItem" style="width:<?= ceil(100/$this->cols); ?>%;">
                <div style="float:left; padding:4px;">
                    <a href="<?= $mod_lk?>">
                        <img src="<?= $camyks->modules[$mod]->get_fileURL('img/icon32.gif', null, $default); ?>" alt="<?= $camyks->modules[$mod]->title; ?>" style="width:32px; height:32px; float:left;"/>
                    </a>
                </div>
                <div class="pluginTitle">
                    <a class="eTitle3" href="<?= $mod_lk?>">
                        <?= $camyks->modules[$mod]->title; ?>
                    </a>
                </div>
                <div class="pluginDesc">
                    <div class="eTitle4">
                        <?= $camyks->get_translation('mod_'.$mod.'_desc'); ?>
                    </div>
                </div>
            </td>
            <?php if (++$col == $this->cols) : ?>
                <?php $col = 0; ?>
                </tr>
            <?php endif; ?>
        <?php endforeach; ?>
        <?php if ($col != 0) : ?>
            <?php for ($i=$col; $i < $this->cols; $i++) : ?>
                <td class="adminControlPanelItem"></td>
            <?php endfor; ?>
            </tr>
        <?php endif; ?>
        </table>
    <?php endif; ?>
    <?php endforeach; ?>
</div>
<?php
/**
 * @endcond Exclude
 */
?>
