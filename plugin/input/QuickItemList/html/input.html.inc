<?php
/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a2
 * Object Version       : 1.0
 * Object Type          : Plugin / Input Layout
 * Creation Date       	: Mar 2007
 * Last Modif Date	: Mar 2009
 *
 * QuickItemList input layout
 */
?>
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
<tr>
<td class="eTableHeader" style="width:50%;">
<?= $this->fullListName ?>
</td>
<td class="eTableHeader" style="width:50%;">
<?= $this->editListName ?>
</td>
</tr>
<tr>
<td id="<?=$this->objectName?>_fullListBox" style="vertical-align:top; padding:2px 10px 2px 4px;">

</td>
<td id="<?=$this->objectName?>_editListBox" style="vertical-align:top; padding:2px 10px 2px 4px;">

</td>
</tr>
</table>
