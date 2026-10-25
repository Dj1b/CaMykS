<?php
/**
 * @brief Admin_GenericEmailingManager module, contact list parameters library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.3
 * @date Creation: Dec 2012
 * @date Modification: Oct 2026
 * @copyright 2012 - 2026 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

global $camyks;

/* Build lists */
$contactsStatusList = $this->get_contactsStatusList(true);
$contactStatusIconList = $this->get_contactStatusIconList();
$contactGroupList = $this->get_contactGroupList(true);

/* Build links */
$newContactLink = $this->get_adminLink(array('mode'=>'edit_contact', 'contact_id'=>0));
$editContactLink = $this->get_adminLink(array('mode'=>'edit_contact', 'contact_id'=>'%s'));
$deleteContactLink = 'javascript:adminengine_confirmRedirect(deleteContactUrl+%s, deleteContactMessage);';
$this->add_JSScript('var deleteContactMessage="'.string_html2Text($this->get_translation('deletecontactmessage')).'";');
$this->add_JSScript('var deleteContactUrl="'.$this->get_adminJSLink(array('mode'=>'delete_contact', 'contact_id'=>'')).'";');

/* Build main parameters */
$this->contactListParams = array('name'=>'contactList', 'useSession'=>true, 'object'=>&$this->contactItem);

/* Build head parameters */
$this->contactListParams['headselectors'] = array(
    'page'      => array('title'=>$camyks->get_translation('formitem_page'), 'itemtype'=>'page'),
    'status'    => array('title'=>$camyks->get_translation('formitem_status'), 'itemtype'=>'select', 'values'=>$contactsStatusList, 'default'=>'-1'),
    'group'     => array('title'=>$this->get_translation('formitem_group'), 'itemtype'=>'select', 'values'=>$contactGroupList, 'default'=>'_all_'),
    'search'    => array('title'=>$this->get_translation('formitem_search'), 'itemtype'=>'text', 'default'=>''),
);

/* Build hidden parameters */
$this->contactListParams['headhiddens'] = array('openTab'=>'contacts');

/* Build sort parameters */
$this->contactListParams['sort'] = array('allowed'=>false, 'default'=>'lastname', 'defaultway'=>'asc');

/* Build column parameters */
$this->contactListParams['listcolumns'] = array(
    'status'    => array('title'=>' ', 'columntype'=>'list', 'values'=>$contactStatusIconList, 'class'=>'eTableIconCell'),
    'name'      => array('title'=>$camyks->get_translation('name'),'columntype'=>'specialtext', 'text'=>'%s %s', 'vars'=>array('firstname', 'lastname'), 'maxlength'=>'64'),
    'email'     => array('title'=>$camyks->get_translation('email'),'columntype'=>'text'),
);

if ($this->check_right(1)==true ) {
  $this->contactListParams['listlinks'] = array('new'=>array('title'=>$this->get_translation('addnewcontact'), 'icon'=>'plus', 'url_value'=>$newContactLink, 'titlecolumn'=>'name', 'buttoncolumn'=>'edit'));
  $this->contactListParams['listcolumns']['edit'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'edit', 'url_value'=>$editContactLink, 'url_title'=>$this->get_translation('editcontact'));
  $this->contactListParams['listcolumns']['delete'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$deleteContactLink, 'url_title'=>$this->get_translation('deletecontact'));
}
?>
