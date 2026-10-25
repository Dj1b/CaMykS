<?php
/**
 * @brief Admin_GenericGlossaryManager module, definition list parameters.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: May 2010
 * @date Modification: Oct 2026
 * @copyright 2010 - 2026 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

$definitionStatusList = $this->get_definitionsStatusList(true);
$categoryList = $this->get_categoryTitleList(true);

/* Build links */
$newDefinitionLink = $this->get_adminLink(array('mode'=>'edit_definition', 'definition_id'=>0));
$editDefinitionLink = $this->get_adminLink(array('mode'=>'edit_definition', 'definition_id'=>'%s'));
$deleteDefinitionLink = 'javascript:adminengine_confirmRedirect(deleteDefinitionUrl+%s, deleteDefinitionMessage);';
$this->add_JSScript('var deleteDefinitionMessage="'.string_html2Text($this->get_translation('deletedefinitionmessage')).'";');
$this->add_JSScript('var deleteDefinitionUrl="'.$this->get_adminJSLink(array('mode'=>'delete_definition', 'definition_id'=>'')).'";');

/* Build main parameters */
$this->definitionListParams = array('name'=>'definitionList', 'useSession'=>true, 'object'=>&$this->definitionItem, 'language'=>$this->language);

/* Build head parameters */
$this->definitionListParams['headselectors'] = array(
    'page'      => array('title'=>$camyks->get_translation('formitem_page'), 'itemtype'=>'page'),
    'status'    => array('title'=>$camyks->get_translation('formitem_status'), 'itemtype'=>'select', 'values'=>$definitionStatusList, 'default'=>'-1'),
    'category'  => array('title'=>$this->get_translation('formitem_category'), 'itemtype'=>'select', 'values'=>$categoryList, 'default'=>'-1'),
);

/* Build sort parameters */
$this->definitionListParams['sort'] = array('allowed'=>false, 'default'=>'word', 'defaultway'=>'');

/* Build column parameters */
$this->definitionListParams['listcolumns'] = array(
    'status'    => array('title'=>' ', 'columntype'=>'boolean', 'mode'=>'pict', 'style'=>'width:12px;'),
    'word'      => array('title'=>$this->get_translation('word'),'columntype'=>'text'),
    'category'  => array('title'=>$this->get_translation('header_category'),'columntype'=>'list', 'values'=>$categoryList),
);

if ($this->check_right(2)==true ) {
    if (count($categoryList)>1)
        $this->definitionListParams['listlinks'] = array('new'=>array('title'=>$this->get_translation('addnewdefinition'), 'icon'=>'plus', 'url_value'=>$newDefinitionLink, 'titlecolumn'=>'word', 'buttoncolumn'=>'edit'));
    $this->definitionListParams['listcolumns']['edit'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'edit', 'url_value'=>$editDefinitionLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('editdefinition'));
    $this->definitionListParams['listcolumns']['delete'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$deleteDefinitionLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('deletedefinition'));
}
?>
