<?php
/**
 * @brief Content_GenericGlossaryViewer module.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: May 2010
 * @date Modification: Jan 2020
 * @copyright 2010 - 2020 Ideogram Design
 */

/**
 * Content_GenericGlossaryViewer class.
 */
final class Content_GenericGlossaryViewer extends Module {
    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('Content_GenericGlossaryViewer', $path_type);

        /* Override Plugin variables */
        $this->plugin_package = 'Generic';
        $this->version = '1.0';

        /* Override Module variables */
        $this->type = 'content';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* load plugin libraries */
        $this->load_library('Content_GenericGlossaryViewerItem');

        /* Initialise plugin libraries */
        $this->configItem = new Content_GenericGlossaryViewerItem(0, $this);
    }

    /* Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return ($this->configItem->install() and parent::install());
    }

    /**
     * Uninstall module.
     * @return boolean success
     */
    public function uninstall() {
        return $this->configItem->uninstall();
    }

    /**
     * Check module installation
     * @return boolean result
     */
    public function is_installed() {
        return $this->configItem->is_installed();
    }

    /**
     * get available content ids as list
     * @return array
     */
    public function get_contentList() {
        return $this->configItem->get_namelist();
    }

    /**
     * init module object in admin mode
     * @return void
     */
    public function init_admin() {
        global $camyks;

        /* generic pre-initialisation */
        parent::preInit_admin();

        /* check right for this page */
        if ($this->check_right($this->page_id) === false)
            return $this->init_admin_pageAccessDenied();

        /* get mode */
        $this->mode = isset ($_REQUEST['mode']) ? $_REQUEST['mode'] : 'edit';

        /* initialise module with mode */
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
        /* generic module init */
        parent::init_admin();
    }

    /**
     * Initialise module object in site mode.
     * @return void
     */
    public function init_site($content=1, $params=array(), $mindex=null) {
        global $camyks;

        /* add email management javascripts */
        $this->add_JSEngineFile('tool/mail.js');

        /* save params */
        $this->params = $params;

        /* load manager */
        $this->load_glossaryManager();

        /* get news list to display */
        $this->configItem->id = $content;
        $this->configItem->get($camyks->current_language);
        $this->configItem->get_fromItems();

        /* get category list */
        $cParams = array('status'=>1);
        if ($this->configItem->vars['categories'] != '')
            $cParams['ids'] = $this->configItem->vars['categories_'];
        $this->categoryList = $this->manager->get_categoryTitleList(false, $cParams);

        /* initialise query params */
        $qParams = array();
        $qParams['categories'] = array_keys($this->categoryList);
        $qParams['status'] = 1;

        /* build page lists */
        switch($this->configItem->vars['pagemode']) {
            case 0 :
                /* By page */
                if (isset($camyks->inputs['GenericPageController'])) {

                /* Update params */
                $wordCount = $this->manager->count_words($qParams);
                $p = array();
                $p['pageCurrent'] = isset($params['page']) ? $params['page'] : 0;
                $p['pageCount'] = ceil($wordCount / (int)$this->configItem->vars['wordcount']);
                $p['pageParams'] = array($camyks->contentPage->id, $camyks->current_language, array());
                $p['pageParam'] = 'page';
                $p['hideEmpty'] = 1;

                if ($this->configItem->vars['gpc_source'] == 0) {
                    $p['buttonSource'] = 'theme';
                    $p['styleSource'] = 'theme';
                } else {
                    $p['buttonSource'] = 'plugin';
                    $p['styleSource'] = 'plugin';
                }

                /* check current page */
                if ($p['pageCurrent'] >= $p['pageCount'])
                    $p['pageCurrent'] = 0;

                /* load generic page controller */
                $this->pageController = &$camyks->inputs['GenericPageController'];
                $this->pageController->initialise($p);

                /* Update query params */
                $qParams['limit'] = $p['pageCurrent']*$this->configItem->vars['wordcount'];
                $qParams['count'] = $this->configItem->vars['wordcount'];
                break;
                }
            case 1:
                /* by letter */
                $this->pages = array();
                for ($i=ord('A'); $i<=ord('Z'); $i++)
                    $this->pages[chr($i)] = $this->get_pageLink(array('letter'=>chr($i)));
                if (isset($params['letter']))
                    $qParams['letters'] = $params['letter'];
                else
                    $qParams['letters'] = 'A';
                break;
            case 2:
                /* by group 1 */
                $this->pages = array();
                $this->pages['A-L'] = $this->get_pageLink(array('A'=>'L'));
                $this->pages['M-Z'] = $this->get_pageLink(array('M'=>'Z'));
                foreach ($params as $l1 => $l2) {
                    if (isset($this->pages[$l1.'-'.$l2]))
                        $qParams['letters'] = $l1.'-'.$l2;
                    elseif ($l1 == 'letter' and strlen($l2) == 1) {
                        $l = ord(strtoupper($l2));
                        if ($l >= ord('A') and $l <= ord('L'))
                            $qParams['letters'] = 'A-L';
                        elseif ($l >= ord('M') and $l <= ord('Z'))
                            $qParams['letters'] = 'M-2';
                    }
                }
                if (!isset($qParams['letters']))
                    $qParams['letters'] = 'A-L';
                    break;
            case 3:
                /* by group 2 */
                $this->pages = array();
                $this->pages['A-G'] = $this->get_pageLink(array('A'=>'G'));
                $this->pages['H-Q'] = $this->get_pageLink(array('H'=>'Q'));
                $this->pages['R-Z'] = $this->get_pageLink(array('R'=>'Z'));
                foreach ($params as $l1 => $l2) {
                if (isset($this->pages[$l1.'-'.$l2]))
                    $qParams['letters'] = $l1.'-'.$l2;
                elseif ($l1 == 'letter' and strlen($l2)==1) {
                    $l = ord(strtoupper($l2));
                    if ($l >= ord('A') and $l <= ord('G'))
                        $qParams['letters'] = 'A-G';
                    elseif ($l >= ord('H') and $l <= ord('Q'))
                        $qParams['letters'] = 'H-Q';
                    elseif ($l >= ord('R') and $l <= ord('Z'))
                        $qParams['letters'] = 'R-Z';
                    }
                }
                if (!isset($qParams['letters']))
                    $qParams['letters'] = 'A-G';
                break;
            case 4:
                /* by group 3 */
                $this->pages = array();
                $this->pages['A-D'] = $this->get_pageLink(array('A'=>'D'));
                $this->pages['E-L'] = $this->get_pageLink(array('E'=>'L'));
                $this->pages['M-S'] = $this->get_pageLink(array('M'=>'S'));
                $this->pages['T-Z'] = $this->get_pageLink(array('T'=>'Z'));
                foreach ($params as $l1 => $l2) {
                    if (isset($this->pages[$l1.'-'.$l2]))
                        $qParams['letters'] = $l1.'-'.$l2;
                    elseif ($l1 == 'letter' and strlen($l2)==1) {
                        $l = ord(strtoupper($l2));
                        if ($l >= ord('A') and $l <= ord('D'))
                            $qParams['letters'] = 'A-D';
                        elseif($l >= ord('E') and $l <= ord('L'))
                            $qParams['letters'] = 'E-L';
                        elseif($l >= ord('T') and $l <= ord('Z'))
                            $qParams['letters'] = 'T-Z';
                    }
                }
                if (!isset($qParams['letters']))
                    $qParams['letters'] = 'A-D';
                break;
        }

        /* load word list */
        $this->wordList = $this->manager->get_wordList($qParams);

        /* Update layout */
        $this->selected_layout = 'site_'.$this->configItem->vars['layout'].'.html.inc';

        /* parent site init */
        parent::init_site();
    }

    /* Specific mode methods */

    /**
     * Initialise module in admin / edit mode.
     * @return void
     */
    private function init_admin_edit() {
        global $camyks;
        /* get object id */
        $id = isset ($_REQUEST['id']) ? $_REQUEST['id'] : 0;

        /* get object data */
        $this->configItem->id = $id;
        $this->configItem->get();
        $this->configItem->get_fromItems();

        /* load manager */
        $this->load_glossaryManager();

        /* check for Inputs */
        $this->gpcAvailable = isset($camyks->inputs['GenericPageController']);

        /* get edition languages */
        $this->elgs = $camyks->get_confValue('editing_languages');

        /* load data */
        $this->categoryList = $this->manager->get_categoryTitleList(false, array('status'=>1));

        /* get tabs */
        $this->tabBuilder = &$camyks->inputs['TabBuilder'];

        /* add definitions tab */
        $this->tabBuilder->add_tab(
            array(
                'name'  => 'Properties',
                'title' => $camyks->get_translation('properties'),
            )
        );
        if (count($this->elgs) == 1)
            $this->tabBuilder->add_tab(
                array(
                    'name'  => $this->elgs[0],
                    'title' => $this->get_translation('tabcontent'),
                )
            );
        else
            foreach($this->elgs as $l)
                $this->tabBuilder->add_tab(
                    array(
                        'name'  => $l,
                        'title' => language_getIcon($l),
                    )
                );

        /* Load editor */
        $this->editor = $camyks->get_input('TinyMCEv3');
        $this->editor->initialise();

        /* add help tab */
        if ($this->help != null)
            $this->tabBuilder(
                array(
                    'name'  => 'help',
                    'title' => $camyks->get_translation('help'),
                )
            );

        /* initialise tabs */
        $this->tabBuilder->initialise(array('default'=>'Properties'));

        /* get form object */
        $this->form = new HTMLForm('editform', $this->get_adminlink(array('mode'=>'save')), 'POST');
        $this->form->set_object($this->configItem);
        $this->form->add_hidden('id', $this->configItem->id);
        $this->form->add_hidden('page_id', $this->page_id);
        $this->form->add_hidden('module_index', $this->module_index);
        $this->form->add_hidden('category_cnt', count($this->categoryList));

        /* load client-side scripts */
        $this->add_JSEngineFile('object/ctransition.js');
        $this->add_JSFile('genericglossaryviewer.js');
        $this->add_JSScript('var formName = "'.$this->form->name.'";');

        /* button interface */
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
     * Initialise module in admin / save mode
     * @return void
     */
    private function init_admin_save() {
        global $camyks;

        /* disable admin menus */
        $this->disable_adminEngineMenus();

        /* get object id */
        if (!(isset($_REQUEST['id'])))
            $this->init_admin_edit();
        $id = (int)$_REQUEST['id'];

        /* save object */
        $this->configItem->id = $id;
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
        $this->set_redirect($this->get_adminLink(array(
            'mode'          => 'edit',
            'id'            => $this->configItem->id,
            'page_id'       => $this->page_id,
            'module_index'  => $this->module_index,
        )));

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
    }

    /**
     * Return layout list.
     * @return array
     */
    protected function get_layoutList() {
        return array('nobox' => $this->get_translation('layout_nobox'));
    }

    /**
     * Return category list.
     * @return array
     */
    protected function get_categoryList() {
        return $this->manager->get_categoryTitleList(true);
    }

    /**
     * Return page mode list.
     * @param boolean $allowPageMode
     * @return array
     */
    protected function get_pageModeList($allowPageMode=false) {
        return $this->configItem->get_pageModeList($allowPageMode);
    }

    /* Specific tool methods in site mode */

    /**
     * Load glossary manager module.
     * @return void
     */
    private function load_glossaryManager() {
        global $camyks;
        $this->manager = $camyks->get_module('Admin_GenericGlossaryManager');
    }

    /**
     * Return generic status list.
     * @return array
     */
    private function get_genericStatusList() {
        return array(
            0   => $this->get_translation('status_disabled'),
            1   => $this->get_translation('status_enabled'),
        );
    }

    /**
     * Return GPC source list.
     * @return array
     */
    protected function get_configGPCSourceList() {
        return $this->configItem->get_gpcSourceList();
    }

    /**
     * build current page link
     * @param array $params
     * @param string $anchor
     * @return string
     */
    public function get_pageLink($params=array(), $anchor='') {
        global $camyks;
        $page = $camyks->contentPage->name;
        if ($anchor != '')
            return $camyks->get_siteLink($page, '', $camyks->current_language, array('letter'=>strtoupper(substr($anchor, 0, 1)))).'#'.$anchor;
        return $camyks->get_siteLink($page, '', $camyks->current_language, $params);
    }
}
?>
