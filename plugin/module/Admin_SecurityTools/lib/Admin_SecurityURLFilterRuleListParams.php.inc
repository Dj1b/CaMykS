<?php
/**
 * @brief Admin_SecurityTools Module URL Filter list parameters library.
 * @details Plugin / Module Library
 * @file plugin/module/Admin_SecurityTools/lib/Admin_SecurityURLFilterRuleListParams.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jan 2019
 * @date Modification: Jan 2019
 * @copyright 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

/* build lists */
$this->urlFilterRulesStatusList = $this->get_urlFilterRulesStatusList(array('addAll'=>true));

/* build links */
$this->newURLFilterRuleLink = $this->get_adminLink(array('mode'=>'edit_urlFilterRule', 'ruleId'=>0));
$this->editURLFilterRuleLink = $this->get_adminLink(array('mode'=>'edit_urlFilterRule', 'ruleId'=>'%s'));
$this->deleteURLFilterRuleLink = 'javascript:adminengine_confirmRedirect(deleteURLFilterRuleUrl+%s, deleteURLFilterRuleMessage);';
$this->add_JSScript('var deleteURLFilterRuleMessage="'.string_html2Text($this->get_translation('deletefilteriprule')).'";');
$this->add_JSScript('var deleteURLFilterRuleUrl="'.$this->get_adminJSLink(array('mode'=>'delete_urlFilterRule', 'ruleId'=>'')).'";');

/* build main parameters */
$this->urlFilterRuleListParams = array('name'=>'urlFilterRuleList', 'useSession'=>true, 'object'=>&$this->urlFilterRule);

/* build head parameters */
$this->urlFilterRuleListParams['headselectors'] = array(
    'page'      => array('title'=>$camyks->get_translation('formitem_page'), 'itemtype'=>'page'),
    'status'    => array('title'=>$camyks->get_translation('formitem_status'), 'itemtype'=>'select', 'values'=>$this->urlFilterRulesStatusList, 'default'=>'-1'),
);

/* build hidden parameters */
$this->urlFilterRuleListParams['headhiddens'] = array('openTab'=>'URLFilter');

/* build sort parameters */
$this->urlFilterRuleListParams['sort'] = array('allowed'=>false, 'default'=>'ipaddress', 'defaultway'=>'asc');

/* build column parameters */
$this->urlFilterRuleListParams['listcolumns'] = array(
    'status'        => array('title'=>' ', 'columntype'=>'boolean', 'mode'=>'pict', 'style'=>'width:12px;'),
    'pattern'       => array('title'=>$this->get_translation('pattern'), 'columntype'=>'text'),
    'comment'       => array('title'=>$this->get_translation('comment'), 'columntype'=>'text', 'maxlength'=>'48'),
);

/* add action for write rights */
if ($this->check_right(1)==true) {

    /* build master action parameters */
    $this->urlFilterRuleListParams['listlinks'] = array('new'=>array('title'=>$this->get_translation('addnewurlfilterrule'), 'icon'=>'plus', 'url_value'=>$this->newURLFilterRuleLink, 'titlecolumn'=>'pattern', 'buttoncolumn'=>'edit'));

    /* build object action parameters */
    $this->urlFilterRuleListParams['listcolumns']['edit'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'edit', 'url_value'=>$this->editURLFilterRuleLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('urlfilter_editrule'));
    $this->urlFilterRuleListParams['listcolumns']['delete'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$this->deleteURLFilterRuleLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('urlfilter_deleterule'));
}

?>
