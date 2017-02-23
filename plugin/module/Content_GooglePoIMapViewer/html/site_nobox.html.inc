<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author	    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type	    : Plugin / Module Layout
 * Creation Date    : Jun 2010
 * Last Modif Date  : Jun 2010
 * 
 * Content_GooglePoIMapViewer Module Point Layout
*/
$mapHeight = 300;
$menuHeight = 200;
$menuWidth = 200;
$descHeight = 200;
$space = 8;

?>
<script>pmv.set_param("GooglePoIMapClass", "eTableHeader");</script>
<?=$this->contentItem->vars['content'];?>
<div>
  <div id="GooglePoIMapBox" style="height:<?=$mapHeight;?>px; margin-bottom:<?=$space?>px;">
    &nbsp;
  </div>
  <div style="width:<?=$menuWidth?>px; float:left;">
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
  <div id="GooglePoIMapMenu" style="height:<?=$menuHeight?>px; overflow:auto;">
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

  <div id="GooglePoIMapDescription" style="margin-left:<?=$menuWidth+$space?>px; height:<?=$descHeight?>px; overflow:auto;">
     &nbsp;
  </div>

  <div style="clear:both;">
    &nbsp;
  </div>
</div>
