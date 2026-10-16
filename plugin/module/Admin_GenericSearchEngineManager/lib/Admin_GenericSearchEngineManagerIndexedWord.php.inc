<?php
/**
 * @brief Admin_GenericSearchEngineManager module, indexed word library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.1.0
 * @date Creation: Sep 2026
 * @date Modification: Oct 2026
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
     * Delete content from given object list.
     * @param array $objectIds
     * @return boolean success
     */
    public function delete_objectsIndexedContent($objectIds=array()) {
        /* Check object ids */
        if (!is_array($objectIds) or count($objectIds) === 0)
            return true;

        /* Sanitise ids */
        $ids = array();
        foreach ($objectIds as $id) {
            if ((int)$id > 0)
                $ids[] = (int)$id;
        }
        if (count($ids) === 0)
            return true;

        /* Build SQL query */
        $sql = 'delete from '.$this->_libSQLTable.' where object in ('.implode(',', $ids).');';

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
                $c = array_merge(array('level'=>3, 'language'=>$camyks->get_confValue('site_default_language'), 'type'=>'html', 'content'=>''), $c);
            else
                $c = array('level'=>3, 'language'=>$camyks->get_confValue('site_default_language'), 'type'=>'html', 'content'=>$c);

            /* Get words from content */
            $words['l'.$c['level'].'_'.$c['language']] = array_merge($words['l'.$c['level'].'_'.$c['language']], string_text2Words($c['content'], array('contenttype'=>$c['type'], 'accents'=>'replace', 'changecase'=>'lower', 'keptchars'=>$this->get_configValue('Indexing_WordKeptChars'), 'minlength'=>$this->get_configValue('Indexing_WordMinLength'))));
        }

        /* Remove excluded words */
        foreach ($camyks->get_confValue('editing_languages') as $l) {
            $excludedWords = $this->get_excludedWords($l);
            if (count($excludedWords) > 0) {
                $words['l1_'.$l] = array_values(array_diff($words['l1_'.$l], $excludedWords));
                $words['l2_'.$l] = array_values(array_diff($words['l2_'.$l], $excludedWords));
                $words['l3_'.$l] = array_values(array_diff($words['l3_'.$l], $excludedWords));
            }
        }

        /* Check maximum word per level */
        if ($this->get_configValue('Indexing_N1MaxWords') > 0) {
            foreach ($camyks->get_confValue('editing_languages') as $l) {
                if (count($words['l1_'.$l]) > $this->get_configValue('Indexing_N1MaxWords')) {
                    /* Move extra words on next level and apply level limit */
                    $extraWords = array_splice($words['l1_'.$l], $this->get_configValue('Indexing_N1MaxWords'));
                    $words['l2_'.$l] = array_merge($extraWords, $words['l2_'.$l]);
                }
            }
        }
        if ($this->get_configValue('Indexing_N2MaxWords') > 0) {
            foreach ($camyks->get_confValue('editing_languages') as $l) {
                if (count($words['l2_'.$l]) > $this->get_configValue('Indexing_N2MaxWords')) {
                    /* Move extra words on next level and apply level limit */
                    $extraWords = array_splice($words['l2_'.$l], $this->get_configValue('Indexing_N2MaxWords'));
                    $words['l3_'.$l] = array_merge($extraWords, $words['l3_'.$l]);
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

                    /* Add occurences to word with logarithmic saturation */
                    $saturatedCnt = min(5, 1 + (int)floor(log($cnt, 2)));
                    $data[$word.'_'.$l]['l'.$level.'Weight'] += $saturatedCnt;
                }
            }
        }

        /* Check if content has words to index */
        if (count($data) === 0)
            return true;

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
        $words = array_unique($words);
        $excludedWords = $this->get_excludedWords($query['language']);
        if (count($excludedWords) > 0)
            $words = array_values(array_diff($words, $excludedWords));
        if (count($words) == 0)
            return $results;

        /* Load variant weight configuration */
        $variantWeight = (float)$this->get_configValue('Searching_VariantWeight', 0.75);

        /* Build search words with variants */
        $exactWords = array();
        $allWords = array();
        $wordGroups = array();

        foreach ($words as $word) {
            $word = substr($word, 0, 32);
            $exactWords[] = $word;
            if ($variantWeight > 0) {
                $variants = $this->get_wordVariants($word, $query['language']);
            } else {
                $variants = array($word);
            }
            $wordGroups[] = $variants;
            $allWords = array_merge($allWords, $variants);
        }
        $allWords = array_values(array_unique($allWords));

        /* Resolve date filtering */
        $checkDates = (!isset($query['checkDates']) or $query['checkDates']);
        $searchDate = (isset($query['date']) and !is_null($query['date'])) ? (int)$query['date'] : time();

        /* Build SQL query */
        $sql = 'select w.object, ';
        if ($variantWeight > 0 and $variantWeight < 1.0 and count($allWords) > count($exactWords)) {
            $exactEscaped = array();
            foreach ($exactWords as $ew)
                $exactEscaped[] = '"'.addslashes($ew).'"';
            $sql .= ' sum((case when w.word in ('.implode(', ', $exactEscaped).') then 1.0 else '.$variantWeight.' end) * (w.l1Weight*'.(int)$query['weights']['L1'].' + w.l2Weight*'.(int)$query['weights']['L2'].' + w.l3Weight*'.(int)$query['weights']['L3'].')) as score';
        } else {
            $sql .= ' sum(w.l1Weight*'.(int)$query['weights']['L1'].' + w.l2Weight*'.(int)$query['weights']['L2'].' + w.l3Weight*'.(int)$query['weights']['L3'].') as score';
        }
        $sql .= ' from '.$this->_libSQLTable.' as w';
        if ($checkDates or !empty($query['modules']) or !empty($query['moduleObjectTypes']))
            $sql .= ' inner join '.$this->get_objectSQLTable().' as o on w.object = o.id';
        $sql .= ' where w.lg="'.addslashes($query['language']).'"';
        if ($checkDates) {
            $sql .= ' and (o.publicationDate = 0 or o.publicationDate <= '.$searchDate.')';
            $sql .= ' and (o.expirationDate = 0 or o.expirationDate >= '.$searchDate.')';
        }
        if (!empty($query['modules'])) {
            $sm = array();
            foreach ($query['modules'] as $module)
                $sm[] = '"'.addslashes($module).'"';
            $sql .= ' and o.module in ('.implode(', ', $sm).')';
        }
        if (!empty($query['moduleObjectTypes'])) {
            $st = array();
            foreach ($query['moduleObjectTypes'] as $type)
                $st[] = '"'.addslashes($type).'"';
            $sql .= ' and o.moduleObjectType in ('.implode(', ', $st).')';
        }
        $sql .= ' and (';

        $sw = array();
        foreach ($wordGroups as $group) {
            $gw = array();
            foreach ($group as $w)
                $gw[] = 'w.word = "'.addslashes($w).'"';
            $sw[] = '('.implode(' or ', $gw).')';
        }
        $sql .= implode(' or ', $sw);
        $sql .= ') group by w.object';

        /* Order by */
        if (count($exactWords) > 1 and count($allWords) > count($exactWords)) {
            $exactEscaped = array();
            foreach ($exactWords as $ew)
                $exactEscaped[] = '"'.addslashes($ew).'"';
            $sql .= ' order by count(distinct case when w.word in ('.implode(', ', $exactEscaped).') then w.word else null end) desc, count(distinct w.word) desc, score desc';
        } else {
            $sql .= ' order by count(distinct w.word) desc, score desc';
        }
        $sql .= ' limit '.(int)$this->get_configValue('Results_MaximumCount').';';

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
     * Return word variants (singular/plural and direct inflections).
     * @param string $word
     * @param string $language
     * @return array
     */
    public function get_wordVariants($word, $language='fr') {
        $variants = array($word);
        $len = strlen($word);

        /* Ignore very short words */
        if ($len < 3)
            return $variants;

        if ($language === 'fr') {
            /* 1. Words ending in -eau, -eaux */
            if (substr($word, -4) === 'eaux') {
                $variants[] = substr($word, 0, -1);
            } elseif (substr($word, -3) === 'eau') {
                $variants[] = $word.'x';
            }
            /* 2. Words ending in -eu, -eux */
            elseif (substr($word, -4) === 'ieux') {
                $variants[] = substr($word, 0, -1);
            } elseif (substr($word, -3) === 'eux' and !in_array($word, array('peux', 'veux', 'mieux', 'deux'))) {
                $variants[] = substr($word, 0, -1);
            } elseif (substr($word, -2) === 'eu') {
                $variants[] = $word.'x';
            }
            /* 3. Words ending in -oux <-> -ou */
            elseif (substr($word, -4) === 'oux') {
                $variants[] = substr($word, 0, -1);
            } elseif (in_array($word, array('bijou', 'caillou', 'chou', 'genou', 'hibou', 'joujou', 'pou'))) {
                $variants[] = $word.'x';
            }
            /* 4. Words ending in -aux <-> -al / -ail */
            elseif (substr($word, -3) === 'aux' and $len > 4) {
                if ($word === 'travaux')
                    $variants[] = 'travail';
                else
                    $variants[] = substr($word, 0, -3).'al';
            } elseif ($word === 'travail') {
                $variants[] = 'travaux';
            } elseif (substr($word, -2) === 'al' and $len > 3) {
                if (!in_array($word, array('bal', 'carnaval', 'chacal', 'festival', 'recital', 'regal')))
                    $variants[] = substr($word, 0, -2).'aux';
                else
                    $variants[] = $word.'s';
            }
            /* 5. Plural in -s (words not ending in s, x, z) */
            elseif (substr($word, -1) === 's') {
                if ($len > 3 and substr($word, -2) !== 'ss') {
                    $variants[] = substr($word, 0, -1);
                }
            } elseif (substr($word, -1) !== 'x' and substr($word, -1) !== 'z') {
                $variants[] = $word.'s';
            }

            /* 6. Common verb infinitive -er <-> -e, -es */
            if (substr($word, -2) === 'er' and $len > 4) {
                $base = substr($word, 0, -2);
                $variants[] = $base.'e';
                $variants[] = $base.'es';
            }
        } elseif ($language === 'en') {
            /* 1. Plural in -ies <-> -y */
            if (substr($word, -3) === 'ies' and $len > 4) {
                $variants[] = substr($word, 0, -3).'y';
            } elseif (substr($word, -1) === 'y' and $len > 3 and !in_array(substr($word, -2, 1), array('a', 'e', 'i', 'o', 'u'))) {
                $variants[] = substr($word, 0, -1).'ies';
            }
            /* 2. Plural in -es */
            elseif (substr($word, -2) === 'es' and $len > 4) {
                $variants[] = substr($word, 0, -2);
                $variants[] = substr($word, 0, -1);
            }
            /* 3. Plural in -s */
            elseif (substr($word, -1) === 's') {
                if ($len > 3 and substr($word, -2) !== 'ss')
                    $variants[] = substr($word, 0, -1);
            } else {
                $variants[] = $word.'s';
            }
        }

        /* Filter excluded words and truncate to 32 chars */
        $excludedWords = $this->get_excludedWords($language);
        $cleanVariants = array();
        foreach (array_unique($variants) as $v) {
            $v = substr($v, 0, 32);
            if ($v !== '' and strlen($v) >= (int)$this->get_configValue('Indexing_WordMinLength', 2) and !in_array($v, $excludedWords))
                $cleanVariants[] = $v;
        }

        return count($cleanVariants) > 0 ? $cleanVariants : array($word);
    }

    /**
     * Return excluded words list for given language.
     * @param string $language
     * @return array
     */
    private function get_excludedWords($language) {
        $excluded = trim((string)$this->get_configValue('Indexing_ExcludedWords_'.$language, ''));
        if ($excluded === '')
            return array();
        return array_unique(string_text2Words($excluded, array('contenttype'=>'text', 'accents'=>'replace', 'changecase'=>'lower', 'keptchars'=>$this->get_configValue('Indexing_WordKeptChars'), 'minlength'=>1)));
    }

    /**
     * Return indexed object SQL table name.
     * @return string
     */
    private function get_objectSQLTable() {
        return $this->_libParent->get_objectSQLTable();
    }

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
