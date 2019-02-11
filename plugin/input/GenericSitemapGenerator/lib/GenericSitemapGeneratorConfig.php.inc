<?php
/**
 * @brief GenericSitemapGenerator Input configuration object
 * @details Plugin / Input Library
 * @file plugin/input/GenericSitemapGenerator/lib/GenericSitemapGeneratorConfig.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Feb 2019
 * @date Modification: Feb 2019
 * @copyright 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * GenericSitemapGeneratorConfig PluginConfig class.
 */
final class GenericSitemapGeneratorConfig extends PluginConfig {

    /*
     * Class constructor.
     * @param string $name
     * @param Module $parent
     * @return void
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* Update items */
        $this->add_newItem('update_method', 'int', 0);
        $this->add_newItem('update_mode', 'int', 0);
        $this->add_newItem('update_delayUnit', 'int', 2);
        $this->add_newItem('update_delayValue', 'int', 1);

        /* Last update items */
        $this->add_newItem('lastUpdate_date', 'date', 0);
        $this->add_newItem('lastUpdate_pages', 'int', 0);
        $this->add_newItem('lastUpdate_duration', 'int', 0);

        /* Define update items */
        $this->update_items = array('method', 'mode', 'delayUnit', 'delayValue');

        /* generic initialisation */
        parent::init_config();
    }

    /* Specific tool methods */

    /**
     * Load update items values from header.
     * @return void
     */
    public function get_updateFromHeader() {
        foreach ($this->update_items as $item) {
            $this->vars['update_'.$item] = $this->_libItems['update_'.$item]->get_fromHeader();
        }
    }

    /**
     * Return update method values.
     * @return array
     */
    public function get_updateMethodList() {
        return array(
            0 => $this->get_translation('updatemethod_modulereadingwithcache'),
            1 => $this->get_translation('updatemethod_modulereadingondemand'),
            2 => $this->get_translation('updatemethod_websitecrawling'),
        );
    }

    /**
     * Return update method value.
     * @return string
     */
    public function get_updateMethodTitle() {
        $l = $this->get_updateMethodList();
        return (isset($l[$this->vars['update_method']]) ? $l[$this->vars['update_method']] : '');
    }

    /**
     * Return update mode values.
     * @return array
     */
    public function get_updateModeList() {
        return array(
            0 => $this->get_translation('updatemode_manually'),
            1 => $this->get_translation('updatemode_automatically'),
        );
    }

    /**
     * Return update mode value.
     * @return string
     */
    public function get_updateModeTitle() {
        $l = $this->get_updateModeList();
        return (isset($l[$this->vars['update_mode']]) ? $l[$this->vars['update_mode']] : '');
    }

    /**
     * Return update delay unit values.
     * @return array
     */
    public function get_updateDelayUnitList() {
        global $camyks;

        /* Load CaMykS unit library */
        require_once('units.php.inc');

        return array(
            0 => unit_getTitle('minute(s)'),
            1 => unit_getTitle('hour(s)'),
            2 => unit_getTitle('day(s)'),
            3 => unit_getTitle('week(s)'),
            4 => unit_getTitle('month(s)'),
        );
    }

    /**
     * Return update delay unit value.
     * @return string
     */
    public function get_updateDelayTitle() {
        $l = $this->get_updateDelayUnitList();
        return (isset($l[$this->vars['update_delayUnit']]) ? $this->vars['update_delayValue'].' '.$l[$this->vars['update_delayUnit']] : '');
    }

    /**
     * Update last update date
     * @param int $pages
     * @param int $duration
     * @return boolean success
     */
    public function update_lastUpdateDate($pages, $duration) {
        global $camyks;

        $this->vars['lastUpdate_date'] = time();
        $this->vars['lastUpdate_pages'] = $pages;
        $this->vars['lastUpdate_duration'] = $duration;
        if ($this->save()) {
            $camyks->log('SitemapGenerator', 'Update', 'Success - '.$pages.' pages - '.$duration.' ms.');
            return true;
        }
        $camyks->log('SitemapGenerator', 'Update', 'Failure');
        return false;
    }
}
?>
