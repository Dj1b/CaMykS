<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author	    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Library
 * Creation Date    : Sep 2010
 * Last Modif Date  : Sep 2010
 * 
 * Admin_GenericPetitionManager signature list parameters
 */
global $camyks;

/* load data */
$this->signatureStatusList = $this->get_signaturesStatusList(true);

/* build links */
$this->editSignatureLink = $this->get_adminLink(array('mode'=>'edit_signature', 'signature_id'=>'%s'));
$this->deleteSignatureLink = 'javascript:adminengine_confirmRedirect(deleteSignatureUrl+%s, deleteSignatureMessage);';
$this->add_JSScript('var deleteSignatureMessage="'.string_html2Text($this->get_translation('deletesignaturemessage')).'";');
$this->add_JSScript('var deleteSignatureUrl="'.$this->get_adminJSLink(array('mode'=>'delete_signature', 'signature_id'=>'')).'";');

/* build main parameters */
$this->signatureListParams = array('name'=>'signatureList', 'useSession'=>true, 'object'=>&$this->signatureItem);

/* build head hidden values */
$this->signatureListParams['headhiddens'] = array('petition_id'=>$this->petitionItem->id);

/* build head parameters */
$this->signatureListParams['headselectors'] = array('page'=> array('title'=>$camyks->get_translation('formitem_page'), 'itemtype'=>'page'),
						   'status'=> array('title'=>$camyks->get_translation('formitem_status'), 'itemtype'=>'select', 'values'=>$this->signatureStatusList, 'default'=>'-1'));

/* build sort parameters */
$this->signatureListParams['sort'] = array('allowed'=>true, 'default'=>'signdate', 'defaultway'=>'desc');

/* build column parameters */
//$this->signatureListParams['listlinks'] = array('new'=>array('title'=>$this->get_translation('addnewsignature'), 'icon'=>'plus', 'url_value'=>vsprintf($this->editSignatureLink, 0), 'titlecolumn'=>'title', 'buttoncolumn'=>'edit'));

$this->signatureListParams['listcolumns'] = array('status'=>array('title'=>' ', 'columntype'=>'boolean', 'mode'=>'pict', 'style'=>'width:12px;'),
						  'lastname'=>array('title'=>$this->get_translation('signatory'),'columntype'=>'specialtext', 'text'=>'%s %s', 'vars'=>array('firstname', 'lastname')),
						  'city'=>array('title'=>$this->get_translation('location'), 'columntype'=>'specialtext', 'text'=>'%s(%s)', 'vars'=>array('city', 'zipcode')),
						  'signdate'=>array('title'=>$camyks->get_translation('date'), 'columntype'=>'date', 'mode'=>'numericwithhour'),
						  'edit'=>array('title'=>' ', 'columntype'=>'button', 'icon'=>'edit', 'url_value'=>$this->editSignatureLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('editsignature')),
						  'delete'=>array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$this->deleteSignatureLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('deletesignature'), 'condition'=>'is_deletable'));
?>