<?php
/**
 * @brief Admin_Statistics Module admin options tab sublayout
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Sep 2020
 * @date Modification: Sep 2020
 * @copyright 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;
?>
<div id="itemOptions" style="display:<?= $this->tabBuilder->get_tabDisplay('Options'); ?>;" class="adminContentPanel">
    <?= $this->form->display_header(); ?>
    <?= $this->form->display_hiddens(); ?>

    <div class="eTitle3">
        <?= $this->statobject->vars['title']; ?> - <?= $camyks->get_translation('module').$camyks->get_translation('formitem_separator').$this->statobject->vars['plugintitle']; ?>
    </div>

    <div>
        &nbsp;
    </div>

    <div class="options">
        <?php if ($this->config->optionSettingsDisplay > 0 ) : ?>
        <div class="optionsSettings">
            <?php $this->load_file('html/options/settings.html.inc'); ?>
        </div>
        <?php endif; ?>
        <div class="optionsColors">
            <?php $this->load_file('html/options/colors.html.inc'); ?>
        </div>
    </div>

    <div>
        &nbsp;
    </div>

    <div class="buttons">
        <?php foreach ($this->optionsButtons as $button) : ?>
            <?= $this->theme->get_button($button); ?>
        <?php endforeach; ?>
    </div>

    <?= $this->form->display_footer(); ?>
</div>

<?php
/**
 * @endcond Exclude
 */
?>
