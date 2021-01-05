<?php
/**
 * @brief Admin_GenericMediaLibraryManager Module admin view configuration layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: Jun 2015
 * @date Modification: Jan 2021
 * @copyright 2015 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
	<tr>
  		<td colspan="4" class="eTableHeader">
    		<?= $this->get_translation('picturegalleries'); ?>
  		</td>
	</tr>

	<tr>
  		<td class="eTableLine0 eContent2">
    		<?= $this->get_translation('formitem_maxfilesize'); ?>
  		</td>
  		<td class="eTableLine0 eContent1" colspan="3">
    		<?= $this->config->vars['picture_maxFileSize']?> M<?=language_getFileUnit(); ?>
  		</td>
	</tr>

	<tr>
  		<td class="eTableLine1 eContent2" style="width:200px;">
    		<?= $this->get_translation('formitem_resizemode'); ?>
  		</td>
  		<td class="eTableLine1 eContent1">
    		<?= $this->configResizeModeList[$this->config->vars['picture_resizeMode']]; ?>
  		</td>
	</tr>

	<tr>
  		<td class="eTableLine0 eContent2" style="width:200px;">
    		<?= $this->get_translation('formitem_backgroundcolor'); ?>
  		</td>
  		<td class="eTableLine0 eContent1">
    		<?= $this->config->vars['picture_backgroundColor']; ?>
  		</td>
	</tr>

	<tr>
  		<td class="eTableLine1 eContent2">
    		<?= $this->get_translation('formitem_filetype'); ?>
  		</td>
  		<td class="eTableLine1 eContent1">
    		<?= $this->configFileTypeList[$this->config->vars['picture_fileType']]; ?>
  		</td>
	</tr>

	<tr>
  		<td class="eTableLine0 eContent2">
    		<?= $this->get_translation('formitem_quality'); ?>
  		</td>
  		<td class="eTableLine0 eContent1">
    		<?= $this->config->vars['picture_jpgQuality']; ?> %
  		</td>
	</tr>

	<tr>
  		<td class="eTableLine1 eContent2">
    		<?= $this->get_translation('formitem_picturewidth'); ?>
  		</td>
  		<td class="eTableLine1 eContent1">
    		<?= $this->config->vars['picture_pictureWidth']; ?> px
  		</td>
	</tr>

	<tr>
  		<td class="eTableLine0 eContent2">
    		<?= $this->get_translation('formitem_pictureheight'); ?>
  		</td>
  		<td class="eTableLine0 eContent1">
    		<?= $this->config->vars['picture_pictureHeight']; ?> px
  		</td>
	</tr>

	<tr>
  		<td class="eTableLine1 eContent2">
    		<?= $this->get_translation('formitem_thumbwidth'); ?>
  		</td>
  		<td class="eTableLine1 eContent1">
    		<?= $this->config->vars['picture_thumbWidth']; ?> px
  		</td>
	</tr>

	<tr>
  		<td class="eTableLine0 eContent2">
    		<?= $this->get_translation('formitem_thumbheight'); ?>
  		</td>
  		<td class="eTableLine0 eContent1">
    		<?= $this->config->vars['picture_thumbHeight']; ?> px
  		</td>
	</tr>

	<tr>
  		<td colspan="2">
    		&nbsp;
  		</td>
	</tr>

	<tr>
  		<td colspan="2">
    		<?= $this->theme->get_button(array('url'=>$this->get_adminLink(array('mode'=>'edit_config')), 'title'=>$this->get_translation('edit_config'))); ?>
  		</td>
	</tr>
</table>
