<?php
/**
 * @brief TrustIndexCustomerReviews input, display layout.
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
    <?php if ($this->params['integrationMode'] === 'loader') : ?>
        <script defer async src="<?= htmlspecialchars($this->get_loaderUrl()); ?>"></script>
    <?php elseif ($this->params['integrationMode'] === 'raw') : ?>
        <?= $this->params['rawCode']; ?>
    <?php endif; ?>
</div>
<?php
/**
 * @endcond Exclude
 */
?>
