<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	       		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version		: 1.0b
 * Object Version		: 1.0
 * Object Type			: Plugin / Input Layout
 * Creation Date 		: Apr 2011
 * Last Modif Date	: Apr 2011
 *
 * MultiSelectionList input layout
 */
?>
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
<tr>
<td class="eTableHeader" style="width:50%;">
<?= $this->params['listTitle']; ?>
</td>
<td class="eTableHeader" style="width:50%;">
<?= $this->params['selectionTitle'] ?>
</td>
</tr>
<tr>
<td id="<?=$this->params['name']?>_fullListBox" style="vertical-align:top; padding:2px 10px 2px 4px;">

</td>
<td id="<?=$this->params['name']?>_selListBox" style="vertical-align:top; padding:2px 10px 2px 4px;">

</td>
</tr>
</table>
