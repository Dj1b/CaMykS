<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Jan 2008
 * Last Modif Date	: Jan 2008
 *
 * Content_GenericHTMLNews Module Site Layout : next & previous page button bar for "free" layouts
*/		
?>
<?php if ( isset( $this->buttons ) ) : ?>
<div style="margin-top:8px; padding-top:4px; border-top:solid 1px #DEDEDE;">
  <table cellspacing="0" cellpadding="0" border="0" style="width:100%">
    <tr>
      <td style="width:33%;text-align:left;">
	<?php if ( $this->buttons[0]['link'] != '' ) : ?>
	<a href="<?=$this->buttons[0]['link']?>" class="link2">
	  <?=$this->buttons[0]['title'] ?>
	</a>
	<?php else : ?>
	<?=$this->buttons[0]['title'] ?>
	<?php endif; ?> 
      </td>
      
      <td class="content2" style="width:33%; text-align:center;">
	<?=$this->buttons[1]['title'] ?>
      </td>
      
      <td style="width:33%;text-align:right;">
	<?php if ( $this->buttons[2]['link'] != '' ) : ?>
	<a href="<?=$this->buttons[2]['link']?>" class="link2">
	  <?=$this->buttons[2]['title'] ?>
	</a>
	<?php else : ?>
	<?=$this->buttons[2]['title'] ?>
	<?php endif; ?> 
      </td>
      
    </tr>
  </table>
</div>
<?php endif; ?>