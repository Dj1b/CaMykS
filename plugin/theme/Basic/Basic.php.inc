<?php
/**
 * @brief Basic theme.
 * <br /> Very simple theme.
 * @details Plugin / Theme Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.1
 * @date Creation: Sep 2005
 * @date Modification: Jul 2025
 * @copyright 2005 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Basic Theme class.
 */
final class Basic extends Theme {
    /**
     * Class constructor.
     * @param string $path_type.
     */
    public function __construct($path_type) {
        parent::__construct('Basic', $path_type);

        /* Override Plugin variables */
        $this->title = 'Basic';
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* Define author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';
    }

    /* Mark: Override Theme methods */

    /**
     * Overwrite box buttons bar.
     * @param array $buttons
     * @return string
     */
    public function get_boxButtonsBar($buttons=array()) {
        /* get min button value */
        $min = 2;

        /* update button size */
        if ( $sized ) {
            $cols = max( $min, count($buttons));
            $colw = 'width:'.intval(100/$cols).'%;';
        } else {
            $colw = '';
        }

        $str = '';
        $str .= $this->get_part('boxButtonsBarHeader');
        foreach ( $buttons as $b ) {
            if ( isset($b['link']) and $b['link']!= '') {
                $str .= $this->get_part('boxButtonWithLink', array( $colw, $b['link'], $b['title']));
            } else {
                $str .= $this->get_part('boxButtonWithoutLink', array( $colw, $b['title']));
            }
        }
        /* simulate a "min" cols bar */
        for( $i=count($buttons); $i < $min; $i++ ) {
            $str .= $this->get_part('boxButtonWithoutLink', array( $colw, '&nbsp;'));
        }
        $str .= $this->get_part('boxButtonsBarFooter');
        return $str;
    }
}
?>
