<?php
/**
 * @brief IPGeolocator Input, ipify service object
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
 * IPGeolocator_Ipify class.
 */
final class IPGeolocator_Ipify {
    /**
     * Execute IP geolocation.
     * @param array $params
     * @return mixed
     */
    public function execute($params) {
        /* Check API Key params */
        if ($params['APIKey_Ipify'] == '')
            return false;

        /* Build request URL */
        $url = 'https://geo.ipify.org/api/v1?apiKey='.$params['APIKey_Ipify'];
        $url .= '&ipAddress='.$params['addressIp'];

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
            'AddressZipcode' => $data['location']['postalCode'],
            'AddressCity' => $data['location']['city'],

            /* Region / state */
            'RegionCode' => '',
            'RegionName' => $data['location']['region'],

            /* Country data */
            'CountryAlpha2' => strToLower($data['location']['country']),
            'CountryAlpha3' => '',
            'CountryName' => '',

            /* Continent data */
            'ContinentCode' => '',
            'ContinentName' => '',

            /* Geolocalisation */
            'Latitude' => $data['location']['lat'],
            'Longitude' => $data['location']['lng'],
        );
    }
}
?>
