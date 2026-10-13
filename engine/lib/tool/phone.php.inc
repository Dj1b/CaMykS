<?php
/**
 * @brief Phone related methods.
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Nov 2024
 * @date Modification: Oct 2025
 * @copyright 2024 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Check phone number is valid.
 * @param string $number
 * @return boolean result
 */
function phone_isNumberValid($number) {
    return preg_match('/^([\+]|00|0)([0-9\.\- ]+)$/', $number, $matches);
}

/**
 * Parse phone number.
 * @param string $number
 * @param string $defaultCountryCode
 * @return mixed
 */
function phone_parse($number, $defaultCountryCode=null) {
    global $__countriesData;

    /* Initialise result */
    $result = array('CountryCode'=>$defaultCountryCode, 'AreaCode'=>'', 'Number'=>'', 'Type'=>'');

    /* Clean phone number */
    $number = trim(preg_replace('/[^0-9\+]/', '', $number));

    /* Check number is valid and find format prefix */
    if (!preg_match('/^([\+]|00|0)([0-9 ]+)$/', $number, $matches)) {
        return false;
    }

    /* Detect country */
    if ($matches[1] !== '0') {
        countries_loadData();
        foreach ($__countriesData as $code => $data) {
            if (!empty($data['PhoneIndex']) and !empty($data['PhoneLength'])) {
                if (preg_match('/^('.$data['PhoneIndex'].')([0-9]{'.$data['PhoneLength'].'})$/', $matches[2], $m)) {
                    $result['CountryCode'] = $code;
                    $result['AreaCode'] = $m[1];
                    $result['Number'] = $m[2];
                    break;
                }
            }
        }
    }

    if ($result['Number'] == '') {
        /* Load area code from country data */
        $code = countries_getSingleDataValue($defaultCountryCode, 'PhoneIndex');

        if (string_startsWith($matches[2], preg_replace('/[\.\-]/', ' ', $result['AreaCode']))) {
            $result['Number'] = substr($matches[2], strlen($result['AreaCode']));
            $result['AreaCode'] = $code;
        } else {
            $result['Number'] = $matches[2];
        }
    }

    /* Check type */
    switch ($result['CountryCode']) {
        case 'be':
            $result['Type'] = preg_match('/^4[56789]/', $result['Number']) ? 'Mobile' : 'Fixed'; break;
        case 'ch':
            $result['Type'] = preg_match('/^7[56789]/', $result['Number']) ? 'Mobile' : 'Fixed'; break;
        case 'fr':
            $result['Type'] = in_array(substr($result['Number'], 0, 1), array('6','7')) ? 'Mobile' : 'Fixed'; break;
        case 'gb':
            $result['Type'] = substr($result['Number'], 0, 1) == '7' ? 'Mobile' : 'Fixed'; break;
        default:
    }

    /* Return result */
    return $result;
}

/**
 * Display phone number.
 * @param string $number
 * @param string $defaultCountryCode
 * @param string $prefixDisplay
 * @return string
 */
function phone_display($number, $defaultCountryCode=null, $prefixDisplay='code') {
    $number = phone_parse($number, $defaultCountryCode);

    /* Check Country code */
    if (is_null($number['CountryCode']))
        $prefixDisplay = 'local';

    /* Format prefix */
    switch ($prefixDisplay) {
        case 'local':
            switch ($number['CountryCode']) {
                case 'fr':
                case 'gb':
                default :
                    $prefix = '0'; break;
            }
            break;
        case 'full':
            switch ($number['CountryCode']) {
                case 'fr':
                    $prefix = '+'.$number['AreaCode'].' (0)'; break;
                default :
                    $prefix = '+'.$number['AreaCode'].' '; break;
            }
            break;
        case 'code':
        default:
            $prefix = '+'.$number['AreaCode'].' '; break;
    }

    /* Format number main part */
    switch ($number['CountryCode']) {
        case 'fr':
            $main = substr($number['Number'], 0, 1).' '.substr($number['Number'], 1, 2).' '.substr($number['Number'], 3, 2).' '.substr($number['Number'], 5, 2).' '.substr($number['Number'], 7, 2); break;
        case 'gb':
            $main = substr($number['Number'], 0, 4).' '.substr($number['Number'], 4); break;
        default:
            $main = $number['Number'];
    }

    /* Build result */
    return $prefix.$main;
}
?>
