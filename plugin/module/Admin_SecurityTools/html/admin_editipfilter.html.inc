<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Oct 2007
 * Last Modif Date	: Oct 2007
 * 
 * Admin_SecurityTools module admin layout : edit filter ip rule
 */
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title.' : '.$this->get_translation('ipfilter_editruleid', $this->ipfilterrule->id) ) ?>
<?=$this->theme->get_boxContent2Header( )?>
<?=$this->form->display_header(); ?>
<?=$this->form->display_hiddens(); ?>
<div class="adminContentPanel">
  <table cellspacing="0" cellpadding="0" border="0" style="width:100%">
    <?php if ( isset( $this->ipfilterrule->_libError ) ) : ?>
    <tr>
      <td class="error" colspan="3">
	<?=$this->ipfilterrule->_libError?>
      </td>
    </tr>
    <?php endif; ?>
    <tr>
      <td class="eTableLine0 eContent2">
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
<?=$this->form->display_footer(); ?>
<?=$this->theme->get_boxContent2Footer();?>
<?=$this->theme->get_boxButtonsBar( $this->buttons );?>
<?=$this->theme->get_boxFooter();?>