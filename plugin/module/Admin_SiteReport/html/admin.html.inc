<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Apr 2007
 * Last Modif Date	: Jul 2008
 *
 * Admin_SiteReport Module Admin Layout : list
*/
global $camyks;

/* get imgs url */
$view = $this->theme->get_pictURL('view', 12, 'std');
$view_ = $this->theme->get_pictURL('view', 12, 'ovr');
$edit = $this->theme->get_pictURL('edit', 12, 'std');
$edit_ = $this->theme->get_pictURL('edit', 12, 'ovr');
$del = $this->theme->get_pictURL('cross', 12, 'std');
$del_ = $this->theme->get_pictURL('cross', 12, 'ovr');
$upd = $this->theme->get_pictURL('target', 12, 'std');
$upd_ = $this->theme->get_pictURL('target', 12, 'ovr');

$valid = $this->theme->get_pictURL('valid', 12, 'ovr');
$empty = $this->theme->get_pictURL('empty', 12, 'ovr');

?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title);?>
<?=$this->theme->get_boxTabsBar($this->tabs,
				$this->tabObject.'.mouseclick',
				$this->tabObject.'.mouseover',
				$this->tabObject.'.mouseout',
				'list');?>
<?=$this->theme->get_boxContent2Header();?>
<div id="itemlist" style="display:block;" class="adminContentPanel">
  <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
    <tr>
      <td style="padding:8px 0px;">
	<?=$this->form->display_header();?>
	<?=$this->form->display_hiddens();?>
	<table cellspacing="0" cellpadding="0" border="0" style="height:20px;width:100%;">
	  <tr>
	    <td class="">
	      <?=$this->get_translation('display')?> :
	      <?=$this->get_translation('from')?>
	    </td>
	    <td class="">
	      <select name="listpage" style="width:70px;">
		<option value="0" <?=$this->listpage==0?' selected="selected"':''?>>
		  <?=$this->get_translation('x', array($this->itemsbypage)) ?>
		</option>
		<?php for ( $i=1; $i<$this->pages; $i++ ) : ?>
		<option value="<?=$i?>" <?=$this->listpage==$i?' selected="selected"':''?>>
		  <?=$this->get_translation('xtoy', array($this->itemsbypage*$i, 
		  $this->itemsbypage*($i+1))) ?>
		</option>
		<?php endfor; ?>
	      </select>
	    </td>
	    <td class="">
	      <?=$this->get_translation('fromend')?>
	      <?=$this->get_translation('fromtype')?>
	    </td>
	    <td class="">
	      <select name="listtype" style="width:100px;">
		<option value=""<?=$this->listtype==''?' selected="selected"':''?>>
		  <?=$this->get_translation('all')?>
		</option>
		<?php foreach ( $this->typelist as $t ) : ?>
		<option value="<?=$t->id?>"<?=$this->listtype == $t->id ? ' selected="selected"' : ''?>>
		  <?=$t->vars['name']?>
		</option>
		<?php endforeach; ?>
	      </select>
	    </td>
	    <td class="">
	      <?=$this->get_translation('markedas')?>
	    </td>
	    <td class="">
	      <select name="listviewed" style="width:100px;">
		<option value="0"<?=$this->listviewed==0?' selected="selected"':''?>>
		  <?=$this->get_translation('readandnotread')?>
		</option>
		<option value="1"<?=$this->listviewed==1?' selected="selected"':''?>>
		  <?=$this->get_translation('readonly')?>
		</option>
		<option value="2"<?=$this->listviewed==2?' selected="selected"':''?>>
		  <?=$this->get_translation('notreadonly')?>
		</option>
	      </select>
	    </td>
	    <td class="">
	      <a href="<?=$this->form->get_HTMLSubmitLink();?>">
	      <img src="<?=$upd?>"
		alt="<?=$camyks->get_translation('display')?>" border="0"
		style="cursor:pointer;"
		onmouseover="this.src='<?=$upd_?>';"
		onmouseout="this.src='<?=$upd?>';" />
	      </a>
	    </td>
	  </tr>
	</table>
	<?=$this->form->display_footer();?>
      </td>
    </tr>
    <tr>
      <td>	
	<table cellspacing="0" cellpadding="0" border="0" width="100%">
	  <tr>
	    <td class="listheader" align="center" style="width:20px;">
	      &nbsp;
	    </td>
	    <td class="listheader" style="width:20px;">
	      <?=$this->get_translation('number')?>
	    </td>
	    <td class="listheader" style="width:60px;">
	      <?=$this->get_translation('date')?>
	    </td>
	    <td class="listheader">
	      <?=$this->get_translation('type')?>
	    </td>
	    <td class="listheader">
	      <?=$this->get_translation('object')?>
	    </td>
	    <td class="listheader">
	      <?=$this->get_translation('answered')?>
	    </td>
	    <td class="listheader" style="text-align:center;width:12px;">
	      &nbsp;
	    </td>
	    <?php if ( $this->check_right(1) ) : ?>
	    <td class="listheader" style="text-align:center;width:12px;">
	      &nbsp;
	    </td>
	    <?php endif; ?>
	  </tr>
	  
	  <?php $alt = 0; ?>
	  <?php foreach ( $this->itemlist as $item ) : ?>
	  <tr>
	    <td class="listline<?=$alt?>">
	      <img src="<?=($item->vars['answer_date']>0?$valid:$empty)?>" alt="" border="0" />
	    </td>
	    <td class="listline<?=$alt?>">
	      <?= $item->id ?>
	    </td>
	    <td class="listline<?=$alt?>">
	      <?=date_displayQuickDate($item->vars['creation_date']) ?>
	    </td>
	    <td class="listline<?=$alt?>">
	      <?= $this->typelist[$item->vars['type']]->vars['name'] ?>
	    </td>
	    <td class="listline<?=$alt?>">
	      <?=$item->vars['title']?>
	    </td>
	    <td class="listline<?=$alt?>">
	      <?php if ( $item->vars['answer_date'] > 0 ) : ?>
	      <?=date_displayQuickDate($item->vars['answer_date']) ?>
	      <?php else : ?>
	      <?=$this->get_translation('noanswer') ?>
	      <?php endif; ?>
	    </td>
	    
	    <td class="listline<?=$alt?>">
	      <a href="<?=$this->viewReportLink.$item->id?>">
		<img src="<?=$view?>" alt="<?=$this->get_translation('admin_viewreport');?>" border="0" onmouseover="this.src='<?=$view_?>';" onmouseout="this.src='<?=$view?>';" />
	      </a>
	    </td>
	    
	    <?php if ( $this->check_right(1)===true ) : ?>
	    <td class="listline<?=$alt?>">
  	      <a href="javascript:adminengine_confirmRedirect(deletereportlink+'<?=$item->id?>', deletereportmessage);">
		<img src="<?=$del?>" alt="<?=$this->get_translation('admin_deletereport');?>" border="0" onmouseover="this.src='<?=$del_?>';" onmouseout="this.src='<?=$del?>';" />
	      </a>
	    </td>
	    <?php endif; ?>    
	  </tr> 
	  <?php $alt = abs( $alt-1 );?>
	  <?php endforeach; ?>
	</table>
	
      </td>
    </tr>
  </table>
</div>

<?php if ( $this->check_right(2)===true ) : ?>
<div id="itemconfigure" style="display:none;" class="adminContentPanel">
<?=$this->configform->display_header();?>
<?=$this->configform->display_hiddens();?>
  <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
    <tr>
      <td class="listline0 eContent2">
  <?=$this->get_translation('config_fileallowed');?>
      </td>
<td class="listline0">
      <input type="checkbox" name="file_allowed" value="1"<?=$this->config->vars['file_allowed']==1?' checked="checed"':''?> onchange="admin_sitereport_checkallowedfiles();" />
</td>
</tr>
<tr>
<td class="listline1 eContent2" style="width:150px;">
<?=$this->get_translation('config_filemaxsize');?>
</td>
<td class="listline1">
<input type="text" name="file_maxsize" value="<?=$this->config->vars['file_maxsize']?>" maxlength="6" size="7" <?=$this->config->vars['file_allowed']==1?'':'disabled="disabled"'?> /> K<?=language_getFileUnit();?>
</td>
</tr>
<tr>
  <td class="listline0" colspan="2">
<?=$this->theme->get_button(array('url'=>$this->configform->get_HTMLSubmitLink(), 'title'=>$camyks->get_translation('valid')));?>
</td>
</tr>
  </table>
<?=$this->configform->display_footer();?>
</div>
<div id="itemtypes" style="display:none;" class="adminContentPanel">
  <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
    <tr>
      <td class="listheader">
	<?=$camyks->get_translation('name')?>
      </td>
      <td class="listheader" colspan="3">
	&nbsp;
      </td>
    </tr>
    
    <tr>
      <td class="listline1">
	<a href="<?=$this->editTypeLink?>0">
	  <?=$this->get_translation('new_type')?>
	</a>
      </td>
      <td class="listline1" style="width:12px;">
	&nbsp;
      </td>
      <td class="listline1" style="width:12px;">
	<a href="<?=$this->editTypeLink?>0">
	  <img src="<?=$edit?>" alt="<?=$this->get_translation('new_type')?>" border="0"
            onmouseover="this.src='<?=$edit_?>';" onmouseout="this.src='<?=$edit?>';"/>
	</a>
      </td>
      <td class="listline1" style="width:12px;">
	&nbsp;
      </td>
    </tr>
    
    
    <?php $alt = 0; ?>
    <?php foreach ( $this->typelist as $rtype ) : ?>
    <tr>
      <td class="listline<?=$alt?>">
	<a class="link2" href="<?=$camyks->get_adminLink( $this->name, array('mode'=>'viewtype', 'rtype'=>$rtype->id))?>">
	  <?=$rtype->vars['name'];?>
	</a>
      </td>
      <td class="listline<?=$alt?>">
	<a href="<?=$this->viewTypeLink.$rtype->id?>">
	  <img src="<?=$view?>" border="0" alt="<?=$this->get_translation('admin_viewtype');?>"
	    onmouseover="this.src='<?=$view_?>';" onmouseout="this.src='<?=$view?>';" />
	</a>
      </td>
      <td class="listline<?=$alt?>">
	<a href="<?=$this->editTypeLink.$rtype->id?>">
	  <img src="<?=$edit?>" border="0" alt="<?=$this->get_translation('admin_edittype');?>"
	    onmouseover="this.src='<?=$edit_?>';" onmouseout="this.src='<?=$edit?>';" />
	</a>
      </td>
      <td class="listline<?=$alt?>">
	<a href="javascript:adminengine_confirmRedirect(deletetypelink+'<?=$rtype->id?>', deletetypemessage);">
	  <img src="<?=$del?>" alt="<?=$this->get_translation('admin_deletetype')?>" border="0" 
	    onmouseover="this.src='<?=$del_?>';" onmouseout="this.src='<?=$del?>';" />
	</a>
      </td>
    </tr>
    <?php $alt=abs($alt-1); ?>
    <?php endforeach; ?>
  </table>
</div>
<?php endif; ?>
<?=$this->theme->get_boxContent2Footer();?>
<?=$this->theme->get_boxButtonsBar($this->buttons );?>
<?=$this->theme->get_boxFooter();?>