<?php
/**
 * @brief ExternalCustomerReviews input, Facebook Graph API service connector.
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
 * ExternalCustomerReviews_Facebook class.
 */
final class ExternalCustomerReviews_Facebook extends ExternalCustomerReviewsSource {
    /**
     * Execute Facebook Page Ratings retrieval via Graph API.
     * @param array $params
     * @return mixed
     */
    public function execute($params) {
        /* Check required credentials */
        if (empty($params['facebook_pageId']) or empty($params['facebook_accessToken']))
            return false;

        $pageId = trim($params['facebook_pageId']);
        $accessToken = trim($params['facebook_accessToken']);
        $lang = !empty($params['language']) ? $params['language'] : 'fr';

        $fields = 'name,overall_star_rating,rating_count,link,ratings{reviewer,rating,recommendation_type,review_text,created_time}';
        $url = 'https://graph.facebook.com/v19.0/'.urlencode($pageId)
            .'?fields='.urlencode($fields)
            .'&access_token='.urlencode($accessToken);

        $data = $this->request_json($url);
        if ($data === false or isset($data['error']))
            return false;

        $reviews = array();
        if (isset($data['ratings']['data']) and is_array($data['ratings']['data'])) {
            foreach ($data['ratings']['data'] as $item) {
                /* Compute star rating (Facebook uses either explicit rating 1-5 or recommendation_type positive/negative) */
                $itemRating = 5.0;
                if (isset($item['rating']))
                    $itemRating = (float)$item['rating'];
                elseif (isset($item['recommendation_type']) and $item['recommendation_type'] === 'negative')
                    $itemRating = 1.0;

                $timestamp = isset($item['created_time']) ? (int)strtotime($item['created_time']) : 0;

                $reviews[] = $this->build_reviewItem(array(
                    'id'            => $timestamp > 0 ? (string)$timestamp : '',
                    'authorName'    => isset($item['reviewer']['name']) ? $item['reviewer']['name'] : '',
                    'authorAvatar'  => '',
                    'authorURL'     => '',
                    'rating'        => $itemRating,
                    'date'          => $timestamp,
                    'dateText'      => '',
                    'title'         => '',
                    'text'          => isset($item['review_text']) ? $item['review_text'] : '',
                    'language'      => $lang,
                    'reviewURL'     => isset($data['link']) ? $data['link'].'reviews' : '',
                ));
            }
        }

        return $this->build_result('Facebook', 'Facebook', array(
            'placeName'     => isset($data['name']) ? $data['name'] : '',
            'placeURL'      => isset($data['link']) ? $data['link'] : 'https://www.facebook.com/'.$pageId,
            'rating'        => isset($data['overall_star_rating']) ? (float)$data['overall_star_rating'] : 0.0,
            'maxRating'     => 5,
            'totalReviews'  => isset($data['rating_count']) ? (int)$data['rating_count'] : count($reviews),
            'reviews'       => $reviews,
        ));
    }
}
?>
