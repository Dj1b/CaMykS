<?php
/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Module Engine
 * Create Date		: Apr 2008
 * Last Modif Date	: Jan 2010
 * History
 * * 08-03-13 : Initial file 
 * * 08-06-13 : Disable admin menu for data I/O modes
 * * 09-11-19 : Add social network input management
 * * 10-01-20 : Add page controller input management
 * * 10-01-20 : Add both input configuration
 *
 * Content_GenericBlogsViewer module :
 * Display Admin_GenericBlogsManager contents
 */

class Content_GenericBlogsViewer extends Module {
  /*
   * Constructor
   * @param string $path_type
   */
  function Content_GenericBlogsViewer ( $path_type ) {
    parent::Module('Content_GenericBlogsViewer', $path_type);
    /* set module type */
    $this->type = 'content';
    /* set plugin version */
    $this->version = '1.01';
    /* set plugin package */
    $this->plugin_package = 'Generic';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    /* load plugin libraries */
    $this->libs[] = 'Content_GenericBlogsViewerItem.php.inc';
    $this->get_PHPLibs();
    /* initialise plugin libraries */
    $this->configItem = new Content_GenericBlogsViewerItem( 0, $this );
  }
  
  /* overwrite Module methods */

  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install ( ) {
    if ( $this->configItem->install() )
      return parent::install();
    return false;
  }

  /*
   * uninstall module
   * @return boolean success
   * @access private
   */  
  function uninstall ( ) {
    return $this->configItem->uninstall();
  }
  
  /*
   * check module installation
   * @return boolean result
   * @access private
   */
  function is_installed () {
    return $this->configItem->is_installed();
  }
  
  /*
   * get available content ids as list
   * @return array
   * @access private
   */
  function get_contentList ( ) {
    return $this->configItem->get_namelist();
  }
 
  /*
   * update module
   * @return boolean success
   * @access private
   */
  function update($version, $more='') {
    global $camyks;
    
    /* check version 1.01 */
    if ( version_compare( $this->version, $version ) === 1  )
      if ( $this->configItem->update_toVersion1_01() === false )
	return false;
    
    /* generic update */
    return parent::update($version, $more);
  }
 
  /*
   * init module object in admin mode
   * @return void
   * @access private
   */
  function init_admin () {
    global $camyks;

    /* generic pre-initialisation */
    parent::preInit_admin();
 
    /* check right for this page */
    if ( $this->check_right( $this->page_id ) === false )
      return $this->init_admin_pageAccessDenied();

    /* get mode */
    $this->mode = isset ( $_REQUEST['mode'] ) ? $_REQUEST['mode'] : 'edit';

    /* initialise module with mode */
    switch ( $this->mode ) {
    case 'save' :
      /* mode == save */
      $this->init_admin_save();
    break;
    case 'edit' :
    default:
      /* mode == edit */
      $this->init_admin_edit();
      break;
    }
    /* generic module init */
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
   * init module object in site mode
   * @return void
   * @access private
   */
  function init_site ( $content=1, $params=array(), $mindex=null ) {
    global $camyks;

    /* add email management javascripts */
    $this->add_JSEngineFile('tool/mail.js');

    /* save params */
    $this->params = $params;

    /* load manager */
    $this->load_blogManager();

    /* load blog manager config */
    $this->manager->config->get();
    
    /* get authors list */
    $this->authorList = $camyks->modules['Admin_User']->get_userList(); 

    /* get news list to display */
    $this->configItem->id = $content;
    $this->configItem->get();
    $this->configItem->get_fromItems();

    /* initialise social network sharing panel  */
    if ($this->configItem->vars['snsp_status'] == 1
	and isset($camyks->inputs['SocialNetworksSharingPanel'])) {
      $this->networkInput = &$camyks->inputs['SocialNetworksSharingPanel'];
      $this->networkInput->initialise(array('text'=>$this->get_translation('site_shareon')));
    } else
      $this->networkInput = false;
    
    /* check for RSS Feed link */
    if ( $this->configItem->vars['enablerss'] == 1
	 and isset($camyks->inputs['GenericRSSFeed'])) {
      $st = $camyks->_conf['site_title'];
      if (count($this->configItem->vars['authors_']) == 0)
	$t = $this->get_translation('rss_title0', $st);
      elseif (count($this->configItem->vars['authors_']) == 1)
	$t = $this->get_translation('rss_title1', array($st, $this->configItem->vars['authors_']));
      else
	$t = $this->get_translation('rss_titlex', $st);
      
      $rssURL = $camyks->_conf['url'].'/request.php?module='.$this->name;
      $rssURL .= '&amp;blog='.$this->configItem->id;
      $rssURL .= '&amp;page='.$camyks->contentPage->name;
      $this->set_RSSFeed($rssURL, $t );
    }
    
    /* get mode to display */
    if ( isset ( $this->params['blogitem'] ) and $this->params['blogitem'] >= 0 )
      $this->init_site_item();
    else
      $this->init_site_list();
    
    /* parent site init */
    parent::init_site();
  }
  
  /*
   * display module object in site mode
   * @return void
   * @access private
   */
  function display_site () {
    parent::display_site();
  }
  
  /*
   * execute module object in request mode 
   * @return void
   * @access private
   */
  function execute_request() {
    global $camyks;

    /* check if newslist info is available */
    if ( !isset($_REQUEST['blog']))
      die();

    /* check page */
    if ( !isset($_REQUEST['page']))
      die();

    /* get database connection */
    $camyks->get_databaseConnection();
    $camyks->get_currentLanguage('site');

    /* load camyks content page module */
    $camyks->modules['Admin_ContentPage'] = module_get('Admin_ContentPage');

    /* get newslist item */
    $this->configItem->id = $_REQUEST['blog'];
    $this->configItem->get();
    $this->configItem->get_fromItems();

    /* check if RSS is enabled */
    if ( $this->configItem->vars['enablerss'] != 1 )
      die();

    /* get input */
    $rssInput = input_get('GenericRSSFeed');
    if ( $rssInput === false )
      die();

    $manager = module_get('Admin_GenericBlogsManager');
    if ( $manager === false )
      die();

    /* get items */
    $newsItems = $manager->newsItem->get_blogItemlist($this->configItem->vars['authors_'],
						      null,
						      0,
						      20,
						      true);
    /* build rss config */
    $config = array();

    /* build title & description */
    $st = string_html2text($camyks->_conf['site_title']);
    if (count($this->configItem->vars['authors_']) == 0)
      $t = $this->get_translation('rss_title0', $st);
    elseif (count($this->configItem->vars['authors_']) == 1)
      $t = $this->get_translation('rss_title1', array($st, $this->configItem->vars['authors_']));
    else
      $t = $this->get_translation('rss_titlex', $st);

    if ( $this->configItem->vars['title'] != '' ) {
      $config['title'] = $this->get_translation('rss_description', $this->configItem->vars['title']);
      $config['description'] = $t;
    } else {
      $config['title'] = $t;
      $config['description'] = '';
    }

    /* build link */
    $config['link'] = $camyks->_conf['url'].'/'.$camyks->get_siteLink($_REQUEST['page']);    

    /* build items list */
    $items = array();
    foreach ( $newsItems as $news ) {
      $item = array();
      $item['title'] = $news->vars['title'];
      $item['link'] = $camyks->_conf['url'].'/'.$camyks->get_siteLink($_REQUEST['page'], '', '', array('blogitem'=>$news->id));
      $item['description'] = $news->vars['content'];
      $item['date'] = $news->vars['ndate'];
      $item['isPermalink'] = 'true';
      $items[] = $item;
    }

    /* build RSS XML */
    $rssInput->initialise( $config, $items );
    $rssInput->display();
  }

  /* specific mode methods */

  /*
   * init module in admin / edit mode
   * @return void
   * @access private
   */
  function init_admin_edit ( ) {
    global $camyks;
    /* get object id */
    $id = isset ( $_REQUEST['id'] ) ? $_REQUEST['id'] : 0;

    /* get object data */
    $this->configItem->id = $id;
    $this->configItem->get();
    $this->configItem->get_fromItems();

    /* get authors list */
    $this->authorList = $camyks->modules['Admin_User']->get_userList(); 

    /* check for Inputs */
    $this->rssAvailable = isset( $camyks->inputs['GenericRSSFeed'] );
    $this->gpcAvailable = isset( $camyks->inputs['GenericPageController'] );
    $this->snspAvailable = isset( $camyks->inputs['SocialNetworksSharingPanel'] );

    /* get form object */
    $this->form = new HTMLForm ('blog_form',
				$camyks->get_adminlink( $this->name, array('mode'=>'save')),
				'POST');
    $this->form->set_object($this->configItem);
    $this->form->add_hidden('id', $this->configItem->id );
    $this->form->add_hidden('page_id', $this->page_id );
    $this->form->add_hidden('module_index', $this->module_index );
    $this->form->add_hidden('authorsCount', count($this->authorList));

    /* add form relative scripts */
    $this->add_JSScript('var genericblogsviewerform="'.$this->form->name.'";');
    $this->add_JSFile('genericblogsviewer.js');

    /* button interface */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link'=>$camyks->get_adminLink('Admin_ContentPage',
								array('mode'=>'modify',
								      'page_id'=> $this->page_id,
								      'openTab'=>'content'))),
			   array('title'=>$camyks->get_translation('valid'),
				 'link'=>$this->form->get_HTMLSubmitLink()));
  }

  /*
   * init module in admin / save mode
   * @return void
   * @access private
   */
  function init_admin_save ( ) {
    global $camyks;

    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* get object id */
    if ( !(isset($_REQUEST['id'] )))
      $this->init_admin_edit();
    $id = $_REQUEST['id'];

    /* save object */
    $this->configItem->id = $id;
    $this->configItem->get_fromHeader();
    if ( $this->configItem->save() ) {
      /* update page information with object id for new content */
      if ( $id == 0 and $this->page_id > 0 ) {
	ContentPage::static_update_singleModuleContent( $this->page_id, $this->module_index, $this->configItem->id );
      }
      $this->text = $this->get_translation('savedone');
    } else {
      $this->text = $this->get_translation('savefailed');
    }
    /* redirect save page */
    $this->set_redirect ( 4, $camyks->get_adminLink($this->name,
						    array('mode'=>'edit',
							  'id'=>$this->configItem->id,
							  'page_id'=>$this->page_id,
							  'module_index'=>$this->module_index ) ) );
    /* layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
  }


  /*
   * init module in site / list mode
   * @return void
   * @access private
   */
  function init_site_list( ) {
    global $camyks;

    $params = array();
    /* get news page to display */
    $params['pageCurrent'] = isset($this->params['blogpage'])?$this->params['blogpage']:0;

    /* get other search params */
    $pageParams = array();
    if ( isset($this->params['blogauthor']) and (count($this->configItem->vars['authors_'])==0 or in_array($this->params['blogauthor'], $this->configItem->vars['authors_']))) {
      $author = array($this->params['blogauthor']);
      $pageParams['blogauthor'] = $this->params['blogauthor'];
    } else {
      $author = $this->configItem->vars['authors_'];
    }
    if ( isset($this->params['blogtag']) and $this->params['blogtag']!='' ) {
      $tag = $this->params['blogtag'];
      $pageParams['blogtag'] = $this->params['blogtag'];
    } else {
      $tag = null;
    }

    /* get total item count */
    $this->blogItemCount = $this->manager->newsItem->get_blogItemCount($author,
								       $tag,
								       true);

    if($this->configItem->vars['gpc_status']==1 
       and isset($camyks->inputs['GenericPageController'])) {

      /* build controller params */
      $params['pageCount'] = ceil( $this->blogItemCount / $this->configItem->vars['list_count'] );
      $params['pageParams'] = array($camyks->contentPage->id,$camyks->current_language, $pageParams);
      $params['pageParam'] = 'blogpage';
      
      if ($params['pageCount'] > 0 and $params['pageCurrent'] >= $params['pageCount'])
	$params['pageCurrent'] = $params['pageCount']-1;
      if ($this->configItem->vars['gpc_source'] == 0) {
	$params['buttonSource'] = 'theme';
	$params['styleSource'] = 'theme';
      } else {
	$params['buttonSource'] = 'plugin';
	$params['styleSource'] = 'plugin';
      }

      /* load page controller */
      $this->pageController = &$camyks->inputs['GenericPageController'];
      $this->pageController->initialise($params);
    } else {
      $this->pageController = false;
      /* load internal controller */
      $this->build_listInternalButtonList($params['pageCurrent']);
    }

    /* get blog items to display */
    if ( $this->blogItemCount > 0 ) 
      $this->blogItems = $this->manager->newsItem->get_blogItemList($author,
								    $tag,
								    $params['pageCurrent'],
								    $this->configItem->vars['list_count'],
								    true);
    else 
      $this->blogItems = array();
        
    /* check tool panel display */
    if ( $this->configItem->vars['list_panel']==1 )
      $this->init_site_panel();
    
    /* set layout to display */
    $this->selected_layout = 'site_'.$this->configItem->vars['list_layout'].'.html.inc';
  }
  
  /*
   * init module object in site item mode
   * @return void
   * @access private
   */
  function init_site_item () {
    global $camyks;

    /* get news object */
    $this->blogItem = &$this->manager->newsItem;

    /* get news object data */
    $this->blogItem->id = $this->params['blogitem'];
    if ( $this->blogItem->get() === false 
	 or $this->blogItem->check_siteDisplay($this->configItem->vars['authors_'])===false)
      return $this->init_site_list();

    $this->blogItem->get_fromItems();
    $this->blogItem->get_tagList();

    /* update page title */
    $camyks->HTMLPage->page_title .= ' - '. $this->blogItem->vars['title'];

    /* check comment mode */
    $this->com_mode = isset($_REQUEST['com_mode'])?$_REQUEST['com_mode']:'form';
    $this->com_error = '';
    $this->commentItem = &$this->manager->commentItem;
    
    /* execute comment actions */
    if ( $this->com_mode == 'form' ) {
      $this->init_site_item_comment_form();
    } else if ( $this->com_mode == 'save' ) {
      $this->init_site_item_comment_save();
    } else {
      /* nothing to do */
    }
    $this->commentItem->get_fromItems();
    $this->blogItem->get_blogComments();

    /* buttons list */
    $this->buttons = array(array('title' => $this->get_translation('site_back'),
				 'link' =>  $camyks->get_siteLink( $camyks->contentPage->id,
								   $camyks->contentPage->name)));
    
    /* check tool panel display */
    if ( $this->configItem->vars['item_panel'] == 1 )
      $this->init_site_panel();
    
    /* set layout to display */
    $this->selected_layout = 'site_'.$this->configItem->vars['item_layout'].'.html.inc';
  }
  
  /* specific tool methods in admin mode */

  /*
   * init tool panel in site mode
   * @return void
   * @access private
   */
  function init_site_panel() {
    global $camyks;

    /* get author list including news count */
    $this->panel_authors = $this->manager->newsItem->get_newsCountByAuthor($this->configItem->vars['authors_'], true);

    /* get tag list includin news count */
    $this->panel_tags = $this->manager->newsItem->get_newsCountByTag($this->configItem->vars['authors_'], true);

    /* get link list */
    $this->panel_links = $this->manager->linkItem->get_linkListByAuthor($this->configItem->vars['authors_'], true); 
  }

  /*
   * init module object in site item/comment form mode
   * @return void
   * @access private
   */
  function init_site_item_comment_form() {
    global $camyks;
    $camyks->set_sessionValue('blogcommentpost', 0);
    $this->com_form = new HTMLForm('com_form',
				   $camyks->get_siteCurrentLink(),
				   'POST');
    $this->com_form->add_hidden('com_mode', 'save');
  }

  /*
   * init module object in site item/comment save mode
   * @return void
   * @access private
   */
  function init_site_item_comment_save() {
    global $camyks;

    /* check "reload action" */
    if ($camyks->get_sessionValue('blogcommentpost', 1)==1 )
      return;

    /* update reload action session value */
    $camyks->set_sessionValue('blogcommentpost', 1);

    /* get comment */
    $this->commentItem->get_fromHeader();
    
    /* complete data */
    $this->commentItem->_libItems['status']->value = $this->manager->config->vars['comments_validationmode'];
    $this->commentItem->_libItems['newsid']->value = $this->params['blogitem'];
    $this->commentItem->_libItems['ndate']->value = mktime();
    $this->commentItem->_libItems['ipaddress']->value = client_getIp();
    
    /* save comment */
    if ( $this->commentItem->save() == false ) {
      $this->com_mode = 'form';
      $this->com_error = $this->commentItem->_libError;
      return $this->init_site_item_comment_form();
    }
  } 

  /*
   * return list layouts list
   * @return array
   * @access public
   */
  function get_listLayouts() {
    return array('list_box'=>$this->get_translation('layout_list_box'));
  }

  /*
   * return item layouts list
   * @return array
   * @access public
   */
  function get_itemLayouts() {
    return array('item_box'=>$this->get_translation('layout_item_box'));
  }


  /* specific tool methods in site mode */

  /*
   * load blog manager module
   * @return void
   * @access private
   */
  function load_blogManager() {
    global $camyks; 
    /* load blog manager */
    if ( !isset($camyks->modules['Admin_GenericBlogsManager'] ) )
      /* to do */
      die();
    $this->manager = $camyks->modules['Admin_GenericBlogsManager'];
  }
  
  /*
   * return blog news content display
   * @param string $content
   * @return string
   * @access private
   */
  function get_blogNewsContentDisplay( $content ) {
    global $camyks;

    /* check manager config */
    switch( $this->manager->config->vars['news_editormode'] ) {
    case 0 :
      return '<p class="eContent1">'.nl2br( $content ).'</p>';
    case 1 :
      return '<p class="eContent1">'.$content.'</p>';
    default:
      return $content;
    }
  }

  /*
   * return blog news author display
   * @param string $author
   * @param string $css
   * @return string
   * @access private
   */
  function get_blogNewsAuthorDisplay( $author, $css='' ) {
    global $camyks;

    /* check given author into author list */
    if (!isset($this->authorList[$author])) {
      return $author;
    }

    /* build author name */
    if ($this->authorList[$author]['firstname']!='' and
	$this->authorList[$author]['lastname']!='')
      $name = $this->authorList[$author]['firstname'].' '.$this->authorList[$author]['lastname'];
    else if ($this->authorList[$author]['firstname']!='')
      $name = $this->authorList[$author]['firstname'];
    else if ($this->authorList[$author]['lastname']!='')
      $name = $this->authorList[$author]['lastname'];
    else
      $name = $author;

    /* build result link */
    $a = '<a ';
    if ($css!='')
      $a .= 'class="'.$css.'" ';
    $a.= 'href="'.$camyks->get_siteLink($camyks->contentPage->id,
					$camyks->contentPage->name,
					'',
					array('blogauthor'=>$author));
    $a.= '">'.$name.'</a>';
    return $a;
  }

  /*
   * return blog news tag list display
   * @param array $tags
   * @param string $css
   * @return string
   * @access private
   */
  function get_blogNewsTagsDisplay($tags, $css='') {
    global $camyks;

    /* check tags */
    if ( count($tags) == 0 )
      return '';

    /* check css value */
    if ( $css!='' )
      $css = 'class="'.$css.'" ';

    /* build tags */
    $tags_ = array();
    foreach($tags as $tag) {
      $t= '<a '.$css.'href="'.$camyks->get_siteLink($camyks->contentPage->id,
						    $camyks->contentPage->name,
						    '',
						    array('blogtag'=>$tag->vars['name']));
      $t.='">'.$tag->vars['title'].'</a>';
      $tags_[] = $t;
    }
    /* return formatted tag list */
    return implode(', ', $tags_);
  }

  /*
   * return blog news comments link display
   * @param integer $blogitem
   * @param integer $comments
   * @param string $css
   * @return string
   * @access private
   */
  function get_blogNewsCommentsDisplay($blogitem, $comments, $css='') {
    global $camyks;
   
    /* check comment count */
    if ( $comments == 0 ) {
      $text = $this->get_translation('site_nocomment');
    } else if ( $comments == 1 ) {
      $text = $this->get_translation('site_1comment');
    } else {
      $text = $this->get_translation('site_xcomments', $comments);
    }

    /* build comments link */
    $a = '<a ';
    if ( $css!='' )
      $a .= 'class="'.$css.'" ';
    $a.= 'href="'.$this->get_singleNewsLink($blogitem).'#comments"';
    $a.='>'.$text.'</a>';

    /* return built link */
    return $a;
  }

  /*
   * build site single item link
   * @param integer $newsid
   * @return string;
   * @access public
   */
  function get_singleNewsLink ( $newsid ) {
    global $camyks;
    return $camyks->get_confValue('url').'/'
      .$camyks->get_siteLink($camyks->contentPage->id,
			     $camyks->contentPage->name,
			     '',
			     array('blogitem'=>$newsid));
  }

  /*
   * return last news from selected blog
   * @params integer $blogid
   * @params integer $count
   * @return array
   * @access private
   */
  function get_lastNewsList( $blogid, $count=null) {
    global $camyks;

    /* load blog manager */
    if ( !isset($camyks->modules['Admin_GenericBlogsManager'] ) )
      return array();
    $this->manager = $camyks->modules['Admin_GenericBlogsManager'];

    /* load viewer object */
    $this->configItem->id = $blogid;
    if ( $this->configItem->get() === false )
      return array();
    $this->configItem->get_fromItems();

    if (!isset($count))
      $count = $this->configItem->vars['list_count'];
    
    /* return news list */
    return $this->manager->newsItem->get_blogItemlist($this->configItem->vars['authors_'],
						      null,
						      0,
						      $count,
						      true);
  }

  /*
   * build list internal button list
   * @param integer $page
   * @return void
   * @access private
   */
  function build_listInternalButtonList($page) {
    global $camyks;
    
    /* check if link building is requiered */
    if ( $this->blogItemCount <= $this->configItem->vars['list_count'] )
      return;

    /* build previous page button */
    if ( ($page+1)*$this->configItem->vars['list_count'] < $this->blogItemCount)
      $this->blogPrevPage = $camyks->get_siteLink( $camyks->contentPage->id,
						   $camyks->contentPage->name,
						   '',
						   array_merge($this->params, array('blogpage'=> $page+1)));
    else 
      $this->blogPrevPage = '';
    
    /* build next page button */
    if ( $page > 0 )
      $this->blogNextPage = $camyks->get_siteLink( $camyks->contentPage->id,
						   $camyks->contentPage->name,
						   '',
						   array_merge($this->params, array('blogpage'=> $page-1)));
    else 
      $this->blogNextPage = '';
    
    /* build buttons list */
    $this->buttons = array(array('title' => $this->get_translation('site_previouspage'),
				 'link' => $this->blogPrevPage ),
			   array('title' => $this->get_translation('site_currentpage', array($page+1)),
				 'link' => '' ),
			   array('title' => $this->get_translation('site_nextpage'),
				 'link' => $this->blogNextPage ));
  }

  /*
   * return generic status list
   * @return array
   * @access private
   */
  function get_genericStatusList() {
    return array(0=>$this->get_translation('status_disabled'),
		 1=>$this->get_translation('status_enabled'));
  }

  /*
   * return GPC source list
   * @return array
   * @access private
   */
  function get_gpcSourceList() {
    global $camyks;
    return array(0=>$camyks->get_translation('theme'),
		 1=>$this->get_translation('gpc_name'));
  }
}
?>