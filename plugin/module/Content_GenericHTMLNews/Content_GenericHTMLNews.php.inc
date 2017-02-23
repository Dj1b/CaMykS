<?php
/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a2
 * Object Version       : 1.0
 * Object Type          : Plugin / Module Engine
 * Create Date		: Dec 2007
 * Last Modif Date	: Apr 2009
 * History
 * * 07-12-15 : Initial file 
 * * 08-01-08 : Add new display layouts
 * * 08-05-18 : Update admin list layout
 * * 08-06-13 : Disable admin menu for data I/O modes
 * * 08-07-22 : Add support of TinyMCE version 3
 *
 * Content_GenericHTMLNews module :
 * Display HTML News
 */

class Content_GenericHTMLNews extends Module {
  /* variables */
  var $layouts_list;
  var $layouts_item;
  var $titles_modes;
  var $newspage;
  var $newsbypage;
  var $status;

  /*
   * constructor
   * @param string $path_type
   */
  function Content_GenericHTMLNews ( $path_type ) {
    parent::Module('Content_GenericHTMLNews', $path_type);
    /* set module type */
    $this->type = 'content';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Generic';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    /* load plugin libraries */
    $this->libs[] = 'Content_GenericHTMLNewsList.php.inc';
    $this->libs[] = 'Content_GenericHTMLNewsItem.php.inc';
    $this->get_PHPLibs();
    /* initialise plugin variables */
    $this->layouts_list = array('list_box_complete',
				'list_box_summary',
				'list_box_title',
				'list_free_complete',
				'list_free_summary',
				'list_free_title',
				'list_custom');
    $this->layouts_item = array('item_box_complete',
				'item_free_complete',
				'item_custom');
    $this->newsbypage = 16;
    $this->status = array(0 => 'inedition',
			  1 => 'inline' );
    /* initialise plugin libraries */
    $this->newslist = new Content_GenericHTMLNewsList( 0, $this );
    $this->newsitem = new Content_GenericHTMLNewsItem( 0, $this );
  }
  
  /* overwrite Module methods */

  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install ( ) {
    if ( $this->newslist->install() and $this->newsitem->install() )
      return parent::install();
    return false;
  }

  /*
   * uninstall module
   * @return boolean success
   * @access private
   */  
  function uninstall ( ) {
    return $this->newsitem->uninstall() and $this->newslist->uninstall();
  }
  
  /*
   * check module installation
   * @return boolean success
   * @access private
   */
  function is_installed () {
    return $this->newsitem->is_installed();
  }
  
  /*
   * get available content ids as list
   * @return array
   * @access public
   */
  function get_contentList ( ) {
    return $this->newslist->get_namelist();
  }
  
  /*
   * init module in admin mode
   * @return void
   * @access priavte
   */
  function init_admin () {
    global $camyks;

    /* generic module pre-init */
    parent::preinit_admin();

    /* check right for this page */
    if ( $this->check_right( $this->page_id ) === false )
      return $this->init_admin_pageAccessDenied();
    
    /* check dependencies */
    if(!isset($camyks->inputs['TabBuilder']))
      return $this->init_admin_missingPlugin('Input', 'TabBuilder');
    if (!isset($camyks->inputs['AdminItemListViewer']))
      return $this->init_admin_missingPlugin('Input', 'AdminItemListViewer');
    if (!isset($camyks->inputs['TinyMCEv3']) and !isset($camyks->inputs['TinyMCE']))
      return $this->init_admin_missingPlugin('Input', 'TinyMCEv3');
    
    /* get mode */
    $this->mode = isset ($_REQUEST['mode'])?$_REQUEST['mode'] : 'view_list';
    
    /* initialise module with mode */
    switch ( $this->mode ) {
    case 'edit_item' :
      /* mode == edit_item */
      $this->init_admin_edit_item();
      break;
    case 'save_item' :
      /* mode == save_item */
      $this->init_admin_save_item();
      break;
    case 'delete_item' :
      /* mode == delete_item */
      $this->init_admin_delete_item();
      break;
    case 'edit_list': 
      /* mode == edit_list */
      $this->init_admin_edit_list();
      break;
    case 'save_list' :
      /* mode == save_list */
      $this->init_admin_save_list();
      break;
    case 'view_list' :
    default:
      /* mode == view_list */
      $this->init_admin_view_list();
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
   * @param integer $content
   * @param array $params
   * @return void
   * @access private
   */
  function init_site ( $content=1, $params=array(), $mindex=null ) {
    global $camyks;
    
    /* add module css styles */
    $this->add_styleFile('generichtmlnews.css');

    /* add email management javascripts */
    $this->add_JSEngineFile('tool/mail.js');
    
    /* get news list to display */
    $this->newslist->id = $content;
    $this->newslist->get();
    $this->newslist->get_fromItems();

    /* add social network sharing tools */
    $this->add_JSExternFile('http://static.ak.fbcdn.net/connect.php/js/FB.Share');

    if ( isset ( $params['newsitem'] ) and $params['newsitem'] >= 0 ) {
      /* get single item init */
      $this->init_site_item ( $params );
    } else {
      /* get news list init */
      $this->init_site_list( $params );
    }
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
    if ( !isset($_REQUEST['newslist']))
      die();

    /* check language */
    if ( !isset($_REQUEST['_clg_']))
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
    $this->newslist->id = $_REQUEST['newslist'];
    $this->newslist->get();
    $this->newslist->get_fromItems();

    /* check if RSS is enabled */
    if ( $this->newslist->vars['enablerss'] != 1 )
      die();

    /* get input */
    $rssInput = input_get( 'GenericRSSFeed' );

    if ( $rssInput === false )
      die();

    /* get items */
    $newsitems = $this->newsitem->get_lastItemsList( $this->newslist->id, $camyks->current_language, $count);
    
    /* build rss config */
    $config = array();
    $config['title'] = $this->get_translation('rss_title');
    $config['link'] = $camyks->_conf['url'].'/'.$camyks->get_siteLink($_REQUEST['page'], '', $camyks->current_language);
    $config['description'] = $this->get_translation('rss_description', $camyks->_conf['site_title']);
    $config['language'] = $camyks->current_language;

    /* build items list */
    $items = array();
    foreach ( $newsitems as $news ) {
      $item = array();
      $item['title'] = $news->vars['title'];
      $item['link'] = $camyks->_conf['url'].'/'.$camyks->get_siteLink($_REQUEST['page'], '', $camyks->current_language, array('newsitem'=>$news->id));
      $item['description'] = $news->vars['summary'];
      $item['isPermalink'] = 'true';
      $item['date'] = $news->vars['ndate'];
      $items[] = $item;
    }

    /* build RSS XML */
    $rssInput->initialise( $config, $items );
    $rssInput->display();
  }
  
  /* specific admin modes methods */

  /*
   * init module in admin / view_list mode
   * @return void
   * @access private
   */
  function init_admin_view_list ( ) {
    global $camyks;

    /* get object id */
    if ($this->id == 0)
      return $this->init_admin_edit_list();

    /* get object data */
    $this->newslist->id = $this->id;
    $this->newslist->get();
    $this->newslist->get_fromItems();
    if ($this->newslist->id == 0)
      return $this->init_admin_edit_list();

    /* build tabs */
    $this->tabBuilder = &$camyks->inputs['TabBuilder'];
    $this->tabBuilder->add_tabs(array(array('name'=>'properties',
					    'title'=>$this->get_translation('tabproperties')),
				      array('name'=>'newsitems',
					    'title'=>$this->get_translation('tabnewsitems'))));
    $this->tabBuilder->initialise(array('default'=>'newsitems'));

    /* build news list */
    $this->load_file('lib/Content_GenericHTMLNewsListParams.php.inc');
    $this->listObject = &$camyks->inputs['AdminItemListViewer'];
    $this->listObject->set_params($this->newsListParams);
    $this->listObject->initialise();

    /* check for RSS Input */
    $this->rssAvailable = isset( $camyks->inputs['GenericRSSFeed'] );

    /* get buttons */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link'=>$camyks->get_adminLink('Admin_ContentPage',
								array('mode'=>'modify',
								      'page_id'=> $this->page_id,
								      'openTab'=>'content'))));
    /* update layout */
    $this->selected_layout = 'admin_view_list.html.inc';
  }
  
  /*
   * init module in admin / edit_list mode
   * @return void
   * @access private
   */
  function init_admin_edit_list ( ) {
    global $camyks;
    
    /* get object data */
    $this->newslist->id = $this->id;
    $this->newslist->get();
    $this->newslist->get_fromItems();
    /* check for RSS Input */
    $this->rssAvailable = isset( $camyks->inputs['GenericRSSFeed'] );
    
    /* get form object */
    $this->form = new HTMLForm ('newslist_form',
				$camyks->get_adminlink( $this->name, array('mode'=>'save_list')),
				'POST');
    $this->form->add_hidden('id', $this->newslist->id );
    $this->form->add_hidden('page_id', $this->page_id );
    $this->form->add_hidden('module_index', $this->module_index );

    if ($this->id == 0) 
      $link = $camyks->get_adminLink('Admin_ContentPage',
				     array('mode'=>'modify',
					   'page_id'=> $this->page_id,
					   'openTab'=>'content'));
    else
      $link = $this->get_adminLink();
    
    /* button interface */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link'=> $link),
			   array('title'=>$camyks->get_translation('valid'),
				 'link'=>$this->form->get_HTMLSubmitLink()));
    
    
    /* update layout */
    $this->selected_layout = 'admin_edit_list.html.inc';
  }
  
  /*
   * init module in admin / save_list mode
   * @return void
   * @access private
   */
  function init_admin_save_list ( ) {
    global $camyks;

    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* save object */
    $this->newslist->id = $this->id;
    $this->newslist->get_fromHeader();
    if ( $this->newslist->save() ) {
      /* update page information with object id for new content */
      if ( $this->id == 0 and $this->page_id > 0 ) {
	ContentPage::static_update_singleModuleContent( $this->page_id, $this->module_index, $this->newslist->id );
	$this->id = $this->newslist->id;
      }
      $this->text = $this->get_translation('newslistsaved');
    } else {
      $this->text = $this->get_translation('newslistnotsaved');
    }

    /* redirect save page */
    $this->set_redirect ( $camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink());

    /* layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
  }
  
  /*
   * init module in admin / save_item mode
   * @return void
   * @access private
   */
  function init_admin_save_item ( ) {
    global $camyks;

    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* get object id */
    $id = isset ( $_REQUEST['news_id'] ) ? $_REQUEST['news_id'] : 0;

    /* save object */
    $this->newsitem->id = $id;
    $this->newsitem->get_fromHeader();
    if ( $this->newsitem->save() ) {
      $this->newsitem->get_fromItems();
      /* redirect save page */
      $this->text = $this->get_translation('newsitemsaved');
    } else {
      $this->text = $this->get_translation('newsitemnotsaved');
    }

    /* layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink());
  }
  
  /*
   * init module in admin / edit_item mode
   * @return void
   * @access private
   */
  function init_admin_edit_item ( ) {
    global $camyks;

    /* get object id */
    $id = isset ( $_REQUEST['news_id'] ) ? $_REQUEST['news_id'] : 0;

    /* get object data */
    $this->newsitem->id = $id;
    $this->newsitem->get();
    $this->newsitem->get_fromItems();
    
    if ( $this->newsitem->id == 0 ) {
      $this->newsitem->vars['listid'] = $this->id;
    }
    
    /* get form object */
    $this->form = new HTMLForm ( 'newsitem_form',
				 $camyks->get_adminlink( $this->name, array('mode'=>'save_item')),
				 'POST');
    $this->form->set_object($this->newsitem);
    $this->form->add_hidden('id', $this->newsitem->vars['listid'] );
    $this->form->add_hidden('news_id', $this->newsitem->id );
    $this->form->add_hidden('listid', $this->newsitem->vars['listid'] );
    $this->form->add_hidden('author', $this->newsitem->vars['author'] );
    $this->form->add_hidden('page_id', $this->page_id );
    $this->form->add_hidden('module_index', $this->module_index );
    
    /* build tabs */
    $this->tabBuilder = &$camyks->inputs['TabBuilder'];
    $this->tabBuilder->add_tabs(array(array('name'=>'properties',
					    'title'=>$this->get_translation('tabproperties')),
				      array('name'=>'content',
					    'title'=>$this->get_translation('tabcontent'))));
    $this->tabBuilder->initialise(array('default'=>'newsitems'));
    
    /* get HTML Editor with default config */
    if( isset($camyks->inputs['TinyMCEv3'])) {
      $this->input = &$camyks->inputs['TinyMCEv3'];
    } elseif( isset($camyks->inputs['TinyMCE'])) {
      $this->input = &$camyks->inputs['TinyMCE'];
      $this->input->set_configInfos('default');
    }
    $this->input->set_contentInfos('file', $this->newsitem->vars['content'] );
    $this->input->set_textareaInfos('content', '100%', '400px');
    $this->input->initialise();
    
    /* get buttons */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
				 'link'=>$this->get_adminLink()),
			   array('title'=>$camyks->get_translation('valid'),
				 'link'=>$this->form->get_HTMLSubmitLink()));
    
    /* layout */
    $this->selected_layout = 'admin_edit_item.html.inc';
  }
  
  /*
   * init module in admin / delete_item mode
   * @return void
   * @access private
   */
  function init_admin_delete_item( ) {
    global $camyks;

    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* get object id */
    $id = isset ( $_REQUEST['news_id'] ) ? $_REQUEST['news_id'] : 0;

    /* save object */
    $this->newsitem->id = $id;
    $this->newsitem->get();
    $this->newsitem->get_fromItems();
    if ( $this->newsitem->vars['listid']==$this->id and $this->newsitem->delete()){
      $this->text = $this->get_translation('newsitemdeleted');
    } else {
      $this->text = $this->get_translation('newsitemnotdeleted');
    }

    /* layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink());
  }

  /* specific site mode methods */

  /*
   * init module object in site / list mode 
   * @param array $params
   * @return void
   * @access private
   */
  function init_site_list ( $params ) {
    global $camyks;

    /* get news page to display */
    if ( isset ( $params['newspage'] ) and $params['newspage'] >= 0 ) {
      $this->newspage = $params['newspage'];
    } else {
      $this->newspage = 0;
    }

    /* get news items to display from news list */
    $this->newsitems = $this->newsitem->get_siteList( $this->newslist->id,
						      $this->newspage,
						      $this->newslist->vars['count_list']);

    $this->newscount = $this->newsitem->get_listcount( $this->newslist->id,
						       1,
						       $camyks->current_language,
						       true);
    /* get buttons list */
    if ( $this->newscount > $this->newslist->vars['count_list'] ) {
      if ( ($this->newspage+1)*$this->newslist->vars['count_list'] < $this->newscount)
	$this->nextnews = $camyks->get_siteLink( $camyks->contentPage->id,
						 $camyks->contentPage->name,
						 '',
						 array('newspage'=> $this->newspage+1));
      else 
	$this->nextnews = '';
      
      if ( $this->newspage > 0 )
	$this->prevnews = $camyks->get_siteLink( $camyks->contentPage->id,
						 $camyks->contentPage->name,
						 '',
						 array('newspage'=> $this->newspage-1));
      else 
	$this->prevnews = '';
      
      /* build buttons list */
      $this->buttons = array(array('title' => $this->get_translation('previousnews'),
				   'link' => $this->prevnews ),
			     array('title' => $this->get_translation('page', array( $this->newspage+1 )),
				   'link' => '' ),
			     array('title' => $this->get_translation('nextnews'),
				   'link' => $this->nextnews ));
    }
    
    /* check for RSS Feed link */
    if ( isset( $camyks->inputs['GenericRSSFeed'] ) and ( $this->newslist->vars['enablerss'] == 1 ) ){
      $rssURL = $camyks->_conf['url'].'/request.php?module='.$this->name;
      $rssURL .= '&amp;newslist='.$this->newslist->id;
      $rssURL .= '&amp;_clg_='.$camyks->current_language;
      $rssURL .= '&amp;page='.$camyks->contentPage->name;
      $this->set_RSSFeed($rssURL, $this->get_translation('rss_title') );
    }

    /* set layout to display */
    $this->selected_layout = 'site_'.$this->newslist->vars['layout_list'].'.html.inc';
  }
  
  /*
   * init module object in site / item mode
   * @param array $params
   * @return void
   * @access private
   */
  function init_site_item ( $params ) {
    global $camyks;
    
    /* get news item object */
    $this->newsitem->id = $params['newsitem'];
    if ( $this->newsitem->get()===false )
      return $this->init_site_list($params);
    $this->newsitem->get_fromItems();

    /* update page title */
    $camyks->HTMLPage->page_title .= ' - '. $this->newsitem->vars['title'];
    
    /* check if object is valid */
    if ( ( $this->newsitem->vars['language'] != $camyks->current_language )
	 or ( $this->newsitem->vars['status'] == 0 ) 
	 or ( $this->newsitem->vars['listid'] != $this->newslist->id ) )
      return $this->init_site_list($params);
    /* buttons list */
    $this->buttons = array(array('title' => $this->get_translation('back'),
				 'link' =>  $camyks->get_siteLink( $camyks->contentPage->id,
								   $camyks->contentPage->name)));
    
    /* set layout to display */
    $this->selected_layout = 'site_'.$this->newslist->vars['layout_item'].'.html.inc';
  }

  /* specific admin tool methods */

  /*
   * return list layout values
   * @return array
   * @access private
   */
  function get_listLayoutList() {
    $list = array();
    foreach($this->layouts_list as $l)
      $list[$l] = $this->get_translation($l);
    return $list;
  }

  /*
   * return news layout values
   * @return array
   * @access private
   */
  function get_newsLayoutList() {
    $list = array();
    foreach($this->layouts_item as $l)
      $list[$l] = $this->get_translation($l);
    return $list;
  }

  /*
   * return news status values
   * @return array
   * @access private
   */
  function get_newsStatusList() {
    $list = array();
    foreach($this->status as $s => $n) {
      $list[$s] = $this->get_translation($n);
    }
    return $list;
  }

  /*
   * return news language values
   * @return array
   * @access private
   */
  function get_newsLanguageList() {
    global $camyks;
    $list = array();
    foreach($camyks->_conf['editing_languages'] as $l)
      $list[$l] = $camyks->get_translation('lang_'.$l);
    return $list;
  }

  /* specific site tool methods */

  /*
   * get current page single news link
   * @param integer $id
   * @return string
   * @access private
   */
  function get_singlenewslink ( $id ) {
    global $camyks;
    return $camyks->get_confValue('url').'/' 
      .$camyks->get_siteLink ($camyks->contentPage->id,
			      $camyks->contentPage->name,
			      '',
			      array('newsitem'=>$id));
  }

  /*
   * return last news
   * @param integer $listid
   * @param integer $count
   * @return array
   * @access public
   */
  function get_lastNewsList( $listid, $count=null ) {
    global $camyks;
    
    /* get newslist item */
    $this->newslist->id = $listid;
    if ( $this->newslist->get() === false )
      return array();
    $this->newslist->get_fromItems();
    
    /* check count value */
    if ( !isset($count))
      $count = $this->newslist->vars['count_list'];
    
    /* get items */
    return $this->newsitem->get_lastItemsList( $this->newslist->id, $camyks->current_language, $count);
  }
}
?>