<?php
/**
 * @brief France related methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.4
 * @date Creation: Apr 2017
 * @date Modification: Jul 2025
 * @copyright 2017 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Check if given phone number is valid for french phone numbers.
 * @param string $number
 * @param array $params
 * @parblock - Available parameters are <br />
 * \e boolean mobileOnly <br />
 * @endparblock
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
        /* check local format */
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

/**
 * Return france socioprofessional categories.
 * @param array $params
 * @parblock - Available parameters are <br />
 * \e string language <br />
 * \e integer groups - \b 0 : no / \b 1 : simple \b 2 : unselectable for select <br />
 * \e integer addNone - \b 0 : off / \b 1 : none \b 2 : void <br />
 * \e integer addNumber - \b 0 : off / \b 1 : on <br />
 * @endparblock
 * @return array
 */
function france_getSocioProfessionalCategoryList($params=array()) {
    global $camyks;

    /* build default params list */
    $defaultParams = array(
        'language'      => $camyks->current_language,
        'addGroups'     => 0,
        'addNone'       => 0,
        'addNumber'     => 0,
        'groupStyle'    => 'color:#ADADAD;',
    );

    /* merge params */
    $params = array_merge($defaultParams, $params);

    /* load locales */
    $camyks->add_generic_translation('frenchsocioprofessionaldata', $params['language']);

    $data = array(
        1 => array(11, 12, 13),
        2 => array(21, 22, 23),
        3 => array(31, 33, 34, 35, 37, 38),
        4 => array(42, 43, 44, 45, 46, 47, 48),
        5 => array(52, 53, 54, 55, 56),
        6 => array(62, 63, 64, 65, 67, 68, 69),
        7 => array(71, 72, 74, 75, 77, 78),
        8 => array(81, 83, 84, 85, 86),
    );

    /* initialise list */
    $list = array();

    /* check for add none */
    if ($params['addNone'] == 1)
        $list[0] = $camyks->get_translation('frenchsocioprofessionaldata_category0');
    elseif ($params['addNone'] == 2)
        $list[0] = '';

    /* build list */
    $pre = '';
    foreach ($data as $group => $categories) {
        if ($params['addNumber'] == 1)
            $pre = $group.' - ';

        if ($params['addGroups'] == 1)
            $list[$group] = $pre.$camyks->get_translation('frenchsocioprofessionaldata_group'.$group);
        elseif ($params['addGroups'] == 2)
            $list[$group] = array('value'=>$pre.$camyks->get_translation('frenchsocioprofessionaldata_group'.$group), 'style'=>$params['groupStyle'], 'disabled'=>'disabled');

        foreach ($categories as $category) {
            if ($params['addNumber'] == 1)
                $pre = $category.' - ';
            $list[$category] = $pre.$camyks->get_translation('frenchsocioprofessionaldata_category'.$category);
        }
    }
    /* return list */
    return $list;
}

/**
 * Return france socioprofessional category title.
 * @param string $category
 * @param string $language
 * @return string
 */
function france_getSocioProfessionalCategoryTitle($category='', $language='') {
    global $camyks;

    /* check lang value */
    if ($language=='') $language = $camyks->current_language;

    /* load locales */
    $camyks->add_generic_translation('frenchsocioprofessionaldata', $language);

    /* Check category or group */
    if ($category == 0)
        return $camyks->trads['frenchsocioprofessionaldata_category0'];
    if ($category < 10) {
        if (isset($camyks->trads['frenchsocioprofessionaldata_group'.$category]))
            return $camyks->trads['frenchsocioprofessionaldata_group'.$category];
    } else {
        if (isset($camyks->trads['frenchsocioprofessionaldata_category'.$category]))
            return $camyks->trads['frenchsocioprofessionaldata_category'.$category];
    }

    /* Return default void result */
    return '';
}

/**
 * Return France holiday list for given year.
 * @param integer $year
 * @return array
 */
function france_getHolidayList($year=null) {
    /* Check year */
    if (is_null($year)) $year = date('Y');

    /* Initialise list */
    $list = array();

    /* Adds New Year's day */
    $list[] = date_getNewYearsDay($year);

    /* Adds religeous days */
    $easter = date_getEasterDay($year);
    $list[] = mktime(0, 0, 0, date('n', $easter), date('j', $easter)+1, $year);
    $list[] = date_getAscensionDay(null, $easter);
    $list[] = date_getPentecostDay(null, $easter);
    $list[] = date_getAssumptionDay($year);
    $list[] = date_getAllSaintsDay($year);
    $list[] = date_getChristmasDay($year);

    /* Adds national days */
    $list[] = mktime(0, 0, 0, 5, 1, $year);
    $list[] = mktime(0, 0, 0, 5, 8, $year);
    $list[] = mktime(0, 0, 0, 7, 14, $year);
    $list[] = mktime(0, 0, 0, 11, 11, $year);

    /* Sort list */
    sort($list);

    /* Return list */
    return $list;
}

/**
 * Return French company international VAT Number from its SIREN.
 * @param string $siren
 * @return string
 */
function france_getIntlVATFromSiren($siren) {
    $key = "".($siren % 97 * 3 + 12) % 97;
    $key = str_pad($key, 2, "0", STR_PAD_LEFT);
    return 'FR'.$key.$siren;
}
?>
