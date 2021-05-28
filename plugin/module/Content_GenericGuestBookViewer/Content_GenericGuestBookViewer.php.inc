<?php
/**
 * @brief Content_GenericGuestBookViewer module.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Sep 2010
 * @date Modification: May 2021
 * @copyright 2010 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_GenericGuestBookViewer class.
 */
final class Content_GenericGuestBookViewer extends Module {
    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('Content_GenericGuestBookViewer', $path_type);

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
        $this->load_library('Content_GenericGuestBookViewerItem');

        /* Initialise plugin libraries */
        $this->configItem = new Content_GenericGuestBookViewerItem(0, $this);
    }

    /* overwrite Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return $this->configItem->install() and parent::install();
    }

    /**
     * Uninstall module.
     * @return boolean success
     */
    public function uninstall() {
        return $this->configItem->uninstall();
    }

    /**
     * Check module installation.
     * @return boolean result
     */
    public function is_installed() {
        return $this->configItem->is_installed();
    }

    /**
     * Return available content ids as list.
     * @return array
     */
    public function get_contentList() {
        return $this->configItem->get_namelist();
    }

    /**
     * Initialise module object in admin mode.
     * @return void
     */
    public function init_admin() {
        global $camyks;

        /* Generic pre-initialisation */
        parent::preInit_admin();

        /* Check right for this page */
        if ($this->check_right($this->page_id) === false)
            return $this->init_admin_pageAccessDenied();

        /* Check dependencies */
        if (!isset($camyks->inputs['TabBuilder']))
            return $this->init_admin_missingPlugin('Input', 'TabBuilder');
        if (!isset($camyks->inputs['TinyMCEv3']))
            return $this->init_admin_missingPlugin('Input', 'TinyMCEv3');

        /* Load action to execute */
        $this->mode = isset ($_REQUEST['mode']) ? $_REQUEST['mode'] : 'edit';

        /* Execute action */
        switch ($this->mode) {
            case 'save' :
                /* mode == save */
                $this->init_admin_save();
                break;
            case 'edit' :
            default:
                /* mode == edit */
                $this->init_admin_edit();
                break;
        }

        /* Generic module initialisation */
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
        /* Add email management javascripts */
        $this->add_JSEngineFile('tool/mail.js');

        /* Load manager */
        $this->load_guestBookManager();
        $this->msgItem = $this->manager->get_messageObject();
        $this->mdgItem->isLoaded = false;

        /* Load config */
        $this->configItem->id = $content;
        $this->configItem->get();
        $this->configItem->get_fromItems();

        /* Load action to execute */
        $mode = isset($params['msg']) ? $params['msg'] : 'list';

        /* Execute action */
        switch ($mode) {
            case 'save':
                $this->init_site_save_message();
                break;
            case 'add':
                $this->init_site_add_message();
                break;
            case 'list':
            default:
                $this->init_site_list_message($params);
                break;
        }
    }

    /**
     * Initialise module object in site / save message mode.
     * @return void
     */
    private function init_site_save_message() {
        /* Attempt to save message */
        if ($this->manager->save_siteMessage()) {
            /* Update layout*/
            $this->set_selectedLayout('site_message_'.$this->configItem->vars['layout'].'.html.inc');
            return true;
        }

        /* Load message fo re-edition */
        $this->msgItem->get_fromItems();
        $this->msgItem->isLoaded = true;
        return $this->init_site_add_message();
    }

    /**
     * Initialise module object in site / add message mode.
     * @return void
     */
    private function init_site_add_message() {
        /* Load message data */
        if ($this->msgitem->isLoaded == false)
            $this->msgItem->initialise();

        /* Check for form display */
        if ($this->configItem->vars['formlayout']==1)
            return $this->init_site_list_message();

        /* Load message edition form */
        $this->get_messageForm();

        /* Update layout */
        $this->set_selectedLayout('site_form_'.$this->configItem->vars['layout'].'.html.inc');
    }

    /**
     * Init module object in site / list message mode.
     * @param array $params
     * @return void
     */
    private function init_site_list_message($params) {
        global $camyks;

        /* Check for popup usage */
        if ($this->configItem->vars['formlayout'] == 1){
            /* Load popup engine */
            $this->add_JSEngineFile('tool/popup.js');

            /* Load message edition form */
            $this->get_messageForm();

            /* Check for automatic popup opening */
            if ($this->msgItem->isLoaded == true)
                $this->add_JSLoadScript('popup_openModal("msgpopup");');
        }

        /* Count message total */
        $this->msgCount = $this->manager->count_messages(array('status'=>1));

        /* Build params list */
        $p = array();
        $p['pageCurrent'] = isset($params['page'])?$params['page']:0;
        $p['pageCount'] = ceil($this->msgCount/(int)$this->configItem->vars['msgcount']);

        /* Check current page */
        if ($p['pageCurrent'] >= $p['pageCount'])
            $p['pageCurrent'] = 0;

        /* Add page controller params */
        if (isset($camyks->inputs['GenericPageController'])) {
            /* Load message list page controller */
            $p['pageParams'] = array($camyks->contentPage->id, $camyks->current_language, array());
            $p['pageParam'] = 'page';
            $p['hideEmpty'] = 1;
            if ($this->configItem->vars['gpcstyle'] == 0) {
                $p['buttonSource'] = 'theme';
                $p['styleSource'] = 'theme';
            } else {
                $p['buttonSource'] = 'plugin';
                $p['styleSource'] = 'plugin';
            }

            /* Load page controller */
            $this->pageController = &$camyks->inputs['GenericPageController'];
            $this->pageController->initialise($p);
        } else {
            $this->pageController = false;
        }

        /* Load sign list */
        $this->msgList = $this->manager->get_messageList(array('status'=>1, 'order'=>'edate', 'orderway'=>'desc', 'limit' => $p['pageCurrent']*$this->configItem->vars['msgcount'], 'count' => $this->configItem->vars['msgcount']));

        /* Update layout */
        $this->set_selectedLayout('site_'.$this->configItem->vars['layout'].'.html.inc');

        /* Parent site init */
        parent::init_site();
    }

    /* Specific mode methods */

    /**
     * Initialise module in admin / edit mode.
     * @return void
     */
    private function init_admin_edit() {
        global $camyks;
        /* Get object id */
        $id = isset ($_REQUEST['id']) ? (int)$_REQUEST['id'] : 0;

        /* Load object data */
        $this->configItem->id = $id;
        $this->configItem->get(true);
        $this->configItem->get_fromItems();

        /* Load manager */
        $this->load_guestBookManager();

        /* Load edition languages */
        $this->lgs = $camyks->get_confValue('editing_languages');

        /* Get form object */
        $this->form = new HTMLForm('editform', $this->get_adminlink(array('mode'=>'save')), 'POST');
        $this->form->set_object($this->configItem);
        $this->form->add_hidden('id', $this->configItem->id);
        $this->form->add_hidden('page_id', $this->page_id);
        $this->form->add_hidden('module_index', $this->module_index);

        /* Get tabs */
        $this->tabBuilder = $camyks->get_input('TabBuilder');

        /* Add properties tab */
        $this->tabBuilder->add_tab(array(
            'name'  => 'properties',
            'title' => $this->get_translation('tabproperties'),
        ));
        if (count($this->lgs) == 1)
            $this->tabBuilder->add_tab(array(
                'name'=>$this->lgs[0],
                'title'=>$this->get_translation('tabcontent'),
            ));
        else
            foreach ($this->lgs as $l)
                $this->tabBuilder->add_tab(array(
                    'name'=>$l,
                    'title'=>language_getIcon($l),
                ));

        /* Add help tab */
        if ($this->help != null)
            $this->tabBuilder->add_tab(array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help'),
            ));

        /* Initialise tabs */
        $this->tabBuilder->initialise(array('default'=>'properties'));

        /* Load editor */
        $this->editor = $camyks->get_input('TinyMCEv3');
        $this->editor->initialise();

        /* Build interface buttons */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'  => $camyks->get_adminLink('Admin_ContentPage', array(
                    'mode'=>'modify',
                    'page_id'=> $this->page_id,
                    'openTab'=>'content'
                )),
            ),
            array(
                'title' => $camyks->get_translation('valid'),
                'link'  => $this->form->get_HTMLSubmitLink(),
            ),
        );
    }

    /**
     * Initialise module in admin / save mode.
     * @return void
     */
    private function init_admin_save() {
        global $camyks;

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Load object id */
        if (!(isset($_REQUEST['id'])))
            $this->init_admin_edit();

        /* save object */
        $this->configItem->id = (int)$_REQUEST['id'];
        $this->configItem->get_fromHeader();
        if ($this->configItem->save()) {
            /* Update page information with object id for new content */
            if ($id == 0 and $this->page_id > 0)
                $this->add_moduleContentToPage($this->page_id, $this->module_index, $this->configItem->id);
            $this->text = $this->get_translation('savedone');
        } else {
            $this->text = $this->get_translation('savefailed');
        }

        /* Redirect save page */
        $this->set_redirect($this->get_adminLink(array('mode'=>'edit', 'id'=>$this->configItem->id)));

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
    }

    /**
     * Return config layout list.
     * @return array
     */
    public function get_configLayoutList() {
        return $this->configItem->get_layoutList();
    }

    /**
     * Return config form layout list.
     * @return array
     */
    public function get_configFormLayoutList() {
        return $this->configItem->get_formLayoutList();
    }

    /**
     * Return config GPC style list.
     * @return array
     */
    public function get_configGPCStyleList() {
        return $this->configItem->get_gpcStyleList();
    }

    /* Specific tool methods in site mode */

    /**
     * Load blog manager module.
     * @return void
     */
    public function load_guestBookManager() {
        global $camyks;

        /* Load guestbook manager */
        $this->manager = $camyks->get_module('Admin_GenericGuestBookManager');

        /* Check manager */
        if ($this->manager === false)
            die();
    }

    /**
     * Return add message link.
     * @return string
     */
    public function get_newMessageLink() {
        global $camyks;
        if ($this->configItem->vars['formlayout'] == 1)
            return 'javascript:popup_openModal(\'msgpopup\');';
        return $camyks->get_siteLink($camyks->contentPage->id, '', '', array('msg'=>'add'));
    }

    /**
     * Return message list link.
     * @return string
     */
    public function get_messageListLink() {
        global $camyks;
        return $camyks->get_siteLink($camyks->contentPage->id);
    }

    /**
     * Load message edition form.
     * @return void
     */
    public function get_messageForm() {
        global $camyks;

        $this->msgform = new HTMLForm('msgform', 'javascript:void(0);', 'POST');
        $this->msgform->set_parent($this);
        $this->msgform->set_object($this->msgItem);
        $this->add_JSLoadScript('document.msgform.action="'.$camyks->get_siteLink($camyks->contentPage->id, '', null, array('msg'=>'save')).'?preview=forced";');
    }
}
?>
