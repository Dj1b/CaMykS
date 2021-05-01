<?php
/**
 * @brief Content_GenericLegalMentions Module site data, english sub layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Apr 2021
 * @date Modification: Apr 2021
 * @copyright 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
?>
<div id="LM-Data" class="anchor" title="7. Management of personal data"></div>

<h2 class="eTitle2">
    7. Management of personal data
</h2>

<p class="eContent1">
    The <span class="eContent2">Web surfer</span> is informed of the regulations concerning marketing communication, the law of 21 June 2014 to promote confidence in the Digital Economy, the Computing and Freedom Law of 6 August 2004 and the General Data Protection Regulation (GDPR: n&deg; 2016-679).
</p>

<h3 class="eTitle3">
    7.1 Entities responsible for collecting personal data
</h3>

<p class="eContent1">
    In respect of the <span class="eContent2">Personal Data</span> collected in connection with use and browsing on the <span class="eContent2">Website</span>, the <span class="eContent2">Personal Data</span> controller is <?= $this->contentItem->get_editorFullName(); ?>.
</p>

<p class="eContent1">
<?= $this->contentItem->vars['owner_name']; ?> is represented by <a href="<?= mail_encode($this->contentItem->vars['owner_manageremail']); ?>" class="eLink1"><?= $this->contentItem->vars['owner_managername']; ?></a><?php if (!$this->contentItem->is_individual()) : ?>, its legal representative<?php endif; ?>.
</p>

<p class="eContent1">
    As data controller for data which the <span class="eContent2">Website</span> collects, <?= $this->contentItem->get_editorFullName(); ?> undertakes to comply with the legal provisions in force. It is the <span class="eContent2">Client</span>'s responsibility, in particular, to determine the purposes of its data processing, to provide its prospects and clients, from the time when their consents have been obtained, with complete information concerning processing of their <span class="eContent2">Personal Data</span>, and to keep a register of processing which reflects reality. Whenever <?= $this->contentItem->get_editorFullName(); ?> processes <span class="eContent2">Personal Data</span>, <?= $this->contentItem->get_editorFullName(); ?> takes all reasonable measures to ensure the accuracy and relevance of the <span class="eContent2">Personal Data</span>, bearing in mind the purposes for which <?= $this->contentItem->get_editorFullName(); ?> processes it.
</p>

<h3 class="eTitle3">
    7.2 Purpose of the collected data
</h3>

<p class="eContent1">
    <?= $this->contentItem->get_editorFullName(); ?> may process all or part of the data:
</p>

<ul>
    <li class="eContent1">
        <strong>to improve browsing on the</strong> <span class="eContent2">Website</span>
        <ul>
            <li><b>Collected data</b>: login and usage data</li>
            <li><b>Period for which the data is kept</b>: Maximum 12 months.</li>
        </ul>
    </li>

    <li class="eContent1">
        <strong>to prevent and take action against computer fraud (spamming, hacking, etc.)</strong>
        <ul>
            <li><b>Collected data</b>: computer equipment used (user agent) for browsing and the IP address</li>
            <li><b>Period for which the data is kept</b>: Maximum 12 months.</li>
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
                        <b>Collected data</b>: <?= $data['data']; ?>
                    </li>
                    <?php endif; ?>
                    <li>
                        <b>Period for which the data is kept</b>:
                        <?php if ($data['duration'] != '') : ?>
                            <?= $data['duration']; ?>
                        <?php else : ?>
                            Maximum 12 months.
                        <?php endif; ?>
                    </li>
                </ul>
            </li>
        <?php endforeach; ?>
        <?php endforeach; ?>
    <?php endforeach; ?>
</ul>

<h3 class="eTitle3">
    7.3 Right of access, rectification and objection
</h3>

<p class="eContent1">
    Pursuant to the European regulations in force, <span class="eContent2">Users</span> of the Site <?= $this->contentItem->get_websiteURL(); ?> have the following rights:
</p>

<ul>
    <li class="eContent1">
        a right of access (article 15 of the GDPR) and of rectification (article 16 of the GDPR), of update, of completeness of the <span class="eContent2">Users</span>' data, right to have <span class="eContent2">Users</span>' <span class="eContent2"><span class="eContent2">Personal Data</span></span> blocked or deleted (article 17 of the GDPR), when it is inaccurate, incomplete, ambiguous, out-of-date, or the collection, use, communication or conservation of which is prohibited,
    </li>

    <li class="eContent1">
        right to withdraw consent at any time (article 13-2c of the GDPR),
    </li>

    <li class="eContent1">
        right to restrict processing of <span class="eContent2">Users</span>' data (article 18 of the GDPR),
    </li>

    <li class="eContent1">
        right to object to processing of <span class="eContent2">Users</span>' data (article 21 of the GDPR),
    </li>

    <li class="eContent1">
        right to portability of data which the <span class="eContent2">Users</span> have provided, when this data is subject to automated processing based on their consent, or on a contract (article 20 of the GDPR),
    </li>

    <li class="eContent1">
        right to define how the <span class="eContent2">Users</span>' data is used after their death, and to choose to whom <?= $this->contentItem->get_editorFullName(); ?> must (or must not) send their data, to a third party which it has designated beforehand,
    </li>

    <li class="eContent1">
        as soon as <?= $this->contentItem->get_editorFullName(); ?> learns of the death of a <span class="eContent2">User</span>, and if this <span class="eContent2">User</span> has not given it any instructions, <?= $this->contentItem->get_editorFullName(); ?> undertakes to destroy its <span class="eContent2"><span class="eContent2">Personal Data</span></span>, unless conservation of it is required for probative purposes, or to meet a legal obligation.
    </li>
</ul>

<p class="eContent1">
    If the <span class="eContent2">User</span> wishes to know how <?= $this->contentItem->get_editorFullName(); ?> uses its <span class="eContent2">Personal Data</span>, to ask to rectify it or to object to processing of it, the <span class="eContent2">User</span> can contact <?= $this->contentItem->get_editorFullName(); ?> in writing at the following address: <br />
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
In this case the <span class="eContent2">User</span> must state which <span class="eContent2">Personal Data</span> it desires <?= $this->contentItem->get_editorFullName(); ?> to correct, update or delete, identifying itself precisely with a copy of an identity document (identity card or passport).
</p>

<p class="eContent1">
    Requests for deletion of <span class="eContent2">Personal Data</span> shall be subject to the obligations of <?= $this->contentItem->get_editorFullName(); ?> in law, in particular in respect of conservation or archiving of documents. Finally, <span class="eContent2">Users</span> of the <span class="eContent2">Website</span> <?= $this->contentItem->get_websiteURL(); ?> can make a complaint to the supervisory authorities, and in particular to <a href="https://www.cnil.fr/fr/plaintes" class="eLink1" target="_blank" rel="noopener noreferer">french national commission for information technology and civil liberties (CNIL)</a>.
</p>

<h3 class="eTitle3">
    7.4 Non-communication of personal data
</h3>

<p class="eContent1">
    <?= ucfirst($this->contentItem->get_editorFullName()); ?> undertakes not to process, host or transfer collected data on its <span class="eContent2">Clients</span> to a country located outside the European Union or recognised as "not adequate" by the European Commission, without informing the client thereof before doing so. However, <?= $this->contentItem->get_editorFullName(); ?> remains free to choose its technical and commercial subcontractors, providing they have sufficient guarantees pursuant to the requirements of the General Data Protection Regulation (GDPR: n&deg; 2016-679).
</p>

<p class="eContent1">
    <?= ucfirst($this->contentItem->get_editorFullName()); ?> undertakes to take all necessary precautions to safeguard the security of the <span class="eContent2">Personal Data</span>, and in particular to ensure that it is not communicated to unauthorised persons or entities. However, if an incident impacting the integrity or confidentiality of the <span class="eContent2">Client</span>'s <span class="eContent2">Personal Data</span> is brought to the attention of <?= $this->contentItem->get_editorFullName(); ?>, the latter must, as rapidly as possible, inform the <span class="eContent2">Client</span> thereof, and also inform it of the corrective measures which have been taken. Furthermore, <?= $this->contentItem->get_editorFullName(); ?> does not collect any &laquo; sensitive data&raquo;.
</p>

<?php if (!$this->contentItem->is_individual()) : ?>
<p class="eContent1">
    The <span class="eContent2">User</span>'s <span class="eContent2">Personal Data</span> can be processed by subsidiaries of <?= $this->contentItem->get_editorFullName(); ?> and subcontractors (service-providers), exclusively to achieve the purposes of the present policy.
</p>

<p class="eContent1">
    Persons or entities which may have access to the <span class="eContent2">Personal Data</span> of the <span class="eContent2">Users</span> of <?= $this->contentItem->get_websiteURL(); ?> are designated and are under the sole liability of the manager of <?= $this->contentItem->get_editorFullName(); ?>. Their respective attributions can also be limited in accordance with the requirements and purposes mentioned above.
</p>
<?php endif; ?>

<p class="eContent1">
    &nbsp;
</p>
