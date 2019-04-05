<?php
/**
 * @brief HTML form object library
 * @details Engine / Object Library
 * @file engine/lib/object/HTMLForm.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.1.5
 * @date Creation: Jun 2005
 * @date Modification: Apr 2019
 * @copyright 2005 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @todo Add methods params details in method header
 */

/*
 * @def HTMLFORM_METHOD_POST
 */
define('HTMLFORM_METHOD_POST',  0);

/*
 * @def HTMLFORM_METHOD_GET
 */
define('HTMLFORM_METHOD_GET',   1);

/**
 * HTMLForm class.
 * @author CaMykS Team <camyks.contact@gmail.com>
 */
class HTMLForm {
    /**
     * @var string $name
     * @brief Form name.
     */
    public $name;

    /**
     * @var string $action
     * @brief Form action.
     */
    public $action;

    /**
     * @var string $method
     * @brief Form data sending method.
     */
    public $method;

    /**
     * @var string $onSubmit
     * @brief Form on submit action script.
     */
    public $onSubmit;

    /**
     * @var string $target
     * @brief Form target window/frame.
     */
    public $target;

    /**
     * @var array $hiddens
     * @brief Form hidden value list.
     */
    public $hiddens = array();

    /**
     * @var boolean $allowFiles
     * @brief Form on submit action script.
     */
    public $allowFiles = false;

    /**
     * @var integer $tabIndex
     * @brief Form current tab index.
     */
    public $tabIndex = -1;

    /**
     * @var ModuleLibrary $object
     * @brief ModuleLibrary object to auto-fill values.
     */
    protected $object = null;

    /**
     * @var Module $parent
     * @brief Parent module.
     */
    protected $parent = null;

    /**
     * @var integer $inputsCount
     * @brief Form inputs counter.
     */
    protected $inputsCount = 0;

    /**
     * @var integer $inputsLimit
     * @brief Form input limit.
     */
    protected $inputsLimit;

    /**
     * @var array $inputsLimitUniques
     * @brief Form stored unique input names.
     */
    protected $inputsLimitUniques = array();

    /**
     * @var boolean $inputsLimitReached
     * @brief Form input limit reached.
     */
    protected $inputsLimitReached = false;

    /**
     * var array $inputDefaultParams
     * @brief List all default params for inputs
     */
    protected $inputDefaultParams = array(
        'id'            => '',
        'name'          => '',
        'language'      => '',
        'default'       => '',
        'class'         => 'inputs',
        'style'         => '',
        'onchange'      => '',
        'onfocus'       => '',
        'onblur'        => '',
        'oninput'       => '',
        'onkeydown'     => '',
        'onkeyup'       => '',
        'disabled'      => '',
        'data'          => array(),
        'tabIndex'      => -1,
        'placeholder'   => '',
        'maxlength'     => 0,
        'minlength'     => 0,
        'pattern'       => '',
        'readonly'      => '',
        'list'          => '',
        'autocomplete'  => '',
        'allowMultiple' => false,

        'size'          => 0,
    );

    /**
     * Class constructor.
     * @param string $name
     * @param string $action
     * @param mixed $method
     * @param string $onSubmit
     * @param string $target
     * @return void
     */
    public function __construct($name='', $action='./', $method=null, $onSubmit='', $target='') {
        $this->name = $name;
        $this->action = $action;
        $this->onSubmit = $onSubmit;
        $this->target = $target;

        /* set up inputs limit */
        $this->inputsLimit = ini_get('max_input_vars');

        /* check for method type */
        switch ($method) {
            case HTMLFORM_METHOD_GET :
            case 'GET' :
            case 'get' :
                $this->method = 'get';
                break;
            case HTMLFORM_METHOD_POST :
            case 'POST' :
            case 'post' :
            default:
                $this->method = 'post';
                break;
        }
    }

    /* methods */

    /**
     * Allow files for this form.
     * @param boolean $allow
     * @param integer $size the allowed file size in bytes
     * @return void
     */
    public function allow_files($allow=true, $size=null) {
        $this->allowFiles = $allow;
        if ($size > 0) {
            $this->add_hidden('MAX_FILE_SIZE', $size);
        }
    }

    /**
     * Update object value.
     * @param ModuleLibrary $object
     * @return void
     */
    public function set_object($object=null) {
        $this->object = &$object;
    }

    /**
     * Update parent value.
     * @param Module $parent
     * @return void
     */
    public function set_parent($parent=null) {
        $this->parent = &$parent;
    }

    /**
     * Return form header as text.
     * @return string
     */
    public function display_header() {
        $html = '<form';

        if ($this->name != '') {
            $html .= ' name="'.$this->name.'"';
            $html .= ' id="'.$this->name.'"';
        }

        $html .= ' action="'.$this->action.'"';

        if ($this->onSubmit != '')
            $html .= ' onSubmit="'.$this->onSubmit.'"';

        if ($this->allowFiles)
            $html .= ' enctype="multipart/form-data"';

        if ($this->target != '')
            $html .= ' target="'.$this->target.'"';

        $html .= ' method="'.$this->method.'"';
        $html .= '>'."\n";
        return $html;
    }

    /**
     * Return form footer as string.
     * @return string
     */
    public function display_footer() {
        return '</form>';
    }

    /**
     * Create an hidden value.
     * @param string $name the hidden value name
     * @param string $value the hidden value content
     * @param string $id the hidden value id
     * @return void
     */
    public function add_hidden($name, $value=null, $id='') {
        if ($value == null and isset($this->object) and isset($this->object->vars[$name]))
            $value = $this->object->vars[$name];
        if ($value !== null)
            $this->hiddens[] = new HTMLForm_hidden($name, $value, $id);
    }

    /**
     * Return hidden input as text.
     * @return string
     */
    public function display_hiddens () {
        $html = '';
        foreach ($this->hiddens as $hidden)
            $html .= $hidden->display()."\n";
        return $html;
    }

    /**
     * Return javascript code to set focus on given form element.
     * @param string $focus the form item to focus
     * @return string
     */
    public function set_jsFocus($focus) {
        return 'document.'.$this->name.'.'.$focus.'.focus();';
    }

    /**
     * Return complete date form display.
     * @param date $date
     * @param string $oname
     * @param array $objects
     * @param array $buttons
     * @return string
     */
    public function display_dateInput($date=TODAY, $oname='date', $objects=array('day','month','year','hours','minutes'), $buttons=array()) {
        global $camyks;
        /* build param list */
        $params = array('objects'=>null, 'buttons'=>null, 'hasEmptyFirstOption'=>false, 'dayAsSelect'=>false, 'monthAsText'=>false, 'yearAsSelect'=>false, 'yearRange'=>array('from'=>2000, 'to'=>2050));

        /* check header params */
        if (is_array($date)) {
            $params = array_merge($this->inputDefaultParams, $params, $date);
        } else {
            $params = array_merge($this->inputDefaultParams, $params);
            if (isset($oname))
                $params['name'] = $oname;
            if (isset($date))
                $params['default'] = $date;
            if (isset($objects))
                $params['objects'] = $objects;
            if (isset($buttons))
                $params['buttons'] = $buttons;
        }

        /* check object params */
        if ($params['default'] === '' and $params['hasEmptyFirstOption'] === false) {
            $n = $params['name'];
            $params['default'] = isset($this->object->vars[$n])?$this->object->vars[$n]:TODAY;
        }
        if ($params['objects'] === null)
            $params['objects'] = array('day','month','year','hours','minutes');

        /* check parent params */
        if ($params['buttons'] === null) {
            if (isset($this->parent))
                $params['buttons'] = $this->parent->get_dateInputButtons();
            elseif (isset($this->object->_libParent))
                $params['buttons'] = $this->object->_libParent->get_dateInputButtons();
        }

        /* start html rendering */
        $html = '';

        /* add day input */
        if (in_array('day', $params['objects'])) {
            $default = $params['default'] === '' ? '' : date('d', $params['default']);
            if ($params['dayAsSelect'] == true) {
                $d = array();
                for ($i=1; $i<32; $i++) $d[$i] = $i;
                $html .= $this->display_selectInput(array(
                    'name'      => $params['name'].'_day',
                    'class'     => 'vsinputs',
                    'values'    => $d,
                    'default'   => $default,
                    'tabIndex'  => $params['tabIndex'] == -1 ? -1 : $params['tabIndex'],
                    'onchange'  => $params['onchange'],
                    'onfocus'   => $params['onfocus'],
                    'onblur'    => $params['onblur']
                ));
            } else {
                $html .= $this->display_textInput(array(
                    'name'      => $params['name'].'_day',
                    'maxlength' => 2,
                    'size'      => 2,
                    'class'     => '',
                    'default'   => $default,
                    'tabIndex'  => $params['tabIndex'] == -1 ? -1 : $params['tabIndex'],
                    'onchange'  => $params['onchange'],
                    'onfocus'   => $params['onfocus'],
                    'onblur'    => $params['onblur']
                ));
            }
            $html .= ' ';
        }

        /* add month input */
        if (in_array('month', $params['objects'])) {
            if ($params['monthAsText'] == true) {
                $default = $params['default'] === '' ? 0 : date('m', $params['default']);
                $html .= $this->display_textInput(array(
                    'name'      => $params['name'].'_month',
                    'maxlength' => 2,
                    'size'      => 2,
                    'class'     => '',
                    'default'   => $default,
                    'tabIndex'  => $params['tabIndex'] == -1 ? -1 : $params['tabIndex'],
                    'onchange'  => $params['onchange'],
                    'onfocus'   => $params['onfocus'],
                    'onblur'    => $params['onblur']
                ));
            } else {
                $default = $params['default'] === '' ? 0 : (int)date('n', $params['default']);
                $m = array();
                if ($params['hasEmptyFirstOption'])
                    $m[0] = '';
                for ($i=1; $i<=12; $i++)
                    $m[$i] = ucfirst(strftime ('%B', mktime(0, 0, 0, $i, 1, 1)));
                $html .= $this->display_selectInput(array(
                    'name'      => $params['name'].'_month',
                    'values'    => $m,
                    'class'     => 'sinputs',
                    'default'   => $default,
                    'tabIndex'  => $params['tabIndex'] == -1 ? -1 : $params['tabIndex']+1,
                    'onchange'  => $params['onchange'],
                    'onfocus'   => $params['onfocus'],
                    'onblur'    => $params['onblur'],
                ));
                $html .= ' ';
            }
        }

        /* add year input */
        if (in_array('year', $params['objects'])) {
            $default = $params['default'] === '' ? '' : date('Y', $params['default']);
            if ($params['yearAsSelect'] == true and $params['yearRange']['from'] > 0 and $params['yearRange']['to'] > 0) {
                $y = array();
                for ($i=$params['yearRange']['from']; $i<=$params['yearRange']['to']; $i++)
                    $y[$i] = $i;
                $html .= $this->display_selectInput(array(
                    'name'      => $params['name'].'_year',
                    'class'     => 'sinputs',
                    'values'    => $y,
                    'default'   => $default,
                    'tabIndex'  => $params['tabIndex'] == -1 ? -1 : $params['tabIndex']+2,
                    'onchange'  => $params['onchange'],
                    'onfocus'   => $params['onfocus'],
                    'onblur'    => $params['onblur']
                ));
            } else {
                $html .= $this->display_textInput(array(
                    'name'      => $params['name'].'_year',
                    'maxlength' => 4,
                    'size'      => 4,
                    'class'     => '',
                    'default'   => $default,
                    'tabIndex'  => $params['tabIndex'] == -1 ? -1 : $params['tabIndex']+2,
                    'onchange'  => $params['onchange'],
                    'onfocus'   => $params['onfocus'],
                    'onblur'    => $params['onblur'],
                ));
                $html.= ' ';
            }
        }

        /* add hours input */
        if (in_array('hours', $params['objects'])) {
            $default = $params['default'] === '' ? '' : date('H', $params['default']);
            $html .= $this->display_textInput(array(
                'name'      => $params['name'].'_hours',
                'maxlength' => 2,
                'size'      => 2,
                'class'     => '',
                'default'   => $default,
                'tabIndex'  => $params['tabIndex'] == -1 ? -1 : $params['tabIndex']+3,
                'onchange'  => $params['onchange'],
                'onfocus'   => $params['onfocus'],
                'onblur'    => $params['onblur'],
            ));
            $html .= 'h ';
        }

        /* add minutes inputs */
        if (in_array('minutes', $params['objects'])) {
            $default = $params['default'] === '' ? '' : date('i', $params['default']);
            $html .= $this->display_textInput(array(
                'name'      => $params['name'].'_minutes',
                'maxlength' => 2,
                'size'      => 2,
                'class'     => '',
                'default'   => $default,
                'tabIndex'  => $params['tabIndex'] == -1 ? -1 : $params['tabIndex']+4,
                'onchange'  => $params['onchange'],
                'onfocus'   => $params['onfocus'],
                'onblur'    => $params['onblur'],
            ));
            $html .= 'm ';
        }

        /* add seconds inputs */
        if (in_array('seconds', $params['objects'])) {
            $default = $params['default'] === '' ? '' : date('s', $params['default']);
            $html .= $this->display_textInput(array(
                'name'      => $params['name'].'_seconds',
                'maxlength' => 2,
                'size'      => 2,
                'class'     => '',
                'default'   => $default,
                'tabIndex'  => $params['tabIndex'] == -1 ? -1 : $params['tabIndex']+5,
                'onchange'  => $params['onchange'],
                'onfocus'   => $params['onfocus'],
                'onblur'    => $params['onblur'],
            ));
            $html .= 's ';
        }

        /* add buttons */
        if (count($params['buttons']) > 0) {
            $b = 'document.'.$this->name.'.'.$params['name'];
            /* add "update date" button */
            if (isset ($params['buttons']['update'])) {
                /* add space */
                $html .= '&nbsp;&nbsp;';
                /* add button link */
                $html .= '<a href="javascript:';
                $html .= 'd = new Date();';
                /* update day */
                if (in_array('day', $params['objects']))
                    $html .= $b.'_day.value=d.getDate();';
                /* update month */
                if (in_array('month', $params['objects']))
                    $html .= $b.'_month.options.selectedIndex=d.getMonth();';
                /* update year */
                if (in_array('year', $params['objects']))
                    $html .= $b.'_year.value=d.getFullYear();';
                /* update hours */
                if (in_array('hours', $params['objects']))
                    $html .= $b.'_hours.value=d.getHours();';
                /* update minutes */
                if (in_array('minutes', $params['objects']))
                    $html .= $b.'_minutes.value=d.getMinutes();';
                /* update seconds */
                if (in_array('seconds', $params['objects']))
                    $html .= $b.'_seconds.value=d.getSeconds();';
                $html .= 'void(0);">';
                if (isset ($params['buttons']['update']['std'])) {
                    $html .= '<img src="'.$params['buttons']['update']['std'].'"';
                    $html .= ' class="fileInputButton"';
                    $html .= ' alt="'.$params['buttons']['update']['title'].'"';
                    $html .= ' title="'.$params['buttons']['update']['title'].'"';
                    if (isset($params['buttons']['update']['class']))
                        $html .= ' class="'.$params['buttons']['update']['class'].'"';
                    if (isset($params['buttons']['update']['style']))
                        $html .= ' style="'.$params['buttons']['update']['style'].'"';
                    $html .= ' onmouseover="this.src=\''.$params['buttons']['update']['ovr'].'\';"';
                    $html .= ' onmouseout="this.src=\''.$params['buttons']['update']['std'].'\';"/>';
                } else {
                    $html .= '<img src="'.$params['buttons']['update'].'" alt="" />';
                }
                $html .= '</a> ';
            }

            /* add "reset date" button */
            if (isset ($params['buttons']['reset'])) {
                /* add space */
                $html .= '&nbsp;';
                /* add button link */
                $html .= '<a href="javascript:';
                /* reset day */
                if (in_array('day', $params['objects']))
                    $html .= $b.'_day.value=0;';
                /* reset month */
                if (in_array('month', $params['objects']))
                    $html .= $b.'_month.options.selectedIndex=0;';
                /* reset year */
                if (in_array('year', $params['objects']))
                    $html .= $b.'_year.value=0;';
                /* reset hours */
                if (in_array('hours', $params['objects']))
                    $html .= $b.'_hours.value=0;';
                /* reset minutes */
                if (in_array('minutes', $params['objects']))
                    $html .= $b.'_minutes.value=0;';
                /* reset seconds */
                if (in_array('seconds', $params['objects']))
                    $html .= $b.'_seconds.value=0;';
                $html .= 'void(0);">';
                /* reset image */
                if (isset ($params['buttons']['reset']['std'])) {
                    $html .= '<img src="'.$params['buttons']['reset']['std'].'"';
                    $html .= ' class="fileInputButton"';
                    $html .= ' alt="'.$params['buttons']['reset']['title'].'" ';
                    $html .= ' title="'.$params['buttons']['reset']['title'].'" ';
                    if (isset($params['buttons']['update']['class']))
                        $html .= ' class="'.$params['buttons']['update']['class'].'"';
                    if (isset($params['buttons']['update']['style']))
                        $html .= ' style="'.$params['buttons']['update']['style'].'"';
                    $html .= ' onmouseover="this.src=\''.$params['buttons']['reset']['ovr'].'\';"';
                    $html .= ' onmouseout="this.src=\''.$params['buttons']['reset']['std'].'\';"/>';
                } else {
                    $html .= '<img src="'.$params['buttons']['reset'].'" alt="" />';
                }
                $html .= '</a>';
            }
        }
        return $html;
    }

    /**
     * Display file input form item.
     * @param string $file the form item name
     * @param string $default the default value
     * @param array $buttons the button descriptions to add
     * @return string
     */
    public function display_fileInput($file='file', $default='', $buttons=null) {
        global $camyks;

        /* build param list */
        $params = array('class'=>'', 'buttons'=>null, 'accept'=>'');

        /* check limit */
        $this->check_inputsLimit(2);

        /* check header params */
        if (is_array($file)) {
            $params = array_merge($this->inputDefaultParams, $params, $file);
        } else {
            $params = array_merge($this->inputDefaultParams, $params);
            $params['name'] = $file;
            if (isset($default))
                $params['default'] = $default;
            if (isset($buttons))
                $params['buttons'] = $buttons;
        }

        /* check object params */
        $n = $params['name'].($params['language']?'_'.$params['language']:'');
        if ($params['default'] === '' and isset($this->object)) {
            $params['default'] = isset($this->object->vars[$n])?$this->object->vars[$n]:'';
        }

        /* check parent params */
        if ($params['buttons'] === null) {
            if (isset($this->parent))
                $params['buttons'] = $this->parent->get_fileInputButtons();
            elseif (isset($this->object->_libParent))
                $params['buttons'] = $this->object->_libParent->get_fileInputButtons();
        }

        /* build file input element */
        $html = '<input type="file"';
        $html .= $this->build_inputGenericAttributes($params);
        if ($params['accept'] != '')
            $html .= ' accept="'.$params['accept'].'"';
        if ($params['allowMultiple'] == true)
            $html .= ' multiple=""';
        $html .= ' /> ';
        $html .= '<input type="hidden" name="'.$n.'_deletefile" value="0" />';

        /* check for file infos */
        if ($params['default'] === false) {
            /* do not write anything */
        } elseif ($params['default'] == '') {
            $html .= $camyks->get_translation('file_nofile');
        } else {
            $file = new FSFile($params['default']);
            $html .= '<span id="'.$n.'_filedesc">';
            $html .= $camyks->get_translation('file_filetype', strtoupper($file->ext));
            $html .= ' ';

            foreach ($params['buttons'] as $name => $button) {
                if ($name == 'view') {
                    /* check view button */
                    if ($file->type == 'image' and isset($button['std'])) {
                        $html .= '&nbsp;<a href="'.$params['default'].'" target="_blank">';
                        $html .= '<img src="'.$button['std'].'" class="fileInputButton"';
                        $html .= ' alt="'.$button['title'].'" border="0"';
                        $html .= ' onmouseover="this.src=\''.$button['ovr'].'\';"';
                        $html .= ' onmouseout="this.src=\''.$button['std'].'\';"/>';
                        $html .= '</a>';
                    }
                } elseif ($name == 'listen') {
                    if ($file->type == 'audio' and isset($button['std'])) {
                        $html .= '&nbsp;<audio id="sound-'.$n.'">';
                        $html .= '<source src="'.$params['default'].'" type="'.$file->mime.'">';
                        $html .= '</audio>';
                        $html .= '<a href="javascript:document.getElementById(\'sound-'.$n.'\').play();">';
                        $html .= '<img src="'.$button['std'].'" class="fileInputButton"';
                        $html .= ' alt="'.$button['title'].'" border="0"';
                        $html .= ' onmouseover="this.src=\''.$button['ovr'].'\';"';
                        $html .= ' onmouseout="this.src=\''.$button['std'].'\';"/>';
                        $html .= '</a>';
                    }
                } elseif ($name == 'delete') {
                    if (isset($params['buttons']['delete']['std'])) {
                        /* add delete button */
                        $html .= '&nbsp;<a href="javascript:';
                        $html .= 'document.'.$this->name.'.'.$n.'_deletefile.value=1;';
                        $html .= 'document.getElementById(\''.$n.'_filedesc\').innerHTML=\''.$camyks->get_translation('file_deleted').'\';';
                        $html .= 'void(0);">';
                        $html .= '<img src="'.$params['buttons']['delete']['std'].'"';
                        $html .= ' class="fileInputButton"';
                        $html .= ' alt="'.$params['buttons']['delete']['title'].'" border="0"';
                        $html .= ' onmouseover="this.src=\''.$params['buttons']['delete']['ovr'].'\';"';
                        $html .= ' onmouseout="this.src=\''.$params['buttons']['delete']['std'].'\';"/>';
                        $html .= '</a>';
                    }
                } else {
                    $html .= '&nbsp;<a href="'.$button['url'].'"';
                    if (isset($button['urlTarget']) and $button['urlTarget'] != '')
                        $html .= ' target="'.$button['url'].'"';
                    $html .= '><img src="'.$button['std'].'"';
                    $html .= ' alt="'.$button['title'].'" border="0"';
                    $html .= ' onmouseover="this.src=\''.$button['ovr'].'\';"';
                    $html .= ' onmouseout="this.src=\''.$button['std'].'\';"/>';
                    $html .= '</a>';
                }
            }
            $html .= '</span>&nbsp;';
        }
        return $html;
    }

    /**
     * Build and return select input.
     * @param mixed $select
     * @param array $values
     * @param mixed $default
     * @return string
     */
    public function display_selectInput($select, $values=null, $default=null) {
        global $camyks;
        /* build param list */
        $params = array('values'=>array(), 'hasEmptyFirstOption'=>false, 'blocId'=>'');

        /* check header params */
        if (is_array($select)) {
            $params = array_merge($this->inputDefaultParams, $params, $select);
        } else {
            $params = array_merge($this->inputDefaultParams, $params);
            $params['name'] = $select;
            if (isset($values))
                $params['values'] = $values;
            if (isset($default))
                $params['default'] = $default;
        }

        /* check limit */
        $this->check_inputsLimit();

        /* check object params */
        if ($params['default'] === '' and isset($this->object)) {
            $n = $params['name']. ($params['language']?'_'.$params['language']:'');
            $params['default'] = isset($this->object->vars[$n])?$this->object->vars[$n]:'';
        }

        /* check for first empty item */
        if ($params['hasEmptyFirstOption'] === true)
            $params['values'] = array(''=>' ') + $params['values'];
        elseif (is_array($params['hasEmptyFirstOption']))
            $params['values'] = $params['hasEmptyFirstOption']+ $params['values'];
        elseif ($params['hasEmptyFirstOption'] !== false)
            $params['values'] = array(''=>$params['hasEmptyFirstOption']) + $params['values'];

        /* build select header */
        $html = '';
        if ($camyks->theme->useEnhancedSelectInputs == true or $params['blocId'] != '') {
            $addBloc = true;
            $html = '<div class="'.$params['class'].'"';
            if ($params['blocId'] != '')  $html.= ' id="'.$params['blocId'].'"';
            $html .= '>';
        } else {
            $addBloc = false;
        }

        $html .= '<select';
        $html .= $this->build_inputGenericAttributes($params);
        $html .= '>' . "\n";

        /* add option items */
        foreach ($params['values'] as $name => $value) {
            if (is_array($value)) {
                $dAttr = array('value'=>'', 'class'=>'', 'style'=>'', 'disabled'=>'');
                $value = array_merge($dAttr, $value);

                $html .= '<option value="'.htmlentities($name, ENT_COMPAT, 'UTF-8').'"';
                if ($value['class'] != '')
                    $html .= ' class="'.$value['class'].'"';
                if ($value['style'] != '')
                    $html .= ' style="'.$value['style'].'"';
                if ($value['disabled'] != '')
                    $html .= ' disabled="'.$value['disabled'].'"';
                else
                    $html .= ($name==$params['default']?' selected="selected"':'');
                $html .= '>';
                $html .= $value['value'];
                $html .= '</option>';
            } else {
                $html .= '<option value="'.htmlentities($name, ENT_COMPAT, 'UTF-8').'"';
                $html .= ($name==$params['default']?' selected="selected"':'').'>';
                $html .= $value;
                $html .= '</option>';
            }
        }
        /* add select footer */
        $html .= '</select>';
        if ($addBloc)
            $html .= '</div>';
        return $html;
    }

    /**
     * Build and return boolean select input.
     * @param mixed $select
     * @param mixed $default
     * @return string
     */
    public function display_booleanSelectInput($select, $default=null) {
        global $camyks;
        /* build param list */
        $params = array('values'=>array(0 => $camyks->get_translation('no'), 1 => $camyks->get_translation('yes')));

        /* check header params */
        if (is_array($select)) {
            $params = array_merge($params, $select);
        } else {
            $params['name'] = $select;
            if (isset($default))
                $params['default'] = $default;
        }

        /* build display */
        return $this->display_selectInput($params);
    }

    /**
     * Build and return country select input.
     * @param mixed $select
     * @param mixed $default
     * @return string
     */
    public function display_countrySelectInput($select=array(), $default=null) {
        global $camyks;
        /* build param list */
        $params = array('name'=>'country', 'highlighted'=>array(), 'shortlist'=>array(), 'territories'=>1, 'highlight_separator'=>'', 'hasEmptyFirstOption'=>false);

        /* check header params */
        if (is_array($select)) {
            $params = array_merge($this->inputDefaultParams, $params, $select);
        } else {
            $params = array_merge($this->inputDefaultParams, $params);
            $params['name'] = $select;
            if (isset($default))
                $params['default'] = $default;
        }

        /* check object params */
        $n = $params['name'].($params['language']?'_'.$params['language']:'');
        if ($params['default'] == '' and isset($this->object)) {
            $params['default'] = isset($this->object->vars[$n])?$this->object->vars[$n]:'';
        }

        /* load country list */
        $countries = countries_getTitleList(array(
            'territories'   => $params['territories'],
            'shortlist'     => $params['shortlist'],
        ));

        /* check for highlighted countries */
        if (is_array($params['highlighted']) and count($params['highlighted'])>0) {
            $hc = array();
            foreach ($params['highlighted'] as $code) {
                if (isset($countries[$code])) {
                    $hc[$code] = $countries[$code];
                    unset($countries[$code]);
                }
            }
            if ($params['highlight_separator'] != '')
                $hc[''] = array('value'=>$params['highlight_separator'], 'disabled'=>'disabled');
            $countries = array_merge($hc,$countries);
        }

        /* update params value */
        $params['values'] = $countries;

        /* build display */
        return $this->display_selectInput($params);
    }

    /**
     * Build and return phone prefix select input.
     * @param mixed $select
     * @param mixed $default
     * @return string
     */
    public function display_phonePrefixSelectInput($select=array(), $default=null) {
        global $camyks;

        /* build param list */
        $params = array('name'=>'phonePrefix', 'highlighted'=>array(), 'shortList'=>array(), 'territories'=>1, 'highlight_separator'=>'', 'hasEmptyFirstOption'=>false, 'display_country'=>false, 'display_plus'=>false, 'display_zero'=>false, 'value'=>'countryCode', 'class'=>'sinputs');

        /* check header params */
        if (is_array($select)) {
            $params = array_merge($this->inputDefaultParams, $params, $select);
        } else {
            $params = array_merge($this->inputDefaultParams, $params);
            $params['name'] = $select;
            if (isset($default))
                $params['default'] = $default;
        }

        /* check object params */
        $n = $params['name'].($params['language']?'_'.$params['language']:'');
        if ($params['default'] == '' and isset($this->object)) {
            $params['default'] = isset($this->object->vars[$n])?$this->object->vars[$n]:'';
        }

        /* load country list */
        $prefixes = countries_getPhonePrefixes();

        $countries = countries_getTitleList(array(
            'territories'   => $params['territories'],
            'shortlist'     => $params['shortList'],
        ));

        $list = array();

        /* check for highlighted countries */
        if (is_array($params['highlighted']) and count($params['highlighted'])>0) {
            $hc = array();
            foreach ($params['highlighted'] as $code) {
                if (isset($prefixes[$code])) {
                    $hc[$code] = $prefixes[$code];
                    unset($prefixes[$code]);
                }
            }
            if ($params['highlight_separator'] != '')
                $hc[''] = array('value'=>$params['highlight_separator'], 'disabled'=>'disabled');
            $prefixes = array_merge($hc, $prefixes);
        }

        foreach ($prefixes as $code => $value) {
            if ($code == '' or count($params['shortList']) == 0 or in_array($code, $params['shortList'])) {
                if ($code != '') {
                    $v = '';
                    if ($params['display_country']) {
                        if (!isset($countries[$code]))
                            continue;
                        $v .= $countries[$code] . ' ';
                    }
                    if ($params['display_plus'])
                        $v .= '+ ';
                    $v .= $value;
                    if ($params['display_zero'])
                        $v .= ' (0)';
                    if ($params['value'] == 'phonePrefix')
                        $c = $value;
                    else
                        $c = $code;
                    $list [$c] = $v;
                } else {
                    $list[$code] = $value;
                }
            }
        }

        /* define params for display select input method */
        $params['values'] = $list;

        /* build display */
        return $this->display_selectInput($params);
    }

    /**
     * Build and return civility select input.
     * @param mixed $select
     * @param mixed $default
     * @return string
     */
    public function display_civilitySelectInput($select, $default=null) {
        global $camyks;
        /* build param list */
        $params = array('class'=>'vsinput');
        $params['values'] = array();
        $civilities = array('mr', 'mrs', 'ms', 'sir', 'dr', 'pr', 'me');
        foreach($civilities as $c) {
            if (($v = $camyks->get_translation('civility_'.$c))!='')
                $params['values'][$c] = $v;
        }

        /* check header params */
        if (is_array($select)) {
            $params = array_merge($this->inputDefaultParams, $params, $select);
        } else {
            $params = array_merge($this->inputDefaultParams, $params);
            $params['name'] = $select;
            if (isset($default))
                $params['default'] = $default;
        }

        /* build display */
        return $this->display_selectInput($params);
    }

    /**
     * Build and return week days select input.
     * @param mixed $select
     * @param mixed $default
     * @return string
     */
    public function display_weekDaySelectInput($select, $default=null) {
        global $camyks;
        /* build param list */
        $params = array('format'=>1);

        /* check header params */
        if (is_array($select)) {
            $params = array_merge($this->inputDefaultParams, $params, $select);
        } else {
            $params = array_merge($this->inputDefaultParams, $params);
            $params['name'] = $select;
            if (isset($default))
                $params['default'] = $default;
        }

        /* setup values */
        $params['values'] = array();

        for ($i=(0+$params['format']); $i<=(6+$params['format']); $i++) {
            $params['values'][$i] = strftime('%A', mktime(0, 0, 0, 1, 2+$i, 0));
        }

        /* build display */
        return $this->display_selectInput($params);
    }

    /**
     * Build and return text input.
     * @param mixed $input
     * @param string $default
     * @return string
     */
    public function display_textInput($input, $default=null) {
        /* check header params */
        if (is_array($input)) {
            $params = array_merge($this->inputDefaultParams, $input);
        } else {
            $params = $this->inputDefaultParams;
            $params['name'] = $input;
            if (isset($default))
                $params['default'] = $default;
        }

        /* check limit */
        $this->check_inputsLimit();

        /* check object params */
        if (isset($this->object)) {
            /* check default value */
            if ($params['default'] === '') {
                $v = $params['name'].($params['language']==''?'':'_'.$params['language']);
                $params['default'] = isset($this->object->vars[$v])?$this->object->vars[$v]:'';
            }

        /* check maxlength value */
        if ($params['maxlength'] == 0)
            if (isset($this->object->_libItems[$params['name']]->datatype)
                    and in_array($this->object->_libItems[$params['name']]->datatype, array('etext', 'text'))
                    and $this->object->_libItems[$params['name']]->datadesc2 > 0)
                $params['maxlength'] = $this->object->_libItems[$params['name']]->datadesc2;
            else
                $params['maxlength'] = 32;
        }



        /* build input */
        $html = '<input type="text"';
        $html .= ' value="'.htmlentities($params['default'], ENT_COMPAT, 'UTF-8').'"';
        $html .= $this->build_inputGenericAttributes($params);
        $html .= ' />';
        return $html;
    }

    /**
     * Build and return number input.
     * @param mixed $input
     * @param string $default
     * @return string
     */
    public function display_numberInput($input, $default=null) {
        /* build param list */
        $params = array('min'=>'', 'max'=>'', 'step'=>'');

        /* check header params */
        if (is_array($input)) {
            $params = array_merge($this->inputDefaultParams, $params, $input);
        } else {
            $params = array_merge($this->inputDefaultParams, $params);
            $params['name'] = $input;
            if (isset($default))
                $params['default'] = $default;
        }

        /* check limit */
        $this->check_inputsLimit();

        /* check object params */
        if (isset($this->object)) {
            /* check default value */
            if ($params['default'] === '') {
                $v = $params['name'].($params['language']==''?'':'_'.$params['language']);
                $params['default'] = isset($this->object->vars[$v])?$this->object->vars[$v]:'';
            }
        }

        /* build input */
        $html = '<input type="number"';
        $html .= ' value="'.(int)$params['default'].'"';
        $html .= $this->build_inputGenericAttributes($params);
        if ($params['min'] > 0)
            $html .= ' min="'.$params['min'].'"';
        if ($params['max'] > 0)
            $html .= ' max="'.$params['max'].'"';
        if ($params['step'] > 0)
            $html .= ' step="'.$params['step'].'"';
        $html .= ' />';
        return $html;
    }

    /**
     * Build and return email input.
     * @param mixed $input
     * @param string $default
     * @return string
     */
    public function display_emailInput($input, $default=null) {
        /* build param list */
        $params = array('multiple'=>false);

        /* check header params */
        if (is_array($input)) {
            $params = array_merge($this->inputDefaultParams, $params, $input);
        } else {
            $params = array_merge($this->inputDefaultParams, $params);
            $params['name'] = $input;
            if (isset($default))
                $params['default'] = $default;
        }

        /* check limit */
        $this->check_inputsLimit();

        /* check object params */
        if (isset($this->object)) {
            /* check default value */
            if ($params['default'] === '') {
                $v = $params['name'].($params['language']==''?'':'_'.$params['language']);
                $params['default'] = isset($this->object->vars[$v])?$this->object->vars[$v]:'';
            }
        }

        /* build input */
        $html = '<input type="email"';
        $html .= ' value="'.$params['default'].'"';
        $html .= $this->build_inputGenericAttributes($params);
        if ($params['multiple'] === true)
            $html .= ' multiple';
        $html .= ' />';
        return $html;
    }

    /**
     * Build and return phone input.
     * @param mixed $input
     * @param string $default
     * @return string
     */
    public function display_phoneInput($input, $default=null) {
        /* check header params */
        if (is_array($input)) {
            $params = array_merge($this->inputDefaultParams, $input);
        } else {
            $params = $this->inputDefaultParams;
            $params['name'] = $input;
            if (isset($default))
                $params['default'] = $default;
        }

        /* check limit */
        $this->check_inputsLimit();

        /* check object params */
        if (isset($this->object)) {
            /* check default value */
            if ($params['default'] === '') {
                $v = $params['name'].($params['language']==''?'':'_'.$params['language']);
                $params['default'] = isset($this->object->vars[$v])?$this->object->vars[$v]:'';
            }
        }

        /* build input */
        $html = '<input type="tel"';
        $html .= ' value="'.$params['default'].'"';
        $html .= $this->build_inputGenericAttributes($params);
        if ($params['size'] > 0)
            $html .= ' size="'.$params['size'].'"';
        if ($params['readonly'] == 'readonly' or $params['readonly'] == true)
            $html .= ' readonly="readonly"';
        if ($params['list'] != '')
            $html .= ' list="'.$params['list'].'"';
        if ($params['autocomplete'] != '')
            $html .= ' autocomplete="'.$params['autocomplete'].'"';
        if ($params['pattern'] != '')
            $html .= ' pattern="'.$params['pattern'].'"';
        $html .= ' />';
        return $html;
    }

    /**
     * Build and return URL input.
     * @param mixed $input
     * @param string $default
     * @return string
     */
    public function display_URLInput($input, $default=null) {
        /* check header params */
        if (is_array($input)) {
            $params = array_merge($this->inputDefaultParams, $input);
        } else {
            $params = $this->inputDefaultParams;
            $params['name'] = $input;
            if (isset($default))
                $params['default'] = $default;
        }

        /* check limit */
        $this->check_inputsLimit();

        /* check object params */
        if (isset($this->object)) {
            /* check default value */
            if ($params['default'] === '') {
                $v = $params['name'].($params['language']==''?'':'_'.$params['language']);
                $params['default'] = isset($this->object->vars[$v])?$this->object->vars[$v]:'';
            }
        }

        /* build input */
        $html = '<input type="url"';
        $html .= ' value="'.$params['default'].'"';
        $html .= $this->build_inputGenericAttributes($params);
        $html .= ' />';
        return $html;
    }

    /**
     * Build and return textarea input.
     * @param mixed $input
     * @param string $default
     * @return string
     */
    public function display_textareaInput($input, $default=null) {
        /* build param list */
        $params = array('class'=>'vlinputs', 'cols'=>'40', 'rows'=>'4');

        /* check header params */
        if (is_array($input)) {
            $params = array_merge($this->inputDefaultParams, $params, $input);
        } else {
            $params = array_merge($this->inputDefaultParams, $params);
            $params['name'] = $input;
            if (isset($default))
                $params['default'] = $default;
        }

        /* check limit */
        $this->check_inputsLimit();

        /* check object params */
        if ($params['default'] == '') {
            $v = $params['name'].($params['language']==''?'':'_'.$params['language']);
            if ($this->object != null and isset($this->object->vars[$v]))
                $params['default'] = $this->object!=null?$this->object->vars[$v]:'';
        }

        /* build input */
        $html = '<textarea';
        $html .= $this->build_inputGenericAttributes($params);
        $html .= ' cols="'.$params['cols'].'"';
        $html .= ' rows="'.$params['rows'].'"';
        $html .= ' >';
        $html .= string_text2html($params['default']);
        $html .= '</textarea>';
        return $html;
    }

    /**
     * Build and return password input.
     * @param mixed $input
     * @return string
     */
    public function display_passwordInput($input) {
        /* build param list */
        $params = array('size'=>0,);

        /* check header params */
        if (is_array($input)) {
            $params = array_merge($this->inputDefaultParams, $params, $input);
        } else {
            $params = array_merge($this->inputDefaultParams, $params);
            $params['name'] = $input;
        }

        /* check limit */
        $this->check_inputsLimit();

        /* check object params */
        if (isset($this->object)) {
            /* check maxlength value */
            if ($params['maxlength'] == 0)
                if (isset($this->object->_libItems[$params['name']]->datatype)
                        and in_array($this->object->_libItems[$params['name']]->datatype, array('password', 'etext', 'text'))
                        and (int)$this->object->_libItems[$params['name']]->datadesc2 > 0)
                    $params['maxlength'] = $this->object->_libItems[$params['name']]->datadesc2;
                else
                    $params['maxlength'] = 32;
        }

        /* build input */
        $html = '<input type="password"';
        $html .= $this->build_inputGenericAttributes($params);
        $html .= ' value=""';
        $html .= ' />';
        return $html;
    }

    /**
     * Build and return checkbox input.
     * @param mixed $input
     * @param string $default
     * @return string
     */
    public function display_checkboxInput($input, $default=null) {
        /* build param list */
        $params = array('class'=>'', 'size'=>0, 'value'=>'', 'label'=>'', 'labelClass'=>'', 'labelStyle'=>'', 'multiValues'=>false);

        /* check header params */
        if (is_array($input)) {
            $params = array_merge($this->inputDefaultParams, $params, $input);
        } else {
            $params = array_merge($this->inputDefaultParams, $params);
            $params['name'] = $input;
            if (isset($default))
                $params['default'] = $default;
        }

        /* check limit */
        $this->check_inputsLimit();

        /* check object params */
        if (isset($this->object)) {
            /* check default value */
            if ($params['default'] == '') {
                $v = $params['name'].($params['language']==''?'':'_'.$params['language']);
                $params['default'] = isset($this->object->vars[$v])?$this->object->vars[$v]:'';
            }
        }

        /* check labels and id */
        if ($params['label'] != '' and $params['id'] == '') {
            $params['id'] = '_'.$params['name'].($params['language'] != '' ? '_'.$params['language']:'').'_'.$params['value'];
        }

        /* build input */
        $html = '<input type="checkbox"';
        if ($params['language'] == '')
            $html .= ' name="'.$params['name'];
        else
            $html .= ' name="'.$params['name'].'_'.$params['language'];
        if ($params['multiValues']===true)
            $html .= '[]';
        $html .= '"';
        $html .= ' value="'.$params['value'].'"';

        /* avoid name to be rewritten in generic attributes */
        $params['name'] = '';
        $html .= $this->build_inputGenericAttributes($params);

        if ($params['default'] === $params['value'])
            $html .= ' checked="checked"';
        elseif ($params['multiValues'] === true and is_array($params['default']) and in_array($params['value'], $params['default']))
            $html .= ' checked="checked"';
        $html .= ' />';

        /* build optional label */
        if ($params['label'] != '') {
            $html .= '<label for="'.$params['id'].'"';
            if ($params['labelClass'] != '')
                $html .= ' class="'.$params['labelClass'].'"';
            if ($params['labelStyle'] != '')
                $html .= ' style="'.$params['labelStyle'].'"';
            $html .= '>'.$params['label'].'</label>';
        }

        /* send html code */
        return $html;
    }

    /**
     * Build and return radio input.
     * @param mixed $input
     * @param string $default
     * @return string
     */
    public function display_radioInput($input, $default=null) {
        /* build param list */
        $params = array('class'=>'', 'value'=>'', 'label'=>'', 'labelClass'=>'', 'labelStyle'=>'');

        /* check header params */
        if (is_array($input)) {
            $params = array_merge($this->inputDefaultParams, $params, $input);
        } else {
            $params = array_merge($this->inputDefaultParams, $params);
            $params['name'] = $input;
            if (isset($default))
                $params['default'] = $default;
        }

        /* check limit */
        $this->check_inputsLimit(1, $params['name']);

        /* check object params */
        if (isset($this->object)) {
            /* check default value */
            if ($params['default'] == '') {
                $v = $params['name'].($params['language']==''?'':'_'.$params['language']);
                $params['default'] = isset($this->object->vars[$v])?$this->object->vars[$v]:'';
            }
        }

        /* check labels and id */
        if ($params['label'] != '' and $params['id'] == '') {
            $params['id'] = '_'.$params['name'].($params['language'] != '' ? '_'.$params['language']:'').'_'.$params['value'];
        }

        /* build input */
        $html = '<input type="radio"';
        $html .= ' value="'.$params['value'].'"';
        $html .= $this->build_inputGenericAttributes($params);
        if ($params['default'] === $params['value'])
            $html .= ' checked="checked"';
        $html .= ' />';

        /* build optional label */
        if ($params['label'] != '') {
            $html .= '<label for="'.$params['id'].'"';
            if ($params['labelClass'] != '')
                $html .= ' class="'.$params['labelClass'].'"';
            if ($params['labelStyle'] != '')
                $html .= ' style="'.$params['labelStyle'].'"';
            $html .= '>'.$params['label'].'</label>';
        }

        /* send html code */
        return $html;
    }

    /**
     * Build and return hidden input.
     * @param mixed $input
     * @param string $default
     * @return string
     */
    public function display_hiddenInput($input, $default=null) {
        /* check header params */
        if (is_array($input)) {
            $params = array_merge($this->inputDefaultParams, $input);
        } else {
            $params = $this->inputDefaultParams;
            $params['name'] = $input;
            if (isset($default))
                $params['default'] = $default;
        }

        /* check limit */
        $this->check_inputsLimit(1, $params['name']);

        /* check object params */
        if (isset($this->object)) {
            /* check default value */
            if ($params['default'] == '') {
                $v = $params['name'].($params['language']==''?'':'_'.$params['language']);
                $params['default'] = isset($this->object->vars[$v])?$this->object->vars[$v]:'';
            }
        }

        /* build input */
        $html = '<input type="hidden"';
        $html .= $this->build_inputGenericAttributes($params);
        $html .= ' value="'.$params['default'].'"';
        $html .= ' />';

        /* send html code */
        return $html;
    }

    /**
     * Return generic attributes for inputs
     * @param array $params
     * @return string
     */
    protected function build_inputGenericAttributes($params) {
        $html = '';
        if ($params['name'] != '') {
            if ($params['language'] == '')
                $html .= ' name="'.$params['name'].'"';
            else
                $html .= ' name="'.$params['name'].'_'.$params['language'].'"';
        }
        if ($params['allowMultiple'] == true)
            $params['name'] .= '[]';
        if ($params['id'] != '')
            $html .= ' id="'.$params['id'].'"';
        if ($params['maxlength'] > 0)
            $html .= ' maxlength="'.$params['maxlength'].'"';
        if ($params['minlength'] > 0)
            $html .= ' minlength="'.$params['minlength'].'"';
        if ($params['class'] != '')
            $html .= ' class="'.$params['class'].'"';
        if ($params['style'] != '')
            $html .= ' style="'.$params['style'].'"';
        if ($params['onchange'] != '')
            $html .= ' onchange="'.$params['onchange'].'"';
        if ($params['onkeydown'] != '')
            $html .= ' onkeydown="'.$params['onkeydown'].'"';
        if ($params['onkeyup'] != '')
            $html .= ' onkeyup="'.$params['onkeyup'].'"';
        if ($params['onfocus'] != '')
            $html .= ' onfocus="'.$params['onfocus'].'"';
        if ($params['onblur'] != '')
            $html .= ' onblur="'.$params['onblur'].'"';
        if ($params['oninput'] != '')
            $html .= ' oninput="'.$params['oninput'].'"';
        if ($params['disabled'] != '')
            $html .= ' disabled="disabled"';
        if ($params['placeholder'] != '')
            $html .= ' placeholder="'.$params['placeholder'].'"';
        if ($params['readonly'] == 'readonly' or $params['readonly'] == true)
            $html .= ' readonly="readonly"';
        if ($params['list'] != '')
            $html .= ' list="'.$params['list'].'"';
        if ($params['autocomplete'] != '')
            $html .= ' autocomplete="'.$params['autocomplete'].'"';
        if ($params['pattern'] != '')
            $html .= ' pattern="'.$params['pattern'].'"';
        if (is_array($params['data'])) {
            foreach ($params['data'] as $name => $value)
                $html .= ' data-'.$name.'="'.$value.'"';
        }
        if ($this->tabIndex>-1 or $params['tabIndex'] != -1)
            $html .= ' '.$this->get_tabIndex(true, $params['tabIndex']);
        if ($params['size'] > 0)
            $html .= ' size="'.$params['size'].'"';
        return $html;
    }

    /**
     * Return hidden submit link for "enter" pressed validation.
     * @return string
     */
    public function display_hiddenSubmit() {
        return '<input type="submit" style="position: absolute; left: -9999px; width: 1px; height: 1px;" tabindex="-1" />';
    }

    /**
     * Return current form html submit link.
     * @return string
     */
    public function get_HTMLSubmitLink() {
        return 'javascript:document.'.$this->name.'.submit();';
    }

    /**
     * Return current form javascript submit link.
     * @return string
     */
    public function get_JSSubmitLink() {
        return 'document.'.$this->name.'.submit();';
    }

    /**
     * Start tabIndex.
     * @return void
     */
    public function start_tabIndex() {
        $this->tabIndex = 0;
    }

    /**
     * Return tabIndex value or form value.
     * @param boolean $full indicate if method return html source
     * @param integer $index indicate forced value
     * @return mixed
     */
    public function get_tabIndex($full=false, $index=-1) {
        if ($index) {
            if ($this->tabIndex < $index)
                $this->tabIndex = $index;
            } elseif ($this->tabIndex == -1) {
                $this->tabIndex = 1;
                $index = $this->tabIndex;
            } else {
                $this->tabIndex++;
                $index = $this->tabIndex;
            }

        if ($full) {
            return ' tabindex="'.$index.'"';
        }
        return $index;
    }

    /**
     * Check max input vars limit.
     * @param integer $items
     * @param integer $name
     * @return boolean result
     */
    private function check_inputsLimit($items=1, $name=false) {
        global $camyks;

        /* check is limit has already been reached */
        if ($this->inputsLimitReached)
            return false;

        /* check for unique items */
        if ($name !== false) {
            if (in_array($name, $this->inputsLimitUniques))
                return true;
            else
                $this->inputsLimitUniques[] = $name;
        }

        /* update count value */
        $this->inputsCount += $items;

        /* check count value */
        if ($this->inputsLimit !== false and $this->inputsCount >= $this->inputsLimit) {
            $camyks->log_executionerror($this, 'Max inputs limit reached in form');
            return false;
        }

        /* success */
        return true;
    }

    /**
     * Temporarily and virtually update max input vars limit.
     * @param integer $value
     * @return void
     */
    public function update_inputsLimit($value=1000) {
        $this->inputsLimit = $value;
    }

    /* deprecated methods */

    /**
     * Alias to display_footer method.
     * @see display_footer()
     * @return string
     * @deprecated Use display_footer instead.
     */
    public function display_ender() {
        return $this->display_footer();
    }
}

/**
 * HTMLForm_hidden class.
 * @author CaMykS Team <camyks.contact@gmail.com>
 */
final class HTMLForm_hidden {
    /**
     * @var string $name
     * @brief Hidden input name.
     */
    public $name;

    /**
     * @var mixed $value
     * @brief Hidden input value.
     */
    public $value;

    /**
     * @var string $id
     * @brief Hidden input id.
     */
    public $id;

    /**
     * Class constructor.
     * @param string $name
     * @param mixed $value
     * @param string $id
     * @return void
     */
    public function __construct($name, $value, $id='') {
        $this->name = $name;
        $this->value = $value;
        $this->id = $id;
    }

    /**
     * Return input object html.
     * @return string
     */
    public function display() {
        return '<input type="hidden" name="'.$this->name.'" '.($this->id!=''?'id="'.$this->id.'" ':'').'value="'.htmlentities($this->value, ENT_COMPAT, 'UTF-8').'" />';
    }
}
?>
