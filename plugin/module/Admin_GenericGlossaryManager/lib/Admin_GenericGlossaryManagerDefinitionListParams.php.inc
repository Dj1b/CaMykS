<?php
/*
 * CaMykS Engine
 * Developed by			: camyks.net
 * Author						: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version		: 1.0b
 * Object Version		: 1.0
 * Object Type      : Plugin / Module Library
 * Creation Date		: May 2010
 * Last Modif Date	: May 2010
 * 
 * Admin_GenericGlossaryManager definition list parameters
 */
global $camyks;

$this->definitionStatusList = $this->get_definitionsStatusList(true);
$this->categoryList = $this->get_categoryTitleList(true);

/* build links */
$this->editDefinitionLink = $this->get_adminLink(array('mode'=>'edit_definition', 'definition_id'=>'%s'));
$this->deleteDefinitionLink = 'javascript:adminengine_confirmRedirect(deleteDefinitionUrl+%s, deleteDefinitionMessage);';
$this->add_JSScript('var deleteDefinitionMessage="'.string_html2Text($this->get_translation('deletedefinitionmessage')).'";');
$this->add_JSScript('var deleteDefinitionUrl="'.$this->get_adminJSLink(array('mode'=>'delete_definition', 'definition_id'=>'')).'";');

/* build main parameters */
$this->definitionListParams = array('name'=>'definitionList', 'useSession'=>true, 'object'=>&$this->definitionItem, 'language'=>$this->language);

/* build head parameters */
$this->definitionListParams['headselectors'] = array('page'=> array('title'=>$camyks->get_translation('formitem_page'), 'itemtype'=>'page'),
						   'status'=> array('title'=>$camyks->get_translation('formitem_status'), 'itemtype'=>'select', 'values'=>$this->definitionStatusList, 'default'=>'-1'),
						   'category'=> array('title'=>$this->get_translation('formitem_category'), 'itemtype'=>'select', 'values'=>$this->categoryList, 'default'=>'-1'));

/* build sort parameters */
$this->definitionListParams['sort'] = array('allowed'=>false, 'default'=>'word', 'defaultway'=>'');

/* build column parameters */
$this->definitionListParams['listcolumns'] = array('status'=>array('title'=>' ', 'columntype'=>'boolean', 'mode'=>'pict', 'style'=>'width:12px;'),
						 'word'=>array('title'=>$this->get_translation('word'),'columntype'=>'text'),
						 'category'=>array('title'=>$this->get_translation('header_category'),'columntype'=>'list', 'values'=>$this->categoryList));

if ($this->check_right(2)==true ) {
	if (count($this->categoryList)>1)
		$this->definitionListParams['listlinks'] = array('new'=>array('title'=>$this->get_translation('addnewdefinition'), 'icon'=>'plus', 'url_value'=>vsprintf($this->editDefinitionLink, 0), 'titlecolumn'=>'word', 'buttoncolumn'=>'edit'));
  $this->definitionListParams['listcolumns']['edit'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'edit', 'url_value'=>$this->editDefinitionLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('editdefinition'));
  $this->definitionListParams['listcolumns']['delete'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$this->deleteDefinitionLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('deletedefinition'));
}
?>