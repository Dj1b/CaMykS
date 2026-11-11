<?php
/**
 * @brief Content_GenericLegalMentions module, site services, spanish sub layout.
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
<div id="LM-Services" class="anchor" title="3. Descripción de los servicios prestados"></div>

<h2 class="eTitle2">
    3. Descripción de los servicios prestados
</h2>

<?php if (!$this->contentItem->is_individual()) : ?>
<p class="eContent1">
    El <span class="eContent2">Sitio</span> web <?= $this->contentItem->get_websiteURL(); ?> tiene por objeto proporcionar información sobre el conjunto de las actividades de <?= $this->contentItem->get_ownerFullTypeTitle(); ?>.
</p>
<?php endif; ?>

<p class="eContent1">
    <?= ucfirst($this->contentItem->get_editorFullName()); ?> procura ofrecer en el <span class="eContent2">Sitio</span> <?= $this->contentItem->get_websiteURL(); ?> información lo más precisa posible. No obstante, no podrá ser considerado responsable de omisiones, inexactitudes o deficiencias en su actualización, ya sean imputables a él o a terceros colaboradores que le proporcionen dicha información.
</p>

<p class="eContent1">
    Toda la información publicada en el <span class="eContent2">Sitio</span> <?= $this->contentItem->get_websiteURL(); ?> se facilita a título informativo y puede evolucionar. Además, la información que figura en el <span class="eContent2">Sitio</span> <?= $this->contentItem->get_websiteURL(); ?> no es exhaustiva. Se ofrece sin perjuicio de las modificaciones realizadas desde su publicación.
</p>

<p class="eContent1">
    &nbsp;
</p>
