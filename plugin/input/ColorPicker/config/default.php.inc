<?php
/**
 * @brief ColorPicker Input default configuration.
 * @details Plugin / Input Library
 * @file plugin/input/ColorPicker/config/default.php.inc
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
    'width'     => 6,
    'height'    => 8,
    'maxcols'   => 36,
    'maxrows'   => 6,
    'colors'    => array(),
);

$item = array('FF', 'CC', '99', '66', '33', '00');
foreach ($item as $a) {
  foreach ($item as $b) {
    foreach ($item as $c) {
      $this->config['colors'][] = $a.$b.$c; 
    }
  }
}
?>
