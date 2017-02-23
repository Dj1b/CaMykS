<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author	    			: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type	    : Plugin / Module Layout
 * Creation Date    : Jul 2010
 * Last Modif Date  : Jul 2010
 * 
 * Content_GooglePoIMapViewer Module Point Layout
*/
$mapHeight = 250;
?>
<script>pmv.set_param("GooglePoIMapClass", "eTableHeader");</script>
<?=$this->contentItem->vars['content'];?>
<div style="overflow:hidden">
	<div id="GooglePoITabs">
		<?php if ($this->contentItem->vars['geo_status'] == 1) : ?>
		<div id="GooglePoIMapButton" class="eContent1" style="float:right;" onClick="pmv.load_userLocation();">
			<?=$this->get_translation('findmylocation');?>
		</div>
		<?php endif; ?>
		<div id="GooglePoIMapTab" class="eContent2" style="display:inline;margin:4px;" onClick="pmv.select_mapTab();">
			<?=$this->get_translation('tab_map');?>
		</div>
		<div id="GooglePoIListTab" class="eContent1" style="display:inline;margin:4px;" onClick="pmv.select_listTab();">
			<?=$this->get_translation('tab_points');?>
		</div>
	</div>
	<div id="GooglePoIMap">
  	<div id="GooglePoIMapBox" style="height:<?=$mapHeight;?>px;">
    	&nbsp;
  	</div>
  </div>
  <div id="GooglePoIPointList" style="display:none;">
  <?php if ( $this->has_selector == true ) : ?>
    <?=$this->form->display_header(); ?>
    <?=$this->form->display_hiddens(); ?>
    <div style="border:solid 1px #888888; padding:2px">
       <?php $menuHeight -= 4; ?>
      <?php if ( $this->contentItem->vars['category_select'] == 1 ) : ?>
       <?php $menuHeight -= 24; ?>
       <div style="text-align:center; padding:2px 0;">
  <?=$this->form->display_selectInput(array('name'=>'category', 'values'=>$this->categoryList, 'default'=>$this->selCategory, 'class'=>'sinputs', 'onchange'=>'pmv.update_category(this);'));?>
       </div>
       <?php endif; ?>
      <?php if ( $this->contentItem->vars['country_select'] == 1 ) : ?>
       <?php $menuHeight -= 24; ?>
       <div style="text-align:center; padding:2px 0;">
  <?=$this->form->display_selectInput(array('name'=>'country', 'values'=>$this->countryList, 'default'=>$this->selCountry, 'class'=>'sinputs', 'onchange'=>'pmv.update_country(this);'));?>
       </div>
       <?php endif; ?>
    </div>
  <?=$this->form->display_footer();?>
  <?php endif; ?>
  <div id="GooglePoIMapMenu" style="">
    <div>
    <?php $alt = 0; ?>
    <?php foreach($this->pointList as $point) : ?>
      <div id="GooglePoIMapItem<?=$point->id?>" onclick="pmv.select_point(<?=$point->id?>, 'list');" class="eTableLine<?=$alt?>" style="display:block; cursor:pointer;">
        <?=$point->vars['title'];?>
      </div>
    <?php $alt = abs($alt-1); ?>
    <?php endforeach; ?>
    </div>
  </div>
  </div>

  <div id="GooglePoIPointDescription" style="display:none;" onclick="pmv.select_mapTab();">
     &nbsp;
  </div>
</div>
