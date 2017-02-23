<?php
/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0b
 * Object Version       : 1.0
 * Object Type          : Plugin / Module Engine
 * Create Date		: Jul 2010
 * Last Modif Date	: Jul 2010
 * History
 * * 10-07-22 : Initial file 
 *
 * Content_TwitterStatusesViewer module :
 * Read Twitter account statuses and display them.
 */

class Content_TwitterStatusesViewer extends Module {
  /*
   * Constructor
   * @param string $path_type
   */
  function Content_TwitterStatusesViewer ( $path_type ) {
    parent::Module('Content_TwitterStatusesViewer', $path_type);
    /* set module type */
    $this->type = 'content';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Twitter';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    /* load plugin libraries */
    $this->libs[] = 'Content_TwitterStatusesViewerItem.php.inc';
    $this->get_PHPLibs();
    /* initialise plugin libraries */
    $this->configItem = new Content_TwitterStatusesViewerItem(0, $this);
  }
  
  /* overwrite Module methods */

  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install ( ) {
    return ($this->configItem->install() and parent::install());
  }

  /*
   * uninstall module
   * @return boolean success
   * @access private
   */  
  function uninstall ( ) {
    return ($this->configItem->uninstall() and parent::uninstall());
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

    /* save params */
    $this->params = $params;
   
    /* load viewer item */
    $this->configItem->id = $content;
    $this->configItem->get();
    $this->configItem->get_fromItems();
    $this->tweets = $this->configItem->load_statuses();

    /* unserialise XML */
    $this->tweets = xml_unserialize($this->tweets);

    /* check tweet count */
    if ( count($this->tweets['status']) == 0) {

      return;
    }

    /* load user data */
    $this->userData = $this->tweets['status'][0]['user'];

    /* add tweeter account styles */
    if ( $this->configItem->vars['style'] == 1) {
      $this->add_styleScript('.twitterBox'.$this->userData['id'].' {background:#'.$this->userData['profile_background_color'].';}');
      $this->add_styleScript('.twitterBox'.$this->userData['id'].' p {color:#'.$this->userData['profile_text_color'].';}');
      $this->add_styleScript('.twitterBox'.$this->userData['id'].' div {color:#'.$this->userData['profile_text_color'].';}');
      $this->add_styleScript('.twitterBox'.$this->userData['id'].' a {color:#'.$this->userData['profile_link_color'].';}');
    }



    /* update layout */
    $this->selected_layout = 'site_'.$this->configItem->vars['layout'].'.html.inc';
    
    /* parent site init */
    parent::init_site();
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

    
    /* get tabs */
    $this->tabBuilder = &$camyks->inputs['TabBuilder'];
    /* add definitions tab */
    $this->tabBuilder->add_tab(array('name'=>'properties',
				     'title'=>$this->get_translation('tabproperties')));
    /* add help tab */
    if ( $this->help != null )
      $this->tabBuilder(array('name'=>'help',
			      'title'=>$camyks->get_translation('help')));
    /* initialise tabs */
    $this->tabBuilder->initialise(array('default'=>'properties'));

    /* get form object */
    $this->form = new HTMLForm('editform',
			       $camyks->get_adminlink( $this->name, array('mode'=>'save')),
			       'POST');
    $this->form->set_object($this->configItem);
    $this->form->add_hidden('id', $this->configItem->id );
    $this->form->add_hidden('page_id', $this->page_id );
    $this->form->add_hidden('module_index', $this->module_index );

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
    $this->set_redirect(4, $camyks->get_adminLink($this->name,
						    array('mode'=>'edit',
							  'id'=>$this->configItem->id,
							  'page_id'=>$this->page_id,
							  'module_index'=>$this->module_index ) ) );
    /* layout */
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
  }

  /*
   * return layout list
   * @return array
   * @access public
   */
  function get_layoutList() {
    return array('nobox'=>$this->get_translation('layout_nobox'));
  }

  /*
   * return style values list
   * @return array
   * @access public
   */
  function get_styleList() {
    return array(0=>$this->get_translation('style_normal'),
		 1=>$this->get_translation('style_twitteraccount'));
  }

  /*
   * return style values list
   * @return array
   * @access public
   */
  function get_dateDisplayList() {
    return array(0=>$this->get_translation('datedisplay_relative'),
		 1=>$this->get_translation('datedisplay_absolutelight'),
		 2=>$this->get_translation('datedisplay_absolutefull'));
  }

  /* site tool methods */
  
  /*
   * return updated tweet text
   * @param string $text
   * @param array $params
   * @return void
   * @access private
   */
  function update_tweetText($text, $params=array()) {
    /* default params */
    $dParams = array('parse_links'=>true, 'link_class'=>'eLink1');
    $params = array_merge($dParams, $params);

    /* check for link */
    if ($params['parse_links'])
      $text = preg_replace('/(http:\/\/)([^\s]*)/', '<a href="\\1\\2" class="'.$params['link_class'].'" target="_blank">\\2</a>', $text);
    
    return $text;
  }

  /*
   * return formatted date
   * @param string $date
   * @return string
   * @access private
   */
  function display_tweetDate($date) {
    if (isset($this->configItem->vars))
      $mode = $this->configItem->vars['datedisplay'];
    else
      $mode = 1;
    $date = strtotime($date);

    switch ($mode) {
    case 0:
      $d = TODAY - $date;

      /* check for seconds */
      if ( $d < 60 )
	return $this->get_translation('tweetedsomesecondsago');

      /* check for minutes */
      $d = floor($d/60);
      if ( $d == 1 )
	return $this->get_translation('tweetedaminuteago');
      elseif ( $d < 90)
	return $this->get_translation('tweetedxminutesago', $d);

      /* check for hours */
      $d = floor($d/60);
      if ( $d == 1 )
	return $this->get_translation('tweetedanhourago');
      elseif ( $d < 72)
	return $this->get_translation('tweetedxhoursago', $d);

      /* check for days */
      $d = floor($d/24);
      if ( $d < 365 )
	return $this->get_translation('tweetedxdaysago', $d);

      /* check for years */
      $d  = floor($d/365);
      if ($d == 1)
	return $this->get_translation('tweetedayearago');
      return $this->get_translation('tweetedxyearsago', $d);

      break;
    case 2:
      return date_displayShortDateHour($date);
      break;
    case 1:
    default:
      if (date_isSameDay($date))
	return date_displayHour($date);
      return date_displayShortDate($date);
      break;
    } 
  }

  /*
   * return border color
   * @param string $default
   * @return string
   * @access private
   */
  function get_borderColor($default='888888') {
    if ($this->configItem->vars['style'] == 0)
      return $default;
    return $this->userData['profile_sidebar_border_color'];
  }
}
?>