<?php
/**
 * @brief Admin_SecurityTools Module URL Filter rule library.
 * @details Plugin / Module Library
 * @file plugin/module/Admin_SecurityTools/lib/Admin_SecurityURLFilterRule.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jan 2019
 * @date Modification: Jan 2019
 * @copyright 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_SecurityURLFilterRule ModuleLibrary class.
 */
final class Admin_SecurityURLFilterRule extends ModuleLibrary {
    /**
     * Class Constructor
     * @param integer $id
     * @param Module $parent
     * @return void
     */
    public function __construct($id, &$parent) {
        parent::__construct($id, $parent);
        /* library items */
        $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('pattern', 'db', 'text', 'varchar', 128, '');
        $this->add_newItem('comment', 'db', 'text', 'varchar', 255, '');

        /* generic library initialisation */
        parent::init_library();
    }

    /* Specific properties definition method */

    /**
     * Return status list.
     * @return array
     */
    public function get_statusList() {
        return array(
            0 => $this->get_translation('urlfilterrulestatus_disabled'),
            1 => $this->get_translation('urlfilterrulestatus_enabled'),
        );
    }

    /**
     * Return multi object status list.
     * @param array $params
     * @return array
     */
    public function get_multiStatusList($params=array()) {

        /* check params */
        $defaultParams = array('addAll'=>false);
        $params = array_merge($defaultParams, $params);

        /* build list */
        $list = array();
        if ($params['addAll'])
            $list['-1'] = $this->get_translation('urlfilterrules_all');
        $list['0'] = $this->get_translation('urlfilterrulesstatus_disabled');
        $list['1'] = $this->get_translation('urlfilterrulesstatus_enabled');

        /* send list */
        return $list;
    }

    /* specific tool methods */

    /**
     * Check IP Filter security.
     * @return boolean result
     */
    public function check_security() {
        global $camyks;

        /* Load all rules */
        $rules = $this->get_list(array('status' => 1));

        /* Load current URL */
        $url = $_SERVER['REQUEST_URI'];

        /* Check if IP match a rule */
        foreach ($rules as $rule) {
            if (preg_match('/'.$rule->vars['pattern'].'/i', $url)) {
                $camyks->log('Security', 'Connection refused', 'Black listed URL ('.$rule->vars['comment'].': "'. $url .'")');
                $error = array(
                    'title'         => 'Security: Access denied',
                    'description'   => '',
                    'content1'      => 'This website has an active URL Filter.',
                    'content2'      => 'Your request matches one of website filter rules.',
                    'content3'      => 'If you think it is an error, please contact the website administrator.',
                );
                header('HTTP/1.1 403 Forbidden');
                $camyks->throwFatalError($error);
                return;
            }
        }
    }

    /**
     * Return object list.
     * @param array $params
     * @return array
     */
    public function get_list($params=array()) {
        global $camyks;

        /* default params list */
        $dParams = array('language'=>$camyks->current_language, 'limit'=>-1, 'count'=>-1, 'order'=>'updateDate', 'orderway'=>'desc');

        /* merge params */
        $params = array_merge($this->get_defaultParams(), $dParams, $params);

        /* build where statement */
        $w = $this->build_whereStatement($params);

        /* return list */
        return $this->get_objectList($params['language'], $w, $params['limit'], $params['count'], $params['order'], $params['orderway']);
    }

    /**
     * Return object count.
     * @params array $params
     * @return array
     */
    public function count($params=array()) {
        global $camyks;
        $params = array_merge($this->get_defaultParams(), $params);
        $where = $this->build_whereStatement($params);
        return $this->get_objectCount($where);
    }

    /**
     * return default parameters
     * @param array
     * @access private
     */
    private function get_defaultParams() {
        return array(
            'status'        => -1,
       );
    }

    /**
     * Build where statement from params.
     * @param array $params
     * @return string
     */
    private function build_whereStatement($params=array()) {
        $w = array();

        /* check status */
        if ($params['status'] != -1)
            $w[] = 'status = '.$params['status'];

        /* return result */
        return implode(' and ', $w);
    }
}
?>
