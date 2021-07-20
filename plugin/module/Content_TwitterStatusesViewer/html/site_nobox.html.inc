<?php
/**
 * @brief Content_TwitterStatusesViewer module, site nobox layout.
 * @details Plugin / Module Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jul 2010
 * @date Modification: Jul 2021
 * @copyright 2010 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
$uData = $this->userData;
$tData = $this->tweets;
?>
<div class="twitterBox<?= $uData['id']; ?>">
    <div>
        <a href="http://www.twitter.com/" target="_blank">
            <img src="<?= $this->get_fileURL('img/icon_twitter.png');?>" style="float:left; margin-right:4px;" alt="Twitter" />
        </a>
        <a href="http://www.twitter.com/<?= $uData['screen_name']; ?>" class="eTitle2" target="_blank">
            @<?= $uData['name']; ?>
        </a>
    </div>
    <?php foreach ($tData['status'] as $status) : ?>
        <p class="eContent<?= $status['favorited']=='true' ? 2 : 1; ?>">
            <?= $this->update_tweetText($status['text']); ?>
        </p>
        <div class="eTitle4">
            <?= $this->display_tweetDate($status['created_at']); ?>
        </div>
        <div style="border-top:solid 1px #<?= $this->get_borderColor('888888'); ?>; margin:8px 20px 0;">
            &nbsp;
        </div>
    <?php endforeach; ?>
</div>
