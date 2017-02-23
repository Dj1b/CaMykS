<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Theme HTML Parts
 * Create Date		: Jan 2009
 * Last Modif Date      : Jan 2009
 *
 * Red Box theme HTML parts
 */

/* bar parts */
$this->parts['barLeft'] = '
<div class="redboxBar">
';

$this->parts['barRight'] = '
</div>
';

$this->parts['barButton'] = '
<a href="%2$s" id="%1$s" class="redboxBarButton" style="%4$s">
%3$s
</a>
';

$this->parts['barItem'] = '
<div id="%1$s" class="redboxBarItem" style="%3$s">
%2$s
</div>
';


/* box Parts */
$this->parts['boxHeader'] = '
<div class="redboxBox" style="%s">
';

$this->parts['boxTitleBar'] = '
<div class="redboxBoxTitleBar">
  %s
</div>
';

$this->parts['boxTabsBarHeader'] = '
<div class="redboxBoxTabsBar">
';

$this->parts['boxTab'] = '
<div id="tab%s" class="redboxBoxTab" onclick="%s" onmouseover="%s" onmouseout="%s">%s</div>';

$this->parts['boxTabSelected'] = '
<div id="tab%s" class="redboxBoxTabS" onclick="%s" onmouseover="%s" onmouseout="%s">%s</div>';

$this->parts['boxTabCSSStandart'] = 'redboxBoxTab';
$this->parts['boxTabCSSSelected'] = 'redboxBoxTabS';
$this->parts['boxTabCSSRollover'] = 'redboxBoxTabO';

$this->parts['boxTabsBarFooter'] = '
</div>';

$this->parts['boxButtonsBarHeader'] = '
<div class="redboxBoxButtonBar">
';

$this->parts['boxButtonWithLink'] = '
<a href="%2$s" class="redboxBoxButton" style="%1$s">%3$s</a>
';

$this->parts['boxButtonWithoutLink'] = '
<div class="redboxBoxButton" style="%1$s">%2$s</div>
';

$this->parts['boxButtonsBarFooter'] = '
</div>
';


/* box part : Content1 */
$this->parts['boxContent1Header'] = '
<div class="redboxBoxContent1" style="%s">
';

$this->parts['boxContent1Footer'] = '
</div>
';

/* box part : Content2 */
$this->parts['boxContent2Header'] = '
<div class="redboxBoxContent2" style="%s">
';

$this->parts['boxContent2Footer'] = '
</div>';

$this->parts['boxFooter'] = '
</div>';

$this->parts['lightBoxHeader'] = '
<div class="redboxLightBox" style="%s">';

$this->parts['lightBoxFooter'] = '
</div>';

/* button part */
$this->parts['button'] = '
<a href="%2$s" class="redboxButton" style="%1$s">
  %3$s
</a>
';

$this->parts['layeredMenuHeader'] = '
<div id="%1$s" class="redboxLayeredMenuHeader"
onmouseover="%2$s.select(\'%1$s\');"
onmouseout="%2$s.unselect(\'%1$s\');">
  <div class="redboxLayeredMenuBox">
';

$this->parts['layeredMenuSeparator'] = '
<div class="redboxLayeredMenuSeparator">
  &nbsp;
</div>';


$this->parts['layeredMenuNoLinkItem'] = '
<div id="%1$s" class="redboxLayeredMenuItem">
%2$s
</div>
';

$this->parts['layeredMenuLinkItem'] = '
<a id="%1$s" href="%3$s" class="redboxLayeredMenuItem"%4$s>
%2$s
</a>
';


$this->parts['layeredMenuFooter'] = '
  </div>
</div>';

?>