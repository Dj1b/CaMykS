<?php
/**
 * @brief HTML page object
 * @details Engine / Object Library
 * @file engine/lib/object/HTMLPage.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: Jun 2005
 * @date Modification: Oct 2018
 * @copyright 2005 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @todo Try to set up output page parts as private, as they should be only called by add_HTMLHeader().
 */

/**
 * HTMLPage class.
 * @author CaMykS Team <camyks.contact@gmail.com>
 */
final class HTMLPage {
    /**
     * @var string $content
     * @brief Page content.
     */
    private $content;

    /**
     * @var string $doctype
     * @brief Page doctype.
     */
    private $doctype;

    /**
     * @var integer $htmlVersion
     * @brief HTML version for page.
     */
    private $htmlVersion;

    /**
     * @var string $language
     * @brief Page current language.
     */
    private $language;

    /**
     * @var int $redirect_time
     * @brief Page redirection delay in second.
     */
    private $redirect_time = 0;

    /**
     * @var string $redirect_url
     * @brief Page redirection URL.
     */
    private $redirect_url = '';

    /**
     * @var boolean $disable_cache
     * @brief Is cache disabled for page.
     */
    private $disable_cache = false;

    /**
     * @var string $site_title
     * @brief Site title for page header.
     */
    private $site_title = '';

    /**
     * @var string $page_title
     * @brief Content page title for page header.
     */
    public $page_title = '';

    /**
     * @var string $charset
     * @brief Page charset header.
     */
    private $charset = "UTF-8";

    /**
     * @var array $metas
     * @brief Page metas header.
     */
    private $metas = array();

    /**
     * @var string $rss
     * @brief RSS URL for page header.
     */
    private $rss = '';

    /**
     * @var boolean $robots_index
     * @brief Are robots allowed to index this page.
     */
    private $robots_index = true;

    /**
     * @var boolean $robots_follow
     * @brief Are robots allowed to follow links in this page.
     */
    private $robots_follow = true;

    /**
     * @var array $js_files
     * @brief Javascript files to be inserted.
     */
    private $js_files = array();

    /**
     * @var array $js_scripts
     * @brief Javascript scripts to be inserted.
     */
    private $js_scripts = array();

    /**
     * @var array $js_pre_scripts
     * @brief Javascript scripts to be inserted before Javascript file insertion.
     */
    private $js_pre_scripts = array();

    /**
     * @var array $js_event_scripts
     * @brief Javascript scripts to be inserted on page events.
     */
    private $js_event_scripts = array();

    /**
     * @var array $style_files
     * @brief CSS styles files to be inserted.
     */
    private $style_files = array();

    /**
     * @var array $style_scripts
     * @brief CSS styles scripts to be inserted.
     */
    private $style_scripts = array();

    /**
     * @var array $style_included_files
     * @brief CSS styles files to be inserted as script.
     */
    private $style_included_files = array();

    /**
     * @var array $links
     * @brief Header links for page.
     */
    private $links = array();

    /**
     * @var array $google_analytics
     * @brief Google analytics information to be inserted in page.
     */
    private $google_analytics = array('code'=>'', 'domain'=>'auto');

    /**
     * @var string $header_extras
     * @brief Page extra headers.
     */
    private $header_extras = '';

    /**
     * @var array $header_extras
     * @brief Page extra headers.
     */
    private $favicon = '';

    /**
     * Class constructor.
     * @return void
     */
    public function __construct(){
        global $camyks;

        /* load HTML version */
        $this->htmlVersion = $camyks->get_confValue('html_version', 4);

        /* load doctype */
        if ($this->htmlVersion == 5) {
            $this->doctype = '<!DOCTYPE html>';
        } else {
            $this->doctype = '<!DOCTYPE html  PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">';
        }

        /* add compatibility tag */
        if ($camyks->get_confValue('html_compatibilityTag') != false)
            $this->add_meta('X-UA-Compatible', $camyks->get_confValue('html_compatibilityTag'), 'http-equiv');

        /* add other meta case of HTML version */
        if ($this->htmlVersion == 4) {
            $this->add_meta('Content-Type', 'text/html; charset='.$this->charset.'', 'http-equiv');
            if ($this->disable_cache) {
                $this->add_meta('Expires', '0', 'http-equiv');
                $this->add_meta('Pragma', 'no-cache', 'http-equiv');
            }
            $this->add_meta('Content-Style-Type', 'text/css', 'http-equiv');
            $this->add_meta('Content-Script-Type', 'text/javascript', 'http-equiv');
        } elseif ($this->htmlVersion == 5) {
            $this->add_meta($this->charset, '', 'charset');
            $this->add_meta('viewport', 'width=device-width, user-scalable=1', 'name');
        }

        /* add generator meta as CaMykS */
        $this->add_meta('generator', $camyks->name.' '.$camyks->version);
    }

    /*********** INPUT METHODS **************/

    /**
     * Define site information.
     * @param string $site_title the website title
     * @param string $site_author the website author
     * @return void
     */
    public function set_siteInformations($site_title, $site_author='') {
        $this->site_title = $site_title;
        if ($site_author != '')
            $this->add_meta('author',  $site_author);
    }

    /**
     * Define page information.
     * @param string $page_title the webpage title
     * @param string $page_desc the webpage description meta
     * @param string $page_keys the webpage keywords meta
     * @param string $page_lang the webpage language displayed
     * @return void
     */
    public function set_pageInformations($page_title, $page_desc='', $page_keys='', $page_lang='') {
        $this->page_title = $page_title;
        if ($page_keys != '')
            $this->add_meta('keywords',  $page_keys);
        if ($page_desc != '')
            $this->add_meta('description', $page_desc);
        if ($page_lang != '') {
            if ($this->htmlVersion == 4)
                $this->add_meta('Content-Language', $page_lang, 'http-equiv');
            else
                $this->language = $page_lang;
        }
    }

    /**
     * Define robots information.
     * @param boolean $index the index value
     * @param boolean $follow the follow value
     * @return void
     */
    public function set_robotInformations($index=true, $follow=true) {
        $this->robots_index = $index;
        $this->robots_follow = $follow;
        $this->add_meta('robots', ($this->robots_index?'':'no').'index,'.($this->robots_follow?'':'no').'follow');
    }

    /**
     * Define google information.
     * @param string $code the google code value
     * @param string $domain the google domain value
     * @return void
     */
    public function set_googleInformations($code='', $domain='') {
        if ($code != '')
            $this->google_analytics['code'] = $code;
        if ($domain != '')
            $this->google_analytics['code'] = $domain;
    }

    /**
     * Define site favicon.
     * @param string $favicon the favicon file name
     * @return void
     */
    public function set_favicon($favicon=null) {
        global $camyks;
        $root = $camyks->get_rootBaseURL('absolute_long');
        if (isset($favicon) and file_exists($favicon))
            $this->add_link('icon', $root.$favicon);
        else if (count($f = glob('favicon.*'))>0)
            $this->add_link('icon', $root.basename($f[0]));
    }

    /**
     * Define charset.
     * @param string $charset
     * @return void
     */
    public function set_charset($charset='') {
        if ($charset != '' and $this->charset != $charset) {
            $this->charset = $charset;
            $this->add_meta('Content-Type', 'text/html; charset='.$this->charset.'', 'http-equiv');
        }
    }

    /**
     * Add a new meta.
     * @param string $key the meta name
     * @param string $value the meta value
     * @param string $method the meta displaying method
     * @return void
     */
    public function add_meta($key, $value, $method='name') {
        if ($method == 'link:rel')
            return $this->add_link($key, $value);
        $this->metas[$key] = array('value'=>$value, 'method'=>$method);
    }

    /**
     * Add a new link
     * @param string $rel the rel value
     * @param string $href the href value
     * @param array $params the other params
     * @return void
     */
    public function add_link($rel, $href, $params=array()) {
        if ($rel == '')
            $this->links[] = array_merge($params, array('href'=>$href));
        else
            $this->links[] = array_merge(array('rel'=>$rel, 'href'=>$href), $params);
    }

    /**
     * Add a new Javascript file.
     * @param string $file the file path & name
     * @return void
     */
    public function add_JSFile($file='') {
        if ($file != '' and !in_array($file, $this->js_files))
            $this->js_files[] = $file;
    }

    /**
     * Add a new Javascript script.
     * @param string $script the script to add
     * @param boolean $unique this script has to be unique
     * @return void
     */
    public function add_JSScript($script='', $unique=false) {
        if ($script=='' or ($unique and in_array($script, $this->js_scripts)))
            return;
        $this->js_scripts[] = $script;
    }

    /**
     * Add a new Javascript pre-script.
     * @param string $script the script to add
     * @param boolean $unique this script has to be unique
     * @return void
     */
    public function add_JSPreScript($script='', $unique=false) {
        if ($script=='' or ($unique and in_array($script, $this->js_pre_scripts)))
            return;
        $this->js_pre_scripts[] = $script;
    }

    /**
     * Add a new Javascript script to window event script list.
     * @param string $event the window event
     * @param string $script the script to add
     * @param boolean $unique this script has to be unique
     * @return void
     */
    public function add_JSWindowEventScript($event, $script, $unique=false) {
        /* check empty script */
        if ($script == '')
            return;

        /* check event */
        if (substr($event, 0, 2) == 'on')
            $event = substr($event, 2);

        /* check event list */
        if (!isset($this->js_event_scripts[$event]))
             $this->js_event_scripts[$event] = array();

        /* check unique script */
        if ($unique and in_array($script, $this->js_event_scripts[$event]))
            return;

        /* add script to list */
        $this->js_event_scripts[$event][] = $script;
    }

    /**
     * Add Javascript script on load window event.
     * @see add_JSWindowEventScript()
     * @param string $script the script to add
     * @param boolean $unique tell if this script must be unique
     * @return void
     */
    public function add_JSloadScript($script='', $unique=false) {
        return $this->add_JSWindowEventScript('load', $script, $unique);
    }

    /**
     * Add Javascript script on unload window event.
     * @see add_JSWindowEventScript()
     * @param string $script the script to add
     * @param boolean $unique tell if this script must be unique
     * @return void
     */
    public function add_JSunloadScript($script='', $unique=false) {
        return $this->add_JSWindowEventScript('unload', $script, $unique);
    }

    /**
     * Add CSS style file.
     * @param string $file the file path & name
     * @param string $media the media which the style will be displayed
     * @param string $condition the media condition
     * @return void
     */
    public function add_styleFile($file='', $media='', $condition='') {
        $file = trim($file);
        if ($file == '')
            return;
        if (!isset($this->style_files[$media]))
            $this->style_files[$media] = array();
        $this->style_files[$media][] = array('file' => $file, 'condition' => $condition);
    }

    /**
     * Add CSS style script.
     * @param string $css the style script to add
     * @return void
     */
    public function add_styleScript($css='') {
        if ($css != '')
            $this->style_scripts[] = $css;
    }

    /**
     * Add CSS style file to be inserted as script.
     * @param string $file the file path & name
     * @return void
     */
    public function add_styleIncludedFile($file='') {
        if ($file != '')
            $this->style_included_files[] = $file;
    }

    /**
     * Add extra content to header.
     * @param string $content
     * @return void
     */
    public function add_headerExtra($content='') {
        $this->header_extras .= $content."\n";
    }

    /**
     * Add RSS feed.
     * @param string $url the feed URL
     * @param string $title the feed title
     * @return void
     */
    public function add_RSSFeed($url='', $title='') {
        $this->add_link('alternate', $url, array('title'=>$title, 'type'=>'application/rss+xml'));
    }

    /**
     * Set a http redirection.
     * @param int $time the time before redirection in second
     * @param string $url the target url
     * @return void
     */
    public function set_redirect($time, $url) {
        $this->redirect_time = $time;
        $this->redirect_url = $url;
        $this->add_meta('Refresh', $time.';url='.$url, 'http-equiv');
    }

    /**
     * Define mobile metas.
     * @param boolean $enabled
     * @param array $config
     * @parblock - Available parameters are <br />
     * \e string width <br />
     * \e string initial-scale <br />
     * \e string maximum-scale <br />
     * \e integer user-scalable <br />
     * @endparblock
     * @return void
     */
    public function set_mobileMeta($enabled=false, $config=array()) {
        if ($enabled == false)
            return;

        /* set default config */
        $defaultConfig = array(
            'width'         => 'device-width',
            'initial-scale' => '1.0',
            'maximum-scale' => '1.0',
            'user-scalable' => 0,
        );

        /* check config */
        if ($config == false)
            $config = $defaultConfig;
        else
            $config = array_merge($defaultConfig, $config);

        /* build config value */
        $value = array();
        foreach($config as $c => $v)
            $value[] = $c.'='.$v;
        $value = implode(', ', $value);

        /* set meta */
        $this->add_meta('viewport', $value, 'name');

        /* update doctype */
        if ($this->htmlVersion != 5)
            $this->doctype = '<!DOCTYPE html PUBLIC "-//WAPFORUM//DTD XHTML Mobile 1.2//EN" "http://www.openmobilealliance.org/tech/DTD/xhtml-mobile12.dtd">';
    }

    /*********** OUTPUT PAGE METHODS *************/

    /**
     * Display builded content and re-initialise actual content.
     * @param string $buffer the content to output
     * @return void
     */
    public function write_HTMLContent($buffer='') {
        echo $this->content.$buffer;
        $this->content = '';
    }

    /**
     * Alias for write_HTMLContent method.
     * @see write_HTMLContent()
     * @param string $buffer the content to output
     * @return void
     */
    public function flush($buffer = '') {
        $this->write_HTMLContent($buffer);
    }

    /**
     * Update content with given html content
     * @param string $content
     * @return void
     */
    public function add_HTMLContent($content='') {
        $this->content .= $content;
    }

    /**
     * Display built content updated with buffer value, then add a file content.
     * @param string $file the file path & name
     * @param string $buffer the content to add
     * @return string
     */
    public function write_HTMLFile($file='', $buffer='') {
        if (file_exists($file)) {
            $this->add_HTMLContent($buffer);
            $this->write_HTMLContent();
            require($file);
            return '';
        }
        return $buffer;
    }

    /**
     * Write html page header.
     * @return void
     */
    public function add_HTMLHeader() {
        $this->get_doctype();
        $this->get_htmlHeader();
        $this->get_title();
        $this->get_metas();
        $this->get_links();
        $this->get_JSPreScripts();
        $this->get_JSFiles();
        $this->get_JSScripts();
        $this->get_styleFiles();
        $this->get_styleScripts();
        $this->get_headerExtras();
        $this->get_body();
    }

    /**
     * Write html page footer.
     * @return void
     */
    public function add_HTMLFooter() {
        echo "</body>\n";
        echo "</html>\n";
    }

    /*********** OUTPUT PAGE PARTS METHODS *************/

    /**
     * Write page header doctype.
     * @return void
     */
    public function get_doctype() {
        echo $this->doctype."\n";
    }

    /**
     * Write page html header.
     * @return void
     */
    public function get_htmlHeader() {
        global $camyks;
        if ($this->language != '' and $this->htmlVersion == 4)
            echo '<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="'.$this->language.'" lang="'.$this->language.'">'."\n".'<head>';
        elseif ($this->language == '')
            echo "<html>\n<head>\n";
        else
            echo "<html lang=\"".$this->language."\">\n<head>\n";

        /* add base url for modern urls */
        if (($camyks->get_confValue('friendlyurls') == 'modern' or $camyks->get_confValue('friendlyurls') == 'modern2') and $camyks->mode != CAMYKS_MODE_ADMIN)
            echo "<base href=\"".$camyks->get_rootBaseURL('absolute_long')."\" />\n";
    }

    /**
     * Write page title header.
     * @return void
     */
    public function get_title() {
        global $camyks;

        /* prepare title */
        $t = array();

        if (!isset($camyks->contentPage) or $camyks->contentPage->homepage == 1) {
            /* display site title first on home page, then page title */
            if ($this->site_title != "") $t[] = $this->site_title;
            if ($this->page_title != "") $t[] = $this->page_title;
        } else {
            /* display page title first on other pages, then site title */
            if ($this->page_title != "") $t[] = $this->page_title;
            if ($this->site_title != "") $t[] = $this->site_title;
        }
        $str = "<title>";
        $str .= implode(' - ', $t);
        $str .= "</title>\n";
        echo $str;
    }

    /**
     * Write page header metas.
     * @return void
     */
    public function get_metas() {
        foreach ($this->metas as $key => $meta) {
            if (isset($meta['value']) and $meta['value'] != '')
                echo "<meta ".$meta['method']."=\"".$key."\" content=\"".preg_replace('/"/', '\'', $meta['value'])."\" />\n";
            else
                echo "<meta ".$meta['method']."=\"".$key."\" />\n";
        }
    }

    /**
     * Write page header links.
     * @return void
     */
    public function get_links() {
        foreach ($this->links as $link) {
            echo '<link';
            foreach ($link as $key => $value)
                echo ' '.$key.'="'.$value.'"';
            echo ' />'."\n";
        }
    }

    /**
     * Write page jeader Javascript files
     * @return void
     */
    public function get_JSFiles() {
        global $camyks;

        /* check HTML version for extra attribute in script tag */
        $t = ($this->htmlVersion > 4 ? '' : ' type="text/javascript"');

        /* check for server side caches */
        if ($camyks->mode == CAMYKS_MODE_SITE and $camyks->get_confValue('cache_server_side') == 'enabled' and count($this->js_files)>1) {
            $str = '';
            $cachedJS = array();
            foreach ($this->js_files as $idx => $js) {
                $f = new FSFile($js);
                /* do not cache external files */
                if (preg_match('/http?s:\/\//', $js))
                    continue;

                $cachedJS[] = $js;
                unset($this->js_files[$idx]);
                $str .= $f->filename.'-'.$f->md5().'/';
            }

            /* build cached script with checksum */
            $checksum = md5($str);
            $masterScript = $camyks->site_var_path.'/ServerCache/scripts/script-'.count($cachedJS).'-'.$checksum.'.js';

            /* write cached script if it doesn't exists */
            if (!file_exists($masterScript)) {
                folder_completePath ($camyks->site_var_path.'/ServerCache/scripts');
                $mf = fopen($masterScript, 'a+');
                foreach ($cachedJS as $js) {
                    $file = new FSFile($js);
                    $content = $file->get_contents();
                    $content = preg_replace('/(\r\n){1,}/', "\n", $content);
                    fwrite($mf, $content."\n\n");
                }
                fclose($mf);
            }
            echo "<script".$t." src=\"".$camyks->get_fileURL($masterScript)."\">/* add javascript */</script>\n";
        }

        /* check for client side cache */
        if ($camyks->get_confValue('cache_client_side') == 'disabled')
            $r = '?'.rand(0, 999999);
        else
            $r = '';

        /* add files */
        foreach ($this->js_files as $js) {
            if (preg_match('/https?:\/\//i', $js))
                echo "<script".$t." src=\"".$js.$r."\">/* add javascript */</script>\n";
            else
                echo "<script".$t." src=\"".$camyks->get_fileURL($js).$r."\">/* add javascript */</script>\n";
        }
    }

    /**
     * Write Javascript pre-scripts.
     * @return void
     */
    public function get_JSPreScripts() {
        /* check for pre-scripts to write */
        if (count ($this->js_pre_scripts) == 0)
            return;

        /* check HTML version for extra attribute in script tag */
        $t = ($this->htmlVersion > 4 ? '' : ' type="text/javascript"');

        /* add scripts */
        $str = "<script".$t.">\n";
        foreach ($this->js_pre_scripts as $script) {
            $str .= "\t".$script."\n";
        }
        $str .= "</script>\n";
        echo $str;
    }

    /**
     * Write Javascript scripts
     * @return void
     */
    public function get_JSScripts() {
        /* check for scripts to write */
        if (count ($this->js_scripts) == 0
                and count ($this->js_event_scripts) == 0
                and $this->google_analytics['code'] == '')
            return;

        /* check HTML version for extra attribute in script tag */
        $t = ($this->htmlVersion > 4 ? '' : ' type="text/javascript"');

        /* open script section */
        $str = "<script".$t.">\n";

        /* add main scripts */
        foreach ($this->js_scripts as $script) {
            $str .= "\t".$script."\n";
        }

        /* add window event scripts */
        foreach ($this->js_event_scripts as $event => $scripts) {
            if (count ($scripts) > 0) {
                $str .= "\n\t".'/* on '.$event.' scripts */' . "\n";
                $str .= "\t".'window.on'.$event.' = function() {'."\n";
                foreach ($scripts as $fx ) {
                    $str .= "\t\t".$fx."\n";
                }
                $str .= "\t".'}'."\n";
            }
        }
        /* close script section */
        $str .= "</script>\n";
        echo $str;
    }

    /**
     * Write style files.
     * @return void
     */
    public function get_styleFiles() {
        global $camyks;

        /* check for server side caches */
        if ($camyks->mode == CAMYKS_MODE_SITE and $camyks->get_confValue('cache_server_side') == 'enabled') {
            $allfiles = array();
            foreach ($this->style_files as $media => $files) {
                if (count($files) <= 1)
                    continue;

                $str = '';
                $cachedCSS = array();
                foreach ($files as $idx => $fInfo) {
                    $f = new FSFile($fInfo['file']);
                    if ($fInfo['condition'] != '' or preg_match('/https?:\/\//', $fInfo['file'])) {
                        continue;
                    }

                    $cachedCSS[] = $fInfo;
                    unset($this->style_files[$media][$idx]);
                    $str .= $f->filename.'-'.$f->md5().'/';
                }

                /* build cached styles for media with checksum */
                $checksum = md5($str);
                $masterStyles = $camyks->site_var_path.'/ServerCache/styles/style-'.count($cachedCSS).'-'.$checksum.'.css';

                /* write cache file if it doesn't exists */
                if (!file_exists($masterStyles)) {
                    folder_completePath ($camyks->site_var_path.'/ServerCache/styles');
                    $mf = fopen($masterStyles, 'a+');
                    foreach ($cachedCSS as $f) {
                        $file = new FSFile($f['file']);
                        $p = $file->path;
                        $content = $file->get_contents();
                        $content = preg_replace('/url\(/i', 'url(../../../'.$p.'/', $content);
                        $content = preg_replace('/(\r\n){1,}/', "\n", $content);

                        fwrite($mf, $content."\n\n");
                    }
                    fclose($mf);
                }

                if ($media == '')
                    echo '<link href="'.$camyks->get_fileURL($masterStyles).'" type="text/css" rel="stylesheet" />'."\n";
                else
                    echo '<link href="'.$camyks->get_fileURL($masterStyles).'" media="'.$media.'" type="text/css" rel="stylesheet" />'."\n";
            }
        }

        /* check for client side caches */
        if ($camyks->get_confValue('cache_client_side') == 'disabled')
            $r = '?'.rand(0, 999999);
        else
            $r = '';

        /* add specific styles */
        foreach ($this->style_files as $media => $files) {
            foreach ($files as $file) {
                /* check for condition */
                if ($file['condition'] != '')
                echo '<!--[if '.$file['condition'].']>'."\n";

                /* add files */
                if ($media == '')
                    echo '<link href="'.$camyks->get_fileURL($file['file']).$r.'" type="text/css" rel="stylesheet" />'."\n";
                else
                    echo '<link href="'.$camyks->get_fileURL($file['file']).$r.'" media="'.$media.'" type="text/css" rel="stylesheet" />'."\n";

                /* end condition */
                if ($file['condition'] != '')
                    echo '<![endif]-->'."\n";
            }
        }
    }

    /**
     * Write style scripts.
     * @return void
     */
    public function get_styleScripts() {
        /* check for scripts to write */
        if (count($this->style_scripts) == 0 and count ($this->style_included_files) == 0)
            return;

        /* write file included styles */
        echo '<style type="text/css">'."\n";
        foreach ($this->style_included_files as $s) {
            if (file_exists($s))
                require($s);
        }

        /* write styles */
        $str = '';
        foreach ($this->style_scripts as $s) {
            $str .= $s ."\n\n";
        }
        $str .= '</style>'."\n";
        echo $str;
    }

    /**
     * write extra header data
     * @return void
     */
    public function get_headerExtras() {
        echo $this->header_extras;
    }

    /**
     * Write body header.
     * @return void
     */
    public function get_body () {
        echo "</head>\n<body>\n";
        if ($this->google_analytics['code'] != '') {
            /* add google analytics */
            $str = "<script>\n";
            $str .= "\t(function(i,s,o,g,r,a,m){i['GoogleAnalyticsObject']=r;i[r]=i[r]||function(){\n";
            $str .= "\t(i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),\n";
            $str .= "\tm=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)\n";
            $str .= "\t})(window,document,'script','//www.google-analytics.com/analytics.js','ga');\n";
            $str .= "\tga('create', '".$this->google_analytics['code']."', '".$this->google_analytics['domain']."');\n";
            $str .= "\tga('send', 'pageview');\n";
            $str .= "</script>\n";
            echo ($str);
        }
    }

    /* deprecated methods */

    /**
     * Alias to add_RSSFeed.
     * @see add_RSSFeed()
     * @param string $url the rss url
     * @param string $title the rss title
     * @return void
     * @deprecated Use add_RSSFeed instead.
     */
    public function set_RSSFeed($url='', $title='') {
        $this->add_RSSFeed($url, $title);
    }
}
?>
