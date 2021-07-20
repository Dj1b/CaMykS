<?php
/**
 * @brief Content_TwitterStatusesViewer module.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jul 2010
 * @date Modification: Jul 2021
 * @copyright 2010 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_TwitterStatusesViewer class.
 */
final class Content_TwitterStatusesViewer extends Module {
    /**
     * var Object $configItem
     * @brief Content object.
     */
    protected $configItem;

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('Content_TwitterStatusesViewer', $path_type);

        /* Override Plugin variables */
        $this->plugin_package = 'Twitter';
        $this->version = '1.0';

        /* Override Module variables */
        $this->type = 'content';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Load plugin libraries */
        $this->load_library('Content_TwitterStatusesViewerItem');

        /* Initialise plugin libraries */
        $this->configItem = new Content_TwitterStatusesViewerItem(0, $this);
    }

    /* Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return ($this->configItem->install() and parent::install());
    }

    /**
     * Uninstall module
     * @return boolean success
     */
    public function uninstall() {
        return ($this->configItem->uninstall() and parent::uninstall());
    }

    /**
     * Check module installation
     * @return boolean result
     */
    public function is_installed() {
        return $this->configItem->is_installed();
    }

    /**
     * Return available content ids as list.
     * @return array
     */
    public function get_contentList() {
        return $this->configItem->get_namelist();
    }

    /**
     * Initialise module object in admin mode.
     * @return void
     */
    public function init_admin() {
        /* Generic pre-initialisation */
        parent::preInit_admin();

        /* Check permission for this page */
        if ($this->check_right($this->page_id) === false)
            return $this->init_admin_pageAccessDenied();

        /* Load mode to exexute */
        $this->mode = isset($_REQUEST['mode']) ? $_REQUEST['mode'] : 'edit';

        /* Initialise module with mode */
        switch ($this->mode) {
            case 'save' :
                /* mode == save */
                $this->init_admin_save();
                break;
            case 'edit' :
            default:
                /* mode == edit */
                $this->init_admin_edit();
                break;
        }

        /* Generic admin initialisation */
        parent::init_admin();
    }

    /**
     * Initialise module object in site mode.
     * @param integer $content
     * @param array $params
     * @param integer $mindex
     * @return void
     */
    public function init_site($content=1, $params=array(), $mindex=null) {
        global $camyks;

        /* Save params */
        $this->params = $params;

        /* Load viewer item */
        $this->configItem->id = $content;
        $this->configItem->get();
        $this->configItem->get_fromItems();
        $this->tweets = $this->configItem->load_statuses();

        /* Unserialise XML */
        $this->tweets = xml_unserialize($this->tweets);

        /* Check tweet count */
        if (count($this->tweets['status']) == 0)
            return;

        /* Load user data */
        $this->userData = $this->tweets['status'][0]['user'];

        /* Add tweeter account styles */
        if ($this->configItem->vars['style'] == 1) {
            $this->add_styleScript('.twitterBox'.$this->userData['id'].' {background:#'.$this->userData['profile_background_color'].';}');
            $this->add_styleScript('.twitterBox'.$this->userData['id'].' p {color:#'.$this->userData['profile_text_color'].';}');
            $this->add_styleScript('.twitterBox'.$this->userData['id'].' div {color:#'.$this->userData['profile_text_color'].';}');
            $this->add_styleScript('.twitterBox'.$this->userData['id'].' a {color:#'.$this->userData['profile_link_color'].';}');
        }

        /* Update layout */
        $this->set_selectedLayout('site_'.$this->configItem->vars['layout'].'.html.inc');

        /* Generic site initialisation */
        parent::init_site();
    }

    /* Specific mode methods */

    /**
     * Initialise module in admin / edit mode.
     * @return void
     */
    private function init_admin_edit() {
        global $camyks;

        /* Load object data */
        $this->configItem->id = isset ($_REQUEST['id']) ? (int)$_REQUEST['id'] : 0;
        $this->configItem->get();
        $this->configItem->get_fromItems();

        /* Build tabs */
        $this->tabBuilder = $camyks->get_input('TabBuilder');
        $this->tabBuilder->add_tab(array(
            'name'  => 'properties',
            'title' => $this->get_translation('tabproperties'),
        ));

        /* Add help tab */
        if ($this->help != null)
            $this->tabBuilder(array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help'),
            ));

        /* Initialise tabs */
        $this->tabBuilder->initialise(array('default'=>'properties'));

        /* Build form object */
        $this->form = new HTMLForm('editform', $this->get_adminlink(array('mode'=>'save')), 'POST');
        $this->form->set_object($this->configItem);
        $this->form->add_hidden('id', $this->configItem->id);
        $this->form->add_hidden('page_id', $this->page_id);
        $this->form->add_hidden('module_index', $this->module_index);

        /* Build button interface */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'  => $camyks->get_adminLink('Admin_ContentPage', array(
                    'mode'      => 'modify',
                    'page_id'   => $this->page_id,
                    'openTab'   => 'content',
                )),
            ),
            array(
                'title' => $camyks->get_translation('valid'),
                'link'  => $this->form->get_HTMLSubmitLink(),
            ),
        );
    }

    /**
     * Initialise module in admin / save mode.
     * @return void
     */
    private function init_admin_save() {
        global $camyks;

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Check object id */
        if (!(isset($_REQUEST['id'])))
            $this->init_admin_edit();

        /* Load object */
        $this->configItem->id = (int)$_REQUEST['id'];
        $this->configItem->get_fromHeader();

        /* Save object */
        if ($this->configItem->save()) {
            /* Update page information with object id for new content */
            if ($this->configItem->id == 0 and $this->page_id > 0)
                $this->add_moduleContentToPage($this->page_id, $this->module_index, $this->configItem->id);

            $this->text = $this->get_translation('savedone');
        } else {
            $this->text = $this->get_translation('savefailed');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('mode'=>'edit', 'id'=>$this->configItem->id, 'page_id'=>$this->page_id, 'module_index'=>$this->module_index)));
    }

    /**
     * Return layout list.
     * @return array
     */
    public function get_layoutList() {
        return array('nobox'=>$this->get_translation('layout_nobox'));
    }

    /**
     * Return style values list.
     * @return array
     */
    public function get_styleList() {
        return array(
            0 => $this->get_translation('style_normal'),
            1 => $this->get_translation('style_twitteraccount'),
        );
    }

    /**
     * Return style values list.
     * @return array
     */
    public function get_dateDisplayList() {
        return array(
            0 => $this->get_translation('datedisplay_relative'),
            1 => $this->get_translation('datedisplay_absolutelight'),
            2 => $this->get_translation('datedisplay_absolutefull'),
        );
    }

    /* Site tool methods */

    /**
     * Return updated tweet text.
     * @param string $text
     * @param array $params
     * @return void
     */
    protected function update_tweetText($text, $params=array()) {
        /* Default params */
        $dParams = array('parse_links'=>true, 'link_class'=>'eLink1');
        $params = array_merge($dParams, $params);

        /* Check for link */
        if ($params['parse_links'])
            $text = preg_replace('/(http:\/\/)([^\s]*)/', '<a href="\\1\\2" class="'.$params['link_class'].'" target="_blank">\\2</a>', $text);

        /* Return updated text */
        return $text;
    }

    /**
     * Return formatted date.
     * @param string $date
     * @return string
     */
    protected function display_tweetDate($date) {
        if (isset($this->configItem->vars))
            $mode = $this->configItem->vars['datedisplay'];
        else
            $mode = 1;
        $date = strtotime($date);

        switch ($mode) {
            case 0:
                $d = TODAY - $date;

                /* Check for seconds */
                if ($d < 60)
                    return $this->get_translation('tweetedsomesecondsago');

                /* Check for minutes */
                $d = floor($d/60);
                if ($d == 1)
                    return $this->get_translation('tweetedaminuteago');
                elseif ($d < 90)
                    return $this->get_translation('tweetedxminutesago', $d);

                /* Check for hours */
                $d = floor($d/60);
                if ($d == 1)
                    return $this->get_translation('tweetedanhourago');
                elseif ($d < 72)
                    return $this->get_translation('tweetedxhoursago', $d);

                /* Check for days */
                $d = floor($d/24);
                if ($d < 365)
                    return $this->get_translation('tweetedxdaysago', $d);

                /* Check for years */
                $d = floor($d/365);
                if ($d == 1)
                    return $this->get_translation('tweetedayearago');
                return $this->get_translation('tweetedxyearsago', $d);

                break;
            case 2:
                return date_displayShortDateHour($date);
                break;
            case 1:
            default:
                if (date_isSameDay($date))
                    return date_displayHour($date);
                return date_displayShortDate($date);
            break;
        }
    }

    /**
     * Return border color
     * @param string $default
     * @return string
     */
    protected function get_borderColor($default='888888') {
        if ($this->configItem->vars['style'] == 0)
            return $default;
        return $this->userData['profile_sidebar_border_color'];
    }
}
?>
