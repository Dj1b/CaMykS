<?php
/**
 * @brief IPGeolocator Input, ip-api service object, library has to be updated with pro service support.
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
 * IPGeolocator_IP_API class.
 */
final class IPGeolocator_IP_API {
    /**
     * Execute IP geolocation.
     * @param array $params
     * @return mixed
     */
    public function execute($params) {
        /* Execute request to IP Geolocation API service */
        $result = http_getContents(array('url'=>'http://ip-api.com/json/'.$params['ipAddress'].'?fields=status,continent,country,countryCode,region,regionName,city,zip,lat,lon'));

        /* Check result */
        if (strlen($result) == 0)
            return false;

        /* Check JSON */
        $data = json_decode($result, true);
        if (json_last_error() !== JSON_ERROR_NONE or !is_array($data))
            return false;

        /* Check query success */
        if ($data['status'] != 'success')
            return false;

        /* Build and return result */
        return array(
            /* Address data */
            'Address' => '',
            'AddressZipcode' => $data['zip'],
            'AddressCity' => $data['city'],

            /* Region / state */
            'RegionCode' => strToLower($data['region']),
            'RegionName' => $data['regionName'],

            /* Country data */
            'CountryAlpha2' => strToLower($data['countryCode']),
            'CountryAlpha3' => '',
            'CountryName' => $data['country'],

            /* Continent data */
            'ContinentCode' => strToLower($data['continentCode']),
            'ContinentName' => $data['continent'],

            /* Geolocalisation */
            'Latitude' => $data['lat'],
            'Longitude' => $data['lon'],
        );
    }
}
?>
