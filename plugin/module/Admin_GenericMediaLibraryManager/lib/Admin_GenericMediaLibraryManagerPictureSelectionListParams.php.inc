<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version	: 1.0
 * Object Type      : Plugin / Module Engine
 * Creation Date	: Jun 2015
 * Last Modif Date	: Nov 2017
 *
 * Admin_GenericMediaLibraryManager picture list parameters
 */
global $camyks;

$this->picturesStatusList = $this->get_picturesStatusList(true);

/* build links */
$this->editPictureLink = $this->get_adminLink(array('mode'=>'edit_picture', 'picture_id'=>'%s'));
$this->deletePictureLink = 'javascript:adminengine_confirmRedirect(deletePictureUrl+%s, deletePictureMessage);';
$this->add_JSScript('var deletePictureMessage="'.string_html2Text($this->get_translation('deletepicturemessage')).'";');
$this->add_JSScript('var deletePictureUrl="'.$this->get_adminJSLink(array('mode'=>'delete_picture', 'picture_id'=>'')).'";');
$this->viewPictureLink = 'javascript:pl.display_picturePreview(%s);';

/* build main parameters */
$this->pictureListParams = array('name'=>'pictureList', 'useSession'=>true, 'object'=>&$this->pictureItem, 'language'=>$this->language);

/* build selector params */
$this->pictureListParams['headhiddens'] = array('openTab'=>'Pictures', 'gallery'=>$this->pictureGalleryItem->id);

/* build sort parameters */
$this->pictureListParams['sort'] = array('allowed'=>false, 'default'=>'sortPosition', 'defaultway'=>'asc');

/* build column parameters */
$this->pictureListParams['listcolumns'] = array('thumbIcon'=>array('title'=>' ', 'columntype'=>'method', 'method'=>'get_isDefaultIconRadio', 'style'=>'width:20px;'),
						 'title'=>array('title'=>$camyks->get_translation('title'),'columntype'=>'text'),
						 'cdate'=>array('title'=>$camyks->get_translation('date'), 'columntype'=>'date', 'mode'=>'numeric', 'style'=>'width:80px;'),
						 /* 'infos'=>array('title'=>$this->get_translation('header_infos'), 'columntype'=>'method', 'method'=>'get_fileInfos'),*/
						 'view'=>array('title'=>'', 'columntype'=>'button', 'icon'=>'view', 'url_value'=>$this->viewPictureLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('viewpicture')),
);
?>
