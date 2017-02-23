<?php
/*
 * CaMykS Engine
 * Developed by		: Ideogram Design
 * Author			: JB Lebrun <jb.lebrun@ideogram-design.fr>
 * CaMykS Version	: 1.0b
 * Object Version	: 1.0
 * Object Type      : Plugin / Theme HTML Parts
 * Create Date		: Oct 2014
 * Last Modif Date  : Oct 2014
 *
 * Indigo Flat Theme HTML parts
 */
 
/* button parts */

$this->parts['button'] = '
<a class="unselectable indigoFlatStyleButton %5$s" style="%1$s" %4$s href="%2$s" target="%6$s">
%3$s
</a>
';


/* bar parts */
$this->parts['barLeft'] = '
<div class="indigoFlatStyleBar">
';

$this->parts['barRight'] = '
</div>
';

$this->parts['barButton'] = '
<a id="%s" class="indigoFlatStyleBarButton" href="%s">
%s
</a>
';

$this->parts['barItem'] = '
<div id="%s" class="unselectable indigoFlatStyleBarItem">
%s
</div>
';


/* box Parts */

$this->parts['boxHeader'] = '
<div id="%2$s" class="indigoFlatStyleBox %3$s" style="%1$s">
';

$this->parts['boxTitleBar'] = '
<div class="eTitle2">
  %s
</div>';

$this->parts['boxTabsBarHeader'] = '
<div class="indigoFlatStyleBoxTabsBarLine">
    <table cellspacing="0" cellpadding="0" border="0">
      <tr>
        <td class="indigoFlatStyleBoxTabsBar">
          <table cellspacing="0" cellpadding="0" border="0" class="indigoFlatStyleBoxTabsBar">
            <tr>';

$this->parts['boxTab'] = '
<td id="tab%s" class="unselectable indigoFlatStyleBoxTab" onclick="%s" onmouseover="%s" onmouseout="%s">%s</td>';

$this->parts['boxTabSelected'] = '
<td id="tab%s" class="unselectable indigoFlatStyleBoxTabS" onclick="%s" onmouseover="%s" onmouseout="%s">%s</td>';

$this->parts['boxTabCSSStandart'] = 'unselectable indigoFlatStyleBoxTab';
$this->parts['boxTabCSSSelected'] = 'unselectable indigoFlatStyleBoxTabS';
$this->parts['boxTabCSSRollover'] = 'unselectable indigoFlatStyleBoxTabO';

$this->parts['boxTabsBarFooter'] = '
</tr>
</table>
</td>
</tr>
</table>
</div>
';

$this->parts['boxButtonsBarHeader'] = '
<div class="indigoFlatStyleBoxButtonBar">
';

$this->parts['boxButtonWithLink'] = '
<a class="unselectable indigoFlatStyleBoxButton" style="%1$s" %4$s href="%2$s">%3$s</a>';

$this->parts['boxButtonWithoutLink'] = '
<div class="unselectable indigoFlatStyleBoxButton" style="%3$s" %4$s>%2$s</div>';

$this->parts['boxButtonsBarFooter'] = '
</div>';

/* box part : OpenContent */
$this->parts['boxOpenContentHeader'] = '
<div class="indigoFlatStyleBoxContent" style="%s">
';

$this->parts['boxOpenContentFooter'] = '
</div>
';


/* box part : Content1 */
$this->parts['boxContent1Header'] = '
<div class="indigoFlatStyleBoxContent" style="%s">
';

$this->parts['boxContent1Footer'] = '
</div>
';

/* box part : Content2 */
$this->parts['boxContent2Header'] = '
<div class="indigoFlatStyleBoxContent" style="%s">
';

$this->parts['boxContent2Footer'] = '
</div>
';

$this->parts['boxFooter'] = '
</div>';

/* light box : Header */
$this->parts['lightBoxHeader'] = '
<div class="indigoFlatStyleLightBox" style="%s">';


/* light box : Footer */
$this->parts['lightBoxFooter'] = '
</div>';

/* layered menu parts */
$this->parts['layeredMenuHeader'] = '
<div id="%1$s" class="indigoFlatStyleLayeredMenuHeader"
onmouseover="%2$s.select(\'%1$s\');"
onmouseout="%2$s.unselect(\'%1$s\');">';

$this->parts['layeredMenuSeparator'] = '
<div class="unselectable indigoFlatStyleLayeredMenuSeparator">
  &nbsp;
</div>';


$this->parts['layeredMenuNoLinkItem'] = '
<div id="%1$s" class="unselectable indigoFlatStyleLayeredMenuItem">
%2$s
</div>
';

$this->parts['layeredMenuLinkItem'] = '
<a id="%1$s" href="%3$s" class="unselectable indigoFlatStyleLayeredMenuItem"%4$s>
%2$s
</a>
';


$this->parts['layeredMenuFooter'] = '
</div>';
?>