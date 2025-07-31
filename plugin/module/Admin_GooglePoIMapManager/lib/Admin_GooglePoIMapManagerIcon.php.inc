<?php
/**
 * @brief Admin_GooglePoIMapManager module, icon library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Mar 2010
 * @date Modification: Jul 2025
 * @copyright 2010 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GooglePoIMapManagerIcon class.
 */
final class Admin_GooglePoIMapManagerIcon extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* Main attributes */
        $this->add_newItem('name', 'db', 'text', 'varchar', 32, '');

        $this->add_newItem('anchorLocX', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('anchorLocY', 'db', 'int', 'tinyint unsigned', '', 0);

        $this->add_newItem('mainImg', 'file', 'icons', '', '', '');
        $this->add_newItem('rollImg', 'file', 'icons', '', '', '');
        $this->add_newItem('slctImg', 'file', 'icons', '', '', '');
        $this->add_newItem('shdwImg', 'file', 'icons', '', '', '');

        /* Generic initialisation */
        $this->init_library();
    }

    /* Mark: Specific tool methods */

    /**
     * Return name list.
     * @param array $params
     * @return array
     */
    public function get_objectNameList($params) {
        /* Define default params */
        $dParams = array('none'=>false);

        /* Merge params */
        $params = array_merge($dParams, $params);

        /* Check params */
        if ($params['none'] == true)
            $list = array(0 => $this->get_translation('none'));
        else
            $list = array();

        /* Return list */
        return $list + $this->get_nameList();
    }

    /**
     * Return object list.
     * @param array $params
     * @return array
     */
    public function get_list($params) {
        /* Define default params */
        $dParams = array('ids'=>'-1', '_sized'=>false);

        /* Merge params */
        $params = array_merge($dParams, $params);

        /* Initialise where statement */
        $w = array();

        /* Check params */
        if (is_array($params['ids'])) {
            if (count($params['ids']) == 0)
                return array();
            if (count($params['ids']) == 1)
                $w[] = 'id = '.$params['ids'][0];
            else
                $w[] = 'id in ('.implode(',', $params['ids']).')';
        }
        $w = implode(' and ', $w);

        /* Load list */
        $list = $this->get_objectList(false, $w);

        foreach ($list as $id => &$icon) {
            /* Remove icons which doesn't have a main image */
            if ($icon->vars['mainImg'] == '') {
                unset($list[$id]);
                continue;
            }

            /* Check for required sized */
            if ($params['_sized'] == true) {
                $f = new FSFile($icon->vars['mainImg']);
                $icon->vars['mainWidth'] = $f->moreinfos['width'];
                $icon->vars['mainHeight'] = $f->moreinfos['height'];
                $f = new FSFile($icon->vars['shdwImg']);
                if ($f->exists) {
                    $icon->vars['shdwWidth'] = $f->moreinfos['width'];
                    $icon->vars['shdwHeight'] = $f->moreinfos['height'];
                } else {
                    $icon->vars['shdwWidth'] = 0;
                    $icon->vars['shdwHeight'] = 0;
                }
            }
        }
        return $list;
    }
}
?>
