<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Engine
 * Creation Date	: Aug 2007
 * Last Modif Date      : Jun 2008
 *
 * Installer Module
 * To do :
 * - add a link to camyks "installation help" article to the buttons list
 * - add folder check and installation
 */

class Tool_Installer extends Module {
  /* variables */
  var $summary;
  var $allowInstall;
  var $textcolors;

  /*
   * constructor
   * @param string $path_type
   */
  function Tool_Installer ( $path_type ) {
    parent::Module('Tool_Installer', $path_type);
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
    /* get mode */
    $mode = isset($_REQUEST['mode']) ? $_REQUEST['mode'] : 'main';

    /* installer data */
    $this->symlinks = array('plugin'=>'cplugin', 'engine/data'=>'cdata');
    $this->textcolors = array('yes' => 'green',
			      'no' => '#CC3333');

    /* installer execution */
    switch ( $mode ) {
    case 'install':
      /* mode == install */
      $this->init_admin_install();
      break;
    case 'main':
    default:
      /* mode == main */
      $this->init_admin_main();
      break;
    }
  }

  /*
   * display module object in admin mode
   * @return void
   * @access private
   */
  function display_admin () {
    parent::display_admin();
  }

  /* specific admin mode methods */

  /*
   * init module object in admin/main mode
   * @return void
   * @access private
   */
  function init_admin_main() {
    $this->allowInstall = true;
    $this->summary = array();

    /* execute all checks */
    $this->checkCaMykSConfig();
    $this->checkSiteConfig();
    $this->checkPlugins();
    $this->checkDatabase();
    $this->checkSymlinks();

    if ( $this->allowInstall ) {
      $this->buttons = array(array('title'=>$this->get_translation('install'),
				   'link'=>'?mode=install'));
    } else {
      $this->buttons = array(array('title'=>$this->get_translation('install'),
				   'link'=>''));
    }
  }

  /*
   * init module object in admin/install mode
   * @return void
   * @access private
   */
  function init_admin_install() {
    $this->allowInstall = true;
    $this->isInstalled = true;
    $this->buttons = array();
    $this->summary = array();

    /* basic checks */
    $this->checkSiteConfig();
    $this->checkPlugins();

    /* install all part if installation is allowed */
    if ( $this->allowInstall ) {
      /* erase check message */
      $this->summary = array();

      $this->installDatabase();

      if ( $this->isInstalled ) 
	$this->installPlugins();

      if ( $this->isInstalled )
	$this->installSymlinks();
      
      if ( $this->isInstalled  ){
	/* finalise installation */
	$this->installDone();
      } else {
	
      }
    }
  }

  /* specific tool methods */

  /*
   * check CaMykS engine config
   * @return void
   * @access private
   */
  function checkCaMykSConfig() {
    global $camyks;
    /* add camyks config title */
    $this->summary[] = array('type'=>'title',
			     'name'=>$this->get_translation('camyksconfigcheck'),
			     'value'=>'');
    /* display engine availability */
    $this->summary[] = array('type'=>'message',
			     'name'=>$this->get_translation('availability'),
			     'value'=>$this->get_translation('ok'),
			     'color'=>$this->textcolors['yes']);
    /* display engine installation mode */
    $this->summary[] = array('type'=>'message',
			     'name'=>$this->get_translation('installationmode'),
			     'value'=>$camyks->get_translation($camyks->_installationMode));    
  }


  /*
   * check site configuration file
   * @return void
   * @access private
   */
  function checkSiteConfig() {
    global $camyks;
    /* add configuration file title */
    $this->summary[] = array('type'=>'title',
			     'name'=>$this->get_translation('siteconfigcheck'),
			     'value'=>'');
    /* check site/folder name */
    $message = array('type'=>'message',
		     'name'=>$this->get_translation('configvalue', 'site_name'),
		     'value'=>'');
    $folderName = explode('/', realpath('.') );
    $folderName = $folderName[count($folderName)-1];
    if ( $folderName == $camyks->site_conf['site_name'] ){
      $message['value'] = $this->get_translation('ok');
      $message['color'] = $this->textcolors['yes'];
    } else {
      $message['value'] = $this->get_translation('sitename_error');
      $message['color'] = $this->textcolors['no'];
      $this->allowInstall = false; 
    }
    $this->summary[] = $message;
    
    /* check site url */
    $message = array('type'=>'message',
		     'name'=>$this->get_translation('configvalue', 'url'),
		     'value'=>'');
    if ( isset($camyks->site_conf['url']) and $camyks->site_conf['url'] != '' ) {
      $message['value'] = $this->get_translation('ok');
      $message['color'] = $this->textcolors['yes'];
    } else {
      $message['value'] = $this->get_translation('url_error');
      $message['color'] = $this->textcolors['no'];
      $this->allowInstall = false; 
    }
    $this->summary[] = $message;

    /* check admininstation entry file */
    $message = array('type'=>'message',
		     'name'=>$this->get_translation('configvalue', 'admin_entry'),
		     'value'=>'');
    if ( isset($camyks->site_conf['admin_entry']) 
	 and file_exists(realpath('./'.$camyks->site_conf['admin_entry']))) {
      $message['value'] = $this->get_translation('ok');
      $message['color'] = $this->textcolors['yes'];
    } else {
      $message['value'] = $this->get_translation('adminentry_error');
      $message['color'] = $this->textcolors['no'];
      $this->allowInstall = false; 
    }
    $this->summary[] = $message;

    /* check database name */
    $message = array('type'=>'message',
		     'name'=>$this->get_translation('configvalue', 'database_name'),
		     'value'=>'');
    if ( isset($camyks->_conf['database_name']) and $camyks->_conf['database_name'] != '' ) {
      $message['value'] = $this->get_translation('ok');
      $message['color'] = $this->textcolors['yes'];
    } else {
      $message['value'] = $this->get_translation('database_name_error');
      $message['color'] = $this->textcolors['no'];
      $this->allowInstall = false; 
    }
    $this->summary[] = $message;

    /* check page_maxmodules ( default value is 8 ) */
    $message = array('type'=>'message',
		     'name'=>$this->get_translation('configvalue', 'page_maxmodules'),
		     'value'=>'');
    if ( isset($camyks->site_conf['page_maxmodules']) and $camyks->site_conf['page_maxmodules'] > 0 ) {
      $message['value'] = $this->get_translation('ok');
      $message['color'] = $this->textcolors['yes'];
    } else {
      $message['value'] = $this->get_translation('page_maxmodules_error');
      $this->allowInstall = false; 
      $message['color'] = $this->textcolors['no'];
    }
    $this->summary[] = $message;
  }

  /*
   * check database connection
   * @return void
   * @access private
   */
  function checkDatabase() {
    global $camyks;
    /* add database tests title */
    $this->summary[] = array('type'=>'title',
			     'name'=>$this->get_translation('databasecheck'),
			     'value'=>'');

    /* check connection */
    $message = array('type'=>'message',
		     'name'=>$this->get_translation('database_connection'),
		     'value'=>'');
    $this->db_conn = new Database_connection ( $camyks->_conf['database_host'],
					       $camyks->_conf['database_login'], 
					       $camyks->_conf['database_pwd'] );
    if ( $this->db_conn->is_active() ) {
      $message['value'] = $this->get_translation('ok');
      $message['color'] = $this->textcolors['yes'];
    } else {
      $message['value'] = $this->get_translation('database_connection_failed');
      $message['color'] = $this->textcolors['no'];
      $this->allowInstall = false; 
    }
    $this->summary[] = $message;

    /* check if database exists */
    $message = array('type'=>'message',
		     'name'=>$this->get_translation('database_db'),
		     'value'=>'');
    if ( $this->db_conn->is_active() ) {
      if( $this->db_conn->select( $camyks->_conf['database_name'] ) )
	$message['value'] = $this->get_translation('ok');
      else
	$message['value'] = $this->get_translation('database_dbdoesntexist');
    }
    $this->summary[] = $message;

  }

  /*
   * check symbolic links existance
   * @return void
   * @access private
   */
  function checkSymlinks() {
    global $camyks;

    /* do not install sym links in "dedicated" installation mode */
    if ( $camyks->_installationMode == 'dedicated' )
      return;
    
    /* add symlinks check title */
    $this->summary[] = array('type'=>'title',
			     'name'=>$this->get_translation('symlinkscheck'),
			     'value'=>'');
    /* check write right */
    $message = array('type'=>'message',
		     'name'=>$this->get_translation('write_rights'),
		     'value'=>'');
    $myfile = realpath('.');

    if ( is_writable( $myfile ) ) {
      $message['value'] = $camyks->get_translation('yes');
      $message['color'] = $this->textcolors['yes'];
    } else {
      $message['value'] = $camyks->get_translation('no');
      $message['color'] = $this->textcolors['no'];
      $this->allowInstall = false;
    }
    $this->summary[] = $message;

    /* check symlink exists */
    foreach ( $this->symlinks as $l ) {
      $message = array('type'=>'message',
		       'name'=>$this->get_translation('symlinkfound', $l),
		       'value'=>'');
      
      if ( file_exists( realpath('./'.$l) ) ) {
	$message['value'] = $camyks->get_translation('yes');
      } else {
	$message['value'] = $camyks->get_translation('no');
      }
      $this->summary[] = $message;
    }
  }

  /*
   * check mandatory plugins
   * @return void
   * @access private
   */
  function checkPlugins() {
    global $camyks;

    $this->summary[] = array('type'=>'title',
			     'name'=>$this->get_translation('pluginscheck'),
			     'value'=>'');
    /* get mandatory plugin for CaMykS */
    $camyks->get_neededPlugins();

    /* check modules */
    foreach ( $camyks->neededModules as $p ) {
      $message = array('type'=>'message',
		       'name'=>$camyks->get_translation('modulex', $p['name']));
      if ( !isset($camyks->modules[$p['name']])) {
	$message['value'] = $this->get_translation('notfound');
	$message['color'] = $this->textcolors['no'];
	$this->allowInstall = false;
      } else if ( $camyks->modules[$p['name']]->version < $p['version'] ) {
	$message['value'] = $this->get_translation('oldversion');
	$message['color'] = $this->textcolors['no'];
	$this->allowInstall = false;
      } else {
	$message['value'] = $camyks->get_translation('yes');
	$message['color'] = $this->textcolors['yes'];
      }
      $this->summary[] = $message;
    }

    /* check inputs */
    foreach ( $camyks->neededInputs as $p ) {
      $message = array('type'=>'message',
		       'name'=>$camyks->get_translation('inputx', $p['name']));

      if ( !isset($camyks->inputs[$p['name']])) {
	$message['value'] = $this->get_translation('notfound');
	$message['color'] = $this->textcolors['no'];
	$this->allowInstall = false;
      } else if ( $camyks->inputs[$p['name']]->version < $p['version'] ) {
	$message['value'] = $this->get_translation('oldversion');
	$message['color'] = $this->textcolors['no'];
	$this->allowInstall = false;
      } else {
	$message['value'] = $camyks->get_translation('yes');
	$message['color'] = $this->textcolors['yes'];
      }
      $this->summary[] = $message;
    }

    /* check themes */
    foreach ( $camyks->neededThemes as $p ) {
      $message = array('type'=>'message',
		       'name'=>$camyks->get_translation('themex', $p['name']));

      if ( !isset($camyks->themes[$p['name']])) {
	$message['value'] = $this->get_translation('notfound');
	$message['color'] = $this->textcolors['no'];
	$this->allowInstall = false;
      } else if ( $camyks->themes[$p['name']]->version < $p['version'] ) {
	$message['value'] = $this->get_translation('oldversion');
	$message['color'] = $this->textcolors['no'];
	$this->allowInstall = false;
      } else {
	$message['value'] = $camyks->get_translation('yes');
	$message['color'] = $this->textcolors['yes'];
      }
      $this->summary[] = $message;
    }

    /* check templates */
    foreach ( $camyks->neededTemplates as $p ) {
      $message = array('type'=>'message',
		       'name'=>$camyks->get_translation('templatex', $p['name']));

      if ( !isset($camyks->templates[$p['name']])) {
	$message['value'] = $this->get_translation('notfound');
	$message['color'] = $this->textcolors['no'];
	$this->allowInstall = false;
      } else if ( $camyks->templates[$p['name']]->version < $p['version'] ) {
	$message['value'] = $this->get_translation('oldversion');
	$message['color'] = $this->textcolors['no'];
	$this->allowInstall = false;
      } else {
	$message['value'] = $camyks->get_translation('yes');
	$message['color'] = $this->textcolors['yes'];
      }
      $this->summary[] = $message;
    }
  }


  /*
   * install database
   * @return void
   * @access private
   */
  function installDatabase() {
    global $camyks;
    /* get mysql engin connection */
    $camyks->db_conn = new Database_connection ( $camyks->_conf['database_host'],
					       $camyks->_conf['database_login'], 
					       $camyks->_conf['database_pwd'] );
    /* check if connection is active */
    if ( $camyks->db_conn->is_active() ) {
      if( !$camyks->db_conn->select( $camyks->_conf['database_name'] ) ) {
	$message = array('type'=>'message',
			 'name'=>$this->get_translation('database_created'));
	/* try to create database  */
	if ( $camyks->db_conn->database_create( $camyks->_conf['database_name'], $camyks->get_mysqlencodingvalue() ) ) {
	  $message['value'] = $camyks->get_translation('yes');
	  $message['color'] = $this->textcolors['yes'];
	  $camyks->db_conn->select( $camyks->_conf['database_name']);
	} else {
	  $message['value'] = $camyks->get_translation('no');
	  $message['color'] = $this->textcolors['no'];
	  $this->isInstalled = false;
	}
	$this->summary[] = $message;
      }
    } else {
      /* database connection failed */
      $this->summary[] = array('type'=>'message',
			       'name'=>$this->get_translation('database_connection'),
			       'value'=>$this->get_translation('database_connection_failed'),
			       'color'=>$this->textcolors['no']);
      $this->isInstalled = false;
    }
  }
  
  /*
   * install symbolic links
   * @return void
   * @access private
   */
  function installSymlinks() {
    global $camyks;

    /* do not install sym links in "dedicated" installation mode */
    if ( $camyks->_installationMode == 'dedicated' )
      return;
    
    /* build symlinks */
    foreach ( $this->symlinks as $f => $l ) {
      $message = array('type'=>'message',
		       'name'=>$this->get_translation('symlink_x_created', $l ));
      shell_ln ( $camyks->site_conf['engine_path'].'/'.$f, realpath('.').'/'.$l);
      if ( file_exists( realpath('./'.$l ))) {
	$message['value'] = $camyks->get_translation('yes');
	$message['color'] = $this->textcolors['yes'];
	$this->summary[] = $message;
      } else {
	$message['value'] = $camyks->get_translation('no');
	$message['color'] = $this->textcolors['no'];
	$this->summary[] = $message;
	$this->isInstalled = false;
	return;
      }
    }
  }

  /*
   * install plugins
   * @return void
   * @access private
   */
  function installPlugins() {
    global $camyks;
    $message = array('type'=>'message',
		     'name'=>$this->get_translation('module_x_installed', 'Admin_PluginManager'));
    /* first, try to install plugin manager plugin */
    if ( $camyks->modules['Admin_PluginManager']->install() ) {
      $message['value'] = $camyks->get_translation('yes');
      $message['color'] = $this->textcolors['yes'];
      $this->summary[] = $message;

      /* install needed modules */
      foreach ( $camyks->neededModules as $p ) {
	$message = array('type'=>'message',
			 'name'=>$this->get_translation('module_x_installed', $p['name'] ));
	if ( $camyks->modules['Admin_PluginManager']->install_plugin($p['name'], 'module', 'camyks', 1) ) {
	  $message['value'] = $camyks->get_translation('yes');
	  $message['color'] = $this->textcolors['yes'];
	  $this->summary[] = $message;
	} else {
	  $message['value'] = $camyks->get_translation('no');
	  $message['color'] = $this->textcolors['no'];
	  $this->summary[] = $message;
	  $this->isInstalled = false;
	  return;
	}
      }

      /* install needed inputs */
      foreach ( $camyks->neededInputs as $p ) {
	$message = array('type'=>'message',
			 'name'=>$this->get_translation('input_x_installed', $p['name'] ));
	if ( $camyks->modules['Admin_PluginManager']->install_plugin($p['name'], 'input', 'camyks', 1) ) {
	  $message['value'] = $camyks->get_translation('yes');
	  $message['color'] = $this->textcolors['yes'];
	  $this->summary[] = $message;
	} else {
	  $message['value'] = $camyks->get_translation('no');
	  $message['color'] = $this->textcolors['no'];
	  $this->summary[] = $message;
	  $this->isInstalled = false;
	  return;
	}
      }

      /* install needed themes */
      foreach ( $camyks->neededThemes as $p ) {
	$message = array('type'=>'message',
			 'name'=>$this->get_translation('theme_x_installed', $p['name'] ));
	if ( $camyks->modules['Admin_PluginManager']->install_plugin($p['name'], 'theme', 'camyks', 1) ) {
	  $message['value'] = $camyks->get_translation('yes');
	  $message['color'] = $this->textcolors['yes'];
	  $this->summary[] = $message;
	} else {
	  $message['value'] = $camyks->get_translation('no');
	  $message['color'] = $this->textcolors['no'];
	  $this->summary[] = $message;
	  $this->isInstalled = false;
	  return;
	}
      }

      /* install needed templates */
      foreach ( $camyks->neededTemplates as $p ) {
	$message = array('type'=>'message',
			 'name'=>$this->get_translation('template_x_installed', $p['name'] ));
	if ( $camyks->modules['Admin_PluginManager']->install_plugin($p['name'], 'template', 'camyks', 1) ) {
	  $message['value'] = $camyks->get_translation('yes');
	  $message['color'] = $this->textcolors['yes'];
	  $this->summary[] = $message;
	} else {
	  $message['value'] = $camyks->get_translation('no');
	  $message['color'] = $this->textcolors['no'];
	  $this->summary[] = $message;
	  $this->isInstalled = false;
	  return;
	}
      }
    } else {
      $message['value'] = $camyks->get_translation('no');
      $message['color'] = $this->textcolors['no'];
      $this->summary[] = $message;
      $this->isInstalled = false;
    }
  }

  /*
   * finalise installation
   * @return void
   * @access private
   */
  function installDone() {
    global $camyks;
    
    /* update camyks version in conf file */
    $camyks->site_conf['cms_version'] = $camyks->version;
    
    /* add 'installed' value to the conf file */
    $camyks->site_conf['installed'] = 1;
    
    $content = file_getPHPFileHeader('site configuration file', '1.0');
    $content .= '$conf = ' . var_export( $camyks->site_conf, true ) . ';';
    $content .= file_getPHPFileFooter();

    file_write(realpath('./etc/site.php.inc'), $content);

    /* add installation successfull message line */
    $message = array('type'=>'message',
		     'name'=>$this->get_translation('installation_done'),
		     'value'=>$camyks->get_translation('yes'),
		     'color'=>$this->textcolors['yes']);
    $this->summary[] = $message;
    /* add site admin link button */
    $this->buttons = array(array('title'=>$this->get_translation('open_admin'),
				 'link'=>$camyks->get_adminLink()));
    return true;
  }
}
?>