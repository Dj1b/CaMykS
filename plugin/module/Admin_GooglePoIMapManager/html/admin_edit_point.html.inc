<?php
/*
 * CaMykS Engine
 * Developed by	    : Ideogram Design
 * Author	    : JB Lebrun <jb.lebrun@ideogram-design.fr>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type	    : Plugin / Module Layout
 * Create Date	    : Jun 2010
 * Last Modif Date  : Jun 2010
 * 
 * Admin_GooglePoIMapManager Module Admin Layout : edit_point
 */
global $camyks;

/* load used icons */
$target = $this->theme->get_pictURL('target', 12, 'std');
$target_ = $this->theme->get_pictURL('target', 12, 'ovr');
?>
<?=$this->theme->get_boxHeader('width:610px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->adminTitle);?>
<?=$this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams);?>
<?=$this->theme->get_boxContent2Header();?>
<?=$this->editform->display_header(); ?>
<?=$this->editform->display_hiddens(); ?>
<div id="itemproperties" style="display:<?=$this->tabBuilder->get_tabDisplay('properties');?>;" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">

<tr>
<td class="eTableLine0 eContent2" style="width:100px;">
<?=$camyks->get_translation('formitem_status')?>
</td>
<td class="eTableLine0 eContent1" colspan="3">
<?=$this->editform->display_selectInput(array('name'=>'status', 'values'=>$this->get_pointStatusList()));?>
</td>
</tr>

<tr>
<td class="eTableLine1 eContent2">
<?=$camyks->get_translation('formitem_category')?>
</td>
<td class="eTableLine1 eContent1" colspan="3">
<?=$this->editform->display_selectInput(array('name'=>'category', 'values'=>$this->get_categoryTitleList()));?>
</td>
</tr>

<tr>
<td class="eTableLine0 eContent2">
<?=$this->get_translation('formitem_icon')?>
</td>
<td class="eTableLine0 eContent1" colspan="3">
  <?=$this->editform->display_selectInput(array('name'=>'icon', 'values'=>$this->get_iconNameList(array('none'=>true))));?>
</td>
</tr>

<tr>
<td class="eTableHeader" colspan="4">
<?=$this->get_translation('formtitle_location')?>
</td>
</tr>

<tr>
  <td class="eTableLine0 eContent2">
    <?=$camyks->get_translation('formitem_address');?>
  </td>
  <td class="eTableLine0 eContent1">
    <?=$this->editform->display_textInput('address1');?>
  </td>
  <td class="eTableLine0 eContent2" colspan="2" style="text-align:right;">
    <a href="javascript:pe.get_pointPositionFromAddress();" class="eLink1">
    <img src="<?=$target?>" border="0"
      style="float:right;"
      alt="<?=$this->get_translation('refreshmapposition');?>"
      title="<?=$this->get_translation('refreshmapposition');?>"
      onmouseover="this.src='<?=$target_?>'"
      onmouseout="this.src='<?=$target?>'" />
      <?=$this->get_translation('refreshmapposition');?>
    </a>
  </td>
</tr>

<tr>
  <td class="eTableLine1 eContent2">
    &nbsp;
  </td>
  <td class="eTableLine1 eContent1" colspan="3">
    <?=$this->editform->display_textInput('address2');?>
  </td>
</tr>

<tr>
  <td class="eTableLine0 eContent2">
    &nbsp;
  </td>
  <td class="eTableLine0 eContent1" colspan="3">
    <?=$this->editform->display_textInput('address3');?>
  </td>
</tr>

<tr>
  <td class="eTableLine1 eContent2">
    <?=$camyks->get_translation('formitem_country');?>
  </td>
  <td class="eTableLine1 eContent1" colspan="3">
    <?=$this->editform->display_selectInput(array('name'=>'country', 'values'=>countries_getList()));?>
  </td>
</tr>

<tr>
  <td class="eTableLine0 eContent2">
    <?=$this->get_translation('formitem_latitude');?>
  </td>
  <td class="eTableLine0 eContent1">
    <?=$this->editform->display_textInput(array('name'=>'latitude', 'class'=>'sinputs'));?>
  </td>
  <td class="eTableLine0 eContent2">
    <?=$this->get_translation('formitem_longitude');?>
  </td>
  <td class="eTableLine0 eContent1">
    <?=$this->editform->display_textInput(array('name'=>'longitude', 'class'=>'sinputs'));?>
  </td>
</tr>
<tr>
  <td class="eTableLine0" colspan="4">
    <div id="GoogleMapBox" style="height:400px; width:560px; margin:0 auto;">
      &nbsp;
    </div>
  </td>
</tr>
</table>
</div>

<?php foreach ( $camyks->get_confValue('editing_languages') as $l ) : ?>
<div id="item<?=$l?>" style="display:<?=$this->tabBuilder->get_tabDisplay($l)?>;" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
  <tr>
    <td class="eTableLine0 eContent2" style="width:100px;">
      <?=$camyks->get_translation('formitem_title')?>
    </td>
    <td class="eTableLine0 eContent1">
       <?=$this->editform->display_textInput(array('name'=>'title', 'language'=>$l));?>
    </td>
  </tr>
  <tr>
    <td class="eTableLine0" colspan="2">
      <?php $this->input->set_contentInfos ('text', $this->pointItem->vars['description_'.$l] ); ?>
      <?php $this->input->set_textareaInfos ('description_'.$l, '100%', '400px'); ?>
      <?php $this->input->display();?>
    </td>
  </tr>
</table>
</div>
<?php endforeach; ?>

<?=$this->editform->display_footer(); ?>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar($this->buttons); ?>
<?=$this->theme->get_boxFooter(); ?>