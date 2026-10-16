<?php
/**
 * @brief ExternalCustomerReviews input, TripAdvisor Content API service connector.
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
 * ExternalCustomerReviews_TripAdvisor class.
 */
final class ExternalCustomerReviews_TripAdvisor extends ExternalCustomerReviewsSource {
    /**
     * Execute TripAdvisor reviews retrieval.
     * @param array $params
     * @return mixed
     */
    public function execute($params) {
        /* Check required credentials */
        if (empty($params['tripadvisor_apiKey']) or empty($params['tripadvisor_locationId']))
            return false;

        $apiKey = trim($params['tripadvisor_apiKey']);
        $locationId = trim($params['tripadvisor_locationId']);
        $lang = !empty($params['language']) ? $params['language'] : 'fr';

        /* Fetch location details */
        $detailsURL = 'https://api.content.tripadvisor.com/api/v1/location/'.urlencode($locationId).'/details'
            .'?key='.urlencode($apiKey)
            .'&language='.urlencode($lang);
        $details = $this->request_json($detailsURL);

        /* Fetch location reviews */
        $reviewsURL = 'https://api.content.tripadvisor.com/api/v1/location/'.urlencode($locationId).'/reviews'
            .'?key='.urlencode($apiKey)
            .'&language='.urlencode($lang);
        $reviewsData = $this->request_json($reviewsURL);

        if ($details === false and $reviewsData === false)
            return false;
        if (isset($details['error']) and isset($reviewsData['error']))
            return false;

        /* Parse reviews */
        $reviews = array();
        if (is_array($reviewsData) and isset($reviewsData['data']) and is_array($reviewsData['data'])) {
            foreach ($reviewsData['data'] as $item) {
                $timestamp = isset($item['published_date']) ? (int)strtotime($item['published_date']) : 0;
                $avatar = '';
                if (isset($item['user']['avatar']['small']))
                    $avatar = $item['user']['avatar']['small'];
                elseif (isset($item['user']['avatar']['thumbnail']))
                    $avatar = $item['user']['avatar']['thumbnail'];

                $reviews[] = $this->build_reviewItem(array(
                    'id'            => isset($item['id']) ? (string)$item['id'] : '',
                    'authorName'    => isset($item['user']['username']) ? $item['user']['username'] : '',
                    'authorAvatar'  => $avatar,
                    'authorURL'     => '',
                    'rating'        => isset($item['rating']) ? (float)$item['rating'] : 5.0,
                    'date'          => $timestamp,
                    'dateText'      => '',
                    'title'         => isset($item['title']) ? $item['title'] : '',
                    'text'          => isset($item['text']) ? $item['text'] : '',
                    'language'      => isset($item['lang']) ? $item['lang'] : $lang,
                    'reviewURL'     => isset($item['url']) ? $item['url'] : '',
                ));
            }
        }

        return $this->build_result('TripAdvisor', 'TripAdvisor', array(
            'placeName'     => (is_array($details) and isset($details['name'])) ? $details['name'] : '',
            'placeURL'      => (is_array($details) and isset($details['web_url'])) ? $details['web_url'] : '',
            'rating'        => (is_array($details) and isset($details['rating'])) ? (float)$details['rating'] : 0.0,
            'maxRating'     => 5,
            'totalReviews'  => (is_array($details) and isset($details['num_reviews'])) ? (int)$details['num_reviews'] : count($reviews),
            'reviews'       => $reviews,
        ));
    }
}
?>
