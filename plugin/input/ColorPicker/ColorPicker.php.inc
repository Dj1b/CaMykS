<?php
/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Input Engine
 * Create Date		: Mar 2007
 * Last Modif Date	: Mar 2007
 * History :
 * * 07-03-xx : Initial files
 * * 08-02-29 : English localisation
 *
 * Generic Color Picker
 */

class ColorPicker extends Input {
  /* variables */
  var $cp_name;
  var $mode;
  var $modaldisplay;
  var $color;
  var $config;

  /*
   * constructor
   * @param String $path_type
   */
  function ColorPicker ( $path_type ) {
    parent::Input('ColorPicker', $path_type);
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Default';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    /* initialise plugin variables */
    $this->modaldisplay = false;
  }
  
  /* overwrite input methods */

  /*
   * initialise input
   * @param string $name
   * @param string $default
   * @param string $mode
   * @return void
   * @access public
   */
  function initialise ( $name='cp', $config='default', $mode='popup' ) {
    global $camyks;    

    /* get config */
    $this->cp_name = $name;
    $this->config = $config;
    $this->mode = $mode;

    /* add javascript files */
    $this->add_JSFile('colorpicker.js');

    if ( $this->mode == 'modal' ) {
      /* get config */
      $this->get_config();

      /* get modal window buttons */
      $this->buttons = array(array('title'=>$camyks->get_translation('cancel'),
				   'link'=>'javascript:colorpicker_hide(\''.$this->cp_name.'\')'),
			     array('title'=>$camyks->get_translation('valid'),
				   'link'=>'javascript:colorpicker_save(\''.$this->cp_name.'\')'));

      /* add javascripts */
      $this->add_JSFile('colorpicker_popup.js');
      $this->add_JSScript('var inputname = "";');
      $this->add_JSScript('var inputcolor = "";');
    }

    /* Input generic initialization */
    parent::initialise();
  }
  
  /*
   * display input
   * @param string $name
   * @param string $color
   * @return void
   * @access public
   */
  function display ( $name=null, $color=null ) {
    /* update data */
    if ( isset ( $name ) ) {
      $this->inputname = $name;
    } else {
      $this->inputname = $this->cp_name;
    }

    if ( isset ( $color ) ) {
      $this->color = $color;
    }

    /* Input generic display */
    parent::display();
  }

  /*
   * run input engine as request
   * @return void
   * @access public
   */
  function execute_request () {
    global $camyks;

    /* get config */
    $this->config = isset ( $_REQUEST['cp_config'] ) ? $_REQUEST['cp_config'] : 'default';
    $this->color = isset ( $_REQUEST['cp_color'] ) ? $_REQUEST['cp_color'] : null;
    $this->cp_name = isset ( $_REQUEST['cp_name'] ) ? $_REQUEST['cp_name'] : null;
    $this->inputname = $this->cp_name; 
    $this->get_config();
   

    /* get theme */
    $theme = isset( $_REQUEST['theme'] ) ? $_REQUEST['theme'] : $camyks->_conf['admin_default_theme']; 

    if ( ($this->theme = theme_get( $theme, 'site' )) === false ) {
      if ( ($this->theme = theme_get( $theme, 'camyks' )) === false ) {
	/* theme not found return error */
	/* TO DO */
	return ;
      }
    }

    /* get layout buttons */
    $this->buttons = array(array('title'=>$this->get_translation('cancel'),
				 'link'=>'javascript:colorpicker_cancel()'),
			   array('title'=>$this->get_translation('valid'),
				 'link'=>'javascript:colorpicker_valid()'));

    /* build html page */
    $camyks->HTMLPage = new HTMLPage();
    $camyks->HTMLPage->set_charset ( $camyks->get_htmlencodingvalue());
    $camyks->HTMLPage->add_styleFile ( $camyks->site_data_url.'/css/generic.css' );
    $camyks->HTMLPage->set_siteInformations ( $camyks->_conf['site_title'],
					      $camyks->_conf['site_author'],
					      $camyks->_conf['site_company']);
    $camyks->HTMLPage->set_robotInformations ( false, false );

    /* add javascripts */
    $camyks->HTMLPage->add_JSFile ( $this->get_fileURL('js/colorpicker_popup.js', '', false ) );
    $camyks->HTMLPage->add_JSScript ( 'var inputname = "'.$this->inputname.'";' );
    $camyks->HTMLPage->add_JSScript ( 'var inputcolor = "'.$this->color.'";' );

    /* load theme */
    $this->theme->get_main_css();
    $this->theme->get_parts();

    /* display html page */
    $camyks->HTMLPage->add_HTMLHeader();
    $camyks->HTMLPage->write_HTMLContent();

    $this->load_file('html/popup.html.inc');

    $camyks->HTMLPage->add_HTMLFooter();
    $camyks->HTMLPage->write_HTMLContent();
  }

  /* specific methods */


  /*
   * display modal window
   * @return void
   * @access public
   */
  function display_modalWindow() {
    if ( $this->mode == 'modal' and $this->modaldisplay == false ) {
      $this->modaldisplay = true;
      $this->load_file('html/modal.html.inc');
    }
  }



  /*
   * return available configurations
   * @return array
   * @access private
   */
  function get_configs ( ) {
    return array('default',
		 'reds',
		 'blues',
		 'greens',
		 'yellows');
  }


  /*
   * load configuration
   * @return void
   * @access private
   */
  function get_config ( ) {
    /* set build-in config */
    $configs = $this->get_configs();
    if ( isset ( $this->config ) and file_exists ( $this->config ) ) {
      /* load an external config file */
      require ( $this->config );
    } else if ( in_array($this->config, $configs) ) {
      /* load a build-in config file */
      $this->load_file('config/'.$this->config.'.php.inc');
    } else {
      /* load default config file */
      $this->load_file('config/default.php.inc');
    }
  }
}

?>