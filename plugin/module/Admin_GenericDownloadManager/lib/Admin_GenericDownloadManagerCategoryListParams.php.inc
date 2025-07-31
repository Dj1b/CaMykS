<?php
/**
 * @brief Admin_GenericDownloadManager module, category list parameters.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Apr 2009
 * @date Modification: Jul 2025
 * @copyright 2009 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

/* Load other data */
$this->categoryStatusList = $this->get_categoryStatusList(true);

/* Build links */
$this->editCategoryLink = $this->get_adminLink(array('mode'=>'edit_category', 'category_id'=>'%s'));
$this->deleteCategoryLink = 'javascript:adminengine_confirmRedirect(deleteCategoryUrl+%s, deleteCategoryMessage);';
$this->add_JSScript('var deleteCategoryMessage="'.string_html2Text($this->get_translation('deletecategorymessage')).'";');
$this->add_JSScript('var deleteCategoryUrl="'.$this->get_adminJSLink(array('mode'=>'delete_category', 'category_id'=>'')).'";');

/* Build main parameters */
$this->categoryListParams = array('name'=>'categoryList', 'useSession'=>true, 'object'=>&$this->categoryItem, 'language'=>$this->language);

/* Build head parameters */
$this->categoryListParams['headselectors'] = array(
    'page'      => array('title'=>$camyks->get_translation('formitem_page'), 'itemtype'=>'page'),
    'active'    => array('title'=>$camyks->get_translation('formitem_status'), 'itemtype'=>'select', 'values'=>$this->categoryStatusList, 'default'=>'-1'),
);

/* Build sort parameters */
$this->categoryListParams['sort'] = array('allowed'=>false, 'default'=>'title', 'defaultway'=>'');

/* Build head links */
$this->categoryListParams['listlinks'] = array('new'=>array('title'=>$this->get_translation('addnewcategory'), 'icon'=>'plus', 'url_value'=>vsprintf($this->editCategoryLink, array(0=>0)), 'titlecolumn'=>'title', 'buttoncolumn'=>'edit'));

/* Build column parameters */
$this->categoryListParams['listcolumns'] = array(
    'active'    => array('title'=>' ', 'columntype'=>'boolean', 'mode'=>'pict', 'style'=>'width:12px;'),
    'title'     => array('title'=>$camyks->get_translation('title'),'columntype'=>'text'),
    'docs'      => array('title'=>$this->get_translation('header_docs'), 'columntype'=>'text'),
    'edit'      => array('title'=>' ', 'columntype'=>'button', 'icon'=>'edit', 'url_value'=>$this->editCategoryLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('editcategory')),
    'delete'    => array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$this->deleteCategoryLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('deletecategory'), 'condition'=>'is_deletable'),
);
?>
