<?php
/**
 * @brief Content_GenericHTMLNews Module site view list, box title only layout.
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
<?= $this->theme->get_boxHeader(); ?>
<?= $this->theme->get_boxTitleBar($this->get_translation('site_title')); ?>
<?= $this->theme->get_boxContent1Header(); ?>
<?php foreach ($this->newsitems as $n) : ?>
    <div class="eTitle2">
        <a href="<?= $this->get_singlenewslink($n->id); ?>" class="eLink2">
            <?= $n->vars['title']; ?>
            <span class="eTitle3">
        -
        <?= $n->vars['author']; ?>
        -
        <?=date_displayShortDateHour($n->vars['ndate']); ?>
            </span>
        </a>
    </div>
<?php endforeach; ?>
<?= $this->theme->get_boxContent1Footer(); ?>
<?php if (isset($this->buttons)) : ?>
    <?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?php endif; ?>
<?= $this->theme->get_boxFooter(); ?>
