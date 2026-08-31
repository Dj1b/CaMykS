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
?>
<p class="eContent1">
    <?= $this->get_translation('redirectobankmessage'); ?>
</p>

<p class="eContent1">
    <?= $this->get_translation('redirectobankmessage2', array($this->redirectURL, 'eLink1')); ?>
</p>
