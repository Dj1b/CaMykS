<?php
/**
 * @brief Content_GenericLegalMentions module, site services, german sub layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Nov 2026
 * @date Modification: Nov 2026
 * @copyright 2026 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
?>
<div id="LM-Services" class="anchor" title="3. Beschreibung der angebotenen Dienste"></div>

<h2 class="eTitle2">
    3. Beschreibung der angebotenen Dienste
</h2>

<?php if (!$this->contentItem->is_individual()) : ?>
<p class="eContent1">
    Die <span class="eContent2">Website</span> <?= $this->contentItem->get_websiteURL(); ?> dient dazu, Informationen über sämtliche Tätigkeiten von <?= $this->contentItem->get_ownerFullTypeTitle(); ?> bereitzustellen.
</p>
<?php endif; ?>

<p class="eContent1">
    <?= ucfirst($this->contentItem->get_editorFullName()); ?> bemüht sich, auf der <span class="eContent2">Website</span> <?= $this->contentItem->get_websiteURL(); ?> möglichst genaue Informationen bereitzustellen. Für Auslassungen, Ungenauigkeiten oder unzureichende Aktualisierungen, unabhängig davon, ob sie selbst verursacht wurden oder auf Drittpartner zurückgehen, die diese Informationen liefern, wird jedoch keine Haftung übernommen.
</p>

<p class="eContent1">
    Alle auf der <span class="eContent2">Website</span> <?= $this->contentItem->get_websiteURL(); ?> veröffentlichten Informationen dienen lediglich der Orientierung und können sich ändern. Die Angaben auf der <span class="eContent2">Website</span> <?= $this->contentItem->get_websiteURL(); ?> sind zudem nicht vollständig. Änderungen seit ihrer Veröffentlichung bleiben vorbehalten.
</p>

<p class="eContent1">
    &nbsp;
</p>
