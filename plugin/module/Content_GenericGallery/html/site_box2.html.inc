<?php
/**
 * @brief Content_GenericGallery module, site, box type 2 layout
 * @details Plugin / Module Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jul 2007
 * @date Modification: May 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(); ?>
<?= $this->theme->get_boxContent2Header(); ?>

<?php $this->gallery->display(); ?>

<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxFooter(); ?>
