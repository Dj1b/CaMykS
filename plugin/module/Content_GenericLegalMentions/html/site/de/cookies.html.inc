<?php
/**
 * @brief Content_GenericLegalMentions module, site cookies, german sub layout.
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
    Ein „Cookie“ ist eine kleine Informationsdatei, die an den Browser des <span class="eContent2">Nutzers</span> gesendet und auf dem Gerät des <span class="eContent2">Nutzers</span> gespeichert wird (z. B. Computer oder Smartphone). Diese Datei enthält Angaben wie den Domainnamen des <span class="eContent2">Nutzers</span>, den Internetzugangsanbieter des <span class="eContent2">Nutzers</span>, das Betriebssystem des <span class="eContent2">Nutzers</span> sowie Datum und Uhrzeit des Zugriffs. Cookies können das Gerät des Nutzers in keinem Fall beschädigen.
</p>

<p class="eContent1">
    <?= ucfirst($this->contentItem->get_editorFullName()); ?> kann Informationen über den Besuch des <span class="eContent2">Nutzers</span> auf der <span class="eContent2">Website</span> verarbeiten, etwa aufgerufene Seiten und durchgeführte Suchanfragen. Diese Informationen ermöglichen es <?= $this->contentItem->get_editorFullName(); ?>, die Inhalte der <span class="eContent2">Website</span> und die Navigation des <span class="eContent2">Nutzers</span> zu verbessern.
</p>

<p class="eContent1">
    Da Cookies die Navigation und/oder die Bereitstellung der auf der <span class="eContent2">Website</span> angebotenen Dienste erleichtern, kann der <span class="eContent2">Nutzer</span> seinen Browser so einstellen, dass er über die Annahme von Cookies entscheidet. Cookies können so auf dem Gerät gespeichert oder grundsätzlich beziehungsweise je nach Absender abgelehnt werden. Der <span class="eContent2">Nutzer</span> kann seinen Browser auch so einstellen, dass er vor der Speicherung eines Cookies für die Dauer des Besuchs des <span class="eContent2">Nutzers</span> jeweils zur Annahme oder Ablehnung aufgefordert wird. <?= ucfirst($this->contentItem->get_editorFullName()); ?> weist den <span class="eContent2">Nutzer</span> darauf hin, dass in diesem Fall möglicherweise nicht alle Funktionen der <span class="eContent2">Website</span> verfügbar sind.
</p>

<p class="eContent1">
    Lehnt der <span class="eContent2">Nutzer</span> die Speicherung von Cookies auf seinem Gerät oder in seinem Browser ab oder löscht der <span class="eContent2">Nutzer</span> bereits gespeicherte Cookies, wird der <span class="eContent2">Nutzer</span> darüber informiert, dass die Navigation und die Nutzung der <span class="eContent2">Website</span> eingeschränkt sein können. Das kann auch dann der Fall sein, wenn <?= $this->contentItem->get_editorFullName(); ?> oder einer seiner Dienstleister aus Gründen der technischen Kompatibilität den verwendeten Browsertyp, die Sprach- und Anzeigeeinstellungen oder das Land, aus dem das Gerät offenbar mit dem Internet verbunden ist, nicht erkennen kann.
</p>

<p class="eContent1">
    Gegebenenfalls übernimmt <?= $this->contentItem->get_editorFullName(); ?> keine Haftung für die Folgen einer eingeschränkten Funktionsfähigkeit der <span class="eContent2">Website</span> und der möglicherweise von <?= $this->contentItem->get_editorFullName(); ?> angebotenen Dienste, die sich (i) aus der Ablehnung von Cookies durch den Nutzer oder (ii) daraus ergeben, dass <?= $this->contentItem->get_editorFullName(); ?> aufgrund der Entscheidung des <span class="eContent2">Nutzers</span> die für den Betrieb erforderlichen Cookies nicht speichern oder auslesen kann. Die Einstellungen zur Verwaltung von Cookies und der Entscheidungen des <span class="eContent2">Nutzers</span> unterscheiden sich je nach Browser. Im Hilfemenü des Browsers wird erklärt, wie der <span class="eContent2">Nutzer</span> seine Cookie-Einstellungen ändern kann.
</p>

<p class="eContent1">
Der <span class="eContent2">Nutzer</span> kann seine Cookie-Einstellungen jederzeit festlegen und ändern. <?= ucfirst($this->contentItem->get_editorFullName()); ?> kann außerdem externe Dienstleister hinzuziehen, die bei der Erfassung und Verarbeitung der in diesem Abschnitt beschriebenen Informationen helfen.
</p>

<p class="eContent1">
Diese Cookies werden nur dann auf Ihren Geräten gespeichert, wenn Sie durch die weitere Nutzung der <span class="eContent2">Website</span> oder der mobilen Anwendung von <?= $this->contentItem->get_editorFullName(); ?> darin einwilligen. Der <span class="eContent2">Nutzer</span> kann seine Einwilligung in die Speicherung solcher Cookies durch die <span class="eContent2">Website</span> jedoch jederzeit widerrufen.
</p>

<?php if ($this->cookieAgreementInput !== false) : ?>
<p class="eContent1">
Nachstehend sind die Dienste auf der <span class="eContent2">Website</span> aufgeführt, die Cookies verwenden:
</p>
<ul>
    <?php foreach($this->cookieAgreementInput->get_servicesList() as $service) : ?>
        <li class="eContent1">
            <span class="eContent2"><?= $service['title']; ?></span>
            <br /><?= $service['purpose']; ?>
            <?php if ($service['usage'] !== '') : ?>
                <br />Verwendung: <?= $service['usage']; ?>
            <?php endif; ?>
            <?php if ($service['duration'] !== '') : ?>
                <br />Speicherdauer: <?= $service['duration']; ?>
            <?php endif; ?>
            <?php if ($service['aboutURL'] != '') : ?>
                <br /><a href="<?= $service['aboutURL']; ?>" class="link" target="_blank" rel="noopener,noreferer,nofollow">Mehr erfahren</a>
            <?php endif; ?>
        </li>
    <?php endforeach; ?>
</ul>

<p class="eContent1" style="text-align:center;">
    <?= $this->theme->get_button(array(
        'title' => 'Cookie-Verwaltung öffnen',
        'url'   => $this->cookieAgreementInput->get_cookieManagementPanelOpenLink(),
    )); ?>
</p>

<?php endif; ?>

<p class="eContent1">
    &nbsp;
</p>

