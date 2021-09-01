<?php
/**
 * @brief Content_SystemSiteReport module, site simple sent layout.
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
<div style="width:300px; margin:0 auto;">
    <?php if ($this->rfitem->title_mode > 0) : ?>
        <div class="eTitle1">
            <?=$this->rfitem->get_siteTitle();?>
        </div>
    <?php endif; ?>
    <div class="eContent2" style="margin:8px;">
        <?= $this->get_translation('requestsent'); ?>
    </div>
    <div style="margin:8px" align="center">
        <?= $this->theme->get_button( $this->get_translation('backtohome'), $camyks->get_siteHomepageLink()); ?>
    </div>
</div>
