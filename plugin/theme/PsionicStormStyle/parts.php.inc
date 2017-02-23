<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Theme HTML Parts
 * Create Date		: Jun 2008
 * Last Modif Date      : Jun 2008
 *
 * HTML parts for Psionic Storm Style theme
 */

/* bar parts */
$this->parts['barLeft'] = '
<div class="psionicstormBar" style="%s">
';

$this->parts['barRight'] = '
</div>
';

$this->parts['barButton'] = '
<a href="%2$s" id="%1$s" class="psionicstormBarButton" style="%4$s">
%3$s
</a>
';

$this->parts['barItem'] = '
<div id="%1$s" class="psionicstormBarItem" style="%3$s">
%2$s
</div>
';


/* box Parts */

$this->parts['boxHeader'] = '
<div class="psionicstormBox" style="%s">
';

$this->parts['boxTitleBar'] = '
<div class="psionicstormBoxTitleOuterBar">
  <div class="psionicstormBoxTitleInnerBar">
    <div class="psionicstormBoxTitleText">
      %s
    </div>
  </div>
</div>
';

$this->parts['boxTabsBarHeader'] = '
<div class="psionicstormBoxTabsBar">
  <div class="psionicstormBoxTabSpace">
    &nbsp;
  </div>
';

$this->parts['boxTab'] = '
<div id="tab%s" class="psionicstormBoxTab" onclick="%s" onmouseover="%s" onmouseout="%s">%s</div>';

$this->parts['boxTabSelected'] = '
<div id="tab%s" class="psionicstormBoxTabS" onclick="%s" onmouseover="%s" onmouseout="%s">%s</div>';

$this->parts['boxTabCSSStandart'] = 'psionicstormBoxTab';
$this->parts['boxTabCSSSelected'] = 'psionicstormBoxTabS';
$this->parts['boxTabCSSRollover'] = 'psionicstormBoxTabO';

$this->parts['boxTabsBarFooter'] = '
</div>';

$this->parts['boxButtonsBarHeader'] = '
<div class="psionicstormBoxButtonOuterBar">
  <div class="psionicstormBoxButtonInnerBar">
';

$this->parts['boxButtonWithLink'] = '
<div class="psionicstormBoxButtonItem">
  <a href="%2$s" class="psionicstormBoxButton" style="%1$s">%3$s</a>
</div>';

$this->parts['boxButtonWithoutLink'] = '
<div class="psionicstormBoxButtonItem">
  <div class="psionicstormBoxButton" style="%s">%s</div>
</div>';

$this->parts['boxButtonsBarFooter'] = '
  </div>
</div>';


/* box part : Content1 */
$this->parts['boxContent1Header'] = '
<div class="psionicstormBoxContent1" style="%s">
';

$this->parts['boxContent1Footer'] = '
</div>
';

/* box part : Content2 */
$this->parts['boxContent2Header'] = '
<div class="psionicstormBoxContent2Box">
  <div class="psionicstormBoxContent2" style="%s">
';

$this->parts['boxContent2Footer'] = '
  </div>
</div>';

$this->parts['boxFooter'] = '
</div>';

/* light box */
$this->parts['lightBoxHeader'] = '
<div class="psionicstormLightBox" style="%s">
';

$this->parts['lightBoxFooter'] = '
</div>';

/* button part */
$this->parts['button'] = '
<a href="%2$s" class="psionicstormButton" style="%1$s">
  %3$s
</a>
';

$this->parts['layeredMenuHeader'] = '
<div id="%1$s" class="psionicstormLayeredMenuHeader"
onmouseover="%2$s.select(\'%1$s\');"
onmouseout="%2$s.unselect(\'%1$s\');">';

$this->parts['layeredMenuSeparator'] = '
<div class="psionicstormLayeredMenuSeparator">
  &nbsp;
</div>';


$this->parts['layeredMenuNoLinkItem'] = '
<div id="%1$s" class="psionicstormLayeredMenuItem">
%2$s
</div>
';

$this->parts['layeredMenuLinkItem'] = '
<a id="%1$s" href="%3$s" class="psionicstormLayeredMenuItem"%4$s>
%2$s
</a>
';


$this->parts['layeredMenuFooter'] = '
</div>';

?>