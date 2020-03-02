<?php
/**
 * @brief Content_GenericLegalMentions Module site services, french sub layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Jan 2020
 * @date Modification: Feb 2020
 * @copyright 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
?>
<div id="LM-Services" class="anchor" title="3. Description des services fournis"></div>

<h2 class="eTitle2">
    3. Description des services fournis
</h2>

<?php if (!$this->contentItem->is_individual()) : ?>
<p class="eContent1">
    Le <span class="eContent2">Site</span> internet <?= $this->contentItem->get_websiteURL(); ?> a pour objet de fournir une information concernant l'ensemble des activit&eacute;s de la soci&eacute;t&eacute;.
</p>
<?php endif; ?>

<p class="eContent1">
    <?= ucfirst($this->contentItem->get_editorFullName()); ?> s'efforce de fournir sur le <span class="eContent2">Site</span> <?= $this->contentItem->get_websiteURL(); ?> des informations aussi pr&eacute;cises que possible. Toutefois, il ne pourra &ecirc;tre tenu responsable des oublis, des inexactitudes et des carences dans la mise &agrave; jour, qu’elles soient de son fait ou du fait des tiers partenaires qui lui fournissent ces informations.
</p>

<p class="eContent1">
    Toutes les informations indiqu&eacute;es sur le <span class="eContent2">Site</span> <?= $this->contentItem->get_websiteURL(); ?> sont donn&eacute;es &agrave; titre indicatif, et sont susceptibles d’&eacute;voluer. Par ailleurs, les renseignements figurant sur le <span class="eContent2">Site</span> <?= $this->contentItem->get_websiteURL(); ?> ne sont pas exhaustifs. Ils sont donn&eacute;s sous r&eacute;serve de modifications ayant &eacute;t&eacute; apport&eacute;es depuis leur mise en ligne.
</p>

<p class="eContent1">
    &nbsp;
</p>
