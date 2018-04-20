<?php
/**
 * @brief AdminItemListViewer Input
 * <br /> Display customisable admin list of objects.
 * @details Plugin / Input Engine
 * @file plugin/input/AdminItemListViewer/AdminItemListViewer.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Sep 2008
 * @date Modification: Apr 2018
 * @copyright 2008 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * AdminItemListViewer Input class.
 * @author CaMykS Team <camyks.contact@gmail.com>
 */
final class AdminItemListViewer extends Input {
    /**
     * var boolean $valide
     * @brief Indicate if given parameters are valid.
     */
    private $valide = true;

    /**
     * @var array $selectionValues
     * @brief Store current selection values.
     */
    protected $selectionValues = array();

    /**
     * var array $selectionValues
     * @brief Store current selection values.
     */
    protected $sortValues = array('column'=>'id', 'way'=>'');

    /**
     * var array $preRenders
     * @brief Store pre rendered columns.
     */
    protected $preRenders = array();

    /**
     * var array $icons
     * @brief Cache of button icon urls.
     */
    protected $icons = array();

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('AdminItemListViewer', $path_type);

        /* set plugin version */
        $this->version = '1.0';

        /* set plugin package */
        $this->plugin_package = 'Default';

        /* set plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';
    }

    /* overwrite Input methods */

    /**
     * Initialise input.
     * @param array $params
     * @return void
     */
    public function initialise($params=array()) {

        /* check params */
        if (($this->valide = $this->check_params())) {
            /* build all params */
            $this->build_panelsData();
            /* build item pre-rendering */
            $this->build_listData();
        }
        /* generic Input initialisation */
        parent::initialise();
    }

    /**
     * Display input.
     * @param string $panel
     * @return void
     */
    public function display ($panel='list') {
        /* update layout */
        if ($this->valide)
            $this->set_selectedLayout('input_'.$panel.'.html.inc');
        else
            $this->set_selectedLayout('input_.html.inc');

        /* generic input display */
        parent::display();
    }

    /* specific tool methods */

    /**
     * Set all params.
     * @param array $params
     * @return void
     */
    public function set_params($params=array()) {
        $this->params = $params;
    }

    /**
     * Add a head param.
     * @param string $type
     * @param string $name
     * @param mixed $value
     * @return void
     */
    public function add_param($type, $name, $value) {
        if (!isset($type))
            $this->params[$type] = array();
        $this->params[$type][$name] = $value;
    }

    /**
     * Check paramaters.
     * @return void
     */
    private function check_params() {
        global $camyks;

        /* default params */
        $defaultParams = array(
            'name'          => 'genViewer',
            'useSession'    => false,
            'object'        => null,
            'language'      => false,
            'itemsbypage'   => $camyks->get_confValue('admin_itemsbypage', 10),
            'theme'         => &$camyks->theme,
            'baseurl'       => '',
            'sort'          => array('allowed'=>false),
            'headselectors' => array(),
            'headcolumns'   => 2,
            'headhiddens'   => array(),
            'extraparams'   => array(),
            'listcolumns'   => array(),
            'listlinks'     => array()
        );

        /* merge default params and parent's params */
        $this->params = array_merge($defaultParams, $this->params);

        /* check object */
        if (!isset($this->params['object']))
            return false;
        if (!isset($this->params['object']->object_type) or  $this->params['object']->object_type!= 'ModuleLibrary')
            return false;

        /* check basurl param */
        if (!isset($this->params['baseurl']))
            if (isset($this->params['object']) and isset($this->params['object']->_libParent))
                $this->params['baseurl'] = $camyks->get_adminLink($this->params['object']->_libParent->name);
            else
                $this->params['baseurl'] = $camyks->get_adminLink();

        /* check sorting values */
        if (!isset($this->params['sort']['allowed']))
            $this->params['sort']['allowed'] = false;
        if ($this->params['sort']['allowed'] === true and !isset($this->params['sort']['default']))
            $this->params['sort']['default'] = 'id';
        if ($this->params['sort']['allowed'] === true and !isset($this->params['sort']['defaultway']))
            $this->params['sort']['defaultway'] = '';

        return true;
    }

    /**
     * Return header selector value.
     * @param string $name
     * @param array $params
     * @return mixed
     */
    private function get_selectorValue($name, $params) {
        if (!isset($params['itemtype']))
            return null;

        switch ($params['itemtype']) {
            case 'page' :
                return (int)$_REQUEST[$this->params['name'].'_form'.$name]-1;
            default :
                if (!isset($params['datatype']))
                    $params['datatype'] = 'string';
                switch ($params['datatype']) {
                    case 'int':
                    case 'integer':
                        return (int)$_REQUEST[$this->params['name'].'_form'.$name];
                    case 'string':
                        return $_REQUEST[$this->params['name'].'_form'.$name];
                }
        }
    }

    /**
     * Return header selector default value.
     * @param string $name
     * @param array $params
     * @return mixed
     */
    private function get_selectorDefaultValue($name, $params) {
        if (!isset($params['itemtype']))
            return null;

        if (isset($params['default']))
            return $params['default'];

        switch($params['itemtype']) {
            case 'page' :
                return 0;
            default :
                if (!isset($params['datatype']))
                    $params['datatype'] = 'string';
                switch ($params['datatype']) {
                    case 'int':
                    case 'integer':
                        return 0;
                    case 'string':
                        return '';
                }
        }
    }

    /**
     * Build every params needed into the display panels.
     * @return void
     */
    private function build_panelsData() {
        global $camyks;

        /* prepare default vars value */
        $search = '';
        $from = -1;
        $count = -1;

        /* add form and script */
        if (count($this->params['headselectors']) > 0 or $this->params['sort']['allowed'] === true) {
            /* build form object */
            $this->selectorForm = new HTMLForm($this->params['name'].'_form', $this->params['baseurl'], 'POST');

            /* add hiddens */
            foreach($this->params['headhiddens'] as $hiddenName => $hiddenValue)
                $this->selectorForm->add_hidden($hiddenName, $hiddenValue);

            /* add javascript */
            $this->add_JSFile('AdminItemListViewer.js');
            $this->add_JSScript('var '.$this->params['name'].' = new AdminItemListViewer("'.$this->params['name'].'");');
            $this->add_JSLoadScript($this->params['name'].'.initialise();');
        } else {
            $this->selectorForm = false;
        }

        /* check sorting values */
        if ($this->params['sort']['allowed'] === true) {
            /* get sort column value */
            if (isset($_REQUEST[$this->params['name'].'_sortcolumn'])) {
                $value = $_REQUEST[$this->params['name'].'_sortcolumn'];
                if ($this->params['useSession'] == true)
                    $camyks->set_sessionValue($this->params['name'].'_sortcolumn', $value);
            } elseif ($this->params['useSession'] == true)
                $value = $camyks->get_sessionValue($this->params['name'].'_sortcolumn', $this->params['sort']['default']);
            else
                $value = $this->params['sort']['default'];
            $this->sortValues['column'] = $value;
            $this->selectorForm->add_hidden($this->params['name'].'_sortcolumn', $value);

            /* get sort column way */
            if (isset($_REQUEST[$this->params['name'].'_sortway'])) {
                $value = $_REQUEST[$this->params['name'].'_sortway'];
                if ($this->params['useSession'] == true)
                    $camyks->set_sessionValue($this->params['name'].'_sortway', $value);
            } elseif ($this->params['useSession'] == true)
                $value = $camyks->get_sessionValue($this->params['name'].'_sortway', $this->params['sort']['defaultway']);
            else
                $value = $this->params['sort']['defaultway'];
            $this->sortValues['way'] = $value;
            $this->selectorForm->add_hidden($this->params['name'].'_sortway', $value);
        } else {
            $this->sortValues['column'] = $this->params['sort']['default'];
            $this->sortValues['way'] = $this->params['sort']['defaultway'];
        }

        /* check hiddens params */
        foreach ($this->params['headhiddens'] as $name => $value)
            $this->selectionValues[$name] = $value;

        /* check head selectors */
        if (count($this->params['headselectors']) > 0) {
            /* get header or default values */
            $refresh = false;
            foreach ($this->params['headselectors'] as $name => $selector) {
                /* get value */
                if (isset($_REQUEST[$this->params['name'].'_form'.$name])) {
                    $value = $this->get_selectorValue($name, $selector);
                    if ($this->params['useSession'] == true)
                        $camyks->set_sessionValue($this->params['name'].'_form'.$name, $value);
                    $refresh = true;
                } elseif ($this->params['useSession'] == true)
                    $value = $camyks->get_sessionValue($this->params['name'].'_form'.$name, $this->get_selectorDefaultValue($name, $selector));
                else
                    $value = $this->get_selectorDefaultValue($name, $selector);
                /* set value */
                $this->selectionValues[$name] = $value;
            }

            /* force refresh to avoid annoying message when using back button */
            if ($refresh == true and $this->params['useSession'] == true) {
                $params = $_GET;
                if (isset($this->params['headhiddens']['openTab']))
                    $params['openTab'] = $this->params['headhiddens']['openTab'];
                $params = array_merge($params, $this->params['extraparams']);
                if ($camyks->mode == CAMYKS_MODE_REQUEST) {
                    header('Location:'.$camyks->get_requestJSLink($params));
                } else {
                    $module = $params['module'];
                    unset($params['module']);
                    header('Location:'.$camyks->get_adminJSLink($module, $params));
                }
            }

            /* initialise list values */
            $search = $this->params['object']->build_SQLCondition($this->selectionValues);
            $objcount = $this->params['object']->get_objectCount($search, $this->params['language']);

            /* check for specific pager */
            if (isset($this->params['headselectors']['page']) and $this->params['headselectors']['page']['itemtype'] == 'page') {

                $this->params['headselectors']['page']['maxpages'] = ceil($objcount/$this->params['itemsbypage']);

                /* update selection value */
                $this->selectionValues['page'] = min(max(0, $this->selectionValues['page']), $this->params['headselectors']['page']['maxpages']-1);
                $from = $this->selectionValues['page']*$this->params['itemsbypage'];
                $count = $this->params['itemsbypage'];
            }
        } else {
            /* initialise list values */
            $search = $this->params['object']->build_SQLCondition($this->selectionValues);
            $objcount = $this->params['object']->get_objectCount($search, $this->params['language']);
        }

        /* save object count */
        $this->objectCount = $objcount;

        /* load object list */
        $this->objectList = $this->params['object']->get_objectList($this->params['language'], $search, $from, $count, $this->sortValues['column'], $this->sortValues['way']);
    }

    /**
     * Build list data.
     * @return void
     */
    private function build_listData() {
        global $global_theme_picts_items;

        $this->preRenders = array();
        if (count($this->objectList) === 0)
            return;

        foreach($this->params['listcolumns'] as $name => $column) {
            /* check condition */
            if (isset($column['condition'])) {
                if ($column['condition']=='' or !method_exists($this->params['object'], $column['condition'])) {
                    unset($this->params['listcolumns'][$name]['condition']);
                }
            }

            /* build columns pre-rendering */
            switch ($column['columntype']) {
                case 'button':
                    /* columntype == button */
                    $render = '<a href="'.$column['url_value'].'"'.(isset($column['url_target'])?' target="'.$column['url_target'].'"':'').'>';

                    if (!isset($column['url_title']))
                        $column['url_title'] = '';
                    if (isset($column['id']) and $column['id'] != '') {
                        $idAttr = ' id="'.$column['id'].'"';
                    } else {
                        $idAttr = '';
                    }

                    if (in_array($column['icon'], $global_theme_picts_items['12']['items'])) {
                        $render .= '<img src="'.$this->get_icon($column['icon'], 'std').'"';
                        $render .= $idAttr;
                        $render .= ' alt="'.$column['url_title'].'" title="'.$column['url_title'].'" border="0"';
                        $render .= ' onmouseover="this.src=\''.$this->get_icon($column['icon'], 'ovr').'\';"';
                        $render .= ' onmouseout="this.src=\''.$this->get_icon($column['icon'], 'std').'\';" />';
                    } else {
                        $render .= '<img src="'.$column['icon'].'"';
                        $render .= $idAttr;
                        $render .= ' alt="'.$column['url_title'].'" title="'.$column['url_title'].'" border="0"';
                        if (isset($column['icon_over'])) {
                            $render .= ' onmouseover="this.src=\''.$link['icon_over'].'\';"';
                            $render .= ' onmouseout="this.src=\''.$link['icon'].'\';"';
                        }
                        $render .= ' />';
                    }
                    $render .= '</a>';
                    $this->preRenders[$name] = $render;
                    break;
                case 'checkbox':
                    /* columntype == checkbox */
                    $render = '<input type="checkbox" id="'.$name.'%2$s" name="'.$name.'%2$s" value="%1$s" onchange="'.$this->params['name'].'.update_singleCheckbox(\''.$name.'\');"/>';
                    $this->preRenders[$name] = $render;
                    break;
                case 'boolean':
                    /* columntype == boolean */
                    switch($column['mode']) {
                        case 'text': break;
                        case 'pict':
                            $this->preRenders[$name] = '<img src="%s" alt="" border="0" />';
                            break;
                        case 'checkbox':
                        default:
                            $this->preRenders[$name] = '<input type="checkbox" disabled="disabled" %s />';
                            break;
                    }
                    break;
                case 'text':
                    /* columntype == text */
                case 'list':
                    /* columntype == list */
                case 'country':
                    /* columntype == country */
                case 'date':
                    /* columntype == date */
                case 'specialtext':
                    /* columntype == specialtext */
                    break;
                case 'method':
                    /* columntype == method */
                    if (!isset($column['method']) or $column['method'] == '' or !method_exists($this->params['object'], $column['method']))
                        $this->params['listcolumns'][$name]['columntype'] = 'empty';
                    break;
                case 'empty':
                    /* columntype == empty */
                    break;
            }
        }
    }

    /**
     * Return object item display.
     * @param object $object
     * @param string $name
     * @param array $column
     * @param integer $line
     * @return string
     */
    protected function get_itemDisplay($object, $name, $column, $line) {
        global $camyks;

        /* check condition */
        if (isset($column['condition']) and call_user_func(array(&$object, $column['condition'])) === false)
            return '';

        /* return item display */
        switch ($column['columntype']) {
            case 'button':
                /* columntype == button */
                if (!isset($column['vars']))
                    return vsprintf($this->preRenders[$name], $object->id);
                else {
                    $vars = array();
                    foreach ($column['vars'] as $index => $v) {
                        if ($v == 'id')
                            $vars[$index] = $object->id;
                        else
                            $vars[$index] = isset($object->vars[$v]) ? $object->vars[$v] : '';
                    }
                    return vsprintf($this->preRenders[$name], $vars);
                }
                break;
            case 'checkbox' :
                /* columntype == checkbox */
                return vsprintf($this->preRenders[$name], array($object->id, $line));
            case 'text':
                /* columntype == text */
                if (isset($column['maxlength']) and $column['maxlength']>0)
                    return string_getShortenedSentence($object->vars[$name], $column['maxlength']);
                return $object->vars[$name];
            case 'list':
                /* columntype == list */
                if (!isset($column['values'][$object->vars[$name]]))
                    return '';
                if (isset($column['maxlength']) and $column['maxlength']>0)
                    return string_getShortenedSentence($column['values'][$object->vars[$name]], $column['maxlength']);
                return $column['values'][$object->vars[$name]];
            case 'country':
                /* columntype == country */
                return language_getIcon($object->vars[$name]);
            case 'date':
                /* columntype == date */
                switch ($column['mode']) {
                    case 'long':
                        return date_displayLongDate($object->vars[$name]);
                    case 'longwithhour':
                        return date_displayLongDateHour($object->vars[$name]);
                    case 'longwithday':
                        return date_displayLongDayDate($object->vars[$name]);
                    case 'longwithdayandhour':
                        return date_displayLongDayDateHour($object->vars[$name]);
                    case 'short':
                        return date_displayShortDate($object->vars[$name]);
                    case 'shortwithhour':
                        return date_displayShortDateHour($object->vars[$name]);
                    case 'shortwithday':
                        return date_displayShortDayDate($object->vars[$name]);
                    case 'shortwithdayandhour':
                        return date_displayShortDayDateHour($object->vars[$name]);
                    case 'numeric':
                        return date_displayNumericDate($object->vars[$name]);
                    case 'numericwithhour':
                    default:
                        return date_displayNumericDateHour($object->vars[$name]);
                }
            case 'boolean':
                /* columntype == boolean */
                switch ($column['mode']) {
                    case 'text':
                        return $camyks->get_translation($object->vars[$name]?'yes':'no');
                    case 'pict':
                        return vsprintf($this->preRenders[$name], $this->get_icon($object->vars[$name] ? 'valid' : 'empty'));
                    case 'checkbox':
                    default:
                        return vsprintf($this->preRenders[$name], $object->vars[$name] ? ' checked="checked"' : '');
                }
            case 'specialtext' :
                /* columntype == specialtext */
                if (!isset($column['text']) or !isset($column['vars']))
                    return '';
                $vars = array();
                foreach ($column['vars'] as $index => $v) {
                    if ($v == 'id')
                        $vars[$index] = $object->id;
                    else
                        $vars[$index] = isset($object->vars[$v]) ? $object->vars[$v] : '';
                }
                if (isset($column['maxlength']) and $column['maxlength']>0)
                    return string_getShortenedSentence(vsprintf($column['text'], $vars), $column['maxlength']);
                return vsprintf($column['text'], $vars);
            case 'method':
                /* columntype == method */
                $v = call_user_func(array(&$object, $column['method']));
                if (isset($column['maxlength']) and $column['maxlength']>0)
                    return string_getShortenedSentence($v, $column['maxlength']);
                return $v;
        }
        /* default value */
        return '';
    }

    /**
     * Return generic icon URL.
     * @param string $icon
     * @param string $mode
     * @return string
     */
    protected function get_icon($icon, $mode='std') {
        if (!isset($this->icon[$icon.'_'.$mode]))
            $this->icons[$icon.'_'.$mode] = $this->params['theme']->get_pictURL($icon, 12, $mode);
        return $this->icons[$icon.'_'.$mode];
    }

    /**
     * Check if given column can be use as sort.
     * @param string $column
     * @return boolean
     */
    protected function is_columnSortable($column='') {
        return (in_array($column, $this->params['object']->_libItemTypes['db']) or in_array($column, $this->params['object']->_libItemTypes['dbl']));
    }

    /**
     * Calculate and return list link button position.
     * @param array $link
     * @return array
     */
    protected function get_listLinkColspans($link=array()) {
        $cols = count($this->params['listcolumns']);
        $spans = array('firsts'=>0, 'title'=>$cols-1, 'lasts'=>0);

        if (!isset($link['buttoncolumn']) and !isset($link['titlecolumn']))
            return $spans;

        $title = isset($link['titlecolumn']) ? $this->get_columnPosition($link['titlecolumn']) : 1;
        $button = isset($link['buttoncolumn']) ? $this->get_columnPosition($link['buttoncolumn']) : $cols;

        if ($title >= $button)
            return $spans;

        $spans['firsts'] = $title-1;
        $spans['title'] = $button-$title;
        $spans['lasts'] = $cols-$button;

        return $spans;
    }

    /**
     * Calculate and return column position.
     * @param mixed $column
     * @return integer
     */
    private function get_columnPosition($column) {
        /* check column type */
        if (is_integer($column))
            return $column;
        $cnt = 0;
        foreach($this->params['listcolumns'] as $n => $value) {
            $cnt++;
            if ($n == $column)
                break;
        }
        return $cnt;
    }
}
?>