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
 * Content_GenericQuickMessage Module admin layout : edit item
 */
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title 
				 .' : '. $this->qmlist->vars['name']
				 .' [ ' .$this->qmlist->id . ' ] ');?>
<?=$this->theme->get_boxContent2Header(); ?>
<?=$this->form->display_header()?>
<?=$this->form->display_hiddens()?>
<div class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">

<tr>
<td class="listline1 content2" colspan="2">
<?=$this->get_translation('itemid', $this->qmitem->id);?>
</td>
</tr>

<tr>
<td class="listline0" style="width:150px;">
<?=$this->get_translation('state');?> :
</td>
<td class="listline0">
<select name="status" class="inputs">
<?php foreach ( $this->qmitem->get_statusValueList() as $value=>$title ) : ?>
<option value="<?=$value?>"<?=$value==$this->qmitem->vars['status']?' selected="selected"':''?>>
<?=$title?>
</option>
<?php endforeach; ?>
</select>
</tr>

<tr>
<td class="listline1">
<?=$this->get_translation('messageauthor');?> :
</td>
<td class="listline1">
<input type="text" name="author" value="<?=$this->qmitem->vars['author']?>" maxlength="64" class="inputs" />
</td>
</tr> 

<tr>
<td class="listline0">
<?=$this->get_translation('messageemail');?> :
</td>
<td class="listline0">
<input type="text" name="email" value="<?=$this->qmitem->vars['email']?>" maxlength="255" class="inputs" />
</td>
</tr>

<tr>
<td class="listline1">
<?=$this->get_translation('date');?> :
</td>
<td class="listline1">
<?=$this->form->display_dateInput($this->qmitem->vars['ndate'],
                                  'ndate');?>
</td>
</tr>


<tr>
<td class="listline0">
<?=$this->get_translation('messagetitle');?> :
</td>
<td class="listline0">
<input type="text" name="title" value="<?=$this->qmitem->vars['title']?>" maxlength="255" class="inputs" />
</td>
</tr> 

<tr>
<td class="listline1">
<?=$this->get_translation('messagecontent');?> :
</td>
<td class="listline1">
<textarea cols="40" rows="6" name="message"><?=$this->qmitem->vars['message']?></textarea>

</table>
<?$this->form->display_footer()?>
</div>  
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons );?>
<?=$this->theme->get_boxFooter(); ?>
