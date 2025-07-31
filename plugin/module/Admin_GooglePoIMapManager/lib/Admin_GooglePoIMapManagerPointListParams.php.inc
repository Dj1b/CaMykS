<?php
/**
 * @brief Admin_GooglePoIMapManager module, point list parameters.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Jun 2010
 * @date Modification: Jul 2025
 * @copyright 2010 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

/* Build lists */
$this->pointStatusList = $this->get_pointsStatusList(true);

/* Build links */
$this->editPointLink = $this->get_adminLink(array('mode'=>'edit_point', 'point_id'=>'%s'));
$this->deletePointLink = 'javascript:adminengine_confirmRedirect(deletePointUrl+%s, deletePointMessage);';
$this->add_JSScript('var deletePointMessage="'.string_html2Text($this->get_translation('deletepointmessage')).'";');
$this->add_JSScript('var deletePointUrl="'.$this->get_adminJSLink(array('mode'=>'delete_point', 'point_id'=>'')).'";');

/* Build main parameters */
$this->pointListParams = array('name'=>'pointList', 'useSession'=>true, 'object'=>&$this->pointItem, 'language'=>$this->language);

/* Build head parameters */
$this->pointListParams['headselectors'] = array(
    'page'      => array('title'=>$camyks->get_translation('formitem_page'), 'itemtype'=>'page'),
    'status'    => array('title'=>$camyks->get_translation('formitem_status'), 'itemtype'=>'select', 'values'=>$this->pointStatusList, 'default'=>'-1'),
);

/* Build sort parameters */
$this->pointListParams['sort'] = array('allowed'=>false, 'default'=>'id', 'defaultway'=>'asc');

$this->pointListParams['listcolumns'] = array(
    'status'    => array('title'=>' ', 'columntype'=>'boolean', 'mode'=>'pict', 'style'=>'width:12px;'),
    'title'     => array('title'=>$camyks->get_translation('title'), 'columntype'=>'text', 'maxlength'=>48),
);

if ($this->check_right(1)) {
    $this->pointListParams['listlinks'] = array('new'=>array('title'=>$this->get_translation('addnewpoint'), 'icon'=>'plus', 'url_value'=>vsprintf($this->editPointLink, array(0=>0)), 'titlecolumn'=>'title', 'buttoncolumn'=>'edit'));
    $this->pointListParams['listcolumns']['edit'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'edit', 'url_value'=>$this->editPointLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('editpoint'));
    $this->pointListParams['listcolumns']['delete'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$this->deletePointLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('deletepoint'));
}
?>
