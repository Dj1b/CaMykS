<?php
/**
 * @brief SunnyBlocksStyle Theme parts.
 * @details Plugin / Theme Parts
 * @file plugin/theme/SunnyBlocksStyle/parts.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jul 2008
 * @date Modification: Aug 2018
 * @copyright 2008 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/* bar parts */
$this->parts['barLeft'] = '
<div class="sunnyblocksBarOuter">
  <div class="sunnyblocksBarInner">
';

$this->parts['barRight'] = '
  </div>
</div>
';

$this->parts['barButton'] = '
<a href="%2$s" id="%1$s" class="sunnyblocksBarButton" style="%4$s">
%3$s
</a>
';

$this->parts['barItem'] = '
<div id="%1$s" class="sunnyblocksBarItem" style="%3$s">
%2$s
</div>
';


/* box Parts */

$this->parts['boxHeader'] = '
<div class="sunnyblocksBox" style="%s">
';

$this->parts['boxTitleBar'] = '
<div class="sunnyblocksBoxTitleOuterBar">
  <div class="sunnyblocksBoxTitleInnerBar">
    <div class="sunnyblocksBoxTitleBarLeft">
      &nbsp;
    </div>
    <div class="sunnyblocksBoxTitleBarText">
    %s
    </div>
    <div class="sunnyblocksBoxTitleBarRight">
      &nbsp;
    </div>
  </div>
</div>
';

$this->parts['boxTabsBarHeader'] = '
<div class="sunnyblocksBoxTabsOuterBar">
  <div class="sunnyblocksBoxTabsInnerBar">
    <div class="sunnyblocksBoxTabSpace">
    &nbsp;
    </div>
';

$this->parts['boxTab'] = '
<div id="tab%s" class="sunnyblocksBoxTab" onclick="%s" onmouseover="%s" onmouseout="%s">%s</div>';

$this->parts['boxTabSelected'] = '
<div id="tab%s" class="sunnyblocksBoxTabS" onclick="%s" onmouseover="%s" onmouseout="%s">%s</div>';

$this->parts['boxTabCSSStandart'] = 'sunnyblocksBoxTab';
$this->parts['boxTabCSSSelected'] = 'sunnyblocksBoxTabS';
$this->parts['boxTabCSSRollover'] = 'sunnyblocksBoxTabO';

$this->parts['boxTabsBarFooter'] = '
  </div>
</div>';

$this->parts['boxButtonsBarHeader'] = '
<div class="sunnyblocksBoxButtonOuterBar">
  <div class="sunnyblocksBoxButtonInnerBar">
    <div class="sunnyblocksBoxButtonSpace">&nbsp;</div>
';

$this->parts['boxButtonWithLink'] = '
<a href="%2$s" class="sunnyblocksBoxButton" style="%1$s">%3$s</a>';

$this->parts['boxButtonWithoutLink'] = '
<div class="sunnyblocksBoxButton" style="%s">%s</div>';

$this->parts['boxButtonsBarFooter'] = '
    <div class="sunnyblocksBoxButton sunnyblocksBoxButtonSpace">&nbsp;</div>
  </div>
</div>';


/* box part : Content1 */
$this->parts['boxContent1Header'] = '
<div class="sunnyblocksBoxContent1" style="%s">
';

$this->parts['boxContent1Footer'] = '
</div>
';

/* box part : Content2 */
$this->parts['boxContent2Header'] = '
<div class="sunnyblocksBoxContent2Box">
  <div class="sunnyblocksBoxContent2" style="%s">
';

$this->parts['boxContent2Footer'] = '
  </div>
</div>';

$this->parts['boxFooter'] = '
</div>';

$this->parts['lightBoxHeader'] = '
<div class="sunnyblocksLightBox" style="%s">';

$this->parts['lightBoxFooter'] = '
</div>';

/* button part */
$this->parts['button'] = '
<a href="%2$s" class="sunnyblocksButton" style="%1$s">
  %3$s
</a>
';

$this->parts['layeredMenuHeader'] = '
<div id="%1$s" class="sunnyblocksLayeredMenuHeader"
onmouseover="%2$s.select(\'%1$s\');"
onmouseout="%2$s.unselect(\'%1$s\');">';

$this->parts['layeredMenuSeparator'] = '
<div class="sunnyblocksLayeredMenuSeparator">
  &nbsp;
</div>';


$this->parts['layeredMenuNoLinkItem'] = '
<div id="%1$s" class="sunnyblocksLayeredMenuItem">
%2$s
</div>
';

$this->parts['layeredMenuLinkItem'] = '
<a id="%1$s" href="%3$s" class="sunnyblocksLayeredMenuItem">
%2$s
</a>
';


$this->parts['layeredMenuFooter'] = '
</div>';

?>
