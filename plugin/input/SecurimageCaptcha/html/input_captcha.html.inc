<?php
/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Input Layout
 * Create Date		: Jul 2009
 * Last Modif Date	: Jul 2009
 * 
 * SecurimageCaptcha captcha input layout
*/
$imgURL = 'request.php?input='.$this->name.'&amp;'.md5(uniqid(time()));
?>
<img src="<?=$imgURL?>" alt="" border="0" />