<?php
/**
 * @brief Content_GenericArticle module, admin layout.
 * @details Plugin / Module Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Sep 2007
 * @date Modification: Jul 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

$add = $this->theme->get_pictURL('plus', 12, 'std');
$add_ = $this->theme->get_pictURL('plus', 12, 'ovr');

$edit = $this->theme->get_pictURL('edit', 12, 'std');
$edit_ = $this->theme->get_pictURL('edit', 12, 'ovr');

$del = $this->theme->get_pictURL('cross', 12, 'std');
$del_ = $this->theme->get_pictURL('cross', 12, 'ovr');

$upd = $this->theme->get_pictURL('target', 12, 'std');
$upd_ = $this->theme->get_pictURL('target', 12, 'ovr');
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar ($this->title.' : '.$this->articleitem->vars['name'].' [ '.$this->articleitem->id.' ] '); ?>
<?= $this->theme->get_boxTabsBar($this->tabs, $this->tabObject.'.mouseclick', $this->tabObject.'.mouseover', $this->tabObject.'.mouseout', 'general'); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<?= $this->form->display_header(); ?>
<?= $this->form->display_hiddens(); ?>
<div id="itemgeneral" style="display:block;" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableLine0 eContent2" style="width:150px">
                <?= $this->get_translation('itemname'); ?>
            </td>
            <td class="eTableLine0">
                <input type="text" name="name" value="<?= $this->articleitem->vars['name']; ?>" maxlength="32" class="inputs" />
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('itemlayout'); ?>
            </td>
            <td class="eTableLine1">
                <?= $this->form->display_selectInput(array('name'=>'layout', 'values'=>$this->layouts, 'default'=>$this->articleitem->vars['layout'])); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('itemdate'); ?>
            </td>
            <td class="eTableLine0">
                <?= $this->form->display_dateInput($this->articleitem->vars['date_'], 'date_', array('day', 'month', 'year'), array('update'=>array('title'=>$camyks->get_translation('update'), 'std'=>$upd, 'ovr'=>$upd_), 'reset'=>array('title'=>$camyks->get_translation('reset'), 'std'=>$del, 'ovr'=>$del_))); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('itemauthor'); ?>
            </td>
            <td class="eTableLine1">
                <select name="author" class="inputs">
                    <?php foreach ($this->adminList as $login=>$user) : ?>
                        <option value="<?= $login; ?>"<?= $login == $this->articleitem->vars['author'] ? ' selected="selected"' : ''; ?>>
                            <?php if ($user['firstname'] == ''  and $user['lastname'] == '') : ?>
                                <?= $user['login']; ?>
                            <?php else : ?>
                                <?= $user['firstname'] . ' ' . $user['lastname']; ?>
                            <?php endif; ?>
                        </option>
                    <?php endforeach; ?>
                </select>
            </td>
        </tr>
    </table>
</div>

<?php foreach ($camyks->get_confValue('editing_languages') as $l) : ?>
<div id="item<?= $l; ?>" style="display:none;" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableLine0 eContent2" style="width:150px">
                <?= $this->get_translation('itemtitle'); ?>
            </td>
            <td class="eTableLine0">
                <input type="text" name="title_<?= $l; ?>" value="<?= $this->articleitem->vars['title_'.$l]; ?>" maxlength="128" class="inputs" />
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('itemsubtitle'); ?>
            </td>
            <td class="eTableLine1">
                <input type="text" name="subtitle_<?= $l; ?>" value="<?= $this->articleitem->vars['subtitle_'.$l]; ?>" maxlength="255" class="inputs" />
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('itemheader'); ?>
            </td>
            <td class="eTableLine0">
                <textarea name="header_<?= $l; ?>" cols="40" rows="4" class="mceNoEditor"><?= $this->articleitem->vars['header_'.$l]?></textarea>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2" colspan="2">
                <?= $this->get_translation('itemcontent'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1" colspan="2">
                <?php $this->input->set_contentInfos('file', $this->articleitem->vars['content_'.$l]); ?>
                <?php $this->input->set_textareaInfos('content_'.$l, '100%', '300px'); ?>
                <?php $this->input->display(); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('itemnote'); ?>
            </td>
            <td class="eTableLine0">
                <textarea name="note_<?= $l; ?>" cols="40" rows="4" class="mceNoEditor"><?= $this->articleitem->vars['note_'.$l]?></textarea>
            </td>
        </tr>
    </table>
</div>
<?php endforeach; ?>

<?php if ($this->help != null) : ?>
    <div id="itemhelp" style="display:none;" class="adminContentPanel">
        <?php $this->display_help(); ?>
    </div>
<?php endif; ?>

<?= $this->form->display_footer(); ?>

<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
