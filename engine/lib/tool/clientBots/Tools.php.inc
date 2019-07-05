<?php
/**
 * @brief Tools as client bots specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientBots/Tools.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.21
 * @date Creation: May 2018
 * @date Modification: Jul 2019
 * @copyright 2018 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return given known web tool list.
 * @return array
 * @private
 */
function _client_getKnownTools() {
    $knownTools = array();

    /* w3c validator */
    $knownTools['w3c_validator'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'W3C Validator',
        'tool_url'          => 'http://validator.w3.org',
        'engine_title'      => 'World Wide Web Consortium',
        'engine_url'        => 'http://www.w3.org',
    );

    /* Validator.nu/LV */
    $knownTools['validator.nu/lv'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'validator.nu',
        'tool_url'          => 'http://validator.nu',
        'engine_title'      => 'World Wide Web Consortium',
        'engine_url'        => 'http://validator.w3.org/services',
    );

    /* google translation */
    $knownTools['translate.google.com'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Google Translation',
        'tool_url'          => 'http://translate.google.com/',
        'engine_title'      => 'Google',
        'engine_url'        => 'http://www.google.com',
    );

    /* google translation */
    $knownTools['google wireless transcoder'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Google Wireless Transcoder',
        'tool_url'          => '',
        'engine_title'      => 'Google',
        'engine_url'        => 'http://www.google.com',
    );

    /* google page speed insight mobile */
    $knownTools['google page speed insights) version/6.0 mobile'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'handheld',
        'tool_title'        => 'Google Page Speed Insights (Mobile)',
        'tool_url'          => 'https://developers.google.com/speed/pagespeed/insights/',
        'engine_title'      => 'Google',
        'engine_url'        => 'http://www.google.com',
    );

    /* google page speed insight */
    $knownTools['google page speed insights'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Google Page Speed Insights',
        'tool_url'          => 'https://developers.google.com/speed/pagespeed/insights/',
        'engine_title'      => 'Google',
        'engine_url'        => 'http://www.google.com',
    );

    /* Google Feedfetcher */
    $knownTools['feedfetcher-google'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Google Feedfetcher',
        'tool_url'          => 'http://www.google.com/feedfetcher.html',
        'engine_title'      => 'Google',
        'engine_url'        => 'http://www.google.com',
    );

    /* Google Google-Youtube-Links */
    $knownTools['google-youtube-links'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Google-Youtube-Links',
        'tool_url'          => '',
        'engine_title'      => 'Google',
        'engine_url'        => 'http://www.google.com',
    );

    /* yahoo translation : babel fish */
    $knownTools['babelfish.yahoo.com'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Babel Fish',
        'tool_url'          => 'http://babelfish.yahoo.com',
        'engine_title'      => 'Yahoo',
        'engine_url'        => 'http://www.yahoo.com',
    );

    /* Yahoo Link Preview */
    $knownTools['yahoo link preview'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Yahoo Link Preview',
        'tool_url'          => 'https://help.yahoo.com/kb/mail/yahoo-link-preview-SLN23615.html',
        'engine_title'      => 'Yahoo',
        'engine_url'        => 'http://www.yahoo.com',
    );

    /* facebook external hit */
    $knownTools['facebookexternalhit'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Facebook',
        'tool_url'          => 'http://www.facebook.com/externalhit_uatext.php',
        'engine_title'      => 'Facebook',
        'engine_url'        => 'http://www.facebook.com',
    );

    /* facebook share follower */
    $knownTools['facebook share follower'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Facebook',
        'tool_url'          => '',
        'engine_title'      => 'Facebook',
        'engine_url'        => 'http://www.facebook.com',
    );

    /* tumblr */
    $knownTools['tumblr'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => '',
        'tool_url'          => '',
        'engine_title'      => 'Tumblr',
        'engine_url'        => 'https://www.tumblr.com',
    );

    /* builtwith engine */
    $knownTools['builtwith.com'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'BuiltWith',
        'tool_url'          => 'http://builtwith.com/tool.html',
        'engine_title'      => 'Builtwith',
        'engine_url'        => 'http://builtwith.com',
    );

    /* bloglines */
    $knownTools['bloglines'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'BlogLines',
        'tool_url'          => 'http://www.bloglines.com',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* Acrobat Capture */
    $knownTools['webcapture'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'WebCapture',
        'tool_url'          => '',
        'engine_title'      => 'Adobe Acrobat Capture',
        'engine_url'        => '',
    );

    /* vBSEO */
    $knownTools['vbseo'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'vBSEO',
        'tool_url'          => 'http://www.vbseo.com',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* WebmasterCoffee */
    $knownTools['webmastercoffee'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'WebmasterCoffee',
        'tool_url'          => 'http://webmastercoffee.com/about',
        'engine_title'      => 'WebmasterCoffee',
        'engine_url'        => 'http://webmastercoffee.com',
    );

    /* Embed.ly */
    $knownTools['embed.ly'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'embed.ly',
        'tool_url'          => '',
        'engine_title'      => 'embed.ly',
        'engine_url'        => 'http://embed.ly/',
    );

    /* Tweetmeme */
    $knownTools['tweetmemebot'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'TweetmemeBot',
        'tool_url'          => '',
        'engine_title'      => 'Tweetmeme',
        'engine_url'        => 'http://tweetmeme.com/',
    );

    /* LinkedIn Bot */
    $knownTools['linkedinbot'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'LinkedInBot',
        'tool_url'          => '',
        'engine_title'      => 'LinkedIn',
        'engine_url'        => 'http://www.linkedin.com/',
    );

    /* Xenu Link Sleuth */
    $knownTools['xenu link sleuth'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Xenu Link Sleuth',
        'tool_url'          => 'http://home.snafu.de/tilman/xenulink.html',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* MSIECrawler */
    $knownTools['msiecrawler'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'MSIECrawler',
        'tool_url'          => '',
        'engine_title'      => 'Microsoft',
        'engine_url'        => 'http://www.microsoft.com',
    );

    /* Microsoft Office Protocol Discovery    */
    $knownTools['microsoft office protocol discovery'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Microsoft Office Protocol Discovery',
        'tool_url'          => '',
        'engine_title'      => 'Microsoft',
        'engine_url'        => 'http://www.microsoft.com',
    );

    /* HTTrack */
    $knownTools['httrack'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => '',
        'tool_url'          => '',
        'engine_title'      => 'HTTrack',
        'engine_url'        => 'https://www.httrack.com',
    );

    /* powermarks */
    $knownTools['powermarks'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Powermarks',
        'tool_url'          => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* WeChatShareExtension, before CFNetwork */
    $knownTools['wechatshareextension'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'WeChat Share Extension',
        'tool_url'          => 'https://www.wechat.com',
        'engine_title'      => 'Tencent Holdings',
        'engine_url'        => 'https://www.tencent.com/en-us/',
    );

    /* wkhtmltoimage */
    $knownTools['wkhtmltoimage'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'wkhtmltoimage',
        'tool_url'          => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* khtml2png */
    $knownTools['khtml2png'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'khtml2png',
        'tool_url'          => 'https://github.com/xsuchy/khtml2png',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* CasperJS */
    $knownTools['casperjs'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'CasperJS',
        'tool_url'          => 'http://casperjs.org',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* PhantomJS */
    $knownTools['phantomjs'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'PhantomJS',
        'tool_url'          => 'http://phantomjs.org',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* SlimerJS */
    $knownTools['slimerjs'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'SlimerJS',
        'tool_url'          => 'http://slimerjs.org',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* S.N.O.W. */
    $knownTools['s.n.o.w.'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'S.N.O.W.',
        'tool_url'          => 'http://www.trilibis.com/snow.jsp',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* Scrutiny */
    $knownTools['scrutiny'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Scrutiny',
        'tool_url'          => 'http://peacockmedia.software',
        'engine_title'      => 'PeacockMedia',
        'engine_url'        => 'http://peacockmedia.software/mac/scrutiny/',
    );

    /* Pagespeed */
    $knownTools['pagespeed.de'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Pagespeed',
        'tool_url'          => 'http://www.pagespeed.de',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* Screaming Frog SEO Spider */
    $knownTools['screaming frog seo spider'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Screaming Frog SEO Spider',
        'tool_url'          => 'http://www.screamingfrog.co.uk/seo-spider/',
        'engine_title'      => 'Screaming Frog',
        'engine_url'        => 'http://www.screamingfrog',
    );

    /* Bot.AraTurka.com */
    $knownTools['bot.araturka.com'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Bot.AraTurka.com',
        'tool_url'          => '',
        'engine_title'      => 'AraTurka',
        'engine_url'        => 'http://www.araturka.com/index.php',
    );

    /* crawler4j */
    $knownTools['crawler4j'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'crawler4j',
        'tool_url'          => 'https://code.google.com/p/crawler4j/',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* Zend_Http_Client */
    $knownTools['zend_http_client'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Zend_Http_Client',
        'tool_url'          => 'http://framework.zend.com/manual/1.12/en/zend.http.client.advanced.html',
        'engine_title'      => 'Zend',
        'engine_url'        => 'http://www.zend.com',
    );

    /* GetRequest */
    $knownTools['getrequest'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'GetRequest',
        'tool_url'          => 'http://www.getrequest.net',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* CrazyWebCrawler */
    $knownTools['crazywebcrawler'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'CrazyWebCrawler',
        'tool_url'          => 'http://www.crazywebcrawler.com',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* AppEngine-Google */
    $knownTools['appengine-google'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'AppEngine-Google',
        'tool_url'          => 'http://code.google.com/appengine',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* WSCheck */
    $knownTools['wscheck'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'wscheck',
        'tool_url'          => '',
        'engine_title'      => 'WSCheck',
        'engine_url'        => 'http://wscheck.com',
    );

    /* MRA */
    $knownTools[' mra '] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Mail.ru downloader',
        'tool_url'          => '',
        'engine_title'      => 'Mail.ru',
        'engine_url'        => 'http://mail.ru',
    );

    /* DowntimeDetector */
    $knownTools['downtimedetector'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'DowntimeDetector',
        'tool_url'          => 'http://downforeveryoneorjustme.com',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* LinkedInBot */
    $knownTools['linkedinbot'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'LinkedInBot',
        'tool_url'          => '',
        'engine_title'      => 'LinkedIn',
        'engine_url'        => 'http://www.linkedin.com',
    );

    /* XML-Sitemaps */
    $knownTools['xml-sitemaps'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => '',
        'tool_url'          => '',
        'engine_title'      => 'XML-Sitemaps',
        'engine_url'        => 'https://www.xml-sitemaps.com',
    );

    /* GTmetrix */
    $knownTools['gtmetrix'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => '',
        'tool_url'          => '',
        'engine_title'      => 'GTmetrix',
        'engine_url'        => 'https://gtmetrix.com',
    );

    /* splash */
    $knownTools['splash safari'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => '',
        'tool_url'          => '',
        'engine_title'      => 'Splash',
        'engine_url'        => 'https://github.com/scrapinghub/splash',
    );

    /* Spider-Pig by Tinfoil security */
    $knownTools['spider-pig'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Spider-Pig',
        'tool_url'          => '',
        'engine_title'      => 'Tinfoil security',
        'engine_url'        => 'https://tinfoilsecurity.com/',
    );

    /* W3C-checklink */
    $knownTools['w3c-checklink'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'W3C-checklink',
        'tool_url'          => 'https://validator.w3.org/checklink',
        'engine_title'      => 'World Wide Web Consortium',
        'engine_url'        => 'https://www.w3.org',
    );

    /* Wappalyzer */
    $knownTools['wappalyzer'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Wappalyzer',
        'tool_url'          => 'https://github.com/AliasIO/Wappalyzer',
        'engine_title'      => 'Wappalyzer',
        'engine_url'        => 'https://wappalyzer.com',
    );

    /* CakePHP */
    $knownTools['cakephp'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'CakePHP',
        'tool_url'          => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* MetaInspector */
    $knownTools['metainspector'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'MetaInspector',
        'tool_url'          => 'https://github.com/jaimeiniesta/metainspector',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* PerfectMail */
    $knownTools['perfectmail'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'PerfectMail WebProbe',
        'tool_url'          => 'http://perfectmail.com/kb/web_probe',
        'engine_title'      => 'PerfectMail',
        'engine_url'        => 'http://perfectmail.com',
    );

    /* SiteTruth.com */
    $knownTools['sitetruth.com'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => '',
        'tool_url'          => '',
        'engine_title'      => 'SiteTruth.com',
        'engine_url'        => 'http://SiteTruth.com',
    );

    /* SalesIntelligent */
    $knownTools['salesintelligent'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => '',
        'tool_url'          => '',
        'engine_title'      => 'SalesIntelligent',
        'engine_url'        => 'http://SalesIntelligent.com',
    );

    /* SSL Labs */
    $knownTools['ssl labs'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'SSL Labs',
        'tool_url'          => 'https://www.ssllabs.com/ssltest',
        'engine_title'      => 'Qualys',
        'engine_url'        => 'https://www.ssllabs.com/index.html',
    );

    /* woobot */
    $knownTools['woobot'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'woobot',
        'tool_url'          => '',
        'engine_title'      => 'Woorank',
        'engine_url'        => 'https://www.woorank.com',
    );

    /* internetVista monitor */
    $knownTools['internetvista monitor'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'internetVista monitor',
        'tool_url'          => '',
        'engine_title'      => 'internetVista',
        'engine_url'        => 'http://www.internetvista.com',
    );

    /* Contacts Crawler - is maybe a bot */
    $knownTools['contacts crawler'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Contacts Crawler',
        'tool_url'          => '',
        'engine_title'      => 'Scrapinghub',
        'engine_url'        => 'http://scrapinghub.com',
    );

    /* Seoterritory.com - is maybe a bot */
    $knownTools['seoterritory.com'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Seoterritory.com',
        'tool_url'          => 'http://www.seoterritory.com',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* Spatineo */
    $knownTools['spatineo'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Spatineo Monitor Controller',
        'tool_url'          => 'http://www.spatineo.com/spatineo-monitor/',
        'engine_title'      => 'Spatineo',
        'engine_url'        => 'http://www.spatineo.com',
    );

    /* Spatineo */
    $knownTools['spatineo'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Spatineo Monitor Controller',
        'tool_url'          => 'http://www.spatineo.com/spatineo-monitor/',
        'engine_title'      => 'Spatineo',
        'engine_url'        => 'http://www.spatineo.com',
    );

    /* Integrity */
    $knownTools['integrity'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Integrity',
        'tool_url'          => 'http://peacockmedia.software/mac/integrity/free.html',
        'engine_title'      => 'PeacockMedia',
        'engine_url'        => 'http://peacockmedia.software',
    );

    /* UniversalFeedParser */
    $knownTools['universalfeedparser'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'UniversalFeedParser',
        'tool_url'          => '',
        'engine_title'      => 'FeedParser',
        'engine_url'        => 'http://feedparser.org',
    );

    /* FreeWebMonitoring SiteChecker */
    $knownTools['freewebmonitoring sitechecker'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'FreeWebMonitoring SiteChecker',
        'tool_url'          => '',
        'engine_title'      => 'FreeWebMonitoring SiteChecker',
        'engine_url'        => 'http://www.freewebmonitoring.com',
    );

    /* SkypeUriPreview */
    $knownTools['skypeuripreview'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'SkypeUriPreview',
        'tool_url'          => '',
        'engine_title'      => 'Skype',
        'engine_url'        => 'https://www.skype.com',
    );

    /* BrokenLinkCheck.com */
    $knownTools['brokenlinkcheck.com'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => '',
        'tool_url'          => '',
        'engine_title'      => 'Broken Link Check',
        'engine_url'        => 'http://BrokenLinkCheck.com',
    );

    /* OpenStat */
    $knownTools['openstat'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => '',
        'tool_url'          => '',
        'engine_title'      => 'OpenStat',
        'engine_url'        => 'https://www.openstat.com',
    );

    /* Iframely */
    $knownTools['iframely'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => '',
        'tool_url'          => '',
        'engine_title'      => 'Iframely',
        'engine_url'        => 'https://iframely.com',
    );

    /* Link Examiner */
    $knownTools['linkexaminer'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'LinkExaminer',
        'tool_url'          => 'http://www.analogx.com/contents/download/network/lnkexam/freeware.htm',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* Link Saver */
    $knownTools['linksaver'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'LinkSaver',
        'tool_url'          => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* Link Saver */
    $knownTools['linkparser'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'LinkParser',
        'tool_url'          => 'http://www.seerobots.com/linkparser',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* HEADMasterSEO */
    $knownTools['headmasterseo'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'HEADMasterSEO',
        'tool_url'          => 'https://headmasterseo.com',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* BuiltWith */
    $knownTools['builtwith'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => '',
        'tool_url'          => '',
        'engine_title'      => 'BuiltWith',
        'engine_url'        => 'https://builtwith.com',
    );

    /* BlueCoat ProxySG */
    $knownTools['bluecoat proxysg'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'BlueCoat ProxySG ',
        'tool_url'          => '',
        'engine_title'      => 'BlueCoat',
        'engine_url'        => 'https://bluecoat.com',
    );

    /* Flipboard */
    $knownTools['flipboard'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Flipboard Proxy',
        'tool_url'          => 'http://flipboard.com/browserproxy',
        'engine_title'      => 'Flipboard',
        'engine_url'        => 'http://flipboard.com',
    );

    /* LinkCheck by Siteimprove.com */
    $knownTools['linkcheck by siteimprove.com'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'LinkCheck',
        'tool_url'          => '',
        'engine_title'      => 'Siteimprove.com',
        'engine_url'        => 'https://siteimprove.com',
    );

    /* Match by Siteimprove.com */
    $knownTools['match by siteimprove.com'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Match',
        'tool_url'          => '',
        'engine_title'      => 'Siteimprove.com',
        'engine_url'        => 'https://siteimprove.com',
    );

    /* webscreenie */
    $knownTools['webscreenie'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'webscreenie',
        'tool_url'          => 'https://www.openhub.net/p/webscreenie',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* JOC Web Spider */
    $knownTools['joc web spider'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'JOC Web Spider',
        'tool_url'          => '',
        'engine_title'      => 'Jocsoft',
        'engine_url'        => 'http://www.jocsoft.com/jws/',
    );

    /* WhatWeb */
    $knownTools['whatweb'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => '',
        'tool_url'          => '',
        'engine_title'      => 'WhatWeb',
        'engine_url'        => 'https://www.morningstarsecurity.com/research/whatweb',
    );

    /* SBL-BOT */
    $knownTools['sbl-bot'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'SBL-BOT',
        'tool_url'          => '',
        'engine_title'      => 'SoftByte Labs',
        'engine_url'        => 'http://sbl.net',
    );

    /* Chrome-Lighthouse */
    $knownTools['chrome-lighthouse'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Chrome-Lighthouse',
        'tool_url'          => 'https://github.com/GoogleChrome/lighthouse',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* Google-AMPHTML */
    $knownTools['google-amphtml'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Google-AMPHTML',
        'tool_url'          => 'https://www.ampproject.org',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* SiteWinder */
    $knownTools['sitewinder'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'SiteWinder',
        'tool_url'          => '',
        'engine_title'      => 'Web washer',
        'engine_url'        => 'https://www.mcafee.com',
    );

    /* Optimizer */
    $knownTools['optimizer'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Optimizer',
        'tool_url'          => '',
        'engine_title'      => 'Sistrix',
        'engine_url'        => 'https://www.sistrix.com',
    );

    /* evc-batch */
    $knownTools['evc-batch'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'evc-batch',
        'tool_url'          => '',
        'engine_title'      => 'eVenture Capital Partners II, LLC',
        'engine_url'        => 'http://www.eventures.vc/',
    );

    /* Nmap Scripting Engine */
    $knownTools['nmap scripting engine'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Nmap Scripting Engine',
        'tool_url'          => 'https://nmap.org/book/nse.html',
        'engine_title'      => 'NMAP',
        'engine_url'        => 'https://nmap.org/',
    );

    /* Outiref */
    $knownTools['outiref'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => '',
        'tool_url'          => '',
        'engine_title'      => 'Outiref',
        'engine_url'        => 'https://www.outiref.fr/',
    );

    /* alyze.info */
    $knownTools['alyze.info'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => '',
        'tool_url'          => '',
        'engine_title'      => 'alyze',
        'engine_url'        => 'https://alyze.info/',
    );

    /* DareBoost */
    $knownTools['dareboost'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => '',
        'tool_url'          => '',
        'engine_title'      => 'DareBoost',
        'engine_url'        => 'https://www.dareboost.com/',
    );

    /* WebZIP */
    $knownTools['webzip'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'WebZIP',
        'tool_url'          => '',
        'engine_title'      => 'SpiderSoft',
        'engine_url'        => 'http://www.spidersoft.com',
    );

    /* Newspaper */
    $knownTools['newspaper'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Newspaper',
        'tool_url'          => 'https://github.com/codelucas/newspaper',
        'engine_title'      => 'Lucas Lee Ou-Yang',
        'engine_url'        => 'https://codelucas.com',
    );

    /* eZ Publish Link Validator  */
    $knownTools['ez publish link validator'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'eZ Publish Link Validator',
        'tool_url'          => '',
        'engine_title'      => 'eZ Publish',
        'engine_url'        => 'https://ez.no',
    );

    /* AppleSyndication  */
    $knownTools['applesyndication'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Apple Syndication (RSS Reader)',
        'tool_url'          => '',
        'engine_title'      => 'Apple',
        'engine_url'        => 'https://www.apple.com',
    );

    /* HTTPing  */
    $knownTools['httping'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'HTTPing',
        'tool_url'          => 'https://www.vanheusden.com/httping/',
        'engine_title'      => 'vanheusden.com',
        'engine_url'        => 'https://www.vanheusden.com',
    );

    /* PocketParser  */
    $knownTools['pocketparser'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'PocketParser',
        'tool_url'          => 'https://getpocket.com/pocketparser_ua',
        'engine_title'      => 'Pocket',
        'engine_url'        => 'https://getpocket.com',
    );

    /* DemandbasePublisherAnalyzer  */
    $knownTools['demandbasepublisheranalyzer'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'DemandbasePublisherAnalyzer',
        'tool_url'          => '',
        'engine_title'      => 'DemandeBase',
        'engine_url'        => 'https://www.demandbase.com',
    );

    /* MagpieRSS  */
    $knownTools['magpierss'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => '',
        'tool_url'          => '',
        'engine_title'      => 'MagpieRSS',
        'engine_url'        => 'http://magpierss.sf.net',
    );

    /* Re-re Studio */
    $knownTools['re-re studio'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => '',
        'tool_url'          => '',
        'engine_title'      => 'Re-re Studio',
        'engine_url'        => 'http://re-re.ru/',
    );

    /* InetURL */
    $knownTools['ineturl'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'InetURL',
        'tool_url'          => '',
        'engine_title'      => 'IVM',
        'engine_url'        => 'https://www.nch.com.au/ivm/plugins.html',
    );

    /* htmlyse */
    $knownTools['htmlyse'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => '',
        'tool_url'          => '',
        'engine_title'      => 'htmlyse',
        'engine_url'        => 'https://www.htmlyse.com/',
    );

    /* Mr.4x3 Powered */
    $knownTools['mr.4x3 powered'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Mr.4x3 Powered',
        'tool_url'          => '',
        'engine_title'      => 'CrushUs.com',
        'engine_url'        => 'https://crushus.com',
    );

    /* Goose */
    $knownTools['goose'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => '',
        'tool_url'          => '',
        'engine_title'      => 'Goose',
        'engine_url'        => 'https://pypi.org/project/goose3/',
    );

    /* Slackbot-LinkExpanding */
    $knownTools['slackbot-linkexpanding'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Slackbot-LinkExpanding',
        'tool_url'          => 'https://api.slack.com/robots',
        'engine_title'      => 'Slack',
        'engine_url'        => 'https://slack.com/',
    );

    /* Siteliner */
    $knownTools['siteliner'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Siteliner bot',
        'tool_url'          => 'http://www.siteliner.com/bot',
        'engine_title'      => 'Siteliner',
        'engine_url'        => 'http://www.siteliner.com',
    );

    /* Discordbot */
    $knownTools['discordbot'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Discordbot',
        'tool_url'          => '',
        'engine_title'      => 'Discord',
        'engine_url'        => 'https://discordapp.com',
    );

    /* Google + snippet */
    $knownTools['+https://developers.google.com/+/web/snippet/'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Google + preview/snippet',
        'tool_url'          => '',
        'engine_title'      => 'Google',
        'engine_url'        => 'https://www.google.com',
    );

    /* DownUpTime */
    $knownTools['konqueror/4.0; microsoft windows) khtml/4.0.80'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => '',
        'tool_url'          => '',
        'engine_title'      => 'DownUpTime',
        'engine_url'        => 'https://downuptime.net',
    );

    /* Let's Encrypt validation server */
    $knownTools['let\'s encrypt validation server'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => '',
        'tool_url'          => '',
        'engine_title'      => 'Let\'s Encrypt',
        'engine_url'        => 'https://letsencrypt.org',
    );

    /* XenForo */
    $knownTools['xenforo'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => '',
        'tool_url'          => '',
        'engine_title'      => 'XenForo',
        'engine_url'        => 'https://xenforo.com',
    );

    /* Site-Shot */
    $knownTools['site-shot'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => '',
        'tool_url'          => '',
        'engine_title'      => 'Site-Shot',
        'engine_url'        => 'https://www.site-shot.com',
    );

    /* CloudFlare-AlwaysOnline */
    $knownTools['cloudflare-alwaysonline'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Cloud Flare Always Online',
        'tool_url'          => 'https://www.cloudflare.com/always-online/',
        'engine_title'      => 'Cloud Flare',
        'engine_url'        => 'https://www.cloudflare.com/',
    );

    /* Miniature.io */
    $knownTools['miniature.io'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => '',
        'tool_url'          => '',
        'engine_title'      => 'Miniature.io',
        'engine_url'        => 'https://miniature.io/',
    );

    /* Scamadviser-Frontend */
    $knownTools['scamadviser-frontend'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Scamadviser-Frontend',
        'tool_url'          => '',
        'engine_title'      => 'Scamadviser',
        'engine_url'        => 'https://www.scamadviser.com/',
    );

    /* PTST */
    $knownTools['ptst'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'SpeedCurve Speed Tester',
        'tool_url'          => '',
        'engine_title'      => 'SpeedCurve',
        'engine_url'        => 'https://speedcurve.com/',
    );

    /* Slackbot-LinkExpanding */
    $knownTools['slackbot-linkexpanding'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Slackbot LinkExpanding',
        'tool_url'          => 'https://api.slack.com/robots',
        'engine_title'      => 'Slack',
        'engine_url'        => 'https://slack.com/',
    );

    /* Slackbot-LinkExpanding */
    $knownTools['slackbot-linkexpanding'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Slackbot LinkExpanding',
        'tool_url'          => 'https://api.slack.com/robots',
        'engine_title'      => 'Slack',
        'engine_url'        => 'https://slack.com/',
    );

    /* Slack-ImgProxy */
    $knownTools['slack-imgproxy'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Slackbot ImgProxy',
        'tool_url'          => 'https://api.slack.com/robots',
        'engine_title'      => 'Slack',
        'engine_url'        => 'https://slack.com/',
    );

    /* Slackbot */
    $knownTools['slackbot'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Slackbot',
        'tool_url'          => 'https://api.slack.com/robots',
        'engine_title'      => 'Slack',
        'engine_url'        => 'https://slack.com/',
    );

    /* Cocolyzebot */
    $knownTools['cocolyzebot'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Cocolyzebot',
        'tool_url'          => 'https://cocolyze.com/bot',
        'engine_title'      => 'Cocolyze',
        'engine_url'        => 'https://cocolyze.com/',
    );

    /* return list */
    return $knownTools;
}
?>
