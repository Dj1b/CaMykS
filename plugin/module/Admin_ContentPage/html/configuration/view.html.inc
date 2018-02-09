<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author			: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0
 * Object Version	: 1.0
 * Object Type	    : Plugin / Module Layout
 * Creation Date    : Dec 2014
 * Last Modif Date	: Feb 2018
 * 
 * Admin_ContentPage Module Admin Layout : view configuration
*/
global $camyks;
?>
<?php if (isset($this->isConfig) and $this->isConfig) : ?>

<?=$camyks->theme->get_boxContent2Header();?>
<div class="adminContentPanel">

<?php endif; ?>

<table cellspacing="2" cellpadding="0" border="0" style="width:100%;">

<tr>
  <td class="eTableHeader" colspan="2">
    <?=$this->get_translation('formtitle_actions'); ?>
  </td>
</tr>

<tr>
    <td class="eTableLine0 eContent2" style="width:160px;">
        <?=$this->get_translation('formitem_w3cvalidator');?>
    </td>
    <td class="eTableLine0 eContent1">
        <?=$this->config->get_w3cValidatorTitle(); ?>
    </td>
</tr>

<tr>
  <td class="eTableLine0" colspan="2">
    &nbsp;
  </td>
</tr>

<tr>
  <td class="eTableHeader" colspan="2">
    <?=$this->get_translation('formtitle_ogmeta'); ?>
  </td>
</tr>


<tr>
    <td class="eTableLine0 eContent2">
        <?=$camyks->get_translation('formitem_status');?>
    </td>
    <td class="eTableLine0 eContent1">
        <?=$this->config->get_ogMetaStatusTitle(); ?>
    </td>
</tr>


<tr>
  <td class="eTableLine0" colspan="2">
    &nbsp;
  </td>
</tr>

<tr>
  <td class="eTableHeader" colspan="2">
    <?=$this->get_translation('formtitle_pagesnotfound'); ?>
  </td>
</tr>

<tr>
    <td class="eTableLine0 eContent2">
        <?=$this->get_translation('formitem_404fallback');?>
    </td>
    <td class="eTableLine0 eContent1">
      <?=$this->config->get_404FallbackTitle(); ?>
      <?php if (in_array($this->config->vars['page_404FallBack'], array('error404_display', 'error404_redirect'))) : ?>
      (<?=$this->get_translation('formitem_file') . $this->config->vars['page_404ErrorFile'];?>)
      <?php elseif (in_array($this->config->vars['page_404FallBack'], array('page_display', 'page_redirect'))) : ?>
      (<?=$this->get_translation('formitem_page') . $this->config->vars['page_404ErrorPage'];?>)
      <?php endif; ?>
    </td>
</tr>

<?php if (substr($this->config->vars['page_404FallBack'], -7, 7) == 'display'): ?>
<tr>
  <td class="eTableLine0 eContent2">
    <?=$this->get_translation('formitem_send404header');?>
  </td>
  <td class="eTableLine0 eContent1">
    <?=$camyks->get_translation($this->config->vars['page_404SendHeader']?'yes':'no');?>
  </td>
</tr>
<?php endif; ?>

</table>

<?php if (isset($this->isConfig) and $this->isConfig) :?>

</div>
<?=$camyks->theme->get_boxContent2Footer();?>

<?php endif; ?>