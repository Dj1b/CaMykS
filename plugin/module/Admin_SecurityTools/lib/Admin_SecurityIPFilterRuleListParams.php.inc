<?php
/**
 * @brief Admin_SecurityTools Module IPFilter list parameters library.
 * @details Plugin / Module Library
 * @file plugin/module/Admin_SecurityTools/lib/Admin_SecurityIPFilterRuleListParams.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Nov 2018
 * @date Modification: Nov 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

/* build lists */
$this->ipFilterRulesStatusList = $this->get_ipFilterRulesStatusList(array('addAll'=>true));
$this->ipFilterRulePermissionIconList = $this->get_ipFilterRulePermissionIconList();
$this->ipFilterRuleSiteModeList = $this->get_ipFilterRulePSideModeList();

/* build links */
$this->newIPFilterRuleLink = $this->get_adminLink(array('mode'=>'edit_ipfilter', 'ruleid'=>0));
$this->editIPFilterRuleLink = $this->get_adminLink(array('mode'=>'edit_ipfilter', 'ruleid'=>'%s'));
$this->deleteIPFilterRuleLink = 'javascript:adminengine_confirmRedirect(deleteIPFilterRuleUrl+%s, deleteIPFilterRuleMessage);';
$this->add_JSScript('var deleteIPFilterRuleMessage="'.string_html2Text($this->get_translation('deletefilteriprule')).'";');
$this->add_JSScript('var deleteIPFilterRuleUrl="'.$this->get_adminJSLink(array('mode'=>'delete_ipfilter', 'ruleid'=>'')).'";');

/* build main parameters */
$this->ipFilterRuleListParams = array('name'=>'ipFilterRuleList', 'useSession'=>true, 'object'=>&$this->ipfilterrule);

/* build head parameters */
$this->ipFilterRuleListParams['headselectors'] = array(
    'page'      => array('title'=>$camyks->get_translation('formitem_page'), 'itemtype'=>'page'),
    'status'    => array('title'=>$camyks->get_translation('formitem_status'), 'itemtype'=>'select', 'values'=>$this->ipFilterRulesStatusList, 'default'=>'-1'),
);

/* build hidden parameters */
$this->ipFilterRuleListParams['headhiddens'] = array('openTab'=>'IPFilter');

/* build sort parameters */
$this->ipFilterRuleListParams['sort'] = array('allowed'=>false, 'default'=>'ipaddress', 'defaultway'=>'asc');

/* build column parameters */
$this->ipFilterRuleListParams['listcolumns'] = array(
    'active'        => array('title'=>' ', 'columntype'=>'boolean', 'mode'=>'pict', 'style'=>'width:12px;'),
    'permission'    => array('title'=>' ', 'columntype'=>'list', 'values'=> $this->ipFilterRulePermissionIconList, 'class'=>'eTableIconCell'),
    'ipaddress'     => array('title'=>$this->get_translation('ipaddress'), 'columntype'=>'text'),
    'sitemode'      => array('title'=>$this->get_translation('sitemode'), 'columntype'=>'list', 'values'=>$this->get_ipFilterRulePSideModeList()),
    'comment'       => array('title'=>$this->get_translation('comment'), 'columntype'=>'text', 'maxlength'=>'48'),
);

/* add action for write rights */
if ($this->check_right(1)==true) {

    /* build master action parameters */
    $this->ipFilterRuleListParams['listlinks'] = array('new'=>array('title'=>$this->get_translation('addnewipFilterRule'), 'icon'=>'plus', 'url_value'=>$this->newIPFilterRuleLink, 'titlecolumn'=>'permission', 'buttoncolumn'=>'edit'));

    /* build object action parameters */
    $this->ipFilterRuleListParams['listcolumns']['edit'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'edit', 'url_value'=>$this->editIPFilterRuleLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('ipfilter_editrule'));
    $this->ipFilterRuleListParams['listcolumns']['delete'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$this->deleteIPFilterRuleLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('ipfilter_deleterule'));
}

?>
