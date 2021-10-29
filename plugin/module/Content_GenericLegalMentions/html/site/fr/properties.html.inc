<?php
/**
 * @brief Content_GenericLegalMentions module, french version of site properties sub layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.2
 * @date Creation: Jan 2020
 * @date Modification: Oct 2021
 * @copyright 2020 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
?>
<div id="LM-Properties" class="anchor" title="1. Editeur(s) du Site"></div>

<h2 class="eTitle2">
    1. Editeur(s) du Site
</h2>

<p class="eContent1">
En vertu de l'article 6 de la loi n&deg; 2004-575 du 21 juin 2004 pour la confiance dans l'&eacute;conomie num&eacute;rique, il est pr&eacute;cis&eacute; aux utilisateurs du <span class="eContent2">Site</span> internet <?= $this->contentItem->get_websiteURL(); ?> l'identit&eacute; des diff&eacute;rents intervenants dans le cadre de sa r&eacute;alisation et de son suivi.
</p>

<?php if ($this->contentItem->is_individual()) : ?>
<h3 class="eTitle3">
    Propri&eacute;taire &amp; responsable publication
</h3>
<p class="eContent1">
    <a href="<?= mail_encode($this->contentItem->vars['owner_manageremail']); ?>" class="eLink1">
    <?= $this->contentItem->vars['owner_managername']; ?>
    </a> <br />
    Le responsable publication est une personne physique ou une personne morale.
<?php else : ?>
<h3 class="eTitle3">
    Propri&eacute;taire
</h3>
<p class="eContent1">
        <span class="eContent2"><?= $this->contentItem->vars['owner_name'].' '. $this->contentItem->vars['owner_company_legalform']; ?></span> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('owner_address')) : ?>
    <?= $this->contentItem->vars['owner_address']; ?> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('owner_phone')) : ?>
    T&eacute;l&eacute;phone : <?= $this->contentItem->vars['owner_phone']; ?> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('owner_fax')) : ?>
    Fax : <?= $this->contentItem->vars['owner_fax']; ?> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('owner_email')) : ?>
    <a href="<?= mail_encode($this->contentItem->vars['owner_email']); ?>" class="eLink1"> Contact par e-mail </a> <br />
<?php endif; ?>
</p>

<?php if (!$this->contentItem->is_individual()) : ?>
<p class="eContent1">
<?php if ($this->contentItem->has_content('owner_company_siret')) : ?>
SIRET : <?= $this->contentItem->vars['owner_company_siret']; ?> <br />
<?php endif; ?>
<?php if ($this->contentItem->has_content('owner_company_vat')) : ?>
TVA Intracomm. : <?= $this->contentItem->vars['owner_company_vat']; ?> <br />
<?php endif; ?>
<?php if ($this->contentItem->has_content('owner_company_capital')) : ?>
Capital social : <?= $this->contentItem->vars['owner_company_capital']; ?> <br />
<?php endif; ?>
<?php if ($this->contentItem->has_content('owner_company_rcsnum') and $this->contentItem->has_content('owner_company_rcsloc')) : ?>
Enregistr&eacute;e sous le num&eacute;ro : <?= $this->contentItem->vars['owner_company_rcsnum']; ?> - <?= $this->contentItem->vars['owner_company_rcsloc']; ?><br />
<?php endif; ?>
<?php if ($this->contentItem->has_content('owner_company_naf')) : ?>
Code NAF : <?= $this->contentItem->vars['owner_company_naf']; ?> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('owner_additional')) : ?>
<?= $this->contentItem->vars['owner_additional']; ?> <br />
<?php endif; ?>
</p>
<h3 class="eTitle3">
    Responsable publication
</h3>
<p class="eContent1">
<a href="<?= mail_encode($this->contentItem->vars['owner_manageremail']); ?>" class="eLink1">
<?= $this->contentItem->vars['owner_managername']; ?>
</a> <br />
Le responsable publication est une personne physique ou une personne morale.
</p>
<?php endif; ?>

<?php if ($this->contentItem->has_content('creator_name')) : ?>
<h3 class="eTitle3">
    Cr&eacute;ation
</h3>

<p class="eContent1">
<span class="eContent2"> <?= $this->contentItem->vars['creator_name']; ?> </span> <br />

<?php if ($this->contentItem->has_content('creator_address')) : ?>
    <?= $this->contentItem->vars['creator_address']; ?> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('creator_phone')) : ?>
    T&eacute;l&eacute;phone : <?= $this->contentItem->vars['creator_phone']; ?> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('creator_fax')) : ?>
    Fax: <?= $this->contentItem->vars['creator_fax']; ?> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('creator_email')) : ?>
    <a href="<?= mail_encode($this->contentItem->vars['creator_email']); ?>" class="eLink1"> Contact par e-mail </a> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('creator_website')) : ?>
    <a href="<?= url_getAsComplete($this->contentItem->vars['creator_website']); ?>" class="eLink1" target="_blank"> <?=  url_getAsSmart($this->contentItem->vars['creator_website']); ?> </a> <br />
<?php endif; ?>

<?php endif; ?>

<?php if ($this->contentItem->has_content('webmaster_name')) : ?>
<h3 class="eTitle3">
    Webmaster
</h3>

<p class="eContent1">
    <a href="<?= mail_encode($this->contentItem->vars['webmaster_email']); ?>" class="eLink1"><?= $this->contentItem->vars['webmaster_name']; ?></a>
    <?php if ($this->contentItem->has_content('webmaster_company')) : ?>
    - <?= $this->contentItem->vars['webmaster_company']; ?>
    <?php endif; ?>
</p>
<?php endif; ?>

<?php if ($this->contentItem->has_content('dpo_name')) : ?>
<h3 class="eTitle3">
    D&eacute;l&eacute;gu&eacute; à la protection des donn&eacute;es (DPO)
</h3>

<p class="eContent1">
    <a href="<?= mail_encode($this->contentItem->vars['dpo_email']); ?>" class="eLink1"><?= $this->contentItem->vars['dpo_name']; ?></a>
    <?php if ($this->contentItem->has_content('dpo_company')) : ?>
    - <?= $this->contentItem->vars['dpo_company']; ?>
    <?php endif; ?>
</p>
<?php endif; ?>

<?php if ($this->contentItem->has_content('host_name')) : ?>
<h3 class="eTitle3">
    H&eacute;bergeur
</h3>

<p class="eContent1">
<span class="eContent2"> <?= $this->contentItem->vars['host_name']; ?> </span> <br />

<?php if ($this->contentItem->has_content('host_address')) : ?>
    <?= $this->contentItem->vars['host_address']; ?> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('host_phone')) : ?>
    T&eacute;l&eacute;phone : <?= $this->contentItem->vars['host_phone']; ?> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('host_fax')) : ?>
    Fax: <?= $this->contentItem->vars['host_fax']; ?> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('host_email')) : ?>
    <a href="<?= mail_encode($this->contentItem->vars['host_email']); ?>" class="eLink1">Contact par e-mail</a> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('host_website')) : ?>
    <a href="<?= url_getAsComplete($this->contentItem->vars['host_website']); ?>" class="eLink1" target="_blank"><?= url_getAsSmart($this->contentItem->vars['host_website']); ?></a> <br />
<?php endif; ?>

<?php endif; ?>

<p class="eContent1">
    &nbsp;
</p>
