<?php
/*
 * CaMykS Engine
 * Developed by        : camyks.net
 * Author            : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version    : 1.0
 * Object Version    : 2.0.2
 * Object Type      : Plugin / Module Engine
 * Creation Date    : Aug 2007
 * Last Modif Date  : Oct 2018
 *
 * Installer Module
 * To do :
 * - add a link to camyks "installation help" article to the buttons list
 * - add folder check and installation
 */

final class Tool_Installer extends Module {
  /* variables */
  protected $summary;
  private $allowInstall;
  private $symLinks;
  private $textColors;

  /*
   * constructor
   * @param string $path_type
   * @access public
   */
  public function __construct ( $path_type ) {
    parent::Module('Tool_Installer', $path_type);
    /* set module type */
    $this->type = 'tool';
    /* set plugin version */
    $this->version = '2.0';
    /* set plugin package */
    $this->plugin_package = 'System';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';

    /* load library */
    $this->libs[] = 'Tool_InstallerParams.php.inc';
    $this->get_PHPLibs();
    $this->params = new Tool_InstallerParams(0, $this);
  }

  /* overwrite Module methods */

  /*
   * init module object in admin mode
   * @return void
   * @access public
   */
  public function init_admin() {
    global $camyks;

    /* get mode */
    $mode = isset($_REQUEST['mode']) ? $_REQUEST['mode'] : 'welcome';

    /* define installer data */
    $this->symLinks = array('plugin'=>'cplugin', 'engine/data'=>'cdata');
    $this->textColors = array(
        'yes'   => 'green',
        'no'    => '#CC3333',
    );

    /* load params */
    $this->params->initialise();
    $this->params->load_fromSession('InstallerConfig', true);
    $this->params->initialise_hiddenValues();
    $this->params->get_fromItems();

    /* add specific styles */
    $bkgdPicture = new FSFile($this->get_filePath('img/bkgd.png'));
    $this->add_styleScript("\n".'body{ background-repeat:no-repeat; background-position:50% 0; background-image:url("'.$bkgdPicture->get_base64Data().'");}');

    /* installer execution */
    switch ($mode) {
      case 'install':
        /* mode == install */
        $this->init_admin_install();
        break;
      case 'summary':
        /* mode == summary */
        $this->init_admin_summary();
        break;
      case 'save_configuration':
        /* mode == save_configuration */
        $this->init_admin_save_configuration();
        break;
      case 'configuration':
        /* mode == configuration */
        $this->init_admin_configuration();
        break;
      case 'welcome':
        /* mode == welcome */
        $this->init_admin_welcome();
        break;
    }
  }

  /* specific admin mode methods */

  /*
   * init module object in admin/welcome mode
   * @return void
   * @access private
   */
  private function init_admin_welcome() {
    global $camyks;

    /* load camyks logo */
    $this->welcomePicture = new FSFile($camyks->camyks_engine_path.'/data/img/logo/logo500.png');

    /* update selected layout */
    $this->selected_layout = 'admin_welcome.html.inc';
  }

  /*
   * init module object in admin/configuration mode
   * @return void
   * @access private
   */
  private function init_admin_configuration() {
    global $camyks;

    /* build configuration form */
    $this->configForm = new HTMLForm('configForm', '?mode=save_configuration', 'POST');
    $this->configForm->set_object($this->params);

    /* load script */
    $this->add_JSScript(file_get_contents($camyks->camyks_engine_path.'/data/js/object/ctab.js'));
    $this->add_JSScript('var cTabs = new CTab();');
    $this->add_JSLoadScript('cTabs.init("", "eTableSubHeader", "eTableSubHeader", "eTableSubHeader");');
    $this->add_JSLoadScript('cTabs.mouseclick("Website");');
    $this->add_JSScript('document.addEventListener("keydown", function (e) {  onTabPressed(e); }, false);');
    $this->add_JSScript('function onTabPressed(e) {');
    $this->add_JSScript('if (e.keyCode != 9) return;');
    $this->add_JSScript('elmnt = document.activeElement.name;');
    $this->add_JSScript('switch (elmnt) {');
    $this->add_JSScript('case "site_company": e.preventDefault(); cTabs.mouseclick("Admin"); document.getElementById("configForm")["_admin_languages_en"].focus(); return;');
    $this->add_JSScript('case "admin_ssl": e.preventDefault(); cTabs.mouseclick("Site"); document.getElementById("configForm")["_site_languages_en"].focus(); return;');
    $this->add_JSScript('case "site_ssl": e.preventDefault(); cTabs.mouseclick("Database"); document.getElementById("configForm")["database_driver"].focus(); return;');
    $this->add_JSScript('case "database_pwd": e.preventDefault(); cTabs.mouseclick("Webmaster"); document.getElementById("configForm")["webmaster_login"].focus(); return;');
    $this->add_JSScript('case "webmaster_email": e.preventDefault(); cTabs.mouseclick("Options"); document.getElementById("configForm")["google_analytics"].focus(); return;');
    $this->add_JSScript('case "mobileMode": e.preventDefault(); cTabs.mouseclick("Website"); document.getElementById("configForm")["site_title"].focus(); return;');
    $this->add_JSScript('}');

    $this->add_JSScript('}');

    /* load data */
    $this->driverList = Database_connection::get_availableDriverList();
    $this->encodingList = array('utf8'=>'UTF8');
    $this->SSLModeList = $this->params->get_SSLModeList();
    $this->adminThemeList = $this->params->get_adminThemeList();
    $this->siteThemeList = $this->params->get_siteThemeList();
    $this->templateList = $this->params->get_templateList();
    $this->mobileModeList = $this->params->get_mobileModeList();
    $this->languages = $this->params->get_availableLanguages();

    /* build button list */
    $this->buttons = array(array(
      'title' => $this->get_translation('continue'),
      'link'  => $this->configForm->get_HTMLSubmitLink(),
    ));

    /* update selected layout */
    $this->selected_layout = 'admin_configuration.html.inc';
  }

  /*
   * init module object in admin/save_configuration mode
   * @return void
   * @access private
   */
  private function init_admin_save_configuration() {

    /* check from header data */
    if (!isset($_REQUEST['site_title'])) {
      header('Location:?mode=configuration');
      die();
    }

    /* load config from header */
    $this->params->get_fromHeader();
    $this->params->get_fromItems();

    /* save config */
    $this->params->save_toSession('InstallerConfig');

    /* go to summary display */
    header('Location:?mode=summary');
  }

  /*
   * init module object in admin/main mode
   * @return void
   * @access private
   */
  private function init_admin_summary() {
    global $camyks;

    /* define some running vars */
    $this->allowInstall = true;
    $this->summary = array();

    /* merge personnalised config */
    foreach ($camyks->site_conf as $name => $value) {
      if (isset($this->params->vars[$name])) $camyks->site_conf[$name] = $this->params->vars[$name];
    }

    /* execute all checks */
    $this->checkCaMykSConfig();
    $this->checkSiteConfig();
    $this->checkPlugins();
    $this->checkDatabase();
    $this->checkSymLinks();
    $this->checkAdminUser();

    /* build button list */
    $this->buttons = array(array(
        'title' => $camyks->get_translation('back'),
        'link'  => '?mode=configuration',
    ));

    if ($this->allowInstall) {
      $this->buttons[] = array(
        'title' => $this->get_translation('install'),
        'link'  => '?mode=install',
      );
    } else {
      $this->buttons[] = array(
        'title' => $this->get_translation('install'),
        'link'  => '',
      );
    }

    /* update selected layout */
    $this->selected_layout = 'admin_summary.html.inc';
  }

  /*
   * init module object in admin/install mode
   * @return void
   * @access private
   */
  private function init_admin_install() {
    global $camyks;

    /* define some running vars */
    $this->allowInstall = true;
    $this->isInstalled = true;
    $this->buttons = array();
    $this->summary = array();

    /* merge personnalised config */
    foreach ($camyks->site_conf as $name => $value) {
      if (isset($this->params->vars[$name])) $camyks->site_conf[$name] = $this->params->vars[$name];
    }

    /* Check optional config items */
    if (isset($camyks->site_conf['database_host']) and trim($camyks->site_conf['database_host']) == '') unset($camyks->site_conf['database_host']);
    if (isset($camyks->site_conf['database_login']) and trim($camyks->site_conf['database_login']) == '') unset($camyks->site_conf['database_login']);
    if (isset($camyks->site_conf['database_pwd']) and trim($camyks->site_conf['database_pwd']) == '') unset($camyks->site_conf['database_pwd']);

    /* build button list */
    $this->buttons = array(array(
        'title' => $camyks->get_translation('back'),
        'link'  => '?mode=configuration',
    ));

    /* basic checks */
    $this->checkSiteConfig();
    $this->checkPlugins();

    /* install all part if installation is allowed */
    if ( $this->allowInstall ) {
      /* erase check message */
      $this->summary = array();

      $this->installDatabase();

      if ($this->isInstalled)
        $this->installPlugins();

      if ($this->isInstalled)
        $this->installsymLinks();

      if ($this->isInstalled) {
        /* finalise installation */
        $this->installDone();
      } else {

      }
    }

    /* update selected layout */
    $this->selected_layout = 'admin_summary.html.inc';
  }

  /* specific tool methods */

  /*
   * check CaMykS engine config
   * @return void
   * @access private
   */
  private function checkCaMykSConfig() {
    global $camyks;

    /* add camyks config title */
    $this->summary[] = array(
      'type'    => 'title',
      'name'    => $this->get_translation('camyksconfigcheck'),
      'value'   => '',
    );

    /* display engine availability */
    $this->summary[] = array(
      'type'    => 'message',
      'name'    => $this->get_translation('availability'),
      'value'   => $this->get_translation('ok'),
      'color'   => $this->textColors['yes'],
    );

    /* display engine installation mode */
    $this->summary[] = array(
      'type'    => 'message',
      'name'    => $this->get_translation('installationmode'),
      'value'   => $camyks->get_translation($camyks->_installationMode),
    );
  }

  /*
   * check site configuration file
   * @return void
   * @access private
   */
  private function checkSiteConfig() {
    global $camyks;

    /* add configuration file title */
    $this->summary[] = array(
      'type'    => 'title',
      'name'    => $this->get_translation('siteconfigcheck'),
      'value'   => '',
    );

    /* check site/folder name */
    $message = array(
      'type'    => 'message',
      'name'    => $this->get_translation('configvalue', 'site_name'),
      'value'   => '',
    );

    $folderName = explode('/', realpath('.') );
    $folderName = $folderName[count($folderName)-1];
    if ( $folderName == $camyks->site_conf['site_name'] ){
      $message['value'] = $this->get_translation('ok');
      $message['color'] = $this->textColors['yes'];
    } else {
      $message['value'] = $this->get_translation('sitename_error');
      $message['color'] = $this->textColors['no'];
      $this->allowInstall = false;
    }
    $this->summary[] = $message;

    /* check site url */
    $message = array(
      'type'    => 'message',
      'name'    => $this->get_translation('configvalue', 'url'),
      'value'   => '',
    );

    if (isset($camyks->site_conf['url']) and $camyks->site_conf['url'] != '') {
      $message['value'] = $this->get_translation('ok');
      $message['color'] = $this->textColors['yes'];
    } else {
      $message['value'] = $this->get_translation('url_error');
      $message['color'] = $this->textColors['no'];
      $this->allowInstall = false;
    }
    $this->summary[] = $message;

    /* check admininstation entry file */
    $message = array(
      'type'=>'message',
      'name'=>$this->get_translation('configvalue', 'admin_entry'),
      'value'=>'',
    );

    if (isset($camyks->site_conf['admin_entry']) and file_exists(realpath('./'.$camyks->site_conf['admin_entry']))) {
      $message['value'] = $this->get_translation('ok');
      $message['color'] = $this->textColors['yes'];
    } else {
      $message['value'] = $this->get_translation('adminentry_error');
      $message['color'] = $this->textColors['no'];
      $this->allowInstall = false;
    }
    $this->summary[] = $message;

    /* check database name */
    $message = array(
      'type'    => 'message',
      'name'    => $this->get_translation('configvalue', 'database_name'),
      'value'   => '',
    );

    if ( isset($camyks->site_conf['database_name']) and $camyks->site_conf['database_name'] != '' ) {
      $message['value'] = $this->get_translation('ok');
      $message['color'] = $this->textColors['yes'];
    } else {
      $message['value'] = $this->get_translation('database_name_error');
      $message['color'] = $this->textColors['no'];
      $this->allowInstall = false;
    }
    $this->summary[] = $message;

    /* check page_maxmodules (default value is 8) */
    $message = array(
      'type'    => 'message',
      'name'    => $this->get_translation('configvalue', 'page_maxmodules'),
      'value'   => '',
    );

    if ( isset($camyks->site_conf['page_maxmodules']) and $camyks->site_conf['page_maxmodules'] > 0 ) {
      $message['value'] = $this->get_translation('ok');
      $message['color'] = $this->textColors['yes'];
    } else {
      $message['value'] = $this->get_translation('page_maxmodules_error');
      $this->allowInstall = false;
      $message['color'] = $this->textColors['no'];
    }
    $this->summary[] = $message;
  }

  /*
   * check database connection
   * @return void
   * @access private
   */
  private function checkDatabase() {
    global $camyks;

    /* add database tests title */
    $this->summary[] = array(
      'type'    => 'title',
      'name'    => $this->get_translation('databasecheck'),
      'value'   => '',
    );

    /* create connection */
    $message = array(
      'type'    => 'message',
      'name'    => $this->get_translation('database_connection'),
      'value'   => ''
    );
    $camyks->db_conn = new Database_connection (
        isset($camyks->site_conf['database_host']) ? $camyks->site_conf['database_host']:$camyks->_conf['database_host'],
        isset($camyks->site_conf['database_login']) ? $camyks->site_conf['database_login']:$camyks->_conf['database_login'],
        isset($camyks->site_conf['database_pwd']) ? $camyks->site_conf['database_pwd']:$camyks->_conf['database_pwd'],
        isset($camyks->site_conf['database_driver']) ? $camyks->site_conf['database_driver']:$camyks->_conf['database_driver']
    );

    /* check status */
    $status = $camyks->db_conn->check_status($camyks->site_conf['database_name']);

    if ($status['ServerConnected']) {
      $message['value'] = $this->get_translation('ok');
      $message['color'] = $this->textColors['yes'];
    } else {
      $message['value'] = $this->get_translation('database_connection_failed');
      $message['color'] = $this->textColors['no'];
      $this->allowInstall = false;
    }
    $this->summary[] = $message;

    /* check if database exists */
    $message = array(
      'type'    => 'message',
      'name'    => $this->get_translation('database_db'),
      'value'   => ''
    );

    if ($status['DatabaseExists'])
      $message['value'] = $this->get_translation('ok');
    else
      $message['value'] = $this->get_translation('database_dbdoesntexist');

    $this->summary[] = $message;

    /* close the database */
    $camyks->db_conn->close();
  }

  /*
   * check symbolic links existance
   * @return void
   * @access private
   */
  private function checkSymLinks() {
    global $camyks;

    /* do not install sym links in "dedicated" installation mode */
    if ($camyks->_installationMode == 'dedicated')
      return;

    /* add symLinks check title */
    $this->summary[] = array(
        'type'  => 'title',
        'name'  => $this->get_translation('symLinkscheck'),
        'value' => '',
    );

    /* check write right */
    $message = array(
        'type'  => 'message',
        'name'  => $this->get_translation('write_rights'),
        'value' => '',
    );
    $myfile = realpath('.');

    if (is_writable($myfile)) {
      $message['value'] = $camyks->get_translation('yes');
      $message['color'] = $this->textColors['yes'];
    } else {
      $message['value'] = $camyks->get_translation('no');
      $message['color'] = $this->textColors['no'];
      $this->allowInstall = false;
    }
    $this->summary[] = $message;

    /* check symlink exists */
    foreach ($this->symLinks as $l) {
      $message = array(
        'type'  => 'message',
        'name'  => $this->get_translation('symlinkfound', $l),
        'value' => '',
      );

      if (file_exists(realpath('./'.$l))) {
        $message['value'] = $camyks->get_translation('yes');
      } else {
        $message['value'] = $camyks->get_translation('no');
      }
      $this->summary[] = $message;
    }
  }

  /*
   * check mandatory plugins
   * @return void
   * @access private
   */
  private function checkPlugins() {
    global $camyks;

    $this->summary[] = array(
        'type'  => 'title',
        'name'  => $this->get_translation('pluginscheck'),
        'value' => ''
    );

    /* check modules */
    foreach ($camyks->neededModules as $p) {
      $message = array(
        'type'  => 'message',
        'name'  => $camyks->get_translation('modulex', $p['name']),
      );
      if (!isset($camyks->modules[$p['name']])) {
        $message['value'] = $this->get_translation('notfound');
        $message['color'] = $this->textColors['no'];
        $this->allowInstall = false;
      } elseif ($camyks->modules[$p['name']]->version < $p['version']) {
        $message['value'] = $this->get_translation('oldversion');
        $message['color'] = $this->textColors['no'];
        $this->allowInstall = false;
      } else {
        $message['value'] = $camyks->get_translation('yes');
        $message['color'] = $this->textColors['yes'];
      }
      $this->summary[] = $message;
    }

    /* check inputs */
    foreach ($camyks->neededInputs as $p) {
      $message = array(
        'type'  => 'message',
        'name'  => $camyks->get_translation('inputx', $p['name']),
      );

      if (!isset($camyks->inputs[$p['name']])) {
        $message['value'] = $this->get_translation('notfound');
        $message['color'] = $this->textColors['no'];
        $this->allowInstall = false;
      } elseif ($camyks->inputs[$p['name']]->version < $p['version']) {
        $message['value'] = $this->get_translation('oldversion');
        $message['color'] = $this->textColors['no'];
        $this->allowInstall = false;
      } else {
        $message['value'] = $camyks->get_translation('yes');
        $message['color'] = $this->textColors['yes'];
      }
      $this->summary[] = $message;
    }

    /* check themes */
    foreach ($camyks->neededThemes as $p) {
      $message = array(
        'type'  => 'message',
        'name'  => $camyks->get_translation('themex', $p['name']),
      );

      if (!isset($camyks->themes[$p['name']])) {
        $message['value'] = $this->get_translation('notfound');
        $message['color'] = $this->textColors['no'];
        $this->allowInstall = false;
      } elseif ($camyks->themes[$p['name']]->version < $p['version']) {
        $message['value'] = $this->get_translation('oldversion');
        $message['color'] = $this->textColors['no'];
        $this->allowInstall = false;
      } else {
        $message['value'] = $camyks->get_translation('yes');
        $message['color'] = $this->textColors['yes'];
      }
      $this->summary[] = $message;
    }

    /* check templates */
    foreach ($camyks->neededTemplates as $p) {
      $message = array(
        'type'  => 'message',
        'name'  => $camyks->get_translation('templatex', $p['name']),
      );

      if (!isset($camyks->templates[$p['name']])) {
        $message['value'] = $this->get_translation('notfound');
        $message['color'] = $this->textColors['no'];
        $this->allowInstall = false;
      } elseif ($camyks->templates[$p['name']]->version < $p['version']) {
        $message['value'] = $this->get_translation('oldversion');
        $message['color'] = $this->textColors['no'];
        $this->allowInstall = false;
      } else {
        $message['value'] = $camyks->get_translation('yes');
        $message['color'] = $this->textColors['yes'];
      }
      $this->summary[] = $message;
    }
  }

  /*
   * check admin user
   * @return void
   * @access private
   */
  private function checkAdminUser() {
    global $camyks;

    if (!$camyks->modules['Admin_User'])
      return;

    /* add title */
    $this->summary[] = array(
        'type'  => 'title',
        'name'  => $this->get_translation('adminscheck'),
        'value' => ''
    );

    /* prepare message */
    $message = array(
        'type'  => 'message',
        'name'  => $this->get_translation('masteraccount'),
      );

    $user = $camyks->modules['Admin_User']->user;
    $user->login = $this->params->vars['webmaster_login'];
    $user->change_pwd = 1;
    $user->pwd = $this->params->vars['webmaster_password'];
    $user->pwd_conf = $this->params->vars['webmaster_password'];
    $user->email = $this->params->vars['webmaster_email'];

    if ($user->check_data()) {
      $message['value'] = $camyks->get_translation('yes');
      $message['color'] = $this->textColors['yes'];
    } else {
      $message['value'] = $user->_libError;
      $message['color'] = $this->textColors['no'];
      $this->allowInstall = false;
    }
    $this->summary[] = $message;
  }

  /*
   * install database
   * @return void
   * @access private
   */
  private function installDatabase() {
    global $camyks;

    print_r($camyks->_conf);

    /* get database connection */
    $camyks->db_conn = new Database_connection(
        isset($camyks->site_conf['database_host']) ? $camyks->site_conf['database_host']:$camyks->_conf['database_host'],
        isset($camyks->site_conf['database_login']) ? $camyks->site_conf['database_login']:$camyks->_conf['database_login'],
        isset($camyks->site_conf['database_pwd']) ? $camyks->site_conf['database_pwd']:$camyks->_conf['database_pwd'],
        isset($camyks->site_conf['database_driver']) ? $camyks->site_conf['database_driver']:$camyks->_conf['database_driver']
    );

    /* check if connection is active */
    if ($camyks->db_conn->is_active()) {
      if (!$camyks->db_conn->database_exists($camyks->site_conf['database_name'])) {
        $message = array(
          'type'    => 'message',
          'name'    => $this->get_translation('database_created'),
        );

        /* try to create database  */
        if (!$camyks->db_conn->database_create($camyks->site_conf['database_name'], $camyks->get_mysqlencodingvalue())) {
          $message['value'] = $camyks->get_translation('no');
          $message['color'] = $this->textColors['no'];
          $this->isInstalled = false;
          $this->summary[] = $message;
          return;
        }
        $message['value'] = $camyks->get_translation('yes');
        $message['color'] = $this->textColors['yes'];

        $this->summary[] = $message;
      }

      $camyks->db_conn->select($camyks->site_conf['database_name']);
    } else {
      /* database connection failed */
      $this->summary[] = array(
        'type'  => 'message',
        'name'  => $this->get_translation('database_connection'),
        'value' => $this->get_translation('database_connection_failed'),
        'color' => $this->textColors['no']
      );
      $this->isInstalled = false;
    }
  }

  /*
   * install symbolic links
   * @return void
   * @access private
   */
  private function installsymLinks() {
    global $camyks;

    /* do not install sym links in "dedicated" installation mode */
    if ( $camyks->_installationMode == 'dedicated' )
      return;

    /* build symLinks */
    foreach ( $this->symLinks as $f => $l ) {
      $message = array(
        'type'  => 'message',
        'name'  => $this->get_translation('symlink_x_created', $l),
      );

      /* check if link already exists */
      if (file_exists(realpath('./'.$l)))
        continue;

      /* create link */
      shell_ln ( $camyks->site_conf['engine_path'].'/'.$f, realpath('.').'/'.$l);

      /* check it has correctly be created */
      if (file_exists( realpath('./'.$l ))) {
        $message['value'] = $camyks->get_translation('yes');
        $message['color'] = $this->textColors['yes'];
        $this->summary[] = $message;
      } else {
        $message['value'] = $camyks->get_translation('no');
        $message['color'] = $this->textColors['no'];
        $this->summary[] = $message;
        $this->isInstalled = false;
        return;
      }
    }
  }

  /*
   * install plugins
   * @return void
   * @access private
   */
  private function installPlugins() {
    global $camyks;

    $message = array(
      'type'    => 'message',
      'name'    => $this->get_translation('module_x_installed', 'Admin_PluginManager'),
    );

    /* first, try to install plugin manager plugin */
    if ($camyks->modules['Admin_PluginManager']->install()) {
      $message['value'] = $camyks->get_translation('yes');
      $message['color'] = $this->textColors['yes'];
      $this->summary[] = $message;
      /* remove plugin manager from needed modules list */
      unset($camyks->neededModules['Admin_PluginManager']);

      /* install needed modules */
      foreach ($camyks->neededModules as $p) {
        $message = array(
          'type'=>'message',
          'name'=>$this->get_translation('module_x_installed', $p['name']),
        );
        if ($camyks->modules['Admin_PluginManager']->install_plugin($p['name'], 'module', false, 1)) {
          $message['value'] = $camyks->get_translation('yes');
          $message['color'] = $this->textColors['yes'];
          $this->summary[] = $message;
        } else {
          $message['value'] = $camyks->get_translation('no');
          $message['color'] = $this->textColors['no'];
          $this->summary[] = $message;
          $this->isInstalled = false;
          return;
        }
      }

      /* install needed inputs */
      foreach ($camyks->neededInputs as $p) {
        $message = array(
          'type'    => 'message',
          'name'    => $this->get_translation('input_x_installed', $p['name']),
        );

        if ($camyks->modules['Admin_PluginManager']->install_plugin($p['name'], 'input', false, 1)) {
          $message['value'] = $camyks->get_translation('yes');
          $message['color'] = $this->textColors['yes'];
          $this->summary[] = $message;
        } else {
          $message['value'] = $camyks->get_translation('no');
          $message['color'] = $this->textColors['no'];
          $this->summary[] = $message;
          $this->isInstalled = false;
          return;
        }
      }

      /* install needed themes */
      foreach ($camyks->neededThemes as $p) {
        $message = array(
          'type'    => 'message',
          'name'    => $this->get_translation('theme_x_installed', $p['name']),
        );

        if ($camyks->modules['Admin_PluginManager']->install_plugin($p['name'], 'theme', false, 1)) {
          $message['value'] = $camyks->get_translation('yes');
          $message['color'] = $this->textColors['yes'];
          $this->summary[] = $message;
        } else {
          $message['value'] = $camyks->get_translation('no');
          $message['color'] = $this->textColors['no'];
          $this->summary[] = $message;
          $this->isInstalled = false;
          return;
        }
      }

      /* install needed templates */
      foreach ($camyks->neededTemplates as $p) {
        $message = array(
          'type'    => 'message',
          'name'    => $this->get_translation('template_x_installed', $p['name']),
        );

        if ( $camyks->modules['Admin_PluginManager']->install_plugin($p['name'], 'template', false, 1) ) {
          $message['value'] = $camyks->get_translation('yes');
          $message['color'] = $this->textColors['yes'];
          $this->summary[] = $message;
        } else {
          $message['value'] = $camyks->get_translation('no');
          $message['color'] = $this->textColors['no'];
          $this->summary[] = $message;
          $this->isInstalled = false;
          return;
        }
      }
    } else {
      $message['value'] = $camyks->get_translation('no');
      $message['color'] = $this->textColors['no'];
      $this->summary[] = $message;
      $this->isInstalled = false;
    }
  }

  /*
   * finalise installation
   * @return boolean success
   * @access private
   */
  private function installDone() {
    global $camyks;

    /* update camyks version in conf file */
    $camyks->site_conf['cms_version'] = $camyks->version;

    /* add 'installed' value to the conf file */
    $camyks->site_conf['installed'] = 1;

    $content = file_getPHPFileHeader('site configuration file', '1.0');
    $content .= '$conf = ' . var_export($camyks->site_conf, true) . ';';
    $content .= file_getPHPFileFooter();

    /* write configuration file */
    if (!file_write(realpath('./etc/site.php.inc'), $content)) {
      $message = array(
        'type'  => 'message',
        'name'  => $this->get_translation('installation_done'),
        'value' => $camyks->get_translation('no'),
        'color' => $this->textColors['no'],
      );
      $this->summary[] = $message;
      $message = array(
        'type'  => 'detail',
        'name'  => $this->get_translation('installation_error_cantwriteconfigfile'),
        'value' => '',
        'color' => $this->textColors['no'],
      );
      $this->summary[] = $message;

      return false;
    }

    /* add installation successfull message line */
    $message = array(
        'type'  => 'message',
        'name'  => $this->get_translation('installation_done'),
        'value' => $camyks->get_translation('yes'),
        'color' => $this->textColors['yes'],
    );
    $this->summary[] = $message;

    /* remove config from session */
    $this->params->delete_fromSession('InstallerConfig');

    /* add site admin link button */
    $this->buttons = array(array(
        'title' => $this->get_translation('open_admin'),
        'link'  => $camyks->get_adminLink(),
    ));

    /* return success */
    return true;
  }
}
?>
