<?php
/**
 * @brief Content_GenericSiteMap module.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jul 2008
 * @date Modification: Jul 2021
 * @copyright 2008 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_GenericSiteMap class.
 */
final class Content_GenericSiteMap extends Module {
    /**
     * var Object $smItem
     * @brief Content object.
     */
    protected $smItem;

    /* site variables */
    var $sitemap;
    var $pagecount;
    var $pagelimit;

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('Content_GenericSiteMap', $path_type);

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
        $this->load_library('Content_GenericSiteMapItem');

        /* Initialise plugin libraries */
        $this->smItem = new Content_GenericSiteMapItem(0, $this);
    }

    /* Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return $this->smItem->install() and parent::install();
    }

    /**
     * Uninstall module.
     * @return boolean success
     */
    public function uninstall() {
        return $this->smItem->uninstall() and parent::uninstall();
    }

    /**
     * Check module installation.
     * @return boolean result
     */
    public function is_installed() {
        return $this->smItem->is_installed();
    }

    /**
     * Return available content id/name as list.
     * @return array
     */
    public function get_contentList() {
        return $this->smItem->get_nameList();
    }

    /**
     * Initialise module object in admin mode.
     * @return void
     */
    public function init_admin() {
        /* Generic pre-initialisation */
        parent::preInit_admin();

        /* Check right for this page */
        if ($this->check_right($this->page_id) === false)
            return $this->init_admin_pageAccessDenied();

        /* Load content item id */
        $this->smItem->id = isset($_REQUEST['id']) ? (int)$_REQUEST['id'] : 0;

        /* Load action to execute */
        $this->mode = isset($_REQUEST['mode']) ? $_REQUEST['mode'] : '';

        /* Execute action */
        switch ($this->mode) {
            case 'save' :
                /* mode == save */
                $this->init_admin_save();
                break;
            case 'modify':
            default:
                /* mode == modify */
                $this->init_admin_modify();
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
        /* Load content item */
        $this->smItem->id = $content;
        $this->smItem->get();
        $this->smItem->get_fromItems();

        /* Update layout */
        $this->set_selectedLayout('site_'.$this->smItem->vars['layout'].'.html.inc');

        /* Build site map */
        $this->init_site_buildMap();
    }

    /* specific admin mode methods */

    /**
     * Initialise module object in admin/modify mode.
     * @return void
     */
    private function init_admin_modify() {
        global $camyks;

        /* Build layout list */
        $this->layouts = array(
            'text' => $this->get_translation('layout_text'),
            'textbox1' => $this->get_translation('layout_textbox', 1),
            'textbox2' => $this->get_translation('layout_textbox', 2),
        );

        /* Load content object */
        $this->smItem->get();
        $this->smItem->get_fromItems();

        /* Build form */
        $this->form = new HTMLForm('genericsitemap_form', $this->get_adminlink(array('mode'=>'save')), 'POST');
        $this->form->add_hidden('page_id', $this->page_id);
        $this->form->add_hidden('module_index', $this->module_index);
        $this->form->add_hidden('id', $this->smItem->id);

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
     * Initialise module object in admin/modify mode.
     * @return void
     */
    private function init_admin_save() {
        global $camyks;

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Save item */
        $this->smItem->get_fromHeader();
        if ($this->smItem->save()) {
            /* Update page information with object id for new content */
            if ($this->smItem->id == 0 and $this->page_id > 0)
                $this->add_moduleContentToPage($this->page_id, $this->module_index, $this->smItem->id);

            $this->text = $camyks->get_translation('savedone');
        } else {
            $this->text = $camyks->get_translation('savefailed');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('mode'=>'modify', 'id'=>$this->smItem->id, 'page_id'=>$this->page_id, 'module_index'=>$this->module_index)));
    }

    /* Specific site methods */

    /**
     * Build site map.
     * @param void
     * @return void
     */
    private function init_site_buildMap() {
        global $camyks;

        /* Check admin page manager */
        if (!isset($camyks->modules['Admin_ContentPage'])) {
            $camyks->throwFatalError(array(
                'title'         => $this->get_translation('site_fatalerror_title'),
                'error_link'    => 'http://www.camyks.net',
                'error_title'   => 'Check CaMykS website for more informations.',
            ));
        }

        /* Load pages */
        $this->pages = $camyks->modules['Admin_ContentPage']->get_sitePages();

        /* Build map */
        $this->pagecount = 0;
        $this->col_width = floor(100/max(1,$this->smItem->vars['columns']));
        $this->pagelimit = ceil(count($this->pages)/(2*max(1,$this->smItem->vars['columns'])));

        $this->sitemap = '<div><div style="float:left;width:'.$this->col_width.'%;">';
        $this->build_ageChildrenMap($this->pages[0]->children, 0);
        $this->sitemap .= '</div><div style="height:2px; font-size:1px; clear:both;">&nbsp;</div></div>';
    }

    /**
     * Recursive page children build.
     * @param array $children
     * @param integer $level
     * @return void
     */
    private function build_pageChildrenMap($children, $level) {
        foreach($children as $p) {
            $page = $this->pages[$p];

            /* Load page infos */
            if ($page->active == 1 or $level > 1) {
                $title = $page->get_get_shortTitleDisplay('html');
                $url = $page->get_siteLink();
            } else if ($page->shorttitle != '' or $page->title != '') {
                $title = $page->shorttitle!=''?$page->shorttitle:$page->title;
                $url = false;
            } else {
                $title = false;
            }

            /* Check new column */
            if ($this->pagecount == $this->pagelimit) {
                $this->sitemap .= '</div><div style="float:left;width:'.$this->col_width.'%;">';
                $this->pagecount = 0;
            }

            /* build page map item */
            if ($title !== false) {
                $margin = $level>0 ? ($level*10).'px' : '0';
                $this->sitemap .= '<div class="eContent1" style="margin:1px 0 1px '.$margin.'">';
                if ($url !== false)
                    $this->sitemap .= '<a class="eLink1" href="'.$url.'">'.$title.'</a>';
                else
                    $this->sitemap .= $title;
                $this->sitemap .= '</div>'."\n";
                $this->pagecount++;
            }

            /* display children */
            if (count($page->children) > 0)
                $this->buildPageChildrenMap($page->children,$level+1);
        }
    }
}
?>
