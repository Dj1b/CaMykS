<?php
/**
 * @brief CodeAuthenticator Input, edit configuration layout.
 * @details Plugin / Input layout
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
                <?= $this->get_translation('formtitle_codeparams'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2" style="width:160px;">
                <?= $this->get_translation('formitem_length'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->get_configValue('code_length'); ?>
                <?= $this->get_translation('formunit_characters'); ?>
            </td>
        </tr>

        <tr>
            <td colspan="2" class="eTableLine0">
                &nbsp;
            </td>
        </tr>

        <tr>
            <td colspan="2" class="eTableHeader">
                <?= $this->get_translation('formtitle_secretparams'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2" style="width:160px;">
                <?= $this->get_translation('formitem_length'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->get_configValue('secret_length'); ?>
                <?= $this->get_translation('formunit_bits'); ?>
            </td>
        </tr>
    </table>
</div>
<?= $camyks->theme->get_boxContent2Footer(); ?>
