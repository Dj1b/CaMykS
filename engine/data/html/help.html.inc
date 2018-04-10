<?php
/**
 * @brief Engine help layout file
 * @details Engine / Generic Layout
 * @file engine/data/html/help.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Feb 2007
 * @date Modification: Apr 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
?>
<table cellspacing="0" cellpadding="0" border="0" style="height:100%; width:100%">
    <tr>
        <?php if (count($this->help) > 1) : ?>
        <td class="adminhelplist">
            <table cellspacing="0" cellpadding="0" border="0" style="width:100%;"">
                <?php foreach ( $this->help as $i => $v ) : ?>
                <?php if ((isset( $v['location']) and $v['location'] == 'camyks' ) or $i != "main") : ?>
                <tr>
                    <td id="<?=$this->name?>_menu<?=$i?>" 
                        class="<?=$camyks->theme->parts['boxTabCSSStandart']?>"
                        onmouseover="<?=strtolower($this->name)?>_helpObject.mouseover('<?=$i?>');"
                        onmouseout="<?=strtolower($this->name)?>_helpObject.mouseout('<?=$i?>');"
                        onclick="<?=strtolower($this->name)?>_helpObject.mouseclick('<?=$i?>');">
                        <?=$v['title']?>
                    </td>
                </tr>
                <?php endif; ?>
                <?php endforeach; ?>
            </table>
        </td>
        <?php endif; ?>
        <td class="adminhelptext">
            <?php foreach ($this->help as $i => $v) : ?>
            <div id="<?=$this->name?>_page<?=$i?>" style="display:none;padding:0px 16px;">
                <?php if ( isset ( $v['location'] ) and $v['location']=='camyks' ) : ?>
                    <?php $this->load_engineFile('data/html/'.$v['html'] ); ?>
                <?php elseif ( $i != 'main' ) : ?>   
                    <?php $this->load_file('help/'.$camyks->current_language.'/'.$v['html'] ); ?>
                <?php endif; ?>
            </div>
            <?php endforeach; ?>
        </td>
    </tr>
</table>
<?php 
/**
 * @endcond Exclude
 */
?>