<?php
/**
 * @brief Content_GenericMenu module, site vertical / left layers layout.
 * @details Plugin / Module Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Dec 2007
 * @date Modification: May 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<div class="cgmMain">
    <?php foreach ($this->root->children as $p) : ?>
        <?php $page = $this->pages[$p]; ?>
        <?php if ((!isset($page->metas['menu']) or $page->metas['menu']['content'] != 'hidden') and $page->active==1) : ?>
            <a class="cgmItem" href="<?= $page->get_siteLink(); ?>"
                <?php if (count($page->children)>0) : ?>
                    id="cgm<?= $this->mindex; ?>_<?= $page->name; ?>Button"
                    onmouseover="globalCMenu.select('cgm<?= $this->mindex; ?>_<?= $page->name; ?>Menu');"
                    onmouseout="globalCMenu.unselect('cgm<?= $this->mindex; ?>_<?= $page->name; ?>Menu');"
                <?php endif; ?>
            ><?= $page->shorttitle != '' ? $page->shorttitle : ($page->title != '' ? $page->title : $page->name); ?></a>
        <?php endif; ?>
    <?php endforeach; ?>
</div>

<?php foreach ($this->layeredMenu as $n => $m) : ?>
    <?= $this->theme->get_layeredMenu($n, 'globalCMenu', $m); ?>
<?php endforeach; ?>
