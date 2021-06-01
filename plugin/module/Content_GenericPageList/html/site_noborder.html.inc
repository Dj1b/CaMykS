<?php
/**
 * @brief Content_GenericPageList module, site, no border layout.
 * @details Plugin / Module Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Nov 2007
 * @date Modification: May 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<h1 class="eTitle1">
    <?= $this->plitem->vars['title']?>
</h1>
<?php foreach ($this->plitem->vars['pages'] as $p) : ?>
    <?php $page = $this->pages[$p]; ?>
    <div style="padding:4px 0px;">
        <a class="eLink1" href="<?= $page->get_siteLink(); ?>">
            <?= $page->title; ?>
        </a>
    </div>
<?php endforeach; ?>
