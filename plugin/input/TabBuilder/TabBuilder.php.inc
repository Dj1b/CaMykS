<?php
/**
 * @brief TabBuilder Input
 * <br /> Manages tabs.
 * @details Plugin / Input Engine
 * @file plugin/input/TabBuilder/TabBuilder.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Sep 2008
 * @date Modification: Jul 2018
 * @copyright 2008 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * TabBuilder Input class.
 */
final class TabBuilder extends Input {
    /**
     * var array $params
     * @brief Plugin parameters.
     */
    public $params = null;

    /**
     * var array $tabs
     * @brief Tab list.
     */
    public $tabs = array();

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('TabBuilder', $path_type);

        /* overwrite Plugin information */
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';
    }

    /* overwrite Input methods */

    /**
     * Initialise object.
     * @param array $params
     * @return void
     */
    public function initialise($params=array()) {
        /* get params */
        $this->params = $params;

        /* check parameters */
        $this->_check_params();

        /* check for opened tab */
        if (isset($_REQUEST['openTab']) and isset($this->tabs[$_REQUEST['openTab']])) {
            $this->params['default'] = $_REQUEST['openTab'];
        }

        /* initialise tabs */
        $this->add_JSEngineFile('object/ctab.js');
        $this->add_JSScript($this->params['name'].' = new CTab();');
        $this->add_JSScript($this->params['name'].'.init("'.$this->params['default'].'", "'
            .$this->params['theme']->parts['boxTabCSSStandart'].'","'
            .$this->params['theme']->parts['boxTabCSSSelected'].'","'
            .$this->params['theme']->parts['boxTabCSSRollover'].'");');

        /* build JS params */
        $this->jsParams = array(
            'clic'      => $this->params['name'].'.mouseclick',
            'mover'     => $this->params['name'].'.mouseover',
            'mout'      => $this->params['name'].'.mouseout',
            'selected'  => $this->params['default'],
        );
    }

    /* specific methods */

    /**
     * Add a single tab to tab list.
     * @param mixed $tab
     * @param string $title
     * @return void
     */
    public function add_tab($tab, $title='') {
        if (is_array($tab))
            $this->tabs[$tab['name']] = $tab;
        else
            $this->tabs[$tab] = array('name'=>$tab, 'title'=>$title);
    }

    /**
     * Add tabs to tab list.
     * @param array $tabs
     * @return void
     */
    public function add_tabs($tabs) {
        foreach ($tabs as $tab) {
            $this->add_tab($tab);
        }
    }

    /**
     * Return given tab display status.
     * @param string $tab
     * @return string
     */
    public function get_tabDisplay($tab) {
        if ($this->params['default'] === $tab)
            return 'block';
        return 'none';
    }

    /**
     * Check parameters.
     * @return void
     */
    private function _check_params() {
        global $camyks;

        /* check if tabs is an array */
        if (!is_array($this->tabs)) {
            $this->tabs = array();
            return;
        }

        /* check name */
        if (!isset($this->params['name']))
            $this->params['name'] = 'genTabsObject';

        /* check theme */
        if (!isset($this->params['theme']))
            if ($camyks->mode == CAMYKS_MODE_ADMIN)
                $this->params['theme'] = &$camyks->themes[$camyks->_conf['admin_default_theme']];
            else
                $this->params['theme'] = &$camyks->themes[$camyks->_conf['site_default_theme']];

        /* check default opened tab */
        if (!isset($this->params['default']) or !isset($this->tabs[$this->params['default']])) {
            foreach($this->tabs as $tab) {
                $this->params['default'] = $tab['name'];
                break;
            }
        }

        /* check request parameters */
        if (!isset($this->params['param']))
            $this->params['param'] = 'openTab';
    }
}
?>
