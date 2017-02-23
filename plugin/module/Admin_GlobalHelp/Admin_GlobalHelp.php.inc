<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * Camyks Version   	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Engine
 * Creation Date	: Fev 2007
 * Last Modif Date	: Mar 2008
 * History :
 * * 07-02-xx : Initial files
 *
 * TO DO :
 * - get site help files
 *
 */

class Admin_GlobalHelp extends Module {
  /* variables */
  var $mode;
  
  /* list mode vars */
  var $list;
  var $help;
  var $htitle;
  
  /* dislay mode vars */
  var $hfile;
  var $location;
  var $layout;
  var $helpfile;

  /*
   * constructor
   * @param string $path_type
   */
  function Admin_GlobalHelp ( $path_type ) {
    parent::Module('Admin_GlobalHelp', $path_type);
    /* set module type */
    $this->type = 'admin';
    $this->admin_type = 'helpers';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Default';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
  }
  
  /* overwrite Module methods */

  /*
   * get rights
   * @return void
   * @access private
   */
  function get_rights ( ) {
    global $camyks;
    $this->rights[0] = array( 'name'=>'read',
			      'title'=> $camyks->get_translation('read'),
			      'default'=> true);
  }

  /*
   * init object when in admin mode
   * @return void
   * @access private
   */
  function init_admin () {
    global $camyks;
    /* check read rights */
    if ( $this->check_right(0) === false ) {
      return $this->init_admin_accessDenied();
    }
    
    /* get header values */
    $this->mode = isset ( $_REQUEST['mode'] ) ? $_REQUEST['mode'] : 'list';
    
    /* get action ton execute case of mode */
    switch ( $this->mode ) {
    case 'display':
      /* get header values */
      $this->location = isset ( $_REQUEST['location'] ) ? $_REQUEST['location'] : '';
      $this->hfile = isset ( $_REQUEST['hfile'] ) ? $_REQUEST['hfile'] : '';
      
      /* check if given values are set */
      if ( $this->location == '' or $this->hfile == '' ) {
      	$this->selected_layout = 'admin_message.html.inc';
	$this->selected_layout_location = 'camyks';
	$this->text = $this->get_translation('nohelpfound');
	$this->set_redirect(4, $camyks->get_adminLink($this->name));
      	break;
      }

      /* button list for buttons bars */
      $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				   'link'=>$camyks->get_adminLink( $this->name, array())));
      
      /* check if given value correspond to a help file */
      if ($this->location == 'engine' and  $this->check_engineHelpFile ( $this->hfile )) {
      	$this->help_path = $camyks->camyks_engine_path.'/help/'.$this->hfile.'/'.$camyks->current_language.'/';
      	$this->selected_layout = 'display_engine.html.inc';
      	$this->add_JSEngineFile('object/cmdd.js');
      	$this->add_JSScript(strtolower($this->name).'_helpObject = new Cmdd();' );
      	$this->add_JSScript(strtolower($this->name).'_helpObject.init("'.$this->name.
			    '", "","'.$camyks->theme->parts['boxTabCSSStandart'].
			    '","'.$camyks->theme->parts['boxTabCSSSelected'].
			    '","'.$camyks->theme->parts['boxTabCSSRollover'].'");' );
	
      	foreach ( $this->help as $i => $v ) {
	  $this->add_JSLoadScript(strtolower($this->name).'_helpObject.mouseclick(\''.$i.'\');');
	  break;
	}
      	
      } else if ($this->location == 'modules' and  $this->check_modulesHelpFile ( $this->hfile )) {
      	$this->help_path = $camyks->modules[$this->hfile]->plugin_path.'/help/'.$camyks->current_language.'/';
      	$this->selected_layout = 'display_modules.html.inc';
      } else if ($this->location == 'site' and  $this->check_siteHelpFile ( $this->hfile )) {
      	$this->help_path = '';
      	$this->selected_layout = 'display_modules.html.inc';
      } else {
      	$this->selected_layout = 'admin_message.html.inc';
	$this->selected_layout_location = 'camyks';
	$this->text = $this->get_translation('nohelpfound');
	$this->set_redirect(4, $camyks->get_adminLink($this->name));
        break;
      }
      break;
    case 'list':
    default:
      $this->list = array();
      /* get engine list */
      $this->get_engineHelpList();
      /* get module list */
      $this->get_modulesHelpList();
      /* get site list */
      $this->get_siteHelpList();
      $this->selected_layout = 'list.html.inc';
      /* button list for buttons bars */
      $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				   'link'=>$camyks->get_adminLink()));
      break;
    }
    /* generic module admin initialisation */
    parent::init_admin();
  }
  
  /*
   * display object when in admin part
   * @return void
   * @access private
   */
  function display_admin () {
    parent::display_admin();
  }

  /* specific tool methods */
  
  /*
   * check engine help folder
   * @return void
   * @access private
   */
  function get_engineHelpList ( ) {
    global $camyks;
    $this->list['engine'] = array();
    $folder = $camyks->camyks_engine_path.'/help';
    
    /* start listing folders */
    if ( $dir = opendir( $folder ) ) {
      $folders = array();
      while ( ( $file = readdir ( $dir ) ) !== false ) {
      	if ( ( $file != '.') and ( $file != '..' ) and  ( is_dir( $folder.'/'.$file ) ) ) {
          if ( file_exists( $folder.'/'.$file.'/'.$camyks->current_language.'/help.php.inc' ) ){
	    require $folder.'/'.$file.'/'.$camyks->current_language.'/help.php.inc';	
	    $this->list['engine'][$file] = array ( 'title' => $this->htitle,
						   'link'=>$camyks->get_adminLink($this->name, array('mode'=>'display', 'location'=>'engine', 'hfile'=>$file)));
	  }
	}  
      }
    }
  }
  
  /*
   * check modules help folder
   * @return void
   * @access private
   */
  function get_modulesHelpList ( ) {
    global $camyks;
    $this->list['modules'] = array();
    $hfile = 'help/'.$camyks->current_language.'/help.php.inc';
    
    foreach ( $camyks->modules as $n => $m ) {
      $m->load_file( $hfile );
      if ( $m->help != null ) {
      	$this->list['modules'][$n]=array('title' => $m->title,
					 'link'=>$camyks->get_adminLink($this->name, array('mode'=>'display',
											   'location'=>'modules',
											   'hfile'=>$n)));
      }
    }
  }
  
  /*
   * check site help folder
   * @return void
   * @access private
   */
  function get_siteHelpList ( ) {
    global $camyks;
    $this->list['site'] = array();
  }
  
  /*
   * check engine help
   * @return void
   * @access private
   */
  function check_engineHelpFile ( $name ) {
    global $camyks;
    if ( file_exists( $camyks->camyks_engine_path.'/help/'.$name.'/'.$camyks->current_language.'/help.php.inc') ) {
      require $camyks->camyks_engine_path.'/help/'.$name.'/'.$camyks->current_language.'/help.php.inc';
      return true;
    }
    return false;
  }
  
  /*
   * check modules help
   * @return void
   * @access private
   */
  function check_modulesHelpFile ( $name ) {
    global $camyks;
    if ( !isset($camyks->modules[$name]))
      return false;

    $camyks->modules[$name]->get_help();
    $camyks->modules[$name]->init_parent_admin();
    
    $this->help = $camyks->modules[$name]->help;
    if ( $this->help != null ) {
      return true;	 
  	}
    return false;
  }
  
  /* 
   * check site help
   * @return void
   * @access private
   */
  function check_siteHelpFile ( $name ) {
    /* TO DO */  
  }
}
?>