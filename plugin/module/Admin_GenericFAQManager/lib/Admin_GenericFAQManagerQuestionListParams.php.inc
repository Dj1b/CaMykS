<?php
/**
 * @brief Admin_GenericFAQManager module, question list parameters.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Feb 2020
 * @date Modification: Oct 2026
 * @copyright 2020 - 2026 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

/* Build lists */
$questionsStatusList = $this->questionItem->get_multiStatusList(array('addAll'=>true));
$familyTitleList = $this->get_familyTitleList(array('addAll'=>true));

/* Build links */
$moveDownQuestionLink = $this->get_adminLink(array('mode'=>'moveDown_question', 'question_id'=>'%s'));
$moveUpQuestionLink = $this->get_adminLink(array('mode'=>'moveUp_question', 'question_id'=>'%s'));
$newQuestionLink = $this->get_adminLink(array('mode'=>'edit_question', 'question_id'=>0));
$editQuestionLink = $this->get_adminLink(array('mode'=>'edit_question', 'question_id'=>'%s'));
$deleteQuestionLink = 'javascript:adminengine_confirmRedirect(deleteQuestionUrl+%s, deleteQuestionMessage);';
$this->add_JSScript('var deleteQuestionMessage="'.string_html2Text($this->get_translation('deletequestionmessage')).'";');
$this->add_JSScript('var deleteQuestionUrl="'.$this->get_adminJSLink(array('mode'=>'delete_question', 'question_id'=>'')).'";');

/* Build main parameters */
$this->questionListParams = array('name'=>'questionList', 'useSession'=>true, 'object'=>&$this->questionItem, 'language'=>$this->language);

/* Build head parameters */
$this->questionListParams['headselectors'] = array(
    'page'      => array('title'=>$camyks->get_translation('formitem_page'), 'itemtype'=>'page'),
    'status'    => array('title'=>$camyks->get_translation('formitem_status'), 'itemtype'=>'select', 'values'=>$questionsStatusList, 'default'=>'-1'),
    'family'    => array('title'=>$this->get_translation('formitem_family'), 'itemtype'=>'select', 'values'=>$familyTitleList, 'default'=>'-1'),
);

/* Build sort parameters */
$this->questionListParams['sort'] = array('allowed'=>false, 'default'=>array('family'=>'asc', 'sortPosition'=>'asc'), 'defaultway'=>'');

/* Build column parameters */
$this->questionListParams['listcolumns'] = array(
    'status'    => array('title'=>' ', 'columntype'=>'boolean', 'mode'=>'pict'),
    'title'     => array('title'=>$camyks->get_translation('title'),'columntype'=>'text', 'maxlength'=>64),
    'family'    => array('title'=>$this->get_translation('family'),'columntype'=>'list', 'values'=>$familyTitleList),
);

if ($this->check_right(1)) {
    $this->questionListParams['listlinks'] = array('new'=>array('title'=>$this->get_translation('addnewquestion'), 'icon'=>'plus', 'url_value'=>$newQuestionLink, 'titlecolumn'=>'title', 'buttoncolumn'=>'edit'));
    $this->questionListParams['listcolumns']['movedown'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'down', 'url_value'=>$moveDownQuestionLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('movedownquestion'), 'condition'=>'is_notLast');
    $this->questionListParams['listcolumns']['moveup'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'up', 'url_value'=>$moveUpQuestionLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('moveupquestion'), 'condition'=>'is_notFirst');
    $this->questionListParams['listcolumns']['edit'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'edit', 'url_value'=>$editQuestionLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('editquestion'));
    $this->questionListParams['listcolumns']['delete'] = array('title'=>' ', 'columntype'=>'button', 'icon'=>'cross', 'url_value'=>$deleteQuestionLink, 'style'=>'width:12px;', 'url_title'=>$this->get_translation('deletequestion'));
}
?>
