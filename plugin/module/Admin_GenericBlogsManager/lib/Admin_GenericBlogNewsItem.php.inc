<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author               : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version       : 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Module Lib
 * Create Date          : Apr 2008
 * Last Modif Date      : Apr 2008
 *
 * Admin_GenericBlogNewsItem object for Admin_GenericBlogsManager module
*/
class Admin_GenericBlogNewsItem extends ModuleLibrary {
  /*
   * Constructor
   * @param integer $id
   * @param Module $module
   */
  function Admin_GenericBlogNewsItem ( $id, &$module ) {
    parent::ModuleLibrary( $id, $module );
    /* content */
    $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
    $this->add_newItem('title', 'db', 'etext', 'varchar', 255, '');
    $this->add_newItem('content', 'db', 'etext', 'text', '', '');
    $this->add_newItem('author', 'db', 'text', 'varchar', 32, '' );
    $this->add_newItem('ndate', 'db', 'date', 'bigint unsigned', '', time());
    $this->add_newItem('videolink', 'db', 'etext', 'text', '', '');
    /* generic initialisation */
    $this->init_library();
  }

  /* overwrite ModuleLibrary methods */

  /*
   * initialise object
   * @return boolean success
   * @access private
   */
  function initialise() {
    global $camyks;
    /* generic initialisation */
    if ( parent::initialise() ) {
      /* update admin user author */
      $this->_libItems['author']->value = $camyks->adminUser->login;
      /* return success */
      return true;
    }
    return false;
  }

  /*
   * check data
   * @return boolean result
   * @access private
   */
  function check_data() {
    /* get tag list */
    $tagCount = isset($_REQUEST['tagCounter'])?$_REQUEST['tagCounter']:0;

    $this->oldTags = array();
    $this->newTags = array();

    for ( $i=0; $i< $tagCount; $i ++ ) {
      if ( isset( $_REQUEST['tag'.$i.'_id'] ) ) {
	$id = $_REQUEST['tag'.$i.'_id'];
	$value = $_REQUEST['tag'.$i.'_value'];

	if ( $id > 0 ) {
	  $this->oldTags[ $id ] = $value;
	} else {
	  if ( !in_array( $value, $this->oldTags ) ) {
	    $this->newTags[] = $value;
	  }
	}
      }
    }
    return true;
  }

  /*
   * save object
   * @return boolean success
   * @access private
   */
  function save() {
    if ( parent::save() === true ) 
      return $this->save_tags();
  }

  /* specific methods */
  
  /*
   * get linked tag objects list
   * @return void
   * @access private
   */
  function get_tagList() {
    global $camyks;

    /* get tag item */
    $tagItem = &$this->_libParent->tagItem;

    /* get tag list */
    if ( $this->id == 0 )
      $this->tagList = array();
    else
      $this->tagList = $tagItem->get_objectList(false, 'newsid='.$this->id);
  }
  
  /*
   * get comment objects list
   * @return void
   * @access private
   */
  function get_blogComments() {
    global $camyks;

    /* get tag item */
    $commentItem = &$this->_libParent->commentItem;

    /* get tag list */
    if ( $this->id == 0 )
      $this->vars['comments'] = array();
    else
      $this->vars['comments'] = $commentItem->get_objectList(false, 'newsid='.$this->id.' and status=1');
  }


  /*
   * save news 
   * @return boolean succes
   * @access private
   */
  function save_tags() {
    global $camyks;

    /* get tag item */
    $tagItem = &$this->_libParent->tagItem;

    /* delete old unused tags */
    $tagIDs = array_keys( $this->oldTags );  
    if( count( $tagIDs ) > 0 ) {
      if ( $tagItem->prune_oldNewsTags( $this->id, $tagIDs ) === false )
	return false;
    }

    /* insert new tags */
    $tagItem->_libItems['author']->value = $camyks->adminUser->login;
    $tagItem->_libItems['newsid']->value = $this->id;;
    foreach( $this->newTags as $tag ) {
      $tagItem->id = 0;
      $tagItem->_libItems['title']->value = $tag;
      if ($tagItem->save() === false )
	return false;
    }
    
    /* return success */
    return true;
  }

  /*
   * return object list by date
   * @param array $authors
   * @param string $tag
   * @param integer $page
   * @param integer $count
   * @return array
   * @access private
   */
  function get_blogItemList( $authors, $tag, $page, $count, $dated=false ) {
    global $camyks;

    $items = array();
    /* build sql query */
    $sql = 'select m.*';
    $sql .= ' from '.$this->_libSQLTable.' as m';
    if ( $tag != null and $tag != '' )
      $sql .= ', '.$this->_libParent->tagItem->_libSQLTable.' as t';
    
    /* check active */
    $sql .= ' where m.status=1';
    
    /* check authors */
    if ( count($authors)==1 )
      $sql .= ' and m.author="'.$authors[0].'"';
    else if ( count($authors) > 1 )
      $sql .= ' and m.author in ("'.implode('","', $authors).'")';
      
    /* check date */
    if ( $dated == true ) {
      $sql .= ' and m.ndate < '.time();
    }
    
    /* check tags */
    if ( $tag != null and $tag != '' ) {
      $sql .= ' and t.name="'.$tag.'"';
      $sql .= ' and t.newsid=m.id';
    }

    /* add order */
    $sql .= ' order by m.ndate desc';

    /* add limit */
    $sql .= ' limit '.$page*$count.', '.$count;
    

    /* execute query */
    if ( $req = mysql_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) ) {
      /* gather data */
      while ( $data = mysql_fetch_assoc( $req )) {
	$item = new Admin_GenericBlogNewsItem ( $data['id'], $this->_libParent );
	$item->get_fromArray( $data, $this->_libItemTypes['db'] );
	$item->get_fromItems();
	$item->vars['coms'] = 0;
	$item->tagList = array();
	$items[$data['id']] = $item;
      }
    }

    /* complete data */
    if ( count($items) > 0 ) {
      $ids = array_keys($items);
      /* get items tags */
      $tags = $this->_libParent->tagItem->get_objectList(false, 'newsid IN('.implode(',', $ids).')');
      foreach ( $tags as $tag ) {
	$items[$tag->vars['newsid']]->tagList[] = $tag;
      }
      

      /* get items comment counts */
      $comCount = $this->_libParent->commentItem->count_newsComments($ids, 1);
      foreach( $comCount as $newsid=>$coms ) {
	$items[$newsid]->vars['coms'] = $coms;
      }
    }
    return $items;
  }
  
  /*
   * return object count
   * @param array $authors
   * @param string $tag
   * @return array
   * @access private
   */
  function get_blogItemCount( $authors, $tag, $dated=false ) {
    global $camyks;
    
    /* build sql query */
    $sql = 'select count(m.id) as c';
    $sql .= ' from '.$this->_libSQLTable.' as m';
    if ( $tag != null and $tag != '' )
      $sql .= ', '.$this->_libParent->tagItem->_libSQLTable.' as t';
    
    /* check active */
    $sql .= ' where m.status=1';
    
    /* check authors */
    if ( count($authors)==1 )
      $sql .= ' and m.author="'.$authors[0].'"';
    else if ( count($authors) > 1 )
      $sql .= ' and m.author in ("'.implode('","', $authors).'")';
    
    /* check date */
    if ( $dated == true ) {
      $sql .= ' and m.ndate < '.time();
    }
    
    /* check tags */
    if ( $tag != null and $tag != '' ) {
      $sql .= ' and t.name="'.$tag.'"';
      $sql .= ' and t.newsid=m.id';
    }
    
    /* execute query */
    if ( $req = mysql_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) )
      /* gather data */
      if ( $data = mysql_fetch_assoc( $req ))
	return $data['c'];
    return 0;
  } 

  /*
   * return news count by author from given author list
   * @param array $authors
   * @return array
   * @access public
   */
  function get_newsCountByAuthor( $authors, $dated=false ) {
    global $camyks;
    
    /* initialise result array */
    $result = array();

    /* pre-initialise result array values */
    if ( count( $authors ) ) {
      foreach ( $authors as $a )
	$result[$a] = 0;
    }

    /* build sql query */
    $sql = 'select count(id) as c, author';
    $sql .= ' from '.$this->_libSQLTable.' as m';
    
    /* check active */
    $sql .= ' where status=1';
    
    /* check authors */
    if ( count($authors)==1 )
      $sql .= ' and author="'.$authors[0].'"';
    else if ( count($authors) > 1 )
      $sql .= ' and author in ("'.implode('","', $authors).'")';
    else
      $sql .= ' and author<>""';

    /* check date */
    if ( $dated == true ) {
      $sql .= ' and m.ndate < '.time();
    }

    /* add group statement */
    $sql  .= ' group by author';
    /* execute query */
    if ( $req = mysql_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) )
      /* gather data */
      while ( $data = mysql_fetch_assoc( $req ))
	$result[$data['author']] = $data['c'];
    return $result;    
  }

  /*
   * return news count by tag from given author list
   * @param array $authors
   * @return array
   * @access public
   */
  function get_newsCountByTag( $authors, $dated=false ) {
    global $camyks;
    
    /* initialise result array */
    $result = array();

    /* build sql query */
    $sql = 'select t.title as title, t.name as name, count(t.id) as c';
    $sql .= ' from '.$this->_libSQLTable.' as m';
    $sql .= ', '.$this->_libParent->tagItem->_libSQLTable.' as t';
    
    /* check active */
    $sql .= ' where m.status=1';
    
    /* check authors */
    if ( count($authors)==1 )
      $sql .= ' and m.author="'.$authors[0].'"';
    else if ( count($authors) > 1 )
      $sql .= ' and m.author in ("'.implode('","', $authors).'")';
    
    /* check date */
    if ( $dated == true ) {
      $sql .= ' and m.ndate < '.time();
    }
    
    /* check tags */
    $sql .= ' and t.newsid=m.id';
    
    /* add groupe statement */
    $sql .= ' group by title, name';

    /* execute query */
    if ( $req = mysql_query($sql) or $camyks->log_sqlerror( $this, $sql, __FILE__, __LINE__ ) )
      /* gather data */
      while ( $data = mysql_fetch_assoc( $req )) {
	$tag = new Admin_GenericBlogTagItem(0, $this->_libParent);
	$tag->vars = array();
	$tag->vars['title'] = $data['title'];
	$tag->vars['name'] = $data['name'];
	$result[] = array('count'=>$data['c'], 'tag'=>$tag);
      }
    return $result;
  }

  /*
   * check if object is valid for site display
   * @param array $validAuthors
   * @return boolean sucess
   * @access private
   */
  function check_siteDisplay($validAuthors) {
    /* check status */
    if ( $this->_libItems['status']->value == 0 )
      return false;

    /* check author */
    if ( count($validAuthors)>0 and in_array($this->_libItems['author']->value, $validAuthors)===false )
      return false;

    /* return default value */
    return true;
  }
}
?>