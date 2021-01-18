<?php
/**
 * @brief SocialNetworksSharingPanel Input integrate facebook mode layout
 * @details Plugin / Input layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Jan 2021
 * @date Modification: Jan 2021
 * @copyright 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

$tabs = array();
if ($this->params['integrate_facebook_tabTimeline'])
    $tabs[] = 'timeline';
if ($this->params['integrate_facebook_tabEvents'])
    $tabs[] = 'events';
if ($this->params['integrate_facebook_tabMessages'])
    $tabs[] = 'messages';
$tabs = implode(',', $tabs);
?>
<div class="fb-page"
    data-href="https://www.facebook.com/<?= $this->params['integrate_facebook_href']; ?>"
    data-width="<?= $this->params['integrate_facebook_width']; ?>"
    data-height="<?= $this->params['integrate_facebook_height']; ?>"
    data-tabs="<?= $tabs; ?>"
    data-hide-cover="<?= $this->params['integrate_facebook_hideCover'] ? 'true' : 'false'; ?>"
    data-show-facepile="<?= $this->params['integrate_facebook_showFacePile'] ? 'true' : 'false'; ?>"
    data-hide-cta="<?= $this->params['integrate_facebook_hideCTA'] ? 'true' : 'false'; ?>"
    data-small-header="<?= $this->params['integrate_facebook_smallHeader'] ? 'true' : 'false'; ?>"
    data-adapt-container-width="<?= $this->params['integrate_facebook_adaptWidth'] ? 'true' : 'false'; ?>"
    data-lazy="<?= $this->params['integrate_facebook_lazy'] ? 'true' : 'false'; ?>"
></div>

