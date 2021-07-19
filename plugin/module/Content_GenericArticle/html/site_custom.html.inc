<?php
/**
 * @brief Content_GenericArticle module, site custom mode layout.
 * @details Plugin / Module Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Sep 2007
 * @date Modification: Jul 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(); ?>
    <?php if ($this->articleitem->vars['title'] != '') : ?>
        <?= $this->theme->get_boxTitleBar($this->articleitem->vars['title']); ?>
    <?php endif; ?>
<?= $this->theme->get_boxContent1Header(); ?>

<?php if ($this->articleitem->vars['subtitle'] != '') : ?>
    <h1 class="eTitle2">
        <?= $this->articleitem->vars['subtitle']; ?>
    </h1>
<?php endif; ?>

<?php if ($this->articleitem->vars['author'] != '') : ?>
    <h2 class="eTitle3">
        <?= $this->get_translation('siteauthor', $this->articleAuthor['display']); ?>
    </h2>
<?php endif; ?>

<?php if ($this->articleitem->vars['date_'] != '') : ?>
    <p class="eTitle3">
        <?= date_displayDate($this->articleitem->vars['date_']); ?>
    </p>
<?php endif; ?>

<?php if ($this->articleitem->vars['header'] != '') : ?>
    <p class="eContent2">
        <?= nl2br($this->articleitem->vars['header']); ?>
    </p>
<?php endif; ?>

<?php if (file_exists($this->articleitem->vars['content'])) : ?>
    <?php include $this->articleitem->vars['content']; ?>
<?php endif; ?>

<?php if ($this->articleitem->vars['note'] != '') : ?>
    <p class="eContent1">
        &nbsp;
    </p>
    <p class="eContent3">
        <?= nl2br($this->articleitem->vars['note']); ?>
    </p>
<?php endif; ?>
<?= $this->theme->get_boxContent1Footer(); ?>
<?= $this->theme->get_boxFooter(); ?>
