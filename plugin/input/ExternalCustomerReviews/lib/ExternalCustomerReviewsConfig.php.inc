<?php
/**
 * @brief ExternalCustomerReviews input, configuration library.
 * @details Plugin / Input Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Oct 2026
 * @date Modification: Oct 2026
 * @copyright 2026 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * ExternalCustomerReviewsConfig PluginConfig class.
 */
final class ExternalCustomerReviewsConfig extends PluginConfig {
    /**
     * Class constructor.
     * @param string $name
     * @param Plugin $parent
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* General & display parameters */
        $this->add_newItem('styleSource', 'string', 'plugin');      // plugin / theme
        $this->add_newItem('source', 'string', 'Google');           // Google / TripAdvisor / TrustPilot / Yelp / AvisVerifies / Facebook
        $this->add_newItem('layout', 'string', 'grid');             // grid / list / badge
        $this->add_newItem('showSummary', 'integer', 1);            // 0: hidden / 1: displayed
        $this->add_newItem('maxReviews', 'integer', 5);             // 0: all / >0: max count
        $this->add_newItem('minRating', 'integer', 1);              // 1 to 5
        $this->add_newItem('cacheTTL', 'integer', 86400);           // Cache duration in seconds (default 24h)

        /* Google Places credentials */
        $this->add_newItem('google_apiKey', 'string', '');
        $this->add_newItem('google_placeId', 'string', '');

        /* TripAdvisor Content API credentials */
        $this->add_newItem('tripadvisor_apiKey', 'string', '');
        $this->add_newItem('tripadvisor_locationId', 'string', '');

        /* TrustPilot Public API credentials */
        $this->add_newItem('trustpilot_apiKey', 'string', '');
        $this->add_newItem('trustpilot_businessUnitId', 'string', '');

        /* Yelp Fusion API credentials */
        $this->add_newItem('yelp_apiKey', 'string', '');
        $this->add_newItem('yelp_businessId', 'string', '');

        /* Avis Verifies (Skeepers) credentials */
        $this->add_newItem('avisverifies_websiteId', 'string', '');
        $this->add_newItem('avisverifies_secretKey', 'string', '');

        /* Facebook Graph API credentials */
        $this->add_newItem('facebook_pageId', 'string', '');
        $this->add_newItem('facebook_accessToken', 'string', '');

        /* Generic initialisation */
        parent::init_config();
    }

    /* Mark: Specific data methods */

    /**
     * Return sources metadata list.
     * @return array
     */
    public function get_sourceList() {
        return array(
            'Google' => array(
                'Title'         => 'Google',
                'URL'           => 'https://www.google.com/maps',
                'PortalURL'     => 'https://console.cloud.google.com/apis/library/places-backend.googleapis.com',
                'Fields'        => array('google_apiKey', 'google_placeId'),
            ),
            'TripAdvisor' => array(
                'Title'         => 'TripAdvisor',
                'URL'           => 'https://www.tripadvisor.com',
                'PortalURL'     => 'https://www.tripadvisor.com/developers',
                'Fields'        => array('tripadvisor_apiKey', 'tripadvisor_locationId'),
            ),
            'TrustPilot' => array(
                'Title'         => 'Trustpilot',
                'URL'           => 'https://www.trustpilot.com',
                'PortalURL'     => 'https://developers.trustpilot.com/',
                'Fields'        => array('trustpilot_apiKey', 'trustpilot_businessUnitId'),
            ),
            'Yelp' => array(
                'Title'         => 'Yelp',
                'URL'           => 'https://www.yelp.com',
                'PortalURL'     => 'https://www.yelp.com/developers/v3/manage_app',
                'Fields'        => array('yelp_apiKey', 'yelp_businessId'),
            ),
            'AvisVerifies' => array(
                'Title'         => 'Avis Vérifiés (Skeepers)',
                'URL'           => 'https://www.avis-verifies.com',
                'PortalURL'     => 'https://www.avis-verifies.com/',
                'Fields'        => array('avisverifies_websiteId', 'avisverifies_secretKey'),
            ),
            'Facebook' => array(
                'Title'         => 'Facebook',
                'URL'           => 'https://www.facebook.com',
                'PortalURL'     => 'https://developers.facebook.com/',
                'Fields'        => array('facebook_pageId', 'facebook_accessToken'),
            ),
        );
    }

    /**
     * Return source title list for select input.
     * @return array
     */
    public function get_sourceTitleList() {
        $result = array();
        foreach ($this->get_sourceList() as $id => $source)
            $result[$id] = $source['Title'];
        return $result;
    }

    /**
     * Return active source title.
     * @return string
     */
    public function get_sourceTitle() {
        $list = $this->get_sourceList();
        if (isset($list[$this->vars['source']]))
            return $list[$this->vars['source']]['Title'];
        return '';
    }

    /**
     * Return style source value list.
     * @return array
     */
    public function get_styleSourceList() {
        return array(
            'plugin'    => $this->get_translation('stylesource_plugin'),
            'theme'     => $this->get_translation('stylesource_theme'),
        );
    }

    /**
     * Return style source value title.
     * @return string
     */
    public function get_styleSourceTitle() {
        $list = $this->get_styleSourceList();
        return isset($list[$this->vars['styleSource']]) ? $list[$this->vars['styleSource']] : '';
    }

    /**
     * Return layout value list.
     * @return array
     */
    public function get_layoutList() {
        return array(
            'grid'  => $this->get_translation('layout_grid'),
            'list'  => $this->get_translation('layout_list'),
            'badge' => $this->get_translation('layout_badge'),
        );
    }

    /**
     * Return layout value title.
     * @return string
     */
    public function get_layoutTitle() {
        $list = $this->get_layoutList();
        return isset($list[$this->vars['layout']]) ? $list[$this->vars['layout']] : '';
    }

    /**
     * Return showSummary value list.
     * @return array
     */
    public function get_showSummaryList() {
        global $camyks;
        return array(
            1 => $camyks->get_translation('yes'),
            0 => $camyks->get_translation('no'),
        );
    }

    /**
     * Return showSummary value title.
     * @return string
     */
    public function get_showSummaryTitle() {
        $list = $this->get_showSummaryList();
        return isset($list[$this->vars['showSummary']]) ? $list[$this->vars['showSummary']] : '';
    }

    /**
     * Return minimum rating value list.
     * @return array
     */
    public function get_minRatingList() {
        return array(
            1 => $this->get_translation('minrating_stars', 1),
            2 => $this->get_translation('minrating_stars', 2),
            3 => $this->get_translation('minrating_stars', 3),
            4 => $this->get_translation('minrating_stars', 4),
            5 => $this->get_translation('minrating_stars', 5),
        );
    }

    /**
     * Return minimum rating value title.
     * @return string
     */
    public function get_minRatingTitle() {
        $list = $this->get_minRatingList();
        return isset($list[$this->vars['minRating']]) ? $list[$this->vars['minRating']] : '';
    }
}
?>
