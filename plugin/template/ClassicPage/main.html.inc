<?php
/*
 * CaMykS Engine
 * Developed by            : camyks.net
 * Author                  : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version          : 1.0a
 * Object Version          : 1.0
 * Object Type             : Plugin / Template Layout
 * Create Date             : Feb 2007
 * Last Modif Date         : Jan 2008
 *
 * ClassicPage templage html layout 
 */
?>
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
  <tr>
    <td colspan="2" style="height:150px;">
      <?=$this->display_module(0)?>
    </td>
  </tr>
  <tr>
    <td style="vertical-align:top;width:150px;">
      <?=$this->display_module(1)?>
    </td>
    <td style="vertical-align:top;">
      <?=$this->display_module(2)?>
    </td>
  </tr>
</table>
