<?php
/**
 * @brief Content_GenericLegalMentions module, site cookies, italian sub layout.
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
<div id="LM-Cookies" class="anchor" title="9. Cookies."></div>

<h2 class="eTitle2">
    9. Cookies
</h2>

<p class="eContent1">
    Un «cookie» è un piccolo file informativo inviato al browser dell'<span class="eContent2">Utente</span> e memorizzato sul dispositivo dell'<span class="eContent2">Utente</span> (per esempio, computer o smartphone). Il file contiene informazioni quali il nome di dominio dell'<span class="eContent2">Utente</span>, il fornitore di accesso a Internet dell'<span class="eContent2">Utente</span>, il sistema operativo dell'<span class="eContent2">Utente</span>, nonché la data e l'ora dell'accesso. I cookie non possono in alcun caso danneggiare il dispositivo dell'Utente.
</p>

<p class="eContent1">
    <?= ucfirst($this->contentItem->get_editorFullName()); ?> può trattare le informazioni dell'<span class="eContent2">Utente</span> relative alla sua visita al <span class="eContent2">Sito</span>, come le pagine consultate e le ricerche effettuate. Tali informazioni permettono a <?= $this->contentItem->get_editorFullName(); ?> di migliorare il contenuto del <span class="eContent2">Sito</span> e la navigazione dell'<span class="eContent2">Utente</span>.
</p>

<p class="eContent1">
    Poiché i cookie facilitano la navigazione e/o la fornitura dei servizi offerti dal <span class="eContent2">Sito</span>, l'<span class="eContent2">Utente</span> può configurare il browser in modo da decidere se accettarli o meno, consentendo la loro memorizzazione sul dispositivo oppure rifiutandoli, sistematicamente o in base al soggetto che li invia. L'<span class="eContent2">Utente</span> può anche configurare il browser affinché la scelta di accettare o rifiutare i cookie venga proposta di volta in volta, prima che un cookie possa essere memorizzato sul dispositivo per la durata della visita dell'<span class="eContent2">Utente</span>. <?= ucfirst($this->contentItem->get_editorFullName()); ?> informa l'<span class="eContent2">Utente</span> che, in tal caso, alcune funzionalità offerte dal <span class="eContent2">Sito</span> potrebbero non essere disponibili.
</p>

<p class="eContent1">
    Se l'<span class="eContent2">Utente</span> rifiuta la memorizzazione dei cookie sul proprio dispositivo o browser, oppure se l'<span class="eContent2">Utente</span> elimina quelli già memorizzati, l'<span class="eContent2">Utente</span> è informato che la navigazione e l'esperienza sul <span class="eContent2">Sito</span> potrebbero risultare limitate. Ciò potrebbe verificarsi anche quando <?= $this->contentItem->get_editorFullName(); ?> o uno dei suoi fornitori non riesca a riconoscere, per ragioni di compatibilità tecnica, il tipo di browser utilizzato dal dispositivo, le impostazioni di lingua e visualizzazione o il paese dal quale il dispositivo sembra connesso a Internet.
</p>

<p class="eContent1">
    In tal caso, <?= $this->contentItem->get_editorFullName(); ?> declina ogni responsabilità per le conseguenze di un funzionamento ridotto del <span class="eContent2">Sito</span> e degli eventuali servizi offerti da <?= $this->contentItem->get_editorFullName(); ?>, derivanti (i) dal rifiuto dei cookie da parte dell'Utente o (ii) dall'impossibilità per <?= $this->contentItem->get_editorFullName(); ?> di memorizzare o consultare i cookie necessari al loro funzionamento a causa delle scelte dell'<span class="eContent2">Utente</span>. Per la gestione dei cookie e delle preferenze dell'<span class="eContent2">Utente</span>, la configurazione varia a seconda del browser. Le relative istruzioni sono disponibili nel menu di aiuto del browser, che spiega come l'<span class="eContent2">Utente</span> può modificare le proprie preferenze sui cookie.
</p>

<p class="eContent1">
In qualsiasi momento, l'<span class="eContent2">Utente</span> può esprimere e modificare le proprie preferenze in materia di cookie. <?= ucfirst($this->contentItem->get_editorFullName()); ?> può inoltre ricorrere a fornitori esterni che lo aiutino a raccogliere e trattare le informazioni descritte in questa sezione.
</p>

<p class="eContent1">
Questi cookie vengono installati sui vostri dispositivi solo se acconsentite continuando la navigazione sul <span class="eContent2">Sito</span> web o sull'applicazione mobile di <?= $this->contentItem->get_editorFullName(); ?>. L'<span class="eContent2">Utente</span> può comunque revocare in qualsiasi momento il consenso all'installazione di questo tipo di cookie da parte del <span class="eContent2">Sito</span>.
</p>

<?php if ($this->cookieAgreementInput !== false) : ?>
<p class="eContent1">
Di seguito è riportato l'elenco dei servizi presenti sul <span class="eContent2">Sito</span> che utilizzano cookie:
</p>
<ul>
    <?php foreach($this->cookieAgreementInput->get_servicesList() as $service) : ?>
        <li class="eContent1">
            <span class="eContent2"><?= $service['title']; ?></span>
            <br /><?= $service['purpose']; ?>
            <?php if ($service['usage'] !== '') : ?>
                <br />Utilizzo: <?= $service['usage']; ?>
            <?php endif; ?>
            <?php if ($service['duration'] !== '') : ?>
                <br />Durata: <?= $service['duration']; ?>
            <?php endif; ?>
            <?php if ($service['aboutURL'] != '') : ?>
                <br /><a href="<?= $service['aboutURL']; ?>" class="link" target="_blank" rel="noopener,noreferer,nofollow">Per saperne di più</a>
            <?php endif; ?>
        </li>
    <?php endforeach; ?>
</ul>

<p class="eContent1" style="text-align:center;">
    <?= $this->theme->get_button(array(
        'title' => 'Aprire il pannello di gestione dei cookie',
        'url'   => $this->cookieAgreementInput->get_cookieManagementPanelOpenLink(),
    )); ?>
</p>

<?php endif; ?>

<p class="eContent1">
    &nbsp;
</p>

