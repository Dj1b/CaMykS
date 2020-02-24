<?php
/**
 * @brief TinyMCEv3 Input
 * <br /> Interfaces TinyMCE version 3 for CaMykS.
 * @details Plugin / Input Engine
 * @file plugin/input/TinyMCEv3/TinyMCEv3.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jul 2008
 * @date Modification: Feb 2020
 * @copyright 2008 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @note Includes TinyMCE version 3.5.11 (http://tinymce.moxiecode.com/)
 */

/**
 * TinyMCEv3 Input class.
 */
final class TinyMCEv3 extends Input {
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
        parent::__construct('TinyMCEv3', $path_type);

        /* overwrite Plugin information */
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* recommended configs */
        $this->admin_configs = array('default', 'classic', 'simple', 'flash');
        $this->client_configs = array('classic_cs', 'simple_cs', 'textual');

        /* available configs */
        $this->specific_configs = array('file', 'text');
        $this->builtin_configs = array_merge(array('advanced'), $this->admin_configs, $this->client_configs);
        $this->configs = array_merge($this->specific_configs, $this->builtin_configs);
    }

    /* overwrite input methods */

    /**
     * Initialise input.
     * @return void
     */
    function initialise($params=array()) {
        global $camyks;

        /* add javascript engine */
        $this->add_JSFile('tiny_mce/tiny_mce.js');
        /* add mail encoding javascript */
        $this->add_JSEngineFile('tool/mail.js');
        /* add current language */
        $this->add_JSPreScript('camyks_language="'.$camyks->current_language.'";');

        /* load external plugins */
        $extPlugins = $this->get_registeredExtensions();
        if ($extPlugins === false) {
            $this->add_JSPreScript('camyks_ext_plugins=\'\';');
            $this->add_JSPreScript('camyks_ext_buttons=\'\';');
        } else {
            $camyks_ext_plugins = '';
            $camyks_ext_buttons = array();
            foreach($extPlugins as $plugin) {
                $pluginParams = $plugin->get_tinyMCEPluginParams();

                /* add plugin to plugin list */
                $camyks_ext_plugins .= ',-'.$pluginParams['name'];
                /* add plugin buttons to buttons list */
                $camyks_ext_buttons = array_merge($camyks_ext_buttons, $pluginParams['buttons']);
            }
            $this->add_JSPreScript('camyks_ext_plugins=\''.$camyks_ext_plugins.'\';');
            $this->add_JSPreScript('camyks_ext_buttons=\''.implode(',', $camyks_ext_buttons).'\';');
            $this->add_JSPreScript('camyks_plugin_url=\''.$camyks->get_confValue('url').'/'.$camyks->camyks_plugin_url.'\';');
            $this->add_JSPreScript('camyks_data_url=\''.$camyks->get_confValue('url').'/'.$camyks->site_data_url.'\';');
        }

        /* add path mode values */
        $mode = $camyks->get_confValue('file_path');

        /* check for boolean mode value */
        if ($mode === false)
            $mode = 'relative';
        elseif ($mode === true)
            $mode ='absolute';

        /* return base url from mode */
        switch ($mode) {
            case 'absolute':
            case 'absolute_long':
                $this->add_JSPreScript('camyks_relative_urls=false;');
                $this->add_JSPreScript('camyks_remove_host=false;');
                break;
            case 'absolute_short':
                $this->add_JSPreScript('camyks_relative_urls=false;');
                $this->add_JSPreScript('camyks_remove_host=true;');
                break;
            case 'relative':
            default:
                $this->add_JSPreScript('camyks_relative_urls=true;');
                $this->add_JSPreScript('camyks_remove_host=true;');
                break;
        }

        /* check config */
        if (!in_array($this->configType, $this->configs)) {
                $this->configType = (isset($camyks->_conf['editor_default_config']) && in_array($camyks->_conf['editor_default_config'], $this->configs))?$camyks->_conf['editor_default_config']:'default';
        }
        switch ($this->configType) {
            /* specific configs */
            case 'file':
                $this->add_JSExternFile($this->configValue);
                break;
            case 'text':
                $this->add_JSScript($this->configValue);
                break;
            /* built-in configs */
            case 'default':
            case 'advanced':
            case 'classic':
            case 'simple':
                /* get file manager input object */
                if (isset($this->configMore['fm_path']) and isset($this->configMore['fm_url']))
                    $this->load_fileManager($this->configMore['fm_path'], $this->configMore['fm_url'], isset($this->configMore['fm_title'])?$this->configMore['fm_title']:'');
                else
                    $this->load_fileManager();
            case 'flash':
                /* get page chooser input object */
                $this->load_pageChooser();
            case 'textual':
            case 'classic_cs':
            case 'simple_cs':
                /* get page theme */
                $this->load_themeCSSFile();
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
     * @param string $contentLg
     * @return void
     */
    public function set_contentInfos($contentType='text', $contentValue='', $contentLg='') {
        $this->contentType = $contentType;
        $this->contentValue = $contentValue;
        $this->contentLg = $contentLg;

        if ($this->contentType == 'file' and !file_exists ($this->contentValue)) {
            $this->contentType = 'text';
            $this->contentValue = '';
        }
    }

    /**
     * Define config information.
     * @param string $configType
     * @param string $configValue
     * @param array $more
     * @return void
     */
    public function set_configInfos($configType='default', $configValue='', $more=array()) {
        $this->configType = $configType;
        $this->configValue = $configValue;
        $this->configMore = $more;
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
     * Load page theme.
     * @param integer $pageid
     * @return void
     */
    public function load_themeCSSFile($pageid=null) {
        global $camyks;
        $theme = '';

        if (!isset($pageid) and isset($_REQUEST['page_id']))
            $pageid = $pageid;

        if (isset($pageid)) {
            /* get page information */
            $page = new ContentPage($pageid);
            $page->get();
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
     * Load filemanager input.
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
            $this->add_JSScript('function image_callback(field_name, field_value, type, win) {');
            $this->add_JSScript('icb_win = win;');
            $this->add_JSScript('icb_field = field_name;');
            $this->add_JSScript($this->filemanager->get_link('field_value'));
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
        $this->add_JSFile('editor.js');

        /* check input availability */
        if (isset ($camyks->inputs['PageChooser'])) {
            /* get input */
            $this->pagechooser = &$camyks->inputs['PageChooser'];
            $this->pagechooser->initialise('pagelink', '', 'page_updatevalue');
            $this->add_JSScript('isPageChooserAvailable = true;');
            /* add content languages */
            $this->add_JSScript('editing_languages = new Array("'.implode('", "', $camyks->get_confValue('editing_languages')).'");', true);
            $this->add_JSScript('site_languages = new Array("'.implode('", "', $camyks->get_confValue('site_languages')).'");', true);
        } else {
            $this->add_JSScript('isPageChooserAvailable = false;');
        }
    }

    /**
     * Return selected config list.
     * @return array
     */
    public function get_configList($mode='admin') {
         switch($mode) {
            case 'admin':
                $c = &$this->admin_configs;
                break;
            case 'client':
                $c = &$this->client_configs;
                break;
            case 'builtin':
                $c = &$this->builtin_configs;
                break;
         }
         $configs = array();
         foreach ($c as $i) {
             $configs[$c] = $this->get_translation('config_'.$c);
         }
         return $configs;
    }
}
?>
