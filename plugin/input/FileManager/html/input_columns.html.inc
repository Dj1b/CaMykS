<?php
/**
 * @brief FileManager Input columns layout
 * @details Plugin / Input layout
 * @file plugin/input/FileManager/html/input_columns.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jun 2007
 * @date Modification: Apr 2019
 * @copyright 2007 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
?>
<div id="fm_browser" style="width:100%; overflow:auto;">
<table cellspacing="0">
<tr>
<?php for ( $i=0; $i< count($this->cols); $i++ ) : ?>
<td id="fm_column<?=$i?>" class="filemanagerColumn adminContentPanel">
<div style="width:150px; height:1px; font-size:1px;">&nbsp;</div>
<?=$this->cols[$i]?>
</td>
<?php endfor; ?>
</tr>
</table>
</div>
<?php
/**
 * @endcond Exclude
 */
?>
