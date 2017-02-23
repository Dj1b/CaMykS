<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author	    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Engine
 * Creation Date    : Jun 2010
 * Last Modif Date  : Jun 2010
 * 
 * Admin_GooglePoIMapManager point list parameters
 */
global $camyks;

/* build lists */
$this->pointStatusList = $this->get_pointsStatusList(true);

/* build links */
$this->editPointLink = $this->get_adminLink(array('mode'=>'edit_point', 'point_id'=>'%s'));
$this->deletePointLink = 'javascript:adminengine_confirmRedirect(deletePointUrl+%s, deletePointMessage);';
$this->add_JSScript('var deletePointMessage="'.string_html2Text($this->get_translation('deletepointmessage')).'";');
$this->add_JSScript('var deletePointUrl="'.$this->get_adminJSLink(array('mode'=>'delete_point', 'point_id'=>'')).'";');

/* build main parameters */
$this->pointListParams = array('name'=>'pointList', 'useSession'=>true, 'object'=>&$this->pointItem, 'language'=>$this->language);

/* build head parameters */
$this->pointListParams['headselectors'] = array('page'=> array('title'=>$camyks->get_translation('formitem_page'), 'itemtype'=>'page'),
						   'status'=> array('title'=>$camyks->get_translation('formitem_status'), 'itemtype'=>'select', 'values'=>$this->pointStatusList, 'default'=>'-1'));
/* build sort parameters */
$this->pointListParams['sort'] = array('allowed'=>false, 'default'=>'id', 'defaultway'=>'asc');
  
$this->pointListParams['listcolumns'] = array('status'=>array('title'=>' ', 'columntype'=>'boolean', 'mode'=>'pict', 'style'=>'width:12px;'),
					      'title'=>array('title'=>$camyks->get_translation('title'), 'columntype'=>'text', 'maxlength'=>48));

if ($this->check_right(1)==true ) {
  $this->pointListParams['listlinks'] = array('new'=>array('title'=>$this->get_translation('addnewpoint'), 'icon'=>'plus', 'url_value'=>vsprintf($this->editPointLink, 0), 'titlecolumn'=>'title', 'buttoncolumn'=>'edit'));
  $this->pointListParams['listcolumns']['edit'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'edit', 'url_value'=>$this->editPointLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('editpoint'));
  $this->pointListParams['listcolumns']['delete'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$this->deletePointLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('deletepoint'));
 }
?>