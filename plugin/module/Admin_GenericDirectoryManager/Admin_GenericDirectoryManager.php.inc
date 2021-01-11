<?php
/**
 * @brief Admin_GenericDirectoryManager Module
 * <br /> Manages a directory of contacts, by category.
 * @details Plugin, Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jul 2010
 * @date Modification: Jan 2021
 * @copyright 2010 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GenericDirectoryManager class.
 */
final class Admin_GenericDirectoryManager extends Module {
    /**
     * var Object $contactItem
     * @brief Contact object.
     */
    public $contactItem;

    /**
     * var array $contactList
     * @brief Contact list.
     */
    public $contactList = null;

    /**
     * var Object $categoryItem
     * @brief Category object.
     */
    public $categoryItem;

    /**
     * var array $categoryList
     * @brief Category list.
     */
    public $categoryList = null;

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('Admin_GenericDirectoryManager', $path_type);

        /* Override Plugin variables */
        $this->plugin_package = 'Generic';
        $this->version = '1.0';

        /* Override Module variables */
        $this->type = 'admin';
        $this->admin_type = 'content';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Load plugin libraries */
        $this->load_library('Admin_GenericDirectoryManagerContact');
        $this->load_library('Admin_GenericDirectoryManagerCategory');

        /* Initialise plugin libraries */
        $this->contactItem = new Admin_GenericDirectoryManagerContact(0, $this);
        $this->categoryItem = new Admin_GenericDirectoryManagerCategory(0, $this);
    }

    /* Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return ($this->contactItem->install() and $this->categoryItem->install()
            and parent::install());
    }

    /**
     * Check module installation.
     * @return boolean result
     */
    public function is_installed() {
        return $this->contactItem->is_installed();
    }

    /**
     * Define module permissions.
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
            'name'      => 'contact',
            'title'     => $this->get_translation('rights_contact'),
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
        $this->mode = (isset ($_REQUEST['mode']) ? $_REQUEST['mode'] : 'main');

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
            case 'edit_contact':
                /* mode == edit_contact */
                $this->init_admin_edit_contact();
                break;
            case 'save_contact':
                /* mode == save_contact */
                $this->init_admin_save_contact();
                break;
            case 'delete_contact':
                /* mode == delete_contact */
                $this->init_admin_delete_contact();
                break;
            case 'main':
            default:
                /* mode == main */
                $this->init_admin_main();
        }

        /* Perform generic initialisation */
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

        /* Build contact tab */
        $this->load_library('Admin_GenericDirectoryManagerContactListParams');
        $this->listContact = new AdminItemListViewer('camyks');
        $this->listContact->set_params($this->contactListParams);
        $this->listContact->initialise();

        /* build category tab */
        if ($this->check_right(1) === true) {
            $this->load_library('Admin_GenericDirectoryManagerCategoryListParams');
            $this->listCategory = new AdminItemListViewer('camyks');
            $this->listCategory->set_params($this->categoryListParams);
            $this->listCategory->initialise();

            /* Load categories id */
            $categoryIDs = array_keys($this->listCategory->objectList);
            $cnts = $this->contactItem->count_byCategories($categoryIDs);
            foreach($this->listCategory->objectList as $id => $category)
                $this->listCategory->objectList[$id]->vars['contacts'] = isset($cnts[$id]) ? $cnts[$id] : 0;
        }

        /* Load tabs */
        $this->tabBuilder = $camyks->get_input('TabBuilder');

        /* Add contacts tab */
        $this->tabBuilder->add_tab(array(
            'name'  => 'contacts',
            'title' => $this->get_translation('tabcontacts'),
        ));

        /* Add categories tab */
        if ($this->check_right(1))
            $this->tabBuilder->add_tab(array(
                'name'  => 'categories',
                'title' => $this->get_translation('tabcategories'),
            ));

        /* Add help tab */
        if ($this->help != null)
            $this->tabBuilder(array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help'),
            ));

        /* Initialise tabs */
        $this->tabBuilder->initialise(array('default'=>'contacts'));

        /* Load interface buttons */
        $this->buttons = array(
            array(
                'link'  => $camyks->get_adminLink(),
                'title' => $camyks->get_translation('back'),
            ),
        );
    }

    /**
     * Initialise module object in admin/edit_contact mode.
     * @return void
     */
    private function init_admin_edit_contact() {
        global $camyks;

        /* Check user permission */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* Load language to use with content */
        $this->language = $this->get_adminEditionLanguage();
        $this->lgs = $camyks->get_confValue('editing_languages');

        /* Load contact item */
        $this->contactItem->id = isset($_REQUEST['contact_id']) ? (int)$_REQUEST['contact_id'] : 0;
        $this->contactItem->get();
        $this->contactItem->get_fromItems();

        /* Load data */
        $this->categoryList = $this->get_categoryTitleList();

        /* Build form */
        $this->editform = new HTMLForm('edit_contact', $this->get_adminlink(array('mode'=>'save_contact')), 'POST');
        $this->editform->add_hidden('contact_id', $this->contactItem->id);
        $this->editform->set_object($this->contactItem);

        /* Load tabs */
        $this->tabBuilder = $camyks->get_input('TabBuilder');

        /* Add properties tab */
        $this->tabBuilder->add_tab(array(
            'name'  => 'properties',
            'title' => $camyks->get_translation('properties'),
        ));
        if (count($this->lgs) == 1)
            $this->tabBuilder->add_tab(array(
                'name'  => $this->lgs[0],
                'title' => $this->get_translation('tabcontent'),
            ));
        else
            foreach ($this->lgs as $l)
                $this->tabBuilder->add_tab(array(
                    'name'  => $l,
                    'title' => language_getIcon($l),
                ))
                ;
        /* Add help tab */
        if ($this->help != null)
            $this->tabBuilder->add_tab(array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help'),
            ));

        /* Initialise tabs */
        $this->tabBuilder->initialise(array('default'=>'contacts'));

        /* Load editor */
        $this->editor = &$camyks->inputs['TinyMCEv3'];
        $this->editor->initialise();

        /* Initialise page chooser */
        $this->add_JSFile('glossarymanager.js');
        $link = $camyks->get_confValue('url').'/request.php?module=Admin_ContentPage';
        $this->add_JSScript('pc2 = new PageChooser("pagename", "glossarymanager_updateButtonLink", "'.$link.'");');

        /* Build title */
        $this->adminTitle = $this->title;
        $this->adminTitle .= $camyks->get_translation('formitem_separator');
        if ($this->contactItem->id == 0)
            $this->adminTitle .= $this->get_translation('contactnew');
        else
            $this->adminTitle .= $this->get_translation('contactid', $this->contactItem->id);

        /* Build interface buttons */
        $this->buttons = array(
            array(
                'link'  => $this->get_adminLink(),
                'title' => $camyks->get_translation('back'),
            ),
            array(
                'link'  => $this->editform->get_HTMLSubmitLink(),
                'title' => $camyks->get_translation('valid'),
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('admin_edit_contact.html.inc');
    }

    /**
     * Initialise module object in admin/save_contact mode.
     * @return void
     */
    private function init_admin_save_contact() {
        global $camyks;

        /* Check user permission */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* Check contact id */
        if (!isset($_REQUEST['contact_id']))
            return $this->init_admin_main();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Save contact */
        $this->contactItem->id = (int)$_REQUEST['contact_id'];
        $this->contactItem->get_fromHeader();
        if ($this->contactItem->save())
            $this->text = $this->get_translation('contact_saved');
        else
            $this->text = $this->get_translation('contact_notsaved');

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /**
     * Initialise module object in admin/delete_contact mode.
     * @return void
     */
    private function init_admin_delete_contact() {
        global $camyks;

        /* Check user permission */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* Check contact id */
        if (!isset($_REQUEST['contact_id']))
            return $this->init_admin_main();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Delete contact */
        $this->contactItem->id = (int)$_REQUEST['contact_id'];
        if ($this->contactItem->delete())
            $this->text = $this->get_translation('contact_deleted');
        else
            $this->text = $this->get_translation('contact_notdeleted');

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /**
     * Initialise module object in admin/edit_category mode.
     * @return void
     */
    private function init_admin_edit_category() {
        global $camyks;

        /* Check user permission */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* Load category item */
        $category_id =
        $this->categoryItem->id = isset($_REQUEST['category_id']) ? (int)$_REQUEST['category_id'] : 0;
        $this->categoryItem->get();
        $this->categoryItem->get_fromItems();

        /* Build form */
        $this->editform = new HTMLForm('edit_category', $this->get_adminlink(array('mode'=>'save_category')), 'POST');
        $this->editform->set_object($this->categoryItem);
        $this->editform->add_hidden('category_id', $this->categoryItem->id);

        /* Build button list */
        $this->buttons = array(
            array(
                'link'  => $this->get_adminLink(array('openTab'=>'categories')),
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

        /* Check category id */
        if (!isset($_REQUEST['category_id']))
            return $this->init_admin_main();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Save category */
        $this->categoryItem->id = (int)$_REQUEST['category_id'];
        $this->categoryItem->get_fromHeader();
        if ($this->categoryItem->save())
            $this->text = $this->get_translation('category_saved');
        else
            $this->text = $this->get_translation('category_notsaved');

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
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
        if(!isset($_REQUEST['category_id']))
            return $this->init_admin_main();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Delete category */
        $this->categoryItem->id = (int)$_REQUEST['category_id'];
        if ($this->categoryItem->delete())
            $this->text = $this->get_translation('category_deleted');
        else
            $this->text = $this->get_translation('category_notdeleted');

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
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
     * Return contact status list.
     * @return array
     */
    public function get_contactStatusList() {
        return $this->contactItem->get_statusList();
    }

    /**
     * Return contacts status list.
     * @param boolean $full
     * @return array
     */
    public function get_contactsStatusList($full=false) {
        return $this->contactItem->get_multiStatusList($full);
    }

    /**
     * Return contact list.
     * @param array $params
     * @return array
     */
    public function get_contactList($params=array()) {
        return $this->contactItem->get_list($params);
    }

    /**
     * Return contact count.
     * @param array $params
     * @return array
     */
    public function count_contacts($params=array()) {
        return $this->contactItem->count($params);
    }
}
?>
