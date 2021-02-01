<?php
/**
 * @brief Admin_GenericFAQManager Module.
 * @details Plugin / Module engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Feb 2020
 * @date Modification: Jan 2021
 * @copyright 2020 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Class Admin_GenericFAQManager.
 */
final class Admin_GenericFAQManager extends Module {
    /**
     * @var object $questionItem
     * @brief Link to question object.
     */
    protected $questionItem = null;

    /**
     * @var object $questionList
     * @brief Link to question list.
     */
    protected $questionList = null;

    /**
     * @var object $familyItem
     * @brief Link to family object.
     */
    protected $familyItem = null;

    /**
     * @var object $familyList
     * @brief Link to family list.
     */
    protected $familyList = null;

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('Admin_GenericFAQManager', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'Generic';

        /* Override Module variables */
        $this->type = 'admin';
        $this->admin_type = 'content';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Load plugin libraries */
        $this->load_library('Admin_GenericFAQManagerQuestion');
        $this->load_library('Admin_GenericFAQManagerFamily');

        /* Initialise plugin libraries */
        $this->questionItem = new Admin_GenericFAQManagerQuestion(0, $this);
        $this->familyItem = new Admin_GenericFAQManagerFamily(0, $this);
    }

    /* Override Module methods */

    /**
     * Install module
     * @return boolean success
     */
    public function install() {
        return ($this->questionItem->install() and $this->familyItem->install()
            and parent::install());
    }

    /**
     * Check module installation.
     * @return boolean result
     */
    public function is_installed() {
        return $this->familyItem->is_installed();
    }

    /**
     * Build module permissions.
     * @return void
     */
    public function get_rights() {
        global $camyks;
        $this->rights[0] = array(
            'name'      => 'read',
            'title'     => $camyks->get_translation('read'),
            'default'   => true,
        );
        $this->rights[1] = array(
            'name'      => 'write',
            'title'     => $camyks->get_translation('write'),
            'default'   => false,
        );
    }

    /**
     * Initialise module object in admin mode.
     * @return void
     */
    public function init_admin() {
        global $camyks;

        /* check read rights */
        if ($this->check_right(0) === false)
            return $this->init_admin_accessDenied();

        /* check dependencies */
        if (!isset($camyks->inputs['TabBuilder']))
            return $this->init_admin_missingPlugin('Input', 'TabBuilder');
        if (!isset($camyks->inputs['AdminItemListViewer']))
            return $this->init_admin_missingPlugin('Input', 'AdminItemListViewer');

        /* Load mode to execute */
        $this->mode = (isset ($_REQUEST['mode']) ? $_REQUEST['mode'] : 'main');

        /* Execute mode */
        switch ($this->mode) {
            case 'edit_question':
                /* mode == edit_question */
                $this->init_admin_edit_question();
                break;
            case 'save_question':
                /* mode == save_question */
                $this->init_admin_save_question();
                break;
            case 'delete_question':
                /* mode == delete_question */
                $this->init_admin_delete_question();
                break;
            case 'moveUp_question':
                /* mode == moveUp_question */
                $this->init_admin_moveUp_question();
                break;
            case 'moveDown_question':
                /* mode == moveDown_question */
                $this->init_admin_moveDown_question();
                break;
            case 'edit_family':
                /* mode == edit_family */
                $this->init_admin_edit_family();
                break;
            case 'save_family':
                /* mode == save_family */
                $this->init_admin_save_family();
                    break;
            case 'delete_family':
                /* mode == delete_family */
                $this->init_admin_delete_family();
                break;
            case 'moveUp_family':
                /* mode == moveUp_family */
                $this->init_admin_moveUp_family();
                break;
            case 'moveDown_family':
                /* mode == moveDown_family */
                $this->init_admin_moveDown_family();
                break;
            case 'main':
            default:
                /* mode == main */
                $this->init_admin_main();
        }

        /* Execute generic module initialisation */
        parent::init_admin();
    }

    /* Specific admin mode methods */

    /**
     * Initialise module object in admin/main mode.
     * @return void
     */
    private function init_admin_main() {
        global $camyks;

        /* Load help */
        $this->get_help();

        /* Load tabs */
        $this->tabBuilder = $camyks->get_input('TabBuilder');
        $this->tabBuilder->add_tabs(array(
            array(
                'name'  => 'Questions',
                'title' => $this->get_translation('questions'),
            ),
            array(
                'name'  => 'Families',
                'title' => $this->get_translation('families'),
            ),
        ));
        if ($this->help != null)
             $this->tabBuilder->add_tab(array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help'),
            ));

        $this->tabBuilder->initialise(array('default'=>'Questions'));

        /* Load language to use with content */
        $this->language = $this->get_adminEditionLanguage();

        /* Build question tab */
        $this->load_library('Admin_GenericFAQManagerQuestionListParams');
        $this->questionList = $camyks->get_input('AdminItemListViewer');
        $this->questionList->set_params($this->questionListParams);
        $this->questionList->initialise();

        /* Build family tab */
        $this->load_library('Admin_GenericFAQManagerFamilyListParams');
        $this->familyList = new AdminItemListViewer('camyks');
        $this->familyList->set_params($this->familyListParams);
        $this->familyList->initialise();

        /* Load buttons */
        $this->buttons = array(
            array(
                'link'  => $camyks->get_adminLink(),
                'title' => $camyks->get_translation('back'),
            ),
        );
    }

    /**
     * Initialise module object in admin/edit_question mode.
     * @return void
     */
    private function init_admin_edit_question() {
        global $camyks;

        /* Check edit question permission */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* Load help */
        $this->get_help();

        /* Load tabs */
        $this->tabBuilder = $camyks->get_input('TabBuilder');
        $this->tabBuilder->add_tab(array(
            'name'  => 'Properties',
            'title' => $camyks->get_translation('properties'),
        ));
        foreach ($camyks->get_confValue('editing_languages') as $l) {
            $this->tabBuilder->add_tab(array(
                'name'  => $l,
                'title' => language_getIcon($l),
            ));
        }
        if ($this->help != null)
             $this->tabBuilder->add_tab(array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help'),
            ));
        $this->tabBuilder->initialise(array('default'=>'Properties'));

        /* Load question object */
        $this->questionItem->id = isset($_REQUEST['question_id']) ? (int)$_REQUEST['question_id']:0;
        $this->questionItem->get();
        $this->questionItem->get_fromItems();

        /* get form */
        $this->editform = new HTMLForm('edit_question', $this->get_adminlink(array('mode'=>'save_question')), 'POST');
        $this->editform->set_object($this->questionItem);
        $this->editform->add_hidden('question_id', $this->questionItem->id);

        /* get editor input */
        $this->input = $camyks->get_input('TinyMCEv3');
        $this->input->initialise();

        /* build title */
        $this->adminTitle = $this->title;
        $this->adminTitle .= $camyks->get_translation('formitem_separator');
        if ($this->questionItem->id == 0)
            $this->adminTitle .= $this->get_translation('questionnew');
        else
            $this->adminTitle .= $this->get_translation('questionid', $this->questionItem->id);

        /* Load buttons */
        $this->buttons = array(
            array(
                'link'  => $this->get_adminLink(),
                'title' => $camyks->get_translation('back'),
            ),
            array(
                'link'  => $this->editform->get_HTMLSubmitLink(),
                'title' => $camyks->get_translation('valid'),
            )
        );

        /* Update layout */
        $this->set_selectedLayout('admin_edit_question.html.inc');
    }

    /**
     * Initialise module object in admin/save_question mode.
     * @return void
     */
    private function init_admin_save_question() {
        global $camyks;

        /* Check user permissions */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* save object */
        $this->questionItem->id = isset($_REQUEST['question_id']) ? (int)$_REQUEST['question_id'] : 0;
        $this->questionItem->get_fromHeader();
        if ($this->questionItem->save()) {
            $this->text = $this->get_translation('question_saved');
        } else {
            $this->text = $this->get_translation('question_notsaved');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /**
     * Initialise module object in admin/delete_question mode.
     * @return void
     */
    private function init_admin_delete_question() {
        global $camyks;

        /* Check user permissions */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* Check question id */
        if (!isset($_REQUEST['question_id']))
            return $this->init_admin_main();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Delete object */
        $this->questionItem->id = (int)$_REQUEST['question_id'];
        if ($this->questionItem->delete()) {
            $this->text = $this->get_translation('question_deleted');
        } else {
            $this->text = $this->get_translation('question_notdeleted');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /**
     * Initialise module object in admin/moveUp_question mode.
     * @return void
     */
    private function init_admin_moveUp_question() {
        global $camyks;

        /* Check user permissions */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        if (!isset($_REQUEST['question_id']))
            return $this->init_admin_main();

        /* Try to moveup object */
        $this->questionItem->id = (int)$_REQUEST['question_id'];
        $this->questionItem->get();
        $this->questionItem->update_moveUp();

        /* Update layout */
        $this->selected_layout = '__';
        $this->set_redirect(0, $this->get_adminLink(array('openTab'=>'Questions')));
    }

    /**
     * Initialise module object in admin/moveDown_question mode.
     * @return void
     */
    private function init_admin_moveDown_question() {
        global $camyks;

        /* Check user permissions */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        if (!isset($_REQUEST['question_id']))
            return $this->init_admin_main();

        /* try to moveup object */
        $this->questionItem->id = (int)$_REQUEST['question_id'];
        $this->questionItem->get();
        $this->questionItem->update_moveDown();

        /* update layout */
        $this->selected_layout = '__';
        $this->set_redirect(0, $this->get_adminLink(array('openTab'=>'Questions')));
    }

    /**
     * Initialise module object in admin/edit_family mode.
     * @return void
     */
    private function init_admin_edit_family() {
        global $camyks;

        /* Check user permissions */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* Load help */
        $this->get_help();

        /* Load tabs */
        $this->tabBuilder = $camyks->get_input('TabBuilder');
        $this->tabBuilder->add_tab(array(
            'name'  => 'Properties',
            'title' => $camyks->get_translation('properties'),
        ));
        if ($this->help != null)
             $this->tabBuilder->add_tab(array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help'),
            ));
        $this->tabBuilder->initialise(array('default'=>'Properties'));

        /* Load family item */
        $this->familyItem->id = isset($_REQUEST['family_id']) ? (int)$_REQUEST['family_id'] : 0;
        $this->familyItem->get();
        $this->familyItem->get_fromItems();

        /* Load form */
        $this->editform = new HTMLForm('edit_family', $this->get_adminlink(array('mode'=>'save_family')), 'POST');
        $this->editform->set_object($this->familyItem);
        $this->editform->add_hidden('family_id', $this->familyItem->id);
        $this->editform->add_hidden('sortPosition');

        /* Build title */
        $this->adminTitle = $this->title;
        $this->adminTitle .= $camyks->get_translation('formitem_separator');
        if ($this->familyItem->id == 0)
            $this->adminTitle .= $this->get_translation('familynew');
        else
            $this->adminTitle .= $this->get_translation('familyid', $this->familyItem->id);

        /* Load buttons */
        $this->buttons = array(
            array(
                'link'  => $this->get_adminLink(array('openTab'=>'Families')),
                'title' => $camyks->get_translation('back')
            ),
            array(
                'link'  => $this->editform->get_HTMLSubmitLink(),
                'title' => $camyks->get_translation('valid'),
            )
        );

        /* Update layout */
        $this->set_selectedLayout('admin_edit_family.html.inc');
    }

    /**
     * Initialise module object in admin/save_family mode.
     * @return void
     */
    private function init_admin_save_family() {
        global $camyks;

        /* Check user permissions */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Save object */
        $this->familyItem->id = isset($_REQUEST['family_id']) ? (int)$_REQUEST['family_id'] : 0;
        $this->familyItem->get_fromHeader();
        if ($this->familyItem->save()) {
            $this->text = $this->get_translation('family_saved');
        } else {
            $this->text = $this->get_translation('family_notsaved');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('openTab'=>'Families')));
    }

    /**
     * Initialise module object in admin/delete_family mode.
     * @return void
     */
    private function init_admin_delete_family() {
        global $camyks;

        /* Check user permissions */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* Check family id */
        if (!isset($_REQUEST['family_id']))
            return $this->init_admin_main();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Delete object */
        $this->familyItem->id = (int)$_REQUEST['family_id'];
        if ($this->familyItem->delete()) {
            $this->text = $this->get_translation('family_deleted');
        } else {
            $this->text = $this->get_translation('family_notdeleted');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('openTab'=>'Families')));
    }

    /**
     * Initialise module object in admin/moveUp_family mode.
     * @return void
     */
    private function init_admin_moveUp_family() {
        global $camyks;

        /* Check user permissions */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        if (!isset($_REQUEST['family_id']))
            return $this->init_admin_main();

        /* Try to moveup object */
        $this->familyItem->id = (int)$_REQUEST['family_id'];
        $this->familyItem->update_moveUp();

        /* Update layout */
        $this->selected_layout = '__';
        $this->set_redirect(0, $this->get_adminLink(array('openTab'=>'Families')));
    }

    /**
     * Initialise module object in admin/moveDown_family mode.
     * @return void
     */
    private function init_admin_moveDown_family() {
        global $camyks;

        /* Check user permissions */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        if (!isset($_REQUEST['family_id']))
            return $this->init_admin_main();

        /* try to moveup object */
        $this->familyItem->id = (int)$_REQUEST['family_id'];
        $this->familyItem->update_moveDown();

        /* update layout */
        $this->selected_layout = '__';
        $this->set_redirect(0, $this->get_adminLink(array('openTab'=>'Families')));
    }

    /* Family related methods */

    /**
     * Return family list.
     * @param array $params
     * @return array
     */
    public function get_familyList($params=array()) {
        return $this->familyItem->get_list($params);
    }

    /**
     * Return family title list.
     * @param array $params
     * @return array
     */
    public function get_familyTitleList($params=array()) {
        return $this->familyItem->get_titleList($params);
    }

    /**
     * Return family list count.
     * @return integer
     */
    public function get_familyListCount() {
        /* Check familyList is defined */
        if (!isset($this->familyList) or !isset($this->familyList->objectCount))
            return false;

        /* Return object count */
        return $this->familyList->objectCount;
    }

    /* Question related methods */

    /**
     * Return question list.
     * @param array $params
     * @return array
     */
    public function get_questionList($params=array()) {
        return $this->questionItem->get_list($params);
    }

    /**
     * Return question list count.
     * @return integer
     */
    public function get_questionListCount() {
        /* Check questionList is defined */
        if (!isset($this->questionList) or !isset($this->questionList->objectCount))
            return false;

        /* Return object count */
        return $this->questionList->objectCount;
    }
}
?>
