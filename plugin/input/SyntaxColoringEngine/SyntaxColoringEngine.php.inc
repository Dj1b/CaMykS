<?php
/**
 * @brief SyntaxColoringEngine Input
 * <br /> Colourise given text following syntax in given mode.
 * @details Plugin / Input Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.1
 * @date Creation: Mar 2007
 * @date Modification: Jul 2025
 * @copyright 2007 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * SyntaxColoringEngine Input class.
 */
final class SyntaxColoringEngine extends Input {
    /**
     * var string $mode
     * @brief Current syntax colouring mode.
     */
    public $mode = 'none';

    /**
     * var string $content
     * @brief Content to colourise.
     */
    public $content = '';

    /**
     * var array $modes
     * @brief Available syntax colouring modes.
     */
    private $modes = array('none', 'javascript', 'css');

    /**
     * var array $loaded
     * @brief Loaded modes.
     */
    private $loaded = array();

    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('SyntaxColoringEngine', $path_type);

        /* Override Plugin information */
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* Define author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';
    }

    /* Mark: Override input methods */

    /**
     * Initialise input.
     * @param string $text
     * @param string $mode
     * @return void
     */
    public function initialise($text=null, $mode=null) {
        global $camyks;

        /* colorise text */
        if (isset($text) and isset($mode)) {
            $this->execute($text, $mode);
        }

        /* Input generic initialisation */
        parent::initialise();
    }

    /**
     * Display input.
     * @param string $text
     * @param string $mode
     * @return void
     */
    public function display($text='', $mode='') {
        /* update data */
        echo $this->execute($text, $mode);

        /* Input generic display */
        parent::display();
    }

    /* Mark: Specific methods */

    /**
     * Execute colorisation.
     * @param string $text
     * @param string $mode
     * @param array $params
     * @return string
     */
    public function execute($text='', $mode='', $params=array()) {
        if (in_array($mode, $this->modes)) {
            /* load mode engine if needed */
            if (!in_array($mode, $this->loaded)) {
                $this->load_file('mode/'.$mode.'.php.inc');
                $this->loaded[] = $mode;
            }
            /* set mode */
            eval('$this->mode = new SyntaxColoringEngine_'.$mode.'();');

            /* run colourisation */
            $this->content = $this->mode->execute($text, $params);
        } else
            $this->content = $text;

        /* return content */
        return $this->content;
    }
}
?>
