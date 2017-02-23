<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Engine / Data HTML File
 * Create Date	       	: Fev 2007
 * Last Modif Date	: Jun 2008
 * 
 * Engine Help HTML File
*/
?>
<table cellspacing="0" cellpadding="0" border="0" style="height:100%; width:100%">
  <tr>
    <?php if ( count( $this->help ) > 1 ) : ?>
    <td class="adminhelplist">
      <table cellspacing="0" cellpadding="0" border="0" style="width:100%;"">
	<?php foreach ( $this->help as $i => $v ) : ?>
	<?php if ( (isset( $v['location']) and $v['location'] == 'camyks' ) or $i != "main" ) : ?>
	<tr>
	  <td id="<?=$this->name?>_menu<?=$i?>" 
	    class="<?=$camyks->theme->parts['boxTabCSSStandart']?>"
	    onmouseover="<?=strtolower($this->name)?>_helpObject.mouseover('<?=$i?>');"
	    onmouseout="<?=strtolower($this->name)?>_helpObject.mouseout('<?=$i?>');"
	    onclick="<?=strtolower($this->name)?>_helpObject.mouseclick('<?=$i?>');">
	    <?=$v['title']?>
	  </td>
	</tr>
	<?php endif; ?>
	<?php endforeach; ?>
      </table>
    </td>
    <?php endif; ?>
    <td class="adminhelptext">
      <?php foreach ( $this->help as $i => $v ) : ?>
      <div id="<?=$this->name?>_page<?=$i?>" style="display:none;padding:0px 16px;">
	<?php if ( isset ( $v['location'] ) and $v['location']=='camyks' ) : ?>
	<?php $this->load_engineFile('data/html/'.$v['html'] ); ?>
	<?php elseif ( $i != 'main' ) : ?>   
	<?php $this->load_file('help/'.$camyks->current_language.'/'.$v['html'] ); ?>
	<?php endif; ?>
      </div>
      <?php endforeach; ?>
    </td>
  </tr>
</table>