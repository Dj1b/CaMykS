<?php
/**
 * @brief Content_GenericSiteMap module, site text box 2 layout.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jul 2008
 * @date Modification: Jul 2021
 * @copyright 2008 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(); ?>
<?= $this->theme->get_boxTitleBar($this->get_translation('site_title')); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<?= $this->sitemap; ?>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxFooter(); ?>
