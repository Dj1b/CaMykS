<?php
/**
 * @brief Admin_Statistics Module admin colorpicker replacement layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Sep 2007
 * @date Modification: Sep 2020
 * @copyright 2007 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
?>
<div style="background-color:#<?= $this->colorPickerValue; ?>; border:solid 1px #666; width:30px; height:16px; float:left; margin-right:4px;">
    &nbsp;
</div>
<div class="eContent1">
    #<?= $this->colorPickerValue; ?>
</div>
<?php
/**
 * @endcond Exclude
 */
?>
