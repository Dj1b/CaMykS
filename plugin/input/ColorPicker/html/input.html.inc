<?php
/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Input Layout
 * Create Date		: May 2007
 * Last Modif Date	: May 2007
 * 
 * ColorPicker input layout
*/
?>

<input type="hidden" name="<?=$this->inputname?>" value="<?=$this->color?>" id="colorpicker_input<?=$this->inputname?>" />
<table cellspacing="0">
<tr>
<td>
<div style="background-color:#<?=$this->color?>; border:solid 1px black; width:30px; height:16px;cursor:pointer;"
<?php if ( $this->mode == 'popup' ) : ?>
onclick="colorpicker_open('<?=$this->inputname?>', '<?=$this->color?>', '<?=$this->config?>')" 
<?php elseif ( $this->mode == 'modal' ) :?>
onclick="colorpicker_show('<?=$this->cp_name?>', '<?=$this->inputname?>', '<?=$this->color?>')" 
<?php endif; ?>
id="colorpicker_obj<?=$this->inputname?>">
&nbsp;
</div>
</td>
<td id="colorpicker_txt<?=$this->inputname?>">
#<?=$this->color?> 
</td>
</tr>
</table>

<?php if ( $this->mode == 'modal' and $this->modaldisplay == false ) : ?>
<?php $this->modaldisplay = true; ?>
<?php $this->load_file('html/modal.html.inc') ?>
<?php endif; ?>