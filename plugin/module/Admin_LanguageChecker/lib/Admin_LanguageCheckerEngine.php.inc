<?php
/**
 * @brief Admin_LanguageChecker Module, engine library.
 * @details Plugin, Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Nov 2006
 * @date Modification: Jan 2021
 * @copyright 2006 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_LanguageCheckerEngine class.
 */
final class Admin_LanguageCheckerEngine {
    /**
     * var boolean $hasfile
     * @brief Has language file.
     */
    public $hasfile;

    /**
     * var array $trads
     * @brief Locale list.
     */
    public $trads;

    /**
     * Class constructor.
     * @param string $folder
     * @param string $locale
     * @return void
     */
    public function __construct($folder, $locale) {
        global $camyks;

        /* Build file full path */
        $file = $folder.'/translation_'.$locale.$camyks->file_extension;

        /* Load locales */
        $this->trads = array();
        if (file_exists($file)) {
            $this->hasfile = true;
            require ($file);
        } else {
            $this->hasfile = false;
        }
    }
}
?>
