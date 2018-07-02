<?php
/**
 * @brief Admin_SecurityTools Module admin layout to edit backup configuration
 * @details Plugin / Module layout
 * @file plugin/module/Admin_SecurityTools/html/admin_editbackupconfig.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Oct 2007
 * @date Modification: Jun 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;
?>
<?=$this->theme->get_boxHeader(array('class'=>'adminEditorModule'));?>
<?=$this->theme->get_boxTitleBar($this->title.' : '.$this->get_translation('backup_modifyconfig'));?>
<?=$this->theme->get_boxContent2Header();?>
<?=$this->form->display_header();?>
<?=$this->form->display_hiddens();?>
<div class="adminContentPanel">
  <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
    <tr>
      <td class="eTableLine0 eContent2">
        <?=$this->get_translation('backup_method'); ?>
      </td>
      <td class="eTableLine0 eContent1">
      <?=$this->form->display_selectInput(array('name'=>'backup_method', 'values'=>$this->backup_methods, 'default'=>$this->config->vars['backup_method']));?>
      </td>
    </tr>
    
    <tr>
      <td class="eTableLine1 eContent2">
        <?=$this->get_translation('backup_compression'); ?>
      </td>
      <td class="eTableLine1 eContent1">
      <?=$this->form->display_selectInput(array('name'=>'backup_compression', 'values'=>$this->backup_compressions, 'default'=>$this->config->vars['backup_compression']));?>
      </td>
    </tr>
    <tr>
      <td class="eTableLine0 eContent2">
        <?=$this->get_translation('backup_type'); ?>
      </td>
      <td class="eTableLine0 eContent1">
      <?=$this->form->display_selectInput(array('name'=>'backup_type', 'values'=>$this->backup_types, 'default'=>$this->config->vars['backup_type']));?>
      </td>
    </tr>
    
    <tr>
      <td class="eTableLine1 eContent2">
        <?=$this->get_translation('backup_temp'); ?>
      </td>
      <td class="eTableLine1 eContent1">
        <input type="text" name="backup_temp" value="<?=$this->config->vars['backup_temp']?>" maxlength="128" class="inputs" />
      </td>
    </tr>
    <tr>
      <td class="eContent1">
        &nbsp; 
      </td>
      <td class="eContent3">
        <?=$this->get_translation('backup_nulltempissystemfolder');?>
      </td>
    </tr>
  </table>
</div>
<?= $this->form->display_footer(); ?>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>

<?php 
/**
 * @endcond Exclude
 */
?>