<?php
/**
 * @brief ClassicPage Template main layout
 * @details Plugin / Template layout
 * @file plugin/template/ClassicPage/main.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Feb 2007
 * @date Modification: Aug 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
?>
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
  <tr>
    <td colspan="2" style="height:150px;">
      <?= $this->display_module(0); ?>
    </td>
  </tr>
  <tr>
    <td style="vertical-align:top; width:150px;">
      <?= $this->display_module(1); ?>
    </td>
    <td style="vertical-align:top;">
      <?= $this->display_module(2); ?>
    </td>
  </tr>
</table>
<?php
/**
 * @endcond Exclude
 */
?>
