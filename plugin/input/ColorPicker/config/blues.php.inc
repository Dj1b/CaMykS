<?php
/**
 * @brief ColorPicker Input blues configuration.
 * @details Plugin / Input Library
 * @file plugin/input/ColorPicker/config/blues.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Mar 2007
 * @date Modification: Apr 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

$this->config = array(
    'more'      => true,
    'width'     => 12,
    'height'    => 12,
    'maxcols'   => 16,
    'maxrows'   => 8,
    'colors'    => array(),
);

for ($i=63; $i >= 0; $i--) {
    $v = dechex($i*4);
    $v = str_pad($v, 2, '0', STR_PAD_LEFT);
    $this->config['colors'][] = $v.$v.'FF'; 
}

for ($i=63; $i >= 0; $i--) {
    $v = dechex($i*4);
    $v = str_pad($v, 2, '0', STR_PAD_LEFT);
    $this->config['colors'][] = '0000'.$v; 
}
?>
