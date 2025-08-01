<?php
/**
 * @brief Admin_GenericContactFormManager module, form list parameters.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Nov 2010
 * @date Modification: Jul 2025
 * @copyright 2010 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

/* Build links */
$this->editFormLink = $camyks->get_adminLink($this->name, array('mode'=>'edit_form', 'form_id'=>'%s'));
$this->viewFormLink = $camyks->get_adminLink($this->name, array('mode'=>'view_form', 'form_id'=>'%s'));
$this->deleteFormLink = 'javascript:adminengine_confirmRedirect(deleteFormUrl+%s, deleteFormForm);';
$this->add_JSScript('var deleteFormForm="'.string_html2Text($this->get_translation('deleteformform')).'";');
$this->add_JSScript('var deleteFormUrl="'.$camyks->get_adminJSLink($this->name, array('mode'=>'delete_form', 'form_id'=>'')).'";');
$this->listRegistrationLink = $camyks->get_adminLink($this->name, array('mode'=>'list_registration', 'form_id'=>'%s'));

/* Build main parameters */
$this->formListParams = array('name'=>'formList', 'useSession'=>true, 'object'=>&$this->formItem, 'listlinks'=>array());

/* Build head parameters */
$this->formListParams['headselectors'] = array(
    'page'      => array('title'=>$this->get_translation('itempage'), 'itemtype'=>'page'),
    'status'    => array('title'=>$camyks->get_translation('formitem_status'), 'itemtype'=>'select', 'values'=>$this->get_formsStatusList(true), 'default'=>-1),
);

/* Build sort parameters */
$this->formListParams['sort'] = array('allowed'=>false, 'default'=>'edate', 'defaultway'=>'desc');

/* Build column parameters */
$this->formListParams['listcolumns'] = array(
    'status'    => array('title'=>'', 'columntype'=>'list', 'values'=>$this->get_formStatusIconList(), 'style'=>'width:20px;'),
    'edate'     => array('title'=>$this->get_translation('header_date'), 'columntype'=>'date', 'mode'=>'shortwithhours', 'style'=>'width:100px;'),
    'author'    => array('title'=>$this->get_translation('header_author'), 'columntype'=>'text'),
    'view'      => array('title'=>'', 'columntype'=>'button', 'icon'=>'view', 'url_value'=>$this->viewFormLink, 'url_title'=>$this->get_translation('viewform'), 'style'=>'width:12px;'),
);

/* Add right's dependent columns and link lines */
if ($this->check_right(1)===true) {
    $this->formListParams['listcolumns']['edit'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'edit', 'url_value'=>$this->editFormLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('editform'));
    $this->formListParams['listcolumns']['delete'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$this->deleteFormLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('deleteform'));
}
?>
