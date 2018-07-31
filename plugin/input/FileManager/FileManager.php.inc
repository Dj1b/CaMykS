<?php
/**
 * @brief FileManager Input
 * <br /> Displays a file manager and allows users to manage the folder contents
 * <br /> Features :
 * <br /> + 3 modes : manage | selection | requestlink
 * <br /> + browse files from given folder (default input folder is default site folder)
 * <br /> - view : cols
 * <br /> - view : list
 * <br /> . view : bigicons
 * <br /> . view : smallicons
 * <br /> . view : slideshow
 * <br /> + upload files (case of rights)
 * <br /> + create new folders (case of rights)
 * <br /> + reload action button
 * <br /> . duplicate action button
 * <br /> + rename action button (+ alert: some links may be broken)
 * <br /> . compress file/folder action button
 * <br /> . uncompress file/folder action button
 * <br /> + download file action button
 * <br /> + delete folders and files (case of rights)
 * <br /> + file description (type, size, creation date, modification date, more ...)
 * <br /> . show visible/invisible file only
 * <br /> . browsing file filter (case of file extension)
 * <br /> + store view prefs for each admin (in a cookie)
 * <br /> . upload file filter < input type="file" name="" devices="file" accept="text/ *" >
 * <br /> . folder create error management
 * <br /> . file upload error management
 * <br /> . file upload file already exists
 * <br /> . file image thumbnail (for jpg and png)
 * <br /> . rebuild system with ajax
 * @details Plugin / Input Engine
 * @file plugin/input/FileManager/FileManager.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jun 2007
 * @date Modification: Jul 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @todo Add missing features and extension management.
 */

/**
 * FileManager Input class.
 */
final class FileManager extends Input {
    /**
     * var string $winSize
     * @brief Size of the manager view.
     */
    public $winSize = '100%';

    /**
     * var string $objname
     * @brief Manager object name.
     */
    public $objname = 'fm';

    /**
     * var array $modes
     * @brief Available mode list.
     */
    private $modes = array('manage', 'selection', 'requestlink');

    /**
     * var array $views
     * @brief Available view list.
     */
    private $views = array('columns', /* 'list', 'bigicons', 'smallicons', 'slideshow' */);

    /**
     * var array $views
     * @brief Applied theme to the view.
     */
    public $theme;

    /**
     * var string $folder_path
     * @brief Path to folder to manage.
     */
    public $folder_path;

    /**
     * var string $folder_url
     * @brief URL to folder to manage.
     */
    public $folder_url;

    /**
     * var string $folder_title
     * @brief Title of folder to manage.
     */
    public $folder_title;

    /**
     * var string $engine_mode
     * @brief Selected mode for current view.
     */
    public $engine_mode;

    /**
     * var string $engine_url
     * @brief Url of current view.
     */
    public $engine_url;

    /**
     * var string $engine_rights
     * @brief User rights for current view.
     */
    public $engine_rights;

    /**
     * var string $engine_action
     * @brief Action to execute in current view.
     */
    public $engine_action;

    /**
     * var string $browser_maxfilesize
     * @brief Upload max file size.
     */
    public $browser_maxfilesize;

    /**
     * var string $browser_maxlevel
     * @brief Browser max level.
     */
    public $browser_maxlevel;

    /**
     * var string $browser_view
     * @brief Browser current view.
     */
    public $browser_view;

    /**
     * var string $browser_filter
     * @brief Browser current filter.
     */
    public $browser_filter;

    /**
     * var string $browser_path
     * @brief Browser current path.
     */
    public $browser_path;

    /**
     * var string $browser_openpath
     * @brief Browser current open path.
     */
    public $browser_openpath;

    /**
     * var array $browser_files
     * @brief Browser files.
     */
    public $browser_files;

    /**
     * var string $selection_callback_function
     * @brief Callback function for selection mode.
     */
    public $selection_callback_function;

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('FileManager', $path_type);

        /* overwrite Plugin information */
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';
    }

    /* overwrite input methods */

    /**
     * Initialise input.
     * @return void
     */
    public function initialise($params=array()) {
        global $camyks;

        /* check engine mode values */
        if ($this->engine_mode == null or in_array($this->engine_mode, $this->modes) == false)
            $this->engine_mode = $this->modes[0];

        /* execute current mode */
        switch ($this->engine_mode) {
            case 'requestlink':
                $this->initialise_link_mode();
                break;
            case 'selection':
                $this->initialise_selection_mode();
                break;
            case 'manage':
                $this->initialise_manage_mode();
                break;
        }

        /* Input generic initialisation */
        parent::initialise();
    }

    /**
     * Execute plugin engine as request
     * @return void
     */
    public function execute_request() {
        global $camyks;

        $camyks->get_adminInit();

        /* check admin session value    */
        if ($camyks->get_sessionValue('admin_user') == null)
            die();

        $camyks->adminUser = new AdminUser($camyks->get_sessionValue('admin_user'));
        if (!$camyks->adminUser->get_fromDatabase())
            die();

        /* get values from header */
        $this->get_headerValues();

        /* set engine url */
        $this->engine_url = $camyks->get_confValue('url').'/request.php?input='.$this->name;

        /* add generic translation for file description */
        $camyks->add_generic_translation();

        /* build html page */
        $camyks->HTMLPage = new HTMLPage();
        $camyks->HTMLPage->set_charset($camyks->get_htmlencodingvalue());
        $camyks->HTMLPage->set_siteInformations(
            $camyks->get_confValue('site_title'),
            $camyks->get_confValue('site_author'),
            $camyks->get_confValue('site_company')
        );
        $camyks->HTMLPage->set_robotInformations(false, false);

        $this->add_JSEngineFile('tool/adminengine.js');
        /* initialise plugin */
        $this->initialise();
        /* update window size */
        $this->winSize = '450px;';

        /* load theme */
        $this->theme->initialise_adminMode();
        $this->add_styleFile('popup.css');

        /* display html page */
        $camyks->HTMLPage->add_HTMLHeader();
        $camyks->HTMLPage->write_HTMLContent('<div id="adminengine_main">');
        $this->display();
        $this->load_file('html/_input_selection.html.inc');
        $camyks->HTMLPage->write_HTMLContent('</div>');
        $camyks->HTMLPage->add_HTMLFooter();
        $camyks->HTMLPage->write_HTMLContent();
    }

    /* specific tool methods */

    /**
     * Update object name.
     * @param string $n
     * @return void
     */
    public function set_objectName($n) {
        $this->objname = $n;
    }

    /**
     * Define theme.
     * @param Object $theme
     * @return void
     */
    public function set_themeValues($theme) {
        $this->theme = &$theme;
    }

    /**
     * Define folder values.
     * @param string $path
     * @param string $url
     * @param string $title
     * @return void
     */
    public function set_folderValues($path=null, $url=null, $title=null) {
        $this->folder_path = $path;
        $this->folder_url = $url;
        $this->folder_title = $title;
    }

    /**
     * Define engine values
     * @param string $mode
     * @param string $url
     * @param string $rights
     * @return void
     */
    public function set_engineValues($mode=null, $url=null, $rights=null) {
        $this->engine_mode = $mode;
        $this->engine_url = $url;
        $this->engine_rights = $rights;
    }

    /**
     * Define browser values.
     * @param int $size
     * @param string $filter
     * @param string $path
     * @return void
     */
    public function set_browserValues($size=null, $filter=null, $path=null) {
        $this->browser_maxfilesize = $size;
        $this->browser_filter = $filter;
        $this->browser_path = $path;
    }

    /**
     * Define specific to selection mode values.
     * @param string $function
     * @return void
     */
    public function set_selectionValues($function=null) {
        $this->selection_callback_function = $function;
    }

    /**
     * Get running values
     * @return void
     */
    public function get_runningValues() {
        global $camyks;
        /* get engine action from header */
        $this->engine_action = isset($_REQUEST['fm_engine_action'])? $_REQUEST['fm_engine_action']:'';

        /* get browser view from session / cookie */
        if ($this->browser_view == ''){
            if ($camyks->get_sessionValue('fm_browser_view') != null and in_array($camyks->get_sessionValue('fm_browser_view'), $this->views)) {
                $this->browser_view = $camyks->get_sessionValue('fm_browser_view');
            } else if (isset($_COOKIE['fmc_browser_view']) and in_array($_COOKIE['fmc_browser_view'], $this->views)) {
                $this->browser_view = $_COOKIE['fmc_browser_view'];
                $camyks->set_sessionValue('fm_browser_view', $this->browser_view);
                setcookie('fmc_browser_view', $this->browser_view, mktime()+60*60*24*30);
            } else {
                $this->browser_view = 'columns';
                $camyks->set_sessionValue('fm_browser_view', $this->browser_view);
            }
        }
    }

    /**
     * Check all plugin values and complete them with default values
     * @return void
     */
    public function check_allValues() {
        global $camyks;
        /* check theme */
        if (!isset($this->theme)) {
            $this->theme = $camyks->site_conf['admin_default_theme'];
        }
        if (is_string($this->theme)) {
            $theme = $this->theme;
            if (isset ($camyks->themes[$theme])) {
                $this->theme = &$camyks->themes[$theme];
            } else {
                if (($this->theme = theme_get($theme, 'site')) === false) {
                    if (($this->theme = theme_get($theme, 'camyks')) === false) {
                        /* TO DO : theme not found */
                    }
                }
            }
        }

        /* check folder values */
        if ($this->folder_path === null or $this->folder_url === null) {
            $this->folder_path = $this->plugin_var_path;
            $this->folder_url = $this->plugin_var_url;
            $this->folder_title = $this->get_translation('defaultfoldertitle');
            $this->folder_default = true;
        } else {
            $this->folder_default = true;
        }

        /* check engine values */
        if ($this->engine_url == null) {
            $this->engine_url = $camyks->site_conf['url'].$_SERVER['REQUEST_URI'];
        }

        if (!is_array($this->engine_rights)) {
            $this->engine_rights = array();
            if ($this->folder_default and isset($camyks->modules['Admin_DocumentManager'])) {
                $this->engine_rights['add'] = $camyks->modules['Admin_DocumentManager']->check_right(1);
                $this->engine_rights['remove'] = $camyks->modules['Admin_DocumentManager']->check_right(2);
            }
        }

        if (!isset ($this->engine_rights['add'])){
            if ($this->folder_default and isset($camyks->modules['Admin_DocumentManager'])) {
                $this->engine_rights['add'] = $camyks->modules['Admin_DocumentManager']->check_right(1);
            } else {
                $this->engine_rights['add'] = 0;
            }
        }

        if (!isset ($this->engine_rights['remove'])){
            if ($this->folder_default and isset($camyks->modules['Admin_DocumentManager'])) {
                $this->engine_rights['remove'] = $camyks->modules['Admin_DocumentManager']->check_right(2);
            } else {
                $this->engine_rights['remove'] = 0;
            }
        }

        if (!isset ($this->engine_rights['alter'])){
            if ($this->folder_default and isset($camyks->modules['Admin_DocumentManager'])) {
                $this->engine_rights['alter'] = $camyks->modules['Admin_DocumentManager']->check_right(3);
            } else {
                $this->engine_rights['alter'] = 0;
            }
        }

        /* check browser values */
        if ($this->browser_maxfilesize == null) {
            $this->browser_maxfilesize = isset($camyks->_conf['maxfilesize']) ? $camyks->_conf['maxfilesize'] : 2;
        }
        $this->browser_maxfilesize = $this->browser_maxfilesize*1024*1024;

        /* check path value overwrite in header */
        if (isset($_REQUEST['fm_browser_path'])) {
            $this->browser_path = $_REQUEST['fm_browser_path'];
        }
        /* check for file url values */
        if (strpos($this->browser_path, $this->folder_url) === 0) {
            $this->browser_path = substr($this->browser_path, strlen($this->folder_url)+1);
        }
        /* set path to array */
        $this->browser_openpath = explode('/', $this->browser_path);

        /* check selection values if needed */
        if ($this->engine_mode == 'selection') {
            if ($this->selection_callback_function == null) {
                $this->selection_callback_function = 'file_callback';
            }
        }
    }

    /**
     * Load all values from header
     * @return void
     */
    private function get_headerValues() {
        /* get theme */
        if (isset($_REQUEST['fm_theme']))
            $this->theme = $_REQUEST['fm_theme'];

        /* get folder definition vars */
        /* folder path */
        if (isset($_REQUEST['fm_folder_path']))
            $this->folder_path = $_REQUEST['fm_folder_path'];

        /* folder url */
        if (isset($_REQUEST['fm_folder_url']))
            $this->folder_url = $_REQUEST['fm_folder_url'];
        /* folder_title */
        if (isset($_REQUEST['fm_folder_title']))
            $this->folder_title = $_REQUEST['fm_folder_title'];

        /* engine definition vars */
        /* engine running mode */
        if (isset($_REQUEST['fm_engine_mode']))
            $this->engine_mode = $_REQUEST['fm_engine_mode'];
            /* engine rights */
        if (isset($_REQUEST['fm_engine_rights']))
            $this->engine_rights = data_decode_properties($_REQUEST['fm_engine_rights'], ':');

        /* browser definition vars */
        /* browser max file size for upload */
        if (isset($_REQUEST['fm_browser_maxfilesize']))
            $this->browser_maxfilesize = $_REQUEST['fm_browser_maxfilesize'];
        /* browser filter */
        if (isset($_REQUEST['fm_browser_filter']))
            $this->browser_filter = $_REQUEST['fm_browser_filter'];
        /* browser selected path */
        if (isset($_REQUEST['fm_browser_path']))
            $this->browser_path;

        /* selection mode specific vars */
        if (isset($_REQUEST['fm_selection_callback_function']))
            $this->selection_callback_function = $_REQUEST['fm_selection_callback_function'];
    }

    /**
     * Plugin initialisation in link mode.
     * @return void
     */
    private function initialise_link_mode () {
        global $camyks;
        /* get popup link */
        $link = $camyks->get_confValue('url').'/request.php?input=FileManager';

        $this->add_JSFile('filemanager.js');
        $this->add_JSScript($this->objname.' = new FileManager("'.$link.'");');
        /* set theme */
        if (isset($this->theme))
            $this->add_JSScript($this->objname.'.addParam("fm_theme", "'.$this->theme->name.'");');
        /* set folder definition vars */
        if (isset($this->folder_path))
            $this->add_JSScript($this->objname.'.addParam("fm_folder_path", "'.$this->folder_path.'");');
        if (isset($this->folder_url))
            $this->add_JSScript($this->objname.'.addParam("fm_folder_url", "'.$this->folder_url.'");');
        if (isset($this->folder_title))
            $this->add_JSScript($this->objname.'.addParam("fm_folder_title", "'.$this->folder_title.'");');
        /* set engine definition vars */
        $this->add_JSScript($this->objname.'.addParam("fm_engine_mode", "selection");');
        if (isset($this->engine_rights))
            $this->add_JSScript($this->objname.'.addParam("fm_engine_rights","'.data_encode_properties($this->engine_rights, ':').'");');

        /* set browser definition vars */
        if (isset($this->browser_maxfilesize))
            $this->add_JSScript($this->objname.'.addParam("fm_browser_maxfilesize", "'.$this->browser_maxfilesize.'");');
        if (isset($this->browser_filter))
            $this->add_JSScript($this->objname.'.addParam("fm_browser_filter", "'.$this->browser_filter.'");');

        /* set selection specific vars */
        if (isset($this->selection_callback_function))
            $this->add_JSScript($this->objname.'.addParam("fm_selection_callback_function", "'.$this->selection_callback_function.'");');
    }

    /**
     * Plugin initialisation in view mode.
     * @return void
     */
    private function initialise_manage_mode() {
        global $camyks;

        /* get running values */
        $this->get_runningValues();

        /* check values */
        $this->check_allValues();

        /* build actions list case of rights */
        $this->actions = array('reload');
        if ($this->engine_rights['add'] == 1) {
            $this->actions[] = 'folder';
            $this->actions[] = 'file';
        }
        if ($this->engine_rights['add'] == 1)
            $this->actions[] = 'download';
        if ($this->engine_rights['remove'] == 1)
            $this->actions[] = 'trash';
        if ($this->engine_rights['alter'] == 1) {
            $this->actions[] = 'rename';
            // $this->actions[] = 'duplicate';
            // $this->actions[] = cut';
            // $this->actions[] = paste';
        }

        $this->browser_maxlevel = 0;

        /* execute action */
        switch ($this->engine_action) {
            case 'folder':
                $this->initialise_folder_execute();
                break;
        case 'file':
                $this->initialise_file_execute();
                break;
        case 'trash':
                $this->initialise_trash_execute();
                break;
        case 'change_view':
                $this->initialise_change_view_execute();
                break;
        case 'rename':
                $this->initialise_rename_execute();
                break;
        case 'download':
                $this->initialise_download_execute();
                break;
        case 'reload':
        default:
                break;
        }

        /* get file tree */
        $this->get_fileTree();

        /* add specific style */
        $this->add_styleFile('filemanager.css');

        /* add javascripts */
        $this->add_JSFile('filemanager.js');
        $this->add_JSScript('var filemanager_selectedobjects=new Array();');
        $this->add_JSScript('var filemanager_selectedfolder=\'\';');
        $this->add_JSScript('var filemanager_maxlevel='.$this->browser_maxlevel.';');
        $this->add_JSScript('var filemanager_rooturl="'.$this->folder_url.'";');

        /* get form */
        $this->form = new HTMLForm ('input_filemanager',
                $this->engine_url,
                'post');
        $this->form->allow_files(true, $this->browser_maxfilesize);
        $this->form->add_hidden('fm_engine_action', 'reload');
        $this->form->add_hidden('fm_engine_mode', $this->engine_mode);
        $this->form->add_hidden('fm_browser_path', '');
        $this->form->add_hidden('fm_browser_view', '');
        if ($this->folder_path != '') {
            $this->form->add_hidden('fm_folder_path', $this->folder_path);
            $this->form->add_hidden('fm_folder_url', $this->folder_url);
            $this->form->add_hidden('fm_folder_title', $this->folder_title);
        }
        $this->form->add_hidden('fm_selection_callback_function', $this->selection_callback_function);

        /* get "new folder" popup buttons */
        $this->folderbuttons = array(
            array(
                'title' => $camyks->get_translation('cancel'),
                'link'  => 'javascript:adminengine_modalPopupClose(\'filemanager_folderpopup\');',
            ),
            array(
                'title' => $camyks->get_translation('valid'),
                'link'  => 'javascript:document.'.$this->form->name.'.submit()',
            ),
        );

        /* get "upload file" popup buttons */
        $this->filebuttons = array(
            array(
                'title' => $camyks->get_translation('cancel'),
                'link'  => 'javascript:adminengine_modalPopupClose(\'filemanager_filepopup\');',
            ),
            array(
                'title' => $camyks->get_translation('valid'),
                'link'  => 'javascript:filemanager_action_fileLoading();',
            ),
        );

        /* get "trash item" popup buttons */
        $this->trashbuttons = array(
            array(
                'title' => $camyks->get_translation('cancel'),
                'link'  => 'javascript:adminengine_modalPopupClose(\'filemanager_trashpopup\');',
            ),
            array(
                'title' => $camyks->get_translation('valid'),
                'link'  => 'javascript:document.'.$this->form->name.'.submit()',
            ),
        );

        /* get "rename" popup buttons */
        $this->renamebuttons = array(
            array(
                'title' => $camyks->get_translation('cancel'),
                'link'  => 'javascript:adminengine_modalPopupClose(\'filemanager_renamepopup\');',
            ),
            array(
                'title' => $camyks->get_translation('valid'),
                'link'  => 'javascript:document.'.$this->form->name.'.submit()',
            ),
        );

        /* build view buttons list */
        $this->viewButtons = array();
        foreach ($this->views as $v) {
            if ($v == $this->browser_view) {
                $this->viewButtons[$v] = array(
                    'title' => '<img src="'.$this->get_fileURL('img/view/'.$v.'.gif').'" alt="'.$this->get_translation('view_'.$v).'" title="'.$this->get_translation('view_'.$v).'" border="0" />',
                );
            } else {
                $this->viewButtons[$v] = array(
                    'title' => '<img src="'.$this->get_fileURL('img/view/'.$v.'.gif').'" alt="'.$this->get_translation('view_'.$v).'" title="'.$this->get_translation('view_'.$v).'" border="0" />',
                    'url'   => 'javascript:filemanager_action_change_view(\''.$v.'\')',
                );
            }
        }

        /* build action buttons list */
        $this->actionButtons = array();
        foreach ($this->actions as $a) {
            $this->actionButtons[$a] = array(
                'title' => '<img src="'.$this->get_fileURL('img/action/'.$a.'.gif').'" alt="'.$this->get_translation('action_'.$a).'" title="'.$this->get_translation('action_'.$a).'" border="0" />',
                'url'   => 'javascript:filemanager_action_'.$a.'();',
            );
        }

        /* get specific view initialization */
        switch ($this->browser_view) {
            case 'columns':
                $this->initialise_columnsview();
                break;
            case 'list':
                $this->initialise_listview();
                break;
        }
    }

    /**
     * Initialise plugin in selection mode.
     * @return void
     */
    private function initialise_selection_mode() {
        global $camyks;
        /* initialise manage mode */
        $this->initialise_manage_mode ();
        /* complete initialisation */
        $this->add_JSScript('folderurl="'.$this->folder_url.'"');
        $this->add_JSScript('callback_function="'.$this->selection_callback_function.'";');
        $this->selectionButtons = array(
            array(
                'title' => $camyks->get_translation('cancel'),
                'link'  => 'javascript:window.close();',
            ),
            array(
                'title' => $this->get_translation('selectobject'),
                'link'  => 'javascript:filemanager_select_file();',
            ),
        );
    }

    /**
     * Request link mode link.
     * @param mixed $page_value
     * @return string
     */
    public function get_link($page_value) {
        return $this->objname.'.openFileManager('.$page_value.');';
    }

    /**
     * Build file tree.
     * @return void
     */
    private function get_fileTree() {
        if (!file_exists($this->folder_path)) {
            /* check if folder exists */
            folder_completePath($this->folder_path);
            /* get content */
            $this->browser_files = array(
                'name'      => '',
                'path'      => '',
                'full'      => '',
                'type'      => 'folder',
                'children'  => array()
            );
            return;
        } else if (!is_dir($this->folder_path)) {
            /* given folder is not a valid folder */
            /* get content */
            $this->browser_files = array(
                'name'      => '',
                'path'      => '',
                'full'      => '',
                'type'      => 'folder',
                'children'  => array());
            return;
        }
        /* get content */
        $this->browser_files = array(
            'name'      => '',
            'path'      => '',
            'full'      => '',
            'type'      => 'folder',
            'children'  => $this->get_folderContent('', 0)
        );
    }

    /**
     * Get folder content
     * @param string $folder
     * @param integer $level
     * @return array
     */
    private function get_folderContent($folder, $level) {
        $files = array();
        $path = $this->folder_path.'/'.$folder;

        $this->browser_maxlevel = max($level+1, $this->browser_maxlevel);

        $folder_files = scandir($path);
        foreach($folder_files as $file) {
            if (($file != '.') and ($file != '..')) {
                $f = $path.'/'.$file;
                    if (is_dir ($f)) {
                        /* add folder to list */
                        $n = array(
                            'name'      => $file,
                            'path'      => $folder,
                            'full'      => $folder!=''?$folder.'/'.$file:$file,
                            'type'      => 'folder',
                            'children'  => $this->get_folderContent(($folder==''?$file:$folder.'/'.$file), ($level+1)));
                        $files[$file] = $n;
                } else if (is_file($f)){
                    /* add file to list */
                    $n = array(
                        'name'  => $file,
                        'path'  => $folder,
                        'full'  => $folder!=''?$folder.'/'.$file:$file,
                        'type'  => 'file',
                        'file'  => new FSFile($path, $file));
                    $files[$file] = $n;
                }
            }
        }
        return $files;
    }

    /**
     * Create a folder action.
     * @return void
     */
    private function initialise_folder_execute() {
        /* get folder name */
        $folder_name = isset ($_REQUEST['fm_foldername']) ? $_REQUEST['fm_foldername'] : '';

        /* create full path */
        if ($this->browser_path == '') {
            $path = $this->folder_path.'/'.$this->browser_path.$folder_name;
        } else {
            $path = $this->folder_path.'/'.$this->browser_path.'/'.$folder_name;
        }

        /* check folder name validity */
        if (!file_exists($path)) {
            if (preg_match('/\b([a-zA-Z0-9]{1,}[a-zA-Z0-9_\-]{2,})\b/', $folder_name, $tempvalue)) {
                if ($folder_name == $tempvalue[1]) {
                    folder_completePath($path);
                }
            }
        }
    }

    /**
     * Upload a file action.
     * @return void
     */
    private function initialise_file_execute() {
        /* get file info */
        if (!empty($_FILES['fm_file'])) {
            $folder = $this->folder_path.'/'.$this->browser_path.'/';

            if (is_array($_FILES['fm_file']['name'])) {
                foreach ($_FILES['fm_file']['name'] as $i => $v) {
                    $file_name = $_FILES['fm_file']['name'][$i];
                    $file_tmp = $_FILES['fm_file']['tmp_name'][$i];
                    $file_size = $_FILES['fm_file']['size'][$i];
                    $file_type = $_FILES['fm_file']['type'][$i];
                    $file_error = $_FILES['fm_file']['error'][$i];
                    if ($file_error == ''){
                        move_uploaded_file($file_tmp, $folder.$file_name);
                    }
                }
            } else {
                $file_name = $_FILES['fm_file']['name'];
                $file_tmp = $_FILES['fm_file']['tmp_name'];
                $file_size = $_FILES['fm_file']['size'];
                $file_type = $_FILES['fm_file']['type'];
                $file_error = $_FILES['fm_file']['error'];
                if ($file_error == ''){
                    move_uploaded_file($file_tmp, $folder.$file_name);
                }
            }
        }
    }

    /**
     * Trash a file action.
     * @return void
     */
    private function initialise_trash_execute() {
        $object = $this->folder_path.'/'.$this->browser_path;
        if (file_exists($object)) {
            if (is_file ($object)) {
                unlink($object);
            } else if (is_dir($object)) {
                folder_delete($object, true);
            }
        }
    }

    /**
     * Change file system view action.
     * @return void
     */
    private function initialise_change_view_execute() {
        global $camyks;
        $view = isset($_REQUEST['fm_browser_view'])?$_REQUEST['fm_browser_view']:'';
        if ($view != '' and in_array($view, $this->views)) {
            $this->browser_view = $view;
            /* update session value */
            $camyks->set_sessionValue('fm_browser_view', $view);
            /* update cookie */
            setcookie('fmc_browser_view', $view, time()+60*60*24*30);
        }
    }

    /**
     * Rename a file or a folder action.
     * @return void
     */
    private function initialise_rename_execute() {
        /* get new name value form header */
        $name = isset ($_REQUEST['fm_newname']) ? $_REQUEST['fm_newname'] : '';

        /* check name validity */
        if (file_exists ($this->folder_path.'/'.$this->browser_path)) {
            if (preg_match('/\b([_a-zA-Z0-9]{1,}[a-zA-Z0-9_\-\.]{2,})\b/', $name, $tempvalue)) {
                if ($name == $tempvalue[1]) {
                    $newpath = explode('/', $this->browser_path);
                    $newpath[count($newpath)-1] = $name;
                    $newpath = implode('/', $newpath);
                    if (!file_exists($this->folder_path.'/'.$newpath)) {
                        rename($this->folder_path.'/'.$this->browser_path, $this->folder_path.'/'.$newpath);
                        $this->browser_path = $newpath;
                    }
                }
            }
        }
    }

    /**
     * Download a file action.
     * @return void
     */
    private function initialise_download_execute() {
        $file = new FSFile($this->folder_path.'/'.$this->browser_path);
        if ($file->exists) {
            $file->download();
            die();
        } else {
            /* to do : file doesn't exist */
        }
    }

    /**
     * Specific initialization for columns view.
     * @return void
     */
    private function initialise_columnsview() {
        /* build content */
        $this->cols = array();
        $this->build_columnsHTML($this->browser_files, 0, true);

        /* add javascript */
        $f = '';
        $i = &$this->browser_files['children'];
        foreach ($this->browser_openpath as $idx=>$item) {
            if ($item == '') {
                break;
            }
            if ($idx> 0)
                 $f .= '/'.$item;
            else
                $f .= $item;
            if (isset ($i[$item])) {
                $v = $i[$item]['type']=='folder'?1:0;
                $this->add_JSLoadScript('filemanager_columnSelectObject("'.$f.'" , '.$idx.', '.$v.')');
                 if ($v == 1) {
                    $i= $i[$item]['children'];
                }
            }
        }
    }

    /**
     * Build html for columns view.
     * @param array $file
     * @param int $level
     * @param boolean $visible
     * @return string
     */
    private function build_columnsHTML(&$file, $level, $visible=false) {
        /* check files validity */

        /* build layout header */
        $html = '<div id="obj'.$file['full'].'"';
        $html .= ' class="filemanagerColumnBloc adminContentPanel" style="display:'.($visible?'block':'none').';">';
        $html .= '<table cellspacing="0" style="width:100%; border-collapse:collapse;">';
        foreach ($file['children'] as $f) {
            $html .= '<tr><td class="eTableLine0 unselectable"';
            $html .= ' style="cursor:pointer; border:solid 1px white; border-top:none; line-height:16px;"';
            $html .= ' id="line'.$f['full'].'"';
            $html .= ' onmouseover="filemanager_columnSwapLine(\''.addslashes($f['full']).'\', '.$level.', 1);"';
            $html .= ' onmouseout="filemanager_columnSwapLine(\''.addslashes($f['full']).'\', '.$level.', 0);"';

            if ($f['type'] == 'file') {
                $html .= ' onclick="filemanager_columnSelectObject(\''.addslashes($f['full']).'\', '.$level.', 0);">';
                $this->build_columnsHTMLDescription($f, $level+1, false);
                $icon = $f['file']->get_mimeIconURL(16);

                //$icon = $this->get_fileURL('img/item/'.$f['type'].'.gif');
            } else if ($f['type'] == 'folder') {
                $html .= ' onclick="filemanager_columnSelectObject(\''.addslashes($f['full']).'\', '.$level.', 1);">';
                $icon = $this->get_fileURL('img/item/'.$f['type'].'.gif');
                /* build folder sub structure */
                $this->build_columnsHTML($f, $level+1, false);
            }
            /* build file line */
            $html .= '<div class="filemanagerColumnItemName"';
            $html .= ' style="background:url('.$icon.') no-repeat;">';
            $html .= $f['name'];
            $html .= '</div>';
            $html .= '</td></tr>';
        }
        $html .= '</table>';
        $html .= '</div>';
        if (!isset ($this->cols[$level]))
            $this->cols[$level] = '';
        $this->cols[$level] .= $html;
    }

    /**
     * Build html for folder descriptions.
     * @param array $file
     * @param int $level
     * @param boolean $visible
     * @return string
     */
    private function build_columnsHTMLDescription(&$file, $level, $visible=false) {
        global $camyks;
        $html = '<div id="obj'.$file['full'].'"';
        $html .= ' class="filemanagerColumnBloc" style="display:'.($visible?'block':'none').';">';
        $html .= '<table cellspacing="0" style="width:100%;">';
        /* title */
        $html .= '<tr><td class="filemanagerColumnDescTitle">'.$file['name'].'</td></tr>';
        /* icon */
        $html .= '<tr><td class="filemanagerColumnDescIcon" align="center">';
        $html .= $file['file']->get_mimeIcon(128).'</td></tr>';
        /* type */
        $html .= '<tr><td class="filemanagerColumnDescTxt">';
        $html .= $file['file']->typedesc.'</td></tr>';
        if ($file['file']->mimedesc != '') {
            $html .= '<tr><td class="filemanagerColumnDescTxt">(';
            $html .= $file['file']->mimedesc.')</td></tr>';
        }
        /* dimensions */
        if (isset($file['file']->moreinfos['width'])) {
            $html .= '<tr><td class="filemanagerColumnDescTxt">'.$file['file']->moreinfos['width'].'x';
            $html .= $file['file']->moreinfos['height'].'px</td></tr>';
        }
        /* size */
        $html .= '<tr><td class="filemanagerColumnDescTxt">'.$this->get_translation('filesize').' : ';
        $html .= $file['file']->hsize.'</td></tr>';
        /* date */
        $html .= '<tr><td class="filemanagerColumnDescTxt">'.$this->get_translation('filemodification').' : ';
        $html .= date_displayShortFormat($file['file']->mtime).'</td></tr>';

        $html .= '</table>';
        $html .= '</div>';
        if (!isset ($this->cols[$level]))
            $this->cols[$level] = '';
        $this->cols[$level] .= $html;
    }

    /**
     * Specific initialization for list view.
     * @return void
     */
    private function initialise_listview() {
        $this->add_JSScript('var image_url="'.$this->get_fileURL('img/').'";');

        $this->html = '';
        /* header line */
        $this->html .= '<div class="filemanagerListLine">';
        $this->html .= '<table cellspacing="0" style="width:100%">';
        $this->html .= '<tr>';

        $this->html .= '<td class="filemanagerListName listheader">';
        $this->html .= $this->get_translation('listname');
        $this->html .= '</td>';

        $this->html .= '<td class="filemanagerListSize listheader">';
        $this->html .= $this->get_translation('listsize');
        $this->html .= '</td>';

        $this->html .= '<td class="filemanagerListType listheader">';
        $this->html .= $this->get_translation('listtype');
        $this->html .= '</td>';

        $this->html .= '<td class="filemanagerListDate listheader">';
        $this->html .= $this->get_translation('listdate');
        $this->html .= '</td>';

        $this->html .= '</tr>';
        $this->html .= '</table>';
        $this->html .= '</div>';

        $this->alt=1;
        $this->build_listHTML($this->browser_files['children'], 0, true);


        /* add javascript */
        $f = '';
        $last = '';
        $i = &$this->browser_files['children'];
        foreach ($this->browser_openpath as $idx=>$item) {
            if ($item == '') {
                break;
            }
            if ($idx> 0)
                $f .= '/'.$item;
            else
                $f .= $item;
            if (isset ($i[$item])) {
                $v = $i[$item]['type']=='folder'?1:0;
                if ($v == 1) {
                    $this->add_JSLoadScript('filemanager_listOpenObject("'.$f.'" , '.$idx.', '.$v.')');
                    $i= $i[$item]['children'];
                }
            }
        }
        if ($f != '') {
            $this->add_JSLoadScript('filemanager_listSelectObject("'.$f.'" , '.$idx.', '.$v.')');
        }
    }

    /**
     * Build html for list view
     * @param array $files
     * @param int $level
     * @param boolean $visible
     * @return string
     */
    private function build_listHTML(&$files, $level, $visible=false) {
        foreach ($files as $file) {
            if ($file['type'] == 'file') {

                $this->html .= '<div id="object'.$file['full'].'" class="filemanagerListLine"';
                $this->html .= ' onmouseover="filemanager_listSwapLine(\''.$file['full'].'\', '.$level.', 1);"';
                $this->html .= ' onmouseout="filemanager_listSwapLine(\''.$file['full'].'\', '.$level.', 0);">';
                $this->html .= '<table cellspacing="0" style="width:100%">';
                $this->html .= '<tr>';

                for ($i=0; $i < $level+1; $i++) {
                    $this->html .= '<td class="filemanagerListArrow">';
                    $this->html .= '&nbsp;';
                    $this->html .= '</td>';
                }

                $this->html .= '<td class="filemanagerListName"';
                $this->html .= ' onclick="filemanager_listSelectObject(\''.$file['full'].'\', '.$level.', 0);">';
                $this->html .= $file['name'];
                $this->html .= '</td>';

                $this->html .= '<td class="filemanagerListSize"';
                $this->html .= ' onclick="filemanager_listSelectObject(\''.$file['full'].'\', '.$level.', 0);">';
                $this->html .= $file['file']->hsize;
                $this->html .= '</td>';

                $this->html .= '<td class="filemanagerListType"';
                $this->html .= ' onclick="filemanager_listSelectObject(\''.$file['full'].'\', '.$level.', 0);">';
                $this->html .= $file['file']->typedesc;
                $this->html .= '</td>';

                $this->html .= '<td class=" filemanagerListDate"';
                $this->html .= ' onclick="filemanager_listSelectObject(\''.$file['full'].'\', '.$level.', 0);">';
                $this->html .= date_displayShortFormat($file['file']->mtime);
                $this->html .= '</td>';

                $this->html .= '</tr>';
                $this->html .= '</table>';
                $this->html .= '</div>';
            } else if ($file['type'] == 'folder') {
                $this->html .= '<div id="object'.$file['full'].'" class="filemanagerListLine"';
                $this->html .= ' onmouseover="filemanager_listSwapLine(\''.$file['full'].'\', '.$level.', 1);"';
                $this->html .= ' onmouseout="filemanager_listSwapLine(\''.$file['full'].'\', '.$level.', 0);">';
                $this->html .= '<table cellspacing="0" style="width:100%">';
                $this->html .= '<tr>';

                for ($i=0; $i<$level; $i++) {
                    $this->html .= '<td class="filemanagerListArrow">';
                    $this->html .= '&nbsp;';
                    $this->html .= '</td>';
                }

                $this->html .= '<td class="filemanagerListArrow">';
                $this->html .= '<a href="javascript:filemanager_listOpenObject(\''.$file['full'].'\');">';
                $this->html .= '<img src="'.$this->get_fileURL('img/arrow_closed.gif').'" ';
                $this->html .= ' id="arrow'.$file['full'].'"';
                $this->html .= ' alt="" border="0" align="right">';
                $this->html .= '</a>';
                $this->html .= '</td>';

                $this->html .= '<td class="filemanagerListName"';
                $this->html .= ' onclick="filemanager_listSelectObject(\''.$file['full'].'\', '.$level.', 1);">';
                $this->html .= $file['name'];
                $this->html .= '</td>';

                $this->html .= '<td class="filemanagerListSize"';
                $this->html .= ' onclick="filemanager_listSelectObject(\''.$file['full'].'\', '.$level.', 1);">';
                if (count($file['children']) > 1)
                    $this->html .= $this->get_translation('xelements', count($file['children']));
                else
                    $this->html .= $this->get_translation('xelement', count($file['children']));
                $this->html .= '</td>';

                $this->html .= '<td class="filemanagerListType"';
                $this->html .= ' onclick="filemanager_listSelectObject(\''.$file['full'].'\', '.$level.', 1);">';
                $this->html .= $this->get_translation('folder');
                $this->html .= '</td>';

                $this->html .= '<td class="filemanagerListDate"';
                $this->html .= ' onclick="filemanager_listSelectObject(\''.$file['full'].'\', '.$level.', 1);">';
                $this->html .= '&nbsp;';
                $this->html .= '</td>';

                $this->html .= '</tr>';
                $this->html .= '</table>';
                $this->html .= '</div>';
                $this->html .= '<div id="children'.$file['full'].'" class="filemanagerListLine" style="display:none;">';
                //$this->alt = abs($this->alt-1);
                if (count($file['children']) > 0)
                    $this->build_listHTML($file['children'], $level+1, false);
                $this->html .= '</div>';
            }
        }
    }
}
?>
