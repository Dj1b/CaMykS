<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Engine
 * Creation Date    : Sep 2010
 * Last Modif Date  : Mar 2018
 * 
 * Admin_GenericGuestBookManager message list parameters
 */
global $camyks;

/* build links */
$this->editMsgLink = $this->get_adminLink(array('mode'=>'edit_msg', 'msg_id'=>'%s'));
$this->viewMsgLink = $this->get_adminLink(array('mode'=>'view_msg', 'msg_id'=>'%s'));
$this->deleteMsgLink = 'javascript:adminengine_confirmRedirect(deleteMsgUrl+%s, deleteMsgMessage);';
$this->add_JSScript('var deleteMsgMessage="'.string_html2Text($this->get_translation('deletemsgmessage')).'";');
$this->add_JSScript('var deleteMsgUrl="'.$this->get_adminJSLink(array('mode'=>'delete_msg', 'msg_id'=>'')).'";');

/* build main parameters */
$this->msgListParams = array('name'=>'msgList', 'useSession'=>true, 'object'=>&$this->msgItem);

/* build head parameters */
$this->msgListParams['headselectors'] = array(
    'page'      => array('title'=>$this->get_translation('itempage'), 'itemtype'=>'page'),
    'status'    => array('title'=>$camyks->get_translation('formitem_status'), 'itemtype'=>'select', 'values'=>$this->get_messagesStatusList(true), 'default'=>-1)
);

/* build sort parameters */
$this->msgListParams['sort'] = array('allowed'=>false, 'default'=>'edate', 'defaultway'=>'desc');

/* build column parameters */
$this->msgListParams['listlinks'] = array();
$this->msgListParams['listcolumns'] = array(
    'status'    => array('title'=>'', 'columntype'=>'list', 'values'=>$this->get_messageStatusIconList(), 'style'=>'width:20px;'),
    'edate'     => array('title'=>$this->get_translation('header_date'), 'columntype'=>'date', 'mode'=>'shortwithhours', 'style'=>'width:100px;'),
    'author'    => array('title'=>$this->get_translation('header_author'), 'columntype'=>'text'),
    'message'   => array('title'=>$this->get_translation('header_message'), 'columntype'=>'text', 'maxlength'=>64),
    'view'      => array('title'=>'', 'columntype'=>'button', 'icon'=>'view', 'url_value'=>$this->viewMsgLink, 'url_title'=>$this->get_translation('viewmsg'), 'style'=>'width:12px;'),
);

/* add right's dependent columns and link lines */
if ($this->check_right(1)===true) {
    $this->msgListParams['listcolumns']['edit'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'edit', 'url_value'=>$this->editMsgLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('editmsg'));
    $this->msgListParams['listcolumns']['delete'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$this->deleteMsgLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('deletemsg'));
}
?>