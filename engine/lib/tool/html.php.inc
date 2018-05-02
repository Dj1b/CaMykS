<?php
/**
 * @brief Some basic html methods, now obsolete
 * @details Engine / Tool Library
 * @file engine/lib/tool/html.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Mar 2005
 * @date Modification: Apr 2018
 * @copyright 2017 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @deprecated Now obsolete
 */

/**
 * Return a html table header.
 * @param integer $cp
 * @param integer $cs
 * @param string $s
 * @param string $cl
 * @param integer $b
 * @param string $o
 * @return string
 */
function html_getTableHeader($cp=0, $cs=0, $s='', $cl='', $b=0,  $o='') {
    $html = '<table';
    $html .= ' cellpadding="'.$cp.'"';
    $html .= ' cellspacing="'.$cs.'"';
    $html .= ' border="'.$b.'"';
    if ($cl != '')
        $html .= ' class="'.$cl.'"';
    if ($s != '')
        $html .= ' style="'.$s.'"';
    if ($o != '')
        $html .= ' '.$o;
    $html .= '>';
    return $html;
}

/**
 * Return a html table header.
 * @return string
 */
function html_getTableFooter() {
    return '</table>';
}
?>