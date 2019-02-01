<?php
/**
 * @brief Admin_MyShortcuts Module shortcut list parameters.
 * @details Plugin, Module Library
 * @file plugin/module/Admin_MyShortcuts/lib/Admin_UserShortcutListParams.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jan 2019
 * @date Modification: Jan 2019
 * @copyright  2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

/* build links */
$this->openShortcutLink = $this->get_adminLink(array('mode'=>'open_shortcut', 'shortcut_id'=>'%s'));
$this->editShortcutLink = $this->get_adminLink(array('mode'=>'edit_shortcut', 'shortcut_id'=>'%s'));
$this->deleteShortcutLink = 'javascript:adminengine_confirmRedirect(deleteShortcutUrl+%s, deleteShortcutMessage);';
$this->add_JSScript('var deleteShortcutMessage="'.string_html2Text($this->get_translation('deleteshortcutmessage')).'";');
$this->add_JSScript('var deleteShortcutUrl="'.$this->get_adminJSLink(array('mode'=>'delete_shortcut', 'shortcut_id'=>'')).'";');

/* build main parameters */
$this->shortcutListParams = array('name'=>'shortcutList', 'useSession'=>true, 'object'=>&$this->shortcutItem);

/* build head parameters */
$this->shortcutListParams['headselectors'] = array(
    'page'      => array('title'=>$camyks->get_translation('formitem_page'), 'itemtype'=>'page'),
);

/* build sort parameters */
$this->shortcutListParams['sort'] = array('allowed'=>false, 'default'=>'id', 'defaultway'=>'asc');

/* build column parameters */
$this->shortcutListParams['listcolumns'] = array(
    'empty'     => array('title'=>'', 'columntype'=>'specialtext', 'text'=>' ', 'class'=>'eTableIconCell'),
    'name'      => array('title'=>$camyks->get_translation('title'), 'columntype'=>'text'),
    '_date'     => array('title'=>$this->get_translation('adddate'), 'columntype'=>'date', 'mode'=>'numeric',),
    'view'      => array('title'=>'', 'columntype'=>'button', 'icon'=>'view', 'url_value'=>$this->openShortcutLink, 'url_title'=>$this->get_translation('openshortcut')),
    'edit'      => array('title'=>'', 'columntype'=>'button', 'icon'=>'edit', 'url_value'=>$this->editShortcutLink, 'url_title'=>$this->get_translation('editshortcut')),
    'delete'    => array('title'=>'', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$this->deleteShortcutLink, 'url_title'=>$this->get_translation('deleteshortcut')),
);
?>
