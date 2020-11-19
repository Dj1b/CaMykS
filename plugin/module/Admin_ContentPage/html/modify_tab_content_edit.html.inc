<?php
/**
 * @brief Admin_ContentPage Module edit content sub layout for page edition
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.1
 * @date Creation: Dec 2006
 * @date Modification: Nov 2020
 * @copyright 2006 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;

/* get images URL */
$edit = $this->theme->get_pictURL('edit', 12, 'std');
$edit_ = $this->theme->get_pictURL('edit', 12, 'ovr');
$edit_content = $this->get_fileURL('img/edit_content.gif');
?>
<div id="itemcontent" style="display:<?= $this->tabBuilder->get_tabDisplay('content'); ?>;" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <?php if (count($this->models) > 0) : ?>
            <tr>
                <td colspan="2">
                    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
                        <tr>
                            <td class="eTableLine1 eContent2" style="width:100px;">
                                <?= $this->get_translation('formitem_model'); ?>
                            </td>
                            <td class="eTableLine1 eContent1">
                                <?= $this->form->display_selectInput(array('name'=>'model', 'values'=>$this->modelTitleList, 'default'=>'', 'onchange'=>'acpe.onModelChange();')); ?>
                            </td>
                        </tr>
                    </table>
                </td>
            </tr>
        <?php endif; ?>
        <tr>
            <td class="contentpagecontentcol">
                <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
                    <tr>
                        <td class="eTableLine0 eContent2" style="width:100px;">
                            <?= $this->get_translation('formitem_theme'); ?>
                        </td>
                        <td class="eTableLine0 eContent1">
                            <?= $this->form->display_selectInput(array('name'=>'theme', 'values'=>$this->themeTitleList, 'default'=>$this->page->theme, 'onchange'=>'acpe.onThemeChange();')); ?>
                        </td>
                    </tr>
                    <tr>
                        <td class="eTableLine0 eContent2">
                            <?= $this->get_translation('formitem_template'); ?>
                        </td>
                        <td class="eTableLine0 eContent1">
                         <?= $this->form->display_selectInput(array('name'=>'template', 'values'=>$this->templateTitleList, 'default'=>$this->page->template, 'onchange'=>'acpe.onTemplateChange();')); ?>
                        </td>
                    </tr>
                    <tr>
                        <td class="eTableLine0 eContent1">
                            &nbsp;
                        </td>
                        <td class="eTableLine0">
                            <?php foreach ($camyks->templates as $t) : ?>
                                <div id="template_<?= $t->name?>" style="display:none;width:202px;height:122px;overflow:hidden;">
                                    <?= $t->display_thumb(); ?>
                                </div>
                            <?php endforeach; ?>
                        </td>
                    </tr>
                </table>
            </td>
            <td class="contentpagecontentcol">
                <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
                    <tr>
                        <td class="eTableLine0 eContent2 inputHeight">
                            <?= $this->get_translation('formitem_modules'); ?>
                        </td>
                    </tr>
                    <tr>
                        <td class="eTableLine0">
                            <div style="width:100%;height:400px;overflow:auto;">
                                <?php $alt=1; ?>
                                <?php for ($i=0; $i< $this->page->maxmodules; $i++) : ?>
                                    <?php if (isset($this->page->modules[$i])) : ?>>
                                        <?php $m = &$this->page->modules[$i]; ?>
                                    <?php else : ?>
                                        <?php $m = array('name'=>''); ?>
                                    <?php endif; ?>
                                    <div id="module<?= $i?>" style="display:block;padding-bottom:4px;;">
                                        <table cellspacing="0" cellpadding="0" border="0" width="100%">
                                            <tr>
                                                <td class="eTableHeader" colspan="2">
                                                    <div id="module_editbutton<?= $i?>" style="display:block; float:right;">
                                                        <a href="javascript:acpe.edit_moduleContent(<?= $i?>);">
                                                            <?= $camyks->get_translation('edit'); ?><img src="<?= $edit?>" class="img"
                                                                style="margin-left:8px; vertical-align:baseline;"
                                                                alt="<?= $this->get_translation('edit_module'); ?>"
                                                                title="<?= $this->get_translation('edit_module'); ?>"
                                                                onmouseover="this.src='<?= $edit_?>';"
                                                                onmouseout="this.src='<?= $edit?>';" /></a>
                                                    </div>
                                                    <?= $this->get_translation('blockx', ($i+1)); ?>
                                                </td>
                                            </tr>
                                            <tr>
                                                <td class="eTableLine<?= $alt; ?> eContent2">
                                                    <?= $this->get_translation('formitem_module'); ?>
                                                </td>
                                                <td class="eTableLine<?= $alt; ?>" style="width:200px;">
                                                    <?= $this->form->display_selectInput(array('name'=>'m'.$i.'_name', 'values'=>$this->moduleTitleList, 'default'=>$m['name'], 'onchange'=>'acpe.onBlockModuleChange('.$i.');')); ?>
                                                </td>
                                            </tr>
                                            <tr>
                                                <td class="eTableLine<?= $alt; ?> eContent2">
                                                    <img src="<?= $edit_content?>" alt="" border="0" style="float:left; margin:0 4px 0 0;" />
                                                    <?= $this->get_translation('formitem_content'); ?>
                                                </td>
                                                <td class="eTableLine<?= $alt; ?>">
                                                    <?= $this->form->display_selectInput(array('name'=>'m'.$i.'_content', 'values'=>array(''=>''), 'default'=>'', 'onchange'=>'acpe.onBlockContentChange('.$i.');')); ?>
                                                </td>
                                            </tr>
                                            <?php if ($this->allow_theme_change) : ?>
                                                <tr>
                                                    <td class="eTableLine<?= $alt; ?> eContent2">
                                                        <?= $this->get_translation('formitem_theme'); ?>
                                                    </td>
                                                    <td class="eTableLine<?= $alt; ?> eContent1">
                                                        <?= $this->form->display_selectInput(array('name'=>'m'.$i.'_theme', 'values'=>$this->mthemeTitleList, 'default'=>$this->page->theme, 'onchange'=>'acpe.onBlockThemeChange('.$i.');')); ?>
                                                    </td>
                                                </tr>
                                            <?php endif; ?>
                                        </table>
                                    </div>
                                    <?php $alt = abs($alt-1); ?>
                                <?php endfor; ?>
                            </div>
                        </td>
                    </tr>
                </table>
            </td>
        </tr>
    </table>
</div>
<?php
/**
 * @endcond Exclude
 */
?>
