<?php
/**
 * @brief Content_GenericLegalMentions module, german sub layout.
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
<div id="LM-Properties" class="anchor" title="1. Betreiber der Website"></div>

<h2 class="eTitle2">
    1. Betreiber der Website
</h2>

<p class="eContent1">
Gemäß Artikel 6 des französischen Gesetzes Nr. 2004-575 vom 21. Juni 2004 über das Vertrauen in die digitale Wirtschaft werden die Nutzer der <span class="eContent2">Website</span> <?= $this->contentItem->get_websiteURL(); ?> über die Identität der an ihrer Erstellung und Betreuung beteiligten Personen und Einrichtungen informiert.
</p>

<?php if ($this->contentItem->is_individual()) : ?>
<h3 class="eTitle3">
    Inhaber und Verantwortlicher für die Veröffentlichung
</h3>
<p class="eContent1">
    <a href="<?= mail_encode($this->contentItem->vars['owner_manageremail']); ?>" class="eLink1">
    <?= $this->contentItem->vars['owner_managername']; ?>
    </a> <br />
    Der Verantwortliche für die Veröffentlichung ist eine natürliche oder juristische Person.
<?php else : ?>
<h3 class="eTitle3">
    Inhaber
</h3>
<p class="eContent1">
        <span class="eContent2"><?= $this->contentItem->vars['owner_name'].' '. $this->contentItem->vars['owner_company_legalform']; ?></span> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('owner_address')) : ?>
    <?= $this->contentItem->vars['owner_address']; ?> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('owner_phone')) : ?>
    Telefon: <?= $this->contentItem->vars['owner_phone']; ?> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('owner_fax')) : ?>
    Fax: <?= $this->contentItem->vars['owner_fax']; ?> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('owner_email')) : ?>
    <a href="<?= mail_encode($this->contentItem->vars['owner_email']); ?>" class="eLink1"> Kontakt per E-Mail </a> <br />
<?php endif; ?>
</p>

<?php if (!$this->contentItem->is_individual()) : ?>
<p class="eContent1">
<?php if ($this->contentItem->has_content('owner_company_siret')) : ?>
SIRET : <?= $this->contentItem->vars['owner_company_siret']; ?> <br />
<?php endif; ?>
<?php if ($this->contentItem->has_content('owner_company_vat')) : ?>
Innergemeinschaftliche Umsatzsteuer-ID: <?= $this->contentItem->vars['owner_company_vat']; ?> <br />
<?php endif; ?>
<?php if ($this->contentItem->has_content('owner_company_capital')) : ?>
Gesellschaftskapital: <?= $this->contentItem->vars['owner_company_capital']; ?> <br />
<?php endif; ?>
<?php if ($this->contentItem->has_content('owner_company_rcsnum') and $this->contentItem->has_content('owner_company_rcsloc')) : ?>
Eingetragen unter der Nummer: <?= $this->contentItem->vars['owner_company_rcsnum']; ?> - <?= $this->contentItem->vars['owner_company_rcsloc']; ?><br />
<?php endif; ?>
<?php if ($this->contentItem->has_content('owner_company_naf')) : ?>
Code NAF : <?= $this->contentItem->vars['owner_company_naf']; ?> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('owner_additional')) : ?>
<?= $this->contentItem->vars['owner_additional']; ?> <br />
<?php endif; ?>
</p>
<h3 class="eTitle3">
    Verantwortlicher für die Veröffentlichung
</h3>
<p class="eContent1">
<a href="<?= mail_encode($this->contentItem->vars['owner_manageremail']); ?>" class="eLink1">
<?= $this->contentItem->vars['owner_managername']; ?>
</a> <br />
Der Verantwortliche für die Veröffentlichung ist eine natürliche oder juristische Person.
</p>
<?php endif; ?>

<?php if ($this->contentItem->has_content('creator_name')) : ?>
<h3 class="eTitle3">
    Erstellung
</h3>

<p class="eContent1">
<span class="eContent2"> <?= $this->contentItem->vars['creator_name']; ?> </span> <br />

<?php if ($this->contentItem->has_content('creator_address')) : ?>
    <?= $this->contentItem->vars['creator_address']; ?> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('creator_phone')) : ?>
    Telefon: <?= $this->contentItem->vars['creator_phone']; ?> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('creator_fax')) : ?>
    Fax: <?= $this->contentItem->vars['creator_fax']; ?> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('creator_email')) : ?>
    <a href="<?= mail_encode($this->contentItem->vars['creator_email']); ?>" class="eLink1"> Kontakt per E-Mail </a> <br />
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
    Datenschutzbeauftragter (DPO)
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
    Hosting-Anbieter
</h3>

<p class="eContent1">
<span class="eContent2"> <?= $this->contentItem->vars['host_name']; ?> </span> <br />

<?php if ($this->contentItem->has_content('host_address')) : ?>
    <?= $this->contentItem->vars['host_address']; ?> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('host_phone')) : ?>
    Telefon: <?= $this->contentItem->vars['host_phone']; ?> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('host_fax')) : ?>
    Fax: <?= $this->contentItem->vars['host_fax']; ?> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('host_email')) : ?>
    <a href="<?= mail_encode($this->contentItem->vars['host_email']); ?>" class="eLink1">Kontakt per E-Mail</a> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('host_website')) : ?>
    <a href="<?= url_getAsComplete($this->contentItem->vars['host_website']); ?>" class="eLink1" target="_blank"><?= url_getAsSmart($this->contentItem->vars['host_website']); ?></a> <br />
<?php endif; ?>

<?php endif; ?>

<p class="eContent1">
    &nbsp;
</p>
