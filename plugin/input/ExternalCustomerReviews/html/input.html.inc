<?php
/**
 * @brief ExternalCustomerReviews input, site main layout.
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
global $camyks;

if (!is_array($this->reviewsData))
    return;

$data = $this->reviewsData;
$sourceKey = strtolower($data['source']);
$layout = $this->params['layout'];
$showSummary = ($this->params['showSummary'] == 1 or $layout === 'badge');
?>
<div class="externalCustomerReviews layout-<?= htmlspecialchars($layout); ?> source-<?= htmlspecialchars($sourceKey); ?>">
    <?php if ($showSummary) : ?>
        <div class="ecr-summary">
            <div class="ecr-summary-info">
                <div class="ecr-source-badge">
                    <span class="ecr-source-name"><?= htmlspecialchars($data['sourceTitle']); ?></span>
                    <?php if (!empty($data['placeName'])) : ?>
                        <span class="ecr-place-name"><?= htmlspecialchars($data['placeName']); ?></span>
                    <?php endif; ?>
                </div>

                <div class="ecr-rating-overview">
                    <span class="ecr-rating-score"><?= number_format((float)$data['rating'], 1); ?></span>
                    <span class="ecr-rating-max">/ <?= (int)$data['maxRating']; ?></span>
                    <?= $this->get_starsHTML($data['rating'], $data['maxRating']); ?>
                </div>

                <?php if ((int)$data['totalReviews'] > 0) : ?>
                    <div class="ecr-total-reviews">
                        <?= $this->get_translation('based_on_reviews', (int)$data['totalReviews']); ?>
                    </div>
                <?php endif; ?>
            </div>

            <?php if (!empty($data['placeURL'])) : ?>
                <div class="ecr-summary-actions">
                    <?php if ($this->params['styleSource'] == 'plugin') : ?>
                        <a href="<?= htmlspecialchars($data['placeURL']); ?>" class="ecr-button" target="_blank" rel="noopener noreferrer nofollow">
                            <?= $this->get_translation('view_on_source', htmlspecialchars($data['sourceTitle'])); ?>
                        </a>
                    <?php else : ?>
                        <?= $camyks->theme->get_button(array(
                            'title'     => $this->get_translation('view_on_source', htmlspecialchars($data['sourceTitle'])),
                            'url'       => $data['placeURL'],
                            'target'    => '_blank',
                        )); ?>
                    <?php endif; ?>
                </div>
            <?php endif; ?>
        </div>
    <?php endif; ?>

    <?php if ($layout !== 'badge') : ?>
        <?php if (!empty($data['reviews'])) : ?>
            <div class="ecr-reviews">
                <?php foreach ($data['reviews'] as $review) : ?>
                    <?php $formattedDate = $this->get_formattedDate($review); ?>
                    <div class="ecr-review-card">
                        <div class="ecr-review-header">
                            <div class="ecr-author-avatar">
                                <?php if (!empty($review['authorAvatar'])) : ?>
                                    <img src="<?= htmlspecialchars($review['authorAvatar']); ?>" alt="<?= htmlspecialchars($review['authorName']); ?>" loading="lazy" referrerpolicy="no-referrer" />
                                <?php else : ?>
                                    <span class="ecr-avatar-initials"><?= htmlspecialchars($this->get_authorInitials($review['authorName'])); ?></span>
                                <?php endif; ?>
                            </div>

                            <div class="ecr-author-meta">
                                <div class="ecr-author-name">
                                    <?php if (!empty($review['authorURL'])) : ?>
                                        <a href="<?= htmlspecialchars($review['authorURL']); ?>" target="_blank" rel="noopener noreferrer nofollow">
                                            <?= htmlspecialchars($review['authorName']); ?>
                                        </a>
                                    <?php else : ?>
                                        <?= htmlspecialchars($review['authorName']); ?>
                                    <?php endif; ?>
                                </div>
                                <?php if ($formattedDate !== '') : ?>
                                    <div class="ecr-review-date">
                                        <?= htmlspecialchars($formattedDate); ?>
                                    </div>
                                <?php endif; ?>
                            </div>

                            <div class="ecr-review-rating">
                                <?= $this->get_starsHTML($review['rating'], $data['maxRating']); ?>
                            </div>
                        </div>

                        <?php if (!empty($review['title'])) : ?>
                            <div class="ecr-review-title">
                                <?= htmlspecialchars($review['title']); ?>
                            </div>
                        <?php endif; ?>

                        <?php if (!empty($review['text'])) : ?>
                            <div class="ecr-review-text">
                                <?= nl2br(htmlspecialchars($review['text'])); ?>
                            </div>
                        <?php endif; ?>

                        <?php if (!empty($review['reviewURL'])) : ?>
                            <div class="ecr-review-footer">
                                <a href="<?= htmlspecialchars($review['reviewURL']); ?>" class="ecr-review-link" target="_blank" rel="noopener noreferrer nofollow">
                                    <?= $this->get_translation('read_review'); ?>
                                </a>
                            </div>
                        <?php endif; ?>
                    </div>
                <?php endforeach; ?>
            </div>
        <?php else : ?>
            <div class="ecr-no-reviews">
                <?= $this->get_translation('no_reviews_available'); ?>
            </div>
        <?php endif; ?>
    <?php endif; ?>
</div>
<?php
/**
 * @endcond Exclude
 */
?>
