<?php
/*
 * CaMykS Engine
 * Developed by		: Ideogram Design
 * Author			: JB Lebrun <jb.lebrun@ideogram-design.fr>
 * CaMykS Version	: 1.0b
 * Object Version	: 1.0
 * Object Type	    : Plugin / Module Layout
 * Creation Date    : Dec 2014
 * Last Modif Date	: Feb 2017
 * 
 * Admin_ContentPage Module Admin Layout : view configuration
*/
global $camyks;
?>
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
        <?=$this->W3CValidatorStatus[$this->config->vars['action_w3cValidator']]; ?>
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
        <?=$this->OGMetaStatus[$this->config->vars['site_ogmeta']]; ?>
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
      <?=$this->Error404FallBacks[$this->config->vars['page_404FallBack']]; ?>
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

<?php if ($this->check_right(8)) : ?>
<tr>
    <td class="eTableLine0 eContent2" coslpan="2">
        <?=$this->theme->get_button(array('url'=>$this->get_adminLink(array('mode'=>'edit_config')), 'title'=>$camyks->get_translation('modify')));?>
    </td>
</tr>
<?php endif; ?>

</table>