<?php
/**
 * @brief BreadCrumbs Input layout
 * @details Plugin / Input Layout
 * @file plugin/input/BreadCrumbs/html/input.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jul 2008
 * @date Modification: Apr 2018
 * @copyright 2008 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
?>
<div class="<?=$this->params['container_class']?>">
    <?php foreach($this->path as $page) : ?>
    <div style="display:inline;">
        <span class="<?=$this->params['text_class']?>">
            <?=$this->params['separator']?>
        </span>
        <?php if ($page['url'] !== false ) : ?>
        <a href="<?=$page['url']?>" class="<?=$this->params['link_class']?>"><?=$page['title'];?></a>
        <?php else : ?>
        <span class="<?=$this->params['text_class']?>">
            <?=$page['title'];?>
        </span>
        <?php endif; ?>
    </div>
    <?php endforeach; ?>
</div>
<?php 
/**
 * @endcond Exclude
 */
?>