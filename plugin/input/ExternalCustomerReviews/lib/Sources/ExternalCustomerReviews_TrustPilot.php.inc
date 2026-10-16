<?php
/**
 * @brief ExternalCustomerReviews input, Trustpilot Public API service connector.
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
 * ExternalCustomerReviews_TrustPilot class.
 */
final class ExternalCustomerReviews_TrustPilot extends ExternalCustomerReviewsSource {
    /**
     * Execute Trustpilot reviews retrieval.
     * @param array $params
     * @return mixed
     */
    public function execute($params) {
        /* Check required credentials */
        if (empty($params['trustpilot_apiKey']) or empty($params['trustpilot_businessUnitId']))
            return false;

        $apiKey = trim($params['trustpilot_apiKey']);
        $businessUnitId = trim($params['trustpilot_businessUnitId']);
        $lang = !empty($params['language']) ? $params['language'] : 'fr';

        $headers = array(
            'apikey' => $apiKey,
        );

        /* Fetch Business Unit profile */
        $unitURL = 'https://api.trustpilot.com/v1/business-units/'.urlencode($businessUnitId);
        $unitData = $this->request_json($unitURL, $headers);

        /* Fetch Business Unit service reviews */
        $reviewsURL = 'https://api.trustpilot.com/v1/business-units/'.urlencode($businessUnitId).'/reviews'
            .'?perPage=20&language='.urlencode($lang);
        $reviewsData = $this->request_json($reviewsURL, $headers);

        if ($unitData === false and $reviewsData === false)
            return false;

        /* Parse reviews */
        $reviews = array();
        if (is_array($reviewsData) and isset($reviewsData['reviews']) and is_array($reviewsData['reviews'])) {
            foreach ($reviewsData['reviews'] as $item) {
                $timestamp = isset($item['createdAt']) ? (int)strtotime($item['createdAt']) : 0;
                $reviewId = isset($item['id']) ? (string)$item['id'] : '';
                $reviews[] = $this->build_reviewItem(array(
                    'id'            => $reviewId,
                    'authorName'    => isset($item['consumer']['displayName']) ? $item['consumer']['displayName'] : '',
                    'authorAvatar'  => '',
                    'authorURL'     => '',
                    'rating'        => isset($item['stars']) ? (float)$item['stars'] : 5.0,
                    'date'          => $timestamp,
                    'dateText'      => '',
                    'title'         => isset($item['title']) ? $item['title'] : '',
                    'text'          => isset($item['text']) ? $item['text'] : '',
                    'language'      => isset($item['language']) ? $item['language'] : $lang,
                    'reviewURL'     => $reviewId !== '' ? 'https://www.trustpilot.com/reviews/'.$reviewId : '',
                ));
            }
        }

        /* Extract overall profile details */
        $placeName = '';
        $placeURL = '';
        $rating = 0.0;
        $totalReviews = count($reviews);

        if (is_array($unitData)) {
            if (isset($unitData['displayName']))
                $placeName = $unitData['displayName'];
            elseif (isset($unitData['name']['identifying']))
                $placeName = $unitData['name']['identifying'];

            if (isset($unitData['name']['identifying']))
                $placeURL = 'https://www.trustpilot.com/review/'.$unitData['name']['identifying'];

            if (isset($unitData['score']['trustScore']))
                $rating = (float)$unitData['score']['trustScore'];
            elseif (isset($unitData['score']['stars']))
                $rating = (float)$unitData['score']['stars'];

            if (isset($unitData['numberOfReviews']['total']))
                $totalReviews = (int)$unitData['numberOfReviews']['total'];
        }

        return $this->build_result('TrustPilot', 'Trustpilot', array(
            'placeName'     => $placeName,
            'placeURL'      => $placeURL,
            'rating'        => $rating,
            'maxRating'     => 5,
            'totalReviews'  => $totalReviews,
            'reviews'       => $reviews,
        ));
    }
}
?>
