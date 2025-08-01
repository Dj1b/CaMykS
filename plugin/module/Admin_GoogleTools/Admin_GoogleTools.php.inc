<?php
/**
 * @brief Admin_GoogleTools module.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Sep 2007
 * @date Modification: Jul 2025
 * @copyright 2007 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GoogleTools class.
 */
final class Admin_GoogleTools extends Module {
    /**
     * var array $referredpages
     * @brief List of refered pages.
     */
    protected $referredpages;

    /**
     * var integer $maxreferredpages
     * @brief Default max referred pages loaded.
     */
    private $maxreferredpages = 100;

    /**
     * var array $linkedpages
     * @brief List of linked pages.
     */
    protected $linkedpages;

    /**
     * var integer $maxlinkedpages
     * @brief Default mex linked pages loaded
     */
    private $maxlinkedpages = 100;

    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('Admin_GoogleTools', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'Google';

        /* Override Module variables */
        $this->type = 'admin';
        $this->admin_type = 'monitoring';

        /* Define plugin author */
        $this->authors_name = 'CaMykS Team';
        $this->authors_mail = 'camyks.contact@gmail.com';
        $this->authors_group = 'camyks.net';
    }

    /* Mark: Override Module methods */

    /**
     * Define module permission.
     * @return void
     */
    function get_rights() {
        global $camyks;
        $this->rights[0] = array(
            'name'      => 'read',
            'title'     => $camyks->get_translation('read'),
            'default'   => false,
        );
    }

    /**
     * Initialise module object in admin mode
     * @return void
     */
    public function init_admin() {
        global $camyks;

        /* Check admin user permission */
        if ($this->check_right(0) === false) {
            return $this->init_admin_accessDenied();
        }

        /* Load action to execute */
        $this->mode = isset($_REQUEST['mode']) ? $_REQUEST['mode'] : '';

        /* Execute action */
        switch ($this->mode) {
            case 'referred':
                $this->init_admin_referred();
                break;
            case 'linked':
                $this->init_admin_linked();
                break;
            default:
                $this->openTab = 'referred';
        }

        /* Load tab engine */
        $this->tabObject = 'gtools_tabObject';
        $this->add_JSEngineFile('object/ctab.js');
        $this->add_JSScript($this->tabObject.' = new CTab();');
        $this->add_JSScript($this->tabObject.'.init("referred", "'
            .$this->theme->parts['boxTabCSSStandart'].'","'
            .$this->theme->parts['boxTabCSSSelected'].'","'
            .$this->theme->parts['boxTabCSSRollover'].'");');
        $this->add_JSLoadScript($this->tabObject.'.mouseclick(\''.$this->openTab.'\');');

        $this->tabs = array(
            array(
                'name'  => 'referred',
                'title' => $this->get_translation('tabreferred'),
            ),
            array(
                'name'  => 'linked',
                'title' => $this->get_translation('tablinked'),
            ),
        );

        /* Build buttons */
        $this->buttons = array(
            array(
                'link'  => $camyks->get_adminLink(),
                'title' => $camyks->get_translation('back'),
            ),
        );

        /* Perform generic initialisation */
        parent::init_admin();
    }

    /* Mark: Admin initialise mode sub methods */

    /**
     * Initialise module object in admin/referred mode.
     * @return void
     */
    private function init_admin_referred() {
        global $camyks;

        $this->openTab = 'referred';

        $this->referredpages = array();
        $this->referredpages['count'] = 0;
        $this->referredpages['list'] = array();

        $url = $camyks->_conf['url'];
        $find = '@^(?:http://)?([^/]+)@i';
        if (preg_match($find, $url, $result)   )
            $url = $result[1];

        $gurl = 'http://www.google.com/search?hl=en&num='.$this->maxreferredpages;
        $gurl .= '&btnG=Google+Search&as_sitesearch='.urlencode($url);
        $gurl .= '&ie=utf-8&oe=utf-8';

        /* get google page */
        $handle = @fopen($gurl, 'rb');
        $content = stream_get_contents($handle);
        fclose($handle);

        /* parse count result in page */
        if (preg_match ('/about <b>([0-9,\ ]*)<\/b> from/', $content, $count)) {
            $this->referredpages['count'] = (int)preg_replace('/[^0-9]/', '', $count[1]);
        }

        /* parse list result in page */
        if (preg_match_all('/<h[^>]*><a href="([^"]*)"[^>]*>([^<]*)<\/a><\/h/i', $content, $list)) {
            foreach ($list[0] as $i=>$result) {
                $r = array ('title'=> $list[2][$i], 'url'=> $list[1][$i]);
                $this->referredpages['list'][] = $r;
            }
        }
    }

    /**
     * Initialise module object in admin/linked mode.
     * @return void
     */
    private function init_admin_linked() {
        global $camyks;

        $this->openTab = 'linked';

        $this->linkedpages = array();
        $this->linkedpages['count'] = 0;
        $this->linkedpages['list'] = array();

        $url = $camyks->site_conf['url'];
        $find = '@^(?:http://)?([^/]+)@i';
        if (preg_match($find, $url, $result)   )
            $url = $result[1];

        $gurl = 'http://www.google.com/search?hl=en&q=link%3A'.urlencode($url).'&btnG=Search';
        $gurl .= '&ie=utf-8&oe=utf-8&num='.$this->maxlinkedpages;

        /* get google page */
        $handle = @fopen($gurl, 'rb');
        $content = stream_get_contents($handle);
        fclose($handle);

        /* parse count result in page */
        if (preg_match('/ <b>([0-9,\ ]*)<\/b> linking/', $content, $count)) {
            $this->linkedpages['count'] = (int)preg_replace('/[^0-9]/', '', $count[1]);
        }

        /* parse list result in page */
        if (preg_match_all('/<h[^>]*><a href="([^"]*)"[^>]*>([^<]*)<\/a><\/h/i', $content, $list)) {
            foreach ($list[0] as $i=>$result) {
                $r = array ('title'=> $list[2][$i], 'url'=> $list[1][$i]);
                $this->linkedpages['list'][] = $r;
            }
        }
    }
}
?>
