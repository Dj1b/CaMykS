<?php
/**
 * @brief Admin_LanguageChecker module.
 * <br /> Development module to check missing locales.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Nov 2006
 * @date Modification: Jul 2025
 * @copyright 2006 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_LanguageChecker class.
 */
final class Admin_LanguageChecker extends Module {
    /* variables */
    var $locales;
    var $langs;
    var $list;
    var $items;
    var $prefix;
    var $defaultTab;

    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('Admin_LanguageChecker', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'Development';

        /* Override Module variables */
        $this->type = 'admin';
        $this->admin_type = 'devel';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Load library */
        $this->load_library('Admin_LanguageCheckerEngine');
    }

    /* Mark: Override Module methods */

    /**
     * Define module permissions
     * @return void
     */
    public function get_rights() {
        global $camyks;
        $this->rights[0] = array(
            'name'      => 'read',
            'title'     => $camyks->get_translation('read'),
            'default'   => false,
        );
    }

    /**
     * Initialise module object in admin mode.
     * @return void
     */
    public function init_admin() {
        /* Check user permission */
        if ($this->check_right(0) === false) {
            return $this->init_admin_accessDenied();
        }

        /* Load action to execute */
        $this->mode = isset($_REQUEST['mode']) ? $_REQUEST['mode'] : 'list';

        /* Execute action */
        switch ($this->mode) {
            case 'checker' :
                $this->init_admin_checker();
                break;
            case 'list' :
            default :
                $this->init_admin_list();
                break;
        }

        /* Perform generic initalisation */
        parent::init_admin();
    }

    /* Mark: Admin initialise mode sub methods */

    /**
     * Initialise module object in admin/checker mode.
     * @return void
     */
    private function init_admin_checker() {
        global $camyks;

        /* Initialise variables */
        $this->locales = array();
        $view = $_REQUEST['view'];
        $type = $_REQUEST['type'];
        $this->items = array();

        /* Load folder */
        if ($type == 'engine' and $view == 'camyks') {
            $folder = $camyks->camyks_engine_path.'/locale';
        } else if ($type == 'engine') {
            $folder = $camyks->camyks_engine_path.'/locale/'.$view;
        } else if ($type == 'module') {
            $folder = $camyks->modules[$view]->plugin_path.'/locale';
        } else if ($type == 'input') {
            $folder = $camyks->inputs[$view]->plugin_path.'/locale';
        }

        /* Load available languages for folder */
        $languages = array_merge($camyks->get_confValue('editing_languages'), language_getDictionnaryList($folder));

        foreach ($languages as $language) {
            $this->locales[$language] = new Admin_LanguageCheckerEngine($folder, $language);

            /* Build item list */
            foreach ($this->locales[$language]->trads as $item => $value) {
                if (!in_array($item, $this->items)) {
                    $this->items[] = $item;
                }
            }
        }

        /* Sort items */
        sort($this->items);

        /* get prefix */
        foreach ($this->items as $i) {
            $this->prefix = $i;
            break;
        }
        foreach ($this->items as $i) {
            $this->prefix = string_getSimilarBeginning($i, $this->prefix);
        }

        /* Load default tab */
        $this->defaultTab = '';
        foreach ($this->locales as $l=>$v) {
            $this->defaultTab = 'lang'.$l;
            break;
        }

        /* Load tab engine */
        $this->tabObject = 'admin_languagechecker_tabObject';
        $this->add_JSEngineFile('object/ctab.js');
        $this->add_JSScript($this->tabObject.' = new CTab();');
        $this->add_JSScript($this->tabObject.'.init("'.$this->defaultTab.'", "'.$camyks->theme->parts['boxTabCSSStandart'].'", "'.$camyks->theme->parts['boxTabCSSSelected'].'", "'.$camyks->theme->parts['boxTabCSSRollover'].'");');

        /* Build tabs */
        $this->tabs = array();
        foreach ($this->locales as $l => $v) {
            $this->tabs[] = array(
                'name'  => 'lang'.$l,
                'title' => language_getIcon($l),
            );
        }

        /* Build interface buttons */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'  => $this->get_adminLink(),
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('checker.html.inc');
    }

    /**
     * Initialise module object in admin/list mode
     * @return void
     */
    private function init_admin_list() {
        global $camyks;
        $this->list = array();

        /* Add camyks global locales */
        $this->list['camyks'] = array('type'=>'engine', 'title' => 'CaMykS');

        /* Add camyks dedicated locales */
        $folders = folder_listFolders($camyks->camyks_engine_path.'/locale');
        foreach ($folders as $folder)
            $this->list[$folder] = array('type'=>'engine', 'title' => ' / '.$folder);

        /* Add modules */
        foreach ($camyks->modules as $m) {
            $this->list[$m->name] = array('type'=>'module', 'title' => $m->title);
        }

        /* Add inputs */
        foreach ($camyks->inputs as $m) {
            $this->list[$m->name] = array('type'=>'input', 'title' => $m->name);
        }

        /* Build interface buttons */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'  => $camyks->get_adminLink(),
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('list.html.inc');
    }
}
?>
