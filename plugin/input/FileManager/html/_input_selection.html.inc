<?php
/**
 * @brief FileManager Input selection layout
 * @details Plugin / Input layout
 * @file plugin/input/FileManager/html/input.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jun 2007
 * @date Modification: Jul 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
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
<?php
/**
 * @endcond Exclude
 */
?>
