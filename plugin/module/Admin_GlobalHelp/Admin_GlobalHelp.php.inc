<?php
/**
 * @brief Admin_GlobalHelp Module
 * <br /> Displays help for all plugins.
 * @details Plugin, Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Fev 2007
 * @date Modification: Jan 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GlobalHelp class.
 */
final class Admin_GlobalHelp extends Module {
    /**
     * var array $list
     * @brief List of available help files.
     */
    protected $list;

    /**
     * var mixed $help
     * @brief Link to help files.
     */
    public $help;

    /**
     * var string $htitle
     * @brief Help files title.
     */
    protected $htitle;

    /**
     * var string $hfile
     * @brief Help files name to display.
     */
    protected $hfile;

    /**
     * var string $location
     * @brief Help files location to display.
    */
    protected $location;

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('Admin_GlobalHelp', $path_type);

        /* Override Plugin variables */
        $this->plugin_package = 'Default';
        $this->version = '1.0';

        /* Override Module variables */
        $this->type = 'admin';
        $this->admin_type = 'helpers';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';
    }

    /* Override Module methods */

    /**
     * Define plugin permissions.
     * @return void
     */
    public function get_rights() {
        global $camyks;
        $this->rights[0] = array(
            'name'      => 'read',
            'title'     => $camyks->get_translation('read'),
            'default'   => true
        );
    }

    /**
     * Initialise object when in admin mode
     * @return void
     */
    public function init_admin() {
        global $camyks;

        /* Check read permission */
        if ($this->check_right(0) === false) {
            return $this->init_admin_accessDenied();
        }

        /* Load mode to execute */
        $this->mode = isset($_REQUEST['mode']) ? $_REQUEST['mode'] : 'list';

        /* Execute action */
        switch ($this->mode) {
            case 'display':
                /* Load header values */
                $this->location = isset ($_REQUEST['location']) ? $_REQUEST['location'] : '';
                $this->hfile = isset ($_REQUEST['hfile']) ? $_REQUEST['hfile'] : '';

                /* Check if given values are set */
                if ($this->location == '' or $this->hfile == '') {
                    $this->set_selectedLayout('admin_message.html.inc', 'camyks');
                    $this->text = $this->get_translation('nohelpfound');
                    $this->set_redirect(4, $this->get_adminLink());
                    break;
                }

                /* Build button list */
                $this->buttons = array(array(
                    'title' => $camyks->get_translation('back'),
                    'link'  => $this->get_adminLink(),
                ));

                /* Check if given value correspond to a help file */
                if ($this->location == 'engine' and $this->check_engineHelpFile($this->hfile)) {
                    $this->help_path = $camyks->camyks_engine_path.'/help/'.$this->hfile.'/'.$camyks->current_language.'/';
                    $this->set_selectedLayout('display_engine.html.inc');
                    $this->add_JSEngineFile('object/cmdd.js');
                    $this->add_JSScript(strtolower($this->name).'_helpObject = new Cmdd();');
                    $this->add_JSScript(strtolower($this->name).'_helpObject.init("'.$this->name.
                        '", "","'.$camyks->theme->parts['boxTabCSSStandart'].
                        '","'.$camyks->theme->parts['boxTabCSSSelected'].
                        '","'.$camyks->theme->parts['boxTabCSSRollover'].'");');

                    foreach ($this->help as $i => $v) {
                        $this->add_JSLoadScript(strtolower($this->name).'_helpObject.mouseclick(\''.$i.'\');');
                        break;
                    }

                } else if ($this->location == 'modules' and $this->check_modulesHelpFile ($this->hfile)) {
                    $this->help_path = $camyks->modules[$this->hfile]->plugin_path.'/help/'.$camyks->current_language.'/';
                    $this->set_selectedLayout('display_modules.html.inc');
                } else if ($this->location == 'site' and $this->check_siteHelpFile ($this->hfile)) {
                    $this->help_path = '';
                    $this->set_selectedLayout('display_modules.html.inc');
                } else {
                    $this->set_selectedLayout('admin_message.html.inc', 'camyks');
                    $this->text = $this->get_translation('nohelpfound');
                    $this->set_redirect(4, $this->get_adminLink());
                    break;
                }
                break;
            case 'list':
            default:
                $this->list = array();

                /* Load engine help list */
                $this->get_engineHelpList();

                /* Load module help list */
                $this->get_modulesHelpList();

                /* Load site help list */
                $this->get_siteHelpList();
                $this->set_selectedLayout('list.html.inc');

                /* Build button list */
                $this->buttons = array(array(
                    'title' => $camyks->get_translation('back'),
                    'link'  => $camyks->get_adminLink(),
                ));
                break;
        }

        /* Perform generic module */
        parent::init_admin();
    }

    /* Specific tool methods */

    /**
     * Load engine help files.
     * @return void
     */
    private function get_engineHelpList() {
        global $camyks;

        /* Initialise variables */
        $this->list['engine'] = array();
        $folder = $camyks->camyks_engine_path.'/help';

        /* Build list */
        if ($dir = @opendir($folder)) {
            $folders = array();
            while (($file = readdir ($dir)) !== false) {
                if (($file != '.') and ($file != '..') and    (is_dir($folder.'/'.$file))) {
                    if (file_exists($folder.'/'.$file.'/'.$camyks->current_language.'/help.php.inc')) {
                        require $folder.'/'.$file.'/'.$camyks->current_language.'/help.php.inc';
                        $this->list['engine'][$file] = array(
                            'title' => $this->htitle,
                            'link'    => $this->get_adminLink(array('mode'=>'display', 'location'=>'engine', 'hfile'=>$file)),
                        );
                    }
                }
            }
        }
    }

    /**
     * Load modules help files.
     * @return void
     */
    private function get_modulesHelpList() {
        global $camyks;

        /* Initialise variables */
        $this->list['modules'] = array();
        $hfile = 'help/'.$camyks->current_language.'/help.php.inc';

        foreach ($camyks->modules as $n => $m) {
            $m->load_file($hfile);
            if ($m->help != null) {
                $this->list['modules'][$n] = array(
                    'title' => $m->title,
                    'link'  => $this->get_adminLink(array('mode'=>'display', 'location'=>'modules', 'hfile'=>$n)),
                );
            }
        }
    }

    /**
     * Load site help files.
     * @return void
     */
    private function get_siteHelpList() {
        global $camyks;
        $this->list['site'] = array();
        /* TO DO */
    }

    /**
     * Check engine help files.
     * @return void
     */
    private function check_engineHelpFile($name) {
        global $camyks;
        if (file_exists($camyks->camyks_engine_path.'/help/'.$name.'/'.$camyks->current_language.'/help.php.inc')) {
            require $camyks->camyks_engine_path.'/help/'.$name.'/'.$camyks->current_language.'/help.php.inc';
            return true;
        }
        return false;
    }

    /**
     * Check modules help files.
     * @return void
     */
    private function check_modulesHelpFile($name) {
        global $camyks;
        if (!isset($camyks->modules[$name]))
            return false;

        $camyks->modules[$name]->get_help();
        $camyks->modules[$name]->init_parent_admin();
        $this->help = &$camyks->modules[$name]->help;

        if ($this->help != null)
            return true;
        return false;
    }

    /**
     * Check site help.
     * @return void
     */
    private function check_siteHelpFile($name) {
        /* TO DO */
    }
}
?>
