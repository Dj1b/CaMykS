<?php
/**
 * @brief Admin_GenericEmailingManager Module view configuration sub layout
 * @details Plugin, Module Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2.1
 * @date Creation: Dec 2012
 * @date Modification: Nov 2020
 * @copyright 2012 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>

<?php if (isset($this->isConfig) and $this->isConfig) :?>

<?= $camyks->theme->get_boxContent2Header(); ?>
<div class="adminContentPanel">

<?php endif; ?>

<table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
<tr>
    <td class="eTableHeader" colspan="2">
        <?= $this->get_translation('formtitle_unsubscribe'); ?>
    </td>
</tr>

<tr>
    <td class="eTableLine0 eContent2" style="width:150px">
        <?= $this->get_translation('formitem_backpage'); ?>
    </td>
    <td class="eTableLine0 eContent1">
        <?= $this->config->get_value('unsubscribe_backpage'); ?>
    </td>
</tr>

<?php if (!isset($this->isConfig) or $this->isConfig === false) :?>
<tr>
    <td class="eTableLine0 eContent2" coslpan="2">
        <?= $camyks->theme->get_button(array('url'=>$this->get_adminLink(array('mode'=>'edit_config')), 'title'=>$camyks->get_translation('modify'))); ?>
    </td>
</tr>
<?php endif; ?>
</table>

<?php if (isset($this->isConfig) and $this->isConfig) :?>

</div>
<?= $camyks->theme->get_boxContent2Footer();?>

<?php endif; ?>
