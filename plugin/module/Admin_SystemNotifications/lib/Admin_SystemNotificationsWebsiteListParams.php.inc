<?php
/**
 * @brief Admin_SystemNotifications Module website list parameters
 * @details Plugin / Module Library
 * @file plugin/module/Admin_SystemNotifications/lib/Admin_SystemNotificationsWebsiteListParams.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jul 2017
 * @date Modification: May 2019
 * @copyright 2017 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

/* build lists */
$this->websitesStatusList = $this->get_websitesStatusList(true);

/* build links */
$this->editWebsiteLink = $this->get_adminLink(array('mode'=>'edit_website', 'website_id'=>'%s'));
$this->deleteWebsiteLink = 'javascript:adminengine_confirmRedirect(deleteWebsiteUrl+%s, deleteWebsiteMessage);';
$this->add_JSScript('var deleteWebsiteMessage="'.string_html2Text($this->get_translation('deletewebsitemessage')).'";');
$this->add_JSScript('var deleteWebsiteUrl="'.$this->get_adminJSLink(array('mode'=>'delete_website', 'website_id'=>'')).'";');

/* build main parameters */
$this->websiteListParams = array('name'=>'websiteList', 'useSession'=>true, 'object'=>&$this->websiteItem);

/* build head parameters */
$this->websiteListParams['headselectors'] = array(
    'page'      => array('title'=>$camyks->get_translation('formitem_page'), 'itemtype'=>'page'),
    'status'    => array('title'=>$camyks->get_translation('formitem_status'), 'itemtype'=>'select', 'values'=>$this->websitesStatusList, 'default'=>'-1'),
);

/* build hidden parameters */
$this->websiteListParams['headhiddens'] = array('openTab'=>'Websites');

/* build sort parameters */
$this->websiteListParams['sort'] = array('allowed'=>false, 'default'=>'name', 'defaultway'=>'asc');

/* build column parameters */
$this->websiteListParams['listcolumns'] = array(
    'status'    => array('title'=>' ', 'columntype'=>'boolean', 'mode'=>'pict', 'style'=>'width:12px;'),
    'cdate'     => array('title'=>$camyks->get_translation('date'), 'columntype'=>'date', 'mode'=>'numericwithhours'),
    'name'      => array('title'=>$this->get_translation('website'), 'columntype'=>'text', 'maxlength'=>'48'),
);

/* Check write permission */
if ($this->check_right(1)==true) {
    /* build master action parameters */
    $this->websiteListParams['listlinks'] = array('new'=>array('title'=>$this->get_translation('addnewwebsite'), 'icon'=>'plus', 'url_value'=>$this->get_adminLink(array('mode'=>'edit_website')), 'titlecolumn'=>'cdate', 'buttoncolumn'=>'edit'));

    /* build object action parameters */
    $this->websiteListParams['listcolumns']['edit'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'edit', 'url_value'=>$this->editWebsiteLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('editwebsite'));
    $this->websiteListParams['listcolumns']['delete'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$this->deleteWebsiteLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('deletewebsite'));
}
?>
