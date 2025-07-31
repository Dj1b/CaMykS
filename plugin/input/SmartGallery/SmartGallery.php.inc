<?php
/**
 * @brief SmartGallery Input
 * <br /> Display an image gallery.
 * @details Plugin / Input Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.1
 * @date Creation: Jul 2007
 * @date Modification: Jul 2025
 * @copyright 2007 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * SmartGallery Input class.
 */
final class SmartGallery extends Input {

    /**
     * @var string $name
     * @brief Instance name.
     */
    public $name;

    /**
     * @var string $theme
     * @brief Instance theme.
     */
    public $theme = 'itunes';

     /**
     * @var array $items
     * @brief Item list.
     */
    public $items = array();

     /**
     * @var boolean $sliding
     * @brief Is sliding enabled.
     */
    public $sliding = false;

    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('SmartGallery', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* Define author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Initialise plugin variables */
        $this->themes = array(
            'itunes'    => $this->get_translation('theme_itunes'),
            'safari'    => $this->get_translation('theme_safari'),
            'custom'    => $this->get_translation('theme_custom')
       );

        $this->slidingMethods = array(
            'page'  => $this->get_translation('slidingmethod_page'),
            /*'one'=>$this->get_translation('slidingmethod_one')*/
       );
    }

    /* Mark: Override Input methods */

    /**
     * Initialise input.
     * @param string $name
     * @return void
     */
    public function initialise($name='sg') {
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
        foreach ($this->items as $item) {
            $itemvalue = array();
            foreach ($item as $name => $value) {
                $itemvalue[] = $name.':"'.$value.'"';
            }
            $itemvalue = implode(',', $itemvalue);
            $this->add_JSScript($this->objectName.'.addItem({'.$itemvalue.'});');
        }
        /* Input generic initialisation */
        parent::initialise();
    }

    /* Mark: Specific methods */

    /**
     * Set theme value.
     * @param string $theme
     * @return void
     */
    public function set_themeValues($theme='itunes') {
        if (isset($this->themes[$theme]))
            $this->theme = $theme;
        else
            foreach ($this->themes as $n=>$t) {
                $this->theme = $n;
                break;
            }
    }

    /**
     * Set images urls.
     * @param string $image
     * @param string $thumb
     * @return void
     */
    public function set_URLsValues($image, $thumb) {
        $this->imageURL = $image;
        $this->thumbURL = $thumb;
    }

    /**
     * Set thumb images info.
     * @param int $width
     * @param int $height
     * @param int $count
     * @return void
     */
    public function set_thumbValues($width=80, $height=60, $count=6) {
        $this->thumbCount = $count;
        $this->thumbWidth = $width;
        $this->thumbHeight = $height;
        $this->thumb = true;
    }

    /**
     * Set main images info.
     * @param int $width
     * @param int $height
     * @param bool $hasTitle
     * @param bool $hasDesc
     * @return void
     */
    public function set_imageValues($width=0, $height=0, $hasTitle=true, $hasDesc=true) {
        $this->imageWidth = $width;
        $this->imageHeight = $height;
        $this->imageTitle = $hasTitle;
        $this->imageDesc = $hasDesc;
        $this->image = true;
    }

    /**
     * Set sliding config.
     * @param string $method
     * @param int $accel
     * @param int $speed
     * @param int $interval
     * @return void
     */
    public function set_slidingValues ($method='page', $accel=1, $speed=30, $interval=25) {
        if (isset($this->slidingMethods[$method]))
            $this->slidingMethod = $method;
        else
            foreach ($this->slidingMethods as $n => $m) {
                $this->slidingMethod = $n;
                break;
            }

        $this->slidingAccel = $accel;
        $this->slidingSpeed = $speed;
        $this->slidingInterval = $interval;
        $this->sliding=true;
    }

    /**
     * insert a new item in item list
     * @param mixed $id
     * @param string $type
     * @param string $thumb
     * @param string $image
     * @param string $title
     * @param string $desc
     * @return void
     */
    public function add_item ($id, $type, $thumb, $image, $title='', $desc='') {
        $this->items[] = array(
            'id'    => $id,
            'type'  => $type,
            'thumb' => $thumb,
            'image' => $image,
            'title' => $title,
            'desc'  => $desc);
    }
}
?>
