<?php
/**
 * @brief Admin_SystemReport Module report list parameters
 * @details Plugin / Module Library
 * @file plugin/module/Admin_SystemReport/lib/Admin_SystemReportItemListParams.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: Oct 2014
 * @date Modification: Apr 2019
 * @copyright 2014 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

/* build lists */
$this->reportsStatusList = $this->get_reportsStatusList(true);
$this->reportsTypeList = $this->get_reportsStatusList();
$this->reportTypeList = $this->get_reportTypeList(true);

/* build links */
$this->viewReportLink = $this->get_adminLink(array('mode'=>'readreport', 'report_id'=>'%s'));
$this->deleteReportLink = 'javascript:adminengine_confirmRedirect(deleteReportUrl+%s, deleteReportMessage);';
$this->add_JSScript('var deleteReportMessage="'.string_html2Text($this->get_translation('deletelogmessage')).'";');
$this->add_JSScript('var deleteReportUrl="'.$this->get_adminJSLink(array('mode'=>'deletesingle', 'report'=>'')).'";');

/* build main parameters */
$this->reportListParams = array('name'=>'reportList', 'useSession'=>true, 'object'=>&$this->reportItem);

/* build head parameters */
$this->reportListParams['headselectors'] = array(
    'page'      => array('title'=>$camyks->get_translation('formitem_page'), 'itemtype'=>'page'),
    'status'    => array('title'=>$camyks->get_translation('formitem_status'), 'itemtype'=>'select', 'values'=>$this->reportsStatusList, 'default'=>'-1'),
    'type'      => array('title'=>$camyks->get_translation('formitem_type'), 'itemtype'=>'select', 'values'=>$this->reportTypeList, 'default'=>'all'),
);

/* build sort parameters */
$this->reportListParams['sort'] = array('allowed'=>false, 'default'=>'_date', 'defaultway'=>'desc');

/* build column parameters */
$this->reportListParams['listcolumns'] = array(
    'selection'     => array('title'=>'', 'columntype'=>'checkbox'),
    'status'        => array('title'=>' ', 'columntype'=>'boolean', 'mode'=>'pict', 'style'=>'width:12px;'),
    '_date'         => array('title'=>$camyks->get_translation('date'), 'columntype'=>'date', 'mode'=>'numeric', 'style'=>'width:60px;'),
    'type'          => array('title'=>$camyks->get_translation('type'), 'columntype'=>'text', 'class'=>'hiddenOnMobile'),
    'objectname'    => array('title'=>$camyks->get_translation('object'), 'columntype'=>'text', 'maxlength'=>'64'),
);

if ($this->check_right(1) == true) {
  $this->reportListParams['listcolumns']['view'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'view', 'url_value'=>$this->viewReportLink, 'url_title'=>$this->get_translation('view'));
  $this->reportListParams['listcolumns']['delete'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$this->deleteReportLink, 'url_title'=>$this->get_translation('deletereport'));
}
?>
