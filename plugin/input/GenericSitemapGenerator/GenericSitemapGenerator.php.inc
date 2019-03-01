<?php
/**
 * @brief GenericSitemapGenerator Input
 * <br />Default sitemap generator.
 * @details Plugin / Input Engine
 * @file plugin/input/GenericSitemapGenerator/GenericSitemapGenerator.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Feb 2019
 * @date Modification: Jul 2019
 * @copyright 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @todo Create other update methods: module reading on demand, and website crawling.
 * <br /> Create other update mode: automatic update for methods module reading with cache and website crawling.
 */

/**
 * GenericSitemapGenerator Input class.
 */
final class GenericSitemapGenerator extends Input {

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('GenericSitemapGenerator', $path_type);

        /* Override Plugin information */
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* Define author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Register plugin as Admin_Site extension */
        $this->register_asExtension('Admin_Site');

        /* load configuration */
        $this->load_configuration();

        /* Check for automatic file update */
        $this->register_asCaMykSEventHandler('onInitialise');
    }

    /* Override Input methods */

    /**
     * Initialise input.
     * @param array $params
     * @return void
     */
    public function initialise($params=array()) {
        global $camyks;


        /* Input generic initialization */
        parent::initialise();
    }

    /**
     * Execute Input object in request mode.
     * @return void
     */
    public function execute_request() {
        global $camyks;

        /* Load CaMykS in site mode */
        $camyks->get_siteInit();

        /* Load mode to execute */
        $mode = isset($_REQUEST['mode']) ? $_REQUEST['mode'] : '';

        /* Execute mode */
        switch($mode) {
            case 'writeSitemap' : return $this->execute_request_writeSitemap();
            case 'sentSitemap' : return $this->execute_request_sendSitemap();
        }

        /* Throw CaMykS fatal error */
        die();
    }

    /* Override Plugin methods */

    /**
     * Execute handler on CaMykS initialisation.
     * @return void
     */
    public function execute_onCaMykSInitialise() {

        /* Check mode */
        if ($this->config->vars['update_mode'] != 1)
            return;

        /* Check delay */
        switch($this->config->vars['update_delayUnit']) {
            case 0:
                $diff = 60*$this->config->vars['update_delayValue'];
                break;
            case 1:
                $diff = 60*60*$this->config->vars['update_delayValue'];
                break;
            case 2:
                $diff = 24*60*60*$this->config->vars['update_delayValue'];
                break;
            case 3:
                $diff = 7*24*60*60*$this->config->vars['update_delayValue'];
                break;
            case 4:
                $diff = mktime(0, 0, 1, 1+$this->config->vars['update_delayValue'], 1, 1970);
                break;
        }

        if ($this->config->vars['lastUpdate_date'] + $diff > time())
            return;

        /* Build site map content */
        $content = $this->get_sitemapContent();

        /* Write content to sitemap file */
        $this->write_file($content);
    }

    /* Specific request mode methods */

    /**
     * Execute Input object in request / write sitemap mode.
     * @return void
     */
    private function execute_request_writeSitemap() {
        /* Prepare answer */
        $this->answer = new CRequestAnswer();

        /* Build site map content */
        $content = $this->get_sitemapContent();

        /* Write content to sitemap file */
        if ($this->write_file($content))
            $this->answer->send_asJSON(array('status'=>'success', 'action'=>'writeSitemap', 'message'=>$this->get_translation('sitemapfile_created')));
        else
            $this->answer->send_asJSON(array('status'=>'failure', 'action'=>'writeSitemap', 'message'=>$this->get_translation('sitemapfile_notcreated')));
    }

    /**
     * Execute Input object in request / send sitemap mode.
     * @return void
     */
    private function execute_request_sendSitemap() {
        $content = $this->get_sitemapContent();

        /* send XML */
        header("Content-type: text/xml");
        echo $content;
        die();
    }


    /* Specific tool methods */

    /**
     * Load configuration.
     * @return void
     */
    private function load_configuration() {
        $this->load_library('GenericSitemapGeneratorConfig');
        $this->config = new GenericSitemapGeneratorConfig('config', $this);
        $this->config->get();
    }

    /**
     * Write sitemap file.
     * @param string $content
     * @return boolean sucess
     */
    private function write_file($content) {
        return file_write('sitemap.xml', $content);
    }

    /**
     * Build sitemap content.
     * @return string
     */
    private function get_sitemapContent() {
        if ($this->config->get_value('update_method') == 0)
            return $this->get_sitemapContentFromModules();
        return '';
    }

    /**
     * Build sitemap content from modules.
     * @return void
     */
    private function get_sitemapContentFromModules() {
        global $camyks;

        /* Initialise duration */
        $duration = microtime(true);

        /* Build default link */
        $defaultLink = array(
            'loc'       => '',
            'lastmod'   => time(),
            'priority'  => 0.5,
            'alt'       => array(),
        );

        /* Initialise link list */
        $links = array();

        /* Load extensions */
        $extensions = $this->get_registeredExtensions();

        /* Load links from extension plugins */
        foreach ($extensions as $plugin)
            $links += $plugin->get_sitemapLinks();

        /* Build content header */
        $content = '<?xml version="1.0" encoding="UTF-8"?>'."\n";
        $content .= '<urlset xmlns="http://www.sitemaps.org/schemas/sitemap/0.9"'."\n";
        $content .= 'xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"'."\n";
        $content .= 'xsi:schemaLocation="http://www.sitemaps.org/schemas/sitemap/0.9'."\n";
        $content .= 'http://www.sitemaps.org/schemas/sitemap/0.9/sitemap.xsd">'."\n";

        /* Add links */
        foreach ($links as $link) {
            /* Merge link with default link */
            $link = array_merge($defaultLink, $link);

            /* Check link data */
            if (!preg_match('#^https?://#', $link['loc']))
                $link['loc'] = $camyks->get_fileURL($link['loc'], 'absolute');
            $link['lastmod'] = date('c', $link['lastmod']);
            if ($link['priority'] > 1 and $link['priority'] <= 100)
                $link['priority'] /= 100;
            $link['priority'] = string_numberFormat($link['priority'], 2, 'num');

            /* Build content link */
            $content .= '<url>'."\n";
            $content .= '    <loc>'.$link['loc'].'</loc>'."\n";
            if (count($link['alt']) > 0) {
                foreach ($link['alt'] as $lg => $url)
                    $content .= '    <xhtml:link rel="alternate" hreflang="'.$lg.'" href="'.$url.'" />'."\n";
            }
            $content .= '    <lastmod>'.$link['lastmod'].'</lastmod>'."\n";
            $content .= '    <priority>'.$link['priority'].'</priority>'."\n";
            $content .= '</url>'."\n";
        }

        /* Build content footer */
        $content .= '</urlset>';

        /* Update duration */
        $duration = (int)((microtime(true) - $duration)*1000);

        /* Update last upsate date */
        $this->config->update_lastUpdateDate(count($links), $duration);

        /* Return content */
        return $content;
    }

    /* Admin_Site extension configuration methods */

    /**
     * Initialise object in Admin_Site / view configuration mode.
     * @return void
     */
    public function initialise_configDisplay() {
        global $camyks;

        /* add needed JS */
        $this->add_JSEngineFile('object/cajaxrequest.js');
        $this->add_JSFile('ConfigViewer.js');
        $this->add_JSLoadScript('ConfigViewer.set_param("baseURL", "'.$camyks->get_fileURL('request.php?input='.$this->name, 'absolute').'");');
        $this->add_JSLoadScript('ConfigViewer.initialise();');
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
        /* update form */
        $this->form = &$form;
        $this->form->set_object($this->config);

        /* Add scripts */
        $this->add_JSFile('ConfigEditor.js');
        $this->add_JSLoadScript('ConfigEditor.set_param("form", "'.$this->form->name.'");');
        $this->add_JSLoadScript('ConfigEditor.initialise();');
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
        $this->load_configuration();
        $this->config->get_updateFromHeader();
        return $this->config->save();
    }
}
?>
