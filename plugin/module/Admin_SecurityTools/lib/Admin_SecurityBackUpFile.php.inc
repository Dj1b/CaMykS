<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Library
 * Creation Date	: Oct 2007
 * Last Modif Date	: Oct 2007
 *
 * Admin_SecurityBackUpFile Library Object for Admin_SecurityTools Module
 * Items :
 * - name : file name
 * - ndate : date where backup was created
 * - type : backup type 
 * -- complete : full site folder + database
 * -- data : var folder + database
 * -- file : var folder
 */

class Admin_SecurityBackUpFile extends ModuleLibrary {
  /* variables */
  var $backupdir;
  
  /*
   * constructor
   * @param integer $id
   * @param Module $parent
   */
  function Admin_SecurityBackUpFile ( $id, &$parent ) {
    global $camyks;
    parent::ModuleLibrary( $id, $parent );
    /* library items */
    $this->add_newItem('name', 'db', 'text', 'varchar', 32, '');
    $this->add_newItem('ndate', 'db', 'date', 'bigint unsigned', '', time());
    $this->add_newItem('type', 'db', 'text', 'varchar', '8', 0);    
    /* variables */
    $this->backupdir = 'backups';
    /* generic library initialisation */
    parent::init_library();
  }

  /* specific tool methods */

  /*
   * return current backup file size display
   * @return string
   * @access private
   */
  function get_fileSize() {
    $f = new FSFile( $this->_libParent->plugin_var_path.'/'.$this->backupdir, $this->vars['name'] );
    return $f->hsize;
  }

  /*
   * create a backup
   * @param string $method
   * @param string $type
   * @param string $compression
   * @return boolean success
   * @access private
   */
  function backup( $method=null, $type=null, $compression=null ) {
    global $camyks;

    /* extends script time limitation */
    set_time_limit(300);

    /* load PEAR archive Object */
    require_once ('File/Archive.php');
    
    /* check if parent config is available */
    if ( !isset( $this->_libParent->config->vars ) ) {
      $this->_libParent->config->get();
    }
    
    $method = isset($method)?$method:$this->_libParent->config->vars['backup_method'];
    $type = isset($type)?$type:$this->_libParent->config->vars['backup_type'];
    $compression = isset($compression)?$compression:$this->_libParent->config->vars['backup_compression'];
    
    /* init pathes */
    $backupPath = $this->_libParent->plugin_var_path;
    $backupFolder = $backupPath.'/'.$this->backupdir;
    if ( $this->_libParent->config->vars['backup_temp'] == '' ) 
      $tempPath = folder_getTemporaryFolder();
    else 
      $tempPath = $this->_libParent->config->vars['backup_temp'];
    $tempFolder = $tempPath.'/'.$this->backupdir;
    
    /* delete previous temp folder if exists */
    folder_delete($tempFolder, true);
    
    /* temp folder not found, what to do ? */
    if ( $tempPath === false ) {
      return;
    }
    
    /* built backupFolder path if needed */
    if ( !file_exists( $backupFolder ) ){
      folder_completePath($backupFolder);
    }
    
    /* move old backups to temp */
    if ( folder_move( $backupFolder, $tempPath ) ) {
      /* create random backup file name */
      $x = 0;
      $name = '';
      while( file_exists($tempFolder.'/'.$name)) {
	    $name = md5('backup'.time());
	    $name = substr($name, -8);
	    $name = 'backup_'.$name.'.'.$compression;
      }
      
      $fileArchive = new File_Archive();
      
      /* create backup case of type into temp folder */
      switch ( $type ) {
      case 'complete':
	    /* dump database into root folder */
	    $camyks->db_conn->database_dump($camyks->site_path.'/'.$camyks->site_conf['site_name'].'.sql');
	    
	    /* create full site folder archive */
	    $fileArchive->extract(
	        $fileArchive->read($camyks->site_path),
			$fileArchive->toArchive(
			    $tempFolder.'/'.$name,
			    $fileArchive->toFiles(),
			    $compression
		    )
	    );
	    break;
      case 'data':
	    /* dump database into var folder */
    	$camyks->db_conn->database_dump($camyks->site_var_path.'/'.$camyks->site_conf['site_name'].'.sql');
    	
	    /* create full site folder archive */
	    $fileArchive->extract(
	        $fileArchive->read($camyks->site_var_path),
			$fileArchive->toArchive(
			    $tempFolder.'/'.$name,
			    $fileArchive->toFiles(),
			    $compression
			)
		);
	    break;
      case 'file':
	    /* create full site folder archive */
	    $fileArchive->extract(
	        $fileArchive->read($camyks->site_var_path),
			$fileArchive->toArchive(
			    $tempFolder.'/'.$name,
			    $fileArchive->toFiles(),
			    $compression
			)
	    );	
	    break;
      }

      /* move backups to there original location */
      if ( folder_move( $tempFolder, $backupPath ) ) {
	    /* save backup info into database */
	    $this->id = 0;
	    $this->_libItems['ndate']->value = time();
	    $this->_libItems['name']->value = $name;
	    $this->_libItems['type']->value = $type;
	    $this->save();
	    /* log backup */
    	$camyks->log_information( $this,
				  ucfirst($method.' backup done successfully.'),
				  '');
	    return true;
      } else {
	    /* log critical error : can't move back backup folder */
    	$camyks->log_executionerror( $this,
				     ucfirst($method.' backup failure.'),
				     'Can\'t move back backups folder.');
      }
    } else {
      /* log error :  can't move backup folder */
      $camyks->log_executionerror( $this,
				   ucfirst($method.' backup failure.'),
				   'Can\'t move backups folder.');
    }
    return false;
  }
}
?>