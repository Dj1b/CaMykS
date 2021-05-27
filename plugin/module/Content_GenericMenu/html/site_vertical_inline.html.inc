<?php
/**
 * @brief Content_GenericMenu module, site vertical / inline layout.
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
<div class="cgmMain">
    <?php foreach ($this->root->children as $p) : ?>
        <?php $page = $this->pages[$p]; ?>
            <?php if ((!isset($page->metas['menu']) or $page->metas['menu']['content'] != 'hidden') and $page->active==1) : ?>
                <a class="cgmItem" href="<?= $page->get_siteLink(); ?>">
                    <?= $page->shorttitle != '' ? $page->shorttitle : ($page->title != '' ? $page->title : $page->name); ?>
                </a>

                <?php foreach ($page->children as $p) : ?>
                    <?php $pagel2 = $this->pages[$p]; ?>
                    <?php if (!isset($pagel2->metas['menu']) or $pagel2->metas['menu']['content'] != 'hidden') : ?>
                        <a class="cgmItemL2" href="<?= $pagel2->get_siteLink(); ?>">
                            <?= $pagel2->shorttitle != '' ? $pagel2->shorttitle : ($pagel2->title != '' ? $pagel2->title : $pagel2->name); ?>
                        </a>

                        <?php foreach ($pagel2->children as $p) : ?>
                            <?php $pagel3 = $this->pages[$p]; ?>
                            <?php if (!isset($pagel2->metas['menu']) or $pagel2->metas['menu']['content'] != 'hidden') : ?>
                                <a class="cgmItemL3" href="<?= $pagel3->get_siteLink(); ?>">
                                    <?= $pagel3->shorttitle != '' ? $pagel3->shorttitle : ($pagel3->title != '' ? $pagel3->title : $pagel3->name); ?>
                                </a>
                            <?php endif; ?>
                        <?php endforeach; ?>

                <?php endif; ?>
            <?php endforeach; ?>

        <?php endif; ?>
    <?php endforeach; ?>
</div>
