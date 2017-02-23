<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author	    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Engine
 * Creation Date    : Mar 2010
 * Last Modif Date  : Mar 2010
 * 
 * Admin_GooglePoIMapManager icon list parameters
 */
global $camyks;

/* build links */
$this->editIconLink = $this->get_adminLink(array('mode'=>'edit_icon', 'icon_id'=>'%s'));
$this->deleteIconLink = 'javascript:adminengine_confirmRedirect(deleteIconUrl+%s, deleteIconMessage);';
$this->add_JSScript('var deleteIconMessage="'.string_html2Text($this->get_translation('deleteiconmessage')).'";');
$this->add_JSScript('var deleteIconUrl="'.$this->get_adminJSLink(array('mode'=>'delete_icon', 'icon_id'=>'')).'";');

/* build main parameters */
$this->iconListParams = array('name'=>'iconList', 'useSession'=>true, 'object'=>&$this->iconItem, 'language'=>$this->language);

/* build head parameters */
$this->iconListParams['headselectors'] = array('page'=> array('title'=>$camyks->get_translation('formitem_page'), 'itemtype'=>'page'));

/* build sort parameters */
$this->iconListParams['sort'] = array('allowed'=>false, 'default'=>'id', 'defaultway'=>'asc');
  
$this->iconListParams['listcolumns'] = array('space'=>array('title'=>' ', 'columntype'=>'special_text', 'text'=>' ', 'style'=>'width:12px;'),
					     'name'=>array('title'=>$camyks->get_translation('name'), 'columntype'=>'text'));


if ($this->check_right(2)==true ) {
  $this->iconListParams['listlinks'] = array('new'=>array('title'=>$this->get_translation('addnewicon'), 'icon'=>'plus', 'url_value'=>vsprintf($this->editIconLink, 0), 'titlecolumn'=>'name', 'buttoncolumn'=>'edit'));
  $this->iconListParams['listcolumns']['edit'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'edit', 'url_value'=>$this->editIconLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('editicon'));
  $this->iconListParams['listcolumns']['delete'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$this->deleteIconLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('deleteicon'), 'condition'=>'is_deletable');
}
?>