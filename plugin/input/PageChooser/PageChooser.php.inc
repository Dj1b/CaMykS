<?php
/**
 * @brief PageChooser Input
 * <br /> Open a request popup window with Admin_ContentPage in request mode.
 * @details Plugin / Input Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.1
 * @date Creation: Jun 2007
 * @date Modification: Jul 2025
 * @copyright 2007 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * PageChooser Input class.
 */
final class PageChooser extends Input {
    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('PageChooser', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* set plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';
    }

    /* Mark: Override input methods */

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

    /* Mark: Specific methods */

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
