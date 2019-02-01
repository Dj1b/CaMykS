<?php
/**
 * @brief PayZenPayment Input main layout
 * @details Plugin / Input layout
 * @file plugin/input/PayZenPayment/html/input.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Dec 2018
 * @date Modification: Dec 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
?>

<?= $this->paymentForm->display_header(); ?>
<?= $this->paymentForm->display_hiddens(); ?>
<?= $this->paymentForm->display_footer(); ?>

<p class="eContent1">
    <?= $this->get_translation('redirectobankmessage'); ?>
</p>

<p class="eContent1">
    <?= $this->get_translation('redirectobankmessage2', array($this->paymentForm->get_HTMLSubmitLink(), 'eLink1')); ?>
</p>
