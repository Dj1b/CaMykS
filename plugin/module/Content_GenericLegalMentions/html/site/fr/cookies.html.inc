<?php
/**
 * @brief Content_GenericLegalMentions Module site cookies, french sub layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jan 2020
 * @date Modification: Apr 2021
 * @copyright 2020 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
?>
<div id="LM-Cookies" class="anchor" title="9. Cookies."></div>

<h2 class="eTitle2">
    9. Cookies
</h2>

<p class="eContent1">
    Un &laquo; cookie &raquo; est un petit fichier d'information envoy&eacute; sur le navigateur de l'<span class="eContent2">Utilisateur</span> et enregistr&eacute; au sein du terminal de l'<span class="eContent2">Utilisateur</span> (ex : ordinateur, smartphone). Ce fichier comprend des informations telles que le nom de domaine de l'<span class="eContent2">Utilisateur</span>, le fournisseur d'acc&egrave;s Internet de l'<span class="eContent2">Utilisateur</span>, le syst&egrave;me d'exploitation de l'<span class="eContent2">Utilisateur</span>, ainsi que la date et l'heure d'acc&egrave;s. Les cookies ne risquent, en aucun cas, d'endommager le terminal de l'Utilisateur.
</p>

<p class="eContent1">
    <?= ucfirst($this->contentItem->get_editorFullName()); ?> est susceptible de traiter les informations de l'<span class="eContent2">Utilisateur</span> concernant sa visite du <span class="eContent2">Site</span>, telles que les pages consult&eacute;es, les recherches effectu&eacute;es. Ces informations permettent &agrave; <?= $this->contentItem->get_editorFullName(); ?> d'am&eacute;liorer le contenu du <span class="eContent2">Site</span>, et la navigation de l'<span class="eContent2">Utilisateur</span>.
</p>

<p class="eContent1">
    Les cookies facilitant la navigation et/ou la fourniture des services propos&eacute;s par le <span class="eContent2">Site</span>, l'<span class="eContent2">Utilisateur</span> peut configurer son navigateur pour qu'il lui permette de d&eacute;cider s'il souhaite ou non les accepter de mani&egrave;re &agrave; ce que des cookies soient enregistr&eacute;s dans le terminal ou, au contraire, qu'ils soient rejet&eacute;s, soit syst&eacute;matiquement, soit selon leur &eacute;metteur. L'<span class="eContent2">Utilisateur</span> peut &eacute;galement configurer son logiciel de navigation de mani&egrave;re &agrave; ce que l'acceptation ou le refus des cookies lui soient propos&eacute;s ponctuellement, avant qu'un cookie soit susceptible d'&ecirc;tre enregistr&eacute;, pour la dur&eacute;e de la visite de l'<span class="eContent2">Utilisateur</span>, dans son terminal. <?= ucfirst($this->contentItem->get_editorFullName()); ?> informe l'<span class="eContent2">Utilisateur</span> que, dans ce cas, il se peut que les fonctionnalit&eacute;s propos&eacute;es par le <span class="eContent2">Site</span> ne soient pas toutes disponibles.
</p>

<p class="eContent1">
    Si l'<span class="eContent2">Utilisateur</span> refuse l'enregistrement de cookies dans son terminal ou son navigateur, ou si l'<span class="eContent2">Utilisateur</span> supprime ceux qui y sont enregistr&eacute;s, l'<span class="eContent2">Utilisateur</span> est inform&eacute; que sa navigation et son exp&eacute;rience sur le <span class="eContent2">Site</span> peuvent &ecirc;tre limit&eacute;es. Cela pourrait &eacute;galement &ecirc;tre le cas lorsque <?= $this->contentItem->get_editorFullName(); ?> ou l'un de ses prestataires ne peut pas reconna&icirc;tre, &agrave; des fins de compatibilit&eacute; technique, le type de navigateur utilis&eacute; par le terminal, les param&egrave;tres de langue et d'affichage ou le pays depuis lequel le terminal semble connect&eacute; &agrave; Internet.
</p>

<p class="eContent1">
    Le cas &eacute;ch&eacute;ant, <?= $this->contentItem->get_editorFullName(); ?> d&eacute;cline toute responsabilit&eacute; pour les cons&eacute;quences li&eacute;es au fonctionnement d&eacute;grad&eacute; du <span class="eContent2">Site</span> et des services &eacute;ventuellement propos&eacute;s par <?= $this->contentItem->get_editorFullName(); ?>, r&eacute;sultant (i) du refus de cookies par l'Utilisateur (ii) de l'impossibilit&eacute; pour <?= $this->contentItem->get_editorFullName(); ?> d'enregistrer ou de consulter les cookies n&eacute;cessaires &agrave; leur fonctionnement du fait du choix de l'<span class="eContent2">Utilisateur</span>. Pour la gestion des cookies et des choix de l'<span class="eContent2">Utilisateur</span>, la configuration de chaque navigateur est diff&eacute;rente. Elle est d&eacute;crite dans le menu d'aide du navigateur, qui permettra de savoir de quelle mani&egrave;re l'<span class="eContent2">Utilisateur</span> peut modifier ses souhaits en mati&egrave;re de cookies.
</p>

<p class="eContent1">
&Agrave; tout moment, l'<span class="eContent2">Utilisateur</span> peut faire le choix d'exprimer et de modifier ses souhaits en mati&egrave;re de cookies. <?= ucfirst($this->contentItem->get_editorFullName()); ?> pourra en outre faire appel aux services de prestataires externes pour l'aider &agrave; recueillir et traiter les informations d&eacute;crites dans cette section.
</p>

<p class="eContent1">
Ces cookies ne sont d&eacute;pos&eacute;s sur vos terminaux qu'&agrave; condition que vous y consentiez, en continuant votre navigation sur le <span class="eContent2">Site</span> Internet ou l'application mobile de <?= $this->contentItem->get_editorFullName(); ?>. &Agrave; tout moment, l'<span class="eContent2">Utilisateur</span> peut n&eacute;anmoins revenir sur son consentement &agrave; ce que le <span class="eContent2">Site</span> d&eacute;pose ce type de cookies.
</p>

<?php if ($this->cookieAgreementInput !== false) : ?>
<p class="eContent1">
Voici la liste des services pr&eacute;sents sur le <span class="eContent2">Site</span>, et faisant usage de cookies :
</p>
<ul>
    <?php foreach($this->cookieAgreementInput->get_servicesList() as $service) : ?>
        <li class="eContent1">
            <span class="eContent2"><?= $service['title']; ?></span>
            <br /><?= $service['purpose']; ?>
            <?php if ($service['usage'] !== '') : ?>
                <br />Usage : <?= $service['usage']; ?>
            <?php endif; ?>
            <?php if ($service['duration'] !== '') : ?>
                <br />Dur&eacute;e de vie : <?= $service['duration']; ?>
            <?php endif; ?>
            <?php if ($service['aboutURL'] != '') : ?>
                <br /><a href="<?= $service['aboutURL']; ?>" class="link" target="_blank" rel="noopener,noreferer,nofollow">En savoir plus</a>
            <?php endif; ?>
        </li>
    <?php endforeach; ?>
</ul>

<p class="eContent1" style="text-align:center;">
    <?= $this->theme->get_button(array(
        'title' => 'Ouvrir le panneau de gestion des cookies',
        'url'   => $this->cookieAgreementInput->get_cookieManagementPanelOpenLink(),
    )); ?>
</p>

<?php endif; ?>

<p class="eContent1">
    &nbsp;
</p>

