<?php
/**
 * @brief MacOS7Style Theme parts.
 * @details Plugin / Theme Parts
 * @file plugin/theme/MacOS7Style/parts.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Dec 2008
 * @date Modification: Aug 2018
 * @copyright 2008 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/* bar parts */
$this->parts['barLeft'] = '
<div  style="%s">
  <div class="macos7styleBarOuterBox">
    <div class="macos7styleBarInnerBox">
';

$this->parts['barRight'] = '
    </div>
  </div>
</div>
';

$this->parts['barButton'] = '
<div id="%s" class="macos7styleBarButton"
onmouseover="this.className=\'macos7styleBarButtonOver\'"
onmouseout="this.className=\'macos7styleBarButton\'"
>
<a href="%s" class="macos7styleBarButton">
%s
</a>
</div>';

$this->parts['barItem'] = '
<div id="%s" class="macos7styleBarItem">
%s
</div>
';


/* box Parts */

$this->parts['boxHeader'] = '
<div class="macos7styleBox" style="%s">
';

$this->parts['boxTitleBar'] = '
<div class="macos7styleBoxTitleOuterBar">
  <table cellspacing="0" cellpadding="0" class="macos7styleBoxTitleInnerBar">
    <tr>
      <td class="macos7styleBoxTitleBarLeft">
        &nbsp;
      </td>
      <td class="macos7styleBoxTitleBarText">
        <span>
          %s
        </span>
      </td>
      <td class="macos7styleBoxTitleBarRight">
        &nbsp;
      </td>
    </tr>
  </table>
</div>';


$this->parts['boxTitleBarE'] = '
<div class="macos7styleBoxTitleOuterBar">
  <table cellspacing="0" cellpadding="0" class="macos7styleBoxTitleInnerBar">
    <tr>
      <td class="macos7styleBoxTitleBarLeft">
        &nbsp;
      </td>
      <td class="macos7styleBoxTitleBarText">
        &nbsp;
      </td>
      <td class="macos7styleBoxTitleBarRight">
        &nbsp;
      </td>
    </tr>
  </table>
</div>';

$this->parts['boxTabsBarHeader'] = '
<div class="macos7styleBoxTabsBar">
  <table cellspacing="0" cellpadding="0" style="macos7styleBoxTabsBar">
    <tr>
';

$this->parts['boxTab'] = '
<td id="tab%s" class="macos7styleBoxTab" onclick="%s" onmouseover="%s" onmouseout="%s">%s</td>';

$this->parts['boxTabSelected'] = '
<td id="tab%s" class="macos7styleBoxTabS" onclick="%s" onmouseover="%s" onmouseout="%s">%s</td>';

$this->parts['boxTabCSSStandart'] = 'macos7styleBoxTab';
$this->parts['boxTabCSSSelected'] = 'macos7styleBoxTabS';
$this->parts['boxTabCSSRollover'] = 'macos7styleBoxTabO';

$this->parts['boxTabsBarFooter'] = '
    </tr>
  </table>
</div>';

$this->parts['boxButtonsBarHeader'] = '
<div class="macos7styleBoxButtonsBarLine">';

$this->parts['boxButtonWithLink'] = '
<a href="%2$s" class="macos7styleBoxButton" style="%1$s">%3$s</a>';

$this->parts['boxButtonWithoutLink'] = '
<div class="macos7styleBoxItem" style="%1$s">%2$s</div>';

$this->parts['boxButtonsBarFooter'] = '
</div>
';

/* box part : contents */

$this->parts['boxContent1Header'] = '
<div class="macos7styleBoxContent1" style="%s">
';

$this->parts['boxContent1Footer'] = '
</div>
';

/* box part : Content2 */
$this->parts['boxContent2Header'] = '
<div class="macos7styleBoxContent2" style="%s">
';

$this->parts['boxContent2Footer'] = '
</div>
';

$this->parts['boxFooter'] = '
  <div class="macos7styleBoxFooter">
    &nbsp;
  </div>
</div>';

/* light box : Header */
$this->parts['lightBoxHeader'] = '
<div style="%s">';


/* light box : Footer */
$this->parts['lightBoxFooter'] = '
</div>';


/* button part */
$this->parts['button'] = '
<table cellspacing="0">
  <tr>
    <td class="macos7styleButtonOuterBox" style="%s">
      <div class="macos7styleButtonInnerBox">
        <a href="%s" class="macos7styleButton">
          %s
        </a>
      </div>
    </td>
  </tr>
</table>
';

$this->parts['layeredMenuHeader'] = '
<div id="%1$s" class="macos7styleLayeredMenuHeader"
onmouseover="%2$s.select(\'%1$s\');"
onmouseout="%2$s.unselect(\'%1$s\');">';

$this->parts['layeredMenuSeparator'] = '
<div class="macos7styleLayeredMenuSeparator">
  &nbsp;
</div>';


$this->parts['layeredMenuNoLinkItem'] = '
<div id="%1$s" class="macos7styleLayeredMenuItem">
%2$s
</div>
';

$this->parts['layeredMenuLinkItem'] = '
<a id="%1$s" href="%3$s" class="macos7styleLayeredMenuItem"%4$s>
%2$s
</a>
';


$this->parts['layeredMenuFooter'] = '
</div>';
?>
