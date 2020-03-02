<?php
/**
 * @brief CookieAgreementMessage Input layout
 * @details Plugin / Input layout
 * @file plugin/input/CookieAgreementMessage/html/input.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: May 2017
 * @date Modification: Apr 2018
 * @copyright 2017 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;
?>
<div id="cookieAgreementMessage" class="cookieAgreementMessage <?= $this->params['location']; ?>">
    <div class="message">
        <?= $this->params['message']; ?>
    </div>

    <div class="buttons">
        <?php if ($this->params['styleSource'] == 'plugin') : ?>
            <a href="javascript:CookieAgreementMessage.accept_cookies();void(0);" class="acceptButton">
                <?= $this->get_translation('accept'); ?>
            </a>
            <?php if ($this->params['aboutCookie'] != '') : ?>
                <a href="<?= $this->params['aboutCookie']; ?>" class="aboutButton" target="_blank" rel="noopener">
                    <?= $this->get_translation('about'); ?>
                </a>
            <?php endif; ?>
        <?php else : ?>
            <?= $camyks->theme->get_button(array(
                    'title'     => $this->get_translation('accept'),
                    'link'      => 'javascript:CookieAgreementMessage.accept_cookies();void(0);',
                )); ?>
            <?php if ($this->params['aboutCookie'] != '') : ?>
                <?= $camyks->theme->get_button(array(
                    'title'     => $this->get_translation('about'),
                    'link'      => $this->params['aboutCookie'],
                    'target'    => '_blank',
                 )); ?>
            <?php endif; ?>
        <?php endif; ?>
    </div>
</div>
<?php
/**
 * @endcond Exclude
 */
?>
