<?php
/**
 * @brief IPGeolocator Input, ipapi service object, which is a duplicate of ipstack
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
 * IPGeolocator_IPAPI class.
 */
final class IPGeolocator_IPAPI {
    /**
     * Execute IP geolocation.
     * @param array $params
     * @return mixed
     */
    public function execute($params) {
        /* Check API Key params */
        if ($params['APIKey_IPAPI'] == '')
            return false;

        /* Build request URL */
        $url = 'http'.($params['APIKey_IPAPIPremium'] == 1 ? 's' : '').'://api.ipapi.com/'.$params['ipAddress'];
        $url .= '?access_key='.$params['APIKey_IPAPI'];

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
            'AddressZipcode' => $data['zip'],
            'AddressCity' => $data['city'],

            /* Region / state */
            'RegionCode' => strToLower($data['region_code']),
            'RegionName' => $data['region_name'],

            /* Country data */
            'CountryAlpha2' => strToLower($data['country_code']),
            'CountryAlpha3' => '',
            'CountryName' => $data['country_name'],

            /* Continent data */
            'ContinentCode' => strToLower($data['continent_code']),
            'ContinentName' => $data['continent_name'],

            /* Geolocalisation */
            'Latitude' => $data['latitude'],
            'Longitude' => $data['longitude'],
        );
    }
}
?>
