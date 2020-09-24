<?php
/**
 * @brief Admin_Statistics Module options for mixed type stats library.
 * @details Plugin, Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: May 2007
 * @date Modification: Sep 2020
 * @copyright 2007 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_StatisticMixedOptions class.
 */
final class Admin_StatisticMixedOptions extends ModuleLibrary {

    /**
     * var integer $optionSettingsDisplay
     * @brief Define settings to display in option tab.
     */
    public $optionSettingsDisplay = 1;

    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     * @return void
     */
    public function __construct($id, &$module) {
        parent::__construct ($id, $module);

        /* Define items */
        $this->add_newItem('displaymode', 'temp', 'int', 'tinyint', '', 0);
        $this->add_newItem('displayday', 'temp', 'date', 'bigint', '', time());
        $this->add_newItem('displayfrom', 'temp', 'date', 'bigint', '', time());
        $this->add_newItem('displayto', 'temp', 'date', 'bigint', '', time());
        $this->add_newItem('displaycount', 'temp', 'int', 'tinyint', '', 10);
        $this->add_newItem('coloralternate0', 'temp', 'text', 'varchar', 6, '5b8dcd');
        $this->add_newItem('coloralternate1', 'temp', 'text', 'varchar', 6, 'ffd802');

        /* Generic initialisation */
        $this->init_library();
    }

    /* Specific tool methods */

    /**
     * Return values from given properties.
     * @param string $properties
     * @return void
     */
    public function get_valuesFromProperties($properties) {
        $values = data_decode_properties($properties);
        foreach ($values as $name => $value) {
            if (isset ($this->_libItems[$name])) {
                $this->_libItems[$name]->value = $value;
            }
        }
    }

    /**
     * Return colors from properties.
     * @param string $properties
     * @return void
     */
    public function get_colorsFromProperties($properties) {
        $colors = data_decode_properties ($properties);
        foreach ($colors as $name => $value) {
            if (isset ($this->_libItems[$name])) {
                $this->_libItems[$name]->value = $value;
            }
        }
    }

    /**
     * Return values as properties.
     * @return string
     */
    public function get_valuesAsProperties() {
        return data_encode_properties(array(
            'displaymode'   => $this->_libItems['displaymode']->value,
            'displayday'    => $this->_libItems['displayday']->value,
            'displayfrom'   => $this->_libItems['displayfrom']->value,
            'displayto'     => $this->_libItems['displayto']->value,
            'displaycount'  => $this->_libItems['displaycount']->value,
        ));
    }

    /**
     * Return colors as properties.
     * @return string
     */
    public function get_colorsAsProperties() {
        return data_encode_properties(array(
            'coloralternate0' => $this->_libItems['coloralternate0']->value,
            'coloralternate1' => $this->_libItems['coloralternate1']->value,
        ));
    }

    /*
     * Build and return object configuration.
     * @param integer $objectid
     * @return array
     */
    public function build_config($objectid) {
        /* build default config */
        $config = array(
            'maintotalwhere'    => 'statid='.$objectid,
            'mainbydaywhere'    => 'statid='.$objectid,
            'mainbydaydate'     => 0,
            'mainbymonthwhere'  => 'statid='.$objectid,
            'mainbymonthdate'   => 0,
            'mainbyyearwhere'   => 'statid='.$objectid,
            'mainbyyeardate'    => 0,
            'detailwhere'       => 'statid='.$objectid,
            'detaillimit'       => $this->vars['displaycount'],
            'detaildesc'        => ''
        );

        /* main tab statistics : by day */
        $d = mktime(0, 0, 0, date('m'), date('d')-$this->_libParent->get_displayItems('day'), date('Y'));
        $config['mainbydaywhere'] .= ' and statdate >='. $d;

        /* main tab statistics : by month */
        $d = mktime(0, 0, 0, date('m')-$this->_libParent->get_displayItems('month'), 1, date('Y'));
        $config['mainbymonthwhere'] .= ' and statdate >='. $d;

        /* main tab statistics : by day */
        $d = mktime(0, 0, 0, 1, 1, date('Y')-$this->_libParent->get_displayItems('year'));
        $config['mainbyyearwhere'] .= ' and statdate >='. $d;

        /* update config case of options */
        switch ($this->vars['displaymode']) {
            case 0:
                /* mode == 0 | today's stats */
                $config['detailwhere'] .= ' and statdate>='.date_getTodayValue();
                $config['detaildesc'] = $this->get_translation('todaysrecords');
                break;
            case 1:
                /* mode == 1 | yesterday's stats */
                $config['detailwhere'] .= ' and statdate>='.date_getYesterdayValue().' and statdate<'.date_getTodayValue();
                $config['detaildesc'] = $this->get_translation('yesterdaysrecords');
                break;
            case 2:
                /* mode == 2 | this week's stats */
                $d = date_getThisWeekValue();
                $config['detailwhere'] .= ' and statdate>='.$d;
                $config['detaildesc'] = $this->get_translation('fromxtoyrecords', array(date_displayDate($d), date_displayDate($d+6*24*60*60)));
                break;
            case 3:
                /* mode == 3 | last week's stats */
                $d = date_getLastWeekValue();
                $config['detailwhere'] .= ' and statdate>='.$d.' and statdate<'.date_getThisWeekValue();
                $config['detaildesc'] = $this->get_translation('fromxtoyrecords', array(date_displayDate($d), date_displayDate($d+6*24*60*60)));
                break;
            case 4:
                /* mode == 4 | this year's stats */
                $d = date_getThisYearValue();
                $d2 = date_getNextYearValue()-1;
                $config['detailwhere'] .= ' and statdate>='.$d;
                $config['detaildesc'] = $this->get_translation('fromxtoyrecords', array(date_displayDate($d), date_displayDate($d2)));
                break;
            case 5:
                /* mode == 5 | last year's stats */
                $d = date_getlastYearValue();
                $d2 = date_getThisYearValue()-1;
                $config['detailwhere'] .= ' and statdate>='.$d.' and statdate<'.$d2;
                $config['detaildesc'] = $this->get_translation('fromxtoyrecords', array(date_displayDate($d), date_displayDate($d2)));
                break;
            case 6:
                /* mode == 6 | specific day's stats */
                $d = $this->vars['displayday'];
                $sd = mktime(0, 0, 0, date('m', $d), date('d', $d), date('Y', $d));
                $ed = mktime(23, 59, 59, date('m', $d), date('d', $d), date('Y', $d));
                $config['detailwhere'] .= ' and statdate>='.$sd;
                $config['detailwhere'] .= ' and statdate<'.$ed;
                $config['detaildesc'] = $this->get_translation('dayxrecords', array(date_displayDate($this->vars['displayday'])));
                break;
            case 7:
                /* mode == 7 | day range's stats */
                $d = $this->vars['displayfrom'];
                $sd = mktime(0, 0, 0, date('m', $d), date('d', $d), date('Y', $d));
                $d = $this->vars['displayto'];
                $ed = mktime(23, 59, 59, date('m', $d), date('d', $d), date('Y', $d));
                $config['detailwhere'] .= ' and statdate>='.$sd;
                $config['detailwhere'] .= ' and statdate<'.$ed;
                $config['detaildesc'] = $this->get_translation('fromxtoyrecords', array(date_displayDate($this->vars['displayfrom']), date_displayDate($this->vars['displayto'])));
                break;
            case 9:
                /* mode == 9 | this month's stats */
                $d = date_getThisMonthValue();
                $d2 = date_getNextMonthValue()-1;
                $config['detailwhere'] .= ' and statdate>='.$d;
                $config['detaildesc'] = $this->get_translation('fromxtoyrecords', array(date_displayDate($d), date_displayDate($d2)));
                break;
            case 10:
                /* mode == 10 | last month's stats */
                $d = date_getLastMonthValue();
                $d2 = date_getThisMonthValue()-1;
                $config['detailwhere'] .= ' and statdate>='.$d.' and statdate<'.$d2;
                $config['detaildesc'] = $this->get_translation('fromxtoyrecords', array(date_displayDate($d), date_displayDate($d2)));
                break;
        }
        return $config;
    }
}
?>
