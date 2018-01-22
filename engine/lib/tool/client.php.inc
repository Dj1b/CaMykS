<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0
 * Object Version	: 1.0
 * Object Type      : Engine / Tool Library
 * Creation Date	: Jun 2007
 * Last Modif Date  : Jan 2018
 *
 * client user methods
 */

/*
 * get client IP address
 * @return string
 * @access public
 */
function client_getIp() {
  if (isset($_SERVER['HTTP_PC_REMOTE_ADDR']))
    return $_SERVER['HTTP_PC_REMOTE_ADDR'];
  return $_SERVER['REMOTE_ADDR'];
}

/*
 * get client user agent
 * @return string
 * @access public
 */
function client_getUserAgent() {
  if (isset($_SERVER['HTTP_USER_AGENT']))
    return $_SERVER['HTTP_USER_AGENT'];
  return '';
}

/*
 * check if page is loaded is HTTPS(SSL)
 * @return boolean result
 * @access public
 */
function client_isHTTPS() {
  return (!empty($_SERVER['HTTPS']));
}

/*
 * get client referer site
 * @return string
 * @access public
 */
function client_getRefererSite() {
  if (isset($_SERVER['HTTP_REFERER']))
    return $_SERVER['HTTP_REFERER'];
  return '';
}

/* 
 * check if server is also client
 * @return boolean result
 * @access public
 */
function client_isServerClient() {
  return ($_SERVER['SERVER_ADDR'] == client_getIp()); 
}

/*                  
 * return client informations                     
 * @param mixte $ua                
 * @return array                  
 * @access public                   
 */
function client_getUAInfos($ua=false) {
  $req = true;
  
  /* get user agent */
  if ($ua===false) $ua = client_getUserAgent();

  /* init result value */
  $infos = array();
  
  /*** check fake visitors */
  if ( ($c = client_getFakeInfosFromUserAgent($ua)) !== false)
    return $c;
  
  /*** check hacks */
  if ( ($c = client_getHackInfosFromUserAgent($ua)) !== false)
    return $c;
    
  /*** check tool */
  if ( ($c = client_getToolInfosFromUserAgent($ua)) !== false)
    return $c;
  
  /*** check bot */
  if ( ($c = client_getBotInfosFromUserAgent($ua)) !== false)
    return $c;
    
  /*** check generic bot/tool */
  if ( ($c = client_getGenericInfosFromUserAgent($ua)) !== false)
    return $c;

  /*** check plateform ***/
  
  /* load max versions to check and default fake value */
  $maxVersions = _client_getUAPropertiesMaxVersions();
  $fake = array('platform_type'=>'fake');

  /* check Playstation 4 / Vita */
  if (preg_match('/\(PlayStation ([^ ]*) ([0-9\.]*)\)/i', $ua, $matches))
  	return _client_mergeUAInfos($req, array('platform_company'=>'Sony', 
      'platform_model'=>'Playstation '.$matches[1],
  	  'platform_type'=>'computer',
  	  'platform_format'=>'desktop',
      'system_title'=>'Playstation '.$matches[1],
      'system_version'=>$matches[2],
      'browser_title'=>'PS '.$matches[1].' Browser',
      'browser_version'=>'--'));

  /* check Playstation 3 */
  if (preg_match('/\(PLAYSTATION 3; ([0-9\.]*)\)$/', $ua, $matches))
  	return _client_mergeUAInfos($req, array('platform_company'=>'Sony', 
  	  'platform_model'=>'Playstation 3',
  	  'platform_type'=>'computer',
      'platform_format'=>'desktop',
      'system_title'=>'Playstation 3',
      'system_version'=>$matches[1],
      'browser_title'=>'PS3 Browser',
      'browser_version'=>'--'));
      
  /* check Playstation Portable */
  if (preg_match('/PSP \(PlayStation Portable\); ([0-9\.]*)\)?$/', $ua, $matches))
  	return _client_mergeUAInfos($req, array('platform_company'=>'Sony', 
      'platform_model'=>'Playstation Portable',
      'platform_type'=>'computer',
      'platform_format'=>'handheld',
      'system_title'=>'Playstation Portable',
      'system_version'=>$matches[1],
      'browser_title'=>'PSP Browser',
      'browser_version'=>'--'));
       
  /* check Black Berry */
  if (preg_match('/BlackBerry([^\/;]{1,})\/([0-9\.]*)/', $ua, $matches))
  	return _client_mergeUAInfos($req, array('platform_company'=>'BlackBerry', 
      'platform_model'=>$matches[1],
      'platform_type'=>'handheld',
      'platform_format'=>'handheld',
      'system_title'=>'BlackBerry OS',
      'system_version'=>$matches[2],
      'browser_title'=>'BB Browser',
      'browser_version'=>'--'));
  if (preg_match('/BlackBerry ([^;]{1,});?.*Version\/([0-9\.]*) /', $ua, $matches))
  	return _client_mergeUAInfos($req, array('platform_company'=>'BlackBerry', 
      'platform_model'=>$matches[1],
      'platform_type'=>'handheld',
      'platform_format'=>'handheld',
      'system_title'=>'BlackBerry OS',
      'system_version'=>$matches[2],
      'browser_title'=>'BB Browser',
      'browser_version'=>'--'));
  if (preg_match('/BB([^\/;]{1,});/', $ua, $matches))
  	return _client_mergeUAInfos($req, array('platform_company'=>'BlackBerry', 
      'platform_model'=>$matches[1],
      'platform_type'=>'handheld',
      'platform_format'=>'handheld',
      'system_title'=>'BlackBerry OS',
      'system_version'=>$matches[1],
      'browser_title'=>'BB Browser',
      'browser_version'=>'--'));
      
  /* check Nokia - before iPhone */
  elseif (preg_match('/RX-51 N900/', $ua, $matches))
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Nokia', 
      'platform_model'=>'N900',
      'platform_type'=>'handheld',
      'platform_format'=>'handheld',
      'system_title'=>'Maemo',
      'system_version'=>5,
      ));
  elseif (preg_match('/Nokia(?: |_|\-|\/|)([^ _\-\/]+)/', $ua, $matches)) {
    $rep = array(
        'X2DS'  => array('platform_model' => 'X2 (Dual Sim)', ),
    );
    
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Nokia', 
      'platform_model'=>$matches[1],
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'), 
      isset($rep[$matches[1]])?$rep[$matches[1]]:array());
  }  
  elseif (preg_match('/Lumia ([a-zA-Z0-9]*)/', $ua, $matches))
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Nokia', 
      'platform_model'=>'Lumia '.$matches[1],
      'platform_type'=>'handheld',
      'platform_format'=>'handheld',));
      
  /* check iphone / ipod / ipad */
  elseif (preg_match('/(iPod|iPhone|iPad);?.*; CPU ([A-Za-z\ ]*)? ([0-9_]*)?.*(Version)\/([0-9\.]*)/', $ua, $matches)) {
    /* check version */
    $version = str_replace('_', '.', $matches[3]);
    if (version_compare($version, $maxVersions['system']['iOS']) > 0)
      return $fake;
      
  	$infos = array_merge($infos, array('platform_company'=>'Apple', 
      'platform_model'=>$matches[1],
      'platform_type'=>$matches[1]=='iPad'? 'tablet': 'handheld',
      'platform_format'=>$matches[1]=='iPad'? 'tablet': 'handheld',
      'system_title'=> 'iOS', //$matches[2],
      'system_version'=>$version,
      'browser_title'=>'Safari Mobile',
      'browser_version'=>$matches[5],
    ));
  } elseif (preg_match('/(iPod|iPhone|iPad);?.*; CPU ([A-Za-z\ ]*)? ([0-9_]*)/', $ua, $matches)) {
    /* check version */
    $version = str_replace('_', '.', $matches[3]);
    if (version_compare($version, $maxVersions['system']['iOS']) > 0)
      return $fake;
    
  	$infos = array_merge($infos, array('platform_company'=>'Apple', 
      'platform_model'=>$matches[1],
      'platform_type'=>$matches[1]=='iPad'? 'tablet': 'handheld',
      'platform_format'=>$matches[1]=='iPad'? 'tablet': 'handheld',
      'system_title'=>'iOS', //$matches[2],
      'system_version'=>$version,
    ));
  } elseif (preg_match('/(iPod|iPhone|iPad)/', $ua, $matches))
  	$infos = array_merge($infos, array('platform_company'=>'Apple', 
      'platform_model'=>$matches[1],
      'platform_type'=>$matches[1]=='iPad'? 'tablet': 'handheld',
      'platform_format'=>$matches[1]=='iPad'? 'tablet': 'handheld',
      'system_title'=>'iOS',
    ));
      
  /* check Google Nexus */
  elseif (preg_match('/(Nexus( [^ \/;]+)?) Build/', $ua, $matches))
  	$infos = array_merge($infos, array('platform_company'=>'Google', 
      'platform_model'=>$matches[1],
      'platform_type'=>'handheld',
      'platform_format'=>'handheld',));
      
  /* check HTC */
  elseif (preg_match('/HTC;([A-Za-z0-9 ]*)/', $ua, $matches))
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'HTC', 
      'platform_model'=>$matches[1],
      'platform_type'=>'handheld',
      'platform_format'=>'handheld',));
  elseif (preg_match('/HTC(?: |_|\-)?([^ _\-\/]+)/', $ua, $matches)) {
  	$rep = array(
  	    'M8Sx'         => array('platform_model' => 'One', ),
  	    'IncredibleS'  => array('platform_model' => 'Incredible S'),
  	    'D820u'        => array('platform_model' => 'Desire 820 Dual SIM'),
  	);
  	
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'HTC', 
      'platform_model'=>((isset($matches[1]) and strlen($matches[1]) > 1)?ucwords(strtolower($matches[1])):''),
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'),
      isset($rep[$matches[1]])?$rep[$matches[1]]:array());
  }
  
  /* check LG */
  elseif (preg_match('/^LG(?:E|)(?: |_|\-|\/)([^ _\-\/]+)/', $ua, $matches))
  	$infos = array_merge($infos, array('platform_company'=>'LG', 
      'platform_model'=>$matches[1],
      'platform_type'=>'handheld',
      'platform_format'=>'handheld',));
      
  elseif (preg_match('/LG-([A-Z][0-9]{3}[A-Z]?)/', $ua, $matches)) {
    $rep = array(
        'E610'  => array('platform_model' => 'Optimus L5',),
        'L160L' => array('platform_model' => 'Optimus LTE2',),
        'D315'  => array('platform_model' => 'F70',),
        'D855'  => array('platform_model' => 'G3',),
        'D722'  => array('platform_model' => 'G3 S',),
        'H815'  => array('platform_model' => 'G4',),
        'H870D'	=> array('platform_model' => 'G6',),
	    'M700'  => array('platform_model' => 'Q6 Alpha',),
        'M160'  => array('platform_model' => 'K4 (2017)',),
    );
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'LG', 
      'platform_model'=>$matches[1],
      'platform_type'=>'handheld'), 
      isset($rep[$matches[1]])?$rep[$matches[1]]:array());
      
  } elseif (preg_match('/LG([A-Z]{1,2}[0-9]*)/', $ua, $matches)) {
    $rep = array(
        'LS996'=>array('platform_model' => 'G Flex 2', ),
    );
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'LG', 
      'platform_model'=>$matches[1],
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'), 
      isset($rep[$matches[1]])?$rep[$matches[1]]:array());
  }
  
  /* check Motorola */
  elseif (preg_match('/mot(?:-|orola |o|\-moto)([^ \/;]+)/i', $ua, $matches))
  	$infos = array_merge($infos, array('platform_company'=>'Motorola', 
      'platform_model'=>$matches[1],
      'platform_type'=>'handheld',
      'platform_format'=>'handheld',));
  elseif (preg_match('/ (Droid|MB200|RAZR HD|Moto G)/', $ua, $matches))
 	$infos = array_merge($infos, array('platform_company'=>'Motorola', 
      'platform_model'=>$matches[1],
      'platform_type'=>'handheld',
      'platform_format'=>'handheld',));
  elseif (preg_match('/XT([0-9]{3,})/', $ua, $matches)) {
    $rep = array('XT720' =>array('platform_model' => 'Milestone XT720', ),
                 'XT1022'=>array('platform_model' => 'Moto E', ),
                 'XT1032'=>array('platform_model' => 'Moto G', ),
                 'XT1039'=>array('platform_model' => 'Moto 4G', ),
                 'XT1072'=>array('platform_model' => 'Moto G 4G (2nd Gen)', ),
                 'XT1092'=>array('platform_model' => 'Moto X (2nd Gen)', ),
    );
 	$infos = array_merge($infos, array('platform_company'=>'Motorola', 
      'platform_model'=>$matches[0],
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'),
      isset($rep[$matches[0]])?$rep[$matches[0]]:array());
  }   
      
  /* check palm */
  elseif (preg_match('/(Pre|Pixi)\/[0-9\.]*$/', $ua, $matches))
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Palm', 
      'platform_model'=>$matches[1],
      'platform_type'=>'handheld',
      'platform_format'=>'handheld',));
  
  /* check samsung devices */
  elseif (preg_match('/(GT|SM|SGH|SHV)-([A-Z0-9]{4,})/', $ua, $matches)) {
    $rep = array(
        /* check samsung tablets */
        'GT-P1000'  => array('platform_model' => 'Galaxy Tab', 'platform_type'=>'tablet', 'platform_format'=>'tablet'),
        'GT-P3100'  => array('platform_model' => 'Galaxy Tab 2', 'platform_type'=>'tablet', 'platform_format'=>'tablet'),
        'GT-P3110'  => array('platform_model' => 'Galaxy Tab 2', 'platform_type'=>'tablet', 'platform_format'=>'tablet'),
        'GT-P5100'  => array('platform_model' => 'Galaxy Tab 2', 'platform_type'=>'tablet', 'platform_format'=>'tablet'),
        'GT-P5110'  => array('platform_model' => 'Galaxy Tab 2', 'platform_type'=>'tablet', 'platform_format'=>'tablet'),
        'GT-P5200'  => array('platform_model' => 'Galaxy Tab 3', 'platform_type'=>'tablet', 'platform_format'=>'tablet'),
        'GT-P5210'  => array('platform_model' => 'Galaxy Tab 3', 'platform_type'=>'tablet', 'platform_format'=>'tablet'),
        'GT-P7300'  => array('platform_model' => 'Galaxy Tab 8.9', 'platform_type'=>'tablet', 'platform_format'=>'tablet'),
        'SM-T110'   => array('platform_model' => 'Galaxy Tab 3 Lite', 'platform_type'=>'tablet', 'platform_format'=>'tablet'),
        'SM-T113'   => array('platform_model' => 'Galaxy Tab 3 Lite (2015)', 'platform_type'=>'tablet', 'platform_format'=>'tablet'),
        'SM-T310'   => array('platform_model' => 'Galaxy Tab 3', 'platform_type'=>'tablet', 'platform_format'=>'tablet'),
        'SM-T116NU' => array('platform_model' => 'Galaxy Tab 3 V', 'platform_type'=>'tablet', 'platform_format'=>'tablet'),
        'SM-T320'   => array('platform_model' => 'Galaxy Tab Pro', 'platform_type'=>'tablet', 'platform_format'=>'tablet'),
        'SM-T230'   => array('platform_model' => 'Galaxy Tab 4', 'platform_type'=>'tablet', 'platform_format'=>'tablet'),
        'SM-T530'   => array('platform_model' => 'Galaxy Tab 4', 'platform_type'=>'tablet', 'platform_format'=>'tablet'),
        'SM-T531'   => array('platform_model' => 'Galaxy Tab 4 (3G)', 'platform_type'=>'tablet', 'platform_format'=>'tablet'),
        'SM-T533'   => array('platform_model' => 'Galaxy Tab 4', 'platform_type'=>'tablet', 'platform_format'=>'tablet'),
        'SM-T535'   => array('platform_model' => 'Galaxy Tab 4 (4G)', 'platform_type'=>'tablet', 'platform_format'=>'tablet'),
        'SM-T550'   => array('platform_model' => 'Galaxy Tab A', 'platform_type'=>'tablet', 'platform_format'=>'tablet'),
        'SM-P550'   => array('platform_model' => 'Galaxy Tab A', 'platform_type'=>'tablet', 'platform_format'=>'tablet'),
        'SM-T560'   => array('platform_model' => 'Galaxy Tab E', 'platform_type'=>'tablet', 'platform_format'=>'tablet'),
        'SM-T800'   => array('platform_model' => 'Galaxy Tab S', 'platform_type'=>'tablet', 'platform_format'=>'tablet'),
        'SM-T715'   => array('platform_model' => 'Galaxy Tab S2', 'platform_type'=>'tablet', 'platform_format'=>'tablet'),
        'SM-T810'   => array('platform_model' => 'Galaxy Tab S2', 'platform_type'=>'tablet', 'platform_format'=>'tablet'),
        'SM-T813'   => array('platform_model' => 'Galaxy Tab S2', 'platform_type'=>'tablet', 'platform_format'=>'tablet'),
        
        /* check samsung phones */
        'GT-S3800W' => array('platform_model' => 'REX 70', ),
        'GT-S7562'  => array('platform_model' => 'Galaxy S Duo', ),
        'GT-I9000'  => array('platform_model' => 'Galaxy S', ),
        'GT-I9100'  => array('platform_model' => 'Galaxy S2', ),
        'GT-I9300'  => array('platform_model' => 'Galaxy S3', ),
        'GT-I9305'  => array('platform_model' => 'Galaxy S3 (4G)', ),
        'GT-I9301I' => array('platform_model' => 'Galaxy S3 Neo', ),
        'GT-I9500'  => array('platform_model' => 'Galaxy S4', ),
        'GT-I9505'  => array('platform_model' => 'Galaxy S4', ),
        'GT-I9506'  => array('platform_model' => 'Galaxy S4', ),
        'SM-G900A'  => array('platform_model' => 'Galaxy S5', ),
        'SM-G900F'  => array('platform_model' => 'Galaxy S5', ),
        'SM-G903F'  => array('platform_model' => 'Galaxy S5', ),
        'SM-G901F'  => array('platform_model' => 'Galaxy S5+', ),
        'SM-G920F'  => array('platform_model' => 'Galaxy S6'),
        'SM-G920I'  => array('platform_model' => 'Galaxy S6'),
        'SM-G920P'  => array('platform_model' => 'Galaxy S6'),
        'SM-G925T'  => array('platform_model' => 'Galaxy S6 Edge'),
        'SM-G925F'  => array('platform_model' => 'Galaxy S6 Edge'),
        'SM-G928C'  => array('platform_model' => 'Galaxy S6 Edge+'),
        'SM-G928F'  => array('platform_model' => 'Galaxy S6 Edge+'),
        'SM-G930F'  => array('platform_model' => 'Galaxy S7'),
        'SM-G930V'  => array('platform_model' => 'Galaxy S7'),
        'SM-G935F'  => array('platform_model' => 'Galaxy S7 Edge'),
        'SM-T580'   => array('platform_model' => 'Galaxy S8'),
        'SM-G950F'  => array('platform_model' => 'Galaxy S8'),
        'SM-G950F'  => array('platform_model' => 'Galaxy S8'),
        'SM-G955F'  => array('platform_model' => 'Galaxy S8+'),
        'SM-G892A'  => array('platform_model' => 'Galaxy S8 Active'),
        'SM-G313HZ' => array('platform_model' => 'Galaxy V', ),
        'SM-A300F'  => array('platform_model' => 'Galaxy A3', ),
        'SM-A300FU' => array('platform_model' => 'Galaxy A3', ),
        'SM-A310F'  => array('platform_model' => 'Galaxy A3', ),
        'SM-A300M'  => array('platform_model' => 'Galaxy A3', ),
        'SM-A320FL' => array('platform_model' => 'Galaxy A3 (2017)', ),
        'SM-A500FU' => array('platform_model' => 'Galaxy A5', ),
        'SM-A510F'  => array('platform_model' => 'Galaxy A5 (2016)', ),
        'SM-A5100'  => array('platform_model' => 'Galaxy A5 (2016)', ),
        'SM-A520F'  => array('platform_model' => 'Galaxy A5 (2017)', ),
        'SM-A700L'  => array('platform_model' => 'Galaxy A7', ),
        'SM-E500F'  => array('platform_model' => 'Galaxy E5 (2015)', ),
        'SM-E500H'  => array('platform_model' => 'Galaxy E5 (2015)', ),
        'SM-E500HQ' => array('platform_model' => 'Galaxy E5 (2015)', ),
        'SM-E500M'  => array('platform_model' => 'Galaxy E5 (2015)', ),
        'SM-E700H'  => array('platform_model' => 'Galaxy E7', ),
        'SM-J100H'  => array('platform_model' => 'Galaxy J1', ),
        'SM-J110H'  => array('platform_model' => 'Galaxy J1 (2015)', ),
        'SM-J120FN' => array('platform_model' => 'Galaxy J1 (2016)', ),
        'SM-J200F'  => array('platform_model' => 'Galaxy J2', ),
        'SM-J320FN' => array('platform_model' => 'Galaxy J3', ),
        'SM-J320F'  => array('platform_model' => 'Galaxy J3 (2016)', ),
        'SM-J500F'  => array('platform_model' => 'Galaxy J5 (2015)', ),
        'SM-J500FN' => array('platform_model' => 'Galaxy J5 (2015)', ),
        'SM-J500G'  => array('platform_model' => 'Galaxy J5 (2015)', ),
        'SM-J500Y'  => array('platform_model' => 'Galaxy J5 (2015)', ),
        'SM-J500M'  => array('platform_model' => 'Galaxy J5 (2015)', ),
        'SM-J500H'  => array('platform_model' => 'Galaxy J5 (2015)', ),
        'SM-J5007'  => array('platform_model' => 'Galaxy J5 (2015)', ),
        'SM-J510FN' => array('platform_model' => 'Galaxy J5 (2016)', ),
        'SM-J500M'  => array('platform_model' => 'Galaxy J5 (2016)', ),
        'SM-J5010F' => array('platform_model' => 'Galaxy J5 (2016)', ),
        'SM-J510G'  => array('platform_model' => 'Galaxy J5 (2016)', ),
        'SM-J510M'  => array('platform_model' => 'Galaxy J5 (2016)', ),
        'SM-J510Y'  => array('platform_model' => 'Galaxy J5 (2016)', ),
        'SM-G610F'  => array('platform_model' => 'Galaxy J7 (2016)', ),
        'SM-J710F'  => array('platform_model' => 'Galaxy J7 (2016)', ),
        'SM-J710MN' => array('platform_model' => 'Galaxy J7 (2016)', ),
        'SM-G610M'  => array('platform_model' => 'Galaxy J7 Prime (2016)', ),
        'SM-J730F'  => array('platform_model' => 'Galaxy J7 (2017)', ),
        'GT-S5360'  => array('platform_model' => 'Galaxy Y', ),
        'GT-S6102'  => array('platform_model' => 'Galaxy Y Duos', ),
        'GT-S7582'  => array('platform_model' => 'Galaxy S Duos', ),
        'GT-I8750'  => array('platform_model' => 'Ativ S', ),
        'GT-I8190'  => array('platform_model' => 'Galaxy S3 Mini', ),
        'GT-I9195'  => array('platform_model' => 'Galaxy S4 Mini', ),
        'GT-I9195I' => array('platform_model' => 'Galaxy S4 Mini', ),
        'GT-I9192'  => array('platform_model' => 'Galaxy S4 Mini Duos', ),
        'SM-G800F'  => array('platform_model' => 'Galaxy S5 Mini', ),
        'GT-S5830'  => array('platform_model' => 'Galaxy Ace', ),
        'SM-G357FZ' => array('platform_model' => 'Galaxy Ace 4', ),
        'SM-G850F'  => array('platform_model' => 'Galaxy Alpha', ),
        'SM-G850W'  => array('platform_model' => 'Galaxy Alpha', ),
        'GT-S6812'  => array('platform_model' => 'Galaxy Fame Duos'),
        'SM-G355HN' => array('platform_model' => 'Galaxy Core 2'),
        'SM-G360F'  => array('platform_model' => 'Galaxy Core Prime', ),
        'SM-G361F'  => array('platform_model' => 'Galaxy Core Prime', ),
        'SM-G386F'  => array('platform_model' => 'Galaxy Core 4G'),
        'SM-G530H'  => array('platform_model' => 'Galaxy Grand Prime', ),
        'SM-G530T'  => array('platform_model' => 'Galaxy Grand Prime', ),
        'SM-G531F'  => array('platform_model' => 'Galaxy Grand Prime', ),
        'SM-G530FZ' => array('platform_model' => 'Galaxy Grand Prime', ),
        'SM-G532F'  => array('platform_model' => 'Galaxy Grand Prime Plus', ),
        'GT-I9082L' => array('platform_model' => 'Galaxy Grand', ),
        'GT-I9060I' => array('platform_model' => 'Galaxy Grand Plus', ),
        'GT-I9082'  => array('platform_model' => 'Galaxy Grand Duos', ),
        'SM-G550FY' => array('platform_model' => 'Galaxy On5', ),
        'GT-N5110'  => array('platform_model' => 'Galaxy Note', ),
        'GT-N7000'  => array('platform_model' => 'Galaxy Note (3G)', ),
        'GT-N7003'  => array('platform_model' => 'Galaxy Note (4G)', ),
        'GT-N8000'  => array('platform_model' => 'Galaxy Note 10.1 (3G)', ),
        'GT-N8010'  => array('platform_model' => 'Galaxy Note 10.1', ),
        'GT-N7100'  => array('platform_model' => 'Galaxy Note II (3G)', ),
        'GT-N7105'  => array('platform_model' => 'Galaxy Note II', ),
        'SHV-E250S' => array('platform_model' => 'Galaxy Note II', ),
        'SM-N900W8' => array('platform_model' => 'Galaxy Note 3', ),
        'SM-N900P'  => array('platform_model' => 'Galaxy Note 3', ),
        'SM-N900A'  => array('platform_model' => 'Galaxy Note 3', ),
        'SM-N900'   => array('platform_model' => 'Galaxy Note 3 (3G)', ),
        'SM-N9002'  => array('platform_model' => 'Galaxy Note 3 (Dual-SIM)', ),
        'SM-N9005'  => array('platform_model' => 'Galaxy Note 3 (4G)', ),
        'SM-N7505'  => array('platform_model' => 'Galaxy Note 3 Neo', ),
        'SM-N910A'  => array('platform_model' => 'Galaxy Note 4', ),
        'SM-N910F'  => array('platform_model' => 'Galaxy Note 4', ),
        'SM-N920V'  => array('platform_model' => 'Galaxy Note 5', ),
        'SM-N930T'  => array('platform_model' => 'Galaxy Note 7', ),
        'SM-N950'   => array('platform_model' => 'Galaxy Note 8', ),
        'SM-N950F'  => array('platform_model' => 'Galaxy Note 8', ),
        'SM-B313E'  => array('platform_model' => 'Galaxy Metro 313 (2014)', ),
        'SM-G350E'  => array('platform_model' => 'Galaxy Star 2 Plus', ),
        'SM-G130E'  => array('platform_model' => 'Galaxy Star 2 Plus', ),
        'SGH-I527'  => array('platform_model' => 'Galaxy Mega', ),
        'GT-S7392'  => array('platform_model' => 'Galaxy Trend', ),
        'GT-S7560'  => array('platform_model' => 'Galaxy Trend', ),
        'GT-S7580'  => array('platform_model' => 'Galaxy Trend+ (2013)', ),
        'SM-G318H'  => array('platform_model' => 'Galaxy Trend 2 lite (2015)', ),
        'GT-S5660'  => array('platform_model' => 'Galaxy Gio', ),
        'GT-S5660M' => array('platform_model' => 'Galaxy Gio', ),
        'GT-S8500'  => array('platform_model' => 'Galaxy Wave', ),
        'GT-I8552'  => array('platform_model' => 'Galaxy Win Duos', ),
        'SM-G388F'  => array('platform_model' => 'Galaxy Xcover 3', ),
        'SM-G130H'  => array('platform_model' => 'Galaxy Young 2', ),
        'SM-G130HN' => array('platform_model' => 'Galaxy Young 2', ),
    );
 	$infos = array_merge($infos, array(
 	  'platform_company'=>'Samsung', 
      'platform_model'=>$matches[0],
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'), 
      isset($rep[$matches[0]])?$rep[$matches[0]]:array());
      
  } elseif (preg_match('/SAMSUNG\-(?:SGH\-|)([^\/]+)/', $ua, $matches))
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Samsung', 
      'platform_model'=>$matches[1],
      'platform_type'=>'handheld',
      'platform_format'=>'handheld',));
  elseif (preg_match('/(Galaxy)/', $ua, $matches))
 	$infos = array_merge($infos, array(
 	  'platform_company'=>'Samsung', 
      'platform_model'=>$matches[1],
      'platform_type'=>'handheld',
      'platform_format'=>'handheld',));
  elseif (preg_match('/(klte)/', $ua, $matches))
 	$infos = array_merge($infos, array(
 	  'platform_company'=>'Samsung', 
      'platform_model'=>'Galaxy S5',
      'platform_type'=>'handheld',
      'platform_format'=>'handheld',));
  
  /* check Samsung PC */
  elseif (preg_match('/MASMJS|SMJB/', $ua, $matches))
 	$infos = array_merge($infos, array(
 	  'platform_company'=>'Samsung (PC)'));
  
  /* check OnePlus - to be inserted before Sony */
  elseif (preg_match('/ ONE (E[0-9]+)/', $ua, $matches)) {
    $rep = array(
        'E1003'=>array('platform_model' => 'X'),         
    );
    $model = trim($matches[1]);
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'OnePlus', 
      'platform_model'=>$model,
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'), 
      isset($rep[$model])?$rep[$model]:array());
  }
  elseif (preg_match('/ ONEPLUS (A[0-9]+)/', $ua, $matches)) {
    $rep = array(
        'A5000'=>array('platform_model' => '5'),         
    );
    $model = trim($matches[1]);
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'OnePlus', 
      'platform_model'=>$model,
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'), 
      isset($rep[$model])?$rep[$model]:array());
  }
      
  /* check SonyEricsson */
  elseif (preg_match('/SonyEricsson([^ \/]+)/', $ua, $matches))
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'SonyEricsson', 
      'platform_model'=>$matches[1],
      'platform_type'=>'handheld',
      'platform_format'=>'handheld',));
  
  /* check Sony mobiles and tablets */
  elseif (preg_match('/ (C|D|E|F|G)([0-9]{4}) /', $ua, $matches)) {
    $rep = array(
        'C1505'=>array('platform_model' => 'Xperia E'),  
        'C2105'=>array('platform_model' => 'Xperia L'), 
        'C5303'=>array('platform_model' => 'Xperia SP'),
        'C6603'=>array('platform_model' => 'Xperia Z'),
        'D6503'=>array('platform_model' => 'Xperia Z2'),
        'D2005'=>array('platform_model' => 'Xperia E1'),
        'D2203'=>array('platform_model' => 'Xperia E3 (2014)'),
        'D2303'=>array('platform_model' => 'Xperia M2'),
        'D2305'=>array('platform_model' => 'Xperia M2'),
        'D2306'=>array('platform_model' => 'Xperia M2'),
        'D5303'=>array('platform_model' => 'Xperia T2 Ultra'),
        'D5503'=>array('platform_model' => 'Xperia Z1 Compact'),
        'D5803'=>array('platform_model' => 'Xperia Z3 Compact'), 
        'D6603'=>array('platform_model' => 'Xperia Z3'),         
        'E6653'=>array('platform_model' => 'Xperia Z5'),
        'E5823'=>array('platform_model' => 'Xperia Z5 Compact'),
        'F3111'=>array('platform_model' => 'Xperia XA'),
        'F5121'=>array('platform_model' => 'Xperia X'),
        'F8331'=>array('platform_model' => 'Xperia XZ'),
        'G8141'=>array('platform_model' => 'Xperia XZ Premium'),
    );
    $model = trim($matches[0]);
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Sony', 
      'platform_model'=>$model,
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'), 
      isset($rep[$model])?$rep[$model]:array());
  }
  elseif (preg_match('/SOV33/', $ua, $matches)) {
    $rep = array(
        'SOV33'=>array('platform_model' => 'Xperia X Performance'),  
    );
    $model = trim($matches[0]);
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Sony', 
      'platform_model'=>$model,
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'), 
      isset($rep[$model])?$rep[$model]:array());
  }
  /* check Sony PCs */
  elseif (preg_match('/MASE|MASEJS|MASP|MASPJS|MASA|MASAJS/', $ua, $matches))
    $infos = array_merge($infos, array(
  	  'platform_company'=>'Sony (PC)'));
  
  /* check Huawei */
  elseif (preg_match('/Huawei([A-Z0-9\-]{7,})/i', $ua, $matches)) {
    $rep = array(
        'EVA-L09'   => array('platform_model' => 'P9'),
        'VNS-L31'   => array('platform_model' => 'P9 Lite'),
        'VIE-L29'   => array('platform_model' => 'P9 Plus'),
        'ALE-L21'   => array('platform_model' => 'P8 Lite'),
        'GRA-L09'   => array('platform_model' => 'P8'),
        'NXT-L09'   => array('platform_model' => 'Mate 8'),
        'NXT-L29'   => array('platform_model' => 'Mate 8'),
        'CRR-L09'   => array('platform_model' => 'Mate S'),
        'FRD-L09'   => array('platform_model' => 'Honor 8'),
        'FRD-L19'   => array('platform_model' => 'Honor 8'),
        'Y635-L01'  => array('platform_model' => 'Y635'),
        'Y520-U22'  => array('platform_model' => 'Ascend'),
        'Y600-U151' => array('platform_model' => 'Ascend'),
        'CUN-L21'   => array('platform_model' => 'Y5'),
        'LYO-L01'   => array('platform_model' => 'Y6 II Compact'),
    );
    $model = trim($matches[1]);
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Huawei', 
      'platform_model'=>$model,
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'), 
      isset($rep[$model])?$rep[$model]:array());
  }
  
  elseif (preg_match('/HONOR([A-Z0-9\-]{7,})/i', $ua, $matches)) {
    $rep = array(
        'KIW-L21'   => array('platform_model' => 'Honor 5X'),
        'PLK-L01'   => array('platform_model' => 'Honor 7'),
    );
    $model = trim($matches[1]);
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Huawei', 
      'platform_model'=>$model,
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'), 
      isset($rep[$model])?$rep[$model]:array());
  }
  
  elseif (preg_match('/SCL\-L01/', $ua, $matches)) {
    $rep = array(
        'SCL-L01'   => array('platform_model' => 'Y6'),
    );
    $model = trim($matches[0]);
    $infos = array_merge($infos, array(
  	  'platform_company'=>'Huawei', 
      'platform_model'=>$model,
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'),
      isset($rep[$model])?$rep[$model]:array());
  }
  
  /* check Spice Mobility */
  elseif (preg_match('/Spice ([A-Z0-9\-]{5,})/i', $ua, $matches)) {
    $rep = array(
        'Mi-349'   => array('platform_model' => 'Smart Flo Edge'),
    );
    $model = trim($matches[1]);
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Spice Mobility', 
      'platform_model'=>$model,
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'), 
      isset($rep[$model])?$rep[$model]:array());
  }
  
  /* check Archos */
  elseif (preg_match('/AC([A-Z0-9\-]{3,})/', $ua, $matches)) {
    $rep = array(
        '45BHE'=>array('platform_model' => 'Helium 45b'),
        '50BHE'=>array('platform_model' => 'Helium 50b'),
    );
    $model = trim($matches[1]);
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Archos', 
      'platform_model'=>$model,
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'), 
      isset($rep[$model])?$rep[$model]:array());
  }
  elseif (preg_match('/A40Ti/', $ua, $matches))
    $infos = array_merge($infos, array(
  	  'platform_company'=>'Archos', 
      'platform_model'=>'A40Ti'));
  
  /* check Lenovo */
  elseif (preg_match('/Lenovo[ |_]([A-Z0-9\-]{3,})/i', $ua, $matches)) {
    $rep = array(
        'P70-A'     => array('platform_model' => 'P70'),
        'B8000-F'   => array('platform_model' => 'Yoga', 'platform_type'=>'tablet', 'platform_format'=>'tablet'),
        'A2010-a'   => array('platform_model' => 'A2010', ),
        'K53a48'    => array('platform_model' => 'K6 Note', ),
    );
    $model = trim($matches[1]);
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Lenovo', 
      'platform_model'=>$model,
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'), 
      isset($rep[$model])?$rep[$model]:array());
  }
  elseif (preg_match('/IdeaTab ([A-Z0-9\-]{3,})/', $ua, $matches)) {
    $rep = array(
        'A2107A-H'  => array('platform_model' => 'IdeaTab A2107A-H', 'platform_type'=>'tablet', 'platform_format'=>'tablet'),
    );
    $model = trim($matches[1]);
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Lenovo', 
      'platform_model'=>$model,
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'), 
      isset($rep[$model])?$rep[$model]:array());
  }
  
  /* check Lenovo PCs */
  elseif (preg_match('/MALC|MALCJS|MALN|MALNJS|LCJB|LEN2/', $ua, $matches))
    $infos = array_merge($infos, array(
  	  'platform_company'=>'Lenovo (PC)'));
  
  /* check Asus mobiles and tablets */
  elseif (preg_match('/(K|ME)([0-9]{2})([A-Z0-9]{1,2}) /', $ua, $matches)) {
    $rep = array(
        'K007'      => array('platform_model' => 'MeMO Pad 7', 'platform_type'=>'tablet', 'platform_format'=>'tablet'),
        'K01E'      => array('platform_model' => 'MeMO Pad', 'platform_type'=>'tablet', 'platform_format'=>'tablet'),
        'ME173X'    => array('platform_model' => 'MeMO Pad HD 7', 'platform_type'=>'tablet', 'platform_format'=>'tablet'),
    );
    $model = trim($matches[0]);
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Asus', 
      'platform_model'=>$model,
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'), 
      isset($rep[$model])?$rep[$model]:array());
  }
  elseif (preg_match('/ASUS_([A-Z0-9]+) /', $ua, $matches)) {
    $rep = array(
        'Z00ED'     => array('platform_model' => 'Zenfon 2'),
        'Z00LD'     => array('platform_model' => 'Zenfon 2 Laser'),
    );
    $model = trim($matches[1]);
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Asus', 
      'platform_model'=>$model,
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'), 
      isset($rep[$model])?$rep[$model]:array());
  }
  
  /* check Asus PCs */
  elseif (preg_match('/MAAU|ASJB|ASU2JS|ASU2|NP0[6789]/', $ua, $matches))
    $infos = array_merge($infos, array(
  	  'platform_company'=>'Asus (PC)'));   

  /* check Micromax */
  elseif (preg_match('/Micromax( |_)([^ \/\)]+)/', $ua, $matches)) {
    $rep = array(
        'A62'       => array('platform_model' => 'Bolt A62'),
        'Q335'      => array('platform_model' => 'Bolt Q335'),
        'Q350'      => array('platform_model' => 'Canvas Spark Q350'),
        'Q380'      => array('platform_model' => 'Canvas Spark Q380'),
    );
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Micromax', 
      'platform_model'=>$matches[2],
      'platform_type'=>'handheld',
      'platform_format'=>'handheld',), 
      isset($rep[$matches[2]])?$rep[$matches[2]]:array());
  }
      
  /* check ITel */
  elseif (preg_match('/itel it([^ \/;]+( Plus)?)/', $ua, $matches))
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'ITel', 
      'platform_model'=>$matches[1],
      'platform_type'=>'handheld',
      'platform_format'=>'handheld',)); 
      
  /* check Nintendo */
  elseif (preg_match('/Nintendo ([^ \/;\)]+)/', $ua, $matches)) {
  	$infos = array_merge($infos, array('platform_company'=>'Nintendo', 
      'platform_model'=>$matches[1],
      'platform_type'=>preg_match('/DS/', $matches[1])?'handheld':'computer',
      'platform_format'=>preg_match('/DS/', $matches[1])?'handheld':'desktop'));
  }
  /* check Xbox / XBox One */
  elseif (preg_match('/Xbox(; Xbox [a-zA-Z0-9]*)?/i', $ua, $matches))
  	$infos = array_merge($infos, array('platform_company'=>'Microsoft', 
      'platform_model'=>isset($matches[1])?substr($matches[1], 2):'Xbox 360',
      'platform_type'=>'computer',
      'platform_format'=>'desktop',));
  
  /* check Amazon Kindle */
  elseif (preg_match('/Kindle([0-9\.]*)/', $ua, $matches))
  	$infos = array_merge($infos, array('platform_company'=>'Amazon', 
      'platform_model'=>'Kindle',
      'platform_type'=>'tablet',
      'platform_format'=>'tablet',
      'browser_title'=>'Kindle browser',
      'browser_version'=>$matches[1]));
      
  /* check Macintosh */
  elseif (preg_match('/(?:Intel |PPC |)Mac OS X( Mach-O| [0-9\._]*|)/i', $ua, $matches)) {
    /* check version */
    $version = ($matches[1]!=' Mach-O')?substr(str_replace('_','.',$matches[1]), 1):'';
    if (version_compare($version, $maxVersions['system']['Mac OS X']) > 0)
      return $fake;
    
    /* build info */
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Apple', 
      'platform_model'=>'Macintosh',
      'platform_type'=>'computer',
      'platform_format'=>'desktop',
      'system_title'=>'Mac OS X',
      'system_version'=> $version));
  }
  
  /* check Wiko */
  elseif (preg_match('/DARKSIDE|LENNY|RIDGE 4G|U FEEL LITE|FEVER|JERRY|TOMMY2|RAINBOW|SUNSET2/', $ua, $matches)) {
    $rep = array(
        'TOMMY2'    => array('platform_model' => 'Tommy 2',),
        'SUNSET2'    => array('platform_model' => 'Sunset 2',),
    );
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Wiko', 
      'platform_model'=>ucfirst(strtolower($matches[0])),
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'),
      isset($rep[$matches[0]])?$rep[$matches[0]]:array()
      );
  }
  
  /* check SpreadTrum */
  elseif (preg_match('/SpreadTrum/', $ua, $matches))
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'SpreadTrum', 
      'platform_model'=>'',
      'platform_type'=>'handheld',
      'platform_format'=>'handheld',));
  
  /* check Maximus MAX908 */
  elseif (preg_match('/MAX908/', $ua, $matches))
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Maximus', 
      'platform_model'=>'MAX908',
      'platform_type'=>'handheld',
      'platform_format'=>'handheld',));
  
  /* check Alcatel */
  elseif (preg_match('/ ([0-9]{4}[A-Z]) Build/', $ua, $matches)) {
    $rep = array(
        '4015D' => array('platform_model' => 'One Touch Idol 3',),
        '5050X' => array('platform_model' => 'One Touch Pop S3',),
        '5070D' => array('platform_model' => 'One Touch Pop Star 4G',),
        '6045Y' => array('platform_model' => 'One Touch Pop C1',),
    );
    $model = trim($matches[1]);
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Alcatel', 
      'platform_model'=>$model,
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'), 
      isset($rep[$model])?$rep[$model]:array());
  }
  elseif (preg_match('/Orange KLIF/', $ua, $matches)) {   
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Alcatel', 
      'platform_model'  =>'Orange KLIF',
      'system_title'    =>'Firefox OS',
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'));
  }
  
  /* check Lava Iris models */
  elseif (preg_match('/Iris([A-Z0-9]+)/i', $ua, $matches))
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Lava', 
      'platform_model'=>'Iris '.$matches[1],
      'platform_type'=>'handheld',
      'platform_format'=>'handheld',));
      
  /* check Tecno mobiles */
  elseif (preg_match('/Tecno ?([^;| ]*)/i', $ua, $matches))
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Tecno', 
      'platform_model'=>isset($matches[1])?$matches[1]:'',
      'platform_type'=>'handheld',
      'platform_format'=>'handheld',));
  
  /* check Yezz Andy models */
  elseif (preg_match('/Andy[_ ]([A-Z0-9]{2,})/i', $ua, $matches))
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Yezz', 
      'platform_model'=>'Andy '.$matches[1],
      'platform_type'=>'handheld',
      'platform_format'=>'handheld',));
  
  /* check accent mobiles */
  elseif (preg_match('/Accent ?([^;| ]*)/i', $ua, $matches))
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Accent', 
      'platform_model'=>isset($matches[1])?ucwords(strtolower($matches[1])):'',
      'platform_type'=>'handheld',
      'platform_format'=>'handheld',));
  
  /* check Memup SlidePad 704CE */
  elseif (preg_match('/SP704CE/i', $ua, $matches))
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Memup', 
      'platform_model'=>'SP704CE',
      'platform_type'=>'handheld',
      'platform_format'=>'tablet',));
  
  /* check Wing mobiles */
  elseif (preg_match('/Wing_([A-Za-z0-9]{2,})/i', $ua, $matches))
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Wing', 
      'platform_model'=>isset($matches[1])?ucwords(strtolower($matches[1])):'',
      'platform_type'=>'handheld',
      'platform_format'=>'handheld',));
      
  /* check Leagoo mobiles */
  elseif (preg_match('/ Elite 2 Build/', $ua, $matches))
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Leagoo', 
      'platform_model'=>'Elite 2',
      'platform_type'=>'handheld',
      'platform_format'=>'handheld',));
  
  /* check Wortmann TERRA PAD 1003 mobiles */
  elseif (preg_match('/TERRA PAD 1003/', $ua, $matches))
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Wortmann', 
      'platform_model'=>'Terra Pad 1003',
      'platform_type'=>'tablet',
      'platform_format'=>'tablet',));
  
  /* check QMobile */
  elseif (preg_match('/A3 Build|LT700/', $ua, $matches)) {
    $rep = array(
        'A3 Build'	=> array('platform_model' => 'A3'),
        'LT700'	=> array('platform_model' => 'LT700'),
    );
    $model = trim($matches[0]);
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'QMobile', 
      'platform_model'=>'A3',
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'), 
      isset($rep[$model])?$rep[$model]:array());
  }
  
  /* check Haier mobiles */
  elseif (preg_match('/(CDP7TAB4C8|G30)/', $ua, $matches)) {
    $rep = array(
        'CDP7TAB4C8'    => array('platform_model' => 'CDisplay E701', 'platform_type'=>'tablet', 'platform_format'=>'tablet'),
        'G30'           => array('platform_model' => 'Voyage G30',),
    );
    $model = trim($matches[1]);
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Haier', 
      'platform_model'=>$model,
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'), 
      isset($rep[$model])?$rep[$model]:array());
  }
  
  /* check Bloom */
  elseif (preg_match('/BLOOM Build/', $ua, $matches))
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Bloom', 
      'platform_model'=>'',
      'platform_type'=>'handheld',
      'platform_format'=>'handheld',));
  
  /* check Carrefour */
  elseif (preg_match('/CMB([0-9]{3})/', $ua, $matches)) {
    $rep = array(
        '510'=>array('platform_model' => 'Smart 5'),
    );
    $model = trim($matches[1]);
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Carrefour', 
      'platform_model'=>$model,
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'), 
      isset($rep[$model])?$rep[$model]:array());
  }
  
  /* check Orange */
  elseif (preg_match('/Nura 2/', $ua, $matches)) {
    $rep = array(
        '510'=>array('platform_model' => 'Smart 5'),
    );
    $model = trim($matches[0]);
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Orange', 
      'platform_model'=>$model,
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'), 
      isset($rep[$model])?$rep[$model]:array());
  }
  elseif (preg_match('/Orange ([^.]*) Build/', $ua, $matches)) {
    $rep = array(
        
    );
    $model = trim($matches[1]);
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Orange', 
      'platform_model'=>$model,
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'), 
      isset($rep[$model])?$rep[$model]:array());
  }
  
  /* check Logicom */
  elseif (preg_match('/L-EMENT?_[0-9]{3}/', $ua, $matches)) {
    $rep = array(
        'L-EMENT501'=>array('platform_model' => 'L-Element 501'),
        'L-EMENT451'=>array('platform_model' => 'L-Element 451'),
        'L-EMENT_403'=>array('platform_model' => 'L-Element 403'),
    );
    $model = trim($matches[0]);
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Logicom', 
      'platform_model'=>$model,
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'), 
      isset($rep[$model])?$rep[$model]:array());
  }
  
  /* check Coolpad devices */
  elseif (preg_match('/CP(8298_I00) Build/', $ua, $matches)) {
    $rep = array(
        '8298_I00'=>array('platform_model' => 'Note Lite 3', 'platform_type'=>'handheld', 'platform_format'=>'handheld'),
    );
    $infos = array_merge($infos, array(
 	  'platform_company'=>'Coolpad', 
      'platform_model'=>$matches[1],
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'), 
      isset($rep[$matches[1]])?$rep[$matches[1]]:array());
  }
  
  /* check Vestel devices */
  elseif (preg_match('/(Venus_V3_5570)/', $ua, $matches)) {
    $rep = array(
        'Venus_V3_5570'=>array('platform_model' => 'Ven&uuml;s V3 5570', 'platform_type'=>'handheld', 'platform_format'=>'handheld'),
    );
    $infos = array_merge($infos, array(
 	  'platform_company'=>'Vestel', 
      'platform_model'=>$matches[1],
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'), 
      isset($rep[$matches[1]])?$rep[$matches[1]]:array());
  }
  
  /* check Hewlett Packard OEM computers */
  elseif (preg_match('/HPCMHP|HPNTDF|HPNTDFJS|HPDTDF|HPDTDFJS/', $ua, $matches)) {
    $infos = array_merge($infos, array(
 	  'platform_company'=>'Hewlett Packard (PC)'));
  }
  
  /* check Dell OEM computers */
  elseif (preg_match('/MDDR|MDDRJS|MDDC|MDDCJS|MDDS|MDDSJS/', $ua, $matches)) {
    $infos = array_merge($infos, array(
 	  'platform_company'=>'Dell (PC)'));
  }
  
  /* check Toshiba OEM computers */
  elseif (preg_match('/MATM|MATMJS|MATB|MATBJS|MATP|MATPJS|TNJB|TAJB/', $ua, $matches)) {
    $infos = array_merge($infos, array(
 	  'platform_company'=>'Toshiba (PC)'));
  }
  
  /* check Acer mobiles */
  elseif (preg_match('/(Z130|T03|T04)/', $ua, $matches)) {
    $rep = array(
        'Z130' => array('platform_model' => 'Liquid Z3',),
        'T03' => array('platform_model' => 'Liquid Z630',),
        'T04' => array('platform_model' => 'Liquid Z630S',),
    );
    $model = trim($matches[1]);
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Acer', 
      'platform_model'=>$model,
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'), 
      isset($rep[$model])?$rep[$model]:array());
  }
  
  /* check Acer OEM computers */
  elseif (preg_match('/MAAR|MAARJS/', $ua, $matches)) {
    $infos = array_merge($infos, array(
 	  'platform_company'=>'Acer (PC)'));
  }
  
  /* check Medion OEM computers */
  elseif (preg_match('/MAMD/', $ua, $matches)) {
    $infos = array_merge($infos, array(
 	  'platform_company'=>'Medion (PC)'));
  }
  
  /* check MSI OEM computers */
  elseif (preg_match('/MAMI|MAMIJS|MAM3/', $ua, $matches)) {
    $infos = array_merge($infos, array(
 	  'platform_company'=>'Medion (PC)'));
  }
  
  /* check Gateway OEM computers */
  elseif (preg_match('/MAGW|MAGWJS/', $ua, $matches)) {
    $infos = array_merge($infos, array(
 	  'platform_company'=>'Gateway (PC)'));
  }
  
  /* check Fujitsu OEM computers */
  elseif (preg_match('/MAFS|MAFSJS/', $ua, $matches)) {
    $infos = array_merge($infos, array(
 	  'platform_company'=>'Fujitsu (PC)'));
  }
  
  /* check Compaq OEM computers */
  elseif (preg_match('/CPDTDF|CPNTDF|CMNTDF|CMNTDFJS/', $ua, $matches)) {
    $infos = array_merge($infos, array(
 	  'platform_company'=>'Compaq (PC)'));
  }
  
  /* check Polaroid tablets, to be inserted before Xiaomi */
  elseif (preg_match('/MID4X10/', $ua, $matches)) {
    $rep = array();
    $infos = array_merge($infos, array(
 	  'platform_company'=>'Polaroid', 
      'platform_model'=>$matches[0],
      'platform_type'=>'tablet',
      'platform_format'=>'tablet'), 
      isset($rep[$matches[0]])?$rep[$matches[0]]:array());
  }
  
  /* check Xiaomi mobiles */
  elseif (preg_match('/MI ?([A-Za-z0-9]{1,} )Build/', $ua, $matches)) {
    $rep = array(
        'PAD'=>array('platform_model' => 'MI PAD', 'platform_type'=>'tablet', 'platform_format'=>'tablet'),
    );
    $infos = array_merge($infos, array(
 	  'platform_company'=>'Xiaomi', 
      'platform_model'=>'MI '.$matches[1],
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'), 
      isset($rep[$matches[1]])?$rep[$matches[1]]:array());
  }    
  elseif (preg_match('/HM NOTE 1LTE/', $ua, $matches))
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Xiaomi', 
      'platform_model'=>'Redmi Note 3',
      'platform_type'=>'handheld',
      'platform_format'=>'handheld')
    );
  elseif (preg_match('/(Redmi [A-Za-z0-9 ]{1,}) Build/', $ua, $matches))
    $infos = array_merge($infos, array(
  	  'platform_company'=>'Xiaomi', 
      'platform_model'=>$matches[1],
      'platform_type'=>'handheld',
      'platform_format'=>'handheld',)
    );
    
  /* check Iris Sat mobiles */
  elseif (preg_match('/(I-S3)/', $ua, $matches)) {
    $rep = array(
        'I-S3' => array('platform_model' => 'I-S3',),
    );
    $model = trim($matches[1]);
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Iris Sat', 
      'platform_model'=>$model,
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'), 
      isset($rep[$model])?$rep[$model]:array());
  }
  
  /* check Umi mobiles */
  elseif (preg_match('/(IRON Pro)/', $ua, $matches)) {
    $rep = array(
        'IRON Pro' => array('platform_model' => 'IRON Pro',),
    );
    $model = trim($matches[1]);
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Umi', 
      'platform_model'=>$model,
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'), 
      isset($rep[$model])?$rep[$model]:array());
  }
  
  /* check Kazam mobiles */
  elseif (preg_match('/KAZAM_(Trooper_450L)/', $ua, $matches)) {
    $rep = array(
        'Trooper_450L' => array('platform_model' => 'Trooper 450L',),
    );
    $model = trim($matches[1]);
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Kazam', 
      'platform_model'=>$model,
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'), 
      isset($rep[$model])?$rep[$model]:array());
  }
    
  /* check Condor mobiles */
  elseif (preg_match('/(P[A-Z]{2}[0-9]{3})/', $ua, $matches)) {
    $rep = array(
        'PGN521' => array('platform_model' => 'Griffe G4 Plus',),
        'PHQ520' => array('platform_model' => 'Griffe G5',),
        'PGN528' => array('platform_model' => 'Plume P6 Pro',),
	    'PGN523' => array('platform_model' => 'Plume P7 Plus',),
        'PGN605' => array('platform_model' => 'Plume P8',),
    );
    $model = trim($matches[1]);
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Condor', 
      'platform_model'=>$model,
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'), 
      isset($rep[$model])?$rep[$model]:array());
  }
      
  /* check Smartisan mobiles */
  elseif (preg_match('/(SM[0-9]{3})/', $ua, $matches)) {
    $rep = array(
        'SM801' => array('platform_model' => 'T2',),
    );
    $model = trim($matches[1]);
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Smartisan', 
      'platform_model'=>$model,
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'), 
      isset($rep[$model])?$rep[$model]:array());
  }
      
  /* check Gigabyte mobiles */
  elseif (preg_match('/(GSmart Rey R3)/', $ua, $matches)) {
    $rep = array(
        /* '' => array('platform_model' => '',), */
    );
    $model = trim($matches[1]);
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Gigabyte', 
      'platform_model'=>$model,
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'), 
      isset($rep[$model])?$rep[$model]:array());
  }
      
  /* check Lyf mobiles */
  elseif (preg_match('/(LYF\/F61F)/', $ua, $matches)) {
    $rep = array(
         'LYF/F61F' => array('platform_model' => 'JioPhone',),
    );
    $model = trim($matches[1]);
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Lyf', 
      'platform_model'=>$model,
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'), 
      isset($rep[$model])?$rep[$model]:array());
  }
      
  /* check Cubot mobiles */
  elseif (preg_match('/(GT90)/', $ua, $matches)) {
    $rep = array(
         
    );
    $model = trim($matches[1]);
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Cubot', 
      'platform_model'=>$model,
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'), 
      isset($rep[$model])?$rep[$model]:array());
  }
      
  /* check Infinix  mobiles */
  elseif (preg_match('/(X559)/', $ua, $matches)) {
    $rep = array(
        'X559'  => array('platform_model' => 'Hot 5 Lite',),
    );
    $model = trim($matches[1]);
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'Infinix', 
      'platform_model'=>$model,
      'platform_type'=>'handheld',
      'platform_format'=>'handheld'), 
      isset($rep[$model])?$rep[$model]:array());
  }
  
  /* check Digital Alpha servers */
  elseif (preg_match('/ (Digital AlphaServer [A-Za-z0-9]*) /', $ua, $matches)) {
    $model = trim($matches[1]);
  	$infos = array_merge($infos, array(
  	  'platform_company'=>'PC (Digital Equipment Corporation)', 
      'platform_model'=>$model
    ));
  }
            
  /*** check operating system ***/
  
  if (!isset($infos['system_title'])) {
    /* check Windows Phone */
    if (preg_match('/Windows Phone ?([^;]*);/', $ua, $matches)) 
      $infos = array_merge(array(
     'platform_type'=>'handheld',
     'platform_format'=>'handheld',
     'system_title'=>'Windows Phone',
     'system_version'=>isset($matches[1])?$matches[1]:''), $infos);
    
    /* check Android */
  	elseif (preg_match('/(?:Android|Adr)[ \/]?([^;\) ]*)/', $ua, $matches)) {
  	  /* check version */
      $version = isset($matches[1])?$matches[1]:'';
      if ($version != '' and version_compare($version, $maxVersions['system']['Android']) > 0)
        return $fake;
      
      $infos = array_merge(array(
        'platform_type'     => (preg_match('/tablet/i',$ua) ? 'tablet' : 'handheld'),
        'platform_format'   => (preg_match('/tablet/i',$ua) ? 'tablet' : 'handheld'),
        'system_title'      => 'Android',
        'system_version'    => $version,
      ), $infos);  	
    }
    
    /* check Windows */
  	else if (preg_match('/(?:Windows;)?[^.]*(?:Windows |Windows|Win |Win)([^;\)]+)/', $ua, $matches)) {
  	  // '/(?:Windows |Win)([^;]{1,});/'
  	  
  	  /* build known windows versions */
      $w = array('3.1'=>'3.1', '95'=>'95', '98'=>'98', '9x 4.90' => '98', '9x4.90' => '98', 'CE'=>'CE', 
          'ME'=>'ME', 'NT'=>'NT', 'NT3.51'=> 'NT 3.51',  'NT 4.0'=>'NT 4.0', 'NT4.0'=>'NT 4.0', 'NT 5.0'=>'2000', 
          '2000'=>'2000', 'NT 5.1'=>'XP', 'NT 5.2'=>'XP Pro / Server 2003 / Home Server', 'NT 6.0'=>'Vista', 
          'NT 6.1'=>'7', 'NT6.1'=>'7', 'NT 6.1'=>'7', 'NT 6.2'=>'8', 'NT 6.3'=>'8.1', 'NT 6.4'=>'10', 'NT 9.1'=>'NT 9.1',
          'NT 10.0'=>'10', '10'=>'10',           
      );
      
      /* build known windows fake versions */
      $wf = array('NT 15.0');
      
      /* load version */
      $v = $matches[1];
      if (substr($v, 0, 1) == ' ') $v = trim(substr($v, 0, 7)); 
      $version = isset($w[$v])?$w[$v]:'';
      
      /* check fake version */
      if (in_array($v, $wf))
        return $fake;
        
      $infos = array_merge(array(
        'platform_company'=>'PC', 
      	'platform_model'=>'',
        'platform_type'=>'computer',
        'platform_format'=>'desktop',
      	'system_title'=>'Windows',
      	'system_version'=>$version), $infos);
  	}
  	
    /* check determined linux os */
  	elseif (preg_match('/(Debian|Ubuntu|DragonFly|SUSE|Slackware|CentOS|Fedora|Kubuntu|Edubuntu|Xubuntu|Gentoo|Red Hat|Mint|Mandriva|CrOS|Arch ?Linux|Caldera Systems OpenLinux)/i', $ua, $matches)) {
      $w = array('CrOS'=>'Chrome OS');
      $infos = array_merge(array(
        'platform_company'=>'PC', 
      	'platform_model'=>'',
        'platform_type'=>'computer',
        'platform_format'=>'desktop',
      	'system_title'=>isset($w[$matches[1]])?$w[$matches[1]]:ucwords($matches[1]).' (Linux)',
      	'system_version'=>''), $infos);
  	}
    /* check mobile gen os with notified version */
  	elseif (preg_match('/(SymbianOS|webOS|KAIOS|Bada)(?:\/| )?([0-9][a-z0-9\._]*)/i', $ua, $matches)){
      $infos = array_merge(array(
        'platform_company'=>'PC', 
      	'platform_model'=>'',
        'platform_type'=>'handheld',
        'platform_format'=>'handheld',
      	'system_title'=>$matches[1],
      	'system_version'=>isset($matches[2])?$matches[2]:''), $infos);
    }
    /* check gen os with notified version */
  	elseif (preg_match('/(AmigaOS|WebTV)(?:\/| )([0-9][a-z0-9\._]*)?/i', $ua, $matches))
      $infos = array_merge(array(
        'platform_company'=>'PC', 
      	'platform_model'=>'',
        'platform_type'=>'computer',
        'platform_format'=>'desktop',
      	'system_title'=>$matches[1],
      	'system_version'=>isset($matches[2])?$matches[2]:''), $infos);
  	
    /* check gen os without notified version */
  	elseif (preg_match('/(Linux|FreeBSD|SunOS|OpenBSD|SymbOS|OS\/2|BeOS|NetBSD|OpenSolaris)[^\.]/', $ua, $matches)) {
  	  $rep = array(
        'SymbOS'    => array('platform_company' => '', 'system_title' => 'SymbianOS', 'platform_type'=>'handheld', 'platform_format'=>'handheld',),
      );
      
      $model = trim($matches[1]);
      
      $infos = array_merge($infos, array(
        'platform_company'=>'PC', 
      	'platform_model'=>'',
        'platform_type'=>'computer',
        'platform_format'=>'desktop',
      	'system_title'=>$matches[1],
      	'system_version'=>''), 
      	isset($rep[$model])?$rep[$model]:array()
      );      	
    }
    
    /* check X11 gen unix  */
    elseif (preg_match('/X11/', $ua, $matches)) {
      $infos = array_merge($infos, array(
        'platform_company'  =>'PC', 
      	'platform_model'    =>'',
        'platform_type'     =>'computer',
        'platform_format'   =>'desktop',
      	'system_title'      => 'UNIX',
      	'system_version'    => ''), 
      	isset($rep[$matches[0]])?$rep[$matches[0]]:array()
      );
    }
  }
  
  /*** check browser ***/
  //if ( !isset($infos['browser_title'])) {
    /* check opera mini */
  	if (preg_match('/Opera Mini\/([0-9]+\.[0-9]+)/', $ua, $matches))
      $infos = array_merge(array(
        'browser_title'=>'Opera Mini', 
      	'browser_version'=>$matches[1],
      	'platform_type'=>'handheld',
        'platform_format'=>'handheld',), $infos);
            
    /* check unsmartly written browser */
  	elseif (preg_match('/(Maxthon|Opera|webissimo|NintendoBrowser|Acoo ?Browser|Deepnet Explorer|Avant Browser|BrowseX|OffByOne|KKman|LBBROWSER|Maemo Browser|BIDUBrowser|UBrowser|SE |Airmail|EmbeddedWB|DX-Browser|Links|Sputnik)(?:\/| )?([a-z0-9\._]*)?/i', $ua, $matches)) {
      $rep = array('BIDUBrowser'=>'Baidu Brower', 'SE '=>'Sogou Explorer', 'AcooBrowser' => 'Acoo Browser', 'EmbeddedWB'=>'Delphi Embedded Web Browser');
      $infos = array_merge($infos, array(
	    'browser_title'     => isset($rep[$matches[1]])?$rep[$matches[1]]:$matches[1],
      	'browser_version'   => isset($matches[2])?$matches[2]:'',
      ));
    }
    
    /* check compatible level 2 browsers */
    elseif (preg_match('/(Yowser|MQQBrowser)\/([a-z0-9\._]*)?/i', $ua, $matches)) {
      $rep = array('MQQBrowser'=>'Mobile QQBrowser');
	  $infos = array_merge($infos, array(
	    'browser_title'     => isset($rep[$matches[1]])?$rep[$matches[1]]:$matches[1],
      	'browser_version'   => isset($matches[2])?$matches[2]:'',
      ));
    }
    
    /* check Chrome/Safari/Firefox/Explorer compatible browsers, to be tested before usual browsers */
    elseif (preg_match('/(YaBrowser|OPR|IceDragon|Dragon|CriOS|Adventurer|Sleipnir|BoBrowser|Dolfin|ChromePlus|Phoenix|Shiretoko|NS8|MiuiBrowser|SamsungBrowser\/CrossApp|SamsungBrowser|Vivaldi|Qt|Iceweasel|Puffin|Firebird|FBAV|app-ipad-CoteMaison|QQBrowser|PaleMoon|Arora|Edge|Cheshire|MicroMessenger|Getter|Dooble|amaya|Roccat|QupZilla|MMS|Iron|ACHEETAHI|OPiOS|Beonex|LibertyBrowser|LinkedIn|SeaMonkey|Cyberfox|Focus|Fennec|K-Meleon|CoolNovo|QuickLook|GSA|Electron|NG)\/([a-z0-9\._]*)?/i', $ua, $matches)) {
      $rep = array('OPR'=>'Opera', 'CriOS'=>'Chrome', 'Dragon'=>'IceDragon', 'NS8'=>'Netscape', 'Firebird'=>'Thunderbird', 'FBAV'=>'Facebook App', 'app-ipad-CoteMaison'=>'C&ocirc;t&eacute; Maison App', 'amaya'=>'Amaya', 'MMS'=>'Opera Neon', 'ACHEETAHI'=>'CM Browser', 'OPiOS'=>'Opera mini', 'Focus'=>'Firefox Focus', 'GSA'=>'Google Search App', 'NG'=>'Browser NG');
	  $infos = array_merge($infos, array(
	    'browser_title'     => isset($rep[$matches[1]])?$rep[$matches[1]]:$matches[1],
      	'browser_version'   => isset($matches[2])?$matches[2]:'',
      ));
    }
        
    /* check no version written browser */
    elseif (preg_match('/(HeadlessChrome|Iron|Advanced Browser)/', $ua, $matches)) {
      $rep = array();
      $infos = array_merge($infos, array(
	    'browser_title'     => isset($rep[$matches[1]])?$rep[$matches[1]]:$matches[1],
      ));
    }
    
    /* check some other browsers */
    elseif (preg_match('/(Edge|TencentTraveler)/i', $ua, $matches)) {
      $rep = array('TencentTraveler'=>'TT Explorer');
	  $infos = array_merge($infos, array(
	    'browser_title'=>isset($rep[$matches[1]])?$rep[$matches[1]]:$matches[1],
      	'browser_version'=>''));
    }
    
    /* check gen computer browsers */
  	elseif (preg_match('/(Chromium|Netscape|Camino|Minefield|Fennec|Firefox|Galeon|iCab|Konqueror|OmniWeb|IEMobile|Shiira|NetNewsWire|Symphony|Lynx|Crazy Browser|UCBrowser|GoBrowser|Cobra|ELinks|HotJava|Tor Browser|Dillo|FDM)(?:\/| )?([a-z0-9\._]*)/', $ua, $matches)) {
      $rep = array('FDM'=>'Free Download Manager',);
      $infos = array_merge(array(
        'platform_type'     => 'computer',
        'browser_title'     => isset($rep[$matches[1]])?$rep[$matches[1]]:$matches[1], 
      	'browser_version'   => str_replace('_','.',$matches[2])), $infos);
    }
    
    /* check chrome browser - separated from gen case of alternative browser using Chrome user agent */
    elseif (preg_match('/(Chrome)(?:\/| )?([a-z0-9\._]*)/', $ua, $matches)) {
      $infos = array_merge(array(
        'platform_type'     => 'computer',
        'browser_title'     => 'Chrome', 
      	'browser_version'   => str_replace('_','.',$matches[2])), $infos);
  
      /* Amigo's Mail.ru web browser based on chrome (and using chrome version) */
      if (preg_match('/(MRCHROME)/', $ua, $matches))
        $infos['browser_title'] = 'Amigo';
    }
    
    /* check gen mobile browsers */
  	elseif (preg_match('/(Dorado WAP-Browser)(?:\/| )?([a-z0-9\._]*)/', $ua, $matches)) {
      $rep = array('Dorado WAP-Browser'=>'Dorado');
      $infos = array_merge(array(
        'platform_type'     => 'handheld',
        'platform_format'   => 'handheld',
        'browser_title'     => $matches[1], 
      	'browser_version'   => str_replace('_','.',$matches[2])), $infos);
    }
    
    /* check gen browser : ?? */
  	elseif (preg_match('/Version\/([a-z0-9\._]*)( Mobile)? Safari\//', $ua, $matches)) {
  	  if ( $infos['system_title'] == 'Android')
  	    $infos = array_merge(array(
  	        'browser_title'=>'Chrome'.(isset($matches[2])?$matches[2]:''), 
      	    'browser_version'=>str_replace('_','.',$matches[1])
      	), $infos);
  	  else
        $infos = array_merge(array(
            'browser_title'=>'Safari'.(isset($matches[2])?$matches[2]:''), 
      	    'browser_version'=>str_replace('_','.',$matches[1])
      	), $infos);
    } 

    /* check no version detection browser */
  	elseif (preg_match('/(Opera Mobi)/', $ua, $matches))
      $infos = array_merge(array('browser_title'=>$matches[1], 
      	'browser_version'=>''), $infos);
      
    /* check undeterminated safari version */
  	elseif (preg_match('/(Safari|AppleWebKit)/', $ua, $matches)) {
  	  if ($infos['system_title'] == 'Android') {
        $infos = array_merge(array(
            'browser_title'=>'Android browser', 
      	    'browser_version'=>'',
      	), $infos);
  	  } else {
        $infos = array_merge(array(
            'browser_title'=>'Safari compatible', 
      	    'browser_version'=>'',
      	), $infos);
      }
    }
    
    /* check America Online Browser */
    elseif (preg_match('/America Online Browser ([a-z0-9\._]*);/', $ua, $matches))
      $infos = array_merge(array('browser_title'=>'America Online Browser', 
      	'browser_version'=>str_replace('_','.',$matches[1])), $infos);
  	
    /* check msie */
  	elseif (preg_match('/MSIE ?([a-z0-9\._]*)( |;|\-|\))/', $ua, $matches))
      $infos = array_merge(array(
        'browser_title'=>'Internet Explorer', 
      	'browser_version'=>str_replace('_','.',$matches[1])
      ), $infos);
  	
    /* check IE Mobile detection */
  	elseif (preg_match('/(IEMobile)(?:\ )([a-z0-9\._]*)/', $ua, $matches))
      $infos = array_merge(array('browser_title'=>'IE Mobile', 
      	'browser_version'=>str_replace('_','.',$matches[2])), $infos);
      	
    /* check trident compatible browsers */
  	elseif (preg_match('/(Trident\/)([a-z0-9\._]*)/', $ua, $matches))
  	  if ( preg_match('/rv:11.0/', $ua, $m))
  	    $infos = array_merge(array(
  	        'browser_title'     => 'Internet Explorer', 
      	    'browser_version'   => '11.0',
      	), $infos);
  	  else
        $infos = array_merge(array(
            'browser_title'     => 'Trident compatible', 
      	    'browser_version'   => str_replace('_','.',$matches[2]),
      	), $infos);
    
    /* check old netscape */
    elseif (preg_match('/^Mozilla\/([1-4].[0-9]{1,2})/', $ua, $matches))
      $infos = array_merge(array(
        'browser_title'     => 'Netscape', 
      	'browser_version'   => $matches[1],
      ), $infos);
      
    /* check WMP */
    elseif (preg_match('/^Windows-Media-Player\/([^\(]*)|Media Player Classic/', $ua, $matches))
      $infos = array_merge(array(
        'browser_title'     => 'Microsoft Windows Media Player', 
      	'browser_version'   => isset($matches[1])?$matches[1]:'',
      	'system_title'      =>'Windows',
      ), $infos);
    
    
    /* check FrontPage */
    elseif (preg_match('/^MSFrontPage\/([^\(]*)/', $ua, $matches))
      $infos = array_merge(array(
        'browser_title'     => 'Microsoft FrontPage', 
      	'browser_version'   => $matches[1],
      	'system_title'      =>'Windows',
      ), $infos);
      
    /* check Zoo Tycoon 2 Client */
    elseif (preg_match('/^Zoo Tycoon 2 Client/', $ua, $matches))
      $infos = array_merge(array(
        'browser_title'     => 'Microsoft Zoo Tycoon 2 Client', 
      	'browser_version'   => '',
      	'system_title'      =>'Windows',
      ), $infos);
  
    /* check MoonBrowser */
    elseif (preg_match('/MoonBrowser \(([^\(]*)\)/', $ua, $matches))
      $infos = array_merge(array(
        'browser_title'     => 'Moon Browser', 
      	'browser_version'   => $matches[1],
      	'system_title'      =>'Windows',
      ), $infos);
    
    /* check Barca */
    elseif (preg_match('/^Barca\/([^\(]*)/', $ua, $matches))
      $infos = array_merge(array(
        'browser_title'     => 'Barca', 
      	'browser_version'   => $matches[1],
      	'system_title'      =>'Windows',
      ), $infos);
      
    /* check Microsoft Data Access Internet Publishing Provider DAV */
    elseif (preg_match('/^Microsoft Data Access Internet Publishing Provider DAV$/', $ua, $matches))
      $infos = array_merge(array($infos, 
        'browser_title'     => 'Office (2000 and superior) WebDav client ', 
      	'system_title'      =>'Windows',
      ));  
       
    /* check Microsoft Office */
    elseif (preg_match('/^(Microsoft Office [A-Za-z0-9\ ]*)$/', $ua, $matches))
      $infos = array_merge(array($infos, 
        'browser_title'     => $matches[1], 
      	'system_title'      =>'Windows',
      ));  
      
    /* check HotJava */
    elseif (preg_match('/^HotJava\/([^\(]*)/', $ua, $matches))
      $infos = array_merge(array(
        'browser_title'     => 'HotJava', 
      	'browser_version'   => $matches[1],
      ), $infos);
      
    /* check MAUI WAP Browser  */
    elseif (preg_match('/^MAUI( |_)WAP( |_)Browser/', $ua, $matches))
      $infos = array_merge(array(
        'browser_title'     => 'MAUI WAP Browser', 
      	'browser_version'   => '',
      	'platform_type'     => 'handheld',
        'platform_format'   => 'handheld',
      ), $infos);
    
    /* check Gecko compatible */
    elseif (preg_match('/Gecko/', $ua, $matches))
      $infos = array_merge(array(
        'browser_title'     => 'Firefox compatible', 
      ), $infos);
  
    /* set type to "visitor" if not defined and browser title set */
    if (!isset($infos['platform_type']) and isset($infos['browser_title']) and $infos['browser_title'] != '')
      $infos['platform_type'] = 'computer';
    if ((!isset($infos['platform_format']) or $infos['platform_format'] == '') and isset($infos['browser_title']) and $infos['browser_title'] != '')
      $infos['platform_format'] = 'desktop';
        
    if (!isset($infos['platform_format']) or $infos['platform_format'] == '' or $infos['platform_format'] == 'desktop') {
      /* check for generic mobile */
      if (preg_match('/mobile/i', $ua, $matches))
        $infos = array_merge($infos,array(
          'platform_format'=>'handheld'
        ));
  
      /* check for generic tablet */
      elseif (preg_match('/tablet/i', $ua, $matches))
        $infos = array_merge($infos, array(
          'platform_format'=>'tablet'
        ));
  }
  
  /* check browser and version */
  if (isset($infos['browser_version']) and isset($maxVersions['browser'][$infos['browser_title']]) and version_compare($infos['browser_version'], $maxVersions['browser'][$infos['browser_title']]) > 0)
    return $fake;
  
  /* return result */
  return _client_mergeUAInfos($req, $infos);
}

/*
 * return bot index if bot
 * @param string $ua
 * @return mixed
 * @access public
 */
function client_checkIsBot($ua=false) {
  /* get user agent */
  if (!$ua)	$ua = client_getUserAgent();
 
  /* load known bots */
  $knownBots = client_getKnownBots();
  
  /* build detection pattern */
  $detectionPattern = implode('|', array_keys($knownBots));
  $detectionPattern = preg_replace ('/(\/|\(|\)|\.)/', '\\\$1', $detectionPattern);
  $detectionPattern = '/'.$detectionPattern.'/i';

  /* start detection and return result */
  if ( preg_match ( $detectionPattern, strtolower($ua), $result ) )
    return $result[0];
  return false;
}

/*
 * return bot info if bot
 * @param string $ua
 * @return mixed
 * @access public
 */
function client_getBotInfos($bot='') {
  $knownBots = client_getKnownBots();
  
  if (isset($knownBots[$bot]))
    return $knownBots[$bot];
  return array();
}


/*
 * return bot info from user agent
 * @param string $ua
 * @return mixed
 * @access public
 */
function client_getBotInfosFromUserAgent($ua='') {
  $knownBots = client_getKnownBots();
    
  /* build detection pattern */
  $detectionPattern = implode('|', array_keys($knownBots));
  $detectionPattern = preg_replace ('/(\/|\(|\)|\.|\+)/', '\\\$1', $detectionPattern);
  $detectionPattern = '/'.$detectionPattern.'/i';

  /* start detection and return result */
  if ( preg_match ( $detectionPattern, strtolower($ua), $result ) )
    return $knownBots[$result[0]];
  return false;
}

/*
 * return known bots list
 * @return array
 * @access private
 */
function client_getKnownBots() {
  $knownBots = array();
  
  /* Ideogram Design bot */
  $knownBots['idpunchbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',            
	'bot_title'=>'IDPunchBot',
	'bot_url'=>'http://www.ideogram-design.fr/Punch_Bot.html',
	'engine_title'=>'Ideogram Design',
	'engine_url'=>'http://www.ideogram-design.fr/');
  
  /* import.io crawler bot (to be inserted before GoogleBot, use GoogleBot in user agent)  */
  $knownBots['googlebot/2.1; +http://import.io'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',            
	'bot_title'=>'import.io crawler',
	'bot_url'=>'http://support.import.io/knowledgebase/articles/265494-crawler-faq',
	'engine_title'=>'import.io',
	'engine_url'=>'http://import.io');
  
  /* Dictanova crawler bot (to be inserted before GoogleBot, use GoogleBot in user agent) / to complete */
  $knownBots['googlebot/1.0 (dictanova'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',            
	'bot_title'=>'Dictanova crawler',
	'bot_url'=>'',
	'engine_title'=>'Dictanova',
	'engine_url'=>'http://www.dictanova.com/');
  $knownBots['googlebot/1.0 (googlebot; http://www.google.com/bot.html; crawler at dictanova dot com)'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',            
	'bot_title'=>'Dictanova crawler',
	'bot_url'=>'',
	'engine_title'=>'Dictanova',
	'engine_url'=>'http://www.dictanova.com/');
  
  /* googlebot_poolmer (to be inserted before GoogleBot, use GoogleBot in user agent) / to complete */
  $knownBots['googlebot_poolmer'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',            
	'bot_title'=>'poolmer',
	'bot_url'=>'',
	'engine_title'=>'',
	'engine_url'=>'');
  
  /* WebHistoryBot (to be inserted before GoogleBot, use GoogleBot in user agent) / to complete */
  $knownBots['webhistorybot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',            
	'bot_title'=>'WebHistoryBot',
	'bot_url'=>'',
	'engine_title'=>'',
	'engine_url'=>'');
	
  /* startmebot (to be inserted before GoogleBot, use GoogleBot in user agent) / to complete */
  $knownBots['googlebot/2.1; startmebot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',            
	'bot_title'=>'startmebot',
	'bot_url'=>'https://start.me/bot',
	'engine_title'=>'start.me',
	'engine_url'=>'https://start.me');
	
  /* Yahoo mobile bot : Yahoo! Slurp */
  $knownBots['mobile (compatible; yahoo! slurp'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'handheld',            
	'bot_title'=>'Yahoo! Slurp Mobile',
	'bot_url'=>'http://help.yahoo.com/help/us/ysearch/slurp',
	'engine_title'=>'Yahoo!',
	'engine_url'=>'http://www.yahoo.com');
	
  /* Yahoo bot : Yahoo! Slurp */
  $knownBots['yahoo! slurp'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',            
	'bot_title'=>'Yahoo! Slurp',
	'bot_url'=>'http://help.yahoo.com/help/us/ysearch/slurp',
	'engine_title'=>'Yahoo!',
	'engine_url'=>'http://www.yahoo.com');
	
  /* Yahoo bot : yahoo/Nutch */
  $knownBots['yahoo/nutch'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',            
	'bot_title'=>'',
	'bot_url'=>'',
	'engine_title'=>'Yahoo!',
	'engine_url'=>'http://www.yahoo.com');

  /* Google mobile bot : Googlebot-Mobile */
  $knownBots['safari/537.36 (compatible; googlebot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'handheld', 
	'bot_title'=>'Googlebot Mobile',
	'bot_url'=>'http://www.google.com/bot.html',
	'engine_title'=>'Google',
	'engine_url'=>'http://www.google.com');
	
  /* Google mobile bot : Googlebot-Mobile */
  $knownBots['safari/600.1.4 (compatible; googlebot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'handheld', 
	'bot_title'=>'Googlebot Mobile',
	'bot_url'=>'http://www.google.com/bot.html',
	'engine_title'=>'Google',
	'engine_url'=>'http://www.google.com');
 
  /* Google mobile bot : Googlebot-Mobile */
  $knownBots['safari/8536.25 (compatible; googlebot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'handheld', 
	'bot_title'=>'Googlebot Mobile',
	'bot_url'=>'http://www.google.com/bot.html',
	'engine_title'=>'Google',
	'engine_url'=>'http://www.google.com');
    
  /* Google mobile bot : Googlebot-Mobile */
  $knownBots['googlebot-mobile'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'handheld', 
	'bot_title'=>'Googlebot Mobile',
	'bot_url'=>'http://www.google.com/bot.html',
	'engine_title'=>'Google',
	'engine_url'=>'http://www.google.com');
    
  /* Google bot : Googlebot */
  $knownBots['googlebot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop', 
	'bot_title'=>'Googlebot',
	'bot_url'=>'http://www.google.com/bot.html',
	'engine_title'=>'Google',
	'engine_url'=>'http://www.google.com');	
 
  /* Google bot : Google Favicon */
  $knownBots['google favicon'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop', 
	'bot_title'=>'Google favicon',
	'bot_url'=>'http://www.google.com/bot.html',
	'engine_title'=>'Google',
	'engine_url'=>'http://www.google.com');
	
  /* Google bot : Google Web Preview */
  $knownBots['google web preview'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop', 
	'bot_title'=>'Google Web Preview',
	'bot_url'=>'http://www.google.com/bot.html',
	'engine_title'=>'Google',
	'engine_url'=>'http://www.google.com');

  /* Google-Site-Verification */
  $knownBots['google-site-verification'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop', 
	'bot_title'=>'Google-Site-Verification',
	'bot_url'=>'http://www.google.com/bot.html',
	'engine_title'=>'Google',
	'engine_url'=>'http://www.google.com');
    
  /* Google Media Partners */
  $knownBots['mediapartners-google'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Google-MediaPartners',
    'bot_url'=>'',
    'engine_title'=>'Google',
    'engine_url'=>'http://www.google.com');
    
  /* Google AdsBot */
  $knownBots['adsbot-google'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Google-AdsBot',
    'bot_url'=>'http://www.google.com/adsbot.html',
    'engine_title'=>'Google',
    'engine_url'=>'http://www.google.com');
    
  /* Apple bot : Applebot */
  $knownBots['applebot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop', 
    'bot_title'=>'Applebot',
    'bot_url'=>'https://support.apple.com/en-us/HT204683',
    'engine_title'=>'Apple',
    'engine_url'=>'http://www.apple.com');
         
  /* Voila bot : VoilaBot */
  $knownBots['voilabot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
	'bot_title'=>'VoilaBot',
	'bot_url'=>'',
	'engine_title'=>'Voila',
	'engine_url'=>'http://www.voila.com');

  /* MSN Search bot : msnbot */
  $knownBots['msnbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'msnbot',
    'bot_url'=>'http://search.msn.com/msnbot.htm',
    'engine_title'=>'MSN Search',
    'engine_url'=>'http://search.msn.com');
  
  /* MSN Search bot : hidden behind fake user agent */
  $knownBots['msie 9.0; windows nt 6.1; trident/5.0;  trident/5.0)'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'msnbot',
    'bot_url'=>'http://search.msn.com/msnbot.htm',
    'engine_title'=>'MSN Search',
    'engine_url'=>'http://search.msn.com');
  
  /* MSN Search bot : hidden behind fake user agent */
  $knownBots['msie 9.0; windows nt 6.0; trident/5.0;  trident/5.0)'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'msnbot',
    'bot_url'=>'http://search.msn.com/msnbot.htm',
    'engine_title'=>'MSN Search',
    'engine_url'=>'http://search.msn.com');

  /* MS Bing mobile bot : bingbot */
  $knownBots['safari/9537.53 (compatible; bingbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'handheld',
    'bot_title'=>'Bingbot Mobile',
    'bot_url'=>'http://www.bing.com/bingbot.htm',
    'engine_title'=>'bing',
    'engine_url'=>'http://www.bing.com/');

  /* MS Bing bot : bingbot */
  $knownBots['bingbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'bingbot',
    'bot_url'=>'http://www.bing.com/bingbot.htm',
    'engine_title'=>'bing',
    'engine_url'=>'http://www.bing.com/');

  /* MS Bing bot : BingPreview */
  $knownBots['bingpreview'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'BingPreview',
    'bot_url'=>'http://www.bing.com/bingbot.htm',
    'engine_title'=>'bing',
    'engine_url'=>'http://www.bing.com/');
    
  /* MS Bing bot : BingLocalSearch */
  $knownBots['binglocalsearch'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'BingLocalSearch',
    'bot_url'=>'http://www.bing.com/bingbot.htm',
    'engine_title'=>'bing',
    'engine_url'=>'http://www.bing.com/');
    
  /*  MS Search 6.0 Robot  */
  $knownTools['ms search 6.0 robot'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Microsoft Sharepoint Crawler',
    'tool_url'=>'',
    'engine_title'=>'Microsoft',
    'engine_url'=>'http://www.microsoft.com');
	
  /* Facebook bot : facebot */
  $knownBots['facebot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'FaceBot',
    'bot_url'=>'',
    'engine_title'=>'Facebook',
    'engine_url'=>'http://www.facebook.com/');
    
  /* Cuill search engine : Twiceler */
  $knownBots['cuill.com'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Twiceler',
    'bot_url'=>'http://www.cuill.com/twiceler/robot.html',
    'engine_title'=>'Cuill Inc.',
    'engine_url'=>'http://www.cuill.com');
    
  /* Exalead bot : Exabot */
  $knownBots['exabot.com'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Exabot',
    'bot_url'=>'http://www.exabot.com/go/robot',
    'engine_title'=>'Exalead',
    'engine_url'=>'http://www.exalead.com');

  /* ExaleadCloudView bot : Exabot */
  $knownBots['exaleadcloudview'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'ExaleadCloudView',
    'bot_url'=>'http://www.exabot.com/go/robot',
    'engine_title'=>'Exalead',
    'engine_url'=>'http://www.exalead.com');

  /* Exabot-Thumbnails */
  $knownBots['exabot-thumbnails'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Exabot-Thumbnails',
    'bot_url'=>'https://www.exalead.com/search/webmasterguide',
    'engine_title'=>'Exalead',
    'engine_url'=>'http://www.exalead.com');

  /* Baidu mobile bot */
  $knownBots['mobile safari/10600.6.3 (compatible; baiduspider'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'handheld',
    'bot_title'=>'Baiduspider',
    'bot_url'=>'http://www.baidu.com/search/spider.htm',
    'engine_title'=>'Baidu',
    'engine_url'=>'http://www.baidu.com');

  /* Baidu bot : Baiduspider */    
  $knownBots['baiduspider'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Baiduspider',
    'bot_url'=>'http://www.baidu.com/search/spider.htm',
    'engine_title'=>'Baidu',
    'engine_url'=>'http://www.baidu.com');

  /* old baidu bot */
  $knownBots['baidu.com'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Baiduspider',
    'bot_url'=>'http://www.baidu.com/search/spider.htm',
    'engine_title'=>'Baidu',
    'engine_url'=>'http://www.baidu.com');

  /* Baidu bot : BaiduImagespider */    
  $knownBots['baiduimagespider'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'BaiduImagespider',
    'bot_url'=>'http://www.baidu.com/search/spider.htm',
    'engine_title'=>'Baidu',
    'engine_url'=>'http://www.baidu.com');
    
  /* Gigablast bot : Gigabot */
  $knownBots['gigablast.com'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'GigaBot',
    'bot_url'=>'http://www.gigablast.com/spider.html',
    'engine_title'=>'Gigablast',
    'engine_url'=>'http://www.gigablast.com');
  
  /* Gigablast bot : Gigabot */
  $knownBots['gigabot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'GigaBot',
    'bot_url'=>'http://www.gigablast.com/spider.html',
    'engine_title'=>'Gigablast',
    'engine_url'=>'http://www.gigablast.com');
    
  /* GigablastOpensource : Gigabot */
  $knownBots['gigablastopensource'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'GigaBlast Open Source',
    'bot_url'=>'http://www.gigablast.com/spider.html',
    'engine_title'=>'Gigablast',
    'engine_url'=>'http://www.gigablast.com');
    
  /* GigablastOpensource : Gigabot */
  $knownBots['g-i-g-a-b-o-t'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'GigaBlast Open Source',
    'bot_url'=>'http://www.gigablast.com/spider.html',
    'engine_title'=>'Gigablast',
    'engine_url'=>'http://www.gigablast.com');
    
  /* Amfibi bot : Cabot/Nutch */
  $knownBots['amfibi.com'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Cabot/Nutch',
    'bot_url'=>'http://www.amfibi.com/cabot/',
    'engine_title'=>'Amfibi',
    'engine_url'=>'http://www.amfibi.com');
    
  /* Healthline bot : NimbleCrawler */
  $knownBots['healthline.com'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'NimbleCrawler',
    'bot_url'=>'',
    'engine_title'=>'HealthLine',
    'engine_url'=>'http://www.healthline.com');
    
  /* Ask bot : Ask Jeeves/Teoma */
  $knownBots['ask.com'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Ask Jeeves/Teoma',
    'bot_url'=>'http://about.ask.com/en/docs/about/webmasters.shtml',
    'engine_title'=>'Ask.com',
    'engine_url'=>'http://www.ask.com');       
       
  /* FAST bot : FAST Enterprise Crawler */
  $knownBots['fast.no'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'FAST Enterprise Crawler',
    'bot_url'=>'',
    'engine_title'=>'Fast',
    'engine_url'=>'http://www.fast.no');
       
  /* entireweb bot : Seedy Spider */
  $knownBots['entireweb.com'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Speedy Spider',
    'bot_url'=>'http://www.entireweb.com/about/search_tech/speedy_spider',
    'engine_title'=>'Entire Web',
    'engine_url'=>'http://www.entireweb.com');
       
  /* Naver bot : Yeti */
  $knownBots['naver.com'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Yeti',
    'bot_url'=>'http://help.naver.com/robots/',
    'engine_title'=>'Naver (cn)',
    'engine_url'=>'http://www.naver.com');
    
  /* Naver bot : Yeti */
  $knownBots['naver.me'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Yeti',
    'bot_url'=>'http://naver.me/bot',
    'engine_title'=>'Naver (cn)',
    'engine_url'=>'http://www.naver.com');
    
  /* CommonCrawl bot : CCBot */
  $knownBots['commoncrawl.org'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'ccBot',
    'bot_url'=>'http://www.commoncrawl.org/bot.html',
    'engine_title'=>'CommonCrawl',
    'engine_url'=>'http://www.commoncrawl.org');
       
  /* Acoon bot : Acoon-Robot */
  $knownBots['acoon.de'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Acoon-Robot',
    'bot_url'=>'http://www.acoon.de',
    'engine_title'=>'Acoon',
    'engine_url'=>'http://www.acoon.de');
    
  /* Whois bot : SurveyBot */
  $knownBots['whois.sc'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'SurveyBot',
    'bot_url'=>'http://www.whois.sc',
    'engine_title'=>'Whois',
    'engine_url'=>'http://www.whois.sc');
       
  /* Wauuu bot : wauuu engine */
  $knownBots['wauuu.com'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'wauuu engine',
    'bot_url'=>'http://www.wauuu.com',
    'engine_title'=>'Wauuu',
    'engine_url'=>'http://www.wauuu.com');     
       
  /* Searchme bot : Charlotte */
  $knownBots['searchme.com'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Charlotte',
    'bot_url'=>'http://www.searchme.com/support/',
    'engine_title'=>'Searchme',
    'engine_url'=>'http://www.searchme.com');
       
  /* WebAlta bot : WebAlta Crawler */
  $knownBots['webalta.net'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'WebAlta Crawler',
    'bot_url'=>'http://www.webalta.net/ru/about_webmaster.html',
    'engine_title'=>'WebAlta',
    'engine_url'=>'http://www.webalta.net');

  /* Gais bot : Gaisbot */
  $knownBots['gais.cs.ccu.edu.tw'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Gaisbot',
    'bot_url'=>'http://gais.cs.ccu.edu.tw/robot.php',
    'engine_title'=>'Global Area Information Servers',
    'engine_url'=>'http://gais.cs.ccu.edu.tw');

  /* ScoutJet bot */
  $knownBots['scoutjet.com'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'ScoutJet',
    'bot_url'=>'http://www.scoutjet.com/',
    'engine_title'=>'',
    'engine_url'=>'');
      
  /* Discovery engine bot : discobot */
  $knownBots['discoveryengine.com'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'discobot',
    'bot_url'=>'http://discoveryengine.com/discobot.html',
    'engine_title'=>'Discovery Engine',
    'engine_url'=>'http://discoveryengine.com');
       
  /* Touche bot */
  $knownBots['touche.com.ve'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Touche',
    'bot_url'=>'',
    'engine_title'=>'Touch&eacute;',
    'engine_url'=>'http://www.touche.com.ve');

  /* Morfeo bot : holmes */
  $knownBots['morfeo.centrum.cz'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'holmes',
    'bot_url'=>'',
    'engine_title'=>'Morfeo',
    'engine_url'=>'http://morfeo.centrum.cz');

  /* Mail.ru bot */
  $knownBots['mail.ru'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'',
    'bot_url'=>'',
    'engine_title'=>'Mail.ru',
    'engine_url'=>'http://www.mail.ru');

  /* Rankiva bot : rankivabot */
  $knownBots['rankiva.com'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Rankivabot',
    'bot_url'=>'http://www.rankiva.com/rankivabot/index.php',
    'engine_title'=>'Rankiva',
    'engine_url'=>'http://www.rankiva.com');
       
  /* iearthworm bot */
  $knownBots['iearthworm'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'iearthworm',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
       
  /* Alexa bot : ia_archiver */
  $knownBots['ia_archiver'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'ia_archiver',
    'bot_url'=>'http://www.alexa.com/site/help/webmasters',
    'engine_title'=>'Alexa',
    'engine_url'=>'http://www.alexa.com');
       
  /* Alexa site audit */
  $knownBots['alexa site audit'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'alexa site audit',
    'bot_url'=>'http://www.alexa.com/site/help/webmasters',
    'engine_title'=>'Alexa',
    'engine_url'=>'http://www.alexa.com');

  /* Mirago bot : Henri */
  $knownBots['mirago.co.uk'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Henri, the Mirago Robot',
    'bot_url'=>'http://www.miragorobot.com',
    'engine_title'=>'Mirago',
    'engine_url'=>'http://www.mirago.co.uk');

  /* Cote d'azur bot : SunIndexer */
  $knownBots['cote.azur.fr'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'SunIndexer',
    'bot_url'=>'http://www.cote.azur.fr/SunIndexer.html',
    'engine_title'=>'C&ocirc;te d\'Azur',
    'engine_url'=>'http://www.cote.azur.fr');

  /* MSR-ISRCCrawler */
  $knownBots['MSR-ISRCCrawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'MSR-ISRCCrawler',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');

  /* DeepIndex bot */
  $knownBots['deepindex'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'',
    'bot_url'=>'',
    'engine_title'=>'DeepIndex',
    'engine_url'=>'http://www.deepindex.fr');

  /* Powerset bot */
  $knownBots['powerset.com'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'',
    'bot_url'=>'',
    'engine_title'=>'Powerset',
    'engine_url'=>'http://www.powerset.com');

  /* Zippp bot */
  $knownBots['zippp.com'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'ZipppBot',
    'bot_url'=>'',
    'engine_title'=>'Zippp',
    'engine_url'=>'http://www.zippp.com');

  /* insynchro.net bot */
  $knownBots['insynchro.net'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'SearchHub',
    'bot_url'=>'',
    'engine_title'=>'insynchro',
    'engine_url'=>'http://www.insynchro.net');

  /* yandex bot */
  $knownBots['yandex'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Yandex',
    'bot_url'=>'',
    'engine_title'=>'Yandex',
    'engine_url'=>'http://www.yandex.ru');

  /* feedoo bot */
  $knownBots['feedoo'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Feedoo7 Crawler',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');

  /* guruji bot */
  $knownBots['gurujibot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'GurujiBot',
    'bot_url'=>'http://www.guruji.com/en/WebmasterFAQ.html',
    'engine_title'=>'Guruji',
    'engine_url'=>'http://www.guruji.com');

  /* Sogou Spider bot */
  $knownBots['sogou'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Sogou Spider',
	'bot_url'=>'http://www.sogou.com/docs/help/webmasters.htm',
	'engine_title'=>'Sogou',
	'engine_url'=>'http://www.sogou.com');
    
  /* CamontSpider bot */
  $knownBots['camontspider'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'CamontSpider',
    'bot_url'=>'http://epweb2.ph.bham.ac.uk/user/slater/camont/info.html',
    'engine_title'=>'',
    'engine_url'=>'');

  /* Chen-Li bot */
  $knownBots['chen li'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Chen Li/Nutch',
    'bot_url'=>'http://chenli.com.cn',
    'engine_title'=>'',
    'engine_url'=>'');

  /* ICC-Crawler bot */
  $knownBots['icc-crawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'ICC-Crawler',
    'bot_url'=>'http://kc.nict.go.jp/project1/crawl.html',
    'engine_title'=>'Knowledge Clustered Group',
    'engine_url'=>'');

  /* KIT webcrawler bot */
  $knownBots['kit webcrawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'KIT webcrawler',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
    
  /* Linguee Bot */
  $knownBots['linguee bot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Linguee Bot',
    'bot_url'=>'http://www.linguee.com/bot',
    'engine_title'=>'Linguee',
    'engine_url'=>'http://www.linguee.com');

  /* MLBot Bot */
  $knownBots['mlbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'MLBot',
	'bot_url'=>'http://www.metadatalabs.com/mlbot',
	'engine_title'=>'metadata labs',
	'engine_url'=>'http://www.metadatalabs.com');

  /*  DotBot */
  $knownBots['dotbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'DotBot',
	'bot_url'=>'http://www.opensiteexplorer.org/dotbot',
	'engine_title'=>'DotNetDotCom',
	'engine_url'=>'http://www.dotnetdotcom.org');

  /*  KaloogaBot */
  $knownBots['kaloogabot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'KaloogaBot',
	'bot_url'=>'http://www.kalooga.com/info.html?page=crawler',
	'engine_title'=>'Kalooga',
	'engine_url'=>'http://www.kalooga.com');

  /* Majestic 12 Bot */
  $knownBots['mj12bot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'MJ12Bot',
    'bot_url'=>'http://www.majestic12.co.uk/bot.php?+',
    'engine_title'=>'Majestic 12',
    'engine_url'=>'http://www.majestic12.co.uk/');
 
  /* Netcraft Survey Agent */
  $knownBots['netcraftsurveyagent'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'NetcraftSurveyAgent',
    'bot_url'=>'',
    'engine_title'=>'Netcraft',
    'engine_url'=>'http://news.netcraft.com');
    
  /* Netcraft Survey Agent */
  $knownBots['netcraft ssl server survey'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'NetcraftSurveyAgent',
    'bot_url'=>'',
    'engine_title'=>'Netcraft',
    'engine_url'=>'http://news.netcraft.com');
 
  /* Pure search bot */
  $knownBots['purebot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'PureBot',
    'bot_url'=>'',
    'engine_title'=>'Pure Search',
    'engine_url'=>'http://www.puritysearch.net');

  /* Suchbaer Bot */
  $knownBots['suchbaerbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'SuchbaerBot',
    'bot_url'=>'http://bot.suchbaer.de/info.html',
    'engine_title'=>'Suchbaer',
    'engine_url'=>'http://www.suchbaer.de');

  /* Tagoo Bot */
  $knownBots['tagoobot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Tagoobot',
    'bot_url'=>'',
    'engine_title'=>'Tagoo',
    'engine_url'=>'http://www.tagoo.ru');

  /* youdao bot */
  $knownBots['youdaobot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'YoudaoBot',
    'bot_url'=>'http://www.youdao.com/help/webmaster/spider',
    'engine_title'=>'Youdao',
    'engine_url'=>'http://www.youdao.com');

  /* aihit bot */
  $knownBots['aihitbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'aiHitBot',
    'bot_url'=>'',
    'engine_title'=>'aiHit',
    'engine_url'=>'http://www.aihit.com');

  /* sbider bot */
  $knownBots['sbider'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'SBIder',
    'bot_url'=>'http://www.sitesell.com/sbider.html',
    'engine_title'=>'SiteSell',
    'engine_url'=>'http://www.sitesell.com');

  /* Sosospider bot */
  $knownBots['sosospider'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Sosospider',
    'bot_url'=>'http://help.soso.com/webspider.htm',
    'engine_title'=>'Soso',
    'engine_url'=>'http://www.soso.com');

  /* turnitin bot */
  $knownBots['turnitinbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'TurnitinBot',
    'bot_url'=>'http://www.turnitin.com/robot/crawlerinfo.html',
    'engine_title'=>'Turnitin',
    'engine_url'=>'http://www.turnitin.com');

  /* SiteExplorer bot */
  $knownBots['siteexplorer'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'',
    'bot_url'=>'',
    'engine_title'=>'SiteExplorer',
    'engine_url'=>'http://siteexplorer.info/');

  /* envolk bot */
  $knownBots['envolk'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'envolk',
    'bot_url'=>'http://www.envolk.com/envolkspiderinfo.html',
    'engine_title'=>'envolk',
    'engine_url'=>'http://www.envolk.com');

  /* findlinks bot */
  $knownBots['findlinks'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'findlinks',
    'bot_url'=>'http://wortschatz.uni-leipzig.de/findlinks/',
    'engine_title'=>'FindLinks',
    'engine_url'=>'');

  /* magpie bot */
  $knownBots['magpie-crawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'magpie-crawler',
     'bot_url'=>'',
     'engine_title'=>'BrandWatch',
     'engine_url'=>'http://www.brandwatch.net');

  /* taptu bot */
  $knownBots['taptubot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'taptubot',
    'bot_url'=>'http://www.taptu.com/corp/taptubot',
    'engine_title'=>'Taptu',
    'engine_url'=>'http://www.taptu.com');

  /* kosmix bot */
  $knownBots['voyager'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'voyager',
    'bot_url'=>'http://www.kosmix.com/crawler.html',
    'engine_title'=>'Kosmix',
    'engine_url'=>'http://www.kosmix.com');
        
  /* SiteBot bot */
  $knownBots['sitebot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'SiteBot',
    'bot_url'=>'http://www.sitebot.org/robot/',
    'engine_title'=>'SiteBot',
    'engine_url'=>'http://www.sitebot.org');
       
  /* MnoGoSearch bot */
  $knownBots['mnogosearch'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'MnoGoSearch',
    'bot_url'=>'',
    'engine_title'=>'MnoGoSearch',
    'engine_url'=>'http://www.mnogosearch.org/');
		
  /* Ezooms bot */
  $knownBots['ezooms'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Ezooms',
    'bot_url'=>'',
    'engine_title'=>'Ezooms',
    'engine_url'=>'http://www.ezooms.com/');
       
  /* Quirina Hurdler */
  $knownBots['quirina'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Qirina Hurdler',
    'bot_url'=>'http://www.qirina.com/hurdler.html',
    'engine_title'=>'Qirina',
    'engine_url'=>'http://www.qirina.com/');
       
  /* AboutUs bot */
  $knownBots['aboutus'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'AboutUs bot',
    'bot_url'=>'',
    'engine_title'=>'AboutUs',
    'engine_url'=>'http://www.aboutus.org/');
       
  /* Bixo labs bot */
  $knownBots['bixolabs.com'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Bixo labs bot',
    'bot_url'=>'',
    'engine_title'=>'Bixo labs',
    'engine_url'=>'http://bixolabs.com/');
       
  /* Birubot */
  $knownBots['birubot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Birubot',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
       
  /* unwindfetchor */
  $knownBots['unwindfetchor'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'UnwindFetchor',
    'bot_url'=>'',
    'engine_title'=>'Gnip',
    'engine_url'=>'http://www.gnip.com/');
		
  /* Crystal Semantics Bot */
  $knownBots['crystalsemanticsbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Crystal Semantics Bot',
    'bot_url'=>'http://www.crystalsemantics.com/service-navigation/imprint/useragent/',
    'engine_title'=>'Crystal Semantics',
    'engine_url'=>'http://www.crystalsemantics.com/');
		
  /* PaperLiBot */
  $knownBots['paperlibot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'PaperLiBot',
    'bot_url'=>'',
    'engine_title'=>'Amazon',
    'engine_url'=>'http://aws.amazon.com/');
       
  /* Suggy Bot */
  $knownBots['suggybot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'SuggyBot',
    'bot_url'=>'http://blog.suggy.com/was-ist-suggy/suggy-webcrawler/',
    'engine_title'=>'Suggy',
    'engine_url'=>'http://blog.suggy.com/');
		
  /* NjuiceBot */
  $knownBots['njuicebot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'NjuiceBot',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
       
  /* OrangeAsk Bot */
  $knownBots['orangeaskbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'OrangeAskBot',
    'bot_url'=>'',
    'engine_title'=>'OrangeAsk',
    'engine_url'=>'http://www.orangeask.com/');
       
  /* regios Bot */
  $knownBots['regios.com'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'',
    'bot_url'=>'',
    'engine_title'=>'Regios',
    'engine_url'=>'http://www.regios.org/');
       
  /* gravitext Bot : iudex */
  $knownBots['iudex'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Iudex',
    'bot_url'=>'http://gravitext.com/iudex/',
    'engine_title'=>'',
    'engine_url'=>'');
       
  /* crawl-e bot */
  $knownBots['crawl-e'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'CRAWL-E',
    'bot_url'=>'http://code.google.com/p/crawl-e/',
    'engine_title'=>'',
    'engine_url'=>'');
       
  /* Cligoo bot */
  $knownBots['cligoorobot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'CligooRobot',
    'bot_url'=>'',
    'engine_title'=>'Cligoo',
    'engine_url'=>'http://www.cligoo.de/');
       
  /* lexxe bot */
  $knownBots['lexxebot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'lexxebot',
    'bot_url'=>'',
    'engine_title'=>'Lexxe',
    'engine_url'=>'http://lexxe.com/');
		
  /* worio bot */
  $knownBots['worio.com'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'',
    'bot_url'=>'',
    'engine_title'=>'Worio',
    'engine_url'=>'http://worio.com/');
       
  /* summify bot */
  $knownBots['summify'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'',
    'bot_url'=>'',
    'engine_title'=>'Summify',
    'engine_url'=>'http://summify.com/');
       
  /* cmsworldmap bot */
  $knownBots['cmsworldmap'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'',
    'bot_url'=>'',
    'engine_title'=>'CMS World Map',
    'engine_url'=>'http://www.cmsworldmap.com/');
       
  /* GeoHasher bot */
  $knownBots['geohasher.gotdns.org'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'GeoHasher/Nutch',
    'bot_url'=>'',
    'engine_title'=>'GeoHasher',
    'engine_url'=>'http://geohasher.gotdns.org/');
       
  /* Ahrefs bot */
  $knownBots['ahrefsbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'AhrefsBot',
    'bot_url'=>'http://ahrefs.com/robot/',
    'engine_title'=>'Ahrefs',
    'engine_url'=>'https://ahrefs.com');
	
  /* linkdexbot bot */
  $knownBots['linkdexbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'linkdexbot',
    'bot_url'=>'http://www.linkdex.com/about/bots/',
    'engine_title'=>'Linkdex',
    'engine_url'=>'http://www.linkdex.com');
	
  /* Orange Bot */
  $knownBots['orangebot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'OrangeBot',
    'bot_url'=>'mailto:support.orangebot@orange.com',
    'engine_title'=>'Orange',
    'engine_url'=>'');
	
  /* bulk-retrieval Bot */
  $knownBots['bulk-retrieval'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'bulk-retrieval',
    'bot_url'=>'http://varocarbas.com/bulk-retrieval_bot.php',
    'engine_title'=>'',
    'engine_url'=>'http://varocarbas.com');
       
  /* surveybot */
  $knownBots['surveybot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'SurveyBot',
    'bot_url'=>'http://www.domaintools.com/webmasters/surveybot.php',
    'engine_title'=>'DomainTools',
    'engine_url'=>'http://www.domaintools.com');	
    
  /* Daumoa */
  $knownBots['daumoa'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Daumoa',
    'bot_url'=>'http://tab.search.daum.net/aboutWebSearch.html',
    'engine_title'=>'Daum',
    'engine_url'=>'http://www.daum.net');
  
  /* Daum */
  $knownBots['daum'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'',
    'bot_url'=>'',
    'engine_title'=>'Daum',
    'engine_url'=>'http://www.daum.net');
	
  /* FRCrawler */
  $knownBots['frcrawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'FRCrawler',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
       
  /* FRCrawler, alternative  */
  $knownBots['fr_crawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'FRCrawler',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
	
  /* IstellaBot */
  $knownBots['istellabot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'IstellaBot',
    'bot_url'=>'http://www.istella.it/en/',
    'engine_title'=>'Tiscali',
    'engine_url'=>'http://www.tiscali.it/');
	
  /* SeznamBot */
  $knownBots['seznambot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'SeznamBot',
    'bot_url'=>'http://fulltext.sblog.cz',
    'engine_title'=>'Seznam',
    'engine_url'=>'https://www.seznam.cz');
  
  /* SeznamBot screenshot generator */
  $knownBots['seznam screenshot-generator'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Seznam screenshot-generator',
    'bot_url'=>'http://fulltext.sblog.cz',
    'engine_title'=>'Seznam',
    'engine_url'=>'https://www.seznam.cz');
	
  /* 360Spider */
  $knownBots['360spider'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'360Spider',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
	
  /* memoryBot */
  $knownBots['memorybot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'memoryBot',
    'bot_url'=>'http://mignify.com/bot.html',
    'engine_title'=>'[m]ignify',
    'engine_url'=>'https://mignify.com');
	
  /* Cliqzbot */
  $knownBots['cliqzbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Cliqzbot',
    'bot_url'=>'http://cliqz.com/company/cliqzbot',
    'engine_title'=>'Cliqz',
    'engine_url'=>'https://www.cliqz.com');

  /* YioopBot */
  $knownBots['yioopbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'YioopBot',
    'bot_url'=>'http://www.yioop.com/bot.php',
    'engine_title'=>'Yioop!',
    'engine_url'=>'http://www.yioop.com');
       
  /* Wotbox */
  $knownBots['wotbox'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Wotbox Web Crawler',
    'bot_url'=>'http://www.wotbox.com/bot/',
    'engine_title'=>'Wotbox',
    'engine_url'=>'http://www.wotbox.com');
	
  /* XoviBot */
  $knownBots['xovibot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'XoviBot',
    'bot_url'=>'http://www.xovibot.net',
    'engine_title'=>'',
    'engine_url'=>'');
	
  /* PagesInventory */
  $knownBots['pagesinventory'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'PagesInventory',
    'bot_url'=>'http://www.pagesinventory.com',
    'engine_title'=>'',
    'engine_url'=>'');
	
  /* DigExt; DTS Agent */
  $knownBots['digext; dts agent'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'DigExt; DTS Agent',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
       
  /* TestCrawler/Nutch */
  $knownBots['testcrawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'TestCrawler/Nutch',
    'bot_url'=>'http://balihoo.com/',
    'engine_title'=>'',
    'engine_url'=>'');
	
  /* WebTarantula.com Crawler */
  $knownBots['webtarantula'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'WebTarantula.com Crawler',
    'bot_url'=>'',
    'engine_title'=>'WebTarantula.com',
    'engine_url'=>'http://webtarantula.com');
	
  /* CMS Crawler */
  $knownBots['cmscrawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'',
    'bot_url'=>'',
    'engine_title'=>'CMS Crawler',
    'engine_url'=>'http://www.cmscrawler.com');
	
  /* cuwhois */
  $knownBots['cuwhois'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'cuwhois',
    'bot_url'=>'',
    'engine_title'=>'cuwhois.com',
    'engine_url'=>'http://www.cuwhois.com/');

  /* Vagabondo */
  $knownBots['vagabondo'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Vagabondo',
    'bot_url'=>'',
    'engine_title'=>'WiseGuys',
    'engine_url'=>'http://www.wise-guys.nl/');
	
  /* Vagabondo */
  $knownBots['vagabondo'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Vagabondo',
    'bot_url'=>'',
    'engine_title'=>'WiseGuys',
    'engine_url'=>'http://www.wise-guys.nl/');
	
  /* StatRank */
  $knownBots['statrank'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'StatRank',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
	
  /* spbot */
  $knownBots['spbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'spbot',
    'bot_url'=>'http://OpenLinkProfiler.org/bot',
    'engine_title'=>'OpenLink Profiler',
    'engine_url'=>'http://www.openlinkprofiler.org');
	
  /* YisouSpider */
  $knownBots['yisouspider'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'YisouSpider',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');

  /* DomainAppender */
  $knownBots['domainappender'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'DomainAppender',
    'bot_url'=>'http://www.profound.net/domainappender',
    'engine_title'=>'Profound Networks',
    'engine_url'=>'http://www.profound.net');
	
  /* ltx71 - (http://ltx71.com/) */
  $knownBots['ltx71'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'ltx71',
    'bot_url'=>'http://ltx71.com/',
    'engine_title'=>'',
    'engine_url'=>'');
	
  /* StudioFACA */
  $knownBots['studiofaca'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'',
    'bot_url'=>'',
    'engine_title'=>'StudioFACA',
    'engine_url'=>'http://www.studiofaca.com/');
	
  /* yacybot */
  $knownBots['yacybot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'yacybot',
    'bot_url'=>'http://yacy.net/bot.html',
    'engine_title'=>'Yacy',
    'engine_url'=>'http://yacy.net/fr/index.html');
       
  /* SISTRIX Crawler */
  $knownBots['sistrix'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'SISTRIX Crawler',
    'bot_url'=>'http://crawler.sistrix.net/',
    'engine_title'=>'SISTRIX',
    'engine_url'=>'http://www.sistrix.net/');
    
  /* BLEXBot */
  $knownBots['blexbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'BLEXBot',
    'bot_url'=>'',
    'engine_title'=>'webmeup',
    'engine_url'=>'http://webmeup-crawler.com/');
	
  /* Qwantify */
  $knownBots['qwantify'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Qwantify',
    'bot_url'=>'',
    'engine_title'=>'Qwant',
    'engine_url'=>'https://www.qwant.com');
       
  /* meanpathbot */
  $knownBots['meanpathbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'meanpathbot',
    'bot_url'=>'http://www.meanpath.com/meanpathbot.html',
    'engine_title'=>'meanpath',
    'engine_url'=>'http://www.meanpath.com');
       
  /* Add Catalog */
  $knownBots['add catalog'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Add Catalog',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
       
  /* SemrushBot */
  $knownBots['semrushbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'SemrushBot',
    'bot_url'=>'http://www.semrush.com/bot/',
    'engine_title'=>'SEMrush',
    'engine_url'=>'http://www.semrush.com');
       
  /* DuckDuckGo */
  $knownBots['duckduckgo'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'',
    'bot_url'=>'',
    'engine_title'=>'DuckDuckGo',
    'engine_url'=>'http://duckduckgo.com');
       
  /* PageAnalyzer */
  $knownBots['pageanalyzer'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'PageAnalyzer',
    'bot_url'=>'http://www.ranks.nl/docs/page-analyzer/troubleshooting',
    'engine_title'=>'RANKS NL',
    'engine_url'=>'http://www.ranks.nl');
       
  /* Superarama.com bot : Tamara */
  $knownBots['superarama.com-tarama-botu'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Tarama',
    'bot_url'=>'',
    'engine_title'=>'Superarama.com',
    'engine_url'=>'http://www.superarama.com');
       
  /* MixrankBot */
  $knownBots['mixrankbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'MixrankBot',
    'bot_url'=>'crawler@mixrank.com',
    'engine_title'=>'Mixrank',
    'engine_url'=>'');
       
  /* finbot */
  $knownBots['finbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'FINbot',
    'bot_url'=>'',
    'engine_title'=>'findbot.com',
    'engine_url'=>'http://findbot.com');
  
  /* Babya Discoverer */
  $knownBots['babya discoverer'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Babya Discoverer',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
    
  /* ContextAd Bot */
  $knownBots['contextad bot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'ContextAd Bot',
    'bot_url'=>'',
    'engine_title'=>'PulsePoint',
    'engine_url'=>'http://www.pulsepoint.com');
    
  /* RSSMicro.com */
  $knownBots['rssmicro.com'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'RSSMicro.com RSS/Atom Feed Robot',
    'bot_url'=>'',
    'engine_title'=>'RSS Micro',
    'engine_url'=>'http://www.rssmicro.com');
    
  /* Sisabot */
  $knownBots['sisabot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'sisabot',
    'bot_url'=>'http://www.sisabot.com/bot.html',
    'engine_title'=>'Sisabot',
    'engine_url'=>'http://www.sisabot.com');
    
  /* go 1 */
  $knownBots['go 1'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Go 1.1',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* SimpleCrawler */
  $knownBots['simplecrawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'SimpleCrawler',
    'bot_url'=>'https://github.com/cgiffard/node-simplecrawler',
    'engine_title'=>'',
    'engine_url'=>'');
    
  /* Gluten Free Crawler */
  $knownBots['gluten free crawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Gluten Free Crawler',
    'bot_url'=>'http://glutenfreepleasure.com',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* netEstate NE Crawler */
  $knownBots['netestate ne crawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'netEstate NE Crawler',
    'bot_url'=>'http://www.website-datenbank.de',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* idmarch bot */
  $knownBots['idmarch'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'idmarch',
    'bot_url'=>'https://www.idmarch.org/bot.html',
    'engine_title'=>'International Digital Media Archive',
    'engine_url'=>'https://www.idmarch.org');
  
  /* ips-agent */
  $knownBots['ips-agent'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'ips-agent',
    'bot_url'=>'',
    'engine_title'=>'Verisign',
    'engine_url'=>'http://www.verisign.com');
  
  /* seegnifybot */
  $knownBots['seebot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'seegnifybot',
    'bot_url'=>'http://www.seegnify.com/bot',
    'engine_title'=>'Seegnify',
    'engine_url'=>'http://www.seegnify.com');
  
  /* riddler */
  $knownBots['riddler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'riddler',
    'bot_url'=>'http://riddler.io/about',
    'engine_title'=>'riddler.io',
    'engine_url'=>'https://riddler.io');
  
  /* MegaIndex.ru */
  $knownBots['megaindex.ru'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'MegaIndex',
    'bot_url'=>'http://megaindex.com/crawler',
    'engine_title'=>'MegaIndex',
    'engine_url'=>'https://MegaIndex.ru');
    
  /* PHPCrawl */
  $knownBots['phpcrawl'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'PHPCrawl',
    'bot_url'=>'http://phpcrawl.cuab.de/about.html',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* worldwebheritage.org */
  $knownBots['worldwebheritage.org'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'worldwebheritage.org',
    'bot_url'=>'crawl@worldwebheritage.org',
    'engine_title'=>'',
    'engine_url'=>''); 
  
  /* worldwebheritage.org */
  $knownBots['y!j-asr'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Y!J-ASR',
    'bot_url'=>'http://www.yahoo-help.jp/app/answers/detail/p/595/a_id/42716/',
    'engine_title'=>'Yahoo Japan',
    'engine_url'=>'http://www.yahoo.co.jp/');
  
  /* SurdotlyBot */
  $knownBots['surdotlybot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'SurdotlyBot',
    'bot_url'=>'http://sur.ly/bot.html',
    'engine_title'=>'sur.ly',
    'engine_url'=>'http://sur.ly');
  
  /* RogerBot */
  $knownBots['rogerbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'RogerBot',
    'bot_url'=>'',
    'engine_title'=>'Moz',
    'engine_url'=>'https://moz.com');
    
  /* NerdyBot */
  $knownBots['nerdybot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'NerdyBot',
    'bot_url'=>'http://nerdybot.com/',
    'engine_title'=>'NerdyData',
    'engine_url'=>'http://nerdydata.com/');
    
  /* AdnormCrawler */
  $knownBots['adnormcrawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'AdnormCrawler',
    'bot_url'=>'',
    'engine_title'=>'Adnorm',
    'engine_url'=>'http://www.adnorm.com/');
    
  /* Apercite */
  $knownBots['apercite'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Apercite',
    'bot_url'=>'http://www.apercite.fr/robot/index.html',
    'engine_title'=>'Apercite',
    'engine_url'=>'http://www.apercite.fr/');
    
  /* Lipperhey-Kaus-Australis */
  $knownBots['lipperhey-kaus-australis'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Lipperhey Spider',
    'bot_url'=>'https://www.lipperhey.com/en/about/',
    'engine_title'=>'Dataprovider',
    'engine_url'=>'https://www.dataprovider.com/');
    
  /* Lipperhey SEO Service */
  $knownBots['lipperhey seo'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Lipperhey Spider',
    'bot_url'=>'https://www.lipperhey.com/en/about/',
    'engine_title'=>'Dataprovider',
    'engine_url'=>'https://www.dataprovider.com/');
    
  /* Dataprovider */
  $knownBots['dataprovider'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Dataprovider Spider',
    'bot_url'=>'https://www.dataprovider.com/spider/',
    'engine_title'=>'Dataprovider',
    'engine_url'=>'https://www.dataprovider.com/');
    
  /* SEOkicks-Robot */
  $knownBots['seokicks-robot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'SEOkicks-Robot',
    'bot_url'=>'http://www.seokicks.de/robot.html',
    'engine_title'=>'SEOkicks',
    'engine_url'=>'http://www.seokicks.de/');
    
  /* Focus Spider */
  $knownBots['focus spider'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Focus Spider',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* zeerch */
  $knownBots['zeerch'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Zeerch',
    'bot_url'=>'http://www.zeerch.com/zeerch2/bot.php',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* Linkpad */
  $knownBots['linkpad'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'LinkpadBot',
    'bot_url'=>'',
    'engine_title'=>'Linkpad',
    'engine_url'=>'http://www.linkpad.ru');
  
  /* MixBot */
  $knownBots['mixbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'MixBot',
    'bot_url'=>'',
    'engine_title'=>'MixData',
    'engine_url'=>'https://www.mixdata.com');
  
  /* TrueBot */
  $knownBots['truebot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'TrueBot',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* NetSeer crawler */
  $knownBots['netseer crawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'NetSeer crawler',
    'bot_url'=>'http://www.netseer.com/crawler.html',
    'engine_title'=>'NetSeer',
    'engine_url'=>'http://www.netseer.com');
  
  /* AdvBot */
  $knownBots['advbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'AdvBot',
    'bot_url'=>'http://advbot.net/bot.html',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* archive.org_bot */
  $knownBots['archive.org_bot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'archive.org_bot',
    'bot_url'=>'https://archive.org/details/archive.org_bot',
    'engine_title'=>'archive.org',
    'engine_url'=>'https://archive.org');
  
  /* Diffbot */
  $knownBots['diffbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Diffbot',
    'bot_url'=>'http://www.diffbot.com',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* GrapeshotCrawler */
  $knownBots['grapeshotcrawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'GrapeshotCrawler',
    'bot_url'=>'http://www.grapeshot.co.uk/crawler.php',
    'engine_title'=>'Grapeshot',
    'engine_url'=>'http://www.grapeshot.co.uk');
  
  /* LSSRocketCrawler */
  $knownBots['lssrocketcrawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'LSSRocketCrawler',
    'bot_url'=>'',
    'engine_title'=>'Lightspeed Systems',
    'engine_url'=>'http://www.lightspeedsystems.com');
  
  /* DomainMacroCrawler */
  $knownBots['domainmacrocrawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'DomainMacroCrawler',
    'bot_url'=>'',
    'engine_title'=>'DomainMacro',
    'engine_url'=>'http://domainmacro.com');
  
  /* ocrawler */
  $knownBots['ocrawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'ocrawler',
    'bot_url'=>'omax7828@yahoo.com',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* WeViKaBot */
  $knownBots['wevikabot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'WeViKaBot',
    'bot_url'=>'',
    'engine_title'=>'WeViKa',
    'engine_url'=>'http://www.wevika.de');
  
  /* HyperCrawl */
  $knownBots['hypercrawl'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'HyperCrawl',
    'bot_url'=>'http://www.seograph.net/bot.html',
    'engine_title'=>'SEO Graph',
    'engine_url'=>'http://www.seograph.net');
  
  /* psbot */
  $knownBots['psbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'psbot',
    'bot_url'=>'http://www.picsearch.com/bot.html',
    'engine_title'=>'Picsearch',
    'engine_url'=>'http://www.picsearch.com');
  
  /* BDCbot */
  $knownBots['bdcbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'BDCbot',
    'bot_url'=>'http://ecommerce.bigdatacorp.com.br/faq.aspx',
    'engine_title'=>'BigData',
    'engine_url'=>'http://www.bigdatacorp.info');
  
  /* Thunderstone */
  $knownBots['t-h-u-n-d-e-r-s-t-o-n-e'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Thunderstone',
    'bot_url'=>'http://search.thunderstone.com/texis/websearch/about.html',
    'engine_title'=>'Thunderstone',
    'engine_url'=>'http://search.thunderstone.com');
  
  /* Thunderstone */
  $knownBots['thunderstone'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Thunderstone',
    'bot_url'=>'http://search.thunderstone.com/texis/websearch/about.html',
    'engine_title'=>'Thunderstone',
    'engine_url'=>'http://search.thunderstone.com');
     
  /* Barkrowler - to be placed before Owler */
  $knownBots['barkrowler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Barkrowler',
    'bot_url'=>'http://www.exensa.com/crawl',
    'engine_title'=>'exenSa',
    'engine_url'=>'http://www.exensa.com');
  
  /* Owler */
  $knownBots['owler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Owler',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* maluuba-crawler */
  $knownBots['maluuba-crawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'maluuba-crawler',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* Digincore crawler */
  $knownBots['digincore crawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Digincore crawler',
    'bot_url'=>'',
    'engine_title'=>'Digincore.com',
    'engine_url'=>'https://www.digincore.com/index.php');
  
  /* Guardcrwlr */
  $knownBots['guardcrwlr'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Guardcrwlr',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* Dazoobot */
  $knownBots['dazoobot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Dazoobot',
    'bot_url'=>'',
    'engine_title'=>'Dazoo',
    'engine_url'=>'http://dazoo.fr');
  
  /* yelpspider */
  $knownBots['yelpspider'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'yelpspider',
    'bot_url'=>'',
    'engine_title'=>'Yelp',
    'engine_url'=>'http://yelp.com');
  
  /* SectorPages.com  */
  $knownBots['sectorpages.com'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'',
    'bot_url'=>'',
    'engine_title'=>'SectorPages.com',
    'engine_url'=>'http://sectorpages.com');
  
  /* SEOlyticsCrawler */
  $knownBots['seolyticscrawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'SEOlyticsCrawler',
    'bot_url'=>'http://crawler.seolytics.net/',
    'engine_title'=>'SEOlytics',
    'engine_url'=>'http://www.seolytics.com');
  
  /* Robot14 */
  $knownBots['robot14'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Robot14 spider',
    'bot_url'=>'http://www.robot14.com/bot.php',
    'engine_title'=>'Robot14',
    'engine_url'=>'http://www.robot14.com/');
  
  /* MojeekBot */
  $knownBots['mojeekbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'MojeekBot',
    'bot_url'=>'https://www.mojeek.com/bot.html',
    'engine_title'=>'Mojeek',
    'engine_url'=>'https://www.mojeek.com');
  
  /* Findxbot */
  $knownBots['findxbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Findxbot',
    'bot_url'=>'http://www.findxbot.com',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* Aloofly */
  $knownBots['aloofly'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'',
    'bot_url'=>'',
    'engine_title'=>'Aloofly',
    'engine_url'=>'http://aloofly.com');
  
  /* QuerySeekerSpider */
  $knownBots['queryseekerspider'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'QuerySeekerSpider',
    'bot_url'=>'http://queryseeker.com/bot.html',
    'engine_title'=>'QuerySeeker',
    'engine_url'=>'http://queryseeker.com');
  
  /* 007ac9 Crawler */
  $knownBots['007ac9 crawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'007ac9 Crawler',
    'bot_url'=>'http://crawler.007ac9.net',
    'engine_title'=>'Sistrix',
    'engine_url'=>'https://www.sistrix.com/');
    
  /* Plukkie */
  $knownBots['plukkie'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Plukkie',
    'bot_url'=>'http://www.botje.com/plukkie.htm',
    'engine_title'=>'Botje',
    'engine_url'=>'http://www.botje.com');
    
  /* Uptimebot */
  $knownBots['uptimebot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Uptimebot',
    'bot_url'=>'http://www.uptime.com/uptimebot',
    'engine_title'=>'Uptime',
    'engine_url'=>'http://www.uptime.com');

  /* CheckMarkNetwork */
  $knownBots['checkmarknetwork'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'CheckMark Network Crawler',
    'bot_url'=>'http://www.checkmarknetwork.com/spider.html/',
    'engine_title'=>'CheckMark Network',
    'engine_url'=>'http://www.checkmarknetwork.com/');

  /* RukiCrawler */
  $knownBots['rukicrawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'RukiCrawler',
    'bot_url'=>'http://ruki.rezko.net',
    'engine_title'=>'',
    'engine_url'=>'');

  /* electricmonk */
  $knownBots['electricmonk'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'ElectricMonk',
    'bot_url'=>'https://www.duedil.com/our-crawler',
    'engine_title'=>'DueDil',
    'engine_url'=>'https://www.duedil.com');

  /* DeuSu */
  $knownBots['deusu'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'DeuSu',
    'bot_url'=>'https://deusu.de',
    'engine_title'=>'deusu',
    'engine_url'=>'https://deusu.de/robot.html');

  /* Garlik */
  $knownBots['garlikcrawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'GarlikCrawler',
    'bot_url'=>'',
    'engine_title'=>'Garlik',
    'engine_url'=>'http://garlik.com/');

  /* Garlik */
  $knownBots['experibot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Experibot',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');

  /* SafeDNSBot */
  $knownBots['safednsbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'SafeDNSBot',
    'bot_url'=>'https://www.safedns.com/searchbot',
    'engine_title'=>'SafeDNS',
    'engine_url'=>'https://www.safedns.com/');
  
  /* SMTBot mobile */
  $knownBots['mobile/10a5376e safari/8536.25 (compatible; smtbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'handheld',
    'bot_title'=>'SMTBot',
    'bot_url'=>'http://www.similartech.com/smtbot',
    'engine_title'=>'SimilarTech',
    'engine_url'=>'http://www.similartech.com/');
  

  /* SMTBot */
  $knownBots['smtbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'SMTBot',
    'bot_url'=>'http://www.similartech.com/smtbot',
    'engine_title'=>'SimilarTech',
    'engine_url'=>'http://www.similartech.com/');

  /* DNSdelve */
  $knownBots['dnsdelve'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'',
    'bot_url'=>'',
    'engine_title'=>'DNSdelve',
    'engine_url'=>'http://www.dnsdelve.net');

  /* redback */
  $knownBots['redback'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'redback',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');

  /* seoscanners.net */
  $knownBots['seoscanners.net'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'seoscanners.net',
    'bot_url'=>'spider@seoscanners.net',
    'engine_title'=>'',
    'engine_url'=>'');

  /* yoozBot */
  $knownBots['yoozbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'yoozBot',
    'bot_url'=>'',
    'engine_title'=>'Yooz',
    'engine_url'=>'http://yooz.ir');

  /* contactbigdatafr */
  $knownBots['contactbigdatafr'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'contactbigdatafr',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');

  /* LinqiaCrawlerBot */
  $knownBots['linqiacrawlerbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'LinqiaCrawlerBot',
    'bot_url'=>'eng@linqia.com',
    'engine_title'=>'Linqia',
    'engine_url'=>'http://www.linqia.com');

  /* LinqiaRSSBot */
  $knownBots['linqiarssbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'LinqiaRSSBot',
    'bot_url'=>'eng@linqia.com',
    'engine_title'=>'Linqia',
    'engine_url'=>'http://www.linqia.com');

  /* ZoomBot */
  $knownBots['zoombot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'ZoomBot',
    'bot_url'=>'',
    'engine_title'=>'seozoom',
    'engine_url'=>'https://www.seozoom.it');
    
  /* eXenSa-DEW - to be added before bubing */
  $knownBots['exensa'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'eXenSa-DEW',
    'bot_url'=>'',
    'engine_title'=>'eXenSa',
    'engine_url'=>'http://www.exensa.com');

  /* BUbiNG */
  $knownBots['bubing'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'BUbiNG',
    'bot_url'=>'http://law.di.unimi.it/BUbiNG.html',
    'engine_title'=>'',
    'engine_url'=>'');

  /* CATExplorador */
  $knownBots['catexplorador'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'CATExplorador',
    'bot_url'=>'http://domini.cat/catexplorador.html',
    'engine_title'=>'',
    'engine_url'=>'');

  /* aisou */
  $knownBots['aisou'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'aisou',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');

  /* IDBot */
  $knownBots['idbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'IDBot',
    'bot_url'=>'http://www.id-search.xyz/bot.html',
    'engine_title'=>'ID-Search<sup>xyz</sup>',
    'engine_url'=>'http://www.id-search.xyz');

  /* DomainCrawler */
  $knownBots['domaincrawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'DomainCrawler',
    'bot_url'=>'info@domaincrawler.com',
    'engine_title'=>'DomainCrawler',
    'engine_url'=>'http://www.domaincrawler.com');

  /* parsijoo-bot */
  $knownBots['parsijoo-bot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'parsijoo-bot',
    'bot_url'=>'ehsanmousa@parsijoo.ir',
    'engine_title'=>'Parsijoo',
    'engine_url'=>'http://www.parsijoo.ir/');

  /* bnf.fr_bot */
  $knownBots['bnf.fr_bot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'bnf.fr_bot',
    'bot_url'=>'http://www.bnf.fr/fr/outils/a.dl_web_capture_robot.html',
    'engine_title'=>'Biblioth&egrave;que Nationale de France',
    'engine_url'=>'http://www.bnf.fr');

  /* sSearch Crawler */
  $knownBots['ssearch_bot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'sSearch Crawler',
    'bot_url'=>'',
    'engine_title'=>'sSearch',
    'engine_url'=>'http://www.semantissimo.de');

  /* wonderbot/JS */
  $knownBots['wonderbot/js'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'wonderbot',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');

  /* SecurityResearch.bot */
  $knownBots['securityresearch.bot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'SecurityResearch.bot',
    'bot_url'=>'http://besome1.info/securityresearchbot.html',
    'engine_title'=>'',
    'engine_url'=>'');

  /* deeris */
  $knownBots['deeris'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Deeris',
    'bot_url'=>'http://www.deeris.com',
    'engine_title'=>'',
    'engine_url'=>'');

  /* Searchie */
  $knownBots['searchie'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Searchie',
    'bot_url'=>'https://www.searchie.org',
    'engine_title'=>'',
    'engine_url'=>'');

  /* AugDiscovery-Bot */
  $knownBots['augdiscovery-bot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'AugDiscovery-Bot',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* ToweYandext */
  $knownBots['toweyabot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Toweyabot',
    'bot_url'=>'',
    'engine_title'=>'Toweya',
    'engine_url'=>'toweya.com');
  
  /* RSSingBot */
  $knownBots['rssingbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'RSSingBot',
    'bot_url'=>'',
    'engine_title'=>'RSSing',
    'engine_url'=>'http://www.rssing.com');
  
  /* exif-search */
  $knownBots['www.exif-search.com'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Heritrix',
    'bot_url'=>'',
    'engine_title'=>'Exif Search',
    'engine_url'=>'https://www.exif-search.com');
  
  /* Digincore bot */
  $knownBots['digincore bot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Digincore bot',
    'bot_url'=>'https://www.digincore.com/crawler.html',
    'engine_title'=>'Digincore',
    'engine_url'=>'https://www.digincore.com');
  
  /* Wopabot */
  $knownBots['wopabot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Wopabot',
    'bot_url'=>'',
    'engine_title'=>'Wopa',
    'engine_url'=>'https://www.wopa.fr/');
  
  /* linkapediabot */
  $knownBots['linkapediabot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'linkapediabot',
    'bot_url'=>'',
    'engine_title'=>'Linkapedia',
    'engine_url'=>'http://www.linkapedia.com');
  
  /* WBSearchBot */
  $knownBots['wbsearchbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'WBSearchBot',
    'bot_url'=>'http://www.warebay.com/bot.html',
    'engine_title'=>'Warebay',
    'engine_url'=>'http://www.warebay.com');
  
  /* BacklinkCrawler */
  $knownBots['backlinkcrawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'BacklinkCrawler',
    'bot_url'=>'http://www.backlinktest.com/crawler.html',
    'engine_title'=>'backlink test',
    'engine_url'=>'http://www.backlinktest.com');
  
  /* ParsijooBot */
  $knownBots['parsijoobot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'ParsijooBot',
    'bot_url'=>'crawler@parsijoo.ir',
    'engine_title'=>'Parsijoo',
    'engine_url'=>'http://www.parsijoo.ir');
  
  /* Stratagems Kumo */
  $knownBots['stratagems kumo'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Stratagems Kumo',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* ExactSeekCrawler */
  $knownBots['exactseekcrawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'ExactSeekCrawler',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* Jaunt */
  $knownBots['jaunt/'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Jaunt',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* UXCrawlerBot  */
  $knownBots['uxcrawlerbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'UXCrawlerBot ',
    'bot_url'=>'',
    'engine_title'=>'Zium',
    'engine_url'=>'http://zium.co');
  
  /* HRCrawlerBot  */
  $knownBots['hrcrawlerbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'HRCrawlerBot ',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* LinqiaMetadataDownloaderBot  */
  $knownBots['linqiametadatadownloaderbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'LinqiaMetadataDownloaderBot ',
    'bot_url'=>'eng@linqia.com',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* roboto  */
  $knownBots['roboto'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'roboto ',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* 2ADAMbot */
  $knownBots['2adambot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'2ADAMbot ',
    'bot_url'=>'',
    'engine_title'=>'2adam',
    'engine_url'=>'http://www.2adam.com');
  
  /* mfibot */
  $knownBots['mfibot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'mfibot ',
    'bot_url'=>'',
    'engine_title'=>'mfisoft',
    'engine_url'=>'http://www.mfisoft.ru/analyst/');
  
  /* FlippyBearBot */
  $knownBots['flippybearbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'FlippyBearBot ',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* vebidoobot */
  $knownBots['vebidoobot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'vebidoobot ',
    'bot_url'=>'https://blog.vebidoo.de/vebidoobot/',
    'engine_title'=>'vebidoo',
    'engine_url'=>'https://www.vebidoo.de');
  
  /* Xaldon WebSpider */
  $knownBots['xaldon'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Xaldon WebSpider ',
    'bot_url'=>'',
    'engine_title'=>'Xaldon',
    'engine_url'=>'http://www.xaldon.de');
  
  /* panscient.com */
  $knownBots['panscient.com'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'',
    'bot_url'=>'',
    'engine_title'=>'panscient.com',
    'engine_url'=>'http://panscient.com');
  
  /* semanticbot */
  $knownBots['semanticbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'semanticbot',
    'bot_url'=>'info@semanticaudience.com',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* LinqiaScrapeBot */
  $knownBots['linqiascrapebot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'LinqiaScrapeBot',
    'bot_url'=>'',
    'engine_title'=>'Linqia',
    'engine_url'=>'http://www.linqia.com');
  
  /* focusbot */
  $knownBots['focusbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'focusbot',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* orbiter */
  $knownBots['orbiter'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'orbiter',
    'bot_url'=>'',
    'engine_title'=>'DailyOrbit',
    'engine_url'=>'http://dailyorbit.com');
  
  /* spuhexbot */
  $knownBots['spuhexbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'SpuhexBot',
    'bot_url'=>'',
    'engine_title'=>'Spuhex',
    'engine_url'=>'http://www.spuhex.com');
  
  /* iZSearch.com  */
  $knownBots['izsearch.com'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'',
    'bot_url'=>'',
    'engine_title'=>'iZSearch.com',
    'engine_url'=>'http://iZSearch.com');
  
  /* servernfo.com  */
  $knownBots['servernfo.com'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'',
    'bot_url'=>'',
    'engine_title'=>'servernfo.com',
    'engine_url'=>'http://servernfo.com/');
  
  /* PrivacyAwareBot */
  $knownBots['privacyawarebot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'PrivacyAwareBot',
    'bot_url'=>'',
    'engine_title'=>'Privacy Aware',
    'engine_url'=>'http://www.privacyaware.org');
  
  /* WbSrch */
  $knownBots['wbsrch'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'',
    'bot_url'=>'',
    'engine_title'=>'WbSrch',
    'engine_url'=>'http://wbsrch.com');
  
  /* Cuasarbot */
  $knownBots['cuasarbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Cuasarbot',
    'bot_url'=>'',
    'engine_title'=>'Cuasar',
    'engine_url'=>'http://www.cuasar.com/spider_beta/');
  
  /* Lippershey */
  $knownBots['lippershey'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Lippershey',
    'bot_url'=>'https://www.lipperhey.com/en/about/website-spider/',
    'engine_title'=>'Lipperhey',
    'engine_url'=>'https://www.lipperhey.com');
  
  /* ImplisenseBot */
  $knownBots['implisensebot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'ImplisenseBot',
    'bot_url'=>'',
    'engine_title'=>'Implisense',
    'engine_url'=>'http://implisense.com');
  
  /* coccoc */
  $knownBots['coccoc'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'coccocbot',
    'bot_url'=>'',
    'engine_title'=>'coccoc',
    'engine_url'=>'http://help.coccoc.com/');
  
  /* coccoc */
  $knownBots['coccoc'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'coccocbot',
    'bot_url'=>'',
    'engine_title'=>'coccoc',
    'engine_url'=>'http://help.coccoc.com/');
  
  /* ltbot */
  $knownBots['ltbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'ltbot',
    'bot_url'=>'',
    'engine_title'=>'Knowledge Discovery Scientific Literature',
    'engine_url'=>'http://www.kdsl.tu-darmstadt.de/de/kdsl/research-program/crawling-and-semantic-structuring/');
  
  /* HRCrawler */
  $knownBots['hrcrawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'HRCrawler',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* Simple crawler */
  $knownBots['simple crawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Simple crawler',
    'bot_url'=>'http://crawler.own3d.pl',
    'engine_title'=>'',
    'engine_url'=>'');

  /* uMBot */
  $knownBots['umbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'uMBot',
    'bot_url'=>'',
    'engine_title'=>'ubermetrics',
    'engine_url'=>'http://www.ubermetrics-technologies.com');

  /* JobFeed discovery script */
  $knownBots['jobfeed discovery script'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'uMBot',
    'bot_url'=>'',
    'engine_title'=>'JobFeed',
    'engine_url'=>'http://www.jobfeed.com');

  /* LinkStats Bot */
  $knownBots['linkstats bot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'LinkStats Bot',
    'bot_url'=>'',
    'engine_title'=>'Peter Shumacher',
    'engine_url'=>'http://web-eifel.de');

  /* ichiro */
  $knownBots['ichiro'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'ichiro',
    'bot_url'=>'http://search.goo.ne.jp/option/use/sub4/sub4-1/',
    'engine_title'=>'',
    'engine_url'=>'');

  /* archive-fr.com */
  $knownBots['archive-fr.com'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'archive-fr.com',
    'bot_url'=>'http://archive-fr.com/bot',
    'engine_title'=>'Archive-fr.com',
    'engine_url'=>'http://archive-fr.com/');

  /* serbot */
  $knownBots['serbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'serbot',
    'bot_url'=>'http://www.serdec.com/bot.html',
    'engine_title'=>'serdec',
    'engine_url'=>'http://www.serdec.com');

  /* TWMBot */
  $knownBots['twmbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'TWMBot',
    'bot_url'=>'',
    'engine_title'=>'The Web Miner',
    'engine_url'=>'https://thewebminer.com');

  /* LinkWalker */
  $knownBots['linkwalker'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'LinkWalker',
    'bot_url'=>'',
    'engine_title'=>'Brand Protect',
    'engine_url'=>'http://www.brandprotect.com');

  /* SpiderLing */
  $knownBots['spiderling'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'SpiderLing',
    'bot_url'=>'http://nlp.fi.muni.cz/trac/spiderling',
    'engine_title'=>'BiWeC',
    'engine_url'=>'https://nlp.fi.muni.cz/projects/biwec/');

  /* SafeSearch microdata crawler */
  $knownBots['safesearch microdata crawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'SafeSearch',
    'bot_url'=>'https://safesearch.avira.com',
    'engine_title'=>'Avira',
    'engine_url'=>'https://www.avira.com/fr/index');

  /* Corporama matcher */
  $knownBots['corporama matcher'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Corporama matcher',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');

  /* ActiveWorlds */
  $knownBots['activeworlds'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'',
    'bot_url'=>'',
    'engine_title'=>'ActiveWorlds',
    'engine_url'=>'https://www.activeworlds.com/web/index.php');
  
  /* HELLO Crawler */
  $knownBots['hello crawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'HELLO Crawler',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* Larbin */
  $knownBots['larbin'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'larbin',
    'bot_url'=>'http://larbin.sourceforge.net',
    'engine_title'=>'',
    'engine_url'=>'');
  
  $knownBots['binlar'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'larbin',
    'bot_url'=>'http://larbin.sourceforge.net',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* IpixelY */
  $knownBots['ipixely'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'IpixelY',
    'bot_url'=>'',
    'engine_title'=>'IpixelY',
    'engine_url'=>'http://www.ipixely.xyz');
  
  /* JamesBOT */
  $knownBots['james bot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'JamesBOT',
    'bot_url'=>'http://cognitiveseo.com/bot.html',
    'engine_title'=>'Congitive SEO',
    'engine_url'=>'http://cognitiveseo.com');
    
  $knownBots['cognitiveseo'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'JamesBOT',
    'bot_url'=>'http://cognitiveseo.com/bot.html',
    'engine_title'=>'Congitive SEO',
    'engine_url'=>'http://cognitiveseo.com');
  
  /* aranea */
  $knownBots['aranea'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Aranea',
    'bot_url'=>'http://aranea.juls.savba.sk/',
    'engine_title'=>'Web Corpora &amp; Corpus Linguistics Portal',
    'engine_url'=>'http://aranea.juls.savba.sk/aranea_about.html');
  
  /* VenusCrawler */
  $knownBots['venuscrawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'VenusCrawler',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* gobyus */
  $knownBots['gobyus'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'gobyus',
    'bot_url'=>'',
    'engine_title'=>'gobyus',
    'engine_url'=>'http://gobyus.com/en');
  
  /* WP Spydr */
  $knownBots['wp spydr'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'WP Spydr',
    'bot_url'=>'http://wpspydr.com',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* Virusdie crawler */
  $knownBots['virusdie crawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Virusdie crawler',
    'bot_url'=>'',
    'engine_title'=>'Virusdie',
    'engine_url'=>'https://virusdie.com');
  
  /* StumbleUpon crawler */
  $knownBots['stumbleupon'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'',
    'bot_url'=>'',
    'engine_title'=>'StumbleUpon',
    'engine_url'=>'https://http://www.stumbleupon.com');
  
  /* Vegi bot */
  $knownBots['vegi bot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Vegi bot',
    'bot_url'=>'mailto:abuse-report@terrykyleseoagency.com',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* AwarioSmartBot */
  $knownBots['awariosmartbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'AwarioSmartBot',
    'bot_url'=>'https://awario.com/bots.html',
    'engine_title'=>'Awario',
    'engine_url'=>'https://awario.com');
  
  /* 0xff.org */
  $knownBots['0xff.org'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'0xFF Domain Crawler',
    'bot_url'=>'',
    'engine_title'=>'0xff.org',
    'engine_url'=>'https://0xff.org');
  
  /* YaK from linkfluence.com */
  $knownBots['linkfluence.com'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'YaK',
    'bot_url'=>'mailto:bot@linkfluence.com',
    'engine_title'=>'linkfluence',
    'engine_url'=>'http://linkfluence.com/');
  
  /* aboundex */
  $knownBots['aboundex'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Aboundex Crawler',
    'bot_url'=>'http://www.aboundex.com/crawler/',
    'engine_title'=>'Aboundex',
    'engine_url'=>'http://www.aboundex.com/');
  
  /* KomodiaBot */
  $knownBots['komodiabot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'KomodiaBot',
    'bot_url'=>'http://www.komodia.com/newwiki/index.php/URL_server_crawler',
    'engine_title'=>'Komodia',
    'engine_url'=>'http://www.komodia.com/');
  
  /* spyonweb.com */
  $knownBots['spyonweb.com'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'',
    'bot_url'=>'',
    'engine_title'=>'SpyOnWeb',
    'engine_url'=>'http://spyonweb.com/');
  
  /* ZoominfoBot */
  $knownBots['zoominfobot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'ZoominfoBot',
    'bot_url'=>'mailto:ZoominfoBot@zoominfo.com',
    'engine_title'=>'ZoominfoBot',
    'engine_url'=>'http://www.zoominfo.com/');
  
  /* XilopixBot */
  $knownBots['xilopixbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'XilopixBot',
    'bot_url'=>'http://www.xilopix.com/bot.html',
    'engine_title'=>'Xilopix',
    'engine_url'=>'http://pro.xilopix.com');
  
  /* kula.jp/endo */
  $knownBots['kula.jp/endo'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'',
    'bot_url'=>'',
    'engine_title'=>'Endo',
    'engine_url'=>'http://kula.jp/endo');
  
  /* DJEcoBot */
  $knownBots['djecobot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'DJEcoBot',
    'bot_url'=>'mailto:analytics@demandjump.com',
    'engine_title'=>'DemandJump',
    'engine_url'=>'https://www.demandjump.com');
  
  /* RankingBot2 */
  $knownBots['rankingbot2'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'RankingBot2',
    'bot_url'=>'https://varocarbas.com/bot_ranking2/',
    'engine_title'=>'varocarbas.com',
    'engine_url'=>'https://varocarbas.com');
  
  /* AliveAdvisorCrawler */
  $knownBots['aliveadvisorcrawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'AliveAdvisorCrawler',
    'bot_url'=>'mailto:crawler@aliveadvisor.com',
    'engine_title'=>'AliveAdvisor',
    'engine_url'=>'http://search.aliveadvisor.com');
  
  /* http://www.x9o.de */
  $knownBots['www.x9o.de'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'',
    'bot_url'=>'',
    'engine_title'=>'x9o.de',
    'engine_url'=>'http://www.x9o.de');
  
  /* ExtLinksBot */
  $knownBots['extlinksbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'ExtLinksBot',
    'bot_url'=>'https://extlinks.com/Bot.html',
    'engine_title'=>'ExtLinks',
    'engine_url'=>'https://extlinks.com/');
  
  /* DomainStatsBot */
  $knownBots['domainstatsbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'DomainStatsBot',
    'bot_url'=>'http://domainstats.io/our-bot',
    'engine_title'=>'DomainStats.io',
    'engine_url'=>'http://domainstats.io/');
  
  /* GroupHigh */
  $knownBots['grouphigh'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'',
    'bot_url'=>'',
    'engine_title'=>'GroupHigh',
    'engine_url'=>'http://www.grouphigh.com/');
    
  /* Melodibot */
  $knownBots['melodibot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Melodibot',
    'bot_url'=>'http://www.irit.fr/melodibot/',
    'engine_title'=>'IRIT',
    'engine_url'=>'https://www.irit.fr');
    
  /* SnowHaze SearcH */
  $knownBots['snowhaze search'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'SnowHaze SearcH',
    'bot_url'=>'mailto:support@snowhaze.com',
    'engine_title'=>'SnowHaze',
    'engine_url'=>'https://snowhaze.com/');
    
  /* Scopia Crawler */
  $knownBots['scopia crawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Scopia Crawler',
    'bot_url'=>'',
    'engine_title'=>'Scopia',
    'engine_url'=>'http://www.scopia.co');
    
  /* Companybook-Crawler */
  $knownBots['companybook-crawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Companybook-Crawler',
    'bot_url'=>'',
    'engine_title'=>'Companybook',
    'engine_url'=>'https://www.companybooknetworking.com');
    
  /* ExperianCrawlUK */
  $knownBots['experiancrawluk'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'ExperianCrawlUK',
    'bot_url'=>'',
    'engine_title'=>'PHGroup',
    'engine_url'=>'http://www.phgroup.com');
    
  /* Zombiebot */
  $knownBots['zombiebot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Zombiebot',
    'bot_url'=>'http://www.zombiedomain.net/robot/',
    'engine_title'=>'ZombieDomain',
    'engine_url'=>'http://www.zombiedomain.net');
    
  /* AlphaBot */
  $knownBots['alphabot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'AlphaBot',
    'bot_url'=>'http://alphaseobot.com/bot.html',
    'engine_title'=>'Alpha SEO Bot',
    'engine_url'=>'http://alphaseobot.com/');
    
  /* Gowikibot */
  $knownBots['gowikibot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Gowikibot',
    'bot_url'=>'http://www.gowikibot.com',
    'engine_title'=>'GoWiki',
    'engine_url'=>'');
    
  /* Seobility */
  $knownBots['seobility'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Seobility bot',
    'bot_url'=>'https://www.seobility.net/sites/bot.html',
    'engine_title'=>'Seobility',
    'engine_url'=>'https://www.seobility.net/en/');
    
  /* IndeedBot */
  $knownBots['indeedbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'IndeedBot',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
    
  /* looid.com crawler */
  $knownBots['looid.com crawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'looid.com crawler',
    'bot_url'=>'looid.com',
    'engine_title'=>'',
    'engine_url'=>'');
    
  /* um-LN */
  $knownBots['um-ln'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'um-LN',
    'bot_url'=>'mailto:techinfo@ubermetrics-technologies.com',
    'engine_title'=>'uberMetrics Technologies',
    'engine_url'=>'https://www.ubermetrics-technologies.com');
    
  /* um-FC */
  $knownBots['um-fc'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'um-FC',
    'bot_url'=>'mailto:techinfo@ubermetrics-technologies.com',
    'engine_title'=>'uberMetrics Technologies',
    'engine_url'=>'https://www.ubermetrics-technologies.com');
    
  /* Grobbot */
  $knownBots['grobbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Grobbot',
    'bot_url'=>'',
    'engine_title'=>'Grob',
    'engine_url'=>'https://grob.it');
    
  /* Contacts-Crawler */
  $knownBots['contacts-crawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Contacts-Crawler',
    'bot_url'=>'',
    'engine_title'=>'Scrapinghub',
    'engine_url'=>'http://www.scrapinghub.com');
    
  /* GeeGee */
  $knownBots['geegee'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'',
    'bot_url'=>'',
    'engine_title'=>'GeeGee',
    'engine_url'=>'https://geegee.online/');
    
  /* AplicatiiGalaxy */
  $knownBots['aplicatiigalaxy'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'AplicatiiGalaxy',
    'bot_url'=>'mailto:aplicatiigalaxy@gmail.com',
    'engine_title'=>'',
    'engine_url'=>'');
    
  /* PiplBot */
  $knownBots['piplbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'PiplBot',
    'bot_url'=>'http://www.pipl.com/bot/',
    'engine_title'=>'Pipl',
    'engine_url'=>'http://www.pipl.com');
    
  /* LightspeedSystemsCrawler */
  $knownBots['lightspeedsystemscrawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'LightspeedSystemsCrawler',
    'bot_url'=>'',
    'engine_title'=>'Lightspeed Systems, Inc.',
    'engine_url'=>'https://www.lightspeedsystems.com');
    
  /* SearchmetricsBot */
  $knownBots['searchmetricsbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'SearchmetricsBot',
    'bot_url'=>'https://www.searchmetrics.com/searchmetricsbot/',
    'engine_title'=>'SearchMetrics',
    'engine_url'=>'https://www.searchmetrics.com/');
    
  /* Techlimed */
  $knownBots['techlimed'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'ntlk/Nutch',
    'bot_url'=>'',
    'engine_title'=>'Techlimed',
    'engine_url'=>'');
    
  /* pmoz.info */
  $knownBots['pmoz.info'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'pmoz.info ODP link checker',
    'bot_url'=>'http://pmoz.info/doc/botinfo.htm',
    'engine_title'=>'Dmoz.org',
    'engine_url'=>'http://www.dmoz.org');
    
  /* ArchiveBot */
  $knownBots['archivebot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'ArchiveBot',
    'bot_url'=>'https://www.archiveteam.org/index.php?title=ArchiveBot',
    'engine_title'=>'ArchiveTeam',
    'engine_url'=>'https://www.archiveteam.org');
    
  /* unknown bot */
  $knownBots['seo bulls'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'SEO Bulls (unknown bot)',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
    
  /* unknown bot */
  $knownBots['tmm crawler'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'TMM Crawler (unknown bot)',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');

  /* unknown bot */
  $knownBots['no.indexing@gmail.com'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Unknown bot',
    'bot_url'=>'mailto:no.indexing@gmail.com',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* unknown bot */
  $knownBots['nbertaupete95(at)gmail.com'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Unknown bot',
    'bot_url'=>'mailto:nbertaupete95@gmail.com',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* unknown bot */
  $knownBots['centurybot9'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Unknown bot',
    'bot_url'=>'mailto:centurybot9@gmail.com',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* unknown bot */
  $knownBots['celious search engine'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Unknown bot',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* unknown bot */
  $knownBots['celious search engine'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Unknown bot',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* unknown bot */
  $knownBots['smurlexpander'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Unknown bot',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* unknown bot */
  $knownBots['dnyzbot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Unknown bot',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
    
  /* return bot list */
  return $knownBots;
}

/*
 * return tool index if tool
 * @param string $ua
 * @return mixed
 * @access public
 */
function client_checkIsTool($ua=false) {
  /* get user agent */
  if (!$ua)	$ua = client_getUserAgent();

  /* load known tools */
  $knownTools = client_getKnownTools();
  
  /* build detection pattern */
  $detectionPattern = implode('|', array_keys($knownTools));
  $detectionPattern = preg_replace ('/(\/|\(|\)|\.)/', '\\\$1', $detectionPattern);
  $detectionPattern = '/'.$detectionPattern.'/i';

  /* start detection and return result */
  if ( preg_match ( $detectionPattern, strtolower($ua), $result ))
    return $result[0];
  return false;
}

/*
 * return bot info if tool
 * @param string $tool
 * @return mixed
 * @access public
 */
function client_getToolInfos($tool='') {
  $knownTools = client_getKnownTools();
    
  if (isset($knownTools[$tool]))
    return $knownTools[$tool];
  return array();
}

/*
 * return bot info from user agent
 * @param string $ua
 * @return mixed
 * @access public
 */
function client_getToolInfosFromUserAgent($ua='') {
  $knownTools = client_getKnownTools();
  
  /* build detection pattern */
  $detectionPattern = implode('|', array_keys($knownTools));
  $detectionPattern = preg_replace ('/(\/|\(|\)|\.)/', '\\\$1', $detectionPattern);
  $detectionPattern = '/'.$detectionPattern.'/i';

  /* start detection and return result */
  if ( preg_match ( $detectionPattern, strtolower($ua), $result ) )
    return $knownTools[$result[0]];
  return false;
}

/*
 * return given known web tool or tool list
 * @return array
 * @access public
 */
function client_getKnownTools() {
  $knownTools = array();

  /* w3c validator */
  $knownTools['w3c_validator'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'W3C Validator',
    'tool_url'=>'http://validator.w3.org',
    'engine_title'=>'World Wide Web Consortium',
    'engine_url'=>'http://www.w3.org');
  
  /* Validator.nu/LV */
  $knownTools['validator.nu/lv'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'W3C Validator',
    'tool_url'=>'http://validator.w3.org',
    'engine_title'=>'World Wide Web Consortium',
    'engine_url'=>'http://www.w3.org');
    
  /* google translation */
  $knownTools['translate.google.com'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Google Translation',
    'tool_url'=>'http://translate.google.com/',
    'engine_title'=>'Google',
    'engine_url'=>'http://www.google.com');
    
  /* google translation */
  $knownTools['google wireless transcoder'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Google Wireless Transcoder',
    'tool_url'=>'',
    'engine_title'=>'Google',
    'engine_url'=>'http://www.google.com');
  
  /* google page speed insight mobile */
  $knownTools['google page speed insights) version/6.0 mobile'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'handheld',
    'tool_title'=>'Google Page Speed Insights (Mobile)',
    'tool_url'=>'https://developers.google.com/speed/pagespeed/insights/',
    'engine_title'=>'Google',
    'engine_url'=>'http://www.google.com');
    
  /* google page speed insight */
  $knownTools['google page speed insights'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Google Page Speed Insights',
    'tool_url'=>'https://developers.google.com/speed/pagespeed/insights/',
    'engine_title'=>'Google',
    'engine_url'=>'http://www.google.com');
    
  /* Google Feedfetcher */
  $knownTools['feedfetcher-google'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Google Feedfetcher',
    'tool_url'=>'http://www.google.com/feedfetcher.html',
    'engine_title'=>'Google',
    'engine_url'=>'http://www.google.com');
    
  /* yahoo translation : babel fish */
  $knownTools['babelfish.yahoo.com'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Babel Fish',
    'tool_url'=>'http://babelfish.yahoo.com',
    'engine_title'=>'Yahoo',
    'engine_url'=>'http://www.yahoo.com');
 
  /* facebook external hit */
  $knownTools['facebookexternalhit'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Facebook',
    'tool_url'=>'http://www.facebook.com/externalhit_uatext.php',
    'engine_title'=>'Facebook',
    'engine_url'=>'http://www.facebook.com');

  /* facebook share follower */
  $knownTools['facebook share follower'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Facebook',
    'tool_url'=>'',
    'engine_title'=>'Facebook',
    'engine_url'=>'http://www.facebook.com');
 
  /* tumblr */
  $knownTools['tumblr'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'',
    'tool_url'=>'',
    'engine_title'=>'Tumblr',
    'engine_url'=>'https://www.tumblr.com');
    
  /* builtwith engine */
  $knownTools['builtwith.com'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'BuiltWith',
    'tool_url'=>'http://builtwith.com/tool.html',
    'engine_title'=>'Builtwith',
    'engine_url'=>'http://builtwith.com');

  /* bloglines */
  $knownTools['bloglines'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'BlogLines',
    'tool_url'=>'http://www.bloglines.com',
    'engine_title'=>'',
    'engine_url'=>'');

  /* Acrobat Capture */
  $knownTools['webcapture'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'WebCapture',
    'tool_url'=>'',
    'engine_title'=>'Adobe Acrobat Capture',
    'engine_url'=>'');

  /* vBSEO */
  $knownTools['vbseo'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'vBSEO',
    'tool_url'=>'http://www.vbseo.com',
    'engine_title'=>'',
    'engine_url'=>'');
    
  /* WebmasterCoffee */
  $knownTools['webmastercoffee'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'WebmasterCoffee',
    'tool_url'=>'http://webmastercoffee.com/about',
    'engine_title'=>'WebmasterCoffee',
    'engine_url'=>'http://webmastercoffee.com');

  /* Embed.ly */
  $knownTools['embed.ly'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'embed.ly',
    'tool_url'=>'',
    'engine_title'=>'embed.ly',
    'engine_url'=>'http://embed.ly/');
			       
  /* Tweetmeme */
  $knownTools['tweetmemebot'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'TweetmemeBot',
    'tool_url'=>'',
    'engine_title'=>'Tweetmeme',
    'engine_url'=>'http://tweetmeme.com/');
			       
  /* LinkedIn Bot */
  $knownTools['linkedinbot'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'LinkedInBot',
    'tool_url'=>'',
    'engine_title'=>'LinkedIn',
    'engine_url'=>'http://www.linkedin.com/');
    
  /* Xenu Link Sleuth */
  $knownTools['xenu link sleuth'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Xenu Link Sleuth',
    'tool_url'=>'http://home.snafu.de/tilman/xenulink.html',
    'engine_title'=>'',
    'engine_url'=>'');  
  
  /* MSIECrawler */
  $knownTools['msiecrawler'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'MSIECrawler',
    'tool_url'=>'',
    'engine_title'=>'Microsoft',
    'engine_url'=>'http://www.microsoft.com');
    
  /*  Microsoft Office Protocol Discovery  */
  $knownTools['microsoft office protocol discovery'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Microsoft Office Protocol Discovery',
    'tool_url'=>'',
    'engine_title'=>'Microsoft',
    'engine_url'=>'http://www.microsoft.com');
    
  /* HTTrack */
  $knownTools['httrack'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'',
    'tool_url'=>'',
    'engine_title'=>'HTTrack',
    'engine_url'=>'https://www.httrack.com');
  
  /* powermarks */
  $knownTools['powermarks'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Powermarks',
    'tool_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* CFNetwork */
  $knownTools['cfnetwork'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'OS X / iOS',
    'tool_url'=>'',
    'engine_title'=>'Apple',
    'engine_url'=>'');
    
  /* wkhtmltoimage */
  $knownTools['wkhtmltoimage'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'wkhtmltoimage',
    'tool_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
    
  /* CasperJS */
  $knownTools['casperjs'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'CasperJS',
    'tool_url'=>'http://casperjs.org',
    'engine_title'=>'',
    'engine_url'=>'');
    
  /* PhantomJS */
  $knownTools['phantomjs'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'PhantomJS',
    'tool_url'=>'http://phantomjs.org',
    'engine_title'=>'',
    'engine_url'=>'');
    
  /* SlimerJS */
  $knownTools['slimerjs'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'SlimerJS',
    'tool_url'=>'http://slimerjs.org',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* S.N.O.W. */
  $knownTools['s.n.o.w.'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'S.N.O.W.',
    'tool_url'=>'http://www.trilibis.com/snow.jsp',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* Scrutiny */
  $knownTools['scrutiny'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Scrutiny',
    'tool_url'=>'http://peacockmedia.software',
    'engine_title'=>'PeacockMedia',
    'engine_url'=>'http://peacockmedia.software/mac/scrutiny/');
  
  /* Pagespeed */
  $knownTools['pagespeed.de'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Pagespeed',
    'tool_url'=>'http://www.pagespeed.de',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* Screaming Frog SEO Spider */
  $knownTools['screaming frog seo spider'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Screaming Frog SEO Spider',
    'tool_url'=>'http://www.screamingfrog.co.uk/seo-spider/',
    'engine_title'=>'Screaming Frog',
    'engine_url'=>'http://www.screamingfrog');
  
  /* Bot.AraTurka.com */
  $knownTools['bot.araturka.com'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Bot.AraTurka.com',
    'tool_url'=>'',
    'engine_title'=>'AraTurka',
    'engine_url'=>'http://www.araturka.com/index.php');
  
  /* crawler4j */
  $knownTools['crawler4j'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'crawler4j',
    'tool_url'=>'https://code.google.com/p/crawler4j/',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* Zend_Http_Client */
  $knownTools['zend_http_client'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Zend_Http_Client',
    'tool_url'=>'http://framework.zend.com/manual/1.12/en/zend.http.client.advanced.html',
    'engine_title'=>'Zend',
    'engine_url'=>'http://www.zend.com');
  
  /* GetRequest */
  $knownTools['getrequest'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'GetRequest',
    'tool_url'=>'http://www.getrequest.net',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* CrazyWebCrawler */
  $knownTools['crazywebcrawler'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'CrazyWebCrawler',
    'tool_url'=>'http://www.crazywebcrawler.com',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* AppEngine-Google */
  $knownTools['appengine-google'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'AppEngine-Google',
    'tool_url'=>'http://code.google.com/appengine',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* WSCheck */
  $knownTools['wscheck'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'wscheck',
    'tool_url'=>'',
    'engine_title'=>'WSCheck',
    'engine_url'=>'http://wscheck.com');
  
  /* MRA */
  $knownTools[' mra '] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Mail.ru downloader',
    'tool_url'=>'',
    'engine_title'=>'Mail.ru',
    'engine_url'=>'http://mail.ru');
  
  /* DowntimeDetector */
  $knownTools['downtimedetector'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'DowntimeDetector',
    'tool_url'=>'http://downforeveryoneorjustme.com',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* LinkedInBot */
  $knownTools['linkedinbot'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'LinkedInBot',
    'tool_url'=>'',
    'engine_title'=>'LinkedIn',
    'engine_url'=>'http://www.linkedin.com');
    
  /* XML-Sitemaps */
  $knownTools['xml-sitemaps'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'',
    'tool_url'=>'',
    'engine_title'=>'XML-Sitemaps',
    'engine_url'=>'https://www.xml-sitemaps.com');
    
  /* GTmetrix */
  $knownTools['gtmetrix'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'',
    'tool_url'=>'',
    'engine_title'=>'GTmetrix',
    'engine_url'=>'https://gtmetrix.com');
    
  /* splash */
  $knownTools['splash safari'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'',
    'tool_url'=>'',
    'engine_title'=>'Splash',
    'engine_url'=>'https://github.com/scrapinghub/splash');
  
  /* Spider-Pig by Tinfoil security */
  $knownTools['spider-pig'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Spider-Pig',
    'tool_url'=>'',
    'engine_title'=>'Tinfoil security',
    'engine_url'=>'https://tinfoilsecurity.com/');
  
  /* W3C-checklink */
  $knownTools['w3c-checklink'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'W3C-checklink',
    'tool_url'=>'https://validator.w3.org/checklink',
    'engine_title'=>'World Wide Web Consortium',
    'engine_url'=>'https://www.w3.org');
  
  /* Wappalyzer */
  $knownTools['wappalyzer'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Wappalyzer',
    'tool_url'=>'https://github.com/AliasIO/Wappalyzer',
    'engine_title'=>'Wappalyzer',
    'engine_url'=>'https://wappalyzer.com');
  
  /* CakePHP */
  $knownTools['cakephp'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'CakePHP',
    'tool_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* MetaInspector */
  $knownTools['metainspector'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'MetaInspector',
    'tool_url'=>'https://github.com/jaimeiniesta/metainspector',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* PerfectMail */
  $knownTools['perfectmail'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'PerfectMail WebProbe',
    'tool_url'=>'http://perfectmail.com/kb/web_probe',
    'engine_title'=>'PerfectMail',
    'engine_url'=>'http://perfectmail.com');
  
  /* SiteTruth.com */
  $knownTools['sitetruth.com'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'',
    'tool_url'=>'',
    'engine_title'=>'SiteTruth.com',
    'engine_url'=>'http://SiteTruth.com');
  
  /* SalesIntelligent */
  $knownTools['salesintelligent'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'',
    'tool_url'=>'',
    'engine_title'=>'SalesIntelligent',
    'engine_url'=>'http://SalesIntelligent.com');
  
  /* SSL Labs */
  $knownTools['ssl labs'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'SSL Labs',
    'tool_url'=>'https://www.ssllabs.com/ssltest',
    'engine_title'=>'Qualys',
    'engine_url'=>'https://www.ssllabs.com/index.html');
  
  /* woobot */
  $knownTools['woobot'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'woobot',
    'tool_url'=>'',
    'engine_title'=>'Woorank',
    'engine_url'=>'https://www.woorank.com');
  
  /* internetVista monitor */
  $knownTools['internetvista monitor'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'internetVista monitor',
    'tool_url'=>'',
    'engine_title'=>'internetVista',
    'engine_url'=>'http://www.internetvista.com');
  
  /* Contacts Crawler - is maybe a bot */
  $knownTools['contacts crawler'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Contacts Crawler',
    'tool_url'=>'',
    'engine_title'=>'Scrapinghub',
    'engine_url'=>'http://scrapinghub.com');
  
  /* Seoterritory.com - is maybe a bot */
  $knownTools['seoterritory.com'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Seoterritory.com',
    'tool_url'=>'http://www.seoterritory.com',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* Spatineo */
  $knownTools['spatineo'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Spatineo Monitor Controller',
    'tool_url'=>'http://www.spatineo.com/spatineo-monitor/',
    'engine_title'=>'Spatineo',
    'engine_url'=>'http://www.spatineo.com');
  
  /* Spatineo */
  $knownTools['spatineo'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Spatineo Monitor Controller',
    'tool_url'=>'http://www.spatineo.com/spatineo-monitor/',
    'engine_title'=>'Spatineo',
    'engine_url'=>'http://www.spatineo.com');
  
  /* Integrity */
  $knownTools['integrity'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Integrity',
    'tool_url'=>'http://peacockmedia.software/mac/integrity/free.html',
    'engine_title'=>'PeacockMedia',
    'engine_url'=>'http://peacockmedia.software');
  
  /* UniversalFeedParser */
  $knownTools['universalfeedparser'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'UniversalFeedParser',
    'tool_url'=>'',
    'engine_title'=>'FeedParser',
    'engine_url'=>'http://feedparser.org');
  
  /* FreeWebMonitoring SiteChecker */
  $knownTools['freewebmonitoring sitechecker'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'FreeWebMonitoring SiteChecker',
    'tool_url'=>'',
    'engine_title'=>'FreeWebMonitoring SiteChecker',
    'engine_url'=>'http://www.freewebmonitoring.com');
  
  /* SkypeUriPreview */
  $knownTools['skypeuripreview'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'SkypeUriPreview',
    'tool_url'=>'',
    'engine_title'=>'Skype',
    'engine_url'=>'https://www.skype.com');
  
  /* BrokenLinkCheck.com */
  $knownTools['brokenlinkcheck.com'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'',
    'tool_url'=>'',
    'engine_title'=>'Broken Link Check',
    'engine_url'=>'http://BrokenLinkCheck.com');
  
  /* OpenStat */
  $knownTools['openstat'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'',
    'tool_url'=>'',
    'engine_title'=>'OpenStat',
    'engine_url'=>'https://www.openstat.com');
  
  /* Iframely */
  $knownTools['iframely'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'',
    'tool_url'=>'',
    'engine_title'=>'Iframely',
    'engine_url'=>'https://iframely.com');
  
  /* Link Examiner */
  $knownTools['linkexaminer'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'LinkExaminer',
    'tool_url'=>'http://www.analogx.com/contents/download/network/lnkexam/freeware.htm',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* Link Saver */
  $knownTools['linksaver'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'LinkSaver',
    'tool_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* Link Saver */
  $knownTools['linkparser'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'LinkParser',
    'tool_url'=>'http://www.seerobots.com/linkparser',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* HEADMasterSEO */
  $knownTools['headmasterseo'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'HEADMasterSEO',
    'tool_url'=>'https://headmasterseo.com',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* BuiltWith */
  $knownTools['builtwith'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'',
    'tool_url'=>'',
    'engine_title'=>'BuiltWith',
    'engine_url'=>'https://builtwith.com');
  
  /* BlueCoat ProxySG */
  $knownTools['bluecoat proxysg'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'BlueCoat ProxySG ',
    'tool_url'=>'',
    'engine_title'=>'BlueCoat',
    'engine_url'=>'https://bluecoat.com');
  
  /* Flipboard */
  $knownTools['flipboard'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Flipboard Proxy',
    'tool_url'=>'http://flipboard.com/browserproxy',
    'engine_title'=>'Flipboard',
    'engine_url'=>'http://flipboard.com');
  
  /* LinkCheck by Siteimprove.com */
  $knownTools['linkcheck by siteimprove.com'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'LinkCheck',
    'tool_url'=>'',
    'engine_title'=>'Siteimprove.com',
    'engine_url'=>'https://siteimprove.com');
  
  /* Match by Siteimprove.com */
  $knownTools['match by siteimprove.com'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Match',
    'tool_url'=>'',
    'engine_title'=>'Siteimprove.com',
    'engine_url'=>'https://siteimprove.com');
  
  /* webscreenie */
  $knownTools['webscreenie'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'webscreenie',
    'tool_url'=>'https://www.openhub.net/p/webscreenie',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* JOC Web Spider */
  $knownTools['joc web spider'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'JOC Web Spider',
    'tool_url'=>'',
    'engine_title'=>'Jocsoft',
    'engine_url'=>'http://www.jocsoft.com/jws/');
  
  /* WhatWeb */
  $knownTools['whatweb'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'',
    'tool_url'=>'',
    'engine_title'=>'WhatWeb',
    'engine_url'=>'https://www.morningstarsecurity.com/research/whatweb');
    
  /* SBL-BOT */
  $knownTools['sbl-bot'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'SBL-BOT',
    'tool_url'=>'',
    'engine_title'=>'SoftByte Labs',
    'engine_url'=>'http://sbl.net');
    
  /* Chrome-Lighthouse */
  $knownTools['chrome-lighthouse'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Chrome-Lighthouse',
    'tool_url'=>'https://github.com/GoogleChrome/lighthouse',
    'engine_title'=>'',
    'engine_url'=>'');
    
  /* Google-AMPHTML */
  $knownTools['google-amphtml'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Google-AMPHTML',
    'tool_url'=>'https://www.ampproject.org',
    'engine_title'=>'',
    'engine_url'=>'');
    
  /* SiteWinder */
  $knownTools['sitewinder'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'SiteWinder',
    'tool_url'=>'',
    'engine_title'=>'Web washer',
    'engine_url'=>'https://www.mcafee.com');
    
  /* Optimizer */
  $knownTools['optimizer'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Optimizer',
    'tool_url'=>'',
    'engine_title'=>'Sistrix',
    'engine_url'=>'https://www.sistrix.com');
    
  /* evc-batch */
  $knownTools['evc-batch'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'evc-batch',
    'tool_url'=>'',
    'engine_title'=>'eVenture Capital Partners II, LLC',
    'engine_url'=>'http://www.eventures.vc/');
    
  /* Nmap Scripting Engine */
  $knownTools['nmap scripting engine'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Nmap Scripting Engine',
    'tool_url'=>'https://nmap.org/book/nse.html',
    'engine_title'=>'NMAP',
    'engine_url'=>'https://nmap.org/');
    
  /* Outiref */
  $knownTools['outiref'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'',
    'tool_url'=>'',
    'engine_title'=>'Outiref',
    'engine_url'=>'https://www.outiref.fr/');
    
  /* alyze.info */
  $knownTools['alyze.info'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'',
    'tool_url'=>'',
    'engine_title'=>'alyze',
    'engine_url'=>'https://alyze.info/');
    
  /* DareBoost */
  $knownTools['dareboost'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'',
    'tool_url'=>'',
    'engine_title'=>'DareBoost',
    'engine_url'=>'https://www.dareboost.com/');
    
  /* return list */
  return $knownTools;
}

/*** generic tool/boot specific methods */

/*
 * return generic index if generic
 * @param string $ua
 * @return mixed
 * @access public
 */
function client_checkIsGeneric($ua=false) {
  /* get user agent */
  if (!$ua)	$ua = client_getUserAgent();
 
  /* load known generic agents */
  $knownGenerics = client_getKnownGenerics();
  
  /* build detection pattern */
  $detectionPattern = implode('|', array_keys($knownGenerics));
  $detectionPattern = preg_replace ('/(\/|\(|\)|\.)/', '\\\$1', $detectionPattern);
  $detectionPattern = '/'.$detectionPattern.'/i';

  /* start detection and return result */
  if ( preg_match ( $detectionPattern, strtolower($ua), $result ))
    return $result[0];
  return false;
}

/*
 * return bot info if generic
 * @param string $generic
 * @return mixed
 * @access public
 */
function client_getGenericInfos($generic='') {
  $knownGenerics = client_getKnownGenerics();
    
  if (isset($knownGenerics[$generic]))
    return $knownGenerics[$generic];
  return array();
}

/*
 * return bot info from user agent
 * @param string $ua
 * @return mixed
 * @access public
 */
function client_getGenericInfosFromUserAgent($ua='') {

  /* remove hotjava from java results */
  if (preg_match('/^HotJava/i', $ua))
    return false;

  /* load generic/libraries */
  $knownGenerics = client_getKnownGenerics();
  
  /* build detection pattern */
  $detectionPattern = implode('|', array_keys($knownGenerics));
  $detectionPattern = preg_replace ('/(\/|\(|\)|\.)/', '\\\$1', $detectionPattern);
  $detectionPattern = '/'.$detectionPattern.'/i';

  /* start detection and return result */
  if ( preg_match ( $detectionPattern, strtolower($ua), $result ) )
    return $knownGenerics[$result[0]];
  return false;
}

/*
 * return given known web generic or generic list
 * @return array
 * @access public
 */
function client_getKnownGenerics() {
  $knownGenerics = array();
  
  /* CaMykS */
  $knownGenerics['camyksrequest'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'CaMykSRequest',
    'bot_url'=>'https://www.camyks.net/request_bot.html',
    'engine_title'=>'CaMykS',
    'engine_url'=>'https://www.camyks.net');
         
  /* NING */
  $knownGenerics['ning'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'NING',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* heritrix */
  $knownGenerics['heritrix'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'heritrix',
    'bot_url'=>'https://webarchive.jira.com/wiki/display/Heritrix',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* Nutch */
  $knownGenerics['nutch'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Nutch',
    'bot_url'=>'http://nutch.apache.org',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* Voltron */
  $knownGenerics['voltron'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Voltron',
    'bot_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* Scrapy */
  $knownGenerics['scrapy'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'Scrapy',
    'bot_url'=>'',
    'engine_title'=>'Scrapy.org',
    'engine_url'=>'http://scrapy.org');
  
  /* WWW-Mechanize */
  $knownBots['www-mechanize'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'WWW-Mechanize',
    'tool_url'=>'',
    'engine_title'=>'CPAN',
    'engine_url'=>'http://search.cpan.org/~ether/');

  /* Fetcher */
  $knownBots['compatible; fetcher/'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Fetcher',
    'tool_url'=>'',
    'engine_title'=>'Apple',
    'engine_url'=>'http://www.apple.com');
    
  /* Pcore-HTTP  */
  $knownGenerics['pcore-http'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Pcore-HTTP',
    'tool_url'=>'http://search.cpan.org/dist/Pcore/lib/Pcore/HTTP.pm',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* Mechanize (before Ruby) */
  $knownGenerics['mechanize'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Mechanize',
    'tool_url'=>'http://github.com/sparklemotion/mechanize/',
    'engine_title'=>'',
    'engine_url'=>'');

  /* Wget linux library */
  $knownGenerics['wget'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'WGet',
    'tool_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* gettor */
  $knownGenerics['gettor'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'gettor',
    'tool_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* Python library */
  $knownGenerics['python-urllib'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Python Library',
    'tool_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* Python Request library */
  $knownGenerics['python-requests'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Python Request Library',
    'tool_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* Apache-HttpClient library (before Java) */
  $knownGenerics['apache-httpclient'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Apache-HttpClient',
    'tool_url'=>'',
    'engine_title'=>'Apache Software Foundation',
    'engine_url'=>'https://hc.apache.org');
    
  /* Apache-HttpAsyncClient library (before Java) */
  $knownGenerics['apache-httpasyncclient'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Apache-HttpAsyncClient',
    'tool_url'=>'',
    'engine_title'=>'Apache Software Foundation',
    'engine_url'=>'https://hc.apache.org');
  
  /* Apache synapse library (before Synapse) */
  $knownGenerics['synapse-httpcomponent'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Apache Synapse',
    'tool_url'=>'',
    'engine_title'=>'Apache Software Foundation',
    'engine_url'=>'https://hc.apache.org');
  
  /* Jakarta Commons-HttpClient */
  $knownGenerics['jakarta commons-httpclient'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Jakarta Commons-HttpClient',
    'tool_url'=>'http://hc.apache.org/httpclient-3.x/',
    'engine_title'=>'Apache Software Foundation',
    'engine_url'=>'https://hc.apache.org');
  
  /* Ararat Synapse */
  $knownGenerics['synapse'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'',
    'tool_url'=>'',
    'engine_title'=>'Ararat Synapse',
    'engine_url'=>'http://synapse.ararat.cz/doku.php');
  
  /* java library */
  $knownGenerics['java/'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Java Library',
    'tool_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* Perl library */
  $knownGenerics['libwww-perl'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'PERL Library',
    'tool_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* WinHttpRequest */
  $knownGenerics['winhttp'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'WinHttpRequest',
    'tool_url'=>'https://msdn.microsoft.com/en-us/library/windows/desktop/aa382925(v=vs.85).aspx',
    'engine_title'=>'Microsoft',
    'engine_url'=>'');
  
  /* Ruby */
  $knownGenerics['ruby'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Ruby Library',
    'tool_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* GuzzleHttp (before curl) */
  $knownGenerics['guzzle'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'GuzzleHttp Library',
    'tool_url'=>'http://docs.guzzlephp.org/en/latest/',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* cURL */
  $knownGenerics['libcurl'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'cURL Library',
    'tool_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* cURL */
  $knownGenerics['curl/'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'cURL Library',
    'tool_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* pycurl */
  $knownGenerics['pycurl'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'pycurl',
    'tool_url'=>'http://pycurl.io',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* PHP */
  $knownGenerics['php/5'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'PHP Library',
    'tool_url'=>'http://www.php.net',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* Go-http-client */
  $knownGenerics['go-http-client'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Go Language Library',
    'tool_url'=>'https://golang.org/pkg/net/http/',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* Typhoeus */
  $knownGenerics['typhoeus'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Typhoeus',
    'tool_url'=>'https://github.com/typhoeus/typhoeus',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* Chilkat */
  $knownGenerics['chilkat'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Chilkat',
    'tool_url'=>'http://www.chilkatsoft.com/ChilkatHttpUA.asp',
    'engine_title'=>'Chilkat Software',
    'engine_url'=>'http://www.chilkatsoft.com');
  
  /* SEOstats */
  $knownGenerics['seostats'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'SEOstats',
    'tool_url'=>'https://github.com/eyecatchup/SEOstats',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* MLIB_NetWorkLibrary */
  $knownGenerics['mlib_networklibrary'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'MLIB_NetWorkLibrary',
    'tool_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* MLIB_NetWorkBot */
  $knownGenerics['mlib_networkbot'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'MLIB_NetWorkBot',
    'tool_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* Mojolicious */
  $knownGenerics['mojolicious'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'',
    'tool_url'=>'',
    'engine_title'=>'Mojolicious',
    'engine_url'=>'http://mojolicious.org');
  
  /* httpunit */
  $knownGenerics['httpunit'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'httpunit',
    'tool_url'=>'http://httpunit.sourceforge.net',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* aria2 */
  $knownGenerics['aria2'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'aria2',
    'tool_url'=>'https://sourceforge.net/projects/aria2/',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* Google-Apps-Script */
  $knownGenerics['google-apps-script'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Google-Apps-Script',
    'tool_url'=>'',
    'engine_title'=>'Google Apps Script',
    'engine_url'=>'https://www.google.com/script/start/');
  
  /* zgrab */
  $knownGenerics['zgrab'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'zgrab',
    'tool_url'=>'https://github.com/zmap/zgrab/blob/master/zlib/conn.go',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* Dispatch */
  $knownGenerics['dispatch'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Dispatch',
    'tool_url'=>'https://github.com/dispatch/reboot',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* Jersey */
  $knownGenerics['jersey'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Jersey',
    'tool_url'=>'https://jersey.github.io',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* aiohttp */
  $knownGenerics['aiohttp'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'aiohttp',
    'tool_url'=>'https://pypi.python.org/pypi/aiohttp',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* okhttp */
  $knownGenerics['okhttp'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'okhttp',
    'tool_url'=>'https://github.com/square/okhttp',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* MS Web Services Client Protocol */
  $knownGenerics['ms web services client protocol'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'MS Web Services Client Protocol (.NET)',
    'tool_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* Faraday */
  $knownGenerics['faraday'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Faraday',
    'tool_url'=>'https://mislav.net/2011/07/faraday-advanced-http/',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* Indy Library */
  $knownGenerics['indy library'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Indy Library',
    'tool_url'=>'http://www.indyproject.org/index.en.aspx',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* AnyEvent-HTTP */
  $knownGenerics['anyevent-http'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'AnyEvent-HTTP',
    'tool_url'=>'http://software.schmorp.de/pkg/AnyEvent-HTTP.html',
    'engine_title'=>'Schmorpforge Software',
    'engine_url'=>'http://software.schmorp.de');
  
  /* Splashr */
  $knownGenerics['splash'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'splash',
    'tool_url'=>'https://cran.r-project.org/web/packages/splashr/vignettes/intro_to_splashr.html',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* .NET Framework Test Client  */
  $knownGenerics['.net framework'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Microsoft .NET Framework',
    'tool_url'=>'',
    'engine_title'=>'',
    'engine_url'=>'');
  
  /* scalaj-http  */
  $knownGenerics['scalaj-http'] = array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'scalaj-http',
    'tool_url'=>'https://github.com/scalaj/scalaj-http',
    'engine_title'=>'',
    'engine_url'=>'');

  /* obot */
  $knownGenerics[' obot'] = array(
    'platform_type'=>'bot',
    'platform_format'=>'desktop',
    'bot_title'=>'oBot',
    'bot_url'=>'http://filterdb.iss.net/crawler/',
    'engine_title'=>'IBM Germany Research & Development GmbH',
    'engine_url'=>'');
    
  /* return list */
  return $knownGenerics;
}

/*** hack type specific methods ***/

/*
 * return hack index if hack
 * @param string $ua
 * @return mixed
 * @access public
 */
function client_checkIsHack($ua=false) {
  /* get user agent */
  if (!$ua)	$ua = client_getUserAgent();
 
  /* load known bots */
  $knownHacks = client_getKnownHacks();
  
  /* build detection pattern */
  $detectionPattern = implode('|', array_keys($knownHacks));
  $detectionPattern = preg_replace ('/(\/|\(|\)|\.)/', '\\\$1', $detectionPattern);
  $detectionPattern = '/'.$detectionPattern.'/i';

  /* start detection and return result */
  if ( preg_match ( $detectionPattern, strtolower($ua), $result ))
    return $result[0];
  return false;
}

/*
 * return bot info if hack
 * @param string $hack
 * @return mixed
 * @access public
 */
function client_getHackInfos($hack='') {
  $knownHacks = client_getKnownHacks();
    
  if (isset($knownHacks[$hack]))
    return $knownHacks[$hack];
  return array();
}

/*
 * return hack info from user agent
 * @param string $ua
 * @return mixed
 * @access public
 */
function client_getHackInfosFromUserAgent($ua='') {
  $knownHacks = client_getKnownHacks();
  
  /* build detection pattern */
  $detectionPattern = implode('|', array_keys($knownHacks));
  $detectionPattern = preg_replace ('/(\/|\(|\)|\.)/', '\\\$1', $detectionPattern);
  $detectionPattern = '/'.$detectionPattern.'/i';

  /* start detection and return result */
  if ( preg_match ( $detectionPattern, strtolower($ua), $result ) )
    return $knownHacks[$result[0]];
  return false;
}

/*
 * return given known web hack or hack list
 * @return array
 * @access public
 */
function client_getKnownHacks() {
  $knownHacks = array();

  /* Joomla Exploit */
  $knownHacks['jdatabasedrivermysqli'] = array(
    'platform_type'=>'hack',
    'hack_info'=>'Joomla Exploit',
  );
  
  /* Joomla Exploit */
  $knownHacks['bot/0.1 (bot for jce)'] = array(
    'platform_type'=>'hack',
    'hack_info'=>'Joomla JCE Exploit',
  );
  
  /* Bash Exploit */
  $knownHacks['() { foo;};echo; /bin/bash'] = array(
    'platform_type'=>'hack',
    'hack_info'=>'Bash Exploit',
  );
  
  /* Bash Exploit */
  $knownHacks['() { :; }; echo'] = array(
    'platform_type'=>'hack',
    'hack_info'=>'Bash Exploit',
  );
  
  /* Bash Exploit */
  $knownHacks['() { :;};'] = array(
    'platform_type'=>'hack',
    'hack_info'=>'Bash Exploit',
  );
  
  /* Drupal Fckeditor exploit */
  $knownHacks['webfuck v2.1 t0phackteam www.t0p.xyz'] = array(
    'platform_type'=>'hack',
    'hack_info'=>'Drupal Fckeditor exploit',
  );
  
  /* betaBot : should be in bot list with a trustee level to "unwanted" */
  $knownHacks['betabot'] = array(
    'platform_type'=>'hack',
    'hack_info'=>'Unwanted bot',
  );
  
  /* PHP Exploit */
  $knownHacks['php system'] = array(
    'platform_type'=>'hack',
    'hack_info'=>'PHP Exploit',
  );
  
  /* the beast malware */
  $knownHacks['the beast'] = array(
    'platform_type'=>'hack',
    'hack_info'=>'the beast malware',
  );
  
  /* return list */
  return $knownHacks;
}

/*
 * return fake visitor info from user agent
 * @param string $ua
 * @return mixed
 * @access public
 */
function client_getFakeInfosFromUserAgent($ua='') {
  $fake = array('platform_type'=>'fake');
  
  $ua = trim($ua);
  
  if ($ua == '')
    return $fake;
      
  if ($ua == 'null')
    return $fake;
      
  if (preg_match('#^Mozilla$#i', $ua))
    return $fake;
      
  if (preg_match('#^Mozilla-1.1$#i', $ua))
    return $fake;
  
  if (preg_match('#^Mozilla/[0-9][.|,]0$#i', $ua))
    return $fake;
  
  if (preg_match('#^Mozilla/%2F[0-9][.|,]0$#i', $ua))
    return $fake;
    
  if (preg_match('#^Mozilla/[0-9][.|,]0 \(compatible;?\)?$#i', $ua))
    return $fake;
        
  if (preg_match('#^Mozilla/[0-9].0 \(compatible; MSIE[0-9].00; Windows 200[1-9]\)#i', $ua))
    return $fake;
    
  if (preg_match('#^mozilla/0.([0-9]+) beta \(windows\)#i', $ua))
    return $fake;
   
  if (preg_match('#^Mozilla/1.22 \(compatible; MSIE 2.0; Windows 95\)#i', $ua))
    return $fake;
  
  if (preg_match('#^Mozilla/4.0 \(compatible; MSIE 5.0; Windows 98\)#i', $ua))
    return $fake;
  
  if (preg_match('#^Mozilla/4.0 \(compatible; MSIE 999.1; Unknown\)#i', $ua))
    return $fake;
  
  if (preg_match('#^Mozilla/1.22 \(compatible; MSIE 10.0; Windows 3.1\)#i', $ua))
    return $fake;
  
  if (preg_match('#^Mozilla/3.0 \(x86 \[en\] Windows NT 5.1; Sun\)#i', $ua))
    return $fake;
    
  if (preg_match('#^Mozilla/2.02E \(Win95; U\)$#i', $ua))
    return $fake;
    
  if (preg_match('#^Mozilla/42.0 \(compatible; MSIE 28.0; Win128\)$#i', $ua))
    return $fake;
  
  if (preg_match('#Mozilla/2.0 \(compatible; MSIE 3.02; Windows CE; 240x320\)#i', $ua))
    return $fake;
  
  if (preg_match('#Mozilla/4.0 \(compatible; MSIE 6.0; MSIE 5.5; Windows NT 5.0\) Opera 7.02 Bork-edition \[en\]#i', $ua))
    return $fake;
  
  if (preg_match('#Mozilla/5.0 \(compatible; MSIE 10.0; Macintosh; Intel Mac OS X 10_7_3; Trident/6.0\)#i', $ua))
    return $fake;

  /* fake russian spammer */
  if (preg_match('#Mozilla/1.22 \(compatible; MSIE 2.0d; Windows NT\)#i', $ua))
    return $fake;

  /* fake russian spammer */
  if (preg_match('#Mozilla/4.0 \(compatible; MSIE 7.0b; Windows NT 6.0 ; .NET CLR 2.0.50215; SL Commerce Client v1.0; Tablet PC 2.0#i', $ua))
    return $fake;

  /* fake russian spammer */
  if (preg_match('#Mozilla/4.0 \(compatible; MSIE 5.0; Windows 3.1\)#i', $ua))
    return $fake;
  
  /* funwebproducts malware */
  if (preg_match('#FunWebProducts#i', $ua))
    return $fake;
  
  /* fake russian spammer */
  if (preg_match('#^Mozilla/5.0 \(Windows NT 6.1; WOW64; rv:41.0\) Gecko/20100101 Firefox/41.0$#i', $ua))
    return $fake;
  
  /* fake russian spammer */
  if (preg_match('#^Mozilla/5.0 \(Windows NT 6.1; WOW64\) AppleWebKit/537.36 \(KHTML, like Gecko\) Chrome/40.0.2214.111 Safari/537.36$#i', $ua))
    return $fake;
  
  /* php default useragent passed as string intead of CONST */
  if (preg_match('#^_USERAGENT_$#i', $ua))
    return $fake;
    
  /* fake requests from Amazon AWS services */
  if (preg_match('#^Mozilla/5.0 \(Windows NT 6.1; rv:15.0\) Gecko/20120716 Firefox/15.0a2$#i', $ua))
    return $fake;
  if (preg_match('#^"Mozilla/5.0([^"]*)"$#i', $ua))
    return $fake;
    
  /* fake requests from Lituania */
  if (preg_match('#^Dalvik/2.1.0 \(Linux; U; Android 5.1.1; D5503 Build/14.6.A.1.236\)$#i', $ua))
    return $fake;
  
  /* fake requests with double user agent combined */
  if (preg_match_all('#Mozilla/[0-9].0#i', $ua, $matches) and count($matches[0]) > 1)
    return $fake;
  
  /* fake requests from China */
  if (preg_match('#^Mozilla/5.0 \(Windows; U; Windows NT 6.1; en-us; rv:1.9.2.3\) Gecko/20100401 YFF35 Firefox/3.6.3$#i', $ua))
    return $fake;
  
  /* fake request */
  if (preg_match('#\'Mozilla/5.0\(Macintosh;IntelMacOSX10_8_2\)AppleWebKit/537.36\(KHTML,likeGecko\)Chrome/27.0.1453.116Safari/537.36\'#i', $ua))
    return $fake;
  
  /* fake requests with uncomplete gecko firefox UA, same IP as Python requests */
  if (preg_match('#^\'Mozilla/5.0 Gecko Firefox\'$#i', $ua))
    return $fake;
    
  /* fake requests from 80.169.91.26 */
  if (preg_match('#-[0-9]{7}$#', $ua))
    return $fake;
  
  /* badly set user agent */
  if (preg_match('#^=#', $ua))
    return $fake;
  
  /* bad msie/msid request */
  if (preg_match('#^Mozilla/4.0 \(compatible; MSID [0-9\.]+; Windows NT [0-9\.]+\)$#i', $ua))
    return $fake;
  
  /* not a fake but Apple using a bad user agent */
  if (preg_match('#Mozilla/5.0 \(Macintosh; Intel Mac OS X 10_11_1\) AppleWebKit/601.2.4 \(KHTML, like Gecko\) Version/9.0.1 Safari/601.2.4 facebookexternalhit/1.1 Facebot Twitterbot/1.0#', $ua))
    return array(
    'platform_type'=>'tool',
    'platform_format'=>'desktop',
    'tool_title'=>'Apple iMessages bot',
    'tool_url'=>'',
    'engine_title'=>'Apple',
    'engine_url'=>'http://www.apple.com');
  
  /* badly set user agent */
  if (preg_match('#Connection: closern$#i', $ua))
    return $fake;
    
  /* default result */
  return false;
}

/*** private methods ***/

/*                  
 * return merged informations                     
 * @param array $req                
 * @param array $infos               
 * @return array                  
 * @access private                  
 */
function _client_mergeUAInfos($req, $infos) {
  if ($req === true)
    $req = array(
        'platform_company', 'platform_model', 'platform_type', 'platform_format',
        'system_title', 'system_version',
        'browser_title', 'browser_version'
    );
  $i = array();
  foreach($req as $r)
    if (isset($infos[$r]))
      $i[$r] = $infos[$r];
    else
      $i[$r] = '';
  return $i;
}

/*
 * return some max property values to check 
 * @return array
 * @access private
 */
function _client_getUAPropertiesMaxVersions() {
  return array(
    'system' => array(
        'Mac OS X'          => '10.15.0',
        'iOS'               => '13',
        'Android'           => '9',
    ),
    'browser' => array(
        'Firefox'           => '60',
        'Chrome'            => '70',
        'Chromium'          => '70',
        'Internet Explorer' => '11.0.50',
        'Edge'              => '45',
        'Opera'             => '52',
    ),
  );
}
?>
