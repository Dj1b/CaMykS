<?php
/**
 * @brief Admin_Statistics Module admin options colors sublayout
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Sep 2020
 * @date Modification: Sep 2020
 * @copyright 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
?>
<table cellspacing="0" style="width:100%;">
    <tr>
        <td class="eTableHeader" colspan="2">
            <?= $this->get_translation('colorselection'); ?>
        </td>
    </tr>
    <tr>
        <td class="eTableLine0 eContent2" style="width:110px;">
            <?= $this->get_translation('coloralternate1'); ?>
        </td>
        <td class="eTableLine0 eContent1">
            <?= $this->display_colorPicker('coloralternate0'); ?>
        </td>
    </tr>
    <tr>
        <td class="eTableLine1 eContent2">
            <?= $this->get_translation('coloralternate2'); ?>
        </td>
        <td class="eTableLine1 eContent1">
            <?= $this->display_colorPicker('coloralternate1'); ?>
        </td>
    </tr>
</table>

<?php
/**
 * @endcond Exclude
 */
?>
