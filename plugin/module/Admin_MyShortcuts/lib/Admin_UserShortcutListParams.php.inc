<?php
/**
 * @brief Admin_MyShortcuts module, shortcut list parameters.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.1
 * @date Creation: Jan 2019
 * @date Modification: Jul 2025
 * @copyright 2019 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

/* Build links */
$this->openShortcutLink = $this->get_adminLink(array('mode'=>'open_shortcut', 'shortcut_id'=>'%s'));
$this->editShortcutLink = $this->get_adminLink(array('mode'=>'edit_shortcut', 'shortcut_id'=>'%s'));
$this->deleteShortcutLink = 'javascript:adminengine_confirmRedirect(deleteShortcutUrl+%s, deleteShortcutMessage);';
$this->add_JSScript('var deleteShortcutMessage="'.string_html2Text($this->get_translation('deleteshortcutmessage')).'";');
$this->add_JSScript('var deleteShortcutUrl="'.$this->get_adminJSLink(array('mode'=>'delete_shortcut', 'shortcut_id'=>'')).'";');

/* Build main parameters */
$this->shortcutListParams = array('name'=>'shortcutList', 'useSession'=>true, 'object'=>&$this->shortcutItem);

/* Build head parameters */
$this->shortcutListParams['headselectors'] = array(
    'page'      => array('title'=>$camyks->get_translation('formitem_page'), 'itemtype'=>'page'),
);

/* Build sort parameters */
$this->shortcutListParams['sort'] = array('allowed'=>false, 'default'=>'id', 'defaultway'=>'asc');

/* Build column parameters */
$this->shortcutListParams['listcolumns'] = array(
    'empty'     => array('title'=>'', 'columntype'=>'specialtext', 'text'=>' ', 'class'=>'eTableIconCell'),
    'name'      => array('title'=>$camyks->get_translation('title'), 'columntype'=>'text'),
    '_date'     => array('title'=>$this->get_translation('adddate'), 'columntype'=>'date', 'mode'=>'numeric',),
    'view'      => array('title'=>'', 'columntype'=>'button', 'icon'=>'view', 'url_value'=>$this->openShortcutLink, 'url_title'=>$this->get_translation('openshortcut')),
    'edit'      => array('title'=>'', 'columntype'=>'button', 'icon'=>'edit', 'url_value'=>$this->editShortcutLink, 'url_title'=>$this->get_translation('editshortcut')),
    'delete'    => array('title'=>'', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$this->deleteShortcutLink, 'url_title'=>$this->get_translation('deleteshortcut')),
);
?>
