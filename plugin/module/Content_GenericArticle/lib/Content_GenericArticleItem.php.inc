<?php
/**
 * @brief Content_GenericArticle module, article item library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Sep 2007
 * @date Modification: Jul 2025
 * @copyright 2007 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_GenericArticleItem class.
 */
final class Content_GenericArticleItem extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* Content description */
        $this->add_newItem('name', 'db', 'text', 'varchar', 32, '');
        $this->add_newItem('layout', 'db', 'text', 'varchar', 32, '');
        $this->add_newItem('date_', 'db', 'date', 'bigint unsigned', '', 0);
        $this->add_newItem('author', 'db', 'text', 'varchar', 32, '');

        /* Database localised content */
        $this->add_newItem('title', 'db', 'text', 'varchar', 128, '', true);
        $this->add_newItem('subtitle', 'db', 'text', 'varchar', 255, '', true);
        $this->add_newItem('header', 'db', 'text', 'text', '', '', true);
        $this->add_newItem('note', 'db', 'text', 'text', '', '', true);

        /* Text file localised content */
        $this->add_newItem('content', 'text', 'content','', '', '',    true);

        /* Generic initialisation */
        $this->init_library();
    }

    /* Mark: Override ModuleLibrary methods */

    /**
     * Check object data.
     * @return boolean result
     */
    public function check_data() {
        /* Check symbolic name value */
        $this->_libItems['name']->check_value('symbolic_name', 'article');

        /* Return success */
        return true;
    }

    /**
     * Initialise object
     * @return boolean success
     */
    public function initialise() {
        global $camyks;

        /* Do generic initialisation */
        parent::initialise();

        /* Update author value with current admin user login */
        $this->_libItems['author']->value = $camyks->adminUser->login;

        /* Return success */
        return true;
    }
}
?>
