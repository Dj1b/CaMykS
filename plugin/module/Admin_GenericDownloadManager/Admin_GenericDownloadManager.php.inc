<?php
/**
 * @brief Admin_GenericDownloadManager Module
 * <br /> Manages files available to download.
 * @details Plugin, Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2.1
 * @date Creation: May 2008
 * @date Modification: Jun 2023
 * @copyright 2008 - 2023 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GenericDownloadManager class.
 */
final class Admin_GenericDownloadManager extends Module {
    /**
     * var Object $config
     * @brief Module configuration.
     */
    public $config;

    /**
     * var Object $documentItem
     * @brief Document object.
     */
    public $documentItem;

    /**
     * var array $documentList
     * @brief Document list.
     */
    public $documentList = null;

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
        global $camyks;
        parent::__construct('Admin_GenericDownloadManager', $path_type);

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
        $this->load_library('Admin_GenericDownloadManagerConfig');
        $this->load_library('Admin_GenericDownloadManagerDocument');
        $this->load_library('Admin_GenericDownloadManagerCategory');

        /* initialise plugin libraries */
        $this->config = new Admin_GenericDownloadManagerConfig('config', $this);
        $this->documentItem = new Admin_GenericDownloadManagerDocument(0, $this);
        $this->categoryItem = new Admin_GenericDownloadManagerCategory(0, $this);

        /* Declare module as TinyMCE extension */
        if ($camyks->mode == CAMYKS_MODE_ADMIN)
            $this->register_asExtension('TinyMCEv3');
    }

    /* Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return ($this->config->install() and $this->documentItem->install()
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
        return $this->documentItem->is_installed();
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
            'name'      =>'config',
            'title'     => $this->get_translation('rights_config'),
            'default'   => false,
        );
        $this->rights[2] = array(
            'name'      => 'category',
            'title'     => $this->get_translation('rights_category'),
            'default'   => false,
        );
        $this->rights[3] = array(
            'name'      => 'document',
            'title'     => $this->get_translation('rights_document'),
            'default'   => false,
        );
    }

    /**
     * Return file names for statistics tools.
     * @param array $list
     * @param string $object
     * @return array
     */
    public function get_adminStatisticsValueTitles($list, $object=null) {
        /* Check given items */
        if (count($list) == 0)
            return array();

        /* Get files names */
        switch ($object) {
            case 'genericdownload':
                $doc_objects = $this->documentItem->get_titlesList('objectid in ('.implode(',', $list).')');
                foreach ($list as $item) {
                    if (isset($doc_objects[$item])) {
                        $list[$item] = $doc_objects[$item];
                    }
                }
                return $list;
                break;
            default:
                return $list;
        }
    }

    /**
     * Return TinyMCE plugin params.
     * @return array
     */
    public function get_tinyMCEPluginParams() {
        global $camyks;
        $this->add_JSFile('tinymce_plugin/editor_plugin.js');
        $this->add_JSFile('tinymce_plugin/langs/'.$camyks->current_language.'.js');
        return array(
            'name'      => 'genericdownloadmanager',
            'buttons'   => array('insertDownloadLink'),
        );
    }

    /**
     * Initialise module object in admin mode
     * @return void
     */
    public function init_admin() {
        global $camyks;

        /* Check user permissions */
        if ($this->check_right(0) === false)
            return $this->init_admin_accessDenied();

        /* Check dependencies */
        if (!isset($camyks->inputs['TabBuilder']))
            return $this->init_admin_missingPlugin('Input', 'TabBuilder');
        if (!isset($camyks->inputs['AdminItemListViewer']))
            return $this->init_admin_missingPlugin('Input', 'AdminItemListViewer');

        /* Load configuration */
        $this->config->get();

        /* Load action to execute */
        $this->mode = isset($_REQUEST['mode']) ? $_REQUEST['mode'] : 'main';

        switch ($this->mode) {
            case 'edit_config':
                /* mode == edit_config */
                $this->init_admin_edit_config();
                break;
            case 'save_config':
                /* mode == save_config */
                $this->init_admin_save_config();
                break;
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
            case 'edit_document':
                /* mode == edit_document */
                $this->init_admin_edit_document();
                break;
            case 'save_document':
                /* mode == save_document */
                $this->init_admin_save_document();
                break;
            case 'delete_document':
                /* mode == delete_document */
                $this->init_admin_delete_document();
                break;
            case 'main':
            default:
                /* mode == main */
                $this->init_admin_main();
        }
        parent::init_admin();
    }

    /**
     * Execute module object in request mode.
     * @return void
     */
    public function execute_request() {
        global $camyks;

        /* Build error */
        $this->error = array(
            'title'         => $this->get_translation('downloaderrortitle'),
            'description'   => $this->get_translation('downloaderrordesc'),
            'content1'      => $this->get_translation('downloaderrorcnt1'),
        );

        /* Load configuration */
        $this->config->get();

        /* Check file to download */
        if (isset($_REQUEST['did']))
            return $this->execute_request_downloadFile();

        /* Check action to execute */
        if (isset($_REQUEST['action'])) {
            switch($_REQUEST['action']) {
                case 'loadData':
                    return $this->execute_request_loadData();
            }
        }

        /* Throw fatal error */
        $camyks->throwFatalError($this->error);
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

        /* Build document tab */
        $this->load_library('Admin_GenericDownloadManagerDocumentListParams');
        $this->listDocument = new AdminItemListViewer('camyks');
        $this->listDocument->set_params($this->documentListParams);
        $this->listDocument->initialise();

        /* Build category tab */
        if ($this->check_right(2) === true) {
            $this->load_library('Admin_GenericDownloadManagerCategoryListParams');
            $this->listCategory = new AdminItemListViewer('camyks');
            $this->listCategory->set_params($this->categoryListParams);
            $this->listCategory->initialise();

            /* Load categories id */
            $categoryIDs = array_keys($this->listCategory->objectList);
            $cnts = $this->documentItem->get_documentCountByCategories($categoryIDs);
            foreach($this->listCategory->objectList as $id => $category)
                $this->listCategory->objectList[$id]->vars['docs'] = isset($cnts[$id]) ? $cnts[$id] : 0;
        }

        /* Build config tab */
        if ($this->check_right(3) === true) {
            $this->configLinkModeList = $this->get_configLinkModeList();
        }

        /* Load tabs */
        $this->tabBuilder = $camyks->get_input('TabBuilder');

        /* Add configuration tab */
        if ($this->check_right(1) === true)
            $this->tabBuilder->add_tab(array(
                'name'  => 'configuration',
                'title' => $this->get_translation('tabconfiguration'),
        ));

        /* Add categories tab */
        if ($this->check_right(2) === true)
            $this->tabBuilder->add_tab(array(
                'name'  => 'categories',
                'title' => $this->get_translation('tabcategories'),
            ));

        /* Add documents tab */
        $this->tabBuilder->add_tab(array(
            'name'  =>'documents',
            'title' =>$this->get_translation('tabdocuments'),
        ));

        /* Add help tab */
        if ($this->help != null)
            $this->tabBuilder(array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help'),
            ));

        /* Initialise tabs */
        $this->tabBuilder->initialise(array('default'=>'documents'));

        /* Load buttons */
        $this->buttons = array(array(
            'link'  => $camyks->get_adminLink(),
            'title' => $camyks->get_translation('back'),
        ));
    }

    /**
     * Initialise module object in admin/edit_config mode.
     * @return void
     */
    private function init_admin_edit_config() {
        global $camyks;

        /* Check user permission */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* Build config form */
        $this->configform = new HTMLForm('configform', $this->get_adminLink(array('mode' => 'save_config')), 'POST');
        $this->configform->set_object($this->config);

        /* Load buttons */
        $this->buttons = array(
            array(
                'link'  => $this->get_adminLink(),
                'title' => $camyks->get_translation('back'),
            ),
            array(
                'link'=>$this->configform->get_HTMLSubmitLink(),
                'title'=>$camyks->get_translation('valid'),
            ),
        );

        /* Load interface title */
        $this->adminTitle = $this->title;
        $this->adminTitle .= $camyks->get_translation('formitem_separator');
        $this->adminTitle .= $this->get_translation('editconfig_title');

        /* Update layout */
        $this->set_selectedLayout('admin_edit_config.html.inc');
    }

    /**
     * Initialise module object in admin/save_config mode.
     * @return void
     */
    private function init_admin_save_config() {
        global $camyks;

        /* Check user permission */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Save config */
        $this->config->get_fromHeader();
        if ($this->config->save()) {
            $this->text = $this->get_translation('config_saved');
        } else {
            $this->text = $this->get_translation('config_not_saved');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /**
     * Initialise module object in admin/edit_document mode
     * @return void
     */
    private function init_admin_edit_document() {
        global $camyks;

        /* Check user permission */
        if ($this->check_right(3) === false)
            return $this->init_admin_actionNotAllowed();

        /* Load language to use with content */
        $lg = $this->get_adminEditionLanguage();

        /* Load document item */
        $this->documentItem->id = isset($_REQUEST['document_id']) ? (int)$_REQUEST['document_id'] : 0;
        $this->documentItem->get();
        $this->documentItem->get_fromItems();

        /* Load data */
        $this->categoryList = $this->get_categoryTitleList();

        /* Build form */
        $this->editform = new HTMLForm('edit_document', $this->get_adminlink(array('mode'=>'save_document')), 'POST');
        $this->editform->allow_files(true, $this->config->vars['file_size']*1024*1024);
        $this->editform->add_hidden('document_id', $this->documentItem->id);
        if ($this->documentItem->id == 0 or $this->documentItem->vars['security'] == '')
            $this->editform->add_hidden('update_security', 1);
        $this->editform->set_object($this->documentItem);

        /* Build title */
        $this->adminTitle = $this->title;
        $this->adminTitle .= $camyks->get_translation('formitem_separator');
        if ($this->documentItem->id == 0)
            $this->adminTitle .= $this->get_translation('documentnew');
        else
            $this->adminTitle .= $this->get_translation('documentid', $this->documentItem->id);

        /* Build button list */
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
        $this->set_selectedLayout('admin_edit_document.html.inc');
    }

    /**
     * Initialise module object in admin/save_document mode.
     * @return void
     */
    private function init_admin_save_document() {
        global $camyks;

        /* Check user rights */
        if ($this->check_right(3) === false)
            return $this->init_admin_actionNotAllowed();

        /* Check document id */
        if (!isset($_REQUEST['document_id']))
            return $this->init_admin_main();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Save document */
        $this->documentItem->id = (int)$_REQUEST['document_id'];
        $this->documentItem->get_fromHeader();
        if ($this->documentItem->save())
            $this->text = $this->get_translation('document_saved');
        else
            $this->text = $this->get_translation('document_not_saved');

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /**
     * Initialise module object in admin/delete_document mode.
     * @return void
     */
    private function init_admin_delete_document() {
        global $camyks;

        /* Check user rights */
        if ($this->check_right(3) === false)
            return $this->init_admin_actionNotAllowed() ;

        /* Check document id */
        if (!isset($_REQUEST['document_id']))
            return $this->init_admin_main();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Delete document */
        $this->documentItem->id = (int)$_REQUEST['document_id'];
        if ($this->documentItem->delete())
            $this->text = $this->get_translation('document_deleted');
        else
            $this->text = $this->get_translation('document_not_deleted');

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

        /* Check user rights */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed() ;

        /* Load category item */
        $this->categoryItem->id = isset($_REQUEST['category_id']) ? (int)$_REQUEST['category_id'] : 0;
        $this->categoryItem->get();
        $this->categoryItem->get_fromItems();

        /* get form */
        $this->editform = new HTMLForm('edit_category', $this->get_adminlink(array('mode'=>'save_category')), 'POST');
        $this->editform->set_object($this->categoryItem);
        $this->editform->add_hidden('category_id', $this->categoryItem->id);

        /* Build button list */
        $this->buttons = array(
            array(
                'link'  => $this->get_adminLink(array('openTab'=>'categories')),
                'title' => $camyks->get_translation('back')
            ),
            array(
                'link'  => $this->editform->get_HTMLSubmitLink(),
                'title' => $camyks->get_translation('valid'),
            )
        );

        /* Set interface title */
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

        /* Check user rights */
        if ($this->check_right(2) === false)
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
            $this->text = $this->get_translation('category_not_saved');

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

        /* Check user rights */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* Check category id */
        if (!isset($_REQUEST['category_id']))
            return $this->init_admin_main();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Delete category */
        $this->categoryItem->id = (int)$_REQUEST['category_id'];
        if ($this->categoryItem->delete())
            $this->text = $this->get_translation('category_deleted');
        else
            $this->text = $this->get_translation('category_not_deleted');

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /* Request mode methods */

    /**
     * Return selected file as download
     * @return void
     */
    private function execute_request_downloadFile() {
        global $camyks;

        /* load parameters */
        $fid = (int)$_REQUEST['did'];
        $sid = isset($_REQUEST['sid']) ? addslashes($_REQUEST['sid']) : '';

        /* load CaMykS */
        $camyks->get_siteInit();

        /* Check if module is installed */
        if (!$this->is_installed())
            $camyks->throwFatalError($this->error);

        /* Load document object */
        $this->documentItem->id = $fid;
        $this->documentItem->get(true);
        $this->documentItem->get_fromItems();

        /* Check security code */
        if ($this->config->vars['link_mode'] == 1 and $this->documentItem->vars['security'] != $sid)
            $camyks->throwFatalError($this->error);

        /* Check document object */
        if ($this->documentItem->vars['active'] == 0)
            $camyks->throwFatalError($this->error);

        /* Check document file */
        $file = new FSFile($this->documentItem->vars['file']);
        if ($file->exists === false)
            $camyks->throwFatalError($this->error);

        /* Update statistics */
        $camyks->update_statistic('genericdownload', $this->name, 'mixed', $this->documentItem->id, '', '');

        /* Download file */
        if ($this->documentItem->vars['filetitle'] != '')
            $file->download($this->documentItem->vars['filetitle']);
        else
            $file->download();
    }

    /**
     * Return selected file as download.
     * @return void
     */
    private function execute_request_loadData() {
        global $camyks;

        /* Build database connection */
        $camyks->get_databaseConnection();
        $camyks->add_generic_translation();

        /* Load default language */
        $lg = $this->get_adminEditionLanguage();

        /* Intialise result */
        $result = array('result'=>'success', 'categories'=>array(), 'documents'=>array());

        /* Load category list */
        $list = $this->categoryItem->get_nameList('title', 'active=1', $lg);
        foreach ($list as $id=>$item)
            $result['categories'][] = array('id'=>$id, 'title'=>$item);

        /* Load document list */
        $list = $this->documentItem->get_objectList($lg, 'active=1');
        foreach ($list as $id => $item)
            $result['documents'][] = array(
                'id'        => $id,
                'title'     => string_html2text($item->vars['title'].' ('.$item->get_fileInfos().')'),
                'category'  => $item->vars['category'],
                'link'      => $item->get_link(),
            );

        /* Send XML */
        header("Content-type: text/xml");
        echo xml_serialize2XML($result);
    }

    /* Specific admin tool methods */

    /**
     * Return category status list.
     * @param boolean $full
     * @return array
     */
    public function get_categoryStatusList($full=false) {
        $list = array();
        if ($full)
            $list['-1'] = $this->get_translation('categorystatus_all');
        $list['0'] = $this->get_translation('categorystatus_inactive');
        $list['1'] = $this->get_translation('categorystatus_active');
        return $list;
    }

    /**
     * Return status list.
     * @param boolean $full
     * @return array
     */
    public function get_categoryTitleList($full=false) {
        $list = $this->categoryItem->get_nameList('title', '', $this->get_adminEditionLanguage());
        if ($full)
            $list = array('-1'=>$this->get_translation('categorystatus_all'))+ $list;
        return $list;
    }

    /**
     * Return document status list
     * @param boolean $full
     * @return array
     */
    public function get_documentStatusList($full=false) {
        $list = array();
        if ($full)
            $list['-1'] = $this->get_translation('documentstatus_all');
        $list['0'] = $this->get_translation('documentstatus_inactive');
        $list['1'] = $this->get_translation('documentstatus_active');
        return $list;
    }

    /**
     * Return language list
     * @return array
     */
    public function get_languageList() {
        global $camyks;
        $list = array();
        $list[''] = $this->get_translation('document_language_all');
        foreach($camyks->_conf['editing_languages'] as $l)
            $list[$l] = $camyks->get_translation('lang_'.$l);
        return $list;
    }

    /**
     * Return configuration link mode list
     * @return array
     */
    public function get_configLinkModeList() {
        $list = array();
        $list[0] = $this->get_translation('configlinkmode_simple');
        $list[1] = $this->get_translation('configlinkmode_secure');
        return $list;
    }
}
?>
