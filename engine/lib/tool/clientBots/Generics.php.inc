<?php
/**
 * @brief Generic libraries as client bots specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.29.1
 * @date Creation: May 2018
 * @date Modification: Jun 2022
 * @copyright 2018 - 2022 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return given known web generic library or generic library list.
 * @return array
 * @private
 */
function _client_getKnownGenericsL1() {
    $knownGenerics = array();

    /* Mechanize - before Ruby */
    $knownGenerics['mechanize'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Mechanize',
        'tool_url'          => 'http://github.com/sparklemotion/mechanize/',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* MechanicalSoup - before python request */
    $knownGenerics['mechanicalsoup'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'MechanicalSoup',
        'tool_url'          => 'https://mechanicalsoup.readthedocs.io/en/stable/',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* return list */
    return $knownGenerics;
}

/**
 * Return given known web generic library or generic library list.
 * @return array
 * @private
 */
function _client_getKnownGenericsL2() {
    $knownGenerics = array();

    /* CaMykS */
    $knownGenerics['camyksrequest'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'CaMykSRequest',
        'bot_url'           => 'https://www.camyks.net/request_bot.html',
        'engine_title'      => 'CaMykS',
        'engine_url'        => 'https://www.camyks.net',
    );

    /* NING */
    $knownGenerics['ning/1'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'NING',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* heritrix */
    $knownGenerics['heritrix'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'heritrix',
        'bot_url'           => 'https://webarchive.jira.com/wiki/display/Heritrix',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* Nutch */
    $knownGenerics['nutch'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Nutch',
        'bot_url'           => 'http://nutch.apache.org',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* Voltron */
    $knownGenerics['voltron'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Voltron',
        'bot_url'           => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* Scrapy */
    $knownGenerics['scrapy'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'Scrapy',
        'bot_url'           => '',
        'engine_title'      => 'Scrapy.org',
        'engine_url'        => 'http://scrapy.org',
    );

    /* WWW-Mechanize */
    $knownBots['www-mechanize'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'WWW-Mechanize',
        'tool_url'          => '',
        'engine_title'      => 'CPAN',
        'engine_url'        => 'http://search.cpan.org/~ether/',
    );

    /* Fetcher */
    $knownBots['compatible; fetcher/'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Fetcher',
        'tool_url'          => '',
        'engine_title'      => 'Apple',
        'engine_url'        => 'http://www.apple.com',
    );

    /* Pcore-HTTP    */
    $knownGenerics['pcore-http'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Pcore-HTTP',
        'tool_url'          => 'http://search.cpan.org/dist/Pcore/lib/Pcore/HTTP.pm',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* Wget linux library */
    $knownGenerics['wget'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'WGet',
        'tool_url'          => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* gettor */
    $knownGenerics['gettor'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'gettor',
        'tool_url'          => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* Python library */
    $knownGenerics['python-urllib'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Python Library',
        'tool_url'          => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* Python Request library */
    $knownGenerics['python-requests'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Python Request Library',
        'tool_url'          => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* Apache-HttpClient library (before Java) */
    $knownGenerics['apache-httpclient'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Apache-HttpClient',
        'tool_url'          => '',
        'engine_title'      => 'Apache Software Foundation',
        'engine_url'        => 'https://hc.apache.org',
    );

    /* Apache-HttpAsyncClient library (before Java) */
    $knownGenerics['apache-httpasyncclient'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Apache-HttpAsyncClient',
        'tool_url'          => '',
        'engine_title'      => 'Apache Software Foundation',
        'engine_url'        => 'https://hc.apache.org',
    );

    /* AHC */
    $knownGenerics['ahc/'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'AHC',
        'tool_url'          => '',
        'engine_title'      => 'AsyncHttpClient',
        'engine_url'        => 'https://github.com/AsyncHttpClient/async-http-client',
    );

    /* Apache synapse library (before Synapse) */
    $knownGenerics['synapse-httpcomponent'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Apache Synapse',
        'tool_url'          => '',
        'engine_title'      => 'Apache Software Foundation',
        'engine_url'        => 'https://hc.apache.org',
    );

    /* Jakarta Commons-HttpClient */
    $knownGenerics['jakarta commons-httpclient'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Jakarta Commons-HttpClient',
        'tool_url'          => 'http://hc.apache.org/httpclient-3.x/',
        'engine_title'      => 'Apache Software Foundation',
        'engine_url'        => 'https://hc.apache.org',
    );

    /* Ararat Synapse */
    $knownGenerics['synapse'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => '',
        'tool_url'          => '',
        'engine_title'      => 'Ararat Synapse',
        'engine_url'        => 'http://synapse.ararat.cz/doku.php',
    );

    /* unirest-java library */
    $knownGenerics['unirest-java/'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Unirest Java Library',
        'tool_url'          => 'http://kong.github.io/unirest-java/',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* java library */
    $knownGenerics['java/'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Java Library',
        'tool_url'          => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* Perl library */
    $knownGenerics['libwww-perl'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'PERL Library',
        'tool_url'          => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* WinHttpRequest */
    $knownGenerics['winhttp'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'WinHttpRequest',
        'tool_url'          => 'https://msdn.microsoft.com/en-us/library/windows/desktop/aa382925(v=vs.85).aspx',
        'engine_title'      => 'Microsoft',
        'engine_url'        => '',
    );

    /* rest-client - before Ruby */
    $knownGenerics['rest-client'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'rest-client Library',
        'tool_url'          => 'https://github.com/rest-client/rest-client',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* Ruby */
    $knownGenerics['ruby'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Ruby Library',
        'tool_url'          => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* GuzzleHttp (before curl) */
    $knownGenerics['guzzle'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'GuzzleHttp Library',
        'tool_url'          => 'http://docs.guzzlephp.org/en/latest/',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* PHP-Curl-Class (before PHP and Curl) */
    $knownGenerics['php-curl-class'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'PHP-Curl-Class Library',
        'tool_url'          => 'https://github.com/php-curl-class/php-curl-class',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* cURL */
    $knownGenerics['libcurl'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'cURL Library',
        'tool_url'          => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* cURL */
    $knownGenerics['curl/'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'cURL Library',
        'tool_url'          => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* pycurl */
    $knownGenerics['pycurl'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'pycurl',
        'tool_url'          => 'http://pycurl.io',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* PHP */
    $knownGenerics['php/5'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'PHP Library',
        'tool_url'          => 'http://www.php.net',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* Go-http-client */
    $knownGenerics['go-http-client'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Go Language Library',
        'tool_url'          => 'https://golang.org/pkg/net/http/',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* Typhoeus */
    $knownGenerics['typhoeus'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Typhoeus',
        'tool_url'          => 'https://github.com/typhoeus/typhoeus',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* Chilkat */
    $knownGenerics['chilkat'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Chilkat',
        'tool_url'          => 'http://www.chilkatsoft.com/ChilkatHttpUA.asp',
        'engine_title'      => 'Chilkat Software',
        'engine_url'        => 'http://www.chilkatsoft.com',
    );

    /* SEOstats */
    $knownGenerics['seostats'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'SEOstats',
        'tool_url'          => 'https://github.com/eyecatchup/SEOstats',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* MLIB_NetWorkLibrary */
    $knownGenerics['mlib_networklibrary'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'MLIB_NetWorkLibrary',
        'tool_url'          => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* MLIB_NetWorkBot */
    $knownGenerics['mlib_networkbot'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'MLIB_NetWorkBot',
        'tool_url'          => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* Mojolicious */
    $knownGenerics['mojolicious'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => '',
        'tool_url'          => '',
        'engine_title'      => 'Mojolicious',
        'engine_url'        => 'http://mojolicious.org',
    );

    /* httpunit */
    $knownGenerics['httpunit'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'httpunit',
        'tool_url'          => 'http://httpunit.sourceforge.net',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* aria2 */
    $knownGenerics['aria2'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'aria2',
        'tool_url'          => 'https://sourceforge.net/projects/aria2/',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* Google-Apps-Script */
    $knownGenerics['google-apps-script'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Google-Apps-Script',
        'tool_url'          => '',
        'engine_title'      => 'Google Apps Script',
        'engine_url'        => 'https://www.google.com/script/start/',
    );

    /* zgrab */
    $knownGenerics['zgrab'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'zgrab',
        'tool_url'          => 'https://github.com/zmap/zgrab/blob/master/zlib/conn.go',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* Dispatch */
    $knownGenerics['dispatch'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Dispatch',
        'tool_url'          => 'https://github.com/dispatch/reboot',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* Jersey */
    $knownGenerics['jersey'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Jersey',
        'tool_url'          => 'https://jersey.github.io',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* aiohttp */
    $knownGenerics['aiohttp'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'aiohttp',
        'tool_url'          => 'https://pypi.python.org/pypi/aiohttp',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* okhttp */
    $knownGenerics['okhttp'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'okhttp',
        'tool_url'          => 'https://github.com/square/okhttp',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* MS Web Services Client Protocol */
    $knownGenerics['ms web services client protocol'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'MS Web Services Client Protocol (.NET)',
        'tool_url'          => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* Faraday */
    $knownGenerics['faraday'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Faraday',
        'tool_url'          => 'https://mislav.net/2011/07/faraday-advanced-http/',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* Indy Library */
    $knownGenerics['indy library'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Indy Library',
        'tool_url'          => 'http://www.indyproject.org/index.en.aspx',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* AnyEvent-HTTP */
    $knownGenerics['anyevent-http'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'AnyEvent-HTTP',
        'tool_url'          => 'http://software.schmorp.de/pkg/AnyEvent-HTTP.html',
        'engine_title'      => 'Schmorpforge Software',
        'engine_url'        => 'http://software.schmorp.de',
    );

    /* Splashr */
    $knownGenerics['splash'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'splash',
        'tool_url'          => 'https://cran.r-project.org/web/packages/splashr/vignettes/intro_to_splashr.html',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* .NET Framework Test Client    */
    $knownGenerics['.net framework'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Microsoft .NET Framework',
        'tool_url'          => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* scalaj-http    */
    $knownGenerics['scalaj-http'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'scalaj-http',
        'tool_url'          => 'https://github.com/scalaj/scalaj-http',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* zombie.js */
    $knownGenerics['zombie.js'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Zombie',
        'tool_url'          => '',
        'engine_title'      => 'Zombie.js',
        'engine_url'        => 'http://zombie.js.org',
    );

    /* axios */
    $knownGenerics['axios'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'axios',
        'tool_url'          => 'https://libraries.io/npm/axios',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* jsoup */
    $knownGenerics['jsoup'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'jsoup',
        'tool_url'          => 'http://static.javadoc.io/org.jsoup/jsoup/1.8.1/org/jsoup/helper/HttpConnection.html',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* lua-resty-http */
    $knownGenerics['ua-resty-http'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'ua-resty-http Library',
        'tool_url'          => 'https://github.com/pintsized/lua-resty-http',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* photon */
    $knownGenerics['photon'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Photon',
        'tool_url'          => 'https://www.distilnetworks.com/bot-directory/bot/photon1-0/',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* raynette_httprequest */
    $knownGenerics['raynette_httprequest'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'raynette_httprequest (Unknown library)',
        'tool_url'          => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* akka-http */
    $knownGenerics['akka-http'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'akka-http',
        'tool_url'          => '',
        'engine_title'      => 'akka',
        'engine_url'        => 'https://akka.io/',
    );

    /* Microsoft URL Control */
    $knownGenerics['microsoft url control'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Microsoft URL Control',
        'tool_url'          => '',
        'engine_title'      => 'Microsoft',
        'engine_url'        => 'https://www.microsoft.com/',
    );

    /* 4D HTTP Client */
    $knownGenerics['4d_http_client'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => '4D HTTP Client',
        'tool_url'          => '',
        'engine_title'      => '4D',
        'engine_url'        => 'http://www.4d.com',
    );

    /* node-fetch */
    $knownGenerics['node-fetch'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'node-fetch',
        'tool_url'          => 'https://github.com/bitinn/node-fetch',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* check_http (nagios plugin) */
    $knownGenerics['check_http'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'check_http',
        'tool_url'          => 'https://nagios-plugins.org/doc/man/check_http.html',
        'engine_title'      => 'Nagios Plugins',
        'engine_url'        => 'https://nagios-plugins.org',
    );

    /* fasthttp */
    $knownGenerics['fasthttp'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'fasthttp',
        'tool_url'          => 'https://github.com/valyala/fasthttp',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* reqwest */
    $knownGenerics['reqwest'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'reqwest',
        'tool_url'          => 'https://docs.rs/reqwest/',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* unfurlist */
    $knownGenerics['unfurlist'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'unfurlist',
        'tool_url'          => 'https://github.com/Doist/unfurlist',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* feedfinder2 */
    $knownGenerics['feedfinder2'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Feedfinder2',
        'tool_url'          => '',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* colly */
    $knownGenerics['colly'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'colly',
        'tool_url'          => 'https://github.com/gocolly/colly',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* OkHttp */
    $knownGenerics['okhttp'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'OkHttp',
        'tool_url'          => 'https://square.github.io/okhttp/',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* Cortex */
    $knownGenerics['cortex'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Cortex',
        'tool_url'          => 'https://github.com/TheHive-Project/Cortex',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* Microsoft WinInet APIs */
    $knownGenerics['test certificate info'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Test Certificate Info',
        'tool_url'          => '',
        'engine_title'      => 'Microsoft WinInet',
        'engine_url'        => 'https://www.microsoft.com',
    );

    /* Web Thumbnailer */
    $knownGenerics['webthumbnailer'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Web Thumbnailer',
        'tool_url'          => 'https://github.com/ArthurHoaro/web-thumbnailer',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* SecuTix Whymper */
    $knownGenerics['secutix whymper_v3'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Whymper V3',
        'tool_url'          => 'https://confluence.secutix.com/pages/viewpage.action?pageId=41779832',
        'engine_title'      => 'SecuTix',
        'engine_url'        => 'https://www.secutix.com',
    );

    /* python-httpx */
    $knownGenerics['python-httpx'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'python-httpx',
        'tool_url'          => 'https://www.python-httpx.org',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* Boost.Beast */
    $knownGenerics['boost.beast'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Boost.Beast',
        'tool_url'          => 'https://github.com/boostorg/beast',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* Go http package */
    $knownGenerics['go http package'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'Go http package',
        'tool_url'          => 'https://golang.org/pkg/net/http/',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* Got */
    $knownGenerics['sindresorhus/got'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'got',
        'tool_url'          => 'https://github.com/sindresorhus/got',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* PostmanRuntime */
    $knownGenerics['postmanruntime'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'PostmanRuntime',
        'tool_url'          => 'https://github.com/postmanlabs/postman-runtime',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* HTMLParser */
    $knownGenerics['htmlparser'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'HTMLParser',
        'tool_url'          => 'https://robot-framework.readthedocs.io/en/v3.0.4/_modules/HTMLParser.html',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* node-fetch */
    $knownGenerics['node-fetch'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'node-fetch',
        'tool_url'          => 'https://github.com/bitinn/node-fetch',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* GRequests */
    $knownGenerics['grequests'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'GRequests',
        'tool_url'          => 'https://pypi.org/project/grequests/',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* http.rb */
    $knownGenerics['http.rb'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'http.rb',
        'tool_url'          => 'https://github.com/httprb/http',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* curb */
    $knownGenerics['curb'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'curb',
        'tool_url'          => 'https://github.com/taf2/curb',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* httpx */
    $knownGenerics['httpx'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'httpx',
        'tool_url'          => 'github.com/projectdiscovery/httpx',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* popsicle */
    $knownGenerics['popsicle'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'popsicle',
        'tool_url'          => 'https://github.com/blakeembrey/popsicle',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* SSLyze */
    $knownGenerics['sslyze'] = array(
        'platform_type'     => 'tool',
        'platform_format'   => 'desktop',
        'tool_title'        => 'SSLyze',
        'tool_url'          => 'https://github.com/nabla-c0d3/sslyze',
        'engine_title'      => '',
        'engine_url'        => '',
    );

    /* obot */
    $knownGenerics[' obot'] = array(
        'platform_type'     => 'bot',
        'platform_format'   => 'desktop',
        'bot_title'         => 'oBot',
        'bot_url'           => 'http://www.xforce-security.com/crawler/',
        'engine_title'      => 'IBM Germany Research & Development GmbH',
        'engine_url'        => '',
    );

    /* return list */
    return $knownGenerics;
}
?>
