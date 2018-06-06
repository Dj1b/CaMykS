<?php
/**
 * @brief CookieAgreementMessage Input configuration object
 * @details Plugin / Input Library
 * @file plugin/input/CookieAgreementMessage/lib/CookieAgreementMessageConfig.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Feb 2018
 * @date Modification: Apr 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * ContentAnchorMenuConfig PluginConfig class.
 * @author CaMykS Team <camyks.contact@gmail.com>
 */
final class CookieAgreementMessageConfig extends PluginConfig {
    /**
     * Class constructor.
     * @param string $name
     * @param Module $parent
     * @return void
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        $this->add_newItem('insertion', 'int', 0);              // 0 : manual / 1 : automatic
        $this->add_newItem('message', 'array', array());
        $this->add_newItem('styleSource', 'string', 'plugin');  // plugin / theme
        $this->add_newItem('aboutCookie', 'string', '');        // empty / URL / true: send to default cookie page
        $this->add_newItem('remindTTL', 'int', 365);            // days to remind agreement
        $this->add_newItem('location', 'string', 'top');        // top / top-left / top-right / bottom / bottom-left / bottom-right

        /* generic initialisation */
        parent::init_config();
    }

    /* overwrite pluginConfig methods */

    /**
     * Get object items values from header.
     * @return void
     */
    public function get_fromHeader() {
        global $camyks;
        parent::get_fromHeader();

        /* load message for each available languages */
        $this->vars['message'] = array();
        foreach ($camyks->get_confValue('editing_languages') as $language) {
            $this->vars['message'][$language] = isset($_REQUEST['message_'.$language])?$_REQUEST['message_'.$language]:'';
        }
    }

    /* specific tool methods */

    /**
     * Return insertion value list.
     * @return array
     */
    public function get_insertionList() {
        return array(
            0 => $this->get_translation('insertion_manual'),
            1 => $this->get_translation('insertion_automatic'),
        );
    }

    /**
     * Return insertion value title.
     * @return string
     */
    public function get_insertionTitle() {
        $l = $this->get_insertionList();
        return $l[$this->vars['insertion']];
    }

    /**
     * Return style source value list.
     * @return array
     */
    public function get_styleSourceList() {
        return array(
            'plugin'    => $this->get_translation('stylesource_plugin'),
            'theme'     => $this->get_translation('stylesource_theme'),
        );
    }

    /**
     * Return style source value title.
     * @return string
     */
    public function get_styleSourceTitle() {
        $l = $this->get_styleSourceList();
        return $l[$this->vars['styleSource']];
    }

    /**
     * Return location value list.
     * @return array
     */
    public function get_locationList() {
        return array(
            'top'           => $this->get_translation('location_top'),
            'top-left'      => $this->get_translation('location_topleft'),
            'top-right'     => $this->get_translation('location_topright'),
            'bottom'        => $this->get_translation('location_bottom'),
            'bottom-left'   => $this->get_translation('location_bottomleft'),
            'bottom-right'  => $this->get_translation('location_bottomright'),
        );
    }

    /**
     * Return location value title.
     * @return string
     */
    public function get_locationTitle() {
        $l = $this->get_locationList();
        return $l[$this->vars['location']];
    }
}
?>