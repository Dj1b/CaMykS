<?php
/**
 * @brief Content_GenericLegalMentions Module
 * @details Plugin, Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Jan 2020
 * @date Modification: Jan 2020
 * @copyright 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_GenericLegalMentions class.
 */
final class Content_GenericLegalMentions extends Module {
    /**
     * var Object $contentItem
     * @brief Page redirector object.
     */
    protected $contentItem;

    /**
     * var string $mode
     * @brief Admin mode to run.
     */
    private $mode;

    /**
     * var integer $page_id
     * @brief Parent page id.
     */
    public $page_id;

    /**
     * var integer $module_index
     * @brief Parent page, module index.
     */
    protected $module_index;

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('Content_GenericLegalMentions', $path_type);

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
        $this->load_library('Content_GenericLegalMentionsItem');

        /* Initialise plugin libraries */
        $this->contentItem = new Content_GenericLegalMentionsItem(0, $this);
    }

    /* Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return ($this->contentItem->install() and parent::install());
    }

    /**
     * Uninstall module
     * @return boolean success
     */
    public function uninstall() {
        return ($this->contentItem->uninstall() and parent::uninstall());
    }

    /**
     * Check module installation.
     * @return boolean result
     */
    public function is_installed() {
        return $this->contentItem->is_installed();
    }

    /**
     * Return available content id/names as list.
     * @return array
     */
    public function get_contentList() {
        return $this->contentItem->get_nameList();
    }

    /**
     * Initialise module object in admin mode
     * @return void
     */
    public function init_admin() {
        global $camyks;

        /* Pre-initialise module */
        parent::preInit_admin();

        /* Check right for this page */
        if ($this->check_right($this->page_id) === false)
            return $this->init_admin_pageAccessDenied();

        /* Check dependencies */
        if (!isset($camyks->inputs['TinyMCEv3']))
            return $this->init_admin_missingPlugin('Input', 'TinyMCEv3');
        if (!isset($camyks->inputs['TabBuilder']))
            return $this->init_admin_missingPlugin('Input', 'TabBuilder');

        /* Load item id */
        $this->contentItem->id = $this->id;

        /* Load action to execute */
        $this->mode = isset($_REQUEST['mode'])?$_REQUEST['mode']:'';

        /* Execute action */
        switch ($this->mode) {
            case 'save_item':
                /* mode == save_item */
                $this->init_admin_save_item();
                break;
            case 'edit_item':
            default:
                /* mode == edit_item */
                $this->init_admin_edit_item();
                break;
        }

        /* generic admin initialisation */
        parent::init_admin();
    }

    /**
     * Initialise module object in site mode.
     * @param integer $content
     * @param array $params
     * @param integer $mindex
     * @return void
     */
   public function init_site($content=1, $params=array(), $mindex=1) {
        global $camyks;

        /* Load object */
        $this->contentItem->id = $content;
        $this->contentItem->get($camyks->current_language);
        $this->contentItem->get_fromItems();

        /* Load extensions */
        $this->extensions = $this->get_registeredExtensions();

        /* Initialise extra data array */
        $this->extraData = array(
            /*
            'plugin'    => array(
                array(
                    'title' => '',
                    'purpose' => '',
                    'description' => '',
                    'duration' => '',
                    'data' => '',
                ),
             ),
             */
        );

        /* Load data from extensions */
        foreach ($this->extensions as $extension)
            $this->extraData[$extension->name] = $extension->get_legalMentionsData();

        /* Load Javascript */
        $this->add_JSEngineFile('tool/mail.js');

        /* Generic initialisation */
        parent::init_site();
    }

    /* Specific admin mode methods */

    /**
     * Initialise module object in admin/edit_item mode
     * @return void
     */
    private function init_admin_edit_item() {
        global $camyks;

        /* Load object */
        $this->contentItem->get(true);
        $this->contentItem->get_fromItems();

        /* Load editor input */
        $this->editor = &$camyks->inputs['TinyMCEv3'];
        $this->editor->initialise();

        /* Build tabs */
        $this->tabBuilder = $camyks->get_input('TabBuilder');
        $this->tabBuilder->add_tabs(array(
            array(
                'name'  => 'Properties',
                'title' => $camyks->get_translation('properties'),
            ),
            array(
                'name'  => 'Owner',
                'title' => $this->get_translation('tabowner'),
            ),
            array(
                'name'  => 'Creator',
                'title' => $this->get_translation('tabcreator'),
            ),
            array(
                'name'  => 'WebmasterDPO',
                'title' => $this->get_translation('tabwebmasterdpo'),
            ),
            array(
                'name'  => 'Host',
                'title' => $this->get_translation('tabhost'),
            ),
        ));
        foreach ($camyks->get_confValue('editing_languages') as $l)
            $this->tabBuilder->add_tab(array(
                'name'  => $l,
                'title' => $this->get_translation('tabadditionalcontent').' '.language_getIcon($l),
            ));
        /* Initialise tabs */
        $this->tabBuilder->initialise(array('default'=>'Properties'));

        /* Build seocnd tabs for owner tab */
        $this->ownerTabs = new TabBuilder('camyks');
        foreach ($camyks->get_confValue('editing_languages') as $l)
            $this->ownerTabs->add_tab(array(
                'name'  => 'Owner'.$l,
                'title' => language_getIcon($l),
            ));

        /* Initialise tabs */
        $this->ownerTabs->initialise(array('name'=>'OwnerAdditional'));

        /* Build form */
        $this->form = new HTMLForm('edit_form', $this->get_adminlink(array('mode'=>'save_item')), 'POST');
        $this->form->add_hidden('page_id', $this->page_id);
        $this->form->add_hidden('module_index', $this->module_index);
        $this->form->add_hidden('id', $this->contentItem->id);
        $this->form->set_object($this->contentItem);

        /* Build buttons */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'  => $camyks->get_adminLink('Admin_ContentPage', array(
                    'mode'      => 'modify',
                    'page_id'   => $this->page_id,
                    'openTab'   => 'content',
                ))
            ),
            array(
                'title' => $camyks->get_translation('valid'),
                'link'  => $this->form->get_HTMLSubmitLink(),
            ),
        );
    }

    /**
     * Initialise module object in admin/save_item mode
     * @return void
     */
    private function init_admin_save_item() {
        global $camyks;

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Get item object */
        $this->contentItem->get_fromHeader();
        if ($this->contentItem->save()) {
            /* update page information with object id for new content */
            if ($this->id == 0 and $this->page_id > 0)
                $this->add_moduleContentToPage($this->page_id, $this->module_index, $this->contentItem->id);
            $this->text = $camyks->get_translation('savedone');
        } else {
            $this->text = $camyks->get_translation('savefailed');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('id'=>$this->contentItem->id, 'mode'=>'edit_item')));
    }
}
?>
