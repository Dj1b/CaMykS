<?php
/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Input Layout
 * Creation Date	: Jul 2008
 * Last Modif Date	: Jul 2008
 * 
 * FileManager input main layout
 */
 ?>
<div>
  <?=$this->theme->get_barLeft()?>
    <div style="width:600px;">
      <table cellspacing="0" cellpadding="0">
        <tr>
          <?php foreach ( $this->selectionButtons as $b ) : ?>
            <td>
              <?=$this->theme->get_barButton($b['title'], $b['link'])?>
            </td>
          <?php endforeach; ?>
        </tr>
      </table>
    </div>
  <?=$this->theme->get_barRight()?>
</div>

<div id="adminengine_modalPopupBackground" 
  style="display:none;position:absolute;top:0px; left:0px;background:white;opacity:0.75;-moz-opacity:0.75;z-index:10000">
  &nbsp;
</div>