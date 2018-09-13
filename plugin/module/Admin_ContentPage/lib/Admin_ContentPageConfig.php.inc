<?php
/**
 * @brief Admin_ContentPage Module configuration library
 * @details Plugin / Module Library
 * @file plugin/module/Admin_ContentPage/lib/Admin_ContentPageConfig.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jun 2014
 * @date Modification: Sep 2018
 * @copyright 2014 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_ContentPageConfig class.
 */
final class Admin_ContentPageConfig extends PluginConfig {
    /**
     * Class constructor.
     * @param string $name
     * @param Module $parent
     * @return void
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* navigation values */
        $this->add_newItem('navigation_main', 'int', 1);
        $this->add_newItem('navigation_alt', 'int', 0);
        $this->add_newItem('navigation_additional', 'array', array());

        /* key pages values */
        $this->add_newItem('keyPages', 'array', array());

        /* 404 handling values */
        $this->add_newItem('page_404FallBack', 'string', 'home_display');
        $this->add_newItem('page_404ErrorFile', 'string', '');
        $this->add_newItem('page_404ErrorPage', 'string', '');
        $this->add_newItem('page_404SendHeader', 'boolean', 0);

        /* allowed actions values */
        $this->add_newItem('action_w3cValidator', 'boolean', 0);

        /* site parameters values */
        $this->add_newItem('site_ogmeta', 'boolean', 0);

        /* generic initialisation */
        parent::init_config();
    }

    /* overwrite PluginConfig methods */

    /**
     * Return object items values from header.
     * @return void
     */
    public function get_fromHeader() {
        parent::get_fromHeader();

        /* load specific additional navigation list */
        $this->vars['navigation_additional'] = array();
        if (isset($_REQUEST['navAddCnt']) and (int)$_REQUEST['navAddCnt'] > 0) {
            for ($i = 0; $i < (int)$_REQUEST['navAddCnt']; $i++) {
                if (isset($_REQUEST['navAddName'.$i]) and isset($_REQUEST['navAddValue'.$i]) and $_REQUEST['navAddName'.$i] != '') {
                    $this->vars['navigation_additional'][$_REQUEST['navAddName'.$i]] = $_REQUEST['navAddValue'.$i];
                }
            }
        }

        /* load specific key page list */
        $this->vars['keyPages'] = array();
        if (isset($_REQUEST['keyPageCnt']) and (int)$_REQUEST['keyPageCnt'] > 0) {
            for ($i = 0; $i < (int)$_REQUEST['keyPageCnt']; $i++) {
                if (isset($_REQUEST['keyPageName'.$i]) and isset($_REQUEST['keyPageValue'.$i]) and $_REQUEST['keyPageName'.$i] != '') {
                    $this->vars['keyPages'][$_REQUEST['keyPageName'.$i]] = $_REQUEST['keyPageValue'.$i];
                }
            }
        }
    }

    /* Public query methods */

    /**
     * Return key page from config.
     * @param string $key
     * @return mixed
     */
    public function get_keyPage($key) {
        if (isset($this->vars['keyPages'][$key]))
            return $this->vars['keyPages'][$key];
        return false;
    }

    /**
     * Update key page in config.
     * @param string $key
     * @param mixed $value
     * @return void
     */
    public function set_keyPage($key, $value=null) {
        if ($value == null) {
            if (isset($this->vars['keyPages'][$key]))
                return;
            unset($this->vars['keyPages'][$key]);
        } else {
            $this->vars['keyPages'][$key] = $value;
        }
        $this->save();
    }

    /**
     * Return navigation root from config.
     * @param string $key
     * @return mixed
     */
    public function get_navigationRoot($key) {
        if ($key == 'main')
            return $this->vars['navigation_main'];
        elseif ($key == 'alt')
            return $this->vars['navigation_alt'];
        elseif (isset($this->vars['navigation_additional'][$key]))
            return $this->vars['navigation_additional'][$key];
        return false;
    }

    /* Admin management dedicated methods */

    /**
     * Return w3c validation status list.
     * @return array
     */
    public function get_w3cValidatorList() {
        return array(
                0 => $this->get_translation('config_w3cvalidator_disabled'),
                1 => $this->get_translation('config_w3cvalidator_enabled'),
        );
    }

    /**
     * Return w3c validation status title
     * @return array
     */
    public function get_w3cValidatorTitle() {
        $l = $this->get_w3cValidatorList();
        if (isset($l[$this->vars['action_w3cValidator']]))
            return $l[$this->vars['action_w3cValidator']];
        return '';
    }

    /**
     * Return ogmeta status list.
     * @return array
     */
    public function get_ogMetaStatusList() {
        return array(
                0 => $this->get_translation('config_ogmeta_disabled'),
                1 => $this->get_translation('config_ogmeta_enabled'),
        );
    }

    /**
     * Return ogmeta status title.
     * @return array
     */
    public function get_ogMetaStatusTitle() {
        $l = $this->get_ogMetaStatusList();
        if (isset($l[$this->vars['site_ogmeta']]))
            return $l[$this->vars['site_ogmeta']];
        return '';
    }

    /**
     * Return error 404 fallback values.
     * @return array
     */
    public function get_404FallbackList() {
        return array(
            'home_display'      => $this->get_translation('config_404fallback_homedisplay'),
            'home_redirect'     => $this->get_translation('config_404fallback_homeredirect'),
            'page_display'      => $this->get_translation('config_404fallback_pagedisplay'),
            'page_redirect'     => $this->get_translation('config_404fallback_pageredirect'),
            'error404_display'  => $this->get_translation('config_404fallback_error404display'),
            'error404_redirect' => $this->get_translation('config_404fallback_error404redirect'),
        );
    }

    /**
     * Return ogmeta status title.
     * @return array
     */
    public function get_404FallbackTitle() {
        $l = $this->get_404FallbackList();
        if (isset($l[$this->vars['page_404FallBack']]))
            return $l[$this->vars['page_404FallBack']];
        return '';
    }
}
?>
