<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a2
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Engine
 * Create Date		: Apr 2009
 * Last Modif Date	: Apr 2009
 * 
 * Admin_GenericDownloadManager document list parameters
 */
global $camyks;

$this->documentStatusList = $this->get_documentStatusList(true);
$this->categoryList = $this->get_categoryTitleList($this->language);

/* build links */
$this->editDocumentLink = $this->get_adminLink(array('mode'=>'edit_document', 'document_id'=>'%s'));
$this->deleteDocumentLink = 'javascript:adminengine_confirmRedirect(deleteDocumentUrl+%s, deleteDocumentMessage);';
$this->add_JSScript('var deleteDocumentMessage="'.string_html2Text($this->get_translation('deletedocumentmessage')).'";');
$this->add_JSScript('var deleteDocumentUrl="'.$this->get_adminJSLink(array('mode'=>'delete_document', 'document_id'=>'')).'";');

/* build main parameters */
$this->documentListParams = array('name'=>'documentList', 'useSession'=>true, 'object'=>&$this->documentItem, 'language'=>$this->language);

/* build head parameters */
$this->documentListParams['headselectors'] = array('page'=> array('title'=>$camyks->get_translation('formitem_page'), 'itemtype'=>'page'),
						   'active'=> array('title'=>$camyks->get_translation('formitem_status'), 'itemtype'=>'select', 'values'=>$this->documentStatusList, 'default'=>'-1'),
						   'category'=> array('title'=>$this->get_translation('formitem_category'), 'itemtype'=>'select', 'values'=>$this->categoryList, 'default'=>'-1'));

/* build sort parameters */
$this->documentListParams['sort'] = array('allowed'=>false, 'default'=>'title', 'defaultway'=>'');

/* build column parameters */
if ($this->check_right(3)==true and count($this->categoryList)>1)
     $this->documentListParams['listlinks'] = array('new'=>array('title'=>$this->get_translation('addnewdocument'), 'icon'=>'plus', 'url_value'=>vsprintf($this->editDocumentLink, 0), 'titlecolumn'=>'title', 'buttoncolumn'=>'edit'));

$this->documentListParams['listcolumns'] = array('active'=>array('title'=>' ', 'columntype'=>'boolean', 'mode'=>'pict', 'style'=>'width:12px;'),
						 'title'=>array('title'=>$camyks->get_translation('title'),'columntype'=>'text'),
						 'releasedate'=>array('title'=>$camyks->get_translation('date'), 'columntype'=>'date', 'mode'=>'numeric'),
						 'infos'=>array('title'=>$this->get_translation('header_infos'), 'columntype'=>'method', 'method'=>'get_fileInfos'),
						 'category'=>array('title'=>$this->get_translation('header_category'),'columntype'=>'list', 'values'=>$this->categoryList));

if ($this->check_right(3)==true ) {
  $this->documentListParams['listcolumns']['edit'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'edit', 'url_value'=>$this->editDocumentLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('editdocument'));
  
  $this->documentListParams['listcolumns']['delete'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$this->deleteDocumentLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('deletedocument'));
}
?>