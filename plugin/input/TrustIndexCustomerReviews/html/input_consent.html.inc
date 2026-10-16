<?php
/**
 * @brief TrustIndexCustomerReviews input, cookie consent pending layout.
 * @details Plugin / Input Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Oct 2026
 * @date Modification: Oct 2026
 * @copyright 2026 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
?>
<div class="<?= htmlspecialchars($this->params['containerClass']); ?>" style="<?= htmlspecialchars($this->get_containerStyle()); ?>">
    <div class="trustindex-consent-placeholder" style="padding: 12px; border: 1px dashed #cccccc; border-radius: 4px; font-size: 13px; color: #666666; background: #fafafa;">
        <?= $this->get_translation('cookie_consent_required'); ?>
    </div>
</div>
<?php
/**
 * @endcond Exclude
 */
?>
