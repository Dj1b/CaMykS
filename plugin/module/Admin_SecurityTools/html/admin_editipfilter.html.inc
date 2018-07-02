<?php
/**
 * @brief Admin_SecurityTools Module admin layout to edit filter ip rule
 * @details Plugin / Module layout
 * @file plugin/module/Admin_SecurityTools/html/admin_editipfilter.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Oct 2007
 * @date Modification: Jun 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->adminTitle); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<?= $this->form->display_header(); ?>
<?= $this->form->display_hiddens(); ?>
<div class="adminContentPanel">
  <table cellspacing="0" cellpadding="0" border="0" style="width:100%">
    <?php if (isset($this->ipfilterrule->_libError)) : ?>
    <tr>
      <td class="error" colspan="3">
        <?=$this->ipfilterrule->_libError?>
      </td>
    </tr>
    <?php endif; ?>
    <tr>
      <td class="eTableLine0 eContent2" style="width:150px;">
        <?=$this->get_translation('ipfilter_active'); ?>
      </td>
      <td class="eTableLine0 eContent1">
      <?=$this->form->display_booleanSelectInput(array('name'=>'active', 'default'=>$this->ipfilterrule->vars['active']));?>
      </td>
    </tr>
    <tr> 
      <td class="eTableLine1 eContent2">
        <?=$this->get_translation('ipfilter_ipaddress');?>
      </td>
      <td class="eTableLine1 eContent1">
        <input type="text" name="ipaddress" value="<?=$this->ipfilterrule->vars['ipaddress']?>" maxlength="16" class="inputs" />
      </td>
    </tr>
    <tr>
      <td class="eTableLine0 eContent2">
        <?=$this->get_translation('ipfilter_permission');?>
      </td>
      <td class="eTableLine0 eContent1">
        <select name="permission" class="inputs">
          <option value="0"<?=$this->ipfilterrule->vars['permission'] == 0 ? ' selected="selected"':''?>>
            <?=$this->get_translation('ipfilter_permission0');?>
          </option>
          <option value="1"<?=$this->ipfilterrule->vars['permission'] == 1 ? ' selected="selected"':''?>>
            <?=$this->get_translation('ipfilter_permission1');?>
          </option>
        </select>
      </td>
    </tr>
    <tr>
      <td class="eTableLine1 eContent2">
        <?=$this->get_translation('ipfilter_mode');?>
      </td>
      <td class="eTableLine1 eContent1">
        <select name="sitemode" class="inputs">
          <option value="0"<?=$this->ipfilterrule->vars['sitemode'] == 0 ? ' selected="selected"':''?>>
            <?=$this->get_translation('ipfilter_mode0');?>
          </option>
          <option value="1"<?=$this->ipfilterrule->vars['sitemode'] == 1 ? ' selected="selected"':''?>>
            <?=$this->get_translation('ipfilter_mode1');?>
          </option>
          <option value="2"<?=$this->ipfilterrule->vars['sitemode'] == 2 ? ' selected="selected"':''?>>
            <?=$this->get_translation('ipfilter_mode2');?>
          </option>
        </select>
      </td>
    </tr>
    <tr>
      <td class="eTableLine0 eContent2">
        <?=$this->get_translation('ipfilter_comment')?>
      </td>
      <td class="eTableLine0 eContent1">
        <input type="text" name="comment" value="<?=$this->ipfilterrule->vars['comment']?>" maxlength="255" class="inputs" />
      </td>
    </tr>
  </table>
</div>
<?= $this->form->display_footer(); ?>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>

<?php 
/**
 * @endcond Exclude
 */
?>