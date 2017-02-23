<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Input Engine
 * Creation Date    : Nov 2014
 * Last Modif Date	: Nov 2014
 * History : 
 * * 14-11-21 : Initial File
 * 
 * Generic vCard handler : import and export vCard
 */

class GenericVCardHandler extends Input {
  /* variables */
  var $items;
  var $config;

  /*
   * constructor
   * @param string $path_type
   */
  function GenericVCardHandler ( $path_type ) {
    parent::Input('GenericVCardHandler', $path_type);
    /* set plugin version */ 
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Generic';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    $this->loadedObjects = array();
    $this->pluginError = '';
  }
  
  /* overwrite input methods */

  /*
   * initialise input
   * @param array $params
   * @return boolean result
   * @access public
   */
  function initialise($params=array()) {
    global $camyks;
    
    /* check for vCard importation */
    if (isset($params['action']) and $params['action'] == 'import')
      return $this->import_vCard($params);
      
    /* check for vCard exportation */
    if (isset($params['action']) and $params['action'] == 'export')
      return $this->export_vCard($params);
    
    /* no known action found: throw fatal error */
    $camyks->throwFatalError(array('title'=>$this->get_translation('fatalerrortitle'),
		   'description'=>$this->get_translation('fatalerrordesc'),
		   'content1'=>$this->get_translation('fatalerror_noknownaction', $params['action']),
		   'content2'=>$this->get_translation('fatalerrorgenendig'))); 	  
  }
  
  /* specific action methods */
  
  /*
   * export vCard
   * @param array $params
   * @return mixed
   * @access public
   */
  function export_vCard($params) {
    global $camyks;
    
    /* check and merge params */
    $params = array_merge($this->get_exportDefaultParams(), $this->get_vCardDefaultParams(), $params);
    
    /* get vCard content following version */
    switch ($params['version']) {
      case '2.1':
        if ( $this->load_vCardObject('vCard21') ) {
          $vCard = new GenericVCardHandler_vCard21($this, $params);
          $cardContent = $vCard->export_vCard();
        } else {
          $cardContent = false;
          $this->define_pluginError('loadingfailed', $params['version']);
        }
        break;
      case '3.0':
        if ( $this->load_vCardObject('vCard30') ) {
          $vCard = new GenericVCardHandler_vCard30($this, $params);
          $cardContent = $vCard->export_vCard();
        } else {
          $cardContent = false;
          $this->define_pluginError('loadingfailed', $params['version']);
        }
        break;
      case '4.0':
      case 'xCard':
      case 'jCard':
      case 'hCard':
        $cardContent = '';
        break;
      default:
        $cardContent = false;
        $this->define_pluginError('loadingfailed', $params['version']);
        break;
    }
    
    /* output vCard */
    switch ($params['output']) {
      case 'void': return;
      case 'text': return $cardContent;
      case 'file': return ($cardContent and file_write($params['target'], $cardContent));
      case 'download':
        if ( $cardContent === false) {
          $camyks->throwFatalError(array('title'=>$this->get_translation('fatalerror_title'),
		   'description'=>$this->get_translation('fatalerror_desc'),
		   'content1'=>$this->pluginError,
		   'content2'=>$this->get_translation('fatalerror_genendig')));
		}
        header('Content-Type: text/vcard; charset=utf-8');
        header('Content-Disposition: attachment; filename="'.$this->encode_cardTitle($vCard->get_cardTitle()).'"');
        header('Pragma: no-cache');
        echo $cardContent;
        $camyks->init_kill();
    }
    return false;
  }
  
  /*
   * import vCard
   * @param array $params
   * @return mixed
   * @access public
   */
  function import_vCard($params) {
    $params = array_merge($this->get_importDefaultParams(), $params);
    
    /* get vCard content */
    switch (strtolower($params['input'])) {
      case 'file':
      case 'url':
        $content = readfile($params['source']);
        break;
      case 'text':
        $content = $params['source'];
        break;
      default : 
        $this->define_pluginError('cardreadingfailed');
        return false;
    }
    
    /* get vCard version */
    if (($version = $this->check_vCardVersion($content)) === false) {
      $this->define_pluginError('cannotdetectvcardversion');
      return false;
    }
    
    /* parse vCard content following found version */
    switch ($version) {
      case '2.1':
        if ( $this->load_vCardObject('vCard21') ) {
          $vCard = new GenericVCardHandler_vCard21($this, $content);
          return $vCard->import_vCard();
        }
      case '3.0':
      case '4.0':
      case 'xCard':
      case 'jCard':
      case 'hCard':
        break;
    }
    $this->define_pluginError('cannotdetectvcardversion');
    return false;
  }
  
  /* specific public tool methods */
  
  /*
   * return vCard available version 
   * @return array
   * @access public
   */
  function get_vCardAvailableVersions() {
    return array(
        '2.1' => 'vCard 2.1',
        '3.0' => 'vCard 3.0',
    );
  }
  
  /*
   * return vCard default params
   * @return array
   * @access public
   */
  function get_vCardDefaultParams() {
    return array(
      /* vCard structure */
      'version'=>'4.0',
      'kind'=>'individual', // group / org / location
      'source'=>'',
      
      /* data */
      'full_name'=>'',
      'name_last'=>'',
      'name_first'=>'',
      'name_additional'=>'',
      'name_prefix'=>'',
      'name_suffix'=>'',
      'nickname'=>'',
      'photo_mode'=>'URL', // URL / Data
      'photo_url'=>'',  // Accepted types : GIF, CGM, WMF, BMP, MET, PMB, DIB, PICT, TIFF, PS, PDF, JPEG, MPEG, MPEG2, AVI, QTIME
      'birthdate'=>'',
      'gender'=>'', // M => "male", F => "female", O => "other", N => "none or not applicable", U => "unknown".
      'gender_more'=>'',
      'addr_location'=>'', // DOM => Domestic, INTL => International, POSTAL, PARCEL, HOME, WORK
      'addr_pobox'=>'', // Post office box
      'addr_extended'=>'', // Extended address: building, stair, apartment or suite number
      'addr_street'=>'', // Street address
      'addr_city'=>'',
      'addr_zipcode'=>'',
      'addr_region'=>'', // State or province
      'addr_country'=>'',
      'addr_label'=>'',
      'phones'=>array(),
      'phone_type'=>'voice', // "text" / "voice" / "fax" / "cell" / "video" / "pager" / "textphone" / "msg" / "modem" / "car" / "isdn"
      'phone_number'=>'',
      'phone_location'=>'', // home / work
      'phone_pref'=>'', 
      'emails'=>array(),
      'email'=> '',
      'email_location'=>'', // home / work
      'email_pref'=>'',
      'impps'=>array(),
      'impp_protocol'=>'',
      'impp_type'=>'', // home / work
      'impp_pref'=>'',
      'impp'=>'',
      'langs'=>array(),
      'lang'=>'',
      'lang_type'=>'', // home / work
      'lang_pref'=>'',
      'geo_latitude'=>'',
      'geo_longitude'=>'',
      'title'=>'',
      'role'=>'',
      'logo_mode'=>'URL',
      'logo_url'=>'',
      'org_title'=>'',
      'org_unit'=>'',
      'members'=>array(),
      'member'=>'', 
      'relateds'=> array(),
      'related_type'=>'', // "contact" / "acquaintance" / "friend" / "met" / "co-worker" / "colleague" / "co-resident" / "neighbor" / "child" / "parent" / "sibling" / "spouse" / "kin" / "muse" / "crush" / "date" / "sweetheart" / "me" / "agent" / "emergency"
      'related_value'=>'',
      'categories'=>array(),
      'url'=>'',
      'note'=>'',
    );
  }
  
  /* specific prive tool methods */
  
  /*
   * return export action params
   * @return array
   * @access private
   */
  function get_exportDefaultParams() {
    return array('output' => 'void', // void / text / file / download
        'target' => ''); 
  }

  /*
   * return import action params
   * @return array
   * @access private
   */
  function get_importDefaultParams() {
    return array('input' => '', //  void / text / file / url 
        'source' => '');
  }
  
  /*
   * load vCard object
   * @param string $version
   * @return void
   * @access private
   */
  function load_vCardObject($version='') {
    /* check if object is already loaded */
    if (isset($this->loadedObjects[$version]))
      return $this->loadedObjects[$version];
    
    /* load object file */
    if ($this->load_file('lib/GenericVCardHandler-'.$version.'.php.inc')) {
      $this->loadedObjects[$version] = true;
      return true;
    }
    $this->loadedObjects[$version] = false;
    return false;
  }
  
  /*
   * return encoded title
   * @param string $title
   * @return string
   * @access private
   */
  function encode_cardTitle($title) {
    $v = trim($title);
    $v = preg_replace('/[^a-zA-Z0-9\-]/', '-', $v);
    return $v.'.vcf';
  }
  
  /*
   * define plugin error
   * @param string $error
   * @param mixed $param
   * @return void
   * @access private
   */
  function define_pluginError($error, $param=null) {
    $this->pluginError = $this->get_translation('fatalerror_'.$error, $param);
  }
  
  /*
   * return plugin error
   * @return string
   * @access public
   */
  function get_pluginError() {
    return $this->pluginError;
  }
}
?>