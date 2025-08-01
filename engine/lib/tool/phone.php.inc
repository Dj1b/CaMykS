<?php
/**
 * @brief Phone related methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Nov 2024
 * @date Modification: Nov 2024
 * @copyright 2024 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Parse phone number
 * @param string $number
 * @param array $countryCode
 * @return mixed
 */
function phone_parse($number, $countryCode) {

    /* Initialise result */
    $result = array('AreaCode'=>'', 'Number'=>'', 'Type'=>'');

    /* Check for phone splitters */
    $number = preg_replace('/[\.\-]/', ' ', $number);

    /* Check number is valid and find format prefix */
    if (!preg_match('/^([\+]|00|0)([0-9 ]+)$/', $number, $matches)) {
        return false;
    }

    /* Load area code from country data */
    $result['AreaCode'] = countries_getSingleDataValue($countryCode, 'PhoneIndex');

    /* Find number */
    if ($matches[1] === '0') {
        /* Parse local number */
        $result['Number'] = $matches[2];
    } else {
        /* Parse intl number */
        if (string_startsWith($matches[2], preg_replace('/[\.\-]/', ' ', $result['AreaCode']))) {
            $result['Number'] = substr($matches[2], strlen($result['AreaCode']));
        }
    }

    /* Clear number */
    $result['Number'] = preg_replace('/ /', '', $result['Number']);

    /* Check type */
    switch ($countryCode) {
        case 'be':
            $result['Type'] = preg_match('/^4[56789]/', $result['Number']) ? 'Mobile' : 'Fixed'; break;
        case 'ch':
            $result['Type'] = preg_match('/^7[56789]/', $result['Number']) ? 'Mobile' : 'Fixed'; break;
        case 'fr':
            $result['Type'] = in_array(substr($result['Number'], 0, 1), array('6','7')) ? 'Mobile' : 'Fixed'; break;
        default:
    }

    /* Return result */
    return $result;
}
?>
