<?php
/**
 * @brief IPGeolocator Input, IP2Location service object
 * @details Plugin / Input Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Dec 2020
 * @date Modification: Dec 2020
 * @copyright 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * IPGeolocator_IP2Location class.
 */
final class IPGeolocator_IP2Location {
    /**
     * Execute IP geolocation.
     * @param array $params
     * @return mixed
     */
    public function execute($params) {
        /* Check API Key params */
        if ($params['APIKey_IP2Location'] == '')
            return false;

        /* Check API Key params to build request URL */
        $url = 'https://api.ip2location.com/v2/?ip='.$params['addressIp'].'&addon=continent,country,region,city,geotargeting&key='.$params['APIKey_IP2Location'];

        /* Execute request to IP Geolocation API service */
        $result = http_getContents(array('url'=>$url));

        /* Check result */
        if (strlen($result) == 0)
            return false;

        /* Check JSON */
        $data = json_decode($result, true);
        if (json_last_error() !== JSON_ERROR_NONE or !is_array($data))
            return false;

        /* Build and return result */
        return array(
            /* Address data */
            'Address' => '',
            'AddressZipcode' => $data['zip_code'],
            'AddressCity' => $data['city_name'],

            /* Region / state */
            'RegionCode' => '',
            'RegionName' => $data['region_name'],

            /* Country data */
            'CountryAlpha2' => strToLower($data['country_code']),
            'CountryAlpha3' => '',
            'CountryName' => $data['country_name'],

            /* Continent data */
            'ContinentCode' => strToLower($data['continent']['code']),
            'ContinentName' => $data['continent']['name'],

            /* Geolocalisation */
            'Latitude' => $data['latitude'],
            'Longitude' => $data['longitude'],
        );
    }
}
?>

