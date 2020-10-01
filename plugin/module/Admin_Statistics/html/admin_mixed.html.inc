<?php
/**
 * @brief Admin_Statistics Module admin mixed object layout
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.4
 * @date Creation: May 2007
 * @date Modification: Sep 2020
 * @copyright 2007 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;
?>
<div class="statistics_display">
    <?= $this->theme->get_boxHeader(); ?>
    <?= $this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams); ?>
    <?= $this->theme->get_boxContent2Header(); ?>

    <?php $this->load_file('html/dated/tab.html.inc'); ?>

    <?php $this->load_file('html/detail/tab.html.inc'); ?>

    <?php $this->load_file('html/options/tab.html.inc'); ?>

    <?= $this->theme->get_boxContent2Footer(); ?>
    <?= $this->theme->get_boxFooter(); ?>
</div>
<?php
/**
 * @endcond Exclude
 */
?>
