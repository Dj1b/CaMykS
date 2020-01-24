<?php
/**
 * @brief PayBoxPayment Input main layout
 * @details Plugin / Input layout
 * @file plugin/input/PayBoxPayment/html/input.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jan 2020
 * @date Modification: Jan 2020
 * @copyright 2020 CaMykS Team
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
