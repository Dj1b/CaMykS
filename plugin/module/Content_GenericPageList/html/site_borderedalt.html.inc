<?php
/**
 * @brief Content_GenericPageList module, site, with border and alt lines layout.
 * @details Plugin / Module Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Nov 2007
 * @date Modification: May 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
$alt=0;
?>
<?= $this->theme->get_boxHeader('width:100%;'); ?>
<?php if ($this->plitem->vars['title'] != '') : ?>
    <?= $this->theme->get_boxTitleBar($this->plitem->vars['title']); ?>
<?php endif; ?>
<?= $this->theme->get_boxContent1Header('padding:12px;'); ?>
<table cellspacing="0" style="width:100%">
    <?php foreach ($this->plitem->vars['pages'] as $p) : ?>
        <?php $page = $this->pages[$p]; ?>
        <tr>
            <td class="eTableLine<?= $alt; ?>" style="padding:4px">
                <a class="eLink1" href="<?= $page->get_siteLink(); ?>">
                    <?= $page->title; ?>
                </a>
            </td>
        </tr>
        <?php $alt=abs($alt-1); ?>
    <?php endforeach; ?>
</table>
<?= $this->theme->get_boxContent1Footer(); ?>
<?= $this->theme->get_boxFooter(); ?>
