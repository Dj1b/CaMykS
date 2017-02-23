<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Nov 2007
 * Last Modif Date	: Nov 2007
 * 
 * Content_GenericQuickMessage Module admin layout : modify
 */
global $camyks;

$add = $this->theme->get_pictURL('plus', 12, 'std');
$add_ = $this->theme->get_pictURL('plus', 12, 'ovr');

$edit = $this->theme->get_pictURL('edit', 12, 'std');
$edit_ = $this->theme->get_pictURL('edit', 12, 'ovr');

$del = $this->theme->get_pictURL('cross', 12, 'std');
$del_ = $this->theme->get_pictURL('cross', 12, 'ovr');

$send = $this->theme->get_pictURL('target', 12, 'std');
$send_ = $this->theme->get_pictURL('target', 12, 'ovr');

$empty = $this->theme->get_pictURL('empty', 12, 'std');
$valid = $this->theme->get_pictURL('valid', 12, 'std');
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title 
				 .' : '. $this->qmlist->vars['name']
				 .' [ ' .$this->qmlist->id . ' ] ');?>
<?=$this->theme->get_boxTabsBar($this->tabs,
				$this->tabObject.'.mouseclick',
				$this->tabObject.'.mouseover',
				$this->tabObject.'.mouseout',
				'general');?>
<?=$this->theme->get_boxContent2Header(); ?>
<div id="itemgeneral" style="display:block;" class="adminContentPanel">
<?=$this->form->display_header()?>
<?=$this->form->display_hiddens()?>
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
<tr>
<td class="listline1" style="width:150px">
<?=$camyks->get_translation('name')?> :
</td>
<td class="listline1">
<input type="text" name="name" value="<?=$this->qmlist->vars['name'];?>" maxlength="32" class="inputs" />
</td>
</tr>

<tr>
<td class="listline0" style="width:150px;">
<?=$this->get_translation('state')?> :
</td>
<td class="listline0">
<select name="status" class="inputs">
<?php foreach ( $this->qmlist->get_statusValueList() as $value=>$title ) : ?>
<option value="<?=$value?>"<?=$value==$this->qmlist->vars['status']?' selected="selected"':''?>>
<?=$title?>
</option>
<?php endforeach; ?>
</select>
</td>
</tr>

<tr>
<td class="listline1" style="width:150px">
<?=$this->get_translation('listvalidation')?> :
</td>
<td class="listline1">
<select name="validation" class="inputs">
<?php foreach ( $this->qmlist->get_validationValueList() as $value=>$title ) : ?>
<option value="<?=$value?>"<?=$value==$this->qmlist->vars['validation']?' selected="selected"':''?>>
<?=$title?>
</option>
<?php endforeach; ?>
</select>
</td>
</tr>

<tr>
<td class="listline0" colspan="2">
<input type="checkbox" name="notification" value="1"<?=$this->qmlist->vars['notification']?' checked="checked"':''?> />
<?=$this->get_translation('listnotification')?>
</td>
</tr>

<tr>
<td class="listline1">
<?=$this->get_translation('displayedmessages');?>
</td>
<td class="listline1">
<input type="text" name="displayed" value="<?=$this->qmlist->vars['displayed']?>" maxlength="2" class="inputs" />
</td>
</tr>
</table>
<?=$this->form->display_footer()?>
</div>

<?php if ( $this->qmlist->id > 0 ) : ?>
<div id="itemmessages" style="display:none;" class="adminContentPanel">
<?=$this->listform->display_header();?>
<?=$this->listform->display_hiddens();?>
<table cellspacing="0" cellpadding="0" border="0" style="height:20px;width:100%;">
<tr>
<td class="content1">
<?=$this->get_translation('display')?> :
<?=$this->get_translation('from')?>
</td>
<td class="content1">
<select name="listpage" style="width:70px;">
<option value="0" <?=$this->listpage==0?' selected="selected"':''?>>
<?=$this->get_translation('x', array($this->itemsbypage)) ?>
</option>
<?php for ( $i=1; $i<$this->pages; $i++ ) : ?>
<option value="<?=$i?>" <?=$this->listpage==$i?' selected="selected"':''?>>
<?=$this->get_translation('xtoy', array($this->itemsbypage*$i, 
					min($this->itemsbypage*($i+1), $this->qmcount))) ?>
</option>
<?php endfor; ?>
</select>
</td>
<td class="content1">
<?=$this->get_translation('fromend')?>
<?=$this->get_translation('fromstatus')?>
</td>
<td class="content1">
<select name="liststatus" style="width:100px;">
<option value="-1"<?=$this->liststatus=='-1'?' selected="selected"':''?>>
<?=$this->get_translation('all')?>
</option>
<?php foreach ( $this->qmitem->get_statusValueList() as $status=>$title ) : ?>
<option value="<?=$status?>"<?=$this->liststatus == $status ? ' selected="selected"' : ''?>>
<?=$title?>
</option>
<?php endforeach; ?>
</select>
</td>
<td class="content1">
<a href="<?=$this->listform->get_HTMLSubmitLink()?>">
<img src="<?=$send?>"
alt="<?=$this->get_translation('display')?>" border="0"
onMouseOver="this.src='<?=$send_?>'"
onMouseOut="this.src='<?=$send?>'" />
</a>
</td>
</tr>
</table>
<?=$this->listform->display_footer();?>
<table cellspacing="0" cellpadding="0" border="0" width="100%">
<tr>
<td class="listheader" style="width:20px;">
&nbsp;
</td>
<td class="listheader" align="center" style="width:16px;padding:2px;">
<img src="<?=$camyks->theme->get_pictURL( 'valid', '12', 'std' )?>" alt="" border="0"/>
</td>
<td class="listheader" style="width:20px;">
<?=$this->get_translation('number')?>
</td>
<td class="listheader" style="width:120px;">
<?=$this->get_translation('date')?>
</td>
<td class="listheader" style="width:100px;">
<?=$this->get_translation('messagetitle')?>
</td>
<td class="listheader">
<?=$this->get_translation('messageauthor')?>
</td>
</tr>

<?php $alt = 0; ?>
<?php $cnt = 0; ?>
<?php foreach ( $this->qmitems as $item ) : ?>
<?php if ( $item->vars['status'] == 0 ) : ?>
<?php $more = array('', '');?> 
<?php elseif ( $item->vars['status'] == 1 ) : ?>
<?php $more = array('<b>', '</b>');?> 
<?php elseif ( $item->vars['status'] == 2 ) : ?>
<?php $more = array('', '');?> 
<?php endif;?>
<tr>
<td class="listline<?=$alt;?>" align="center">
<a href="<?=$this->editItemLink.$item->id?>">
<img src="<?=$camyks->theme->get_pictURL('view', '12', 'std')?>" 
alt="<?=$camyks->get_translation('displaythisreport')?>" border="0"
onMouseOver="this.src='<?=$camyks->theme->get_pictURL('view', '12', 'ovr')?>';"
onMouseOut="this.src='<?=$camyks->theme->get_pictURL('view', '12', 'std')?>';">
</a>
</td>
<td class="listline<?=$alt;?>" align="center" style="padding:2px;">
<img src="<?=$this->get_fileURL('img/status'.$item->vars['status'].'.gif')?>" alt="" border="0" />
</td>
<td class="listline<?=$alt;?>">
<?=$more[0]?>
<?=$item->id?>
<?=$more[1]?>
</td>
<td class="listline<?=$alt;?>">
<?=$more[0]?>
<?=date_displayShortDayDateHour( $item->vars['ndate'] )?>
<?=$more[1]?>
</td>
<td class="listline<?=$alt;?>">
<?=$more[0]?>
<?=$item->vars['title']?>
<?=$more[1]?>
</td>
<td class="listline<?=$alt;?>">
<?=$more[0]?>
<?=$item->vars['author']?>
<?=$more[1]?>
</td>
</tr>
<?php $alt = abs( $alt-1); ?>
<?php $cnt++; ?>
<?php endforeach; ?>
</table>
</div>
<?php endif; ?>

<?php if ( $this->help != null ) : ?>
<div id="itemhelp" style="display:none;" class="adminContentPanel">
<?php $this->display_help() ?>
</div>
<?php endif; ?>
  
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons );?>
<?=$this->theme->get_boxFooter(); ?>
