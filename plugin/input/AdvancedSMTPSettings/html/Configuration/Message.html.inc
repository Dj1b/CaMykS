<?php
/**
 * @brief AdvancedSMTPSettings input, message layout.
 * @details Plugin / Input Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Jan 2026
 * @date Modification: Jan 2026
 * @copyright 2026 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<div style="margin:0 auto; width:330px; padding-top:100px;">
    <?= $camyks->theme->get_boxHeader('width:100%'); ?>
    <?= $camyks->theme->get_boxContent1Header('padding:20px 8px;'); ?>
        <div id="adminMessage" class="eContent1">
            <?= $this->configActionMessage; ?>
        </div>
    <?= $camyks->theme->get_boxContent1Footer(); ?>
    <?= $camyks->theme->get_boxFooter(); ?>
</div>
