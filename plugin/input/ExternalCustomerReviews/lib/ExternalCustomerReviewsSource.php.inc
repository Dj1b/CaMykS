<?php
/**
 * @brief ExternalCustomerReviews input, abstract source base class.
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
 * ExternalCustomerReviewsSource abstract class.
 */
abstract class ExternalCustomerReviewsSource {
    /**
     * Execute reviews retrieval from external API.
     * @param array $params
     * @return mixed
     */
    abstract public function execute($params);

    /**
     * Perform HTTP GET request and decode JSON response.
     * @param string $url
     * @param array $headers
     * @param integer $timeout
     * @return mixed
     */
    protected function request_json($url, $headers=array(), $timeout=15) {
        /* Build default headers */
        $defaultHeaders = array(
            'Accept' => 'application/json',
        );
        $headers = array_merge($defaultHeaders, $headers);

        /* Format headers as string for http_getContents compatibility */
        $headerLines = array();
        foreach ($headers as $name => $value) {
            $headerLines[] = $name.': '.$value;
        }
        $headerString = implode("\r\n", $headerLines)."\r\n";

        /* Execute HTTP request */
        $result = http_getContents(array(
            'url'       => $url,
            'method'    => 'GET',
            'timeout'   => $timeout,
            'headers'   => $headerString,
        ));

        /* Check response content */
        if ($result === false or strlen(trim($result)) == 0)
            return false;

        /* Decode JSON */
        $data = json_decode($result, true);
        if (json_last_error() !== JSON_ERROR_NONE or !is_array($data))
            return false;

        return $data;
    }

    /**
     * Return standardized result structure.
     * @param string $source
     * @param string $sourceTitle
     * @param array $data
     * @return array
     */
    protected function build_result($source, $sourceTitle, $data=array()) {
        return array_merge(array(
            'source'        => $source,
            'sourceTitle'   => $sourceTitle,
            'placeName'     => '',
            'placeURL'      => '',
            'rating'        => 0.0,
            'maxRating'     => 5,
            'totalReviews'  => 0,
            'reviews'       => array(),
        ), $data);
    }

    /**
     * Return standardized review item structure.
     * @param array $review
     * @return array
     */
    protected function build_reviewItem($review=array()) {
        return array_merge(array(
            'id'            => '',
            'authorName'    => '',
            'authorAvatar'  => '',
            'authorURL'     => '',
            'rating'        => 5.0,
            'date'          => 0,
            'dateText'      => '',
            'title'         => '',
            'text'          => '',
            'language'      => '',
            'reviewURL'     => '',
        ), $review);
    }
}
?>
