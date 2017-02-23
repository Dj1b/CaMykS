<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Theme HTML Parts
 * Create Date		: Dec 2008
 * Last Modif Date      : Dec 2008
 *
 * Blue Box theme HTML parts
 */

/* bar parts */
$this->parts['barLeft'] = '
<div class="blueboxBar">
';

$this->parts['barRight'] = '
</div>
';

$this->parts['barButton'] = '
<a href="%2$s" id="%1$s" class="blueboxBarButton" style="%4$s">
%3$s
</a>
';

$this->parts['barItem'] = '
<div id="%1$s" class="blueboxBarItem" style="%3$s">
%2$s
</div>
';


/* box Parts */
$this->parts['boxHeader'] = '
<div class="blueboxBox" style="%s">
';

$this->parts['boxTitleBar'] = '
<div class="blueboxBoxTitleBar">
  %s
</div>
';

$this->parts['boxTabsBarHeader'] = '
<div class="blueboxBoxTabsBar">
';

$this->parts['boxTab'] = '
<div id="tab%s" class="blueboxBoxTab" onclick="%s" onmouseover="%s" onmouseout="%s">%s</div>';

$this->parts['boxTabSelected'] = '
<div id="tab%s" class="blueboxBoxTabS" onclick="%s" onmouseover="%s" onmouseout="%s">%s</div>';

$this->parts['boxTabCSSStandart'] = 'blueboxBoxTab';
$this->parts['boxTabCSSSelected'] = 'blueboxBoxTabS';
$this->parts['boxTabCSSRollover'] = 'blueboxBoxTabO';

$this->parts['boxTabsBarFooter'] = '
</div>';

$this->parts['boxButtonsBarHeader'] = '
<div class="blueboxBoxButtonBar">
';

$this->parts['boxButtonWithLink'] = '
<a href="%2$s" class="blueboxBoxButton" style="%1$s">%3$s</a>
';

$this->parts['boxButtonWithoutLink'] = '
<div class="blueboxBoxButton" style="%1$s">%2$s</div>
';

$this->parts['boxButtonsBarFooter'] = '
</div>
';


/* box part : Content1 */
$this->parts['boxContent1Header'] = '
<div class="blueboxBoxContent1" style="%s">
';

$this->parts['boxContent1Footer'] = '
</div>
';

/* box part : Content2 */
$this->parts['boxContent2Header'] = '
<div class="blueboxBoxContent2" style="%s">
';

$this->parts['boxContent2Footer'] = '
</div>';

$this->parts['boxFooter'] = '
</div>';

$this->parts['lightBoxHeader'] = '
<div class="blueboxLightBox" style="%s">';

$this->parts['lightBoxFooter'] = '
</div>';

/* button part */
$this->parts['button'] = '
<a href="%2$s" class="blueboxButton" style="%1$s">
  %3$s
</a>
';

$this->parts['layeredMenuHeader'] = '
<div id="%1$s" class="blueboxLayeredMenuHeader"
onmouseover="%2$s.select(\'%1$s\');"
onmouseout="%2$s.unselect(\'%1$s\');">
  <div class="blueboxLayeredMenuBox">
';

$this->parts['layeredMenuSeparator'] = '
<div class="blueboxLayeredMenuSeparator">
  &nbsp;
</div>';


$this->parts['layeredMenuNoLinkItem'] = '
<div id="%1$s" class="blueboxLayeredMenuItem">
%2$s
</div>
';

$this->parts['layeredMenuLinkItem'] = '
<a id="%1$s" href="%3$s" class="blueboxLayeredMenuItem"%4$s>
%2$s
</a>
';


$this->parts['layeredMenuFooter'] = '
  </div>
</div>';

?>