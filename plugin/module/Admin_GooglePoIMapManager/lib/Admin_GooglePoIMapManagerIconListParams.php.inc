<?php
/**
 * @brief Admin_GooglePoIMapManager Module icon list parameters.
 * @details Plugin, Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Mar 2010
 * @date Modification: Feb 2021
 * @copyright 2010 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

/* Build links */
$this->editIconLink = $this->get_adminLink(array('mode'=>'edit_icon', 'icon_id'=>'%s'));
$this->deleteIconLink = 'javascript:adminengine_confirmRedirect(deleteIconUrl+%s, deleteIconMessage);';
$this->add_JSScript('var deleteIconMessage="'.string_html2Text($this->get_translation('deleteiconmessage')).'";');
$this->add_JSScript('var deleteIconUrl="'.$this->get_adminJSLink(array('mode'=>'delete_icon', 'icon_id'=>'')).'";');

/* Build main parameters */
$this->iconListParams = array('name'=>'iconList', 'useSession'=>true, 'object'=>&$this->iconItem, 'language'=>$this->language);

/* Build head parameters */
$this->iconListParams['headselectors'] = array('page'=> array('title'=>$camyks->get_translation('formitem_page'), 'itemtype'=>'page'));

/* Build sort parameters */
$this->iconListParams['sort'] = array('allowed'=>false, 'default'=>'id', 'defaultway'=>'asc');

$this->iconListParams['listcolumns'] = array(
    'space' => array('title'=>' ', 'columntype'=>'special_text', 'text'=>' ', 'style'=>'width:12px;'),
    'name'  => array('title'=>$camyks->get_translation('name'), 'columntype'=>'text'),
);

if ($this->check_right(2)) {
    $this->iconListParams['listlinks'] = array('new'=>array('title'=>$this->get_translation('addnewicon'), 'icon'=>'plus', 'url_value'=>vsprintf($this->editIconLink, 0), 'titlecolumn'=>'name', 'buttoncolumn'=>'edit'));
    $this->iconListParams['listcolumns']['edit'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'edit', 'url_value'=>$this->editIconLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('editicon'));
    $this->iconListParams['listcolumns']['delete'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$this->deleteIconLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('deleteicon'), 'condition'=>'is_deletable');
}
?>
