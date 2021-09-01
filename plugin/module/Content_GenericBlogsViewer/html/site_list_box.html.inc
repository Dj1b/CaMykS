<?php
/**
 * @brief Content_GenericBlogsViewer module, site list box layout.
 * @details Plugin / Module Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Apr 2008
 * @date Modification: Jul 2021
 * @copyright 2008 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?php if ($this->configItem->vars['list_panel'] == 1) : ?>
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%">
        <tr>
            <td style="vertical-align:top">
<?php endif; ?>

<?= $this->theme->get_boxHeader('width:100%'); ?>
<?= $this->theme->get_boxTitleBar($this->configItem->vars['title']); ?>
<?= $this->theme->get_boxContent1Header('padding:4px 8px'); ?>
<?php foreach ($this->blogItems as $b) : ?>
    <?php $newsLink = $this->get_singleNewsLink($b->id); ?>
    <h1 class="eTitle3">
        <a href="<?= $newsLink; ?>" class="eTitle3">
            <?= $b->vars['title']; ?>
        </a>
    </h1>
    <h2 class="eTitle4">
        <?= date_displayLongDayDateHour($b->vars['ndate']); ?>
    </h2>
    <?= $this->get_blogNewsContentDisplay($b->vars['content']); ?>
    <?php if ($b->vars['videolink'] != '') : ?>
        <div class="eContent1" style="text-align:center;">
            <?= $b->vars['videolink']; ?>
        </div>
    <?php endif; ?>

    <p class="eContent1" style="text-align:center;">
        <?php $authorValue = $this->get_blogNewsAuthorDisplay($b->vars['author'], 'eLink1'); ?>
        <?php $tagsValue = $this->get_blogNewsTagsDisplay($b->tagList, 'eLink1'); ?>

        <?php if ($authorValue != '' and $tagsValue != '') : ?>
            <?= $this->get_translation('published_by_into', array($authorValue, $tagsValue)); ?>
            &nbsp; &#124; &nbsp;
        <?php elseif ($authorValue != '') : ?>
            <?= $this->get_translation('published_by', $authorValue); ?>
            &nbsp; &#124; &nbsp;
        <?php elseif ($tagsValue != '') : ?>
            <?= $this->get_translation('published_into', $tagsValue, 'eLink1'); ?>
            &nbsp; &#124; &nbsp;
        <?php endif; ?>

        <?= $this->get_blogNewsCommentsDisplay($b->id, $b->vars['coms'], 'eLink1'); ?>
    </p>

    <?php if ($this->networkInput !== false) : ?>
        <div class="eContent1" style="text-align:center;">
            <?= $this->networkInput->display(array('link'=>$newsLink, 'title'=>$b->vars['title'])); ?>
        </div>
    <?php endif; ?>
    <p class="eContent1">
        &nbsp;
    </p>
<?php endforeach; ?>
<?= $this->theme->get_boxContent1Footer(); ?>

<?php if ($this->pageController == false): ?>
    <?php if (isset($this->buttons)) : ?>
        <?= $this->theme->get_boxButtonsBar($this->buttons); ?>
    <?php endif; ?>
<?php else : ?>
    <?= $this->theme->get_boxContent1Header(); ?>
    <?= $this->pageController->display(); ?>
    <?= $this->theme->get_boxContent1Footer(); ?>
<?php endif; ?>

<?= $this->theme->get_boxFooter(); ?>

<?php if ($this->configItem->vars['list_panel'] == 1) : ?>
        </td>
        <td style="vertical-align:top; padding-left:10px;">
            <?= $this->load_file('html/site_panel_box.html.inc'); ?>
        </td>
    </tr>
</table>
<?php endif; ?>
