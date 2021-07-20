<?php
/**
 * @brief Content_GoogleMapsViewer module, site classic layout.
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
<?php if ($this->mapItem->vars['title']!='') : ?>
    <h1 class="eTitle1">
        <?= $this->mapItem->vars['title']; ?>
    </h1>
<?php endif; ?>
<p class="eContent1">
    <?= nl2br($this->mapItem->vars['description']); ?>
</p>
<?= $this->load_file('html/_site_map.html.inc'); ?>
