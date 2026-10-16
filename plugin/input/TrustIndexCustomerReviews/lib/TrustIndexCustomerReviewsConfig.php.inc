<?php
/**
 * @brief TrustIndexCustomerReviews input, configuration library.
 * @details Plugin / Input Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Oct 2026
 * @date Modification: Oct 2026
 * @copyright 2026 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * TrustIndexCustomerReviewsConfig PluginConfig class.
 */
final class TrustIndexCustomerReviewsConfig extends PluginConfig {
    /**
     * Class constructor.
     * @param string $name
     * @param Plugin $parent
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* General & display parameters */
        $this->add_newItem('widgetId', 'string', '');
        $this->add_newItem('integrationMode', 'string', 'loader');
        $this->add_newItem('rawCode', 'string', '');
        $this->add_newItem('alignment', 'string', 'none');
        $this->add_newItem('containerClass', 'string', 'trustindex-widget-container');
        $this->add_newItem('containerStyle', 'string', '');
        $this->add_newItem('enableCookieConsent', 'integer', 1);
        $this->add_newItem('showConsentMessage', 'integer', 0);

        /* Generic initialisation */
        parent::init_config();
    }

    /* Mark: Specific data methods */

    /**
     * Return integration mode list.
     * @return array
     */
    public function get_integrationModeList() {
        return array(
            'loader'    => $this->get_translation('mode_loader'),
            'raw'       => $this->get_translation('mode_raw'),
        );
    }

    /**
     * Return active integration mode title.
     * @return string
     */
    public function get_integrationModeTitle() {
        $list = $this->get_integrationModeList();
        return isset($list[$this->vars['integrationMode']]) ? $list[$this->vars['integrationMode']] : '';
    }

    /**
     * Return alignment list.
     * @return array
     */
    public function get_alignmentList() {
        return array(
            'none'      => $this->get_translation('alignment_none'),
            'left'      => $this->get_translation('alignment_left'),
            'center'    => $this->get_translation('alignment_center'),
            'right'     => $this->get_translation('alignment_right'),
        );
    }

    /**
     * Return active alignment title.
     * @return string
     */
    public function get_alignmentTitle() {
        $list = $this->get_alignmentList();
        return isset($list[$this->vars['alignment']]) ? $list[$this->vars['alignment']] : '';
    }

    /**
     * Return enableCookieConsent list.
     * @return array
     */
    public function get_enableCookieConsentList() {
        global $camyks;
        return array(
            1 => $camyks->get_translation('yes'),
            0 => $camyks->get_translation('no'),
        );
    }

    /**
     * Return active enableCookieConsent title.
     * @return string
     */
    public function get_enableCookieConsentTitle() {
        $list = $this->get_enableCookieConsentList();
        return isset($list[$this->vars['enableCookieConsent']]) ? $list[$this->vars['enableCookieConsent']] : '';
    }

    /**
     * Return showConsentMessage list.
     * @return array
     */
    public function get_showConsentMessageList() {
        global $camyks;
        return array(
            1 => $camyks->get_translation('yes'),
            0 => $camyks->get_translation('no'),
        );
    }

    /**
     * Return active showConsentMessage title.
     * @return string
     */
    public function get_showConsentMessageTitle() {
        $list = $this->get_showConsentMessageList();
        return isset($list[$this->vars['showConsentMessage']]) ? $list[$this->vars['showConsentMessage']] : '';
    }
}
?>
