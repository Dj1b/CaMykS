<?php
/**
 * @brief Admin_GenericEmailingManager module, email list parameters.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Dec 2012
 * @date Modification: Jul 2025
 * @copyright 2012 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

$this->deleteEmailLink = 'javascript:adminengine_confirmRedirect(deleteEmailUrl+%s, deleteEmailMessage);';
$this->markEmailLink = $this->get_adminLink(array('mode'=>'mark_email', 'email_id'=>'%s'));
$this->add_JSScript('var deleteEmailMessage="'.string_html2Text($this->get_translation('deleteemailmessage')).'";');
$this->add_JSScript('var deleteEmailUrl="'.$this->get_adminJSLink(array('mode'=>'delete_email', 'email_id'=>'')).'";');

/* Build main parameters */
$this->emailListParams = array('name'=>'emailList', 'useSession'=>true, 'object'=>&$this->emailItem);

/* Build head parameters */
$this->emailListParams['headselectors'] = array(
    'page'      => array('title'=>$camyks->get_translation('formitem_page'), 'itemtype'=>'page'),
    'search'    => array('title'=>$this->get_translation('formitem_search'), 'itemtype'=>'text', 'default'=>''),
);

/* Build hidden parameters */
$this->emailListParams['headhiddens'] = array('openTab'=>'emails');

/* Build sort parameters */
$this->emailListParams['sort'] = array('allowed'=>true, 'default'=>'id', 'defaultway'=>'asc');

/* Build column parameters */
$this->emailListParams['listcolumns'] = array(
    'status'            => array('title'=>' ', 'columntype'=>'method', 'method'=>'get_statusIcon', 'style'=>'width:12px;'),
    'title'             => array('title'=>$this->get_translation('contact'),'columntype'=>'text', 'maxlength'=>'64'),
    'sent_date'         => array('title'=>$this->get_translation('sending'),'columntype'=>'method', 'method'=>'get_sentDateValue'),
    'opened_date'       => array('title'=>$this->get_translation('opening'),'columntype'=>'method', 'method'=>'get_openedDateValue'),
    'firstclick_date'   => array('title'=>$this->get_translation('firstclick'),'columntype'=>'method', 'method'=>'get_firstClickDateValue'),
    'click_count'       => array('title'=>$this->get_translation('clicks'),'columntype'=>'text'),
);

/* Add delete email result button */
if ($this->check_right(4)) {
    $this->emailListParams['listcolumns']['delete'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$this->deleteEmailLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('deleteemail'));
    $this->emailListParams['listcolumns']['mark'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'minus', 'url_value'=>$this->markEmailLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('markemailasinvalid'));
}
?>
