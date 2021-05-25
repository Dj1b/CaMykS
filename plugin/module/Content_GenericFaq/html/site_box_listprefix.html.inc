<?php
/**
 * @brief Content_GenericFaq module, site faq list index layout
 * @details Plugin / Module Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Apr 2007
 * @date Modification: May 2021
 * @copyright 2007 - 2021 Ideogram Design
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(); ?>
<?= $this->theme->get_boxTitleBar($this->get_translation('site_title')); ?>
<?= $this->theme->get_boxContent2Header('padding:8px;'); ?>
<table cellspacing="0" cellpadding="0" border="0" width="100%">
    <?php foreach ($this->faqitems as $n) : ?>
        <tr>
            <td class="eTitle3" style="text-align:left;">
                <?= $this->get_translation('question', ''); ?><?= $n->vars['title']?>
            </td>
        </tr>
        <tr>
            <td class="eContent1" style="padding-left:16px;">
                <?= nl2br($n->vars['content']); ?>
             </td>
        </tr>
        <tr>
            <td>
                &nbsp;
            </td>
        </tr>
    <?php endforeach; ?>
</table>
<?= $this->theme->get_boxContent2Footer(); ?>
<?php if ($this->prevfaqs != '' or $this->nextfaqs != '') :?>
<?= $this->theme->get_boxButtonsBar($this->buttons, false); ?>
<?php endif; ?>
<?= $this->theme->get_boxFooter(); ?>
