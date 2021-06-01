<?php
/**
 * @brief Content_GenericPageList module, admin layout.
 * @details Plugin / Module Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Nov 2007
 * @date Modification: May 2021
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
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title.' : '.$this->plitem->vars['name'].' [ ' .$this->plitem->id.' ] '); ?>
<?= $this->theme->get_boxTabsBar($this->tabs, $this->tabObject.'.mouseclick', $this->tabObject.'.mouseover', $this->tabObject.'.mouseout', 'properties'); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<div id="itemproperties" style="display:block;" class="adminContentPanel">
    <?= $this->form->display_header(); ?>
    <?= $this->form->display_hiddens(); ?>
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableLine0 eContent2" style="width:150px">
                <?= $camyks->get_translation('formitem_name'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <input type="text" name="name" value="<?= $this->plitem->vars['name']; ?>" maxlength="32" class="inputs" />
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $camyks->get_translation('formitem_layout'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->form->display_selectInput(array('name'=>'layout', 'values'=>$this->plitem->get_layoutList(), 'default'=>$this->plitem->vars['layout'])); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_root'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <input type="text" name="root" value="<?= $this->plitem->vars['root']; ?>" maxlength="5" class="inputs" />
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_order'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->form->display_selectInput(array('name'=>'listorder', 'values'=>$this->plitem->get_listOrderList(), 'default'=>$this->plitem->vars['listorder'])); ?>
            </td>
        </tr>

        <?php $alt = 0; ?>
        <?php foreach($camyks->get_confValue('editing_languages') as $l) : ?>
            <tr>
                <td class="eTableLine<?= $alt; ?> eContent2">
                    <?= $camyks->get_translation('formitem_title'); ?>
                    <img src="<?=language_getIcon($l, false); ?>" alt="<?= $l; ?>" style="float:right;" ?>
                </td>
                <td class="eTableLine<?= $alt; ?> eContent1">
                    <input type="text" name="title_<?= $l; ?>" value="<?= $this->plitem->vars['title_'.$l]; ?>" maxlength="64" class="inputs" />
                </td>
            </tr>
            <?php $alt = abs($alt-1); ?>
        <?php endforeach; ?>
    </table>
    <?= $this->form->display_footer(); ?>
</div>

<?php if ($this->help != null) : ?>
    <div id="itemhelp" class="adminContentPanel" style="display:none;">
        <?php $this->display_help() ?>
    </div>
<?php endif; ?>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
