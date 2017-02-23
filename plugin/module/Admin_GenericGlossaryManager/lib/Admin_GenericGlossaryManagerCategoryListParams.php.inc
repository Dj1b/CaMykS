<?php
/*
 * CaMykS Engine
 * Developed by			: camyks.net
 * Author						: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version		: 1.0
 * Object Type      : Plugin / Module Library
 * Creation Date		: May 2010
 * Last Modif Date	: May 2010
 * 
 * Admin_GenericGlossaryManager category list parameters
 */
global $camyks;

/* get data */
$this->categoryStatusList = $this->get_categoriesStatusList(true);

/* build links */
$this->editCategoryLink = $this->get_adminLink(array('mode'=>'edit_category', 'category_id'=>'%s'));
$this->deleteCategoryLink = 'javascript:adminengine_confirmRedirect(deleteCategoryUrl+%s, deleteCategoryMessage);';
$this->add_JSScript('var deleteCategoryMessage="'.string_html2Text($this->get_translation('deletecategorymessage')).'";');
$this->add_JSScript('var deleteCategoryUrl="'.$this->get_adminJSLink(array('mode'=>'delete_category', 'category_id'=>'')).'";');

/* build main parameters */
$this->categoryListParams = array('name'=>'categoryList', 'useSession'=>true, 'object'=>&$this->categoryItem, 'language'=>$this->language);

/* build head hidden values */
$this->categoryListParams['headhiddens'] = array('openTab'=>'categories');

/* build head parameters */
$this->categoryListParams['headselectors'] = array('page'=> array('title'=>$camyks->get_translation('formitem_page'), 'itemtype'=>'page'),
						   'status'=> array('title'=>$camyks->get_translation('formitem_status'), 'itemtype'=>'select', 'values'=>$this->categoryStatusList, 'default'=>'-1'));

/* build sort parameters */
$this->categoryListParams['sort'] = array('allowed'=>false, 'default'=>'title', 'defaultway'=>'');

/* build column parameters */
$this->categoryListParams['listlinks'] = array('new'=>array('title'=>$this->get_translation('addnewcategory'), 'icon'=>'plus', 'url_value'=>vsprintf($this->editCategoryLink, 0), 'titlecolumn'=>'title', 'buttoncolumn'=>'edit'));

$this->categoryListParams['listcolumns'] = array('status'=>array('title'=>' ', 'columntype'=>'boolean', 'mode'=>'pict', 'style'=>'width:12px;'),
						 'title'=>array('title'=>$camyks->get_translation('title'),'columntype'=>'text'),
						 'definitions'=>array('title'=>$this->get_translation('definitions'), 'columntype'=>'text'),
						 'edit'=>array('title'=>' ', 'columntype'=>'button', 'icon'=>'edit', 'url_value'=>$this->editCategoryLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('editcategory')),
						 'delete'=>array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$this->deleteCategoryLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('deletecategory'), 'condition'=>'is_deletable'));
?>