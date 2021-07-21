<?php
/**
 * @brief Content_SystemSiteReport module.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.1.1
 * @date Creation: Apr 2007
 * @date Modification: Jul 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_SystemSiteReport class.
 */
final class Content_SystemSiteReport extends Module {
    /**
     * var Object $rfitem
     * @brief Content form object.
     */
    protected $rfitem;

    /**
     * var Object $ritem
     * @brief Link to report object.
     */
    protected $ritem;

    /**
     * var array $layouts_list
     * @brief Available layouts list.
     */
    protected $layouts_list = array('simple', 'box_normal');

    /**
     * var array $title_modes
     * @brief Available title modes list.
     */
    protected $title_modes = array(0=>'title_none', 1=>'title_text', 2=>'title_image', 3=>'title_localizedtext', 4=>'title_localizedimage');

    /**
     * var array $rtypelist
     * @brief List of available subjects
     */
    protected $rtypelist = array();

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('Content_SystemSiteReport', $path_type);

        /* Override Plugin variables */
        $this->plugin_package = 'Default';
        $this->version = '1.01';

        /* Override Module variables */
        $this->type = 'content';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* load plugin libraries */
        $this->load_library('SystemSiteReportForm');

        /* Initialise plugin libraries */
        $this->rfitem = new SystemSiteReportForm(0, $this);
    }

    /* Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return $this->rfitem->install() and parent::install();
    }

    /**
     * Uninstall module.
     * @return boolean success
     */
    public function uninstall() {
        return $this->rfitem->uninstall() and parent::uninstall();
    }

    /**
     * Check module installation.
     * @return boolean result
     */
    public function is_installed() {
        return $this->rfitem->is_installed();
    }

    /**
     * Update module.
     * @return boolean success
     */
    public function update($version, $more='') {
        /* Check version 1.01 */
        if (version_compare($this->version, $version) === 1   )
            if ($this->rfitem->update_toVersion1_01() === false)
                return false;

        /* Generic update */
        return parent::update($version, $more);
    }

    /**
     * Return available content id/name as list.
     * @return array
     */
    public function get_contentList() {
        return $this->rfitem->get_namelist();
    }

    /**
     * Initialise module object when in admin mode.
     * @return void
     */
    public function init_admin() {
        /* Generic pre-initialisation */
        parent::preInit_admin();

        /* Check permission for this page */
        if ($this->check_right($this->page_id) === false)
            return $this->init_admin_pageAccessDenied();

        /* Check dependancy */
        if (!isset($camyks->modules['Admin_SiteReport']))
            return $this->init_adminMissingPlugin('Module', 'Admin_SiteReport');
        if (!isset($camyks->inputs['TinyMCE']))
            return $this->init_adminMissingPlugin('Input', 'TinyMCE');

        /* Load mode to execute */
        $this->mode = isset ($_REQUEST['mode']) ? $_REQUEST['mode'] : 'modify';

        /* Initialise mode */
        switch ($this->mode) {
            case 'save' :
                /* mode == save */
                $this->init_admin_save();
                break;
            case 'modify' :
            default:
                /* mode == edit_list */
                $this->init_admin_edit();
                break;
        }

        /* Generic admin initialisation */
        parent::init_admin();
    }

    /**
     * Initialise module object in site mode.
     * @param integer $content
     * @param array $params
     * @param integer $mindex
     * @return void
     */
    public function init_site($content=1, $params=array(), $mindex=null) {
        global $camyks;

        /* Load content form id */
        $this->rfitem->id = $content;

        /* Load action to execute */
        $srfaction = isset ($_REQUEST['srfaction']) ? $_REQUEST['srfaction'] : 'display';

        /* Initialise mode */
        switch ($srfaction) {
            case 'send':
                /* action == send */
                $this->init_site_send();
                break;
            case 'display':
            default:
                /* action == display */
                $this->init_site_display();
                break;
        }

        /* Generic site initialisation */
        parent::init_site();
    }

    /* Specific admin mode methods */

    /**
     * Initialise module in admin/save mode.
     * @return void
     */
    private function init_admin_save() {
        global $camyks;

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Save object */
        $this->rfitem->id = isset ($_REQUEST['id']) ? (int)$_REQUEST['id'] : 0;
        $this->rfitem->get_fromHeader();
        $this->rfitem->save_toDatabase();

        /* Update page information with object id for new content */
        if ($this->rfitem->id == 0 and $this->page_id > 0)
            $this->add_moduleContentToPage($this->page_id, $this->module_index, $this->rfitem->id);

        /* Update layout */
        $this->text = $camyks->get_translation('savedone');
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('mode'=>'modify', 'id'=>$this->rfitem->id, 'page_id'=>$this->page_id, 'module_index'=>$this->module_index)));
    }

    /**
     * Initialise module in admin/edit mode.
     * @return void
     */
    public function init_admin_edit() {
        global $camyks;

        /* Load object data */
        $this->rfitem->id = isset ($_REQUEST['id']) ? (int)$_REQUEST['id'] : 0;
        $this->rfitem->get();
        $this->rfitem->get_HTMLFiles();

        /* Build tabs javascript engine */
        $this->openTab = isset ($_REQUEST['openTab']) ? $_REQUEST['openTab'] : 'properties';
        $this->tabObject = 'sitereport_tabObject';
        $this->add_JSEngineFile('object/ctab.js');
        $this->add_JSScript($this->tabObject.' = new CTab();');
        $this->add_JSScript($this->tabObject.'.init("properties", "' .$camyks->theme->parts['boxTabCSSStandart'].'","'.$camyks->theme->parts['boxTabCSSSelected'].'","'.$camyks->theme->parts['boxTabCSSRollover'].'");');
        if ($this->openTab != 'properties')
            $this->add_JSLoadScript($this->tabObject.'.mouseclick(\''.$this->openTab.'\');');

        /* Load type list */
        $this->rtypelist = $camyks->modules['Admin_SiteReport']->rtype->get_objectList();
        $this->config = &$camyks->modules['Admin_SiteReport']->config;
        $this->config->get();

        /* Set title mode selector */
        $this->add_JSEngineFile('object/cmdd.js');
        $this->add_JSScript('sitereport_modeObject = new Cmdd();');
        $this->add_JSScript('sitereport_modeObject.init("title_mode", "","","","");');
        $this->add_JSLoadScript('sitereport_modeObject.selectItem('.$this->rfitem->title_mode.');');

        /* Load tiny_mce input */
        $this->input = $camyks->inputs['TinyMCE'];
        $this->input->set_configInfos ('file', $this->get_fileURL('js/tinymce_config.js'));
        $this->input->initialise();
        $this->input->load_themeCSSFile($this->page_id);
        $this->input->load_pageChooser();

        /* Build form object */
        $this->form = new HTMLForm('sitereport_form', $camyks->get_adminlink($this->name, array('mode'=>'save')), 'POST');
        $this->form->allow_files (true);
        $this->form->add_hidden('MAX_FILE_SIZE', 500000);
        $this->form->add_hidden('id', $this->rfitem->id);
        $this->form->add_hidden('type_count', count($this->rtypelist));
        $this->form->add_hidden('page_id', $this->page_id);
        $this->form->add_hidden('module_index', $this->module_index);

        /* tab list for tabs list */
        $this->tabs = array(
            array(
                'name'  => 'properties',
                'title' => $this->get_translation('tabproperties'),
            ),
            array(
                'name'  => 'types',
                'title' => $this->get_translation('tabtypes'),
            ),
        );
        foreach ($camyks->get_confValue('editing_languages') as $l)
            $this->tabs[] = array(
                'name'  => 'desc'.$l,
                'title' => strtoupper($l),
            );

        if ($this->help != null)
            $this->tabs[] = array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help'),
            );

        /* Build interface buttons */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'  => $camyks->get_adminLink('Admin_ContentPage', array(
                    'mode'      => 'modify',
                    'page_id'   => $this->page_id,
                    'openTab'   => 'content',
                )),
            ),
            array(
                'title' => $camyks->get_translation('valid'),
                'link'  => $this->form->get_HTMLSubmitLink(),
            ),
        );
    }

    /* Specific site mode methods */

    /*
     * Initialise module object in site/display mode.
     * @return void
     */
    private function init_site_display() {
        global $camyks;

        /* Load object data */
        $this->rfitem->get();

        /* Add page styles */
        $camyks->theme->get_editor_css();

        /* Load type list */
        $t = &$camyks->modules['Admin_SiteReport']->rtype;
        $this->rtypelist = $t->get_objectList($camyks->current_language, 'id in ('.implode(',', $this->rfitem->type_list).')');

        /* Load tiny_mce input */
        $this->input = $camyks->inputs['TinyMCE'];
        $this->input->set_configInfos('simple');
        $this->input->initialise();
        $this->input->set_contentInfos('text', '');
        $this->input->set_textareaInfos('content', '100%', '200px');

        /* Build form object */
        $this->form = new HTMLForm('sitereport_form', $camyks->get_siteCurrentlink(), 'POST');
        $this->form->add_hidden('srfaction', 'send');
        $this->form->add_hidden('language', $camyks->current_language);
        $this->form->add_hidden('link', isset ($_REQUEST['srflink']) ? $_REQUEST['srflink'] : '');

        /* Load config */
        if (isset($camyks->modules['Admin_SiteReport'])) {
            $this->config = &$camyks->modules['Admin_SiteReport']->config;
            $this->config->get();
            $this->file_allowed = $this->config->vars['file_allowed'];
            $this->file_maxsize = $this->config->vars['file_maxsize'].'K'.language_getFileUnit();
            $this->form->allow_files(true, $this->config->vars['file_maxsize']*1024);
        } else {
            $this->file_allowed = false;
        }

        /* Add anti-reload && post flood control */
        $camyks->set_sessionValue('sitereportpost', 0);

        /* Update layout */
        $this->set_selectedLayout('site_'.$this->rfitem->layout_name.'.html.inc');
    }

    /**
     * Initialise module object in site/send mode.
     * @return void
     */
    private function init_site_send() {
        global $camyks;

        /* Check anti-reload && post flood */
        if ($camyks->get_sessionValue('sitereportpost', 1) == 1)
            return $this->init_site_display();

        /* Update reload action session value */
        $camyks->set_sessionValue('sitereportpost', 1);

        /* Load object data */
        $this->rfitem->get();

        /* Load report item */
        $this->ritem = &$camyks->modules['Admin_SiteReport']->ritem;
        $this->ritem->id = 0;
        $this->ritem->get_fromheader();
        $this->ritem->save();

        /* Update layout */
        $this->set_selectedLayout('site_'.$this->rfitem->layout_name.'_send.html.inc');
    }
}
?>
