<?php
/**
 * @brief CookieAgreementMessage Input configuration object
 * @details Plugin / Input Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.1.0
 * @date Creation: Feb 2018
 * @date Modification: Mar 2021
 * @copyright 2018 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * ContentAnchorMenuConfig PluginConfig class.
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

        $this->add_newItem('insertion', 'int', 0);                  // 0 : manual / 1 : automatic
        $this->add_newItem('message', 'array', array());
        $this->add_newItem('styleSource', 'string', 'plugin');      // plugin / theme
        $this->add_newItem('aboutCookie', 'string', '');            // empty / URL / true: send to default cookie page
        $this->add_newItem('remindTTL', 'int', 180);                // days to remind agreement, default value is half a year
        $this->add_newItem('location', 'string', 'bottom-left');    // top / top-left / top-right / bottom / bottom-left / bottom-right / centered

        /* generic initialisation */
        parent::init_config();
    }

    /* Override PluginConfig methods */

    /**
     * Load object items values from header.
     * @return void
     */
    public function get_fromHeader() {
        global $camyks;
        parent::get_fromHeader();

        /* load message for each available languages */
        $this->vars['message'] = array();
        foreach ($camyks->get_confValue('editing_languages') as $language) {
            $this->vars['message'][$language] = isset($_REQUEST['message_'.$language]) ? $_REQUEST['message_'.$language] : '';
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
            'centered'      => $this->get_translation('location_centered'),
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
