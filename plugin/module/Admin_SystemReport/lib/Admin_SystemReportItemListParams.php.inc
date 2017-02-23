<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	    : Plugin / Module Engine
 * Create Date		: Oct 2014
 * Last Modif Date	: Oct 2014
 *
 * Admin_SystemReportItem object for Admin_SystemReport module
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
$this->reportListParams['headselectors'] = array('page'=> array('title'=>$camyks->get_translation('formitem_page'), 'itemtype'=>'page'),
                           'status'=> array('title'=>$camyks->get_translation('formitem_status'), 'itemtype'=>'select', 'values'=>$this->reportsStatusList, 'default'=>'-1'),
						   'type'=> array('title'=>$camyks->get_translation('formitem_type'), 'itemtype'=>'select', 'values'=>$this->reportTypeList, 'default'=>'all'),
);

/* build sort parameters */
$this->reportListParams['sort'] = array('allowed'=>false, 'default'=>'_date', 'defaultway'=>'desc');

/* build column parameters */
$this->reportListParams['listcolumns'] = array('selection'=>array('title'=>'', 'columntype'=>'checkbox'),
                         'status'=>array('title'=>' ', 'columntype'=>'boolean', 'mode'=>'pict', 'style'=>'width:12px;'),
						 '_date'=>array('title'=>$camyks->get_translation('date'), 'columntype'=>'date', 'mode'=>'numeric', 'style'=>'width:60px;'),
                         'type'=>array('title'=>$camyks->get_translation('type'), 'columntype'=>'text'),
						 'objectname'=>array('title'=>$camyks->get_translation('object'), 'columntype'=>'text', 'maxlength'=>'64'),
						 /*'view'=>array('title'=>'', 'columntype'=>'button', 'icon'=>'view', 'url_value'=>$this->previewReportLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('previewreport'), 'url_target'=>'_blank')*/);
						 
if ($this->check_right(1)==true ) {
  $this->reportListParams['listcolumns']['view'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'edit', 'url_value'=>$this->viewReportLink, 'url_title'=>$this->get_translation('markasread'));
  $this->reportListParams['listcolumns']['delete'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$this->deleteReportLink, 'url_title'=>$this->get_translation('deletereport'));
}
?>