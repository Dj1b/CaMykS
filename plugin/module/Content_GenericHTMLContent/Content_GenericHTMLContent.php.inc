<?php
/**
 * @brief Content_GenericHTMLContent module.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: May 2008
 * @date Modification: Jul 2025
 * @copyright 2008 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_GenericHTMLContent class.
 */
final class Content_GenericHTMLContent extends Module {
    /**
     * var Object $content
     * @brief Content item.
     */
    protected $content;

    /**
     * var Object $input
     * @brief Link to editor input.
     */
    protected $input;

    /**
     * var array $layouts
     * @brief List of available layouts.
     */
    protected $layouts;

    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('Content_GenericHTMLContent', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'Generic';

        /* Override Module variables */
        $this->type = 'content';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Load plugin libraries */
        $this->load_library('Content_GenericHTMLContentItem');
        $this->content = new Content_GenericHTMLContentItem(0, $this);

        /* Initialise plugin variables */
        $this->layouts = array(
            'nobox'     => $this->get_translation('layout_nobox'),
            'largebox'  => $this->get_translation('layout_largebox'),
        );
    }

    /* Mark: Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return $this->content->install() and parent::install();
    }

    /**
     * Uninstall module.
     * @return boolean success
     */
    public function uninstall() {
        return $this->content->uninstall() and parent::uninstall();
    }

    /**
     * Check module installation.
     * @return boolean result
     */
    public function is_installed() {
        return $this->content->is_installed();
    }

    /**
     * Return. available content id/name as list
     * @return array
     */
    public function get_contentList() {
        return $this->content->get_nameList();
    }

    /**
     * Initialise module object when in admin mode.
     * @return void
     */
    public function init_admin() {
        global $camyks;

        /* Generic pre-initialisation */
        parent::preInit_admin();

        /* Check right for this page */
        if ($this->check_right($this->page_id) === false)
            return $this->init_admin_pageAccessDenied();

        /* Load content object */
        $this->id = isset ($_REQUEST['id']) ? (int)$_REQUEST['id'] : 0;
        $this->content->id = $this->id;

        /* Load action to execute */
        $this->mode = isset ($_REQUEST['mode']) ? $_REQUEST['mode'] : 'modify';

        /* Execute action */
        switch ($this->mode) {
            case 'save' :
                /* mode == save */
                $this->init_admin_save();
                break;
            case 'modify':
            default:
                /* mode == modify */
                $this->init_admin_modify();
                break;
        }

        /* Generic initialisation */
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

        if (!isset($this->contents)) {
            /* add email javascript library */
            $this->add_JSEngineFile('tool/mail.js');

            /* build content list */
            $this->contents = array();
        }

        /* get content */
        $this->contents[$mindex] = new Content_GenericHTMLContentItem($content, $this);
        $this->contents[$mindex]->get($camyks->current_language);
        $this->contents[$mindex]->get_fromItems();

        /* Generic initialisation */
        parent::init_site();
    }

    /**
     * Display module object in site mode.
     * @param integer $mindex
     * @return void
     */
    public function display_site($mindex=null) {
        /* get module content */
        $this->content = $this->contents[$mindex];

        /* Update layout */
        $this->set_selectedLayout('site_'.$this->content->vars['layout'].'.html.inc');

        /* Generic display */
        parent::display_site();
    }

    /* Mark: Admin initialise mode sub methods */

    /**
     * Initialise object when in admin / modify mode.
     * @return void
     */
    private function init_admin_modify() {
        global $camyks;

        /* Check editor availability */
        if (!isset($camyks->inputs['TinyMCEv3']) and !isset($camyks->inputs['TinyMCE']))
            return $this->init_admin_missingPlugin('Input', 'TinyMCEv3');

        /* Check tabBuilder availability */
        if (!isset($camyks->inputs['TabBuilder']))
            return $this->init_admin_missingPlugin('Input', 'TabBuilder');

        /* Load help files */
        $this->get_help();

        /* Load content object */
        $this->content->get();
        $this->content->get_fromItems();

        /* Load TinyMCE input */
        if (isset($camyks->inputs['TinyMCEv3'])) {
            $this->input = &$camyks->inputs['TinyMCEv3'];
        } elseif (isset($camyks->inputs['TinyMCE'])) {
            $this->input = &$camyks->inputs['TinyMCE'];
            $this->input->set_configInfos('file', $this->get_fileURL('js/tinymce_config.js'));
            /* get page theme */
            $this->input->load_themeCSSFile($this->page_id);
            /* get file manager input object */
            $this->input->load_fileManager();
            /* get page chooser input object */
            $this->input->load_pageChooser();
        }

        /* Initialise editor */
        $this->input->initialise();

        /* Build tabs */
        $this->tabBuilder = $camyks->get_input('TabBuilder');
        $this->tabBuilder->add_tab(array(
            'name'  => 'Properties',
            'title' => $camyks->get_translation('properties'),
        ));

        /* Update tabs with languages */
        foreach ($camyks->get_confValue('editing_languages') as $l) {
            $this->tabBuilder->add_tab(array(
                'name'   => $l,
                'title' => language_getIcon($l),
            ));
        }
        if ($this->help != null)
            $this->tabBuilder->add_tab(array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help')
            ));
        $this->tabBuilder->initialise(array('default'=>'Properties'));

        /* Create html form */
        $this->form = new HTMLForm('generichtmlcontent_form', $this->get_adminlink(array('mode'=>'save')), 'POST');
        $this->form->set_object($this->content);

        /* Build interface buttons */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'  => $camyks->get_adminLink('Admin_ContentPage', array(
                    'mode'            => 'modify',
                    'page_id'     => $this->page_id,
                    'openTab'     => 'content'
                ))
            ),
            array(
                'title' => $camyks->get_translation('valid'),
                'link'  => $this->form->get_HTMLSubmitLink(),
            ),
       );
    }

    /**
     * Initialise object when in admin / save mode.
     * @return void
     */
    private function init_admin_save() {
        global $camyks;

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Load content */
        $this->content->get_fromHeader();

        /* Save content */
        if ($this->content->save()) {
            if ($this->id == 0 and $this->page_id > 0)
                /* Update page information with object id for new content */
                $this->add_moduleContentToPage($this->page_id, $this->module_index, $this->content->id);
            $this->text = $camyks->get_translation('savedone');
        } else {
            $this->text = $camyks->get_translation('savefailed');
        }

        /* Load languages for back link */
        $lgs = $camyks->get_confValue('editing_languages');

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('mode' => 'modify', 'id' => $this->content->id, 'openTab' => $lgs[0])));
    }
}
?>
