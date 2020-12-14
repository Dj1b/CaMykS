<?php
/**
 * @brief IPGeolocator Input, ipwhois.io service object
 * @details Plugin / Input Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.1
 * @date Creation: Dec 2020
 * @date Modification: Dec 2020
 * @copyright 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * IPGeolocator_IPWhois class.
 */
final class IPGeolocator_IPWhois {
    /**
     * Execute IP geolocation.
     * @param array $params
     * @return mixed
     */
    public function execute($params) {
        /* Check API Key params to build request URL */
        if ($params['APIKey_IPWhois'] == '')
            $url = 'http://ipwhois.app/json/'.$params['ipAddress'];
        else
            $url = 'http://ipwhois.pro/json/'.$params['ipAddress'].'?key='.$params['APIKey_IPWhois'];

        /* Execute request to IP Geolocation API service */
        $result = http_getContents(array('url'=>$url));

        /* Check result */
        if (strlen($result) == 0)
            return false;

        /* Check JSON */
        $data = json_decode($result, true);
        if (json_last_error() !== JSON_ERROR_NONE or !is_array($data))
            return false;

        /* Check query success */
        if ($data['success'] != true)
            return false;

        /* Build and return result */
        return array(
            /* Address data */
            'Address' => '',
            'AddressZipcode' => '',
            'AddressCity' => $data['city'],

            /* Region / state */
            'RegionCode' => '',
            'RegionName' => $data['region'],

            /* Country data */
            'CountryAlpha2' => strToLower($data['country_code']),
            'CountryAlpha3' => '',
            'CountryName' => $data['country'],

            /* Continent data */
            'ContinentCode' => strToLower($data['continent_code']),
            'ContinentName' => $data['continent'],

            /* Geolocalisation */
            'Latitude' => $data['latitude'],
            'Longitude' => $data['longitude'],
        );
    }
}
?>
