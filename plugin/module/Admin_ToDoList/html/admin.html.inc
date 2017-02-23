<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Apr 2007
 * Last Modif Date	: May 2007
 *
 * Admin_ToDoList Module Admin Layout
 *
*/
global $camyks;

/* get imgs url */
$view = $camyks->theme->get_pictURL('view', 12, 'std');
$view_ = $camyks->theme->get_pictURL('view', 12, 'ovr');
$edit = $camyks->theme->get_pictURL('edit', 12, 'std');
$edit_ = $camyks->theme->get_pictURL('edit', 12, 'ovr');
$del = $camyks->theme->get_pictURL('cross', 12, 'std');
$del_ = $camyks->theme->get_pictURL('cross', 12, 'ovr');
$upd = $camyks->theme->get_pictURL('target', 12, 'std');
$upd_ = $camyks->theme->get_pictURL('target', 12, 'ovr');

/* button list for buttons bar */
$buttons = array(array('title'=>$camyks->get_translation('back'),
		       'link' =>$camyks->get_adminLink()));

if ( $this->mode == 'edit' ) {
  $buttons[] = array('title'=>$this->get_translation('validobject'),
		     'link'=>'javascript:document.admintodolist.submit()');
}

/* tab list */
$tabs = array(array('name'=>'general',
		    'title'=>$this->get_translation('tablist')));

if ( $this->mode == 'edit' and $this->item->id == 0 ) {
  $tabs[] = array('name'=>'edit',
		  'title'=>$this->get_translation('tabnew'));
} else if ( $this->mode == 'edit' ) {
  $tabs[] = array('name'=>'edit',
		  'title'=>$this->get_translation('tabedit'));
} else if ( $this->mode == 'view' ) {
  $tabs[] = array('name'=>'view',
		  'title'=>$this->get_translation('tabview', $this->item->vars['title']));
  $tabs[] = array('name'=>'comments',
		  'title'=>$this->get_translation('tabcomments', count($this->item->vars['comments'])));
}

$jsObject = 'admin_todolist_tabObject';

?>
<?=$camyks->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$camyks->theme->get_boxTitleBar($this->title);?>
<?=$camyks->theme->get_boxTabsBar($tabs,
				  $jsObject.'.mouseclick',
				  $jsObject.'.mouseover',
				  $jsObject.'.mouseout',
				  'general');?>
<?=$camyks->theme->get_boxContent2Header();?>
<div id="itemgeneral" style="display:block;" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
<tr>
  <td class="listheader">
    <?=$camyks->get_translation('name')?>
  </td>
  <td class="listheader">
    <?=$this->get_translation('user')?>
  </td>
  <td class="listheader">
    <?=$this->get_translation('limitdateform')?>
  </td>
  <td class="listheader">
    &nbsp;
  </td>
<?php if ( $this->check_right ( 1 ) ) : ?>
  <td class="listheader" colspan="2">
    &nbsp;
  </td>
<?php endif; ?>
</tr>

<?php if ( $this->check_right ( 1 ) ) : ?>
<tr><td class="listline1">
<a class="link1" href="<?=$camyks->get_adminLink( $this->name, array('mode'=>'edit', 'todo'=>''))?>">
<?=$this->get_translation('new_item')?>
</a>
</td>
<td class="listline1" colspan="2">&nbsp;</td>
<td class="listline1" style="width:12px;">&nbsp;</td>
<td class="listline1" style="width:12px;">
<a class="link1" href="<?=$camyks->get_adminLink( $this->name, array('mode'=>'edit', 'todo'=>''))?>">
<img src="<?=$edit?>" border="0" onMouseOver="this.src='<?=$edit_?>';" onMouseOut="this.src='<?=$edit?>';">
</a>
</td>
<td class="listline1" style="width:12px;">&nbsp;</td>
</tr>
<?php endif; ?>


<?php $alt = 0; ?>
<?php foreach ( $this->todolist as $todo ) : ?>
<tr>
<td class="listline<?=$alt?>">
<a class="link2" href="<?=$camyks->get_adminLink( $this->name, array('mode'=>'view', 'todo'=>$todo->id))?>">
<?=$todo->vars['title'];?>
</a>
</td>
<td class="listline<?=$alt?>">
<a class="link2" href="<?=$camyks->get_adminLink( $this->name, array('mode'=>'view', 'todo'=>$todo->id))?>">
<?=$todo->vars['from_user'];?>
</a>
</td>
<td class="listline<?=$alt?>">
<a class="link2" href="<?=$camyks->get_adminLink( $this->name, array('mode'=>'view', 'todo'=>$todo->id))?>">
<?= $todo->vars['limit_date']==0 ? $this->get_translation('none') : date_displayShortFormat($todo->vars['limit_date']);?>
</a>
</td>
<td style="width:12px;" class="listline<?=$alt?>">
<a class="link2" href="<?=$camyks->get_adminLink( $this->name, array('mode'=>'view', 'todo'=>$todo->id))?>">
<img src="<?=$view?>" alt="<?=$this->get_translation('view')?>" border="0"
onMouseOver="this.src='<?=$view_?>';"
onMouseOut="this.src='<?=$view?>';"
></a>
</td>
<?php if ( $this->check_right ( 1 ) ) : ?>
<td style="width:12px;" class="listline<?=$alt?>">
<a class="link2" href="<?=$camyks->get_adminLink( $this->name, array('mode'=>'edit', 'todo'=>$todo->id))?>">
<img src="<?=$edit?>" alt="<?=$this->get_translation('edit')?>" border="0"
onMouseOver="this.src='<?=$edit_?>';"
onMouseOut="this.src='<?=$edit?>';"
></a>
<td style="width:12px;" class="listline<?=$alt?>">
<a class="link2" href="javascript:if(confirm('<?=$this->get_translation('deleteconfirmation')?>')){document.location.href='<?=$camyks->get_adminLink( $this->name, array('mode'=>'delete', 'todo'=>$todo->id))?>';}">
<img src="<?=$del?>" alt="<?=$this->get_translation('del')?>" border="0"
onMouseOver="this.src='<?=$del_?>';"
onMouseOut="this.src='<?=$del?>';"
></a>
</td>
<?php endif; ?>
</tr>
<?php $alt=abs($alt-1); ?>
<?php endforeach; ?>
</table>
</div>

<?php if ( $this->mode == 'edit' ) : ?>
<div id="itemedit" style="display:none;" class="adminContentPanel">
<?=$this->form->display_header(); ?>
<?=$this->form->display_hiddens(); ?>
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
<tr>
  <td class="" style="width:150px;">
<?=$this->get_translation('to_user');?> :
  </td>
  <td class="">
    <select name="to_user">
  <option value=""> <?=$this->get_translation('all') ?> </option>
  <?php foreach ( $this->item->vars['users'] as $u ) : ?>
  <option value="<?=$u->login?>"<?=$this->item->vars['to_user'] == $u->login ? ' selected="selected"':''?>>
<?=$u->login ?> </option> 
  <?php endforeach; ?>
    </select>
  </td>
</tr>
<tr>
 <td class="">
    <?=$this->get_translation('closed');?> :
 </td>
 <td class="">
 <input type="checkbox" name="closed" value="1"<?=$this->item->vars['closed']==1?' checked="checked"':''?>>
 </td>
 </tr>
 <tr>
 <td class="">
 <?= $this->get_translation('limitdateform') ?> :
</td>
 <td class="">
<?=$this->form->display_dateInput( $this->item->vars['limit_date'], 
				   'limit_date',
				   array('day','month','year','hours','minutes'),
				   array('update'=>array('std'=> $upd,
							 'ovr'=> $upd_,
							 'title'=>$camyks->get_translation('update')),
					 'reset'=>array('std'=> $del,
							'ovr'=> $del_,
							'title'=>$camyks->get_translation('reset'))));?>
  </td>
</tr>
<tr>
 <td class="">
 <?=$this->get_translation('ititle');?> :
 </td>
 <td class="">
 <input type="text" name="title" value="<?=$this->item->vars['title']?>" maxlength="64" class="inputs"/>
 </td>
</tr>
<tr>
 <td class="" style="vertical-align:top;">
 <?=$this->get_translation('content');?> :
 </td>
 <td class="">
   <textarea name="content" cols="40" rows="16" style="width:90%;"><?=$this->item->vars['content']?></textarea>
 </td>
</tr>
</table>
<?=$this->form->display_footer(); ?>
</div>

<?php elseif ( $this->mode == 'view' ) : ?>

<div id="itemview" style="display:none;" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
<tr>
  <td class="listline0">
<?=$this->get_translation('objectaddedbyxony', 
			  array($this->item->vars['from_user'], 
				date_displayLongFormat($this->item->vars['creation_date'])));?>
  </td>
</tr>

  <?php if ( $this->item->vars['limit_date'] != 0 ) : ?>
<tr>
  <td class="listline0">
  <?= $this->get_translation ( 'limitdate', 
			       date_displayLongFormat($this->item->vars['limit_date'])); ?>
  </td>
</tr>
  <?php endif; ?>
<tr>
  <td class="listline1 title3">
<?=$this->item->vars['title']?>
  </td>
</tr>
<tr>
  <td class="listline1">
<?=nl2br($this->item->vars['content'])?>
  </td>
</tr>
</table>
</div>


<div id="itemcomments" style="display:none;" class="adminContentPanel">
<?=$this->form->display_header(); ?>
<?=$this->form->display_hiddens(); ?>
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
<tr>
<td class="listline1" align="center">
<textarea name="content" rows="8" style="width:100%;"></textarea>
</td>
</tr>
<tr>
<td class="">
<?=$camyks->theme->get_boxButtonsBar(array(array('title'=>$this->get_translation('validcomment'),
						 'link'=>'javascript:document.admintodolist.submit()'))); ?>
</td>
</tr>

<?php if ( count ( $this->item->vars['comments'] ) ) : ?>
<?php $alt=0 ?>
<?php foreach ( $this->item->vars['comments'] as $c ) : ?>
<?php $c->get_fromItems(); ?>
<tr>
<td class="listline<?=$alt?>">
<?= $this->get_translation('commentfrom', array($c->vars['from_user'], 
						date_displayLongFormat($c->vars['creation_date']))) ?>
</td>
</tr>
<tr>
  <td class="listline<?=$alt?>">
<?=nl2br($c->vars['content']); ?>
  </td>
</tr>
<?php $alt = abs( $alt-1 ); ?>
<?php endforeach; ?>
<?php else : ?>
<tr>
  <td class="listline0">
    <?=$this->get_translation('nocomment')?>
  </td>
</tr>
<?php endif; ?>
</table>
<?=$this->form->display_footer(); ?>
</div>
<?php endif; ?> 
<?=$camyks->theme->get_boxContent2Footer();?>
<?=$camyks->theme->get_boxButtonsBar( $buttons );?>
<?=$camyks->theme->get_boxFooter();?>