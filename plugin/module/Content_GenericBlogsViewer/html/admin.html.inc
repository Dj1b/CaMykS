<?php
/**
 * @brief Content_GenericBlogsViewer module, admin layout.
 * @details Plugin / Module Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Apr 2008
 * @date Modification: Jul 2021
 * @copyright 2008 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader('width:600px;margin:0 auto;'); ?>
<?= $this->theme->get_boxTitleBar($this->title.' : '.$this->configItem->vars['name'].' ['.$this->configItem->id . ']'); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<?= $this->form->display_header(); ?>
<?= $this->form->display_hiddens(); ?>
<div class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableLine0 eContent2" style="width:200px;">
                <?= $camyks->get_translation('formitem_name'); ?>
            </td>
            <td class="eTableLine0">
                <?= $this->form->display_textInput('name'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('title_globalsettings'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $camyks->get_translation('formitem_title'); ?>
            </td>
            <td class="eTableLine0">
                <?= $this->form->display_textInput('title'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('itemauthors'); ?>
            </td>
            <td class="eTableLine1">
                <input type="checkbox" name="authors_all" id="authors_all" value="" <?= $this->configItem->vars['authors'] == '' ? ' checked="checked"' : ''; ?>    onchange="genericblogsviewer_checkAllAuthors()" />
                <label for="authors_all">
                    <?= $this->get_translation('authors_all'); ?>
                </label>
            </td>
        </tr>
        <?php $cnt = 0; ?>
        <?php foreach ($this->authorList as $author) : ?>
            <tr>
                <td class="eTableLine0 eContent1">
                    &nbsp;
                </td>
                <td class="eTableLine1 eContent1">
                    <input type="checkbox" name="author<?= $cnt?>" id="author<?= $cnt?>" value="<?= $author['login']; ?>" <?=($this->configItem->vars['authors'] == '' ? ' checked="checked" disabled="disabled"' : (in_array($author['login'],$this->configItem->vars['authors_']) ? ' checked="checked"' : '')); ?> />
                    <label for="author<?= $cnt; ?>">
                        <?php if ($author['firstname']!='' and $author['lastname']) : ?>
                            <?= $author['firstname'].' '.$author['lastname']; ?>
                        <?php elseif ($author['firstname']!='') : ?>
                            <?= $author['firstname']; ?>
                        <?php elseif ($author['lastname']!='') : ?>
                            <?= $author['lastname']; ?>
                        <?php else : ?>
                            <?= $author['login']; ?>
                        <?php endif; ?>
                    </label>
                </td>
            </tr>
            <?php $cnt++; ?>
        <?php endforeach; ?>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('itemactiverss'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?php if ($this->rssAvailable) : ?>
                    <?= $this->form->display_booleanSelectInput('enablerss'); ?>
                <?php else : ?>
                    <input type="hidden" name="enablerss" value="<?= $this->configItem->vars['enablerss']; ?>" />
                    <?= $this->form->display_booleanSelectInput(array('name'=>'_enablerss', 'default'=>0, 'disabled'=>1)); ?>
                <?php endif; ?>
            </td>
        </tr>

        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('title_listsettings'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('itemlistcount'); ?>
            </td>
            <td class="eTableLine0">
                <?= $this->form->display_textInput(array('name'=>'list_count', 'maxlength'=>2)); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('itemlistlayout'); ?>
            </td>
            <td class="eTableLine1">
                <?= $this->form->display_selectInput(array('name'=>'list_layout', 'values'=>$this->get_listLayouts())); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('itemlistpanel'); ?>
            </td>
            <td class="eTableLine0">
                <?= $this->form->display_booleanSelectInput('list_panel'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('title_itemsettings'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('itemitemlayout'); ?>
            </td>
            <td class="eTableLine0">
                <?= $this->form->display_selectInput(array('name'=>'item_layout', 'values'=>$this->get_itemLayouts())); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('itemitempanel'); ?>
            </td>
            <td class="eTableLine1">
                <?= $this->form->display_booleanSelectInput('item_panel'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('title_panelsettings'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('itempanelinsert'); ?>
            </td>
            <td class="eTableLine0">
                <?= $this->form->display_textareaInput('panel_insert'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('title_commentsettings'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('itemcommentmessage'); ?>
            </td>
            <td class="eTableLine0">
                <?= $this->form->display_textareaInput('comment_message'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('formtitle_socialnetworksharingpanel'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $camyks->get_translation('formitem_status'); ?>
            </td>
            <td class="eTableLine0">
                <?php if ($this->snspAvailable) : ?>
                    <?= $this->form->display_selectInput(array('name'=>'snsp_status', 'values'=>$this->get_genericStatusList())); ?>
                <?php else : ?>
                     <?= $this->get_translation('status_disabled'); ?>
                <?php endif; ?>
            </td>
        </tr>

        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('formtitle_genericpagecontroller'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $camyks->get_translation('formitem_status'); ?>
            </td>
            <td class="eTableLine0">
                <?php if ($this->gpcAvailable) : ?>
                    <?= $this->form->display_selectInput(array('name'=>'gpc_status','values'=>$this->get_genericStatusList())); ?>
                <?php else : ?>
                     <?= $this->get_translation('status_disabled'); ?>
                <?php endif; ?>
            </td>
        </tr>

        <?php if ($this->gpcAvailable) : ?>
            <tr>
                <td class="eTableLine1 eContent2">
                    <?= $this->get_translation('formitem_gpcsource'); ?>
                </td>
                <td class="eTableLine1">
                    <?= $this->form->display_selectInput(array('name'=>'gpc_source', 'values'=> $this->get_gpcSourceList())); ?>
                </td>
            </tr>
        <?php endif; ?>
    </table>
</div>
<?= $this->form->display_footer(); ?>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
