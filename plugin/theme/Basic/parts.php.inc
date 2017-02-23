<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type          : Plugin / Theme HTML Parts
 * Create Date		: Sep 2005
 * Last Modif Date      : Jan 2008
 *
 * HTML Parts for Basic Theme
 */

/* bar parts */
$this->parts['barLeft'] = '
<div class="basicBar">
';

$this->parts['barRight'] = '
</div>
';

/* box parts */

$this->parts['boxHeader'] = '
<div class="basicBox" style="%s">
';

$this->parts['boxTitleBar'] = '
  <div class="basicTitleBar">
    %s
  </div>';

$this->parts['boxTabsBarHeader'] = '';

$this->parts['boxTab'] = '';

$this->parts['boxTabSelected'] = '';

$this->parts['boxTabCSSStandart'] = '';

$this->parts['boxTabCSSSelected'] = '';

$this->parts['boxTabCSSRollover'] = '';

$this->parts['boxTabsBarFooter'] = '';

$this->parts['boxButtonsBarHeader'] = '';

$this->parts['boxButtonWithLink'] = '';

$this->parts['boxButtonWithoutLink'] = '';

$this->parts['boxButtonsBarFooter'] = '';

$this->parts['boxContent1Header'] = '
<div class="basicBoxContent1">
';

$this->parts['boxContent1Footer'] = '
</div>
';

$this->parts['boxContent2Header'] = &$this->parts['boxContent1Header'];

$this->parts['boxContent2Footer'] = &$this->parts['boxContent1Footer'];

$this->parts['boxFooter'] = '
</div>
';

$this->parts['lightBoxHeader'] = '
<div class="basicLightBox" style="%">
';

$this->parts['lightBoxFooter'] = '
</div>
';


/* button part */
$this->parts['button'] = '
<table cellspacing="0">
<tr><td class="basicButton" style="%s"
onmouseover="this.className=\'basicButtonOn\';"
onmouseout="this.className=\'basicButton\';">
  <a href="%s" class="basicButton">
    %s
  </a>
</td></tr>
</table>
';



/* layered menu */
$this->parts['layeredMenuHeader'] = '
<div id="%1$s" class="basicLayeredMenuHeader"
onmouseover="%2$s.select(\'%1$s\');"
onmouseout="%2$s.unselect(\'%1$s\');">';


$this->parts['layeredMenuSeparator'] = '
   <div class="basicLayeredMenuSeparator">
     &nbsp;
   </div>';

$this->parts['layeredMenuNoLinkItem'] = '
    <div id="%1$s" class="basicLayeredMenuItem">
      %2$s
    </div>';

$this->parts['layeredMenuLinkItem'] = '
    <a id="%1$s" href="%3$s" class="basicLayeredMenuItem"%4$s>
      %2$s
    </a>';

$this->parts['layeredMenuFooter'] = '
</div>';

?>