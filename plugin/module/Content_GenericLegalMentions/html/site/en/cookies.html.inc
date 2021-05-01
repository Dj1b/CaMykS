<?php
/**
 * @brief Content_GenericLegalMentions Module site cookies, english sub layout.
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
<div id="LM-Cookies" class="anchor" title="9. Cookies."></div>

<h2 class="eTitle2">
    9. Cookies
</h2>

<p class="eContent1">
    A &laquo; cookie &raquo; is a small data file sent over the <span class="eContent2">User</span>'s browser, and saved in the <span class="eContent2">User</span>'s terminal (e.g.: computer, smartphone). This file includes data such as the <span class="eContent2">User</span>'s domain name, the <span class="eContent2">User</span>'s Internet service provider, the <span class="eContent2">User</span>'s operating system, and the date and time of access. Cookies pose no risk of damage to the <span class="eContent2">User</span>'s terminal.
</p>

<p class="eContent1">
    <?= ucfirst($this->contentItem->get_editorFullName()); ?> may process data of the <span class="eContent2">User</span> concerning its visit of the Site, such as the pages viewed, and searches made. This information enables <?= $this->contentItem->get_editorFullName(); ?> to improve the content of the <span class="eContent2">Website</span>, and the <span class="eContent2">User</span>'s browsing experience.
</p>

<p class="eContent1">
    Since cookies facilitate browsing and/or the supply of the services offered by the Site, the <span class="eContent2">User</span> can configure its browser to enable it to decide whether or not it wishes to accept them, such that cookies are saved in the terminal or, conversely, such that they are rejected, either unconditionally, or depending on their issuer. The <span class="eContent2">User</span> can also configure its browser application so that it is asked whether it wishes to accept or refuse cookies each time, before a cookie can be saved, for the duration of the <span class="eContent2">User</span>'s visit, in its terminal. <?= ucfirst($this->contentItem->get_editorFullName()); ?> informs the <span class="eContent2">User</span> that, in this case, it is possible that not all functions offered by the <span class="eContent2">Website</span> will be available.
</p>

<p class="eContent1">
    If the <span class="eContent2">User</span> refuses to allow cookies to be recorded in its terminal or its browser, or if the <span class="eContent2">User</span> deletes cookies which are saved in them, the <span class="eContent2">User</span> is informed that its browsing and its experience on the <span class="eContent2">Website</span> may be limited. This would also be so when <?= $this->contentItem->get_editorFullName(); ?> or one of its service-providers is unable to recognise, for technical compatibility purposes, the type of browser used by the terminal, its language and display settings, or the country from which your terminal appears to be connected to the Internet.
</p>

<p class="eContent1">
    If applicable, <?= $this->contentItem->get_editorFullName(); ?> declines all liability for consequences relating to degraded operation of the <span class="eContent2">Website</span> and of any services which may be offered by <?= $this->contentItem->get_editorFullName(); ?> resulting (i) from a refusal of cookies by the <span class="eContent2">User</span> (ii) from <?= $this->contentItem->get_editorFullName(); ?>'s inability to save or view the cookies required for their operation due to the choices made by the <span class="eContent2">User</span>. In respect of management of cookies and the <span class="eContent2">User</span>'s choices, the configuration of each browser is different. It is described in your browser's help menu, which will let you know how <span class="eContent2">Users</span> can modify their preferences concerning cookies.
</p>

<p class="eContent1">
    The <span class="eContent2">User</span> may choose to express and to modify its preferences in terms of cookies at any time. <?= ucfirst($this->contentItem->get_editorFullName()); ?> may also make use of outside service-providers to enable it to collect and process the data described in this section.
</p>

<p class="eContent1">
    These cookies are deposited in your terminals only if you consent thereto, continuing your browsing on the <span class="eContent2">Website</span> or the mobile application of <?= $this->contentItem->get_editorFullName(); ?>. The <span class="eContent2">User</span> may nevertheless at any time change its mind regarding its consent for the <span class="eContent2">Website</span> to deposit this type of cookie.
</p>

<?php if ($this->cookieAgreementInput !== false) : ?>
<p class="eContent1">
This is a list of the services present on the <span class="eContent2">Website</span>  which make use of cookies:
</p>
<ul>
    <?php foreach($this->cookieAgreementInput->get_servicesList() as $service) : ?>
        <li class="eContent1">
            <span class="eContent2"><?= $service['title']; ?></span>
            <br /><?= $service['purpose']; ?>
            <?php if ($service['usage'] !== '') : ?>
                <br />Usage: <?= $service['usage']; ?>
            <?php endif; ?>
            <?php if ($service['duration'] !== '') : ?>
                <br />Time to live: <?= $service['duration']; ?>
            <?php endif; ?>
            <?php if ($service['aboutURL'] != '') : ?>
                <br /><a href="<?= $service['aboutURL']; ?>" class="link" target="_blank" rel="noopener,noreferer,nofollow">Learn more</a>
            <?php endif; ?>
        </li>
    <?php endforeach; ?>
</ul>

<p class="eContent1" style="text-align:center;">
    <?= $this->theme->get_button(array(
        'title' => 'Open cookie management panel',
        'url'   => $this->cookieAgreementInput->get_cookieManagementPanelOpenLink(),
    )); ?>
</p>

<?php endif; ?>

<p class="eContent1">
    &nbsp;
</p>

