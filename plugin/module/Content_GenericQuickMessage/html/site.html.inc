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
 * Content_GenericQuickMessage Module site layout
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:100%;');?>
<?=$this->theme->get_boxTitleBar( $this->get_translation('site_title') )?>
<?=$this->theme->get_boxContent1Header()?>
<div id="gqmMessages<?=$this->mindex?>" style="display:<?=$this->content->vars['panel'] == 'Messages'.$this->mindex ? 'block':'none'?>;">
<table cellspacing="0" cellpadding="0" border="0">
<tr>
<td class="content2">
<a class="link1" href="javascript:content_genericquickmessage_swapPanels('Form', <?=$this->mindex?>);">
<?=$this->get_translation('postamessage') ?>
</a>
</td>
</tr>
<?php foreach ( $this->content->vars['messages'] as $message ) : ?>
<tr>
<td class="content2">
<?php if ( $message->vars['email'] != '' and mail_isValidEmail( $message->vars['email'] ) ) : ?>
<?php $author = '<a class="content2" href="'.mail_encode($message->vars['email']).'">'; ?>
<?php $author .=  $message->vars['author'] . '</a>'; ?>
<?=$this->get_translation('byauthor', $author);?>
<?php else: ?>
<?=$this->get_translation('byauthor', $message->vars['author']);?>
<?php endif; ?>
</td>
</tr>
<tr>
<td class="content3">
<?=$this->get_translation('ondate', date_displayShortDateHour($message->vars['ndate']));?>
</td>
</tr>
<tr>
<td class="content2">
<?=$message->vars['title']?>
</td>
</tr>
<td class="content1">
<?=nl2br($message->vars['message'])?>
</td>
</tr>
<tr>
<td class="">
&nbsp;
</td>
</tr>
<?php endforeach; ?>
</table>
</div>


<div id="gqmForm<?=$this->mindex?>" style="display:<?=$this->content->vars['panel'] == 'Form'.$this->mindex ? 'block':'none'?>;">
<div class="content2">
<a class="link1" href="javascript:content_genericquickmessage_swapPanels('Messages', <?=$this->mindex?>);">
<?=$this->get_translation('back') ?>
</a>
</div>
<?php if ( isset( $this->content->vars['save_message'] ) ) : ?>
<div class="content2">
<?=$this->content->vars['save_message']?>
</div>
<?php else : ?>
<?=$this->form->display_header();?>
<?=$this->form->display_hiddens();?>
<table cellspacing="0" cellpadding="0" border="0">
<tr>
<td class="content2">
<?=$this->get_translation('yourname')?> :
</td>
</tr>
<tr>
<td class="content2">
<input type="text" name="author" value="" maxlength="64" style="width:100%" />
</td>
</tr>

<tr>
<td class="content2">
<?=$this->get_translation('yourmail')?> :
</td>
</tr>
<tr>
<td class="content2">
<input type="text" name="email" value="" maxlength="255" style="width:100%" />
</td>
</tr>

<tr>
<td class="content2">
<?=$this->get_translation('messagetitle')?> :
</td>
</tr>
<tr>
<td class="content2">
<input type="text" name="title" value="" maxlength="255" style="width:100%" />
</td>
</tr>

<tr>
<td class="content2">
<?=$this->get_translation('messagecontent')?> :
</td>
</tr>
<tr>
<td class="content2">
<textarea name="message" cols="40" rows="4" style="width:100%"></textarea>
</td>
</tr>

<tr>
<td class="content2">
<?=$this->theme->get_button($this->get_translation('addmessage'),
			    $this->form->get_HTMLSubmitLink());?>
</td>
</tr>
</table>
<?=$this->form->display_footer();?>
<?php endif; ?>
</div>
<?=$this->theme->get_boxContent1Footer()?>
<?=$this->theme->get_boxFooter()?>