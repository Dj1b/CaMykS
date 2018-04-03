<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Engine
 * Creation Date    : May 2008
 * Last Modif Date	: Mar 2018
 * 
 * Content_GenericHTMLContent
 * Display HTML content, use TinyMCE input
 */

final class Content_GenericHTMLContent extends Module {
  /* variables */
  var $content;

  /* admin vars */
  var $mode;
  var $page_id;
  var $module_index;
  var $editor;

  /* 
   * constructor
   * @param string $path_type
   * @return void
   * @access public
   */
  public function __construct($path_type) {
    parent::__construct('Content_GenericHTMLContent', $path_type);
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
    $this->libs[] = 'Content_GenericHTMLContentItem.php.inc';
    $this->get_PHPLibs();
    
    /* initialise plugin libraries */
    $this->content = new Content_GenericHTMLContentItem(0, $this);
    
    /* initialise plugin variables */
    $this->layouts = array(
        'nobox'     => $this->get_translation('layout_nobox'),
		'largebox'  => $this->get_translation('layout_largebox')
	);
  }
  
  /* overwrite Module methods */

  /*
   * install module
   * @return boolean success
   * @access public
   */
  public function install ( ) {
    return $this->content->install() and parent::install();
  }
  
  /*
   * uninstall module
   * @return boolean success
   * @access public
   */
  public function uninstall ( ) {
    return $this->content->uninstall() and parent::uninstall();
  }
  
  /*
   * check module installation
   * @return boolean result
   * @access public
   */
  public function is_installed () {
    return $this->content->is_installed();
  }
  
  /*
   * get available content id/name as list
   * @return array
   * @access public
   */
  public function get_contentList () {
    return $this->content->get_nameList();
  }

  /*
   * init module object when in admin mode
   * @return void
   * @access public
   */
  public function init_admin() {
    global $camyks;
    /* page values */
    $this->page_id = isset ($_REQUEST['page_id']) ? (int)$_REQUEST['page_id'] : 0;
    $this->module_index = isset ($_REQUEST['module_index']) ? (int)$_REQUEST['module_index']: -1;
 
    /* check right for this page */
    if ($this->check_right($this->page_id) === false) {
      return $this->init_admin_pageAccessDenied();
    }

    /* get menu object */
    $this->id = isset ($_REQUEST['id']) ? (int)$_REQUEST['id'] : 0;
    $this->content->id = $this->id;
    
    /* get mode */
    $this->mode = isset ($_REQUEST['mode']) ? $_REQUEST['mode'] : 'modify';

    switch ($this->mode) {
    case 'save' :
      /* mode == save */
      $this->init_admin_save();
      break;
    case 'modify':
    default:
      /* mode == modify */
      $this->init_admin_modify();
      break;
    }
    parent::init_admin();
  }

  /*
   * init module object in site mode
   * @param integer $content
   * @param array $params
   * @param integer $mindex
   * @return void
   * @access public
   */
  public function init_site ($content=1, $params=array(), $mindex=null) {
    global $camyks;

    if (!isset($this->contents)) {
      /* add email javascript library */
      $this->add_JSEngineFile('tool/mail.js');

      /* build content list */
      $this->contents = array();
    }

    /* get content */
    $this->contents[$mindex] = new Content_GenericHTMLContentItem($content, $this);
    $this->contents[$mindex]->get($camyks->current_language);
    $this->contents[$mindex]->get_fromItems();

    parent::init_site();
  }

  /*
   * display module object in site mode
   * @param integer $mindex
   * @return void
   * @access private
   */
  public function display_site ($mindex=null) {
    /* get module content */
    $this->content = $this->contents[$mindex];
    
    /* update layout */
    $this->selected_layout = 'site_'.$this->content->vars['layout'].'.html.inc';
    parent::display_site();
  }


  /* specific admin mode methods */

  /*
   * init object when in admin / modify mode
   * @return void
   * @access private
   */
  private function init_admin_modify( ) {
    global $camyks;

    /* check editor availability */
    if (!isset($camyks->inputs['TinyMCEv3']) and !isset($camyks->inputs['TinyMCE']))
      return $this->init_admin_missingPlugin('Input', 'TinyMCEv3');
    /* check tabBuilder availability */
    if (!isset($camyks->inputs['TabBuilder']))
      return $this->init_admin_missingPlugin('Input', 'TabBuilder');
    
    /* load help files */
    $this->get_help();

    /* get object values */
    $this->content->get();
    $this->content->get_fromItems();

    /* get TinyMCE input */
    if (isset($camyks->inputs['TinyMCEv3'])) {
      $this->input = &$camyks->inputs['TinyMCEv3'];
    } elseif (isset($camyks->inputs['TinyMCE'])) {
      $this->input = &$camyks->inputs['TinyMCE'];
      $this->input->set_configInfos('file', $this->get_fileURL('js/tinymce_config.js'));
      /* get page theme */
      $this->input->load_themeCSSFile( $this->page_id );
      /* get file manager input object */
      $this->input->load_fileManager();
      /* get page chooser input object */
      $this->input->load_pageChooser();
    }

    /* initialise */
    $this->input->initialise();

    /* get tabs */
    $this->tabBuilder = &$camyks->inputs['TabBuilder'];
    $this->tabBuilder->add_tab(array(
        'name'  => 'Properties',
		'title' => $camyks->get_translation('properties')
	));
	
    /* update tabs with languages */
    foreach ( $camyks->get_confValue('editing_languages') as $l) {  
        $this->tabBuilder->add_tab(array(
            'name'  => $l,
		    'title' => language_getIcon($l)
	    ));
    }
	if ( $this->help != null )
	    $this->tabBuilder->add_tab(array(
	        'name'  => 'help',
		    'title' => $camyks->get_translation('help')
	    ));
    $this->tabBuilder->initialise(array('default'=>'Properties'));

    /* create html form */
    $this->form = new HTMLForm(
        'generichtmlcontent_form',
		$this->get_adminlink(array('mode'=>'save')),
		'POST'
	);
	$this->form->set_object($this->content);
    
    /* button list for buttons bars */
    $this->buttons = array(
        array(
            'title' => $camyks->get_translation('back'),
			'link'  => $camyks->get_adminLink('Admin_ContentPage', array(
			    'mode'      => 'modify',
				'page_id'   => $this->page_id,
				'openTab'   => 'content'
			))
		),
		array(
		    'title' => $camyks->get_translation('valid'),
			'link'  => $this->form->get_HTMLSubmitLink(),
		)
	);
  }

  /*
   * init object when in admin / save mode
   * @return void
   * @access private
   */
  private function init_admin_save() {
    global $camyks;

    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* save content */
    $this->content->get_fromHeader();
    if ($this->content->save()) {
      if ($this->id == 0 and $this->page_id > 0) {
	    /* update page information with object id for new content */
	    $this->add_moduleContentToPage($this->page_id, $this->module_index, $this->content->id);
      }
      $this->text = $camyks->get_translation('savedone');
    } else {
      $this->text = $camyks->get_translation('savefailed');
    }
    $lgs = $camyks->get_confValue('editing_languages');
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($this->get_adminLink(array(
        'mode'      => 'modify',
		'id'        => $this->content->id, 
		'openTab'   => $lgs[0],
	)));
  }
}
?>