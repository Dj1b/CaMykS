<?php
/**
 * @brief TinyMCE Input
 * <br /> Interfaces TinyMCE version 2 for CaMykS.
 * @details Plugin / Input Engine
 * @file plugin/input/TinyMCE/TinyMCE.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Mar 2007
 * @date Modification: Jul 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @note Includes TinyMCE version 2.1.0 (http://tinymce.moxiecode.com/)
 */

/**
 * TinyMCE Input class.
 */
final class TinyMCE extends Input {
    /**
     * var string $contentType
     * @brief Content type (text or file).
     */
    protected $contentType = 'text';

    /**
     * var string $contentValue
     * @brief Content value.
     */
    protected $contentValue = '';

    /**
     * var string $configType
     * @brief Editor configuration.
     */
    protected $configType = 'default';

    /**
     * var string $configValue
     * @brief Editor specific configuration.
     */
    protected $configValue = '';

    /**
     * var string $ta_name
     * @brief Editor's name.
     */
    protected $ta_name = 'tinymceta';

    /**
     * var string $ta_sizex
     * @brief Editor's horizontal size.
     */
    protected $ta_sizex = '100%';

    /**
     * var string $ta_sizey
     * @brief Editor's vertical size.
     */
    protected $ta_sizey = '300px';

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('TinyMCE', $path_type);

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
     * @param array $params
     * @return void
     */
    public function initialise($params=array()) {
        global $camyks;
        /* add javascript engine */
        $this->add_JSFile('tiny_mce/tiny_mce.js');

        /* add mail encoding javascript */
        $this->add_JSEngineFile('tool/mail.js');

        /* add current language */
        $this->add_JSPreScript('camyks_language="'.$camyks->current_language.'";');

        /* check config */
        if (!(in_array($this->configType, array('file', 'text', 'default', 'simple')))) {
            $this->configType = 'default';
        }
        switch ($this->configType) {
            case 'file':
                $this->add_JSExternFile($this->configValue);
                break;
            case 'text':
                $this->add_JSScript($this->configValue);
                break;
            case 'default':
                /* get page theme */
                $this->load_themeCSSFile();

                /* get file manager input object */
                $this->load_fileManager();

                /* get page chooser input object */
                $this->load_pageChooser();
                $this->add_JSFile ('configs/default.js');
            default:
                $this->add_JSFile ('configs/'.$this->configType.'.js');
                break;
        }

        /* Input generic initialisation */
        parent::initialise();
    }

    /**
     * Display input.
     * @param string $ta_name
     * @return void
     */
    public function display($ta_name='') {
        /* display with new name */
        if ($ta_name != '') {
            $this->ta_name = $ta_name;
        }
        /* Input generic display */
        parent::display();
    }

    /* specific methods */

    /**
     * Define content information.
     * @param string $contentType
     * @param string $contentValue
     * @return void
     */
    public function set_contentInfos($contentType='text', $contentValue='') {
        $this->contentType = $contentType;
        $this->contentValue = $contentValue;

        if ($this->contentType == 'file' and file_exists ($this->contentValue)) {

        } else {
            $this->contentType == 'text';
        }
    }

    /**
     * Define configuration information.
     * @param string $configType
     * @param string $configValue
     * @return void
     */
    public function set_configInfos($configType='default', $configValue='') {
        $this->configType = $configType;
        $this->configValue = $configValue;
    }

    /**
     * Define textarea information.
     * @param string $name
     * @param string $sx
     * @param string $sy
     * @return void
     */
    public function set_textareaInfos($name='tinymceta', $sx=null, $sy=null) {
        $this->ta_name = $name;
        if (isset ($sx))
            $this->ta_sizex = $sx;
        if (isset ($sy))
            $this->ta_sizey = $sy;
    }

    /**
     * Load page theme
     * @param integer $pageid
     * @return void
     */
    public function load_themeCSSFile($pageid=null) {
        global $camyks;
        $theme = '';

        if (!isset($pageid) and isset($_REQUEST['page_id']))
            $pageid = $pageid;

        if (isset ($pageid)) {
            /* get page information */
            $page = new ContentPage($pageid);
            $page->get_fromDatabase();
            $theme = $page->theme;
        }

        if ($theme == '') {
            $theme = $camyks->site_conf['site_default_theme'];
        }

        if (isset ($camyks->themes[$theme])) {
            $theme = $camyks->themes[$theme]->get_editorCSSURL();
        } else {
            $theme = $this->theme->get_editorCSSURL();
        }

        /* add script before tinymce config init */
        $this->add_JSPreScript('camyks_css_file="'.$theme.'";');
    }

    /**
     * Load filemanager input
     * @param string $fpath
     * @param string $furl
     * @param string $ftitle
     * @return void
     */
    public function load_fileManager($fpath='', $furl='', $ftitle='') {
        global $camyks;
        /* check input availability */
        if (isset($camyks->inputs['FileManager'])) {

            /* get input */
            $this->filemanager = &$camyks->inputs['FileManager'];
            $this->filemanager->set_engineValues('requestlink');
            $this->filemanager->set_selectionValues('image_updatevalue');
            if ($fpath != '' and $furl != '') {
                $this->filemanager->set_folderValues ($fpath, $furl, $ftitle);
            }
            $this->filemanager->initialise();
            /* add javascripts callback */
            $this->add_JSScript('function image_callback(field_name, url, type, win) {');
            $this->add_JSScript('icb_win = win;');
            $this->add_JSScript('icb_field = field_name;');
            $this->add_JSScript('icb_value=icb_win.document.forms[0].elements[icb_field].value;');
            $this->add_JSScript($this->filemanager->get_link('icb_value'));
            $this->add_JSScript('}');
            $this->add_JSScript('function image_updatevalue (url) {');
            $this->add_JSScript('icb_win.document.forms[0].elements[icb_field].value = url;');
            $this->add_JSScript('}');
        } else {
            /* send error message when input is not available */
            $this->add_JSScript('function image_callback() {');
            $this->add_JSScript('alert("FileManager Input not found.");');
            $this->add_JSScript('}');
        }
    }

    /**
     * Load pagechooser input.
     * @return void
     */
    public function load_pageChooser() {
        global $camyks;
        /* check input availability */
        if (isset ($camyks->inputs['PageChooser'])) {
            /* get input */
            $this->pagechooser = &$camyks->inputs['PageChooser'];
            $this->pagechooser->initialise('pagelink', '', 'page_updatevalue');
            /* add javascripts callback */
            $this->add_JSScript('function page_callback(field_name, win) {');
            $this->add_JSScript('icb_win = win;');
            $this->add_JSScript('icb_field = field_name;');
            $this->add_JSScript('icb_value = icb_win.document.forms[0].elements[icb_field].value;');
            $this->add_JSScript($this->pagechooser->get_link('icb_value'));
            $this->add_JSScript('}');
            $this->add_JSScript('function page_updatevalue (url) {');
            $this->add_JSScript('icb_win.document.forms[0].elements[icb_field].value = url;');
            $this->add_JSScript('setTimeout(\'icb_win.focus();\', 500);');
            $this->add_JSScript('}');
        } else {
            $this->add_JSScript('function page_callback() {');
            $this->add_JSScript('alert("FileManager Input not found.");');
            $this->add_JSScript('}');
        }
    }
}
?>
