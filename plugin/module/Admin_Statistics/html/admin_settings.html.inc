<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0
 * Object Version	: 1.0
 * Object Type	    : Plugin / Module Layout
 * Creation Date	: May 2007
 * Last Modif Date	: Oct 2009
 *
 * Admin_Statistics Module Admin part of Layout : configuration
*/
global $camyks;

$plus = $this->theme->get_pictURL('plus', 12, 'std');
$plus_ = $this->theme->get_pictURL('plus', 12, 'ovr');

$minus = $this->theme->get_pictURL('minus', 12, 'std');
$minus_ = $this->theme->get_pictURL('minus', 12, 'ovr');

?>
<?=$this->theme->get_lightBoxHeader('width:100%');?>
<?=$this->theme->get_boxContent2Header();?>
<?=$this->form->display_header();?>
<?=$this->form->display_hiddens();?>
<div class="adminContentPanel">
  <table cellspacing="0" cellpadding="0" border="0" style="width:100%">
    <tr>
      <td class="eTableHeader">
	<?=$this->get_translation('enabledstatistics');?>
      </td>
      <td class="eTableHeader">
	<?=$this->get_translation('filteredips');?>
      </td>
    </tr>
    <tr>
      <td style="width:50%; vertical-align:top;">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%">
    
    <tr>
      <td class="eTableLine1 eContent2">
	<?=$camyks->get_translation('mod_admin_contentpage_stat_visits').
      $camyks->get_translation('formitem_separator');?>
      </td>
      <td class="eTableLine1 eContent1">
        <?=$this->form->display_selectInput(array('name'=>'stat_visits', 'values'=>$this->statusList, 'class'=>'sinputs'));?>
      </td>
    </tr>

    <tr>
      <td class="eTableLine0 eContent2">
	<?=$camyks->get_translation('mod_admin_contentpage_stat_sitepage').
      $camyks->get_translation('formitem_separator');?>
      </td>
      <td class="eTableLine0 eContent1">
        <?=$this->form->display_selectInput(array('name'=>'stat_sitepage', 'values'=>$this->statusList, 'class'=>'sinputs'));?>
      </td>
    </tr>
    
    <tr>
      <td class="eTableLine1 eContent2">
	<?=$camyks->get_translation('mod_admin_contentpage_stat_firstpage').
      $camyks->get_translation('formitem_separator');?>
      </td>
      <td class="eTableLine1 eContent1">
        <?=$this->form->display_selectInput(array('name'=>'stat_firstpage', 'values'=>$this->statusList, 'class'=>'sinputs'));?>
      </td>
    </tr>

    <tr>
      <td class="eTableLine0 eContent2">
      <?=$camyks->get_translation('mod_admin_contentpage_stat_referer').
      $camyks->get_translation('formitem_separator');?>
      </td>
      <td class="eTableLine0 eContent1">
        <?=$this->form->display_selectInput(array('name'=>'stat_referer', 'values'=>$this->statusList, 'class'=>'sinputs'));?>
      </td>
    </tr>
    
    <tr>
      <td class="eTableLine1 eContent2">
	<?=$this->get_translation('stat_webbots').
      $camyks->get_translation('formitem_separator');?>
      </td>
      <td class="eTableLine1 eContent1">
        <?=$this->form->display_selectInput(array('name'=>'stat_webbots', 'values'=>$this->statusList, 'class'=>'sinputs'));?>
      </td>
    </tr>
    
    <tr>
      <td class="eTableLine0 eContent2">
	<?=$this->get_translation('stat_webtools').
      $camyks->get_translation('formitem_separator');?>
      </td>
      <td class="eTableLine0 eContent1">
        <?=$this->form->display_selectInput(array('name'=>'stat_webtools', 'values'=>$this->statusList, 'class'=>'sinputs'));?>
      </td>
    </tr>
  </table>
</td>
<td style="vertical-align:top;">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%">
<tbody id="filteredips">
  <?php foreach($this->settings->vars['stat_filteredips'] as $c => $ip) : ?>
<tr id="filteredipline<?=$c?>">
  <td class="eTableLine0" style="padding:6px 4px;">
  <input type="hidden" name="stat_filteredips_<?=$c?>" value="<?=$ip?>" />
  <?= $ip ?>
  </td>
  <td class="eTableLine0" style="padding:6px 4px; width:12px;">
    <img src="<?=$minus?>" alt="<?=$this->get_translation('remove_filteredip');?>" border="0"
      onclick="sse.remove_filteredIp(<?=$c?>);"
      onmouseover="this.src='<?=$minus_?>';"
      onmouseout="this.src='<?=$minus?>';" />
  </td>
</tr>
  <?php endforeach; ?>
</tbody>
</table>
<table cellspacing="0" cellpadding="0" border="0" style="width:100%" id="filteredipadder">
<tr>
  <td class="eTableLine1">
   <input type="text" name="ipadder" value="" class="inputs" />
  </td>
  <td class="eTableLine1" style="width:12px;">
    <img src="<?=$plus?>" alt="<?=$this->get_translation('add_filteredip');?>" border="0"
      onclick="sse.add_filteredIp();"
      onmouseover="this.src='<?=$plus_?>';"
      onmouseout="this.src='<?=$plus?>';" />
  </td>
</tr>
</table>

</td>
</tr>
  </table>
</div>
<?=$this->form->display_footer();?>
<?=$this->theme->get_boxContent2Footer();?>
<?=$this->theme->get_lightBoxFooter();?>