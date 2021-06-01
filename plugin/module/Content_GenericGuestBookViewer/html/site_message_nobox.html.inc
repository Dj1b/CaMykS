<?php
/**
 * @brief Content_GenericGuestBookViewer module, site message nobox layout.
 * @details Plugin / Module Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Sep 2010
 * @date Modification: May 2021
 * @copyright 2010 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<p class="eContent1">
    <?= $this->get_translation('message_submitted'); ?>
</p>

<p class="eContent1">
    <?= $this->theme->get_button(array(
        'title' => $camyks->get_translation('back'),
        'url'   => $camyks->get_siteLink($camyks->contentPage->id),
    )); ?>
</p>
