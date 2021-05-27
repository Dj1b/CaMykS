<?php
/**
 * @brief Content_GenericMenu module, site horizontal menu with layer layout.
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
<table cellspacing="0" class="cgmMainHTable">
    <tr>
        <?php foreach ($this->root->children as $p) : ?>
            <?php $page = $this->pages[$p]; ?>
            <?php if ((!isset($page->metas['menu']) or $page->metas['menu']['content'] != 'hidden') and $page->active==1) : ?>
                <td class="cgmHItem"
                    <?php if (count($page->children) > 0) : ?>
                        id="cgm<?= $this->mindex; ?>_<?= $page->name; ?>Button"
                        onmouseover="this.className='cgmHItemOver';globalCMenu.select('cgm<?= $this->mindex; ?>_<?= $page->name; ?>Menu');"
                        onmouseout="this.className='cgmHItem';globalCMenu.unselect('cgm<?= $this->mindex; ?>_<?= $page->name; ?>Menu');">
                    <?php else : ?>
                        onmouseover="this.className='cgmHItemOver';" onmouseout="this.className='cgmHItem';">
                    <?php endif; ?>
                    <a class="cgmHItem" href="<?= $page->get_siteLink(); ?>">
                        <?= $page->shorttitle != '' ? $page->shorttitle : ($page->title != '' ? $page->title : $page->name); ?>
                    </a>
                </td>
            <?php endif; ?>
        <?php endforeach; ?>
    </tr>
</table>

<?php foreach ($this->layeredMenu as $n => $m) : ?>
    <?= $this->theme->get_layeredMenu($n, 'globalCMenu', $m); ?>
<?php endforeach; ?>
