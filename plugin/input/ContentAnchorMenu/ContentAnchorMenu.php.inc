<?php
/**
 * @brief ContentAnchorMenu Input
 * <br /> Automatic anchor system build from content.
 * @details Plugin / Input Engine
 * @file plugin/input/ContentAnchorMenu/ContentAnchorMenu.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Feb 2010
 * @date Modification: Apr 2018
 * @copyright 2010 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * ContentAnchorMenu Input class.
 * @author CaMykS Team <camyks.contact@gmail.com>
 */
final class ContentAnchorMenu extends Input {
    /**
     * var array $params
     * @brief Input parameters.
     */
    public $params = array(
        'mode'      => 'AName', // AName (HTML4) / objId (HTML5)
        'name'      => 'anchorMenu',
        'content'   => 'body',
        'linkClass' => 'eLink1',
        'menuClass' => '',
        'shift'     => 0,
    );
    
    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('ContentAnchorMenu', $path_type);
        
        /* set plugin version */
        $this->version = '1.0';
        
        /* set plugin package */
        $this->plugin_package = 'Generic';
        
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
    public function initialise ($params=array()) {
        global $camyks;
        
        $this->params = array_merge($this->params, $params);
        $this->params['name'] = string_parseSpecialChars($this->params['name'], array('pattern'=>'/[^a-zA-Z0-9_]/'));

        /* add javascript */
        $this->add_JSFile('ContentAnchorMenu.js');
        $this->add_JSScript('var '.$this->params['name'].' = new ContentAnchorMenu("'.$this->params['name'].'");');
        $this->add_JSScript($this->params['name'].'.set_param("mode", "'.$this->params['mode'].'");');
        $this->add_JSScript($this->params['name'].'.set_param("content", "'.$this->params['content'].'");');
        $this->add_JSScript($this->params['name'].'.set_param("linkClass", "'.$this->params['linkClass'].'");');
        $this->add_JSScript($this->params['name'].'.set_param("shift", "'.$this->params['shift'].'");');
        $this->add_JSLoadScript($this->params['name'].'.initialise();');
    }
}
?>