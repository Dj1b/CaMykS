<?php
/**
 * @brief Content_GenericBlogsViewer module.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Apr 2008
 * @date Modification: Jul 2021
 * @copyright 2008 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_GenericBlogsViewer class.
 */
final class Content_GenericBlogsViewer extends Module {
    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('Content_GenericBlogsViewer', $path_type);

        /* Override Plugin variables */
        $this->version = '1.01';
        $this->plugin_package = 'Generic';

        /* Override Module variables */
        $this->type = 'content';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Load plugin libraries */
        $this->load_library('Content_GenericBlogsViewerItem');

        /* Initialise plugin libraries */
        $this->configItem = new Content_GenericBlogsViewerItem(0, $this);
    }

    /* Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return $this->configItem->install() and parent::install();
    }

    /**
     * Uninstall module.
     * @return boolean success
     */
    public function uninstall() {
        return $this->configItem->uninstall();
    }

    /**
     * Check module installation.
     * @return boolean result
     */
    public function is_installed() {
        return $this->configItem->is_installed();
    }

    /**
     * Return available content ids as list
     * @return array
     */
    public function get_contentList() {
        return $this->configItem->get_namelist();
    }

    /**
     * Update module.
     * @return boolean success
     */
    public function update($version, $more='') {
        global $camyks;

        /* Check version 1.01 */
        if (version_compare($this->version, $version) === 1)
            if ($this->configItem->update_toVersion1_01() === false)
        return false;

        /* Generic update */
        return parent::update($version, $more);
    }

    /**
     * Initialise module object in admin mode.
     * @return void
     */
    public function init_admin() {
        global $camyks;

        /* Generic pre-initialisation */
        parent::preInit_admin();

        /* Check right for this page */
        if ($this->check_right($this->page_id) === false)
            return $this->init_admin_pageAccessDenied();

        /* Load mode to execute */
        $this->mode = isset ($_REQUEST['mode']) ? $_REQUEST['mode'] : 'edit';

        /* Execute mode */
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

        /* Generic module init */
        parent::init_admin();
    }

    /**
     * Initialise module object in site mode.
     * @param int $content
     * @param array $params
     * @param int $mindex
     * @return void
     */
    public function init_site($content=1, $params=array(), $mindex=null) {
        global $camyks;

        /* Add email management javascripts */
        $this->add_JSEngineFile('tool/mail.js');

        /* Save params */
        $this->params = $params;

        /* Load manager */
        $this->load_blogManager();
        if ($this->manager === false)
            return false;

        /* Load blog manager config */
        $this->manager->config->get();

        /* Load authors list */
        $this->authorList = $camyks->modules['Admin_User']->get_userList();

        /* Load blog article list to display */
        $this->configItem->id = $content;
        $this->configItem->get();
        $this->configItem->get_fromItems();

        /* Initialise social network sharing panel */
        if ($this->configItem->vars['snsp_status'] == 1 and isset($camyks->inputs['SocialNetworksSharingPanel'])) {
            $this->networkInput = &$camyks->inputs['SocialNetworksSharingPanel'];
            $this->networkInput->initialise(array('text'=>$this->get_translation('site_shareon')));
        } else
            $this->networkInput = false;

        /* Check for RSS Feed link */
        if ($this->configItem->vars['enablerss'] == 1 and isset($camyks->inputs['GenericRSSFeed'])) {
            $st = $camyks->_conf['site_title'];
            if (count($this->configItem->vars['authors_']) == 0)
                $t = $this->get_translation('rss_title0', $st);
            elseif (count($this->configItem->vars['authors_']) == 1)
                $t = $this->get_translation('rss_title1', array($st, $this->configItem->vars['authors_']));
            else
                $t = $this->get_translation('rss_titlex', $st);

            $rssURL = $camyks->_conf['url'].'/request.php?module='.$this->name;
            $rssURL .= '&amp;blog='.$this->configItem->id;
            $rssURL .= '&amp;page='.$camyks->contentPage->name;
            $this->set_RSSFeed($rssURL, $t);
        }

        /* Check mode to display */
        if (isset ($this->params['blogitem']) and $this->params['blogitem'] >= 0)
            $this->init_site_item();
        else
            $this->init_site_list();

        /* Parent site init */
        parent::init_site();
    }

    /**
     * Execute module object in request mode.
     * @return void
     */
    public function execute_request() {
        global $camyks;

        /* Check if newslist info is available */
        if (!isset($_REQUEST['blog']))
            die();

        /* Check page */
        if (!isset($_REQUEST['page']))
            die();

        /* Load database connection */
        $camyks->get_databaseConnection();
        $camyks->get_currentLanguage('site');

        /* Load camyks content page module */
        $camyks->modules['Admin_ContentPage'] = module_get('Admin_ContentPage');

        /* Load article list */
        $this->configItem->id = $_REQUEST['blog'];
        $this->configItem->get();
        $this->configItem->get_fromItems();

        /* Check if RSS is enabled */
        if ($this->configItem->vars['enablerss'] != 1)
            die();

        /* Load input */
        $rssInput = input_get('GenericRSSFeed');
        if ($rssInput === false)
            die();

        $manager = module_get('Admin_GenericBlogsManager');
        if ($manager === false)
            die();

        /* Load items */
        $newsItems = $manager->newsItem->get_blogItemlist($this->configItem->vars['authors_'], null, 0, 20, true);

        /* build rss config */
        $config = array();

        /* build title & description */
        $st = string_html2text($camyks->get_confValue('site_title'));
        if (count($this->configItem->vars['authors_']) == 0)
            $t = $this->get_translation('rss_title0', $st);
        elseif (count($this->configItem->vars['authors_']) == 1)
            $t = $this->get_translation('rss_title1', array($st, $this->configItem->vars['authors_']));
        else
            $t = $this->get_translation('rss_titlex', $st);

        if ($this->configItem->vars['title'] != '') {
            $config['title'] = $this->get_translation('rss_description', $this->configItem->vars['title']);
            $config['description'] = $t;
        } else {
            $config['title'] = $t;
            $config['description'] = '';
        }

        /* Build link */
        $config['link'] = $camyks->get_rootBaseURL('absolute_long').$camyks->get_siteLink($_REQUEST['page']);

        /* Build items list */
        $items = array();
        foreach ($newsItems as $news) {
            $item = array();
            $item['title'] = $news->vars['title'];
            $item['link'] = $camyks->get_rootBaseURL('absolute_long').$camyks->get_siteLink($_REQUEST['page'], '', '', array('blogitem'=>$news->id));
            $item['description'] = $news->vars['content'];
            $item['date'] = $news->vars['ndate'];
            $item['isPermalink'] = 'true';
            $items[] = $item;
        }

        /* Build RSS XML */
        $rssInput->initialise($config, $items);
        $rssInput->display();
    }

    /* Specific mode methods */

    /**
     * Initialise module in admin / edit mode.
     * @return void
     */
    private function init_admin_edit() {
        global $camyks;

        /* Load object data */
        $this->configItem->id = isset($_REQUEST['id']) ? (int)$_REQUEST['id'] : 0;
        $this->configItem->get();
        $this->configItem->get_fromItems();

        /* Load authors list */
        $this->authorList = $camyks->modules['Admin_User']->get_userList();

        /* check for Inputs */
        $this->rssAvailable = isset($camyks->inputs['GenericRSSFeed']);
        $this->gpcAvailable = isset($camyks->inputs['GenericPageController']);
        $this->snspAvailable = isset($camyks->inputs['SocialNetworksSharingPanel']);

        /* Build form object */
        $this->form = new HTMLForm ('blog_form', $this->get_adminlink(array('mode'=>'save')), 'POST');
        $this->form->set_object($this->configItem);
        $this->form->add_hidden('id', $this->configItem->id);
        $this->form->add_hidden('page_id', $this->page_id);
        $this->form->add_hidden('module_index', $this->module_index);
        $this->form->add_hidden('authorsCount', count($this->authorList));

        /* Add form related scripts */
        $this->add_JSScript('var genericblogsviewerform="'.$this->form->name.'";');
        $this->add_JSFile('genericblogsviewer.js');

        /* Build interface buttons */
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
     * Initialise module in admin / save mode
     * @return void
     */
    private function init_admin_save() {
        global $camyks;

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Load object id */
        if (!(isset($_REQUEST['id'])))
            $this->init_admin_edit();

        /* Save object */
        $this->configItem->id = (int)$_REQUEST['id'];
        $this->configItem->get_fromHeader();
        if ($this->configItem->save()) {
            /* Update page information with object id for new content */
            if ($this->configItem == 0 and $this->page_id > 0)
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
     * Initialise module in site / list mode.
     * @return void
     */
    private function init_site_list() {
        global $camyks;

        $params = array();

        /* Load blog page to display */
        $params['pageCurrent'] = isset($this->params['blogpage']) ? $this->params['blogpage'] : 0;

        /* Load other search params */
        $pageParams = array();
        if (isset($this->params['blogauthor']) and (count($this->configItem->vars['authors_']) == 0 or in_array($this->params['blogauthor'], $this->configItem->vars['authors_']))) {
            $author = array($this->params['blogauthor']);
            $pageParams['blogauthor'] = $this->params['blogauthor'];
        } else {
            $author = $this->configItem->vars['authors_'];
        }
        if (isset($this->params['blogtag']) and $this->params['blogtag']!='') {
            $tag = $this->params['blogtag'];
            $pageParams['blogtag'] = $this->params['blogtag'];
        } else {
            $tag = null;
        }

        /* Load total item count */
        $this->blogItemCount = $this->manager->newsItem->get_blogItemCount($author, $tag, true);

        if ($this->configItem->vars['gpc_status']==1 and isset($camyks->inputs['GenericPageController'])) {

            /* Load controller params */
            $params['pageCount'] = ceil($this->blogItemCount / $this->configItem->vars['list_count']);
            $params['pageParams'] = array($camyks->contentPage->id,$camyks->current_language, $pageParams);
            $params['pageParam'] = 'blogpage';

            if ($params['pageCount'] > 0 and $params['pageCurrent'] >= $params['pageCount'])
                $params['pageCurrent'] = $params['pageCount']-1;
            if ($this->configItem->vars['gpc_source'] == 0) {
                $params['buttonSource'] = 'theme';
                $params['styleSource'] = 'theme';
            } else {
                $params['buttonSource'] = 'plugin';
                $params['styleSource'] = 'plugin';
            }

            /* Load page controller */
            $this->pageController = &$camyks->inputs['GenericPageController'];
            $this->pageController->initialise($params);
        } else {
            $this->pageController = false;

            /* load internal controller */
            $this->build_listInternalButtonList($params['pageCurrent']);
        }

        /* Load blog items to display */
        if ($this->blogItemCount > 0)
            $this->blogItems = $this->manager->newsItem->get_blogItemList($author, $tag, $params['pageCurrent'], $this->configItem->vars['list_count'], true);
        else
            $this->blogItems = array();

        /* Check tool panel display */
        if ($this->configItem->vars['list_panel'] == 1)
            $this->init_site_panel();

        /* Update layout to display */
        $this->set_selectedLayout('site_'.$this->configItem->vars['list_layout'].'.html.inc');
    }

    /**
     * Initialise module object in site item mode.
     * @return void
     */
    private function init_site_item() {
        global $camyks;

        /* Load news object */
        $this->blogItem = &$this->manager->newsItem;

        /* Load news object data */
        $this->blogItem->id = $this->params['blogitem'];
        if ($this->blogItem->get() === false or $this->blogItem->check_siteDisplay($this->configItem->vars['authors_'])===false)
            return $this->init_site_list();

        $this->blogItem->get_fromItems();
        $this->blogItem->get_tagList();

        /* Update page title */
        $camyks->HTMLPage->page_title .= ' - '. $this->blogItem->vars['title'];

        /* Check comment mode */
        $this->com_mode = isset($_REQUEST['com_mode']) ? $_REQUEST['com_mode'] : 'form';
        $this->com_error = '';
        $this->commentItem = &$this->manager->commentItem;

        /* Execute comment actions */
        if ($this->com_mode == 'form') {
            $this->init_site_item_comment_form();
        } else if ($this->com_mode == 'save') {
            $this->init_site_item_comment_save();
        } else {
            /* nothing to do */
        }
        $this->commentItem->get_fromItems();
        $this->blogItem->get_blogComments();

        /* Build interface buttons list */
        $this->buttons = array(
            array(
                'title' => $this->get_translation('site_back'),
                'link'  => $camyks->get_siteLink($camyks->contentPage->id, $camyks->contentPage->name),
            ),
        );

        /* Check tool panel display */
        if ($this->configItem->vars['item_panel'] == 1)
            $this->init_site_panel();

        /* Update layout to display */
        $this->set_selectedLayout('site_'.$this->configItem->vars['item_layout'].'.html.inc');
    }

    /* Specific tool methods in admin mode */

    /**
     * Initialise tool panel in site mode.
     * @return void
     */
    public function init_site_panel() {
        global $camyks;

        /* Load author list including news count */
        $this->panel_authors = $this->manager->newsItem->get_newsCountByAuthor($this->configItem->vars['authors_'], true);

        /* Load tag list includin news count */
        $this->panel_tags = $this->manager->newsItem->get_newsCountByTag($this->configItem->vars['authors_'], true);

        /* Load link list */
        $this->panel_links = $this->manager->linkItem->get_linkListByAuthor($this->configItem->vars['authors_'], true);
    }

    /**
     * Initialise module object in site item/comment form mode
     * @return void
     */
    public function init_site_item_comment_form() {
        global $camyks;
        $camyks->set_sessionValue('blogcommentpost', 0);
        $this->com_form = new HTMLForm('com_form', $camyks->get_siteCurrentLink(), 'POST');
        $this->com_form->add_hidden('com_mode', 'save');
    }

    /**
     * Initialise module object in site item/comment save mode
     * @return void
     */
    public function init_site_item_comment_save() {
        global $camyks;

        /* Check "reload action" */
        if ($camyks->get_sessionValue('blogcommentpost', 1)==1)
            return;

        /* Update reload action session value */
        $camyks->set_sessionValue('blogcommentpost', 1);

        /* Load comment */
        $this->commentItem->get_fromHeader();

        /* Complete data */
        $this->commentItem->_libItems['status']->value = $this->manager->config->vars['comments_validationmode'];
        $this->commentItem->_libItems['newsid']->value = $this->params['blogitem'];
        $this->commentItem->_libItems['ndate']->value = mktime();
        $this->commentItem->_libItems['ipaddress']->value = client_getIp();

        /* Save comment */
        if ($this->commentItem->save() == false) {
            $this->com_mode = 'form';
            $this->com_error = $this->commentItem->_libError;
            return $this->init_site_item_comment_form();
        }
    }

    /**
     * Return list layouts list.
     * @return array
     */
    protected function get_listLayouts() {
        return array('list_box'=>$this->get_translation('layout_list_box'));
    }

    /**
     * Return item layouts list.
     * @return array
     */
    protected function get_itemLayouts() {
        return array('item_box'=>$this->get_translation('layout_item_box'));
    }

    /* Specific tool methods in site mode */

    /**
     * Load blog manager module.
     * @return void
     */
    private function load_blogManager() {
        global $camyks;
        $this->manager = $camyks->get_module('Admin_GenericBlogsManager');
    }

    /**
     * Return blog news content display.
     * @param string $content
     * @return string
     */
    protected function get_blogNewsContentDisplay($content) {
        global $camyks;

        /* Check manager config */
        switch($this->manager->config->vars['news_editormode']) {
            case 0 :
                return '<p class="eContent1">'.nl2br($content).'</p>';
            case 1 :
                return '<p class="eContent1">'.$content.'</p>';
            default:
                return $content;
        }
    }

    /**
     * Return blog news author display.
     * @param string $author
     * @param string $css
     * @return string
     */
    protected function get_blogNewsAuthorDisplay($author, $css='') {
        global $camyks;

        /* Check given author into author list */
        if (!isset($this->authorList[$author]))
            return $author;

        /* Build author name */
        if ($this->authorList[$author]['firstname']!='' and $this->authorList[$author]['lastname']!='')
            $name = $this->authorList[$author]['firstname'].' '.$this->authorList[$author]['lastname'];
        else if ($this->authorList[$author]['firstname']!='')
            $name = $this->authorList[$author]['firstname'];
        else if ($this->authorList[$author]['lastname']!='')
            $name = $this->authorList[$author]['lastname'];
        else
            $name = $author;

        /* Build result link */
        $a = '<a ';
        if ($css!='')
            $a .= 'class="'.$css.'" ';
        $a.= 'href="'.$camyks->get_siteLink($camyks->contentPage->id, $camyks->contentPage->name, '', array('blogauthor'=>$author));
        $a.= '">'.$name.'</a>';
        return $a;
    }

    /**
     * Return blog news tag list display.
     * @param array $tags
     * @param string $css
     * @return string
     */
    protected function get_blogNewsTagsDisplay($tags, $css='') {
        global $camyks;

        /* Check tags */
        if (count($tags) == 0)
            return '';

        /* Check css value */
        if ($css!='')
            $css = 'class="'.$css.'" ';

        /* Build tags */
        $tags_ = array();
        foreach($tags as $tag) {
            $t= '<a '.$css.'href="'.$camyks->get_siteLink($camyks->contentPage->id, $camyks->contentPage->name, '', array('blogtag'=>$tag->vars['name']));
            $t.='">'.$tag->vars['title'].'</a>';
            $tags_[] = $t;
        }

        /* Return formatted tag list */
        return implode(', ', $tags_);
    }

    /**
     * Return blog news comments link display.
     * @param integer $blogitem
     * @param integer $comments
     * @param string $css
     * @return string
     */
    protected function get_blogNewsCommentsDisplay($blogitem, $comments, $css='') {
        global $camyks;

        /* Check comment count */
        if ($comments == 0) {
            $text = $this->get_translation('site_nocomment');
        } else if ($comments == 1) {
            $text = $this->get_translation('site_1comment');
        } else {
            $text = $this->get_translation('site_xcomments', $comments);
        }

        /* Build comments link */
        $a = '<a ';
        if ($css!='')
            $a .= 'class="'.$css.'" ';
        $a.= 'href="'.$this->get_singleNewsLink($blogitem).'#comments"';
        $a.='>'.$text.'</a>';

        /* Return built link */
        return $a;
    }

    /**
     * Build site single item link.
     * @param integer $newsid
     * @return string;
     */
    protected function get_singleNewsLink($newsid) {
        global $camyks;
        return $camyks->get_confValue('url').'/'.$camyks->get_siteLink($camyks->contentPage->id, $camyks->contentPage->name, '', array('blogitem'=>$newsid));
    }

    /**
     * Return last news from selected blog
     * @param integer $blogid
     * @param integer $count
     * @return array
     */
    protected function get_lastNewsList($blogid, $count=null) {
        global $camyks;

        /* load blog manager */
        if (!isset($camyks->modules['Admin_GenericBlogsManager']))
            return array();
        $this->manager = $camyks->modules['Admin_GenericBlogsManager'];

        /* Load viewer object */
        $this->configItem->id = $blogid;
        if ($this->configItem->get() === false)
            return array();
        $this->configItem->get_fromItems();

        if (!isset($count))
            $count = $this->configItem->vars['list_count'];

        /* Return news list */
        return $this->manager->newsItem->get_blogItemlist($this->configItem->vars['authors_'], null, 0, $count, true);
    }

    /**
     * Build list internal button list.
     * @param integer $page
     * @return void
     */
    protected function build_listInternalButtonList($page) {
        global $camyks;

        /* Check if link building is requiered */
        if ($this->blogItemCount <= $this->configItem->vars['list_count'])
            return;

        /* Build previous page button */
        if (($page+1)*$this->configItem->vars['list_count'] < $this->blogItemCount)
            $this->blogPrevPage = $camyks->get_siteLink($camyks->contentPage->id, $camyks->contentPage->name, '', array_merge($this->params, array('blogpage'=> $page+1)));
        else
            $this->blogPrevPage = '';

        /* Build next page button */
        if ($page > 0)
            $this->blogNextPage = $camyks->get_siteLink($camyks->contentPage->id, $camyks->contentPage->name, '', array_merge($this->params, array('blogpage'=> $page-1)));
        else
            $this->blogNextPage = '';

        /* Build buttons list */
        $this->buttons = array(
            array(
                'title' => $this->get_translation('site_previouspage'),
                'link'  => $this->blogPrevPage
            ),
            array(
                'title' => $this->get_translation('site_currentpage', array($page+1)),
                'link' => '',
            ),
            array(
                'title' => $this->get_translation('site_nextpage'),
                'link' => $this->blogNextPage,
            ),
        );
    }

    /**
     * Return generic status list
     * @return array
     */
    protected function get_genericStatusList() {
        return array(
            0 => $this->get_translation('status_disabled'),
            1 => $this->get_translation('status_enabled'),
        );
    }

    /**
     * Return GPC source list
     * @return array
     */
    protected function get_gpcSourceList() {
        global $camyks;
        return array(
            0 => $camyks->get_translation('theme'),
            1 => $this->get_translation('gpc_name'),
        );
    }
}
?>
