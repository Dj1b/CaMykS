<?php
/**
 * @brief Content_GenericHTMLContent module, site, large box layout.
 * @details Plugin / Module Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: May 2008
 * @date Modification: May 2021
 * @copyright 2008 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
?>
<?= $this->theme->get_boxHeader('width:100%;'); ?>
<?= $this->theme->get_boxContent1Header(); ?>
<?php $this->content->write_content(); ?>
<?= $this->theme->get_boxContent1Footer(); ?>
<?= $this->theme->get_boxFooter(); ?>
