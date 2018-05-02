<?php
/**
 * @brief Template plugin object
 * @details Engine / Object Library
 * @file engine/lib/object/Template.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jun 2005
 * @date Modification: Apr 2018
 * @copyright 2005 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Template class.
 * @author CaMykS Team <camyks.contact@gmail.com>
 */
abstract class Template extends Plugin {
    /**
     * Class constructor.
     * @param string $name
     * @param string $path_type
     * @return void
     */
    public function __construct($name, $path_type) {
        parent::__construct($name, 'template', $path_type);
    }
    
    /*
     * Alias to constructor.
     * @param string $name
     * @param string $path_type
     * @return void
     */
    public function Template($name, $path_type) {
        $this->__construct($name, $path_type);
    }

    /**
     * Initialise template object.
     * @return void
     */
    public function initialise() {
        $this->add_styleFile('style.css');
    }

    /**
     * Display template object layout.
     * @return void
     */
    public function display() {
        $this->load_file('main.html.inc');
    }

    /**
     * Display template object thumb.
     * @return void
     */
    public function display_thumb() {
        $this->load_file('thumb.html.inc');
    }

    /**
     * Display in-template module object.
     * @param integer $module
     * @return void
     */
    public function display_module($module) {
        global $camyks;
        $camyks->contentPage->display_module($module);
    }
}
?>