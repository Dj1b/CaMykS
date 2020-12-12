<?php
/**
 * @brief IPGeolocator Input configuration object
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
 * IPGeolocatorConfig PluginConfig class.
 */
final class IPGeolocatorConfig extends PluginConfig {
    /**
     * Class constructor.
     * @param string $name
     * @param Module $parent
     * @return void
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* Define plugin params */
        $this->add_newItem('service', 'string', 'IPGeolocationAPI');

        /* Services API key */
        $this->add_newItem('APIKey_IPGeolocation', 'string', '');
        $this->add_newItem('APIKey_IPStack', 'string', '');
        $this->add_newItem('APIKey_IPStackPremium', 'integer', 0);
        $this->add_newItem('APIKey_IPAPI', 'string', '');
        $this->add_newItem('APIKey_IPAPIPremium', 'integer', 0);
        $this->add_newItem('APIKey_IPData', 'string', '');
        $this->add_newItem('APIKey_Ipify', 'string', '');
        $this->add_newItem('APIKey_IPWhois', 'string', '');
        $this->add_newItem('APIKey_IPRegistry', 'string', '');
        $this->add_newItem('APIKey_IPInfoDB', 'string', '');
        $this->add_newItem('APIKey_DB_IP', 'string', '');
        $this->add_newItem('APIKey_IP2Location', 'string', '');

        /* generic initialisation */
        parent::init_config();
    }

    /* Specific data methods */

    /**
     * Return services list.
     * @return array
     */
    public function get_serviceList() {
        return array(
            'IPGeolocationAPI' => array(
                'Title'     => 'IP Geolocation API',
                'URL'       => 'https://www.ipgeolocationapi.com',
                'APIKeyURL' => '',
            ),
            'IP_API' => array( /* Can't get documentation for pro service */
                'Title'     => 'ip-api',
                'URL'       => 'https://ip-api.com',
                'APIKeyURL' => '',
            ),
            'IPGeolocation' => array(
                'Title'     => 'ipgeolocation',
                'URL'       => 'https://ipgeolocation.io',
                'APIKeyURL' => 'https://app.ipgeolocation.io',
            ),
            'IPStack' => array(
                'Title'     => 'ipstack',
                'URL'       => 'https://ipstack.com',
                'APIKeyURL' => 'https://ipstack.com/product',
            ),
            'IPAPI' => array( /* Duplicate of IPStack */
                'Title'     => 'ipapi',
                'URL'       => 'https://ipapi.com/',
                'APIKeyURL' => 'https://ipapi.com/product',
            ),
            'IPData' => array(
                'Title'     => 'ipdata',
                'URL'       => 'https://ipdata.co/',
                'APIKeyURL' => 'https://ipdata.co/pricing.html',
            ),
            'Ipify' => array(
                'Title'     => 'ipify',
                'URL'       => 'https://geo.ipify.org',
                'APIKeyURL' => 'https://geo.ipify.org/pricing',
            ),
            'IPWhois' => array(
                'Title'     => 'ipwhois.io',
                'URL'       => 'https://ipwhois.io',
                'APIKeyURL' => 'https://ipwhois.io/pricing',
            ),
            'IPAPICO' => array( /* Can't get documentation to Premium documentation */
                'Title'     => 'ipapi.co',
                'URL'       => 'https://ipapi.co',
                'APIKeyURL' => 'https://ipapi.co/#pricing',
            ),
            'IPRegistry' => array(
                'Title'     => 'ipregistry',
                'URL'       => 'https://ipregistry.co',
                'APIKeyURL' => 'https://dashboard.ipregistry.co/signup',
            ),
            'IPInfoDB' => array(
                'Title'     => 'IPInfoDB',
                'URL'       => 'https://www.ipinfodb.com',
                'APIKeyURL' => 'https://www.ipinfodb.com/register',
            ),
            'DB_IP' => array( /* Testing requires a credit card */
                'Title'     => 'dbip',
                'URL'       => 'https://db-ip.com',
                'APIKeyURL' => '',
            ),
            'IP2Location' => array( /* Full testing requires an upgraded account */
                'Title'     => 'IP2Location',
                'URL'       => 'https://www.ip2location.com',
                'APIKeyURL' => 'https://www.ip2location.com/web-service/ip2location',
            ),
        );
    }

    /**
     * Return service title list.
     * @return array
     */
    public function get_serviceTitleList() {
        $result = array();
        foreach ($this->get_serviceList() as $id => $service)
            $result[$id] = $service['Title'].' ('.$service['URL'].')';
        return $result;
    }

    /**
     * Return service title.
     * @return array
     */
    public function get_serviceTitle() {
        $list = $this->get_serviceList();
        if (isset($list[$this->vars['service']]))
            return $list[$this->vars['service']]['Title'];
        return '';
    }
}
?>
