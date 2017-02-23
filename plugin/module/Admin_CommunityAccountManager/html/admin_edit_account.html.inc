<?php
/*
 * CaMykS Engine
 * Developed by		  : Ideogram Design
 * Author		        : JB Lebrun <jb.lebrun@ideogram-design.fr>
 * CaMykS Version	  : 1.0b
 * Account Version	: 1.0
 * Account Type     : Plugin / Module Layout
 * Create Date      : Mar 2010
 * Last Modif Date	: Mar 2010
 * 
 * Admin_iqsimAccountManager Module admin layout : edit_account
*/
global $camyks;

$plus = $this->theme->get_pictURL('plus', 12, 'std');
$plus_ = $this->theme->get_pictURL('plus', 12, 'ovr');

$minus = $this->theme->get_pictURL('minus', 12, 'std');
$minus_ = $this->theme->get_pictURL('minus', 12, 'ovr');

?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->adminTitle); ?>
<?=$this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams);?>
<?=$this->theme->get_boxContent2Header()?>
<?=$this->editform->display_header(); ?>
<?=$this->editform->display_hiddens(); ?>
<div id="itemadmin" class="adminContentPanel" style="display:<?=$this->tabBuilder->get_tabDisplay('admin')?>">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%">
<?php if (isset($this->accountItem->_libError)): ?>

<tr>
<td class="eTableLine0 error" colspan="2">
<?=$this->accountItem->_libError;?>
</td>
</tr>

<?php endif; ?>

<tr>
<td class="eTableLine1 eContent2" style="width:150px;">
<?=$camyks->get_translation('formitem_status')?>
</td>
<td class="eTableLine1 eContent1">
<?=$this->editform->display_selectInput(array('name'=>'status', 'values'=>$this->get_accountStatusList())); ?>
</td>
</tr>

<tr>
<td class="eTableLine0 eContent2">
<?=$camyks->get_translation('formitem_type')?>
</td>
<td class="eTableLine0 eContent1">
  <?=$this->editform->display_selectInput(array('name'=>'type', 'values'=>$this->get_accountTypeList()));?>
</td>
</tr>

<tr>
<td class="eTableLine1 eContent2">
<?=$camyks->get_translation('formitem_email')?>
</td>
<td class="eTableLine1 eContent1">
  <?=$this->editform->display_textInput('email');?>
</td>
</tr>

<?php if( $this->accountItem->id > 0 ) : ?>

<tr>
<td class="eTableLine0 eContent2">
<?=$this->get_translation('formitem_changepassword')?>
</td>
<td class="eTableLine0 eContent1">
<?= $this->editform->display_booleanSelectInput(array('name'=>'change_password', 'default'=>0, 'onchange'=>'accountEditor.update_passwordPanel()'));?>
</td>
</tr>

<tr>
  <td colspan="2">
<div id="password_panel" style="display:none;">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%">
<tr>
<td class="eTableLine1 eContent2" style="width:150px;">
<?=$this->get_translation('formitem_password')?>
</td>
<td class="eTableLine1 eContent1">
<input type="password" name="password" class="inputs" maxlength="16" />
</td>
</tr>

<tr>
<td class="eTableLine0 eContent2">
<?=$this->get_translation('formitem_confirm')?>
</td>
<td class="eTableLine0 eContent1">
<input type="password" name="confirm_password" class="inputs" maxlength="16" />
</td>
</tr>

</table>
</div>
</td>
</tr>


<tr>
<td class="eTableLine1 eContent2">
<?=$this->get_translation('formitem_registrationdate')?>
</td>
<td class="eTableLine1 eContent1">
<?=date_displayLongDayDateHour($this->accountItem->vars['registrationdate']);?>
</td>
</tr>

<tr>
<td class="eTableLine0 eContent2">
<?=$this->get_translation('formitem_connectiondate')?>
</td>
<td class="eTableLine0 eContent1">
<?=date_displayLongDayDateHour($this->accountItem->vars['connectiondate']);?>
</td>
</tr>

<tr>
<td class="eTableLine1 eContent2">
<?=$this->get_translation('formitem_ipaddresses')?>
</td>
<td class="eTableLine1 eContent1">
<?= preg_replace('/;/', '<br/>', $this->accountItem->vars['ipaddresses']); ?>
</td>
</tr>

<tr>
<td class="eTableLine0 eContent2">
<?=$this->get_translation('formitem_securecode')?>
</td>
<td class="eTableLine0 eContent1">
<?=$this->accountItem->vars['securecode']; ?>
</td>
</tr>

<?php else : ?>

<tr>
<td class="eTableLine0 eContent2">
<?=$this->get_translation('formitem_password')?>
</td>
<td class="eTableLine0 eContent1">
<input type="password" name="account_password" class="inputs" maxlength="<?=$this->config->vars['accounts_maxpwdlength']?>" />
</td>
</tr>

<tr>
<td class="eTableLine1 eContent2">
<?=$this->get_translation('formitem_confirm')?>
</td>
<td class="eTableLine1 eContent1">
<input type="password" name="confirm_password" class="inputs" maxlength="<?=$this->config->vars['accounts_maxpwdlength']?>" />
</td>
</tr>

<?php endif; ?> 

</table>
</div>

<div id="itempersonal" class="adminContentPanel" style="display:<?=$this->tabBuilder->get_tabDisplay('personal')?>">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%">
<tr>
  <td class="eTableLine1 eContent2" style="width:150px;">
<?=$camyks->get_translation('formitem_firstname');?>
  </td>
  <td class="eTableLine1 eContent1">
    <?=$this->editform->display_textInput('firstname');?>
  </td>
</tr>
<tr>
  <td class="eTableLine0 eContent2">
<?=$camyks->get_translation('formitem_lastname');?>
  </td>
  <td class="eTableLine0 eContent1">
    <?=$this->editform->display_textInput('lastname');?>
  </td>
</tr>
<tr>
  <td class="eTableLine1 eContent2">
<?=$this->get_translation('formitem_company');?>
  </td>
  <td class="eTableLine1 eContent1">
    <?=$this->editform->display_textInput('company');?>
  </td>
</tr>
<tr>
  <td class="eTableLine0 eContent2">
<?=$camyks->get_translation('formitem_country');?>
  </td>
  <td class="eTableLine0 eContent1">
    <?=$this->editform->display_selectInput(array('name'=>'country', 'values'=>$this->countries)); ?>
  </td>
</tr>
<tr>
  <td class="eTableLine1 eContent2">
<?=$camyks->get_translation('formitem_phone');?>
  </td>
  <td class="eTableLine1 eContent1">
    <?=$this->editform->display_textInput('phone');?>
  </td>
</tr>

</table>
</div>

<?=$this->editform->display_footer(); ?>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?=$this->theme->get_boxFooter(); ?>