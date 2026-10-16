<?php
/**
 * @brief ExternalCustomerReviews input, Avis Verifies (Skeepers) service connector.
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
 * ExternalCustomerReviews_AvisVerifies class.
 */
final class ExternalCustomerReviews_AvisVerifies extends ExternalCustomerReviewsSource {
    /**
     * Execute Avis Verifies reviews retrieval.
     * @param array $params
     * @return mixed
     */
    public function execute($params) {
        /* Check required credentials */
        if (empty($params['avisverifies_websiteId']))
            return false;

        $websiteId = trim($params['avisverifies_websiteId']);
        $secretKey = isset($params['avisverifies_secretKey']) ? trim($params['avisverifies_secretKey']) : '';
        $lang = !empty($params['language']) ? $params['language'] : 'fr';

        /* Build folder shard from first 3 chars of websiteId (standard NetReviews / Skeepers JSON feed structure) */
        $cleanId = str_replace('-', '', $websiteId);
        $shard = implode('/', str_split(substr($cleanId, 0, 3)));

        /* Try Skeepers / Avis Verifies JSON merchant certificate & reviews endpoints */
        $headers = array();
        if ($secretKey !== '') {
            $headers['Authorization'] = 'Bearer '.$secretKey;
            $headers['X-Api-Key'] = $secretKey;
        }

        $statsURL = 'https://cl.avis-verifies.com/'.$lang.'/cache/'.$shard.'/'.$websiteId.'/AWS/'.$websiteId.'_infosite.json';
        $reviewsURL = 'https://cl.avis-verifies.com/'.$lang.'/cache/'.$shard.'/'.$websiteId.'/AWS/'.$websiteId.'_reviews.json';

        $statsData = $this->request_json($statsURL, $headers);
        $reviewsData = $this->request_json($reviewsURL, $headers);

        if ($statsData === false and $reviewsData === false)
            return false;

        $reviews = array();
        $rawList = array();
        if (is_array($reviewsData)) {
            if (isset($reviewsData['reviews']) and is_array($reviewsData['reviews']))
                $rawList = $reviewsData['reviews'];
            else
                $rawList = $reviewsData;
        }

        foreach ($rawList as $item) {
            if (!is_array($item))
                continue;

            $author = '';
            if (isset($item['firstname']) or isset($item['lastname']))
                $author = trim((isset($item['firstname']) ? $item['firstname'] : '').' '.(isset($item['lastname']) ? substr($item['lastname'], 0, 1).'.' : ''));
            elseif (isset($item['author']))
                $author = $item['author'];

            $dateStr = isset($item['publish_date']) ? $item['publish_date'] : (isset($item['review_date']) ? $item['review_date'] : '');
            $timestamp = ($dateStr !== '') ? (int)strtotime($dateStr) : 0;

            $reviews[] = $this->build_reviewItem(array(
                'id'            => isset($item['id_review']) ? (string)$item['id_review'] : '',
                'authorName'    => $author,
                'authorAvatar'  => '',
                'authorURL'     => '',
                'rating'        => isset($item['rate']) ? (float)$item['rate'] : (isset($item['rating']) ? (float)$item['rating'] : 5.0),
                'date'          => $timestamp,
                'dateText'      => '',
                'title'         => '',
                'text'          => isset($item['review']) ? $item['review'] : (isset($item['text']) ? $item['text'] : ''),
                'language'      => $lang,
                'reviewURL'     => '',
            ));
        }

        $rating = 0.0;
        $totalReviews = count($reviews);
        $placeName = '';
        $placeURL = '';

        if (is_array($statsData)) {
            if (isset($statsData['rate']))
                $rating = (float)$statsData['rate'];
            elseif (isset($statsData['rating']))
                $rating = (float)$statsData['rating'];

            if (isset($statsData['nb_reviews']))
                $totalReviews = (int)$statsData['nb_reviews'];
            elseif (isset($statsData['totalReviews']))
                $totalReviews = (int)$statsData['totalReviews'];

            if (isset($statsData['website_name']))
                $placeName = $statsData['website_name'];

            if (isset($statsData['url_certificat']))
                $placeURL = $statsData['url_certificat'];
        }

        return $this->build_result('AvisVerifies', 'Avis Vérifiés', array(
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
