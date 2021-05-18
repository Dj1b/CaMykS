<?php
/**
 * @brief Content_GenericNews Module site display item, complete layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Mar 2007
 * @date Modification: May 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(); ?>
<?= $this->theme->get_boxTitleBar($this->get_translation('site_title')); ?>
<?= $this->theme->get_boxContent1Header('padding:8px;'); ?>
<h2 class="eTitle3">
    <?= $this->newsitem->vars['title']; ?>
</h2>

<h3 class="eTitle4">
    <?= $this->get_translation('infos', array($this->newsitem->vars['author'], date_displayLongDayDateHour($this->newsitem->vars['ndate']))); ?>
</h3>

<blockquote>
    <p class="eContent1">
        <?= nl2br($this->newsitem->vars['content']); ?>
    </p>

    <?php if ($this->newsitem->vars['source_title'] != '' and $this->newsitem->vars['source_url'] != '') : ?>
        <p class="eContent3">
             <?= $this->get_translation('sourcelnk'); ?>
             <a href="<?= $this->newsitem->vars['source_url']; ?>" class="eTitle4"><?= $this->newsitem->vars['source_title']; ?></a>
        </p>
    <?php elseif ($this->newsitem->vars['source_title'] != '') : ?>
        <p class="eContent3">
            <?= $this->get_translation('sourcelnk'); ?><?= $this->newsitem->vars['source_title']; ?>
        </p>
    <?php endif; ?>
    <div class="eContent1">
        &nbsp;
    </div>
<?= $this->theme->get_boxContent1Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
