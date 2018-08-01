<?php
/**
 * @brief MassiveGreenStyle Theme parts.
 * @details Plugin / Theme Parts
 * @file plugin/theme/MassiveGreenStyle/parts.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jan 2009
 * @date Modification: Aug 2018
 * @copyright 2009 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/* bar parts */
$this->parts['barLeft'] = '
<div class="massivegreenBar">
';

$this->parts['barRight'] = '
</div>
';

$this->parts['barButton'] = '
<a href="%2$s" id="%1$s" class="massivegreenBarButton" style="%4$s">
%3$s
</a>
';

$this->parts['barItem'] = '
<div id="%1$s" class="massivegreenBarItem" style="%3$s">
%2$s
</div>
';


/* box Parts */
$this->parts['boxHeader'] = '
<div class="massivegreenBoxShadow" style="%s">
  <div class="massivegreenBox">
';

$this->parts['boxTitleBar'] = '
<div class="massivegreenBoxTitleBar">
  %s
</div>
';

$this->parts['boxTabsBarHeader'] = '
<div class="massivegreenBoxTabsBar">
';

$this->parts['boxTab'] = '
<div id="tab%s" class="massivegreenBoxTab" onclick="%s" onmouseover="%s" onmouseout="%s">%s</div>';

$this->parts['boxTabSelected'] = '
<div id="tab%s" class="massivegreenBoxTabS" onclick="%s" onmouseover="%s" onmouseout="%s">%s</div>';

$this->parts['boxTabCSSStandart'] = 'massivegreenBoxTab';
$this->parts['boxTabCSSSelected'] = 'massivegreenBoxTabS';
$this->parts['boxTabCSSRollover'] = 'massivegreenBoxTabO';

$this->parts['boxTabsBarFooter'] = '
</div>';

$this->parts['boxButtonsBarHeader'] = '
<div class="massivegreenBoxButtonBar">
';

$this->parts['boxButtonWithLink'] = '
<a href="%2$s" class="massivegreenBoxButton" style="%1$s">%3$s</a>
';

$this->parts['boxButtonWithoutLink'] = '
<div class="massivegreenBoxButton" style="%1$s">%2$s</div>
';

$this->parts['boxButtonsBarFooter'] = '
</div>
';


/* box part : Content1 */
$this->parts['boxContent1Header'] = '
<div class="massivegreenBoxContent1" style="%s">
';

$this->parts['boxContent1Footer'] = '
</div>
';

/* box part : Content2 */
$this->parts['boxContent2Header'] = '
<div class="massivegreenBoxContent2" style="%s">
';

$this->parts['boxContent2Footer'] = '
</div>';

$this->parts['boxFooter'] = '
  </div>
</div>';

$this->parts['lightBoxHeader'] = '
<div class="massivegreenLightBox" style="%s">';

$this->parts['lightBoxFooter'] = '
</div>';

/* button part */
$this->parts['button'] = '
<a href="%2$s" class="massivegreenButton" style="%1$s">
  %3$s
</a>
';

$this->parts['layeredMenuHeader'] = '
<div id="%1$s" class="massivegreenLayeredMenuHeader"
onmouseover="%2$s.select(\'%1$s\');"
onmouseout="%2$s.unselect(\'%1$s\');">
';

$this->parts['layeredMenuSeparator'] = '
<div class="massivegreenLayeredMenuSeparator1">
  &nbsp;
</div>
<div class="massivegreenLayeredMenuSeparator2">
  &nbsp;
</div>';


$this->parts['layeredMenuNoLinkItem'] = '
<div id="%1$s" class="massivegreenLayeredMenuItem">
%2$s
</div>
';

$this->parts['layeredMenuLinkItem'] = '
<a id="%1$s" href="%3$s" class="massivegreenLayeredMenuItem"%4$s>
%2$s
</a>
';


$this->parts['layeredMenuFooter'] = '
</div>';

?>
