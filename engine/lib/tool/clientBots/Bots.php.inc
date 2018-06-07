<?php
/**
 * @brief Bots as client bots specific methods
 * @details Engine / Bot Library
 * @file engine/lib/tool/clientBots/Bots.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: May 2018
 * @date Modification: Jun 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return given known web bot list.
 * @return array
 * @private
 */
function _client_getKnownBots() {
    $knownBots = array();

    /* Ideogram Design bot */
    $knownBots['idpunchbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'IDPunchBot',
        'bot_url'           => 'http://www.ideogram-design.fr/Punch_Bot.html',
        'engine_title'      => 'Ideogram Design',
        'engine_url'        => 'http://www.ideogram-design.fr/',
    );

    /* import.io crawler bot (to be inserted before GoogleBot, use GoogleBot in user agent)    */
    $knownBots['googlebot/2.1; +http://import.io'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'import.io crawler',
        'bot_url'           => 'http://support.import.io/knowledgebase/articles/265494-crawler-faq',
        'engine_title'      => 'import.io',
        'engine_url'        => 'http://import.io',
    );

    /* Dictanova crawler bot (to be inserted before GoogleBot, use GoogleBot in user agent) / to complete */
    $knownBots['googlebot/1.0 (dictanova'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Dictanova crawler',
        'bot_url'           => '',
        'engine_title'      => 'Dictanova',
        'engine_url'        => 'http://www.dictanova.com/',
    );
    $knownBots['googlebot/1.0 (googlebot; http://www.google.com/bot.html; crawler at dictanova dot com)'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Dictanova crawler',
        'bot_url'           => '',
        'engine_title'      => 'Dictanova',
        'engine_url'        => 'http://www.dictanova.com/',
    );

    /* googlebot_poolmer (to be inserted before GoogleBot, use GoogleBot in user agent) / to complete */
    $knownBots['googlebot_poolmer'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'poolmer',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* WebHistoryBot (to be inserted before GoogleBot, use GoogleBot in user agent) / to complete */
    $knownBots['webhistorybot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'WebHistoryBot',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* startmebot (to be inserted before GoogleBot, use GoogleBot in user agent) / to complete */
    $knownBots['googlebot/2.1; startmebot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'startmebot',
        'bot_url'           => 'https://start.me/bot',
        'engine_title'      => 'start.me',
        'engine_url'        => 'https://start.me',
    );

    /* Yahoo mobile bot : Yahoo! Slurp */
    $knownBots['mobile (compatible; yahoo! slurp'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'handheld',
        'bot_title'         => 'Yahoo! Slurp Mobile',
        'bot_url'           => 'http://help.yahoo.com/help/us/ysearch/slurp',
        'engine_title'      => 'Yahoo!',
        'engine_url'        => 'http://www.yahoo.com',
    );

    /* Yahoo bot : Yahoo! Slurp */
    $knownBots['yahoo! slurp'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Yahoo! Slurp',
        'bot_url'           => 'http://help.yahoo.com/help/us/ysearch/slurp',
        'engine_title'      => 'Yahoo!',
        'engine_url'        => 'http://www.yahoo.com',
    );

    /* Yahoo bot : yahoo/Nutch */
    $knownBots['yahoo/nutch'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => '',
        'bot_url'           => '',
        'engine_title'      => 'Yahoo!',
        'engine_url'        => 'http://www.yahoo.com',
    );

    /* Google mobile bot : Googlebot-Mobile */
    $knownBots['safari/537.36 (compatible; googlebot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'handheld',
        'bot_title'         => 'Googlebot Mobile',
        'bot_url'           => 'http://www.google.com/bot.html',
        'engine_title'      => 'Google',
        'engine_url'        => 'http://www.google.com',
    );

    /* Google mobile bot : Googlebot-Mobile */
    $knownBots['safari/600.1.4 (compatible; googlebot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'handheld',
        'bot_title'         => 'Googlebot Mobile',
        'bot_url'           => 'http://www.google.com/bot.html',
        'engine_title'      => 'Google',
        'engine_url'        => 'http://www.google.com',
    );

    /* Google mobile bot : Googlebot-Mobile */
    $knownBots['safari/8536.25 (compatible; googlebot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'handheld',
        'bot_title'         => 'Googlebot Mobile',
        'bot_url'           => 'http://www.google.com/bot.html',
        'engine_title'      => 'Google',
        'engine_url'        => 'http://www.google.com',
    );

    /* Google mobile bot : Googlebot-Mobile */
    $knownBots['googlebot-mobile'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'handheld',
        'bot_title'         => 'Googlebot Mobile',
        'bot_url'           => 'http://www.google.com/bot.html',
        'engine_title'      => 'Google',
        'engine_url'        => 'http://www.google.com',
    );

    /* Google bot : Googlebot */
    $knownBots['googlebot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Googlebot',
        'bot_url'           => 'http://www.google.com/bot.html',
        'engine_title'      => 'Google',
        'engine_url'        => 'http://www.google.com',
    );

    /* Google bot : Google Favicon */
    $knownBots['google favicon'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Google favicon',
        'bot_url'           => 'http://www.google.com/bot.html',
        'engine_title'      => 'Google',
        'engine_url'        => 'http://www.google.com',
    );

    /* Google bot : Google Web Preview */
    $knownBots['google web preview'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Google Web Preview',
        'bot_url'           => 'http://www.google.com/bot.html',
        'engine_title'      => 'Google',
        'engine_url'        => 'http://www.google.com',
    );

    /* Google-Site-Verification */
    $knownBots['google-site-verification'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Google-Site-Verification',
        'bot_url'           => 'http://www.google.com/bot.html',
        'engine_title'      => 'Google',
        'engine_url'        => 'http://www.google.com',
    );

    /* Google Media Partners */
    $knownBots['mediapartners-google'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Google-MediaPartners',
        'bot_url'           => '',
        'engine_title'      => 'Google',
        'engine_url'        => 'http://www.google.com',
    );

    /* Google AdsBot */
    $knownBots['adsbot-google'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Google-AdsBot',
        'bot_url'           => 'http://www.google.com/adsbot.html',
        'engine_title'      => 'Google',
        'engine_url'        => 'http://www.google.com',
    );

    /* Apple bot : Applebot */
    $knownBots['applebot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Applebot',
        'bot_url'           => 'https://support.apple.com/en-us/HT204683',
        'engine_title'      => 'Apple',
        'engine_url'        => 'http://www.apple.com',
    );

    /* Voila bot : VoilaBot */
    $knownBots['voilabot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'VoilaBot',
        'bot_url'           => '',
        'engine_title'      => 'Voila',
        'engine_url'        => 'http://www.voila.com',
    );

    /* MSN Search bot : msnbot */
    $knownBots['msnbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'msnbot',
        'bot_url'           => 'http://search.msn.com/msnbot.htm',
        'engine_title'      => 'MSN Search',
        'engine_url'        => 'http://search.msn.com',
    );

    /* MSN Search bot : hidden behind fake user agent */
    $knownBots['msie 9.0; windows nt 6.1; trident/5.0;    trident/5.0)'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'msnbot',
        'bot_url'           => 'http://search.msn.com/msnbot.htm',
        'engine_title'      => 'MSN Search',
        'engine_url'        => 'http://search.msn.com',
    );

    /* MSN Search bot : hidden behind fake user agent */
    $knownBots['msie 9.0; windows nt 6.0; trident/5.0;    trident/5.0)'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'msnbot',
        'bot_url'           => 'http://search.msn.com/msnbot.htm',
        'engine_title'      => 'MSN Search',
        'engine_url'        => 'http://search.msn.com',
    );

    /* MS Bing mobile bot : bingbot */
    $knownBots['safari/9537.53 (compatible; bingbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'handheld',
        'bot_title'         => 'Bingbot Mobile',
        'bot_url'           => 'http://www.bing.com/bingbot.htm',
        'engine_title'      => 'bing',
        'engine_url'        => 'http://www.bing.com/',
    );

    /* MS Bing bot : bingbot */
    $knownBots['bingbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'bingbot',
        'bot_url'           => 'http://www.bing.com/bingbot.htm',
        'engine_title'      => 'bing',
        'engine_url'        => 'http://www.bing.com/',
    );

    /* MS Bing bot : BingPreview */
    $knownBots['bingpreview'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'BingPreview',
        'bot_url'           => 'http://www.bing.com/bingbot.htm',
        'engine_title'      => 'bing',
        'engine_url'        => 'http://www.bing.com/',
    );

    /* MS Bing bot : BingLocalSearch */
    $knownBots['binglocalsearch'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'BingLocalSearch',
        'bot_url'           => 'http://www.bing.com/bingbot.htm',
        'engine_title'      => 'bing',
        'engine_url'        => 'http://www.bing.com/',
    );

    /* MS Search 6.0 Robot    */
    $knownTools['ms search 6.0 robot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Microsoft Sharepoint Crawler',
        'bot_url'           => '',
        'engine_title'      => 'Microsoft',
        'engine_url'        => 'http://www.microsoft.com',
    );

    /* Facebook bot : facebot */
    $knownBots['facebot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'FaceBot',
        'bot_url'           => '',
        'engine_title'      => 'Facebook',
        'engine_url'        => 'http://www.facebook.com/',
    );

    /* Cuill search engine : Twiceler */
    $knownBots['cuill.com'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Twiceler',
        'bot_url'           => 'http://www.cuill.com/twiceler/robot.html',
        'engine_title'      => 'Cuill Inc.',
        'engine_url'        => 'http://www.cuill.com',
    );

    /* Exalead bot : Exabot */
    $knownBots['exabot.com'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Exabot',
        'bot_url'           => 'http://www.exabot.com/go/robot',
        'engine_title'      => 'Exalead',
        'engine_url'        => 'http://www.exalead.com');

    /* ExaleadCloudView bot : Exabot */
    $knownBots['exaleadcloudview'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'ExaleadCloudView',
        'bot_url'           => 'http://www.exabot.com/go/robot',
        'engine_title'      => 'Exalead',
        'engine_url'        => 'http://www.exalead.com',
    );
    
    /* Exabot-Thumbnails */
    $knownBots['exabot-thumbnails'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Exabot-Thumbnails',
        'bot_url'           => 'https://www.exalead.com/search/webmasterguide',
        'engine_title'      => 'Exalead',
        'engine_url'        => 'http://www.exalead.com',
    );
    
    /* Baidu mobile bot */
    $knownBots['mobile safari/10600.6.3 (compatible; baiduspider'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'handheld',
        'bot_title'         => 'Baiduspider',
        'bot_url'           => 'http://www.baidu.com/search/spider.htm',
        'engine_title'      => 'Baidu',
        'engine_url'        => 'http://www.baidu.com',
    );
    
    /* Baidu bot : Baiduspider */
    $knownBots['baiduspider'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Baiduspider',
        'bot_url'           => 'http://www.baidu.com/search/spider.htm',
        'engine_title'      => 'Baidu',
        'engine_url'        => 'http://www.baidu.com',
    );
    
    /* old baidu bot */
    $knownBots['baidu.com'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Baiduspider',
        'bot_url'           => 'http://www.baidu.com/search/spider.htm',
        'engine_title'      => 'Baidu',
        'engine_url'        => 'http://www.baidu.com',
    );
    
    /* Baidu bot : BaiduImagespider */
    $knownBots['baiduimagespider'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'BaiduImagespider',
        'bot_url'           => 'http://www.baidu.com/search/spider.htm',
        'engine_title'      => 'Baidu',
        'engine_url'        => 'http://www.baidu.com',
    );
    
    /* Gigablast bot : Gigabot */
    $knownBots['gigablast.com'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'GigaBot',
        'bot_url'           => 'http://www.gigablast.com/spider.html',
        'engine_title'      => 'Gigablast',
        'engine_url'        => 'http://www.gigablast.com',
    );
    
    /* Gigablast bot : Gigabot */
    $knownBots['gigabot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'GigaBot',
        'bot_url'           => 'http://www.gigablast.com/spider.html',
        'engine_title'      => 'Gigablast',
        'engine_url'        => 'http://www.gigablast.com',
    );
    
    /* GigablastOpensource : Gigabot */
    $knownBots['gigablastopensource'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'GigaBlast Open Source',
        'bot_url'           => 'http://www.gigablast.com/spider.html',
        'engine_title'      => 'Gigablast',
        'engine_url'        => 'http://www.gigablast.com',
    );
    
    /* GigablastOpensource : Gigabot */
    $knownBots['g-i-g-a-b-o-t'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'GigaBlast Open Source',
        'bot_url'           => 'http://www.gigablast.com/spider.html',
        'engine_title'      => 'Gigablast',
        'engine_url'        => 'http://www.gigablast.com',
    );
    
    /* Amfibi bot : Cabot/Nutch */
    $knownBots['amfibi.com'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Cabot/Nutch',
        'bot_url'           => 'http://www.amfibi.com/cabot/',
        'engine_title'      => 'Amfibi',
        'engine_url'        => 'http://www.amfibi.com',
    );
    
    /* Healthline bot : NimbleCrawler */
    $knownBots['healthline.com'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'NimbleCrawler',
        'bot_url'           => '',
        'engine_title'      => 'HealthLine',
        'engine_url'        => 'http://www.healthline.com',
    );
    
    /* Ask bot : Ask Jeeves/Teoma */
    $knownBots['ask.com'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Ask Jeeves/Teoma',
        'bot_url'           => 'http://about.ask.com/en/docs/about/webmasters.shtml',
        'engine_title'      => 'Ask.com',
        'engine_url'        => 'http://www.ask.com',
    );
    
    /* FAST bot : FAST Enterprise Crawler */
    $knownBots['fast.no'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'FAST Enterprise Crawler',
        'bot_url'           => '',
        'engine_title'      => 'Fast',
        'engine_url'        => 'http://www.fast.no',
    );
    
    /* entireweb bot : Seedy Spider */
    $knownBots['entireweb.com'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Speedy Spider',
        'bot_url'           => 'http://www.entireweb.com/about/search_tech/speedy_spider',
        'engine_title'      => 'Entire Web',
        'engine_url'        => 'http://www.entireweb.com',
    );
    
    /* Naver bot : Yeti */
    $knownBots['naver.com'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Yeti',
        'bot_url'           => 'http://help.naver.com/robots/',
        'engine_title'      => 'Naver (cn)',
        'engine_url'        => 'http://www.naver.com',
    );
    
    /* Naver bot : Yeti */
    $knownBots['naver.me'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Yeti',
        'bot_url'           => 'http://naver.me/bot',
        'engine_title'      => 'Naver (cn)',
        'engine_url'        => 'http://www.naver.com',
    );
    
    /* CommonCrawl bot : CCBot */
    $knownBots['commoncrawl.org'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'ccBot',
        'bot_url'           => 'http://www.commoncrawl.org/bot.html',
        'engine_title'      => 'CommonCrawl',
        'engine_url'        => 'http://www.commoncrawl.org',
    );
    
    /* Acoon bot : Acoon-Robot */
    $knownBots['acoon.de'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Acoon-Robot',
        'bot_url'           => 'http://www.acoon.de',
        'engine_title'      => 'Acoon',
        'engine_url'        => 'http://www.acoon.de',
    );
    
    /* Whois bot : SurveyBot */
    $knownBots['whois.sc'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'SurveyBot',
        'bot_url'           => 'http://www.whois.sc',
        'engine_title'      => 'Whois',
        'engine_url'        => 'http://www.whois.sc',
    );
    
    /* Wauuu bot : wauuu engine */
    $knownBots['wauuu.com'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'wauuu engine',
        'bot_url'           => 'http://www.wauuu.com',
        'engine_title'      => 'Wauuu',
        'engine_url'        => 'http://www.wauuu.com',
    );
    
    /* Searchme bot : Charlotte */
    $knownBots['searchme.com'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Charlotte',
        'bot_url'           => 'http://www.searchme.com/support/',
        'engine_title'      => 'Searchme',
        'engine_url'        => 'http://www.searchme.com',
    );
    
    /* WebAlta bot : WebAlta Crawler */
    $knownBots['webalta.net'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'WebAlta Crawler',
        'bot_url'           => 'http://www.webalta.net/ru/about_webmaster.html',
        'engine_title'      => 'WebAlta',
        'engine_url'        => 'http://www.webalta.net',
    );
    
    /* Gais bot : Gaisbot */
    $knownBots['gais.cs.ccu.edu.tw'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Gaisbot',
        'bot_url'           => 'http://gais.cs.ccu.edu.tw/robot.php',
        'engine_title'      => 'Global Area Information Servers',
        'engine_url'        => 'http://gais.cs.ccu.edu.tw',
    );
    
    /* ScoutJet bot */
    $knownBots['scoutjet.com'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'ScoutJet',
        'bot_url'           => 'http://www.scoutjet.com/',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* Discovery engine bot : discobot */
    $knownBots['discoveryengine.com'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'discobot',
        'bot_url'           => 'http://discoveryengine.com/discobot.html',
        'engine_title'      => 'Discovery Engine',
        'engine_url'        => 'http://discoveryengine.com',
    );
    
    /* Touche bot */
    $knownBots['touche.com.ve'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Touche',
        'bot_url'           => '',
        'engine_title'      => 'Touch&eacute;',
        'engine_url'        => 'http://www.touche.com.ve',
    );
    
    /* Morfeo bot : holmes */
    $knownBots['morfeo.centrum.cz'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'holmes',
        'bot_url'           => '',
        'engine_title'      => 'Morfeo',
        'engine_url'        => 'http://morfeo.centrum.cz',
    );
    
    /* Mail.ru bot */
    $knownBots['mail.ru'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => '',
        'bot_url'           => '',
        'engine_title'      => 'Mail.ru',
        'engine_url'        => 'http://www.mail.ru',
    );
    
    /* Rankiva bot : rankivabot */
    $knownBots['rankiva.com'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Rankivabot',
        'bot_url'           => 'http://www.rankiva.com/rankivabot/index.php',
        'engine_title'      => 'Rankiva',
        'engine_url'        => 'http://www.rankiva.com',
    );
    
    /* iearthworm bot */
    $knownBots['iearthworm'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'iearthworm',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* Alexa bot : ia_archiver */
    $knownBots['ia_archiver'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'ia_archiver',
        'bot_url'           => 'http://www.alexa.com/site/help/webmasters',
        'engine_title'      => 'Alexa',
        'engine_url'        => 'http://www.alexa.com',
    );
    
    /* Alexa site audit */
    $knownBots['alexa site audit'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'alexa site audit',
        'bot_url'           => 'http://www.alexa.com/site/help/webmasters',
        'engine_title'      => 'Alexa',
        'engine_url'        => 'http://www.alexa.com',
    );
    
    /* Mirago bot : Henri */
    $knownBots['mirago.co.uk'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Henri, the Mirago Robot',
        'bot_url'           => 'http://www.miragorobot.com',
        'engine_title'      => 'Mirago',
        'engine_url'        => 'http://www.mirago.co.uk',
    );
    
    /* Cote d'azur bot : SunIndexer */
    $knownBots['cote.azur.fr'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'SunIndexer',
        'bot_url'           => 'http://www.cote.azur.fr/SunIndexer.html',
        'engine_title'      => 'C&ocirc;te d\'Azur',
        'engine_url'        => 'http://www.cote.azur.fr',
    );
    
    /* MSR-ISRCCrawler */
    $knownBots['MSR-ISRCCrawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'MSR-ISRCCrawler',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* DeepIndex bot */
    $knownBots['deepindex'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => '',
        'bot_url'           => '',
        'engine_title'      => 'DeepIndex',
        'engine_url'        => 'http://www.deepindex.fr',
    );
    
    /* Powerset bot */
    $knownBots['powerset.com'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => '',
        'bot_url'           => '',
        'engine_title'      => 'Powerset',
        'engine_url'        => 'http://www.powerset.com',
    );
    
    /* Zippp bot */
    $knownBots['zippp.com'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'ZipppBot',
        'bot_url'           => '',
        'engine_title'      => 'Zippp',
        'engine_url'        => 'http://www.zippp.com',
    );
    
    /* insynchro.net bot */
    $knownBots['insynchro.net'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'SearchHub',
        'bot_url'           => '',
        'engine_title'      => 'insynchro',
        'engine_url'        => 'http://www.insynchro.net',
    );
    
    /* yandex bot */
    $knownBots['yandex'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Yandex',
        'bot_url'           => '',
        'engine_title'      => 'Yandex',
        'engine_url'        => 'http://www.yandex.ru',
    );
    
    /* feedoo bot */
    $knownBots['feedoo'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Feedoo7 Crawler',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* guruji bot */
    $knownBots['gurujibot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'GurujiBot',
        'bot_url'           => 'http://www.guruji.com/en/WebmasterFAQ.html',
        'engine_title'      => 'Guruji',
        'engine_url'        => 'http://www.guruji.com',
    );
    
    /* Sogou Spider bot */
    $knownBots['sogou'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Sogou Spider',
        'bot_url'           => 'http://www.sogou.com/docs/help/webmasters.htm',
        'engine_title'      => 'Sogou',
        'engine_url'        => 'http://www.sogou.com',
    );
    
    /* CamontSpider bot */
    $knownBots['camontspider'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'CamontSpider',
        'bot_url'           => 'http://epweb2.ph.bham.ac.uk/user/slater/camont/info.html',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* Chen-Li bot */
    $knownBots['chen li'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Chen Li/Nutch',
        'bot_url'           => 'http://chenli.com.cn',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* ICC-Crawler bot */
    $knownBots['icc-crawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'ICC-Crawler',
        'bot_url'           => 'http://kc.nict.go.jp/project1/crawl.html',
        'engine_title'      => 'Knowledge Clustered Group',
        'engine_url'        => '',
    );
    
    /* KIT webcrawler bot */
    $knownBots['kit webcrawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'KIT webcrawler',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* Linguee Bot */
    $knownBots['linguee bot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Linguee Bot',
        'bot_url'           => 'http://www.linguee.com/bot',
        'engine_title'      => 'Linguee',
        'engine_url'        => 'http://www.linguee.com',
    );
    
    /* MLBot Bot */
    $knownBots['mlbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'MLBot',
        'bot_url'           => 'http://www.metadatalabs.com/mlbot',
        'engine_title'      => 'metadata labs',
        'engine_url'        => 'http://www.metadatalabs.com',
    );
    
    /* DotBot */
    $knownBots['dotbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'DotBot',
        'bot_url'           => 'http://www.opensiteexplorer.org/dotbot',
        'engine_title'      => 'DotNetDotCom',
        'engine_url'        => 'http://www.dotnetdotcom.org',
    );
    
    /* KaloogaBot */
    $knownBots['kaloogabot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'KaloogaBot',
        'bot_url'           => 'http://www.kalooga.com/info.html?page=crawler',
        'engine_title'      => 'Kalooga',
        'engine_url'        => 'http://www.kalooga.com',
    );
    
    /* Majestic 12 Bot */
    $knownBots['mj12bot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'MJ12Bot',
        'bot_url'           => 'http://www.majestic12.co.uk/bot.php?+',
        'engine_title'      => 'Majestic 12',
        'engine_url'        => 'http://www.majestic12.co.uk/',
    );
    
    /* Netcraft Survey Agent */
    $knownBots['netcraftsurveyagent'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'NetcraftSurveyAgent',
        'bot_url'           => '',
        'engine_title'      => 'Netcraft',
        'engine_url'        => 'http://news.netcraft.com',
    );
    
    /* Netcraft Survey Agent */
    $knownBots['netcraft ssl server survey'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'NetcraftSurveyAgent',
        'bot_url'           => '',
        'engine_title'      => 'Netcraft',
        'engine_url'        => 'http://news.netcraft.com',
    );
    
    /* Pure search bot */
    $knownBots['purebot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'PureBot',
        'bot_url'           => '',
        'engine_title'      => 'Pure Search',
        'engine_url'        => 'http://www.puritysearch.net',
    );
    
    /* Suchbaer Bot */
    $knownBots['suchbaerbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'SuchbaerBot',
        'bot_url'           => 'http://bot.suchbaer.de/info.html',
        'engine_title'      => 'Suchbaer',
        'engine_url'        => 'http://www.suchbaer.de',
    );
    
    /* Tagoo Bot */
    $knownBots['tagoobot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Tagoobot',
        'bot_url'           => '',
        'engine_title'      => 'Tagoo',
        'engine_url'        => 'http://www.tagoo.ru',
    );
    
    /* youdao bot */
    $knownBots['youdaobot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'YoudaoBot',
        'bot_url'           => 'http://www.youdao.com/help/webmaster/spider',
        'engine_title'      => 'Youdao',
        'engine_url'        => 'http://www.youdao.com',
    );
    
    /* aihit bot */
    $knownBots['aihitbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'aiHitBot',
        'bot_url'           => '',
        'engine_title'      => 'aiHit',
        'engine_url'        => 'http://www.aihit.com',
    );
    
    /* sbider bot */
    $knownBots['sbider'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'SBIder',
        'bot_url'           => 'http://www.sitesell.com/sbider.html',
        'engine_title'      => 'SiteSell',
        'engine_url'        => 'http://www.sitesell.com',
    );
    
    /* Sosospider bot */
    $knownBots['sosospider'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Sosospider',
        'bot_url'           => 'http://help.soso.com/webspider.htm',
        'engine_title'      => 'Soso',
        'engine_url'        => 'http://www.soso.com',
    );
    
    /* turnitin bot */
    $knownBots['turnitinbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'TurnitinBot',
        'bot_url'           => 'http://www.turnitin.com/robot/crawlerinfo.html',
        'engine_title'      => 'Turnitin',
        'engine_url'        => 'http://www.turnitin.com',
    );
    
    /* SiteExplorer bot */
    $knownBots['siteexplorer'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => '',
        'bot_url'           => '',
        'engine_title'      => 'SiteExplorer',
        'engine_url'        => 'http://siteexplorer.info/',
    );
    
    /* envolk bot */
    $knownBots['envolk'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'envolk',
        'bot_url'           => 'http://www.envolk.com/envolkspiderinfo.html',
        'engine_title'      => 'envolk',
        'engine_url'        => 'http://www.envolk.com',
    );
    
    /* findlinks bot */
    $knownBots['findlinks'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'findlinks',
        'bot_url'           => 'http://wortschatz.uni-leipzig.de/findlinks/',
        'engine_title'      => 'FindLinks',
        'engine_url'        => '',
    );
    
    /* magpie bot */
    $knownBots['magpie-crawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'magpie-crawler',
         'bot_url'           => '',
         'engine_title'      => 'BrandWatch',
         'engine_url'        => 'http://www.brandwatch.net',
    );
    
    /* taptu bot */
    $knownBots['taptubot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'taptubot',
        'bot_url'           => 'http://www.taptu.com/corp/taptubot',
        'engine_title'      => 'Taptu',
        'engine_url'        => 'http://www.taptu.com',
    );
    
    /* kosmix bot */
    $knownBots['voyager'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'voyager',
        'bot_url'           => 'http://www.kosmix.com/crawler.html',
        'engine_title'      => 'Kosmix',
        'engine_url'        => 'http://www.kosmix.com',
    );
    
    /* SiteBot bot */
    $knownBots['sitebot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'SiteBot',
        'bot_url'           => 'http://www.sitebot.org/robot/',
        'engine_title'      => 'SiteBot',
        'engine_url'        => 'http://www.sitebot.org',
    );
    
    /* MnoGoSearch bot */
    $knownBots['mnogosearch'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'MnoGoSearch',
        'bot_url'           => '',
        'engine_title'      => 'MnoGoSearch',
        'engine_url'        => 'http://www.mnogosearch.org/',
    );
    
    /* Ezooms bot */
    $knownBots['ezooms'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Ezooms',
        'bot_url'           => '',
        'engine_title'      => 'Ezooms',
        'engine_url'        => 'http://www.ezooms.com/',
    );
    
    /* Quirina Hurdler */
    $knownBots['quirina'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Qirina Hurdler',
        'bot_url'           => 'http://www.qirina.com/hurdler.html',
        'engine_title'      => 'Qirina',
        'engine_url'        => 'http://www.qirina.com/',
    );
    
    /* AboutUs bot */
    $knownBots['aboutus'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'AboutUs bot',
        'bot_url'           => '',
        'engine_title'      => 'AboutUs',
        'engine_url'        => 'http://www.aboutus.org/',
    );
    
    /* Bixo labs bot */
    $knownBots['bixolabs.com'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Bixo labs bot',
        'bot_url'           => '',
        'engine_title'      => 'Bixo labs',
        'engine_url'        => 'http://bixolabs.com/',
    );
    
    /* Birubot */
    $knownBots['birubot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Birubot',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* unwindfetchor */
    $knownBots['unwindfetchor'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'UnwindFetchor',
        'bot_url'           => '',
        'engine_title'      => 'Gnip',
        'engine_url'        => 'http://www.gnip.com/',
    );
    
    /* Crystal Semantics Bot */
    $knownBots['crystalsemanticsbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Crystal Semantics Bot',
        'bot_url'           => 'http://www.crystalsemantics.com/service-navigation/imprint/useragent/',
        'engine_title'      => 'Crystal Semantics',
        'engine_url'        => 'http://www.crystalsemantics.com/',
    );
    
    /* PaperLiBot */
    $knownBots['paperlibot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'PaperLiBot',
        'bot_url'           => '',
        'engine_title'      => 'Amazon',
        'engine_url'        => 'http://aws.amazon.com/',
    );
    
    /* Suggy Bot */
    $knownBots['suggybot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'SuggyBot',
        'bot_url'           => 'http://blog.suggy.com/was-ist-suggy/suggy-webcrawler/',
        'engine_title'      => 'Suggy',
        'engine_url'        => 'http://blog.suggy.com/',
    );
    
    /* NjuiceBot */
    $knownBots['njuicebot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'NjuiceBot',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* OrangeAsk Bot */
    $knownBots['orangeaskbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'OrangeAskBot',
        'bot_url'           => '',
        'engine_title'      => 'OrangeAsk',
        'engine_url'        => 'http://www.orangeask.com/',
    );
    
    /* regios Bot */
    $knownBots['regios.com'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => '',
        'bot_url'           => '',
        'engine_title'      => 'Regios',
        'engine_url'        => 'http://www.regios.org/',
    );
    
    /* gravitext Bot : iudex */
    $knownBots['iudex'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Iudex',
        'bot_url'           => 'http://gravitext.com/iudex/',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* crawl-e bot */
    $knownBots['crawl-e'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'CRAWL-E',
        'bot_url'           => 'http://code.google.com/p/crawl-e/',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* Cligoo bot */
    $knownBots['cligoorobot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'CligooRobot',
        'bot_url'           => '',
        'engine_title'      => 'Cligoo',
        'engine_url'        => 'http://www.cligoo.de/',
    );
    
    /* lexxe bot */
    $knownBots['lexxebot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'lexxebot',
        'bot_url'           => '',
        'engine_title'      => 'Lexxe',
        'engine_url'        => 'http://lexxe.com/',
    );
    
    /* worio bot */
    $knownBots['worio.com'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => '',
        'bot_url'           => '',
        'engine_title'      => 'Worio',
        'engine_url'        => 'http://worio.com/',
    );
    
    /* summify bot */
    $knownBots['summify'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => '',
        'bot_url'           => '',
        'engine_title'      => 'Summify',
        'engine_url'        => 'http://summify.com/',
    );
    
    /* cmsworldmap bot */
    $knownBots['cmsworldmap'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => '',
        'bot_url'           => '',
        'engine_title'      => 'CMS World Map',
        'engine_url'        => 'http://www.cmsworldmap.com/',
    );
    
    /* GeoHasher bot */
    $knownBots['geohasher.gotdns.org'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'GeoHasher/Nutch',
        'bot_url'           => '',
        'engine_title'      => 'GeoHasher',
        'engine_url'        => 'http://geohasher.gotdns.org/',
    );
    
    /* Ahrefs bot */
    $knownBots['ahrefsbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'AhrefsBot',
        'bot_url'           => 'http://ahrefs.com/robot/',
        'engine_title'      => 'Ahrefs',
        'engine_url'        => 'https://ahrefs.com',
    );
    
    /* linkdexbot bot */
    $knownBots['linkdexbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'linkdexbot',
        'bot_url'           => 'http://www.linkdex.com/about/bots/',
        'engine_title'      => 'Linkdex',
        'engine_url'        => 'http://www.linkdex.com',
    );
    
    /* Orange Bot */
    $knownBots['orangebot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'OrangeBot',
        'bot_url'           => 'mailto:support.orangebot@orange.com',
        'engine_title'      => 'Orange',
        'engine_url'        => '',
    );
    
    /* bulk-retrieval Bot */
    $knownBots['bulk-retrieval'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'bulk-retrieval',
        'bot_url'           => 'http://varocarbas.com/bulk-retrieval_bot.php',
        'engine_title'      => '',
        'engine_url'        => 'http://varocarbas.com',
    );
    
    /* surveybot */
    $knownBots['surveybot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'SurveyBot',
        'bot_url'           => 'http://www.domaintools.com/webmasters/surveybot.php',
        'engine_title'      => 'DomainTools',
        'engine_url'        => 'http://www.domaintools.com',
    );
    
    /* Daumoa */
    $knownBots['daumoa'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Daumoa',
        'bot_url'           => 'http://tab.search.daum.net/aboutWebSearch.html',
        'engine_title'      => 'Daum',
        'engine_url'        => 'http://www.daum.net',
    );
    
    /* Daum */
    $knownBots['daum'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => '',
        'bot_url'           => '',
        'engine_title'      => 'Daum',
        'engine_url'        => 'http://www.daum.net',
    );
    
    /* FRCrawler */
    $knownBots['frcrawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'FRCrawler',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* FRCrawler, alternative    */
    $knownBots['fr_crawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'FRCrawler',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* IstellaBot */
    $knownBots['istellabot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'IstellaBot',
        'bot_url'           => 'http://www.istella.it/en/',
        'engine_title'      => 'Tiscali',
        'engine_url'        => 'http://www.tiscali.it/',
    );
    
    /* SeznamBot */
    $knownBots['seznambot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'SeznamBot',
        'bot_url'           => 'http://fulltext.sblog.cz',
        'engine_title'      => 'Seznam',
        'engine_url'        => 'https://www.seznam.cz',
    );
    
    /* SeznamBot screenshot generator */
    $knownBots['seznam screenshot-generator'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Seznam screenshot-generator',
        'bot_url'           => 'http://fulltext.sblog.cz',
        'engine_title'      => 'Seznam',
        'engine_url'        => 'https://www.seznam.cz',
    );
    
    /* 360Spider */
    $knownBots['360spider'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => '360Spider',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* memoryBot */
    $knownBots['memorybot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'memoryBot',
        'bot_url'           => 'http://mignify.com/bot.html',
        'engine_title'      => '[m]ignify',
        'engine_url'        => 'https://mignify.com',
    );
    
    /* Cliqzbot */
    $knownBots['cliqzbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Cliqzbot',
        'bot_url'           => 'http://cliqz.com/company/cliqzbot',
        'engine_title'      => 'Cliqz',
        'engine_url'        => 'https://www.cliqz.com',
    );
    
    /* YioopBot */
    $knownBots['yioopbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'YioopBot',
        'bot_url'           => 'http://www.yioop.com/bot.php',
        'engine_title'      => 'Yioop!',
        'engine_url'        => 'http://www.yioop.com',
    );
    
    /* Wotbox */
    $knownBots['wotbox'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Wotbox Web Crawler',
        'bot_url'           => 'http://www.wotbox.com/bot/',
        'engine_title'      => 'Wotbox',
        'engine_url'        => 'http://www.wotbox.com',
    );
    
    /* XoviBot */
    $knownBots['xovibot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'XoviBot',
        'bot_url'           => 'http://www.xovibot.net',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* PagesInventory */
    $knownBots['pagesinventory'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'PagesInventory',
        'bot_url'           => 'http://www.pagesinventory.com',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* DigExt; DTS Agent */
    $knownBots['digext; dts agent'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'DigExt; DTS Agent',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* TestCrawler/Nutch */
    $knownBots['testcrawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'TestCrawler/Nutch',
        'bot_url'           => 'http://balihoo.com/',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* WebTarantula.com Crawler */
    $knownBots['webtarantula'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'WebTarantula.com Crawler',
        'bot_url'           => '',
        'engine_title'      => 'WebTarantula.com',
        'engine_url'        => 'http://webtarantula.com',
    );
    
    /* CMS Crawler */
    $knownBots['cmscrawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => '',
        'bot_url'           => '',
        'engine_title'      => 'CMS Crawler',
        'engine_url'        => 'http://www.cmscrawler.com',
    );
    
    /* cuwhois */
    $knownBots['cuwhois'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'cuwhois',
        'bot_url'           => '',
        'engine_title'      => 'cuwhois.com',
        'engine_url'        => 'http://www.cuwhois.com/',
    );
    
    /* Vagabondo */
    $knownBots['vagabondo'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Vagabondo',
        'bot_url'           => '',
        'engine_title'      => 'WiseGuys',
        'engine_url'        => 'http://www.wise-guys.nl/',
    );
    
    /* Vagabondo */
    $knownBots['vagabondo'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Vagabondo',
        'bot_url'           => '',
        'engine_title'      => 'WiseGuys',
        'engine_url'        => 'http://www.wise-guys.nl/',
    );
    
    /* StatRank */
    $knownBots['statrank'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'StatRank',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* spbot */
    $knownBots['spbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'spbot',
        'bot_url'           => 'http://OpenLinkProfiler.org/bot',
        'engine_title'      => 'OpenLink Profiler',
        'engine_url'        => 'http://www.openlinkprofiler.org',
    );
    
    /* YisouSpider */
    $knownBots['yisouspider'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'YisouSpider',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* DomainAppender */
    $knownBots['domainappender'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'DomainAppender',
        'bot_url'           => 'http://www.profound.net/domainappender',
        'engine_title'      => 'Profound Networks',
        'engine_url'        => 'http://www.profound.net',
    );
    
    /* ltx71 - (http://ltx71.com/) */
    $knownBots['ltx71'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'ltx71',
        'bot_url'           => 'http://ltx71.com/',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* StudioFACA */
    $knownBots['studiofaca'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => '',
        'bot_url'           => '',
        'engine_title'      => 'StudioFACA',
        'engine_url'        => 'http://www.studiofaca.com/',
    );
    
    /* yacybot */
    $knownBots['yacybot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'yacybot',
        'bot_url'           => 'http://yacy.net/bot.html',
        'engine_title'      => 'Yacy',
        'engine_url'        => 'http://yacy.net/fr/index.html',
    );
    
    /* SISTRIX Crawler */
    $knownBots['sistrix'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'SISTRIX Crawler',
        'bot_url'           => 'http://crawler.sistrix.net/',
        'engine_title'      => 'SISTRIX',
        'engine_url'        => 'http://www.sistrix.net/',
    );
    
    /* BLEXBot */
    $knownBots['blexbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'BLEXBot',
        'bot_url'           => '',
        'engine_title'      => 'webmeup',
        'engine_url'        => 'http://webmeup-crawler.com/',
    );
    
    /* Qwantify */
    $knownBots['qwantify'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Qwantify',
        'bot_url'           => '',
        'engine_title'      => 'Qwant',
        'engine_url'        => 'https://www.qwant.com',
    );
    
    /* meanpathbot */
    $knownBots['meanpathbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'meanpathbot',
        'bot_url'           => 'http://www.meanpath.com/meanpathbot.html',
        'engine_title'      => 'meanpath',
        'engine_url'        => 'http://www.meanpath.com',
    );
    
    /* Add Catalog */
    $knownBots['add catalog'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Add Catalog',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* SemrushBot */
    $knownBots['semrushbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'SemrushBot',
        'bot_url'           => 'http://www.semrush.com/bot/',
        'engine_title'      => 'SEMrush',
        'engine_url'        => 'http://www.semrush.com',
    );
    
    /* DuckDuckGo */
    $knownBots['duckduckgo'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => '',
        'bot_url'           => '',
        'engine_title'      => 'DuckDuckGo',
        'engine_url'        => 'http://duckduckgo.com',
    );
    
    /* PageAnalyzer */
    $knownBots['pageanalyzer'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'PageAnalyzer',
        'bot_url'           => 'http://www.ranks.nl/docs/page-analyzer/troubleshooting',
        'engine_title'      => 'RANKS NL',
        'engine_url'        => 'http://www.ranks.nl',
    );
    
    /* Superarama.com bot : Tamara */
    $knownBots['superarama.com-tarama-botu'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Tarama',
        'bot_url'           => '',
        'engine_title'      => 'Superarama.com',
        'engine_url'        => 'http://www.superarama.com',
    );
    
    /* MixrankBot */
    $knownBots['mixrankbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'MixrankBot',
        'bot_url'           => 'crawler@mixrank.com',
        'engine_title'      => 'Mixrank',
        'engine_url'        => '',
    );
    
    /* finbot */
    $knownBots['finbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'FINbot',
        'bot_url'           => '',
        'engine_title'      => 'findbot.com',
        'engine_url'        => 'http://findbot.com',
    );
    
    /* Babya Discoverer */
    $knownBots['babya discoverer'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Babya Discoverer',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* ContextAd Bot */
    $knownBots['contextad bot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'ContextAd Bot',
        'bot_url'           => '',
        'engine_title'      => 'PulsePoint',
        'engine_url'        => 'http://www.pulsepoint.com',
    );
    
    /* RSSMicro.com */
    $knownBots['rssmicro.com'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'RSSMicro.com RSS/Atom Feed Robot',
        'bot_url'           => '',
        'engine_title'      => 'RSS Micro',
        'engine_url'        => 'http://www.rssmicro.com',
    );
    
    /* Sisabot */
    $knownBots['sisabot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'sisabot',
        'bot_url'           => 'http://www.sisabot.com/bot.html',
        'engine_title'      => 'Sisabot',
        'engine_url'        => 'http://www.sisabot.com',
    );
    
    /* go 1 */
    $knownBots['go 1'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Go 1.1',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* SimpleCrawler */
    $knownBots['simplecrawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'SimpleCrawler',
        'bot_url'           => 'https://github.com/cgiffard/node-simplecrawler',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* Gluten Free Crawler */
    $knownBots['gluten free crawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Gluten Free Crawler',
        'bot_url'           => 'http://glutenfreepleasure.com',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* netEstate NE Crawler */
    $knownBots['netestate ne crawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'netEstate NE Crawler',
        'bot_url'           => 'http://www.website-datenbank.de',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* idmarch bot */
    $knownBots['idmarch'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'idmarch',
        'bot_url'           => 'https://www.idmarch.org/bot.html',
        'engine_title'      => 'International Digital Media Archive',
        'engine_url'        => 'https://www.idmarch.org',
    );
    
    /* ips-agent */
    $knownBots['ips-agent'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'ips-agent',
        'bot_url'           => '',
        'engine_title'      => 'Verisign',
        'engine_url'        => 'http://www.verisign.com',
    );
    
    /* seegnifybot */
    $knownBots['seebot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'seegnifybot',
        'bot_url'           => 'http://www.seegnify.com/bot',
        'engine_title'      => 'Seegnify',
        'engine_url'        => 'http://www.seegnify.com',
    );
    
    /* riddler */
    $knownBots['riddler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'riddler',
        'bot_url'           => 'http://riddler.io/about',
        'engine_title'      => 'riddler.io',
        'engine_url'        => 'https://riddler.io',
    );
    
    /* MegaIndex.ru */
    $knownBots['megaindex.ru'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'MegaIndex',
        'bot_url'           => 'http://megaindex.com/crawler',
        'engine_title'      => 'MegaIndex',
        'engine_url'        => 'https://MegaIndex.ru',
    );
    
    /* PHPCrawl */
    $knownBots['phpcrawl'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'PHPCrawl',
        'bot_url'           => 'http://phpcrawl.cuab.de/about.html',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* worldwebheritage.org */
    $knownBots['worldwebheritage.org'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'worldwebheritage.org',
        'bot_url'           => 'crawl@worldwebheritage.org',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* worldwebheritage.org */
    $knownBots['y!j-asr'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Y!J-ASR',
        'bot_url'           => 'http://www.yahoo-help.jp/app/answers/detail/p/595/a_id/42716/',
        'engine_title'      => 'Yahoo Japan',
        'engine_url'        => 'http://www.yahoo.co.jp/',
    );
    
    /* SurdotlyBot */
    $knownBots['surdotlybot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'SurdotlyBot',
        'bot_url'           => 'http://sur.ly/bot.html',
        'engine_title'      => 'sur.ly',
        'engine_url'        => 'http://sur.ly',
    );
    
    /* RogerBot */
    $knownBots['rogerbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'RogerBot',
        'bot_url'           => '',
        'engine_title'      => 'Moz',
        'engine_url'        => 'https://moz.com',
    );
    
    /* NerdyBot */
    $knownBots['nerdybot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'NerdyBot',
        'bot_url'           => 'http://nerdybot.com/',
        'engine_title'      => 'NerdyData',
        'engine_url'        => 'http://nerdydata.com/',
    );
    
    /* AdnormCrawler */
    $knownBots['adnormcrawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'AdnormCrawler',
        'bot_url'           => '',
        'engine_title'      => 'Adnorm',
        'engine_url'        => 'http://www.adnorm.com/',
    );
    
    /* Apercite */
    $knownBots['apercite'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Apercite',
        'bot_url'           => 'http://www.apercite.fr/robot/index.html',
        'engine_title'      => 'Apercite',
        'engine_url'        => 'http://www.apercite.fr/',
    );
    
    /* Lipperhey-Kaus-Australis */
    $knownBots['lipperhey-kaus-australis'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Lipperhey Spider',
        'bot_url'           => 'https://www.lipperhey.com/en/about/',
        'engine_title'      => 'Dataprovider',
        'engine_url'        => 'https://www.dataprovider.com/',
    );
    
    /* Lipperhey SEO Service */
    $knownBots['lipperhey seo'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Lipperhey Spider',
        'bot_url'           => 'https://www.lipperhey.com/en/about/',
        'engine_title'      => 'Dataprovider',
        'engine_url'        => 'https://www.dataprovider.com/',
    );
    
    /* Dataprovider */
    $knownBots['dataprovider'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Dataprovider Spider',
        'bot_url'           => 'https://www.dataprovider.com/spider/',
        'engine_title'      => 'Dataprovider',
        'engine_url'        => 'https://www.dataprovider.com/',
    );
    
    /* SEOkicks-Robot */
    $knownBots['seokicks-robot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'SEOkicks-Robot',
        'bot_url'           => 'http://www.seokicks.de/robot.html',
        'engine_title'      => 'SEOkicks',
        'engine_url'        => 'http://www.seokicks.de/',
    );
    
    /* Focus Spider */
    $knownBots['focus spider'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Focus Spider',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* zeerch */
    $knownBots['zeerch'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Zeerch',
        'bot_url'           => 'http://www.zeerch.com/zeerch2/bot.php',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* Linkpad */
    $knownBots['linkpad'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'LinkpadBot',
        'bot_url'           => '',
        'engine_title'      => 'Linkpad',
        'engine_url'        => 'http://www.linkpad.ru',
    );
    
    /* MixBot */
    $knownBots['mixbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'MixBot',
        'bot_url'           => '',
        'engine_title'      => 'MixData',
        'engine_url'        => 'https://www.mixdata.com',
    );
    
    /* TrueBot */
    $knownBots['truebot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'TrueBot',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* NetSeer crawler */
    $knownBots['netseer crawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'NetSeer crawler',
        'bot_url'           => 'http://www.netseer.com/crawler.html',
        'engine_title'      => 'NetSeer',
        'engine_url'        => 'http://www.netseer.com',
    );
    
    /* AdvBot */
    $knownBots['advbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'AdvBot',
        'bot_url'           => 'http://advbot.net/bot.html',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* archive.org_bot */
    $knownBots['archive.org_bot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'archive.org_bot',
        'bot_url'           => 'https://archive.org/details/archive.org_bot',
        'engine_title'      => 'archive.org',
        'engine_url'        => 'https://archive.org',
    );
    
    /* Diffbot */
    $knownBots['diffbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Diffbot',
        'bot_url'           => 'http://www.diffbot.com',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* GrapeshotCrawler */
    $knownBots['grapeshotcrawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'GrapeshotCrawler',
        'bot_url'           => 'http://www.grapeshot.co.uk/crawler.php',
        'engine_title'      => 'Grapeshot',
        'engine_url'        => 'http://www.grapeshot.co.uk',
    );
    
    /* LSSRocketCrawler */
    $knownBots['lssrocketcrawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'LSSRocketCrawler',
        'bot_url'           => '',
        'engine_title'      => 'Lightspeed Systems',
        'engine_url'        => 'http://www.lightspeedsystems.com',
    );
    
    /* DomainMacroCrawler */
    $knownBots['domainmacrocrawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'DomainMacroCrawler',
        'bot_url'           => '',
        'engine_title'      => 'DomainMacro',
        'engine_url'        => 'http://domainmacro.com',
    );
    
    /* glindahl-cocrawler */
    $knownBots['glindahl-cocrawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'glindahl-cocrawler',
        'bot_url'           => 'http://www.pbm.com/~lindahl/glindahl-cocrawler.html',
        'engine_title'      => 'Greg Lindahl',
        'engine_url'        => 'http://www.pbm.com/~lindahl/',
    );
    
    /* ocrawler */
    $knownBots['ocrawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'ocrawler',
        'bot_url'           => 'omax7828@yahoo.com',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* WeViKaBot */
    $knownBots['wevikabot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'WeViKaBot',
        'bot_url'           => '',
        'engine_title'      => 'WeViKa',
        'engine_url'        => 'http://www.wevika.de',
    );
    
    /* HyperCrawl */
    $knownBots['hypercrawl'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'HyperCrawl',
        'bot_url'           => 'http://www.seograph.net/bot.html',
        'engine_title'      => 'SEO Graph',
        'engine_url'        => 'http://www.seograph.net',
    );
    
    /* psbot */
    $knownBots['psbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'psbot',
        'bot_url'           => 'http://www.picsearch.com/bot.html',
        'engine_title'      => 'Picsearch',
        'engine_url'        => 'http://www.picsearch.com',
    );
    
    /* BDCbot */
    $knownBots['bdcbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'BDCbot',
        'bot_url'           => 'http://ecommerce.bigdatacorp.com.br/faq.aspx',
        'engine_title'      => 'BigData',
        'engine_url'        => 'http://www.bigdatacorp.info',
    );
    
    /* Thunderstone */
    $knownBots['t-h-u-n-d-e-r-s-t-o-n-e'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Thunderstone',
        'bot_url'           => 'http://search.thunderstone.com/texis/websearch/about.html',
        'engine_title'      => 'Thunderstone',
        'engine_url'        => 'http://search.thunderstone.com',
    );
    
    /* Thunderstone */
    $knownBots['thunderstone'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Thunderstone',
        'bot_url'           => 'http://search.thunderstone.com/texis/websearch/about.html',
        'engine_title'      => 'Thunderstone',
        'engine_url'        => 'http://search.thunderstone.com',
    );
    
    /* Barkrowler - to be placed before Owler */
    $knownBots['barkrowler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Barkrowler',
        'bot_url'           => 'http://www.exensa.com/crawl',
        'engine_title'      => 'exenSa',
        'engine_url'        => 'http://www.exensa.com',
    );
    
    /* Owler */
    $knownBots['owler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Owler',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* maluuba-crawler */
    $knownBots['maluuba-crawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'maluuba-crawler',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* Digincore crawler */
    $knownBots['digincore crawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Digincore crawler',
        'bot_url'           => 'https://www.digincore.com/crawler.html',
        'engine_title'      => 'Digincore.com',
        'engine_url'        => 'https://www.digincore.com/index.php',
    );
    
    /* Guardcrwlr */
    $knownBots['guardcrwlr'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Guardcrwlr',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* Dazoobot */
    $knownBots['dazoobot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Dazoobot',
        'bot_url'           => '',
        'engine_title'      => 'Dazoo',
        'engine_url'        => 'http://dazoo.fr',
    );
    
    /* yelpspider */
    $knownBots['yelpspider'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'yelpspider',
        'bot_url'           => '',
        'engine_title'      => 'Yelp',
        'engine_url'        => 'http://yelp.com',
    );
    
    /* SectorPages.com    */
    $knownBots['sectorpages.com'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => '',
        'bot_url'           => '',
        'engine_title'      => 'SectorPages.com',
        'engine_url'        => 'http://sectorpages.com',
    );
    
    /* SEOlyticsCrawler */
    $knownBots['seolyticscrawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'SEOlyticsCrawler',
        'bot_url'           => 'http://crawler.seolytics.net/',
        'engine_title'      => 'SEOlytics',
        'engine_url'        => 'http://www.seolytics.com',
    );
    
    /* Robot14 */
    $knownBots['robot14'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Robot14 spider',
        'bot_url'           => 'http://www.robot14.com/bot.php',
        'engine_title'      => 'Robot14',
        'engine_url'        => 'http://www.robot14.com/',
    );
    
    /* MojeekBot */
    $knownBots['mojeekbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'MojeekBot',
        'bot_url'           => 'https://www.mojeek.com/bot.html',
        'engine_title'      => 'Mojeek',
        'engine_url'        => 'https://www.mojeek.com',
    );
    
    /* Findxbot */
    $knownBots['findxbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Findxbot',
        'bot_url'           => 'http://www.findxbot.com',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* Aloofly */
    $knownBots['aloofly'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => '',
        'bot_url'           => '',
        'engine_title'      => 'Aloofly',
        'engine_url'        => 'http://aloofly.com',
    );
    
    /* QuerySeekerSpider */
    $knownBots['queryseekerspider'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'QuerySeekerSpider',
        'bot_url'           => 'http://queryseeker.com/bot.html',
        'engine_title'      => 'QuerySeeker',
        'engine_url'        => 'http://queryseeker.com',
    );
    
    /* 007ac9 Crawler */
    $knownBots['007ac9 crawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => '007ac9 Crawler',
        'bot_url'           => 'http://crawler.007ac9.net',
        'engine_title'      => 'Sistrix',
        'engine_url'        => 'https://www.sistrix.com/',
    );
    
    /* Plukkie */
    $knownBots['plukkie'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Plukkie',
        'bot_url'           => 'http://www.botje.com/plukkie.htm',
        'engine_title'      => 'Botje',
        'engine_url'        => 'http://www.botje.com',
    );
    
    /* Uptimebot */
    $knownBots['uptimebot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Uptimebot',
        'bot_url'           => 'http://www.uptime.com/uptimebot',
        'engine_title'      => 'Uptime',
        'engine_url'        => 'http://www.uptime.com',
    );
    
    /* CheckMarkNetwork */
    $knownBots['checkmarknetwork'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'CheckMark Network Crawler',
        'bot_url'           => 'http://www.checkmarknetwork.com/spider.html/',
        'engine_title'      => 'CheckMark Network',
        'engine_url'        => 'http://www.checkmarknetwork.com/',
    );
    
    /* RukiCrawler */
    $knownBots['rukicrawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'RukiCrawler',
        'bot_url'           => 'http://ruki.rezko.net',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* electricmonk */
    $knownBots['electricmonk'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'ElectricMonk',
        'bot_url'           => 'https://www.duedil.com/our-crawler',
        'engine_title'      => 'DueDil',
        'engine_url'        => 'https://www.duedil.com',
    );
    
    /* DeuSu */
    $knownBots['deusu'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'DeuSu',
        'bot_url'           => 'https://deusu.de',
        'engine_title'      => 'deusu',
        'engine_url'        => 'https://deusu.de/robot.html',
    );
    
    /* Garlik */
    $knownBots['garlikcrawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'GarlikCrawler',
        'bot_url'           => '',
        'engine_title'      => 'Garlik',
        'engine_url'        => 'http://garlik.com/',
    );
    
    /* Experibot */
    $knownBots['experibot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Experibot',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* SafeDNSBot */
    $knownBots['safednsbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'SafeDNSBot',
        'bot_url'           => 'https://www.safedns.com/searchbot',
        'engine_title'      => 'SafeDNS',
        'engine_url'        => 'https://www.safedns.com/',
    );
    
    /* SMTBot mobile */
    $knownBots['mobile/10a5376e safari/8536.25 (compatible; smtbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'handheld',
        'bot_title'         => 'SMTBot',
        'bot_url'           => 'http://www.similartech.com/smtbot',
        'engine_title'      => 'SimilarTech',
        'engine_url'        => 'http://www.similartech.com/');


    /* SMTBot */
    $knownBots['smtbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'SMTBot',
        'bot_url'           => 'http://www.similartech.com/smtbot',
        'engine_title'      => 'SimilarTech',
        'engine_url'        => 'http://www.similartech.com/',
    );
    
    /* DNSdelve */
    $knownBots['dnsdelve'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => '',
        'bot_url'           => '',
        'engine_title'      => 'DNSdelve',
        'engine_url'        => 'http://www.dnsdelve.net',
    );
    
    /* redback */
    $knownBots['redback'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'redback',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* seoscanners.net */
    $knownBots['seoscanners.net'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'seoscanners.net',
        'bot_url'           => 'spider@seoscanners.net',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* yoozBot */
    $knownBots['yoozbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'yoozBot',
        'bot_url'           => '',
        'engine_title'      => 'Yooz',
        'engine_url'        => 'http://yooz.ir',
    );
    
    /* contactbigdatafr */
    $knownBots['contactbigdatafr'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'contactbigdatafr',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* LinqiaCrawlerBot */
    $knownBots['linqiacrawlerbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'LinqiaCrawlerBot',
        'bot_url'           => 'eng@linqia.com',
        'engine_title'      => 'Linqia',
        'engine_url'        => 'http://www.linqia.com',
    );
    
    /* LinqiaRSSBot */
    $knownBots['linqiarssbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'LinqiaRSSBot',
        'bot_url'           => 'eng@linqia.com',
        'engine_title'      => 'Linqia',
        'engine_url'        => 'http://www.linqia.com',
    );
    
    /* ZoomBot */
    $knownBots['zoombot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'ZoomBot',
        'bot_url'           => '',
        'engine_title'      => 'seozoom',
        'engine_url'        => 'https://www.seozoom.it',
    );
    
    /* eXenSa-DEW - to be added before bubing */
    $knownBots['exensa'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'eXenSa-DEW',
        'bot_url'           => '',
        'engine_title'      => 'eXenSa',
        'engine_url'        => 'http://www.exensa.com',
    );
    
    /* BUbiNG */
    $knownBots['bubing'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'BUbiNG',
        'bot_url'           => 'http://law.di.unimi.it/BUbiNG.html',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* CATExplorador */
    $knownBots['catexplorador'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'CATExplorador',
        'bot_url'           => 'http://domini.cat/catexplorador.html',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* aisou */
    $knownBots['aisou'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'aisou',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* IDBot */
    $knownBots['idbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'IDBot',
        'bot_url'           => 'http://www.id-search.xyz/bot.html',
        'engine_title'      => 'ID-Search<sup>xyz</sup>',
        'engine_url'        => 'http://www.id-search.xyz',
    );
    
    /* DomainCrawler */
    $knownBots['domaincrawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'DomainCrawler',
        'bot_url'           => 'info@domaincrawler.com',
        'engine_title'      => 'DomainCrawler',
        'engine_url'        => 'http://www.domaincrawler.com',
    );
    
    /* parsijoo-bot */
    $knownBots['parsijoo-bot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'parsijoo-bot',
        'bot_url'           => 'ehsanmousa@parsijoo.ir',
        'engine_title'      => 'Parsijoo',
        'engine_url'        => 'http://www.parsijoo.ir/',
    );
    
    /* bnf.fr_bot */
    $knownBots['bnf.fr_bot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'bnf.fr_bot',
        'bot_url'           => 'http://www.bnf.fr/fr/outils/a.dl_web_capture_robot.html',
        'engine_title'      => 'Biblioth&egrave;que Nationale de France',
        'engine_url'        => 'http://www.bnf.fr',
    );
    
    /* sSearch Crawler */
    $knownBots['ssearch_bot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'sSearch Crawler',
        'bot_url'           => '',
        'engine_title'      => 'sSearch',
        'engine_url'        => 'http://www.semantissimo.de',
    );
    
    /* wonderbot/JS */
    $knownBots['wonderbot/js'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'wonderbot',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* SecurityResearch.bot */
    $knownBots['securityresearch.bot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'SecurityResearch.bot',
        'bot_url'           => 'http://besome1.info/securityresearchbot.html',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* deeris */
    $knownBots['deeris'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Deeris',
        'bot_url'           => 'http://www.deeris.com',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* Searchie */
    $knownBots['searchie'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Searchie',
        'bot_url'           => 'https://www.searchie.org',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* AugDiscovery-Bot */
    $knownBots['augdiscovery-bot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'AugDiscovery-Bot',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* ToweYandext */
    $knownBots['toweyabot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Toweyabot',
        'bot_url'           => '',
        'engine_title'      => 'Toweya',
        'engine_url'        => 'toweya.com',
    );
    
    /* RSSingBot */
    $knownBots['rssingbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'RSSingBot',
        'bot_url'           => '',
        'engine_title'      => 'RSSing',
        'engine_url'        => 'http://www.rssing.com',
    );
    
    /* exif-search */
    $knownBots['www.exif-search.com'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Heritrix',
        'bot_url'           => '',
        'engine_title'      => 'Exif Search',
        'engine_url'        => 'https://www.exif-search.com',
    );
    
    /* Digincore bot */
    $knownBots['digincore bot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Digincore bot',
        'bot_url'           => 'https://www.digincore.com/crawler.html',
        'engine_title'      => 'Digincore',
        'engine_url'        => 'https://www.digincore.com',
    );
    
    /* Wopabot */
    $knownBots['wopabot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Wopabot',
        'bot_url'           => '',
        'engine_title'      => 'Wopa',
        'engine_url'        => 'https://www.wopa.fr/',
    );
    
    /* linkapediabot */
    $knownBots['linkapediabot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'linkapediabot',
        'bot_url'           => '',
        'engine_title'      => 'Linkapedia',
        'engine_url'        => 'http://www.linkapedia.com',
    );
    
    /* WBSearchBot */
    $knownBots['wbsearchbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'WBSearchBot',
        'bot_url'           => 'http://www.warebay.com/bot.html',
        'engine_title'      => 'Warebay',
        'engine_url'        => 'http://www.warebay.com',
    );
    
    /* BacklinkCrawler */
    $knownBots['backlinkcrawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'BacklinkCrawler',
        'bot_url'           => 'http://www.backlinktest.com/crawler.html',
        'engine_title'      => 'backlink test',
        'engine_url'        => 'http://www.backlinktest.com',
    );
    
    /* ParsijooBot */
    $knownBots['parsijoobot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'ParsijooBot',
        'bot_url'           => 'crawler@parsijoo.ir',
        'engine_title'      => 'Parsijoo',
        'engine_url'        => 'http://www.parsijoo.ir',
    );
    
    /* Stratagems Kumo */
    $knownBots['stratagems kumo'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Stratagems Kumo',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* ExactSeekCrawler */
    $knownBots['exactseekcrawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'ExactSeekCrawler',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* Jaunt */
    $knownBots['jaunt/'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Jaunt',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* UXCrawlerBot    */
    $knownBots['uxcrawlerbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'UXCrawlerBot ',
        'bot_url'           => '',
        'engine_title'      => 'Zium',
        'engine_url'        => 'http://zium.co',
    );
    
    /* HRCrawlerBot    */
    $knownBots['hrcrawlerbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'HRCrawlerBot ',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* LinqiaMetadataDownloaderBot    */
    $knownBots['linqiametadatadownloaderbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'LinqiaMetadataDownloaderBot ',
        'bot_url'           => 'eng@linqia.com',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* roboto    */
    $knownBots['roboto'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'roboto ',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* 2ADAMbot */
    $knownBots['2adambot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => '2ADAMbot ',
        'bot_url'           => '',
        'engine_title'      => '2adam',
        'engine_url'        => 'http://www.2adam.com',
    );
    
    /* mfibot */
    $knownBots['mfibot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'mfibot ',
        'bot_url'           => '',
        'engine_title'      => 'mfisoft',
        'engine_url'        => 'http://www.mfisoft.ru/analyst/',
    );
    
    /* FlippyBearBot */
    $knownBots['flippybearbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'FlippyBearBot ',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* vebidoobot */
    $knownBots['vebidoobot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'vebidoobot ',
        'bot_url'           => 'https://blog.vebidoo.de/vebidoobot/',
        'engine_title'      => 'vebidoo',
        'engine_url'        => 'https://www.vebidoo.de',
    );
    
    /* Xaldon WebSpider */
    $knownBots['xaldon'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Xaldon WebSpider ',
        'bot_url'           => '',
        'engine_title'      => 'Xaldon',
        'engine_url'        => 'http://www.xaldon.de',
    );
    
    /* panscient.com */
    $knownBots['panscient.com'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => '',
        'bot_url'           => '',
        'engine_title'      => 'panscient.com',
        'engine_url'        => 'http://panscient.com',
    );
    
    /* semanticbot */
    $knownBots['semanticbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'semanticbot',
        'bot_url'           => 'info@semanticaudience.com',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* LinqiaScrapeBot */
    $knownBots['linqiascrapebot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'LinqiaScrapeBot',
        'bot_url'           => '',
        'engine_title'      => 'Linqia',
        'engine_url'        => 'http://www.linqia.com',
    );
    
    /* focusbot */
    $knownBots['focusbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'focusbot',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* orbiter */
    $knownBots['orbiter'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'orbiter',
        'bot_url'           => '',
        'engine_title'      => 'DailyOrbit',
        'engine_url'        => 'http://dailyorbit.com',
    );
    
    /* spuhexbot */
    $knownBots['spuhexbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'SpuhexBot',
        'bot_url'           => '',
        'engine_title'      => 'Spuhex',
        'engine_url'        => 'http://www.spuhex.com',
    );
    
    /* iZSearch.com    */
    $knownBots['izsearch.com'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => '',
        'bot_url'           => '',
        'engine_title'      => 'iZSearch.com',
        'engine_url'        => 'http://iZSearch.com',
    );
    
    /* servernfo.com    */
    $knownBots['servernfo.com'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => '',
        'bot_url'           => '',
        'engine_title'      => 'servernfo.com',
        'engine_url'        => 'http://servernfo.com/',
    );
    
    /* PrivacyAwareBot */
    $knownBots['privacyawarebot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'PrivacyAwareBot',
        'bot_url'           => '',
        'engine_title'      => 'Privacy Aware',
        'engine_url'        => 'http://www.privacyaware.org',
    );
    
    /* WbSrch */
    $knownBots['wbsrch'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => '',
        'bot_url'           => '',
        'engine_title'      => 'WbSrch',
        'engine_url'        => 'http://wbsrch.com',
    );
    
    /* Cuasarbot */
    $knownBots['cuasarbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Cuasarbot',
        'bot_url'           => '',
        'engine_title'      => 'Cuasar',
        'engine_url'        => 'http://www.cuasar.com/spider_beta/',
    );
    
    /* Lippershey */
    $knownBots['lippershey'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Lippershey',
        'bot_url'           => 'https://www.lipperhey.com/en/about/website-spider/',
        'engine_title'      => 'Lipperhey',
        'engine_url'        => 'https://www.lipperhey.com',
    );
    
    /* ImplisenseBot */
    $knownBots['implisensebot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'ImplisenseBot',
        'bot_url'           => '',
        'engine_title'      => 'Implisense',
        'engine_url'        => 'http://implisense.com',
    );
    
    /* coccoc */
    $knownBots['coccoc'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'coccocbot',
        'bot_url'           => '',
        'engine_title'      => 'coccoc',
        'engine_url'        => 'http://help.coccoc.com/',
    );
    
    /* coccoc */
    $knownBots['coccoc'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'coccocbot',
        'bot_url'           => '',
        'engine_title'      => 'coccoc',
        'engine_url'        => 'http://help.coccoc.com/',
    );
    
    /* ltbot */
    $knownBots['ltbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'ltbot',
        'bot_url'           => '',
        'engine_title'      => 'Knowledge Discovery Scientific Literature',
        'engine_url'        => 'http://www.kdsl.tu-darmstadt.de/de/kdsl/research-program/crawling-and-semantic-structuring/',
    );
    
    /* HRCrawler */
    $knownBots['hrcrawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'HRCrawler',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* Simple crawler */
    $knownBots['simple crawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Simple crawler',
        'bot_url'           => 'http://crawler.own3d.pl',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* uMBot */
    $knownBots['umbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'uMBot',
        'bot_url'           => '',
        'engine_title'      => 'ubermetrics',
        'engine_url'        => 'http://www.ubermetrics-technologies.com',
    );
    
    /* JobFeed discovery script */
    $knownBots['jobfeed discovery script'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'uMBot',
        'bot_url'           => '',
        'engine_title'      => 'JobFeed',
        'engine_url'        => 'http://www.jobfeed.com',
    );
    
    /* LinkStats Bot */
    $knownBots['linkstats bot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'LinkStats Bot',
        'bot_url'           => '',
        'engine_title'      => 'Peter Shumacher',
        'engine_url'        => 'http://web-eifel.de',
    );
    
    /* ichiro */
    $knownBots['ichiro'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'ichiro',
        'bot_url'           => 'http://search.goo.ne.jp/option/use/sub4/sub4-1/',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* archive-fr.com */
    $knownBots['archive-fr.com'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'archive-fr.com',
        'bot_url'           => 'http://archive-fr.com/bot',
        'engine_title'      => 'Archive-fr.com',
        'engine_url'        => 'http://archive-fr.com/',
    );
    
    /* serbot */
    $knownBots['serbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'serbot',
        'bot_url'           => 'http://www.serdec.com/bot.html',
        'engine_title'      => 'serdec',
        'engine_url'        => 'http://www.serdec.com',
    );
    
    /* TWMBot */
    $knownBots['twmbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'TWMBot',
        'bot_url'           => '',
        'engine_title'      => 'The Web Miner',
        'engine_url'        => 'https://thewebminer.com',
    );
    
    /* LinkWalker */
    $knownBots['linkwalker'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'LinkWalker',
        'bot_url'           => '',
        'engine_title'      => 'Brand Protect',
        'engine_url'        => 'http://www.brandprotect.com',
    );
    
    /* SpiderLing */
    $knownBots['spiderling'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'SpiderLing',
        'bot_url'           => 'http://nlp.fi.muni.cz/trac/spiderling',
        'engine_title'      => 'BiWeC',
        'engine_url'        => 'https://nlp.fi.muni.cz/projects/biwec/',
    );
    
    /* SafeSearch microdata crawler */
    $knownBots['safesearch microdata crawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'SafeSearch',
        'bot_url'           => 'https://safesearch.avira.com',
        'engine_title'      => 'Avira',
        'engine_url'        => 'https://www.avira.com/fr/index',
    );
    
    /* Corporama matcher */
    $knownBots['corporama matcher'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Corporama matcher',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* ActiveWorlds */
    $knownBots['activeworlds'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => '',
        'bot_url'           => '',
        'engine_title'      => 'ActiveWorlds',
        'engine_url'        => 'https://www.activeworlds.com/web/index.php',
    );
    
    /* HELLO Crawler */
    $knownBots['hello crawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'HELLO Crawler',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* Larbin */
    $knownBots['larbin'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'larbin',
        'bot_url'           => 'http://larbin.sourceforge.net',
        'engine_title'      => '',
        'engine_url'        => '');

    $knownBots['binlar'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'larbin',
        'bot_url'           => 'http://larbin.sourceforge.net',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* IpixelY */
    $knownBots['ipixely'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'IpixelY',
        'bot_url'           => '',
        'engine_title'      => 'IpixelY',
        'engine_url'        => 'http://www.ipixely.xyz',
    );
    
    /* JamesBOT */
    $knownBots['james bot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'JamesBOT',
        'bot_url'           => 'http://cognitiveseo.com/bot.html',
        'engine_title'      => 'Congitive SEO',
        'engine_url'        => 'http://cognitiveseo.com');

    $knownBots['cognitiveseo'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'JamesBOT',
        'bot_url'           => 'http://cognitiveseo.com/bot.html',
        'engine_title'      => 'Congitive SEO',
        'engine_url'        => 'http://cognitiveseo.com',
    );
    
    /* aranea */
    $knownBots['aranea'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Aranea',
        'bot_url'           => 'http://aranea.juls.savba.sk/',
        'engine_title'      => 'Web Corpora &amp; Corpus Linguistics Portal',
        'engine_url'        => 'http://aranea.juls.savba.sk/aranea_about.html',
    );
    
    /* VenusCrawler */
    $knownBots['venuscrawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'VenusCrawler',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* gobyus */
    $knownBots['gobyus'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'gobyus',
        'bot_url'           => '',
        'engine_title'      => 'gobyus',
        'engine_url'        => 'http://gobyus.com/en',
    );
    
    /* WP Spydr */
    $knownBots['wp spydr'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'WP Spydr',
        'bot_url'           => 'http://wpspydr.com',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* Virusdie crawler */
    $knownBots['virusdie crawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Virusdie crawler',
        'bot_url'           => '',
        'engine_title'      => 'Virusdie',
        'engine_url'        => 'https://virusdie.com',
    );
    
    /* StumbleUpon crawler */
    $knownBots['stumbleupon'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => '',
        'bot_url'           => '',
        'engine_title'      => 'StumbleUpon',
        'engine_url'        => 'https://http://www.stumbleupon.com',
    );
    
    /* Vegi bot */
    $knownBots['vegi bot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Vegi bot',
        'bot_url'           => 'mailto:abuse-report@terrykyleseoagency.com',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* AwarioSmartBot */
    $knownBots['awariosmartbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'AwarioSmartBot',
        'bot_url'           => 'https://awario.com/bots.html',
        'engine_title'      => 'Awario',
        'engine_url'        => 'https://awario.com',
    );
    
    /* 0xff.org */
    $knownBots['0xff.org'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => '0xFF Domain Crawler',
        'bot_url'           => '',
        'engine_title'      => '0xff.org',
        'engine_url'        => 'https://0xff.org',
    );
    
    /* YaK from linkfluence.com */
    $knownBots['linkfluence.com'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'YaK',
        'bot_url'           => 'mailto:bot@linkfluence.com',
        'engine_title'      => 'linkfluence',
        'engine_url'        => 'http://linkfluence.com/',
    );
    
    /* aboundex */
    $knownBots['aboundex'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Aboundex Crawler',
        'bot_url'           => 'http://www.aboundex.com/crawler/',
        'engine_title'      => 'Aboundex',
        'engine_url'        => 'http://www.aboundex.com/',
    );
    
    /* KomodiaBot */
    $knownBots['komodiabot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'KomodiaBot',
        'bot_url'           => 'http://www.komodia.com/newwiki/index.php/URL_server_crawler',
        'engine_title'      => 'Komodia',
        'engine_url'        => 'http://www.komodia.com/',
    );
    
    /* spyonweb.com */
    $knownBots['spyonweb.com'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => '',
        'bot_url'           => '',
        'engine_title'      => 'SpyOnWeb',
        'engine_url'        => 'http://spyonweb.com/',
    );
    
    /* ZoominfoBot */
    $knownBots['zoominfobot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'ZoominfoBot',
        'bot_url'           => 'mailto:ZoominfoBot@zoominfo.com',
        'engine_title'      => 'ZoominfoBot',
        'engine_url'        => 'http://www.zoominfo.com/',
    );
    
    /* XilopixBot */
    $knownBots['xilopixbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'XilopixBot',
        'bot_url'           => 'http://www.xilopix.com/bot.html',
        'engine_title'      => 'Xilopix',
        'engine_url'        => 'http://pro.xilopix.com',
    );
    
    /* kula.jp/endo */
    $knownBots['kula.jp/endo'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => '',
        'bot_url'           => '',
        'engine_title'      => 'Endo',
        'engine_url'        => 'http://kula.jp/endo',
    );
    
    /* DJEcoBot */
    $knownBots['djecobot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'DJEcoBot',
        'bot_url'           => 'mailto:analytics@demandjump.com',
        'engine_title'      => 'DemandJump',
        'engine_url'        => 'https://www.demandjump.com',
    );
    
    /* RankingBot2 */
    $knownBots['rankingbot2'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'RankingBot2',
        'bot_url'           => 'https://varocarbas.com/bot_ranking2/',
        'engine_title'      => 'varocarbas.com',
        'engine_url'        => 'https://varocarbas.com',
    );
    
    /* AliveAdvisorCrawler */
    $knownBots['aliveadvisorcrawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'AliveAdvisorCrawler',
        'bot_url'           => 'mailto:crawler@aliveadvisor.com',
        'engine_title'      => 'AliveAdvisor',
        'engine_url'        => 'http://search.aliveadvisor.com',
    );
    
    /* http://www.x9o.de */
    $knownBots['www.x9o.de'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => '',
        'bot_url'           => '',
        'engine_title'      => 'x9o.de',
        'engine_url'        => 'http://www.x9o.de',
    );
    
    /* ExtLinksBot */
    $knownBots['extlinksbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'ExtLinksBot',
        'bot_url'           => 'https://extlinks.com/Bot.html',
        'engine_title'      => 'ExtLinks',
        'engine_url'        => 'https://extlinks.com/',
    );
    
    /* DomainStatsBot */
    $knownBots['domainstatsbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'DomainStatsBot',
        'bot_url'           => 'http://domainstats.io/our-bot',
        'engine_title'      => 'DomainStats.io',
        'engine_url'        => 'http://domainstats.io/',
    );
    
    /* GroupHigh */
    $knownBots['grouphigh'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => '',
        'bot_url'           => '',
        'engine_title'      => 'GroupHigh',
        'engine_url'        => 'http://www.grouphigh.com/',
    );
    
    /* Melodibot */
    $knownBots['melodibot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Melodibot',
        'bot_url'           => 'http://www.irit.fr/melodibot/',
        'engine_title'      => 'IRIT',
        'engine_url'        => 'https://www.irit.fr',
    );
    
    /* SnowHaze SearcH */
    $knownBots['snowhaze search'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'SnowHaze SearcH',
        'bot_url'           => 'mailto:support@snowhaze.com',
        'engine_title'      => 'SnowHaze',
        'engine_url'        => 'https://snowhaze.com/',
    );
    
    /* Scopia Crawler */
    $knownBots['scopia crawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Scopia Crawler',
        'bot_url'           => '',
        'engine_title'      => 'Scopia',
        'engine_url'        => 'http://www.scopia.co',
    );
    
    /* Companybook-Crawler */
    $knownBots['companybook-crawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Companybook-Crawler',
        'bot_url'           => '',
        'engine_title'      => 'Companybook',
        'engine_url'        => 'https://www.companybooknetworking.com',
    );
    
    /* ExperianCrawlUK */
    $knownBots['experiancrawluk'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'ExperianCrawlUK',
        'bot_url'           => '',
        'engine_title'      => 'PHGroup',
        'engine_url'        => 'http://www.phgroup.com',
    );
    
    /* Zombiebot */
    $knownBots['zombiebot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Zombiebot',
        'bot_url'           => 'http://www.zombiedomain.net/robot/',
        'engine_title'      => 'ZombieDomain',
        'engine_url'        => 'http://www.zombiedomain.net',
    );
    
    /* AlphaBot */
    $knownBots['alphabot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'AlphaBot',
        'bot_url'           => 'http://alphaseobot.com/bot.html',
        'engine_title'      => 'Alpha SEO Bot',
        'engine_url'        => 'http://alphaseobot.com/',
    );
    
    /* Gowikibot */
    $knownBots['gowikibot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Gowikibot',
        'bot_url'           => 'http://www.gowikibot.com',
        'engine_title'      => 'GoWiki',
        'engine_url'        => '',
    );
    
    /* Seobility */
    $knownBots['seobility'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Seobility bot',
        'bot_url'           => 'https://www.seobility.net/sites/bot.html',
        'engine_title'      => 'Seobility',
        'engine_url'        => 'https://www.seobility.net/en/',
    );
    
    /* IndeedBot */
    $knownBots['indeedbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'IndeedBot',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* looid.com crawler */
    $knownBots['looid.com crawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'looid.com crawler',
        'bot_url'           => 'looid.com',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* um-LN */
    $knownBots['um-ln'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'um-LN',
        'bot_url'           => 'mailto:techinfo@ubermetrics-technologies.com',
        'engine_title'      => 'uberMetrics Technologies',
        'engine_url'        => 'https://www.ubermetrics-technologies.com',
    );
    
    /* um-FC */
    $knownBots['um-fc'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'um-FC',
        'bot_url'           => 'mailto:techinfo@ubermetrics-technologies.com',
        'engine_title'      => 'uberMetrics Technologies',
        'engine_url'        => 'https://www.ubermetrics-technologies.com',
    );
    
    /* Grobbot */
    $knownBots['grobbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Grobbot',
        'bot_url'           => '',
        'engine_title'      => 'Grob',
        'engine_url'        => 'https://grob.it',
    );
    
    /* Contacts-Crawler */
    $knownBots['contacts-crawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Contacts-Crawler',
        'bot_url'           => '',
        'engine_title'      => 'Scrapinghub',
        'engine_url'        => 'http://www.scrapinghub.com',
    );
    
    /* GeeGee */
    $knownBots['geegee'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => '',
        'bot_url'           => '',
        'engine_title'      => 'GeeGee',
        'engine_url'        => 'https://geegee.online/',
    );
    
    /* AplicatiiGalaxy */
    $knownBots['aplicatiigalaxy'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'AplicatiiGalaxy',
        'bot_url'           => 'mailto:aplicatiigalaxy@gmail.com',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* PiplBot */
    $knownBots['piplbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'PiplBot',
        'bot_url'           => 'http://www.pipl.com/bot/',
        'engine_title'      => 'Pipl',
        'engine_url'        => 'http://www.pipl.com',
    );
    
    /* LightspeedSystemsCrawler */
    $knownBots['lightspeedsystemscrawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'LightspeedSystemsCrawler',
        'bot_url'           => '',
        'engine_title'      => 'Lightspeed Systems, Inc.',
        'engine_url'        => 'https://www.lightspeedsystems.com',
    );
    
    /* SearchmetricsBot */
    $knownBots['searchmetricsbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'SearchmetricsBot',
        'bot_url'           => 'https://www.searchmetrics.com/searchmetricsbot/',
        'engine_title'      => 'SearchMetrics',
        'engine_url'        => 'https://www.searchmetrics.com/',
    );
    
    /* Techlimed */
    $knownBots['techlimed'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'ntlk/Nutch',
        'bot_url'           => '',
        'engine_title'      => 'Techlimed',
        'engine_url'        => '',
    );
    
    /* pmoz.info */
    $knownBots['pmoz.info'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'pmoz.info ODP link checker',
        'bot_url'           => 'http://pmoz.info/doc/botinfo.htm',
        'engine_title'      => 'Dmoz.org',
        'engine_url'        => 'http://www.dmoz.org',
    );
    
    /* ArchiveBot */
    $knownBots['archivebot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'ArchiveBot',
        'bot_url'           => 'https://www.archiveteam.org/index.php?title=ArchiveBot',
        'engine_title'      => 'ArchiveTeam',
        'engine_url'        => 'https://www.archiveteam.org',
    );
    
    /* OrgProbe */
    $knownBots['orgprobe'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'OrgProbe',
        'bot_url'           => '',
        'engine_title'      => 'Blocked!',
        'engine_url'        => 'https://www.blocked.org.uk',
    );
    
    /* RobotsChecker */
    $knownBots['robotschecker'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'OrgProbe',
        'bot_url'           => '',
        'engine_title'      => 'Blocked!',
        'engine_url'        => 'https://www.blocked.org.uk',
    );
    
    /* Researchscan */
    $knownBots['researchscan'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Researchscan',
        'bot_url'           => 'http://researchscan.comsys.rwth-aachen.de',
        'engine_title'      => 'RWTH Aachen University',
        'engine_url'        => 'http://www.rwth-aachen.de',
    );
    
    /* Jooblebot */
    $knownBots['jooblebot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Jooblebot',
        'bot_url'           => 'https://jooble.org/jooble-bot',
        'engine_title'      => 'Jooble',
        'engine_url'        => 'https://jooble.org',
    );
    
    /* MBCrawler */
    $knownBots['mbcrawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'MBCrawler',
        'bot_url'           => '',
        'engine_title'      => 'monitorbacklinks',
        'engine_url'        => 'https://monitorbacklinks.com',
    );
    
    /* DomainSigmaCrawler */
    $knownBots['domainsigmacrawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'DomainSigmaCrawler',
        'bot_url'           => 'http://domainsigma.com/robot',
        'engine_title'      => 'DomainSigma',
        'engine_url'        => 'http://domainsigma.com/',
    );
    
    /* Hstpnetwork.com */
    $knownBots['hstpnetwork.com'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => '',
        'bot_url'           => '',
        'engine_title'      => 'HSTPNetwork',
        'engine_url'        => 'http://www.hstpnetwork.com',
    );
    
    /* NYU Internet Census */
    $knownBots['nyu internet census'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => '',
        'bot_url'           => '',
        'engine_title'      => 'NYU Internet Census',
        'engine_url'        => 'https://scan.lol',
    );
    
    /* Streamline3Bot */
    $knownBots['streamline3bot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Streamline3Bot',
        'bot_url'           => 'https://www.ubtsupport.com/legal/Streamline3Bot.php',
        'engine_title'      => 'UBT',
        'engine_url'        => 'https://www.ubtsupport.com',
    );
    
    /* DomainCheck.io */
    $knownBots['domaincheck.io'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'DomainCheck.io Crawler',
        'bot_url'           => '',
        'engine_title'      => 'DomainCheck.io',
        'engine_url'        => 'https://domaincheck.io',
    );
    
    /* Datanyze */
    $knownBots['datanyze'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => '',
        'bot_url'           => '',
        'engine_title'      => 'Datanyze',
        'engine_url'        => 'https://www.datanyze.com',
    );
    
    /* eright */
    $knownBots['eright'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'eRight bot',
        'bot_url'           => 'mailto:bot@eright.com',
        'engine_title'      => 'eRight',
        'engine_url'        => 'https://www.eright.com',
    );
    
    /* NetTrack */
    $knownBots['nettrack'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => '',
        'bot_url'           => '',
        'engine_title'      => 'NetTrack',
        'engine_url'        => 'https://nettrack.info/',
    );
    
    /* bitlybot */
    $knownBots['bitlybot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'bitlybot',
        'bot_url'           => '',
        'engine_title'      => 'Bit.ly',
        'engine_url'        => 'http://bit.ly/',
    );
    
    /* e.ventures Investment Crawler (eventures.vc)  */
    $knownBots['e.venture'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'e.ventures Investment Crawler',
        'bot_url'           => '',
        'engine_title'      => 'e.ventures Investment',
        'engine_url'        => 'https://eventures.vc',
    );
    
    /* tracemyfile  */
    $knownBots['tracemyfile'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'tracemyfile Bot',
        'bot_url'           => 'mailto:bot@tracemyfile.com',
        'engine_title'      => 'tracemyfile',
        'engine_url'        => 'https://tracemyfile.com',
    );
    
    /* bitlybot */
    $knownBots['bitlybot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'bitlybot',
        'bot_url'           => '',
        'engine_title'      => 'Bit.ly',
        'engine_url'        => 'http://bit.ly/',
    );
    
    /* 3w24bot */
    $knownBots['3w24bot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => '3w24bot',
        'bot_url'           => 'https://3w24.com/bot/',
        'engine_title'      => '3W24',
        'engine_url'        => 'https://3w24.com',
    );
    
    /* trendictionbot */
    $knownBots['trendictionbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'trendictionbot0',
        'bot_url'           => 'http://www.trendiction.de/bot',
        'engine_title'      => 'trendiction.de',
        'engine_url'        => 'http://www.trendiction.de',
    );
    
    /* Quick-Crawler */
    $knownBots['quick-crawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Quick-Crawler',
        'bot_url'           => '',
        'engine_title'      => 'ScrapingHub',
        'engine_url'        => 'https://www.scrapinghub.com/)',
    );
    
    /* unknown bots */
    
    /* SEOBulls - unknown bot */
    $knownBots['seo bulls'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'SEO Bulls (Unknown bot)',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* SEOBulls - unknown bot */
    $knownBots['seobulls'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'SEO Bulls (Unknown bot)',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* unknown bot */
    $knownBots['tmm crawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'TMM Crawler (Unknown bot)',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* unknown bot */
    $knownBots['no.indexing@gmail.com'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Unknown bot',
        'bot_url'           => 'mailto:no.indexing@gmail.com',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* unknown bot */
    $knownBots['nbertaupete95(at)gmail.com'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Unknown bot',
        'bot_url'           => 'mailto:nbertaupete95@gmail.com',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* Centurybot9 - unknown bot */
    $knownBots['centurybot9'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Centurybot9 (Unknown bot)',
        'bot_url'           => 'mailto:centurybot9@gmail.com',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* celious search engine - unknown bot */
    $knownBots['celious search engine'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Celious Search Engine (Unknown bot)',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* SMURLExpander - unknown bot */
    $knownBots['smurlexpander'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'SMURLExpander (Unknown bot)',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* DnyzBot - unknown bot */
    $knownBots['dnyzbot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'DnyzBot (Unknown bot)',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* adscanner - unknown bot */
    $knownBots['adscanner'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'adscanner (Unknown bot)',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* UCmore - unknown bot */
    $knownBots['ucmore'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'UCmore (Unknown bot)',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* BigDataCloud - unknown bot */
    $knownBots['bigdatacloud'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'BigDataCloud (Unknown bot)',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* Peopleman - unknown bot */
    $knownBots['peopleman'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Peopleman (Unknown bot)',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* KickFire - unknown bot */
    $knownBots['kickfire'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'KickFire (Unknown bot)',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* Microgine Crawler - unknown bot */
    $knownBots['microgine crawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Microgine Crawler (Unknown bot)',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* Meta_Bot - unknown bot */
    $knownBots['meta_bot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Meta_Bot (Unknown bot)',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* Your-Website-Sucks - unknown bot */
    $knownBots['your-website-sucks'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Your-Website-Sucks (Unknown bot)',
        'bot_url'           => 'http://www.Your-Website-Sucks.net/',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* test/0.1 (tester)    - unknown bot */
    $knownBots['tester'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'test (Unknown bot)',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* MauiBot - unknown bot */
    $knownBots['mauibot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'MauiBot',
        'bot_url'           => 'mailto:crawler.feedback+wc@gmail.com',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* MauiBot ? crawler (crawler.feedback@gmail.com) - unknown bot */
    $knownBots['crawler.feedback@gmail.com'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'crawler (crawler.feedback@gmail.com) (Unknown bot)',
        'bot_url'           => 'mailto:crawler.feedback@gmail.com',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* Auto Spider - unknown bot */
    $knownBots['auto spider'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Auto Spider (Unknown bot)',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* VelenPublicWebCrawler - unknown bot */
    $knownBots['velenpublicwebcrawler'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'VelenPublicWebCrawler (Unknown bot)',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* The Knowledge AI  - unknown bot */
    $knownBots['the knowledge ai'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'The Knowledge AI (Unknown bot)',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );
    
    /* return bot list */
    return $knownBots;
}
?>