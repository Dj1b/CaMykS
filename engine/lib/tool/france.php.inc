<?php
/**
 * @brief France related methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/france.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Apr 2017
 * @date Modification: Apr 2018
 * @copyright 2017 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Check if given phone number is valid for french phone numbers.
 * @param string $number
 * @param array $params
 * @return boolean
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

/**
 * Return france department list.
 * @param array $params
 * @parblock - Available parameters are <br />
 * \e string language <br />
 * \e integer corsica - \b 1 : one line "20" / \b 2 : two lines "2A" & "2B" <br />
 * \e integer monaco - \b 0 : off / \b 1 : on <br />
 * \e integer domtom - \b 0 : off / \b 1 : on <br />
 * @endparblock
 * @return array
 */
function france_getDepartmentList($params=array()) {
    global $camyks;
  
    /* build default params list */
    $defaultParams = array(
        'language'  => $camyks->current_language, 
        'corsica'   => 1,
        'monaco'    => 0,
        'domtom'    => 0,
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

/**
 * Return france department title.
 * @param string $deptNum
 * @param string $language
 * @return string
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