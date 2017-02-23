<?php
/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team
 * CaMykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Input Layout
 * Creation Date	: Mar 2007
 * Last Modif Date	: Mar 2007
 * 
 * TinyMCE input : TinyMCE WebEditor Integration html file
 */
?>
<textarea name="<?=$this->ta_name;?>" id="<?=$this->ta_name;?>" style="width:<?=$this->ta_sizex?>;height:<?=$this->ta_sizey?>;" cols="40" rows="8"><?php if ( $this->contentType=='text') : ?>
<?=$this->contentValue?>
<?php elseif ( $this->contentType=='file' and file_exists( $this->contentValue ) ) : ?>
<?php require_once $this->contentValue; ?>
<?php endif; ?>
</textarea>