<?php
/*
 * CaMyks Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Sep 2008
 * Last Modif Date	: Sep 2008
 * 
 * Content_GoogleSearchResultsViewer Module Admin Layout
*/		
global $camyks;

$target = $this->theme->get_pictUrl('target', 12, 'std');
$target_ = $this->theme->get_pictUrl('target', 12, 'ovr');
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title .' : '.
				 $this->gsrItem->vars['name'] .' ['.
				 $this->gsrItem->id . ']');?>
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
	<input type="text" name="name" value="<?=$this->gsrItem->vars['name']?>" maxlength="32" class="inputs" />
      </td>
    </tr>
    <tr>
      <td class="listline1">
	<?=$this->get_translation('itemlayout')?> 
      </td>
      <td class="listline1">
	<select name="layout" class="inputs">
	  <?php foreach ( $this->get_layouts() as $name => $title ) : ?>
	  <option value="<?=$name?>"<?=( $this->gsrItem->vars['layout'] == $name ? ' selected="selected"':'')?>>
	    <?=$title ?>
	  </option>
	  <?php endforeach; ?>
	</select>
      </td>
    </tr>
    
    <tr>
      <td class="listheader" colspan="2">
	<?=$this->get_translation('title_gsrsettings');?>
      </td>
    </tr>
    <tr>
      <td colspan="2" style="">
	<div id="itemgsrimporterpanel"<?=$this->gsrItem->id==0?'':' style="display:none;"'?>>
	  <div class="content2">
	    <?=$this->get_translation('itemgsrsourceimport')?>
	  </div>
	  <div>
	    <textarea id="gsrimporter" class="mceNoEditor" cols="40" rows="4" style="width:100%" onchange="googlesearchresultsviewer_importgsr();"></textarea>
	  </div>
	</div>
	<div id="itemgsrpanel"<?=$this->gsrItem->id==0?' style="display:none;"':''?>>
	  <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
	    
	    <tr>
	      <td class="listline0" style="width:200px;">
		<?=$this->get_translation('itemgsrsearchdomain')?> 
	      </td>
	      <td class="listline0">
		<input type="text" name="sr_searchdomain" value="<?=$this->gsrItem->vars['sr_searchdomain']?>" maxlength="255" class="inputs" />
	      </td>
	      <td class="listline0" style="width:12px;">
		<a href="javascript:googlesearchresultsviewer_resetgsr();">
		  <img src="<?=$target?>" border="0"
		    alt="<?=$this->get_translation('resetgsrparameters');?>"
		    title="<?=$this->get_translation('resetgsrparameters');?>"
		    onmouseover="this.src='<?=$target_?>';" onmouseout="this.src='<?=$target?>';" />
		</a>
	      </td>
	    </tr>
	    
	    <tr>
	      <td class="listline1">
		<?=$this->get_translation('itemgsrwidth')?> 
	      </td>
	      <td class="listline1" colspan="2">
		<input type="text" name="sr_width" value="<?=$this->gsrItem->vars['sr_width']?>" maxlength="5" class="inputs" />
	      </td>
	    </tr>
	  </table> 
	</div>
      </td>
    </tr>
  </table>
</div>
<?=$this->form->display_footer()?>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?=$this->theme->get_boxFooter(); ?>