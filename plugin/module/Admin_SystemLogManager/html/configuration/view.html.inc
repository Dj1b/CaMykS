<?php
/**
 * @brief Admin_SystemLogManager Input configuration view layout
 * @details Plugin / Input layout
 * @file plugin/module/Admin_SystemLogManager/html/configuration/view.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jun 2018
 * @date Modification: Jun 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;
?>

<?php if (isset($this->isConfig) and $this->isConfig):?>

<?=$camyks->theme->get_boxContent2Header();?>
<div class="adminContentPanel">

<?php endif; ?>

<table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
    <tr>
        <td class="eTableLine0 eContent2" style="width:160px;">
            <?=$this->get_translation('formitem_rotate');?>
        </td>
        <td class="eTableLine0 eContent1">
            <?=$this->loggingPeriodList[$this->config->get_value('logging_period')];?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine1 eContent2">
            <?=$this->get_translation('formitem_keeplast');?>
        </td>
        <td class="eTableLine1 eContent1">
            <?=$this->config->get_value('logging_lastFilesKept');?>
            <?=$this->get_translation('formdesc_keeplast');?>
        </td>
    </tr>

    <tr>
      <td colspan="2" class="eTableLine0">
        &nbsp;
      </td>
    </tr>

    <?php if ($this->check_right(1) == true) : ?>
    <tr>
      <td colspan="2" class="eTableLine0">
            <?= $this->theme->get_button(array('title'=>$camyks->get_translation('configure'), 'url'=>$this->get_adminLink(array('mode'=>'edit_config')))); ?>
      </td>
    </tr>
    <?php endif; ?>

</table>

<?php if (isset($this->isConfig) and $this->isConfig):?>

</div>
<?=$camyks->theme->get_boxContent2Footer();?>

<?php endif; ?>

<?php
/**
 * @endcond Exclude
 */
?>
