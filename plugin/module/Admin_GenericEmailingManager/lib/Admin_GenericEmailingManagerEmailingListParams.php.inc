<?php
/**
 * @brief Admin_GenericEmailingManager Module emailing list parameters
 * @details Plugin, Module Library
 * @file plugin/module/Admin_GenericEmailingManager/lib/Admin_GenericEmailingManagerEmailingListParams.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Dec 2012
 * @date Modification: Dec 2018
 * @copyright 2012 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

/* build lists */
$this->emailingsStatusList = $this->get_emailingsStatusList(true);
$this->emailingStatusIconList = $this->get_emailingStatusIconList();

/* build links */
$this->previewEmailingLink = 'request.php?module='.$this->name.'&mode=preview_emailing&emailing_id=%s';
$this->viewEmailingLink = $this->get_adminLink(array('mode'=>'view_emailing', 'emailing_id'=>'%s'));
$this->editEmailingLink = $this->get_adminLink(array('mode'=>'edit_emailing', 'emailing_id'=>'%s'));
$this->deleteEmailingLink = 'javascript:adminengine_confirmRedirect(deleteEmailingUrl+%s, deleteEmailingMessage);';
$this->add_JSScript('var deleteEmailingMessage="'.string_html2Text($this->get_translation('deleteemailingmessage')).'";');
$this->add_JSScript('var deleteEmailingUrl="'.$this->get_adminJSLink(array('mode'=>'delete_emailing', 'emailing_id'=>'')).'";');

/* build main parameters */
$this->emailingListParams = array('name'=>'emailingList', 'useSession'=>true, 'object'=>&$this->emailingItem);

/* build head parameters */
$this->emailingListParams['headselectors'] = array(
    'page'      => array('title'=>$camyks->get_translation('formitem_page'), 'itemtype'=>'page'),
    'status'    => array('title'=>$camyks->get_translation('formitem_status'), 'itemtype'=>'select', 'values'=>$this->emailingsStatusList, 'default'=>'-1'),
);

/* build hidden parameters */
$this->emailingListParams['headhiddens'] = array('openTab'=>'emailings');

/* build sort parameters */
$this->emailingListParams['sort'] = array('allowed'=>false, 'default'=>'id', 'defaultway'=>'desc');

/* build column parameters */
$this->emailingListParams['listcolumns'] = array(
    'status'        => array('title'=>' ', 'columntype'=>'list', 'values'=>$this->emailingStatusIconList, 'style'=>'width:12px;'),
    'email_title'   => array('title'=>$camyks->get_translation('title'),'columntype'=>'text', 'maxlength'=>'64'),
    'preview'       => array('title'=>' ', 'columntype'=>'button', 'icon'=>'file', 'url_value'=>$this->previewEmailingLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('previewemailing'), 'url_target'=>'_blank'),
    'view'          => array('title'=>' ', 'columntype'=>'button', 'icon'=>'view', 'url_value'=>$this->viewEmailingLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('viewemailing')),
);

if ($this->check_right(3)==true ) {
    $this->emailingListParams['listlinks'] = array('new'=>array('title'=>$this->get_translation('addnewemailing'), 'icon'=>'plus', 'url_value'=>vsprintf($this->editEmailingLink, 0), 'titlecolumn'=>'email_title', 'buttoncolumn'=>'edit'));
    $this->emailingListParams['listcolumns']['edit'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'edit', 'url_value'=>$this->editEmailingLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('editemailing'), 'condition'=>'is_editable');
    $this->emailingListParams['listcolumns']['delete'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$this->deleteEmailingLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('deleteemailing'), 'condition'=>'is_editable');
}
?>
