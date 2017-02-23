<?php
/*
 * CaMykS Engine
 * Developed by		  : Ideogram Design
 * Author		        : JB Lebrun <jb.lebrun@ideogram-design.fr>
 * CaMykS Version	  : 1.0b
 * Object Version	  : 1.0
 * Object Type	    : Plugin / Module Layout
 * Creation Date    : Mar 2010
 * Last Modif Date	: Mar 2010
 * 
 * Admin_iqsimAccountManager Module Admin Layout : english confirmation email
*/
global $camyks;
$l = $camyks->get_confValue('url').'/request.php?module=Content_iqsimAccountEditor&mode=confirm&code='.$this->accountItem->id.'-'.$this->accountItem->vars['securecode'];
?>
<p>
Dear <?=$this->accountItem->get_nameDisplay(false)?>,
</p>
<p>
Thank you for initiating your registration to the iQsim website.
</p>
<p>
Please confirm your registration by following <a href="<?=$l?>">this link</a>.
</p>
<p class="sign">
iQsim website administrator
</p>