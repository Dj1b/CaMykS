<?php
/*
 * CaMykS Engine
 * Developed by       : camyks.net
 * Author             : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version     : 1.0
 * Object Version     : 1.0
 * Object Type        : Engine / Tool Library
 * Creation Date      : Apr 2017
 * Last Modif Date    : Jun 2017
 *
 * Specific methods related to France
 * /!\ This library is not loaded with CaMykS initialisation
 */

/*
 * check if given number is valid for french phone numbers
 * @param string $number
 * @param mixed $value
 * @param boolean $keepKeys
 * @return string
 * @access public
 */
function france_isValidPhoneNumber($number, $params=array()) {
  
  /* merge params */
  $dParams = array('mobileOnly'=>false);
  $params = array_merge($dParams, $params);
  
  /* check intl format */
  if (preg_match('/^\+33 ?(\(0\))? ([0-9\- ]+)$/', $number, $matches)) {
    
    $number = preg_replace ('/[^0-9]/', '', $matches[2]);
    if (strlen($number) != 9)
      return false;
          
    if ($params['mobileOnly']==true and !in_array(substr($number, 0, 1), array(6, 7)))
      return false;
      
  } else {
    /* check locale format */
    $number = preg_replace ('/[^0-9]/', '', $number);
      
    if (strlen($number) != 10)
      return false;
    if (substr($number, 0, 1) != 0)
      return false;
        
    if ($params['mobileOnly']==true and !in_array(substr($number, 1, 1), array(6, 7)))
      return false;
  }
  return true;
}

/*
 * return france department list
 * @param array $params
 * @return array
 * @access public
 */
function france_getDepartmentList($params=array()) {
  global $camyks;
  
  /* build default params list */
  $defaultParams = array(
    'language'  => $camyks->current_language,
    'corsica'   => 1, // 1 : one line 20 / 2 : two lines 2A/2B
    'monaco'    => 0, // 0 : off / 1 : on
    'domtom'    => 0, // 0 : off / 1 : on
  );
  
  /* merge params */
  $params = array_merge($defaultParams, $params);
  
  /* load locales */
  $camyks->add_generic_translation('frenchdepartments', $params['language']);
  
  /* initialise list */
  $list = array();
  
  /* build list up to corsica */
  for ($i=1; $i<20; $i++) {
    $dep = str_pad($i, 2, '0', STR_PAD_LEFT);
    $list[$dep] = $camyks->get_translation('frenchdepartment_'.$dep);
  }
  
  /* complete list with corsica */
  if ($params['corsica'] == 2) {
    $list['2A'] = $camyks->get_translation('frenchdepartment_2A');
    $list['2B'] = $camyks->get_translation('frenchdepartment_2B');
  } else
    $list['20'] = $camyks->get_translation('frenchdepartment_20');
    
  /* complete list up to monaco */
  for ($i=21; $i<96; $i++) {
    $list[$i] = $camyks->get_translation('frenchdepartment_'.$i);
  }
  
  /* complete list with monaco */
  if ($params['monaco'] == 1)
    $list['95'] = $camyks->get_translation('frenchdepartment_95');
  
  /* complete list with domtom */
  if ($params['domtom'] == 1) {
    $list['971'] = $camyks->get_translation('frenchdepartment_971');
    $list['972'] = $camyks->get_translation('frenchdepartment_972');
    $list['973'] = $camyks->get_translation('frenchdepartment_973');
    $list['974'] = $camyks->get_translation('frenchdepartment_974');
    $list['975'] = $camyks->get_translation('frenchdepartment_975');
    $list['976'] = $camyks->get_translation('frenchdepartment_976');
    $list['977'] = $camyks->get_translation('frenchdepartment_977');
    $list['978'] = $camyks->get_translation('frenchdepartment_978');
    $list['986'] = $camyks->get_translation('frenchdepartment_986');
    $list['987'] = $camyks->get_translation('frenchdepartment_987');
    $list['988'] = $camyks->get_translation('frenchdepartment_988');    
  }
  
  /* return list */
  return $list;
}

/*
 * return france department title
 * @param string $deptNum
 * @param string $language
 * @return string
 * @access public
 */
function france_getDepartmentTitle($deptNum='', $language='') {
  global $camyks;
  
  /* check lang value */
  if ($language=='') $language = $camyks->current_language;
  
  /* load locales */
  $camyks->add_generic_translation('frenchdepartments', $language);
  
  /* check deptNum value */
  $deptNum = str_pad($deptNum, 2, '0', STR_PAD_LEFT);
  
  /* check locale */
  if (isset($camyks->trads['frenchdepartment_'.$deptNum]))
    return $camyks->trads['frenchdepartment_'.$deptNum];
  return $deptNum;
}

?>