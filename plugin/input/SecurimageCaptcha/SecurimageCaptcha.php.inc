<?php
/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a2
 * Object Version       : 1.0
 * Object Type          : Plugin / Input Engine
 * Create Date		: Jul 2009
 * Last Modif Date	: Jul 2009
 * History : 
 * * 09-07-02 : Initial files
 * 
 * SecurimageCaptcha input : Generate and check captcha code
 * from Securimage GPL library
 * Version : 1.0.3.1
 * Website : http://www.phpcaptcha.org
 */

class SecurimageCaptcha extends Input {
  /* variables */

  /* 
   * constructor
   * @param string $path_type
   */
  function SecurimageCaptcha ( $path_type ) {
    parent::Input('SecurimageCaptcha', $path_type);
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

  /*
   * install plugin
   * @return boolean success
   * @access private
   */
  function install() {
    return (extension_loaded('gd') && parent::install());
  }

  /*
   * initialise input
   * @param array $params
   * @return void
   * @access public
   */
  function initialise($params=array()) {
    global $camyks;

    /* update params */
    $params = array_merge(array('ttf_file'=>$this->get_filePath('securimage/elephant.ttf')), $params);
    /* save params */
    $camyks->set_sessionValue('sic_params', $params);

    /* Input generic initialization */
    parent::initialise();
  }


  /* 
   * display input
   * @param string $layout
   * @return void
   * @access public
   */
  function display($layout='captcha') {
    $this->selected_layout = 'input_'.$layout.'.html.inc';
    parent::display();
  }

  /*
   * execute input in request mode
   * @return void
   * @access public
   */
  function execute_request() {
    global $camyks;
    $this->load_file('securimage/securimage.php');
    $img = new Securimage();

    /* check Securimage parameters */
    if (($params = $camyks->get_sessionValue('sic_params', null)) != null) {
      if (isset($params['image_width']))
	$img->image_width = $params['image_width'];
      if (isset($params['image_height']))
	$img->image_height = $params['image_height'];
      if (isset($params['image_type']))
	$img->image_type = $params['image_type'];
      if (isset($params['code_length']))
	$img->code_length = $params['code_length'];
      if (isset($params['charset']))
	$img->charset = $params['charset'];
      if (isset($params['word_list'])) {
	$img->wordlist_file = $params['word_list'];
	$img->use_wordlist = true;
      } else {
	$img->use_wordlist = false;
      }
      if (isset($params['image_bg_color']))
	$img->image_bg_color = $params['image_bg_color'];
      if (isset($params['image_text_colors']))
	$img->multi_text_color = $params['image_text_colors'];
      if (isset($params['ttf_file']))
	$img->ttf_file = $params['ttf_file'];
    }

    /* clean parameters */
    $camyks->set_sessionValue('sic_params', null);

    /* display image */
    $img->show();
  } 
  
  /* specific tool methods */

  /*
   * check captcha
   * @return boolean result
   * @access private
   */
  function check_captcha($code) {
    $this->load_file('securimage/securimage.php');
    $img = new Securimage();
    return $img->check($code);
  }
}
?>