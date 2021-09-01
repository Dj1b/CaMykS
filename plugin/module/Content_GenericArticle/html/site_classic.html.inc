<?php
/**
 * @brief Content_GenericArticle module, site classic mode layout.
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
<div>
    <?php if ($this->articleitem->vars['title'] != '') : ?>
        <h1 class="eTitle1">
            <?= $this->articleitem->vars['title']; ?>
        </h1>
    <?php endif; ?>

    <?php if ($this->articleitem->vars['subtitle'] != '') : ?>
        <h2 class="eTitle2">
            <?= $this->articleitem->vars['subtitle']; ?>
        </h2>
    <?php endif; ?>

    <?php if ($this->articleitem->vars['author'] != '') : ?>
        <h3 class="eTitle3">
            <?= $this->get_translation('siteauthor', $this->articleAuthor['display']); ?>
        </h3>
    <?php endif; ?>

    <?php if ($this->articleitem->vars['date_'] != '') : ?>
        <h3 class="eTitle3">
            <?= date_displayDate($this->articleitem->vars['date_']); ?>
        </h3>
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
</div>
