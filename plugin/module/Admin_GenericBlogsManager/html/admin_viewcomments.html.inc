<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Creation Date	: Apr 2008
 * Last Modif Date	: Jul 2008
 * 
 * Admin_GenericBlogsManager Module Admin Layout : view comments
*/
global $camyks;

/* get some theme buttons */
$valid = $this->theme->get_pictURL('valid', 12, 'std');
$valid_ = $this->theme->get_pictURL('valid', 12, 'ovr');

$target = $this->theme->get_pictURL('target', 12, 'std');
$target_ = $this->theme->get_pictURL('target', 12, 'ovr');

$edit = $this->theme->get_pictURL('edit', 12, 'std');
$edit_ = $this->theme->get_pictURL('edit', 12, 'ovr');

$cross = $this->theme->get_pictURL('cross', 12, 'std');
$cross_ = $this->theme->get_pictURL('cross', 12, 'ovr');
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title.$this->get_translation('viewcomments_listtitle'))?>
<?=$this->theme->get_boxContent1Header('height:20px;')?>
<div style="padding:2px 4px;font-weight:bold;">
<?=$this->get_translation('viewcomments_newscomments', array($this->newsItem->id, 
							    $this->newsItem->vars['title']))?>
</div>
<?=$this->theme->get_boxContent1Footer( )?>
<?=$this->theme->get_boxContent2Header( )?>
<div class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%">
<?php foreach ( $this->newsItem->vars['coms'] as $comment ) : ?>
<tr>
  <td class="eTableLine1 eContent2" style="text-align:right;">
<?=$comment->vars['ipaddress'];?>
&nbsp;&#124;&nbsp;
<select name="comment_<?=$comment->id?>_status" id="comment_<?=$comment->id?>_status">
<?php foreach ( $this->commentStatusList as $status => $title ) : ?>
<option value="<?=$status?>"<?=($status==$comment->vars['status']?' selected="selected"':'')?>>
<?=$title?>
</option>
<?php endforeach; ?>
</select>
<a href="javascript:genericblogsviewcomments_updateCommentStatus(<?=$comment->id?>);">
<img src="<?=$valid?>" border="0"
alt="<?=$this->get_translation('viewcomments_updatecommentstatus');?>"
title="<?=$this->get_translation('viewcomments_updatecommentstatus');?>"
onmouseover="this.src='<?=$valid_?>';" onmouseout="this.src='<?=$valid?>';" />
</a>
&nbsp;&#124;&nbsp;
<a href="<?=$this->editCommentLink.$comment->id?>">
<img src="<?=$edit?>" border="0"
alt="<?=$this->get_translation('viewcomments_editcomment');?>"
title="<?=$this->get_translation('viewcomments_editcomment');?>"
onmouseover="this.src='<?=$edit_?>';" onmouseout="this.src='<?=$edit?>';" />
</a>
<a href="javascript:genericblogsviewcomments_deleteComment(<?=$comment->id?>);">
<img src="<?=$cross?>" border="0"
alt="<?=$this->get_translation('viewcomments_deletecomment');?>"
title="<?=$this->get_translation('viewcomments_deletecomment');?>"
onmouseover="this.src='<?=$cross_?>';" onmouseout="this.src='<?=$cross?>';" />
</a>
</td>
</tr>
<tr>
<td class="eTableLine0 eContent2">
<?php if ($comment->vars['website'] != '' ) : ?>
<?=$this->get_translation('site_comment_headerfull', array( $comment->vars['author'],
							    date_displayLongDayDateHour($comment->vars['ndate']),
							    $comment->vars['website'],
							    'link1'));?>
<?php else : ?>
<?=$this->get_translation('site_comment_headerlight', array( $comment->vars['author'],
							     date_displayLongDayDateHour($comment->vars['ndate'])))?>
<?php endif; ?>
</td>
</tr>
<?php if ( $comment->vars['title'] != '' ) : ?>
<tr>
<td class="eTableLine0 eContent2">
<?=$comment->vars['title'];?>
</td>
</tr>
<?php endif; ?>
<tr>
<td class="eTableLine0 eContent1">
<?=nl2br($comment->vars['content']);?>
</td>
</tr>
<tr>
<td class="eTableLine0">
&nbsp;
</td>
</tr>
<?php endforeach; ?>
</table>
</div>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar($this->buttons); ?>
<?=$this->theme->get_boxFooter(); ?>