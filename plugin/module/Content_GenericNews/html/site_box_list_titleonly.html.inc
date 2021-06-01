<?php
/**
 * @brief Content_GenericNews Module site display list, title only layout.
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
<table cellspacing="0" cellpadding="0" border="0" width="100%">
    <?php foreach ($this->newsitems as $n) : ?>
        <tr>
            <td class="eTitle3" style="text-align:left;">
                <a href="<?= $this->get_singlenewslink($n->id)?>" class="eTitle3">
                    <?= $n->vars['title']; ?>
                    <span class="eTitle4">
                        -
                        <?= $n->vars['author']; ?>
                        -
                        <?= date_displayShortDateHour($n->vars['ndate']); ?>
                    </span>
                </a>
            </td>
        </tr>
        <tr>
            <td>
                &nbsp;
            </td>
        </tr>
    <?php endforeach; ?>
</table>
<?= $this->theme->get_boxContent1Footer(); ?>
<?php if ($this->prevnews != '' or $this->nextnews != '') : ?>
    <?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?php endif; ?>
<?= $this->theme->get_boxFooter(); ?>
