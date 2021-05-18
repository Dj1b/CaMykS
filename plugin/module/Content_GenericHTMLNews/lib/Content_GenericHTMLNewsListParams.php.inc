<?php
/**
 * @brief Content_GenericHTMLNews Module news list parameters.
 * @details Plugin, Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Apr 2009
 * @date Modification: May 2021
 * @copyright 2009 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

/* Build links */
$this->editNewsLink = $this->get_adminLink(array('mode'=>'edit_item', 'news_id'=>'%s'));
$this->deleteNewsLink = 'javascript:adminengine_confirmRedirect(deleteNewsUrl+%s, deleteNewsMessage);';
$this->add_JSScript('var deleteNewsMessage="'.string_html2Text($this->get_translation('deletenewsmessage')).'";');
$this->add_JSScript('var deleteNewsUrl="'.$this->get_adminJSLink(array('mode'=>'delete_item', 'news_id'=>'')).'";');

/* Build main parameters */
$this->newsListParams = array('name'=>'newsList', 'useSession'=>true, 'object'=>&$this->newsitem);

/* Build head parameters */
$this->newsListParams['headselectors'] = array('page'=> array('title'=>$this->get_translation('itempage'), 'itemtype'=>'page'));

/* Build sort parameters */
$this->newsListParams['sort'] = array('allowed'=>true, 'default'=>'ndate', 'defaultway'=>'desc');

/* Build column parameters */
$this->newsListParams['listlinks'] = array('new'=>array('title'=>$this->get_translation('addnewnews'), 'icon'=>'plus', 'url_value'=>vsprintf($this->editNewsLink, 0), 'titlecolumn'=>'language', 'buttoncolumn'=>'edit'));

$this->newsListParams['listcolumns'] = array(
    'status'    => array('title'=>' ', 'columntype'=>'boolean', 'mode'=>'pict', 'style'=>'width:12px;'),
    'language'  => array('title'=>' ', 'columntype'=>'country', 'style'=>'width:20px;'),
    'author'    => array('title'=>$camyks->get_translation('author'), 'columntype'=>'text'),
    'ndate'     => array('title'=>$camyks->get_translation('date'), 'columntype'=>'date', 'mode'=>'shortwithhour', 'style'=>'width:140px;'),
    'title'     => array('title'=>$camyks->get_translation('title'),'columntype'=>'text'),
    'edit'      => array('title'=>' ', 'columntype'=>'button', 'icon'=>'edit', 'url_value'=>$this->editNewsLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('editnews')),
    'delete'    => array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$this->deleteNewsLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('deletenews')),
);
?>
