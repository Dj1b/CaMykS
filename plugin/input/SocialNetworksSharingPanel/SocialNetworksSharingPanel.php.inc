<?php
/**
 * @brief SocialNetworksSharingPanel Input.
 * <br /> Display social networks sharing and follow links.
 * @details Plugin / Input Engine
 * @file plugin/input/SocialNetworksSharingPanel/SocialNetworksSharingPanel.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Nov 2009
 * @date Modification: Jun 2019
 * @copyright 2009 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * SocialNetworksSharingPanel Input class.
 */
final class SocialNetworksSharingPanel extends Input {

    /**
     * var array $iparams
     * @brief Plugin's internal parameters list.
     */
    protected $iparams = array();

    /**
     * var array $dparams
     * @brief Plugin's display parameters list.
     */
    protected $dparams;

    /**
     * var integer $currentIndex
     * @brief Network list current index.
     */
    var $currentIndex;

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        global $camyks;
        parent::__construct('SocialNetworksSharingPanel', $path_type);

        /* Override Plugin information */
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* Define author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Load networks */
        $this->initialise_networkList();

        /* Load configuration library */
        $this->load_library('SocialNetworksSharingPanelConfig');

        /* Load configuration */
        $this->config = new SocialNetworksSharingPanelConfig('config', $this);
        $this->config->get();

        /* Check for automatic insertion */
        if ($camyks->mode == CAMYKS_MODE_SITE and $this->config->vars['follow_insertion'] == 1) {
            $this->register_asCaMykSEventHandler('onPageLoad');
            $this->register_asCaMykSEventHandler('onBodyClose');
        }

        /* Register plugin as Admin_Site extension */
        $this->register_asExtension('Admin_Site');
    }

    /* Override Input methods */

    /**
     * Initialise input.
     * @param array $params
     * @param string $mode
     * @return void
     */
    public function initialise($params=array(), $mode='share') {
        /* check mode to execute */
        switch ($mode) {
            case 'share': return $this->initialise_sharePanel($params);
            case 'follow': return $this->initialise_followPanel($params);
        }
    }

    /**
     * Display input.
     * @param array $params
     * @param string $mode
     * @return void
     */
    public function display($params=array(), $mode='share') {

        /* check mode to execute */
        switch ($mode) {
            case 'share': $this->display_sharePanel($params); break;
            case 'follow' : $this->display_followPanel($params); break;
        }

        /* generic display */
        parent::display();
    }

    /* Override Plugin methods */

    /**
     * Execute handler on body closing.
     * @return string
     */
    public function execute_onCaMykSPageLoad() {
        $this->initialise(array(), 'follow');
    }

    /**
     * Execute handler on body opening.
     * @return string
     */
    public function execute_onCaMykSBodyOpen() {
        global $languages, $camyks;

        $l = $languages[$camyks->current_language]['locale'][''][0];

        return "<div id=\"fb-root\"></div>\n
                        <script>(function(d, s, id) {\n
                        var js, fjs = d.getElementsByTagName(s)[0];\n
                        if (d.getElementById(id)) return;\n
                        js = d.createElement(s); js.id = id;\n
                        js.src = 'https://connect.facebook.net/".$l."/sdk.js#xfbml=1&version=v2.11';\n
                        fjs.parentNode.insertBefore(js, fjs);\n
                        }(document, 'script', 'facebook-jssdk'));</script>";
    }

    /**
     * Execute handler on body closing.
     * @return string
     */
    public function execute_onCaMykSBodyClose() {
        $this->display(array(), 'follow');
        return '';
    }

    /* Specific initialise mode methods */

    /**
     * Initialise input in share mode.
     * @param array $params
     * @return void
     */
    private function initialise_sharePanel($params) {
        global $camyks;

        /* initialise index */
        $this->currentIndex = 0;

        /* set initial params */
        $this->iparams = array(
            'text'=>'',
            'block_class'       => 'SNSP share',
            'text_class'        => '',
            'separator'         => '&#124;',
            'title'             => '',
            'link'              => '',
            'shortlink'         => '',
            'summary'           => '',
            'image'             => '',
            'type'              => '',
            'sitename'          => $camyks->get_confValue('site_title'),
            'enable_poppanel'   => 1,
            'theme'             => $camyks->get_confValue('site_default_theme'),
            'include_ogmetas'   => 0,
            'networks'          => array(0, 0, 0),
            'locale'            => $camyks->current_language,
        );

        /* merge params */
        $this->iparams = array_merge($this->iparams, $params);

        /* clean title & description */
        if (string_isHTML($this->iparams['title']))
            $this->iparams['title'] = string_html2text($this->iparams['title']);
        $this->iparams['title'] = preg_replace('/\n|\r|\'|"/', ' ', $this->iparams['title']);
        if (string_isHTML($this->iparams['summary']))
            $this->iparams['summary'] = string_html2text(strip_tags($this->iparams['summary']));
        $this->iparams['summary'] = preg_replace('/\n|\r|\'|"/', ' ', $this->iparams['summary']);

        /* add scripts */
        $this->add_JSFile('snsp.js');
        $this->add_JSScript('var snsp = new SNSPanel("snsp");');
        $this->add_JSEngineFile('tool/htmlelement.js');
        $this->add_JSLoadScript('snsp.initialise();');

        /* prepare specific facebook like integration */
        if ($this->config->vars['like_facebook'] == 1 ) {
            $this->register_asCaMykSEventHandler('onBodyOpen');
        }

        /* set theme */
        $this->theme = &$camyks->themes[$this->iparams['theme']];

        /* add og metas to header */
        if ($this->iparams['include_ogmetas'] == 1) {
            $camyks->HTMLPage->add_meta('og:locale', $this->iparams['locale'], 'property');
            if ($this->iparams['sitename'] != '') $camyks->HTMLPage->add_meta('og:site_name', $this->iparams['sitename'], 'property');
            if ($this->iparams['title'] != '') $camyks->HTMLPage->add_meta('og:title', string_text2HTML($this->iparams['title']), 'property');
            if ($this->iparams['link'] != '') $camyks->HTMLPage->add_meta('og:url', $this->iparams['link'], 'property');
            if ($this->iparams['summary'] != '') $camyks->HTMLPage->add_meta('og:description', string_text2HTML($this->iparams['summary']), 'property');
            if ($this->iparams['image'] != '') $camyks->HTMLPage->add_meta('og:image', $this->iparams['image'], 'property');
            if ($this->iparams['type'] != '') $camyks->HTMLPage->add_meta('og:type', $this->iparams['type'], 'property');
        }
    }

    /**
     * Initialise input in follow mode
     * @param array $params
     * @return void
     */
    private function initialise_followPanel($params) {

        /* merge params */
        $this->params = array_merge($this->config->vars, $params);

        /* check for styles loading */
        if ($this->params['follow_insertion'] == 1 and $this->params['follow_styleSource'] == 'plugin') {
            $this->add_styleFile('css/styles.css');
        }
    }

    /* specific display mode methods */

    /**
     * Display input in share mode.
     * @param array $params
     * @return void
     */
    private function display_sharePanel($params=array()) {

        /* update index */
        $this->currentIndex++;

        /* merge new params */
        $this->dparams = array_merge($this->iparams, $params);
        $this->count_displayedNetworks();

        /* update selected layout */
        $this->set_selectedLayout('input.html.inc');
    }

    /**
     * Display input in share mode.
     * @param array $params
     * @return void
     */
    private function display_followPanel($params=array()) {
        /* update selected layout */
        $this->set_selectedLayout('input_follow.html.inc');
    }

    /* specific tool methods */

    /**
     * Return given network href link.
     * @param string $network
     * @return string
     */
    protected function get_networkHrefLink($network) {
        if (!isset($this->networks[$network]))
            return '';
        if ($this->networks[$network]['link']=='')
            return '';
        return 'href="'.$this->get_networkURL($network, 'link').'"';
    }

    /**
     * Return given network href link.
     * @param string $network
     * @return string
     */
    protected function get_networkOnclickLink($network) {
        if (!isset($this->networks[$network]))
            return '';
        if ($this->networks[$network]['clic']=='')
            return '';
        return 'onclick="'.$this->get_networkURL($network, 'clic').'"';
    }

    /**
     * Return given network URL.
     * @param string $network
     * @param string $mode
     * @return string
     */
    protected function get_networkURL($network, $mode) {
        switch ($network) {
            case 'twitter':
                if ($this->dparams['shortlink'] != '')
                    $link = $this->dparams['shortlink'];
                else
                    $link = $this->dparams['link'];

                $txtLength = 143 - strlen($link);
                $title = string_getShortenedSentence(urlencode($this->dparams['title']), $txtLength);
                return vsprintf($this->networks[$network][$mode], $title.'+'.$link);
            case 'email':
                return preg_replace(array('/_title_/', '/_link_/', '/_ln_/'), array($this->dparams['title'], $this->dparams['link'], '%0d%0a'), $this->networks[$network][$mode]);
        }
        return vsprintf(
            $this->networks[$network][$mode],
            array(
                1 => urlencode($this->dparams['link']),
                2 => urlencode($this->dparams['title']),
                3 => urlencode($this->dparams['summary'])
            )
        );
    }

    /**
     * Return given network icon url.
     * @param string $network
     * @param string $mode
     * @return string
     */
    public function get_networkIconURL($network='', $mode='') {
        return $this->get_fileURL('img/'.$mode.'Icons/'.$network.'.'.$this->get_configValue($mode.'_pictureFormat'));
    }

    /**
     * Count enabled networks.
     * @return void
     */
    private function count_displayedNetworks() {
        foreach ($this->networks as $name => $network)
            if ($network['share'] == 1)
                $this->dparams['networks'][$this->config->vars['share_'.$name]]++;
    }

    /**
     * Initialise network list
     * @return void
     */
    private function initialise_networkList() {
        global $camyks;

        $this->networks = array(
            /* add facebook */
            'facebook' => array(
                'title'     => 'Facebook',
                'link'      => 'http://www.facebook.com/share.php?u=%1$s',
                'clic'      => '',
                'share'     => 1,
                'follow'    => 1,
                'like'      => 1,
            ),

            /* add twitter */
            'twitter' => array(
                'title'     => 'Twitter',
                'link'      => 'http://twitter.com/home?status=%1$s',
                'clic'      => '',
                'share'     => 1,
                'follow'    => 1,
            ),

            /* add google+ *
            'gplus' => array(
                'title'     => 'Google +',
                'link'      => 'https://plus.google.com/share?url=%1$s',
                'clic'      => '',
                'share'     => 1,
                'follow'    => 1,
            ),

            /* add linkedin */
            'linkedin' => array(
                'title'     => 'LinkedIn',
                'link'      => 'http://www.linkedin.com/shareArticle?mini=true&url=%1$s&title=%2$s&summary=%3$s&source=',
                'clic'      => '',
                'share'     => 1,
                'follow'    => 1,
            ),

            /* add instagram */
            'instagram' => array(
                'title'     => 'Instagram',
                'link'      => '',
                'clic'      => '',
                'share'     => 0,
                'follow'    => 1,
            ),

            /* add Youtube */
            'youtube' => array(
                'title'     => 'Youtube',
                'link'      => '',
                'clic'      => '',
                'share'     => 0,
                'follow'    => 1,
            ),

            /* add DailyMotion */
            'dailymotion' => array(
                'title'     => 'DailyMotion',
                'link'      => '',
                'clic'      => '',
                'share'     => 0,
                'follow'    => 1,
            ),

            /* add google bookmarks */
            'google' => array(
                'title'     => 'Google Bookmarks',
                'link'      => 'http://www.google.com/bookmarks/mark?op=add&bkmk=%1$s&title=%2$s&annotation=%3$s',
                'clic'      => '',
                'share'     => 1,
                'follow'    => 1,
            ),

            /* add digg */
            'digg' => array(
                'title'     => 'Digg',
                'link'      => 'http://digg.com/submit?url=%1$s&title=%2$s&bodytext=%3$s',
                'clic'      => '',
                'share'     => 1,
                'follow'    => 1,
            ),

            /* add slashdot */
            'slashdot' => array(
                'title'     => 'Slashdot',
                'link'      => 'http://slashdot.org/bookmark.pl?url=%1$s&title=%2$s',
                'clic'      => '',
                'share'     => 1,
                'follow'    => 1,
            ),

            /* add technorati */
            'technorati' => array(
                'title'     => 'Technorati',
                'link'      => 'http://www.technorati.com/faves?add=%1$s&title=%2$s',
                'clic'      => '',
                'share'     => 1,
                'follow'    => 1,
            ),

            /* add reddit */
            'reddit' => array(
                'title'     => 'Reddit',
                'link'      => 'http://reddit.com/submit?url=%1$s&title=%2$s',
                'clic'      => '',
                'share'     => 1,
                'follow'    => 1,
            ),

            /* add stumbleupon */
            'stumbleupon' => array(
                'title'     => 'StumbleUpon',
                'link'      => 'http://www.stumbleupon.com/submit?url=%1$s&title=%2$s',
                'clic'      => '',
                'share'     => 1,
                'follow'    => 1,
            ),

            /* add viadeo */
            'viadeo' => array(
                'title'     => 'Viadeo',
                'link'      => 'http://www.viadeo.com/shareit/share/?url=%1$s&title=%2$s&urllanguage='.$camyks->current_language,
                'clic'      => '',
                'share'     => 1,
                'follow'    => 1,
            ),

            /* add pinterest */
            'pinterest' => array(
                'title'     => 'Pinterest',
                'link'      => 'https://www.pinterest.com/pin/create/button/?url=%1$s&Description=%2$s',
                'clic'      => '',
                'share'     => 1,
                'follow'    => 1,
            ),

            /* add tumbler */
            'tumblr' => array(
                'title'     => 'Tumblr',
                'link'      => 'http://tumblr.com/widgets/share/tool?canonicalUrl=%1$s',
                'clic'      => '',
                'share'     => 1,
                'follow'    => 1,
            ),

            /* add vimeo */
            'vimeo' => array(
                'title'     => 'Vimeo',
                'link'      => '',
                'clic'      => '',
                'share'     => 0,
                'follow'    => 1,
            ),

            /* add flickr */
            'flickr' => array(
                'title'     => 'Flickr',
                'link'      => '',
                'clic'      => '',
                'share'     => 0,
                'follow'    => 1,
            ),

            /* add blogger */
            'blogger' => array(
                'title'     => 'Blogger',
                'link'      => 'https://www.blogger.com/blog_this.pyra?t&u=%1$s&n=%2$s',
                'clic'      => '',
                'share'     => 1,
                'follow'    => 1,
            ),

            /* add DeviantArt */
            'deviantart' => array(
                'title'     => 'DeviantArt',
                'link'      => '',
                'clic'      => '',
                'share'     => 0,
                'follow'    => 1,
            ),

            /* add SnapShat */
            'snapchat' => array(
                'title'     => 'Snapshat',
                'link'      => '',
                'clic'      => '',
                'share'     => 0,
                'follow'    => 1,
            ),

            /* add email */
            'email' => array(
                'title'     => 'E-mail',
                'link'      => 'mailto:?subject='.$this->get_translation('emailsubject', $camyks->get_confValue('site_title')).'&body='.$this->get_translation('emailbody'),
                'clic'      => '',
                'share'     => 1,
                'follow'    => 0,
            ),
        );
    }

    /**
     * Return configuration value
     * @param string $item
     * @return mixed
     */
    private function get_configValue($item) {
        return $this->config->get_value($item);
    }

    /* Admin_Site extension configuration methods */

    /**
     * Initialise object in Admin_Site / view configuration mode.
     * @return void
     */
    public function initialise_configDisplay() {
        global $camyks;

        /* prepare tabs */
        $this->tabBuilder = $camyks->get_input('TabBuilder');

        /* add tabs */
        $this->tabBuilder->add_tabs(array(
            array(
                'name'  => 'Share',
                'title' => $this->get_translation('tabshare'),
            ),
            array(
                'name'  => 'Follow',
                'title' => $this->get_translation('tabfollow'),
            ),
        ));

        /* initialise tabs */
        $this->tabBuilder->initialise(array('default'=>'Share'));
    }

    /**
     * Display object in Admin_Site / view configuration mode.
     * @return void
     */
    public function display_configDisplay() {
        $this->load_file('html/configuration/view.html.inc');
    }

    /**
     * Initialise object in Admin_Site / edit configuration mode.
     * @param Object $form
     * @return void
     */
    public function initialise_configEdition($form) {
        global $camyks;

        /* update form */
        $this->form = &$form;
        $this->form->set_object($this->config);

        /* load data */
        $this->sharingValues = $this->config->get_sharingNetworkList();
        $this->likeValues = $this->config->get_networkLikeList();

        /* prepare tabs */
        $this->tabBuilder = $camyks->get_input('TabBuilder');

        /* add tabs */
        $this->tabBuilder->add_tabs(array(
            array(
                'name'  => 'Share',
                'title' => $this->get_translation('tabshare'),
            ),
            array(
                'name'  => 'Follow',
                'title' => $this->get_translation('tabfollow'),
            ),
        ));

        /* initialise tabs */
        $this->tabBuilder->initialise(array('default'=>'Share'));
    }

    /**
     * Display object in Admin_Site / edit configuration mode.
     * @return void
     */
    public function display_configEdition() {
        $this->load_file('html/configuration/edit.html.inc');
    }

    /**
     * Execute object in Admin_Site / save configuration mode.
     * @return void
     */
    public function save_configuration() {
        $this->config->get_fromHeader();
        return $this->config->save();
    }
}
?>
