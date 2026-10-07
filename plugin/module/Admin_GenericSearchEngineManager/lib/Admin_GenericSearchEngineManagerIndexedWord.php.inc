<?php
/**
 * @brief Admin_GenericSearchEngineManager module, indexed word library.
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
 * Admin_GenericSearchEngineManagerIndexedWord class.
 */
final class Admin_GenericSearchEngineManagerIndexedWord extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* Content attributes */
        $this->add_newItem('object', 'db', 'int', 'bigint unsigned', '', 0);
        $this->add_newItem('lg', 'db', 'text', 'varchar', 2, '');
        $this->add_newItem('word', 'db', 'text', 'varchar', 32, '');
        $this->add_newItem('hash', 'db', 'int', 'bigint', '', 0);
        $this->add_newItem('l1Weight', 'db', 'int', 'smallint unsigned', '', 0);
        $this->add_newItem('l2Weight', 'db', 'int', 'smallint unsigned', '', 0);
        $this->add_newItem('l3Weight', 'db', 'int', 'smallint unsigned', '', 0);

        /* Generic initialisation */
        $this->init_library();
    }

    /* Mark: Action methods */

    /**
     * Delete content from given object.
     * @param integer $objectId
     * @return boolean success
     */
    public function delete_objectIndexedContent($objectId) {
        /* Check object id */
        if (!($objectId > 0))
            return false;

        /* Build SQL query */
        $sql = 'delete from '.$this->_libSQLTable.' where object = '.$objectId;

        /* Return SQL query execution success */
        return $this->execute_DBQuery($sql, __LINE__, __FILE__);
    }

    /**
     * Insert content for given object.
     * @param integer $objectId
     * @param array $content
     * @return boolean success
     */
    public function insert_objectIndexContent($objectId, $content) {
        global $camyks;

        /* Initialise list */
        $words = array();

        /* Initialise list items */
        foreach ($camyks->get_confValue('editing_languages') as $l) {
            $words['l1_'.$l] = array();
            $words['l2_'.$l] = array();
            $words['l3_'.$l] = array();
        }

        /* Read content */
        foreach ($content as $c) {
            /* Check content */
            if (is_array($c))
                $c = array_merge(array(array('level'=>3, 'language'=>$camyks->get_confValue('site_default_language'), 'type'=>'html', 'content'=>'')), $c);
            else
                $c = array('level'=>3, 'language'=>$camyks->get_confValue('site_default_language'), 'type'=>'html', 'content'=>$c);

            /* Get words from content */
            $words['l'.$c['level'].'_'.$c['language']] += string_text2Words($c['content'], array('contenttype'=>$c['type'], 'accents'=>'replace', 'changecase'=>'lower', 'keptchars'=>$this->get_configValue('Indexing_WordKeptChars'), 'minlength'=>$this->get_configValue('Indexing_WordMinLength')));
        }

        /* Check maximum word per level */
        if ($this->get_configValue('Indexing_N1MaxWords') > 0) {
            foreach ($camyks->get_confValue('editing_languages') as $l) {
                if (count($words['l1_'.$l]) > $this->get_configValue('Indexing_N1MaxWords')) {
                    /* Move extra words on next level */
                    $words['l2_'.$l] = array_splice($words['l1_'.$l], $this->get_configValue('Indexing_N1MaxWords'), 0) + $words['l2_'.$l];
                    /* Apply level limit */
                    $words['l1_'.$l] = array_splice($words['l1_'.$l], 0, $this->get_configValue('Indexing_N1MaxWords'));
                }
            }
        }
        if ($this->get_configValue('Indexing_N2MaxWords') > 0) {
            foreach ($camyks->get_confValue('editing_languages') as $l) {
                if (count($words['l2_'.$l]) > $this->get_configValue('Indexing_N2MaxWords')) {
                    /* Move extra words on next level */
                    $words['l3_'.$l] = array_splice($words['l2_'.$l], $this->get_configValue('Indexing_N2MaxWords'), 0) + $words['l3_'.$l];
                    /* Apply level limit */
                    $words['l2_'.$l] = array_splice($words['l2_'.$l], 0, $this->get_configValue('Indexing_N2MaxWords'));
                }
            }
        }

        /* Count occurences of words per level and languages */
        foreach ($camyks->get_confValue('editing_languages') as $l) {
            $words['l1_'.$l] = array_count_values($words['l1_'.$l]);
            $words['l2_'.$l] = array_count_values($words['l2_'.$l]);
            $words['l3_'.$l] = array_count_values($words['l3_'.$l]);
        }

        /* Initialise content data */
        $data = array();

        /* Build content data */
        foreach ($camyks->get_confValue('editing_languages') as $l) {
            for ($level = 1; $level <= 3; $level++) {
                foreach ($words['l'.$level.'_'.$l] as $word => $cnt) {
                    /* Create word if needed */
                    if (!isset($data[$word.'_'.$l])) {
                        $data[$word.'_'.$l] = array(
                            'object'    => $objectId,
                            'lg'        => $l,
                            'word'      => substr($word, 0, 32),
                            'hash'      => crc32($word),
                            'l1Weight'  => 0,
                            'l2Weight'  => 0,
                            'l3Weight'  => 0,
                        );
                    }

                    /* Add occurences to word ¨*/
                    $data[$word.'_'.$l]['l'.$level.'Weight'] += $cnt;
                }
            }
        }

        /* Add content data to database */
        return $this->insert_multiObjectsDatabaseItems(array('object', 'lg', 'word', 'hash', 'l1Weight', 'l2Weight', 'l3Weight'), $data);
    }

    /* Mark: Search methods */

    /**
     * Perform a search in words.
     * @param array $query
     * @return array
     */
    public function perform_search($query) {
        /* Initialise result */
        $results = array();

        /* Load words to search */
        $words = string_text2Words($query['search'], array('contenttype'=>'text', 'accents'=>'replace', 'changecase'=>'lower', 'keptchars'=>$this->get_configValue('Indexing_WordKeptChars'), 'minlength'=>$this->get_configValue('Indexing_WordMinLength')));
        if (count($words) == 0)
            return $results;

        /* Build SQL query */
        $sql = 'select object, ';
        $sql .= ' sum(l1Weight*'.$query['weights']['L1'].') + sum(l2Weight*'.$query['weights']['L2'].') + sum(l1Weight*'.$query['weights']['L1'].') as score';
        $sql .= ' from '.$this->_libSQLTable;
        $sql .= ' where lg="'.$query['language'].'" and (';

        $sw = array();
        foreach ($words as $word) {
            $sw[] = 'word = "'.substr($word, 0, 32).'"';
        }
        $sql .= implode(' or ', $sw);
        $sql .= ') group by object';
        $sql .= ' order by score desc';
        $sql .= ' limit '.$this->get_configValue('Results_MaximumCount').';';

        /* Execute SQL query */
        if ($this->execute_DBQuery($sql, __LINE__, __FILE__)) {
            while ($data = $this->get_DBQueryDataLine()) {
                $results[] = $data['object'];
            }
        }

        /* Return result */
        return $results;
    }

    /* Mark: Specific tool methods */

    /**
     * Return configuration value.
     * @param string $name
     * @param mixed $default
     * @return mixed
     */
    private function get_configValue($name, $default=null) {
        return $this->_libParent->get_configValue($name, $default);
    }
}
?>
