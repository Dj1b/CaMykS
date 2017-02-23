<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * Camyks Version   	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Engine
 * Creation Date	: Apr 2008
 * Last Modif Date	: Jul 2008
 * History :
 * * 08-04-05 : Initial files
 * * 08-05-28 : Disable admin menu for data I/O modes
 * * 08-07-22 : Add support of TinyMCE version 3
 * 
 * Manage admin users blogs
*/

class Admin_GenericBlogsManager extends Module {
  /*
   * constructor
   * @param string $path_type
   */
  function Admin_GenericBlogsManager ( $path_type ) {
    parent::Module('Admin_GenericBlogsManager', $path_type);
    /* set module type */
    $this->type = 'admin';
    $this->admin_type = 'content';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Generic';
    /* set plugin author description */
    $this->authors_name = 'CaMykS Team';
    $this->authors_mail = 'camyks.contact@gmail.com';
    $this->authors_group = 'camyks.net';

    /* variables */
    $this->itemsByPage = 15;

    /* load libraries */
    $this->libs[] = 'Admin_GenericBlogsManagerConfig.php.inc';
    $this->libs[] = 'Admin_GenericBlogNewsItem.php.inc';
    $this->libs[] = 'Admin_GenericBlogLinkItem.php.inc';
    $this->libs[] = 'Admin_GenericBlogTagItem.php.inc';
    $this->libs[] = 'Admin_GenericBlogCommentItem.php.inc';
    $this->get_PHPLibs();

    /* initialise library objects */
    $this->config = new Admin_GenericBlogsManagerConfig('blogconfig', $this);
    $this->linkItem = new Admin_GenericBlogLinkItem(0, $this);
    $this->tagItem = new Admin_GenericBlogTagItem(0, $this);
    $this->commentItem = new Admin_GenericBlogCommentItem(0, $this);
    $this->newsItem = new Admin_GenericBlogNewsItem(0, $this);
  }
  
  /* overwrite Module methods */  

  /*
   * install module object
   * @return boolean success
   * @access private
   */
  function install() {
    if ( $this->config->install() and $this->newsItem->install()
	 and $this->linkItem->install() and $this->tagItem->install()
	 and $this->commentItem->install())
      return parent::install();
    return false;
  }

  /*
   * uninstall module object 
   * @return boolean success
   * @access private
   */
  function uninstall() {
    return false;
  }

  /*
   * check installation
   * @return boolean result
   * @access private
   */
  function is_installed() {
    return $this->commentItem->is_installed();
  }

  /*
   * update description in control panel
   * @return void
   * @access private
   */
  function get_adminControlPanelAction ( ) {
    global $camyks;

    $n = null;
    if ( $this->check_right(7)===true )
      $n = $this->commentItem->get_objectCount('status=0');
    else if ( $this->check_right(6)===true)
      $n = $this->commentItem->count_userNewsUnreadComments();

    if ( $n == 1 )
      $camyks->trads['mod_admin_genericblogsmanager_desc'] = $camyks->trads['mod_admin_genericblogsmanager_desc1'];
    else if ( $n > 1 )
      $camyks->trads['mod_admin_genericblogsmanager_desc'] = vsprintf($camyks->trads['mod_admin_genericblogsmanager_descx'], $n);
  }


  /*
   * initialise module object in admin mode
   * @return void
   * @access private
   */
  function init_admin () {
    global $camyks;
    /* check user rights */
    if ( $this->check_right(0) === false )
      return $this->init_admin_accessDenied();

    /* load configuration */
    $this->config->get();

    /* get informations */
    $this->mode = ( isset ( $_REQUEST['mode'] ) ? $_REQUEST['mode'] : 'main' );
    
    switch ( $this->mode ) {
    case 'editlink':
      /* mode == editlink */
      $this->init_admin_editLink();
      break;  
    case 'savelink':
      /* mode == savelink */
      $this->init_admin_saveLink();
      break;  
    case 'deletelink':
      /* mode == deletelink */
      $this->init_admin_deleteLink();
      break;  
    case 'savetag':
      /* mode == savetag */
      $this->init_admin_saveTag();
      break;  
    case 'deletetag':
      /* mode == deletetag */
      $this->init_admin_deleteTag();
      break;
    case 'saveconfig':
      /* mode == saveconfig */
      $this->init_admin_saveConfig();
      break;
    case 'editnews':
      /* mode == editnews */
      $this->init_admin_editNews();
      break;
    case 'savenews':
      /* mode == savenews */
      $this->init_admin_saveNews();
      break;
    case 'deletenews':
      /* mode == deletenews */
      $this->init_admin_deleteNews();
      break;
    case 'viewcomments':
      /* mode == viewcomments */
      $this->init_admin_viewComments();
      break;
    case 'editcomment':
      /* mode == editcomment */
      $this->init_admin_editComment();
      break;
    case 'savecomment':
      /* mode == savecomment */
      $this->init_admin_saveComment();
      break;
    case 'deletecomment':
      /* mode == deletecomment */
      $this->init_admin_deleteComment();
      break;
    case 'updatecommentstatus':
      /* mode == updatecommentstatus */
      $this->init_admin_updateCommentStatus();
      break;
    case 'main':
    default:
      /* mode == main */
      $this->init_admin_main();
      break;
    }
    parent::init_admin();
  }
  
  /*
   * display module object in admin mode
   * @return void
   * @access private
   */
  function display_admin () {
    parent::display_admin();
  }

  /*
   * set module rights
   * @return void
   * @access private
   */
  function get_rights ( ) {
    global $camyks;
    $this->rights[0] = array('name'=>'read',
			     'title'=> $camyks->get_translation('read'),
			     'default'=> true);
    $this->rights[1] = array('name'=>'config',
			     'title'=> $this->get_translation('right_config'),
			     'default'=> false);
    $this->rights[2] = array('name'=>'news_limited',
			     'title'=> $this->get_translation('right_news_limited'),
			     'default'=> true);
    $this->rights[3] = array('name'=>'news_global',
			     'title'=> $this->get_translation('right_news_global'),
			     'default'=> false);
    $this->rights[4] = array('name'=>'link_limited',
			     'title'=> $this->get_translation('right_link_limited'),
			     'default'=> true);
    $this->rights[5] = array('name'=>'link_global',
			     'title'=> $this->get_translation('right_link_global'),
			     'default'=> false);
    $this->rights[6] = array('name'=>'comment_limited',
			     'title'=> $this->get_translation('right_comment_limited'),
			     'default'=> true); 
    $this->rights[7] = array('name'=>'comment_global',
			     'title'=> $this->get_translation('right_comment_global'),
			     'default'=> false);
    $this->rights[8] = array('name'=>'tag_limited',
			     'title'=> $this->get_translation('right_tag_limited'),
			     'default'=> false);
    $this->rights[9] = array('name'=>'tag_global',
			     'title'=> $this->get_translation('right_tag_global'),
			     'default'=> false);
  }

  /* specific module mode methods */

  /*
   * initialise module object in admin/main mode
   * @return void
   * @access private
   */
  function init_admin_main() {
    global $camyks;

    /* check itemsByPage value */
    if (isset($camyks->_conf['admin_itemsbypage']))
      $this->itemsByPage = $camyks->_conf['admin_itemsbypage'];

    /* get module scripts */
    $this->add_JSFile('genericblogsmanager.js');

    /* get tab engine */
    $this->tabObject = 'gbm_tabObject';
    $this->add_JSEngineFile('object/ctab.js');
    $this->add_JSScript($this->tabObject.' = new CTab();');
    $this->add_JSScript($this->tabObject.'.init("news", "'
      .$this->theme->parts['boxTabCSSStandart'].'","'
      .$this->theme->parts['boxTabCSSSelected'].'","'
      .$this->theme->parts['boxTabCSSRollover'].'");');

    if ( isset( $_REQUEST['openTab'] ) )
      $this->add_JSLoadScript($this->tabObject.'.mouseclick(\''.$_REQUEST['openTab'].'\');');
    $this->tabs = array();
    /* configuration tab */
    if( $this->check_right(1)===true ) {
      $this->tabs[] = array('name'=>'configuration',
			    'title'=>$this->get_translation('tabconfig'));

      $this->editorMode = (isset( $camyks->inputs['TinyMCEv3']) or isset($camyks->inputs['TinyMCE']));
    }
    /* news tab */
    $this->tabs[] = array('name'=>'news',
			  'title'=>$this->get_translation('tabnews'));

    /* links management */
    if ( $this->check_right(4)===true or $this->check_right(5)===true ) {
      /* load links */
      if ( $this->check_right(5) === true ) {
	$this->links = $this->linkItem->get_objectList(false);
	$this->adminLinkCount = 0;
	foreach ( $this->links as $l )
	  if ( $l->vars['author'] == $camyks->adminUser->login )
	    $this->adminLinkCount ++;
      } else {
	$this->links = $this->linkItem->get_objectList(false, 'author="'.$camyks->adminUser->login.'"');
	$this->adminLinkCount = count( $this->links );
      }

      /* links tab */
      $this->tabs[] = array('name'=>'links',
			    'title'=>$this->get_translation('tablinks'));
      
      /* links links */
      $this->editLinkLink = $camyks->get_adminLink($this->name, array('mode'=>'editlink', 'link_id'=>''));
      /* delete link javascript */
      $this->add_JSScript('var deleteLinkMessage="'.utf8_encode(html_entity_decode($this->get_translation('links_deletemessage'))).'";');
      $this->add_JSScript('var deleteLinkLink="'.$camyks->get_adminJSLink($this->name, array('mode'=>'deletelink', 'link_id'=>'')).'";');
    }

    /* tags tab */
    if ( $this->check_right(8)=== true or $this->check_right(9)===true ) {
      $this->tabs[] = array('name'=>'tags',
			    'title'=>$this->get_translation('tabtags'));
      $this->tagList = $this->tagItem->get_countTagList($this->check_right(9));

      /* build tag editor form */
      $this->tagEditor = new HTMLForm('tagEditor_form',
				      $camyks->get_adminLink($this->name,
							     array('mode'=>'savetag')));
      $this->tagEditor->add_hidden('tag', '');

      /* delete tag link */
      $this->add_JSScript('var deleteTagMessage="'.utf8_encode(html_entity_decode($this->get_translation('tags_deletemessage'))).'";');
      $this->add_JSScript('var deleteTagLink="'.$camyks->get_adminJSLink($this->name, array('mode'=>'deletetag', 'tag'=>'')).'";');

      /* edit tag scripts */
      $this->add_JSEngineFile('tool/html.js');
      $this->add_JSScript('var genericblogsmanager_tagEditorForm="'.$this->tagEditor->name.'";');
    }

    /* news management */
    $this->newsListForm = new HTMLForm('newslistform',
				       $camyks->get_adminlink($this->name),
				       'POST');

    /* build search query */
    $search = array();
    
    /* get page selection value */
    if ( isset($_REQUEST['newsListPage']) ) {
      $this->newsListPage = (int)$_REQUEST['newsListPage']-1;
      $camyks->set_sessionValue('newsListPage', $this->newsListPage);
    } else
      $this->newsListPage = $camyks->get_sessionValue('newsListPage', 0);

    /* get unread selection value */
    $this->newsListUnread = isset($_REQUEST['newsListUnread'])?$_REQUEST['newsListUnread']:$camyks->get_sessionValue('newsListUnread', 0);    
    $camyks->set_sessionValue('newsListUnread', $this->newsListUnread);

    $this->unreadCommentIds = $this->commentItem->get_newsWithUnreadComments();    
    if ($this->newsListUnread == 1 and count($this->unreadCommentIds) > 0 )
	$search[] = 'id IN('.implode(',', $this->unreadCommentIds).')';
    
    if ( $this->check_right(3) === false )
      $search[] = 'author="'.$camyks->adminUser->login.'"';
    

    $search = implode(' and ', $search);
    /* get news list */
    $this->newsCount = $this->newsItem->get_objectCount($search);
    $this->newsPages = ceil( $this->newsCount/$this->itemsByPage );
    $this->newsListPage = min( max(0, $this->newsListPage), $this->newsPages-1);
    $this->newsList = $this->newsItem->get_objectList(false,
						      $search,
						      $this->newsListPage*$this->itemsByPage,
						      $this->itemsByPage,
						      'ndate',
						      'desc');
    /* get comment count values */
    $comCount = $this->commentItem->count_newsCommentsByStatus(array_keys($this->newsList));
    foreach( $comCount as $newsid=>$coms ) {
      $this->newsList[$newsid]->vars['coms'] = $coms;
    }
    

    /* news links */
    $this->editNewsLink = $camyks->get_adminLink($this->name, array('mode'=>'editnews', 'news_id'=>''));
    $this->viewCommentsLink = $camyks->get_adminLink($this->name, array('mode'=>'viewcomments', 'news_id'=>''));
    /* delete news javascript */
    $this->add_JSScript('var deleteNewsMessage="'.utf8_encode(html_entity_decode($this->get_translation('news_deletemessage'))).'";');
    $this->add_JSScript('var deleteNewsLink="'.$camyks->get_adminJSLink($this->name, array('mode'=>'deletenews', 'news_id'=>'')).'";');    
    
    
    /* get buttons */
    $this->buttons = array(array('link'=>$camyks->get_adminLink(),
				 'title'=>$camyks->get_translation('back')));
    
    /* add configuration form */
    if ( $this->check_right(1) === true ) {
      $this->configForm = new HTMLForm('configForm',
				       $camyks->get_adminLink($this->name,
							      array('mode'=>'saveconfig')),
				       'POST');
    }
  }

  /*
   * initialise module object in admin/saveconfig mode
   * @return void
   * @access private
   */
  function init_admin_saveConfig() {
    global $camyks;
    /* check right */
    if ( $this->check_right(2) === false ) {
      return $this->init_admin_actionNotAllowed();
    }

    /* disable admin menu */
    $this->disable_adminEngineMenus();
    
    $this->config->get_fromHeader();
    if ($this->config->save()) {
      $this->text = $this->get_translation('message_saveconfig_done');
    } else {
      $this->text = $this->get_translation('message_saveconfig_failed');
    }
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect(4, $camyks->get_adminLink($this->name,
						  array('openTab'=>'configuration')));
  }

  /*
   * initialise module object in admin/editlink mode
   * @return void
   * @access private
   */
  function init_admin_editLink() {
    global $camyks;

    /* load link */
    $this->linkItem->id = isset($_REQUEST['link_id'])?$_REQUEST['link_id']:0;
    $this->linkItem->get();
    $this->linkItem->get_fromItems();

    /* check right */
    if ( $this->check_right(5)===false
	 and ($this->check_right(4)===false or $this->linkItem->vars['author']!=$camyks->adminUser->login )) {
      return $this->init_admin_actionNotAllowed();
    }

    /* build form */
    $this->form = new HTMLForm('editlink_form',
			       $camyks->get_adminLink($this->name,
						      array('mode'=>'savelink')),
			       'POST');
    $this->form->add_hidden('link_id', $this->linkItem->id);

    /* build buttons */
    $this->buttons = array(array('link'=>$camyks->get_adminLink($this->name, array('openTab'=>'links')),
				 'title'=>$camyks->get_translation('back')),
			   array('link'=>$this->form->get_HTMLSubmitLink(),
				 'title'=>$camyks->get_translation('valid')));
    /* update layout */
    $this->selected_layout = 'admin_editlink.html.inc';
  }

  /*
   * initialise module object in admin/saveLink mode
   * @return void
   * @access private
   */
  function init_admin_saveLink() {
    global $camyks;

    /* disable admin menu */
    $this->disable_adminEngineMenus();

    /* get link id */
    $linkItemID = isset($_REQUEST['link_id'])?$_REQUEST['link_id']:0;

    /* load link */
    $linkItem = new Admin_GenericBlogLinkItem( $linkItemID, $this );
    $linkItem->get();
    $linkItem->get_fromItems();

    /* check right */
    if ( $this->check_right(5)===false
	 and ($this->check_right(4)===false or $linkItem->vars['author']!=$camyks->adminUser->login )) {
      return $this->init_admin_actionNotAllowed();
    }
    
    /* get link data */
    $this->savingAllowed = true;
    $this->linkItem->id = $linkItemID;
    $this->linkItem->get_fromHeader();
    if ( $linkItemID == 0 ) {
      $this->linkItem->_libItems['author']->value = $camyks->adminUser->login; 
      $this->linkItem->_libItems['ndate']->value = mktime();
      /* check link count */
      if ( $this->linkItem->get_objectCount('author="'.$camyks->adminUser->login.'"') >= $this->config->vars['links_maxcount'] )
	$this->savingAllowed = false;
    } else {
      $this->linkItem->_libItems['author']->value = $linkItem->vars['author'];
      $this->linkItem->_libItems['ndate']->value = $linkItem->vars['ndate'];
    }
    
    if ($this->savingAllowed === false ) {
      $this->text = $this->get_translation('links_maxlinkcountreached');
      $this->text .= ' '.$this->get_translation('message_savelink_notdone');
    } else if ($this->linkItem->save()) {
      $this->text = $this->get_translation('message_savelink_done');
    } else {
      $this->text = $this->get_translation('message_savelink_failed');
    }
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect(4, $camyks->get_adminLink($this->name,
						  array('openTab'=>'links')));
  }

  /*
   * initialise module object in admin/deletelink mode
   * @return void
   * @access private
   */
  function init_admin_deleteLink() {
    global $camyks;

    /* disable admin menu */
    $this->disable_adminEngineMenus();

    /* load link */
    $this->linkItem->id = isset($_REQUEST['link_id'])?$_REQUEST['link_id']:0;
    $this->linkItem->get();
    $this->linkItem->get_fromItems();

    /* check right */
    if ( $this->check_right(5)===false
	 and ($this->check_right(4)===false or $this->linkItem->vars['author']!=$camyks->adminUser->login )) {
      return $this->init_admin_actionNotAllowed();
    }
    
    if ($this->linkItem->delete()) {
      $this->text = $this->get_translation('message_deletelink_done');
    } else {
      $this->text = $this->get_translation('message_deletelink_failed');
    }
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect(4, $camyks->get_adminLink($this->name,
						  array('openTab'=>'links')));
  }

  /*
   * initialise module object in admin/savetag mode
   * @return void
   * @access private
   */
  function init_admin_saveTag() {
    global $camyks;

    /* check right */
    if ( $this->check_right(8)===false and $this->check_right(9)===false ) {
      return $this->init_admin_actionNotAllowed();
    }

    /* disable admin menu */
    $this->disable_adminEngineMenus();

    /* check if tag is defined */
    if ( !isset($_REQUEST['tag']) or !isset($_REQUEST['tagvalue'])) {
      return $this->init_admin_main();
    }
    /* update tag */
    if ($this->tagItem->update_tagTitle($_REQUEST['tag'], 
					$_REQUEST['tagvalue'],
					$this->check_right(9))) {
      $this->text = $this->get_translation('message_savetag_done');
    } else {
      $this->text = $this->get_translation('message_savetag_failed');
    }
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect(4, $camyks->get_adminLink($this->name,
						  array('openTab'=>'tags')));
  }

  /*
   * initialise module object in admin/deletetag mode
   * @return void
   * @access private
   */
  function init_admin_deleteTag() {
    global $camyks;

    /* check right */
    if ( $this->check_right(8)===false and $this->check_right(9)===false ) {
      return $this->init_admin_actionNotAllowed();
    }

    /* disable admin menu */
    $this->disable_adminEngineMenus();

    /* check if tag is defined */
    if ( !isset($_REQUEST['tag'])) {
      return $this->init_admin_main();
    }
    /* delete tag */
    if ($this->tagItem->delete_tagTitle($_REQUEST['tag'], $this->check_right(9))) {
      $this->text = $this->get_translation('message_deletetag_done');
    } else {
      $this->text = $this->get_translation('message_deletetag_failed');
    }
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect(4, $camyks->get_adminLink($this->name,
						  array('openTab'=>'tags')));
  }

  /*
   * initialise module object in admin/editnews mode
   * @return void
   * @access private
   */
  function init_admin_editNews () {
    global $camyks;
    
    /* check dependencies */
    if ( $this->config->vars['news_editormode'] > 0 and 
	 !isset( $camyks->inputs['TinyMCEv3']) and 
	 !isset($camyks->inputs['TinyMCE']))  
      return $this->init_admin_missingPlugin('Input', 'TinyMCEv3');
    
    /* load news */
    $this->newsItem->id = isset($_REQUEST['news_id'])?$_REQUEST['news_id']:0;
    $this->newsItem->get();
    $this->newsItem->get_fromItems();

    /* check right */
    if ( $this->check_right(3)===false
	 and ($this->check_right(2)===false or $this->newsItem->vars['author']!=$camyks->adminUser->login )) {
      return $this->init_admin_actionNotAllowed();
    }

    /* get news item tag list */
    $this->newsItem->get_tagList();

    /* get full tag list */
    $this->tagList = $this->tagItem->get_titleList();
    
    /* get tab engine */
    $this->tabObject = 'gbm_tabObject';
    $this->add_JSEngineFile('object/ctab.js');
    $this->add_JSScript($this->tabObject.' = new CTab();');
    $this->add_JSScript($this->tabObject.'.init("properties", "'
      .$this->theme->parts['boxTabCSSStandart'].'","'
      .$this->theme->parts['boxTabCSSSelected'].'","'
      .$this->theme->parts['boxTabCSSRollover'].'");');

    $this->tabs = array(array('name'=>'properties',
			      'title'=>$this->get_translation('tabproperties')),
			array('name'=>'content',
			      'title'=>$this->get_translation('tabcontent')));

    /* build form */
    $this->form = new HTMLForm('editnews_form',
			       $camyks->get_adminLink($this->name,
						      array('mode'=>'savenews')),
			       'POST');
    $this->form->add_hidden('news_id', $this->newsItem->id);
    $this->form->add_hidden('tagCounter', count($this->newsItem->tagList));

    /* get tag engine */
    $this->add_JSEngineFile('tool/html.js');
    $this->add_JSFile('genericblogsnewseditor.js');
    $this->add_JSScript('genericblogsmanager_form="'.$this->form->name.'";');
    $this->add_JSScript('genericblogsmanager_minusImg="'.$this->theme->get_pictURL('minus', 12, 'std').'";');
    $this->add_JSLoadScript('genericblogsmanager_initialiseTagEngine();');


    /* get content editor */
    if ( $this->config->vars['news_editormode'] > 0 ) {
      $this->load_tinyMCEInput();
    }
    
    /* build buttons */
    $this->buttons = array(array('link'=>$camyks->get_adminLink($this->name, array('openTab'=>'news')),
				 'title'=>$camyks->get_translation('back')),
			   array('link'=>$this->form->get_HTMLSubmitLink(),
				 'title'=>$camyks->get_translation('valid')));
    /* update layout */
    $this->selected_layout = 'admin_editnews.html.inc';
  }

  /*
   * initialise module object in admin/saveNews mode
   * @return void
   * @access private
   */
  function init_admin_saveNews() {
    global $camyks;

    /* disable admin menu */
    $this->disable_adminEngineMenus();

    /* check news id */
    if ( !isset( $_REQUEST['news_id'] ) )
      $this->init_admin_main();
    $newsItemID = $_REQUEST['news_id'];

    /* load news */
    $newsItem = new Admin_GenericBlogNewsItem( $newsItemID, $this );
    $newsItem->get();
    $newsItem->get_fromItems();

    /* check right */
    if ( $this->check_right(3)===false
	 and ($this->check_right(2)===false or $newsItem->vars['author']!=$camyks->adminUser->login )) {
      return $this->init_admin_actionNotAllowed();
    }
    
    /* get news data */
    $this->newsItem->id = $newsItemID;
    $this->newsItem->get_fromHeader();
    if ( $newsItemID == 0 or $newsItem->vars['author'] == '' ) {
      $this->newsItem->_libItems['author']->value = $camyks->adminUser->login; 
    } else {
      $this->newsItem->_libItems['author']->value = $newsItem->vars['author'];
    }

    /* save news data */
    if ($this->newsItem->save()) {
      $this->text = $this->get_translation('message_savenews_done');
    } else {
      $this->text = $this->get_translation('message_savenews_failed');
    }
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect(4, $camyks->get_adminLink($this->name,
						  array('openTab'=>'news')));
  }

  /*
   * initialise module object in admin/deletenews mode
   * @return void
   * @access private
   */
  function init_admin_deleteNews() {
    global $camyks;

    /* disable admin menu */
    $this->disable_adminEngineMenus();

    /* load news */
    $this->newsItem->id = isset($_REQUEST['news_id'])?$_REQUEST['news_id']:0;
    $this->newsItem->get();
    $this->newsItem->get_fromItems();

    /* check right */
    if ( $this->check_right(3)===false
	 and ($this->check_right(2)===false or $this->newsItem->vars['author']!=$camyks->adminUser->login )) {
      return $this->init_admin_actionNotAllowed();
    }
    
    if ($this->commentItem->delete_newsComments($this->newsItem->id)
	and $this->tagItem->delete_newsTags($this->newsItem->id)
	and $this->newsItem->delete()) {
      $this->text = $this->get_translation('message_deletenews_done');
    } else {
      $this->text = $this->get_translation('message_deletenews_failed');
    }
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect(4, $camyks->get_adminLink($this->name,
						  array('openTab'=>'news')));
  }

  /*
   * initialise module object in admin/viewcomments mode
   * @return void
   * @access private
   */
  function init_admin_viewComments() {
    global $camyks;

    /* check news id */
    if ( !isset($_REQUEST['news_id']) )
      return $this->init_admin_main();

    /* load news item */
    $this->newsItem->id = $_REQUEST['news_id'];
    $this->newsItem->get();
    $this->newsItem->get_fromItems();

    /* check right */
    if ( $this->check_right(7)===false
	 and ($this->check_right(6)===false or $this->newsItem->vars['author']!=$camyks->adminUser->login )) {
      return $this->init_admin_actionNotAllowed();
    }

    /* load news comments */
    $this->newsItem->vars['coms'] = $this->commentItem->get_objectList(false, 'newsid='.$this->newsItem->id);
    
    /* constant vars */
    $this->commentStatusList = $this->commentItem->get_statusList();

    /* builds links */
    $this->editCommentLink = $camyks->get_adminLink($this->name,
						    array('mode'=>'editcomment',
							  'comment_id'=>''));
    /* update comment status scripts */
    $this->add_JSScript('var updateCommentStatusLink="'.$camyks->get_adminJSLink($this->name,
									     array('mode'=>'updatecommentstatus',
										   'comment_id'=>'')).'";');
    /* delete comment javascripts */
    $this->add_JSScript('var deleteCommentMessage="'.utf8_encode(html_entity_decode($this->get_translation('comment_deletemessage'))).'";');
    $this->add_JSScript('var deleteCommentLink="'.$camyks->get_adminJSLink($this->name,
									   array('mode'=>'deletecomment',
										 'comment_id'=>'')).'";');

    /* add javascript file */
    $this->add_JSFile('genericblogsviewcomments.js');
    
    /* add layout buttons */
    $this->buttons = array(array('link'=>$camyks->get_adminLink($this->name),
				 'title'=>$camyks->get_translation('back')));
    
    /* update layout */
    $this->selected_layout = 'admin_viewcomments.html.inc';
  }

  /*
   * initialise module object in admin/editcomment mode
   * @return void
   * @access private
   */
  function init_admin_editComment() {
    global $camyks;

    /* get header comment id value */
    if (!isset($_REQUEST['comment_id']))
      return $this->init_admin_main();

    /* load comment item */
    $this->commentItem->id = $_REQUEST['comment_id'];
    $this->commentItem->get();
    $this->commentItem->get_fromItems();

    /* load news */
    $this->newsItem->id = $this->commentItem->vars['newsid'];
    $this->newsItem->get();
    $this->newsItem->get_fromItems();

    /* check right */
    if ( $this->check_right(7)===false
	 and ($this->check_right(6)===false or $this->newsItem->vars['author']!=$camyks->adminUser->login )) {
      return $this->init_admin_actionNotAllowed();
    }

    /* get form */
    $this->form = new HTMLForm('editcomment',
			       $camyks->get_adminLink($this->name,
						      array('mode'=>'savecomment')),
			       'POST');
    $this->form->add_hidden('comment_id', $this->commentItem->id);


    /* get buttons */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link'=>$camyks->get_adminLink($this->name,
								array('mode'=>'viewcomments',
								      'news_id'=>$this->newsItem->id))),
			   array('title'=>$camyks->get_translation('valid'),
				 'link'=>$this->form->get_HTMLSubmitLink()));

    /* update layout */
    $this->selected_layout = 'admin_editcomment.html.inc';
  }

  /*
   * initalise module object in admin/savecomment mode
   * @return void
   * @access private
   */
  function init_admin_saveComment() {
    global $camyks;

    /* disable admin menu */
    $this->disable_adminEngineMenus();

    /* get header comment id value */
    if (!isset($_REQUEST['comment_id']))
      return $this->init_admin_main();

    /* load comment item */
    $commentItem = new Admin_GenericBlogCommentItem($_REQUEST['comment_id'], $this);
    $commentItem->get();
    $commentItem->get_fromItems();

    /* load news */
    $this->newsItem->id = $commentItem->vars['newsid'];
    $this->newsItem->get();
    $this->newsItem->get_fromItems();

    /* check right */
    if ( $this->check_right(7)===false
	 and ($this->check_right(6)===false or $this->newsItem->vars['author']!=$camyks->adminUser->login )) {
      return $this->init_admin_actionNotAllowed();
    }

    /* get comment data */
    $this->commentItem->id = $commentItem->id;
    $this->commentItem->get_fromHeader();
    $this->commentItem->_libItems['email']->value = $commentItem->vars['email'];
    $this->commentItem->_libItems['newsid']->value = $commentItem->vars['newsid'];
    $this->commentItem->_libItems['ndate']->value = $commentItem->vars['ndate'];
    $this->commentItem->_libItems['ipaddress']->value = $commentItem->vars['ipaddress'];

    /* save comment */
    if ($this->commentItem->save()) {
      $this->text = $this->get_translation('message_savecomment_done');
    } else {
      $this->text = $this->get_translation('message_savecomment_failed');
    }
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect(4, $camyks->get_adminLink($this->name,
						  array('mode'=>'viewcomments',
							'news_id'=>$this->newsItem->id)));
  }

  /*
   * initalise module object in admin/deletecomment mode
   * @return void
   * @access private
   */
  function init_admin_deleteComment() {
    global $camyks;

    /* disable admin menu */
    $this->disable_adminEngineMenus();

    /* get header comment id value */
    if (!isset($_REQUEST['comment_id']))
      return $this->init_admin_main();

    /* load comment item */
    $this->commentItem->id = $_REQUEST['comment_id'];
    $this->commentItem->get();
    $this->commentItem->get_fromItems();

    /* load news */
    $this->newsItem->id = $this->commentItem->vars['newsid'];
    $this->newsItem->get();
    $this->newsItem->get_fromItems();

    /* check right */
    if ( $this->check_right(7)===false
	 and ($this->check_right(6)===false or $this->newsItem->vars['author']!=$camyks->adminUser->login )) {
      return $this->init_admin_actionNotAllowed();
    }

    /* delete comment */
    if ($this->commentItem->delete()) {
      $this->text = $this->get_translation('message_deletecomment_done');
    } else {
      $this->text = $this->get_translation('message_deletecomment_failed');
    }
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect(4, $camyks->get_adminLink($this->name,
						  array('mode'=>'viewcomments',
							'news_id'=>$this->newsItem->id)));
  }

  /*
   * initalise module object in admin/updatecommentstatus mode
   * @return void
   * @access private
   */
  function init_admin_updateCommentStatus() {
    global $camyks;

    /* disable admin menu */
    $this->disable_adminEngineMenus();

    /* get header comment id value */
    if (!isset($_REQUEST['comment_id']) or !isset($_REQUEST['status']))
      return $this->init_admin_main();
    
    /* load comment item */
    $this->commentItem->id = $_REQUEST['comment_id'];
    $this->commentItem->get();
    $this->commentItem->get_fromItems();

    /* load news */
    $this->newsItem->id = $this->commentItem->vars['newsid'];
    $this->newsItem->get();
    $this->newsItem->get_fromItems();

    /* check right */
    if ( $this->check_right(7)===false
	 and ($this->check_right(6)===false or $this->newsItem->vars['author']!=$camyks->adminUser->login )) {
      return $this->init_admin_actionNotAllowed();
    }

    /* update status value */
    $this->commentItem->_libItems['status']->value = $_REQUEST['status'];

    /* update comment */
    if ($this->commentItem->save()) {
      $this->text = $this->get_translation('message_updatecomment_done');
    } else {
      $this->text = $this->get_translation('message_updatecomment_failed');
    }
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect(4, $camyks->get_adminLink($this->name,
						  array('mode'=>'viewcomments',
							'news_id'=>$this->newsItem->id)));
  }

  /* specific tool methods */
  
  /*
   * load tinyMCE input
   * @return void
   * @access private
   */
  function load_tinyMCEInput() {
    global $camyks;
    /* get input */
    if ( isset($camyks->inputs['TinyMCEv3'])) {
      $this->webEditor = &$camyks->inputs['TinyMCEv3'];
      $config_url = 'js/tinymcev3_mode';
    } else {
      $this->webEditor = &$camyks->inputs['TinyMCE'];
      $config_url = 'js/tinymce_mode';
    }
    
    /* update editor config */
    $this->webEditor->set_configInfos('file', $this->get_fileURL($config_url.$this->config->vars['news_editormode'].'.js'));
    $this->webEditor->load_themeCSSFile();
    /* load document folder case of mode */
    if( $this->config->vars['news_documentmode'] == 0 ) {
      $this->webEditor->load_fileManager();
    } else if ( $this->config->vars['news_documentmode'] == 1 ) {
      $this->webEditor->load_fileManager( $this->plugin_var_path.'/resource',
					  $this->plugin_var_url.'/resource',
					  $this->title );
    } else if ( $this->config->vars['news_documentmode'] == 2 ) {
      $this->webEditor->load_fileManager( $this->plugin_var_path.'/resource/'.$camyks->adminUser->login,
					  $this->plugin_var_url.'/resource/'.$camyks->adminUser->login,
					  $this->title );
    }
    $this->webEditor->load_pageChooser();
    $this->webEditor->set_contentInfos('text', $this->newsItem->vars['content'] );
    $this->webEditor->set_textareaInfos('content', '100%', '400px');
    $this->webEditor->initialise();
  }
}
?>