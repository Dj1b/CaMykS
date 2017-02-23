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
 * ColorPicker input modal layout
*/
global $camyks;
?>
<div id="colorpicker_<?=$this->cp_name?>_modalwindow" 
style="display:none;position:absolute;width:350px; height:200px; padding:5px;" align="center">
<?=$camyks->theme->get_boxHeader() ?>
<?=$camyks->theme->get_boxTitleBar( $this->get_translation('windowtitle') ) ?>
<?=$camyks->theme->get_boxContent1Header() ?>
<div align="center">
<table cellspacing="0" style="background:white; border:solid 1px white;">
<?php $cols = 0; ?>
<?php $rows = 0; ?>

<?php foreach ( $this->config['colors'] as $color ) : ?>
<?php if ( $cols == 0 ) : ?>
<tr>
<?php endif ?> 

<td id="colorpicker_<?=$this->cp_name?>_<?=$color?>" 
onmouseover="colorpicker_select('<?=$this->cp_name?>', '<?=$color?>');"
onmouseout="colorpicker_unselect('<?=$this->cp_name?>', '<?=$color?>');"
onclick="colorpicker_update('<?=$this->cp_name?>', '<?=$color?>');"
style="border:solid 1px white; width:<?=$this->config['width']?>px; height:<?=$this->config['height']?>px; font-size:2px; background:#<?=$color?>; cursor:pointer;">
&nbsp;
</td>
<?php if ( ++$cols == $this->config['maxcols'] ) : ?>
</tr>
<?php $cols =0; ?>
<?php if ( ++$rows == $this->config['maxrows'] ) : ?>
<?php break; ?>
<?php endif; ?>
<?php endif ?> 
<?php endforeach; ?>

</table>
</div>
<?=$camyks->theme->get_boxContent1Footer() ?>
<?=$camyks->theme->get_boxContent1Header('height:20px;') ?>

<table cellspacing="0" style="width:100%">
<tr>
<td id="colorpicker_<?=$this->cp_name?>_oldtxt" class="title4" style="width:35%;text-align:right;padding-right:4px;">
#
</td>
<td style="width:15%">
<div id="colorpicker_<?=$this->cp_name?>_oldobj" style="border:solid 1px black; width:30px; height:16px;">
&nbsp;
</div>
</td>
<td style="width:15%" align="right">
<div id="colorpicker_<?=$this->cp_name?>_newobj"
 style="background-color:#<?=$this->color?>; border:solid 1px black; width:30px; height:16px;">
&nbsp;
</div>
</td>
<td id="colorpicker_<?=$this->cp_name?>_newtxt" class="title4" style="width:35%; padding-left:4px;">
#<?=$this->color?>
</td>
</tr>
</table>
<?=$camyks->theme->get_boxContent1Footer() ?>
<?=$camyks->theme->get_boxButtonsBar( $this->buttons ) ?>
<?=$camyks->theme->get_boxFooter() ?>
</div>