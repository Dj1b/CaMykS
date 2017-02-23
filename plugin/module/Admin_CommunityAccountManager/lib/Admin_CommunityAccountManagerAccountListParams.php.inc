<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Library
 * Creation Date    : Oct 2010
 * Last Modif Date  : Oct 2010
 * 
 * Admin_CommunityAccountManager account list parameters
 */
global $camyks;

$this->statusList = $this->get_accountsStatusList(true);
$this->statusIconList = $this->get_accountStatusIconList();

/* build links */
$this->editAccountLink = $camyks->get_adminLink($this->name, array('mode'=>'edit_account', 'account_id'=>'%s'));
$this->deleteAccountLink = 'javascript:adminengine_confirmRedirect(deleteAccountUrl+%s, deleteAccountMessage);';
$this->add_JSScript('var deleteAccountMessage="'.string_html2Text($this->get_translation('deleteaccountmessage')).'";');
$this->add_JSScript('var deleteAccountUrl="'.$camyks->get_adminJSLink($this->name, array('mode'=>'delete_account', 'account_id'=>'')).'";');

/* build main parameters */
$this->accountListParams = array('name'=>'accountList', 'useSession'=>true, 'object'=>&$this->accountItem);

/* build head parameters */
$this->accountListParams['headselectors'] = array('page'=> array('title'=>$this->get_translation('itempage'), 'itemtype'=>'page'),
  'status'=> array('title'=>$camyks->get_translation('formitem_status'), 'itemtype'=>'select', 'values'=>$this->statusList, 'default'=>-1),
  'type'=> array('title'=>$camyks->get_translation('formitem_type'), 'itemtype'=>'select', 'values'=>$this->mTypeList, 'default'=>-1));

/* build sort parameters */
$this->accountListParams['sort'] = array('allowed'=>false, 'default'=>'id', 'defaultway'=>'asc');

/* build column parameters */
$this->accountListParams['listlinks'] = array();
$this->accountListParams['listcolumns'] = array('status'=>array('title'=>' ', 'columntype'=>'list', 'style'=>'width:12px;', 'values'=>$this->statusIconList),
						'lastname'=>array('title'=>$this->get_translation('headname'), 'columntype'=>'specialtext', 'text'=>'%s %s', 'vars'=>array(1=>'firstname', 2=>'lastname')),
						'type'=>array('title'=>$this->get_translation('headtype'), 'columntype'=>'list', 'values'=>$this->sTypeList));

if ($this->check_right(1)===true) {
  $this->accountListParams['listcolumns']['edit'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'edit', 'url_value'=>$this->editAccountLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('editaccount'));
  $this->accountListParams['listcolumns']['delete'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$this->deleteAccountLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('deleteaccount'));
  $this->accountListParams['listlinks']['new'] = array('title'=>$this->get_translation('addnewaccount'), 'icon'=>'plus', 'url_value'=>vsprintf($this->editAccountLink, 0), 'titlecolumn'=>'lastname', 'buttoncolumn'=>'edit');
}
?>