<?php
/**
 * @brief Content_SystemSiteReport module, site box send layout.
 * @details Plugin / Module Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Apr 2007
 * @date Modification: Jul 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader('width:300px; margin0 auto;'); ?>
<?php if ($this->rfitem->title_mode > 0) : ?>
    <?= $this->theme->get_boxTitleBar($this->rfitem->get_siteTitle()); ?>
<?php endif; ?>
<?= $this->theme->get_boxContent2Header(); ?>
<table cellspacing="0" cellpadding="4" border="0">
    <tr>
        <td colspan="2" class="">
            <?= $this->get_translation('requestsent'); ?>
        </td>
    </tr>
</table>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar(array(array('title'=> $this->get_translation('backtohome'), 'link'=> $camyks->get_siteHomepageLink())), 1); ?>
<?= $this->theme->get_boxFooter(); ?>
