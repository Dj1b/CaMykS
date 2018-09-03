<?php
/**
 * @brief GreyStyle Theme.
 * <br /> Initial CaMykS theme.
 * @details Plugin / Theme Engine
 * @file plugin/theme/GreyStyle/GreyStyle.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jun 2005
 * @date Modification: Aug 2018
 * @copyright 2005 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * GreyStyle Theme class.
 */
final class GreyStyle extends Theme {
    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('GreyStyle', $path_type);

        /* overwrite Plugin information */
        $this->title = 'Grey Style';
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* initialise Theme variables */
        $this->hasTabs = false;
    }

    /* overwrite Theme parts */

    /**
     * Overwrite box tab bar.
     * @param array $tabs
     * @param string $click
     * @param string $mover
     * @param string $mout
     * @param string $selected
     * @return string
     */
    public function get_boxTabsBar($tabs, $click, $mover='', $mout='', $selected='') {
        $this->hasTabs = true;
        return parent::get_boxTabsBar($tabs, $click, $mover, $mout, $selected);
    }

    /**
     * Build box content header.
     * @param string $more
     * @return string
     */
    public function get_boxContent1Header($more='') {
        if ($this->hasTabs === true) {
            return $this->get_part('boxOpenContentHeader', $more);
        } else {
            return $this->get_part('boxContent1Header', $more);
        }
    }

    /**
     * Build box content header.
     * @param string $more
     * @return string
     */
    public function get_boxContent2Header($more='') {
        if ($this->hasTabs === true) {
            return $this->get_part('boxOpenContentHeader', $more);
        } else {
            return $this->get_part('boxContent2Header', $more);
        }
    }

    /**
     * Build box content footer.
     * @return string
     */
    public function get_boxContent1Footer() {
        if ($this->hasTabs === true) {
            $this->hasTabs = false;
            return $this->get_part('boxOpenContentFooter');
        } else {
            return $this->get_part('boxContent1Footer');
        }
    }

    /**
     * Build box content footer.
     * @return string
     */
    public function get_boxContent2Footer() {
        if ($this->hasTabs === true) {
            $this->hasTabs = false;
            return $this->get_part('boxOpenContentFooter');
        } else {
            return $this->get_part('boxContent2Footer');
        }
    }

    /**
     * Build box buttons bar.
     * @param array $buttons
     * @param boolean $sized
     * @return string
     */
    public function get_boxButtonsBar ($buttons=array(), $sized=true) {
        $defaultButton = array('link'=>'', 'title'=>'', 'style'=>'', 'id'=>'', 'more'=>'');

        /* get min button value */
        $min = 2;

        /* update button size */
        if ($sized) {
            $cols = max($min, count($buttons));
            $colw = 'width:'.intval(100/$cols).'%;';
        } else {
            $colw = '';
        }

        $str = '';
        $str .= $this->get_part('boxButtonsBarHeader');
        foreach ($buttons as $b) {
            $b = array_merge($defaultButton, $b);

            if ($b['id'] != '')
                $b['more'] .= ' id="'.$b['id'].'"';

            if ($b['link'] != '') {
                $str .= $this->get_part('boxButtonWithLink', array($b['style'], $b['link'], $b['title'], $b['more'], $colw));
            } else {
                $str .= $this->get_part('boxButtonWithoutLink', array($b['style'], $b['title'], $b['more'], $colw));
            }
        }

        /* simulate a "min" cols bar */
        for($i=count($buttons); $i < $min; $i++) {
            $str .= $this->get_part('boxButtonWithoutLink', array('', '&nbsp;', '', $colw));
        }
        $str .= $this->get_part('boxButtonsBarFooter');
        return $str;
    }
}
?>
