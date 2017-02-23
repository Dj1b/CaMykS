<?php
/*
 * CaMyks Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Apr 2008
 * Last Modif Date	: Nov 2009
 * 
 * Content_GenericBlogsViewer Module Site Layout : site item_box layout
 */
global $camyks;

$newsLink = $this->get_singleNewsLink($this->blogItem->id);
?>
<?php if ( $this->configItem->vars['item_panel']==1 ) : ?>
<table cellspacing="0" cellpadding="0" border="0" style="width:100%">
  <tr>
    <td style="vertical-align:top">
      <?php endif; ?>
      <?=$this->theme->get_boxHeader('width:100%');?>
      <?=$this->theme->get_boxTitleBar($this->configItem->vars['title'].
      $this->get_translation('site_title_separator').
      $this->blogItem->vars['title']);?>
      <?=$this->theme->get_boxContent1Header('padding:4px 8px');?>
      <h2 class="eTitle4">
	<?=date_displayLongDayDateHour($this->blogItem->vars['ndate'])?>
      </h2>
      <?=$this->get_blogNewsContentDisplay($this->blogItem->vars['content'])?>
      <?php if( $this->blogItem->vars['videolink'] != '' ) : ?>
      <div class="eContent1" style="text-align:center;">
	<?= $this->blogItem->vars['videolink']; ?>
      </div>
      <?php endif; ?>
      <p class="eContent1" style="text-align:center;">
	<?php $authorValue = $this->get_blogNewsAuthorDisplay($this->blogItem->vars['author'], 'eLink1'); ?>
	<?php $tagsValue = $this->get_blogNewsTagsDisplay($this->blogItem->tagList, 'eLink1'); ?>
	
	<?php if ( $authorValue != ''  and $tagsValue != '' ) : ?>
	<?=$this->get_translation('published_by_into', array($authorValue,
	$tagsValue))?>
	<?php elseif ( $authorValue != '' ) : ?>
	<?=$this->get_translation('published_by', $authorValue);?>
	<?php elseif ( $tagsValue != '' ) : ?>
	<?=$this->get_translation('published_into', $tagsValue, 'eLink1');?>
	<?php endif; ?>
      </p>
        <?php if ($this->networkInput !== false) : ?>
	<div class="eContent1" style="text-align:center;">
	  <?=$this->networkInput->display(array('link'=>$newsLink, 'title'=>$this->blogItem->vars['title']));?>
      </div>
	<?php endif; ?>
      <div style="margin:16px 32px">
	<a name="comments"></a>
	<h2 class="eTitle3">
	  <?php if ( count($this->blogItem->vars['comments']) == 0 ) : ?>
	  <?=$this->get_translation('site_nocomment_title');?>
	  <?php elseif ( count($this->blogItem->vars['comments']) == 1 ) : ?>
	  <?=$this->get_translation('site_comment_title');?>
	  <?php else : ?>
	  <?=$this->get_translation('site_comments_title', count($this->blogItem->vars['comments']));?>
	  <?php endif; ?>
	</h2>
	<?php $alt=0; ?>
	<?php foreach ( $this->blogItem->vars['comments'] as $comment ): ?>
	<div class="eTableLine<?=$alt?>">
	  <h3 class="eTitle4">
	    <?php if ($comment->vars['website'] != '' ) : ?>
	    <?=$this->get_translation('site_comment_headerfull', array( $comment->vars['author'],
	    date_displayLongDayDateHour($comment->vars['ndate']),
	    $comment->vars['website'],
	    'eLink1'));?>
	    <?php else : ?>
	    <?=$this->get_translation('site_comment_headerlight', array( $comment->vars['author'],
	    date_displayLongDayDateHour($comment->vars['ndate'])))?>
	    <?php endif; ?>
	  </h3>
	  <?php if ( $comment->vars['title'] != '' ) : ?>
	  <p class="eContent2">
	    <?=$comment->vars['title'];?>
	  </p>
	  <?php endif; ?>
	  <p class="eContent1">
	    <?=nl2br($comment->vars['content']);?>
	  </p>
	</div>
	<?php $alt=abs($alt-1);?>
	<?php endforeach; ?>
	
	<p class="eContent1">
	  &nbsp;
	</p>
	<?php if ( $this->com_mode == 'form' ) : ?>
	<h2 class="eTitle3">
	  <?=$this->get_translation('site_comment_add');?>
	</h2>
	
	<?php if($this->configItem->vars['comment_message'] != '') : ?>
	<p class="eContent1">
	  <?=$this->configItem->vars['comment_message'];?>
	</p>
	<?php endif; ?>
	
	<?php if ( $this->com_error != '' ) : ?>
	<div class="error">
	  <?=$this->com_error?>
	</div>
	<?php endif; ?>
	<?=$this->com_form->display_header();?>
	<?=$this->com_form->display_hiddens();?>
	<table cellspacing="0" cellpadding="0" border="0" style="width:100%">
	  <tr>
	    <td class="eContent2">
	      <?=$this->get_translation('site_comment_yourname');?>
	      <span class="eContent1">
		<?=$this->get_translation('site_comment_mandatory');?>
	      </span>
	    </td>
	    <td class="eContent1" style="text-align:right;">
	      <input type="text" name="author" value="<?=$this->commentItem->vars['author']?>" maxlength="32" class="inputs" /></input>
	    </td>
	  </tr>
	  <tr>
	    <td class="eContent2">
	      <?=$this->get_translation('site_comment_youremail');?>
	      <span class="eContent1">
		<?=$this->get_translation('site_comment_mandatory');?>
	      </span>
	    </td>
	    <td class="eContent1" style="text-align:right;">
	      <input type="text" name="email" value="<?=$this->commentItem->vars['email']?>" maxlength="255" class="inputs" /></input>
	    </td>
	  </tr>
	  <tr>
	    <td class="eContent1">
	      <?=$this->get_translation('site_comment_yourwebsite');?>
	    </td>
	    <td class="eContent1" style="text-align:right;">
	      <input type="text" name="website" value="<?=$this->commentItem->vars['website']?>" maxlength="128" class="inputs" /></input>
	    </td>
	  </tr>
	  <tr>
	    <td class="eContent1">
	      <?=$this->get_translation('site_comment_yourcommtitle');?>
	    </td>
	    <td class="eContent1" style="text-align:right;">
	      <input type="text" name="title" value="<?=$this->commentItem->vars['title']?>" maxlength="128" class="inputs" /></input>
	    </td>
	  </tr>
	  <tr>
	    <td class="eContent1" colspan="2">
	      <textarea cols="40" rows="8" style="width:100%" name="content"><?=$this->commentItem->vars['content']?></textarea>
	    </td>
	  </tr>
	  <tr>
	    <td class="eContent1" colspan="2">
	      <?=$this->theme->get_button($this->get_translation('site_comment_send'), $this->com_form->get_HTMLSubmitLink());?>
	    </td>
	  </tr>
	</table>
	<?=$this->com_form->display_footer();?>
	<?php elseif ( $this->com_mode == 'save' ) : ?>
	<p class="title3">
	  <?=$this->get_translation('site_comment_saved');?>
	  <?php if ( $this->manager->config->vars['comments_validationmode']==0 ): ?>
	  <?=' '.$this->get_translation('site_comment_savedneedvalidation');?>
	  <?php endif; ?>
	</p>
	<?php endif; ?>
      </div>
      
      <?=$this->theme->get_boxContent1Footer(); ?>
      <?php if ( isset( $this->buttons ) ) : ?>
      <?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
      <?php endif; ?>
      <?=$this->theme->get_boxFooter(); ?>
      
      <?php if ( $this->configItem->vars['item_panel']==1 ) : ?>
    </td>
    <td style="vertical-align:top; padding-left:10px;">
      <?=$this->load_file('html/site_panel_box.html.inc');?>
    </td>
  </tr>
</table>
<?php endif;?>