<?php
/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a2
 * Object Version       : 1.0b1
 * Object Type          : Plugin / Input Engine
 * Create Date		: Sep 2008
 * Last Modif Date	: Oct 2008
 * History :
 * * 08-10-03 : Initial Files
 * 
 * AdminItemListViewer input : Display generic list of items
 */

class AdminItemListViewer extends Input {
  /* variables */
  var $params;
  
  var $selectionValues;
  var $sortValues;
  var $icons;
  
  /* 
   * constructor
   * @param string $path_type
   */
  function AdminItemListViewer ( $path_type ) {
    parent::Input('AdminItemListViewer', $path_type);
    /* set plugin version */
    $this->version = '1.0b1';
    /* set plugin package */
    $this->plugin_package = 'Default';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    
    /* initialise plugin variables */
    $this->valide = true; 
    $this->selectionValues = array();
    $this->sortValues = array('column'=>'id', 'way'=>'');
    $this->icons = array();
    $this->params = array();
  }
  
  /* overwrite Input methods */

  /*
   * initialise input
   * @param array $params
   * @return void
   * @access public
   */
  function initialise($params=array()) {
    global $camyks;

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
  
  /*
   * display input
   * @param string $panel
   * @return void
   * @access public
   */
  function display ($panel='list') {
    /* update layout */
    if ($this->valide) 
      $this->selected_layout = 'input_'.$panel.'.html.inc';
    else
      $this->selected_layout = 'input_.html.inc';
    
    /* generic input display */
    parent::display();
  }
  
  /* specific tool methods */
  
  /*
   * set all params
   * @param array $params
   * @return void
   * @access public
   */
  function set_params($params=array()) {
    $this->params = $params;
  }
  
  /*
   * add a head param
   * @param string $type
   * @param array $param
   * @return void
   * @access public
   */
  function add_param($type, $name, $value) {
    if (!isset($type))
      $this->params[$type] = array();
    $this->params[$type][$name] = $value;
  }
  
  /*
   * check main params
   * @return void
   * @access private
   */
  function check_params() {
    global $camyks;
    /* default params */
    $defaultParams = array('name'=>'genViewer', 
			   'useSession'=>false, 
			   'object'=>null, 
			   'language' => false,
			   'itemsbypage' => $camyks->get_confValue('admin_itemsbypage', 10),
			   'theme' => &$camyks->theme,
			   'baseurl'=>'',
			   'sort'=>array('allowed'=>false),
			   'headselectors'=>array(),
			   'headcolumns'=>2,
			   'headhiddens'=>array(),
			   'extraparams'=>array(),
			   'listcolumns'=>array(),
			   'listlinks'=>array());
    
    /* merge default params and parent's params */
    $this->params = array_merge($defaultParams, $this->params);
    
    /* check object */
    if (!isset($this->params['object']))
      return false;
    if(!isset($this->params['object']->object_type) or  $this->params['object']->object_type!= 'ModuleLibrary')
      return false;
    
    /* check basurl param */
    if ( !isset($this->params['baseurl']))
      if ( isset($this->params['object']) and isset($this->params['object']->_libParent))
        $this->params['baseurl'] = $camyks->get_adminLink($this->params['object']->_libParent->name);
      else
        $this->params['baseurl'] = $camyks->get_adminLink();
      
    /* check sorting values */
    if ( !isset($this->params['sort']['allowed']))
      $this->params['sort']['allowed'] = false;
    if ($this->params['sort']['allowed'] === true and !isset($this->params['sort']['default']))
      $this->params['sort']['default'] = 'id';
    if ($this->params['sort']['allowed'] === true and !isset($this->params['sort']['defaultway']))
      $this->params['sort']['defaultway'] = '';
    
    return true;
  }
  
  /*
   * get header selector value
   * @param string $name
   * @param array $params
   * @return mixed
   * @access private
   */
  function get_selectorValue($name, $params) {
    if ( !isset($params['itemtype']))
      return null;
  
    switch($params['itemtype']){ 
    case 'page' : 
      return (int)$_REQUEST[$this->params['name'].'_form'.$name]-1;
    default :
      if (!isset($params['datatype']))
        $params['datatype'] = 'string';
      switch($params['datatype']) {
      case 'int':
      case 'integer':
        return (int)$_REQUEST[$this->params['name'].'_form'.$name];
      case 'string':
        return $_REQUEST[$this->params['name'].'_form'.$name];
      }
    }
  }
    
  /*
   * get header selector default value
   * @param string $name
   * @param array $params
   * @return mixed
   * @access private
   */
  function get_selectorDefaultValue($name, $params) {
    if ( !isset($params['itemtype']))
      return null;
    
    if ( isset($params['default']))
      return $params['default'];
  
    switch($params['itemtype']){ 
    case 'page' : 
      return 0;
    default :
      if (!isset($params['datatype']))
        $params['datatype'] = 'string';
      switch($params['datatype']) {
      case 'int':
      case 'integer':
        return 0;
      case 'string':
        return '';
      }
    }
  }
  
  /*
   * build every params needed into the display panels
   * @return void
   * @access private
   */
  function build_panelsData() {
    global $camyks;
    
    /* prepare default vars value */
    $search = '';
    $from = -1;
    $count = -1;
    
    /* add form and script */
    if( count($this->params['headselectors']) > 0 or $this->params['sort']['allowed'] === true ) {
      /* build form object */
      $this->selectorForm = new HTMLForm($this->params['name'].'_form',
        $this->params['baseurl'], 'POST');

      /* add hiddens */
      foreach($this->params['headhiddens'] as $hiddenName => $hiddenValue)
	$this->selectorForm->add_hidden($hiddenName, $hiddenValue);
      
      /* add javascript */
      $this->add_JSFile('adminitemlistviewer.js');
      $this->add_JSScript('var '.$this->params['name'].' = new AdminItemListViewer("'.$this->params['name'].'");');
      $this->add_JSLoadScript($this->params['name'].'.initialise();');
    } else {
      $this->selectorForm = false;
    }
    
    /* check sorting  values */
    if ( $this->params['sort']['allowed'] === true ) {
      /* get sort column value */
      if ( isset($_REQUEST[$this->params['name'].'_sortcolumn']) ) {
        $value = $_REQUEST[$this->params['name'].'_sortcolumn'];
        if ( $this->params['useSession'] == true )
          $camyks->set_sessionValue($this->params['name'].'_sortcolumn', $value);
      } elseif ( $this->params['useSession'] == true )
         $value = $camyks->get_sessionValue($this->params['name'].'_sortcolumn', $this->params['sort']['default']);
      else
        $value = $this->params['sort']['default'];
      $this->sortValues['column'] = $value;
      $this->selectorForm->add_hidden($this->params['name'].'_sortcolumn', $value);
      
      /* get sort column way */
      if ( isset($_REQUEST[$this->params['name'].'_sortway']) ) {
        $value = $_REQUEST[$this->params['name'].'_sortway'];
        if ( $this->params['useSession'] == true )
          $camyks->set_sessionValue($this->params['name'].'_sortway', $value);
      } elseif ( $this->params['useSession'] == true )
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
    if( count($this->params['headselectors']) > 0 ) {
      /* get header or default values */
      $refresh = false;
      foreach( $this->params['headselectors'] as $name => $selector ) {
        /* get value */
        if ( isset($_REQUEST[$this->params['name'].'_form'.$name]) ) {
          $value = $this->get_selectorValue($name, $selector);
          if ( $this->params['useSession'] == true )
            $camyks->set_sessionValue($this->params['name'].'_form'.$name, $value);
          $refresh = true;
        } elseif ( $this->params['useSession'] == true )
           $value = $camyks->get_sessionValue($this->params['name'].'_form'.$name, $this->get_selectorDefaultValue($name, $selector));
        else
          $value = $this->get_selectorDefaultValue( $name, $selector );
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
      $search = $this->params['object']->build_SQLCondition( $this->selectionValues );
      $objcount = $this->params['object']->get_objectCount($search, $this->params['language']);
      
      /* check for specific pager */
      if ( isset( $this->params['headselectors']['page']) and $this->params['headselectors']['page']['itemtype'] == 'page' ) {
        
        $this->params['headselectors']['page']['maxpages'] = ceil( $objcount/$this->params['itemsbypage']);
        /* update selection value */
        $this->selectionValues['page'] = min( max(0, $this->selectionValues['page']), $this->params['headselectors']['page']['maxpages']-1);
        $from = $this->selectionValues['page']*$this->params['itemsbypage'];
        $count = $this->params['itemsbypage'];
      }
    } else {
      /* initialise list values */
      $search = $this->params['object']->build_SQLCondition( $this->selectionValues );
      $objcount = $this->params['object']->get_objectCount($search, $this->params['language']);
    }
    
    /* save object count */
    $this->objectCount = $objcount;

    /* load object list */
    $this->objectList = $this->params['object']->get_objectList($this->params['language'], $search, $from, $count, $this->sortValues['column'], $this->sortValues['way']);  
  }
  
  /*
   * build list data
   * @return void
   * @access private
   */
  function build_listData() {
    global $global_theme_picts_items;
  
    $this->preRenders = array();
    if (count($this->objectList) === 0)
      return;
      
    foreach($this->params['listcolumns'] as $name => $column ) {
      /* check condition */
      if ( isset($column['condition'])) {
	if($column['condition']=='' or !method_exists($this->params['object'], $column['condition'])) {
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
          if ( isset($column['icon_over']) ) {
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
        switch( $column['mode'] ) {
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
	if (!isset($column['method']) 
	    or $column['method']=='' 
	    or !method_exists($this->params['object'], $column['method']))
	  $this->params['listcolumns'][$name]['columntype'] = 'empty';
	break;
      case 'empty':
	/* columntype == empty */
	break;
      }
    }
  }
  
  /*
   * return object item display
   * @param object $object
   * @param string $name
   * @param array $column
   * @param integer $line
   * @return string
   * @access private
   */
  function get_itemDisplay($object, $name, $column, $line) {
    global $camyks;
    
    /* check condition */
    if (isset($column['condition']) 
	and call_user_func(array(&$object, $column['condition'])) === false )
      return '';

    /* return item display */
    switch ( $column['columntype'] ) {
    case 'button':
      /* columntype == button */
      if (!isset($column['vars']))
        return vsprintf( $this->preRenders[$name], $object->id );
      else {
        $vars = array();
        foreach ($column['vars'] as $index=>$v ) {
	      if($v == 'id')
	        $vars[$index] = $object->id;
	      else
	        $vars[$index] = isset($object->vars[$v])?$object->vars[$v]:'';
	    }
	    return vsprintf($this->preRenders[$name], $vars);
      }
      break;
    case 'checkbox' : 
      /* columntype == checkbox */
      return vsprintf( $this->preRenders[$name], array($object->id, $line));
      break;
    case 'text':
      /* columntype == text */
      if (isset($column['maxlength']) and $column['maxlength']>0 )
		return string_getShortenedSentence($object->vars[$name], $column['maxlength']);
      return $object->vars[$name];
    case 'list':
      /* columntype == list */
      return isset($column['values'][$object->vars[$name]])?$column['values'][$object->vars[$name]]:'';
      break;
    case 'country':
      /* columntype == country */
      return language_getIcon($object->vars[$name]);
      break;
    case 'date':
      /* columntype == date */
      switch( $column['mode'] ) {  
      case 'long':
        return date_displayLongDate($object->vars[$name]);
        break;
      case 'longwithhour':
        return date_displayLongDateHour($object->vars[$name]);
        break;
      case 'longwithday':
        return date_displayLongDayDate($object->vars[$name]);
        break;
      case 'longwithdayandhour':
        return date_displayLongDayDateHour($object->vars[$name]);
        break;
      case 'short':
        return date_displayShortDate($object->vars[$name]);
        break;
      case 'shortwithhour':
        return date_displayShortDateHour($object->vars[$name]);
        break;
      case 'shortwithday':
        return date_displayShortDayDate($object->vars[$name]);
        break;
      case 'shortwithdayandhour':
        return date_displayShortDayDateHour($object->vars[$name]);
        break;
      case 'numeric':
        return date_displayNumericDate($object->vars[$name]);
        break;
      case 'numericwithhour':
      default:
	return date_displayNumericDateHour($object->vars[$name]);
	break;
      }
      break;
    case 'boolean':
      /* columntype == boolean */
      switch( $column['mode'] ) {
      case 'text':
        return $camyks->get_translation($object->vars[$name]?'yes':'no');
        break;
      case 'pict':
        return vsprintf( $this->preRenders[$name], $this->get_icon($object->vars[$name]?'valid':'empty'));
      break;
      case 'checkbox':
      default:
        return vsprintf( $this->preRenders[$name], $object->vars[$name]?' checked="checked"':'');
        break;
      }
      break;
    case 'specialtext' :
      /* columntype == specialtext */
      if(!isset($column['text']) or !isset($column['vars']))
	    return '';
      $vars = array();
      foreach ($column['vars'] as $index=>$v ) {
	    if($v == 'id')
	      $vars[$index] = $object->id;
	    else
	      $vars[$index] = isset($object->vars[$v])?$object->vars[$v]:'';
      }
      if (isset($column['maxlength']) and $column['maxlength']>0 )
	return string_getShortenedSentence(vsprintf($column['text'], $vars), $column['maxlength']);
      return vsprintf($column['text'], $vars);
    case 'method':
      /* columntype == method */
      $v = call_user_func(array(&$object, $column['method']));
      if (isset($column['maxlength']) and $column['maxlength']>0 )
        return string_getShortenedSentence($v, $column['maxlength']);
      return $v;
    }
    /* default value */
    return '';
  }
  
  /*
   * return generic icon url
   * @param string $icon
   * @param string $mode
   * @return string
   * @access private
   */
  function get_icon($icon, $mode='std') {
    if ( !isset( $this->icon[$icon.'_'.$mode] ))
      $this->icons[$icon.'_'.$mode] = $this->params['theme']->get_pictURL($icon, 12, $mode);
    return $this->icons[$icon.'_'.$mode];
  }
  
  /*
   * check if given column can be use as sort
   * @params string $column
   * @return boolean
   * @access private
   */
  function is_columnSortable($column='') {
    return (in_array($column, $this->params['object']->_libItemTypes['db']) or 
      in_array($column, $this->params['object']->_libItemTypes['dbl']));
  }

  /*
   * calculate and return list link button position
   * @param array $link
   * @return array
   * @access private
   */
  function get_listLinkColspans($link) {
    $cols = count($this->params['listcolumns']);
    $spans = array('firsts'=>0, 'title'=>$cols-1, 'lasts'=>0 );
  
    if (!isset($link['buttoncolumn']) and !isset($link['titlecolumn']))
      return $spans;
    
    $title = isset($link['titlecolumn']) ? $this->get_columnPosition($link['titlecolumn']) : 1;
    $button = isset($link['buttoncolumn']) ? $this->get_columnPosition($link['buttoncolumn']) : $cols;
    
    if ( $title >= $button )
      return $spans;
      
    $spans['firsts'] = $title-1;
    $spans['title'] = $button-$title;
    $spans['lasts'] = $cols-$button;
    
    return $spans;
  }
  
  /*
   * calculate and return column position
   * @param mixed $column
   * @return integer
   * @access private
   */
  function get_columnPosition($column) {
    /* check column type */
    if ( is_integer($column) )
      return $column;
    $cnt = 0;
    foreach($this->params['listcolumns'] as $n => $value ){
      $cnt++;
      if ( $n == $column )
        break;
    }
    return $cnt;
  }
}
?>