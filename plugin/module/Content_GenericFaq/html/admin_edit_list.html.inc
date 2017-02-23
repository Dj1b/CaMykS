<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version       : 1.0a
 * Object Version       : 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Apr 2007
 * Last Modif Date	: Apr 2007
 *
 * Content_GenericFaq Module Admin Layout : edit faq list
 */
	
global $camyks;

/* get imgs urls */
$edit = $camyks->theme->get_pictURL('edit', 12, 'std');
$edit_ = $camyks->theme->get_pictURL('edit', 12, 'ovr');
$up = $camyks->theme->get_pictURL('up', 12, 'std');
$up_ = $camyks->theme->get_pictURL('up', 12, 'ovr');
$down = $camyks->theme->get_pictURL('down', 12, 'std');
$down_ = $camyks->theme->get_pictURL('down', 12, 'ovr');
$del = $camyks->theme->get_pictURL('cross', 12, 'std');
$del_ = $camyks->theme->get_pictURL('cross', 12, 'ovr');
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title .' : '.
				 $this->faqlist->vars['name'].' ['.
				 $this->faqlist->id . ']'
				 );?>
<?php if ( $this->faqlist->id > 0 ) : ?> 
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
  <table cellspacing="0" cellpadding="0" border="0" width="100%">
    <tr>
      <td class="listline0" style="width:200px;">
	<?=$this->get_translation('name')?> : 
      </td>
      <td class="listline0">
	<input type="text" name="name" value="<?=$this->faqlist->vars['name']?>" maxlength="64" class="inputs" /></input>
      </td>
    </tr>
    <tr>
      <td class="listline1">
	<?=$this->get_translation('count_list')?> : 
      </td>
      <td class="listline1">
	<input type="text" name="count_list" value="<?=$this->faqlist->vars['count_list']?>" maxlength="2" class="inputs" /></input>
      </td>
    </tr>
    <tr>
      <td class="listline0">
	<?=$this->get_translation('layout_list')?> : 
      </td>
      <td class="listline0">
	<select name="layout_list">
	  <?php foreach ( $this->layouts_list as $l ) : ?>
	  <option value="<?=$l?>"<?=( $this->faqlist->vars['layout_list'] == $l ? ' selected="selected"':'')?>>
	    <?=$this->get_translation($l) ?>
	  </option>
	  <?php endforeach; ?>
	</select>
    </td>
    </tr>
  </table>
  <?=$this->form->display_footer()?>
</div>
  
<div id="itemitems" style="display:none;" class="adminContentPanel">
  <table cellspacing="0" cellpadding="0" border="0" width="100%">
    <tr>
      <td class="listheader" style="width:20px;">
	#
      </td>
      <td class="listheader">
	<?= $this->get_translation('status'); ?>
      </td>
      <td class="listheader">
	<?= $this->get_translation('faqtitle'); ?>
      </td>
      <td class="listheader">
	<?= $this->get_translation('language'); ?>
      </td>
      <td class="listheader" style="width:12px;">
	&nbsp;
      </td>
      <td class="listheader" style="width:12px;">
	&nbsp;
      </td>
      <td class="listheader" style="width:12px;">
	&nbsp;
      </td>
      <td class="listheader" style="width:12px;">
	&nbsp;
      </td>
    </tr>
    <tr>
      <td class="listline1" colspan="8">
	<a href="<?=$this->linknew?>"
	  style="font-weight:bold; color: #888888;">
	  <?= $this->get_translation('newitem'); ?>
	</a>
      </td>
    </tr>
    <?php $alt=0; ?>
    <?php $cnt=0; ?>
    <?php foreach ( $this->faqitems as $n ) : ?>
    <tr>
      <td class="listline<?=$alt?>">
	<?= $n->vars['position'] ?>
      </td>
      <td class="listline<?=$alt?>">
	<?=$this->get_translation($this->status[$n->vars['status']] ); ?>
      </td>
      <td class="listline<?=$alt?>">
	<?php if ( strlen ( $n->vars['title'] ) > 48 ) : ?>
	<?=substr($n->vars['title'], 0, 48 )?>...
	<?php else : ?>
	<?=$n->vars['title'];?>
	<?php endif; ?>
      </td>
      <td class="listline<?=$alt?>">
	<?=$n->vars['language']?>
      </td>
      <td class="listline<?=$alt?>">
	<a href="<?=$this->linkedit.$n->id?>">
	<img src="<?=$edit?>"
	  alt="<?=$this->get_translation('edit')?>" border="0"
	  style="cursor:pointer;"
	  onmouseover="this.src='<?=$edit_?>';"
	  onmouseout="this.src='<?=$edit?>';" />
	</a>
      </td>
      
      <td class="listline<?=$alt?>">
	<?php if ( $cnt > 0 ) : ?> 
	<a href="<?=$this->linkup.$n->id?>">
	  <img src="<?=$up?>" 
	    onmouseover="this.src='<?=$up_?>'"
	    onmouseout="this.src='<?=$up?>'"
	    border="0" alt="" />
	</a>
	<?php else : ?>
	&nbsp;
	<?php endif; ?>
      </td>
      
      <td class="listline<?=$alt?>">
	<?php if ( $cnt < count($this->faqitems)-1 ) : ?>
	<a href="<?=$this->linkdown.$n->id?>">
	  <img src="<?=$down?>"
	    onMouseOver="this.src='<?=$down_?>'"
	    onMouseOut="this.src='<?=$down?>'"
	    border="0" alt="" />
	</a>
	<?php else : ?>
	&nbsp;
	<?php endif; ?>
      </td>
      
      <td class="listline<?=$alt?>">
	<a href="javascript:if(confirm('<?=$this->get_translation('js_delete')?>')){document.location.href='<?=$this->linkdelete.$n->id?>';}">
	  <img src="<?=$del?>"
	    onMouseOver="this.src='<?=$del_?>'"
	    onMouseOut="this.src='<?=$del?>'"
	    border="0" alt="" />
	</a>
      </td>
    </tr>
    <?php $cnt++; ?>
    <?php $alt=abs ( $alt-1 ); ?>
    <?php endforeach; ?> 
  </table>
</div>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar($this->buttons);?>
<?=$this->theme->get_boxFooter(); ?>
