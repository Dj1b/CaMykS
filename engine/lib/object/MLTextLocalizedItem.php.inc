<?php
/**
 * @brief Text localised item of Module Library item.
 * @details Engine / Object Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.1
 * @date Creation: Jul 2007
 * @date Modification: Jul 2025
 * @copyright 2007 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * MLTextLocalizedItem class.
 */
final class MLTextLocalizedItem extends MLTextItem {
    /**
     * @var array $value
     * @brief Item current values.
     */
    public $value = array();

    /**
     * Class constructor.
     * @param string $name
     * @param string $folder
     * @param string $path
     * @param string $default
     */
    public function __construct($name, $folder, $path, $default='') {
        parent::__construct($name, $folder, $path, $default);
    }

    /**
     * Initialise object with default value.
     * @return void
     */
    public function initialise() {
        global $camyks;
        $this->value = array();
        foreach ($camyks->get_confValue('editing_languages') as $l)
            $this->value[$l] = $this->default;
    }

    /**
     * Load object value.
     * @param integer $_libObjId the parent object id
     * @param string $language the language version to get
     * @return boolean
     */
    public function get($_libObjId, $language=null) {
        global $camyks;
        $this->value = array();
        if (isset($language)) {
            $this->value[$language] = $this->path.'/'.$this->folder.'/'.$this->name.$_libObjId.'_'.$language.'.html.inc';
        } else {
            foreach ($camyks->get_confValue('editing_languages') as $language)
                $this->value[$language] = $this->path.'/'.$this->folder.'/'.$this->name.$_libObjId.'_'.$language.'.html.inc';
        }
        return true;
    }

    /**
     * Save text files.
     * @param integer $_libObjId the parent object id
     * @param string $_libName the file header title
     * @return boolean
     */
    public function save($_libObjId, $_libName='Generic Content') {
        global $camyks;

        /* initialise result */
        $ok = true;

        /* update folder path if needed */
        if (folder_completePath($this->path.'/'.$this->folder,  0771)) {
            /* prepare header */
            $header = file_getPHPFileHeader($_libName.' file', '1.0');
            $header .= file_getPHPFileFooter();

            /* write files */
            foreach ($camyks->get_confValue('editing_languages') as $l ) {
                $this->filepath = $this->path.'/'.$this->folder.'/'.$this->name.$_libObjId.'_'.$l.'.html.inc';
                if (file_exists($this->filepath) or $this->value[$l] != '') {
                    if (!file_write($this->filepath, $header.$this->value[$l]))
                        $ok = false;
                }
            }
        }
        return $ok;
    }

    /**
     * Load object value from header.
     * @param string $prefix
     * @return void
     */
    public function get_fromHeader($prefix='') {
        global $camyks;

        $name = $prefix.$this->name;

        $this->value = array();
        foreach ($camyks->get_confValue('editing_languages') as $l) {
            $this->value[$l] = $this->get_valueFromHeader($name.'_'.$l);
            $this->value[$l] = $this->parse_PHPTags($this->value[$l]);
            /* check magic_quote_gpc */
            if (ini_get('magic_quotes_gpc')) {
                $this->value[$l] = stripslashes($this->value[$l]);
            }
        }
    }

    /**
     * Return values as structured array $name => $value.
     * @return array
     */
    public function get_exportedValue() {
        if (count($this->value) == 0)
            return array();
        $a = array();
        if (count($this->value) == 1) {
            foreach ($this->value as $l => $v) {
                $a[$this->name] = $v;
                $a[$this->name.'_'.$l] = $v;
            }
        } else {
            foreach ($this->value as $l => $v) {
                $a[$this->name.'_'.$l] = $v;
            }
        }
        return $a;
    }
}
?>
