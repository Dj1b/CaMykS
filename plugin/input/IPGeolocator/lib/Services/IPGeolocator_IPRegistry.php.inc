<?php
/**
 * @brief IPGeolocator Input, ipregistry service object
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
 * IPGeolocator_IPRegistry class.
 */
final class IPGeolocator_IPRegistry {
    /**
     * Execute IP geolocation.
     * @param array $params
     * @return mixed
     */
    public function execute($params) {
        /* Check API Key params */
        if ($params['APIKey_IPRegistry'] == '')
            return false;

        /* Check API Key params to build request URL */
        $url = 'https://api.ipregistry.co/'.$params['addressIp'].'?key='.$params['APIKey_IPRegistry'];

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
            'AddressZipcode' => $data['location']['postal'],
            'AddressCity' => $data['location']['city'],

            /* Region / state */
            'RegionCode' => strToLower($data['location']['region']['code']),
            'RegionName' => $data['location']['region']['code'],

            /* Country data */
            'CountryAlpha2' => strToLower($data['location']['country']['code']),
            'CountryAlpha3' => '',
            'CountryName' => $data['location']['country']['name'],

            /* Continent data */
            'ContinentCode' => strToLower($data['location']['continent']['code']),
            'ContinentName' => $data['location']['continent']['name'],

            /* Geolocalisation */
            'Latitude' => $data['location']['latitude'],
            'Longitude' => $data['location']['longitude'],
        );
    }
}
?>
