<?php
/**
 * @brief DemoPayment input, main layout.
 * @details Plugin / Input Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Mar 2024
 * @date Modification: Mar 2024
 * @copyright 2024 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->siteForm->display_header(); ?>
<?= $this->siteForm->display_hiddens(); ?>

<div class="paymentDemo">
    <span id="CreditCard" class="creditcard">
        &nbsp;
    </span>
    &nbsp;
    &nbsp;
    <span id="DateMonth" class="datemonth">
        &nbsp;
    </span>
    &nbsp; / &nbsp;
    <span id="DateYear" class="datemonth">
        &nbsp;
    </span>
    <div>
        &nbsp;
    </div>
    <div class="formButtons">
        <?= $camyks->theme->get_button(array('title'=>$this->get_translation('submitpayment'), 'url'=>$this->siteForm->get_HTMLSubmitLink())); ?>
    </div>
</div>

<?= $this->siteForm->display_footer(); ?>
