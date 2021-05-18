<?php
/**
 * @brief Content_GenericNews Module admin edit item layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Mar 2007
 * @date Modification: May 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule'); ?>
<?= $this->theme->get_boxTitleBar($this->title.' : '.$this->get_translation('editanews')); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<?= $this->form->display_header(); ?>
<?= $this->form->display_hiddens(); ?>
<div id="itemproperties" style="display:block;" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" width="100%">
        <tr>
            <td class="eTableLine0">
                <?= $this->get_translation('newstitle'); ?> :
            </td>
            <td class="eTableLine0">
                <input type="text" name="title" value="<?= $this->newsitem->vars['title']; ?>" maxlength="64" class="inputs" />
            </td>
        </tr>
        <tr>
            <td class="eTableLine1">
                <?= $this->get_translation('status'); ?> :
            </td>
            <td class="eTableLine1">
                <select name="status" class="inputs">
                    <?php foreach ($this->status as $i => $v) : ?>
                        <option value="<?= $i; ?>"<?= ($i==$this->newsitem->vars['status']? 'selected="selected"':''); ?>>
                            <?= $this->get_translation($v); ?>
                        </option>
                    <?php endforeach; ?>
                </select>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0">
                <?= $this->get_translation('language'); ?> :
            </td>
            <td class="eTableLine0">
                <select name="language">
                    <?php foreach ($camyks->site_conf['editing_languages'] as $l) : ?>
                        <option value="<?= $l; ?>"<?= ($l==$this->newsitem->vars['language']? 'selected="selected"':''); ?>>
                            <?= $l; ?>
                        </option>
                    <?php endforeach; ?>
                </select>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1">
                <?= $this->get_translation('date'); ?> :
            </td>
            <td class="eTableLine1">
                <?= $this->form->display_dateInput($this->newsitem->vars['ndate'], 'ndate'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0">
                <?= $this->get_translation('content'); ?> :
            </td>
            <td class="eTableLine0">
                <textarea name="content" cols="40" rows="8">
                    <?= $this->newsitem->vars['content']; ?>
                </textarea>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1">
                <?= $this->get_translation('source_title'); ?> :
            </td>
            <td class="eTableLine1">
                <input type="text" name="source_title" value="<?= $this->newsitem->vars['source_title']; ?>" maxlength="254" class="inputs" />
            </td>
        </tr>

        <tr>
            <td class="eTableLine0">
                <?= $this->get_translation('source_url'); ?> :
            </td>
            <td class="eTableLine0">
                <input type="text" name="source_url" value="<?= $this->newsitem->vars['source_url']; ?>" maxlength="254" class="inputs" />
            </td>
        </tr>
    </table>
</div>
<?= $this->form->display_footer(); ?>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
