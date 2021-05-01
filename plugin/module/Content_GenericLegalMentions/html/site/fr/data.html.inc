<?php
/**
 * @brief Content_GenericLegalMentions Module site data, french sub layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Jan 2020
 * @date Modification: Apr 2021
 * @copyright 2020 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
?>
<div id="LM-Data" class="anchor" title="7. Gestion des donn&eacute;es personnelles"></div>

<h2 class="eTitle2">
    7. Gestion des donn&eacute;es personnelles
</h2>

<p class="eContent1">
    L'<span class="eContent2">Internaute</span> est inform&eacute; des r&eacute;glementations concernant la communication marketing, la loi du 21 Juin 2014 pour la confiance dans l'Economie Num&eacute;rique, la Loi Informatique et Libert&eacute; du 06 Ao&ucirc;t 2004 ainsi que du R&egrave;glement G&eacute;n&eacute;ral sur la Protection des Donn&eacute;es (RGPD : n&deg; 2016-679).
</p>

<h3 class="eTitle3">
    7.1 Responsables de la collecte des donn&eacute;es personnelles
</h3>

<p class="eContent1">
    Pour les <span class="eContent2">Donn&eacute;es Personnelles</span> collect&eacute;es dans le cadre de l'utilisation et de la navigation sur le <span class="eContent2">Site</span>, le responsable du traitement des <span class="eContent2">Donn&eacute;es Personnelles</span> est <?= $this->contentItem->get_editorFullName(); ?>.
</p>

<p class="eContent1">
<?= $this->contentItem->vars['owner_name']; ?> est repr&eacute;sent&eacute; par <a href="<?= mail_encode($this->contentItem->vars['owner_manageremail']); ?>" class="eLink1"><?= $this->contentItem->vars['owner_managername']; ?></a><?php if (!$this->contentItem->is_individual()) : ?>, son repr&eacute;sentant l&eacute;gal<?php endif; ?>.
</p>

<p class="eContent1">
    En tant que responsable du traitement des donn&eacute;es que le <span class="eContent2">Site</span> collecte, <?= $this->contentItem->get_editorFullName(); ?> s'engage &agrave; respecter le cadre des dispositions l&eacute;gales en vigueur. Il appartient notamment au <span class="eContent2">Client</span> d'&eacute;tablir les finalit&eacute;s de ses traitements de donn&eacute;es, de fournir &agrave; ses prospects et clients, &agrave; partir de la collecte de leurs consentements, une information compl&egrave;te sur le traitement de leurs <span class="eContent2">Donn&eacute;es Personnelles</span> et de maintenir un registre des traitements conforme &agrave; la r&eacute;alit&eacute;. Chaque fois que <?= $this->contentItem->get_editorFullName(); ?> traite des <span class="eContent2">Donn&eacute;es Personnelles</span>, <?= $this->contentItem->get_editorFullName(); ?> prend toutes les mesures raisonnables pour s'assurer de l'exactitude et de la pertinence des <span class="eContent2">Donn&eacute;es Personnelles</span> au regard des finalit&eacute;s pour lesquelles <?= $this->contentItem->get_editorFullName(); ?> les traite.
</p>

<h3 class="eTitle3">
    7.2 Finalit&eacute; des donn&eacute;es collect&eacute;es
</h3>

<p class="eContent1">
    <?= ucfirst($this->contentItem->get_editorFullName()); ?> est susceptible de traiter tout ou partie des donn&eacute;es :
</p>

<ul>
    <li class="eContent1">
        <strong>pour am&eacute;liorer la navigation sur le</strong> <span class="eContent2">Site</span>
        <ul>
            <li><b>Donn&eacute;es collect&eacute;es</b> : donn&eacute;es de connexion et d'utilisation</li>
            <li><b>Dur&eacute;e de conservation des donn&eacute;es</b> : Maximum 12 mois.</li>
        </ul>
    </li>

    <li class="eContent1">
        <strong>pour pr&eacute;venir et lutter contre la fraude informatique (spamming, hacking...)</strong>
        <ul>
            <li><b>Donn&eacute;es collect&eacute;es</b> : mat&eacute;riel informatique utilis&eacute; (agent utilisateur) pour la navigation et l'adresse IP</li>
            <li><b>Dur&eacute;e de conservation des donn&eacute;es</b> : Maximum 12 mois.</li>
        </ul>
    </li>

    <?php foreach ($this->extraData as $plugin) : ?>
        <?php foreach ($plugin as $pluginData) : ?>
        <?php foreach ($pluginData as $data) : ?>
            <li class="eContent1">
                <strong><?= $data['title']; ?></strong>
                <ul>
                    <?php if ($data['description'] != '') : ?>
                        <li> <?= $data['description']; ?> </li>
                    <?php endif; ?>
                    <?php if ($data['data'] != '') : ?>
                    <li>
                        <b>Donn&eacute;es collect&eacute;es</b> : <?= $data['data']; ?>
                    </li>
                    <?php endif; ?>
                    <li>
                        <b>Dur&eacute;e de conservation des donn&eacute;es</b> :
                        <?php if ($data['duration'] != '') : ?>
                            <?= $data['duration']; ?>
                        <?php else : ?>
                            Maximum 12 mois.
                        <?php endif; ?>
                    </li>
                </ul>
            </li>
        <?php endforeach; ?>
        <?php endforeach; ?>
    <?php endforeach; ?>
</ul>

<h3 class="eTitle3">
    7.3 Droit d'acc&egrave;s, de rectification et d'opposition
</h3>

<p class="eContent1">
    Conform&eacute;ment &agrave; la r&eacute;glementation europ&eacute;enne en vigueur, les <span class="eContent2">Utilisateurs</span> du <span class="eContent2">Site</span> <?= $this->contentItem->get_websiteURL(); ?> disposent des droits suivants :

</p>

<ul>
    <li class="eContent1">
        droit d'acc&egrave;s (article 15 RGPD) et de rectification (article 16 RGPD), de mise &agrave; jour, de compl&eacute;tude des <span class="eContent2">Donn&eacute;es Personnelles</span> des <span class="eContent2">Utilisateurs</span>, droit de verrouillage ou d'effacement des donn&eacute;es des <span class="eContent2">Utilisateurs</span> &agrave; caract&egrave;re personnel (article 17 du RGPD), lorsqu'elles sont inexactes, incompl&egrave;tes, &eacute;quivoques, p&eacute;rim&eacute;es, ou dont la collecte, l'utilisation, la communication ou la conservation est interdite,
    </li>

    <li class="eContent1">
        droit de retirer &agrave; tout moment un consentement (article 13-2c RGPD),
    </li>

    <li class="eContent1">
        droit &agrave; la limitation du traitement des donn&eacute;es des <span class="eContent2">Utilisateurs</span> (article 18 RGPD),
    </li>

    <li class="eContent1">
        droit d'opposition au traitement des donn&eacute;es des <span class="eContent2">Utilisateurs</span> (article 21 RGPD),
    </li>

    <li class="eContent1">
        droit &agrave; la portabilit&eacute; des donn&eacute;es que les <span class="eContent2">Utilisateurs</span> auront fournies, lorsque ces donn&eacute;es font l'objet de traitements automatis&eacute;s fond&eacute;s sur leur consentement ou sur un contrat (article 20 RGPD),
    </li>

    <li class="eContent1">
        droit de d&eacute;finir le sort des donn&eacute;es des <span class="eContent2">Utilisateurs</span> apr&egrave;s leur mort et de choisir &agrave; qui <?= $this->contentItem->get_editorFullName(); ?> devra communiquer (ou non) ses donn&eacute;es &agrave; un tiers qu'il aura pr&eacute;alablement d&eacute;sign&eacute;,
    </li>

    <li class="eContent1">
        d&egrave;s que <?= $this->contentItem->get_editorFullName(); ?> a connaissance du d&eacute;c&egrave;s d'un <span class="eContent2">Utilisateur</span> et &agrave; d&eacute;faut d'instructions de sa part, <?= $this->contentItem->get_editorFullName(); ?> s'engage &agrave; d&eacute;truire ses <span class="eContent2">Donn&eacute;es Personnelles</span>, sauf si leur conservation s'av&egrave;re n&eacute;cessaire &agrave; des fins probatoires ou pour r&eacute;pondre &agrave; une obligation l&eacute;gale.
    </li>
</ul>

<p class="eContent1">
    Si l'<span class="eContent2">Utilisateur</span> souhaite savoir comment <?= $this->contentItem->get_editorFullName(); ?> utilise ses <span class="eContent2">Donn&eacute;es Personnelles</span>, demander &agrave; les rectifier ou s'oppose &agrave; leur traitement, l'<span class="eContent2">Utilisateur</span> peut contacter <?= $this->contentItem->get_editorFullName(); ?> par &eacute;crit &agrave; l'adresse suivante : <br />
<br />
<?php if (!$this->contentItem->is_individual()) : ?>
    <span class="eContent2"><?= $this->contentItem->vars['owner_name']; ?></span> <br />
<?php endif; ?>
<a href="<?= mail_encode($this->contentItem->vars['owner_manageremail']); ?>" class="eLink1">
<?= $this->contentItem->vars['owner_managername']; ?> (DPO)</a> <br />
<?php if ($this->contentItem->has_content('owner_address')) : ?>
<?= $this->contentItem->vars['owner_address']; ?> <br />
<?php endif; ?>
<br />
Dans ce cas, l'<span class="eContent2">Utilisateur</span> doit indiquer les <span class="eContent2">Donn&eacute;es Personnelles</span> qu'il souhaiterait que <?= $this->contentItem->get_editorFullName(); ?> corrige, mette &agrave; jour ou supprime, en s'identifiant pr&eacute;cis&eacute;ment avec une copie d'une pi&egrave;ce d'identit&eacute; (carte d'identit&eacute; ou passeport).
</p>

<p class="eContent1">
    Les demandes de suppression de <span class="eContent2">Donn&eacute;es Personnelles</span> seront soumises aux obligations qui sont impos&eacute;es &agrave; <?= $this->contentItem->get_editorFullName(); ?> par la loi, notamment en mati&egrave;re de conservation ou d'archivage des documents. Enfin, les <span class="eContent2">Utilisateurs</span> du <span class="eContent2">Site</span> <?= $this->contentItem->get_websiteURL(); ?> peuvent d&eacute;poser une r&eacute;clamation aupr&egrave;s des autorit&eacute;s de contr&ocirc;le, et notamment de la <a href="https://www.cnil.fr/fr/plaintes" class="eLink1" target="_blank" rel="noopener noreferer">CNIL</a>.
</p>

<h3 class="eTitle3">
    7.4 Non-communication des donn&eacute;es personnelles
</h3>

<p class="eContent1">
    <?= ucfirst($this->contentItem->get_editorFullName()); ?> s'interdit de traiter, h&eacute;berger ou transf&eacute;rer les informations collect&eacute;es sur ses <span class="eContent2">Clients</span> vers un pays situ&eacute; en dehors de l'Union europ&eacute;enne ou reconnu comme &laquo; non ad&eacute;quat &raquo; par la Commission europ&eacute;enne sans en informer pr&eacute;alablement le <span class="eContent2">Client</span>. Pour autant, <?= $this->contentItem->get_editorFullName(); ?> reste libre du choix de ses sous-traitants techniques et commerciaux &agrave; la condition qu'il pr&eacute;sentent les garanties suffisantes au regard des exigences du R&egrave;glement G&eacute;n&eacute;ral sur la Protection des Donn&eacute;es (RGPD : n&deg; 2016-679).
</p>

<p class="eContent1">
    <?= ucfirst($this->contentItem->get_editorFullName()); ?> s'engage &agrave; prendre toutes les pr&eacute;cautions n&eacute;cessaires afin de pr&eacute;server la s&eacute;curit&eacute; des <span class="eContent2">Donn&eacute;es Personnelles</span> et notamment qu'elles ne soient pas communiqu&eacute;es &agrave; des personnes non autoris&eacute;es. Cependant, si un incident impactant l'int&eacute;grit&eacute; ou la confidentialit&eacute; des <span class="eContent2">Donn&eacute;es Personnelles</span> du <span class="eContent2">Client</span> est port&eacute;e &agrave; la connaissance de <?= $this->contentItem->get_editorFullName(); ?>, celle-ci devra dans les meilleurs d&eacute;lais informer le Client et lui communiquer les mesures de corrections prises. Par ailleurs, <?= $this->contentItem->get_editorFullName(); ?> ne collecte aucune &laquo; donn&eacute;es sensibles &raquo;.
</p>

<?php if (!$this->contentItem->is_individual()) : ?>
<p class="eContent1">
    Les <span class="eContent2">Donn&eacute;es Personnelles</span> de l'<span class="eContent2">Utilisateur</span> peuvent &ecirc;tre trait&eacute;es par des filiales de <?= $this->contentItem->get_editorFullName(); ?> et des sous-traitants (prestataires de services), exclusivement afin de r&eacute;aliser les finalit&eacute;s de la pr&eacute;sente politique.
</p>

<p class="eContent1">
    Les personnes susceptibles d'avoir acc&egrave;s aux <span class="eContent2">Donn&eacute;es Personnelles</span> des <span class="eContent2">Utilisateurs</span> de <?= $this->contentItem->get_websiteURL(); ?> sont d&eacute;sign&eacute;es et sous la seule responsabilit&eacute; du responsable de <?= $this->contentItem->get_editorFullName(); ?>. En outre, leurs attributions respectives peuvent &ecirc;tre limit&eacute;es selon les besoins et les finalit&eacute;s rappel&eacute;es ci-dessus.
</p>
<?php endif; ?>

<p class="eContent1">
    &nbsp;
</p>
