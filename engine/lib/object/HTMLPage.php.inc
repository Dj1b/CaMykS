<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	    : Engine / Object Lib
 * Creation Date	: Jun 2005
 * Last Modif Date	: Mar 2007
 *
 * HTMLPage object
 * Used to build the html page for admin and visit page.
 * Build xhtml1-transitional pages
*/

final class HTMLPage {  
  /* current page content */
  private $content;

  /* header doctype */
  private $doctype;

  /* redirect values */
  private $redirect_time;
  private $redirect_url;

  /* cache control */
  private $disable_cache;

  /* header titles */
  private $site_title;
  public $page_title;

  /* header metas */
  private $charset;
  private $metas;
  private $rss;
  private $robots_index;
  private $robots_follow;
 
  /* header language */
  private $language;
  
  /* included javascript files */
  private $js_files;
  /* included javascript scripts */
  private $js_scripts;
  /* included javascript scripts, added before files importation */
  private $js_pre_scripts;
  
  /* included style files */
  private $style_files;
  /* included style scripts */
  private $style_scripts;
  /* included style files as script */
  private $style_included_files;
  
  /* header extra */
  private $header_extras;

  /* header favicon */
  private $favicon;
  
  /* onload attributes */
  private $js_event_scripts;

  /* 
   * HTMLPage object constructor
   * @return void
   * @access public
   */
  public function __construct(){
    global $camyks;
    
    /* load HTML version to display */
    $this->htmlVersion = $camyks->get_confValue('html_version', 4);

    if ($this->htmlVersion == 5) {
      $this->doctype = '<!DOCTYPE html>';
    } else {
      $this->doctype = '<!DOCTYPE html  PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">';
    }
    /* initialise object variables */
    $this->redirect_time = 0;
    $this->redirect_url = '';
    $this->site_title = '';
    $this->page_title = '';
    $this->favicon = '';
    $this->disable_cache = true;
    $this->robots_index = true;
    $this->robots_follow = true;
    $this->charset = "UTF-8";
    $this->metas = array();
    $this->links = array();
    $this->js_pre_scripts = array();
    $this->js_files = array();
    $this->js_scripts = array();
    $this->js_event_scripts = array();
    $this->style_files = array();
    $this->style_scripts = array();
    $this->style_included_files = array();
    $this->header_extras = '';
    $this->content = '';
    $this->google_analytics = array('code'=>'', 'domain'=>'auto');
    
    /* add compatibility tag */
    if ($camyks->get_confValue('html_compatibilityTag') != false)
      $this->add_meta('X-UA-Compatible', $camyks->get_confValue('html_compatibilityTag'), 'http-equiv');

    /* add mandatory metas */
    $this->add_meta('Content-Type', 'text/html; charset='.$this->charset.'', 'http-equiv');

    /* add other meta case of HTML version */
    if ($this->htmlVersion == 4) {
      if ( $this->disable_cache ) {
        $this->add_meta('Expires', '0', 'http-equiv');
        $this->add_meta('Pragma', 'no-cache', 'http-equiv');
      }
      $this->add_meta('Content-Style-Type', 'text/css', 'http-equiv' );
      $this->add_meta('Content-Script-Type', 'text/javascript', 'http-equiv');
    } elseif ($this->htmlVersion == 5) {
       $this->add_meta('viewport', 'width=device-width, user-scalable=1', 'name');
    }
    $this->add_meta('generator', $camyks->name.' '.$camyks->version);
  }
  
  /*********** INPUT METHODS **************/
  
  /* 
   * set site informations
   * @param string $site_title the website title
   * @param string $site_author the website developer
   * @param string $site_company the website developer company
   * @return void
   * @access public
   */
  public function set_siteInformations($site_title, $site_author='') {
    $this->site_title = $site_title;
    if ($site_author != '') 
      $this->add_meta('author',  $site_author);
  }
  
  /*
   * set page informations
   * @param string $page_title the webpage title
   * @param string $page_desc the webpage description meta
   * @param string $page_keys the webpage keywords meta
   * @param string $page_lang the webpage language displayed
   * @return void
   * @access public
   */
  public function set_pageInformations($page_title, $page_desc='', $page_keys='', $page_lang='') {
    $this->page_title = $page_title;
    $this->language = $page_lang;
    if ( $page_keys != '' )
      $this->add_meta('keywords',  $page_keys);
    if ( $page_desc != '' )
      $this->add_meta('description', $page_desc);
    if ( $page_lang != '' and $this->htmlVersion == 4)
      $this->add_meta('Content-Language', $page_lang, 'http-equiv');
  }
  
  /* 
   * set robots information for the page
   * @param boolean $index the index value
   * @param boolean $follow the $follow value
   * @return void
   * @access public
   */
  public function set_robotInformations($index=true, $follow=true) {
    $this->robots_index = $index;
    $this->robots_follow = $follow;
    $this->add_meta('robots', ($this->robots_index?'':'no').'index,'.($this->robots_follow?'':'no').'follow');
  }

  /* 
   * set google information
   * @param string $code the google code value
   * @return void
   * @access public
   */
  public function set_googleInformations($code='', $domain='') {
    if ($code != '')
      $this->google_analytics['code'] = $code;
    if ($domain != '') 
      $this->google_analytics['code'] = $domain;
  }
  
  /* 
   * set site favicon
   * @param string $fav the favicon file name
   * @return void
   * @access public
   */
  public function set_favicon($fav=null) {
  	global $camyks;
  	$root = $camyks->get_rootBaseURL('absolute_long');
    if ( isset( $fav ) and file_exists($fav) ) {
      $this->add_link('icon', $root.$fav);
    } else if ( count($f = glob('favicon.*'))>0 ) {
      $this->add_link('icon', $root.basename($f[0]));
    }
  }
  
  /* 
   * set site charset
   * @param string $charset
   * @return void
   * @access public
   */
  public function set_charset($charset='') {
    if ($charset != '' and $this->charset != $charset) {
      $this->charset = $charset;
      $this->add_meta('Content-Type', 'text/html; charset='.$this->charset.'', 'http-equiv');
    }
  }
  
  /* 
   * add a meta to the current list
   * @param string $key the meta name
   * @param string $value the meta value
   * @param string $method the meta displaying method
   * @return void
   * @access public
   */
  public function add_meta($key, $value, $method='name') {
    if ($method == 'link:rel')
      return $this->add_link($key, $value);
    $this->metas[$key] = array('value'=>$value, 'method'=>$method);
  }
  
  /*
   * add a link to the current list
   * @param string $rel the rel value
   * @param string $href the href value
   * @param array $params the other params
   * @return void
   * @access public
   */
  public function add_link($rel, $href, $params=array()) {
    if ($rel == '')
      $this->links[] = array_merge($params, array('href'=>$href));
    else
      $this->links[] = array_merge(array('rel'=>$rel, 'href'=>$href), $params);
  }
  
  /*
   * add js file to the current list
   * @param string $file the file path & name
   * @return void
   * @access public 
   */
  public function add_JSFile($file='') {
    if ($file != '' and !in_array($file, $this->js_files))
      $this->js_files[] = $file;
  }
  
  /*
   * add js script to the current list
   * @param string $script the script to add
   * @param boolean $unique tell if this script must be unique
   * @return void
   * @access public
   */
  public function add_JSScript( $script='', $unique=false ) {
    if ( $script=='' or ($unique and in_array($script, $this->js_scripts)))
      return;
    $this->js_scripts[] = $script;
  }
  
  /* 
   * add js pre script to the current list
   * @param string $script the script to add
   * @param boolean $unique tell if this script must be unique
   * @return void
   * @access public
   */
  public function add_JSPreScript( $script='', $unique=false ) {
    if ($script=='' or ($unique and in_array($script, $this->js_pre_scripts)))
      return;
    $this->js_pre_scripts[] = $script;
  }
  
  /*
   * add script to window event script list
   * @param string $event
   * @param string $script
   * @param boolean $unique
   * @return void
   * @access public
   */
   
  public function add_JSWindowEventScript($event, $script, $unique=false) {
    /* check empty script */
    if ($script == '')
      return;
      
    /* check event */
    if (substr($event, 0, 2) == 'on')
      $event = substr($event, 2);
      
    /* check event list */
    if (!isset($this->js_event_scripts[$event]))
      $this->js_event_scripts[$event] = array();
    
    /* check unique script */
    if ($unique and in_array($script, $this->js_event_scripts[$event]))
      return;
      
    /* add script to list */
    $this->js_event_scripts[$event][] = $script;
  }
  
  /* 
   * add onload window event js script to the current list
   * @param string $script the script to add
   * @param boolean $unique tell if this script must be unique
   * @return void
   * @access public
   */
  public function add_JSloadScript($script='', $unique=false) {
    return $this->add_JSWindowEventScript('load', $script, $unique);
  }

  /*
   * add onunload window event js script to the current list
   * @param string $script the script to add
   * @param boolean $unique tell if this script must be unique
   * @return void
   * @access public
   */
  public function add_JSunloadScript($script='', $unique=false) {
    return $this->add_JSWindowEventScript('unload', $script, $unique);
  }
  
  /*
   * add css file to the current list
   * @param string $file the file path & name
   * @param string $media the media which the style will be displayed 
   * @return void
   * @access public
   */
  public function add_styleFile($file='', $media='', $condition='') {  
    $file = trim($file);
    if ($file == '')
      return;
    if (!isset($this->style_files[$media]))
      $this->style_files[$media] = array();
    $this->style_files[$media][] = array('file'=>$file, 'condition'=>$condition);
  }

  /*
   * add directly included css script
   * @param string $css the style script to add
   * @return void
   * @access public
   */
  public function add_styleScript($css='') {
    if ($css != '')
      $this->style_scripts[] = $css;
  }

  /* 
   * add css file to the current list
   * @param string $file the file path & name
   * @return void
   * @access public
   */
  public function add_styleIncludedFile($file='') {
    if ($file != '') 
      $this->style_included_files[] = $file;
  }
  
  /*
   * add extra content to header
   * @param string $content
   * @return void
   * @access public
   */
  public function add_headerExtra($content='') {
    $this->header_extras .= $content."\n";
  }

  /*
   * DEPRECATED : use add_RSSFeed instead
   * @param string $url the rss url
   * @param string $title the rss title
   * @return void
   * @access public
   */
  public function set_RSSFeed($url='', $title='') {
    $this->add_RSSFeed($url, $title);
  }
  
  /*
   * add RSS feed to web page
   * @param string $url the feed URL
   * @param string $title the feed title
   * @return void
   * @access public
   */
  public function add_RSSFeed($url='', $title='') {
    $this->add_link('alternate', $url, array('title'=>$title, 'type'=>'application/rss+xml'));
  }

  /* 
   * set a http redirection
   * @param int $time the time before redirection in second
   * @param string $url the target url
   * @return void
   * @access public
   */
  public function set_redirect($time, $url) {
    $this->redirect_time = $time;
    $this->redirect_url = $url;
    $this->add_meta('Refresh', $time.';url='.$url, 'http-equiv');
  }

  /*
   * set mobile metas
   * @param boolean $enabled
   * @param array $config
   * @return void
   * @access public
   */
  public function set_mobileMeta($enabled=false, $config=array()) {
    if ($enabled == false)
      return;

    /* set default config */
    $defaultConfig = array('width'=>'device-width',
			   'initial-scale'=>'1.0',
			   'maximum-scale'=>'1.0',
			   'user-scalable'=>0);

    /* check config */
    if ($config == false)
      $config = $defaultConfig;
    else
      $config = array_merge($defaultConfig, $config);

    /* build config value */
    $value = array();
    foreach($config as $c=>$v)
      $value[] = $c.'='.$v;
    $value = implode(', ', $value);

    /* set meta */
    $this->add_meta('viewport', $value, 'name');
    
    /* update doctype */
    if ( $this->htmlVersion != 5 )
      $this->doctype = '<!DOCTYPE html PUBLIC "-//WAPFORUM//DTD XHTML Mobile 1.2//EN" "http://www.openmobilealliance.org/tech/DTD/xhtml-mobile12.dtd">';
  }
  
  /*********** OUTPUT PAGE METHODS *************/
  
  /* 
   * display builded content and re-init actual content
   * @param string $buffer the content to output
   * @return void
   * @access public
   */
  public function write_HTMLContent($buffer = '') {
    echo $this->content.$buffer;
    $this->content = '';
  }
  
  /*
   * alias for write_HTMLContent method
   * @param string $buffer the content to output
   * @return void
   * @access public
   */
  public function flush($buffer = '') {
    $this->write_HTMLContent($buffer);
  }

  /*
   * update content with given html content
   * @param string $content
   * @return void
   * @access public
   */
  public function add_HTMLContent($content='') {
    $this->content .= $content;
  }
  
  /*
   * display built content updated with buffer value, then add a file content
   * @param string $file the file path & name
   * @param string $buffer the content to add
   * @return string
   * @access public
   */
  public function write_HTMLFile($file='', $buffer='') {
    if (file_exists($file)) {
      $this->add_HTMLContent($buffer);
      $this->write_HTMLContent();
      require($file);
      return '';
    }
    return $buffer;
  }

  /* 
   * write html page header
   * @return void
   * @access public
   */
  public function add_HTMLHeader() {
    $this->get_doctype();
    $this->get_htmlHeader();
    $this->get_title();
    $this->get_metas();
    $this->get_links();
    $this->get_JSPreScripts();
    $this->get_JSFiles();
    $this->get_JSScripts();
    $this->get_styleFiles();
    $this->get_styleScripts();
    $this->get_headerExtras();
    $this->get_body();
  }
  
  /*
   * write html page footer
   * @return void
   * @access public 
   */
  public function add_HTMLFooter() {
    echo "</body>\n";
    echo "</html>\n";
  }
   
  /*********** OUTPUT PAGE PARTS METHODS *************/

  /*
   * write page doctype
   * @return void
   * @access public
   */
  public function get_doctype() {
    echo $this->doctype."\n";
  }
  
  /*
   * write page html header
   * @return void
   * @access public
   */
  public function get_htmlHeader() {
    global $camyks;
    if ($this->language != "" and $this->htmlVersion == 4)
      echo '<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="'.$this->language.'" lang="'.$this->language.'">'."\n".'<head>';
    elseif ($this->language == '')
      echo "<html>\n<head>\n";
    else
      echo "<html lang=\"".$this->language."\">\n<head>\n";
    
    /* add base url for modern urls */
    if ($camyks->get_confValue('friendlyurls') == 'modern')
      echo "<base href=\"".$camyks->get_rootBaseURL('absolute_long')."\" />\n";
  }
  
  /*
   * write page title
   * @return void
   * @access public
   */
  public function get_title() {
    global $camyks;
    
    /* prepare title */
    $t = array();
    
    if (!isset($camyks->contentPage) or $camyks->contentPage->homepage == 1) {
      /* display site title first on home page, then page title */
      if ($this->site_title != "") $t[] = $this->site_title;
      if ($this->page_title != "") $t[] = $this->page_title;
    } else {
      /* display page title first on other pages, then site title */
      if ($this->page_title != "") $t[] = $this->page_title;
      if ($this->site_title != "") $t[] = $this->site_title;
    }
    $str = "<title>";
    $str .= implode(' - ', $t);
    $str .= "</title>\n";
    echo $str;
  }
  
  /*
   * write all metas
   * @return void
   * @access public
   */
  public function get_metas() {      
    foreach ($this->metas as $key => $meta) {
      echo "<meta ".$meta['method']."=\"".$key."\" content=\"".preg_replace('/"/', '\'', $meta['value'])."\" />\n";
    } 
  }
  
  /*
   * write all links
   * @return void
   * @access public
   */
  public function get_links() {      
    foreach ( $this->links as $link ) {
      echo '<link';
      foreach ($link as $key => $value)
        echo ' '.$key.'="'.$value.'"';
      echo ' />'."\n";
    } 
  }
    
  /*
   * write javascript files links
   * @return void
   * @access public
   */
  public function get_JSFiles() {
    global $camyks;
    
    $t = ($this->htmlVersion > 4 ? '' : ' type=\"text/javascript\"');
        
    /* check for server side caches */
    if ($camyks->mode == CAMYKS_MODE_SITE and $camyks->get_confValue('cache_server_side') == 'enabled' and count($this->js_files)>1) {
      $str = '';
      $cachedJS = array();
      foreach ($this->js_files as $idx => $js) {
        $f = new FSFile($js);
        if (preg_match('/http?s:\/\//', $js)) 
          continue;
        
        $cachedJS[] = $js;
        unset($this->js_files[$idx]);
        $str .= $f->filename.'-'.$f->md5().'/';
      }
      
      $checksum = md5($str);
      $masterScript = $camyks->site_var_path.'/ServerCache/scripts/script-'.count($cachedJS).'-'.$checksum.'.js';
      
      if (!file_exists($masterScript)) {
        folder_completePath ($camyks->site_var_path.'/ServerCache/scripts');
        $mf = fopen($masterScript, 'a+');
        foreach ($cachedJS as $js) {
          $content = file_get_contents($js);
          $content = preg_replace('/(\r\n){1,}/', "\n", $content);
          fwrite($mf, $content."\n\n");
        }
        fclose($mf);
      }
      echo "<script type=\"text/javascript\" src=\"".$camyks->get_fileURL($masterScript)."\">/* add javascript */</script>\n";
    }
    
    /* check for client side cache */
    if ($camyks->get_confValue('cache_client_side') == 'disabled')
      $r = '?'.rand(0, 999999);
    else
      $r = '';
    
    /* add files */
    foreach ($this->js_files as $js ) {
      if (preg_match('/https?:\/\//i', $js))
        echo "<script type=\"text/javascript\" src=\"".$js.$r."\">/* add javascript */</script>\n";
      else
        echo "<script type=\"text/javascript\" src=\"".$camyks->get_fileURL($js).$r."\">/* add javascript */</script>\n";
    }
  }

  /*
   * write pre javascript scripts 
   * @return void
   * @access public
   */
  public function get_JSPreScripts() {
    /* check for pre-scripts to write */
    if (count ($this->js_pre_scripts) == 0)
      return;
      
    /* add scripts */
    $str = "<script type=\"text/javascript\">\n";
    foreach ($this->js_pre_scripts as $script) {
      $str .= "\t".$script."\n";
    }
    $str .= "</script>\n";
    echo $str;
  }    

  
  /* 
   * write javascript scripts
   * @return void
   * @access public
   */
  public function get_JSScripts() {
    /* check for scripts to write */
    if ( count ( $this->js_scripts ) == 0 
	 and count ( $this->js_event_scripts ) == 0
	 and $this->google_analytics['code'] == '' )
      return;

    /* add main scripts */
    $str = "<script type=\"text/javascript\">\n";
    foreach ( $this->js_scripts as $script ) {
      $str .= "\t".$script."\n";
    }
    
    /* add window event scripts */
    foreach ($this->js_event_scripts as $event => $scripts) {
      if ( count ( $scripts ) > 0 ) {
        $str .= "\n\t".'/* on '.$event.' scripts */' . "\n";
        $str .= "\t".'window.on'.$event.' = function() {'."\n";
        foreach ( $scripts as $fx  ) {
	        $str .= "\t\t".$fx."\n";
        }
        $str .= "\t".'}'."\n";
      }
    }
    /* close script section */
    $str .= "</script>\n";
    echo $str;
  }
  
  /*
   * write style files
   * @return void
   * @access public
   */
  public function get_styleFiles() {
    global $camyks;
    
    /* check for server side caches */
    if ($camyks->mode == CAMYKS_MODE_SITE and $camyks->get_confValue('cache_server_side') == 'enabled') {
      $allfiles = array();
      foreach ( $this->style_files as $media => $files ) {
        if (count($files) <= 1)
          continue;
          
        $str = '';
        $cachedCSS = array();
        foreach ($files as $idx => $fInfo) {
          $f = new FSFile($fInfo['file']);
          if ($fInfo['condition'] != '' or preg_match('/https?:\/\//', $fInfo['file'])) {
            continue;
          }
          
          $cachedCSS[] = $fInfo;
          unset($this->style_files[$media][$idx]);
          $str .= $f->filename.'-'.$f->md5().'/';
        }
        
        $checksum = md5($str);
        $masterStyles = $camyks->site_var_path.'/ServerCache/styles/style-'.count($cachedCSS).'-'.$checksum.'.css';
      
        if (!file_exists($masterStyles)) {
          folder_completePath ($camyks->site_var_path.'/ServerCache/styles');
          $mf = fopen($masterStyles, 'a+');
          foreach ($cachedCSS as $f) {
            $file= new FSFile($f['file']);
            $p = $file->path;
            
            $content = file_get_contents($f['file']);
            $content = preg_replace('/url\(/i', 'url(../../../'.$p.'/', $content);
            $content = preg_replace('/(\r\n){1,}/', "\n", $content);
            
            fwrite($mf, $content."\n\n");
          }
          fclose($mf);
        }

        if ($media == '')
	      echo '<link href="'.$camyks->get_fileURL($masterStyles).'" type="text/css" rel="stylesheet" />'."\n";
	    else
	      echo '<link href="'.$camyks->get_fileURL($masterStyles).'" media="'.$media.'" type="text/css" rel="stylesheet" />'."\n";
      }
    }
    
    /* check for client side caches */
    if ($camyks->get_confValue('cache_client_side') == 'disabled')
      $r = '?'.rand(0, 999999);
    else
      $r = '';
        
    /* add specific styles */
    foreach ($this->style_files as $media => $files) {
        
      foreach ($files as $file) {      
        /* check for condition */
        if ($file['condition'] != '') 
          echo '<!--[if '.$file['condition'].']>'."\n";
        
        /* add files */
	    if ($media == '')
	      echo '<link href="'.$camyks->get_fileURL($file['file']).$r.'" type="text/css" rel="stylesheet" />'."\n";
	    else
	      echo '<link href="'.$camyks->get_fileURL($file['file']).$r.'" media="'.$media.'" type="text/css" rel="stylesheet" />'."\n";
	    
	    /* end condition */
	    if ($file['condition'] != '') 
  	      echo '<![endif]-->'."\n";
      }
    }
  }

  /*
   * write style scripts 
   * @return void
   * @access public 
   */
  public function get_styleScripts() {
    /* check for scripts to write */
    if (count($this->style_scripts) == 0 and count ($this->style_included_files) == 0) {
      return;
    }
    /* write styles */
    echo '<style type="text/css">'."\n";
    foreach ($this->style_included_files as $s) {
      if ( file_exists( $s ) )
	    require($s);
    }
    $str = '';
    foreach ($this->style_scripts as $s) {
      $str .= $s ."\n\n";
    }
    $str .= '</style>'."\n";
    echo $str;
  }
  
  /*
   * write extra header data
   * @return void
   * @access public
   */
  public function get_headerExtras() {
    echo $this->header_extras;
  }
  
  /*
   * write body header
   * @return void
   * @access public
   */
  public function get_body ( ) {
    echo "</head>\n<body>\n";
    if ( $this->google_analytics['code'] != '' ) {
      /* add google analytics */
      $str = "<script>\n";
  	  $str .= "\t(function(i,s,o,g,r,a,m){i['GoogleAnalyticsObject']=r;i[r]=i[r]||function(){\n";
      $str .= "\t(i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),\n";
      $str .= "\tm=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)\n";
      $str .= "\t})(window,document,'script','//www.google-analytics.com/analytics.js','ga');\n";
      $str .= "\tga('create', '".$this->google_analytics['code']."', '".$this->google_analytics['domain']."');\n";
      $str .= "\tga('send', 'pageview');\n";
      $str .= "</script>\n";
      echo ($str);
	}
  }
}
?>