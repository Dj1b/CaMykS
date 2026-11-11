<?php
/**
 * @brief Content_GenericLegalMentions module, site services, italian sub layout.
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
<div id="LM-Services" class="anchor" title="3. Descrizione dei servizi forniti"></div>

<h2 class="eTitle2">
    3. Descrizione dei servizi forniti
</h2>

<?php if (!$this->contentItem->is_individual()) : ?>
<p class="eContent1">
    Il <span class="eContent2">Sito</span> web <?= $this->contentItem->get_websiteURL(); ?> ha lo scopo di fornire informazioni sull'insieme delle attività di <?= $this->contentItem->get_ownerFullTypeTitle(); ?>.
</p>
<?php endif; ?>

<p class="eContent1">
    <?= ucfirst($this->contentItem->get_editorFullName()); ?> si impegna a fornire sul <span class="eContent2">Sito</span> <?= $this->contentItem->get_websiteURL(); ?> informazioni il più possibile precise. Tuttavia, non può essere ritenuto responsabile di omissioni, inesattezze o carenze nell'aggiornamento, siano esse imputabili a lui o a terzi partner che gli forniscono tali informazioni.
</p>

<p class="eContent1">
    Tutte le informazioni riportate sul <span class="eContent2">Sito</span> <?= $this->contentItem->get_websiteURL(); ?> sono fornite a titolo indicativo e possono essere soggette a modifiche. Inoltre, le informazioni presenti sul <span class="eContent2">Sito</span> <?= $this->contentItem->get_websiteURL(); ?> non sono esaustive. Esse sono fornite con riserva delle modifiche apportate dopo la loro pubblicazione.
</p>

<p class="eContent1">
    &nbsp;
</p>
