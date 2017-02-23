<?php
/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CamykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Module Layout
 * Create Date		: Jun 2007
 * Last Modif Date	: Jun 2007
 *
 * Admin_MyMessages Module admin layout : read message
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title);?>
<?=$this->theme->get_boxContent1Header();?>
<div class="adminContentPanel">
<table cellspacing="0" style="width:100%;">
  <tr>
    <td class="title3">
      <?=$this->get_translation('read'.$this->view, array($this->ouser, 
      date_displayLongFormat($this->message->vars['senddate'])))?>
    </td>
  </tr>
  <tr>
    <td class="title4">
      <?=$this->message->vars['title'] ?>
    </td>
  </tr>
  <tr>
    <td class="content1">
      <?=nl2br($this->message->vars['content']) ?>
    </td>
  </tr>
</table>
</div>
<?=$this->theme->get_boxContent1Footer();?>
<?=$this->theme->get_boxButtonsBar( $this->buttons );?>
<?=$this->theme->get_boxFooter( );?>