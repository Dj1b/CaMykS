<?php
/**
 * @brief Content_GenericGallery module, admin main layout
 * @details Plugin / Module Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jul 2007
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
<?= $this->theme->get_boxTitleBar($this->title.' : '.$this->imagelist->vars['name'].' [ ' .$this->imagelist->id . ' ] '); ?>
<?= $this->theme->get_boxTabsBar($this->tabs, $this->tabObject.'.mouseclick', $this->tabObject.'.mouseover', $this->tabObject.'.mouseout', 'general'); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<?= $this->form->display_header(); ?>
<?= $this->form->display_hiddens(); ?>
<div id="itemgeneral" style="display:block;" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableLine0 eContent2" style="width:200px">
                <?= $this->get_translation('itemname'); ?>
            </td>
            <td class="eTableLine0">
                <input type="text" name="name" value="<?= $this->imagelist->vars['name']; ?>" maxlength="32" class="inputs" />
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('layout'); ?>
            </td>
            <td class="eTableLine1">
                <?= $this->form->display_selectInput(array('name'=>'layout', 'values'=>$this->layouts, 'default'=>$this->imagelist->vars['layout'])); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('theme'); ?>
            </td>
            <td class="eTableLine0">
                <?= $this->form->display_selectInput(array('name'=>'theme', 'values'=>$this->themes, 'default'=>$this->imagelist->vars['theme'])); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('thumb_width'); ?>
            </td>
            <td class="eTableLine1">
                <input type="text" name="thumbWidth" value="<?= $this->imagelist->vars['thumbWidth']; ?>" maxlength="3" class="inputs" />
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('thumb_height'); ?>
            </td>
            <td class="eTableLine0">
                <input type="text" name="thumbHeight" value="<?= $this->imagelist->vars['thumbHeight']; ?>" maxlength="3" class="inputs" />
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('thumb_count'); ?>
            </td>
            <td class="eTableLine1">
                <input type="text" name="thumbCount" value="<?= $this->imagelist->vars['thumbCount']; ?>" maxlength="2" class="inputs" />
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('image_width'); ?>
            </td>
            <td class="eTableLine0">
                <input type="text" name="imageWidth" value="<?= $this->imagelist->vars['imageWidth']; ?>" maxlength="4" class="inputs" />
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('image_height'); ?>
            </td>
            <td class="eTableLine1">
                <input type="text" name="imageHeight" value="<?= $this->imagelist->vars['imageHeight']; ?>" maxlength="4" class="inputs" />
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('image_title'); ?>
            </td>
            <td class="eTableLine0">
                <input type="checkbox" name="imageTitle" value="1"<?= $this->imagelist->vars['imageTitle']==1?'checked="checked"':''?> />
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('image_desc'); ?>
            </td>
            <td class="eTableLine1">
                <input type="checkbox" name="imageDesc" value="1"<?= $this->imagelist->vars['imageDesc']==1?'checked="checked"':''; ?> />
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('sliding_method'); ?>
            </td>
            <td class="eTableLine0">
                <?= $this->form->display_selectInput(array('name'=>'slidingMethod', 'values'=>$this->slidingMethods, 'default'=>$this->imagelist->vars['slidingMethod'])); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('sliding_accel'); ?>
            </td>
            <td class="eTableLine1">
                <input type="text" name="slidingAccel" value="<?= $this->imagelist->vars['slidingAccel']; ?>" maxlength="1" class="inputs" />
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('sliding_speed'); ?>
            </td>
            <td class="eTableLine0">
                <input type="text" name="slidingSpeed" value="<?= $this->imagelist->vars['slidingSpeed']; ?>" maxlength="3" class="inputs" />
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('sliding_interval'); ?>
            </td>
            <td class="eTableLine1">
                <input type="text" name="slidingInterval" value="<?= $this->imagelist->vars['slidingInterval']; ?>" maxlength="4" class="inputs" />
            </td>
        </tr>
    </table>
</div>

<div id="itemimages" style="display:none;" class="adminContentPanel">
    <table cellspacing="0" style="width:100%">
        <tr>
            <td class="eTableLine0">
                <a href="<?= $this->editlink?>0">
                    <?= $this->get_translation('addnewimage'); ?>
                </a>
            </td>
            <td class="eTableLine0" style="width:16px">
                <a href="<?= $this->editlink?>0">
                    <img src="<?= $add; ?>" alt="<?= $this->get_translation('addnewimage'); ?>" title="<?= $this->get_translation('addnewimage'); ?>"
                        onmouseover="this.src='<?= $add_; ?>'" onmouseout="this.src='<?= $add; ?>'" />
                </a>
            </td>
            <td class="eTableLine0" style="width:16px">
                &nbsp;
            </td>
        </tr>

        <?php $alt=1; ?>
        <?php foreach ($this->imagelist->items as $img) : ?>
            <tr>
                 <td class="eTableLine<?= $alt; ?>">
                     <?= $img->vars['name']; ?>
                 </td>
                 <td class="eTableLine<?= $alt; ?>">
                    <a href="<?= $this->editlink.$img->id; ?>">
                        <img src="<?= $edit; ?>" alt="<?= $this->get_translation('editimage'); ?>" title="<?= $this->get_translation('editimage'); ?>"
                        onmouseover="this.src='<?= $edit_; ?>'" onmouseout="this.src='<?= $edit; ?>'" />
                    </a>
                 </td>
                 <td class="eTableLine<?= $alt; ?>">
                     <a href="<?= vsprintf($this->dellink,$img->id); ?>">
                        <img src="<?= $del; ?>" alt="<?= $this->get_translation('deleteimage'); ?>" title="<?= $this->get_translation('deleteimage'); ?>"
                            onmouseover="this.src='<?= $del_; ?>'" onmouseout="this.src='<?= $del; ?>'" />
                    </a>
                 </td>
            </tr>

            <?php $alt = abs($alt-1) ?>
        <?php endforeach; ?>
    </table>
</div>

<?php if ($this->help != null) : ?>
    <div id="itemhelp" style="display:none;" class="adminContentPanel">
        <?php $this->display_help() ?>
    </div>
<?php endif; ?>

<?= $this->form->display_footer(); ?>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
