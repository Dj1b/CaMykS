<?php
/**
 * @brief Admin_GooglePoIMapManager module, category list parameters.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Mar 2010
 * @date Modification: Jul 2025
 * @copyright 2010 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

/* Build links */
$this->editCategoryLink = $this->get_adminLink(array('mode'=>'edit_cat', 'cat_id'=>'%s'));
$this->deleteCategoryLink = 'javascript:adminengine_confirmRedirect(deleteCatUrl+%s, deleteCatMessage);';
$this->add_JSScript('var deleteCatMessage="'.string_html2Text($this->get_translation('deletecatmessage')).'";');
$this->add_JSScript('var deleteCatUrl="'.$this->get_adminJSLink(array('mode'=>'delete_cat', 'cat_id'=>'')).'";');

/* Build main parameters */
$this->catListParams = array('name'=>'catList', 'useSession'=>true, 'object'=>&$this->categoryItem, 'language'=>$this->language);

/* Build head parameters */
$this->catListParams['headselectors'] = array('page'=> array('title'=>$camyks->get_translation('formitem_page'), 'itemtype'=>'page'));

/* Build sort parameters */
$this->catListParams['sort'] = array('allowed'=>false, 'default'=>'id', 'defaultway'=>'asc');

$this->catListParams['listcolumns'] = array(
    'status'    => array('title'=>' ', 'columntype'=>'boolean', 'mode'=>'pict', 'style'=>'width:12px;'),
    'title'     => array('title'=>$camyks->get_translation('title'), 'columntype'=>'text', 'maxlength'=>48),
    'points'    => array('title'=>$this->get_translation('points'), 'columntype'=>'text'),
);

if ($this->check_right(2)) {
    $this->catListParams['listlinks'] = array('new'=>array('title'=>$this->get_translation('addnewcategory'), 'icon'=>'plus', 'url_value'=>vsprintf($this->editCategoryLink, array(0=>0)), 'titlecolumn'=>'title', 'buttoncolumn'=>'edit'));
    $this->catListParams['listcolumns']['edit'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'edit', 'url_value'=>$this->editCategoryLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('editcategory'));
    $this->catListParams['listcolumns']['delete'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$this->deleteCategoryLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('deletecategory'), 'condition'=>'is_deletable');
}
?>
