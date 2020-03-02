<?php
/**
 * @brief Admin_GenericFAQManager Module family list parameters.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Feb 2020
 * @date Modification: Feb 2020
 * @copyright 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

/* build lists */
$this->familyStatusList = $this->familyItem->get_multiStatusList(array('addAll'=>true));

/* build links */
$this->moveDownFamilyLink = $this->get_adminLink(array('mode'=>'moveDown_family', 'family_id'=>'%s'));
$this->moveUpFamilyLink = $this->get_adminLink(array('mode'=>'moveUp_family', 'family_id'=>'%s'));
$this->editFamilyLink = $this->get_adminLink(array('mode'=>'edit_family', 'family_id'=>'%s'));
$this->deleteFamilyLink = 'javascript:adminengine_confirmRedirect(deleteFamilyUrl+%s, deleteFamilyMessage);';
$this->add_JSScript('var deleteFamilyMessage="'.string_html2Text($this->get_translation('deletefamilymessage')).'";');
$this->add_JSScript('var deleteFamilyUrl="'.$this->get_adminJSLink(array('mode'=>'delete_family', 'family_id'=>'')).'";');

/* build main parameters */
$this->familyListParams = array('name'=>'familyList', 'useSession'=>true, 'object'=>&$this->familyItem, 'language'=>$this->language);

/* build head parameters */
$this->familyListParams['headselectors'] = array(
    'page'      => array('title'=>$camyks->get_translation('formitem_page'), 'itemtype'=>'page'),
    'status'    => array('title'=>$camyks->get_translation('formitem_status'), 'itemtype'=>'select', 'values'=>$this->familyStatusList, 'default'=>'-1'),
);

/* build sort parameters */
$this->familyListParams['sort'] = array('allowed'=>false, 'default'=>'sortPosition', 'defaultway'=>'asc');

/* build column parameters */
$this->familyListParams['listcolumns'] = array(
    'status'    => array('title'=>' ', 'columntype'=>'boolean', 'mode'=>'pict', 'style'=>'width:12px;'),
    'title'     => array('title'=>$camyks->get_translation('title'),'columntype'=>'text'),
);

if ($this->check_right(1)==true ) {
    $this->familyListParams['listlinks'] = array('new'=>array('title'=>$this->get_translation('addnewfamily'), 'icon'=>'plus', 'url_value'=>vsprintf($this->editFamilyLink, 0), 'titlecolumn'=>'title', 'buttoncolumn'=>'edit'));
    $this->familyListParams['listcolumns']['movedown'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'down', 'url_value'=>$this->moveDownFamilyLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('movedownfamily'), 'condition'=>'is_notLast');
    $this->familyListParams['listcolumns']['moveup'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'up', 'url_value'=>$this->moveUpFamilyLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('moveupfamily'), 'condition'=>'is_notFirst');
    $this->familyListParams['listcolumns']['edit'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'edit', 'url_value'=>$this->editFamilyLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('editfamily'));
    $this->familyListParams['listcolumns']['delete'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$this->deleteFamilyLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('deletefamily'));
}
?>
