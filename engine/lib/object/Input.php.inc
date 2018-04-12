<?php
/**
 * @brief Input plugin object
 * @details Engine / Object Library
 * @file engine/lib/object/Input.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jun 2005
 * @date Modification: Apr 2018
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
     * @return boolean
     */
    public function display() {
        $this->load_file('html/'.$this->selected_layout);
        return true;
    }
    
    /**
     * Execute input object in request mode.
     * @return boolean
     */
    public function execute_request() {
        global $camyks;    
    
        /* throw a fatal error, if not overwritten */
        $camyks->add_generic_translation();
        $camyks->throwFatalError(array(
            'title'         => $camyks->get_translation('error_fatalerror'),
            'description'   => $camyks->get_translation('error_plugin_doesnt_support_requests_desc'),
            'content1'      => $camyks->get_translation('error_plugin_doesnt_support_requests_content'),
            'back_title'    => $camyks->get_translation('error_plugin_doesnt_support_requests_back_title'),
            'back_link'     => $camyks->get_confValue('url'),
        ));
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