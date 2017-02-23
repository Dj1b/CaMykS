<?php
/*
 * CaMyks Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Jul 2008
 * Last Modif Date	: Jul 2008
 * 
 * Content_GoogleMapsViewer Module Admin Layout
*/		
global $camyks;

$target = $this->theme->get_pictUrl('target', 12, 'std');
$target_ = $this->theme->get_pictUrl('target', 12, 'ovr');
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar( $this->title .' : '.
				  $this->mapItem->vars['name'] .' ['.
				  $this->mapItem->id . ']');?>
<?=$this->theme->get_boxTabsBar( $this->tabs,
				 $this->tabObject.'.mouseclick',
				 $this->tabObject.'.mouseover',
				 $this->tabObject.'.mouseout',
				 'properties');?>
<?=$this->theme->get_boxContent2Header(); ?>
<?=$this->form->display_header()?>
<?=$this->form->display_hiddens()?>
<div id="itemproperties" class="adminContentPanel">
  <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
    <tr>
      <td class="listheader" colspan="2">
        <?=$this->get_translation('title_globalsettings');?>
      </td>
    </tr>
    <tr>
      <td class="listline0" style="width:200px;">
        <?=$this->get_translation('itemname')?> 
      </td>
      <td class="listline0">
        <input type="text" name="name" value="<?=$this->mapItem->vars['name']?>" maxlength="32" class="inputs" />
      </td>
    </tr>
<tr>
  <td class="listline1">
    <?=$this->get_translation('itemlayout')?> 
  </td>
  <td class="listline1">
    <select name="layout" class="inputs">
<?php foreach ( $this->get_layouts() as $name => $title ) : ?>
<option value="<?=$name?>"<?=( $this->mapItem->vars['layout'] == $name ? ' selected="selected"':'')?>>
<?=$title ?>
</option>
<?php endforeach; ?>
    </select>
  </td>
</tr>

<tr>
 <td class="listheader" colspan="2">
<?=$this->get_translation('title_mapsettings');?>
</td>
</tr>
<tr>
 <td colspan="2" style="">
    <div id="itemmapimporterpanel"<?=$this->mapItem->id==0?'':' style="display:none;"'?>>
      <div class="content2">
        <?=$this->get_translation('itemmapsourceimport')?>
      </div>
      <div>
        <textarea id="mapimporter" class="mceNoEditor" cols="40" rows="4" style="width:100%" onchange="googlemapsviewer_importmap();"></textarea>
      </div>
    </div>
    <div id="itemmappanel"<?=$this->mapItem->id==0?' style="display:none;"':''?>>
      <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
  
    <tr>
      <td class="listline0" style="width:200px;">
        <?=$this->get_translation('itemmapbaseurl')?> 
      </td>
      <td class="listline0">
        <input type="text" name="map_baseurl" value="<?=$this->mapItem->vars['map_baseurl']?>" maxlength="255" class="inputs" />
      </td>
      <td class="listline0" style="width:12px;">
        <a href="javascript:googlemapsviewer_resetmap();">
          <img src="<?=$target?>" alt="<?=$this->get_translation('resetmapparameters');?>" border="0"
           onmouseover="this.src='<?=$target_?>';" onmouseout="this.src='<?=$target?>';" />
        </a>
      </td>
    </tr>
    
    <tr>
      <td class="listline1">
        <?=$this->get_translation('itemmapcode')?> 
      </td>
      <td class="listline1" colspan="2">
        <input type="text" name="map_code" value="<?=$this->mapItem->vars['map_code']?>" maxlength="64" class="inputs" />
      </td>
    </tr>
    
    <tr>
      <td class="listline0">
        <?=$this->get_translation('itemmapzoom')?> 
      </td>
      <td class="listline0" colspan="2">
        <select name="map_zoom" class="inputs">
        <option value="1"<?=$this->mapItem->vars['map_zoom']==1?' selected="selected"':''?>><?=$this->get_translation('itemmapzoommin')?></option>
        <?php for ($i=2; $i<16; $i++ ): ?>
          <option value="<?=$i?>"<?=$this->mapItem->vars['map_zoom']==$i?' selected="selected"':''?>><?=$i?></option>
        <?php endfor; ?>
        <option value="16"<?=$this->mapItem->vars['map_zoom']==16?' selected="selected"':''?>><?=$this->get_translation('itemmapzoommax')?></option>
        </select>
      </td>
    </tr>
    
    <tr>
      <td class="listline1">
        <?=$this->get_translation('itemmapwidth')?> 
      </td>
      <td class="listline1" colspan="2">
        <input type="text" name="map_width" value="<?=$this->mapItem->vars['map_width']?>" maxlength="4" /> px
      </td>
    </tr>
    
    <tr>
      <td class="listline0">
        <?=$this->get_translation('itemmapheight')?> 
      </td>
      <td class="listline0" colspan="2">
        <input type="text" name="map_height" value="<?=$this->mapItem->vars['map_height']?>" maxlength="4" /> px
      </td>
    </tr>
    <tr>
      <td class="listline1" colspan="3">
        <a id="googleaccesslink" href="<?=$this->mapItem->id==0?'':$this->mapItem->vars['map_baseurl'].'&amp;z='.$this->mapItem->vars['map_zoom'].'&amp;source=embed'?>" class="link1" target="_blank"><?=$this->get_translation('admin_googleaccess')?></a>
      </td>
    </tr>
    </table>
    </div>
     </td>
</tr>


<tr>
  <td class="listheader" colspan="2">
    <?=$this->get_translation('title_linksettings');?>
  </td>
</tr>
    <tr>
      <td class="listline0" style="width:200px;">
        <?=$this->get_translation('itemlinkenabled')?> 
      </td>
      <td class="listline0">
        <input type="checkbox" name="link_enabled" value="1"<?=$this->mapItem->vars['link_enabled']==1?' checked="checked"':''?> onchange="googlemapsviewer_updatelinkpanel();" />
      </td>
    </tr>
    <tr>
      <td colspan="2">
      <div id="itemlinkpanel" style="display:none;">
      <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
    <tr>
      <td class="listline1" style="width:200px;">
        <?=$this->get_translation('itemlinkclass')?> 
      </td>
      <td class="listline1">
        <select name="link_class" class="inputs" onchange="googlemapsviewer_updatelinkstylespanel();" />
          <option value="0"<?=$this->mapItem->vars['link_class']==0?' selected="selected"':''?>><?=$this->get_translation('itemlinkclass_specific')?></option>
          <option value="1"<?=$this->mapItem->vars['link_class']==1?' selected="selected"':''?>>link1</option>
          <option value="2"<?=$this->mapItem->vars['link_class']==2?' selected="selected"':''?>>link2</option>
        </select>
      </td>
    </tr>
    <tr>
      <td class="listline0">
        &nbsp;
      </td>
      <td class="listline0">
        <div id="itemlinkstylespanel">
          <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
            <tr>
              <td class="">
                <?=$this->get_translation('itemlinkcolor')?> 
              </td>
              <td class="">
                <?php if ($this->colorPicker===false) : ?>
                  <input type="text" name="link_color" maxlength="7" class="inputs" />
                <?php else : ?>
                  <?=$this->colorPicker->display('link_color',$this->mapItem->vars['link_color']);?>
                <?php endif; ?>
              </td>
              <td class="">
                <?=$this->get_translation('itemlinksize')?> 
              </td>
              <td class="" colspan="2">
                <select name="link_size">
                  <?php for($i=8; $i<20; $i++ ) : ?>
                    <option value="<?=$i?>"<?=$this->mapItem->vars['link_size']==$i?' selected="selected"':''?>><?=$i?></option>
                  <?php endfor;?>
                </select> px
              </td>
            </tr>
            <tr>
              <td class="">
                <?=$this->get_translation('itemlinkbold')?> 
                <input type="checkbox" name="link_bold" value="1"<?=$this->mapItem->vars['link_bold']==1?' checked="checked"':''?> />
              </td>
              <td class="">
                <?=$this->get_translation('itemlinkitalic')?> 
                <input type="checkbox" name="link_italic" value="1"<?=$this->mapItem->vars['link_italic']==1?' checked="checked"':''?> />
              </td>
              <td class="">
                <?=$this->get_translation('itemlinkunderline')?> 
                <input type="checkbox" name="link_underline" value="1"<?=$this->mapItem->vars['link_underline']==1?' checked="checked"':''?> />
              </td>
            </tr>
          </table>
        </div>
      </td>
    </tr>
    </table>
    </div>
    </td>
    </tr>
</table>
</div>

<?php foreach ( $camyks->_conf['editing_languages'] as $l ) : ?>
<div id="itemdesc_<?=$l?>" style="display:none;" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
  <tr>
    <td class="listline0 content2" style="width:200px;">
      <?=$this->get_translation('itemtitle')?> 
  </td>
  <td class="listline0">
    <input type="text" name="title_<?=$l?>" value="<?=$this->mapItem->vars['title_'.$l]?>" maxlength="32" class="inputs" />
  </td>
</tr>
<tr>
  <td class="listline1 content2" colspan="0">
    <?=$this->get_translation('itemdescription')?> 
  </td>
</tr>
<tr>
  <td class="listline1" colspan="0">
    <?php if ($this->webEditor === false ) : ?>
      <textarea name="description_<?=$l?>" cols="40" rows="12" style="width:100%"><?=$this->mapitem->vars['description_'.$l]?></textarea?>
    <?php else : ?>
      <?php $this->webEditor->set_textareaInfos('description_'.$l, '100%', '400px'); ?>
      <?php $this->webEditor->set_contentInfos('text', $this->mapItem->vars['description_'.$l] );?>
      <?php $this->webEditor->display(); ?>
    <?php endif; ?>
  </td>
</tr>
</table> 
</div>
<?php endforeach; ?>

<?=$this->form->display_footer()?>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?=$this->theme->get_boxFooter(); ?>

<?php if ($this->colorPicker!==false) : ?>
<?php $this->colorPicker->display_modalWindow();?>
<?php endif; ?>