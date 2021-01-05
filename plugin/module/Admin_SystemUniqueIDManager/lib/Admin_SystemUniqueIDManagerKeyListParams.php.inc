<?php
/**
 * @brief Admin_SystemUniqueIDManager Module key list parameters
 * @details Plugin, Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jan 2015
 * @date Modification: Jan 2021
 * @copyright 2015 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

/* build lists */
$this->keysStatusList = $this->get_keysStatusList(true);

/* build links */
$this->deleteKeyLink = 'javascript:adminengine_confirmRedirect(deleteKeyUrl+%s, deleteKeyMessage);';
$this->add_JSScript('var deleteKeyMessage="'.string_html2Text($this->get_translation('deletekeymessage')).'";');
$this->add_JSScript('var deleteKeyUrl="'.$this->get_adminJSLink(array('mode'=>'delete_key', 'key_id'=>'')).'";');

/* build main parameters */
$this->keyListParams = array('name'=>'uniqueIDList', 'useSession'=>true, 'object'=>&$this->keyItem);

/* build head parameters */
$this->keyListParams['headselectors'] = array(
    'page'		=> array('title'=>$camyks->get_translation('formitem_page'), 'itemtype'=>'page'),
	'status'	=> array('title'=>$camyks->get_translation('formitem_status'), 'itemtype'=>'select', 'values'=>$this->keysStatusList, 'default'=>'-1'),
);

/* build sort parameters */
$this->keyListParams['sort'] = array('allowed'=>true, 'default'=>'cdate', 'defaultway'=>'desc');

/* build master action parameters */
if ($this->check_right(1))
  $this->keyListParams['listlinks'] = array('new'=>array('title'=>$this->get_translation('addnewuniqueid'), 'icon'=>'plus', 'url_value'=>$this->get_adminLink(array('mode'=>'create_key')), 'titlecolumn'=>'cdate', 'buttoncolumn'=>'delete'));

/* build column parameters */
$this->keyListParams['listcolumns'] = array(
    'status'	=> array('title'=>' ', 'columntype'=>'boolean', 'mode'=>'pict', 'style'=>'width:12px;'),
    'cdate'		=> array('title'=>$camyks->get_translation('date'), 'columntype'=>'date', 'mode'=>'numericwithhours'),
	'uniqueID'	=> array('title'=>$this->get_translation('key'), 'columntype'=>'text', 'maxlength'=>'48'),
	'plugin'	=> array('title'=>$this->get_translation('plugin'), 'columntype'=>'text'),
	'object'	=> array('title'=>$this->get_translation('object'), 'columntype'=>'text', 'maxlength'=>96),
);

/* build object action parameters */
if ($this->check_right(1))
    $this->keyListParams['listcolumns']['delete'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$this->deleteKeyLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('deletekey'));
?>