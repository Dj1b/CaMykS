<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author	    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Engine
 * Creation Date    : Mar 2010
 * Last Modif Date  : Mar 2010
 * 
 * Admin_GooglePoIMapManager category list parameters
 */
global $camyks;

/* build links */
$this->editCategoryLink = $this->get_adminLink(array('mode'=>'edit_cat', 'cat_id'=>'%s'));
$this->deleteCategoryLink = 'javascript:adminengine_confirmRedirect(deleteCatUrl+%s, deleteCatMessage);';
$this->add_JSScript('var deleteCatMessage="'.string_html2Text($this->get_translation('deletecatmessage')).'";');
$this->add_JSScript('var deleteCatUrl="'.$this->get_adminJSLink(array('mode'=>'delete_cat', 'cat_id'=>'')).'";');

/* build main parameters */
$this->catListParams = array('name'=>'catList', 'useSession'=>true, 'object'=>&$this->categoryItem, 'language'=>$this->language);

/* build head parameters */
$this->catListParams['headselectors'] = array('page'=> array('title'=>$camyks->get_translation('formitem_page'), 'itemtype'=>'page'));

/* build sort parameters */
$this->catListParams['sort'] = array('allowed'=>false, 'default'=>'id', 'defaultway'=>'asc');
  
$this->catListParams['listcolumns'] = array('status'=>array('title'=>' ', 'columntype'=>'boolean', 'mode'=>'pict', 'style'=>'width:12px;'),
					    'title'=>array('title'=>$camyks->get_translation('title'), 'columntype'=>'text', 'maxlength'=>48),
					    'points'=>array('title'=>$this->get_translation('points'), 'columntype'=>'text'));

if ($this->check_right(2)==true ) {
  $this->catListParams['listlinks'] = array('new'=>array('title'=>$this->get_translation('addnewcategory'), 'icon'=>'plus', 'url_value'=>vsprintf($this->editCategoryLink, 0), 'titlecolumn'=>'title', 'buttoncolumn'=>'edit'));
  $this->catListParams['listcolumns']['edit'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'edit', 'url_value'=>$this->editCategoryLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('editcategory'));
  $this->catListParams['listcolumns']['delete'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$this->deleteCategoryLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('deletecategory'), 'condition'=>'is_deletable');
}
?>