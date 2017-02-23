<?php
/*
 * CaMyks Engine
 * Developed by	    : camyks.net
 * Author	    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type	    : Plugin / Module Layout
 * Create Date	    : Jun 2010
 * Last Modif Date  : Jun 2010
 * 
 * Content_GooglePoIMapViewer Module Admin Layout
*/		
global $camyks;

/* build zoomList */
$zoomList = array();
for ( $i=1; $i<17; $i++ )
  $zoomList[$i] = $i;
?>
<?=$this->theme->get_boxHeader('width:610px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title .' : '.
				 $this->contentItem->vars['name'] .' ['.
				 $this->contentItem->id . ']');?>
<?=$this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams);?>
<?=$this->theme->get_boxContent2Header(); ?>
<?=$this->form->display_header()?>
<?=$this->form->display_hiddens()?>
<div id="itemproperties" style="display:<?=$this->tabBuilder->get_tabDisplay('properties')?>;" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
  <tr>
    <td class="eTableLine0 eContent2" style="width:150px;">
      <?=$camyks->get_translation('formitem_name')?>
    </td>
  <td class="eTableLine0">
    <?=$this->form->display_textInput('name');?>
  </td>
</tr>

  <tr>
    <td class="eTableLine1 eContent2">
      <?=$this->get_translation('formitem_layout')?>
    </td>
  <td class="eTableLine1">
    <?=$this->form->display_selectInput(array('name'=>'layout', 'values'=>$this->get_layoutList()));?>
  </td>
</tr>

  <tr>
    <td class="eTableLine0 eContent2">
      <?=$this->get_translation('formitem_category_selection')?>
    </td>
  <td class="eTableLine0">
    <?=$this->form->display_booleanSelectInput('category_select');?>
  </td>
</tr>

  <tr>
    <td class="eTableLine1 eContent2">
      <?=$this->get_translation('formitem_country_selection')?>
    </td>
  <td class="eTableLine1">
    <?=$this->form->display_booleanSelectInput('country_select');?>
  </td>
</tr>

  <tr>
    <td class="eTableLine0 eContent2">
      <?=$this->get_translation('formitem_displayed_categories')?>
    </td>
    <td class="eTableLine0">
    <input type="checkbox" name="categoryall" id="categoryall" value="1" <?=$this->contentItem->vars['categories'] == ''?'checked="checked"':''?> onchange="poimapviewer_checkAll();" /> 
    <label for="categoryall">
    <?=$this->get_translation('categories_all');?>
    </label>
  </td>
</tr>
  
<?php $cnt = 0; ?>
<?php $alt = 0; ?>
<?php foreach ($this->categoryList as $cid => $cname) : ?>
<?php if ($alt == 0 ) : ?>
  <tr>
    <td class="eTableLine0 eContent2">
      &nbsp;    
    </td>
<?php endif; ?> 
    <td class="eTableLine0">
      <input type="checkbox" name="category<?=$cnt;?>" id="category<?=$cnt;?>" value="<?=$cid?>" 
    <?=(in_array($cid, $this->contentItem->vars['categories_']) or $this->contentItem->vars['categories'] == '') ?'checked="checked"':''?>
    <?=$this->contentItem->vars['categories'] == '' ?'disabled="disabled"':''?> />
    <label for="category<?=$cnt++?>">
    <?=$cname;?>
    </label>
    </td>
    <?php if ($alt==1) : ?>
  </tr>
      <?php endif; ?>
<?php $alt = abs($alt-1);?>
<?php endforeach; ?>

<?php if ($alt==1) : ?>
    <td class="eTableLine0">
       &nbsp;
    </td>
  </tr>
<?php endif; ?>

  <tr>
    <td class="eTableLine1 eContent2">
      <?=$this->get_translation('formitem_default_zoom')?>
    </td>
  <td class="eTableLine1">
    <?=$this->form->display_selectInput(array('name'=>'default_zoom', 'values'=>$zoomList));?>
  </td>
</tr>

	<tr>
    <td class="eTableHeader" colspan="2">
      <?=$this->get_translation('formtitle_geolocalisation')?>
    </td>
	</tr>
	
	<tr>
    <td class="eTableLine0 eContent2">
      <?=$camyks->get_translation('formitem_status')?>
    </td>
  <td class="eTableLine0">
    <?=$this->form->display_selectInput(array('name'=>'geo_status', 'values'=>$this->get_geoStatusList()));?>
  </td>
</tr>

<tr>
    <td class="eTableLine1 eContent2">
      <?=$this->get_translation('formitem_icon')?>
    </td>
  <td class="eTableLine1">
    <?=$this->form->display_selectInput(array('name'=>'geo_icon', 'values'=>$this->get_iconTitleList()));?>
  </td>
</tr>
<tr>
    <td class="eTableLine0 eContent2">
      <?=$this->get_translation('formitem_default_zoom')?>
    </td>
  <td class="eTableLine0">
    <?=$this->form->display_selectInput(array('name'=>'geo_zoom', 'values'=>$zoomList));?>
  </td>
</tr>


</table>
</div>

<?php foreach ( $this->elgs as $l ) : ?>
<div id="item<?=$l?>" style="display:<?=$this->tabBuilder->get_tabDisplay($l);?>;" class="adminContentPanel">
<?php $this->editor->set_contentInfos('text', $this->contentItem->vars['content_'.$l] ); ?>
<?php $this->editor->set_textareaInfos('content_'.$l, '100%', '400px'); ?>
<?php $this->editor->display();?>
</div>
<?php endforeach; ?>

<?=$this->form->display_footer()?>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?=$this->theme->get_boxFooter(); ?>