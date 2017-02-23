<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version	: 1.0
 * Object Type      : Plugin / Module Engine
 * Creation Date	: Jun 2015
 * Last Modif Date	: Jun 2015
 * 
 * Admin_GenericMediaLibraryManager picture list parameters
 */
global $camyks;

$this->picturesStatusList = $this->get_picturesStatusList(true);

/* build links */
$this->moveDownPictureLink = $this->get_adminLink(array('mode'=>'moveDown_picture', 'picture_id'=>'%s'));
$this->moveUpPictureLink = $this->get_adminLink(array('mode'=>'moveUp_picture', 'picture_id'=>'%s'));
$this->editPictureLink = $this->get_adminLink(array('mode'=>'edit_picture', 'picture_id'=>'%s'));
$this->deletePictureLink = 'javascript:adminengine_confirmRedirect(deletePictureUrl+%s, deletePictureMessage);';
$this->add_JSScript('var deletePictureMessage="'.string_html2Text($this->get_translation('deletepicturemessage')).'";');
$this->add_JSScript('var deletePictureUrl="'.$this->get_adminJSLink(array('mode'=>'delete_picture', 'picture_id'=>'')).'";');
$this->viewPictureLink = 'javascript:pl.display_picturePreview(%s);';

/* build main parameters */
$this->pictureListParams = array('name'=>'pictureList', 'useSession'=>true, 'object'=>&$this->pictureItem, 'language'=>$this->language);

$this->pictureListParams['headhiddens'] = array('openTab'=>'Pictures', 'gallery'=>$this->pictureGalleryItem->id);

/* build head parameters */
$this->pictureListParams['headselectors'] = array('page'=> array('title'=>$camyks->get_translation('formitem_page'), 'itemtype'=>'page'),
						                          'status'=> array('title'=>$camyks->get_translation('formitem_status'), 'itemtype'=>'select', 'values'=>$this->picturesStatusList, 'default'=>'-1'));

/* build sort parameters */
$this->pictureListParams['sort'] = array('allowed'=>false, 'default'=>'sortPosition', 'defaultway'=>'asc');

/* build column parameters */
if ($this->check_right(2)==true)
     $this->pictureListParams['listlinks'] = array('new'=>array('title'=>$this->get_translation('addnewpicture'), 'icon'=>'plus', 'url_value'=>vsprintf($this->editPictureLink, 0).'&amp;gallery='.$this->pictureGalleryItem->id, 'titlecolumn'=>'title', 'buttoncolumn'=>'edit'));

$this->pictureListParams['listcolumns'] = array(
                         'status'=>array('title'=>' ', 'columntype'=>'boolean', 'mode'=>'pict', 'style'=>'width:12px;'),
                         'default'=>array('title'=>' ', 'columntype'=>'method', 'method'=>'get_isDefaultPictureIcon', 'style'=>'width:12px;'),
						 'title'=>array('title'=>$camyks->get_translation('title'),'columntype'=>'text'),
						 'cdate'=>array('title'=>$camyks->get_translation('date'), 'columntype'=>'date', 'mode'=>'numericwithhours', 'style'=>'width:100px;'),
						 /* 'infos'=>array('title'=>$this->get_translation('header_infos'), 'columntype'=>'method', 'method'=>'get_fileInfos'),*/
						 'view'=>array('title'=>'', 'columntype'=>'button', 'icon'=>'view', 'url_value'=>$this->viewPictureLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('viewpicture')),
);

if ($this->check_right(2)==true ) {
  $this->pictureListParams['listcolumns']['movedown'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'down', 'url_value'=>$this->moveDownPictureLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('movedownpicture'), 'condition'=>'is_notLast');
  $this->pictureListParams['listcolumns']['moveup'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'up', 'url_value'=>$this->moveUpPictureLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('moveuppicture'), 'condition'=>'is_notFirst');
  $this->pictureListParams['listcolumns']['edit'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'edit', 'url_value'=>$this->editPictureLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('editpicture'));
  $this->pictureListParams['listcolumns']['delete'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$this->deletePictureLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('deletepicture'));
}
?>