<?php
/**
 * @brief Content_GenericHTMLNews Module site view list, box summary layout.
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
    <h2 class="eTitle2">
        <a href="<?= $this->get_singlenewslink($n->id); ?>" class="title3"><?= $n->vars['title']; ?></a>
        &nbsp;-&nbsp;
        <span class="eTitle4">
            <?= $this->get_translation('infos', array($n->vars['author'], date_displayLongDayDateHour($n->vars['ndate']))); ?>
        </span>
    </h2>

    <div style="0 16px;">
        <div class="eContent1">
            <?= nl2br($n->vars['summary']) ?>
        </div>
        <div class="eContent1">
            <a href="<?= $this->get_singlenewslink($n->id); ?>" class="eLink1">
                <?= $this->get_translation('readmore'); ?>
            </a>
        </div>
    </div>
    <?php endforeach; ?>

<?= $this->theme->get_boxContent1Footer(); ?>
<?php if (isset($this->buttons)) : ?>
    <?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?php endif; ?>
<?= $this->theme->get_boxFooter(); ?>
