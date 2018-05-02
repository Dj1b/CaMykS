<?php
/**
 * @brief MultiSelectionList Input layout
 * @details Plugin / Input layout
 * @file plugin/input/MultiSelectionList/html/input.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Apr 2011
 * @date Modification: Apr 2018
 * @copyright 2011 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
?>
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
    <tr>
        <td class="eTableHeader" style="width:50%;">
            <?=$this->params['listTitle'];?>
        </td>
        <td class="eTableHeader" style="width:50%;">
            <?=$this->params['selectionTitle'];?>
        </td>
    </tr>
    <tr>
        <td id="<?=$this->params['name']?>_fullListBox" style="vertical-align:top; padding:2px 10px 2px 4px;">

        </td>
        <td id="<?=$this->params['name']?>_selListBox" style="vertical-align:top; padding:2px 10px 2px 4px;">

        </td>
    </tr>
</table>
<?php
/**
 * @endcond Exclude
 */
?>
