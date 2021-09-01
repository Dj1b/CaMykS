<?php
/**
 * @brief Content_GoogleSearchResultsViewer module, site boxed layout.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Sep 2008
 * @date Modification: Jul 2021
 * @copyright 2008 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
?>
<?= $this->theme->get_boxHeader(); ?>
<?= $this->theme->get_boxTitlebar($this->get_translation('site_title')); ?>
<?= $this->theme->get_boxContent1Header(); ?>
<?= $this->load_file('html/_site_gsr.html.inc'); ?>
<?= $this->theme->get_boxContent1Footer(); ?>
<?= $this->theme->get_boxFooter(); ?>
