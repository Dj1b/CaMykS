<?php
/**
 * @brief Admin_GenericPetitionManager module.
 * <br /> Manages petitions.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Sep 2010
 * @date Modification: Jul 2025
 * @copyright 2010 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GenericPetitionManager class.
 */
final class Admin_GenericPetitionManager extends Module {
    /**
     * var Object $petitionItem
     * @brief Petition object.
     */
    public $petitionItem;

    /**
     * var array $petitionList
     * @brief Petition list.
     */
    public $petitionList = null;

    /**
     * var Object $signatureItem
     * @brief Signature object.
     */
    public $signatureItem;

    /**
     * var array $signatureList
     * @brief Signature list.
     */
    public $signatureList = null;

    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('Admin_GenericPetitionManager', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'Generic';

        /* Override Module variables */
        $this->type = 'admin';
        $this->admin_type = 'content';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Load plugin libraries */
        $this->load_library('Admin_GenericPetitionManagerPetition');
        $this->load_library('Admin_GenericPetitionManagerSignature');

        /* Initialise plugin libraries */
        $this->petitionItem = new Admin_GenericPetitionManagerPetition(0, $this);
        $this->signatureItem = new Admin_GenericPetitionManagerSignature(0, $this);
    }

    /* Mark: Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return ($this->petitionItem->install() and $this->signatureItem->install() and parent::install());
    }

    /**
     * Check module installation.
     * @return boolean result
     */
    public function is_installed() {
        return $this->petitionItem->is_installed();
    }

    /**
     * Define module permission.
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
            'name'      => 'configuration',
            'title'     => $this->get_translation('rights_configuration'),
            'default'   => false,
       );
        $this->rights[2] = array(
            'name'      => 'petition',
            'title'     => $this->get_translation('rights_petition'),
            'default'   => false,
       );
        $this->rights[3] = array(
            'name'      => 'signature',
            'title'     => $this->get_translation('rights_signature'),
            'default'   => false,
       );
    }

    /**
     * Register a menu in admin interface.
     * @return array
     */
    public function get_adminEngineSpecificMenus() {
        if ($this->check_right(1) and $this->mode == 'list_signature') {
            return array(
                array(
                    'name'  => 'petitionmanager',
                    'title' => $this->get_translation('menutitle'),
               ),
           );
        }
        return array();
    }

    /**
     * Register menu items in admin interface.
     * @return array
     */
    public function get_adminEngineSpecificMenuItems() {
        if ($this->check_right(1) and $this->mode == 'list_signature') {
            return array(
                array(
                    'name'  => 'exportXLS',
                    'title' => $this->get_translation('xlsexport'),
                    'icon'  => $this->get_fileURL('img/xls.gif'),
                    'menu'  => 'petitionmanager',
                    'url'   => 'javascript:window.open(\'request.php?module='.$this->name.'&mode=exportxls&petition_id='.$this->petitionItem->id.'\');void(0);'
               ),
           );
        }
        return array();
    }

    /**
     * Initialise module object in admin mode
     * @return void
     */
    public function init_admin() {
        global $camyks;

        /* Check user permission */
        if ($this->check_right(0) === false)
            return $this->init_admin_accessDenied();

        /* Check dependencies */
        if (!isset($camyks->inputs['TabBuilder']))
            return $this->init_admin_missingPlugin('Input', 'TabBuilder');
        if (!isset($camyks->inputs['AdminItemListViewer']))
            return $this->init_admin_missingPlugin('Input', 'AdminItemListViewer');
        if (!isset($camyks->inputs['TinyMCEv3']))
            return $this->init_admin_missingPlugin('Input', 'TinyMCEv3');

        /* Load action to execute */
        $this->mode = isset ($_REQUEST['mode']) ? $_REQUEST['mode'] : 'main';

        switch ($this->mode) {
            case 'edit_petition':
                /* mode == edit_petition */
                $this->init_admin_edit_petition();
                break;
            case 'save_petition':
                /* mode == save_petition */
                $this->init_admin_save_petition();
                break;
            case 'delete_petition':
                /* mode == delete_petition */
                $this->init_admin_delete_petition();
                break;
            case 'list_signature':
                /* mode == list_signature */
                $this->init_admin_list_signature();
                break;
            case 'edit_signature':
                /* mode == edit_signature */
                $this->init_admin_edit_signature();
                break;
            case 'save_signature':
                /* mode == save_signature */
                $this->init_admin_save_signature();
                break;
            case 'delete_signature':
                /* mode == delete_signature */
                $this->init_admin_delete_signature();
                break;
            case 'main':
            default:
                /* mode == main */
                $this->init_admin_main();
        }

        /* Perform generic initialisation */
        parent::init_admin();
    }

    /**
     * Execute module object in request mode.
     * @return void
     */
    public function execute_request() {
        global $camyks;

        /* Load admin context */
        $camyks->get_adminInit();
        if (!$camyks->check_adminUser()) {
            /* Throw fatal error */
            $camyks->throwFatalError(array(
                'title'         => $this->get_translation('fatalerror_adminonly'),
                'description'   => $this->get_translation('fatalerror_youmustbelogged'),
           ));
        }

        $camyks->current_language = 'en';

        /* Check action value */
        if (isset($_REQUEST['mode'])) {
            $action = $_REQUEST['mode'];
        } else {
            /* Throw fatal error */
            $camyks->throwFatalError(array(
                'title'         => $this->get_translation('fatalerror_actionundefined'),
                'description'   => $this->get_translation('fatalerror_actionmustbeset'),
           ));
        }

        /* Execute action */
        switch ($action) {
            case 'exportxls':
                return $this->execute_request_exportXLS();
            default :
                /* Throw fatal error */
                $camyks->throwFatalError(array(
                    'title'         => $this->get_translation('fatalerror_actionundefined'),
                    'description'   => $this->get_translation('fatalerror_actionmustbeset')
               ));
        }
    }

    /* Mark: Admin initialise mode sub methods */

    /**
     * Initialise module object in admin/main mode.
     * @return void
     */
    private function init_admin_main() {
        global $camyks;

        /* Define main mode */
        $this->mode = 'main';

        /* Load help */
        $this->get_help();

        /* Load language to use with content */
        $this->language = $this->get_adminEditionLanguage();

        /* Build petition tab */
        $this->load_library('Admin_GenericPetitionManagerPetitionListParams');
        $this->petitionList = $camyks->get_input('AdminItemListViewer');
        $this->petitionList->set_params($this->petitionListParams);
        $this->petitionList->initialise();

        /* Load petition ids */
        $petitionIDs = array_keys($this->petitionList->objectList);
        $cnts = $this->count_signsByPetitions($petitionIDs);
        foreach ($this->petitionList->objectList as $id => &$petition)
            $petition->vars['signs'] = isset($cnts[$id]) ? $cnts[$id] : 0;

        /* Load tabs */
        $this->tabBuilder = $camyks->get_input('TabBuilder');

        /* Add petitions tab */
        $this->tabBuilder->add_tab(array(
            'name'  => 'petitions',
            'title' => $this->get_translation('tabpetitions'),
        ));

        /* Add help tab */
        if ($this->help != null)
            $this->tabBuilder(array(
                'name'=>'help',
                'title'=>$camyks->get_translation('help'),
            ));

        /* Initialise tabs */
        $this->tabBuilder->initialise(array('default'=>'petitions'));

        /* Build interface buttons */
        $this->buttons = array(
            array(
                'link'  => $camyks->get_adminLink(),
                'title' => $camyks->get_translation('back'),
            ),
        );
    }

    /**
     * Initialise module object in admin/edit_petition mode.
     * @return void
     */
    private function init_admin_edit_petition() {
        global $camyks;

        /* Check user permission */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* Load language to use with content */
        $this->language = $this->get_adminEditionLanguage();
        $this->lgs = $camyks->get_confValue('editing_languages');

        /* Load petition item */
        $this->petitionItem->id = isset($_REQUEST['petition_id']) ? $_REQUEST['petition_id'] : 0;
        $this->petitionItem->get();
        $this->petitionItem->get_fromItems();

        /* Build form */
        $this->editform = new HTMLForm('edit_petition', $this->get_adminlink(array('mode'=>'save_petition')), 'POST');
        $this->editform->add_hidden('petition_id', $this->petitionItem->id);
        $this->editform->set_object($this->petitionItem);

        /* Build tabs */
        $this->tabBuilder = $camyks->get_input('TabBuilder');

        /* Add petitions tab */
        $this->tabBuilder->add_tab(array(
            'name'  => 'properties',
            'title' => $this->get_translation('tabproperties'),
        ));
        if (count($this->lgs)== 1)
            $this->tabBuilder->add_tab(array(
                'name'  => $this->lgs[0],
                'title' => $this->get_translation('tabcontent'),
            ));
        else
            foreach ($this->lgs as $l)
                $this->tabBuilder->add_tab(array(
                    'name'  => $l,
                    'title' => language_getIcon($l),
                ));

        /* Add help tab */
        if ($this->help != null)
            $this->tabBuilder->add_tab(array(
                'name'=>'help',
                'title'=>$camyks->get_translation('help'),
            ));

        /* Initialise tabs */
        $this->tabBuilder->initialise(array('default'=>'properties'));

        /* Load editor */
        $this->editor = $camyks->get_input('TinyMCEv3');
        $this->editor->initialise();

        /* Build interface title */
        $this->adminTitle = $this->title;
        $this->adminTitle .= $camyks->get_translation('formitem_separator');
        if ($this->petitionItem->id == 0)
            $this->adminTitle .= $this->get_translation('petitionnew');
        else
            $this->adminTitle .= $this->get_translation('petitionid', $this->petitionItem->id);

        /* Build button list */
        $this->buttons = array(
            array(
                'link'  => $this->get_adminLink(),
                'title' => $camyks->get_translation('back'),
            ),
            array(
                'link'  => $this->editform->get_HTMLSubmitLink(),
                'title' => $camyks->get_translation('valid'),
            )
        );

        /* Update layout */
        $this->set_selectedLayout('admin_edit_petition.html.inc');
    }

    /**
     * Initialise module object in admin/save_petition mode
     * @return void
     */
    private function init_admin_save_petition() {
        global $camyks;

        /* Check user permissions */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* Check petition id */
        if (!isset($_REQUEST['petition_id']))
            return $this->init_admin_main();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Save petition */
        $this->petitionItem->id = (int)$_REQUEST['petition_id'];
        $this->petitionItem->get_fromHeader();
        if ($this->petitionItem->save())
            $this->text = $this->get_translation('petition_saved');
        else
            $this->text = $this->get_translation('petition_notsaved');

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /**
     * Initialise module object in admin/delete_petition mode.
     * @return void
     */
    private function init_admin_delete_petition() {
        global $camyks;

        /* Check user permissions */
        if ($this->check_right(2) === false)
            return $this->init_admin_actionNotAllowed();

        /* Check petition id */
        if (!isset($_REQUEST['petition_id']))
            return $this->init_admin_main();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Delete petition */
        $this->petitionItem->id = (int)$_REQUEST['petition_id'];
        if ($this->petitionItem->delete())
            $this->text = $this->get_translation('petition_deleted');
        else
            $this->text = $this->get_translation('petition_notdeleted');

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink());
    }

    /**
     * Initialise module object in admin/list_signature mode.
     * @return void
     */
    private function init_admin_list_signature() {
        global $camyks;

        /* Check petition */
        if (!isset($_REQUEST['petition_id']))
            return $this->init_admin_main();

        /* Load petition id */
        $this->petitionItem->id = (int)$_REQUEST['petition_id'];

        /* Build petition tab */
        $this->load_library('Admin_GenericPetitionManagerSignatureListParams');
        $this->signList = $camyks->get_input('AdminItemListViewer');
        $this->signList->set_params($this->signatureListParams);
        $this->signList->initialise();

        /* Build interface title */
        $this->adminTitle = $this->title.$camyks->get_translation('formitem_separator').$this->get_translation('title_listsignature');

        /* Build interface buttons */
        $this->buttons = array(
            array(
                'link'=>$this->get_adminLink(),
                'title'=>$camyks->get_translation('back'),
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('admin_list_sign.html.inc');
    }

    /**
     * Initialise module object in admin/edit_signature mode.
     * @return void
     */
    private function init_admin_edit_signature() {
        global $camyks;

        /* Check user permissions */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* get signature item */
        $this->signatureItem->id = isset($_REQUEST['signature_id']) ? (int)$_REQUEST['signature_id'] : 0;
        $this->signatureItem->get();
        $this->signatureItem->get_fromItems();

        /* get form */
        $this->editform = new HTMLForm('edit_signature', $this->get_adminlink(array('mode'=>'save_signature')), 'POST');
        $this->editform->set_object($this->signatureItem);
        $this->editform->add_hidden('signature_id', $this->signatureItem->id);
        $this->editform->add_hidden('petition', $this->signatureItem->vars['petition']);

        /* Build interface title */
        $this->adminTitle = $this->title.$camyks->get_translation('formitem_separator').$this->get_translation('signatureid', $this->signatureItem->id);

        /* Build buttons list */
        $this->buttons = array(
            array(
                'link'  => $this->get_adminLink(array('openTab'=>'categories')),
                'title' => $camyks->get_translation('back'),
            ),
            array(
                'link'  => $this->editform->get_HTMLSubmitLink(),
                'title' => $camyks->get_translation('valid'),
            ),
        );

        /* Update layout */
        $this->set_selectedLayout('admin_edit_signature.html.inc');
    }

    /**
     * Initialise module object in admin/save_signature mode.
     * @return void
     */
    private function init_admin_save_signature() {
        global $camyks;

        /* Check user permissions */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* Check signature id */
        if (!isset($_REQUEST['signature_id']))
            return $this->init_admin_main();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Save signature */
        $this->signatureItem->id = (int)$_REQUEST['signature_id'];
        $this->signatureItem->get_fromHeader();
        if ($this->signatureItem->save())
            $this->text = $this->get_translation('signature_saved');
        else
            $this->text = $this->get_translation('signature_notsaved');

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('mode'=>'list_signature', 'petition_id'=>$this->signatureItem->vars['petition_id'])));
    }

    /**
     * Initialise module object in admin/delete_signature mode.
     * @return void
     */
    private function init_admin_delete_signature() {
        global $camyks;

        /* Check user permissions */
        if ($this->check_right(1) === false)
            return $this->init_admin_actionNotAllowed();

        /* Check signature id */
        if (!isset($_REQUEST['signature_id']))
            return $this->init_admin_main();

        /* Disable admin menu */
        $this->disable_adminEngineMenus();

        /* Delete signature */
        $this->signatureItem->id = (int)$_REQUEST['signature_id'];
        $this->signatureItem->get();
        $this->signatureItem->get_fromItems();
        if ($this->signatureItem->delete())
            $this->text = $this->get_translation('signature_deleted');
        else
            $this->text = $this->get_translation('signature_notdeleted');

        /* Update layout */
        $this->set_selectedLayout('admin_message.html.inc', 'camyks');
        $this->set_redirect($this->get_adminLink(array('mode'=>'list_signature', 'petition_id'=>$this->signatureItem->vars['petition_id'])));
    }

    /* Mark: Specific request mode methods */

    /**
     * Execute module in execute/export results as XLS mode.
     * @return void
     */
    private function execute_request_exportXLS() {
        global $camyks;

        /* Load petition item */
        if (!isset($_REQUEST['petition_id'])) {
            /* Throw fatal error */
            $camyks->throwFatalError(array(
                'title'         => $this->get_translation('fatalerror_undefinedpetition'),
                'description'   => $this->get_translation('fatalerror_'),
            ));
        }
        $this->petitionItem->id = (int)$_REQUEST['petition_id'];
        $this->petitionItem->get();
        $this->petitionItem->get_fromItems($camyks->current_language);

        /* Load external data */
        countries_loadLocales();

        /* Load excel writer library */
        require_once('Spreadsheet/Excel/Writer.php');

        /* prepare sql query */
        $params = array('status'=>1, 'petition'=>$this->petitionItem->id, 'order'=>'signdate', 'orderway'=>'asc');
        $where = $this->signatureItem->build_whereStatement($params);
        $sql = $this->signatureItem->get_objectList_databaseItemsSQLQuery($where, -1, -1, $params['order'], $params['orderway']);

        /* Creating a workbook */
        $workbook = new Spreadsheet_Excel_Writer();

        /* Sending HTTP headers */
        $workbook->send($this->petitionItem->vars['title'].'-'.strftime('%Y-%m-%d').'.xls');

        /* Creating a worksheet */
        $worksheet =& $workbook->addWorksheet($this->get_translation('export_signatures'));

        /* Creates formats */
        $header = &$workbook->addFormat();
        $header->setBold(700);

        $sday = 86400;
        $tdiff = $sday * 25569;

        $sdate = &$workbook->addFormat();
        $sdate->setNumFormat('D/M/YY');

        $ldate = &$workbook->addFormat();
        $ldate->setNumFormat('D/M/YY h:mm');

        /* Add header line */
        $c = 0;
        $worksheet->write(0, $c++, '#', $header);
        $worksheet->write(0, $c++, utf8_decode(string_html2text($this->get_translation('export_signdate'))), $header);
        $worksheet->write(0, $c++, utf8_decode(string_html2text($camyks->get_translation('civility'))), $header);
        $worksheet->write(0, $c++, utf8_decode(string_html2text($camyks->get_translation('firstname'))), $header);
        $worksheet->write(0, $c++, utf8_decode(string_html2text($camyks->get_translation('lastname'))), $header);
        $worksheet->write(0, $c++, utf8_decode(string_html2text($camyks->get_translation('email'))), $header);
        $worksheet->write(0, $c++, utf8_decode(string_html2text($camyks->get_translation('address'))), $header);
        $worksheet->write(0, $c++, utf8_decode(string_html2text($camyks->get_translation('zipcode'))), $header);
        $worksheet->write(0, $c++, utf8_decode(string_html2text($camyks->get_translation('city'))), $header);
        $worksheet->write(0, $c++, utf8_decode(string_html2text($camyks->get_translation('country'))), $header);
        $worksheet->write(0, $c++, utf8_decode(string_html2text($this->get_translation('export_birthdate'))), $header);

        /* Add sign data */
        $cnt = 0;
        $l = 1;

        if ($this->signatureItem->execute_DBQuery($sql, __LINE__)) {
            while ($data = $this->signatureItem->get_DBQueryDataLine()) {
                $c = 0;
                $worksheet->write($l, $c++, ++$cnt);
                $worksheet->write($l, $c++, number_format(($data['signdate'] + $tdiff) / $sday, 6,'.', ''), $ldate);
                $worksheet->write($l, $c++, $data['title']);
                $worksheet->write($l, $c++, utf8_decode($data['firstname']));
                $worksheet->write($l, $c++, utf8_decode($data['lastname']));
                $worksheet->write($l, $c++, $data['email']);
                $worksheet->write($l, $c++, utf8_decode($data['address']));
                $worksheet->write($l, $c++, ' '.$data['zipcode']);
                $worksheet->write($l, $c++, utf8_decode($data['city']));
                $worksheet->write($l, $c++, ($data['country']!=''?countries_getTranslation($data['country']):''));
                $worksheet->write($l, $c++, number_format(($data['birthdate'] + $tdiff) / $sday, 6,'.', ''), $sdate);
                $l++;
            }
        }

        /* Send the file */
        $workbook->close();
    }

    /* Mark: Specific admin tool methods */

    /**
     * Return signature status list.
     * @return array
     */
    public function get_signatureStatusList() {
        return $this->signatureItem->get_statusList();
    }

    /**
     * Return signatures status list.
     * @param boolean $full
     * @return array
     */
    public function get_signaturesStatusList($full=false) {
        return $this->signatureItem->get_multiStatusList($full);
    }

    /**
     * Return signature list.
     * @param array $params
     * @return array
     */
    public function get_signatureList($params=array()) {
        return $this->signatureItem->get_list($params);
    }

    /**
     * Return signature title list.
     * @param boolean $full
     * @param array $params
     * @return array
     */
    public function get_signatureTitleList($full=false, $params=array()) {
        if (!isset($params['language']))
            $params['language'] = $this->get_adminEditionLanguage();

        $list = $this->signatureItem->get_titleList($params);
        if ($full)
            $list = array(0=>$this->get_translation('signaturetitle_all'))+ $list;
        return $list;
    }

    /**
     * Return petition status list.
     * @return array
     */
    public function get_petitionStatusList() {
        return $this->petitionItem->get_statusList();
    }

    /**
     * Return petitions status list.
     * @param boolean $full
     * @return array
     */
    public function get_petitionsStatusList($full=false) {
        return $this->petitionItem->get_multiStatusList($full);
    }

    /**
     * Return petition type list.
     * @return array
     */
    public function get_petitionTypeList() {
        return $this->petitionItem->get_typeList();
    }

    /**
     * Return petitions type list.
     * @param boolean $full
     * @return array
     */
    public function get_petitionsTypeList($full=false) {
        return $this->petitionItem->get_multiTypeList($full);
    }

    /**
     * Return petition title list.
     * @param array $params
     * @return array
     */
    public function get_petitionTitleList($params=array()) {
        return $this->petitionItem->get_titleList($params);
    }

    /**
     * Return petition list.
     * @param array $params
     * @return array
     */
    public function get_petitionList($params=array()) {
        return $this->petitionItem->get_list($params);
    }

    /**
     * Return petition count.
     * @param array $params
     * @return array
     */
    public function count_petitions($params=array()) {
        return $this->petitionItem->count($params);
    }

    /**
     * Return signs count by given petition.
     * @param array $petitions
     * @return array
     */
    public function count_signsByPetitions($petitions) {
        return $this->signatureItem->count_byPetitions($petitions);
    }
}
?>
