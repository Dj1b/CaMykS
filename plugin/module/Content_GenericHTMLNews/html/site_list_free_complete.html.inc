<?php
/**
 * @brief Content_GenericHTMLNews Module site view list, free complete layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Dec 2007
 * @date Modification: May 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
?>
<div>
    <h1 class="eTitle1">
        <?= $this->get_translation('site_title'); ?>
    </h1>

    <?php foreach ($this->newsitems as $n) : ?>
        <h2 class="eTitle2">
            <?= $n->vars['title']; ?>
        </h2>

        <h3 class="eTitle3">
            <?= $this->get_translation('infos', array($n->vars['author'], date_displayLongDayDateHour($n->vars['ndate']))); ?>
        </h3>

        <div style="padding:0 16px 16px;">
            <?php if ($n->vars['source_title'] != '') : ?>
            <h4 class="eTitle4">
                <?= $this->get_translation('sourcelnk'); ?>
                <?php if ($n->vars['source_url'] != '') : ?>
                    <a href="<?= $n->vars['source_url']; ?>" class="eLink1">
                        <?= $n->vars['source_title']; ?>
                    </a>
                <?php else : ?>
                    <?= $n->vars['source_title']; ?>
                <?php endif; ?>
            </h4>
            <?php endif; ?>

            <?php if (file_exists($n->vars['content'])) : ?>
                <?php include $n->vars['content']; ?>
            <?php endif; ?>

            <?php if ($this->networkInput !== false) : ?>
                <?= $this->networkInput->display(array('link'=>$this->get_singlenewslink($n->id))); ?>
            <?php endif; ?>
        </div>
    <?php endforeach; ?>
    <?php $this->load_file('html/site_list_free_buttonsbar.html.inc'); ?>
</div>
