<?php
/*
 * CaMykS Engine
 * Developed by            : camyks.net
 * Author                  : CaMykS Team <camyks.contact@gmail.com> 
 * CaMykS Version          : 1.0a
 * Object Version          : 1.0
 * Object Type             : Plugin / Template layout
 * Creation Date           : Nov 2007
 * Last Modif Date         : Nov 2007 
 * History :
 * * 07-11-28 : Initial file
 *      
 * Large2Page Template Main HTML
 */
?>
<div id="pageMain">
  <div id="pageObject">
    <div id="pageHeader">
      <?=$this->display_module(0);?>
    </div>
    <div id="pageContent">
      <?=$this->display_module(1);?>
    </div>
  </div>
  <div class="camykslink" style="text-align:center;padding:4px;">
    <a href="http://www.camyks.net" target="_blank" class="camykslink">
      Powered by CaMykS
    </a>
  </div>
</div>