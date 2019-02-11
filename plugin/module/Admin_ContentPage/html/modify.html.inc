<?php
/**
 * @brief Admin_ContentPage Module page edition layout
 * @details Plugin / Module layout
 * @file plugin/module/Admin_ContentPage/html/modify.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jun 2005
 * @date Modification: Feb 2019
 * @copyright 2005 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('style'=>'width:700px;margin:0 auto;', 'class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->get_translation('type_'.$this->page->type)
                 . $camyks->get_translation('formitem_separator')
                 . $this->page->name
                 .' [ '. $this->page->id.' ] '); ?>
<?= $this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<?= $this->form->display_header(); ?>
<?= $this->form->display_hiddens(); ?>

<div id="itemgeneral" style="display:<?= $this->tabBuilder->get_tabDisplay('general'); ?>;" class="adminContentPanel">
  <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
    <?php if ($this->allow_content_edition) : ?>
    <tr>
      <td class="eTableLine0 eContent2" style="width:150px">
        <?= $camyks->get_translation('formitem_name'); ?>
      </td>
      <td class="eTableLine0 eContent1">
        <?= $this->form->display_textInput(array('name'=>'name', 'default'=>$this->page->name, 'maxlength'=>128)); ?>
      </td>
    </tr>

    <tr>
      <td class="eTableLine1 eContent2">
    <?= $this->get_translation('formitem_actived'); ?>
      </td>
      <td class="eTableLine1 eContent1">
        <?= $this->form->display_booleanSelectInput(array('name'=>'active', 'default'=>$this->page->active)); ?>
      </td>
    </tr>
    <?php if ($this->page->type == 'model') : ?>
    <tr>
      <td>
    <div style="display:none">
      <table>
        <?php endif; ?>

        <tr>
          <td class="eTableLine0 eContent2" style="width:150px;">
        <?= $this->get_translation('formitem_ishomepage'); ?>
          </td>
          <td class="eTableLine0 eContent1">
          <?= $this->form->display_booleanSelectInput(array('name'=>'homepage', 'default'=>$this->page->homepage)); ?>
          </td>
        </tr>
        <?php else: ?>

        <tr>
          <td class="eTableLine0 eContent2" style="width:150px;">
            <?= $camyks->get_translation('formitem_name'); ?>
          </td>
          <td class="eTableLine0 eContent1">
            <?= $this->page->name; ?>
          </td>
        </tr>

        <tr>
          <td class="eTableLine1 eContent2">
            <?= $this->get_translation('formitem_actived'); ?>
          </td>
          <td class="eTableLine1 eContent1">
            <?= $this->form->display_booleanSelectInput(array('name'=>'active', 'default'=>$this->page->active)); ?>
          </td>
        </tr>

        <tr>
          <td class="eTableLine0 eContent2">
          <?= $this->get_translation('formitem_ishomepage'); ?>
          </td>
          <td class="eTableLine0 eContent1">
            <?= $this->form->display_booleanSelectInput(array('name'=>'homepage', 'default'=>$this->page->homepage)); ?>
          </td>
        </tr>
        <?php endif; ?>

        <tr>
            <td class="eTableLine0" colspan="2">
                &nbsp;
            </td>
        </tr>

        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('formtitle_searchenginebot'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_contentindexing'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->form->display_booleanSelectInput(array('name'=>'robotIndex', 'default'=>$this->page->robotIndex)); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_linkfollowup'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->form->display_booleanSelectInput(array('name'=>'robotFollow', 'default'=>$this->page->robotFollow)); ?>
            </td>
        </tr>

        <tr>
          <td colspan="2" class="eTableLine0">
                &nbsp;
          </td>
        </tr>

        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('formtitle_admindata'); ?>
            </td>
        </tr>

        <?php if ($this->allow_rights_edition) : ?>

        <tr>
          <td class="eTableLine0 eContent2">
        <?= $this->get_translation('formitem_owner'); ?>
          </td>
          <td class="eTableLine0">
        <input type="hidden" name="wf_owner" value="<?= $this->page->wf_owner?>" />
        <?= $this->page->wf_owner?>
          </td>
        </tr>

        <tr>
          <td class="eTableLine1 eContent2">
        <?= $this->get_translation('formitem_editorgroup'); ?>
          </td>
          <td class="eTableLine1">
            <?= $this->form->display_selectInput(array('name'=>'wf_editor', 'values'=>$this->wfEditors, 'default'=>$this->page->wf_editor)); ?>
          </td>
        </tr>

        <?php if ($camyks->_conf['workflow'] == 1) : ?>
        <tr>
          <td class="eTableLine0 eContent2">
           <?= $this->get_translation('formitem_validatorgroup'); ?>
          </td>
          <td class="eTableLine0 eContent1">
          </td>
        </tr>
        <tr>
          <td class="eTableLine1 eContent2">
        <?= $this->get_translation('formitem_wfstatus'); ?>
          </td>
          <td class="eTableLine1 eContent1">
        <?= $this->page->wf_status?> (<?= $this->get_translation('wf_versionx', $this->page->wf_version); ?>)
          </td>
        </tr>

        <?php endif; ?>
        <?php else : ?>

        <tr>
          <td class="eTableLine0 eContent2">
        <?= $this->get_translation('formitem_owner'); ?>
          </td>
          <td class="eTableLine0 eContent1">
        <input type="hidden" name="wf_owner" value="<?= $this->page->wf_owner?>" />
        <?= $this->page->wf_owner?>
          </td>
        </tr>

        <tr>
          <td class="eTableLine1 eContent2">
        <?= $this->get_translation('formitem_editorgroup'); ?>
          </td>
          <td class="eTableLine1 eContent1">
        <?php if (isset($this->admin_groups[$this->page->wf_editor])) : ?>
        <?= $this->admin_groups[$this->page->wf_editor]->title?>
        <?php endif; ?>
          </td>
        </tr>

        <?php if ($camyks->site_conf['workflow'] == 1) : ?>
        <tr>
          <td class="eTableLine0 eContent2">
        <?= $this->get_translation('formitem_validatorgroup'); ?>
          </td>
          <td class="eTableLine0 eContent1">
          </td>
        </tr>
        <tr>
          <td class="eTableLine1 eContent2">
        <?= $this->get_translation('formitem_wfstatus'); ?>
          </td>
          <td class="eTableLine1 eContent1">
        <?= $this->page->wf_status?> (<?= $this->get_translation('wf_versionx', $this->page->wf_version); ?>)
          </td>
        </tr>
        <?php endif; ?>
        <?php endif; ?>

        <tr>
          <td class="eTableLine0 eContent2">
        <?= $this->get_translation('formitem_creation_date'); ?>
          </td>
          <td class="eTableLine0 eContent1">
        <?=date_displayLongDayDateHour($this->page->wf_cdate); ?>
          </td>
        </tr>

        <tr>
          <td class="eTableLine1 eContent2">
        <?= $this->get_translation('formitem_modification_date'); ?>
          </td>
          <td class="eTableLine1 eContent1">
        <?=date_displayLongDayDateHour($this->page->wf_mdate); ?>
          </td>
        </tr>

        <?php if ($this->page->type == 'model') : ?>
      </table>
    </div>
      </td>
    </tr>
    <?php endif; ?>
  </table>
</div>

<?php if ($this->allow_content_edition) : ?>
<?php /* add tabs with edit rights */ ?>
<?php $this->load_file('html/modify_tab_meta_edit.html.inc'); ?>
<?php $this->load_file('html/modify_tab_content_edit.html.inc'); ?>
<?php $this->load_file('html/modify_tab_lang_edit.html.inc'); ?>
<?php else : ?>
<?php /* add tabs without edit rights */ ?>
<?php $this->load_file('html/modify_tab_meta_view.html.inc'); ?>
<?php $this->load_file('html/modify_tab_content_view.html.inc'); ?>
<?php $this->load_file('html/modify_tab_lang_view.html.inc'); ?>
<?php endif; ?>

<?php if ($this->help != null) : ?>
<div id="itemhelp" style="display:none;" class="adminContentPanel">
<?php $this->display_help(); ?>
</div>
<?php endif; ?>

<?= $this->form->display_footer(); ?>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>

<?php
/**
 * @endcond Exclude
 */
?>
