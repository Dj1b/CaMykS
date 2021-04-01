<?php
/**
 * @brief ReCaptcha Input layout
 * @details Plugin / Input layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Mar 2021
 * @date Modification: Mar 2021
 * @copyright 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;
/* Load cookie agreement plugin */
$input = $camyks->get_input('CookieAgreementMessage');
?>
<div class="error">
    <?= $this->get_translation('message_unavailable_title'); ?>
</div>
<div class="eContent1">
    <?= $this->get_translation('message_unavailable_content', $input->get_cookieManagementPanelOpenLink()); ?>
</div>

<?php
/**
 * @endcond Exclude
 */
?>
