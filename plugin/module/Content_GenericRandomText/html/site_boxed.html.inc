<?php
/**
 * @brief Content_GenericRandomText module, site boxed layout.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jun 2007
 * @date Modification: Jul 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
?>
<?= $this->theme->get_boxHeader(); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<div style="padding:8px 2px;">
<?= $this->text; ?>
</div>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxFooter(); ?>
