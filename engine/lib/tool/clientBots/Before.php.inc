<?php
/**
 * @brief Some bots to be tested before as client bots specific methods
 * @details Engine / Bot Library
 * @file engine/lib/tool/clientBots/Before.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.1
 * @date Creation: Feb 2020
 * @date Modification: Dec 2020
 * @copyright 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return given known web before bot list.
 * @return array
 * @private
 */
function _client_getKnownBeforeBots() {
    $knownBots = array();

    /* Apple using a bad user agent : Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_1) AppleWebKit/601.2.4 (KHTML, like Gecko) Version/9.0.1 Safari/601.2.4 facebookexternalhit/1.1 Facebot Twitterbot/1.0 */
    $knownBots['version/9.0.1 safari/601.2.4 facebookexternalhit/1.1 facebot twi'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Apple iMessages bot',
        'tool_url'          => '',
        'engine_title'      => 'Apple',
        'engine_url'        => 'http://www.apple.com',
    );

    /* kakaotalk-scrap, a bot before facebook external hit */
    $knownBots['kakaotalk-scrap'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'kakaotalk-scrap',
        'bot_url'           => 'https://devtalk.kakao.com/t/scrap/33984',
        'engine_title'      => 'Kakao',
        'engine_url'        => 'http://www.kakaocorp.com',
    );

    /* Return bot list */
    return $knownBots;
}
?>
