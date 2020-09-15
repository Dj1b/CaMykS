<?php
/**
 * @brief Admin_Statistics Module admin menu layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: May 2007
 * @date Modification: Sep 2020
 * @copyright 2007 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;
$edit = $this->theme->get_pictURL('edit', 12, 'std');
$edit_ = $this->theme->get_pictURL('edit', 12, 'ovr');
$view = $this->theme->get_pictURL('view', 12, 'std');
$view_ = $this->theme->get_pictURL('view', 12, 'ovr');
?>
<div class="statistics_menu">
    <?php if ($this->check_right(1)) : ?>
    <div class="eTableSubHeader eContent2">
        <a href="<?= $this->get_adminLink(array('object'=>'_settings')); ?>" class="eLink2">
            <?= $this->get_translation('settings'); ?>
            <img src="<?= $edit; ?>" class="button" alt="<?= $this->get_translation('settings'); ?>" title="<?= $this->get_translation('settings'); ?>"
                onmouseover="this.src='<?= $edit_; ?>';" onmouseout="this.src='<?= $edit; ?>';" />
        </a>
    </div>
    <?php endif; ?>

    <div class="eTableHeader">
        <?= $this->get_translation('objects'); ?>
    </div>

    <?php $alt = 0; ?>
    <?php foreach ($this->registered_stats as $stat) : ?>
        <?php if (!isset($this->settings->vars['stat_'.$stat->vars['name']]) or $this->settings->vars['stat_'.$stat->vars['name']]) : ?>
            <div class="eTableLine<?= $alt; ?>">
                <a href="<?= $this->get_adminLink(array('object'=>$stat->vars['name'])); ?>" class="eLink1">
                    <?= $stat->vars['title']; ?>
                    <img src="<?= $view; ?>" class="button" alt="<?= $stat->vars['title']; ?>" title="<?= $stat->vars['title']; ?>"
                        onmouseover="this.src='<?= $view_; ?>';" onmouseout="this.src='<?= $view; ?>';" />
                </a>
            </div>
            <?php $alt = abs($alt-1); ?>
        <?php endif; ?>
    <?php endforeach; ?>
</div>
<?php
/**
 * @endcond Exclude
 */
?>
