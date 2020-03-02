<?php
/**
 * @brief Admin_GenericGlossaryManager Module, category list parameters.
 * @details Plugin, Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: May 2010
 * @date Modification: Feb 2020
 * @copyright 2010 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
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
$this->categoryListParams['headselectors'] = array(
    'page'      => array('title' =>$camyks->get_translation('formitem_page'), 'itemtype'=>'page'),
    'status'    => array('title'=>$camyks->get_translation('formitem_status'), 'itemtype'=>'select', 'values'=>$this->categoryStatusList, 'default'=>'-1'),
);

/* build sort parameters */
$this->categoryListParams['sort'] = array('allowed'=>false, 'default'=>'title', 'defaultway'=>'');

/* build column parameters */
$this->categoryListParams['listlinks'] = array('new'=>array('title'=>$this->get_translation('addnewcategory'), 'icon'=>'plus', 'url_value'=>vsprintf($this->editCategoryLink, 0), 'titlecolumn'=>'title', 'buttoncolumn'=>'edit'));

$this->categoryListParams['listcolumns'] = array(
    'status'        => array('title'=>' ', 'columntype'=>'boolean', 'mode'=>'pict', 'style'=>'width:12px;'),
    'title'         => array('title'=>$camyks->get_translation('title'),'columntype'=>'text'),
    'definitions'   => array('title'=>$this->get_translation('definitions'), 'columntype'=>'text'),
    'edit'          => array('title'=>' ', 'columntype'=>'button', 'icon'=>'edit', 'url_value'=>$this->editCategoryLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('editcategory')),
    'delete'        => array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$this->deleteCategoryLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('deletecategory'), 'condition'=>'is_deletable'),
);
?>
