<?php
/**
 * @brief Content_GenericPetitionViewer module.
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
 * Content_GenericPetitionViewer class.
 */
final class Content_GenericPetitionViewer extends Module {
    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('Content_GenericPetitionViewer', $path_type);

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
        $this->load_library('Content_GenericPetitionViewerItem');

        /* Initialise plugin libraries */
        $this->configItem = new Content_GenericPetitionViewerItem(0, $this);
    }

    /* Override Module methods */

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

        /* Load mode to execute */
        $this->mode = isset($_REQUEST['mode']) ? $_REQUEST['mode'] : 'edit';

        /* Initialise module with mode */
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

        /* Generic module initialise */
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

        /* Add email management javascripts */
        $this->add_JSEngineFile('tool/mail.js');

        /* Save params */
        $this->params = $params;

        /* Load manager */
        $this->load_petitionManager();

        /* Load sign object */
        $this->signItem = &$this->manager->signatureItem;

        /* Check for signature saving */
        if (isset($params['save']) and $params['save'] == 'sign') {
            if ($this->signItem->save_fromSite()) {
                $this->saveMode = 'success';
                $this->signItem->id = 0;
                $this->signItem->get();
            } else {
                $this->saveMode = 'failure';
                $this->saveError = $this->signItem->_libError;
                $this->add_JSLoadScript('popup_openModal("signpopup");');
            }
        } else {
            $this->saveMode = 'null';
            $this->signItem->id = 0;
            $this->signItem->get();
        }
        $this->signItem->get_fromItems();

        /* Load news list to display */
        $this->configItem->id = $content;
        $this->configItem->get();
        $this->configItem->get_fromItems();

        /* Load petition data */
        $this->petitionItem = &$this->manager->petitionItem;
        $this->petitionItem->id = $this->configItem->vars['petition'];
        $this->petitionItem->get($camyks->current_language);
        $this->petitionItem->get_fromItems();
        $this->petitionItem->get_signCount();

        /* Load sign page controller */
        $p = array();
        $p['pageCurrent'] = isset($params['page'])?$params['page']:0;
        $p['pageCount'] = ceil($this->petitionItem->vars['signs'] / (int)$this->configItem->vars['signcount']);
        $p['pageParams'] = array($camyks->contentPage->id, $camyks->current_language, array());
        $p['pageParam'] = 'page';
        $p['hideEmpty'] = 1;
        $p['buttonSource'] = 'theme';
        $p['styleSource'] = 'theme';

        /* Check current page */
        if ($p['pageCurrent'] >= $p['pageCount'])
            $p['pageCurrent'] = 0;

        /* Load sia page controller */
        $this->pageController = &$camyks->inputs['GenericPageController'];
        $this->pageController->initialise($p);

        /* Load sign list */
        $sParams = array(
            'status'    => 1,
            'petition'  => $this->petitionItem->id,
            'order'     => 'signdate',
            'orderway'  => 'desc',
            'limit'     => $p['pageCurrent']*$this->configItem->vars['signcount'],
            'count'     => $this->configItem->vars['signcount'],
        );
        $this->signList = $this->manager->get_signatureList($sParams);

        /* Load sign form */
        $this->signform = new HTMLForm('signform', 'javascript:void(0);', 'POST');
        $this->signform->set_parent($this);
        $this->signform->set_object($this->signItem);
        $this->signform->add_hidden('petition', $this->petitionItem->id);
        $this->add_JSLoadScript('document.signform.action="'.$camyks->get_siteLink($camyks->contentPage->id, '', null, array('save'=>'sign')).'"');
        $this->add_JSEngineFile('tool/popup.js');

        /* Update layout */
        $this->set_selectedLayout('site_'.$this->configItem->vars['layout'].'.html.inc');

        /* Parent site initialisation */
        parent::init_site();
    }

    /* Specific mode methods */

    /**
     * Initialise module in admin / edit mode.
     * @return void
     */
    public function init_admin_edit() {
        global $camyks;

        /* Load object */
        $this->configItem->id = isset ($_REQUEST['id']) ? (int)$_REQUEST['id'] : 0;
        $this->configItem->get();
        $this->configItem->get_fromItems();

        /* Load manager */
        $this->load_petitionManager();

        /* get edition languages */
        $this->elgs = $camyks->get_confValue('editing_languages');

        /* Load data */
        $this->petitionList = $this->manager->get_petitionTitleList(array('status'=>'>0'));

        /* Load form object */
        $this->form = new HTMLForm('editform', $this->get_adminlink(array('mode'=>'save')), 'POST');
        $this->form->set_object($this->configItem);
        $this->form->add_hidden('id', $this->configItem->id);
        $this->form->add_hidden('page_id', $this->page_id);
        $this->form->add_hidden('module_index', $this->module_index);

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

    /**
     * Initialise module in admin / save mode.
     * @return void
     */
    public function init_admin_save() {
        global $camyks;

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* get object id */
        if (!(isset($_REQUEST['id'])))
            $this->init_admin_edit();

        /* Load object */
        $this->configItem->id = (int)$_REQUEST['id'];
        $this->configItem->get_fromHeader();

        /* Save object */
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
     * Return layout list.
     * @return array
     */
    public function get_layoutList() {
        return array('nobox'=>$this->get_translation('layout_nobox'));
    }

    /* Specific tool methods in site mode */

    /**
     * Load blog manager module.
     * @return void
     */
    public function load_petitionManager() {
        global $camyks;

        /* Load petition manager */
        $this->manager = $camyks->get_module('Admin_GenericPetitionManager');

        if ($this->manager === false)
            die();
    }
}
?>
