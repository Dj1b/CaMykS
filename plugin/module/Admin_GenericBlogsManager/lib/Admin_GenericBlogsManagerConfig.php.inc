<?php
/**
 * @brief Admin_GenericBlogsManager Module configuration library
 * @details Plugin, Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Apr 2008
 * @date Modification: Nov 2020
 * @copyright 2008 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @note News editor mode :
 * - 0 : Text only
 * - 1 : Limited web editor
 * - 2 : Advanced web editor
 * - 3 : Full web editor
 *
 * Comments validation mode values :
 * - 0 : validated by an admin
 * - 1 : validated on post
 *
 * Document shared mode value :
 * - 0 : shared with site documents
 * - 1 : shared into a specific module folder
 * - 2 : each user has its own folder into a specific module folder
 */

/**
 * Admin_GenericBlogsManagerConfig class.
 */
final class Admin_GenericBlogsManagerConfig extends PluginConfig {
    /**
     * Class constructor.
     * @param string $name
     * @param Module $parent
     * @return void
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* Object link configuration */
        $this->add_newItem('links_maxcount', 'int', 5);

        /* Object news configuration */
        $this->add_newItem('news_editormode', 'int', 0);
        $this->add_newItem('news_allowvideo', 'boolean', false);
        $this->add_newItem('news_documentmode', 'int', 1);

        /* Object comment configuration */
        $this->add_newItem('comments_validationmode', 'int', 1);

        /* Generic initialisation */
        parent::init_config();
    }

    /* specific methods */

    /**
     * Return available news editor modes.
     * @return array
     */
    public function get_newsEditorModes() {
        return array(
            0 =>$this->get_translation('config_newseditormode_0'),
            1 =>$this->get_translation('config_newseditormode_1'),
            2 =>$this->get_translation('config_newseditormode_2'),
            3 =>$this->get_translation('config_newseditormode_3'),
        );
    }

    /**
     * Return available news document modes.
     * @return array
     */
    public function get_newsDocumentModes() {
        return array(
            0 => $this->get_translation('config_newsdocumentmode_0'),
            1 => $this->get_translation('config_newsdocumentmode_1'),
            2 => $this->get_translation('config_newsdocumentmode_2'),
        );
    }

    /**
     * Return available comment validation modes.
     * @return array
     */
    public function get_commentsValidationModes() {
        return array(
            1 => $this->get_translation('config_commentsvalidationmode_1'),
            0 => $this->get_translation('config_commentsvalidationmode_0'),
        );
    }
}
?>
