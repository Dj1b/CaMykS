<?php
/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Input Engine
 * Create Date		: Jul 2007
 * Last Modif Date	: Jul 2007
 * 
 * Smart Gallery output
 * Display image list 
 */

class SmartGallery extends Input {
  /* defined vars */
  var $name;
  /* theme */
  var $theme;
  /* urls */
  var $imageURL;
  var $thumbURL;

  /* item list */
  var $items;

  /*
   * constructor
   * @param sting $path_type
   */
  function SmartGallery ( $path_type ) {
    parent::Input('SmartGallery', $path_type);
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Default';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
    /* initialise plugin variables */
    $this->themes = array('itunes'=> $this->get_translation('theme_itunes'),
			  'safari'=> $this->get_translation('theme_safari'),
			  'custom'=> $this->get_translation('theme_custom'));
    $this->slidingMethods = array('page'=>$this->get_translation('slidingmethod_page')/*,
				  'one'=>$this->get_translation('slidingmethod_one')*/);
    $this->items = array();
    $this->image = false;
    $this->thumb = false;
    $this->sliding = false;
  }
  
  /* overwrite input methods */

  /*
   * initialise input
   * @param string $name
   * @return void
   * @access public
   */
  function initialise ( $name='sg' ) {
    global $camyks;
    /* set name value */
    $this->objectName = $name;

    /* load style file */
    $this->add_styleFile('smartgallery.css');

    /* load javascript object */
    $this->add_JSFile('SmartGallery.js');
    $this->add_JSEngineFile('tool/math.js');
    $this->add_JSEngineFile('tool/htmlelement.js');
    $this->add_JSScript('var '.$this->objectName.' = new SmartGallery("'.$this->objectName.'");');
    $this->add_JSLoadScript($this->objectName.'.initGallery();');
    /* update config */
    $this->add_JSScript($this->objectName.'.set_urlsConfig("'.$this->get_fileURL('img/'.$this->theme).'", "'.$this->imageURL.'", "'.$this->thumbURL.'");');
    if ($this->image) {
      $this->add_JSScript($this->objectName.'.set_imageConfig('.$this->imageWidth.','.$this->imageHeight.','.$this->imageTitle.','.$this->imageDesc.');');
    }
    if ($this->thumb) {
      $this->add_JSScript($this->objectName.'.set_thumbConfig('.$this->thumbWidth.', '.$this->thumbHeight.', '.$this->thumbCount.');');
    }
    if ($this->sliding) {
      $this->add_JSScript($this->objectName.'.set_slidingConfig("'.$this->slidingMethod.'", '.$this->slidingAccel.', '.$this->slidingSpeed.', '.$this->slidingInterval.');');
    }

    /* add item list */
    foreach ( $this->items as $item ) {
      $itemvalue = array();
      foreach ( $item as $name => $value ) {
	$itemvalue[] = $name.':"'.$value.'"';
      }
      $itemvalue = implode(',', $itemvalue);
      $this->add_JSScript($this->objectName.'.addItem({'.$itemvalue.'});');
    }
    /* Input generic initialisation */
    parent::initialise();
  }
  
  /*
   * display input
   * @return void
   * @access public
   */
  function display() {
    parent::display();
  }

  /* specific methods */

  /*
   * set theme value
   * @param string $theme
   * @return void
   * @access private
   */
  function set_themeValues( $theme='itunes' ) {
    if ( isset( $this->themes[$theme] ) )
      $this->theme = $theme;
    else
      foreach ( $this->themes as $n=>$t ) { 
	$this->theme = $n;
	break;
      }
  }

  /*
   * set images urls
   * @param string $main
   * @param string $thumb
   * @return void
   * @access public
   */
  function set_URLsValues( $image, $thumb ) {
    $this->imageURL = $image;
    $this->thumbURL = $thumb;
  }

  /*
   * set thumb images info
   * @param int $count
   * @param int $width
   * @param int $height
   * @return void
   * @access public
   */
  function set_thumbValues( $width=80, $height=60, $count=6 ) {
    $this->thumbCount = $count;
    $this->thumbWidth = $width;
    $this->thumbHeight = $height;
    $this->thumb = true;
  } 

  /*
   * set main images info
   * @param int $width
   * @param int $height
   * @param bool $hasTitle
   * @param bool $hasDesc
   * @return void
   * @access public
   */
  function set_imageValues( $width=0, $height=0, $hasTitle=true, $hasDesc=true ) {
    $this->imageWidth = $width;
    $this->imageHeight = $height;
    $this->imageTitle = $hasTitle;
    $this->imageDesc = $hasDesc;
    $this->image = true;
  }

  /* 
   * set sliding config
   * @param string $method
   * @param int $accel
   * @param int $speed
   * @param int $interval
   * @return void
   * @access public
   */
  function set_slidingValues ( $method='page', $accel=1, $speed=30, $interval=25) {
    if ( isset( $this->slidingMethods[$method] ) )
      $this->slidingMethod = $method;
    else
      foreach ( $this->slidingMethods as $n => $m ) {
	$this->slidingMethod = $n;
	break;
      }

    $this->slidingAccel = $accel;
    $this->slidingSpeed = $speed;
    $this->slidingInterval = $interval;
    $this->sliding=true;
  }

  /*
   * insert a new item in item list
   * @param mixed $id
   * @param string $type
   * @param string $thumb
   * @param string $image
   * @param string $title
   * @param string $desc
   * @return void
   * @access public
   */
  function add_item ( $id, $type, $thumb, $image, $title='', $desc='' ) {
    $this->items[] = array('id' => $id,
			   'type' => $type,
			   'thumb' => $thumb,
			   'image' => $image,
			   'title' => $title,
			   'desc' => $desc);
  }
}
?>