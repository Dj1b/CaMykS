<?php
/**
 * @brief CookieAgreementMessage Input layout
 * @details Plugin / Input layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.1.0.1
 * @date Creation: May 2017
 * @date Modification: Jun 2021
 * @copyright 2017 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;
?>
<div id="CookieAgreementMessage" class="cookieAgreementMessage <?= $this->params['location']; ?><?= $this->params['status'] === 'minimised' ? ' minimised' : ''; ?>">
    <div class="opener" onclick="CookieAgreementMessage.expand_panel();">
        <img src="<?= $this->get_fileURL('img/black/open.png'); ?>" alt="<?= $this->get_translation('open_panel'); ?>" title="<?= $this->get_translation('open_panel'); ?>" />
    </div>

    <div class="closer" onclick="CookieAgreementMessage.continue_withoutAccepting();">
        <img src="<?= $this->get_fileURL('img/black/close.png'); ?>" alt="<?= $this->get_translation('minimise_panel'); ?>" title="<?= $this->get_translation('minimise_panel'); ?>" />
    </div>

    <div class="message">
        <?= $this->params['message']; ?>
    </div>

    <div id="CookieAgreementMessageServices" class="services">
        <div>
            &nbsp;
        </div>
        <div class="title">
            <?= $this->get_translation('manage_cookies'); ?>
        </div>
        <div class="message">
            <?= $this->get_translation('manage_cookies_desc'); ?>
        </div>
        <?php foreach ($this->serviceInformation as $name => $service) : ?>
            <?php $cookieStatus = $this->get_serviceStatus($name); ?>
            <div class="service">
                <div class="details">

                <div class="title">
                    <?= $service['title']; ?>
                    <?php if ($service['aboutURL'] != '') : ?>
                        &nbsp;<a href="<?= $service['aboutURL']; ?>" class="link" target="_blank" rel="noopener,noreferer,nofollow"><?= $this->get_translation('about'); ?></a>
                    <?php endif; ?>
                </div>

                <div class="message">
                    <?= $service['purpose']; ?>

                    <?php if ($service['usage'] !== '') : ?>
                        <br /><?= $this->get_translation('formitem_usage'); ?>
                        <?= $service['usage']; ?>
                    <?php endif; ?>

                    <?php if ($service['duration'] !== '') : ?>
                        <br /><?= $this->get_translation('formitem_duration'); ?>
                        <?= $service['duration']; ?>
                    <?php endif; ?>
                </div>
                </div>
                <div class="actions">
                    <?php if ($service['isMandatory'] == 1) : ?>
                    <div class="mandatory">
                        <?= $this->get_translation('ismandatory'); ?>
                    </div>
                <?php else : ?>
                    <a href="javascript:CookieAgreementMessage.accept_serviceCookies('<?= $name; ?>');void(0);" class="accept<?= $cookieStatus == 1 ? ' selected':''; ?>" id="<?= $name; ?>Accept" alt="<?= $this->get_translation('accept'); ?>" title="<?= $this->get_translation('accept'); ?>">
                        &nbsp;
                    </a>
                    <a href="javascript:CookieAgreementMessage.refuse_serviceCookies('<?= $name; ?>');void(0);" class="refuse<?= $cookieStatus == 0 ? ' selected':''; ?>" id="<?= $name; ?>Refuse" alt="<?= $this->get_translation('refuse'); ?>" title="<?= $this->get_translation('refuse'); ?>">
                        &nbsp;
                    </a>
                <?php endif; ?>
                </div>
            </div>
        <?php endforeach; ?>
        <div>
            &nbsp;
        </div>
    </div>

    <div class="buttons">
        <?php if ($this->params['styleSource'] == 'plugin') : ?>
            <a href="javascript:CookieAgreementMessage.accept_cookies();void(0);" class="acceptButton">
                <?= $this->get_translation('acceptall'); ?>
            </a>
            <a href="javascript:CookieAgreementMessage.refuse_cookies();void(0);" class="acceptButton">
                <?= $this->get_translation('refuseall'); ?>
            </a>
            <a href="javascript:CookieAgreementMessage.swap_servicesSelectionDisplay();void(0);" class="aboutButton">
                <?= $this->get_translation('personalise'); ?>
            </a>
            <?php if ($this->params['aboutCookie'] != '') : ?>
                <a href="<?= $this->params['aboutCookie']; ?>" class="aboutButton" target="_blank" rel="noopener">
                    <?= $this->get_translation('about'); ?>
                </a>
            <?php endif; ?>
            <a href="javascript:CookieAgreementMessage.refresh_page();void(0);" id="CookieAgreementMessageRefreshButton" class="aboutButton hidden">
                <?= $this->get_translation('refresh_page'); ?>
            </a>
        <?php else : ?>
            <?= $camyks->theme->get_button(array(
                'title'     => $this->get_translation('acceptall'),
                'link'      => 'javascript:CookieAgreementMessage.accept_cookies();void(0);',
            )); ?>
            <?= $camyks->theme->get_button(array(
                'title'     => $this->get_translation('refuseall'),
                'link'      => 'javascript:CookieAgreementMessage.refuse_cookies();void(0);',
            )); ?>
            <?= $camyks->theme->get_button(array(
                'title'     => $this->get_translation('personnalise'),
                'link'      => 'javascript:CookieAgreementMessage.swap_servicesSelectionDisplay();void(0);',
            )); ?>
            <?php if ($this->params['aboutCookie'] != '') : ?>
                <?= $camyks->theme->get_button(array(
                    'title'     => $this->get_translation('about'),
                    'link'      => $this->params['aboutCookie'],
                    'target'    => '_blank',
                 )); ?>
            <?php endif; ?>
            <?= $camyks->theme->get_button(array(
                'title'     => $this->get_translation('refresh_page'),
                'link'      => 'javascript:CookieAgreementMessage.refresh_page();void(0);',
                'id'        => 'CookieAgreementMessageRefreshButton',
                'style'     => 'display:none;',
            )); ?>
        <?php endif; ?>
    </div>
</div>
<?php
/**
 * @endcond Exclude
 */
?>
