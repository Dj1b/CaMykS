<?php
/**
 * @brief SocialNetworksSharingPanel input, configuration library.
 * @details Plugin / Input Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2.1
 * @date Creation: Jan 2018
 * @date Modification: Jul 2025
 * @copyright 2018 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * SocialNetworksSharingPanelConfig PluginConfig class.
 */
final class SocialNetworksSharingPanelConfig extends PluginConfig {

    /**
     * Class constructor.
     * @param string $name
     * @param Module $parent
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        $dnetworks = array('facebook', 'twitter', 'gplus', 'linkedin');

        /* sharing params */
        foreach ($parent->networks as $network => $data)
            if ($data['share'] == 1)
                $this->add_newItem('share_'.$network, 'integer', in_array($network, $dnetworks)? 1 : 0);

        $this->add_newItem('like_facebook', 'integer', 0);
        $this->add_newItem('like_facebookLayout', 'string', 'standard');
        $this->add_newItem('like_facebookSize', 'string', 'small');
        $this->add_newItem('like_facebookAction', 'string', 'like');

        $this->add_newItem('share_pictureFormat', 'string', 'gif');

        /* follow params */
        foreach ($parent->networks as $network => $data)
            if ($data['follow'] == 1)
                $this->add_newItem('follow_'.$network, 'string', '');

        $this->add_newItem('follow_insertion', 'int', 0);    // 0 : manual / 1 : automatic
        $this->add_newItem('follow_styleSource', 'string', 'plugin');     // plugin / theme
        $this->add_newItem('follow_location', 'string', 'fixed-left'); // left / right
        $this->add_newItem('follow_pictureFormat', 'string', 'png');

        /* facebook integration params */
        $this->add_newItem('integrate_facebook_href', 'string', '');
        $this->add_newItem('integrate_facebook_width', 'integer', 340);
        $this->add_newItem('integrate_facebook_height', 'integer', 500);
        $this->add_newItem('integrate_facebook_tabTimeline', 'boolean', true);
        $this->add_newItem('integrate_facebook_tabEvents', 'boolean', false);
        $this->add_newItem('integrate_facebook_tabMessages', 'boolean', false);
        $this->add_newItem('integrate_facebook_hideCover', 'boolean', false);
        $this->add_newItem('integrate_facebook_showFacePile', 'boolean', true);
        $this->add_newItem('integrate_facebook_hideCTA', 'boolean', false);
        $this->add_newItem('integrate_facebook_smallHeader', 'boolean', false);
        $this->add_newItem('integrate_facebook_adaptWidth', 'boolean', true);
        $this->add_newItem('integrate_facebook_lazy', 'boolean', false);

        /* set up variables */
        $this->sharingValues = false;
        $this->likeValues = false;

        /* generic initialisation */
        parent::init_config();
    }

    /* Mark: Generic tool methods */

    /**
     * Return picture format value list.
     * @return array
     */
    public function get_pictureFormatList() {
        return array(
            'gif' => 'GIF (.gif)',
            'png' => 'PNG (.png)',
            'jpg' => 'JPG (.jpg)',
        );
    }

    /**
     * Return picture format value.
     * @param string $mode
     * @return string
     */
    public function get_pictureFormatValue($mode='') {
        if (!isset($this->vars[$mode.'_pictureFormat']))
            return '';
        $list = $this->get_pictureFormatList();
        return $list[$this->vars[$mode.'_pictureFormat']];
    }

    /* sharing tool methods */

    /**
     * Return sharing network value list.
     * @return array
     */
    public function get_sharingNetworkList() {
        return array(
            0 => $this->get_translation('share_disabled'),
            1 => $this->get_translation('share_primary'),
            2 => $this->get_translation('share_secondary'),
        );
    }

    /**
     * Return sharing network value.
     * @param string $network
     * @return string
     */
    public function get_sharingNetworkValue($network='') {
        if (!isset($this->vars['share_'.$network]))
            return '';
        if ($this->sharingValues == false)
            $this->sharingValues = $this->get_sharingNetworkList();
        return $this->sharingValues[$this->vars['share_'.$network]];
    }

    /**
     * Return network like value list.
     * @return array
     */
    public function get_networkLikeList() {
        return array(
            0 => $this->get_translation('like_disabled'),
            1 => $this->get_translation('like_enabled'),
        );
    }

    /**
     * Return network like value.
     * @param string $network
     * @return string
     */
    public function get_networkLikeValue($network='') {
        if (!isset($this->vars['like_'.$network]))
            return '';
        if ($this->likeValues == false)
            $this->likeValues = $this->get_networkLikeList();
        return $this->likeValues[$this->vars['like_'.$network]];
    }

    /* Mark: Facebook specific methods */

    /**
     * Return facebook layout list.
     * @return array
     */
    public function get_facebookLayoutList() {
        return array(
            'standard'      => 'standard',
            'box_count'     => 'box_count',
            'button_count'  => 'button_count',
            'button'        => 'button',
        );
    }

    /**
     * Return facebook size list.
     * @return array
     */
    public function get_facebookSizeList() {
        return array(
            'large'     => 'large',
            'small'     => 'small',
        );
    }

    /**
     * Return facebook action list.
     * @return array
     */
    public function get_facebookActionList() {
        return array(
            'like'      => 'like',
            'recommend' => 'recommend',
        );
    }

    /* Mark: Follow related methods */

    /**
     * Return follow insertion value list.
     * @return array
     */
    public function get_followInsertionList() {
        return array(
            0 => $this->get_translation('followinsertion_manual'),
            1 => $this->get_translation('followinsertion_automatic'),
        );
    }

    /**
     * Eeturn insertion value title.
     * @return string
     */
    public function get_followInsertionTitle() {
        $l = $this->get_followInsertionList();
        return $l[$this->vars['follow_insertion']];
    }

    /**
     * Return style source value list.
     * @return array
     */
    public function get_followStyleSourceList() {
        return array(
            'plugin'    => $this->get_translation('followstylesource_plugin'),
            'theme'     => $this->get_translation('followstylesource_theme'),
        );
    }

    /**
     * Return style source value title.
     * @return string
     */
    public function get_followStyleSourceTitle() {
        $l = $this->get_followStyleSourceList();
        return $l[$this->vars['follow_styleSource']];
    }

    /**
     * Return location value list.
     * @return array
     */
    public function get_followLocationList() {
        return array(
            'fixed-left'    => $this->get_translation('followlocation_fixedleft'),
            'fixed-right'   => $this->get_translation('followlocation_fixedright'),
        );
    }

    /**
     * Return location value title.
     * @return string
     */
    public function get_followLocationTitle() {
        $l = $this->get_followLocationList();
        return $l[$this->vars['follow_location']];
    }
}
?>
