<?php
/**
 * @brief Admin_GenericContactFormManager module, subject list parameters.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: Nov 2010
 * @date Modification: Oct 2026
 * @copyright 2010 - 2026 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

/* Build links */
$newSubjectLink = $camyks->get_adminLink($this->name, array('mode'=>'edit_subject', 'subject_id'=>0));
$editSubjectLink = $camyks->get_adminLink($this->name, array('mode'=>'edit_subject', 'subject_id'=>'%s'));
$viewSubjectLink = $camyks->get_adminLink($this->name, array('mode'=>'view_subject', 'subject_id'=>'%s'));
$deleteSubjectLink = 'javascript:adminengine_confirmRedirect(deleteSubjectUrl+%s, deleteSubjectSubject);';
$this->add_JSScript('var deleteSubjectSubject="'.string_html2Text($this->get_translation('deletesubjectsubject')).'";');
$this->add_JSScript('var deleteSubjectUrl="'.$camyks->get_adminJSLink($this->name, array('mode'=>'delete_subject', 'subject_id'=>'')).'";');
$listSubjectLink = $camyks->get_adminLink($this->name, array('mode'=>'list_registration', 'subject_id'=>'%s'));

/* Build main parameters */
$this->subjectListParams = array('name'=>'subjectList', 'useSession'=>true, 'object'=>&$this->subjectItem, 'listlinks'=>array());

/* Build head parameters */
$this->subjectListParams['headselectors'] = array(
    'page'      => array('title'=>$this->get_translation('itempage'), 'itemtype'=>'page'),
    'status'    => array('title'=>$camyks->get_translation('formitem_status'), 'itemtype'=>'select', 'values'=>$this->get_subjectsStatusList(true), 'default'=>-1),
);

/* Build sort parameters */
$this->subjectListParams['sort'] = array('allowed'=>false, 'default'=>'edate', 'defaultway'=>'desc');

/* Build column parameters */
$this->subjectListParams['listcolumns'] = array(
    'status'    => array('title'=>'', 'columntype'=>'list', 'values'=>$this->get_subjectStatusIconList(), 'style'=>'width:20px;'),
    'edate'     => array('title'=>$this->get_translation('header_date'), 'columntype'=>'date', 'mode'=>'shortwithhours', 'style'=>'width:100px;'),
    'author'    => array('title'=>$this->get_translation('header_author'), 'columntype'=>'text'),
    'view'      => array('title'=>'', 'columntype'=>'button', 'icon'=>'view', 'url_value'=>$viewSubjectLink, 'url_title'=>$this->get_translation('viewsubject'), 'style'=>'width:12px;'),
);

/* add right's dependent columns and link lines */
if ($this->check_right(1)===true) {
    $this->subjectListParams['listcolumns']['edit'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'edit', 'url_value'=>$editSubjectLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('editsubject'));
    $this->subjectListParams['listcolumns']['delete'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$deleteSubjectLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('deletesubject'));
    $this->subjectListParams['listlinks']['new'] = array('title'=>$this->get_translation('addnewsubject'), 'icon'=>'plus', 'url_value'=>$newSubjectLink, 'titlecolumn'=>'edate', 'buttoncolumn'=>'edit');
}

?>
