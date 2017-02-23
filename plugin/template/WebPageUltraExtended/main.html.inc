<?php
/*
 * CaMykS Engine
 * Developed by            : camyks.net
 * Author                  : CaMykS Team <camyks.contact@gmail.com> 
 * CaMykS Version          : 1.0a
 * Object Version          : 1.0
 * Object Type             : Plugin / Template layout
 * Creation Date           : Fev 2008
 * Last Modif Date         : Fev 2008 
 *      
 * WebPage Ultra Extended Template Main HTML
 */
global $camyks;
?>
<div id="pageMain">
  <div id="pageObject">
    <div id="pageHeader">
      <?=$this->display_module(0);?>
    </div>
    <div id="pageLeft">
      <div id="pageLeftTop">
	<?=$this->display_module(1);?>
      </div>
      <div id="pageLeftBottom">
	<?=$this->display_module(4);?>
      </div>       
    </div>
    <div id="pageContent">
      <?=$this->display_module(2);?>
    </div>
    <div id="pageRight">
      <div id="pageRightTop">
	<?=$this->display_module(3);?>
      </div>
      <div id="pageRightBottom">
	<?=$this->display_module(5);?>
      </div>
    </div>
  </div>
  <div id="pageCaMykSBox">
    <a href="http://www.camyks.net" target="_blank" id="pageCaMykSLink">
      Powered by CaMykS
    </a>
  </div>
</div>