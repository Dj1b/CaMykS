<?php
/**
 * @brief Content_GenericLegalMentions module, italian sub layout.
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
<div id="LM-Properties" class="anchor" title="1. Editore/i del Sito"></div>

<h2 class="eTitle2">
    1. Editore/i del Sito
</h2>

<p class="eContent1">
Ai sensi dell'articolo 6 della legge francese n. 2004-575 del 21 giugno 2004 sulla fiducia nell'economia digitale, gli utenti del <span class="eContent2">Sito</span> web <?= $this->contentItem->get_websiteURL(); ?> sono informati dell'identità dei diversi soggetti coinvolti nella sua realizzazione e gestione.
</p>

<?php if ($this->contentItem->is_individual()) : ?>
<h3 class="eTitle3">
    Proprietario e responsabile della pubblicazione
</h3>
<p class="eContent1">
    <a href="<?= mail_encode($this->contentItem->vars['owner_manageremail']); ?>" class="eLink1">
    <?= $this->contentItem->vars['owner_managername']; ?>
    </a> <br />
    Il responsabile della pubblicazione è una persona fisica o giuridica.
<?php else : ?>
<h3 class="eTitle3">
    Proprietario
</h3>
<p class="eContent1">
        <span class="eContent2"><?= $this->contentItem->vars['owner_name'].' '. $this->contentItem->vars['owner_company_legalform']; ?></span> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('owner_address')) : ?>
    <?= $this->contentItem->vars['owner_address']; ?> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('owner_phone')) : ?>
    Telefono: <?= $this->contentItem->vars['owner_phone']; ?> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('owner_fax')) : ?>
    Fax: <?= $this->contentItem->vars['owner_fax']; ?> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('owner_email')) : ?>
    <a href="<?= mail_encode($this->contentItem->vars['owner_email']); ?>" class="eLink1"> Contatto via e-mail </a> <br />
<?php endif; ?>
</p>

<?php if (!$this->contentItem->is_individual()) : ?>
<p class="eContent1">
<?php if ($this->contentItem->has_content('owner_company_siret')) : ?>
SIRET : <?= $this->contentItem->vars['owner_company_siret']; ?> <br />
<?php endif; ?>
<?php if ($this->contentItem->has_content('owner_company_vat')) : ?>
Partita IVA intracomunitaria: <?= $this->contentItem->vars['owner_company_vat']; ?> <br />
<?php endif; ?>
<?php if ($this->contentItem->has_content('owner_company_capital')) : ?>
Capitale sociale: <?= $this->contentItem->vars['owner_company_capital']; ?> <br />
<?php endif; ?>
<?php if ($this->contentItem->has_content('owner_company_rcsnum') and $this->contentItem->has_content('owner_company_rcsloc')) : ?>
Registrata con il numero: <?= $this->contentItem->vars['owner_company_rcsnum']; ?> - <?= $this->contentItem->vars['owner_company_rcsloc']; ?><br />
<?php endif; ?>
<?php if ($this->contentItem->has_content('owner_company_naf')) : ?>
Code NAF : <?= $this->contentItem->vars['owner_company_naf']; ?> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('owner_additional')) : ?>
<?= $this->contentItem->vars['owner_additional']; ?> <br />
<?php endif; ?>
</p>
<h3 class="eTitle3">
    Responsabile della pubblicazione
</h3>
<p class="eContent1">
<a href="<?= mail_encode($this->contentItem->vars['owner_manageremail']); ?>" class="eLink1">
<?= $this->contentItem->vars['owner_managername']; ?>
</a> <br />
Il responsabile della pubblicazione è una persona fisica o giuridica.
</p>
<?php endif; ?>

<?php if ($this->contentItem->has_content('creator_name')) : ?>
<h3 class="eTitle3">
    Realizzazione
</h3>

<p class="eContent1">
<span class="eContent2"> <?= $this->contentItem->vars['creator_name']; ?> </span> <br />

<?php if ($this->contentItem->has_content('creator_address')) : ?>
    <?= $this->contentItem->vars['creator_address']; ?> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('creator_phone')) : ?>
    Telefono: <?= $this->contentItem->vars['creator_phone']; ?> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('creator_fax')) : ?>
    Fax: <?= $this->contentItem->vars['creator_fax']; ?> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('creator_email')) : ?>
    <a href="<?= mail_encode($this->contentItem->vars['creator_email']); ?>" class="eLink1"> Contatto via e-mail </a> <br />
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
    Responsabile della protezione dei dati (DPO)
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
    Fornitore di hosting
</h3>

<p class="eContent1">
<span class="eContent2"> <?= $this->contentItem->vars['host_name']; ?> </span> <br />

<?php if ($this->contentItem->has_content('host_address')) : ?>
    <?= $this->contentItem->vars['host_address']; ?> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('host_phone')) : ?>
    Telefono: <?= $this->contentItem->vars['host_phone']; ?> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('host_fax')) : ?>
    Fax: <?= $this->contentItem->vars['host_fax']; ?> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('host_email')) : ?>
    <a href="<?= mail_encode($this->contentItem->vars['host_email']); ?>" class="eLink1">Contatto via e-mail</a> <br />
<?php endif; ?>

<?php if ($this->contentItem->has_content('host_website')) : ?>
    <a href="<?= url_getAsComplete($this->contentItem->vars['host_website']); ?>" class="eLink1" target="_blank"><?= url_getAsSmart($this->contentItem->vars['host_website']); ?></a> <br />
<?php endif; ?>

<?php endif; ?>

<p class="eContent1">
    &nbsp;
</p>
