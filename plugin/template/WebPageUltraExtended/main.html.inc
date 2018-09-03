<?php
/**
 * @brief WebPageUltraExtended Template main layout
 * @details Plugin / Template layout
 * @file plugin/template/WebPageUltraExtended/main.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Feb 2008
 * @date Modification: Aug 2018
 * @copyright 2008 - 2018 CaMykS Team
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
            <div id="pageLeftTop">
                <?= $this->display_module(1); ?>
            </div>
            <div id="pageLeftBottom">
                <?= $this->display_module(4); ?>
            </div>
        </div>
        <div id="pageContent">
            <?= $this->display_module(2); ?>
        </div>
        <div id="pageRight">
            <div id="pageRightTop">
                <?= $this->display_module(3); ?>
            </div>
            <div id="pageRightBottom">
                <?= $this->display_module(5); ?>
            </div>
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
