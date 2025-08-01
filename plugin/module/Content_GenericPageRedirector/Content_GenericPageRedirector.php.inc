<?php
/**
 * @brief Content_GenericPageRedirector module.
 * <br /> Redirects visitor on another page.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Sep 2009
 * @date Modification: Jul 2025
 * @copyright 2009 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_GenericPageRedirector class.
 */
final class Content_GenericPageRedirector extends Module {
    /**
     * var Object $pritem
     * @brief Page redirector object.
     */
    protected $pritem;

    /**
     * var string $mode
     * @brief Admin mode to run.
     */
    private $mode;

    /**
     * var integer $page_id
     * @brief Parent page id.
     */
    protected $page_id;

    /**
     * var integer $module_index
     * @brief Parent page, module index.
     */
    protected $module_index;

    /**
     * var array $layouts
     * @brief Available layout list.
     */
    private $layouts;

    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('Content_GenericPageRedirector', $path_type);

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
        $this->load_library('Content_GenericPageRedirectorItem');

        /* Initialise plugin libraries */
        $this->pritem = new Content_GenericPageRedirectorItem(0, $this);
    }

    /* Mark: Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return ($this->pritem->install() and parent::install());
    }

    /**
     * Uninstall module
     * @return boolean success
     */
    public function uninstall() {
        return ($this->pritem->uninstall() and parent::uninstall());
    }

    /**
     * Check module installation.
     * @return boolean result
     */
    public function is_installed() {
        return $this->pritem->is_installed();
    }

    /**
     * Return available content id/names as list.
     * @return array
     */
    public function get_contentList() {
        return $this->pritem->get_nameList();
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
        $this->pritem->id = $this->id;

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
        $this->pritem->id = $content;
        $this->pritem->get($camyks->current_language);
        $this->pritem->get_fromItems();

        /* Check URL */
        if ($this->pritem->vars['url'] == '')
            return;
        if (strpos($this->pritem->vars['url'], 'http') === 0)
            $link = $this->pritem->vars['url'];
        else
            $link = $camyks->get_siteLink($this->pritem->vars['url']);

        /* Update selected layout */
        $this->set_selectedLayout('site_'.$this->pritem->vars['layout'].'.html.inc');

        /* Execute redirection following selected method */
        switch ($this->pritem->vars['method']) {
            case 3 :
                header('Location:'.$link);
                break;
            case 1 :
                if ($this->pritem->vars['delay']==0)
                    $this->add_JSLoadScript('document.location.href="'.$link.'";');
                else
                    $this->add_JSLoadScript('setTimeout("document.location.href=\''.$link.'\'", '.($this->pritem->vars['delay']*1000).');');
                break;
            case 2 :
                $this->set_redirect($this->pritem->vars['delay'], $link);
                break;
            case 0:
                if ($this->pritem->vars['delay']==0)
                    $this->add_JSLoadScript('document.location.href="'.$link.'";');
                else
                    $this->add_JSLoadScript('setTimeout("document.location.href=\''.$link.'\'", '.($this->pritem->vars['delay']*1000).');');
                $this->set_redirect($this->pritem->vars['delay'], $link);
                break;
        }

        /* Generic initialisation */
        parent::init_site();
    }

    /* Mark: Admin initialise mode sub methods */

    /**
     * Initialise module object in admin/edit_item mode
     * @return void
     */
    private function init_admin_edit_item() {
        global $camyks;

        /* Load object */
        $this->pritem->get(true);
        $this->pritem->get_fromItems();

        /* Load editor input */
        $this->editor = &$camyks->inputs['TinyMCEv3'];
        $this->editor->initialise();

        /* Build tabs */
        $this->tabBuilder = $camyks->get_input('TabBuilder');
        $this->tabBuilder->add_tab(array(
            'name'  => 'Properties',
            'title' => $this->get_translation('tabproperties'),
        ));
        foreach ($camyks->get_confValue('editing_languages') as $l)
            $this->tabBuilder->add_tab(array(
                'name'  => $l,
                'title' => language_getIcon($l),
            ));

        /* Initialise tabs */
        $this->tabBuilder->initialise();

        /* Build form */
        $this->form = new HTMLForm('edit_form', $this->get_adminlink(array('mode'=>'save_item')), 'POST');
        $this->form->add_hidden('page_id', $this->page_id);
        $this->form->add_hidden('module_index', $this->module_index);
        $this->form->add_hidden('id', $this->pritem->id);
        $this->form->set_object($this->pritem);

        /* Add javascripts */
        $this->add_JSFile('pageredirector.js');
        $this->add_JSLoadScript('update_formFromMethod();');

        /* load page chooser input */
        $this->pc = $camyks->get_input('PageChooser');
        if ($this->pc !== false) {
            $link = $camyks->_conf['url'].'/request.php?module=Admin_ContentPage';
            $this->add_JSScript('pc2 = new PageChooser("pagename", "update_selectedPage", "'.$link.'");');
        }

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
        $this->pritem->get_fromHeader();
        if ($this->pritem->save()) {
            /* update page information with object id for new content */
            if ($this->id == 0 and $this->page_id > 0)
                $this->add_moduleContentToPage($this->page_id, $this->module_index, $this->pritem->id);
            $this->text = $camyks->get_translation('savedone');
        } else {
            $this->text = $camyks->get_translation('savefailed');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('id'=>$this->pritem->id, 'mode'=>'edit_item')));
    }

    /* Mark: Attributes values methods */

    /**
     * Return redirector method list.
     * @return array
     */
    protected function get_redirectorMethodList() {
        return $this->pritem->get_methodList();
    }

    /**
     * Return layout list.
     * @return array
     */
    protected function get_redirectorLayoutList() {
        return $this->pritem->get_layoutList();
    }
}
?>
