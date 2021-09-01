<?php
/**
 * @brief Content_GenericBlogsViewer module, site panel box layout.
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
<div style="width:150px;">
    <?= $this->theme->get_boxHeader('width:100%'); ?>
    <?= $this->theme->get_boxContent1Header('padding:4px 8px'); ?>
    <?php if (count($this->configItem->vars['authors_']) != 1) : ?>
        <div class="eContent2">
            <?= $this->get_translation('panel_authors'); ?>
        </div>
        <div class="eContent1">
            <?php foreach ($this->panel_authors as $author => $count) : ?>
                <?= $this->get_blogNewsAuthorDisplay($author, 'eLink1'); ?> (<?= $count?>) <br />
            <?php endforeach; ?>
        </div>
    <?php endif; ?>

    <?php if (count($this->panel_tags) > 0) : ?>
    <div class="eContent2" style="padding-top:16px;">
        <?= $this->get_translation('panel_tags'); ?>
    </div>
    <div class="eContent1">
        <div class="eContent1">
            <?php foreach ($this->panel_tags as $value) : ?>
                <?php if ($count > 0) : ?>
                    <?= $this->get_blogNewsTagsDisplay(array($value['tag']), 'eLink1'); ?> (<?= $value['count']; ?>) <br />
                <?php endif; ?>
            <?php endforeach; ?>
        </div>
        <?php endif; ?>

        <?php if (count($this->panel_links) > 0) : ?>
            <div class="eContent2" style="padding-top:16px;">
                <?= $this->get_translation('panel_links'); ?>
            </div>
            <div class="eContent1">
                <?php foreach($this->panel_links as $link) : ?>
                    <a href="<?= $link->vars['link']; ?>" class="eLink1" target="_blank">
                        <?= $link->vars['title']; ?>
                    </a><br />
                <?php endforeach; ?>
            </div>
        <?php endif; ?>

        <?php if ($this->configItem->vars['panel_insert'] != '') : ?>
            <div class="eContent1">
                &nbsp;
            </div>
            <div class="eContent1">
                <?= $this->configItem->vars['panel_insert']; ?>
            </div>
        <?php endif; ?>
    </div>
    <?= $this->theme->get_boxContent1Footer(); ?>
    <?= $this->theme->get_boxFooter(); ?>
</div>
