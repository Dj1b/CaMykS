<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version  	: 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Engine
 * Creation Date	: Jun 2015
 * Last Modif Date	: Jun 2015
 * 
 * Admin_GenericMediaLibraryManager PictureGallery list parameters
 */
global $camyks;

/* get data */
$this->pictureGalleriesStatusList = $this->get_pictureGalleriesStatusList(true);
$this->pictureGalleryStatusIconList = $this->get_pictureGalleryStatusIconList();

/* build links */
$this->viewPictureGalleryLink = $this->get_adminLink(array('mode'=>'view_pictureGallery', 'pictureGallery_id'=>'%s'));
$this->editPictureGalleryLink = $this->get_adminLink(array('mode'=>'edit_pictureGallery', 'pictureGallery_id'=>'%s'));
$this->deletePictureGalleryLink = 'javascript:adminengine_confirmRedirect(deletePictureGalleryUrl+%s, deletePictureGalleryMessage);';
$this->add_JSScript('var deletePictureGalleryMessage="'.string_html2Text($this->get_translation('deletepicturegallerymessage')).'";');
$this->add_JSScript('var deletePictureGalleryUrl="'.$this->get_adminJSLink(array('mode'=>'delete_pictureGallery', 'pictureGallery_id'=>'')).'";');

/* build main parameters */
$this->pictureGalleryListParams = array('name'=>'pictureGalleryList', 'useSession'=>true, 'object'=>&$this->pictureGalleryItem, 'language'=>$this->language);
$this->pictureGalleryListParams['headhiddens'] = array('openTab'=>'PictureGalleries');

/* build head parameters */
$this->pictureGalleryListParams['headselectors'] = array('page'=> array('title'=>$camyks->get_translation('formitem_page'), 'itemtype'=>'page'),
						                                 'status'=> array('title'=>$camyks->get_translation('formitem_status'), 'itemtype'=>'select', 'values'=>$this->pictureGalleriesStatusList, 'default'=>'-1'));

/* build sort parameters */
$this->pictureGalleryListParams['sort'] = array('allowed'=>false, 'default'=>'cdate', 'defaultway'=>'desc');

/* build column parameters */
$this->pictureGalleryListParams['listlinks'] = array('new'=>array('title'=>$this->get_translation('addnewpicturegallery'), 'icon'=>'plus', 'url_value'=>vsprintf($this->editPictureGalleryLink, 0), 'titlecolumn'=>'title', 'buttoncolumn'=>'view'));

$this->pictureGalleryListParams['listcolumns'] = array('status'=>array('title'=>' ', 'columntype'=>'list', 'values'=>$this->pictureGalleryStatusIconList, 'class'=>'eTableIconCell'),
						 'title'=>array('title'=>$camyks->get_translation('title'),'columntype'=>'text'),
						 'pictures'=>array('title'=>$this->get_translation('pictures'), 'columntype'=>'text'),
						 'summary'=>array('title'=>$this->get_translation('summary'), 'columntype'=>'text', 'maxlength'=>48),
						 'cdate'=>array('title'=>$camyks->get_translation('date'), 'columntype'=>'date', 'mode'=>'numeric', 'style'=>'width:50px;'),
						 'view'=>array('title'=>' ', 'columntype'=>'button', 'icon'=>'view', 'url_value'=>$this->viewPictureGalleryLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('viewpicturegallery')),
						 'delete'=>array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$this->deletePictureGalleryLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('deletepicturegallery')));
?>