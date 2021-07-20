<?php
/**
 * @brief Content_GoogleMapsViewer module, site boxed layout.
 * @details Plugin / Module Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jul 2008
 * @date Modification: Jul 2021
 * @copyright 2008 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
?>
<?= $this->theme->get_boxHeader(); ?>
<?php if ( $this->mapItem->vars['title']!='') : ?>
    <?= $this->theme->get_boxTitlebar($this->mapItem->vars['title']); ?>
<?php endif; ?>
<?= $this->theme->get_boxContent1Header(); ?>
<div>
<?= nl2br($this->mapItem->vars['description']); ?>
</div>
<?= $this->load_file('html/_site_map.html.inc'); ?>
<?= $this->theme->get_boxContent1Footer(); ?>
<?= $this->theme->get_boxFooter(); ?>
