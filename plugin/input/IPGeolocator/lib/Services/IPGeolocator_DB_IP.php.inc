<?php
/**
 * @brief IPGeolocator Input, DB_IP service object
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
 * IPGeolocator_DB_IP class.
 */
final class IPGeolocator_DB_IP {
    /**
     * Execute IP geolocation.
     * @param array $params
     * @return mixed
     */
    public function execute($params) {
        /* Check API Key params */
        if ($params['APIKey_DB_IP'] == '')
            return false;

        /* Check API Key params to build request URL */
        $url = 'http://api.db-ip.com/v2/'.$params['APIKey_DB_IP'].'/'.$params['ipAddress'];

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
            'AddressZipcode' => '',
            'AddressCity' => $data['city'],

            /* Region / state */
            'RegionCode' => '',
            'RegionName' => $data['stateProv'],

            /* Country data */
            'CountryAlpha2' => strToLower($data['countryCode']),
            'CountryAlpha3' => '',
            'CountryName' => $data['countryName'],

            /* Continent data */
            'ContinentCode' => strToLower($data['continentCode']),
            'ContinentName' => $data['continentName'],

            /* Geolocalisation */
            'Latitude' => '',
            'Longitude' => '',
        );
    }
}
?>
