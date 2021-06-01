<?php
/**
 * @brief Content_GenericNews Module site display list, custom layout.
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
<?= $this->theme->get_boxContent2Header('padding:8px;'); ?>
<table cellspacing="0" cellpadding="0" border="0" width="100%">
    <?php foreach ($this->newsitems as $n) : ?>
        <tr>
            <td class="eTitle3" style="text-align:left;">
                <?= $n->vars['title']; ?>
            </td>
        </tr>
        <tr>
            <td class="eTitle4" style="text-align:left">
                <?= $this->get_translation('infos', array($n->vars['author'], date_displayLongDayDateHour($n->vars['ndate']))); ?>
            </td>
        </tr>
        <tr>
            <td class="eContent1" style="padding-left:16px;">
                <?= nl2br($n->vars['content']); ?>
             </td>
        </tr>
        <?php if ($n->vars['source_title'] != '' and $n->vars['source_url'] != '') : ?>
            <tr>
                <td class="eTitle4" style="padding:4px 16px;">
                    <?= $this->get_translation('sourcelnk'); ?>
                    <a href="<?= $n->vars['source_url']; ?>" class="eTitle4"><?= $n->vars['source_title']; ?></a>
                </td>
            </tr>
        <?php elseif ($n->vars['source_title'] != '') : ?>
            <tr>
                <td class="eTitle4" style="padding:4px 16px;">
                    <?= $this->get_translation('sourcelnk'); ?><?= $n->vars['source_title']; ?>
                </td>
            </tr>
        <?php endif; ?>
        <tr>
            <td>
                &nbsp;
            </td>
        </tr>
    <?php endforeach; ?>
</table>
<?= $this->theme->get_boxContent2Footer(); ?>
<?php if ($this->prevnews != '' or $this->nextnews != '') : ?>
    <?= $this->theme->get_boxButtonsBar($buttons); ?>
<?php endif; ?>
<?= $this->theme->get_boxFooter(); ?>
