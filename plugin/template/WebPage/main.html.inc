<?php
/**
 * @brief WebPage Template main layout
 * @details Plugin / Template layout
 * @file plugin/template/WebPage/main.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Nov 2007
 * @date Modification: Aug 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
?>
<div id="pageMain">
    <div id="pageObject">
        <div id="pageHeader">
            <?= $this->display_module(0); ?>
        </div>
        <div id="pageLeft">
            <?= $this->display_module(1); ?>
        </div>
        <div id="pageContent">
            <?= $this->display_module(2); ?>
        </div>
        <div id="pageRight">
            <?= $this->display_module(3); ?>
        </div>
    </div>
    <div id="pageCaMykSBox">
        <a href="http://www.camyks.net" target="_blank" id="pageCaMykSLink">
            Powered by CaMykS
        </a>
    </div>
</div>
<?php
/**
 * @endcond Exclude
 */
?>
