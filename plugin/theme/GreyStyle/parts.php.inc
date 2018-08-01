<?php
/**
 * @brief GreyStyle Theme parts.
 * @details Plugin / Theme Parts
 * @file plugin/theme/GreyStyle/parts.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jun 2005
 * @date Modification: Aug 2018
 * @copyright 2005 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/* bar parts */
$this->parts['barLeft'] = '
<table cellspacing="0" cellpadding="0" border="0" style="%s">
<tr><td class="greystyleBarLeft">&nbsp;</td>
<td class="greystyleBarCenter">
';

$this->parts['barRight'] = '
</td>
<td class="greystyleBarRight">&nbsp;</td></tr>
</table>
';

$this->parts['barButton'] = '
<div id="%s" class="greystyleBarButton"
onmouseover="this.className=\'greystyleBarButtonOver\'"
onmouseout="this.className=\'greystyleBarButton\'"
>
<a href="%s" class="greystyleBarButton">
%s
</a>
</div>';

$this->parts['barItem'] = '
<div id="%s" class="greystyleBarButtonOver">
%s
</div>
';


/* box Parts */

$this->parts['boxHeader'] = '
<table id="%2$s" cellspacing="0" cellpadding="0" border="0" class="greystyleBox %3$s" style="%1$s">
';

$this->parts['boxTitleBar'] = '
<tr>
  <td class="greystyleBoxTitleBarLine">
    <table cellspacing="0" cellpadding="0" border="0" class="greystyleBoxTitleBar">
      <tr>
        <td class="greystyleBoxTitleBar">
           %s
        </td>
      </tr>
    </table>
  </td>
</tr>';

$this->parts['boxTabsBarHeader'] = '
<tr>
  <td class="greystyleBoxTabsBarLine">
    <table cellspacing="0" cellpadding="0" border="0" class="greystyleBoxTabsBarLine">
      <tr>
        <td class="greystyleBoxTabsBar">
          <table cellspacing="0" cellpadding="0" border="0" class="greystyleBoxTabsBar">
            <tr>';

$this->parts['boxTab'] = '
<td id="tab%s" class="greystyleBoxTab" onclick="%s" onmouseover="%s" onmouseout="%s">%s</td>';

$this->parts['boxTabSelected'] = '
<td id="tab%s" class="greystyleBoxTabS" onclick="%s" onmouseover="%s" onmouseout="%s">%s</td>';

$this->parts['boxTabCSSStandart'] = 'greystyleBoxTab';
$this->parts['boxTabCSSSelected'] = 'greystyleBoxTabS';
$this->parts['boxTabCSSRollover'] = 'greystyleBoxTabO';

$this->parts['boxTabsBarFooter'] = '
</tr>
</table>
</td>
</tr>
</table>
</td>
</tr>';

$this->parts['boxButtonsBarHeader'] = '
<tr>
  <td class="greystyleBoxButtonsBarLine">
    <table cellspacing="0" cellpadding="0" border="0" class="greystyleBoxButtonsBar">
      <tr>';

$this->parts['boxButtonWithLink'] = '
<td class="greystyleBoxButton" style="%5$s" align="center"><a style="%1$s" href="%2$s" class="greystyleBoxButton" %4$s>%3$s</a></td>';

$this->parts['boxButtonWithoutLink'] = '
<td class="greystyleBoxButton" style="%3$s" align="center" %4$s>%2$s</td>';

$this->parts['boxButtonsBarFooter'] = '
</tr>
</table>
</td>
</tr>';

/* box part : OpenContent */
$this->parts['boxOpenContentHeader'] = '
<tr>
  <td class="greystyleBoxOpenContentLine" style="%s">
    <table cellspacing="0" cellpadding="0" border="0" class="greystyleBoxOpenContent">
      <tr>
        <td class="greystyleBoxOpenContent" valign="top">';

$this->parts['boxOpenContentFooter'] = '
        </td>
      </tr>
    </table>
  </td>
</tr>';


/* box part : Content1 */
$this->parts['boxContent1Header'] = '
<tr>
  <td class="greystyleBoxContent1" style="%s">
';

$this->parts['boxContent1Footer'] = '
  </td>
</tr>
';

/* box part : Content2 */
$this->parts['boxContent2Header'] = '
<tr>
  <td class="greystyleBoxContent2Line" style="%s">
    <table cellspacing="0" cellpadding="0" border="0" class="greystyleBoxContent2">
      <tr>
        <td class="greystyleBoxContent2" valign="top">';

$this->parts['boxContent2Footer'] = '
        </td>
      </tr>
    </table>
  </td>
</tr>';

$this->parts['boxFooter'] = '
</table>';

/* light box : Header */
$this->parts['lightBoxHeader'] = '
<table cellspacing="0" cellpadding="0" border="0" style="%s">';


/* light box : Footer */
$this->parts['lightBoxFooter'] = '
</table>';


/* button part */
$this->parts['button'] = '
<table cellspacing="0">
<tr><td class="greystyleButtonOuterBox" style="%s">
  <div class="greystyleButtonInnerBox">
    <a href="%s" class="greystyleButton">
      %s
    </a>
  </div>
</td></tr>
</table>
';

$this->parts['layeredMenuHeader'] = '
<div id="%1$s" class="greystyleLayeredMenuHeader"
onmouseover="%2$s.select(\'%1$s\');"
onmouseout="%2$s.unselect(\'%1$s\');">';

$this->parts['layeredMenuSeparator'] = '
<div class="greystyleLayeredMenuSeparator">
  &nbsp;
</div>';


$this->parts['layeredMenuNoLinkItem'] = '
<div id="%1$s" class="greystyleLayeredMenuItem">
%2$s
</div>
';

$this->parts['layeredMenuLinkItem'] = '
<a id="%1$s" href="%3$s" class="greystyleLayeredMenuItem"%4$s>
%2$s
</a>
';


$this->parts['layeredMenuFooter'] = '
</div>';
?>
