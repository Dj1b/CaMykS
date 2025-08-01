<?php
/**
 * @brief Content_GenericHTMLNews module.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.2
 * @date Creation: Dec 2007
 * @date Modification: Jul 2025
 * @copyright 2007 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_GenericHTMLNews class.
 */
final class Content_GenericHTMLNews extends Module {
    /**
     * var array $layouts_list
     * @brief List of available layouts to display lists.
     */
    protected $layouts_list = array('list_box_complete', 'list_box_summary', 'list_box_title', 'list_free_complete', 'list_free_summary', 'list_free_title', 'list_custom');

    /**
     * var array $layouts_item
     * @brief List of available layouts to display items.
     */
    protected $layouts_item = array('box_item_complete', 'item_free_complete', 'item_custom');

    /**
     * var integer $newsbypage
     * @brief Stores how many news to display in admin page.
     */
    protected $newsbypage = 16;

    /**
     * var array $status
     * @brief Available statuses for items.
     */
    protected $status = array(0 => 'inedition', 1 => 'inline');

    /**
     * var array $status
     * @brief Available statuses for items.
     */
    protected $newspage;

    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('Content_GenericHTMLNews', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'Generic';

        /* Override Module variables */
        $this->type = 'content';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Load plugin libraries */
        $this->load_library('Content_GenericHTMLNewsList');
        $this->load_library('Content_GenericHTMLNewsItem');

        /* Initialise plugin libraries */
        $this->newslist = new Content_GenericHTMLNewsList(0, $this);
        $this->newsitem = new Content_GenericHTMLNewsItem(0, $this);
    }

    /* Mark: Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return ($this->newslist->install() and $this->newsitem->install() and parent::install());
    }

    /**
     * Uninstall module.
     * @return boolean success
     */
    public function uninstall() {
        return $this->newsitem->uninstall() and $this->newslist->uninstall();
    }

    /**
     * Check module installation.
     * @return boolean success
     */
    public function is_installed() {
        return $this->newsitem->is_installed();
    }

    /**
     * Return available content ids as list.
     * @return array
     */
    public function get_contentList() {
        return $this->newslist->get_namelist();
    }

    /**
     * Initialise module in admin mode.
     * @return void
     */
    public function init_admin() {
        global $camyks;

        /* Generic module pre-init */
        parent::preinit_admin();

        /* Check permission for this page */
        if ($this->check_right($this->page_id) === false)
            return $this->init_admin_pageAccessDenied();

        /* Check dependencies */
        if (!isset($camyks->inputs['TabBuilder']))
            return $this->init_admin_missingPlugin('Input', 'TabBuilder');
        if (!isset($camyks->inputs['AdminItemListViewer']))
            return $this->init_admin_missingPlugin('Input', 'AdminItemListViewer');
        if (!isset($camyks->inputs['TinyMCEv3']) and !isset($camyks->inputs['TinyMCE']))
            return $this->init_admin_missingPlugin('Input', 'TinyMCEv3');

        /* Load mode */
        $this->mode = isset($_REQUEST['mode']) ? $_REQUEST['mode'] : 'view_list';

        /* Initialise module with mode */
        switch ($this->mode) {
            case 'edit_item' :
                /* mode == edit_item */
                $this->init_admin_edit_item();
                break;
            case 'save_item' :
                /* mode == save_item */
                $this->init_admin_save_item();
                break;
            case 'delete_item' :
                /* mode == delete_item */
                $this->init_admin_delete_item();
                break;
            case 'edit_list':
                /* mode == edit_list */
                $this->init_admin_edit_list();
                break;
            case 'save_list' :
                /* mode == save_list */
                $this->init_admin_save_list();
                break;
            case 'view_list' :
            default:
                /* mode == view_list */
                $this->init_admin_view_list();
                break;
        }

        /* Generic module initialisation */
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

        /* Add email management javascripts */
        $this->add_JSEngineFile('tool/mail.js');

        /* Load news list to display */
        $this->newslist->id = $content;
        $this->newslist->get();
        $this->newslist->get_fromItems();

        if (isset ($params['newsitem']) and $params['newsitem'] >= 0) {
            /* get single item init */
            $this->init_site_item ($params);
        } else {
            /* get news list init */
            $this->init_site_list($params);
        }

        /* Generic Module initialisation */
        parent::init_site();
    }

    /**
     * Execute module object in request mode.
     * @return void
     */
    public function execute_request() {
        global $camyks;

        /* Check if newslist info is available */
        if (!isset($_REQUEST['newslist']))
            die();

        /* Check language */
        if (!isset($_REQUEST['_clg_']))
            die();

        /* Check page */
        if (!isset($_REQUEST['page']))
            die();

        /* Load database connection */
        $camyks->get_databaseConnection();
        $camyks->get_currentLanguage('site');

        /* Load camyks content page module */
        $camyks->modules['Admin_ContentPage'] = module_get('Admin_ContentPage');

        /* Load newslist item */
        $this->newslist->id = (int)$_REQUEST['newslist'];
        $this->newslist->get();
        $this->newslist->get_fromItems();

        /* Check if RSS is enabled */
        if ($this->newslist->vars['enablerss'] != 1)
            die();

        /* Load RSS input */
        $rssInput = input_get('GenericRSSFeed');

        if ($rssInput === false)
            die();

        /* Load items */
        $newsitems = $this->newsitem->get_lastItemsList($this->newslist->id, $camyks->current_language, $this->newslist->vars['count_list']);

        /* Build rss config */
        $config = array();
        $config['title'] = $this->get_translation('rss_title');
        $config['link'] = $camyks->_conf['url'].'/'.$camyks->get_siteLink($_REQUEST['page'], '', $camyks->current_language);
        $config['description'] = $this->get_translation('rss_description', $camyks->_conf['site_title']);
        $config['language'] = $camyks->current_language;

        /* Build items list */
        $items = array();
        foreach ($newsitems as $news) {
            $item = array();
            $item['title'] = $news->vars['title'];
            $item['link'] = $camyks->_conf['url'].'/'.$camyks->get_siteLink($_REQUEST['page'], '', $camyks->current_language, array('newsitem'=>$news->id));
            $item['description'] = $news->vars['summary'];
            $item['isPermalink'] = 'true';
            $item['date'] = $news->vars['ndate'];
            $items[] = $item;
        }

        /* Build RSS XML */
        $rssInput->initialise($config, $items);
        $rssInput->display();
    }

    /* Mark: Admin initialise mode sub methods */

    /**
     * Initialise module in admin / view_list mode.
     * @return void
     */
    private function init_admin_view_list() {
        global $camyks;

        /* Load object id */
        if ($this->id == 0)
            return $this->init_admin_edit_list();

        /* Load object data */
        $this->newslist->id = $this->id;
        $this->newslist->get();
        $this->newslist->get_fromItems();
        if ($this->newslist->id == 0)
            return $this->init_admin_edit_list();

        /* Build tabs */
        $this->tabBuilder = $camyks->get_input('TabBuilder');
        $this->tabBuilder->add_tabs(array(
            array(
                'name'  => 'properties',
                'title' => $this->get_translation('tabproperties'),
            ),
            array(
                'name'  => 'newsitems',
                'title' => $this->get_translation('tabnewsitems'),
            ),
        ));
        $this->tabBuilder->initialise(array('default'=>'newsitems'));

        /* Build news list */
        $this->load_library('Content_GenericHTMLNewsListParams');
        $this->listObject = $camyks->get_input('AdminItemListViewer');
        $this->listObject->set_params($this->newsListParams);
        $this->listObject->initialise();

        /* Check for RSS Input */
        $this->rssAvailable = isset($camyks->inputs['GenericRSSFeed']);

        /* Build buttons list */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'  => $camyks->get_adminLink('Admin_ContentPage', array(
                    'mode'      => 'modify',
                    'page_id'   => $this->page_id,
                    'openTab'   => 'content',
                )),
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('admin_view_list.html.inc');
    }

    /**
     * Initialise module in admin / edit_list mode.
     * @return void
     */
    private function init_admin_edit_list() {
        global $camyks;

        /* Load object data */
        $this->newslist->id = $this->id;
        $this->newslist->get();
        $this->newslist->get_fromItems();

        /* Check for RSS Input */
        $this->rssAvailable = isset($camyks->inputs['GenericRSSFeed']);

        /* get form object */
        $this->form = new HTMLForm('newslist_form', $this->get_adminlink(array('mode'=>'save_list')), 'POST');
        $this->form->add_hidden('id', $this->newslist->id);
        $this->form->add_hidden('page_id', $this->page_id);
        $this->form->add_hidden('module_index', $this->module_index);

        if ($this->id == 0)
            $link = $camyks->get_adminLink('Admin_ContentPage', array('mode'=>'modify', 'page_id'=> $this->page_id, 'openTab'=>'content'));
        else
            $link = $this->get_adminLink();

        /* Build button list */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'  => $link
            ),
            array(
                'title' =>$camyks->get_translation('valid'),
                'link'  =>$this->form->get_HTMLSubmitLink(),
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('admin_edit_list.html.inc');
    }

    /**
     * Initialise module in admin / save_list mode
     * @return void
     */
    private function init_admin_save_list() {
        global $camyks;

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Load object */
        $this->newslist->id = $this->id;
        $this->newslist->get_fromHeader();

        /* Save object */
        if ($this->newslist->save()) {
            /* Update page information with object id for new content */
            if ($this->id == 0 and $this->page_id > 0) {
                $this->add_moduleContentToPage($this->page_id, $this->module_index, $this->newslist->id);
                $this->id = $this->newslist->id;
            }
            $this->text = $this->get_translation('newslistsaved');
        } else {
            $this->text = $this->get_translation('newslistnotsaved');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /**
     * Initialise module in admin / save_item mode.
     * @return void
     */
    private function init_admin_save_item() {
        global $camyks;

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Load object */
        $this->newsitem->id = isset($_REQUEST['news_id']) ? (int)$_REQUEST['news_id'] : 0;
        $this->newsitem->get_fromHeader();

        /* Save object */
        if ($this->newsitem->save()) {
            $this->text = $this->get_translation('newsitemsaved');
        } else {
            $this->text = $this->get_translation('newsitemnotsaved');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /**
     * Initialise module in admin / edit_item mode.
     * @return void
     */
    private function init_admin_edit_item() {
        global $camyks;

        /* Load object data */
        $this->newsitem->id = isset($_REQUEST['news_id']) ? (int)$_REQUEST['news_id'] : 0;
        $this->newsitem->get();
        $this->newsitem->get_fromItems();
        if ($this->newsitem->id == 0)
            $this->newsitem->vars['listid'] = $this->id;

        /* Build form object */
        $this->form = new HTMLForm ('newsitem_form', $this->get_adminlink(array('mode'=>'save_item')), 'POST');
        $this->form->set_object($this->newsitem);
        $this->form->add_hidden('id', $this->newsitem->vars['listid']);
        $this->form->add_hidden('news_id', $this->newsitem->id);
        $this->form->add_hidden('listid', $this->newsitem->vars['listid']);
        $this->form->add_hidden('author', $this->newsitem->vars['author']);
        $this->form->add_hidden('page_id', $this->page_id);
        $this->form->add_hidden('module_index', $this->module_index);

        /* build tabs */
        $this->tabBuilder = $camyks->get_input('TabBuilder');
        $this->tabBuilder->add_tabs(array(
            array(
                'name'  => 'properties',
                'title' => $this->get_translation('tabproperties'),
            ),
            array(
                'name'  => 'content',
                'title' => $this->get_translation('tabcontent'),
            ),
        ));
        $this->tabBuilder->initialise(array('default'=>'newsitems'));

        /* Load HTML Editor with default configuration */
        if (isset($camyks->inputs['TinyMCEv3'])) {
            $this->input = $camyks->get_input('TinyMCEv3');
        } elseif (isset($camyks->inputs['TinyMCE'])) {
            $this->input = $camyks->get_input('TinyMCE');
            $this->input->set_configInfos('default');
        }
        $this->input->set_contentInfos('file', $this->newsitem->vars['content']);
        $this->input->set_textareaInfos('content', '100%', '400px');
        $this->input->initialise();

        /* Build button list */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'  => $this->get_adminLink(),
            ),
            array(
                'title' => $camyks->get_translation('valid'),
                'link'  => $this->form->get_HTMLSubmitLink(),
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('admin_edit_item.html.inc');
    }

    /**
     * Initialise module in admin / delete_item mode.
     * @return void
     */
    private function init_admin_delete_item() {
        global $camyks;

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Load object */
        $this->newsitem->id = isset ($_REQUEST['news_id']) ? (int)$_REQUEST['news_id'] : 0;
        $this->newsitem->get();
        $this->newsitem->get_fromItems();

        /* Delete object */
        if ($this->newsitem->vars['listid'] == $this->id and $this->newsitem->delete()) {
            $this->text = $this->get_translation('newsitemdeleted');
        } else {
            $this->text = $this->get_translation('newsitemnotdeleted');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /* Mark: Site initialise mode sub methods */

    /**
     * Initialise module object in site / list mode.
     * @param array $params
     * @return void
     */
    private function init_site_list($params) {
        global $camyks;

        /* Load news page to display */
        if (isset ($params['newspage']) and $params['newspage'] >= 0)
            $this->newspage = $params['newspage'];
        else
            $this->newspage = 0;

        /* Load news items to display from news list */
        $this->newsitems = $this->newsitem->get_siteList($this->newslist->id, $this->newspage, $this->newslist->vars['count_list']);
        $this->newscount = $this->newsitem->get_listcount($this->newslist->id, 1, $camyks->current_language, true);

        /* Build buttons list */
        if ($this->newscount > $this->newslist->vars['count_list']) {
            if (($this->newspage+1)*$this->newslist->vars['count_list'] < $this->newscount)
                $this->nextnews = $camyks->get_siteLink($camyks->contentPage->id, $camyks->contentPage->name, '', array('newspage'=> $this->newspage+1));
            else
                $this->nextnews = '';

            if ($this->newspage > 0)
                $this->prevnews = $camyks->get_siteLink($camyks->contentPage->id, $camyks->contentPage->name, '', array('newspage'=> $this->newspage-1));
            else
                $this->prevnews = '';

            /* Build button list */
            $this->buttons = array(
                array(
                    'title' => $this->get_translation('previousnews'),
                    'link'  => $this->prevnews
                ),
                array(
                    'title' => $this->get_translation('page', array($this->newspage+1)),
                    'link'  => '',
                ),
                array(
                    'title' => $this->get_translation('nextnews'),
                    'link'  => $this->nextnews,
                ),
            );
        }

        /* Check for RSS Feed link */
        if (isset($camyks->inputs['GenericRSSFeed']) and ($this->newslist->vars['enablerss'] == 1)){
            $rssURL = $camyks->_conf['url'].'/request.php?module='.$this->name;
            $rssURL .= '&amp;newslist='.$this->newslist->id;
            $rssURL .= '&amp;_clg_='.$camyks->current_language;
            $rssURL .= '&amp;page='.$camyks->contentPage->name;
            $this->set_RSSFeed($rssURL, $this->get_translation('rss_title'));
        }

        /* Load social network sharing */
        $this->networkInput = $camyks->get_input('SocialNetworksSharingPanel');
        if ($this->networkInput !== false)
            $this->networkInput->initialise(array('text'=>$this->get_translation('shareon'), 'separator'=>'', 'block_class'=>'share'));

        /* Update layout */
        $this->set_selectedLayout('site_'.$this->newslist->vars['layout_list'].'.html.inc');
    }

    /**
     * Initialise module object in site / item mode.
     * @param array $params
     * @return void
     */
    private function init_site_item($params) {
        global $camyks;

        /* Load news item object */
        $this->newsitem->id = $params['newsitem'];
        if (!$this->newsitem->get())
            return $this->init_site_list($params);
        $this->newsitem->get_fromItems();

        /* Update page title */
        $camyks->HTMLPage->page_title .= ' - '. $this->newsitem->vars['title'];

        /* Check if object is valid */
        if (($this->newsitem->vars['language'] != $camyks->current_language) or ($this->newsitem->vars['status'] == 0) or ($this->newsitem->vars['listid'] != $this->newslist->id))
            return $this->init_site_list($params);


        /* Check for social network sharing */
        $this->networkInput = $camyks->get_input('SocialNetworksSharingPanel');
        if ($this->networkInput !== false) {
            /* load picture to share */
            if (preg_match('/src="([^"]{1,})"/', $this->newsitem->vars['content'], $matches)) {
                $picture = $matches[1];
                if (!preg_match('/^https?:\/\//', $picture, $s))
                    $picture = $camyks->get_confValue('url').'/'.$picture;
            } else {
                $picture = '';
            }

            /* load input */
            $this->networkInput = &$camyks->inputs['SocialNetworksSharingPanel'];
            $this->networkInput->initialise(array(
                'text'          => $this->get_translation('shareon'),
                'separator'     => '',
                'block_class'   => 'share',
                'link'          => $this->get_singlenewslink($this->newsitem->id),
                'title'         => $this->newsitem->vars['title'],
                'summary'       => $this->newsitem->vars['summary'],
                'image'         => $picture,
                'type'          => 'article',
           ));
        }

        /* Build button list */
        $this->buttons = array(
            array(
                'title' => $this->get_translation('back'),
                'link'  => $camyks->get_siteLink($camyks->contentPage->id, $camyks->contentPage->name),
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('site_'.$this->newslist->vars['layout_item'].'.html.inc');
    }

    /* Specific admin tool methods */

    /**
     * Return list layout values.
     * @return array
     */
    protected function get_listLayoutList() {
        $list = array();
        foreach($this->layouts_list as $l)
            $list[$l] = $this->get_translation($l);
        return $list;
    }

    /**
     * Return news layout values.
     * @return array
     */
    protected function get_newsLayoutList() {
        $list = array();
        foreach($this->layouts_item as $l)
            $list[$l] = $this->get_translation($l);
        return $list;
    }

    /**
     * Return news status values.
     * @return array
     */
    protected function get_newsStatusList() {
        $list = array();
        foreach($this->status as $s => $n) {
            $list[$s] = $this->get_translation($n);
        }
        return $list;
    }

    /**
     * Return news language values.
     * @return array
     */
    protected function get_newsLanguageList() {
        global $camyks;
        $list = array();
        foreach($camyks->_conf['editing_languages'] as $l)
            $list[$l] = $camyks->get_translation('lang_'.$l);
        return $list;
    }

    /* Specific site tool methods */

    /**
     * Return current page single news link.
     * @param integer $id
     * @return string
     */
    protected function get_singlenewslink($id) {
        global $camyks;
        return $camyks->get_confValue('url').'/'.$camyks->get_siteLink ($camyks->contentPage->id, $camyks->contentPage->name, '', array('newsitem'=>$id));
    }

    /**
     * Return last news.
     * @param integer $listid
     * @param integer $count
     * @return array
     */
    protected function get_lastNewsList($listid, $count=null) {
        global $camyks;

        /* Load newslist item */
        $this->newslist->id = $listid;
        if ($this->newslist->get() === false)
            return array();
        $this->newslist->get_fromItems();

        /* Check count value */
        if (!isset($count))
            $count = $this->newslist->vars['count_list'];

        /* Return items */
        return $this->newsitem->get_lastItemsList($this->newslist->id, $camyks->current_language, $count);
    }
}
?>
