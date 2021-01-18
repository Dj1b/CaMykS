<?php
/**
 * @brief Admin_ThemeChecker plugin, admin checker layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jul 2007
 * @date Modification: Jan 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title); ?>
<?= $this->theme->get_boxTabsBar($this->tabs, $this->tabObject.'.mouseclick', $this->tabObject.'.mouseover', $this->tabObject.'.mouseout', 'properties'); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<div id="itemproperties" style="display:block;" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0"  style="width:100%">
        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('check_informations').$camyks->get_translation('formitem_separator'); ?>
            </td>
        </tr>

        <?php $alt=0; ?>
        <?php foreach ($this->infos as $name => $value) : ?>
            <tr>
                <td class="eTableLine<?= $alt; ?>">
                    <?= $camyks->get_translation($name).$camyks->get_translation('formitem_separator'); ?>
                </td>
                <td class="eTableLine<?= $alt; ?>">
                    <?= $value; ?>
                </td>
            </tr>
            <?php $alt = abs($alt-1); ?>
        <?php endforeach; ?>

         <tr>
            <td class="eTableLine0" colspan="2">
                &nbsp;
            </td>
        </tr>

        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('check_content').$camyks->get_translation('formitem_separator'); ?>
            </td>
        </tr>

        <?php $alt=0; ?>
        <?php foreach ($this->files as $file) : ?>
            <tr>
                <td class="eTableLine<?= $alt; ?>">
                    <?= $file['name'].$camyks->get_translation('formitem_separator'); ?>
                </td>
                <td class="eTableLine<?= $alt; ?>">
                    <?php if ($file['exists']) : ?>
                        <?= $this->get_translation('present'); ?>
                    <?php else : ?>
                        <span style="color:#CC3333;">
                            <?= $this->get_translation('missing'); ?>
                        </span>
                    <?php endif; ?>
                </td>
            </tr>
            <?php $alt = abs($alt-1); ?>
        <?php endforeach; ?>
    </table>
</div>

<div id="itemitems" style="display:none;" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0"  style="width:100%">
        <?php foreach ($this->parts as $n=>$part) : ?>
            <tr>
                <td class="eTableHeader" colspan="2">
                    <?= $this->get_translation('item_'.$n).$camyks->get_translation('formitem_separator'); ?>
                </td>
            </tr>

            <?php $alt=0; ?>
            <?php foreach ($part as $i => $item) : ?>
                <tr>
                    <td class="eTableLine<?= $alt; ?>">
                        <?= $this->get_translation('item_'.$i); ?>&nbsp;[<?= $i; ?>] <?= $camyks->get_translation('formitem_separator'); ?>
                    </td>
                    <td class="eTableLine<?= $alt; ?>">
                        <?php if ($item) : ?>
                            <?= $this->get_translation('present'); ?>
                        <?php else : ?>
                            <span style="color:#CC3333;">
                                <?= $this->get_translation('missing'); ?>
                            </span>
                        <?php endif; ?>
                    </td>
                </tr>

                <?php $alt = abs($alt-1); ?>
            <?php endforeach; ?>

            <tr>
                <td>
                    &nbsp;
                </td>
            </tr>
        <?php endforeach; ?>
    </table>
</div>

<div id="itempicts" style="display:none;" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0"  style="width:100%">

        <?php foreach ($this->picts as $size => $pict) : ?>
            <tr>
                <td class="eTableHeader" colspan="<?=($this->maxpos*2 + 1); ?>">
                    <?= $this->get_translation('pict_size',$size).$camyks->get_translation('formitem_separator'); ?>
                </td>
            </tr>
            <tr>
                <td class="eTableHeader">
                    <?= $camyks->get_translation('name'); ?>
                </td>
                <?php foreach ($pict as $imgs) : ?>
                    <?php foreach ($imgs as $pos=>$img) : ?>
                        <td class="eTableHeader">
                            &nbsp;
                        </td>
                        <td class="eTableHeader">
                            <?= $this->get_translation('pict_pos_'.$pos); ?>
                        </td>
                    <?php endforeach; ?>
                    <?php break; ?>
                <?php endforeach; ?>
            </tr>

            <?php $alt = 0; ?>
            <?php foreach ($pict as $name => $imgs) : ?>
                <tr>
                    <td class="eTableLine<?= $alt; ?>">
                        <?= $name; ?>
                    </td>
                    <?php foreach ($imgs as $pos => $img) : ?>
                        <td class="eTableLine<?= $alt; ?>" align="center">
                            <?php if ($img) : ?>
                                <img src="<?= $this->seltheme->get_pictURL($name, $size, $pos); ?>" alt=""  />
                            <?php else : ?>
                                <span style="color:#CC3333;">
                                    <?= $this->get_translation('missing'); ?>
                                </span>
                            <?php endif; ?>
                        </td>
                        <td class="eTableLine<?= $alt; ?>">
                            <?= $size.'_'.$name.'_'.$pos.'.gif'; ?>
                        </td>
                    <?php endforeach; ?>
                </tr>
                <?php $alt = abs($alt-1) ?>
            <?php endforeach; ?>
        <?php endforeach; ?>
    </table>
</div>

<div id="itemdemo" style="display:none;" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0"  style="width:100%">
        <tr>
            <td class="eTitle2">
                <?= $this->get_translation('item_bar').$camyks->get_translation('formitem_separator'); ?>
            </td>
          </tr>
          <tr>
            <td style="padding:4px 0px;">
                <?php if ($this->eparts['bar']) : ?>
                    <div style="width:300px; margin:0 auto;">
                        <?= $this->seltheme->get_barLeft(); ?>
                        <table cellspacing="0" cellpadding="0"  style="width:200px;">
                            <tr>
                                <td>
                                    <?= $this->seltheme->get_barButton($this->get_translation('item_barButton'), 'javascript:void(0);'); ?>
                                </td>
                                <td>
                                    <?= $this->seltheme->get_barButton($this->get_translation('item_barItem')); ?>
                                </td>
                            </tr>
                        </table>
                        <?= $this->seltheme->get_barRight(); ?>
                    </div>
                <?php else : ?>
                    <?= $this->get_translation('demo_uncomplete'); ?>
                <?php endif; ?>
            </td>
        </tr>
        <tr>
            <td class="eTitle2">
                <?= $this->get_translation('item_box').$camyks->get_translation('formitem_separator'); ?>
            </td>
        </tr>
        <tr>
            <td style="padding:4px 0px;">
                <?php if ($this->eparts['box']) : ?>
                    <div style="width:80%">
                        <?= $this->seltheme->get_boxHeader('width:300px;margin:0 auto;'); ?>
                        <?= $this->seltheme->get_boxTitleBar($this->get_translation('item_boxtitlebar')); ?>
                        <?= $this->seltheme->get_boxTabsBar ($this->demo_tabs, 'demo_tabObject.mouseclick', 'demo_tabObject.mouseover', 'demo_tabObject.mouseout', 'demotab1'); ?>
                        <?= $this->seltheme->get_boxContent2Header('height:100px;'); ?>
                        <div id="itemdemotab1" style="display:block;padding:0px;width:100%;">
                            <?= $this->get_translation('demo_tabcontenttext', 1); ?>
                        </div>
                        <div id="itemdemotab2" style="display:none;padding:0px;width:100%;">
                            <?= $this->get_translation('demo_tabcontenttext', 2); ?>
                        </div>
                        <?= $this->seltheme->get_boxContent2Footer(); ?>
                        <?= $this->seltheme->get_boxContent1Header('height:100px;'); ?>
                        <?= $this->get_translation('demo_globalcontenttext'); ?>
                        <?= $this->seltheme->get_boxContent1Footer(); ?>
                        <?= $this->seltheme->get_boxButtonsBar($this->demo_buttons); ?>
                        <?= $this->seltheme->get_boxFooter(); ?>
                    </div>
                <?php else : ?>
                    <?= $this->get_translation('demo_uncomplete'); ?>
                <?php endif; ?>
            </td>
        </tr>
        <tr>
            <td class="eTitle2">
                <?= $this->get_translation('item_button').$camyks->get_translation('formitem_separator'); ?>
            </td>
        </tr>
        <tr>
            <td style="padding:4px 0px;">
                <div>
                    <?php if ($this->eparts['button']) : ?>
                        <?= $this->seltheme->get_button($this->get_translation('demo_button', 1), 'javascript:void(0)'); ?>
                    <?php else : ?>
                        <?= $this->get_translation('demo_uncomplete'); ?>
                    <?php endif; ?>
                </div>
            </td>
        </tr>
        <tr>
            <td class="eTitle2">
                <?= $this->get_translation('item_layeredmenu').$camyks->get_translation('formitem_separator'); ?>
            </td>
        </tr>
        <tr>
            <td style="padding:4px 0px;">
                <?php if ($this->eparts['layeredmenu']) : ?>
                    <div id="demomenuButton" style="width:150px";>
                        <?= $this->seltheme->get_button($this->get_translation('demo_button', 2), 'javascript:globalCMenu.select(\'demomenu\');', 'width:100%;'); ?>
                        <?= $this->seltheme->get_layeredMenu ('demomenu', 'globalCMenu', $this->demo_layeredmenu); ?>
                    </div>
                <?php else : ?>
                    <?= $this->get_translation('demo_uncomplete'); ?>
                <?php endif; ?>
            </td>
        </tr>
    </table>
</div>

<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
