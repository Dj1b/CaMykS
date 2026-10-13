<?php
/**
 * @brief PaylinePayment input, main layout.
 * @details Plugin / Input layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Apr 2026
 * @date Modification: Apr 2026
 * @copyright 2026 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>

<p class="eContent1">
    <?= $this->get_translation('error_occured_while_connecting_bank'); ?>
</p>

<p class="eContent1">
    <?= $this->get_translation('error_sorry'); ?>
</p>

<p class="eContent1">
    <?= $this->get_translation('error_retry_later'); ?>
</p>

<p class="eContent1">
    <?= $camyks->theme->get_button(array(
        'title' => $this->get_translation('action_back'),
        'url'   => $this->redirectURL,
    )); ?>
</p>
