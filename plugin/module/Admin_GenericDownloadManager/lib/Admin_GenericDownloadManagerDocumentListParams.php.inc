<?php
/**
 * @brief Admin_GenericDownloadManager module, document list parameters.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.2
 * @date Creation: Apr 2009
 * @date Modification: Oct 2025
 * @copyright 2009 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

/* Load data */
$documentStatusList = $this->get_documentStatusList(true);
$categoryTitleList = $this->get_categoryTitleList($this->language);

/* Build links */
$newDocumentLink = $this->get_adminLink(array('mode'=>'edit_document', 'document_id'=>'0'));
$editDocumentLink = $this->get_adminLink(array('mode'=>'edit_document', 'document_id'=>'%s'));
$deleteDocumentLink = 'javascript:adminengine_confirmRedirect(deleteDocumentUrl+%s, deleteDocumentMessage);';
$this->add_JSScript('var deleteDocumentMessage="'.string_html2Text($this->get_translation('deletedocumentmessage')).'";');
$this->add_JSScript('var deleteDocumentUrl="'.$this->get_adminJSLink(array('mode'=>'delete_document', 'document_id'=>'')).'";');

/* Build main parameters */
$this->documentListParams = array('name'=>'documentList', 'useSession'=>true, 'object'=>&$this->documentItem, 'language'=>$this->language);

/* Build head parameters */
$this->documentListParams['headselectors'] = array(
    'page'      => array('title'=>$camyks->get_translation('formitem_page'), 'itemtype'=>'page'),
    'active'    => array('title'=>$camyks->get_translation('formitem_status'), 'itemtype'=>'select', 'values'=>$documentStatusList, 'default'=>'-1'),
    'category'  => array('title'=>$this->get_translation('formitem_category'), 'itemtype'=>'select', 'values'=>$categoryTitleList, 'default'=>'-1'),
);

/* Build sort parameters */
$this->documentListParams['sort'] = array('allowed'=>false, 'default'=>'title', 'defaultway'=>'');

/* Build head links parameters */
if ($this->check_right(3) == true and count($categoryTitleList) > 1)
     $this->documentListParams['listlinks'] = array('new'=>array('title'=>$this->get_translation('addnewdocument'), 'icon'=>'plus', 'url_value'=>$newDocumentLink, 'titlecolumn'=>'title', 'buttoncolumn'=>'edit'));

/* Build column parameters */
$this->documentListParams['listcolumns'] = array(
    'active'        => array('title'=>' ', 'columntype'=>'boolean', 'mode'=>'pict', 'class'=>'eTableIconCell'),
    'title'         => array('title'=>$camyks->get_translation('title'),'columntype'=>'text'),
    'releasedate'   => array('title'=>$camyks->get_translation('date'), 'columntype'=>'date', 'mode'=>'numeric'),
    'infos'         => array('title'=>$this->get_translation('header_infos'), 'columntype'=>'method', 'method'=>'get_fileInfos'),
    'category'      => array('title'=>$this->get_translation('header_category'),'columntype'=>'list', 'values'=>$categoryTitleList),
);
if ($this->check_right(3) == true) {
    $this->documentListParams['listcolumns']['edit'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'edit', 'url_value'=>$editDocumentLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('editdocument'));
    $this->documentListParams['listcolumns']['delete'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$deleteDocumentLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('deletedocument'));
}
?>
