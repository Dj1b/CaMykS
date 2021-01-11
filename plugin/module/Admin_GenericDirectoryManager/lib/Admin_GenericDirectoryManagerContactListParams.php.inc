<?php
/**
 * @brief Admin_GenericDirectoryManager Module contact list parameters.
 * @details Plugin, Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jul 2010
 * @date Modification: Jan 2021
 * @copyright 2010 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

$this->contactStatusList = $this->get_contactsStatusList(true);
$this->categoryList = $this->get_categoryTitleList(true);

/* build links */
$this->editContactLink = $this->get_adminLink(array('mode'=>'edit_contact', 'contact_id'=>'%s'));
$this->deleteContactLink = 'javascript:adminengine_confirmRedirect(deleteContactUrl+%s, deleteContactMessage);';
$this->add_JSScript('var deleteContactMessage="'.string_html2Text($this->get_translation('deletecontactmessage')).'";');
$this->add_JSScript('var deleteContactUrl="'.$this->get_adminJSLink(array('mode'=>'delete_contact', 'contact_id'=>'')).'";');

/* build main parameters */
$this->contactListParams = array('name'=>'contactList', 'useSession'=>true, 'object'=>&$this->contactItem, 'language'=>$this->language);

/* build head parameters */
$this->contactListParams['headselectors'] = array(
    'page'      => array('title'=>$camyks->get_translation('formitem_page'), 'itemtype'=>'page'),
    'status'    => array('title'=>$camyks->get_translation('formitem_status'), 'itemtype'=>'select', 'values'=>$this->contactStatusList, 'default'=>'-1'),
    'category'  => array('title'=>$this->get_translation('formitem_category'), 'itemtype'=>'select', 'values'=>$this->categoryList, 'default'=>'-1'),
);

/* build sort parameters */
$this->contactListParams['sort'] = array('allowed'=>false, 'default'=>'word', 'defaultway'=>'');

/* build column parameters */
$this->contactListParams['listcolumns'] = array(
    'status'    => array('title'=>' ', 'columntype'=>'boolean', 'mode'=>'pict', 'style'=>'width:12px;'),
    'name'      => array('title'=>$camyks->get_translation('name'),'columntype'=>'method', 'method'=>'get_listNameDisplay'),
    'category'  => array('title'=>$this->get_translation('header_category'),'columntype'=>'list', 'values'=>$this->categoryList),
);

if ($this->check_right(2)) {
    if (count($this->categoryList) > 1)
        $this->contactListParams['listlinks'] = array('new'=>array('title'=>$this->get_translation('addnewcontact'), 'icon'=>'plus', 'url_value'=>vsprintf($this->editContactLink, 0), 'titlecolumn'=>'name', 'buttoncolumn'=>'edit'));
    $this->contactListParams['listcolumns']['edit'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'edit', 'url_value'=>$this->editContactLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('editcontact'));
    $this->contactListParams['listcolumns']['delete'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$this->deleteContactLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('deletecontact'));
}
?>
