<?php
/**
 * @brief ContentAnchorMenu Input
 * <br /> Automatic anchor system build from content.
 * @details Plugin / Input Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.1
 * @date Creation: Feb 2010
 * @date Modification: Jul 2025
 * @copyright 2010 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * ContentAnchorMenu Input class.
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
     */
    public function __construct($path_type) {
        parent::__construct('ContentAnchorMenu', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'Generic';

        /* Define author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';
    }

    /* Mark: Override input methods */

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
