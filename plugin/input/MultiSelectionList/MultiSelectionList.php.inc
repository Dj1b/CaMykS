<?php
/**
 * @brief MultiSelectionList Input
 * <br /> Allows multi selection in a list.
 * @details Plugin / Input Engine
 * @file plugin/input/MultiSelectionList/MultiSelectionList.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Apr 2011
 * @date Modification: Apr 2018
 * @copyright 2011 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * MultiSelectionList Input class.
 * @author CaMykS Team <camyks.contact@gmail.com>
 */
final class MultiSelectionList extends Input {
    /**
     * var array $params
     * @brief Input parameters.
     */
    public $params = array(
        'name'              =>'MultiSelectionList',
        'fullList'          => array(), // (id => name) array
        'selList'           => array(), // id array
        'formName'          => '', // string
        'formItemName'      => '', // string
        'itemSeparator'     => ',', //sting
        'theme'             => '', // string
        'buttonSource'      => 'theme', // plugin | theme
        'selectedLayout'    => 'input.html.inc',
        'listTitle'         => '',
        'selectionTitle'    => '',
    );

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('MultiSelectionList', $path_type);
        /* set plugin version */
        $this->version = '1.0';
        /* set plugin package */
        $this->plugin_package = 'Default';
        /* set plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';
    }

    /* overwrite input methods */

    /**
     * Initialise input.
     * @param array $params
     * @return void
     */
    public function initialise($params=array()) {
        global $camyks;

        /* update parameters with loaded locales */
        $this->params['listTitle'] = $this->get_translation('listtitle');
        $this->params['selectionTitle'] = $this->get_translation('selectiontitle');

        /* merge parameters */
        $this->params = array_merge($this->params, $params);

        /* load theme if requiered */
        if ($this->params['buttonSource'] == 'theme') {
            if ($this->params['theme'] != '' and isset($camyks->themes[$this->params['theme']]))
                $this->theme = &$camyks->themes[$this->params['theme']];
            elseif ($camyks->mode == CAMYKS_MODE_ADMIN)
                $this->theme = &$camyks->themes[$camyks->get_confValue('admin_default_theme')];
            else
                $this->theme = &$camyks->themes[$camyks->get_confValue('site_default_theme')];
        }

        /* set javascript file */
        $this->add_JSEngineFile('tool/array.js');
        $this->add_JSFile('MultiSelectionList.js');

        /* set javascript object */
        $this->add_JSScript($this->params['name'].' = new MultiSelectionList("'.$this->params['name'].'");');
        $this->add_JSScript($this->params['name'].'.set_param("fullList", {});');
        foreach ($this->params['fullList'] as $id => $name)
            $this->add_JSScript($this->params['name'].'.set_param("fullList", '.$id.', "'.$name.'");');

        $this->add_JSScript($this->params['name'].'.set_param("selList", new Array());');
        foreach ($this->params['selList'] as $index => $id)
            $this->add_JSScript($this->params['name'].'.set_param("selList", '.$index.', '.$id.');');

        $this->add_JSScript($this->params['name'].'.set_param("formName", "'.$this->params['formName'].'")');
        $this->add_JSScript($this->params['name'].'.set_param("formItemName", "'.$this->params['formItemName'].'")');
        $this->add_JSScript($this->params['name'].'.set_param("itemSeparator", "'.$this->params['itemSeparator'].'")');

        /* send icons */
        if ($this->params['buttonSource'] == 'theme') {
            $this->add_JSScript($this->params['name'].'.set_param("plusIcon", "'.$this->theme->get_pictURL('plus', 12, 'std').'");');
            $this->add_JSScript($this->params['name'].'.set_param("plusIconR", "'.$this->theme->get_pictURL('plus', 12, 'ovr').'");');

            $this->add_JSScript($this->params['name'].'.set_param("minusIcon", "'.$this->theme->get_pictURL('minus', 12, 'std').'");');
            $this->add_JSScript($this->params['name'].'.set_param("minusIconR", "'.$this->theme->get_pictURL('minus', 12, 'ovr').'");');
        } else {
            $this->add_JSScript($this->params['name'].'.set_param("plusIcon", "'.$this->get_fileURL('img/plus.gif').'");');
            $this->add_JSScript($this->params['name'].'.set_param("plusIconR", "'.$this->get_fileURL('img/plusR.gif').'");');

            $this->add_JSScript($this->params['name'].'.set_param("minusIcon", "'.$this->get_fileURL('img/minus.gif').'");');
            $this->add_JSScript($this->params['name'].'.set_param("minusIconR", "'.$this->get_fileURL('img/minusR.gif').'");');
        }

        /* set object initialization on page load */
        $this->add_JSLoadScript ($this->name.'.initialise();');

        /* Input generic initialization */
        parent::initialise();
    }

    /**
     * Display input.
     * @return void
     */
    public function display() {
        parent::display($this->params['selectedLayout']);
    }
}
?>