<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author			: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0
 * Object Version	: 1.0
 * Object Type	    : Plugin / Input Layout
 * Creation Date    : Mar 2018
 * Last Modif Date	: Mar 2018
 * 
 * GenericMediaPopupConfig special layout : view configuration
*/
global $camyks;
?>
<?=$camyks->theme->get_boxContent2Header();?>
<div class="adminContentPanel">
<table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
  <tr>
    <td class="eTableLine0 eContent2" style="width:170px;">
      <?=$this->get_translation('formitem_insertion');?>
    </td>
    <td class="eTableLine0 eContent1">
      <?=$this->config->get_insertionTitle(); ?>
    </td>
  </tr>

  <tr>
    <td class="eTableLine1 eContent2">
      <?=$this->get_translation('formitem_stylesource');?>
    </td>
    <td class="eTableLine1 eContent1">
      <?=$this->config->get_styleSourceTitle(); ?>
    </td>
  </tr>
  
  <tr>
    <td class="eTableLine0" colspan="2">
      &nbsp;
    </td>
  </tr>
  
  <tr>
    <td class="eTableHeader" colspan="2">
      <?=$this->get_translation('formtitle_controls');?>
    </td>
  </tr>
  
  <tr>
    <td class="eTableLine0 eContent2">
      <?=$this->get_translation('formitem_clickbkgdtoclose');?>
    </td>
    <td class="eTableLine0">
      <?=$camyks->get_translation($this->config->vars['clickBkgdToClose']==1?'yes':'no'); ?>
    </td>
  </tr>
  
  <tr>
    <td class="eTableLine1 eContent2">
      <?=$this->get_translation('formitem_enableclosebutton');?>
    </td>
    <td class="eTableLine1">
      <?=$camyks->get_translation($this->config->vars['enableCloseButton']==1?'yes':'no'); ?>
    </td>
  </tr>
  
  <tr>
    <td class="eTableLine0 eContent2">
      <?=$this->get_translation('formitem_enablekeyboard');?>
    </td>
    <td class="eTableLine0">
      <?=$camyks->get_translation($this->config->vars['enableKeyboard']==1?'yes':'no'); ?>
    </td>
  </tr>
  
  <tr>
    <td class="eTableLine1 eContent2">
      <?=$this->get_translation('formitem_maxwidth');?>
    </td>
    <td class="eTableLine1">
      <?=$this->config->vars['maxWidth']; ?> px
    </td>
  </tr>
  
  <tr>
    <td class="eTableLine0" colspan="2">
      &nbsp;
    </td>
  </tr>
  
  <tr>
    <td class="eTableHeader" colspan="2">
      <?=$this->get_translation('formtitle_diaporama');?>
    </td>
  </tr>
  
  <tr>
    <td class="eTableLine0 eContent2">
      <?=$this->get_translation('formitem_enablediaporama');?>
    </td>
    <td class="eTableLine0">
      <?=$camyks->get_translation($this->config->vars['enableDiaporama']==1?'yes':'no'); ?>
    </td>
  </tr>

  <tr>
    <td class="eTableLine1 eContent2">
      <?=$this->get_translation('formitem_diaporamabuttonsshift');?>
    </td>
    <td class="eTableLine1">
      <?=$this->config->vars['diaporamaButtonsShift']; ?> px
    </td>
  </tr>
  
  <tr>
    <td class="eTableLine0" colspan="2">
      &nbsp;
    </td>
  </tr>
  
  <tr>
    <td class="eTableHeader" colspan="2">
      <?=$this->get_translation('formtitle_flashplayer');?>
    </td>
  </tr>
  
  <tr>
    <td class="eTableLine0 eContent2">
      <?=$this->get_translation('formitem_enableflash');?>
    </td>
    <td class="eTableLine0">
      <?=$camyks->get_translation($this->config->vars['enableFlash']==1?'yes':'no'); ?>
    </td>
  </tr>

  <tr>
    <td class="eTableLine1 eContent2">
      <?=$this->get_translation('formitem_flvcontrolercolor');?>
    </td>
    <td class="eTableLine1">
      #<?=$this->config->vars['flvControlerColor']; ?>
    </td>
  </tr>
  
  <tr>
    <td class="eTableLine0 eContent2">
      <?=$this->get_translation('formitem_flvcontroleralpha');?>
    </td>
    <td class="eTableLine0">
      <?=$this->config->vars['flvControlerAlpha']; ?>
    </td>
  </tr>

  <tr>
    <td class="eTableLine1 eContent2">
      <?=$this->get_translation('formitem_flvcontrolerheight');?>
    </td>
    <td class="eTableLine1">
      <?=$this->config->vars['flvControlerHeight']; ?> px
    </td>
  </tr>
  
</table>
</div>
<?=$camyks->theme->get_boxContent2Footer();?>