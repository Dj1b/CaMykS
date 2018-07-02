<?php
/**
 * @brief Input plugin object
 * @details Engine / Object Library
 * @file engine/lib/object/Input.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jun 2005
 * @date Modification: Jun 2018
 * @copyright 2005 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @todo Replace Input() by __construct() once all Input objects have been updated.
 */

/**
 * Input class.
 * @author CaMykS Team <camyks.contact@gmail.com>
 */
class Input extends Plugin {
    /**
     * @var string $title
     * @brief Input title.
     */
    public $title;
    
    /**
     * @var array $params
     * @brief Input parameters.
     */
    public $params = array();
    
    /**
     * @var string $selected_layout
     * @brief Input layout to use.
     */
    public $selected_layout = 'input.html.inc';
  
    /**
     * Class constructor.
     * @param string $name
     * @param string $path_type
     * @return void
     */
    public function Input($name, $path_type) {
        /* Plugin Init */
        parent::__construct($name, 'input', $path_type);
        
        /* define title from name */
        $this->title = $this->name;
        
        /* load locales */
        $this->add_translation();
    }

    /**
     * Initialise input.
     * @param array $params
     * @return boolean
     */
    public function initialise($params=array()) {
        $this->params = array_merge($this->params, $params);
        return true;
    }

    /**
     * Display input.
     * @return void
     */
    public function display() {
        $this->load_file('html/'.$this->selected_layout);
    }

    /* locales related methods */

    /**
     * Get locale value.
     * @param string $value
     * @param mixed $data
     * @return string
     */
    public function get_translation($value, $data=null) {
        global $camyks;
        return $camyks->get_translation('input_'.strtolower($this->name).'_'.$value, $data);
    }
  
    /* tool methods */
  
    /**
     * Update selected layout.
     * @param string $layout
     */
    public function set_selectedLayout($layout='') {
        $this->selected_layout = $layout;
    }
}
?>