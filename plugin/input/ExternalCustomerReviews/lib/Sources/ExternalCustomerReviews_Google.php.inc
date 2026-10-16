<?php
/**
 * @brief ExternalCustomerReviews input, Google Places service connector.
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
 * ExternalCustomerReviews_Google class.
 */
final class ExternalCustomerReviews_Google extends ExternalCustomerReviewsSource {
    /**
     * Execute Google Places reviews retrieval.
     * @param array $params
     * @return mixed
     */
    public function execute($params) {
        /* Check required credentials */
        if (empty($params['google_apiKey']) or empty($params['google_placeId']))
            return false;

        $apiKey = trim($params['google_apiKey']);
        $placeId = trim($params['google_placeId']);
        $lang = !empty($params['language']) ? $params['language'] : 'fr';

        /* Try Google Places API (New v1) first */
        $result = $this->execute_placesV1($apiKey, $placeId, $lang);
        if ($result !== false)
            return $result;

        /* Fallback to Google Places API (Legacy) */
        return $this->execute_placesLegacy($apiKey, $placeId, $lang);
    }

    /**
     * Query Google Places API (New v1).
     * @param string $apiKey
     * @param string $placeId
     * @param string $lang
     * @return mixed
     */
    private function execute_placesV1($apiKey, $placeId, $lang) {
        $url = 'https://places.googleapis.com/v1/places/'.urlencode($placeId).'?languageCode='.urlencode($lang);
        $headers = array(
            'X-Goog-Api-Key'    => $apiKey,
            'X-Goog-FieldMask'  => 'displayName,rating,userRatingCount,googleMapsUri,reviews',
        );

        $data = $this->request_json($url, $headers);
        if ($data === false or isset($data['error']))
            return false;

        $reviews = array();
        if (isset($data['reviews']) and is_array($data['reviews'])) {
            foreach ($data['reviews'] as $item) {
                $timestamp = isset($item['publishTime']) ? (int)strtotime($item['publishTime']) : 0;
                $reviews[] = $this->build_reviewItem(array(
                    'id'            => isset($item['name']) ? $item['name'] : '',
                    'authorName'    => isset($item['authorAttribution']['displayName']) ? $item['authorAttribution']['displayName'] : '',
                    'authorAvatar'  => isset($item['authorAttribution']['photoUri']) ? $item['authorAttribution']['photoUri'] : '',
                    'authorURL'     => isset($item['authorAttribution']['uri']) ? $item['authorAttribution']['uri'] : '',
                    'rating'        => isset($item['rating']) ? (float)$item['rating'] : 5.0,
                    'date'          => $timestamp,
                    'dateText'      => isset($item['relativePublishTimeDescription']) ? $item['relativePublishTimeDescription'] : '',
                    'title'         => '',
                    'text'          => isset($item['text']['text']) ? $item['text']['text'] : '',
                    'language'      => isset($item['text']['languageCode']) ? $item['text']['languageCode'] : $lang,
                    'reviewURL'     => isset($item['googleMapsUri']) ? $item['googleMapsUri'] : '',
                ));
            }
        }

        return $this->build_result('Google', 'Google', array(
            'placeName'     => isset($data['displayName']['text']) ? $data['displayName']['text'] : '',
            'placeURL'      => isset($data['googleMapsUri']) ? $data['googleMapsUri'] : '',
            'rating'        => isset($data['rating']) ? (float)$data['rating'] : 0.0,
            'maxRating'     => 5,
            'totalReviews'  => isset($data['userRatingCount']) ? (int)$data['userRatingCount'] : count($reviews),
            'reviews'       => $reviews,
        ));
    }

    /**
     * Query Google Places API (Legacy Details endpoint).
     * @param string $apiKey
     * @param string $placeId
     * @param string $lang
     * @return mixed
     */
    private function execute_placesLegacy($apiKey, $placeId, $lang) {
        $url = 'https://maps.googleapis.com/maps/api/place/details/json'
            .'?place_id='.urlencode($placeId)
            .'&fields=name,rating,user_ratings_total,url,reviews'
            .'&language='.urlencode($lang)
            .'&key='.urlencode($apiKey);

        $data = $this->request_json($url);
        if ($data === false or !isset($data['status']) or $data['status'] !== 'OK' or !isset($data['result']))
            return false;

        $place = $data['result'];
        $reviews = array();
        if (isset($place['reviews']) and is_array($place['reviews'])) {
            foreach ($place['reviews'] as $item) {
                $reviews[] = $this->build_reviewItem(array(
                    'id'            => isset($item['time']) ? (string)$item['time'] : '',
                    'authorName'    => isset($item['author_name']) ? $item['author_name'] : '',
                    'authorAvatar'  => isset($item['profile_photo_url']) ? $item['profile_photo_url'] : '',
                    'authorURL'     => isset($item['author_url']) ? $item['author_url'] : '',
                    'rating'        => isset($item['rating']) ? (float)$item['rating'] : 5.0,
                    'date'          => isset($item['time']) ? (int)$item['time'] : 0,
                    'dateText'      => isset($item['relative_time_description']) ? $item['relative_time_description'] : '',
                    'title'         => '',
                    'text'          => isset($item['text']) ? $item['text'] : '',
                    'language'      => isset($item['language']) ? $item['language'] : $lang,
                    'reviewURL'     => isset($item['author_url']) ? $item['author_url'] : '',
                ));
            }
        }

        return $this->build_result('Google', 'Google', array(
            'placeName'     => isset($place['name']) ? $place['name'] : '',
            'placeURL'      => isset($place['url']) ? $place['url'] : '',
            'rating'        => isset($place['rating']) ? (float)$place['rating'] : 0.0,
            'maxRating'     => 5,
            'totalReviews'  => isset($place['user_ratings_total']) ? (int)$place['user_ratings_total'] : count($reviews),
            'reviews'       => $reviews,
        ));
    }
}
?>
