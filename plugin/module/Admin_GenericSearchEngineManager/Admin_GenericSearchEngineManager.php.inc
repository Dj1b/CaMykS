<?php
/**
 * @brief Admin_GenericSearchEngineManager module.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Sep 2026
 * @date Modification: Sep 2026
 * @copyright 2026 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GenericSearchEngineManager class.
 */
final class Admin_GenericSearchEngineManager extends Module {
    /**
     * @var Object $config
     * @brief Module configuration library.
     */
    protected $config = null;

    /**
     * @var Object $objectItem
     * @brief Indexed object.
     */
    protected $objectItem;

    /**
     * @var Object $wordItem
     * @brief Indexed word object.
     */
    protected $wordItem;

    /**
     * @var array $objectList
     * @brief List of indexed objects.
     */
    protected $objectList;

    /**
     * @var array $wordList
     * @brief List of indexed words.
     */
    protected $wordList;

    /**
     * @var Object $editForm
     * @brief Edition HTMLForm.
     */
    protected $editForm;

    /**
     * @var array $statisticData
     * @brief Indexation statistic data.
     */
    protected $statisticData;

    /**
     * @var Object $searchForm
     * @brief Search HTMLForm.
     */
    protected $searchForm;

    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('Admin_GenericSearchEngineManager', $path_type);

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

        /* Load libraries */
        $this->load_library('Admin_GenericSearchEngineManagerConfiguration');
        $this->load_library('Admin_GenericSearchEngineManagerIndexedObject');
        $this->load_library('Admin_GenericSearchEngineManagerIndexedWord');

        /* Load library items */
        $this->config = new Admin_GenericSearchEngineManagerConfiguration('config', $this);
        $this->objectItem = new Admin_GenericSearchEngineManagerIndexedObject(0, $this);
        $this->wordItem = new Admin_GenericSearchEngineManagerIndexedWord(0, $this);

        /* Register plugin as extension */
        $this->register_asExtension('Admin_Site');

        /* Register plugin to be call on page load handler */
        $this->register_asCaMykSEventHandler('onPageLoad');
    }

    /* Mark: Override Plugin methods */

    /**
     * Execute handler on page load.
     * @return void
     */
    public function execute_onCaMykSPageLoad() {
        global $camyks;
        if ($this->config->is_OpenSearchXMLEnabled())
            $camyks->HTMLPage->add_link('search', $camyks->get_rootBaseURL('absolute').'OpenSearch.xml', array('type'=>'application/opensearchdescription+xml', 'title'=>$this->get_translation('xmltitle', $camyks->get_confValue('site_title'))));
    }


    /* Mark: Override Module methods */

    /**
     * Install module.
     * @return boolean success
     */
    public function install() {
        return $this->objectItem->install() and $this->wordItem->install()
            and $this->config->install() and parent::install();
    }

    /**
     * Check if module is installed.
     * @return boolean result
     */
    public function is_installed () {
        return $this->wordItem->is_installed();
    }

    /**
     * Define module permissions
     * @return void
     */
    public function get_rights() {
        global $camyks;
        $this->rights[0] = array(
            'name'      => 'read',
            'title'     => $camyks->get_translation('read'),
            'default'   => false,
        );
    }

    /**
     * Initialise module object in admin mode.
     * @return void
     */
    public function init_admin() {
        global $camyks;

        /* Check user rights */
        if ($this->check_right(0) === false)
            return $this->init_admin_accessDenied();

        /* Check dependencies */
        if (!isset($camyks->inputs['TabBuilder']))
            return $this->init_admin_missingPlugin('Input', 'TabBuilder');

        /* Load config */
        $this->config->get();

        /* Load mode to execute */
        $this->mode = isset ($_REQUEST['mode']) ? $_REQUEST['mode'] : 'main';

        switch ($this->mode) {
            case 'edit_config':
                /* mode == edit_config */
                $this->init_admin_editConfig();
                break;
            case 'save_config':
                /* mode == save_config */
                $this->init_admin_saveConfig();
                break;
            default:
                /* mode == main */
                $this->init_admin_main();
        }

        /* generic init */
        parent::init_admin();
    }

    /**
     * Execute module object in request mode.
     * @return void
     */
    public function execute_request() {
        global $camyks;

        /* Check mode to execute */
        if (isset($_REQUEST['mode'])) {
            switch($_REQUEST['mode']) {
                case 'getOpenSearchXML':
                    return $this->execute_request_get_OpenSearchXML();
            }
        }

        /* Return default result */
        return false;
    }

    /* Mark: Admin initialise mode sub methods */

    /**
     * Initialise module object in admin/main mode.
     * @return void
     */
   private function init_admin_main() {
        global $camyks;

        /* Load help */
        $this->get_help();

        /* Build tabs */
        $this->tabBuilder = $camyks->get_input('TabBuilder');
        $this->tabBuilder->add_tabs(array(
            array(
                'name'  => 'IndexedContent',
                'title' => $this->get_translation('tabindexedcontent')
            ),
            array(
                'name'  => 'Search',
                'title' => $this->get_translation('tabsearch')
            ),
        ));

        /* Load help tab */
        if ($this->help != null)
            $this->tabBuilder->add_tab(array(
                'name'  => 'help',
                'title' => $camyks->get_translation('help'),
            ));

        /* Initialise tabs */
        $this->tabBuilder->initialise(array('default'=>'IndexedContent'));

        /* Load statistics data */
        $this->statisticData = array(
            'modules' => $this->objectItem->get_moduleStatistics(),
        );

        /* Build search form */
        $this->searchForm = new HTMLForm('searchform', $this->get_adminLink(), 'POST');
        $this->searchForm->add_hidden('openTab', 'Search');

        /* Check for search results */
        if (isset($_REQUEST['search'])) {
            $this->perform_search(array('search'=>$_REQUEST['search']));
        }

        /* Build interface buttons */
        $this->buttons = array(
            array(
                'link'  => $camyks->get_adminLink(),
                'title' => $camyks->get_translation('back'),
            ),
        );
    }

    /* Mark: Request initialise mode methods */

    /**
     * Initialise module object in request/get_OpenSearchXML mode.
     * @return void
     */
    private function execute_request_get_OpenSearchXML() {
        global $camyks;

        /* Check OpenSearch.xml is enabled */
        if (!$this->config->is_OpenSearchXMLEnabled())
            die();

        /* Initialise CaMykS */
        $camyks->get_siteInit();

        /* Compute base URL */
        $baseURL = $camyks->get_rootBaseURL('absolute');

        /* Sends headers */
        header("Content-type: text/xml");

        /* Start writing XML */
        echo '<?xml version="1.0" encoding="UTF-8"?>'."\n";
        echo '<OpenSearchDescription xmlns="http://a9.com/-/spec/opensearch/1.1/">'."\n";
        echo '<ShortName>'.$this->get_configValue('OpenSearchXML_Name').'</ShortName>'."\n";
        if ($this->get_configValue('OpenSearchXML_Description') != '')
            echo '<Description>'.$this->get_configValue('OpenSearchXML_Description').'</Description>'."\n";
        if ($this->get_configValue('OpenSearchXML_Tags') != '')
            echo '<Tags>'.$this->get_configValue('OpenSearchXML_Tags').'</Tags>'."\n";

        $theme = $camyks->get_theme($camyks->get_confValue('site_default_theme'));
        if ($theme !== false) {
            if (($u = $theme->get_fileURL('img/touchIcons/icon-64x64.png')) !== '')
                  echo '<Image height="64" width="64" type="image/png">'.$baseURL.$v.'</Image>'."\n";
            elseif (($u = $theme->get_fileURL('img/touchIcons/icon-16x16.png')) !== '')
                  echo '<Image height="16" width="16" type="image/png">'.$baseURL.$v.'</Image>'."\n";
            elseif (($u = $theme->get_fileURL('img/touchIcons/icon-192x192.png')) !== '')
                  echo '<Image height="192" width="192" type="image/png">'.$baseURL.$v.'</Image>'."\n";
        }

        if (($p = $camyks->get_siteKeypageLink($this->get_configValue('OpenSearchXML_URLPage'))) != '')
            echo ' <Url type="text/html" template="'.$baseURL.$p.'?'.$this->get_configValue('OpenSearchXML_URLParam').'={searchTerms}" />'."\n";
        else
            echo ' <Url type="text/html" template="'.$baseURL.$camyks->get_siteLink($this->get_configValue('OpenSearchXML_URLPage')).'?'.$this->get_configValue('OpenSearchXML_URLParam').'={searchTerms}" />'."\n";

        if ($this->get_configValue('OpenSearchXML_Example') != '')
            echo '<Query role="example" searchTerms="'.$this->get_configValue('OpenSearchXML_Tags').'" />'."\n";
        echo '</OpenSearchDescription>';

        /* Avoid any other action */
        die();
    }

    /* Mark: Indexing methods */

    /**
     * Index object data.
     * @param string $module
     * @param string $moduleObjectType
     * @param string $moduleObjectId
     * @param array $contents
     * @param string $linkType
     * @param array $linkURLs
     * @return boolean sucess
     */
    public function index_objectData($module, $moduleObjectType, $moduleObjectId, $contents, $linkType, $linkURLs) {
        /* Load configuration */
        $this->config->get();

        /* Load object */
        $this->objectItem->load($module, $moduleObjectType, $moduleObjectId);

        /* Delete old indexed content */
        if ($this->objectItem->id > 0) {
            if (!$this->wordItem->delete_objectIndexedContent($this->objectItem->id))
                return false;
        } else {
            $this->objectItem->save();
            $this->objectItem->get_fromItems();
        }

        /* Index object content */
        if (!$this->wordItem->insert_objectIndexContent($this->objectItem->id, $contents))
            return false;

        /* Update parent object */
        return $this->objectItem->set_asUpdated($linkType, $linkURLs);
    }

    /**
     * Unindex object data.
     * @param string $module
     * @param string $moduleObjectType
     * @param string $moduleObjectId
     * @return boolean sucess
     */
    public function unindex_objectData($module, $moduleObjectType, $moduleObjectId) {
        /* Load object */
        $this->objectItem->load($module, $moduleObjectType, $moduleObjectId);

        /* Check content */
        if ($this->objectItem->id == 0)
            return true;

        /* Delete indexed content */
        if (!$this->wordItem->delete_objectIndexedContent($this->objectItem->id))
            return false;

        /* Delete parent object */
        return $this->objectItem->delete();
    }

    /* Mark: Searching methods */

    /**
     * Perform search.
     * @param array $query
     * @return boolean success
     */
    public function perform_search($query) {
        global $camyks;

        /* Load query */
        $query = array_merge(array('search'=>'', 'language'=>$camyks->current_language, 'weights'=>array('L1'=>$this->get_configValue('Indexing_N1Weight'), 'L2'=>$this->get_configValue('Indexing_N2Weight'), 'L3'=>$this->get_configValue('Indexing_N3Weight'))), $query);

        /* Check query */
        $query['search'] = trim($query['search']);
        if ($query['search'] == '')
            return false;

        /* Check saved query */
        if ($camyks->get_sessionValue('searchQuery') == $query)
            return false;

        /* Save query */
        $camyks->set_sessionValue('searchQuery', $query);

        /* Start bench */
        $bench = new CBench();
        $bench->start();

        /* Search in words */
        $results = $this->wordItem->perform_search($query);

        /* Save results */
        $camyks->set_sessionValue('searchResults', $results);

        /* Get bench full time */
        $duration = $bench->get_fullTime();

        /* Check for logs */
        if ($this->get_configValue('Logging_LogQueries'))
            $camyks->log('SearchEngine', 'Search: '.$query['search'].'('.$query['language'].')', count($results).' result(s) - '.$duration.'ms.');

        /* Check for stats */
        if ($this->get_configValue('Logging_StatQueries'))
            $camyks->update_statistic('Search Engine', $this->name, 'mixed', $query['search'], '', '', array('IPFilter'=>1, 'checkAdmin'=>1, 'checkBot'=>0));

        /* Return success */
        return true;
    }

    /**
     * Return search query.
     * @return array
     */
    public function get_searchQuery() {
        global $camyks;
        return $camyks->get_sessionValue('searchQuery', array());
    }

    /**
     * Return search results count.
     * @return integer
     */
    public function get_searchResultCount() {
        global $camyks;
        return count($camyks->get_sessionValue('searchResults', array()));
    }

    /**
     * @return search results data.
     * @param integer $page
     * @param integer $byPage
     * @return array
     */
    public function get_searchResultData($page, $byPage=null) {
        global $camyks;

        /* Check byPage value */
        if (is_null($byPage))
            $byPage = $this->get_configValue('Results_CountPerPage');

        /* Load cached results */
        $resultIds = $camyks->get_sessionValue('searchResults', array());

        /* Slice results to get current page data */
        $resultIds = array_slice($resultIds, $page*$byPage, $byPage);

        /* Check result ids */
        if (count($resultIds) === 0)
            return array();

        /* Load objets from ids */
        $resultData = $this->objectItem->get_list(array('ids'=>$resultIds, 'order'=>array('special'=>'field (m.id, '.implode(',', $resultIds).')')));

        /* Separate result data by module */
        $resultObjIds = array();
        foreach ($resultData as $result) {
            if (!isset($resultObjIds[$result->vars['module']]))
                $resultObjIds[$result->vars['module']] = array();
            if (!isset($resultObjIds[$result->vars['module']][$result->vars['moduleObjectType']]))
                $resultObjIds[$result->vars['module']][$result->vars['moduleObjectType']] = array();
            $resultObjIds[$result->vars['module']][$result->vars['moduleObjectType']][] = $result->vars['moduleObjectId'];
        }

        /* Load results detail from sources */
        $resultDetails = array();
        foreach ($resultObjIds as $moduleName => $moduleObjectData) {
            $m = $camyks->get_module($moduleName);
            if ($m === false)
                continue;
            if (!method_exists($m, 'get_searchEngineResultDetails'))
                continue;
            $resultDetails[$moduleName] = $m->get_searchEngineResultDetails($moduleObjectData);
        }

        /* Apply details to search results */
        $results = array();
        foreach ($resultData as $result) {
            if (isset($resultDetails[$result->vars['module']][$result->vars['moduleObjectType']][$result->vars['moduleObjectId']])) {
                $results[] = array_merge(array('title'=>'', 'description'=>'', 'type'=>'', 'linkType'=>$result->vars['linkType'], 'linkURL'=>$result->vars['linkURL']), $resultDetails[$result->vars['module']][$result->vars['moduleObjectType']][$result->vars['moduleObjectId']]);
            }
        }

        /* Return result */
        return $results;
    }

    /* Mark: Public tool methods */

    /**
     * Return search engine extensions.
     * @return array
     */
    public function get_extensions() {
        return $this->get_registeredExtensions();
    }

    /* Mark: Configuration methods */

    /**
     * Return configuration value.
     * @param string $name
     * @param mixed $default
     * @return mixed
     */
    public function get_configValue($name, $default=null) {
        if ($this->config->vars == null)
            $this->config->get();
        return $this->config->get_value($name, $default);
    }

    /* Mark: Admin_Site extension configuration methods */

    /**
     * Initialise object in Admin_Site, view configuration mode.
     * @return void
     */
    public function initialise_configDisplay() {
        $this->config->get();
    }

    /**
     * Display object in Admin_Site, view configuration mode.
     * @return void
     */
    public function display_configDisplay() {
        $this->load_file('html/Configuration/View.html.inc');
    }

    /**
     * Initialise object in Admin_Site, edit configuration mode.
     * @param Object $form
     * @return void
     */
    public function initialise_configEdition($form) {
        $this->config->get();

        /* Update form */
        $this->editForm = &$form;
        $this->editForm->set_object($this->config);
        $this->editForm->add_hidden('PreviousOpenSearchXMLStatus', $this->config->is_OpenSearchXMLEnabled());
    }

    /**
     * Display object in Admin_Site, edit configuration mode
     * @return void
     */
    public function display_configEdition() {
        $this->load_file('html/Configuration/Edit.html.inc');
    }

    /**
     * Execute object in Admin_Site, save configuration mode
     * @return void
     */
    public function save_configuration() {
        $this->config->get();
        $this->config->get_fromHeader();
        if (!$this->config->save())
            return false;

        /* Load previous OpenSearch.xml status */
        $previousStatus = isset($_REQUEST['PreviousOpenSearchXMLStatus']) ? (int)$_REQUEST['PreviousOpenSearchXMLStatus'] : 0;

        /* Check status hasn't changed */
        if ($this->config->is_OpenSearchXMLEnabled() == $previousStatus)
            return true;

        /* Install rewrite rule */
        if ($previousStatus == 0)
            return $this->add_toHtaccess('RewriteRule ^OpenSearch.xml$ '.$this->get_requestJSLink(array('mode'=>'getOpenSearchXML')).' [L,NS]');
        return $this->add_toHtaccess('');
    }
}
?>
