<?php
/**
 * @brief Admin_GenericBlogsManager Module
 * <br /> Manages articles with comments and tags.
 * @details Plugin, Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Apr 2008
 * @date Modification: Nov 2020
 * @copyright 2008 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GenericBlogsManager class.
 */
final class Admin_GenericBlogsManager extends Module {
    /**
     * var Object $itemsByPage
     * @brief Define how many items are displayed by page.
     */
    public $itemsByPage = 15;

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('Admin_GenericBlogsManager', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'Generic';

        /* Override Module variables */
        $this->type = 'admin';
        $this->admin_type = 'content';

        /* Define plugin author */
        $this->authors_name = 'CaMykS Team';
        $this->authors_mail = 'camyks.contact@gmail.com';
        $this->authors_group = 'camyks.net';

        /* Load libraries */
        $this->load_library('Admin_GenericBlogsManagerConfig');
        $this->load_library('Admin_GenericBlogNewsItem');
        $this->load_library('Admin_GenericBlogLinkItem');
        $this->load_library('Admin_GenericBlogTagItem');
        $this->load_library('Admin_GenericBlogCommentItem');

        /* initialise library objects */
        $this->config = new Admin_GenericBlogsManagerConfig('blogconfig', $this);
        $this->linkItem = new Admin_GenericBlogLinkItem(0, $this);
        $this->tagItem = new Admin_GenericBlogTagItem(0, $this);
        $this->commentItem = new Admin_GenericBlogCommentItem(0, $this);
        $this->newsItem = new Admin_GenericBlogNewsItem(0, $this);
    }

    /* Override Module methods */

    /**
     * Install module object.
     * @return boolean success
     */
    public function install() {
        return $this->config->install() and $this->newsItem->install()
            and $this->linkItem->install() and $this->tagItem->install()
            and $this->commentItem->install() and parent::install();
    }

    /**
     * Check installation.
     * @return boolean result
     */
    public function is_installed() {
        return $this->commentItem->is_installed();
    }

    /**
     * Update description in control panel.
     * @return void
     */
    public function get_adminControlPanelAction() {
        global $camyks;

        $n = null;
        if ($this->check_right(7)===true)
            $n = $this->commentItem->get_objectCount('status=0');
        else if ($this->check_right(6)===true)
            $n = $this->commentItem->count_userNewsUnreadComments();

        if ($n == 1)
            $camyks->trads['mod_admin_genericblogsmanager_desc'] = $this->get_translation('desc1');
        else if ($n > 1)
            $camyks->trads['mod_admin_genericblogsmanager_desc'] = $this->get_translation('descx', $n);
    }

    /**
     * Initialise module object in admin mode
     * @return void
     */
    public function init_admin() {
        /* Check user permissions */
        if ($this->check_right(0) === false)
            return $this->init_admin_accessDenied();

        /* Load configuration */
        $this->config->get();

        /* Load action to execute */
        $this->mode = isset($_REQUEST['mode']) ? $_REQUEST['mode'] : 'main';

        /* Execute action */
        switch ($this->mode) {
            case 'editlink':
                /* mode == editlink */
                $this->init_admin_editLink();
                break;
            case 'savelink':
                /* mode == savelink */
                $this->init_admin_saveLink();
                break;
            case 'deletelink':
                /* mode == deletelink */
                $this->init_admin_deleteLink();
                break;
            case 'savetag':
                /* mode == savetag */
                $this->init_admin_saveTag();
                break;
            case 'deletetag':
                /* mode == deletetag */
                $this->init_admin_deleteTag();
                break;
            case 'saveconfig':
                /* mode == saveconfig */
                $this->init_admin_saveConfig();
                break;
            case 'editnews':
                /* mode == editnews */
                $this->init_admin_editNews();
                break;
            case 'savenews':
                /* mode == savenews */
                $this->init_admin_saveNews();
                break;
            case 'deletenews':
                /* mode == deletenews */
                $this->init_admin_deleteNews();
                break;
            case 'viewcomments':
                /* mode == viewcomments */
                $this->init_admin_viewComments();
                break;
            case 'editcomment':
                /* mode == editcomment */
                $this->init_admin_editComment();
                break;
            case 'savecomment':
                /* mode == savecomment */
                $this->init_admin_saveComment();
                break;
            case 'deletecomment':
                /* mode == deletecomment */
                $this->init_admin_deleteComment();
                break;
            case 'updatecommentstatus':
                /* mode == updatecommentstatus */
                $this->init_admin_updateCommentStatus();
                break;
            case 'main':
            default:
                /* mode == main */
                $this->init_admin_main();
                break;
        }
        parent::init_admin();
    }

    /**
     * Define module permissions.
     * @return void
     */
    public function get_rights() {
        global $camyks;
        $this->rights[0] = array(
            'name'      => 'read',
            'title'     => $camyks->get_translation('read'),
            'default'   => true,
        );
        $this->rights[1] = array(
            'name'      =>'config',
            'title'     => $this->get_translation('right_config'),
            'default'   => false,
        );
        $this->rights[2] = array(
            'name'      => 'news_limited',
            'title'     => $this->get_translation('right_news_limited'),
            'default'   => true,
        );
        $this->rights[3] = array(
            'name'      =>'news_global',
            'title'     => $this->get_translation('right_news_global'),
            'default'   => false,
        );
        $this->rights[4] = array(
            'name'      => 'link_limited',
            'title'     => $this->get_translation('right_link_limited'),
            'default'   => true,
        );
        $this->rights[5] = array(
            'name'      =>  'link_global',
            'title'     => $this->get_translation('right_link_global'),
            'default'   => false,
        );
        $this->rights[6] = array(
            'name'      => 'comment_limited',
            'title'     => $this->get_translation('right_comment_limited'),
            'default'   => true,
        );
        $this->rights[7] = array(
            'name'      => 'comment_global',
            'title'     => $this->get_translation('right_comment_global'),
            'default'   => false,
        );
        $this->rights[8] = array(
            'name'      => 'tag_limited',
            'title'     => $this->get_translation('right_tag_limited'),
            'default'   => false,
        );
        $this->rights[9] = array(
            'name'      => 'tag_global',
            'title'     => $this->get_translation('right_tag_global'),
            'default'   => false,
        );
    }

    /* Specific module mode methods */

    /**
     * Initialise module object in admin/main mode
     * @return void
     */
    private function init_admin_main() {
        global $camyks;

        /* Check itemsByPage value */
        if (($c = $camyks->get_confValue('admin_itemsbypage')) !== false)
            $this->itemsByPage = $c;

        /* Add module scripts */
        $this->add_JSFile('genericblogsmanager.js');

        /* Load tab engine */
        $this->tabObject = 'gbm_tabObject';
        $this->add_JSEngineFile('object/ctab.js');
        $this->add_JSScript($this->tabObject.' = new CTab();');
        $this->add_JSScript($this->tabObject.'.init("news", "'.$this->theme->parts['boxTabCSSStandart'].'","'.$this->theme->parts['boxTabCSSSelected'].'","'.$this->theme->parts['boxTabCSSRollover'].'");');
        if (isset($_REQUEST['openTab']))
            $this->add_JSLoadScript($this->tabObject.'.mouseclick(\''.$_REQUEST['openTab'].'\');');
        $this->tabs = array();

        /* Add configuration tab */
        if ($this->check_right(1) === true) {
            $this->tabs[] = array(
                'name'  => 'configuration',
                'title' => $this->get_translation('tabconfig'),
            );
            $this->editorMode = (isset($camyks->inputs['TinyMCEv3']) or isset($camyks->inputs['TinyMCE']));
        }

        /* Add news tab */
        $this->tabs[] = array(
            'name'  => 'news',
            'title' => $this->get_translation('tabnews'),
        );

        /* Links management */
        if ($this->check_right(4) === true or $this->check_right(5) === true) {
            /* Load links */
            if ($this->check_right(5) === true) {
                $this->links = $this->linkItem->get_objectList(false);
                $this->adminLinkCount = 0;
                foreach ($this->links as $l)
                    if ($l->vars['author'] == $camyks->adminUser->login)
                        $this->adminLinkCount ++;
            } else {
                $this->links = $this->linkItem->get_objectList(false, 'author="'.$camyks->adminUser->login.'"');
                $this->adminLinkCount = count($this->links);
            }

            /* Add links tab */
            $this->tabs[] = array(
                'name'  => 'links',
                'title' => $this->get_translation('tablinks'),
            );

            /* Links links */
            $this->editLinkLink = $camyks->get_adminLink($this->name, array('mode'=>'editlink', 'link_id'=>''));

            /* Delete link javascript */
            $this->add_JSScript('var deleteLinkMessage="'.utf8_encode(html_entity_decode($this->get_translation('links_deletemessage'))).'";');
            $this->add_JSScript('var deleteLinkLink="'.$camyks->get_adminJSLink($this->name, array('mode'=>'deletelink', 'link_id'=>'')).'";');
        }

        /* Add tags tab */
        if ($this->check_right(8) === true or $this->check_right(9) === true) {
            $this->tabs[] = array(
                'name'  => 'tags',
                'title' => $this->get_translation('tabtags'),
            );
            $this->tagList = $this->tagItem->get_countTagList($this->check_right(9));

            /* Build tag editor form */
            $this->tagEditor = new HTMLForm('tagEditor_form', $this->get_adminLink(array('mode'=>'savetag')));
            $this->tagEditor->add_hidden('tag', '');

            /* Delete tag link */
            $this->add_JSScript('var deleteTagMessage="'.utf8_encode(html_entity_decode($this->get_translation('tags_deletemessage'))).'";');
            $this->add_JSScript('var deleteTagLink="'.$camyks->get_adminJSLink($this->name, array('mode'=>'deletetag', 'tag'=>'')).'";');

            /* Edit tag scripts */
            $this->add_JSEngineFile('tool/html.js');
            $this->add_JSScript('var genericblogsmanager_tagEditorForm="'.$this->tagEditor->name.'";');
        }

        /* News management */
        $this->newsListForm = new HTMLForm('newslistform', $this->get_adminlink(), 'POST');

        /* Build search query */
        $search = array();

        /* Get page selection value */
        if (isset($_REQUEST['newsListPage'])) {
            $this->newsListPage = (int)$_REQUEST['newsListPage']-1;
            $camyks->set_sessionValue('newsListPage', $this->newsListPage);
        } else
            $this->newsListPage = $camyks->get_sessionValue('newsListPage', 0);

        /* Get unread selection value */
        $this->newsListUnread = isset($_REQUEST['newsListUnread']) ? $_REQUEST['newsListUnread'] : $camyks->get_sessionValue('newsListUnread', 0);
        $camyks->set_sessionValue('newsListUnread', $this->newsListUnread);

        $this->unreadCommentIds = $this->commentItem->get_newsWithUnreadComments();
        if ($this->newsListUnread == 1 and count($this->unreadCommentIds) > 0)
        $search[] = 'id IN('.implode(',', $this->unreadCommentIds).')';

        if ($this->check_right(3) === false)
            $search[] = 'author="'.$camyks->adminUser->login.'"';

        $search = implode(' and ', $search);

        /* Load news list */
        $this->newsCount = $this->newsItem->get_objectCount($search);
        $this->newsPages = ceil($this->newsCount/$this->itemsByPage);
        $this->newsListPage = min(max(0, $this->newsListPage), $this->newsPages-1);
        $this->newsList = $this->newsItem->get_objectList(false, $search, $this->newsListPage*$this->itemsByPage, $this->itemsByPage, 'ndate', 'desc');

        /* Load comment count values */
        $comCount = $this->commentItem->count_newsCommentsByStatus(array_keys($this->newsList));
        foreach($comCount as $newsid=>$coms) {
            $this->newsList[$newsid]->vars['coms'] = $coms;
        }

        /* News links */
        $this->editNewsLink = $camyks->get_adminLink($this->name, array('mode'=>'editnews', 'news_id'=>''));
        $this->viewCommentsLink = $camyks->get_adminLink($this->name, array('mode'=>'viewcomments', 'news_id'=>''));

        /* Delete news javascript */
        $this->add_JSScript('var deleteNewsMessage="'.utf8_encode(html_entity_decode($this->get_translation('news_deletemessage'))).'";');
        $this->add_JSScript('var deleteNewsLink="'.$camyks->get_adminJSLink($this->name, array('mode'=>'deletenews', 'news_id'=>'')).'";');

        /* Build buttons */
        $this->buttons = array(
            array(
                'link'  => $camyks->get_adminLink(),
                'title' => $camyks->get_translation('back'),
            )
        );

        /* Add configuration form */
        if ($this->check_right(1) === true) {
            $this->configForm = new HTMLForm('configForm', $this->get_adminLink(array('mode'=>'saveconfig')), 'POST');
        }
    }

    /**
     * Initialise module object in admin/saveconfig mode.
     * @return void
     */
    private function init_admin_saveConfig() {
        global $camyks;

        /* Check edit configuration permission */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        $this->config->get_fromHeader();
        if ($this->config->save()) {
            $this->text = $this->get_translation('message_saveconfig_done');
        } else {
            $this->text = $this->get_translation('message_saveconfig_failed');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('openTab'=>'configuration')));
    }

    /**
     * Initialise module object in admin/editlink mode
     * @return void
     */
    private function init_admin_editLink() {
        global $camyks;

        /* Load link */
        $this->linkItem->id = isset($_REQUEST['link_id']) ? (int)$_REQUEST['link_id'] : 0;
        $this->linkItem->get();
        $this->linkItem->get_fromItems();

        /* Check right */
        if ($this->check_right(5)===false and ($this->check_right(4) === false or $this->linkItem->vars['author'] != $camyks->adminUser->login)) {
            return $this->init_admin_actionNotAllowed();
        }

        /* Build form */
        $this->form = new HTMLForm('editlink_form', $this->get_adminLink(array('mode'=>'savelink')), 'POST');
        $this->form->add_hidden('link_id', $this->linkItem->id);

        /* Build buttons */
        $this->buttons = array(
            array(
                'link'  => $camyks->get_adminLink($this->name, array('openTab'=>'links')),
                'title' => $camyks->get_translation('back'),
            ),
            array(
                'link'=>$this->form->get_HTMLSubmitLink(),
                'title'=>$camyks->get_translation('valid'),
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('admin_editlink.html.inc');
    }

    /**
     * Initialise module object in admin/saveLink mode
     * @return void
     */
    private function init_admin_saveLink() {
        global $camyks;

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Get link id */
        $linkItemID = isset($_REQUEST['link_id']) ? (int)$_REQUEST['link_id'] : 0;

        /* Load link */
        $linkItem = $this->linkItem->get_newObject($linkItemID);
        $linkItem->get();
        $linkItem->get_fromItems();

        /* Check right */
        if ($this->check_right(5) === false and ($this->check_right(4) === false or $linkItem->vars['author'] != $camyks->adminUser->login)) {
            return $this->init_admin_actionNotAllowed();
        }

        /* Get link data */
        $this->savingAllowed = true;
        $this->linkItem->id = $linkItemID;
        $this->linkItem->get_fromHeader();
        if ($linkItemID == 0) {
            $this->linkItem->_libItems['author']->value = $camyks->adminUser->login;
            $this->linkItem->_libItems['ndate']->value = time();

            /* Check link count */
            if ($this->linkItem->get_objectCount('author="'.$camyks->adminUser->login.'"') >= $this->config->vars['links_maxcount'])
                $this->savingAllowed = false;
        } else {
            $this->linkItem->_libItems['author']->value = $linkItem->vars['author'];
            $this->linkItem->_libItems['ndate']->value = $linkItem->vars['ndate'];
        }

        if ($this->savingAllowed === false) {
            $this->text = $this->get_translation('links_maxlinkcountreached');
            $this->text .= ' '.$this->get_translation('message_savelink_notdone');
        } else if ($this->linkItem->save()) {
            $this->text = $this->get_translation('message_savelink_done');
        } else {
            $this->text = $this->get_translation('message_savelink_failed');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('openTab'=>'links')));
    }

    /**
     * Initialise module object in admin/deletelink mode
     * @return void
     */
    private function init_admin_deleteLink() {
        global $camyks;

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Load link */
        $this->linkItem->id = isset($_REQUEST['link_id']) ? (int)$_REQUEST['link_id']:0;
        $this->linkItem->get();
        $this->linkItem->get_fromItems();

        /* Check right */
        if ($this->check_right(5) === false and ($this->check_right(4) === false or $this->linkItem->vars['author'] != $camyks->adminUser->login)) {
            return $this->init_admin_actionNotAllowed();
        }

        if ($this->linkItem->delete()) {
            $this->text = $this->get_translation('message_deletelink_done');
        } else {
            $this->text = $this->get_translation('message_deletelink_failed');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('openTab'=>'links')));
    }

    /**
     * Initialise module object in admin/savetag mode
     * @return void
     */
    private function init_admin_saveTag() {
        global $camyks;

        /* Check permission */
        if ($this->check_right(8) === false and $this->check_right(9) === false) {
            return $this->init_admin_actionNotAllowed();
        }

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Check if tag is defined */
        if (!isset($_REQUEST['tag']) or !isset($_REQUEST['tagvalue'])) {
            return $this->init_admin_main();
        }
        /* Update tag */
        if ($this->tagItem->update_tagTitle($_REQUEST['tag'], $_REQUEST['tagvalue'], $this->check_right(9))) {
            $this->text = $this->get_translation('message_savetag_done');
        } else {
            $this->text = $this->get_translation('message_savetag_failed');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('openTab'=>'tags')));
    }

    /**
     * Initialise module object in admin/deletetag mode
     * @return void
     */
    private function init_admin_deleteTag() {
        global $camyks;

        /* Check permision */
        if ($this->check_right(8) === false and $this->check_right(9) === false) {
            return $this->init_admin_actionNotAllowed();
        }

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Check if tag is defined */
        if (!isset($_REQUEST['tag'])) {
            return $this->init_admin_main();
        }
        /* Delete tag */
        if ($this->tagItem->delete_tagTitle($_REQUEST['tag'], $this->check_right(9))) {
            $this->text = $this->get_translation('message_deletetag_done');
        } else {
            $this->text = $this->get_translation('message_deletetag_failed');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('openTab'=>'tags')));
    }

    /**
     * Initialise module object in admin/editnews mode
     * @return void
     */
    private function init_admin_editNews() {
        global $camyks;

        /* Check dependencies */
        if ($this->config->vars['news_editormode'] > 0 and !isset($camyks->inputs['TinyMCEv3']) and !isset($camyks->inputs['TinyMCE']))
            return $this->init_admin_missingPlugin('Input', 'TinyMCEv3');

        /* Load news */
        $this->newsItem->id = isset($_REQUEST['news_id']) ? (int)$_REQUEST['news_id'] : 0;
        $this->newsItem->get();
        $this->newsItem->get_fromItems();

        /* Check right */
        if ($this->check_right(3) === false and ($this->check_right(2) === false or $this->newsItem->vars['author'] != $camyks->adminUser->login)) {
            return $this->init_admin_actionNotAllowed();
        }

        /* Get news item tag list */
        $this->newsItem->get_tagList();

        /* Get full tag list */
        $this->tagList = $this->tagItem->get_titleList();

        /* Get tab engine */
        $this->tabObject = 'gbm_tabObject';
        $this->add_JSEngineFile('object/ctab.js');
        $this->add_JSScript($this->tabObject.' = new CTab();');
        $this->add_JSScript($this->tabObject.'.init("properties", "'.$this->theme->parts['boxTabCSSStandart'].'","'.$this->theme->parts['boxTabCSSSelected'].'","'.$this->theme->parts['boxTabCSSRollover'].'");');
        $this->tabs = array(
            array(
                'name'  => 'properties',
                'title' => $this->get_translation('tabproperties'),
            ),
            array(
                'name'  => 'content',
                'title' => $this->get_translation('tabcontent'),
            ),
        );

        /* Build form */
        $this->form = new HTMLForm('editnews_form', $camyks->get_adminLink(array('mode'=>'savenews')), 'POST');
        $this->form->add_hidden('news_id', $this->newsItem->id);
        $this->form->add_hidden('tagCounter', count($this->newsItem->tagList));

        /* Get tag engine */
        $this->add_JSEngineFile('tool/html.js');
        $this->add_JSFile('genericblogsnewseditor.js');
        $this->add_JSScript('genericblogsmanager_form="'.$this->form->name.'";');
        $this->add_JSScript('genericblogsmanager_minusImg="'.$this->theme->get_pictURL('minus', 12, 'std').'";');
        $this->add_JSLoadScript('genericblogsmanager_initialiseTagEngine();');


        /* Get content editor */
        if ($this->config->vars['news_editormode'] > 0) {
            $this->load_tinyMCEInput();
        }

        /* Build buttons */
        $this->buttons = array(
            array(
                'link'  => $this->get_adminLink(array('openTab'=>'news')),
                'title' => $camyks->get_translation('back'),
            ),
            array(
                'link'  => $this->form->get_HTMLSubmitLink(),
                'title' => $camyks->get_translation('valid'),
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('admin_editnews.html.inc');
    }

    /**
     * Initialise module object in admin/saveNews mode
     * @return void
     */
    private function init_admin_saveNews() {
        global $camyks;

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Check news id */
        if (!isset($_REQUEST['news_id']))
            $this->init_admin_main();
        $newsItemID = (int)$_REQUEST['news_id'];

        /* Load news */
        $newsItem = new Admin_GenericBlogNewsItem($newsItemID, $this);
        $newsItem->get();
        $newsItem->get_fromItems();

        /* Check right */
        if ($this->check_right(3) === false and ($this->check_right(2) === false or $newsItem->vars['author'] != $camyks->adminUser->login)) {
            return $this->init_admin_actionNotAllowed();
        }

        /* Get news data */
        $this->newsItem->id = $newsItemID;
        $this->newsItem->get_fromHeader();
        if ($newsItemID == 0 or $newsItem->vars['author'] == '') {
            $this->newsItem->_libItems['author']->value = $camyks->adminUser->login;
        } else {
            $this->newsItem->_libItems['author']->value = $newsItem->vars['author'];
        }

        /* save news data */
        if ($this->newsItem->save()) {
            $this->text = $this->get_translation('message_savenews_done');
        } else {
            $this->text = $this->get_translation('message_savenews_failed');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('openTab'=>'news')));
    }

    /**
     * Initialise module object in admin/deletenews mode
     * @return void
     */
    private function init_admin_deleteNews() {
        global $camyks;

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Load news */
        $this->newsItem->id = isset($_REQUEST['news_id']) ? (int)$_REQUEST['news_id'] : 0;
        $this->newsItem->get();
        $this->newsItem->get_fromItems();

        /* Check right */
        if ($this->check_right(3) === false and ($this->check_right(2) === false or $this->newsItem->vars['author'] != $camyks->adminUser->login)) {
            return $this->init_admin_actionNotAllowed();
        }

        if ($this->commentItem->delete_newsComments($this->newsItem->id) and $this->tagItem->delete_newsTags($this->newsItem->id) and $this->newsItem->delete()) {
            $this->text = $this->get_translation('message_deletenews_done');
        } else {
            $this->text = $this->get_translation('message_deletenews_failed');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('openTab'=>'news')));
    }

    /**
     * Initialise module object in admin/viewcomments mode
     * @return void
     */
    private function init_admin_viewComments() {
        global $camyks;

        /* Check news id */
        if (!isset($_REQUEST['news_id']))
            return $this->init_admin_main();

        /* Load news item */
        $this->newsItem->id = (int)$_REQUEST['news_id'];
        $this->newsItem->get();
        $this->newsItem->get_fromItems();

        /* Check right */
        if ($this->check_right(7) === false and ($this->check_right(6) === false or $this->newsItem->vars['author'] != $camyks->adminUser->login)) {
            return $this->init_admin_actionNotAllowed();
        }

        /* Load news comments */
        $this->newsItem->vars['coms'] = $this->commentItem->get_objectList(false, 'newsid='.$this->newsItem->id);

        /* Constant vars */
        $this->commentStatusList = $this->commentItem->get_statusList();

        /* Builds links */
        $this->editCommentLink = $this->get_adminLink(array('mode'=>'editcomment', 'comment_id'=>''));

        /* Update comment status scripts */
        $this->add_JSScript('var updateCommentStatusLink="'.$this->get_adminJSLink(array('mode'=>'updatecommentstatus', 'comment_id'=>'')).'";');

        /* Delete comment javascripts */
        $this->add_JSScript('var deleteCommentMessage="'.utf8_encode(html_entity_decode($this->get_translation('comment_deletemessage'))).'";');
        $this->add_JSScript('var deleteCommentLink="'.$this->get_adminJSLink(array('mode'=>'deletecomment','comment_id'=>'')).'";');

        /* Add javascript file */
        $this->add_JSFile('genericblogsviewcomments.js');

        /* Add layout buttons */
        $this->buttons = array(
            array(
                'link'  => $this->get_adminLink(),
                'title' => $camyks->get_translation('back'),
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('admin_viewcomments.html.inc');
    }

    /**
     * Initialise module object in admin/editcomment mode
     * @return void
     */
    private function init_admin_editComment() {
        global $camyks;

        /* Get header comment id value */
        if (!isset($_REQUEST['comment_id']))
            return $this->init_admin_main();

        /* Load comment item */
        $this->commentItem->id = (int)$_REQUEST['comment_id'];
        $this->commentItem->get();
        $this->commentItem->get_fromItems();

        /* Load news */
        $this->newsItem->id = $this->commentItem->vars['newsid'];
        $this->newsItem->get();
        $this->newsItem->get_fromItems();

        /* Check right */
        if ($this->check_right(7) === false and ($this->check_right(6) === false or $this->newsItem->vars['author']!=$camyks->adminUser->login)) {
            return $this->init_admin_actionNotAllowed();
        }

        /* Get form */
        $this->form = new HTMLForm('editcomment', $this->get_adminLink(array('mode'=>'savecomment')), 'POST');
        $this->form->add_hidden('comment_id', $this->commentItem->id);

        /* Get buttons */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'  => $this->get_adminLink(array('mode'=>'viewcomments', 'news_id'=>$this->newsItem->id)),
            ),
            array(
                'title' => $camyks->get_translation('valid'),
                'link'  => $this->form->get_HTMLSubmitLink(),
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('admin_editcomment.html.inc');
    }

    /**
     * Initalise module object in admin/savecomment mode
     * @return void
     */
    private function init_admin_saveComment() {
        global $camyks;

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Get header comment id value */
        if (!isset($_REQUEST['comment_id']))
            return $this->init_admin_main();

        /* Load comment item */
        $commentItem = new Admin_GenericBlogCommentItem((int)$_REQUEST['comment_id'], $this);
        $commentItem->get();
        $commentItem->get_fromItems();

        /* Load news */
        $this->newsItem->id = $commentItem->vars['newsid'];
        $this->newsItem->get();
        $this->newsItem->get_fromItems();

        /* Check right */
        if ($this->check_right(7) === false and ($this->check_right(6) === false or $this->newsItem->vars['author'] != $camyks->adminUser->login)) {
            return $this->init_admin_actionNotAllowed();
        }

        /* Get comment data */
        $this->commentItem->id = $commentItem->id;
        $this->commentItem->get_fromHeader();
        $this->commentItem->_libItems['email']->value = $commentItem->vars['email'];
        $this->commentItem->_libItems['newsid']->value = $commentItem->vars['newsid'];
        $this->commentItem->_libItems['ndate']->value = $commentItem->vars['ndate'];
        $this->commentItem->_libItems['ipaddress']->value = $commentItem->vars['ipaddress'];

        /* save comment */
        if ($this->commentItem->save()) {
            $this->text = $this->get_translation('message_savecomment_done');
        } else {
            $this->text = $this->get_translation('message_savecomment_failed');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('mode'=>'viewcomments', 'news_id'=>$this->newsItem->id)));
    }

    /**
     * Initalise module object in admin/deletecomment mode
     * @return void
     */
    private function init_admin_deleteComment() {
        global $camyks;

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Get header comment id value */
        if (!isset($_REQUEST['comment_id']))
            return $this->init_admin_main();

        /* Load comment item */
        $this->commentItem->id = (int)$_REQUEST['comment_id'];
        $this->commentItem->get();
        $this->commentItem->get_fromItems();

        /* Load news */
        $this->newsItem->id = $this->commentItem->vars['newsid'];
        $this->newsItem->get();
        $this->newsItem->get_fromItems();

        /* Check right */
        if ($this->check_right(7) === false and ($this->check_right(6) === false or $this->newsItem->vars['author'] != $camyks->adminUser->login)) {
            return $this->init_admin_actionNotAllowed();
        }

        /* Delete comment */
        if ($this->commentItem->delete()) {
            $this->text = $this->get_translation('message_deletecomment_done');
        } else {
            $this->text = $this->get_translation('message_deletecomment_failed');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('mode'=>'viewcomments', 'news_id'=>$this->newsItem->id)));
    }

    /**
     * Initalise module object in admin/updatecommentstatus mode
     * @return void
     */
    private function init_admin_updateCommentStatus() {
        global $camyks;

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Get header comment id value */
        if (!isset($_REQUEST['comment_id']) or !isset($_REQUEST['status']))
            return $this->init_admin_main();

        /* Load comment item */
        $this->commentItem->id = (int)$_REQUEST['comment_id'];
        $this->commentItem->get();
        $this->commentItem->get_fromItems();

        /* Load news */
        $this->newsItem->id = $this->commentItem->vars['newsid'];
        $this->newsItem->get();
        $this->newsItem->get_fromItems();

        /* Check right */
        if ($this->check_right(7) === false and ($this->check_right(6) === false or $this->newsItem->vars['author'] != $camyks->adminUser->login)) {
            return $this->init_admin_actionNotAllowed();
        }

        /* Update status value */
        $this->commentItem->_libItems['status']->value = (int)$_REQUEST['status'];

        /* Update comment */
        if ($this->commentItem->save()) {
            $this->text = $this->get_translation('message_updatecomment_done');
        } else {
            $this->text = $this->get_translation('message_updatecomment_failed');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('mode'=>'viewcomments', 'news_id'=>$this->newsItem->id)));
    }

    /* Specific tool methods */

    /**
     * Load tinyMCE input.
     * @return void
     */
    private function load_tinyMCEInput() {
        global $camyks;
        /* Get input */
        if (isset($camyks->inputs['TinyMCEv3'])) {
            $this->webEditor = &$camyks->inputs['TinyMCEv3'];
            $config_url = 'js/tinymcev3_mode';
        } else {
            $this->webEditor = &$camyks->inputs['TinyMCE'];
            $config_url = 'js/tinymce_mode';
        }

        /* Update editor config */
        $this->webEditor->set_configInfos('file', $this->get_fileURL($config_url.$this->config->vars['news_editormode'].'.js'));
        $this->webEditor->load_themeCSSFile();

        /* Load document folder case of mode */
        if ($this->config->vars['news_documentmode'] == 0) {
            $this->webEditor->load_fileManager();
        } else if ($this->config->vars['news_documentmode'] == 1) {
            $this->webEditor->load_fileManager($this->plugin_var_path.'/resource', $this->plugin_var_url.'/resource', $this->title);
        } else if ($this->config->vars['news_documentmode'] == 2) {
            $this->webEditor->load_fileManager($this->plugin_var_path.'/resource/'.$camyks->adminUser->login, $this->plugin_var_url.'/resource/'.$camyks->adminUser->login, $this->title);
        }
        $this->webEditor->load_pageChooser();
        $this->webEditor->set_contentInfos('text', $this->newsItem->vars['content']);
        $this->webEditor->set_textareaInfos('content', '100%', '400px');
        $this->webEditor->initialise();
    }
}
?>
