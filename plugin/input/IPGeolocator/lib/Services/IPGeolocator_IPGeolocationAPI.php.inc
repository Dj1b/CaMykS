<?php
/**
 * @brief IPGeolocator Input, IP Geolocation API service object
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
 * IPGeolocator_IPGeolocationAPI class.
 */
final class IPGeolocator_IPGeolocationAPI {

    /**
     * Execute IP geolocation.
     * @param array $params
     * @return mixed
     */
    public function execute($params) {
        /* Execute request to IP Geolocation API service */
        $result = http_getContents(array('url'=>'https://api.ipgeolocationapi.com/geolocate/'.$params['ipAddress']));

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
            'AddressCity' => '',

            /* Region / state */
            'RegionCode' => '',
            'RegionName' => '',

            /* Country data */
            'CountryAlpha2' => strToLower($data['alpha2']),
            'CountryAlpha3' => strToLower($data['alpha3']),
            'CountryName' => $data['name'],

            /* Continent data */
            'ContinentCode' => '',
            'ContinentName' => $data['region'],

            /* Geolocalisation */
            'Latitude' => $data['geo']['latitude'],
            'Longitude' => $data['geo']['longitude'],
        );
    }
}
?>
