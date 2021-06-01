<?php
/**
 * @brief Content_GenericHTMLNews Module site view list, free title only layout.
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
        <div class="eTitle2">
            <a href="<?= $this->get_singlenewslink($n->id); ?>">
                <?= $n->vars['title']; ?>
                <span class="title4">
                    -
                    <?= $n->vars['author']; ?>
                    -
                    <?= date_displayShortDateHour($n->vars['ndate']); ?>
                </span>
            </a>
        </div>
    <?php endforeach; ?>
    <?php $this->load_file('html/site_list_free_buttonsbar.html.inc'); ?>
</div>
