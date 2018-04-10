<?php
/**
 * @brief Generic admin message
 * @details Engine / Generic Layout
 * @file engine/data/html/admin_message.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Feb 2007
 * @date Modification: Apr 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;
?>
<div style="margin:0 auto; width:330px; padding-top:100px;">
    <?=$camyks->theme->get_boxHeader('width:100%');?>
    <?=$camyks->theme->get_boxTitleBar(isset($this->title)?$this->title:'');?>
    <?=$camyks->theme->get_boxContent1Header('padding:20px 8px;');?>
        <div id="adminMessage" class="eContent1">
            <?=isset($this->text)?$this->text:''?>
        </div>
    <?=$camyks->theme->get_boxContent1Footer();?>
    <?=$camyks->theme->get_boxFooter();?>
</div>