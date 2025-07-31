<?php
/**
 * @brief Admin_GenericMediaLibraryManager module.
 * <br /> Manages media libraries.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.3
 * @date Creation: Jun 2015
 * @date Modification: Jul 2025
 * @copyright 2015 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GenericMediaLibraryManager class.
 */
final class Admin_GenericMediaLibraryManager extends Module {
    /**
     * var Object $pictureItem
     * @brief Picture object.
     */
    public $pictureItem;

    /**
     * var array $pictureList
     * @brief Picture list.
     */
    public $pictureList = null;

    /**
     * var Object $pictureGalleryItem
     * @brief Picture gallery object.
     */
    public $pictureGalleryItem;

    /**
     * var array $pictureGalleryList
     * @brief Picture gallery list.
     */
    public $pictureGalleryList = null;

    /**
     * var Object $config
     * @brief Plugin configuration.
     */
    protected $config;

    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('Admin_GenericMediaLibraryManager', $path_type);

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
        $this->load_library('Admin_GenericMediaLibraryManagerConfig');
        $this->load_library('Admin_GenericMediaLibraryManagerPictureGallery');
        $this->load_library('Admin_GenericMediaLibraryManagerPicture');

        /* Initialise plugin libraries */
        $this->config = new Admin_GenericMediaLibraryManagerConfig('config', $this);
        $this->pictureGalleryItem = new Admin_GenericMediaLibraryManagerPictureGallery(0, $this);
        $this->pictureItem = new Admin_GenericMediaLibraryManagerPicture(0, $this);
    }

    /* Mark: Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return ($this->config->install() and $this->pictureItem->install()
            and $this->pictureGalleryItem->install() and parent::install());
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
        return $this->pictureItem->is_installed();
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
            'name'      => 'config',
            'title'     => $this->get_translation('rights_config'),
            'default'   => false,
        );
        $this->rights[2] = array(
            'name'      => 'edit',
            'title'     => $this->get_translation('rights_picturegalleries'),
            'default'   => false,
        );
    }

    /**
     * Initialise module object in admin mode
     * @return void
     */
    public function init_admin() {
        global $camyks;

        /* Check read permission */
        if ($this->check_right(0) === false)
            return $this->init_admin_accessDenied();

        /* Check dependencies */
        if (!isset($camyks->inputs['TabBuilder']))
            return $this->init_admin_missingPlugin('Input', 'TabBuilder');
        if (!isset($camyks->inputs['AdminItemListViewer']))
            return $this->init_admin_missingPlugin('Input', 'AdminItemListViewer');
        if (!isset($camyks->inputs['TinyMCEv3']))
            return $this->init_admin_missingPlugin('Input', 'TinyMCEv3');

        /* Load configuration */
        $this->config->get();

        /* Load action to execute */
        $this->mode = isset ($_REQUEST['mode']) ? $_REQUEST['mode'] : 'main';

        switch ($this->mode) {
            case 'edit_config':
                /* mode == edit_config */
                $this->init_admin_edit_config();
                break;
            case 'save_config':
                /* mode == save_config */
                $this->init_admin_save_config();
                break;
            case 'view_pictureGallery':
                /* mode == view_pictureGallery */
                $this->init_admin_view_pictureGallery();
                break;
            case 'edit_pictureGallery':
                /* mode == edit_pictureGallery */
                $this->init_admin_edit_pictureGallery();
                break;
            case 'save_pictureGallery':
                /* mode == save_pictureGallery */
                $this->init_admin_save_pictureGallery();
                break;
            case 'delete_pictureGallery':
                /* mode == delete_pictureGallery */
                $this->init_admin_delete_pictureGallery();
                break;
            case 'edit_picture':
                /* mode == edit_picture */
                $this->init_admin_edit_picture();
                break;
            case 'save_picture':
                /* mode == save_picture */
                $this->init_admin_save_picture();
                break;
            case 'delete_picture':
                /* mode == delete_picture */
                $this->init_admin_delete_picture();
                break;
            case 'moveUp_picture':
                /* mode == moveUp_picture */
                $this->init_admin_moveUp_picture();
                break;
            case 'moveDown_picture':
                /* mode == moveDown_picture */
                $this->init_admin_moveDown_picture();
                break;
            case 'main':
            default:
                /* mode == main */
                $this->init_admin_main();
        }

        /* Perform generic intialisation */
        parent::init_admin();
    }

    /**
     * Execute module object in request mode.
     * @return void
     */
    public function execute_request() {
        global $camyks;

        /* Build error message */
        $error = array(
            'title'         => $this->get_translation('downloadfailed'),
            'description'   => $this->get_translation('downloaderror'),
            'content1'      => $this->get_translation('downloaderror2'),
        );

        /* Load mode to execute */
        $mode = isset($_REQUEST['mode']) ? $_REQUEST['mode'] : '';

        /* Execute mode */
        switch ($mode) {
            case 'optimisePictureImage':
                $this->execute_request_optimisePictureImage(); break;
            case 'optimisePictureThumb':
                $this->execute_request_optimisePictureThumb(); break;
            default :
                /* throw fatal error */
                $camyks->throwFatalError($error);
        }
    }

    /* Mark: Admin initialise mode sub methods */

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

        /* Build picture galleries tab */
        $this->load_file('lib/Admin_GenericMediaLibraryManagerPictureGalleryListParams.php.inc');
        $this->pictureGalleryList = new AdminItemListViewer('camyks');
        $this->pictureGalleryList->set_params($this->pictureGalleryListParams);
        $this->pictureGalleryList->initialise();

        /* Update picture count in galleries */
        $galleryIds = array_keys($this->pictureGalleryList->objectList);
        $cnts = $this->pictureItem->get_pictureCountByGalleries($galleryIds);
        foreach($this->pictureGalleryList->objectList as $id => $gallery)
            $this->pictureGalleryList->objectList[$id]->vars['pictures'] = isset($cnts[$id])?$cnts[$id]:0;

        /* Build configuration tab */
        $this->configResizeModeList = $this->get_configResizeModeList();
        $this->configFileTypeList = $this->get_configFileTypeList();

        /* Load tabs */
        $this->tabBuilder = $camyks->get_input('TabBuilder');

        /* Add picture galleries tab */
        $this->tabBuilder->add_tab(array(
            'name'  => 'PictureGalleries',
            'title' => $this->get_translation('tabpicturegalleries'),
        ));

        /* Add configuration tab */
        if ($this->check_right(1) === true)
            $this->tabBuilder->add_tab(array(
                'name'  => 'Configuration',
                'title' => $this->get_translation('tabconfiguration'),
            ));

        /* Add help tab */
        if ($this->help != null)
            $this->tabBuilder(array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help'),
            ));

        /* Initialise tabs */
        $this->tabBuilder->initialise(array('default'=>'PictureGalleries'));

        /* Build button list */
        $this->buttons = array(array(
            'link'  => $camyks->get_adminLink(),
            'title' => $camyks->get_translation('back'),
        ));
    }

    /**
     * Initialise module object in admin/edit_config mode.
     * @return void
     */
    public function init_admin_edit_config() {
        global $camyks;

        /* Check user rights */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* Build config form */
        $this->configform = new HTMLForm('configform', $this->get_adminLink(array('mode' => 'save_config')), 'POST');
        $this->configform->set_object($this->config);

        /* Load data */
        $this->configResizeModeList = $this->get_configResizeModeList();
        $this->configFileTypeList = $this->get_configFileTypeList();

        /* Build button list */
        $this->buttons = array(
            array(
                'link'  => $this->get_adminLink(),
                'title' => $camyks->get_translation('back'),
            ),
            array(
                'link'  => $this->configform->get_HTMLSubmitLink(),
                'title' => $camyks->get_translation('valid'),
            )
        );

        /* Set interface title */
        $this->adminTitle = $this->title;
        $this->adminTitle .= $camyks->get_translation('formitem_separator');
        $this->adminTitle .= $this->get_translation('edit_config');

        /* Update layout */
        $this->set_selectedLayout('configuration/admin_edit.html.inc');
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

        /* Save configuration */
        $this->config->get_fromHeader();
        if ($this->config->save()) {
            $this->text = $this->get_translation('config_saved');
        } else {
            $this->text = $this->get_translation('config_notsaved');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('openTab'=>'Configuration')));
    }

    /**
     * Initialise module object in admin/view_pictureGallery mode
     * @return void
     */
    private function init_admin_view_pictureGallery() {
        global $camyks;

        /* Check user permission */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* Load language to use with content */
        $this->language = $this->get_adminEditionLanguage();

        /* Load pictureGallery item */
        $this->pictureGalleryItem->id = isset($_REQUEST['pictureGallery_id']) ? (int)$_REQUEST['pictureGallery_id'] : 0;
        $this->pictureGalleryItem->get();
        $this->pictureGalleryItem->get_fromItems();

        /* No selected gallery, try to create new one */
        if ($this->pictureGalleryItem->id == 0)
            $this->init_admin_edit_pictureGallery();

        /* Load pictures list */
        $this->load_library('Admin_GenericMediaLibraryManagerPictureListParams');
        $this->pictureList = new AdminItemListViewer('camyks');
        $this->pictureList->set_params($this->pictureListParams);
        $this->pictureList->initialise();

        /* Load data */
        $this->pictureGalleryStatusList = $this->get_pictureGalleryStatusList();

        /* Build tabs */
        $this->tabBuilder = $camyks->get_input('TabBuilder');

        /* Add picture galleries tab */
        $this->tabBuilder->add_tabs(array(
            array(
                'name'  => 'Properties',
                'title' => $camyks->get_translation('properties'),
            ),
            array(
                'name'  => 'Pictures',
                'title' => $this->get_translation('pictures'),
            ),
        ));

        /* Add help tab */
        if ($this->help != null)
            $this->tabBuilder(array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help'),
            ));

        /* Initialise tabs */
        $this->tabBuilder->initialise(array('default'=>'Properties'));

        /* Check preview max width */
        $this->previewWidth = min(250, $this->get_configValue('picture_thumbWidth'));

        /* Attach scripts */
        $this->add_JSFile('PictureList.js');
        $this->add_JSScript('var pl = new PictureList("pl");');
        $this->add_JSScript('pl.set_param("previewMaxWidth", '.$this->previewWidth.');');
        $this->add_JSScript('pl.set_param("picturesURL", new Array());');
        if (count($this->pictureList->objectList) > 0) {
            foreach ($this->pictureList->objectList as $img) {
                $this->add_JSScript('pl.set_param("picturesURL", '.$img->id.', "'.$img->vars['thumb'].'");');
            }
        }
        $this->add_JSLoadScript('pl.initialise();');

        /* Build button list */
        $this->buttons = array(array(
            'link'  => $this->get_adminLink(array('openTab'=>'PictureGalleries')),
            'title' => $camyks->get_translation('back'),
        ));

        /* Set interface title */
        $this->adminTitle = $this->title;
        $this->adminTitle .= $camyks->get_translation('formitem_separator');
        $this->adminTitle .= $this->get_translation('pictureGalleryid', $this->pictureGalleryItem->id);

        /* Update layout */
        $this->set_selectedLayout('admin_view_pictureGallery.html.inc');
    }

    /**
     * Initialise module object in admin/edit_pictureGallery mode.
     * @return void
     */
    private function init_admin_edit_pictureGallery() {
        global $camyks;

        /* Check user permission */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* Load language to use with content */
        $this->language = $this->get_adminEditionLanguage();

        /* Load pictureGallery item */
        $this->pictureGalleryItem->id = isset($_REQUEST['pictureGallery_id']) ? (int)$_REQUEST['pictureGallery_id'] : 0;
        $this->pictureGalleryItem->get();
        $this->pictureGalleryItem->get_fromItems();

        /* Build form */
        $this->editform = new HTMLForm('edit_pictureGallery', $this->get_adminlink(array('mode'=>'save_pictureGallery')), 'POST');
        $this->editform->set_object($this->pictureGalleryItem);
        $this->editform->add_hidden('pictureGallery_id', $this->pictureGalleryItem->id);

        /* Load pictures list */
        $this->load_file('lib/Admin_GenericMediaLibraryManagerPictureSelectionListParams.php.inc');
        $this->pictureList = new AdminItemListViewer('camyks');
        $this->pictureList->set_params($this->pictureListParams);
        $this->pictureList->initialise();

        /* Load data */
        $this->pictureGalleryStatusList = $this->get_pictureGalleryStatusList();

        /* Build tabs */
        $this->tabBuilder = $camyks->get_input('TabBuilder');

        /* Add picture galleries tab */
        $this->tabBuilder->add_tabs(array(
            array(
                'name'  => 'Properties',
                'title' => $camyks->get_translation('properties'),
            ),
            array(
                'name'  => 'Pictures',
                'title' => $this->get_translation('defaultpicture'),
            ),
        ));
        foreach ($camyks->get_confValue('editing_languages') as $l) {
            $this->tabBuilder->add_tab(array(
                'name'  => $l,
                'title' => language_getIcon($l),
            ));
        }

        /* Add help tab */
        if ($this->help != null)
            $this->tabBuilder(array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help'),
            ));

        /* Initialise tabs */
        $this->tabBuilder->initialise(array('default'=>'Properties'));

        /* Load editor input */
        $this->input = $camyks->get_input('TinyMCEv3');
        $this->input->initialise();

        /* Check preview max width */
        $this->previewWidth = min(250, $this->get_configValue('picture_thumbWidth'));

        /* Add scripts */
        $this->add_JSFile('PictureList.js');
        $this->add_JSScript('var pl = new PictureList("pl");');
        $this->add_JSScript('pl.set_param("previewMaxWidth", '.$this->previewWidth.');');
        $this->add_JSScript('pl.set_param("picturesURL", new Array());');
        if (count($this->pictureList->objectList) > 0) {
            foreach ($this->pictureList->objectList as $img) {
                $this->add_JSScript('pl.set_param("picturesURL", '.$img->id.', "'.$img->vars['thumb'].'");');
            }
        }
        $this->add_JSLoadScript('pl.initialise();');

        /* Set interface title */
        $this->adminTitle = $this->title;
        $this->adminTitle .= $camyks->get_translation('formitem_separator');
        if ($this->pictureGalleryItem->id == 0) {
            $this->adminTitle .= $this->get_translation('newpictureGallery');
            $this->buttons = array(array(
                'link'  => $this->get_adminLink(array('openTab'=>'PictureGalleries')),
                'title' => $camyks->get_translation('back'),
            ));
        } else {
            $this->adminTitle .= $this->get_translation('pictureGalleryid', $this->pictureGalleryItem->id);
            $this->buttons = array(array(
                'link'  => $this->get_adminLink(array('mode'=>'view_pictureGallery', 'pictureGallery_id'=>$this->pictureGalleryItem->id)),
                'title' => $camyks->get_translation('back'),
            ));
        }

        /* Build valid button */
        $this->buttons[] = array(
            'link'  => $this->editform->get_HTMLSubmitLink(),
            'title' => $camyks->get_translation('valid'),
        );

        /* Update layout */
        $this->set_selectedLayout('admin_edit_pictureGallery.html.inc');
    }

    /**
     * Initialise module object in admin/save_pictureGallery mode.
     * @return void
     */
    private function init_admin_save_pictureGallery() {
        global $camyks;

        /* Check user permission */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* Check pictureGallery id */
        if (!isset($_REQUEST['pictureGallery_id']))
            return $this->init_admin_main();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Save pictureGallery */
        $this->pictureGalleryItem->id = (int)$_REQUEST['pictureGallery_id'];
        $this->pictureGalleryItem->get_fromHeader();
        if ($this->pictureGalleryItem->save())
            $this->text = $this->get_translation('pictureGallery_saved');
        else
            $this->text = $this->get_translation('pictureGallery_notsaved');

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('mode'=>'view_pictureGallery', 'pictureGallery_id'=>$this->pictureGalleryItem->id)));
    }

    /**
     * Initialise module object in admin/delete_pictureGallery mode.
     * @return void
     */
    private function init_admin_delete_pictureGallery() {
        global $camyks;

        /* Check user permission */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* Check pictureGallery id */
        if (!isset($_REQUEST['pictureGallery_id']))
            return $this->init_admin_main();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Delete pictureGallery */
        $this->pictureGalleryItem->id = (int)$_REQUEST['pictureGallery_id'];
        if ($this->pictureGalleryItem->delete())
            $this->text = $this->get_translation('pictureGallery_deleted');
        else
            $this->text = $this->get_translation('pictureGallery_notdeleted');

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('openTab'=>'PictureGalleries')));
    }

    /**
     * Initialise module object in admin/edit_picture mode.
     * @return void
     */
    private function init_admin_edit_picture() {
        global $camyks;

        /* Check user permission */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* Load language to use with content */
        $lg = $this->get_adminEditionLanguage();

        /* Load picture item */
        $this->pictureItem->id = isset($_REQUEST['picture_id']) ? (int)$_REQUEST['picture_id'] : 0;
        $this->pictureItem->get();
        $this->pictureItem->get_fromItems();

        if ($this->pictureItem->id == 0 and !isset($_REQUEST['gallery'])) {
            /* no gallery defined for new picture */

        } elseif ($this->pictureItem->id == 0) {
            /* Set gallery value */
            $this->pictureItem->vars['gallery'] = (int)$_REQUEST['gallery'];
        }

        /* Build form */
        $this->editform = new HTMLForm('edit_picture', $this->get_adminlink(array('mode'=>'save_picture')), 'POST');
        $this->editform->allow_files(true, $this->config->get_value('picture_maxFileSize')*1024*1024);
        $this->editform->set_object($this->pictureItem);
        $this->editform->add_hidden('picture_id', $this->pictureItem->id);
        $this->editform->add_hidden('gallery', $this->pictureItem->vars['gallery']);
        $this->editform->add_hidden('sortPosition', $this->pictureItem->vars['sortPosition']);

        /* Build title */
        $this->adminTitle = $this->title;
        $this->adminTitle .= $camyks->get_translation('formitem_separator');
        if ($this->pictureItem->id == 0)
            $this->adminTitle .= $this->get_translation('newpicture');
        else
            $this->adminTitle .= $this->get_translation('pictureid', $this->pictureItem->id);

        /* Build button list */
        $this->buttons = array(
            array(
                'link'  => $this->get_adminLink(array('mode'=>'view_pictureGallery', 'pictureGallery_id'=>$this->pictureItem->vars['gallery'], 'openTab'=>'Pictures')),
                'title' => $camyks->get_translation('back'),
            ),
            array(
                'link'  => $this->editform->get_HTMLSubmitLink(),
                'title' => $camyks->get_translation('valid'),
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('admin_edit_picture.html.inc');
    }

    /**
     * Initialise module object in admin/save_picture mode.
     * @return void
     */
    private function init_admin_save_picture() {
        global $camyks;

        /* Check user permission */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* Check picture id */
        if (!isset($_REQUEST['picture_id']))
            return $this->init_admin_main();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Save picture */
        $this->pictureItem->id = (int)$_REQUEST['picture_id'];
        $this->pictureItem->get_fromHeader();
        if ($c = $this->pictureItem->save())
            if ($this->pictureItem->autoDisabled == 1)
                $this->text = $this->get_translation('picture_autodisabled');
            else
                $this->text = $this->get_translation('picture_saved');
        else
            $this->text = $this->get_translation('picture_notsaved');
        $this->pictureItem->get_fromItems();

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');

        /* Check for picture optimisations */
        if ($c and $this->pictureItem->has_newPicture()) {
            /* Load scripts */
            $this->add_JSEngineFile('tool/xml.js');
            $this->add_JSEngineFIle('object/cajaxrequest.js');
            $this->add_JSFile('PictureSaving.js');
            $this->add_JSScript('var ps = new PictureSaving("ps");');
            $this->add_JSScript('ps.set_param("pictureId", '.$this->pictureItem->id.');');
            $this->add_JSScript('ps.set_param("requestBaseURL", "request.php?module='.$this->name.'");');
            $this->add_JSScript('ps.set_param("backURL", "'.$this->get_adminJSLink(array('mode'=>'view_pictureGallery', 'pictureGallery_id'=>$this->pictureItem->vars['gallery'], 'openTab'=>'Pictures')).'");');
            $this->add_JSScript('ps.set_param("quitDelay", '.$camyks->get_confValue('ModuleActionDelay').');');
            $this->add_JSScript('ps.set_locale("picture_saved", "'.$this->get_translation('pictureimage_saved').'");');
            $this->add_JSScript('ps.set_locale("thumb_saved", "'.$this->get_translation('picturethumb_saved').'");');
            $this->add_JSLoadScript('ps.initialise();');
        } else
            $this->set_redirect($this->get_adminLink(array('mode'=>'view_pictureGallery', 'pictureGallery_id'=>$this->pictureItem->vars['gallery'], 'openTab'=>'Pictures')));
    }

    /**
     * Initialise module object in admin/delete_picture mode
     * @return void
     */
    private function init_admin_delete_picture() {
        global $camyks;

        /* Check user permission */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* Check picture id */
        if (!isset($_REQUEST['picture_id']))
            return $this->init_admin_main();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Delete picture */
        $this->pictureItem->id = (int)$_REQUEST['picture_id'];
        $this->pictureItem->get();
        $this->pictureItem->get_fromItems();
        if ($this->pictureItem->delete())
            $this->text = $this->get_translation('picture_deleted');
        else
            $this->text = $this->get_translation('picture_notdeleted');

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('mode'=>'view_pictureGallery', 'pictureGallery_id'=>$this->pictureItem->vars['gallery'], 'openTab'=>'Pictures')));
    }

    /**
     * Initialise module object in admin/moveUp_picture mode.
     * @return void
     */
    private function init_admin_moveUp_picture() {
        global $camyks;

        /* Check user permission */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        if (!isset($_REQUEST['picture_id']))
            return $this->init_admin_main();

        /* Move up item */
        $this->pictureItem->id = (int)$_REQUEST['picture_id'];
        $this->pictureItem->get();
        $this->pictureItem->get_fromItems();
        $this->pictureItem->update_moveUp();

        /* Update layout */
        $this->set_selectedLayout('__');
        $this->set_redirect(0, $this->get_adminLink(array('mode'=>'view_pictureGallery', 'pictureGallery_id'=>$this->pictureItem->vars['gallery'], 'openTab'=>'Pictures')));
    }

    /**
     * Initialise module object in admin/moveDown_picture mode.
     * @return void
     */
    function init_admin_moveDown_picture() {
        global $camyks;

        /* Check user permission */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        if (!isset($_REQUEST['picture_id']))
            return $this->init_admin_main();

        /* Move down item */
        $this->pictureItem->id = (int)$_REQUEST['picture_id'];
        $this->pictureItem->get();
        $this->pictureItem->get_fromItems();
        $this->pictureItem->update_moveDown();

        /* Update layout */
        $this->selected_layout = '__';
        $this->set_redirect(0, $this->get_adminLink(array('mode'=>'view_pictureGallery', 'pictureGallery_id'=>$this->pictureItem->vars['gallery'], 'openTab'=>'Pictures')));
    }

    /* Mark: Request mode sub methods */

    /**
     * Execute module object in picture picture optimisation mode.
     * @return void
     */
    private function execute_request_optimisePictureImage() {
        global $camyks;

        /* Load camyks engine */
        $camyks->get_siteInit();

        /* Load parameters and picture object */
        if (!isset($_REQUEST['picture_id']))
            return;
        $this->pictureItem->id = (int)$_REQUEST['picture_id'];
        if ($this->pictureItem->id == 0 or !$this->pictureItem->get($camyks->current_language))
            return;
        $this->pictureItem->get_fromItems();
        $result = new CRequestAnswer(array('status'=>'failure'));
        if ($this->pictureItem->optimise_picture())
            $result->update_params(array('status'=>'success'));
        $result->send_asXML(array('action'=>'optimisePictureImage'));
    }

    /**
     * Execute module object in picture thumb optimisation mode.
     * @return void
     */
    private function execute_request_optimisePictureThumb() {
        global $camyks;

        /* Load camyks engine */
        $camyks->get_siteInit();

        /* Load parameters and picture object */
        if (!isset($_REQUEST['picture_id']))
            return;
        $this->pictureItem->id = (int)$_REQUEST['picture_id'];
        if ($this->pictureItem->id == 0 or !$this->pictureItem->get($camyks->current_language))
            return;
        $this->pictureItem->get_fromItems();
        $result = new CRequestAnswer(array('status'=>'failure'));
        if ($this->pictureItem->optimise_thumb())
            $result->update_params(array('status'=>'success'));
        $result->send_asXML(array('action'=>'optimisePictureThumb'));
    }

    /* Mark: Specific admin tool methods */

    /**
     * Return given config item value.
     * @param string $item
     * @return mixed
     */
    public function get_configValue($item) {
        if (!isset($this->config->vars))
            $this->config->get();
        if (isset($this->config->vars[$item]))
            return $this->config->vars[$item];
        return false;
    }

    /**
     * Return config resize mode list.
     * @return array
     */
    protected function get_configResizeModeList() {
        return $this->config->get_resizeModeList();
    }

    /**
     * Return config resize mode list.
     * @return array
     */
    protected function get_configFileTypeList() {
        return $this->config->get_fileTypeList();
    }

    /**
     * Return picture gallery status list.
     * @return array
     */
    public function get_pictureGalleryStatusList() {
        return $this->pictureGalleryItem->get_statusList();
    }

    /**
     * Return picture galleries status list.
     * @param boolean $full
     * @return array
     */
    public function get_pictureGalleriesStatusList($full=false) {
        return $this->pictureGalleryItem->get_multiStatusList($full);
    }

    /**
     * Return picture galleries title list.
     * @param array $params
     * @return array
     */
    public function get_pictureGalleriesTitleList($params=array()) {
        return $this->pictureGalleryItem->get_titleList($params);
    }

    /**
     * Return picture gallery status icon list.
     * @return array
     */
    public function get_pictureGalleryStatusIconList() {
        return $this->pictureGalleryItem->get_statusIconList();
    }

    /**
     * Return picture gallery list.
     * @param array $params
     * @return array
     */
    public function get_pictureGalleryList($params=array()) {
        return $this->pictureGalleryItem->get_list($params);
    }

    /**
     * Return picture gallery count.
     * @param array $params
     * @return array
     */
    public function count_pictureGalleries($params=array()) {
        return $this->pictureGalleryItem->count($params);
    }

    /**
     * Return picture status list.
     * @return array
     */
    public function get_pictureStatusList() {
        return $this->pictureItem->get_statusList();
    }

    /**
     * Return pictures status list.
     * @param boolean $full
     * @return array
     */
    public function get_picturesStatusList($full=false) {
        return $this->pictureItem->get_multiStatusList($full);
    }

    /**
     * Return picture list.
     * @param array $params
     * @return array
     */
    public function get_pictureList($params=array()) {
        return $this->pictureItem->get_list($params);
    }

    /**
     * Return picture count.
     * @param array $params
     * @return array
     */
    public function count_pictures($params=array()) {
        return $this->pictureItem->count($params);
    }

    /**
     * Return first picture list.
     * @param array $params
     * @return array
     */
    public function get_firstPicturesList($params=array()) {
        return $this->pictureItem->get_firstList($params);
    }
}
?>
