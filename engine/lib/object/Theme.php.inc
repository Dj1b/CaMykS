<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * Camyks Version	: 1.0b
 * Object Version	: 1.0
 * Object Type      : Engine / Object Library
 * Creation Date    : Jun 2005
 * Last Modif Date  : Oct 2017
 * History : 
 * 05-06-xx : Initial File
 * 08-01-07 : Themes are now full objects
 * 08-05-28 : Modify "LayeredMenu" management methods
 * 10-01-20 : Add "Left" & "Right" pict items
 * 16-02-16 : Touch icon support
 *
 * Theme object
 *
 * Theme element can be :
 * - simple bar ( content, button, item )
 * - box ( title, tabs bar, opencontent1, opencontent2, closecontent1, closecontent1, button bar ) 
 * - simple button
 * - layered menu
 */

/* global variables */
global $global_theme_picts_items, $global_theme_media_types;

$global_theme_picts_items = array();
$global_theme_picts_items['12'] = array( );
$global_theme_picts_items['12']['items'] = array('empty',
						 'cross',
						 'down',
						 'edit',
						 'file',
						 'left',
						 'menu',
						 'minus',
						 'notify',
						 'plus',
						 'right',
						 'square',
						 'target',
						 'text',
						 'up',
						 'valid',
						 'view', 
						 'action',
						 );
$global_theme_picts_items['12']['positions'] = array('std',
						     'ovr'); 
/* available style media */
$global_theme_media_types = array('tty',
				  'tv',
				  'projection',
				  'handheld',
				  'print',
				  'braille',
				  'aural',
				  '3d-glasses',
				  'all');


class Theme extends Plugin {
  /* variables */
  var $isLoaded;
  var $parts;
  var $autoBoxContent;
  
  /*
   * constructor
   * @param string $name
   * @param string $path_type ( camyks or site )
   */
  function Theme ( $name, $path_type ) {
    parent::Plugin( $name, 'theme', $path_type );
    /* is loaded default value  */
    $this->partsLoaded = false;
    
    /* init parts */
    $this->parts = array();
    
    /* define responsiveness of website */
    $this->responsiveStyles = array();
    
    /* define touch icons */
    $this->touchIcons = array();
    
    /* set autoBoxContent to default value */
    $this->autoBoxContent = 'Close';
    
    /* set useEnhancedSelectInputs to default value */
    $this->useEnhancedSelectInputs = false;
    
    /* check for responsive admin mode */
    $this->isAdminResponsive = false;
  }

  /* methods */
  
  
  /* 
   * initialise plugin
   * @return void
   * @access public
   */
  function initialise() {
    global $camyks;
    
    if ($camyks->mode == CAMYKS_MODE_ADMIN) {
      $this->initialise_adminMode();
    
    } else {
      /* add icons */
      foreach ($this->touchIcons as $icon) {
        $camyks->HTMLPage->add_link($icon['name'], $this->get_fileURL('img/touchIcons/'.$icon['url']), array('sizes'=>$icon['sizes']));
        if (isset($icon['default']) and $icon['default'] == 1) {
          if ($camyks->modules['Admin_ContentPage']->get_configValue('site_ogmeta') == 1)
            $camyks->HTMLPage->add_meta('og:image', $this->get_fileURL('img/touchIcons/'.$icon['url']), 'property');
        }
      }
      
      /* load styles */
      $this->get_main_css();
    }
  }
  
  /*
   * initialise admin mode
   * @return void
   * @access private
   */
  function initialise_adminMode() {
    global $camyks;
    
    if ($this->isAdminResponsive) {
      /* update page view port */
      $camyks->HTMLPage->add_meta('viewport', 'width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=0', 'name');
    }
    $this->add_styleFile('style.css');
    $this->add_styleFile('admin.css');
    $this->add_styleFile('editor.css');
    $this->get_parts();
  }

  /*
   * load theme parts
   * @return void
   * @access public
   */
  function get_parts() {
    global $camyks;
    
    if (!$this->partsLoaded) {
      /* get parts css */
      $this->add_styleFile('parts.css');
      /* get parts file */
      $this->load_file ('parts.php.inc');
      /* update partsLoaded check value */
      $this->partsLoaded = true; 
    }
  }

  /*
   * load theme parts as included file
   * @return void
   * @access public
   */
  function get_included_parts() {
    global $camyks;
    
    if (!$this->partsLoaded) {
      /* get parts css */
      if ($this->get_fileURL('css/parts.css') != '')
        $camyks->HTMLPage->add_styleIncludedFile($this->get_filePath('css/parts.css'));
      else
        $camyks->HTMLPage->add_styleIncludedFile($this->get_filePath('parts.css'));
        
      /* get parts file */
      $this->load_file ('parts.php.inc');
      
      /* update partsLoaded check value */
      $this->partsLoaded = true; 
    }
  }


  /*
   * send main css to camyks object
   * @return void
   * @access private
   */
  function get_main_css () {
    global $camyks, $global_theme_media_types;
    
    if ($camyks->get_confValue('enable_responsiveDesign') == 1) {
      /* update page view port */
      $camyks->HTMLPage->add_meta('viewport', 'width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=0', 'name');
      
      /* add styles */
      if (count($this->responsiveStyles) > 0) {
        foreach ($this->responsiveStyles as $style) {
          $this->add_styleFile($style['file'], $style['condition']);
          if ($style['default'])
            $this->add_styleFile($style['file'], $style['condition'], '(lt IE 9)&(!IEMobile)');
        }
      } else {
        $this->add_styleFile('style.css');
      }
    } else {
      $this->add_styleFile('style.css');
      $this->add_styleFile('editor.css');
    }
    
    /* alternate media styles */
    foreach( $global_theme_media_types as $media ) {
      if ($this->get_filePath($media.'.css', false) != false)
		$this->add_styleFile($media.'.css', $media );
    } 
  }

  /*
   * send main css to camyks as included file
   * @return void
   * @access private
   */
  function get_included_main_css() {
    global $camyks;
    if ($this->get_fileURL('css/style.css') != '')
      $camyks->HTMLPage->add_styleIncludedFile($this->get_filePath('css/style.css'));
    else
      $camyks->HTMLPage->add_styleIncludedFile($this->get_filePath('style.css'));
    if ($this->get_fileURL('css/editor.css') != '')
      $camyks->HTMLPage->add_styleIncludedFile($this->get_filePath('css/editor.css'));
    else
      $camyks->HTMLPage->add_styleIncludedFile($this->get_filePath('editor.css'));
  }
  
  /*
   * send editor css to camyks
   * @return void
   * @access private
   */
  function get_editor_css() {
    global $camyks;
    $camyks->HTMLPage->add_styleFile($this->get_fileURL('editor.css'));
  }
  
  /*
   * return editor css url
   * @return string
   * @access public
   */
  function get_editorCSSURL() {
    if ($this->get_fileURL('css/editor.css') != '')
      return $this->get_fileURL('css/editor.css');
    return $this->get_fileURL('editor.css');
  }

  /*
   * generic part display
   * @param string $part
   * @param mixed $data
   * @return string
   * @access private
   */
  function get_part($part, $data=array()) {
    global $camyks;
    
    /* check if theme is loaded */
    $this->get_parts();
    
    /* check if part exist */
    if (isset($this->parts[$part])) {
      return vsprintf($this->parts[$part], $data );
    } else if ($this->name != 'Default') {
      if ( isset ($camyks->themes['camyks']['default'])) {
	    return $camyks->themes['camyks']['default']->get_part($part, $data);
      }
    }
    
    /* return default value */
    return '';
  }

  /*
   * return pict url
   * @param string $item
   * @param integer $size
   * @param string $position
   * @return string
   * @access public
   */
  function get_pictURL ( $item, $size, $position ) {
    global $global_theme_picts_items;
    /* check size */
    $size = (STRING)$size;
    if ( isset( $global_theme_picts_items[$size] ) === false ) {
      foreach ( $global_theme_picts_items as $s => $v ) {
	    $size = $s;
	    break;
      }
    }
    /* check item */
    if ( !in_array( $item, $global_theme_picts_items[$size]['items'] ) ) {
      $item = $global_theme_picts_items[$size]['items'][0];
    }
    /* check position */
    if ( !in_array( $position, $global_theme_picts_items[$size]['positions'] ) ) {
      $position = $global_theme_picts_items[$size]['positions'][0];
    }
    /* return pict image url */
    return $this->get_fileURL('img/picts/'.$size.'_'.$item.'_'.$position.'.gif' );
  }

  /*
   * return pict url
   * @param string $pict
   * @return string
   * @access public
   */
  function get_pictURLWithName( $pict ) {
    return $this->get_fileURL('img/picts/'.$pict);
  }

  /************* PART : SIMPLE BAR ************/

  /*
   * display full bar
   * @param array $params
   * @param string $style // deprecated
   * @return string
   * @access public
   */
  function get_bar ($params='', $style='') {
    $dParams = array('content'=>'', 'style'=>'');
    if (!is_array($params))
      $params = array('content'=>$params, 'style' => $style);
    $params = array_merge($dParams, $params);
  
    return $this->get_barComplete($params['content'], $params['style']);
  }

  /*
   * display full bar
   * @param array $params
   * @param string $style // deprecated, should be in params
   * @return string
   * @access public
   */
  function get_barComplete ( $params='', $style='' ) {
    $dParams = array('content'=>'', 'style'=>'');
    if (!is_array($params))
      $params = array('content'=>$params, 'style' => $style);
    $params = array_merge($dParams, $params);
  
    return $this->get_barLeft($params['style']).
      $params['content'].
      $this->get_barRight();
  }

  /*
   * display left part of the bar
   * @param array $params
   * @return string
   * @access public
   */
  function get_barLeft ($params='' ) {
    $dParams = array('style'=>'', 'class'=>'', 'id'=>'');
    if (!is_array($params))
      $params = array('style' => $params);
    $params = array_merge($dParams, $params);
    
    return $this->get_part('barLeft', array($params['style'], $params['class'], $params['id']));
  }

  /*
   * display right part of the bar
   * @return string
   * @access public
   */
  function get_barRight( ) {
    return $this->get_part('barRight');
  }

  /*
   * display bar button item
   * @param mixed $params (string button title or whole button data struct array)
   * @param string $url
   * @param string $id
   * @param string $style
   * @return string
   * @access public
   */
  function get_barButton( $params='', $url='', $id='', $style='' ) {
    $dParams = array('title'=>'', 'style'=>'', 'class'=>'', 'style'=>'', 'id'=>'', 'url'=>'');
    if (!is_array($params))
      $params = array('title'=>$params, 'url'=>$url, 'id'=>$id, 'style'=>$style);
    $params = array_merge($dParams, $params);

    /* display button */
    if ( $params['url'] == '' )
      return $this->get_barItem(array('title'=>$params['title'],'id'=>$params['id'], 'style'=>$params['style']));
    return $this->get_part('barButton', array( $params['id'], $params['url'], $params['title'], $params['style']));
  }

  /*
   * display bar item
   * @param mixed $params (string item title or whole item data struct array)
   * @param string $id
   * @param string $style
   * @return string
   * @access public
   */
  function get_barItem ( $params, $id='', $style='' ) {
    $dParams = array('title'=>'', 'style'=>'', 'class'=>'', 'style'=>'', 'id'=>'');
    if (!is_array($params))
      $params = array('title'=>$params, 'id'=>$id, 'style'=>$style);
    $params = array_merge($dParams, $params);
    
    /* display item */
    return $this->get_part('barItem', array( $params['id'], $params['title'], $params['style'] ));
  }

  /************* PART : BOX ************/

  /*
   * display box header
   * @param mixed $params (string item style or whole item data struct array)
   * @return string
   * @access public
   */
  function get_boxHeader ( $params='' ) {
    $dParams = array('style'=>'', 'class'=>'', 'id'=>'');
    if (!is_array($params))
      $params = array('style' => $params);
    $params = array_merge($dParams, $params);
    
    return $this->get_part('boxHeader', array($params['style'], $params['id'], $params['class']));
  }

  function get_boxTitleBar ( $title='' ) {
    return $this->get_part('boxTitleBar', array($title));
  }

  function get_boxTabsBar ( $tabs, $params, $mover='', $mout='', $selected='') {
    /* check params */
    if ( !is_array($params)) {
      $params = array('clic'=>$params, 'mover'=>$mover, 'mout'=>$mout, 'selected'=>$selected);
    }
    
    /* build tabs */
    if ( $params['selected'] == '' ) {
      $params['selected'] = $tabs[0]['name'];
    }
    
    $str = '';
    $str .= $this->get_part('boxTabsBarHeader');
    foreach ( $tabs as $t ) {
      if ( $t['name'] == $params['selected'] ) {
	$str .= $this->get_part('boxTabSelected',
				array($t['name'],
				      $params['clic'].'(\''.$t['name'].'\')',
				      $params['mover'].'(\''.$t['name'].'\')',
				      $params['mout'].'(\''.$t['name'].'\')',
				      $t['title'])); 
      } else {
	$str .= $this->get_part('boxTab',
				array($t['name'],
				      $params['clic'].'(\''.$t['name'].'\')',
				      $params['mover'].'(\''.$t['name'].'\')',
				      $params['mout'].'(\''.$t['name'].'\')',
				      $t['title'])); 
      }
    }
    $str .= $this->get_part('boxTabsBarFooter');
    return $str;
  }
  
  function get_boxButtonsBar($buttons=array()) {  
    $defaultButton = array('link'=>'', 'title'=>'', 'style'=>'', 'id'=>'', 'more'=>'');
  
    $str = '';
    $str .= $this->get_part('boxButtonsBarHeader');
    foreach ( $buttons as $b ) {
      $b = array_merge($defaultButton, $b);
      
      if ($b['id'] != '')
        $b['more'] .= ' id="'.$b['id'].'"';

      if ($b['link'] != '') {
	    $str .= $this->get_part('boxButtonWithLink', array($b['style'], $b['link'], $b['title'], $b['more']));
      } else {
	    $str .= $this->get_part('boxButtonWithoutLink', array($b['style'], $b['title'], $b['more']));
      }
    }
    $str .= $this->get_part('boxButtonsBarFooter');
    return $str;
  }

  /* box contents */
  function get_boxContent1Header( $more='' ) {
    return $this->get_part('boxContent1Header', $more);
  }

  function get_boxContent2Header( $more='' ) {
    return $this->get_part('boxContent2Header', $more);
  }

  function get_boxContent1Footer( ) {
    return $this->get_part('boxContent1Footer');
  }
  
  function get_boxContent2Footer( ) {
    return $this->get_part('boxContent2Footer');
  }

  /* default box content */
  function get_boxContentHeader($more='') {
    return $this->get_boxContent1Header($more);
  }

  function get_boxContentFooter() {
    return $this->get_boxContent1Footer();
  }

  /* footer */
  function get_boxFooter () {
    return $this->get_part('boxFooter');
  }

  /************* PART : LIGHT BOX ********************/
  function get_lightBoxHeader($style='') {
    return $this->get_part('lightBoxHeader', array($style));
  }

  function get_lightBoxFooter() {
    return $this->get_part('lightBoxFooter');
  }

  /************* PART : SIMPLE BUTTON ************/

  function get_button ( $params, $url='', $style='' ) {
    $dParams = array('title'=>'', 'url'=>'', 'id'=>'', 'style'=>'', 'class'=>'', 'target'=>'');
    if (!is_array($params))
      $params = array('title'=>$params, 'style' => $style, 'url'=>$url);
    $params = array_merge($dParams, $params);
    
    /*
    if ( is_array( $button ) ) {
      /* button is an array *
      $title = isset($button['title'])?$button['title']:'';
      $url = isset($button['url'])?$button['url']:'';
      $style = isset($button['style'])?$button['style']:'';
      $id = isset($button['id'])? $button['id']:'';
    } else {
      $title=$button;
      $id = '';
    }
    */
    return $this->get_part('button', array( $params['style'], $params['url'], $params['title'], $params['id'], $params['class'], $params['target'] ));
  }

  /************* PART : LAYERED MENU  ************/
  function get_layeredMenu ( $name, $objectname, $content ) {
    $html = $this->get_layeredMenuHeader( $name, $objectname );
    foreach ( $content as $item ) {
      if ( $item['title'] == '----' ) {
	$html .= $this->get_layeredMenuSeparator ( );
      } else if ( $item['url'] == '' ) {
	$html .= $this->get_layeredMenuNoLinkItem ( $item );
      } else {
	$html .= $this->get_layeredMenuLinkItem ( $item );
      }
    }    
    $html .= $this->get_layeredMenuFooter ( );
    return $html;
  }

  function get_layeredMenuHeader ( $name, $objectname ) {
    return $this->get_part('layeredMenuHeader', array($name,
						      $objectname,
						      $name,
						      $objectname,
						      $name));
  }

  function get_layeredMenuSeparator ( ) {
    return $this->get_part('layeredMenuSeparator');
  }

  function get_layeredMenuNoLinkItem ( $item ) {
    /* update title with icon */
    if ( isset($item['icon']) and $item['icon'] != '' )
      $title = '<img src="'.$item['icon'].'" alt="'.strip_tags($item['title']).'" border="0" class="icon" />'.$item['title'];
    else
      $title = $item['title'];
    
    return $this->get_part('layeredMenuNoLinkItem', array(isset($item['name'])?$item['name']:'',
							  $title));
  }
  
  function get_layeredMenuLinkItem ( $item ) {
    /* update title with icon */
    if ( isset($item['icon']) and $item['icon'] != '' )
      $title = '<img src="'.$item['icon'].'" alt="'.strip_tags($item['title']).'" border="0" class="icon" />'.$item['title'];
    else
      $title = $item['title'];
    
    /* compute additional attributes */
    $add = '';
    if (isset($item['target']) and $item['target'] != '')
      $add .= ' target="'.$item['target'].'"';

    return $this->get_part('layeredMenuLinkItem', 
                       array(isset($item['name'])?$item['name']:'',
							$title,
							$item['url'],
							$add
							));
  }
  
  function get_layeredMenuFooter ( ) {
    return $this->get_part('layeredMenuFooter');
  }
}
?>