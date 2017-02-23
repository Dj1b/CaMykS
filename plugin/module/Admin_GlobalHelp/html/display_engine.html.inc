<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * Camyks Version   	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Module Layout
 * Creation Date	: Fev 2007
 * Last Modif Date	: Fev 2008
 *
 * Admin_GlobalHelp Module Layout : display
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar( $this->title );?>
<?=$this->theme->get_boxContent2Header();?>
<div class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%">
<tr>
<?php if ( count( $this->help ) > 1 ) : ?>
  <td class="adminhelplist">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%">
    <?php foreach ( $this->help as $i => $v ) : ?>
    <tr>
      <td id="<?=$this->name?>_menu<?=$i?>" 
      	  class="<?=$camyks->theme->parts['boxTabCSSStandart']?>"
      	  onMouseOver="<?=strtolower($this->name)?>_helpObject.mouseover('<?=$i?>');"
      	  onMouseOut="<?=strtolower($this->name)?>_helpObject.mouseout('<?=$i?>');"
      	  onClick="<?=strtolower($this->name)?>_helpObject.mouseclick('<?=$i?>');"
      	  ><?=$v['title']?>
      </td>
    </tr>
    <?php endforeach; ?>
    </table>
  </td>
<?php endif; ?>
  <td class="adminhelptext">
  	<?php foreach ( $this->help as $i => $v ) : ?>
  	<div id="<?=$this->name?>_page<?=$i?>" style="display:none;padding:0px 8px;">
  		<?php require_once ( $this->help_path.'/'.$v['html'] ); ?>
  	</div>
  	<?php endforeach; ?>
  </td>
</table>
</div>
<?=$this->theme->get_boxContent2Footer();?>
<?=$this->theme->get_boxButtonsBar($this->buttons);?>
<?=$this->theme->get_boxFooter( );?>