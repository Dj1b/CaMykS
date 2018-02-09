<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author			: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0
 * Object Version	: 1.0
 * Object Type	    : Plugin / Module Layout
 * Creation Date    : Dec 2014
 * Last Modif Date	: Feb 2018
 * 
 * Admin_ContactPage Module Admin Layout : edit configuration
*/
global $camyks;
?>
<?php if (isset($this->isConfig) and $this->isConfig) :?>

<?=$camyks->theme->get_boxContent2Header();?>
<div class="adminContentPanel">

<?php endif; ?>

<table cellspacing="2" cellpadding="0" border="0" style="width:100%;">

<tr>
  <td class="eTableHeader" colspan="3">
    <?=$this->get_translation('formtitle_actions'); ?>
  </td>
</tr>

<tr>
    <td class="eTableLine0 eContent2" style="width:150px;">
        <?=$this->get_translation('formitem_w3cvalidator');?>
    </td>
    <td class="eTableLine0 eContent1" colspan="2">
        <?=$this->editform->display_selectInput(array('name'=>'action_w3cValidator', 'values'=>$this->W3CValidatorStatus));?>
    </td>
</tr>

<tr>
  <td class="eTableLine0" colspan="3">
    &nbsp;
  </td>
</tr>

<tr>
  <td class="eTableHeader" colspan="3">
    <?=$this->get_translation('formtitle_ogmeta'); ?>
  </td>
</tr>

<tr>
    <td class="eTableLine0 eContent2">
        <?=$camyks->get_translation('formitem_status');?>
    </td>
    <td class="eTableLine0 eContent1" colspan="2">
        <?=$this->editform->display_selectInput(array('name'=>'site_ogmeta', 'values'=>$this->OGMetaStatus));?>
    </td>
</tr>

<tr>
  <td class="eTableLine0" colspan="3">
    &nbsp;
  </td>
</tr>

<tr>
  <td class="eTableHeader" colspan="3">
    <?=$this->get_translation('formtitle_pagesnotfound'); ?>
  </td>
</tr>

<tr>
    <td class="eTableLine0 eContent2">
        <?=$this->get_translation('formitem_404fallback');?>
    </td>
    <td class="eTableLine0 eContent1" style="width:210px;">
      <?=$this->editform->display_selectInput(array('name'=>'page_404FallBack', 'values'=>$this->Error404FallBacks, 'onchange'=>'ConfigEditor.check_selected404FallBack()')); ?>
    </td>
    <td class="eTableLine0">
      <div id="FileSelectionBox" style="display:none;">
        <span style="display:inline-block; width:70px;" class="eContent2">
          <?=$this->get_translation('formitem_file') ?>
        </span>
        <?=$this->editform->display_textInput(array('name'=>'page_404ErrorFile'));?>
       </div>
      <div id="PageSelectionBox" style="display:none;">
        <span style="display:inline-block; width:70px;" class="eContent2">
          <?=$this->get_translation('formitem_page') ?>
        </span>
        <?=$this->editform->display_textInput(array('name'=>'page_404ErrorPage'));?>
      </div>
    </td>
</tr>
</table>

<table id="HeaderSendingBox" cellspacing="2" cellpadding="0" border="0" style="width:100%; display:none;">
<tr>
    <td class="eTableLine0 eContent2" style="width:150px;">
        <?=$this->get_translation('formitem_send404header');?>
    </td>
    <td class="eTableLine0 eContent1">
      <?=$this->editform->display_booleanSelectInput(array('name'=>'page_404SendHeader')); ?>
    </td>
</tr>
</table>

<?php if (isset($this->isConfig) and $this->isConfig) :?>

</div>
<?=$camyks->theme->get_boxContent2Footer();?>

<?php endif; ?>

