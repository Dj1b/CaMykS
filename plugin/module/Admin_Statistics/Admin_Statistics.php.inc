<?php
/*
 * CaMykS Engine
 * Developed by        : camyks.net
 * Author            : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Engine
 * Creation Date    : May 2007
 * Last Modif Date  : Feb 2018
 * History :
 * * 07-03-xx : Initial files
 * * 08-05-28 : Check rights for configuration modes
 * *            Disable admin menu for data I/O modes
 * * 08-09-26 : ColorPicker input is no more mandatory
 * * 08-10-03 : Add web tools detection and stats
 *
 * Admin Statistics Module
 * Available types :
 * - single : each update create an entry - display each entry
 * - mixed : each item is saved by day and values - display by date and detail values
 * - dated : each item is save by day and values - display by date only
 * - detail : each item is save by day and values - display detail values only
 * - total : only one entry per object (  date is first entry value )
 */

class Admin_Statistics extends Module {
  /* variables */
  var $statobject;
  var $statdata;
  var $registered_stats;
  var $stattypes;
  var $statslist;

  /*
   * constructor
   * @param string $path_type
   */
  function Admin_Statistics ( $path_type ) {
    parent::Module('Admin_Statistics', $path_type);
    /* set module type */
    $this->type = 'admin';
    $this->admin_type = 'monitoring';
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Default';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    /* load plugin libraries */
    $this->libs[] = 'Admin_Statistic.php.inc';
    $this->libs[] = 'Admin_StatisticData.php.inc';
    $this->libs[] = 'Admin_StatisticConfig.php.inc';
    $this->libs[] = 'Admin_StatisticSingleOptions.php.inc';
    $this->libs[] = 'Admin_StatisticMixedOptions.php.inc';
    $this->libs[] = 'Admin_StatisticDatedOptions.php.inc';
    $this->libs[] = 'Admin_StatisticDetailOptions.php.inc';
    $this->libs[] = 'Admin_StatisticsSettings.php.inc';
    $this->libs[] = 'Admin_StatisticWebBotDetector.php.inc';
    $this->libs[] = 'Admin_StatisticWebToolDetector.php.inc';
    $this->get_PHPLibs();
    /* initialise plugin libraries */
    $this->statconfig = new Admin_StatisticConfig( 0, $this);
    $this->statdata = new Admin_StatisticData( 0, $this);
    $this->statobject = new Admin_Statistic( 0, $this );
    $this->settings = new Admin_StatisticsSettings('settings', $this );
    $this->toolDetector = new Admin_StatisticWebToolDetector();
    $this->botDetector = new Admin_StatisticWebBotDetector();
    $this->registered_stats = null;
    /* create statistic types list */
    $this->stattypes = array('single', 'mixed', 'dated', 'detail', 'total');
  }

  /* overwrite Module methods */

  /*
   * install module
   * @return boolean success
   * @access private
   */
  function install ( ) {
    if ( $this->statobject->install()
     and $this->statdata->install()
     and $this->statconfig->install()
     and $this->settings->install()) {
      return parent::install();
    }
    return false;
  }
  
  /*
   * uninstall module
   * @return boolean success
   * @access private
   */
  function uninstall ( ) {
    return $this->statobject->uninstall()
      and $this->statdata->uninstall()
      and $this->statconfig->uninstall()
      and $this->settings->uninstall();
  }
  
  /*
   * check module installation
   * @return boolean result
   * @access private
   */
  function is_installed ( ) {
    return $this->statconfig->is_installed();
  }
  
  /*
   * get module rights
   * @return void
   * @access private
   */
  function get_rights ( ) {
    global $camyks;
    $this->rights[0] = array('name'=>'read',
                 'title'=> $camyks->get_translation('read'),
                 'default'=> false);
    $this->rights[1] = array('name'=>'configuration',
                 'title'=> $this->get_translation('rights_configuration'),
                 'default'=> false);
  }

  /*
   * return statistic titles
   * @param array $pages
   * @param string $type
   * @return array
   * @access private
   */
  function get_adminStatisticsValueTitles ( $data, $type=null ) {
    switch ( $type ) {
    case 'webbots':
      /* type == webbots */
      foreach ( $data as $bot ) {
    if (($botTitle = $this->botDetector->get_botTitle($bot)) != null )
      $data[$bot] = $botTitle;
      }
      return $data;
      break;
    case 'webtools':
      /* type == webtools */
      foreach ( $data as $tool ) {
    if (($toolTitle = $this->toolDetector->get_toolTitle($tool)) != null )
      $data[$tool] = $toolTitle;
      }
      return $data;
      break;
    default:
      return $data;
    }
  }
  
  /*
   * init module object in admin mode
   * @return void
   * @access private
   */
  function init_admin () {
    global $camyks;

    /* check user rights */
    if ( $this->check_right(0) === false )
      return $this->init_admin_accessDenied();
    
    /* get settings */
    $this->settings->get();
    
    /* get registered stats */
    $this->get_registeredStats ( );
    
    /* add statistics styles */
    $this->add_styleFile('admin_statistics.css');
    
    /* add statistics scripts */
    $this->add_JSFile('admin_statistics.js');

    /* build admin title */
    $this->adminTitle = $this->title;
    
    /* build buttons list */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
                 'link' =>$camyks->get_adminLink()));
    
    if ( isset ( $_REQUEST['object'] ) ) {
      $object = $_REQUEST['object'];
      
      if ( $object == '_settings' and $this->check_right(1) ) {
    $mode = isset($_REQUEST['mode'])?$_REQUEST['mode']:'';
    if ( $mode == 'save' )
      $this->init_admin_saveSettings();
    else
      $this->init_admin_editSettings();
      } else if (isset($this->registered_stats[$object])) {
    $this->statobject = $this->registered_stats[$object];
    $this->adminTitle .= $camyks->get_translation('formitem_separator');
    $this->adminTitle .= $this->statobject->vars['title'];
    
    switch ( $this->statobject->vars['type'] ) {
    case 'single':
      $this->init_admin_singleObject();
      break;
    case 'mixed':
      $this->init_admin_mixedObject();
      break;      
    case 'dated':
      $this->init_admin_datedObject();
      break;      
    case 'detail':
      $this->init_admin_detailObject();
      break;      
    case 'total':
      $this->init_admin_totalObject();
      break;
    }

    if (isset($this->form))
      $this->buttons[] = array('title'=>$this->get_translation('computeagain'),
                   'link'=>$this->form->get_HTMLSubmitLink());
      }
    }
    
    /* generic init */
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
  
  /* specific admin mode methods */
  
  /*
   * init module object in admin/edit settings mode
   * @return void
   * @access private
   */
  function init_admin_editSettings() {
    global $camyks;
    /* check configuration rights */
    if ($this->check_right(1) === false )
      return $this->init_admin_accessDenied();

    /* update title */
    $this->adminTitle .= $camyks->get_translation('formitem_separator');
    $this->adminTitle .= $this->get_translation('settings');
    $this->object = 'settings';

    /* build form */
    $this->form = new HTMLForm('editsettings',
                   $camyks->get_adminLink($this->name,
                              array('object'=>'_settings',
                                'mode'=>'save')),
                   'POST');
    $this->form->set_object($this->settings);
    $this->form->add_hidden('stat_filteredips_count_', count($this->settings->vars['stat_filteredips']));

    /* get data */
    $this->statusList = $this->get_settingsStatusList();

    /* add scripts */
    $this->add_JSEngineFile('tool/html.js');
    $this->add_JSFile('admin_statisticssettings.js');
    $this->add_JSScript('var sse = new StatisticsSettingsEditor("sse");');
    $this->add_JSScript('sse.bttn = "'.$this->theme->get_pictURL('minus', 12, 'std').'";');
    $this->add_JSScript('sse.bttn_ = "'.$this->theme->get_pictURL('minus', 12, 'ovr').'";');
    $this->add_JSLoadScript('sse.initialise("'.$this->form->name.'");');

    /* build buttons list */
    $this->buttons = array(array('title'=>$camyks->get_translation('back'),
                 'link' =>$camyks->get_adminLink()),
               array('title'=>$camyks->get_translation('valid'),
                 'link'=>$this->form->get_HTMLSubmitLink()));
  }
  
  /*
   * init module object in admin/save settings mode
   * @return void
   * @access private
   */
  function init_admin_saveSettings() {
    global $camyks;

    /* check configuration rights */
    if ($this->check_right(1) === false )
      return $this->init_admin_accessDenied();

    /* disable admin menus */
    $this->disable_adminEngineMenus();

    /* save */
    $this->settings->get_fromHeader();
    if ($this->settings->save()) {
      $this->text = $this->get_translation('configuration_saved');
    } else {
      $this->text = $this->get_translation('configuration_notsaved');
    }
    $this->selected_layout = 'admin_message.html.inc';
    $this->selected_layout_location = 'camyks';
    $this->set_redirect($camyks->get_confValue('ModuleActionDelay'), $this->get_adminLink());
  }


  /*
   * init module object in admin/single object mode
   * @return void
   * @access private
   */
  function init_admin_singleObject ( ) {
    /* get options */
    $this->init_admin_getsingleoptions();
    /* get tabs */
    $this->init_admin_singleStatisticsTabs();
    /* get form */
    $this->init_admin_optionsForm();
    /* get stats list */
    $this->init_admin_getSingleStatisticValues();
    /* get color input */
    $this->init_admin_colorPickerInput();
  }

  /*
   * init module object in admin/mixed object mode
   * @return void
   * @access private
   */
  function init_admin_mixedObject ( ) {
    /* get options */
    $this->init_admin_getMixedOptions();
    /* get tabs */
    $this->init_admin_mixedStatisticsTabs();
    /* get form */
    $this->init_admin_optionsForm();
    /* get stats list */
    $this->init_admin_getDatedStatisticValues();
    $this->init_admin_getDetailStatisticValues();
    /* get color input */
    $this->init_admin_colorPickerInput();
  }

  /*
   * init module object in admin/detail object mode
   * @return void
   * @access private
   */
  function init_admin_detailObject ( ) {
    /* get options */
    $this->init_admin_getDetailOptions();
    /* get tabs */
    $this->init_admin_singleStatisticsTabs();
    /* get form */
    $this->init_admin_optionsForm();
    /* get stats list */
    $this->init_admin_getDetailStatisticValues();
    /* get color input */
    $this->init_admin_colorPickerInput();
  }

  /*
   * init module object in admin/dated object mode
   * @return void
   * @access private
   */
  function init_admin_datedObject ( ) {
    /* get options */
    $this->init_admin_getDatedOptions();
    /* get tabs */
    $this->init_admin_singleStatisticsTabs();
    /* get form */
    $this->init_admin_optionsForm();
    /* get stats list */
    $this->init_admin_getDatedStatisticValues();
    /* get color input */
    $this->init_admin_colorPickerInput();
  }

  /*
   * init module object in admin/total object mode
   * @return void
   * @access private
   */
  function init_admin_totalObject ( ) {
    /* to do */
  }

  /* specific tool methods */

  /*
   * display statistic
   * @return void
   * @access private
   */
  function display_statistic ( ) {
    $layout = '';
    if ( isset ( $this->statobject->vars['type'] )) {
      $layout = 'admin_'.$this->statobject->vars['type'].'.html.inc';
    } else if ( isset( $this->object ) ) {
      $layout = 'admin_'.$this->object.'.html.inc';
    } else {
      $layout = 'admin_none.html.inc';
    }
    $this->load_file('html/'.$layout);
  }

  /*
   * update statistic
   * @param string $name
   * @param string $plugin
   * @param string $type
   * @param string $main
   * @param string $data1
   * @param string $data2
   * @param array $params
   * @return void
   * @access public
   */
  function update_statistic ( $name='', $plugin='', $type='', $main='', $data1='', $data2='',
    $params = array()) {
    global $camyks;
        
    /* merge params */
    $params = array_merge(array('checkIPFilter'=>1, 'checkAdmin'=>1, 'checkBot'=>1, 'checkTool'=>1), $params);
    
    /* check admin connection */
    if ( $params['checkAdmin'] and $camyks->check_adminUser())
      return;
          
    /* check IP Filter */
    if ( $params['checkIPFilter'] and $this->check_filteredIp(client_getIP()))
      return;
          
    /* check web bots */
    if ( $params['checkBot'] and $this->botDetector->detect() !== false )
      return;
                
    /* check web tool */
    if ( $params['checkTool'] and $this->toolDetector->detect() !== false )
      return;
          
    /* check name */
    if ( $name == '' ) {
      /* log error */
      $camyks->log_executionerror ($this,
                   'Could not save statistic : null name',
                   'Module:'.$plugin.' - type:'.$type.' - data1:'.$data1.' - data2:'.$data2 );
      return;
    }

    /* check plugin */
    if ( $plugin == '' or !isset($camyks->modules[$plugin]) ) {
      /* log error */
      $camyks->log_executionerror ( $this,
                    'Could not save statistic : null or inexistant plugin',
                    'Name:'.$name.' - type:'.$type.' - data1:'.$data1.' - data2:'.$data2 );
      
      return;
    }

    /* check type */
    if ( $type == '' or !in_array($type, $this->stattypes )) {
      /* log error */
      $camyks->log_executionerror ( $this,
                    'Could not save statistic : null or inexistant type',
                    'Module:'.$plugin.' - type:'.$type.' - data1:'.$data1.' - data2:'.$data2 );
      
      return;
    }

    /* get registered stats */
    $this->get_registeredStats ( );

    /* check is stat is already registered */
    if ( isset ($this->registered_stats[$name]) ) {
      /* object exists, check if objectt is the same */
      $s = &$this->registered_stats[$name];
      if ( $s->vars['plugin'] == $plugin
       and $s->vars['type'] == $type ) {
        $s->update_statistic( $main, $data1, $data2 );
      } else {
        /* log error */
        $camyks->log_executionerror ( $this,
                      'Could not save statistic : stat with same name already exists',
                      'Name:'.$name.' - Module:'.$plugin.' - type:'.$type );
        return;
      }
    } else {
      /* create stat object */
      $this->statobject->id = 0;
      $this->statobject->_libItems['name']->value = $name;
      $this->statobject->_libItems['plugin']->value = $plugin;
      $this->statobject->_libItems['type']->value = $type;
      $this->statobject->_libItems['register_date']->value = time();
      $this->statobject->save();
      $camyks->log_information($this,
                   'New '.$type.' statistic named '.$name.' registered by module '.$plugin);
      /* update data */
      $this->statobject->update_statistic( $main, $data1, $data2 ); 
    }
  }

  /*
   * get registered stats list
   * @return boolean success
   * @access private 
   */
  function get_registeredStats( ) {
    global $camyks;
    /* check if registered stats list already exists */
    if ( isset ( $this->registered_stats ) )
      return true;

    /* get complete list */
    $list = $this->statobject->get_objectList(false);
    /* remove disabled module stats objects */
    $this->registered_stats = array();
    foreach ( $list as $s ) {
      if (isset($camyks->modules[$s->vars['plugin']])) {
    $s->get_statisticTitle();
    $this->registered_stats[$s->vars['name']] = $s;
      }
    }
    $list = null;
    return true;
  }

  /*
   * build tabs in single type stats
   * @return void
   * @access private
   */
  function init_admin_singleStatisticsTabs () {
    global $camyks;
    /* tab list for tabs bar */
    $this->tabObject = 'admin_statistics_tabObject';
    $this->tabs = array(array('name'=>'display',
                  'title'=>$this->get_translation('tabdisplay')),
            array('name'=>'options',
                  'title'=>$this->get_translation('taboptions'))); 
    /* add javascript files and scripts */
    $this->add_JSEngineFile('object/ctab.js');
    $this->add_JSScript($this->tabObject.' = new CTab();');
    $this->add_JSScript($this->tabObject.'.init("display", "'
            .$camyks->theme->parts['boxTabCSSStandart'].'","'
            .$camyks->theme->parts['boxTabCSSSelected'].'","'
            .$camyks->theme->parts['boxTabCSSRollover'].'");');

  }

  /*
   * build tabs in mixed type stats
   * @return void
   * @access private
   */
  function init_admin_mixedStatisticsTabs () {
    global $camyks;
    /* tab list for tabs bar */
    $this->tabObject = 'admin_statistics_tabObject';
    $this->tabs = array(array('name'=>'display',
                  'title'=>$this->get_translation('tabdisplay')),
            array('name'=>'detail',
                  'title'=>$this->get_translation('tabdetail')),
            array('name'=>'options',
                  'title'=>$this->get_translation('taboptions'))); 
    /* add javascript files and scripts */
    $this->add_JSEngineFile('object/ctab.js');
    $this->add_JSScript($this->tabObject.' = new CTab();');
    $this->add_JSScript($this->tabObject.'.init("display", "'
            .$camyks->theme->parts['boxTabCSSStandart'].'","'
            .$camyks->theme->parts['boxTabCSSSelected'].'","'
            .$camyks->theme->parts['boxTabCSSRollover'].'");');
    $this->openTab = isset($_REQUEST['openTab']) ? $_REQUEST['openTab'] : 'display'; 
    if ( $this->openTab != 'display' ) {
      $this->add_JSLoadScript($this->tabObject.'.mouseclick("'.$this->openTab.'");');
    }
  }

  /*
   * build option form
   * @return void
   * @access private
   */
  function init_admin_optionsForm () {
    global $camyks;
    /* build form object */
    $this->form = new HTMLForm('admin_statistics_form',
                   $this->get_adminLink(),
                   'POST');
    /* add hiddens */
    $this->form->add_hidden('update_config', 1 );
    $this->form->add_hidden('object', $this->statobject->vars['name'] );
    /* add form name into javascript */
    $this->add_JSScript('admin_statistics_form = "'.$this->form->name.'";');
  }

  /*
   * load color picker
   * @return void
   * @access private
   */
  function init_admin_colorPickerInput ( ){
    global $camyks;
    if ( isset($camyks->inputs['ColorPicker']) ) {
      $this->colorPicker = &$camyks->inputs['ColorPicker'];
      $this->colorPicker->initialise('cp', 'default', 'modal');
    } else {
      $this->colorPicker = false;
    }
  }

  /*
   * build option in single type stats
   * @return void
   * @access private
   */
  function init_admin_getSingleOptions() {
    global $camyks;
    $this->config = new Admin_StatisticSingleOptions(0, $this);
    if ( isset ( $_REQUEST['update_config'] ) ) {
      /* get new config from header */
      $this->config->get_fromHeader();
      /* save new config : colors */
      $this->statconfig->_libItems['user']->value = $camyks->adminUser->login;
      $this->statconfig->_libItems['object']->value = 'colors';
      $this->statconfig->_libItems['mode']->value = '';
      $this->statconfig->_libItems['value']->value = $this->config->get_colorsAsProperties();
      $this->statconfig->save();
      /* save new config : values */
      $this->statconfig->_libItems['object']->value = $this->statobject->vars['name'];
      $this->statconfig->_libItems['value']->value = $this->config->get_valuesAsProperties();
      $this->statconfig->save();
    } else {
      /* get config from database */
      $this->config->get();
      $savedconfigs = $this->statconfig->get_configs ( $this->statobject->vars['name'] );
      if ( isset ( $savedconfigs['colors'] ) ) {
    $this->config->get_colorsFromProperties( $savedconfigs['colors']->vars['value'] );
      }
      if ( isset ( $savedconfigs[$this->statobject->vars['name']] ) ) {
    $this->config->get_valuesFromProperties( $savedconfigs[$this->statobject->vars['name']]->vars['value'] );
      }
    }
    $this->config->get_fromItems();
  }

  /*
   * load values in single type stats
   * @return void
   * @access private
   */
  function init_admin_getSingleStatisticValues ( ) {
    global $camyks;
    /* get config */
    $config = $this->config->build_config($this->statobject->id);
    /* get statistics description */
    $this->statsdesc = $config['desc'];
    /* get statistics list */
    $this->statslist = $this->statdata->get_objectList(false,
                               $config['where'],
                               0,
                               $config['limit'],
                               'statdate',
                               'desc');
    /* get titles */
    $list = array();
    foreach ( $this->statslist as $stat )
      if ( !isset ( $list[$stat->vars['main']] ) )
    $list[$stat->vars['main']] = $stat->vars['main'];
    
    $this->maintitles = $camyks->modules[$this->statobject->vars['plugin']]->get_adminStatisticsValueTitles ( $list, $this->statobject->vars['name'] );
  }


  /*
   * build option in mixed type stats
   * @return void
   * @access private
   */
  function init_admin_getMixedOptions() {
    global $camyks;
    $this->config = new Admin_StatisticMixedOptions(0, $this);
    if ( isset ( $_REQUEST['update_config'] ) ) {
      /* get new config from header */
      $this->config->get_fromHeader();

      /* save new config : colors */
      $this->statconfig->_libItems['user']->value = $camyks->adminUser->login;
      $this->statconfig->_libItems['object']->value = 'colors';
      $this->statconfig->_libItems['mode']->value = '';
      $this->statconfig->_libItems['value']->value = $this->config->get_colorsAsProperties();
      $this->statconfig->save();
      /* save new config : values */
      $this->statconfig->_libItems['object']->value = $this->statobject->vars['name'];
      $this->statconfig->_libItems['value']->value = $this->config->get_valuesAsProperties();
      $this->statconfig->save();
    } else {
      /* get config from database */
      $this->config->get();
      $savedconfigs = $this->statconfig->get_configs ( $this->statobject->vars['name'] );
      if ( isset ( $savedconfigs['colors'] ) ) {
    $this->config->get_colorsFromProperties( $savedconfigs['colors']->vars['value'] );
      }
      if ( isset ( $savedconfigs[$this->statobject->vars['name']] ) ) {
    $this->config->get_valuesFromProperties( $savedconfigs[$this->statobject->vars['name']]->vars['value'] );
      }
    }
    $this->config->get_fromItems();
    /* get config */
    $this->c_config = $this->config->build_config($this->statobject->id);
  }

  /*
   * build option in dated type stats
   * @return void
   * @access private
   */
  function init_admin_getDatedOptions() {
    global $camyks;
    $this->config = new Admin_StatisticDatedOptions(0, $this);
    if ( isset ( $_REQUEST['update_config'] ) ) {
      /* get new config from header */
      $this->config->get_fromHeader();
      /* save new config : colors */
      $this->statconfig->_libItems['user']->value = $camyks->adminUser->login;
      $this->statconfig->_libItems['object']->value = 'colors';
      $this->statconfig->_libItems['mode']->value = '';
      $this->statconfig->_libItems['value']->value = $this->config->get_colorsAsProperties();
      $this->statconfig->save();
      /* save new config : values */
      $this->statconfig->_libItems['object']->value = $this->statobject->vars['name'];
      $this->statconfig->_libItems['value']->value = $this->config->get_valuesAsProperties();
      $this->statconfig->save();
    } else {
      /* get config from database */
      $this->config->get();
      $savedconfigs = $this->statconfig->get_configs ( $this->statobject->vars['name'] );
      if ( isset ( $savedconfigs['colors'] ) ) {
    $this->config->get_colorsFromProperties( $savedconfigs['colors']->vars['value'] );
      }
      if ( isset ( $savedconfigs[$this->statobject->vars['name']] ) ) {
    $this->config->get_valuesFromProperties( $savedconfigs[$this->statobject->vars['name']]->vars['value'] );
      }
    }
    $this->config->get_fromItems();
    /* get config */
    $this->c_config = $this->config->build_config($this->statobject->id);
  }

  /*
   * build option in detail type stats
   * @return void
   * @access private
   */
  function init_admin_getDetailOptions() {
    global $camyks;
    $this->config = new Admin_StatisticDetailOptions(0, $this);
    if ( isset ( $_REQUEST['update_config'] ) ) {
      /* get new config from header */
      $this->config->get_fromHeader();
      /* save new config : colors */
      $this->statconfig->_libItems['user']->value = $camyks->adminUser->login;
      $this->statconfig->_libItems['object']->value = 'colors';
      $this->statconfig->_libItems['mode']->value = '';
      $this->statconfig->_libItems['value']->value = $this->config->get_colorsAsProperties();
      $this->statconfig->save();
      /* save new config : values */
      $this->statconfig->_libItems['object']->value = $this->statobject->vars['name'];
      $this->statconfig->_libItems['value']->value = $this->config->get_valuesAsProperties();
      $this->statconfig->save();
    } else {
      /* get config from database */
      $this->config->get();
      $savedconfigs = $this->statconfig->get_configs ( $this->statobject->vars['name'] );
      if ( isset ( $savedconfigs['colors'] ) ) {
    $this->config->get_colorsFromProperties( $savedconfigs['colors']->vars['value'] );
      }
      if ( isset ( $savedconfigs[$this->statobject->vars['name']] ) ) {
    $this->config->get_valuesFromProperties( $savedconfigs[$this->statobject->vars['name']]->vars['value'] );
      }
    }
    $this->config->get_fromItems();
    /* get config */
    $this->c_config = $this->config->build_config($this->statobject->id);
  }
  
  
  /*
   * load value in dated type stats
   * @return void
   * @access private
   */
  function init_admin_getDatedStatisticValues ( ) {
    /* get main tab statistics total */
    $this->statsmaintotal = $this->statdata->get_statisticsTotalValue( $this->c_config['maintotalwhere'] );
    /* get main tab statistics by day */
    $this->statsmainbyday = $this->statdata->get_statisticsByDayValue( $this->c_config['mainbydaywhere'] );
    /* get main tab statistics by month */
    $this->statsmainbymonth = $this->statdata->get_statisticsByMonthValue( $this->c_config['mainbymonthwhere'] );
    /* get main tab statistics by year */
    $this->statsmainbyyear = $this->statdata->get_statisticsByYearValue( $this->c_config['mainbyyearwhere'] );
  }

  /*
   * load value in detail type stats
   * @return void
   * @access private
   */
  function init_admin_getDetailStatisticValues() {
    global $camyks;
    /* get detail tab statistics description */
    $this->statsdetaildesc = $this->c_config['detaildesc'];
    
    /* get detail tab statistics total */
    $this->statsdetailtotal = $this->statdata->get_statisticsTotalValue( $this->c_config['detailwhere'] );
    
    if ( $this->statsdetailtotal > 0 ) { 
      /* get detail tab statistics list */
      $this->statsdetaillist = $this->statdata->get_mixedStatisticList( $this->c_config['detailwhere'],
                                    $this->c_config['detaillimit']);
      /* get detail tab statistics max value */
      foreach ( $this->statsdetaillist as $stat ) {
    $this->statsdetailmax = $stat;
    break;
      }
      
      /* get combined titles */
      $list = array();
      foreach ( $this->statsdetaillist as $stat=>$value )
    if ( !isset ( $list[$stat] ) )
      $list[$stat] = $stat;
      
      $this->detailtitles = $camyks->modules[$this->statobject->vars['plugin']]->get_adminStatisticsValueTitles ( $list, $this->statobject->vars['name'] );
    } else {
      $this->statsdetaillist = array();
    } 
  }
  
  
  /*
   * update site statistics
   * @return void
   * @access private
   */
  function update_siteStatistics() {
    global $camyks;    

    /* load settings */
    $this->settings->get();

    /* check filtered ip */
    if ($this->check_filteredIp(client_getIP()))
      return;
   
    /* check contected admin */
    if ($camyks->check_adminUser())
      return;
      
    /* build update params */
    $params = array('IPFilter'=>0, 'checkAdmin'=>0, 'checkBot'=>0, 'checkTool'=>0);
    
    /* check web bots */
    if ( ( $bot = $this->botDetector->detect() )!==false ) {
      if ( $this->settings->vars['stat_webbots'] == 1 ) {
        $this->update_statistic('webbots', 
                $this->name,
                'mixed',
                $bot,
                '',
                '',
                $params);
      }
      return;
    } elseif ( ($tool = $this->toolDetector->detect() )!==false ) {
      if ( $this->settings->vars['stat_webtools'] == 1 ) {
        $this->update_statistic('webtools', 
                $this->name,
                'mixed',
                $tool,
                '',
                '',
                $params);
      }
      return;
    }
    
    /* update current page */
    if ( $this->settings->vars['stat_sitepage'] == 2 ) {
      $this->update_statistic('sitepage', 
                  'Admin_ContentPage',
                  'mixed',
                  $camyks->contentPage->id,
                  $camyks->contentPage->params_,
                  $camyks->current_language,
                  $params);
    } else if ( $this->settings->vars['stat_sitepage'] == 1 ){
      $this->update_statistic('sitepage', 
                  'Admin_ContentPage',
                  'mixed',
                  $camyks->contentPage->id,
                  '',
                  '',
                  $params);
    }
    if ( $camyks->get_sessionValue('mysession') != 1 ) {
      /* new visit */
      if ($this->settings->vars['stat_visits'] == 1)
            $this->update_statistic('visits', 'Admin_ContentPage', 'dated', '', '', '', $params);

      /* referer : (remove http:// from url, and compare to current site url) */
      if ($this->settings->vars['stat_referer'] == 1) {
        $rsite = trim(client_getRefererSite());
        if ($rsite != '' and !url_areInSameDomain(array($rsite, $camyks->get_confValue('url')), true)) {
            $rsite = parse_url($rsite);
            if (!in_array($rsite['scheme'], array('http', 'https')))
                $domain = $rsite['host'].' ('.$rsite['scheme'].')';
            else
                $domain = $rsite['host'];
            $this->update_statistic('referer', 'Admin_ContentPage', 'detail', $domain, '', '', $params);
        }
      }
      
      /* first page */
      if ($this->settings->vars['stat_firstpage'] == 1) {
        $this->update_statistic('firstpage', 'Admin_ContentPage', 'detail', $camyks->contentPage->id, $camyks->contentPage->params_, $camyks->current_language, $params);
      }
      /* geo ip */
      /* TO DO */
      /* update session value */
      $camyks->set_sessionValue('mysession', 1);
    }
  }

  /*
   * display color picker
   * @param $name
   * @return void
   * @access private
   */
  function display_colorPicker($name) {
    /* check config color value */
    if (isset($this->config->vars[$name])) {      
      $color = $this->config->vars[$name];
      /* check if color picker is available */
      if ($this->colorPicker !== false) {
        $this->colorPicker->display( $name, $color);
      } else {
        $this->colorPickerValue = $color;
        $this->load_file('html/admin_colorpicker.html.inc');
      }
    }
  }

  /*
   * return settings status list
   * @return array
   * @access private
   */
  function get_settingsStatusList() {
    return array(0 => $this->get_translation('status_disabled'),
         1 => $this->get_translation('status_enabled'));
  }

  /*
   * check given ip in filtered ip list
   * @param string $ip
   * @return boolean result
   * @access private
   */
  function check_filteredIP($ip) {
    if (!isset($this->settings->vars))
      $this->settings->get();
    return (in_array($ip, $this->settings->vars['stat_filteredips']));
  }
  
  /*
   * return statistic values
   * @param string $plugin
   * @param string $statName
   * @param array $params
   * @access public
   */
  function get_statistics($plugin, $statName, $params=array()) {
    global $camyks;
        
    /* load stat id */
    $statId = $this->statobject->get_idFromPluginAndName($plugin, $statName);
    if ($statId === false)
      return array();
        
    /* load stat data */
    return $this->statdata->get_statistics($statId, $params);
  }
}
?>