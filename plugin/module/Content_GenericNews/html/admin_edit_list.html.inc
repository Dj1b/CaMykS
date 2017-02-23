<?php
/*
 * CaMyks Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Mar 2007
 * Last Modif Date	: May 2008
 * 
 * Content_GenericNews Module Admin  Layout : edit news list
*/		
global $camyks;
$edit = $this->theme->get_pictURL('edit', 12, 'std');
$edit_ = $this->theme->get_pictURL('edit', 12, 'ovr');
$add = $this->theme->get_pictURL('plus', 12, 'std');
$add_ = $this->theme->get_pictURL('plus', 12, 'ovr');
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title .' : '.
				 $this->newslist->vars['name'] .' ['.
				 $this->newslist->id . ']');?>
<?php if ( $this->newslist->id > 0 ) : ?> 
<?=$this->theme->get_boxTabsBar($this->tabs,
				$this->tabObject.'.mouseclick',
				$this->tabObject.'.mouseover',
				$this->tabObject.'.mouseout',
				'properties');?>
<?php endif; ?>
<?=$this->theme->get_boxContent2Header(); ?>
<div id="itemproperties" style="display:block;" class="adminContentPanel">
  <?=$this->form->display_header()?>
  <?=$this->form->display_hiddens()?>
  <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
    <tr>
      <td class="listline0" style="width:200px;">
	<?=$this->get_translation('name')?> : 
      </td>
      <td class="listline0">
	<input type="text" name="name" value="<?=$this->newslist->vars['name']?>" maxlength="64" class="inputs" />
      </td>
    </tr>
    <tr>
      <td class="listline1">
	<?=$this->get_translation('count_list')?> : 
      </td>
      <td class="listline1">
	<input type="text" name="count_list" value="<?=$this->newslist->vars['count_list']?>" maxlength="2" class="inputs"/>
      </td>
    </tr>
    <tr>
      <td class="listline0">
	<?=$this->get_translation('layout_list')?> : 
      </td>
      <td class="listline0">
	<select name="layout_list" class="inputs">
	  <?php foreach ( $this->layouts_list as $l ) : ?>
	  <option value="<?=$l?>"<?=( $this->newslist->vars['layout_list'] == $l ? ' selected="selected"':'')?>>
	    <?=$this->get_translation($l) ?>
	  </option>
	  <?php endforeach; ?>
	</select>
      </td>
    </tr>
    <tr>
      <td class="listline1">
	<?=$this->get_translation('layout_item')?> : 
      </td>
      <td class="listline1">
	<select name="layout_item" class="inputs">
	  <?php foreach ( $this->layouts_item as $l ) : ?>
	  <option value="<?=$l?>"<?=( $this->newslist->vars['layout_item'] == $l ? ' selected="selected"':'')?>>
	    <?=$this->get_translation($l) ?>
	  </option>
	  <?php endforeach; ?>
	</select>
      </td>
    </tr>
  </table>
  <?=$this->form->display_footer()?>
</div>
<div id="itemnewsitems" style="display:none;" class="adminContentPanel">
  <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
    <tr>
      <td class="listline0">
	&nbsp;
      </td>
      <td class="listline0" colspan="4">
	<a href="<?=$this->linkedit?>0">
	  <?= $this->get_translation('newnews'); ?>
	</a>
      </td>
      <td class="listline0">
	<a href="<?=$this->linkedit?>0">
	  <img src="<?=$add?>" alt="" border="0"
	    onmouseover="this.src='<?=$add_?>';"
	    onmouseout="this.src='<?=$add?>';" />
	</a>
      </td>
      <td class="listline0">
	&nbsp;
      </td>
    </tr>
    
    <tr>
      <td class="listheader" style="width:12px;">
	&nbsp;
      </td>
      <td class="listheader" style="width:20px;">
	&nbsp;
      </td>
      <td class="listheader" style="width:90px;">
	<?= $this->get_translation('date'); ?>
      </td>
      <td class="listheader">
	<?= $this->get_translation('author') ?>
      </td>
      <td class="listheader">
	<?= $this->get_translation('newstitle'); ?>
      </td>
      <td class="listheader" style="width:12px;">
	&nbsp;
      </td>
      <td class="listheader" style="width:12px;">
	&nbsp;
      </td>
    </tr>
    
    <?php $alt=1; ?>
    <?php foreach ( $this->newsitems as $n ) : ?>
    <tr>
      <td class="listline<?=$alt?>">
        <input type="checkbox" disabled="disabled" <?=$n->vars['status']==1?' checked="checked"':''?> />
      </td>
      <td class="listline<?=$alt?>">
	<?=language_getIcon($n->vars['language']);?>
      </td>
      <td class="listline<?=$alt?>">
	<?= date_displayNumericDateHour($n->vars['ndate']) ?>
      </td>
      <td class="listline<?=$alt?>">
	<?=$n->vars['author']?>
      </td>
      <td class="listline<?=$alt?>">
	<?=$n->vars['title']?>
      </td>
      <td class="listline<?=$alt?>">
	<a href="<?=$this->linkedit.$n->id?>">
	  <img src="<?=$edit?>" alt="<?=$this->get_translation('edit')?>" border="0"
	    onmouseover="this.src='<?=$edit_?>';"
	    onlouseout="this.src='<?=$edit?>';" />
	</a>
      </td>
      <td class="listline<?=$alt?>">
	&nbsp;
      </td>  
    </tr>
    <?php $alt=abs($alt-1);?>
    <?php endforeach; ?> 
    <tr>
      <td colspan="7" class="listheader">
	<table cellspacing="0" cellpadding="0" border="0" style="width:100%">
	  <tr>
	    <td style="width:30%; text-align:left;font-weight:bold;color:#666666;">
	      <?php if ( $this->newspage > 0 ) : ?>
	      <a href="<?= $this->linkprevious ?>"
		style="color:white;font-weight:bold;">
		<?=$this->get_translation('previous');?>
	      </a>
	      <?php else : ?>
	      <?=$this->get_translation('previous');?>
	      <?php endif; ?>
	    </td>
	    <td style="width:40%; text-align:center;font-weight:bold;color:white;">
	      <?=$this->get_translation('newscount', $this->newscount)?>
	    </td>
	    <td style="width:30%; text-align:right;font-weight:bold;color:#666666;">
	      <?php if ( $this->newscount > ($this->newspage+1)*$this->newsbypage ) : ?>
	      <a href="<?= $this->linknext ?>"
		style="color:white; font-weight:bold;">
		<?=$this->get_translation('next');?>
	      </a>
	      <?php else : ?>
	      <?=$this->get_translation('next');?>
	      <?php endif; ?>
	    </td>
	  </tr>
	</table>
      </td>
    </tr>
  </table>
</div>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?=$this->theme->get_boxFooter(); ?>
