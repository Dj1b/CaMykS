<?php
/**
 * @brief Content_GenericArticle module.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Sep 2007
 * @date Modification: Jul 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_GenericArticle class.
 */
final class Content_GenericArticle extends Module {
    /**
     * var Object $articleitem
     * @brief Article content item.
     */
    public $articleitem;

    /**
     * var array $layouts
     * @brief List of client side layouts.
     */
    protected $layouts = array();

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('Content_GenericArticle', $path_type);

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
        $this->load_library('Content_GenericArticleItem');

        /* Initialise plugin libraries */
        $this->articleitem = new Content_GenericArticleItem(0, $this);

        /* Initialise plugin variables */
        $layouts = array('classic', 'classicbox', 'notebox', 'contentbox', 'custom');
        foreach ($layouts as $l) {
            $this->layouts[$l] = $this->get_translation('layout_'.$l);
        }
    }

    /* Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return $this->articleitem->install() and parent::install();
    }

    /**
     * Uninstall module.
     * @return boolean success
     */
    public function uninstall() {
        return $this->articleitem->uninstall() and parent::uninstall();
    }

    /**
     * Check module installation.
     * @return boolean result
     */
    public function is_installed() {
        return $this->articleitem->is_installed();
    }

    /**
     * Return available content id/name as list.
     * @return array
     */
    public function get_contentList() {
        return $this->articleitem->get_nameList();
    }

    /**
     * Initialise module object in admin mode.
     * @return void
     */
    public function init_admin() {
        global $camyks;

        /* Generic pre-initialisation */
        parent::preInit_admin();

        /* Check permission for this page */
        if ($this->check_right($this->page_id) === false)
            return $this->init_admin_pageAccessDenied();

        /* Load content item id */
        $this->articleid = isset($_REQUEST['id']) ? (int)$_REQUEST['id'] : 0;
        $this->articleitem->id = $this->articleid;

        /* Load action to execute */
        $this->mode = isset($_REQUEST['mode']) ? $_REQUEST['mode'] : '';

        /* Execute action */
        switch ($this->mode) {
            case 'save_item':
                $this->init_admin_save_item();
                break;
            case 'modify_item':
            default:
                $this->init_admin_modify_item();
                break;
        }

        /* Generic admin initialisation */
        parent::init_admin();
    }

    /**
     * Initialise module object in site mode.
     * @param int $content
     * @param array $params
     * @param int $mindex
     * @return void
     */
    public function init_site($content=1, $params=array(), $mindex=null) {
        global $camyks;

        /* Add mail encoding javascript */
        $this->add_JSEngineFile('tool/mail.js');

        /* Load item */
        $this->articleitem->id = $content;
        $this->articleitem->get($camyks->current_language);
        $this->articleitem->get_fromItems();

        /* Load author */
        $this->articleAuthor = $camyks->modules['Admin_User']->get_userNameAndEmail($this->articleitem->vars['author']);

        if ($this->articleAuthor['firstname'] == '' and $this->articleAuthor['lastname'] == '') {
            $this->articleAuthor['display'] = $this->articleAuthor['login'];
        } else if ($this->articleAuthor['firstname'] == '') {
            $this->articleAuthor['display'] = $this->articleAuthor['lastname'];
        } else if ($this->articleAuthor['lastname'] == '') {
            $this->articleAuthor['display'] = $this->articleAuthor['firstname'];
        } else {
            $this->articleAuthor['display'] = $this->articleAuthor['firstname'].' '.$this->articleAuthor['lastname'];
        }

        if ($this->articleAuthor['email'] != '') {
            $name = $this->articleAuthor['display'];
            $this->articleAuthor['display'] = '<a class="title3" href="'.mail_encode($this->articleAuthor['email']).'">'.$name.'</a>';
        }

        /* Update layout */
        $this->set_selectedLayout('site_'.$this->articleitem->vars['layout'].'.html.inc');

        /* Generic site initialisation */
        parent::init_site();
    }

    /* Specific admin mode methods */

    /**
     * Initialise module object in admin/modify_item mode.
     * @return void
     */
    private function init_admin_modify_item() {
        global $camyks;

        /* Check editor availability */
        if (!isset($camyks->inputs['TinyMCEv3']) and !isset($camyks->inputs['TinyMCE']))
            return $this->init_admin_missingPlugin('Input', 'TinyMCEv3');

        /* Load help */
        $this->get_help();

        /* Load object */
        $this->articleitem->get(true);
        $this->articleitem->get_fromItems();

        /* get tabs description */
        $this->tabs = array(array(
            'name'  => 'general',
            'title' => $this->get_translation('tabgeneral'),
        ));

        /* Add all available language for edition tabs */
        foreach ($camyks->get_confValue('editing_languages') as $l) {
            $this->tabs[] = array(
                'name'  => $l,
                'title' => language_getIcon($l),
            );
        }

        /* Add help tab */
        if ($this->help != null) {
            $this->tabs[] = array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help'),
            );
        }

        /* Load tabs javascript engine */
        $this->tabObject = 'article_tabObject';
        $this->add_JSEngineFile ('object/ctab.js');
        $this->add_JSScript($this->tabObject.' = new CTab();');
        $this->add_JSScript($this->tabObject.'.init("general", "'
            .$this->theme->parts['boxTabCSSStandart'].'","'
            .$this->theme->parts['boxTabCSSSelected'].'","'
            .$this->theme->parts['boxTabCSSRollover'].'");');

        /* Build form */
        $this->form = new HTMLForm('genericarticle_form', $this->get_adminlink(array('mode'=>'save_item')), 'POST');
        $this->form->add_hidden('page_id', $this->page_id);
        $this->form->add_hidden('module_index', $this->module_index);
        $this->form->add_hidden('id', $this->articleitem->id);

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
                'link'  => $this->form->get_HTMLSubmitLink()
            ),
        );

        /* Load user list */
        $this->adminList = $camyks->modules['Admin_User']->get_activeUserList();

        /* Load tiny_mce input */
        if (isset($camyks->inputs['TinyMCEv3'])) {
            $this->input = &$camyks->inputs['TinyMCEv3'];
        } elseif (isset($camyks->inputs['TinyMCE'])) {
            $this->input = &$camyks->inputs['TinyMCE'];
            $this->input->set_configInfos('default');
        }

        /* Initialise input */
        $this->input->initialise();
    }

    /**
     * Initialise module object in admin/save_item mode
     * @return void
     */
    private function init_admin_save_item() {
        global $camyks;

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* save article */
        $this->articleitem->get_fromHeader();
        if ($this->articleitem->save()) {
            /* Update page information with object id for new content */
            if ($this->articleid == 0 and $this->page_id > 0)
                $this->add_moduleContentToPage($this->page_id, $this->module_index, $this->articleitem->id);

            $this->text = $camyks->get_translation('savedone');
        } else {
            $this->text = $camyks->get_translation('savefailed');
        }
        $this->articleitem->get_fromItems();

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('mode'=>'modify_item', 'id'=>$this->articleitem->id)));
    }
}
?>
