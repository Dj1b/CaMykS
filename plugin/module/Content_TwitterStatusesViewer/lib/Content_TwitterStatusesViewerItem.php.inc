<?php
/**
 * @brief Content_TwitterStatusesViewer module, content library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Jul 2010
 * @date Modification: Jul 2025
 * @copyright 2010 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_TwitterStatusesViewerItem class.
 */
final class Content_TwitterStatusesViewerItem extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* Content attributes */
        $this->add_newItem('name', 'db', 'text', 'varchar', 16, '');
        $this->add_newItem('layout', 'db', 'text', 'varchar', 32, '');
        $this->add_newItem('account', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('tweetcount', 'db', 'int', 'tinyint unsigned', '', 4);
        $this->add_newItem('style', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('datedisplay', 'db', 'int', 'tinyint unsigned', '', 0);

        /* Generic initialisation */
        $this->init_library();
    }

    /* Mark: Override ModuleLibrary methods */

    /**
     * Check object data.
     * @return boolean result
     */
    public function check_data() {
        /* Check name */
        $this->_libItems['name']->check_value('symbolic', 'twitter_statuses');

        /* Return result */
        return true;
    }

    /* Mark: Specific methods */

    /**
     * Return account last statuses.
     * @return array
     */
    public function load_statuses() {
        return file_get_contents('http://twitter.com/statuses/user_timeline/'.$this->vars['account'].'.xml?count='.$this->vars['tweetcount']);
    }
}
?>
