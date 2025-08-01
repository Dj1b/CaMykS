<?php
/**
 * @brief Content_GenericGallery module.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Jul 2007
 * @date Modification: Jul 2025
 * @copyright 2007 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_GenericGallery class.
 */
final class Content_GenericGallery extends Module {
    /**
     * var Object $imageitem
     * @brief Image item.
     */
    protected $imageitem;

    /**
     * var array $imagelist
     * @brief Image list.
     */
    protected $imagelist;

    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('Content_GenericGallery', $path_type);

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
        $this->load_library('Content_GenericGalleryItem');
        $this->load_library('Content_GenericGalleryList');

        /* Initialise plugin libraries */
        $this->imageitem = new Content_GenericGalleryItem(0, $this);
        $this->imagelist = new Content_GenericGalleryList(0, $this);

        /* Initialise plugin variables */
        $this->maxfilesize = 512*1024; /* 512 Ko */
    }

    /* Mark: Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return $this->imageitem->install() and $this->imagelist->install() and parent::install();
    }

    /**
     * Uninstall module.
     * @return boolean success
     */
    public function uninstall() {
        return $this->imageitem->uninstall() and $this->imagelist->uninstall() and parent::uninstall();
    }

    /**
     * Check module installation.
     * @return boolean result
     */
    public function is_installed() {
        return $this->imagelist->is_installed();
    }

    /**
     * Build dependencies list.
     * @return boolean
     */
    public function set_dependencies() {
        $this->add_dependency('SmartGallery', 'Input', '1.0', true);
        return true;
    }

    /**
     * Return available content id/name as list.
     * @return array
     */
    public function get_contentList() {
        return $this->imagelist->get_nameList();
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

        /* Load image list id */
        $this->imageid = isset($_REQUEST['id']) ? (int)$_REQUEST['id'] : 0;
        $this->imagelist->id = $this->imageid;

        /* Load action execute */
        $this->mode = isset($_REQUEST['mode']) ? $_REQUEST['mode'] : '';

        /* Execute action */
        switch ($this->mode) {
            case 'save_item':
                $this->init_admin_save_item();
                break;
            case 'modify_item':
                $this->init_admin_modify_item();
                break;
            case 'delete_item':
                $this->init_admin_delete_item();
                break;
            case 'save_list' :
                $this->init_admin_save_list();
                break;
            case 'modify_list':
            default:
                $this->init_admin_modify_list();
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

        /* Check if input is available */
        if (!isset($camyks->inputs['SmartGallery']))
            return;

        /* Load imagelist */
        $this->imagelist->id = $content;
        $this->imagelist->get($camyks->current_language);
        $this->imagelist->get_fromItems();
        $this->imagelist->get_itemList($camyks->current_language);

        /* get input */
        $this->gallery = $camyks->inputs['SmartGallery'];
        $this->gallery->set_URLsValues($this->plugin_var_url.'/'.$this->imageitem->_libItems['image']->folder, $this->plugin_var_url.'/'.$this->imageitem->_libItems['thumb']->folder);

        $this->gallery->set_themeValues($this->imagelist->vars['theme']);

        $this->gallery->set_thumbValues($this->imagelist->vars['thumbWidth'], $this->imagelist->vars['thumbHeight'], $this->imagelist->vars['thumbCount']);

        $this->gallery->set_imageValues($this->imagelist->vars['imageWidth'], $this->imagelist->vars['imageHeight'], $this->imagelist->vars['imageTitle'], $this->imagelist->vars['imageDesc']);

        $this->gallery->set_slidingValues($this->imagelist->vars['slidingMethod'], $this->imagelist->vars['slidingAccel'], $this->imagelist->vars['slidingSpeed'], $this->imagelist->vars['slidingInterval']);

        foreach ($this->imagelist->items as $item) {
            if ($item->vars['image'] != '' and $item->vars['thumb'] != '') {
                $image = explode('/', $item->vars['image']);
                $image = $image[count($image)-1];
                $thumb = explode('/', $item->vars['thumb']);
                $thumb = $thumb[count($thumb)-1];

                $this->gallery->add_item($item->id, 'image', $thumb, $image, $item->vars['title'], $item->vars['description']);
            }
        }

        $this->gallery->initialise($this->imagelist->vars['name']);

        /* Update layout */
        $this->set_selectedLayout('site_'.$this->imagelist->vars['layout'].'.html.inc');

        /* Generic site initialisation */
        parent::init_site();
    }

    /* Mark: Admin initialise mode sub methods */

    /**
     * Initialise module object in admin/modify_list mode.
     * @return void
     */
    private function init_admin_modify_list() {
        global $camyks;

        /* Define layout list */
        $this->layouts = array(
            'nobox' => $this->get_translation('layout_nobox'),
            'box1'  => $this->get_translation('layout_box', 1),
            'box2'  => $this->get_translation('layout_box', 2),
        );

        if (!isset($camyks->inputs['SmartGallery']))
            return $this->init_admin_missingPlugin('Input', 'SmartGallery');

        /* Set theme list */
        $this->themes = $camyks->inputs['SmartGallery']->themes;

        /* Set sliding method list */
        $this->slidingMethods = $camyks->inputs['SmartGallery']->slidingMethods;

        /* Load help */
        $this->get_help();

        /* Load object */
        $this->imagelist->get(true);
        $this->imagelist->get_fromItems();
        $this->imagelist->get_itemList();

        /* Build form */
        $this->form = new HTMLForm('genericgallery_form', $this->get_adminlink(array('mode'=>'save_list')), 'POST');
        $this->form->add_hidden('page_id', $this->page_id);
        $this->form->add_hidden('module_index', $this->module_index);
        $this->form->add_hidden('id', $this->imagelist->id);

        /* Build interface buttons */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'  => $camyks->get_adminLink('Admin_ContentPage', array(
                    'mode'      => 'modify',
                    'page_id'   => $this->page_id,
                    'openTab'   => 'content'
                ))
            ),
            array(
                'title' => $camyks->get_translation('valid'),
                'link'  => $this->form->get_HTMLSubmitLink(),
            ),
        );

        /* Edit image link */
        $this->editlink = $this->get_adminLink(array(
            'id'            => $this->imagelist->id,
            'page_id'       => $this->page_id,
            'module_index'  => $this->module_index,
            'mode'          => 'modify_item',
            'itemid'        => '',
        ));

        /* Delete image link */
        $this->add_JSScript('var deleteImageMessage="'.string_text2HTML($this->get_translation('deleteitemconfirm')).'";');
        $this->add_JSScript('var deleteImageLink="'.$this->get_adminJSLink(array(
            'id'            => $this->imagelist->id,
            'page_id'       => $this->page_id,
            'module_index'  => $this->module_index,
            'mode'          => 'delete_item',
            'itemid'        => ''
        )).'";');
        $this->dellink = 'javascript:adminengine_confirmRedirect(deleteImageLink+%s,deleteImageMessage);';

        /* Build tabs */
        $this->tabs = array(
            array(
                'name'  => 'general',
                'title' => $this->get_translation('tabgeneral'),
            )
        );
        if ($this->imagelist->id > 0) {
            $this->tabs[] = array(
                'name'  => 'images',
                'title' => $this->get_translation('tabimages'),
            );
        }

        /* add help tab */
        if ($this->help != null) {
            $this->tabs[] = array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help'),
            );
        }

        /* Insert tabs javascript engine */
        $this->tabObject = 'gallery_tabObject';
        $this->add_JSEngineFile ('object/ctab.js');
        $this->add_JSScript($this->tabObject.' = new CTab();');
        $this->add_JSScript($this->tabObject.'.init("general", "'.$this->theme->parts['boxTabCSSStandart'].'","'.$this->theme->parts['boxTabCSSSelected'].'","'.$this->theme->parts['boxTabCSSRollover'].'");');
    }

    /**
     * Initialise module object in admin/save_list mode
     * @return void
     */
    private function init_admin_save_list() {
        global $camyks;

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Load image list */
        $this->imagelist->get_fromHeader();

        /* Save image list */
        if ($this->imagelist->save()) {
            if ($this->imageid == 0 and $this->page_id > 0)
                /* Update page information with object id for new content */
                $this->add_moduleContentToPage($this->page_id, $this->module_index, $this->imagelist->id);
            $this->text = $camyks->get_translation('savedone');
        } else {
            $this->text = $camyks->get_translation('savefailed');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('mode'=>'modify', 'id'=>$this->imagelist->id)));
    }

    /**
     * Initialise module object in admin/modify_item mode.
     * @return void
     */
    private function init_admin_modify_item() {
        global $camyks;

        /* Load help */
        $this->get_help();

        /* Load item object */
        $this->imageitem->id = isset($_REQUEST['itemid']) ? (int)$_REQUEST['itemid'] : 0;
        $this->imageitem->get(true);
        if ($this->imageitem->id == 0)
            $this->imageitem->_libItems['listid']->value = (int)$_REQUEST['id'];
        $this->imageitem->get_fromItems();

        /* Build tabs */
        $this->tabs = array(
            array(
                'name'  => 'general',
                'title' => $this->get_translation('tabgeneral'),
            ),
        );

        foreach ($camyks->get_confValue('editing_languages') as $l) {
            $this->tabs[] = array(
                'name'  => $l,
                'title' => language_getIcon($l),
            );
        }

        if ($this->help != null) {
            $this->tabs[] = array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help'),
            );
        }

        /* Insert tabs javascript engine */
        $this->tabObject = 'gallery_tabObject';
        $this->add_JSEngineFile ('object/ctab.js');
        $this->add_JSScript($this->tabObject.' = new CTab();');
        $this->add_JSScript($this->tabObject.'.init("general", "'.$this->theme->parts['boxTabCSSStandart'].'","'.$this->theme->parts['boxTabCSSSelected'].'","'.$this->theme->parts['boxTabCSSRollover'].'");');

        /* Build form */
        $this->form = new HTMLForm('genericgallery_form', $this->get_adminlink(array('mode'=>'save_item')), 'POST');
        $this->form->allow_files(true, $this->maxfilesize);
        $this->form->add_hidden ('page_id', $this->page_id);
        $this->form->add_hidden ('module_index', $this->module_index);
        $this->form->add_hidden ('id', $this->imageitem->vars['listid']);
        $this->form->add_hidden ('listid', $this->imageitem->vars['listid']);
        $this->form->add_hidden ('itemid', $this->imageitem->id);
        $this->form->add_hidden ('position', $this->imageitem->vars['position']);

        /* Build interface buttons (on valid, show main tab to be sure that image are sent)*/
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'  => $this->get_adminLink(array(
                    'mode'          => 'modify',
                    'id'            => $this->imageitem->vars['listid'],
                    'page_id'       => $this->page_id,
                    'module_index'  => $this->module_index,
                )),
            ),
            array(
                'title' => $camyks->get_translation('valid'),
                'link'  => 'javascript:'.$this->tabObject.'.mouseclick(\'general\');'.'setTimeout(\''.$this->form->get_JSSubmitLink().'\',100);void(0);',
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('admin_item.html.inc');
    }

    /**
     * Initialise module object in admin/save_item mode.
     * @return void
     */
    private function init_admin_save_item() {
        global $camyks;

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Load item object */
        $this->imageitem->id = isset($_REQUEST['itemid']) ? (int)$_REQUEST['itemid'] : 0;
        $this->imageitem->get_fromHeader();

        /* Save item object */
        if ($this->imageitem->save()) {
            $this->text = $camyks->get_translation('savedone');
        } else {
            $this->text = $camyks->get_translation('savefailed');
        }
        $this->imageitem->get_fromItems();

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($camyks->get_adminLink(array('mode'=>'modify_item', 'id'=>$this->imageitem->vars['listid'], 'itemid'=>$this->imageitem->id)));
    }

    /**
     * Initialise module object in admin/save_delete mode.
     * @return void
     */
    private function init_admin_delete_item() {
        global $camyks;

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Load object item */
        $this->imageitem->id = isset($_REQUEST['itemid']) ? (int)$_REQUEST['itemid'] : 0;

        /* Delete item object */
        if ($this->imageitem->delete()) {
            $this->text = $camyks->get_translation('deletedone');
        } else {
            $this->text = $camyks->get_translation('deletefailed');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('mode'=>'modify_list', 'id'=>$this->imagelist->id)));
    }
}
?>
