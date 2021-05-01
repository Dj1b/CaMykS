<?php
/**
 * @brief Content_GenericLegalMentions Module site services, english sub layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Apr 2021
 * @date Modification: Apr 2021
 * @copyright 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
?>
<div id="LM-Services" class="anchor" title="3. Description of the provided services"></div>

<h2 class="eTitle2">
    3. Description of the provided services
</h2>

<?php if (!$this->contentItem->is_individual()) : ?>
<p class="eContent1">
    The purpose of the <span class="eContent2">Website</span> <?= $this->contentItem->get_websiteURL(); ?> is to provide information concerning all <?= $this->contentItem->get_ownerFullTypeTitle(); ?>'s activities.
</p>
<?php endif; ?>

<p class="eContent1">
    <?= ucfirst($this->contentItem->get_editorFullName()); ?> strives to provide on the <span class="eContent2">Website</span> <?= $this->contentItem->get_websiteURL(); ?> information which is as accurate as possible. However, it cannot be held liable for omissions, inaccuracies and failures to make updates, whether it is responsible for them, or partner third parties which provide this information are responsible for them.
</p>

<p class="eContent1">
    All the information displayed on the <span class="eContent2">Website</span> <?= $this->contentItem->get_websiteURL(); ?> is given for information only and is subject to change. In addition, information provided on the <span class="eContent2">Website</span> <?= $this->contentItem->get_websiteURL(); ?> is not exhaustive. It is given subject to any modifications which may have been made since it was onlined.
</p>

<p class="eContent1">
    &nbsp;
</p>
