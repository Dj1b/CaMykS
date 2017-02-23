<?php
/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Module Dictionnary
 * Create Date		: Apr 2007
 * Last Modif Date	: Dec 2007
 *
 * SystemSiteReportForm object for Content_SystemSiteReport object
 */

class SystemSiteReportForm {
  /* vars */
  var $id;
  var $name;
  var $layout_name;
  var $type_list;
  var $title_mode;
  var $title_texts;
  var $title_imgs;
  var $descriptions;
  var $title_texts_; /* encoded version of title_texts; */
  var $title_imgs_; /* encoded version of title_imgs; */
  var $file_allowed;

  /* generic vars */
  var $_libDesc;
  var $_libParent;
  var $_libIsInstalled;

  /*
   * Constructor
   * @param integer $id
   * @param Module $parentModule
   */
  function SystemSiteReportForm ( $id = 0, &$parentModule ) {
    global $camyks;
    $this->id = $id;
    $this->_libDesc = 'Module:'.$parentModule->name.'  Lib:SystemSiteReportForm';
    $this->_libParent = $parentModule;
    $this->_libIsInstalled = null;
  }
  
  /* methods */

  /*
   * get object
   * @return boolean success
   * @access private
   */
  function get () {
    if ( $this->id == 0 ) {
      $this->initialise();
    } else {
      $this->get_fromDatabase();
    }
  }

  /*
   * initialise object
   * @return boolean success
   * @access private
   */
  function initialise () {
    $this->type_list = array();
    return true;
  }

  /* 
   * get object from database
   * @return boolean success
   * @access private
   */
  function get_fromDatabase ( ) {
    global $camyks;
    /* build sql query */
    $sql = 'select *';
    $sql .= ' from content_systemsitereportform';
    $sql .= ' where id='.$this->id;
    
    /* execute sql query */
    if ( $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) ) {
      
      /* get data from database */
      if ( $data = $camyks->db_conn->get_queryDataLine()) {
	    $this->get_fromArray ( $data );
	    return true;
      }
    }
    return false;
  }

  /*
   * save object to database
   * @return boolean success
   * @access private
   */
  function save_toDatabase( ) {
    /* check data validity */
    if ( $this->check_data() ) {
      if ( $this->id == 0 and $this->create_toDatabase()
	   or $this->update_toDatabase()){
	return $this->save_HTMLFiles();
      }
    }
    return false;
  }
  
  /*
   * create object in database
   * @return boolean success
   * @access private
   */
  function create_toDatabase( ) {
    global $camyks;
    /* build sql query */
    $sql = 'insert into `content_systemsitereportform` (';
    $sql .= ' `name`';
    $sql .= ', `type_list`';
    $sql .= ', `layout_name`';
    $sql .= ', `title_mode`';
    $sql .= ', `title_texts`';
    $sql .= ', `title_imgs`';
    $sql .= ', `file_allowed`';
    $sql .= ' ) VALUES ( ';
    $sql .= ' "'.$this->name.'"';
    $sql .= ', "'.$this->type_list.'"';
    $sql .= ', "'.$this->layout_name.'"';
    $sql .= ', '.$this->title_mode.'';
    $sql .= ', "'.addslashes($this->title_texts_).'"';
    $sql .= ', "'.addslashes($this->title_imgs_).'"';
    $sql .= ', '.$this->file_allowed.'';
    $sql .= ' );';
    /* return result of sql query execution */
    if (  $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) ) {
      $this->id = $camyks->db_conn->get_queryGeneratedId();
      return true;
    }
    return false;
  }
  
  /*
   * update object in database
   * @return boolean success
   * @access private
   */
  function update_toDatabase( ) {
    global $camyks;
    /* build sql query */
    $sql = 'update `content_systemsitereportform`';
    $sql .= ' set `name`="'.$this->name.'"';
    $sql .= ', `type_list`="'.$this->type_list.'"';
    $sql .= ', `layout_name`="'.$this->layout_name.'"';
    $sql .= ', `title_mode`='.$this->title_mode.'';
    $sql .= ', `title_texts`="'.addslashes($this->title_texts_).'"';
    $sql .= ', `title_imgs`="'.addslashes($this->title_imgs_).'"';
    $sql .= ', `file_allowed`='.$this->file_allowed.'';
    $sql .= ' where id='.$this->id;
    /* return result of sql query */
    return $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ );
  }
  
  /*
   * delete object in database
   * @return boolean success
   * @access private
   */
  function delete_fromDatabase( ) {
    global $camyks;
    /* build sql query */
    $sql = 'delete from content_systemsitereportform where id='.$this->id;
    /* return result of execute sql query */
    return $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ );
  }
  
  /*
   * install database
   * @return boolean success
   * @access private
   */
  function install( ) {
    global $camyks;
    /* install table in database */
    /* build sql query */
    $sql = 'CREATE TABLE IF NOT EXISTS content_systemsitereportform (';
    $sql .= ' id BIGINT auto_increment,';
    $sql .= ' name  VARCHAR (16),';
    $sql .= ' type_list VARCHAR(255),';
    $sql .= ' layout_name varchar(64) DEFAULT "",';
    $sql .= ' title_mode TINYINT default 0,';
    $sql .= ' title_texts TEXT DEFAULT "",';
    $sql .= ' title_imgs TEXT DEFAULT "",';
    $sql .= ' file_allowed tinyint unsigned default 0';
    $sql .= ' PRIMARY KEY(id) )';
    $sql .= ' CHARACTER SET '.$camyks->get_mysqlencodingvalue( );
    /*  sql query execution */
    if  ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) ) {
      /* create folder */
      if ( folder_createPath ( $this->_libParent->plugin_var_path.'/img', '',  0771) and
	   folder_createPath ( $this->_libParent->plugin_var_path.'/html', '',  0771)) {
	return true;
      } else {
	$camyks->log_pluginerror( $this->_libParent, 
				  'Installation Failed', 
				  'Could not create "var" folder in site folder');
      }
    }
    return false;
  }
  
  /*
   * uninstall database
   * @return boolean success
   * @access private
   */
  function uninstall( ) {
    global $camyks;
    /* build sql query */
    $sql = 'drop table content_systemsitereportform';
    /* return result of sql query execution */
    return $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ );
  }
  
  /*
   * check module installation
   * @return boolean result
   * @access private
   */
  function is_installed () {
    global $camyks;
    if ( $this->_libIsInstalled === null ) {
    
      /* check with plugin manager */
      if (isset($camyks->modules['Admin_PluginManager'])) {
        $this->_libIsInstalled = $camyks->modules['Admin_PluginManager']->check_tableExists('content_systemsitereportform');
      } else {
    
        /* build sql query */
        $sql = "show tables like 'content_systemsitereportform'";
      
        /* execute sql query */
        if ( $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) ) {
	      /* return info from database */
	      $this->_libIsInstalled = ($camyks->db_conn->get_queryDataLine()!==false);
        }
      }
    }
    return $this->_libIsInstalled;
  }

  /*********************** HTML ****************************/

  /*
   * save HTML contents
   * @return boolean success
   * @access private
   */
  function save_HTMLFiles( ) {
    $fcontent = file_getPHPFileHeader( 'htmlcontent file', '1.0' );
    $fcontent .= file_getPHPFileFooter();
  
    foreach ( $this->descriptions as $c=>$v ) {
      if ( get_magic_quotes_gpc() ) {
	$v = stripslashes( $v );
      }
      $this->filepath = $this->_libParent->plugin_var_path.'/html/file'. $this->id.'_'.$c.'.html.inc';
      if ( ! file_write( $this->filepath, $fcontent."\n".$v ) ) {
	return false;
      }
    }
    return true;
  }

  /*
   * load HTML contents
   * @return void
   * @access private
   */
  function get_HTMLFiles ( ) {
    global $camyks;
    $this->descriptions = array();
    foreach ( $camyks->site_conf['editing_languages'] as $l ) {
      $this->descriptions[$l] = $this->_libParent->get_varFilePath ( 'html/file'.$this->id.'_'.$l.'.html.inc');
    }
  }
  
  /*
   * load current language content
   * @return void
   * @access private
   */
  function get_HTMLContent() {
    global $camyks;
    $this->description = 'html/file'. $this->id.'_'.$camyks->current_language.'.html.inc';
    $this->_libParent->load_varFile ( $this->description );
  }

  
  /*
   * get object values from array
   * @return void
   * @access private
   */
  function get_fromArray( $data ) {
    global $camyks;
    $this->id = $data['id'];
    $this->name = $data['name'];
    $this->type_list = $data['type_list'];
    $this->layout_name = $data['layout_name'];
    $this->title_mode = $data['title_mode'];
    $this->title_texts_ = stripslashes($data['title_texts']);
    $this->title_imgs_ = stripslashes($data['title_imgs']);
    $this->title_texts = data_decode_properties( $this->title_texts_ );
    $this->title_imgs = data_decode_properties( $this->title_imgs_ );
    $this->file_allowed = $data['file_allowed'];
    $this->type_list = explode (',', $this->type_list );
  }

  /*
   * get object values from header
   * @return void
   * @access private
   */
  function get_fromHeader ( ) {
    global $camyks;
    $this->name = isset ( $_REQUEST['name'] ) ? $_REQUEST['name'] : '';

    $type_count = isset ( $_REQUEST['type_count'] ) ? $_REQUEST['type_count'] : 0;
    $this->type_list = array();
    for ( $i=0; $i< $type_count; $i++ ) {
      if ( isset ( $_REQUEST['type_'.$i] ) and $_REQUEST['type_'.$i]>0 ) {
	$this->type_list[] = $_REQUEST['type_'.$i];
      }
    }

    $this->layout_name = isset ( $_REQUEST['layout_name'] ) ? $_REQUEST['layout_name'] : '';
    $this->title_mode = isset ( $_REQUEST['title_mode'] ) ? $_REQUEST['title_mode'] : '';

    $this->title_texts = array();
    $this->title_texts['gen'] = isset ( $_REQUEST['title_text_gen'] ) ? $_REQUEST['title_text_gen'] : '';
    foreach ( $camyks->site_conf['editing_languages'] as $l ) {
      $this->title_texts[$l] = isset ( $_REQUEST['title_text_'.$l] ) ? $_REQUEST['title_text_'.$l] : '';
    }

    $this->title_imgs = array();
    $this->title_imgs['gen'] = $this->get_imageFromHeader( 'gen' );
    foreach ( $camyks->site_conf['editing_languages'] as $l ) {
      $this->title_imgs[$l] = $this->get_imageFromHeader( $l );
    }

    $this->descriptions = array();
    foreach ( $camyks->site_conf['editing_languages'] as $l ) {
      $this->descriptions[$l] = isset ( $_REQUEST['description_'.$l] ) ? $_REQUEST['description_'.$l] : '';
    }

    $this->type_list = implode (',', $this->type_list );
    $this->title_texts_ = data_encode_properties ( $this->title_texts );
    $this->title_imgs_ = data_encode_properties ( $this->title_imgs );

    $this->file_allowed = isset($_REQUEST['file_allowed'])?$_REQUEST['file_allowed']:0;
  }

  /*
   * get image name / file from header
   * @param string $img
   * @return string 
   * @access private
   */
  function get_imageFromHeader( $img ) {

    /* get value from header */
    if ( isset ( $_REQUEST['title_img_'.$img] ) and ( $_REQUEST['title_img_'.$img] != '' ) ) {
      return $_REQUEST['title_img_'.$img];
    }

    /* get file */
    $p = $this->_libParent->plugin_var_path.'/img/';

    if ( isset ( $_FILES['up_title_img_'.$img] ) ) {
      $n = basename($_FILES['up_title_img_'.$img]['name'] );
      if ( move_uploaded_file( $_FILES['up_title_img_'.$img]['tmp_name'], $p.$n ) ) {
	return $n;
      }
      return '';
    }
    /* no header and file value */ 
    return '';
  }
 
  /*
   * check object data
   * @return boolean result
   * @access private
   */
  function check_data( ) {
    global $camyks;
    /* check name */
    if ( $this->name == '' ) {
      $this->name = 'form'.$this->id;
    }
    return true;
  }

  /*
   * return site title
   * @return string
   * @access private
   */
  function get_siteTitle ( ) {
    global $camyks;
    switch ( $this->title_mode ) {
    case 0:
      return '';
    case 1:
      return isset ( $this->title_texts['gen'] ) ? $this->title_texts['gen'] : '';
    case 2:
      if ( isset ( $this->title_imgs['gen']) and $this->title_imgs['gen'] != '' ) {
	return '<img src="'.$this->_libParent->get_varFileURL('img/'.$this->title_imgs['gen']).'" alt="" border="0"/>';
      } else {
	return '';
      }
    case 3:
      return isset ($this->title_texts[$camyks->current_language])?$this->title_texts[$camyks->current_language]:'';
    case 4:
      if ( isset ( $this->title_imgs[$camyks->current_language]) and $this->title_imgs[$camyks->current_language] != '') {
	return '<img src="'.$this->_libParent->get_varFileURL('img/'.$this->title_imgs[$camyks->current_language]).'" alt="" border="0"/>';
      } else {
	return '';
      }
    }
    return '';
  }

  /*
   * return all available items name
   * @return array
   * @access private
   */
  function get_namelist ( ) {
    global $camyks;
    $items = array();
    /* build sql query */
    $sql = 'select id, name';
    $sql .= ' from content_systemsitereportform';

    /* execute sql query */
    if ( $camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) ) {
      /* get data from database */
      while ( $data = $camyks->db_conn->get_queryDataLine()) {
	$items[$data['id']] = $data['name'];
      }  
    }
    return $items;
  }

  /*
   * update library to version 1.01
   * @return boolean success
   * @access private
   */
  function update_toVersion1_01() {
    global $camyks;
    /* build sql query */
    $sql = 'alter ignore table content_systemsitereportform add column file_allowed tinyint unsigned default 0;';
    /* execute sql query */
    return ($camyks->db_conn->execute_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__));
  }
}
?>