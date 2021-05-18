<?php
/**
 * @brief Content_GenericHTMLNews Module site view item, complete layout.
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
    <h2 class="eTitle2">
        <?= $this->newsitem->vars['title']; ?>
    </h2>

    <h3 class="eTitle3">
        <?= $this->get_translation('infos', array($this->newsitem->vars['author'], date_displayLongDayDateHour($this->newsitem->vars['ndate']))); ?>
    </h3>

    <div style="padding:0 16px;">
        <?php if ($this->newsitem->vars['source_title'] != '') : ?>
        <h4 class="eTitle4">
            <?= $this->get_translation('sourcelnk'); ?>
            <?php if ($this->newsitem->vars['source_url'] != '') : ?>
                <a href="<?= $this->newsitem->vars['source_url']; ?>" class="eLink1">
                    <?= $this->newsitem->vars['source_title']; ?>
                </a>
            <?php else : ?>
                <?= $this->newsitem->vars['source_title']; ?>
            <?php endif; ?>
        </h4>
        <?php endif; ?>

        <?php if (file_exists($this->newsitem->vars['content'])) : ?>
            <?php include($this->newsitem->vars['content']); ?>
        <?php endif; ?>

        <?php if ($this->networkInput !== false) : ?>
            <?= $this->networkInput->display(); ?>
        <?php endif; ?>
    </div>
<?= $this->theme->get_boxContent1Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
