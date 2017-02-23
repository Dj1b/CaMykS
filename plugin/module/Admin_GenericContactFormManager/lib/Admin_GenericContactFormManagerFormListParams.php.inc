<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Engine
 * Creation Date    : Nov 2010
 * Last Modif Date  : Nov 2010
 * 
 * Admin_GenericContactFormManager form list parameters
 */
global $camyks;

/* build links */
$this->editFormLink = $camyks->get_adminLink($this->name, array('mode'=>'edit_form', 'form_id'=>'%s'));
$this->viewFormLink = $camyks->get_adminLink($this->name, array('mode'=>'view_form', 'form_id'=>'%s'));
$this->deleteFormLink = 'javascript:adminengine_confirmRedirect(deleteFormUrl+%s, deleteFormForm);';
$this->add_JSScript('var deleteFormForm="'.string_html2Text($this->get_translation('deleteformform')).'";');
$this->add_JSScript('var deleteFormUrl="'.$camyks->get_adminJSLink($this->name, array('mode'=>'delete_form', 'form_id'=>'')).'";');
$this->listRegistrationLink = $camyks->get_adminLink($this->name, array('mode'=>'list_registration', 'form_id'=>'%s'));

/* build main parameters */
$this->formListParams = array('name'=>'formList', 'useSession'=>true, 'object'=>&$this->formItem);

/* build head parameters */
$this->formListParams['headselectors'] = array('page'=> array('title'=>$this->get_translation('itempage'), 'itemtype'=>'page'),
					      'status'=> array('title'=>$camyks->get_translation('formitem_status'), 'itemtype'=>'select', 'values'=>$this->get_formsStatusList(true), 'default'=>-1));

/* build sort parameters */
$this->formListParams['sort'] = array('allowed'=>false, 'default'=>'edate', 'defaultway'=>'desc');

/* build column parameters */
$this->formListParams['listlinks'] = array();
$this->formListParams['listcolumns'] = array('status'=>array('title'=>'', 'columntype'=>'list', 'values'=>$this->get_formStatusIconList(), 'style'=>'width:20px;'),
					    'edate'=>array('title'=>$this->get_translation('header_date'), 'columntype'=>'date', 'mode'=>'shortwithhours', 'style'=>'width:100px;'),
					    'author'=>array('title'=>$this->get_translation('header_author'), 'columntype'=>'text'),
					    'view'=>array('title'=>'', 'columntype'=>'button', 'icon'=>'view', 'url_value'=>$this->viewFormLink, 'url_title'=>$this->get_translation('viewform'), 'style'=>'width:12px;'));

/* add right's dependent columns and link lines */
if ($this->check_right(1)===true) {
  $this->formListParams['listcolumns']['edit'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'edit', 'url_value'=>$this->editFormLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('editform'));
  $this->formListParams['listcolumns']['delete'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$this->deleteFormLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('deleteform'));
  /*  $this->formListParams['listlinks']['new'] = array('title'=>$this->get_translation('addnewform'), 'icon'=>'plus', 'url_value'=>vsprintf($this->editFormLink, 0), 'titlecolumn'=>'edate', 'buttoncolumn'=>'edit'); */
}

?>