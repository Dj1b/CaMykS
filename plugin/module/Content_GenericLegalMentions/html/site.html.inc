<?php
/**
 * @brief Content_GenericLegalMentions Module site main layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Jan 2020
 * @date Modification: Jan 2020
 * @copyright 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

?>
<h1 class="eTitle1">
    <?= $camyks->contentPage->get_longTitleDisplay('html'); ?>
</h1>

<?php $this->load_file('html/site/content.html.inc'); ?>
