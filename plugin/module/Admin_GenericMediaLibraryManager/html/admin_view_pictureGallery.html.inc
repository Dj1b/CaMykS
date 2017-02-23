<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0b
 * Object Version	: 1.0
 * Object Type	    : Plugin / Module Layout
 * Creation Date	: Jun 2015
 * Last Modif Date	: Jun 2015
 * 
 * Admin_GenericMediaLibraryManager Module Admin Layout : view_pictureGallery
*/
global $camyks;

/* define flags */
$flags = array();
if (count($camyks->get_confValue('editing_languages')) > 1 )
	foreach ($camyks->get_confValue('editing_languages') as $l)
		$flags[$l] = '<img src="'.language_getIcon($l, false).'" alt="" border="0" style="float:right;" />';
else
	foreach ($camyks->get_confValue('editing_languages') as $l)
		$flags[$l] = '';
		
?>
<?=$this->theme->get_boxHeader('width:800px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->adminTitle);?>
<?=$this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams);?>
<?=$this->theme->get_boxContent2Header();?>

<div id="itemProperties" style="display:<?=$this->tabBuilder->get_tabDisplay('Properties');?>;" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
<tr>
  <td class="eTableLine0 eContent2" style="width:150px;">
    <?=$camyks->get_translation('formitem_status')?>
  </td>
  <td class="eTableLine0">
    <?=$this->pictureGalleryStatusList[$this->pictureGalleryItem->vars['status']];?>
  </td>
</tr>

<?php foreach ( $camyks->get_confValue('editing_languages') as $l ) : ?>
<tr>
<td class="eTableLine1 eContent2">
<?=$flags[$l];?>
<?=$camyks->get_translation('formitem_title')?>
</td>
<td class="eTableLine1 eContent1">
<?=$this->pictureGalleryItem->vars['title_'.$l];?>
</td>
</tr>
<?php endforeach; ?>

<?php foreach ( $camyks->get_confValue('editing_languages') as $l ) : ?>
<tr>
<td class="eTableLine0 eContent2">
<?=$flags[$l];?>
<?=$this->get_translation('formitem_summary')?>
</td>
<td class="eTableLine0 eContent1">
<?=$this->pictureGalleryItem->vars['summary_'.$l];?>
</td>
</tr>
<?php endforeach; ?>

<tr>
  <td class="eTableLine1 eContent2">
    <?=$camyks->get_translation('formitem_date')?>
  </td>
  <td class="eTableLine1">
    <?=date_displayLongDate($this->pictureGalleryItem->vars['cdate']);?>
  </td>
</tr>

<tr>
  <td colspan="2">
    &nbsp;
  </td>
</tr>

<tr>
  <td colspan="2">
    <?=$this->theme->get_button(array('title'=>$this->get_translation('edit_properties'),
        'url'=>$this->get_adminLink(array('mode'=>'edit_pictureGallery', 'pictureGallery_id'=>$this->pictureGalleryItem->id)))); ?>
  </td>
</tr>

</table>
</div>

<div id="itemPictures" style="display:<?=$this->tabBuilder->get_tabDisplay('Pictures');?>;" class="adminContentPanel">
<div style="float:right; width:<?=$this->previewWidth + 2;?>px; margin:27px 0 0 8px;">
  <div id="picturePreview" style="border:solid 1px #6a798b; font-size:0;">
    <img src="<?=$this->get_fileURL('img/preview.jpg');?>" alt="" style="max-width:<?=$this->previewWidth;?>px;" />
  </div>
  <div class="eTableHeader">
    <?=$this->get_translation('photo_preview');?>
  </div>
</div>
<div style="margin-right:<?=$this->previewWidth+10;?>px;">
  <?=$this->pictureList->display('head');?>
  <?=$this->pictureList->display('list');?>
</div>
</div>

<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?=$this->theme->get_boxFooter(); ?>