<?php
/**
 * @brief Text item of Module Library item.
 * @details Engine / Object Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.1
 * @date Creation: Apr 2007
 * @date Modification: Jul 2025
 * @copyright 2007 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * MLTextItem class.
 */
class MLTextItem extends ModuleLibraryItem {
    /**
     * @var string $folder
     * @brief Folder repository for files.
     */
    public $folder;

    /**
     * @var string $path
     * @brief Folder path for files.
     */
    public $path;

    /**
     * Class constructor.
     * @param string $name
     * @param string $folder
     * @param string $path
     * @param string $default
     */
    public function __construct($name, $folder, $path, $default='') {
        $this->name = $name;
        $this->folder = $folder;
        $this->path = $path;
        $this->default = '';
    }

    /**
     * Initialise object with default value.
     * @return void
     */
    public function initialise() {
        $this->value = $this->default;
    }

    /**
     * Load object value, the text file path
     * @param integer $_libObjId the parent object id
     * @return boolean
     */
    public function get($_libObjId) {
        /* get file path */
        $this->value = $this->path.'/'.$this->folder.'/'.$this->name.$_libObjId.'.html.inc';
        return true;
    }

    /**
     * Save text as file.
     * @param integer $_libObjId the parent object id
     * @param string $_libName the file header title
     * @return boolean
     */
    public function save($_libObjId, $_libName='Generic Content') {
        /* update folder path if needed */
        if (folder_completePath ($this->path.'/'.$this->folder,  0771)) {
            /* write file */
            $header = file_getPHPFileHeader($_libName.' file', '1.0');
            $header .= file_getPHPFileFooter();
            $this->filepath = $this->path.'/'.$this->folder.'/'.$this->name.$_libObjId.'.html.inc';
            if (file_exists($this->filepath) or $this->value != '') {
                return file_write($this->filepath, $header.$this->value);
            }
            return true;
        }
        return false;
    }

    /**
     * Delete text file.
     * @return boolean
     */
    public function delete() {
        if (file_exists($this->value))
            return @unlink($this->value);
        return true;
    }

    /**
     * Delete files folder and its content.
     * @return boolean
     */
    public function reset() {
        return ($this->uninstall() and $this->install());
    }

    /**
     * Install object
     * @return boolean
     */
    public function install() {
        /* create folders in site plugin */
        return folder_completePath($this->path.'/'.$this->folder,  0771);
    }

    /**
     * Uninstall object library.
     * @return boolean
     */
    public function uninstall() {
        return folder_delete($this->path.'/'.$this->folder, true);
    }

    /**
     * Load object value from header.
     * @param string $prefix
     * @return void
     */
    public function get_fromHeader($prefix='') {
        $name = $prefix.$this->name;

        $this->value = $this->get_valueFromHeader($name);
        $this->value = $this->parse_PHPTags($this->value);
        /* check magic_quote_gpc */
        if (ini_get('magic_quotes_gpc')) {
            $this->value = stripslashes($this->value);
        }
    }

    /**
     * Return values as structured array $name => $value.
     * @return array
     */
    public function get_exportedValue() {
        return array($this->name => $this->value);
    }
}
?>
