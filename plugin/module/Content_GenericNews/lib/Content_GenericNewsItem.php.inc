<?php
/*
 * CaMyks Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Module Library
 * Create Date		: Mar 2007
 * Last Modif Date	: Mar 2007
 *
 * Content_GenericNewsItem object for Content_GenericNews module
*/
class Content_GenericNewsItem extends ModuleLibrary {  
  /*
   * constructor
   * @param integer $id
   * @param Module $module
   */
  function Content_GenericNewsItem ( $id, &$module ) {
    parent::ModuleLibrary( $id, $module );
    /* content */
    $this->add_newItem('listid', 'db', 'int', 'bigint unsigned', '', 0);
    $this->add_newItem('language', 'db', 'text', 'varchar', 3, '');
    $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('title', 'db', 'etext', 'varchar', 255, '');
    $this->add_newItem('content', 'db', 'etext', 'text', '', '');
    $this->add_newItem('author', 'db', 'text', 'varchar', 32, '' );
    $this->add_newitem('ndate', 'db', 'date', 'bigint unsigned', '', time());
    $this->add_newitem('source_title', 'db', 'etext', 'varchar', 255, '');
    $this->add_newitem('source_url', 'db', 'etext', 'varchar', 255, '');
    /* compile library */
    $this->init_library();
  }

  /* overwrite ModuleLibrary methods */

  /*
   * initialise object
   * @return boolean success 
   * @access private
   */
  function initialise () {
    global $camyks;
    /* generic object initialisation */
    parent::initialise();
    /* update author value */
    $this->_libItems['author']->value = $camyks->adminUser->login; 
    return true;
  }

  /* specific tool methods */

  /*
   * return items list for an admin usage
   * @param integer $listid
   * @param integer $page
   * @param integer $bypage
   * @return array
   * @access private
   */
  function get_adminlist ( $listid, $page=-1, $bypage=-1  ) {
    global $camyks;
    if ( $page>-1 and $bypage>-1 )
      return $this->get_objectList(true,
				   'listid='.$listid.'',
				   $page*$bypage, 
				   $bypage, 
				   'ndate', 
				   'desc');
    return $this->get_objectList(true,
				 'listid='.$listid.'',
				 -1,
				 -1,
				 'ndate', 
				 'desc');
  }

  /*
   * return item list for a site usage
   * @param integer $listid
   * @param integer $page
   * @param integer $bypage
   * @return array
   * @access private
   */
  function get_sitelist ( $listid, $page=-1, $bypage=-1  ) {
    global $camyks;
    $items = array();

    /* build sql query */
    $sql = 'select content_genericnewsitem.id,';
    $sql .= 'content_genericnewsitem.listid,';
    $sql .= 'content_genericnewsitem.ndate,';
    $sql .= 'content_genericnewsitem.title,';
    $sql .= 'content_genericnewsitem.content,';
    $sql .= 'content_genericnewsitem.source_title,';
    $sql .= 'content_genericnewsitem.source_url,';
    $sql .= 'content_genericnewsitem.author,';
    $sql .= 'admin_user.firstname,';
    $sql .= 'admin_user.lastname,';
    $sql .= 'admin_user.email';
    $sql .= ' from content_genericnewsitem, admin_user';
    $sql .= ' where listid='.$listid;
    $sql .= ' and language="'.$camyks->current_language.'"';
    $sql .= ' and status=1';
    $sql .= ' and ndate<'.mktime();
    $sql .= ' and admin_user.login = content_genericnewsitem.author';
    $sql .= ' order by ndate DESC';
    if ( $bypage > 0 and $page > -1 ) {
      $sql .= ' limit '.($page*$bypage).', '.$bypage;
    }
    /* execute sql query */
    if ( $req = mysql_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) ) {
      /* get data from database */
      while ( $data = mysql_fetch_assoc( $req )) {
	$item = new Content_GenericNewsItem ( $data['id'], $this->_libParent );
	$item->get_fromArray( $data, $this->_libItemTypes['db'] );
	$item->get_fromItems();
	/* check author name */
	if ( $data['firstname'] == '' and $data['lastname'] == '' ) {
	  $item->vars['author'] = $data['author'];
	} else if ( $data['firstname'] == '' ) {
	  $item->vars['author'] = $data['lastname'];
	} else if ( $data['lastname'] == '' ) {
	  $item->vars['author'] = $data['firstname'];
	} else {
	  $item->vars['author'] = $data['firstname'] . ' ' . $data['lastname'];
	}

	/* check author email */
	if ( $data['email'] != '' ) {
	  $item->vars['author'] = '<a href="'.mail_encode($data['email']).'" class="link1">'.$item->vars['author'].'</a>';
	}
	$items[] = $item;
      }  
    }
    return $items;
  }

  /*
   * return item count
   * @param integer $listid
   * @param integer $status
   * @param string $lg
   * @return integer 
   * @access private
   */
  function get_listcount( $listid, $status=-1, $lg='', $dated=false ) {
    global $camyks;
    $where = 'listid='.$listid;
    if ( $status > -1 ) {
      $where .= ' and status='.$status;
    }
    if ( $lg != '' ) {
      $where .= ' and language="'.$lg.'"';
    }
    if ( $dated == true ) {
      $where .= ' and ndate<'.time(); 
    }
    return $this->get_objectCount( $where );
  }
}
?>