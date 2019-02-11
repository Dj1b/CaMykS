<?php
/**
 * @brief Theme plugin object
 * @details Engine / Object Library
 * @file engine/lib/object/Theme.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: Jun 2005
 * @date Modification: Feb 2019
 * @copyright 2005 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $global_theme_picts_items, $global_theme_media_types;

/**
 * @var array $global_theme_picts_items
 * @brief Define available picts items
 */
$global_theme_picts_items = array(
    '12'    => array(
        'items' => array(
            'empty',
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
       ),
        'positions' => array(
            'std',
            'ovr'
       ),
   ),
);

/**
 * @var array $global_theme_media_types
 * @brief Define available media types
 */
$global_theme_media_types = array(
    'tty',
    'tv',
    'projection',
    'handheld',
    'print',
    'braille',
    'aural',
    '3d-glasses',
    'all',
);

/**
 * Theme class.
 * @author CaMykS Team <camyks.contact@gmail.com>
 */
abstract class Theme extends Plugin {
    /**
     * @var boolean $partsLoaded
     * @brief Are parts loaded.
     */
    public $partsLoaded = false;

    /**
     * @var array $parts
     * @brief Are parts loaded.
     */
    public $parts = array();

    /**
     * @var array $responsiveStyles
     * @brief Define responsiveness of theme.
     */
    public $responsiveStyles = array();

    /**
     * @var array $touchIcons
     * @brief Define available touch icons.
     */
    public $touchIcons = array();

    /**
     * @var string $autoBoxContent
     * @brief
     */
    private $autoBoxContent = 'Close';

    /**
     * @var boolean $useEnhancedSelectInputs
     * @brief Set useEnhancedSelectInputs to default value.
     */
    public $useEnhancedSelectInputs = false;

    /**
     * @var boolean $isAdminResponsive
     * @brief Set isAdminResponsive to default value.
     */
    private $isAdminResponsive = false;

    /**
     * Class constructor.
     * @param string $name
     * @param string $path_type
     * @return void
     */
    public function __construct($name, $path_type) {
        parent::__construct($name, 'theme', $path_type);
    }

    /*
     * Alias to constructor.
     * @param string $name
     * @param string $path_type
     * @return void
     */
    public function Theme($name, $path_type) {
        $this->__construct($name, $path_type);
    }

    /**
     * Initialise theme object.
     * @return void
     */
    public function initialise() {
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

    /**
     * Initialise theme object in admin mode.
     * @return void
     */
    public function initialise_adminMode() {
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

    /**
     * Load theme parts.
     * @return void
     */
    public function get_parts() {
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

    /**
     * load theme parts as included file
     * @return void
     */
    public function get_included_parts() {
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


    /**
     * Send main CSS files to CaMykS.
     * @return void
     */
    public function get_main_css() {
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
        foreach($global_theme_media_types as $media) {
            if ($this->get_filePath($media.'.css', false) != false)
                $this->add_styleFile($media.'.css', $media);
        }
    }

    /**
     * Send main CSS files to CaMykS as included files
     * @return void
     */
    public function get_included_main_css() {
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

    /**
     * Send editor CSS file to CaMykS.
     * @return void
     */
    public function get_editor_css() {
        global $camyks;
        $camyks->HTMLPage->add_styleFile($this->get_fileURL('editor.css'));
    }

    /**
     * Return editor CSS file URL .
     * @return string
     */
    public function get_editorCSSURL() {
        if ($this->get_fileURL('css/editor.css') != '')
            return $this->get_fileURL('css/editor.css');
        return $this->get_fileURL('editor.css');
    }

    /**
     * Generic part display.
     * @param string $part
     * @param array $data
     * @return string
     */
    public function get_part($part, $data=array()) {
        global $camyks;

        /* check if theme is loaded */
        $this->get_parts();

        /* check if part exist */
        if (isset($this->parts[$part])) {
            return vsprintf($this->parts[$part], $data);
        /*
        } else if ($this->name != 'Default') {
            if (isset ($camyks->themes['camyks']['default'])) {
                return $camyks->themes['camyks']['default']->get_part($part, $data);
            }
        */
        }


        /* return default value */
        return '';
    }

    /**
     * Return pict URL.
     * @param string $item
     * @param integer $size
     * @param string $position
     * @return string
     */
    public function get_pictURL($item, $size=12, $position='std') {
        global $global_theme_picts_items;

        /* check size */
        $size = (STRING)$size;
        if (isset($global_theme_picts_items[$size]) === false) {
            foreach ($global_theme_picts_items as $s => $v) {
                $size = $s;
                break;
            }
        }

        /* check item */
        if (!in_array($item, $global_theme_picts_items[$size]['items'])) {
            $item = $global_theme_picts_items[$size]['items'][0];
        }

        /* check position */
        if (!in_array($position, $global_theme_picts_items[$size]['positions'])) {
            $position = $global_theme_picts_items[$size]['positions'][0];
        }

        /* return pict image url */
        return $this->get_fileURL('img/picts/'.$size.'_'.$item.'_'.$position.'.gif');
    }

    /**
     * Return pict url from full file name.
     * @param string $pict
     * @return string
     */
    public function get_pictURLWithName($pict) {
        return $this->get_fileURL('img/picts/'.$pict);
    }

    /**
     * Return img full tag related to pict.
     * @param array $params
     * @return string
     */
     public function get_pictHTMLTag($params=array()) {
        /* check params */
        $defaultParams = array('pict'=>'', 'size'=>12, 'position'=>'std', 'addMouseover'=>false, 'alt'=>'', 'style'=>'');
        $params = array_merge($defaultParams, $params);

        /* load main picture */
        $url = $this->get_pictURL($params['pict'], $params['size'], $params['position']);

        /* build HTML tag */
        $result = '<img src="'.$url.'" alt="'.$params['alt'].'"';
        if ($params['addMouseover'] == true) {
            $result .= ' onmouseover="this.src=\''.$this->get_pictURL($params['pict'], $params['size'], $params['position']=='std'?'ovr':'std').'\';"';
            $result .= ' onmouseout="this.src=\''.$url.'\';"';
        }
        if ($params['style'] != '')
          $result .= ' style="'.$params['style'].'"';
        $result .= ' />';

        /* return result */
        return $result;
     }

    /************* PART : SIMPLE BAR ************/

    /**
     * Alias to get_barComplete
     * @see get_barComplete()
     * @param array $params
     * @param string $style
     * @return string
     */
    public function get_bar($params='', $style='') {
        return $this->get_barComplete($params, $style);
    }

    /**
     * Display full bar.
     * @param array $params
     * @param string $style
     * @return string
     */
    public function get_barComplete($params='', $style='') {
        $dParams = array('content'=>'', 'style'=>'');
        if (!is_array($params))
            $params = array('content'=>$params, 'style' => $style);
        $params = array_merge($dParams, $params);

        return $this->get_barLeft(array('style'=>$params['style'])).$params['content'].$this->get_barRight();
    }

    /**
     * Display left part of the bar.
     * @param array $params
     * @return string
     */
    public function get_barLeft($params='') {
        $dParams = array('style'=>'', 'class'=>'', 'id'=>'');
        if (!is_array($params))
            $params = array('style' => $params);
        $params = array_merge($dParams, $params);

        return $this->get_part('barLeft', array($params['style'], $params['class'], $params['id']));
    }

    /**
     * Display right part of the bar
     * @return string
     */
    public function get_barRight() {
        return $this->get_part('barRight');
    }

    /**
     * Display bar button item.
     * @param mixed $params (string button title or whole button data struct array)
     * @param string $url
     * @param string $id
     * @param string $style
     * @return string
     */
    public function get_barButton($params='', $url='', $id='', $style='') {
        $dParams = array('title'=>'', 'style'=>'', 'class'=>'', 'style'=>'', 'id'=>'', 'url'=>'');
        if (!is_array($params))
            $params = array('title'=>$params, 'url'=>$url, 'id'=>$id, 'style'=>$style);
        $params = array_merge($dParams, $params);

        /* display button */
        if ($params['url'] == '')
            return $this->get_barItem(array('title'=>$params['title'],'id'=>$params['id'], 'style'=>$params['style']));
        return $this->get_part('barButton', array($params['id'], $params['url'], $params['title'], $params['style']));
    }

    /**
     * Display bar item.
     * @param mixed $params (string item title or whole item data struct array)
     * @param string $id
     * @param string $style
     * @return string
     */
    public function get_barItem ($params, $id='', $style='') {
        $dParams = array('title'=>'', 'style'=>'', 'class'=>'', 'style'=>'', 'id'=>'');
        if (!is_array($params))
            $params = array('title'=>$params, 'id'=>$id, 'style'=>$style);
        $params = array_merge($dParams, $params);

        /* display item */
        return $this->get_part('barItem', array($params['id'], $params['title'], $params['style']));
    }

    /************* PART : BOX ************/

    /**
     * Display box header.
     * @param mixed $params (string item style or whole item data struct array)
     * @return string
     */
    public function get_boxHeader($params='') {
        $dParams = array('style'=>'', 'class'=>'', 'id'=>'');
        if (!is_array($params))
            $params = array('style' => $params);
        $params = array_merge($dParams, $params);

        return $this->get_part('boxHeader', array($params['style'], $params['id'], $params['class']));
    }

    /**
     * Display box title bar.
     * @param string $title
     * @return string
     */
    public function get_boxTitleBar($title='') {
        return $this->get_part('boxTitleBar', array($title));
    }

    /**
     * Display box tabs bar.
     * @param array $tabs
     * @param array $params
     * @param string $mover
     * @param string $mout
     * @param string $selected
     * @return string
     */
    public function get_boxTabsBar($tabs, $params, $mover='', $mout='', $selected='') {
        /* check params */
        if (!is_array($params)) {
            $params = array('clic'=>$params, 'mover'=>$mover, 'mout'=>$mout, 'selected'=>$selected);
        }

        /* build tabs */
        if ($params['selected'] == '') {
            $params['selected'] = $tabs[0]['name'];
        }

        $str = '';
        $str .= $this->get_part('boxTabsBarHeader');
        foreach ($tabs as $t) {
            if ($t['name'] == $params['selected']) {
                $str .= $this->get_part(
                    'boxTabSelected',
                    array(
                        $t['name'],
                        $params['clic'].'(\''.$t['name'].'\')',
                        $params['mover'].'(\''.$t['name'].'\')',
                        $params['mout'].'(\''.$t['name'].'\')',
                        $t['title'],
                    )
                );
            } else {
                $str .= $this->get_part(
                    'boxTab',
                    array(
                        $t['name'],
                        $params['clic'].'(\''.$t['name'].'\')',
                        $params['mover'].'(\''.$t['name'].'\')',
                        $params['mout'].'(\''.$t['name'].'\')',
                        $t['title'],
                    )
                );
            }
        }
        $str .= $this->get_part('boxTabsBarFooter');
        return $str;
    }

    /**
     * Display box buttons bar.
     * @param array $buttons
     * @return string
     */
    public function get_boxButtonsBar($buttons=array()) {
        $defaultButton = array('link'=>'', 'title'=>'', 'style'=>'', 'id'=>'', 'more'=>'');

        $str = '';
        $str .= $this->get_part('boxButtonsBarHeader');
        foreach ($buttons as $b) {
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

    /**
     * Display box content 1 header.
     * @param string $more
     * @return string
     */
    public function get_boxContent1Header($more='') {
        return $this->get_part('boxContent1Header', $more);
    }

    /**
     * Display box content 2 header.
     * @param string $more
     * @return string
     */
    public function get_boxContent2Header($more='') {
        return $this->get_part('boxContent2Header', $more);
    }

    /**
     * Display box content 1 footer.
     * @return string
     */
    public function get_boxContent1Footer() {
        return $this->get_part('boxContent1Footer');
    }

    /**
     * Display box content 2 footer.
     * @return string
     */
    public function get_boxContent2Footer() {
        return $this->get_part('boxContent2Footer');
    }

    /**
     * Display box generic content header, alias to get_boxContent1Header().
     * @param string $more
     * @return string
     */
    public function get_boxContentHeader($more='') {
        return $this->get_boxContent1Header($more);
    }

    /**
     * Display box generic content footer, alias to get_boxContent1Footer().
     * @return string
     */
    public function get_boxContentFooter() {
        return $this->get_boxContent1Footer();
    }

    /**
     * Display box footer.
     * @return string
     */
    public function get_boxFooter() {
        return $this->get_part('boxFooter');
    }

    /************* PART : LIGHT BOX ********************/

    /**
     * Display light box header.
     * @param string $style
     * @return string
     */
    public function get_lightBoxHeader($style='') {
        return $this->get_part('lightBoxHeader', array($style));
    }

    /**
     * Display light box footer.
     * @return string
     */
    public function get_lightBoxFooter() {
        return $this->get_part('lightBoxFooter');
    }

    /************* PART : SIMPLE BUTTON ************/

    /**
     * Display button.
     * @param array $params
     * @param string $url
     * @param string $style
     * @return string
     */
    public function get_button ($params, $url='', $style='') {
        $dParams = array('title'=>'', 'url'=>'', 'id'=>'', 'style'=>'', 'class'=>'', 'target'=>'');
        if (!is_array($params))
            $params = array('title'=>$params, 'style'=>$style, 'url'=>$url);
        $params = array_merge($dParams, $params);

        /* check id */
        print_r(substr($params['id'], 0, 3));
        if ($params['id'] !== '' and substr($params['id'], 0, 3) !== 'id=')
            $params['id'] = 'id="'.$params['id'].'"';
        return $this->get_part('button', array($params['style'], $params['url'], $params['title'], $params['id'], $params['class'], $params['target']));
    }

    /************* PART : LAYERED MENU  ************/

    /**
     * Display layered menu.
     * @param string $name
     * @param string $objectname
     * @param array $content
     * @return string
     */
    public function get_layeredMenu ($name, $objectname, $content) {
        $html = $this->get_layeredMenuHeader($name, $objectname);
        foreach ($content as $item) {
            if ($item['title'] == '----') {
                $html .= $this->get_layeredMenuSeparator();
            } else if ($item['url'] == '') {
                $html .= $this->get_layeredMenuNoLinkItem($item);
            } else {
                $html .= $this->get_layeredMenuLinkItem($item);
            }
        }
        $html .= $this->get_layeredMenuFooter();
        return $html;
    }

    /**
     * Display layered menu header.
     * @param string $name
     * @param string $objectname
     * @return string
     */
    public function get_layeredMenuHeader($name, $objectname) {
        return $this->get_part('layeredMenuHeader', array($name, $objectname, $name, $objectname, $name));
    }

    /**
     * Display layered menu separator.
     * @return string
     */
    public function get_layeredMenuSeparator() {
        return $this->get_part('layeredMenuSeparator');
    }

    /**
     * Display layered menu item without link.
     * @param array $item
     * @return string
     */
    public function get_layeredMenuNoLinkItem($item=array()) {
        /* update title with icon */
        if (isset($item['icon']) and $item['icon'] != '')
            $title = '<img src="'.$item['icon'].'" alt="'.strip_tags($item['title']).'" border="0" class="icon" />'.$item['title'];
        else
            $title = $item['title'];

        return $this->get_part('layeredMenuNoLinkItem', array(isset($item['name'])?$item['name']:'', $title));
    }

    /**
     * Display layered menu item with link.
     * @param array $item
     * @return string
     */
    public function get_layeredMenuLinkItem($item=array()) {
        /* update title with icon */
        if (isset($item['icon']) and $item['icon'] != '')
            $title = '<img src="'.$item['icon'].'" alt="'.strip_tags($item['title']).'" border="0" class="icon" />'.$item['title'];
         else
            $title = $item['title'];

        /* compute additional attributes */
        $add = '';
        if (isset($item['target']) and $item['target'] != '')
            $add .= ' target="'.$item['target'].'"';

        return $this->get_part(
            'layeredMenuLinkItem',
            array(
                isset($item['name'])?$item['name']:'',
                $title,
                $item['url'],
                $add,
        ));
    }

    /**
     * Display layered menu footer.
     * @return string
     */
    public function get_layeredMenuFooter() {
        return $this->get_part('layeredMenuFooter');
    }

    /**
     * Return main icon url from touch icons.
     * @return string
     */
    public function get_mainIcon() {
        foreach ($this->touchIcons as $icon)
            if ($icon['name'] === 'icon')
                return $this->get_fileURL('img/touchIcons/'.$icon['url']);
        return false;
    }
}
?>
