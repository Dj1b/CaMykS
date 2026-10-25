<?php
/**
 * @brief Admin_GenericMediaLibraryManager module, picture selection list parameters.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: Jun 2015
 * @date Modification: Oct 2026
 * @copyright 2015 - 2026 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

$picturesStatusList = $this->get_picturesStatusList(true);

/* Build links */
$editPictureLink = $this->get_adminLink(array('mode'=>'edit_picture', 'picture_id'=>'%s'));
$deletePictureLink = 'javascript:adminengine_confirmRedirect(deletePictureUrl+%s, deletePictureMessage);';
$this->add_JSScript('var deletePictureMessage="'.string_html2Text($this->get_translation('deletepicturemessage')).'";');
$this->add_JSScript('var deletePictureUrl="'.$this->get_adminJSLink(array('mode'=>'delete_picture', 'picture_id'=>'')).'";');
$viewPictureLink = 'javascript:pl.display_picturePreview(%s);';

/* Build main parameters */
$this->pictureListParams = array('name'=>'pictureList', 'useSession'=>true, 'object'=>&$this->pictureItem, 'language'=>$this->language);

/* Build selector params */
$this->pictureListParams['headhiddens'] = array('openTab'=>'Pictures', 'gallery'=>$this->pictureGalleryItem->id);

/* Build sort parameters */
$this->pictureListParams['sort'] = array('allowed'=>false, 'default'=>'sortPosition', 'defaultway'=>'asc');

/* Build column parameters */
$this->pictureListParams['listcolumns'] = array(
    'thumbIcon' => array('title'=>' ', 'columntype'=>'method', 'method'=>'get_isDefaultIconRadio', 'style'=>'width:20px;'),
    'title'     => array('title'=>$camyks->get_translation('title'),'columntype'=>'text'),
    'cdate'     => array('title'=>$camyks->get_translation('date'), 'columntype'=>'date', 'mode'=>'numeric', 'style'=>'width:80px;'),
    'view'      => array('title'=>'', 'columntype'=>'button', 'icon'=>'view', 'url_value'=>$viewPictureLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('viewpicture')),
);
?>
