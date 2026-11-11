<?php
/**
 * @brief Content_GenericLegalMentions module, site data, italian sub layout.
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
<div id="LM-Data" class="anchor" title="7. Gestione dei dati personali"></div>

<h2 class="eTitle2">
    7. Gestione dei dati personali
</h2>

<p class="eContent1">
    L'<span class="eContent2">Internauta</span> è informato delle norme relative alle comunicazioni di marketing, della legge francese del 21 giugno 2014 sulla fiducia nell'economia digitale, della legge francese Informatica e Libertà del 6 agosto 2004 e del Regolamento generale sulla protezione dei dati (RGPD: n. 2016-679).
</p>

<h3 class="eTitle3">
    7.1 Responsabili della raccolta dei dati personali
</h3>

<p class="eContent1">
    Per i <span class="eContent2">Dati Personali</span> raccolti nell'ambito dell'utilizzo e della navigazione sul <span class="eContent2">Sito</span>, il titolare del trattamento dei <span class="eContent2">Dati Personali</span> è <?= $this->contentItem->get_editorFullName(); ?>.
</p>

<p class="eContent1">
<?= $this->contentItem->vars['owner_name']; ?> è rappresentato da <a href="<?= mail_encode($this->contentItem->vars['owner_manageremail']); ?>" class="eLink1"><?= $this->contentItem->vars['owner_managername']; ?></a><?php if (!$this->contentItem->is_individual()) : ?>, suo rappresentante legale<?php endif; ?>.
</p>

<p class="eContent1">
    In qualità di titolare del trattamento dei dati raccolti dal <span class="eContent2">Sito</span>, <?= $this->contentItem->get_editorFullName(); ?> si impegna a rispettare le disposizioni di legge vigenti. Spetta in particolare al <span class="eContent2">Cliente</span> determinare le finalità dei propri trattamenti di dati, fornire ai potenziali clienti e ai clienti, in occasione della raccolta del loro consenso, informazioni complete sul trattamento dei loro <span class="eContent2">Dati Personali</span> e mantenere un registro dei trattamenti conforme alla realtà. Ogni volta che <?= $this->contentItem->get_editorFullName(); ?> tratta <span class="eContent2">Dati Personali</span>, <?= $this->contentItem->get_editorFullName(); ?> adotta tutte le misure ragionevoli per garantire l'esattezza e la pertinenza dei <span class="eContent2">Dati Personali</span> rispetto alle finalità per cui <?= $this->contentItem->get_editorFullName(); ?> li tratta.
</p>

<h3 class="eTitle3">
    7.2 Finalità dei dati raccolti
</h3>

<p class="eContent1">
    <?= ucfirst($this->contentItem->get_editorFullName()); ?> può trattare tutti o parte dei dati:
</p>

<ul>
    <li class="eContent1">
        <strong>per migliorare la navigazione sul</strong> <span class="eContent2">Sito</span>
        <ul>
            <li><b>Dati raccolti</b>: dati di connessione e di utilizzo</li>
            <li><b>Periodo di conservazione dei dati</b>: massimo 12 mesi.</li>
        </ul>
    </li>

    <li class="eContent1">
        <strong>per prevenire e contrastare le frodi informatiche (spam, pirateria informatica, ecc.)</strong>
        <ul>
            <li><b>Dati raccolti</b>: dispositivo informatico utilizzato (user agent) per la navigazione e indirizzo IP</li>
            <li><b>Periodo di conservazione dei dati</b>: massimo 12 mesi.</li>
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
                        <b>Dati raccolti</b>: <?= $data['data']; ?>
                    </li>
                    <?php endif; ?>
                    <li>
                        <b>Periodo di conservazione dei dati</b>:
                        <?php if ($data['duration'] != '') : ?>
                            <?= $data['duration']; ?>
                        <?php else : ?>
                            Massimo 12 mesi.
                        <?php endif; ?>
                    </li>
                </ul>
            </li>
        <?php endforeach; ?>
        <?php endforeach; ?>
    <?php endforeach; ?>
</ul>

<h3 class="eTitle3">
    7.3 Diritto di accesso, rettifica e opposizione
</h3>

<p class="eContent1">
    In conformità alla normativa europea vigente, gli <span class="eContent2">Utenti</span> del <span class="eContent2">Sito</span> <?= $this->contentItem->get_websiteURL(); ?> dispongono dei seguenti diritti:

</p>

<ul>
    <li class="eContent1">
        diritto di accesso (articolo 15 RGPD) e di rettifica (articolo 16 RGPD), aggiornamento e integrazione dei <span class="eContent2">Dati Personali</span> degli <span class="eContent2">Utenti</span>; diritto al blocco o alla cancellazione dei dati personali degli <span class="eContent2">Utenti</span> (articolo 17 RGPD) qualora siano inesatti, incompleti, ambigui od obsoleti, oppure qualora la loro raccolta, il loro utilizzo, la loro comunicazione o conservazione siano vietati,
    </li>

    <li class="eContent1">
        diritto di revocare in qualsiasi momento il consenso (articolo 13-2c RGPD),
    </li>

    <li class="eContent1">
        diritto alla limitazione del trattamento dei dati degli <span class="eContent2">Utenti</span> (articolo 18 RGPD),
    </li>

    <li class="eContent1">
        diritto di opporsi al trattamento dei dati degli <span class="eContent2">Utenti</span> (articolo 21 RGPD),
    </li>

    <li class="eContent1">
        diritto alla portabilità dei dati forniti dagli <span class="eContent2">Utenti</span>, qualora siano oggetto di trattamenti automatizzati fondati sul consenso o su un contratto (articolo 20 RGPD),
    </li>

    <li class="eContent1">
        diritto di stabilire la destinazione dei dati degli <span class="eContent2">Utenti</span> dopo la loro morte e di scegliere a chi <?= $this->contentItem->get_editorFullName(); ?> debba comunicare (o meno) tali dati fra i terzi precedentemente designati,
    </li>

    <li class="eContent1">
        quando <?= $this->contentItem->get_editorFullName(); ?> viene a conoscenza del decesso di un <span class="eContent2">Utente</span> e in assenza di sue istruzioni, <?= $this->contentItem->get_editorFullName(); ?> si impegna a distruggere i suoi <span class="eContent2">Dati Personali</span>, salvo che la loro conservazione sia necessaria a fini probatori o per adempiere a un obbligo legale.
    </li>
</ul>

<p class="eContent1">
    Se l'<span class="eContent2">Utente</span> desidera sapere come <?= $this->contentItem->get_editorFullName(); ?> utilizza i suoi <span class="eContent2">Dati Personali</span>, chiederne la rettifica o opporsi al loro trattamento, l'<span class="eContent2">Utente</span> può contattare <?= $this->contentItem->get_editorFullName(); ?> per iscritto al seguente indirizzo: <br />
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
In tal caso, l'<span class="eContent2">Utente</span> deve indicare i <span class="eContent2">Dati Personali</span> che desidera siano corretti, aggiornati o eliminati da <?= $this->contentItem->get_editorFullName(); ?>, identificandosi in modo preciso mediante copia di un documento d'identità (carta d'identità o passaporto).
</p>

<p class="eContent1">
    Le richieste di cancellazione dei <span class="eContent2">Dati Personali</span> sono soggette agli obblighi imposti dalla legge a <?= $this->contentItem->get_editorFullName(); ?>, in particolare in materia di conservazione o archiviazione dei documenti. Infine, gli <span class="eContent2">Utenti</span> del <span class="eContent2">Sito</span> <?= $this->contentItem->get_websiteURL(); ?> possono presentare un reclamo alle autorità di controllo e, in particolare, alla <a href="https://www.cnil.fr/fr/plaintes" class="eLink1" target="_blank" rel="noopener noreferer">CNIL</a>.
</p>

<h3 class="eTitle3">
    7.4 Divieto di comunicazione dei dati personali
</h3>

<p class="eContent1">
    <?= ucfirst($this->contentItem->get_editorFullName()); ?> si impegna a non trattare, ospitare o trasferire le informazioni raccolte sui propri <span class="eContent2">Clienti</span> verso un paese situato fuori dall'Unione europea o riconosciuto come «non adeguato» dalla Commissione europea senza informare preventivamente il <span class="eContent2">Cliente</span>. <?= $this->contentItem->get_editorFullName(); ?> rimane comunque libero di scegliere i propri subappaltatori tecnici e commerciali purché offrano garanzie sufficienti rispetto ai requisiti del Regolamento generale sulla protezione dei dati (RGPD: n. 2016-679).
</p>

<p class="eContent1">
    <?= ucfirst($this->contentItem->get_editorFullName()); ?> si impegna ad adottare tutte le precauzioni necessarie per tutelare la sicurezza dei <span class="eContent2">Dati Personali</span> e, in particolare, per evitare che siano comunicati a persone non autorizzate. Tuttavia, se <?= $this->contentItem->get_editorFullName(); ?> viene a conoscenza di un incidente che compromette l'integrità o la riservatezza dei <span class="eContent2">Dati Personali</span> del <span class="eContent2">Cliente</span>, deve informare quest'ultimo il prima possibile e comunicargli le misure correttive adottate. Inoltre, <?= $this->contentItem->get_editorFullName(); ?> non raccoglie «dati sensibili».
</p>

<?php if (!$this->contentItem->is_individual()) : ?>
<p class="eContent1">
    I <span class="eContent2">Dati Personali</span> dell'<span class="eContent2">Utente</span> possono essere trattati da società controllate da <?= $this->contentItem->get_editorFullName(); ?> e da subappaltatori (fornitori di servizi), esclusivamente per le finalità della presente informativa.
</p>

<p class="eContent1">
    Le persone che possono accedere ai <span class="eContent2">Dati Personali</span> degli <span class="eContent2">Utenti</span> di <?= $this->contentItem->get_websiteURL(); ?> sono designate sotto la sola responsabilità del responsabile di <?= $this->contentItem->get_editorFullName(); ?>. Le rispettive mansioni possono inoltre essere limitate in base alle esigenze e alle finalità sopra indicate.
</p>
<?php endif; ?>

<p class="eContent1">
    &nbsp;
</p>
