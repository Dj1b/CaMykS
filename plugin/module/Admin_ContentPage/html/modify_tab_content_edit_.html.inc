<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0b
 * Object Version	: 1.0
 * Object Type      : Plugin / Module Layout
 * Creation Date	: Jun 2005
 * Last Modif Date  : Oct 2009
 *
 * Admin_ContentPage Module Layout : Page editor content tab
 */
global $camyks;

/* get images URL */
$edit = $this->theme->get_pictURL('edit', 12, 'std');
$edit_ = $this->theme->get_pictURL('edit', 12, 'ovr');
$edit_content = $this->get_fileURL('img/edit_content.gif');
?>
<div id="itemcontent" style="display:<?=$this->tabBuilder->get_tabDisplay('content')?>;" class="adminControlPanel">
  <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
    <?php if ( count($this->models) > 0 ) : ?>
    <tr>
      <td class="contentpagecontentcol" colspan="2">
	<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
	  <tr>
	    <td class="eTableLine1 eContent2">
	      <?=$this->get_translation('formitem_model');?>
	    </td>
	    <td class="eTableLine1 eContent1">
	      <select name="model" class="inputs" onchange="contentpage_selectModel();">
		<?php if ($this->check_right(6)): ?>
		<option value="">
		   <?=$this->get_translation('none');?>
		</option>
		<option value="" disabled="disabled">
		  ----------------
		</option>
		<?php endif; ?>
		<?php foreach ( $this->models as $model ) : ?>
		<option value="<?=$model->id?>">
		  <?=$model->name?>
		</option>
		<?php endforeach; ?>
	      </select>
	    </td>
	  </tr>
	</table>
      </td>
    </tr>
    <?php endif; ?>
    <tr>
      <td class="contentpagecontentcol">
	<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
	  <tr>
	    <td class="eTableLine0 eContent2" style="width:80px;">
	      <?=$this->get_translation('formitem_theme');?>
	    </td>
	    <td class="eTableLine0 eContent1">
	      <select name="theme" class="inputs" onchange="contentpage_updateTheme()">
		<option value="">
                  <?=$this->get_translation('defaultfromsite');?>
		</option>
		<option value="" disabled="disabled">
		  ----------------
		</option>
		<?php foreach ( $camyks->themes as $theme ) : ?>
		<option value="<?=$theme->name?>"<?=($theme->name==$this->page->theme ? ' selected="selected"':'')?>>
		  <?=$theme->title?>
		</option>
		<?php endforeach; ?>
	      </select>
	    </td>
	  </tr>
	  <tr>
	    <td class="eTableLine0 eContent2">
              <?=$this->get_translation('formitem_template')?>
	    </td>
	    <td class="eTableLine0 eContent1">
	      <select name="template" class="inputs" onchange="contentpage_updateTemplate()">
		<option value="">
		  <?=$this->get_translation('defaultfromsite')?>
		</option>
		<option value="" disabled="disabled">
		  ----------------
		</option>
		<?php foreach ( $camyks->templates as $t ) : ?>
		<option value="<?=$t->name?>"<?=($t->name==$this->page->template?' selected="selected"':'')?>>
		  <?=$t->title?>
		</option>
		<?php endforeach; ?>
	      </select>
	    </td>
	  </tr>
	  <tr>
	    <td class="eTableLine0 eContent1">
              &nbsp;
            </td>
	    <td class="eTableLine0">
	      <?php foreach ( $camyks->templates as $t ) : ?>
	      <div id="template_<?=$t->name?>" style="display:none;width:202px;height:122px;overflow:hidden;">
		<?=$t->display_thumb()?>
	      </div>
	      <?php endforeach; ?>
	    </td>
	  </tr>
	</table>
      </td>
      <td class="contentpagecontentcol">
	<table cellspacing="0" cellpadding="2" border="0" style="width:100%;">
	  <tr>
	    <td class="eTableLine0 eContent2">
	      <?=$this->get_translation('formitem_modules');?>
	    </td>
	  </tr>
	  <tr>
	    <td class="eTableLine0">
	      <div style="width:100%;height:400px;overflow:auto;">
		<?php $alt=1; ?>
		<?php for( $i=0; $i< $this->page->maxmodules; $i++ ) : ?>
		<?php $m = &$this->page->modules[$i];?>
		<div id="module<?=$i?>" style="display:block;padding-bottom:4px;;">
		  <table cellspacing="0" cellpadding="0" border="0" width="100%">
		    <tr>
		      <td class="eTableHeader" colspan="2">
                        <div id="module_editbutton<?=$i?>" style="display:block; float:right;">
			  <a href="javascript:contentpage_editModule(<?=$i?>);">
  <img src="<?=$edit?>" border="0"
    alt="<?=$this->get_translation('edit_module')?>"
    title="<?=$this->get_translation('edit_module')?>"
    onmouseover="this.src='<?=$edit_?>';"
    onmouseout="this.src='<?=$edit?>';" style="float:right;margin-left:8px;" />
  <?=$camyks->get_translation('edit');?></a>
                        </div>
                        <?=$this->get_translation('blockx', ($i+1));?>
		      </td>
		    </tr>
		    <tr>
		      <td class="eTableLine<?=$alt;?> eContent2">
			<?=$this->get_translation('formitem_module');?>
		      </td>
		      <td class="eTableLine<?=$alt;?>" style="width:200px;">
			<select name="m<?=$i?>_name" onchange="contentpage_updateModule(<?=$i?>);" class="inputs">
			  <option value="">
			    <?=$this->get_translation('none')?>
			  </option>
			  <?php foreach ( $this->modules as $name => $title ) : ?>
			  <option value="<?=$name?>"<?= $m['name'] == $name?' selected="selected"':''?>>
                            <?=$title ?>
                          </option>
			  <?php endforeach; ?>
			</select>
		      </td>
		    </tr>
		    <tr>
		      <td class="eTableLine<?=$alt;?> eContent2">
                        <img src="<?=$edit_content?>" alt="" border="0" style="float:left; margin:0 4px 0 0;" />
                        <?=$this->get_translation('formitem_content')?>
		      </td>
		      <td class="eTableLine<?=$alt;?>">
			<select name="m<?=$i?>_content" class="inputs" onchange="contentpage_updateModuleContent();">
                          <option value=""></option>
			</select>
		      </td>
		    </tr>
                    <?php if ($this->allow_theme_change) : ?>
		    <tr>
		      <td class="eTableLine<?=$alt;?> eContent2">
			<?=$this->get_translation('formitem_theme');?>
		      </td>
		      <td class="eTableLine<?=$alt;?> eContent1">
			<select name="m<?=$i?>_theme" class="inputs" onchange="contentpage_updateModuleTheme();">
			  <option value="">
			    <?=$this->get_translation('defaultfrompage')?>
			  </option>
			  <option value="" disabled="disabled">
			    ----------------
			  </option>
			  <?php foreach ( $camyks->themes as $t ) : ?>
			  <option value="<?=$t->name?>"<?=$t->name==$m['theme']?' selected':''?>>
			    <?=$t->title?>
			  </option>
			  <?php endforeach; ?>
			</select>
		      </td>
		    </tr>
		    <?php endif; ?>
		  </table>
		</div>
		<?php $alt=abs( $alt-1 ); ?>
		<?php endfor; ?>
	      </div>
	    </td>
	  </tr>
	</table>
      </td>
    </tr>
  </table>
</div>