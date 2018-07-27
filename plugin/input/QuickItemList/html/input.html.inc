<?php
/**
 * @brief QuickItemList Input layout
 * @details Plugin / Input layout
 * @file plugin/input/QuickItemList/html/input.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Mar 2007
 * @date Modification: Jul 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
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
<?php
/**
 * @endcond Exclude
 */
?>
