<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	    : CaMykS Team <camyks.petition@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Library
 * Creation Date    : Sep 2010
 * Last Modif Date  : Sep 2010
 * 
 * Admin_GenericPetitionManager petition list parameters
 */
global $camyks;

$this->petitionStatusList = $this->get_petitionsStatusList(true);

/* build links */
$this->editPetitionLink = $this->get_adminLink(array('mode'=>'edit_petition', 'petition_id'=>'%s'));
$this->listSignatureLink = $this->get_adminLink(array('mode'=>'list_signature', 'petition_id'=>'%s'));
$this->deletePetitionLink = 'javascript:adminengine_confirmRedirect(deletePetitionUrl+%s, deletePetitionMessage);';
$this->add_JSScript('var deletePetitionMessage="'.string_html2Text($this->get_translation('deletepetitionmessage')).'";');
$this->add_JSScript('var deletePetitionUrl="'.$this->get_adminJSLink(array('mode'=>'delete_petition', 'petition_id'=>'')).'";');

/* build main parameters */
$this->petitionListParams = array('name'=>'petitionList', 'useSession'=>true, 'object'=>&$this->petitionItem, 'language'=>$this->language);

/* build head parameters */
$this->petitionListParams['headselectors'] = array('page'=> array('title'=>$camyks->get_translation('formitem_page'), 'itemtype'=>'page'),
						   'status'=> array('title'=>$camyks->get_translation('formitem_status'), 'itemtype'=>'select', 'values'=>$this->petitionStatusList, 'default'=>'-1'));

/* build sort parameters */
$this->petitionListParams['sort'] = array('allowed'=>false, 'default'=>'', 'defaultway'=>'');

/* build column parameters */
$this->petitionListParams['listcolumns'] = array('status'=>array('title'=>' ', 'columntype'=>'boolean', 'mode'=>'pict', 'style'=>'width:12px;'),
						 'title'=>array('title'=>$camyks->get_translation('title'),'columntype'=>'text'),
						 'signs'=>array('title'=>$this->get_translation('signs'),'columntype'=>'text', 'style'=>'width:75px;'),
						 'cdate'=>array('title'=>$this->get_translation('startedat'), 'columntype'=>'date', 'mode'=>'numeric', 'style'=>'width:75px'));
						 

if ($this->check_right(2)==true ) {
    $this->petitionListParams['listlinks'] = array('new'=>array('title'=>$this->get_translation('addnewpetition'), 'icon'=>'plus', 'url_value'=>vsprintf($this->editPetitionLink, 0), 'titlecolumn'=>'title', 'buttoncolumn'=>'edit'));
  $this->petitionListParams['listcolumns']['edit'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'edit', 'url_value'=>$this->editPetitionLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('editpetition'));
  $this->petitionListParams['listcolumns']['delete'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$this->deletePetitionLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('deletepetition'));
 }

$this->petitionListParams['listcolumns']['list'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'file', 'url_value'=>$this->listSignatureLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('listsignature'));

?>