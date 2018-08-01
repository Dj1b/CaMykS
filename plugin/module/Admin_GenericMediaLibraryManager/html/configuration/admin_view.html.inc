<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0
 * Object Version	: 1.0.1
 * Object Type	    : Plugin / Module Layout
 * Creation Date    : Jun 2015
 * Last Modif Date	: Jul 2018
 * 
 * Admin_GenericMediaLibraryManager Module Admin Layout : edit_config
*/
global $camyks;

?>
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
<tr>
  <td colspan="4" class="eTableHeader">
    <?=$this->get_translation('picturegalleries');?>
  </td>
</tr>

<tr>
  <td class="eTableLine0 eContent2">
    <?=$this->get_translation('formitem_maxfilesize');?>
  </td>
  <td class="eTableLine0 eContent1" colspan="3">
    <?=$this->config->vars['picture_maxFileSize']?> M<?=language_getFileUnit();?>
  </td>
</tr>

<tr>
  <td class="eTableLine1 eContent2" style="width:200px;">
    <?=$this->get_translation('formitem_resizemode');?>
  </td>
  <td class="eTableLine1 eContent1">
    <?=$this->configResizeModeList[$this->config->vars['picture_resizeMode']];?>
  </td>
</tr>
<tr>
  <td class="eTableLine0 eContent2" style="width:200px;">
    <?=$this->get_translation('formitem_backgroundcolor');?>
  </td>
  <td class="eTableLine0 eContent1">
    <?=$this->config->vars['picture_backgroundColor'];?>
  </td>
</tr>

<tr>
  <td class="eTableLine1 eContent2">
    <?=$this->get_translation('formitem_filetype');?>
  </td>
  <td class="eTableLine1 eContent1">
    <?=$this->configFileTypeList[$this->config->vars['picture_fileType']];?>
  </td>
</tr>
<tr>
  <td class="eTableLine0 eContent2">
    <?=$this->get_translation('formitem_quality');?>
  </td>
  <td class="eTableLine0 eContent1">
    <?=$this->config->vars['picture_jpgQuality'];?> %
  </td>
</tr>

<tr>
  <td class="eTableLine1 eContent2">
    <?=$this->get_translation('formitem_picturewidth');?>
  </td>
  <td class="eTableLine1 eContent1">
    <?=$this->config->vars['picture_pictureWidth'];?> px
  </td>
</tr>
<tr>
  <td class="eTableLine0 eContent2">
    <?=$this->get_translation('formitem_pictureheight');?>
  </td>
  <td class="eTableLine0 eContent1">
    <?=$this->config->vars['picture_pictureHeight'];?> px
  </td>
</tr>

<tr>
  <td class="eTableLine1 eContent2">
    <?=$this->get_translation('formitem_thumbwidth');?>
  </td>
  <td class="eTableLine1 eContent1">
    <?=$this->config->vars['picture_thumbWidth'];?> px
  </td>
</tr>
<tr>
  <td class="eTableLine0 eContent2">
    <?=$this->get_translation('formitem_thumbheight');?>
  </td>
  <td class="eTableLine0 eContent1">
    <?=$this->config->vars['picture_thumbHeight'];?> px
  </td>
</tr>

<tr>
  <td colspan="2">
    &nbsp;
  </td>
</tr>

<tr>
  <td colspan="2">
    <?=$this->theme->get_button(array('url'=>$this->get_adminLink(array('mode'=>'edit_config')), 'title'=>$this->get_translation('edit_config')));?>
  </td>
</tr>

</table>