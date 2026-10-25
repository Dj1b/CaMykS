<?php
/**
 * @brief Admin_GenericDirectoryManager module, category list parameters.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: Jul 2010
 * @date Modification: Oct 2026
 * @copyright 2010 - 2026 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

/* Load data */
$categoryStatusList = $this->get_categoriesStatusList(true);

/* Build links */
$newCategoryLink = $this->get_adminLink(array('mode'=>'edit_category', 'category_id'=>0));
$editCategoryLink = $this->get_adminLink(array('mode'=>'edit_category', 'category_id'=>'%s'));
$deleteCategoryLink = 'javascript:adminengine_confirmRedirect(deleteCategoryUrl+%s, deleteCategoryMessage);';
$this->add_JSScript('var deleteCategoryMessage="'.string_html2Text($this->get_translation('deletecategorymessage')).'";');
$this->add_JSScript('var deleteCategoryUrl="'.$this->get_adminJSLink(array('mode'=>'delete_category', 'category_id'=>'')).'";');

/* Build main parameters */
$this->categoryListParams = array('name'=>'categoryList', 'useSession'=>true, 'object'=>&$this->categoryItem, 'language'=>$this->language);

/* Build head hidden values */
$this->categoryListParams['headhiddens'] = array('openTab'=>'categories');

/* Build head parameters */
$this->categoryListParams['headselectors'] = array(
    'page'      => array('title'=>$camyks->get_translation('formitem_page'), 'itemtype'=>'page'),
    'status'    => array('title'=>$camyks->get_translation('formitem_status'), 'itemtype'=>'select', 'values'=>$categoryStatusList, 'default'=>'-1'),
);

/* Build sort parameters */
$this->categoryListParams['sort'] = array('allowed'=>false, 'default'=>'title', 'defaultway'=>'');

/* Build column parameters */
$this->categoryListParams['listlinks'] = array('new'=>array('title'=>$this->get_translation('addnewcategory'), 'icon'=>'plus', 'url_value'=>$newCategoryLink, 'titlecolumn'=>'title', 'buttoncolumn'=>'edit'));

$this->categoryListParams['listcolumns'] = array(
    'status'    => array('title'=>' ', 'columntype'=>'boolean', 'mode'=>'pict', 'style'=>'width:12px;'),
    'title'     => array('title'=>$camyks->get_translation('title'),'columntype'=>'text'),
    'contacts'  => array('title'=>$this->get_translation('contacts'), 'columntype'=>'text'),
    'edit'      => array('title'=>' ', 'columntype'=>'button', 'icon'=>'edit', 'url_value'=>$editCategoryLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('editcategory')),
    'delete'    => array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$deleteCategoryLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('deletecategory'), 'condition'=>'is_deletable'),
);
?>
