<?php
/**
 * @brief Content_GenericGlossaryViewer module site nobox layout.
 * @details Plugin / Module Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: May 2010
 * @date Modification: Jan 2020
 * @copyright 2010 - 2020 Ideogram Design
 */
global $camyks;
$l = '';
?>
<?= $this->configItem->vars['content']; ?>
<div>
    <?php if ($this->configItem->vars['pagemode'] == 0) : ?>
        <?= $this->pageController->display(); ?>
    <?php else : ?>
        <div class="eTableLine1" style="text-align:center;">
            <?php $first = true; ?>
            <?php foreach($this->pages as $title => $link) : ?>
                <?php if ($first) : ?>
                    <?php $first = false; ?>
                <?php else : ?>
                    -
                <?php endif; ?>

                <a href="<?= $link?>" class="eLink1"><?= $title?></a>
            <?php endforeach; ?>
        </div>
    <?php endif; ?>
</div>

<?php foreach($this->wordList as $word) : ?>
    <?php if (substr($word->vars['word'], 0, 1) != $l) : ?>
        <?php $l = substr($word->vars['word'], 0, 1); ?>
        <h2 class="eTitle2" style="font-size:40px">
            <?= strtoupper($l); ?>
        </h2>
    <?php endif; ?>

    <div class="definition">
        <?php $w = $word->vars['word']; ?>
        <a class="eTitle2" name="<?= $w; ?>" href="<?= $this->get_pageLink(null, $w)?>">
            <?= $w; ?>
        </a>

        <?php if (count($this->configItem->vars['categories_']) != 1) : ?>
            <h3 class="eTitle3">
                <?= $camyks->get_translation('formitem_category'); ?>
                <?= $this->categoryList[$word->vars['category']]; ?>
            </h3>
        <?php endif; ?>

        <div class="description">
            <?= $word->vars['description']; ?>
        </div>
    </div>
<?php endforeach; ?>
