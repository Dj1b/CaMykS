<?php
/**
 * @brief ExternalCustomerReviews input, Yelp Fusion API service connector.
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
 * ExternalCustomerReviews_Yelp class.
 */
final class ExternalCustomerReviews_Yelp extends ExternalCustomerReviewsSource {
    /**
     * Execute Yelp Fusion API reviews retrieval.
     * @param array $params
     * @return mixed
     */
    public function execute($params) {
        /* Check required credentials */
        if (empty($params['yelp_apiKey']) or empty($params['yelp_businessId']))
            return false;

        $apiKey = trim($params['yelp_apiKey']);
        $businessId = trim($params['yelp_businessId']);
        $lang = !empty($params['language']) ? $params['language'] : 'fr';
        $locale = ($lang == 'fr') ? 'fr_FR' : 'en_US';

        $headers = array(
            'Authorization' => 'Bearer '.$apiKey,
        );

        /* Fetch business details */
        $businessURL = 'https://api.yelp.com/v3/businesses/'.urlencode($businessId).'?locale='.urlencode($locale);
        $businessData = $this->request_json($businessURL, $headers);

        /* Fetch business reviews */
        $reviewsURL = 'https://api.yelp.com/v3/businesses/'.urlencode($businessId).'/reviews?locale='.urlencode($locale);
        $reviewsData = $this->request_json($reviewsURL, $headers);

        if ($businessData === false and $reviewsData === false)
            return false;
        if (isset($businessData['error']) and isset($reviewsData['error']))
            return false;

        /* Parse reviews */
        $reviews = array();
        if (is_array($reviewsData) and isset($reviewsData['reviews']) and is_array($reviewsData['reviews'])) {
            foreach ($reviewsData['reviews'] as $item) {
                $timestamp = isset($item['time_created']) ? (int)strtotime($item['time_created']) : 0;
                $reviews[] = $this->build_reviewItem(array(
                    'id'            => isset($item['id']) ? (string)$item['id'] : '',
                    'authorName'    => isset($item['user']['name']) ? $item['user']['name'] : '',
                    'authorAvatar'  => isset($item['user']['image_url']) ? $item['user']['image_url'] : '',
                    'authorURL'     => isset($item['user']['profile_url']) ? $item['user']['profile_url'] : '',
                    'rating'        => isset($item['rating']) ? (float)$item['rating'] : 5.0,
                    'date'          => $timestamp,
                    'dateText'      => '',
                    'title'         => '',
                    'text'          => isset($item['text']) ? $item['text'] : '',
                    'language'      => $lang,
                    'reviewURL'     => isset($item['url']) ? $item['url'] : '',
                ));
            }
        }

        $totalReviews = count($reviews);
        if (is_array($businessData) and isset($businessData['review_count']))
            $totalReviews = (int)$businessData['review_count'];
        elseif (is_array($reviewsData) and isset($reviewsData['total']))
            $totalReviews = (int)$reviewsData['total'];

        return $this->build_result('Yelp', 'Yelp', array(
            'placeName'     => (is_array($businessData) and isset($businessData['name'])) ? $businessData['name'] : '',
            'placeURL'      => (is_array($businessData) and isset($businessData['url'])) ? $businessData['url'] : '',
            'rating'        => (is_array($businessData) and isset($businessData['rating'])) ? (float)$businessData['rating'] : 0.0,
            'maxRating'     => 5,
            'totalReviews'  => $totalReviews,
            'reviews'       => $reviews,
        ));
    }
}
?>
