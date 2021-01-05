<?php
/**
 * @brief Admin_GenericMediaLibraryManager Module picture selection list parameters
 * @details Plugin, Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jun 2015
 * @date Modification: Jan 2021
 * @copyright 2015 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
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
$this->pictureListParams['listcolumns'] = array(
	'thumbIcon'	=> array('title'=>' ', 'columntype'=>'method', 'method'=>'get_isDefaultIconRadio', 'style'=>'width:20px;'),
	'title'		=> array('title'=>$camyks->get_translation('title'),'columntype'=>'text'),
	'cdate'		=> array('title'=>$camyks->get_translation('date'), 'columntype'=>'date', 'mode'=>'numeric', 'style'=>'width:80px;'),
	'view'		=> array('title'=>'', 'columntype'=>'button', 'icon'=>'view', 'url_value'=>$this->viewPictureLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('viewpicture')),
);
?>
