<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Creation Date       	: Apr 2007
 * Last Modif Date	: Apr 2007
 *
 * Admin_MessagePanel Module Admin Layout : message list
 */
global $camyks;
/* get imgs url */
$edit = $camyks->theme->get_pictURL('edit', 12, 'std');
$edit_ = $camyks->theme->get_pictURL('edit', 12, 'ovr');
$del = $camyks->theme->get_pictURL('cross', 12, 'std');
$del_ = $camyks->theme->get_pictURL('cross', 12, 'ovr');
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
    <?php foreach ( $this->messages as $message ) : ?>
    <tr>
      <td class="listline0">
	<?=$this->get_translation('listfromat', array( $message->vars['user'], 
	date_displayLongFormat($message->vars['creation_date'])))?>
      </td>
      <td class="listline0" style="width:12px">
	<?php if ( $message->vars['user'] == $camyks->adminUser->login ) : ?>
	<a href="<?=$camyks->get_adminLink( $this->name, array('messageid'=>$message->id, 'openTab'=>'form' ) )?>">
	  <img src="<?=$edit?>" alt="" border="0"
	    onMouseOver="this.src='<?=$edit_?>';"
	    onMouseOut="this.src='<?=$edit?>';" /></img>
	</a>
	<?php else :?>
	&nbsp;
	<?php endif; ?>
      </td>
    </tr>
    <tr>
      <td class="listline1" colspan="2">
	<?=nl2br($message->vars['content']) ?>
      </td>
    </tr>
    <tr>
      <td>
	&nbsp; 
      </td>
    </tr>
    <?php endforeach; ?>
  </table>
</div>
  
<div id="itemform" style="display:none;" class="adminContentPanel">
  <?=$this->form->display_header();?>
  <?=$this->form->display_hiddens();?>
  <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
    <tr>
      <td class="listline0" style="width:120px;">
	<?=$this->get_translation('formtitle')?> : 
      </td>
      <td class="listline0">
	<input type="text" name="title" value="<?=$this->message->vars['title']?>" maxlength="128" class="inputs" /></input>
      </td>
    </tr>
    <tr>
      <td class="listline1">
	<?=$this->get_translation('formmessage')?> : 
      </td>
      <td class="listline1" rowspan="2">
	<textarea name="content" cols="40" rows="8" style="width:100%;"><?=$this->message->vars['content']?></textarea>
      </td>
    </tr>
    <tr>
      <td>
	&nbsp;
      </td>
    </tr>
    <tr>
      <td colspan="2" align="right" class="listline1">
	<?=$this->theme->get_button($camyks->get_translation('valid'),
	$this->form->get_HTMLSubmitLink(),
	'width:100px;');?>
      </td>
    </tr>
  </table>
  <?=$this->form->display_footer();?>
</div>
<?=$this->theme->get_boxContent2Footer();?>
<?=$this->theme->get_boxButtonsBar( $this->buttons );?>
<?=$this->theme->get_boxFooter();?>
