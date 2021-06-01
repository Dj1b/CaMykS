<?php
/**
 * @brief Admin_SiteReport Module
 * @details Plugin, Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Apr 2007
 * @date Modification: May 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_SiteReport class.
 */
final class Admin_SiteReport extends Module {
    /**
     * var Object $ritem
     * @brief Request object.
     */
    public $ritem;

    /**
     * var Object $rtype
     * @brief Request type object.
     */
    public $rtype;

    /**
     * var array $itemlist
     * @brief Request object list.
     */
    public $itemlist;

    /**
     * var array $typelist
     * @brief Request object type list.
     */
    public $typelist;

    /**
     * var Object $config
     * @brief Configuration object.
     */
    public $config;

    /**
     * var Object $config
     * @brief Configuration object.
     */
    protected $itemsbypage = 20;

    /**
     * var array $listpage
     * @brief Admin list page parameter.
     */
    protected $listpage;

    /**
     * var array $listpage
     * @brief Admin list type parameter.
     */
    protected $listtype;

    /**
     * var array $listpage
     * @brief Admin list status parameter.
     */
    protected $listviewed;

    /**
     * var string $answermode
     * @brief Current answer mode.
     */
    protected $answermode;

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('Admin_SiteReport', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* Override Module variables */
        $this->type = 'admin';
        $this->admin_type = 'monitoring';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Load libs */
        $this->load_library('Admin_SiteReportItem');
        $this->load_library('Admin_SiteReportType');
        $this->load_library('Admin_SiteReportConfig');

        /* Define plugin variables */
        $this->ritem = new Admin_SiteReportItem(-1, $this);
        $this->rtype = new Admin_SiteReportType(-1, $this);
        $this->config = new Admin_SiteReportConfig('config', $this);
    }

    /* Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return ($this->ritem->install() and $this->rtype->install()
            and $this->config->install() and parent::install());
    }

    /**
     * Check module installation.
     * @return boolean result
     */
    public function is_installed() {
        return $this->rtype->is_installed();
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
            'name'      => 'answer',
            'title'     => $this->get_translation('answer'),
            'default'   => false,
        );
        $this->rights[2] = array(
            'name'      => 'configure',
            'title'     => $this->get_translation('configure'),
            'default'   => false,
        );
    }

    /**
     * Update control panel description.
     * @return void
     */
    public function get_adminControlPanelAction() {
        global $camyks;
        $condition = 'answer_date=0';
        $n = $this->ritem->get_objectcount($condition);
        $camyks->trads['mod_admin_sitereport_desc'] = $this->get_translation('desc_', $n);
    }

    /**
     * Return notified items for module.
     * @return Array
     */
    public function get_adminInternalNotifications() {

        /* Load reports count */
        $cnt = $this->ritem->get_objectcount('answer_date=0');
        if ($cnt == 0)
            return array();

        /* Initialise result */
        $result = array($this->name => array(
            'title' => $this->title,
            'items' => array(
                array(
                    'title'     => $this->get_translation('tablist'),
                    'cnt'       => $cnt,
                    'priority'  => 1,
                ),
            )
        ));

        /* Send result */
        return $result;
    }

    /**
     * Initialise module object in admin mode.
     * @return void
     */
    public function init_admin() {
        global $camyks;

        /* Check read permissions */
        if ($this->check_right(0) === false)
            return $this->init_admin_accessDenied();

        /* Load module mode to execute */
        $this->mode = isset($_REQUEST['mode']) ? $_REQUEST['mode'] : 'list';

        /* Execute action */
        switch ($this->mode) {
            case 'edittype':
                /* mode == edittype */
                $this->init_admin_edittype();
                break;
            case 'savetype':
                /* mode == savetype */
                $this->init_admin_savetype();
                break;
            case 'viewtype':
                /* mode == viewtype */
                $this->init_admin_viewtype();
                break;
            case 'deletetype':
                /* mode == deletetype */
                $this->init_admin_deletetype();
                break;
            case 'viewitem':
                /* mode == viewitem */
                $this->init_admin_viewitem();
                break;
            case 'saveitem':
                /* mode == saveitem */
                $this->init_admin_saveitem();
                break;
            case 'deleteitem':
                /* mode == deleteitem */
                $this->init_admin_deleteitem();
                break;
            case 'saveconfig':
                /* mode == saveconfig */
                $this->init_admin_saveconfig();
                break;
            case 'downloadfile':
                /* mode == downloadfile */
                $this->init_admin_downloadfile();
                break;
            case 'deletefile':
                /* mode == deletefile */
                $this->init_admin_deletefile();
                break;
            case 'list':
            default:
                /* mode == list */
                $this->init_admin_list();
                break;
        }
        parent::init_admin();
    }

    /* Specific admin mode methods */

    /**
     * Initialise module object in admin/list mode
     * @return void
     */
    private function init_admin_list() {
        global $camyks;

        /* Load config */
        $this->config->get();

        /* Load list parameters from header */
        $this->listpage = isset($_REQUEST['listpage']) ? $_REQUEST['listpage'] : 0;
        $this->listtype = isset($_REQUEST['listtype']) ? $_REQUEST['listtype'] : '';
        $this->listviewed = isset($_REQUEST['listviewed']) ? $_REQUEST['listviewed'] : 0;

        if ($this->listviewed == 1) {
            $listtests = 'answer_date>0';
        } else if ($this->listviewed == 2) {
            $listtests = 'answer_date=0';
        } else {
            $listtests = '';
        }

        /* Load object list */
        $this->itemlist = $this->ritem->get_objectList(false, $listtests, $this->listpage, $this->itemsbypage, 'creation_date', 'desc');
        $this->pages = ceil($this->ritem->get_objectCount($listtests) / $this->itemsbypage);

        /* Load form */
        $this->form = new HTMLForm('admin_sitereport_form', $this->get_adminLink(array('mode'=>'list')), 'POST');

        /* Load tabs engine */
        $this->get_admin_tabs('list');

        /* Build some links */
        $this->add_JSScript('var deletereportlink="'.$this->get_adminJSLink(array('mode'=>'deleteitem', 'ritem'=>'')).'";');
        $this->add_JSScript('var deletereportmessage="'.string_html2Text($this->get_translation('message_js_deletereport')).'";');
        $this->add_JSScript('var deletetypelink="'.$this->get_adminJSLink(array('mode'=>'deletetype', 'rtype'=>'')).'";');
        $this->add_JSScript('var deletetypemessage="'.string_html2Text($this->get_translation('message_js_deletetype')).'";');
        $this->viewReportLink = $this->get_adminLink(array('mode'=>'viewitem', 'ritem'=>''));
        $this->viewTypeLink = $this->get_adminLink(array('mode'=>'viewtype', 'rtype'=>''));
        $this->editTypeLink = $this->get_adminLink(array('mode'=>'edittype', 'rtype'=>''));

        /* Button list for buttons bar */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'  => $camyks->get_adminLink(),
            ),
        );

        /* tab list for tabs bar */
        $this->tabs = array(array('name'=>'list', 'title'=>$this->get_translation('tablist')));
        if ($this->check_right(2) === true) {
            $this->tabs[] = array(
                'name'  => 'configure',
                'title' => $this->get_translation('tabconfigure'),
            );
            $this->tabs[] = array(
                'name'  =>'types',
                'title' => $this->get_translation('tabtypes'),
            );

            /* Load type list */
            $this->typelist = $this->rtype->get_objectlist();

            /* Load config form */
            $this->configform = new HTMLForm('admin_sitereport_configform', $this->get_adminLink(array('mode'=>'saveconfig')), 'POST');
            $this->add_JSScript('admin_sitereport_configFormName="'.$this->configform->name.'";');
            $this->add_JSFile('admin_sitereport.js');

            /* Load config */
            $this->config->get();
        }
    }

    /**
     * Initialise module object in admin/edittype mode.
     * @return void
     */
    private function init_admin_edittype() {
        global $camyks;

        /* Check edit type permission */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* Load object */
        $this->rtype->id = isset($_REQUEST['rtype']) ? (int)$_REQUEST['rtype'] : 0;
        $this->rtype->get(true);

        $this->rtype->get_fromItems();
        $this->form = new HTMLForm('admin_sitereport_form', $this->get_adminLink(array('mode'=>'savetype')), 'POST');
        $this->form->add_hidden('rtype', $this->rtype->id);

        /* Button list for buttons bar */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'  => $this->get_adminLink(),
            ),
            array(
                'title' => $this->get_translation('validtype'),
                'link'  => $this->form->get_HTMLSubmitLink(),
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('admin_edittype.html.inc');
    }

    /**
     * Initialise module object in admin/savetype mode.
     * @return void
     */
    private function init_admin_savetype() {
        global $camyks;

        /* Check edit type permission */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Load object */
        $this->rtype->id = isset($_REQUEST['rtype']) ? (int)$_REQUEST['rtype'] : 0;
        $this->rtype->get_fromHeader();

        /* Save object */
        if ($this->rtype->save())
            $this->text = $this->get_translation('message_typesaved');
        else
            $this->text = $this->get_translation('message_typenotsaved');

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('mode'=>'list')));
    }

    /**
     * Initialise module object in admin/viewtype mode.
     * @return void
     */
    private function init_admin_viewtype() {
        global $camyks;

        /* Check view type permission */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* Load object */
        $this->rtype->id = isset($_REQUEST['rtype']) ? (int)$_REQUEST['rtype'] : 0;
        $this->rtype->get(true);
        $this->rtype->get_fromItems();

        /* Button list for buttons bar */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'  => $this->get_adminLink(),
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('admin_viewtype.html.inc');
    }

    /**
     * Initialise module object in admin/deletetype mode.
     * @return void
     */
    private function init_admin_deletetype() {
        global $camyks;

        /* Check edit type permission */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Load object */
        $this->rtype->id = isset($_REQUEST['rtype']) ? (int)$_REQUEST['rtype'] : 0;
        $this->rtype->get();

        /* Delete object */
        if ($this->rtype->delete())
            $this->text = $this->get_translation('message_typedeleted');
        else
            $this->text = $this->get_translation('message_typenotdeleted');

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('mode'=>'list')));
    }

    /**
     * Initialise module object in admin/viewitem mode
     * @return void
     */
    private function init_admin_viewitem() {
        global $camyks;

        /* Load object */
        $this->ritem->id = isset($_REQUEST['ritem']) ? (int)$_REQUEST['ritem'] : 0;
        $this->ritem->get();
        $this->ritem->get_fromItems();
        $this->ritem->load_attachedFile();

        /* Load type */
        $this->rtype->id = $this->ritem->vars['type'];
        if (in_array($camyks->current_language, $camyks->get_confValue('editing_languages'))) {
            $this->rtype->get($camyks->current_language);
        } else {
            $this->rtype->get();
        }
        $this->rtype->get_fromItems();

        /* Save answer mode */
        if ($this->ritem->vars['answer_date'] > 0) {
            $this->answermode = 'answered';
        } else if ($this->check_right(1)===true) {
            $this->answermode = 'form';
            /* add form */
            $this->form = new HTMLForm('admin_sitereport_form', $this->get_adminLink(array('mode'=>'saveitem')), 'POST');
            $this->form->add_hidden('ritem', $this->ritem->id);
            $this->form->add_hidden('answer_admin', $camyks->adminUser->login);
            /* add javascript */
            $this->add_JSScript('admin_sitereport_formName="'.$this->form->name.'";');
            $this->add_JSFile('admin_sitereport.js');
        } else {
            $this->answermode = 'none';
        }

        $this->downloadFileLink = $this->get_adminLink(array('mode'=>'downloadfile', 'ritem'=>$this->ritem->id));
        $this->add_JSScript('var deletefilelink="'.$this->get_adminJSLink(array('mode'=>'deletefile', 'ritem'=>$this->ritem->id)).'";');
        $this->add_JSScript('var deletefilemessage="'.string_html2Text($this->get_translation('message_js_deletefile')).'";');

        /* Button list for buttons bar */
        $this->buttons = array(
            array(
                'title' => $camyks->get_translation('back'),
                'link'  => $this->get_adminLink(),
            ),
        );

        if ($this->answermode == 'form') {
            $this->buttons[] = array(
                'title' => $camyks->get_translation('valid'),
                'link'  => $this->form->get_HTMLSubmitLink(),
            );
        }

        /* Load list for tabs bar */
        $this->tabs = array(
            array(
                'name'  => 'request',
                'title' => $this->get_translation('tabrequest')
            ),
            array(
                'name'  => 'answer',
                'title' => $this->get_translation('tabanswer'),
            ),
        );

        /* Load tabs */
        $this->get_admin_tabs('request');

        /* update layout */
        $this->set_selectedLayout('admin_viewitem.html.inc');
    }

    /**
     * Initialise module object in admin/saveitem mode.
     * @return void
     */
    private function init_admin_saveitem() {
        global $camyks;

        /* Check edit items permission */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Load item data */
        $this->ritem->id = isset($_REQUEST['ritem']) ? (int)$_REQUEST['ritem'] : 0;

        /* Check if item is not already answered */
        $this->ritem->get();
        $this->ritem->get_fromItems();
        if ($this->ritem->vars['answer_date'] > 0) {
            $this->text = $this->get_translation('allreadyanswered');
        } else {
            $this->ritem->get_fromHeader();
            if ($this->ritem->save()) {
                $this->text = $camyks->get_translation('savedone');
            } else {
                $this->text = $camyks->get_translation('savefailed');
            }
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('mode'=>'list')));
    }

    /**
     * Initialise module object in admin/deleteitem mode.
     * @return void
     */
    private function init_admin_deleteitem() {
        global $camyks;

        /* Check edit items permission */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Load item data */
        $this->ritem->id = isset($_REQUEST['ritem']) ? (int)$_REQUEST['ritem'] : 0;
        if ($this->ritem->delete()) {
            $this->text = $camyks->get_translation('deletedone');
        } else {
            $this->text = $camyks->get_translation('deletefailed');
        }

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('mode'=>'list')));
    }

    /**
     * Initialise module object in admin/saveconfig mode.
     * @return void
     */
    private function init_admin_saveconfig() {
        global $camyks;

        /* Check configure permission */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* Disable admin menus */
        $this->disable_adminEngineMenus();

        /* Load object */
        $this->config->get_fromHeader();

        /* Save object */
        if ($this->config->save())
            $this->text = $this->get_translation('message_configsaved');
        else
            $this->text = $this->get_translation('message_confignotsaved');

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('mode'=>'list')));
    }

    /**
     * Initialise module object in admin/downloadfile mode.
     * @return void
     */
    private function init_admin_downloadfile() {
        global $camyks;

        /* Check request object */
        if (!isset($_REQUEST['ritem']))
            return $this->init_admin_list();

        /* Load item data */
        $this->ritem->id = (int)$_REQUEST['ritem'];
        if (!$this->ritem->get())
            return $this->init_admin_list();
        $this->ritem->get_fromItems();

        /* Load attached file */
        $this->ritem->load_attachedFile();
        if ($this->ritem->attachedFile === false)
            return $this->init_admin_viewitem();

        /* Send attached file */
        $this->ritem->attachedFile->download();
        die();
    }

    /**
     * Initialise module object in admin/deletefile mode
     * @return void
     */
    private function init_admin_deletefile() {
        global $camyks;

        /* Check request object */
        if (!isset($_REQUEST['ritem']))
            return $this->init_admin_list();

        /* Load item data */
        $this->ritem->id = (int)$_REQUEST['ritem'];
        $this->ritem->get();

        /* Delete attached file */
        if ($this->ritem->delete_attachedFile())
            $this->text = $this->get_translation('message_attachedfiledeleted');
        else
            $this->text = $this->get_translation('message_attachedfilenotdeleted');

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('mode'=>'viewitem', 'ritem'=>$this->ritem->id)));
    }

    /* Specific tool methods */

    /**
     * Build javascript for tabs.
     * @return void
     */
    private function get_admin_tabs($default='') {
        $this->tabObject = 'admin_sitereport_tabObject';
        $this->add_JSEngineFile('object/ctab.js');
        $this->add_JSScript($this->tabObject.' = new CTab();');
        $this->add_JSScript($this->tabObject.'.init("'.$default.'", "'.$this->theme->parts['boxTabCSSStandart'].'","'.$this->theme->parts['boxTabCSSSelected'].'","'.$this->theme->parts['boxTabCSSRollover'].'");');
    }
}
?>
