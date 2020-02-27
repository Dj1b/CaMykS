<?php
/**
 * @brief Admin_GenericGlossaryManager Module
 * <br /> Manage a glossary of definitions grouped by categories.
 * @details Plugin, Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: May 2010
 * @date Modification: Feb 2020
 * @copyright 2010 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GenericGlossaryManager class.
 */
final class Admin_GenericGlossaryManager extends Module {
    /**
     * @var Object $definitionItem
     * @brief Definition object.
     */
    public $definitionItem;

    /**
     * @var mixed $definitionList
     * @brief Definition List.
     */
    public $definitionList;

    /**
     * @var Object $categoryItem
     * @brief Category object.
     */
    public $categoryItem;

    /**
     * @var mixed $categoryList
     * @brief Category list.
     */
    public $categoryList;

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('Admin_GenericGlossaryManager', $path_type);

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
        $this->load_library('Admin_GenericGlossaryManagerDefinition');
        $this->load_library('Admin_GenericGlossaryManagerCategory');

        /* Initialise plugin libraries */
        $this->definitionItem = new Admin_GenericGlossaryManagerDefinition(0, $this);
        $this->categoryItem = new Admin_GenericGlossaryManagerCategory(0, $this);
    }

    /* Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return ($this->definitionItem->install()
            and $this->categoryItem->install() and parent::install());
    }

    /**
     * Unintall module.
     * @return boolean success
     */
    public function uninstall() {
        return parent::uninstall();
    }

    /**
     * Check module installation.
     * @return boolean result
     */
    public function is_installed() {
        return $this->definitionItem->is_installed();
    }

    /**
     * Return module permissions.
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
            'name'      => 'category',
            'title'     => $this->get_translation('rights_category'),
            'default'   => false,
        );
        $this->rights[2] = array(
            'name'      => 'definition',
            'title'     => $this->get_translation('rights_definition'),
            'default'   => false,
        );
    }

    /**
     * Initialise module object in admin mode.
     * @return void
     */
    public function init_admin() {
        global $camyks;

        /* Check user permission */
        if ($this->check_right(0) === false)
            return $this->init_admin_accessDenied();

        /* Check dependencies */
        if (!isset($camyks->inputs['TabBuilder']))
            return $this->init_admin_missingPlugin('Input', 'TabBuilder');
        if (!isset($camyks->inputs['AdminItemListViewer']))
            return $this->init_admin_missingPlugin('Input', 'AdminItemListViewer');
        if (!isset($camyks->inputs['TinyMCEv3']))
            return $this->init_admin_missingPlugin('Input', 'TinyMCEv3');

        /* Load action to execute */
        $this->mode = (isset($_REQUEST['mode']) ? $_REQUEST['mode'] : 'main');

        /* Execute action */
        switch ($this->mode) {
            case 'edit_category':
                /* mode == edit_category */
                $this->init_admin_edit_category();
                break;
            case 'save_category':
                /* mode == save_category */
                $this->init_admin_save_category();
                break;
            case 'delete_category':
                /* mode == delete_category */
                $this->init_admin_delete_category();
                break;
            case 'edit_definition':
                /* mode == edit_definition */
                $this->init_admin_edit_definition();
                break;
            case 'save_definition':
                /* mode == save_definition */
                $this->init_admin_save_definition();
                break;
            case 'delete_definition':
                /* mode == delete_definition */
                $this->init_admin_delete_definition();
                break;
            case 'main':
            default:
                /* mode == main */
                $this->init_admin_main();
        }

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

        /* Load language to use with content */
        $this->language = $this->get_adminEditionLanguage();

        /* Build definitions tab */
        $this->load_library('Admin_GenericGlossaryManagerDefinitionListParams');
        $this->listDefinition = new AdminItemListViewer('camyks');
        $this->listDefinition->set_params($this->definitionListParams);
        $this->listDefinition->initialise();

        /* Build categories tab */
        $this->load_library('Admin_GenericGlossaryManagerCategoryListParams');
        $this->listCategory = new AdminItemListViewer('camyks');
        $this->listCategory->set_params($this->categoryListParams);
        $this->listCategory->initialise();

        /* Load categories id */
        $categoryIDs = array_keys($this->listCategory->objectList);
        $cnts = $this->definitionItem->count_byCategories($categoryIDs);
        foreach ($this->listCategory->objectList as $id => $category)
            $this->listCategory->objectList[$id]->vars['definitions'] = isset($cnts[$id])?$cnts[$id]:0;

        /* Load tabs */
        $this->tabBuilder = $camyks->get_input('TabBuilder');

        /* Insert definitions tab */
        $this->tabBuilder->add_tab(array(
            'name'  => 'Definitions',
            'title' => $this->get_translation('tabdefinitions'),
        ));

        /* Insert categories tab */
        $this->tabBuilder->add_tab(array(
            'name'  => 'Categories',
            'title' => $this->get_translation('tabcategories'),
        ));

        /* Insert help tab */
        if (!is_null($this->help))
            $this->tabBuilder(array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help'),
            ));

        /* Initialise tabs */
        $this->tabBuilder->initialise(array('default'=>'Definitions'));

        /* Build button list */
        $this->buttons = array(array(
            'link'  => $camyks->get_adminLink(),
            'title' => $camyks->get_translation('back'),
        ));
    }

    /**
     * Initialise module object in admin/edit_definition mode.
     * @return void
     */
    private function init_admin_edit_definition() {
        global $camyks;

        /* Check user permission */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* Load language to use with content */
        $this->language = $this->get_adminEditionLanguage();
        $this->lgs = $camyks->get_confValue('editing_languages');

        /* get definition item */
        $this->definitionItem->id = isset($_REQUEST['definition_id']) ? (int)$_REQUEST['definition_id'] : 0;
        $this->definitionItem->get();
        $this->definitionItem->get_fromItems();

        /* Load data */
        $this->categoryList = $this->get_categoryTitleList();

        /* Build form */
        $this->editform = new HTMLForm('edit_definition', $this->get_adminlink(array('mode'=>'save_definition')), 'POST');
        $this->editform->add_hidden('definition_id', $this->definitionItem->id);
        $this->editform->set_object($this->definitionItem);

        /* Load tabs */
        $this->tabBuilder = $camyks->get_input('TabBuilder');

        /* Insert tabs */
        $this->tabBuilder->add_tab(array(
            'name'  => 'Properties',
            'title' => $this->get_translation('tabproperties'),
        ));
        if (count($this->lgs) == 1)
            $this->tabBuilder->add_tab(array(
                'name'  => $this->lgs[0],
                'title' => $this->get_translation('tabcontent'),
            ));
        else {
            foreach ($this->lgs as $l)
                $this->tabBuilder->add_tab(array(
                    'name'  => $l,
                    'title' => language_getIcon($l),
                ));
        }

        /* Insert help tab */
        if ($this->help != null)
            $this->tabBuilder->add_tab(array(
                'name'=>'help',
                'title'=>$camyks->get_translation('help'),
            ));

        /* Initialise tabs */
        $this->tabBuilder->initialise(array('default'=>'Definitions'));

        /* Load editor */
        $this->editor = &$camyks->inputs['TinyMCEv3'];
        $this->editor->initialise();

        /* Build interface title */
        $this->adminTitle = $this->title;
        $this->adminTitle .= $camyks->get_translation('formitem_separator');
        if ($this->definitionItem->id == 0)
            $this->adminTitle .= $this->get_translation('definitionnew');
        else
            $this->adminTitle .= $this->get_translation('definitionid', $this->definitionItem->id);

        /* Build button list */
        $this->buttons = array(
            array(
                'link'=>$this->get_adminLink(),
                'title'=>$camyks->get_translation('back'),
            ),
            array(
                'link'=>$this->editform->get_HTMLSubmitLink(),
                'title'=>$camyks->get_translation('valid'),
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('admin_edit_definition.html.inc');
    }

    /**
     * Initialise module object in admin/save_definition mode.
     * @return void
     */
    private function init_admin_save_definition() {
        global $camyks;

        /* Check user permission */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Save definition */
        $this->definitionItem->id = isset($_REQUEST['definition_id']) ? (int)$_REQUEST['definition_id'] : 0;
        $this->definitionItem->get_fromHeader();
        if ($this->definitionItem->save())
            $this->text = $this->get_translation('definition_saved');
        else
            $this->text = $this->get_translation('definition_notsaved');

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /**
     * Initialise module object in admin/delete_definition mode.
     * @return void
     */
    private function init_admin_delete_definition() {
        global $camyks;

        /* Check user rights */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* Check definition id */
        if (!isset($_REQUEST['definition_id']))
            return $this->init_admin_main();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Delete definition */
        $this->definitionItem->id = (int)$_REQUEST['definition_id'];
        if ($this->definitionItem->delete())
            $this->text = $this->get_translation('definition_deleted');
        else
            $this->text = $this->get_translation('definition_notdeleted');

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /**
     * Initialise module object in admin/edit_category mode
     * @return void
     */
    private function init_admin_edit_category() {
        global $camyks;

        /* Check user permission */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* Load category object */
        $this->categoryItem->id = isset($_REQUEST['category_id']) ? (int)$_REQUEST['category_id'] : 0;
        $this->categoryItem->get();
        $this->categoryItem->get_fromItems();

        /* Build form */
        $this->editform = new HTMLForm('edit_category', $this->get_adminlink(array('mode'=>'save_category')), 'POST');
        $this->editform->set_object($this->categoryItem);
        $this->editform->add_hidden('category_id', $this->categoryItem->id);

        /* build button list */
        $this->buttons = array(
            array(
                'link'  => $this->get_adminLink(array('openTab'=>'Categories')),
                'title' => $camyks->get_translation('back'),
            ),
            array(
                'link'  => $this->editform->get_HTMLSubmitLink(),
                'title' => $camyks->get_translation('valid'),
            ),
        );

        /* Build interface title */
        $this->adminTitle = $this->title;
        $this->adminTitle .= $camyks->get_translation('formitem_separator');
        if ($this->categoryItem->id == 0)
            $this->adminTitle .= $this->get_translation('newcategory');
        else
            $this->adminTitle .= $this->get_translation('categoryid', $this->categoryItem->id);

        /* Update layout */
        $this->set_selectedLayout('admin_edit_category.html.inc');
    }

    /**
     * Initialise module object in admin/save_category mode.
     * @return void
     */
    private function init_admin_save_category() {
        global $camyks;

        /* Check user permission */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* save category */
        $this->categoryItem->id = isset($_REQUEST['category_id']) ? (int)$_REQUEST['category_id'] : 0;
        $this->categoryItem->get_fromHeader();
        if ($this->categoryItem->save())
            $this->text = $this->get_translation('category_saved');
        else
            $this->text = $this->get_translation('category_notsaved');

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('openTab'=>'Categories')));
    }

    /**
     * Initialise module object in admin/delete_category mode.
     * @return void
     */
    private function init_admin_delete_category() {
        global $camyks;

        /* Check user permission */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* Check category id */
        if (!isset($_REQUEST['category_id']))
            return $this->init_admin_main();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* delete category */
        $this->categoryItem->id = (int)$_REQUEST['category_id'];
        if ($this->categoryItem->delete())
            $this->text = $this->get_translation('category_deleted');
        else
            $this->text = $this->get_translation('category_notdeleted');

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('openTab'=>'Categories')));
    }

    /* Specific admin tool methods */

    /**
     * Return category status list.
     * @return array
     */
    public function get_categoryStatusList() {
        return $this->categoryItem->get_statusList();
    }

    /**
     * Return categories status list.
     * @param boolean $full
     * @return array
     */
    public function get_categoriesStatusList($full=false) {
        return $this->categoryItem->get_multiStatusList($full);
    }

    /**
     * Return category title list.
     * @param boolean $full
     * @param array $params
     * @return array
     */
    public function get_categoryTitleList($full=false, $params=array()) {
        if (!isset($params['language']))
            $params['language'] = $this->get_adminEditionLanguage();

        $list = $this->categoryItem->get_titleList($params);
        if ($full)
            $list = array(0=>$this->get_translation('categorytitle_all'))+ $list;
        return $list;
    }

    /**
     * Return definition status list.
     * @return array
     */
    public function get_definitionStatusList() {
        return $this->definitionItem->get_statusList();
    }

    /**
     * Return definitions status list.
     * @param boolean $full
     * @return array
     */
    public function get_definitionsStatusList($full=false) {
        return $this->definitionItem->get_multiStatusList($full);
    }

    /**
     * Return definition list.
     * @param array $params
     * @return array
     */
    public function get_wordList($params=array()) {
        return $this->definitionItem->get_list($params);
    }

    /**
     * Return definition count.
     * @param array $params
     * @return array
     */
    public function count_words($params=array()) {
        return $this->definitionItem->count($params);
    }
}
?>
