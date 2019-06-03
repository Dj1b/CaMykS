<?php
/**
 * @brief Tool_Installer Module summary layout
 * @details Plugin / Module Layout
 * @file plugin/module/Tool_Installer/html/admin_summary.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Aug 2007
 * @date Modification: May 2019
 * @copyright 2007 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
$isFirst = true;
?>
<div style="padding:30px 0;">
<?= $camyks->theme->get_boxHeader('width:600px; margin:0 auto;'); ?>
<?= $camyks->theme->get_boxTitleBar($this->title); ?>
<?= $camyks->theme->get_boxContent2Header(); ?>

<table cellspacing="0" style="width:100%">

<?php $alt = 0; ?>
<?php foreach($this->summary as $text) : ?>
    <?php if ($text['type'] == 'title') : ?>
        <?php if ($isFirst) : ?>
            <?php $isFirst = false; ?>
        <?php else : ?>
            <tr>
                <td class="eTableLine0" colspan="2">
                    &nbsp;
                </td>
            </tr>
        <?php endif; ?>
        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $text['name']; ?>
            </td>
        </tr>
    <?php elseif ($text['type'] == 'message') : ?>
        <tr>
            <td class="eTableLine<?= $alt; ?> eContent2">
                <?= $text['name']; ?> :
            </td>
            <td class="eTableLine<?= $alt; ?> eContent2" style="<?= (isset($text['color'])?'color:'.$text['color']:''); ?>">
                <?= $text['value']; ?>
            </td>
        </tr>
        <?php $alt = abs($alt-1); ?>
    <?php elseif ($text['type'] == 'detail') : ?>
    <tr>
        <td class="eTableLine<?= $alt; ?> eContent2" style="<?= (isset($text['color'])?'color:'.$text['color'].'; ':''); ?> padding-left:32px;" colspan="2">
            <?= $text['name']; ?>
        </td>
    </tr>
    <?php $alt = abs($alt-1); ?>
    <?php endif; ?>
<?php endforeach; ?>
</table>

<?= $camyks->theme->get_boxContent2Footer(); ?>
<?= $camyks->theme->get_boxButtonsBar($this->buttons); ?>
<?= $camyks->theme->get_boxFooter(); ?>
</div>
