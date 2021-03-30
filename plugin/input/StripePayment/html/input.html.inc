<?php
/**
 * @brief StripePayment Input main layout
 * @details Plugin / Input layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: May 2020
 * @date Modification: Mar 2021
 * @copyright 2020 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
?>
    <script src="<?= $this->get_fileURL('js/stripe.js'); ?>" defer></script>

    <div class="sr-root">
      <div class="sr-main">
        <form id="payment-form" class="sr-payment-form">
          <div class="sr-combo-inputs-row">
            <div class="sr-input sr-card-element" id="card-element"></div>
          </div>
          <div class="sr-field-error" id="card-errors" role="alert"></div>
          <button id="submit">
            <div class="spinner hidden" id="spinner"></div>
            <span id="button-text"><?= $this->get_translation('action_pay'); ?></span><span id="order-amount"></span>
          </button>
        </form>
        <div class="sr-result hidden">
          <p><?= $this->get_translation('message_payment_completed'); ?><br /></p>
          <pre>
            <code></code>
          </pre>
        </div>
      </div>
    </div>

    <?php if ($this->config->get_value('runningMode') === 'test' and $this->config->get_value('test_displayTestCard') == 1) : ?>
    <div style="text-align:center;">
        <div class="eTitle3">
            <?= $this->get_translation('testmode_title'); ?>
        </div>
        <div class="eContent2">
            <?= $this->get_translation('testmode_desc'); ?>
        </div>
        <div class="eContent1">
            &nbsp;
        </div>
        <div class="eContent1">
            <?= $this->get_translation('testmode_fakecardnumbers'); ?>
        </div>
        <div class="eContent1">
            <?= $this->get_translation('testmode_fakecarddate'); ?>
        </div>
        <div class="eContent1">
            <?= $this->get_translation('testmode_fakecardccv'); ?>
        </div>
    </div>
    <?php endif; ?>
