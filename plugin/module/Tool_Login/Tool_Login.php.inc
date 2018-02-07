<?php
/*
 * Camyks Engine
 * Developed by	    : camyks.net
 * Author	    : CaMykS Team <camyks.contact@gmail.com>
 * Camyks Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Engine
 * Creation Date    : Jun 2005
 * Last Modif Date  : Dec 2010
 * History :
 * * 05-06-xx : Initial Files
 *
 * Login Module
*/

class Tool_Login extends Module {
  /* variables */
  var $login;  
  var $pwd;
  var $text;

  /*
   * Constructor
   * @param string $path_type
   */
  function Tool_Login ( $path_type ) {
    /* get Module generic init */
    parent::Module('Tool_Login', $path_type);
    /* set module type */
    $this->type = 'tool';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'System';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
  }
  
  /* overwrite Module methods */
  
  /*
   * init module object in admin mode
   * @return void
   * @access private
   */
  function init_admin () {
    global $camyks;
    
    /* init values */
    $this->text = '';    

    /* check if a user is loging */
    if (isset($_REQUEST['login'])) {

      $this->login = ( isset ( $_REQUEST['login'] ) ? $_REQUEST['login'] : '' );
      $this->pwd = ( isset ( $_REQUEST['pwd'] ) ? $_REQUEST['pwd'] : '' );
      
      $user = new AdminUser($this->login);
      if ($user->can_login($this->pwd)) {
	    $camyks->set_sessionValue('admin_user', $this->login);
	    $camyks->set_sessionValue('admin_time', time());
       	/* add stat */
	    $camyks->update_statistic('adminlogin', $this->name, 'single', $this->login, client_getIp(), '', array('checkIPFilter'=>0, 'checkAdmin'=>0));
	    $this->selected_layout = 'null';
	    header('Location:'.$camyks->get_adminLink());
	    die();
      } else {
	    /* add stat */
	    $camyks->update_statistic('adminloginfailed', $this->name, 'single', $this->login, client_getIp(), '', array('checkIPFilter'=>0));
	    /* */
	    $this->text = $this->get_translation('loginfailed');
      }
    }

    /* get languages */
    $this->language = array();
    foreach ( $camyks->site_conf['admin_languages'] as $l )
      $this->languages[$l] = language_getTitle( $l );

    /* build form */
    $this->form = new HTMLForm ('login', $camyks->get_adminLink(),'POST');
    
    /* build button list */
    $this->buttons = array(array('title'=>$this->get_translation('access'),
				 'url'=>$this->form->get_HTMLSubmitLink()));
  }
}
?>