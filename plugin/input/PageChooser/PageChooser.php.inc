<?php
/**
 * @brief PageChooser Input
 * <br /> Open a request popup window with Admin_ContentPage in request mode.
 * @details Plugin / Input Engine
 * @file plugin/input/PageChooser/PageChooser.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jun 2007
 * @date Modification: Apr 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * MultiSelectionList Input class.
 * @author CaMykS Team <camyks.contact@gmail.com>
 */
final class PageChooser extends Input {
    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    function __construct($path_type) {
        parent::__construct('PageChooser', $path_type);
        /* set plugin version */
        $this->version = '1.0';

        /* set plugin package */
        $this->plugin_package = 'Default';

        /* set plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';
    }

    /* overwrite input methods */

    /**
     * Initialise input.
     * @param string $mode
     * @param string $page
     * @param string $callback
     * @return void
     */
    public function initialise($mode='pageid', $page='1', $callback='') {
        global $camyks;

        /* check if Admin_ContentPage exists */
        if (isset($camyks->modules['Admin_ContentPage'])) {
            $link = $camyks->get_confValue('url').'/request.php?module=Admin_ContentPage';
            $this->add_JSFile('PageChooser.js');
            $this->add_JSScript('pc = new PageChooser("'.$mode.'", "'.$callback.'", "'.$link.'");');
        }

        /* Input generic initialization */
        parent::initialise();
    }

    /* specific methods */

    /**
     * Return input object link.
     * @param mixed $page_value
     * @return string
     */
    public function get_link($page_value) {
        return 'pc.open('.$page_value.');';
    }
}
?>