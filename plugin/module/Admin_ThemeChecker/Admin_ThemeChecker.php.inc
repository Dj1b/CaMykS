<?php
/**
 * @brief Admin_ThemeChecker Module
 * <br /> Check parts managed by themes.
 * @details Plugin, Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jul 2007
 * @date Modification: Jan 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_ThemeChecker class.
 */
final class Admin_ThemeChecker extends Module {
    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('Admin_ThemeChecker', $path_type);

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
    }

    /* Override Module methods */

    /**
     * Define module permissions.
     * @return void
     */
    public function get_rights() {
        global $camyks;
        $this->rights[0] = array(
            'name'      =>'read',
            'title'     => $camyks->get_translation('read'),
            'default'   => false,
        );
    }

    /**
     * Initialise module object in admin mode
     * @return void
     */
    public function init_admin() {
        /* Check read permission */
        if ($this->check_right(0) === false)
            return $this->init_admin_accessDenied();

        /* Load action to execute */
        $this->mode = isset($_REQUEST['mode']) ? $_REQUEST['mode'] : 'list';
        switch ($this->mode) {
            case 'checker' :
                $this->init_admin_checker();
                break;
            case 'list' :
            default :
                $this->init_admin_list();
                break;
        }

        /* Perform generic initialisation */
        parent::init_admin();
    }

    /* specific admin mode methods */

    /**
     * Initialise module object in admin/checker mode.
     * @return void
     */
    private function init_admin_checker() {
        global $camyks, $global_theme_picts_items;

        $view = isset ($_REQUEST['view']) ? $_REQUEST['view'] : '';
        if (isset($camyks->themes[$view])) {
            $this->seltheme = $camyks->get_theme($view);
        } else {
            return $this->init_admin_list();
        }

        /* list objects to check */
        $files = array('style.css', 'parts.php.inc', 'parts.css', 'editor.css');
        $parts = array(
            'bar'           => array('barLeft', 'barRight', 'barButton', 'barItem'),
            'box'           => array('boxHeader', 'boxTitleBar', 'boxTabsBarHeader','boxTab', 'boxTabSelected', 'boxTabCSSStandart', 'boxTabCSSSelected', 'boxTabCSSRollover', 'boxTabsBarFooter', 'boxButtonsBarHeader', 'boxButtonWithLink', 'boxButtonWithoutLink', 'boxButtonsBarFooter', 'boxContent1Header', 'boxContent1Footer', 'boxContent2Header', 'boxContent2Footer',    'boxFooter'),
            'button'        => array('button'),
            'layeredmenu'   => array('layeredMenuHeader', 'layeredMenuSeparator', 'layeredMenuNoLinkItem', 'layeredMenuLinkItem', 'layeredMenuFooter'),
        );

        /* data & file check */
        $this->infos = array(
            'name'          => $this->seltheme->name,
            'title'         => $this->seltheme->title,
            'version'       => $this->seltheme->version,
            'author'        => $this->seltheme->author_name,
        );

        $this->files = array();
        foreach ($files as $f) {
            $this->files[] = array(
                'name'      => $f,
                'exists'    => (file_exists($this->seltheme->plugin_path.'/'.$f) or file_exists($this->seltheme->plugin_path.'/css/'.$f)),
            );
        }

        /* check parts item */
        $this->seltheme->get_parts();
        $this->parts = array();
        foreach ($parts as $n => $part) {
            $this->parts[$n] = array();
            $this->eparts[$n] = true;
            foreach ($part as $item) {
                $p = isset ($this->seltheme->parts[$item]);
                $this->parts[$n][$item] = $p;
                $this->eparts[$n] = ($this->eparts[$n] and $p);
            }
        }

        /* check picts images */
        $this->picts = array();
        $this->maxpos = 0;
        foreach ($global_theme_picts_items as $size => $list) {
            $this->picts[$size] = array();
            $this->maxpos = max ($this->maxpos, count($list['positions']));
            foreach ($list['items'] as $img) {
                $this->picts[$size][$img] = array();
                foreach ($list['positions'] as $pos)
                    $this->picts[$size][$img][$pos] = file_exists($this->seltheme->plugin_path.'/img/picts/'.$size.'_'.$img.'_'.$pos.'.gif');
            }
        }

        /* Build demo elements */
        $this->add_JSScript('demo_tabObject = new CTab();');
        $this->add_JSScript('demo_tabObject.init("demotab1", "'.(isset($this->seltheme->parts['boxTabCSSStandart']) ? $this->seltheme->parts['boxTabCSSStandart'] : '').'", "'.(isset($this->seltheme->parts['boxTabCSSSelected']) ? $this->seltheme->parts['boxTabCSSSelected'] : '').'", "'.(isset($this->seltheme->parts['boxTabCSSRollover']) ? $this->seltheme->parts['boxTabCSSRollover'] : '').'");');
        $this->demo_tabs = array(
            array(
                'name'  => 'demotab1',
                'title' => $this->get_translation('demo_tab', 1),
            ),
            array(
                'name'  => 'demotab2',
                'title' => $this->get_translation('demo_tab', 2),
            ),
        );

        $this->demo_buttons = array(
            array(
                'title' => $this->get_translation('demo_button', 1),
                'link'  => 'javascript:void(0);',
            ),
            array(
                'title' => $this->get_translation('demo_button', 2),
                'link'  => 'javascript:void(0);'
            ),
        );

        $this->demo_layeredmenu = array(
            array(
                'title' => $this->get_translation('demo_layeredmenu_line'),
                'url'   => 'javascript:void(0);',
                'icon'  => $this->theme->get_pictURL('edit', 12, 'std'),
            ),
            array(
                'title' => $this->get_translation('demo_layeredmenu_nolink'),
                'url'   => '',
                'icon'  => $this->theme->get_pictURL('cross', 12, 'std'),
            ),
            array(
                'title' => $this->get_translation('demo_layeredmenu_noicon'),
                'url'   => 'javascript:void(0);',
                'icon'  => '',
            ),
            array(
                'title' => '----',
                'url'   => '',
            ),
            array(
                'title' => $this->get_translation('demo_layeredmenu_line'),
                'url'   => 'javascript:void(0);',
                'icon'  => $this->theme->get_pictURL('valid', 12, 'std'),
            ),
        );
        $this->add_JSScript('var demomenu = new CMenu("demomenu", null, "demomenuButton", "bottom");');
        $this->add_JSScript('globalCMenu.registerMenu(demomenu);');

        /* Load tab engine */
        $openTab = isset($_REQUEST['openTab']) ? $_REQUEST['openTab'] : '';
        $this->tabObject = 'admin_themechecker_tabObject';
        $this->add_JSEngineFile('object/ctab.js');
        $this->add_JSScript($this->tabObject.' = new CTab();');
        $this->add_JSScript($this->tabObject.'.init("properties", "'.$camyks->theme->parts['boxTabCSSStandart'].'", "'.$camyks->theme->parts['boxTabCSSSelected'].'", "'.$camyks->theme->parts['boxTabCSSRollover'].'");');
        if ($openTab != '' and $openTab != 'properties')
            $this->add_JSLoadScript($this->tabObject.'.mouseclick(\''.$openTab.'\');');

        $this->tabs = array(
            array(
                'name'  => 'properties',
                'title' => $camyks->get_translation('properties'),
            ),
            array(
                'name'  => 'items',
                'title' => $this->get_translation('tabitems'),
            ),
            array(
                'name'  => 'picts',
                'title' =>  $this->get_translation('tabpicts'),
            ),
            array(
                'name'  => 'demo',
                'title' => $this->get_translation('tabdemo'),
            ),
        );

        /* Build interface buttons */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'  => $this->get_adminLink()
            ),
        );

        /* update layout */
        $this->set_selectedLayout('admin_checker.html.inc');
    }

    /**
     * Initialise module object in admin/list mode
     * @return void
     */
    private function init_admin_list() {
        global $camyks;

        /* Build interface buttons */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'  => $camyks->get_adminLink(),
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('admin_list.html.inc');
    }
}
?>
