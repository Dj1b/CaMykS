<?php
/**
 * @brief Admin_GenericSearchEngineManager module, configuration library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Sep 2026
 * @date Modification: Sep 2026
 * @copyright 2026 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GenericSearchEngineManagerConfig class.
 */
final class Admin_GenericSearchEngineManagerConfiguration extends PluginConfig {
    /*
     * Class constructor.
     * @param string $name
     * @param Module $parent
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);
        global $camyks;

        /* Indexing configuration attributes */
        foreach ($camyks->get_confValue('editing_languages') as $l)
            $this->add_newItem('Indexing_ExcludedWords_'.$l, 'string', '');
        $this->add_newItem('Indexing_WordMinLength', 'int', 2);
        $this->add_newItem('Indexing_WordKeptChars', 'string', '');
        $this->add_newItem('Indexing_N1MaxWords', 'int', 25);
        $this->add_newItem('Indexing_N2MaxWords', 'int', 100);
        $this->add_newItem('Indexing_N1Weight', 'int', 5);
        $this->add_newItem('Indexing_N2Weight', 'int', 2);
        $this->add_newItem('Indexing_N3Weight', 'int', 1);

        /* Results configuration attributes */
        $this->add_newItem('Results_MaximumCount', 'int', 1000);
        $this->add_newItem('Results_CountPerPage', 'int', 10);

        /* Logging configuration attributes */
        $this->add_newItem('Logging_LogQueries', 'boolean', true);
        $this->add_newItem('Logging_StatQueries', 'boolean', true);

        /* OpenSearch.xml configuration attributes */
        $this->add_newItem('OpenSearchXML_Status', 'boolean', false);
        $this->add_newItem('OpenSearchXML_Name', 'string', '');
        $this->add_newItem('OpenSearchXML_Description', 'string', '');
        $this->add_newItem('OpenSearchXML_Tags', 'string', '');
        $this->add_newItem('OpenSearchXML_URLPage', 'string', '');
        $this->add_newItem('OpenSearchXML_URLParam', 'string', '');
        $this->add_newItem('OpenSearchXML_Example', 'string', '');

        /* Generic initialisation */
        parent::init_config();
    }

    /* Mark: Override PluginConfig methods */

    /**
     * Check object items values.
     * @return boolean
     */
    public function check_data() {
        /* Trim value */
        $this->vars['OpenSearchXML_Name'] = trim($this->vars['OpenSearchXML_Name']);
        $this->vars['OpenSearchXML_Description'] = trim($this->vars['OpenSearchXML_Description']);
        $this->vars['OpenSearchXML_Tags'] = trim($this->vars['OpenSearchXML_Tags']);
        $this->vars['OpenSearchXML_URLPage'] = trim($this->vars['OpenSearchXML_URLPage']);
        $this->vars['OpenSearchXML_URLParam'] = trim($this->vars['OpenSearchXML_URLParam']);
        $this->vars['OpenSearchXML_Example'] = trim($this->vars['OpenSearchXML_Example']);

        /* Check status */
        if ($this->vars['OpenSearchXML_Status'] == false)
            return true;

        /* Check mandatory values */
        if ($this->vars['OpenSearchXML_Name'] == '')
            $this->vars['OpenSearchXML_Status'] = 0;
        elseif ($this->vars['OpenSearchXML_URLPage'] == '')
            $this->vars['OpenSearchXML_Status'] = 0;
        elseif ($this->vars['OpenSearchXML_URLParam'] == '')
            $this->vars['OpenSearchXML_Status'] = 0;
        return true;
    }


    /* Mark: OpenSearch.xml related methods */

    /**
     * Check OpenSearch.xml is enabled.
     * @return boolean result
     */
    public function is_OpenSearchXMLEnabled() {
        /* Load configuration values if not already done */
        if (is_null($this->vars))
            $this->get();

        /* Check status */
        return $this->get_value('OpenSearchXML_Status');
    }
}
?>
