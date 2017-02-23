<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Engine / Object Library
 * Creation Date	: Jun 2005
 * Last Modif Date	: Fev 2008
 * History :
 * * 05-06-xx : Initial File
 * * 08-01-16 : generic file upload input builder method
 *
 * HTMLForm object
 * Used to build a form in html page.
*/

/*
 * constants
 */
define('HTMLFORM_METHOD_POST',		0);
define('HTMLFORM_METHOD_GET',		1);

/*
 * HTMLForm object 
 */
class HTMLForm {
  /* the form name */
  var $name;
  /* the form action url */
  var $action;
  /* the method use to send data */
  var $method;
  /* the onSubmit script to execute */ 
  var $onSubmit;
  /* the window target */
  var $target;
  /* the hidden values */
  var $hiddens;
  /* indicate if the form allow files */
  var $allowFiles;
  /* the current tab value */
  var $tabIndex;
  /* the ModuleLibrary object */
  var $object;
  /* the Module object */
  var $parent;

  
  /* 
   * constructor
   * @param string $name the form name
   * @param string $action the form action url
   * @param mixed $method the method use to send data
   * @param string $onSubmit the onSubmit script to execute
   * @param string $target the window target
   */
  function HTMLForm ( $name='', $action='./', $method=null, $onSubmit='', $target='' ) {
    $this->name = $name;
    $this->action = $action;
    $this->onSubmit = $onSubmit;
    $this->target = $target;
    $this->allowFiles = false;
    $this->tabIndex = -1;
    $this->object = null;
    $this->parent = null;

    /* check for method type */
    switch ( $method ) {
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
    /* init hiddens list array */
    $this->hiddens = array();
  }

  /* methods */

  /* 
   * update allowFiles value 
   * @param boolean $allow
   * @param int $size the allow file size in bytes
   * @return void
   * @access public
   */
  function allow_files ( $allow=true, $size=null ) {
    $this->allowFiles = $allow;
    if ( $size > 0 ) {
      $this->add_hidden('MAX_FILE_SIZE', $size);
    }
  }


  /*
   * update object value
   * @param ModuleLibrary $object
   * @return void
   * @access public
   */
  function set_object($object=null) {
    $this->object = &$object;
  }

  /*
   * update parent value
   * @param Module $module
   * @return void
   * @access public
   */
  function set_parent($parent=null) {
    $this->parent = &$parent;
  }
  
  /* 
   * return form header as text
   * @return string 
   * @access public
   */
  function display_header( ) {
    $html = '<form';
    
    if ( $this->name != '' ) {
      $html .= ' name="'.$this->name.'"';
      $html .= ' id="'.$this->name.'"';
    }

    $html .= ' action="'.$this->action.'"';
    
    if ( $this->onSubmit != '' )
      $html .= ' onSubmit="'.$this->onSubmit.'"'; 
   
    if ( $this->allowFiles )
      $html .= ' enctype="multipart/form-data"';

    if ( $this->target != '' )
      $html .= ' target="'.$this->target.'"';
 
    $html .= ' method="'.$this->method.'"';
    $html .= '>'."\n";
    return $html;
  }
  
  /* 
   * return form footer as string
   * @return string
   * @access public
   */
  function display_footer( ) {
    return '</form>';
  }

  /*
   * deprecated : alias to display_footer method
   * @return string
   * @access public
   */
  function display_ender( ) {
    return $this->display_footer();
  }
  
  /* 
   * create an hidden value
   * @param string $name the hidden value name
   * @param string $value the hidden value content
   * @return void
   * @access public
   */
  function add_hidden ( $name, $value=null ) {
    if ( $value == null and isset($this->object) and isset($this->object->vars[$name]))
      $value = $this->object->vars[$name];
    if ($value !== null)
      $this->hiddens[] = new HTMLForm_hidden ( $name, $value );
  }
  
  /* 
   * return hidden input as text 
   * @return string
   * @access public
   */
  function display_hiddens ( ) {
    $html = "";
    foreach ( $this->hiddens as $hidden )
      $html .= $hidden->display()."\n";
    return $html;
  }
  
  /* 
   * return javascript code that set focus on given form element
   * @param string $focus the form item to focus
   * @return string
   * @access public
   */
  function set_jsFocus( $focus ) {
    return 'document.'.$this->name.'.'.$focus.'.focus();';
  }

  /*
   * return complete date form display
   * @param date $date
   * @param string $oname
   * @param array $objects 
   * @param array $buttons
   * @return string
   * @access public
   */
  function display_dateInput($date=TODAY, 
			     $oname='date',
			     $objects=array('day','month','year','hours','minutes'),
			     $buttons=array()){
    global $camyks;
    /* build param list */
    $params = array('id'=>'', 'name'=>'date', 'default'=>'', 'class'=>'inputs', 'style'=>'', 'onchange'=>'', 'onfocus'=>'', 'onblur'=>'', 'disabled'=>'', 
    'tabIndex'=>-1, 'objects'=>null, 'buttons'=>null, 'hasEmptyFirstOption'=>false, 'dayAsSelect'=>false, 'yearAsSelect'=>false, 'yearRange'=>array('from'=>2000, 'to'=>2050));

    /* check header params */
    if ( is_array($date)) {
      $params = array_merge($params, $date);
    } else {
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
    if ( $params['default'] === '' and $params['hasEmptyFirstOption'] === false) {
      $n = $params['name'];
      $params['default'] = isset($this->object->vars[$n])?$this->object->vars[$n]:TODAY;
    }
    if ($params['objects'] === null)
      $params['objects'] = array('day','month','year','hours','minutes');
   
    /* check parent params */
    if ($params['buttons'] === null) {
      if (isset($this->parent))
	    $params['buttons'] = $this->parent->get_dateInputButtons();
      elseif(isset($this->object->_libParent))
	    $params['buttons'] = $this->object->_libParent->get_dateInputButtons();
    }

    /* start html render */
    $html = '';
	
    /* add day input */
    if ( in_array('day', $params['objects'])) {
      $default = $params['default'] === '' ? '' : date('d', $params['default']);
      if ( $params['dayAsSelect'] == true) {
        $d = array();
        for ($i=1; $i<32; $i++) $d[$i] = $i;
        $html .= $this->display_selectInput(array(
          'name'=>$params['name'].'_day',
          'class'=>'vsinputs',
          'values'=>$d,
          'default'=>$default,
          'tabIndex'=>$params['tabIndex'] == -1 ? -1 : $params['tabIndex'],
          'onchange'=>$params['onchange'], 
          'onfocus'=>$params['onfocus'], 
          'onblur'=>$params['onblur']));
      } else {
        $html .= $this->display_textInput(array('name'=>$params['name'].'_day',
		  'maxlength'=>2,
		  'size'=>2,
		  'class'=>'',
		  'default'=>$default,
          'tabIndex'=>$params['tabIndex'] == -1 ? -1 : $params['tabIndex'],
          'onchange'=>$params['onchange'], 
          'onfocus'=>$params['onfocus'], 
          'onblur'=>$params['onblur']));
      }
      $html .= ' ';
    }

    /* add month input */
    if ( in_array('month', $params['objects'])) {
      $m = array();
      if ( $params['hasEmptyFirstOption'] )
        $m[0] = '';
      for ( $i=1; $i<=12; $i++ )
	  $m[$i] = ucfirst(strftime ( '%B', mktime( 0, 0, 0, $i, 1, 1 )));
	  $default = $params['default'] === '' ? 0 : (int)date('n', $params['default']);	  
      $html .= $this->display_selectInput(array('name'=>$params['name'].'_month',
						'values'=>$m,
						'class'=>'sinputs',
						'default'=>$default,
          'tabIndex'=>$params['tabIndex'] == -1 ? -1 : $params['tabIndex']+1,
          'onchange'=>$params['onchange'], 
          'onfocus'=>$params['onfocus'], 
          'onblur'=>$params['onblur'],
						));
      $html .= ' ';
    }
    /* add year input */
    if ( in_array('year', $params['objects'])) {
      $default = $params['default'] === '' ? '' : date('Y', $params['default']);
      if ( $params['yearAsSelect'] == true and $params['yearRange']['from'] > 0 and $params['yearRange']['to'] > 0) {
        $y = array();
        for ($i=$params['yearRange']['from']; $i<=$params['yearRange']['to']; $i++) $y[$i] = $i;
        $html .= $this->display_selectInput(array('name'=>$params['name'].'_year',
            'class'=>'sinputs',
            'values'=>$y,
            'default'=>$default,
          'tabIndex'=>$params['tabIndex'] == -1 ? -1 : $params['tabIndex']+2,
          'onchange'=>$params['onchange'], 
          'onfocus'=>$params['onfocus'], 
          'onblur'=>$params['onblur']));
      
      } else {
        $html .= $this->display_textInput(array('name'=>$params['name'].'_year',
					      'maxlength'=>4,
					      'size'=>4,
					      'class'=>'',
					      'default'=> $default,
          'tabIndex'=>$params['tabIndex'] == -1 ? -1 : $params['tabIndex']+2,
          'onchange'=>$params['onchange'], 
          'onfocus'=>$params['onfocus'], 
          'onblur'=>$params['onblur']));
        $html.= ' ';
      }
    }
    /* add hours input */
    if ( in_array( 'hours', $params['objects'] )) {
      $default = $params['default'] === '' ? '' : date('H', $params['default']);
      $html .= $this->display_textInput(array('name'=>$params['name'].'_hours',
					      'maxlength'=>2,
					      'size'=>2,
					      'class'=>'',
					      'default'=>$default,
          'tabIndex'=>$params['tabIndex'] == -1 ? -1 : $params['tabIndex']+3,
          'onchange'=>$params['onchange'], 
          'onfocus'=>$params['onfocus'], 
          'onblur'=>$params['onblur']));
      $html .= 'h ';
    }
    /* add minutes inputs */
    if ( in_array( 'minutes', $params['objects'] )) {
      $default = $params['default'] === '' ? '' : date('i', $params['default']);
      $html .= $this->display_textInput(array('name'=>$params['name'].'_minutes',
					      'maxlength'=>2,
					      'size'=>2,
					      'class'=>'',
					      'default'=>$default,
          'tabIndex'=>$params['tabIndex'] == -1 ? -1 : $params['tabIndex']+4,
          'onchange'=>$params['onchange'], 
          'onfocus'=>$params['onfocus'], 
          'onblur'=>$params['onblur']));
      $html .= 'm ';
    }
    /* add seconds inputs */
    if ( in_array( 'seconds', $params['objects'] )) {
      $default = $params['default'] === '' ? '' : date('s', $params['default']);
      $html .= $this->display_textInput(array('name'=>$params['name'].'_seconds',
					      'maxlength'=>2,
					      'size'=>2,
					      'class'=>'',
					      'default'=>$default,
          'tabIndex'=>$params['tabIndex'] == -1 ? -1 : $params['tabIndex']+5,
          'onchange'=>$params['onchange'], 
          'onfocus'=>$params['onfocus'], 
          'onblur'=>$params['onblur']));
      $html .= 's ';
    }

    /* add buttons */
    if ( count($params['buttons']) > 0 ) {
      $b = 'document.'.$this->name.'.'.$params['name'];
      /* add "update date" button */
      if ( isset ($params['buttons']['update'] )) {
	/* add space */
	$html.= '&nbsp;&nbsp;';
	/* add button link */
	$html .= '<a href="javascript:';
	$html .= 'd = new Date();';
	/* update day */
	if ( in_array( 'day', $params['objects'] ))
	  $html .= $b.'_day.value=d.getDate();';
	/* update month */
	if ( in_array( 'month', $params['objects'] )) 
	  $html .= $b.'_month.options.selectedIndex=d.getMonth();';
	/* update year */
	if ( in_array( 'year', $params['objects'] )) 
	  $html .= $b.'_year.value=d.getFullYear();'; 
	/* update hours */
	if ( in_array( 'hours', $params['objects'] )) 
	  $html .= $b.'_hours.value=d.getHours();'; 
	/* update minutes */
	if ( in_array( 'minutes', $params['objects'] )) 
	  $html .= $b.'_minutes.value=d.getMinutes();'; 
	/* update seconds */
	if ( in_array( 'seconds', $params['objects'] ))
	  $html .= $b.'_seconds.value=d.getSeconds();'; 
	$html .= 'void(0);">';
	if ( isset ( $params['buttons']['update']['std'] ) ) {
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
      if ( isset ($params['buttons']['reset'] )){
	/* add space */
	$html.= '&nbsp;';
	/* add button link */
	$html .= '<a href="javascript:';
	/* reset day */
	if ( in_array( 'day', $params['objects'] ))
	  $html .= $b.'_day.value=0;'; 
	/* reset month */
	if ( in_array( 'month', $params['objects'] ))
	  $html .= $b.'_month.options.selectedIndex=0;';
	/* reset year */
	if ( in_array( 'year', $params['objects'] )) 
	  $html .= $b.'_year.value=0;'; 
	/* reset hours */
	if ( in_array( 'hours', $params['objects'] )) 
	  $html .= $b.'_hours.value=0;'; 
	/* reset minutes */
	if ( in_array( 'minutes', $params['objects'] ))
	  $html .= $b.'_minutes.value=0;'; 
	/* reset seconds */
	if ( in_array( 'seconds', $params['objects'] )) 
	  $html .= $b.'_seconds.value=0;'; 
	$html .= 'void(0);">';
	/* reset image */
	if ( isset ( $params['buttons']['reset']['std'] ) ) {
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

  /*
   * display file input form item
   * @param string $name the form item name
   * @param string $actual the actual value
   * @param array $buttons the button descriptions to add
   * @return string
   * @access public
   */
  function display_fileInput($file='file',
			     $default='',
			     $buttons=null) {
    global $camyks;

    /* build param list */
    $params = array('id'=>'', 'name'=>'', 'default'=>'', 'class'=>'', 'style'=>'', 'onchange'=>'', 'onfocus'=>'', 'onblur'=>'', 'disabled'=>'', 'tabIndex'=>-1, 'buttons'=>null, 'language'=>'', 'accept'=>'');
    
    /* check header params */
    if ( is_array($file)) {
      $params = array_merge($params, $file);
    } else {
      $params['name'] = $file;
      if (isset($default))
	$params['default'] = $default;
      if (isset($buttons))
	$params['buttons'] = $buttons;
    }
    
    /* check object params */
    $n = $params['name'].($params['language']?'_'.$params['language']:'');
    if ( $params['default'] === '' and isset($this->object)) {
      $params['default'] = isset($this->object->vars[$n])?$this->object->vars[$n]:'';
    }
        
    /* check parent params */
    if ($params['buttons'] === null) {
      if (isset($this->parent))
	    $params['buttons'] = $this->parent->get_fileInputButtons();
      elseif(isset($this->object->_libParent))
	    $params['buttons'] = $this->object->_libParent->get_fileInputButtons();
    }  
   
    /* build file input element */
    $html = '<input type="file" name="'.$n.'"';
    if ($this->tabIndex>-1 or $params['tabIndex'] != -1)
      $html .= ' '.$this->get_tabIndex(true, $params['tabIndex']);
    if ($params['class'] != '')
      $html .= ' class="'.$params['class'].'"';
    if ( $params['onchange'] != '')
      $html .= ' onchange="'.$params['onchange'].'"';
    if ( $params['accept'] != '')
      $html .= ' accept="'.$params['accept'].'"';
    $html .= ' /> ';
    $html .= '<input type="hidden" name="'.$n.'_deletefile" value="0" />';

    /* check for file infos */
    if ( $params['default'] === false) {
    	/* do not write anything */
    } elseif ( $params['default'] == '' ) {
      $html .= $camyks->get_translation('file_nofile');
    } else {
      $file = new FSFile( $params['default'] );
      $html .= '<span id="'.$n.'_filedesc">';
      $html .= $camyks->get_translation('file_filetype', strtoupper($file->ext));
      $html .= ' ';
      
      foreach ($params['buttons'] as $name => $button) {      
        
        if ( $name == 'view') {
          /* check view button */
          if ( $file->type == 'image' and isset( $button['std'])) {
	        $html .= '&nbsp;<a href="'.$params['default'].'" target="_blank">';
	        $html .= '<img src="'.$button['std'].'" class="fileInputButton"';
	        $html .= ' alt="'.$button['title'].'" border="0"';
	        $html .= ' onmouseover="this.src=\''.$button['ovr'].'\';"';
	        $html .= ' onmouseout="this.src=\''.$button['std'].'\';"/>';
	        $html .= '</a>';
	      }
	    } elseif ( $name == 'listen') {
	      if ($file->type == 'audio' and isset( $button['std'])) {
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
           if (isset($params['buttons']['delete']['std'])){
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

  /*
   * build and return select input
   * @param mixed $select
   * @param array $values
   * @param mixed $default
   * @return string
   * @access public
   */
  function display_selectInput($select, $values=null, $default=null) {
    global $camyks;
    /* build param list */
    $params = array('id'=>'', 'name'=>'', 'values'=>array(), 'default'=>'', 'class'=>'inputs', 'style'=>'', 'disabled'=>'', 'onchange'=>'', 'tabIndex'=>-1, 'onfocus'=>'', 'onblur'=>'', 'language'=>'', 'hasEmptyFirstOption'=>false,
    'blocId'=>'');

    /* check header params */
    if ( is_array($select) ) {
      $params = array_merge($params, $select);
    } else {
      $params['name'] = $select;
      if (isset($values))
	$params['values'] = $values;
      if (isset($default))
	$params['default'] = $default;
    }

    /* check object params */
    if ( $params['default'] === '' and isset($this->object)) {
      $n = $params['name']. ($params['language']?'_'.$params['language']:'');
      $params['default'] = isset($this->object->vars[$n])?$this->object->vars[$n]:'';
    }
    
    /* check for first empty item */
    if ( $params['hasEmptyFirstOption'] === true )
    	$params['values'] = array(''=>' ') + $params['values'];
    elseif ( is_array($params['hasEmptyFirstOption']))
        $params['values'] = $params['hasEmptyFirstOption']+ $params['values'];
    elseif ( $params['hasEmptyFirstOption'] !== false)
    	$params['values'] = array(''=>$params['hasEmptyFirstOption']) + $params['values'];
        
    /* build select header */
    $html = '';
    if ($camyks->theme->useEnhancedSelectInputs == true or $params['blocId'] != '') {
      $addBloc = true;
      $html = '<div class="'.$params['class'].'"';
      if ( $params['blocId'] != '')  $html.= ' id="'.$params['blocId'].'"';
      $html .= '>';
    } else {
      $addBloc = false;
    }
      
    $html .= '<select';
    if ($params['language'] == '' )
      $html .= ' name="'.$params['name'].'"';
    else
      $html .= ' name="'.$params['name'].'_'.$params['language'].'"';
    if ( $params['id'] != '' )
      $html .= ' id="'.$params['id'].'"';
    if ( $params['class'] != '' )
      $html .= ' class="'.$params['class'].'"';
    if ( $params['style'] != '')
      $html .= ' style="'.$params['style'].'"';
    if ( $params['onchange'] != '')
      $html .= ' onchange="'.$params['onchange'].'"';
    if ( $params['onfocus'] != '')
      $html .= ' onfocus="'.$params['onfocus'].'"';
    if ( $params['onblur'] != '')
      $html .= ' onblur="'.$params['onblur'].'"';
    if ( $params['disabled'] != '')
      $html .= ' disabled="disabled"';
    if ($this->tabIndex>-1 or $params['tabIndex'] != -1)
      $html .= ' '.$this->get_tabIndex(true, $params['tabIndex']);
    $html .= '>' . "\n";
    
    /* add option items */
    foreach ( $params['values'] as $name => $value ) {
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
  
  /*
   * build and return boolean select input
   * @param mixed $select
   * @param mixed $default
   * @return string
   * @access public
   */
  function display_booleanSelectInput($select, $default=null) {
    global $camyks;
    /* build param list */
    $params = array('name'=>'', 'values'=>array(0=>$camyks->get_translation('no'), 1=>$camyks->get_translation('yes')), 'default'=>'');
    
    /* check header params */
    if ( is_array($select) ) {
      $params = array_merge($params, $select);
    } else {
      $params['name'] = $select;
      if (isset($default))
	$params['default'] = $default;
    }

    /* build display */
    return $this->display_selectInput($params);
  }

  /*
   * build and return country select input
   * @param mixed $select
   * @param mixed $default
   * @return string
   * @access public
   */
  function display_countrySelectInput($select=array(), $default=null) {
    global $camyks;
    /* build param list */
    $params = array('name'=>'country', 'default'=>'', 'highlighted'=>array(), 'shortlist'=>array(), 'territories'=>1, 'highlight_separator'=>'', 'language'=>'', 'hasEmptyFirstOption'=>false);
   
    /* check header params */
    if ( is_array($select) ) {
      $params = array_merge($params, $select);
    } else {
      $params['name'] = $select;
      if (isset($default))
	$params['default'] = $default;
    }
    
    /* check object params */
    $n = $params['name'].($params['language']?'_'.$params['language']:'');
    if ( $params['default'] == '' and isset($this->object)) {
      $params['default'] = isset($this->object->vars[$n])?$this->object->vars[$n]:'';
    }
    
    /* load country list */
    $countries = countries_getTitleList(array('territories'=>$params['territories'],
        'shortlist'=>$params['shortlist']));

    /* check for highlighted countries */
    if ( is_array($params['highlighted']) and count($params['highlighted'])>0) {
      $hc = array();
      foreach ($params['highlighted'] as $code) {
	    if (isset($countries[$code])) {
	      $hc[$code] = $countries[$code];
	      unset($countries[$code]);
	    }
      }
      if ( $params['highlight_separator'] != '' )
	    $hc[''] = array('value'=>$params['highlight_separator'], 'disabled'=>'disabled');
      $countries = array_merge($hc,$countries);
    }
    
    /* update params value */
    $params['values'] = $countries;

    /* build display */
    return $this->display_selectInput($params);
  }
  
  /*
   * build and return phone prefix select input
   * @param mixed $select
   * @param mixed $default
   * @return string
   * @access public
   */
  function display_phonePrefixSelectInput($select=array(), $default=null) {
    global $camyks;
    /* build param list */
    $params = array('name'=>'phonePrefix', 'default'=>'', 'highlighted'=>array(), 'shortList'=>array(), 'territories'=>1, 'highlight_separator'=>'', 'language'=>'', 'hasEmptyFirstOption'=>false, 'display_country'=>false, 'display_plus'=>false, 'display_zero'=>false, 'value'=>'countryCode', 'class'=>'sinputs');
   
    /* check header params */
    if ( is_array($select) ) {
      $params = array_merge($params, $select);
    } else {
      $params['name'] = $select;
      if (isset($default))
	    $params['default'] = $default;
    }
    
    /* check object params */
    $n = $params['name'].($params['language']?'_'.$params['language']:'');
    if ( $params['default'] == '' and isset($this->object)) {
      $params['default'] = isset($this->object->vars[$n])?$this->object->vars[$n]:'';
    }
    
    /* load country list */
    $prefixes = countries_getPhonePrefixes();
    
    $countries = countries_getTitleList(array(
        'territories'=>$params['territories'],
        'shortlist'=>$params['shortList']));
    
    $list = array();

    /* check for highlighted countries */
    if ( is_array($params['highlighted']) and count($params['highlighted'])>0) {
      $hc = array();
      foreach ($params['highlighted'] as $code) {
	    if (isset($prefixes[$code])) {
	      $hc[$code] = $prefixes[$code];
	      unset($prefixes[$code]);
	    }
      }
      if ( $params['highlight_separator'] != '' )
	    $hc[''] = array('value'=>$params['highlight_separator'], 'disabled'=>'disabled');
      $prefixes = array_merge($hc, $prefixes);
    }
    
    foreach ($prefixes as $code => $value) {
      if ($code == '' or count($params['shortList']) == 0 or in_array($code, $params['shortList'])) {
        if ( $code != '') {
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

  /*
   * build and return civility select input
   * @param mixed $select
   * @param mixed $default
   * @return string
   * @access public
   */
  function display_civilitySelectInput($select, $default=null) {
    global $camyks;
    /* build param list */
    $params = array('name'=>'', 'default'=>'', 'class'=>'vsinput');
    $params['values'] = array();
    $civilities = array('mr', 'mrs', 'ms', 'sir', 'dr', 'pr', 'me');
    foreach( $civilities as $c) {
      if (($v = $camyks->get_translation('civility_'.$c))!='')
	$params['values'][$c] = $v;
    }

    /* check header params */
    if ( is_array($select) ) {
      $params = array_merge($params, $select);
    } else {
      $params['name'] = $select;
      if (isset($default))
	    $params['default'] = $default;
    }

    /* build display */
    return $this->display_selectInput($params);
  }

  /*
   * build and return text input
   * @param mixed $input
   * @param string default
   * @return string
   * @access private
   */
  function display_textInput($input, $default=null) {
    /* build param list */
    $params = array('id'=>'', 'name'=>'', 'default'=>'', 'class'=>'inputs', 'style'=>'', 'onchange'=>'', 'onfocus'=>'', 'onblur'=>'', 'oninput'=>'',  'disabled'=>'', 'maxlength'=>0, 'size'=>0, 'language'=>'', 'onkeydown'=>'', 'list'=>'', 'autocomplete'=>'', 'placeholder'=>'', 'tabIndex'=>-1);

    /* check header params */
    if ( is_array($input) ) {
      $params = array_merge($params, $input);
    } else {
      $params['name'] = $input;
      if (isset($default))
	    $params['default'] = $default;
    }
    
    /* check object params */
    if (isset($this->object)) {
      /* check default value */
      if ($params['default'] === '') {
	    $v = $params['name'].($params['language']==''?'':'_'.$params['language']);
	    $params['default'] = isset($this->object->vars[$v])?$this->object->vars[$v]:'';
      }
      
      /* check maxlength value */
      if ( $params['maxlength'] == 0 )
	    if ( isset($this->object->_libItems[$params['name']]->datatype) 
	      and in_array($this->object->_libItems[$params['name']]->datatype, array('etext', 'text'))
	      and $this->object->_libItems[$params['name']]->datadesc2 > 0)
	        $params['maxlength'] = $this->object->_libItems[$params['name']]->datadesc2;
	else
	  $params['maxlength'] = 32;
    }
    
    /* build input */
    $html = '<input type="text"';
    if ($params['language'] == '' )
      $html .= ' name="'.$params['name'].'"';
    else
      $html .= ' name="'.$params['name'].'_'.$params['language'].'"';
    $html .= ' value="'.htmlentities($params['default'], ENT_COMPAT, 'UTF-8').'"';
    $html .= ' maxlength="'.$params['maxlength'].'"';
    if ( $params['size'] > 0 ) 
      $html .= ' size="'.$params['size'].'"';
    if ( $params['id'] != '' )
      $html .= ' id="'.$params['id'].'"';
    if ( $params['class'] != '' )
      $html .= ' class="'.$params['class'].'"';
    if ( $params['style'] != '')
      $html .= ' style="'.$params['style'].'"';
    if ( $params['onchange'] != '')
      $html .= ' onchange="'.$params['onchange'].'"';
    if ( $params['onkeydown'] != '')
      $html .= ' onkeydown="'.$params['onkeydown'].'"';
    if ( $params['onfocus'] != '')
      $html .= ' onfocus="'.$params['onfocus'].'"';
    if ( $params['onblur'] != '')
      $html .= ' onblur="'.$params['onblur'].'"';
    if ( $params['oninput'] != '')
      $html .= ' oninput="'.$params['oninput'].'"';
    if ( $params['disabled'] != '')
      $html .= ' disabled="disabled"';
    if ( $params['list'] != '')
      $html .= ' list="'.$params['list'].'"';
    if ( $params['placeholder'] != '')
      $html .= ' placeholder="'.$params['placeholder'].'"';
    if ( $params['autocomplete'] != '')
      $html .= ' autocomplete="'.$params['autocomplete'].'"';
    if ($this->tabIndex>-1 or $params['tabIndex'] != -1)
      $html .= ' '.$this->get_tabIndex(true, $params['tabIndex']);
    $html .= ' />';
    return $html;
  }

  /*
   * build and return textarea input
   * @param mixed $input
   * @param string default
   * @return string
   * @access private
   */
  function display_textareaInput($input, $default=null) {
    /* build param list */
    $params = array('id'=>'', 'name'=>'', 'default'=>'', 'class'=>'vlinputs', 'style'=>'', 'onchange'=>'', 'onfocus'=>'', 'onblur'=>'', 'onkeyup'=>'', 'oninput'=>'', 'disabled'=>'', 'maxlength'=>0, 'language'=>'', 'cols'=>'40', 'rows'=>'4', 'placeholder'=>'', 'tabIndex'=>-1);

    /* check header params */
    if ( is_array($input) ) {
      $params = array_merge($params, $input);
    } else {
      $params['name'] = $input;
      if (isset($default))
	$params['default'] = $default;
    }

    /* check object params */
    if ($params['default'] == '') {
      $v = $params['name'].($params['language']==''?'':'_'.$params['language']);
      if ($this->object != null and isset($this->object->vars[$v]))
	$params['default'] = $this->object!=null?$this->object->vars[$v]:'';
    }

    /* build input */
    $html = '<textarea';
    if ($params['language'] == '' )
      $html .= ' name="'.$params['name'].'"';
    else
      $html .= ' name="'.$params['name'].'_'.$params['language'].'"';
    $html .= ' cols="'.$params['cols'].'"';
    $html .= ' rows="'.$params['rows'].'"';
    if ( $params['id'] != '' )
      $html .= ' id="'.$params['id'].'"';
    if ( $params['class'] != '' )
      $html .= ' class="'.$params['class'].'"';
    if ( $params['style'] != '')
      $html .= ' style="'.$params['style'].'"';
    if ( $params['onchange'] != '')
      $html .= ' onchange="'.$params['onchange'].'"';
    if ( $params['onfocus'] != '')
      $html .= ' onfocus="'.$params['onfocus'].'"';
    if ( $params['onblur'] != '')
      $html .= ' onblur="'.$params['onblur'].'"';
    if ( $params['onkeyup'] != '')
      $html .= ' onkeyup="'.$params['onkeyup'].'"';
    if ( $params['oninput'] != '')
      $html .= ' oninput="'.$params['oninput'].'"';
    if ( $params['disabled'] != '')
      $html .= ' disabled="disabled"';
    if ( $params['placeholder'] != '')
      $html .= ' placeholder="'.$params['placeholder'].'"';
    if ($this->tabIndex>-1 or $params['tabIndex'] != -1)
      $html .= ' '.$this->get_tabIndex(true, $params['tabIndex']);
    $html .= ' >';
    $html .= string_text2html($params['default']);
    $html .= '</textarea>';
    return $html;
  }
  
  /*
   * build and return password input
   * @param mixed $input
   * @param string default
   * @return string
   * @access private
   */
  function display_passwordInput($input, $default=null) {
    /* build param list */
    $params = array('id'=>'', 'name'=>'', 'default'=>'', 'class'=>'inputs', 'style'=>'', 'onchange'=>'', 'onfocus'=>'', 'onblur'=>'', 'disabled'=>'', 'maxlength'=>0, 'size'=>0, 'language'=>'', 'placeholder'=>'', 'tabIndex'=>-1);

    /* check header params */
    if ( is_array($input) ) {
      $params = array_merge($params, $input);
    } else {
      $params['name'] = $input;
      if (isset($default))
	$params['default'] = $default;
    }

    /* check object params */
    if (isset($this->object)) {
      /* check default value */
      if ($params['default'] == '') {
	$v = $params['name'].($params['language']==''?'':'_'.$params['language']);
	$params['default'] = isset($this->object->vars[$v])?$this->object->vars[$v]:'';
      }
      /* check maxlength value */
      if ( $params['maxlength'] == 0 )
	if ( isset($this->object->_libItems[$params['name']]->datatype) 
	     and in_array($this->object->_libItems[$params['name']]->datatype, array('etext', 'text'))
	     and $this->object->_libItems[$params['name']]->datadesc2 > 0)
	  $params['maxlength'] = $this->object->_libItems[$params['name']]->datadesc2;
	else
	  $params['maxlength'] = 32;
    }

    /* build input */
    $html = '<input type="password"';
    if ($params['language'] == '' )
      $html .= ' name="'.$params['name'].'"';
    else
      $html .= ' name="'.$params['name'].'_'.$params['language'].'"';
    $html .= ' value="'.$params['default'].'"';
    $html .= ' maxlength="'.$params['maxlength'].'"';
    if ( $params['size'] > 0 ) 
      $html .= ' size="'.$params['size'].'"';
    if ( $params['id'] != '' )
      $html .= ' id="'.$params['id'].'"';
    if ( $params['class'] != '' )
      $html .= ' class="'.$params['class'].'"';
    if ( $params['style'] != '')
      $html .= ' style="'.$params['style'].'"';
    if ( $params['onchange'] != '')
      $html .= ' onchange="'.$params['onchange'].'"';
    if ( $params['onfocus'] != '')
      $html .= ' onfocus="'.$params['onfocus'].'"';
    if ( $params['onblur'] != '')
      $html .= ' onblur="'.$params['onblur'].'"';
    if ( $params['disabled'] != '')
      $html .= ' disabled="disabled"';
    if ( $params['placeholder'] != '')
      $html .= ' placeholder="'.$params['placeholder'].'"';
    if ($this->tabIndex>-1 or $params['tabIndex'] != -1)
      $html .= ' '.$this->get_tabIndex(true, $params['tabIndex']);
    $html .= ' />';
    return $html;
  }
  
  /*
   * build and return checkbox input
   * @param mixed $input
   * @param string default
   * @return string
   * @access private
   */
  function display_checkboxInput($input, $default=null) {
    /* build param list */
    $params = array('id'=>'', 'name'=>'', 'default'=>'', 'class'=>'', 'style'=>'', 'onchange'=>'', 'onfocus'=>'', 'onblur'=>'', 'disabled'=>'', 'maxlength'=>0, 'size'=>0, 'language'=>'', 'value'=>'', 'tabIndex'=>-1, 'label'=>'', 'labelClass'=>'', 'labelStyle'=>'', 'multiValues'=>false);

    /* check header params */
    if ( is_array($input) ) {
      $params = array_merge($params, $input);
    } else {
      $params['name'] = $input;
      if (isset($default))
	$params['default'] = $default;
    }

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
    if ($params['language'] == '' )
      $html .= ' name="'.$params['name'];
    else
      $html .= ' name="'.$params['name'].'_'.$params['language'];
    if ($params['multiValues']===true)
      $html .= '[]';
    $html .= '"';
    if ( $params['id'] != '' )
      $html .= ' id="'.$params['id'].'"';
    $html .= ' value="'.$params['value'].'"';
    if ( $params['class'] != '' )
      $html .= ' class="'.$params['class'].'"';
    if ( $params['style'] != '')
      $html .= ' style="'.$params['style'].'"';
    if ( $params['onchange'] != '')
      $html .= ' onchange="'.$params['onchange'].'"';
    if ( $params['onfocus'] != '')
      $html .= ' onfocus="'.$params['onfocus'].'"';
    if ( $params['onblur'] != '')
      $html .= ' onblur="'.$params['onblur'].'"';
    if ( $params['disabled'] != '')
      $html .= ' disabled="disabled"';
    if ($params['default'] === $params['value'])
      $html .= ' checked="checked"';
    elseif ($params['multiValues'] === true and is_array($params['default'])
        and in_array($params['value'], $params['default']))
      $html .= ' checked="checked"';    
    
    if ($this->tabIndex>-1 or $params['tabIndex'] != -1)
      $html .= ' '.$this->get_tabIndex(true, $params['tabIndex']);
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
  
    /*
   * build and return radio input
   * @param mixed $input
   * @param string default
   * @return string
   * @access private
   */
  function display_radioInput($input, $default=null) {
    /* build param list */
    $params = array('id'=>'', 'name'=>'', 'default'=>'', 'class'=>'', 'style'=>'', 'onchange'=>'', 'onfocus'=>'', 'onblur'=>'', 'disabled'=>'', 'language'=>'', 'value'=>'', 'tabIndex'=>-1, 'label'=>'', 'labelClass'=>'', 'labelStyle'=>'');

    /* check header params */
    if ( is_array($input) ) {
      $params = array_merge($params, $input);
    } else {
      $params['name'] = $input;
      if (isset($default))
	    $params['default'] = $default;
    }

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
    if ($params['language'] == '' )
      $html .= ' name="'.$params['name'].'"';
    else
      $html .= ' name="'.$params['name'].'_'.$params['language'].'"';
    if ( $params['id'] != '' )
      $html .= ' id="'.$params['id'].'"';    
    
    $html .= ' value="'.$params['value'].'"';
    if ( $params['class'] != '' )
      $html .= ' class="'.$params['class'].'"';
    if ( $params['style'] != '')
      $html .= ' style="'.$params['style'].'"';
    if ( $params['onchange'] != '')
      $html .= ' onchange="'.$params['onchange'].'"';
    if ( $params['onfocus'] != '')
      $html .= ' onfocus="'.$params['onfocus'].'"';
    if ( $params['onblur'] != '')
      $html .= ' onblur="'.$params['onblur'].'"';
    if ( $params['disabled'] != '')
      $html .= ' disabled="disabled"';
    if ( $params['default'] === $params['value'])
      $html .= ' checked="checked"';
    if ($this->tabIndex>-1 or $params['tabIndex'] != -1)
      $html .= ' '.$this->get_tabIndex(true, $params['tabIndex']);
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
  
  /* 
   * return hidden submit link for "enter" pressed validation
   * @return string
   * @access public
   */
  function display_hiddenSubmit() {
    return '<input type="submit" style="position: absolute; left: -9999px; width: 1px; height: 1px;" tabindex="-1" />';
  }

  /*
   * return current form html submit link
   * @return string
   * @access public
   */
  function get_HTMLSubmitLink() {
    return 'javascript:document.'.$this->name.'.submit();';
  }

  /*
   * return current form javascript submit link
   * @return string
   * @access public
   */
  function get_JSSubmitLink() {
    return 'document.'.$this->name.'.submit();';
  }

  /*
   * start tabIndex
   * @return void
   * @access public
   */
  function start_tabIndex() {
    $this->tabIndex = 0;
  }

  /*
   * return tabIndex value or form value
   * @param boolean $full indicate if method return html source
   * @param integer $index indicate forced value
   * @return mixed
   * @access public
   */
  function get_tabIndex( $full=false, $index=-1 ) {
    if ( $index ) {
      if ($this->tabIndex < $index)
        $this->tabIndex = $index;
    } elseif ( $this->tabIndex == -1 ) {
      $this->tabIndex = 1;
      $index = $this->tabIndex;
    } else {
      $this->tabIndex++;
      $index = $this->tabIndex;
    }

    if ( $full ) {
      return ' tabindex="'.$index.'"';
    }
    return $index;
  }
}

/* 
 * hidden input object
 */
class HTMLForm_hidden {
  /* object name */
  var $name;
  /* object value */
  var $value;
  
  /* 
   * constructor
   * @param string $name the hidden object name
   * @param string $value the hidden object value
   * @return void
   * @access public
   */
  function HTMLForm_hidden ( $name, $value ) {
    $this->name = $name;
    $this->value = $value;	
  }
  
  /* methods */
  /*
   * return input object html
   * @return string
   * @access public
   */
  function display ( ) {
    return '<input type="hidden" name="'.$this->name.'" value="'.$this->value.'" />';
  }
}
?>