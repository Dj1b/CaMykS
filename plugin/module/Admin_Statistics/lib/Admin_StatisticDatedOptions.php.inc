<?php
/**
 * @brief Admin_Statistics module, options for dated type stats library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: May 2007
 * @date Modification: Jul 2025
 * @copyright 2007 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_StatisticDatedOptions class.
 */
final class Admin_StatisticDatedOptions extends ModuleLibrary {

    /**
     * var integer $optionSettingsDisplay
     * @brief Define settings to display in option tab.
     */
    public $optionSettingsDisplay = 0;

    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* Define items */
        $this->add_newItem('coloralternate0', 'temp', 'text', 'varchar', 6, '5b8dcd');
        $this->add_newItem('coloralternate1', 'temp', 'text', 'varchar', 6, 'ffd802');

        /* generic initialisation */
        $this->init_library();
    }

    /* Mark: Specific tool methods */

    /**
     * Return values from given properties.
     * @param string $properties
     * @return void
     */
    public function get_valuesFromProperties($properties) {
        return;
    }

    /**
     * Return colors from given properties.
     * @param string $properties
     * @return void
     */
    public function get_colorsFromProperties($properties) {
        $colors = data_decode_properties($properties);
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
    public function get_valuesAsProperties () {
        return '';
    }

    /**
     * Return colors as properties.
     * @return string
     */
    function get_colorsAsProperties () {
        return data_encode_properties(array(
            'coloralternate0'=>$this->_libItems['coloralternate0']->value,
            'coloralternate1'=>$this->_libItems['coloralternate1']->value,
        ));
    }

    /**
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
            'mainbyyeardate'    => 0
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
        return $config;
    }
}
?>
