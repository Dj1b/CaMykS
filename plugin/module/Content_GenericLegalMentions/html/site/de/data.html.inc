<?php
/**
 * @brief Content_GenericLegalMentions module, site data, german sub layout.
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
<div id="LM-Data" class="anchor" title="7. Verarbeitung personenbezogener Daten"></div>

<h2 class="eTitle2">
    7. Verarbeitung personenbezogener Daten
</h2>

<p class="eContent1">
    Der <span class="eContent2">Internetnutzer</span> wird über die Vorschriften zur Marketingkommunikation, das französische Gesetz vom 21. Juni 2014 über das Vertrauen in die digitale Wirtschaft, das französische Gesetz über Informatik und Freiheitsrechte vom 6. August 2004 sowie die Datenschutz-Grundverordnung (DSGVO: Nr. 2016-679) informiert.
</p>

<h3 class="eTitle3">
    7.1 Verantwortliche für die Erhebung personenbezogener Daten
</h3>

<p class="eContent1">
    Verantwortlich für die Verarbeitung der <span class="eContent2">personenbezogenen Daten</span>, die bei der Nutzung und beim Besuch der <span class="eContent2">Website</span> erhoben werden, ist hinsichtlich dieser <span class="eContent2">personenbezogenen Daten</span> <?= $this->contentItem->get_editorFullName(); ?>.
</p>

<p class="eContent1">
<?= $this->contentItem->vars['owner_name']; ?> wird vertreten durch <a href="<?= mail_encode($this->contentItem->vars['owner_manageremail']); ?>" class="eLink1"><?= $this->contentItem->vars['owner_managername']; ?></a><?php if (!$this->contentItem->is_individual()) : ?>, seinen gesetzlichen Vertreter<?php endif; ?>.
</p>

<p class="eContent1">
    Als Verantwortlicher für die Verarbeitung der von der <span class="eContent2">Website</span> erhobenen Daten verpflichtet sich <?= $this->contentItem->get_editorFullName(); ?> zur Einhaltung der geltenden gesetzlichen Vorschriften. Insbesondere obliegt es dem <span class="eContent2">Kunden</span>, die Zwecke seiner Datenverarbeitung festzulegen, Interessenten und Kunden bei der Einholung ihrer Einwilligung umfassend über die Verarbeitung ihrer <span class="eContent2">personenbezogenen Daten</span> zu informieren und ein den tatsächlichen Verarbeitungen entsprechendes Verzeichnis zu führen. Wenn <?= $this->contentItem->get_editorFullName(); ?> <span class="eContent2">personenbezogene Daten</span> verarbeitet, ergreift <?= $this->contentItem->get_editorFullName(); ?> alle angemessenen Maßnahmen, um die Richtigkeit und Relevanz der <span class="eContent2">personenbezogenen Daten</span> im Hinblick auf die Zwecke sicherzustellen, für die <?= $this->contentItem->get_editorFullName(); ?> sie verarbeitet.
</p>

<h3 class="eTitle3">
    7.2 Zwecke der erhobenen Daten
</h3>

<p class="eContent1">
    <?= ucfirst($this->contentItem->get_editorFullName()); ?> kann die Daten ganz oder teilweise zu folgenden Zwecken verarbeiten:
</p>

<ul>
    <li class="eContent1">
        <strong>zur Verbesserung der Navigation auf der</strong> <span class="eContent2">Website</span>
        <ul>
            <li><b>Erhobene Daten</b>: Verbindungs- und Nutzungsdaten</li>
            <li><b>Aufbewahrungsdauer der Daten</b>: höchstens 12 Monate.</li>
        </ul>
    </li>

    <li class="eContent1">
        <strong>zur Vorbeugung und Bekämpfung von Computerbetrug (Spam, Hacking usw.)</strong>
        <ul>
            <li><b>Erhobene Daten</b>: für die Navigation verwendetes Gerät (User-Agent) und IP-Adresse</li>
            <li><b>Aufbewahrungsdauer der Daten</b>: höchstens 12 Monate.</li>
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
                        <b>Erhobene Daten</b>: <?= $data['data']; ?>
                    </li>
                    <?php endif; ?>
                    <li>
                        <b>Aufbewahrungsdauer der Daten</b>:
                        <?php if ($data['duration'] != '') : ?>
                            <?= $data['duration']; ?>
                        <?php else : ?>
                            Höchstens 12 Monate.
                        <?php endif; ?>
                    </li>
                </ul>
            </li>
        <?php endforeach; ?>
        <?php endforeach; ?>
    <?php endforeach; ?>
</ul>

<h3 class="eTitle3">
    7.3 Rechte auf Auskunft, Berichtigung und Widerspruch
</h3>

<p class="eContent1">
    Gemäß den geltenden europäischen Vorschriften stehen den <span class="eContent2">Nutzern</span> der <span class="eContent2">Website</span> <?= $this->contentItem->get_websiteURL(); ?> folgende Rechte zu:

</p>

<ul>
    <li class="eContent1">
        Recht auf Auskunft (Artikel 15 DSGVO) und Berichtigung (Artikel 16 DSGVO) sowie auf Aktualisierung und Vervollständigung der <span class="eContent2">personenbezogenen Daten</span> der <span class="eContent2">Nutzer</span>; Recht auf Sperrung oder Löschung personenbezogener Daten der <span class="eContent2">Nutzer</span> (Artikel 17 DSGVO), wenn diese unrichtig, unvollständig, mehrdeutig oder veraltet sind oder ihre Erhebung, Nutzung, Weitergabe oder Speicherung verboten ist,
    </li>

    <li class="eContent1">
        Recht, eine Einwilligung jederzeit zu widerrufen (Artikel 13-2c DSGVO),
    </li>

    <li class="eContent1">
        Recht auf Einschränkung der Verarbeitung der Daten der <span class="eContent2">Nutzer</span> (Artikel 18 DSGVO),
    </li>

    <li class="eContent1">
        Recht auf Widerspruch gegen die Verarbeitung der Daten der <span class="eContent2">Nutzer</span> (Artikel 21 DSGVO),
    </li>

    <li class="eContent1">
        Recht auf Datenübertragbarkeit hinsichtlich der von den <span class="eContent2">Nutzern</span> bereitgestellten Daten, wenn diese auf Grundlage ihrer Einwilligung oder eines Vertrags automatisiert verarbeitet werden (Artikel 20 DSGVO),
    </li>

    <li class="eContent1">
        Recht, über den Verbleib der Daten der <span class="eContent2">Nutzer</span> nach ihrem Tod zu bestimmen und festzulegen, an welche zuvor benannten Dritten <?= $this->contentItem->get_editorFullName(); ?> diese Daten weitergeben darf oder nicht,
    </li>

    <li class="eContent1">
        sobald <?= $this->contentItem->get_editorFullName(); ?> vom Tod eines <span class="eContent2">Nutzers</span> erfährt und keine Anweisungen vorliegen, verpflichtet sich <?= $this->contentItem->get_editorFullName(); ?>, dessen <span class="eContent2">personenbezogene Daten</span> zu löschen, sofern ihre Aufbewahrung nicht zu Beweiszwecken oder zur Erfüllung einer gesetzlichen Pflicht erforderlich ist.
    </li>
</ul>

<p class="eContent1">
    Wenn der <span class="eContent2">Nutzer</span> wissen möchte, wie <?= $this->contentItem->get_editorFullName(); ?> seine <span class="eContent2">personenbezogenen Daten</span> verwendet, ihre Berichtigung verlangen oder der Verarbeitung widersprechen möchte, kann der <span class="eContent2">Nutzer</span> <?= $this->contentItem->get_editorFullName(); ?> schriftlich unter folgender Adresse kontaktieren: <br />
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
In diesem Fall muss der <span class="eContent2">Nutzer</span> angeben, welche <span class="eContent2">personenbezogenen Daten</span> <?= $this->contentItem->get_editorFullName(); ?> berichtigen, aktualisieren oder löschen soll, und sich durch eine Kopie eines Ausweisdokuments (Personalausweis oder Reisepass) eindeutig ausweisen.
</p>

<p class="eContent1">
    Anträge auf Löschung <span class="eContent2">personenbezogener Daten</span> unterliegen den gesetzlichen Pflichten von <?= $this->contentItem->get_editorFullName(); ?>, insbesondere hinsichtlich der Aufbewahrung oder Archivierung von Dokumenten. Die <span class="eContent2">Nutzer</span> der <span class="eContent2">Website</span> <?= $this->contentItem->get_websiteURL(); ?> können außerdem bei den Aufsichtsbehörden, insbesondere bei der <a href="https://www.cnil.fr/fr/plaintes" class="eLink1" target="_blank" rel="noopener noreferer">CNIL</a>, Beschwerde einlegen.
</p>

<h3 class="eTitle3">
    7.4 Keine Weitergabe personenbezogener Daten
</h3>

<p class="eContent1">
    <?= ucfirst($this->contentItem->get_editorFullName()); ?> verpflichtet sich, Informationen über seine <span class="eContent2">Kunden</span> ohne vorherige Benachrichtigung des <span class="eContent2">Kunden</span> weder in einem Land außerhalb der Europäischen Union oder in einem von der Europäischen Kommission als „nicht angemessen“ eingestuften Land zu verarbeiten noch dort zu hosten oder dorthin zu übertragen. <?= $this->contentItem->get_editorFullName(); ?> kann seine technischen und geschäftlichen Unterauftragnehmer jedoch frei wählen, sofern diese ausreichende Garantien im Hinblick auf die Anforderungen der Datenschutz-Grundverordnung (DSGVO: Nr. 2016-679) bieten.
</p>

<p class="eContent1">
    <?= ucfirst($this->contentItem->get_editorFullName()); ?> verpflichtet sich, alle erforderlichen Vorkehrungen zum Schutz der <span class="eContent2">personenbezogenen Daten</span> zu treffen und insbesondere deren Weitergabe an Unbefugte zu verhindern. Erfährt <?= $this->contentItem->get_editorFullName(); ?> jedoch von einem Vorfall, der die Integrität oder Vertraulichkeit der <span class="eContent2">personenbezogenen Daten</span> des <span class="eContent2">Kunden</span> beeinträchtigt, muss der Kunde so bald wie möglich informiert und über die ergriffenen Abhilfemaßnahmen unterrichtet werden. Darüber hinaus erhebt <?= $this->contentItem->get_editorFullName(); ?> keine „sensiblen Daten“.
</p>

<?php if (!$this->contentItem->is_individual()) : ?>
<p class="eContent1">
    Die <span class="eContent2">personenbezogenen Daten</span> des <span class="eContent2">Nutzers</span> können von Tochtergesellschaften von <?= $this->contentItem->get_editorFullName(); ?> und von Unterauftragnehmern (Dienstleistern) ausschließlich zur Erfüllung der Zwecke dieser Richtlinie verarbeitet werden.
</p>

<p class="eContent1">
    Personen, die Zugang zu den <span class="eContent2">personenbezogenen Daten</span> der <span class="eContent2">Nutzer</span> von <?= $this->contentItem->get_websiteURL(); ?> erhalten können, werden unter der alleinigen Verantwortung der verantwortlichen Person von <?= $this->contentItem->get_editorFullName(); ?> bestimmt. Ihre jeweiligen Befugnisse können entsprechend den oben genannten Erfordernissen und Zwecken beschränkt werden.
</p>
<?php endif; ?>

<p class="eContent1">
    &nbsp;
</p>
