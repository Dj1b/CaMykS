<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Creation Date	: Apr 2008
 * Last Modif Date	: Mar 2009
 * 
 * Admin_GenericBlogsManager Module Admin Layout : edit news
*/
global $camyks;

/* get some theme buttons */
$plus = $this->theme->get_pictURL('plus', 12, 'std');
$plus_ = $this->theme->get_pictURL('plus', 12, 'ovr');

$minus = $this->theme->get_pictURL('minus', 12, 'std');
$minus_ = $this->theme->get_pictURL('minus', 12, 'ovr');
?>
<?=$this->theme->get_boxHeader('width:610px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title.$this->get_translation('editnews_editortitle') ) ?>
<?=$this->theme->get_boxTabsBar($this->tabs,
				$this->tabObject.'.mouseclick',
				$this->tabObject.'.mouseover',
				$this->tabObject.'.mouseout',
				'properties');?>
<?=$this->theme->get_boxContent2Header( )?>
<?=$this->form->display_header(); ?>
<?=$this->form->display_hiddens(); ?>
<div id="itemproperties" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%">
<tr>
  <td class="eTableLine0 eContent2" colspan="2">
<?=$this->get_translation('editnews_'.($this->newsItem->id==0?'createobject':'objectid'), $this->newsItem->id);?>
  </td>
</tr>

<tr>
  <td class="eTableLine1 eContent2">
  <?=$this->get_translation('editnews_author');?>
  </td>
  <td class="eTableLine1 eContent1">
  <?=$this->newsItem->vars['author'];?>
  </td>
</tr>

<tr>
  <td class="eTableLine0 eContent2">
  <?=$this->get_translation('editnews_ndate');?>
  </td>
  <td class="eTableLine0 eContent1">
  <?=$this->form->display_dateInput($this->newsItem->vars['ndate'],
				    'ndate',
				    array('minutes','hours', 'month', 'day', 'year'),
				    $this->get_dateInputButtons());?>
  </td>
</tr>

<tr>
  <td class="eTableLine1 eContent2">
  <?=$this->get_translation('editnews_active');?>
  </td>
  <td class="eTableLine1 eContent1">
 <input type="checkbox" name="status" value="1"<?=($this->newsItem->vars['status']==1?' checked="checked"':'')?> />
  </td>
</tr>

<tr>
  <td class="eTableLine0 eContent2">
  <?=$this->get_translation('editnews_title');?>
</td>
<td class="eTableLine0 eContent1">
<input type="text" name="title" value="<?=$this->newsItem->vars['title']?>" maxlength="255" class="inputs" />
</td>
</tr>

<?php $alt=1; ?>
<?php if ($this->config->vars['news_allowvideo'] == true ) : ?>
<tr>
  <td class="eTableLine<?=$alt?> eContent2">
  <?=$this->get_translation('editnews_videolink');?>
</td>
<td class="eTableLine<?=$alt?> eContent1">
<textarea class="mceNoEditor" name="videolink" rows="4" cols="20" style="width:90%"><?=$this->newsItem->vars['videolink']?></textarea>
</td>
</tr>
<?php $alt=abs($alt-1);?>
<?php endif; ?>

<tr>
  <td class="eTableLine<?=$alt?> eContent2" style="vertical-align:top;">
  <?=$this->get_translation('editnews_taglist');?>
</td>
<td class="eTableLine<?=$alt?> eContent1">
<table cellspacing="0" cellpadding="0" border="0">
<tbody id="taglist">
<?php $cnt=0 ?>
<?php foreach ( $this->newsItem->tagList as $tag ) : ?>
<tr id="tagline<?=$cnt?>">
<td class="content1">
<input type="hidden" name="tag<?=$cnt?>_id" value="<?=$tag->id?>" />
<input type="hidden" name="tag<?=$cnt?>_value" value="<?=$tag->vars['title']?>" />
<input type="text" class="inputs" value="<?=$tag->vars['title']?>" disabled="disabled" />
  </td>
  <td class="content1">
<?php if ( $this->check_right(9)===true or ( $this->check_right(8)=== true and $tag->vars['author']===$camyks->adminUser->login )) :?>
    <a href="javascript:genericblogsmanager_deleteTag(<?=$cnt?>);">
      <img src="<?=$minus?>" alt="" border="0" onmouseover="this.src='<?=$minus_?>';" onmouseout="this.src='<?=$minus?>';" />
    </a>
<?php else : ?>
&nbsp;
<?php endif; ?>
  </td>
</tr>
<?php $cnt++; ?>
<?php endforeach; ?>
</tbody>
</table>

<?php if ($this->check_right(8)===true or $this->check_right(9)===true) : ?>
<table cellspacing="0" cellpadding="0" border="0">
<tr>
  <td id="tageditor" class="content1">
    <select id="tagselect" name="tagChooser" class="inputs" onchange="genericblogsmanager_selectTag()">
<option value=""><?=$this->get_translation('editnews_selecttag');?></option>
<?php foreach ( $this->tagList as $tag ) : ?>
<option value="<?=$tag?>"><?=$tag?></option>
<?php endforeach; ?>
<?php if ( $this->check_right(8) === true ): ?>
<option value="!other"><?=$this->get_translation('editnews_newtag');?></option>
<?php endif; ?>
</select>
  </td>
  <td class="content1">
    <a href="javascript:genericblogsmanager_addTag();">
      <img src="<?=$plus?>" alt="<?=$this->get_translation('editnews_addthistag')?>" border="0" 
onmouseover="this.src='<?=$plus_?>';" onmouseout="this.src='<?=$plus?>';" />
    </a>    
</td>
</tr>
</table>
<?php endif; ?>
</td>
</tr>

</table>
</div>

<div id="itemcontent" style="display:none;" class="adminContentPanel">
<?php if( $this->config->vars['news_editormode'] == 0 ) : ?>
<textarea class="mceNoEditor" name="content" rows="16" cols="20" style="width:100%;"><?=$this->newsItem->vars['content']?></textarea>
<?php else : ?>
<?php $this->webEditor->display(); ?>
<?php endif; ?>
</div>
<?=$this->form->display_footer(); ?>

<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar($this->buttons); ?>
<?=$this->theme->get_boxFooter(); ?>