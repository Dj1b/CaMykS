<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type	    : Plugin / Module Layout
 * Creation Date    : Sep 2010
 * Last Modif Date  : Sep 2010
 * 
 * Admin_GenericGuestBookManager Module layout : email notification
*/
global $camyks;
?>
<p>
<?=$this->admin->get_nameDisplay();?>,
</p>
<p>
  <?=$this->get_translation('notification_emailcontent1', 
			    array($camyks->get_confValue('url'),
				  $camyks->get_confValue('title')));?>
</p>
<p>
  <?=$this->get_translation('notification_emailsign'); ?><br/>
  <?=$camyks->get_confValue('url');?>
</p> 