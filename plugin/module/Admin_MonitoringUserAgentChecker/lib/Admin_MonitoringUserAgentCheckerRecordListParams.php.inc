<?php
/**
 * @brief Admin_MonitoringUserAgentChecker Module record list parameters
 * @details Plugin, Module Library
 * @file plugin/module/Admin_MonitoringUserAgentChecker/lib/Admin_MonitoringUserAgentCheckerRecordListParams.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: Dec 2014
 * @date Modification: Nov 2018
 * @copyright 2014 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

$this->recordTypeListAll = $this->get_multiPlatformTypesList();
$this->recordTypeList = $this->get_singlePlatformTypesList();
$this->viewRecordLink = $this->get_adminLink(array('mode'=>'view_record', 'record_id'=>'%s'));
$this->recordStatusList = $this->get_recordStatusList();

/* build links */
$this->editRecordLink = $this->get_adminLink(array('mode'=>'edit_record', 'record_id'=>'%s'));
$this->deleteRecordLink = 'javascript:adminengine_confirmRedirect(deleteRecordUrl+%s, deleteRecordMessage);';
$this->add_JSScript('var deleteRecordMessage="'.string_html2Text($this->get_translation('deleterecordmessage')).'";');
$this->add_JSScript('var deleteRecordUrl="'.$this->get_adminJSLink(array('mode'=>'delete_record', 'record_id'=>'')).'";');

/* build main parameters */
$this->recordListParams = array('name'=>'recordList', 'useSession'=>true, 'object'=>&$this->recordItem, 'language'=>$this->language);

/* build head parameters */
$this->recordListParams['headselectors'] = array(
    'page'          => array('title'=>$camyks->get_translation('formitem_page'), 'itemtype'=>'page'),
    'status'        => array('title'=>$camyks->get_translation('formitem_status'), 'itemtype'=>'select', 'values'=>$this->recordStatusList, 'default'=>'-1'),
    'user_agent'    => array('title'=>$this->get_translation('formitem_search'), 'itemtype'=>'text'),
    'platform_type' => array('title'=>$this->get_translation('formitem_platform_type'), 'itemtype'=>'select', 'values'=>$this->recordTypeListAll, 'default'=>'-1'),
);

/* build sort parameters */
$this->recordListParams['sort'] = array('allowed'=>false, 'default'=>'lvisit', 'defaultway'=>'desc');

/* build column parameters */
$this->recordListParams['listcolumns'] = array(
    'selection'     => array('title'=>'', 'columntype'=>'checkbox'),
    'status'        => array('title'=>' ', 'columntype'=>'boolean', 'mode'=>'pict'),
    'user_agent'    => array('title'=>$this->get_translation('user_agent'), 'columntype'=>'method', 'maxlength'=>72, 'method'=>'get_adminValue'),
    'platform_type' => array('title'=>$this->get_translation('platform_type'), 'columntype'=>'list', 'values'=>$this->recordTypeList, 'style'=>'width:85px;'),
    'comparaison'   => array('title'=>'' , 'columntype'=>'method', 'method'=>'is_user_agent_correct'),
    'nvisit'        => array('title'=>$this->get_translation('nvisits'), 'columntype'=>'text', 'class'=>'hiddenOnMobile'),
    'lvisit'        => array('title'=>$this->get_translation('lvisits'), 'columntype'=>'date', 'style'=>'width:100px;', 'mode'=>'numeric', 'class'=>'hiddenOnMobile'),
    'view'          => array('title'=>'', 'columntype'=>'button', 'icon'=>'view', 'url_value'=>$this->viewRecordLink, 'url_title'=>$this->get_translation('viewrecord')),
);

$this->recordListParams['listlinks'] = array('new'=>array('title'=>$this->get_translation('addnewrecord'), 'icon'=>'plus', 'url_value'=>'javascript:adminengine_modalPopupOpen(\'admin_genericuseragentmanager_addpopup\');', 'titlecolumn'=>'user_agent', 'buttoncolumn'=>'edit'));
$this->recordListParams['listcolumns']['edit'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'edit', 'url_value'=>$this->editRecordLink, 'url_title'=>$this->get_translation('editrecord'));
$this->recordListParams['listcolumns']['delete'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$this->deleteRecordLink, 'url_title'=>$this->get_translation('deleterecord'));

?>
