<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0a
 * Object Version   : 1.0
 * Object Type      : Plugin / Input Layout
 * Creation Date	: Jun 2007
 * Last Modif Date	: Jun 2007
 * 
 * FileManager input columns view layout
*/
?>
<div id="fm_browser" style="width:680px; overflow:auto;">
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