<?php
/**
 * @brief Admin_User module view configuration layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Jun 2021
 * @date Modification: Jun 2021
 * @copyright 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $camyks->theme->get_boxContent2Header(); ?>
<div class="adminContentPanel">
    <table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td colspan="2" class="eTableHeader">
                <?= $this->get_translation('formtitle_authentication'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2" style="width:160px;">
                <?= $this->get_translation('formitem_2factorinput'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->config->get_authentication2FactorInputTitle(); ?>
            </td>
        </tr>
        <?php /*
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_2factorstatus'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->config->get_authentication2FactorStatusTitle(); ?>
            </td>
        </tr>
        */ ?>
    </table>
</div>
<?= $camyks->theme->get_boxContent2Footer(); ?>
