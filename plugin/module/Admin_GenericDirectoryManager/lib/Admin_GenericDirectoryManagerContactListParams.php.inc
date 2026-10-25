<?php
/**
 * @brief Admin_GenericDirectoryManager module, contact list parameters.
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

$contactStatusList = $this->get_contactsStatusList(true);
$categoryList = $this->get_categoryTitleList(true);

/* Build links */
$newContactLink = $this->get_adminLink(array('mode'=>'edit_contact', 'contact_id'=>0));
$editContactLink = $this->get_adminLink(array('mode'=>'edit_contact', 'contact_id'=>'%s'));
$deleteContactLink = 'javascript:adminengine_confirmRedirect(deleteContactUrl+%s, deleteContactMessage);';
$this->add_JSScript('var deleteContactMessage="'.string_html2Text($this->get_translation('deletecontactmessage')).'";');
$this->add_JSScript('var deleteContactUrl="'.$this->get_adminJSLink(array('mode'=>'delete_contact', 'contact_id'=>'')).'";');

/* Build main parameters */
$this->contactListParams = array('name'=>'contactList', 'useSession'=>true, 'object'=>&$this->contactItem, 'language'=>$this->language);

/* Build head parameters */
$this->contactListParams['headselectors'] = array(
    'page'      => array('title'=>$camyks->get_translation('formitem_page'), 'itemtype'=>'page'),
    'status'    => array('title'=>$camyks->get_translation('formitem_status'), 'itemtype'=>'select', 'values'=>$contactStatusList, 'default'=>'-1'),
    'category'  => array('title'=>$this->get_translation('formitem_category'), 'itemtype'=>'select', 'values'=>$categoryList, 'default'=>'-1'),
);

/* Build sort parameters */
$this->contactListParams['sort'] = array('allowed'=>false, 'default'=>'word', 'defaultway'=>'');

/* Build column parameters */
$this->contactListParams['listcolumns'] = array(
    'status'    => array('title'=>' ', 'columntype'=>'boolean', 'mode'=>'pict', 'style'=>'width:12px;'),
    'name'      => array('title'=>$camyks->get_translation('name'),'columntype'=>'method', 'method'=>'get_listNameDisplay'),
    'category'  => array('title'=>$this->get_translation('header_category'),'columntype'=>'list', 'values'=>$categoryList),
);

if ($this->check_right(2)) {
    if (count($categoryList) > 1)
        $this->contactListParams['listlinks'] = array('new'=>array('title'=>$this->get_translation('addnewcontact'), 'icon'=>'plus', 'url_value'=>$newContactLink, 'titlecolumn'=>'name', 'buttoncolumn'=>'edit'));
    $this->contactListParams['listcolumns']['edit'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'edit', 'url_value'=>$editContactLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('editcontact'));
    $this->contactListParams['listcolumns']['delete'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$deleteContactLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('deletecontact'));
}
?>
