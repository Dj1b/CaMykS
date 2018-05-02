<?php
/**
 * @brief AdminItemListViewer Input list layout
 * @details Plugin / Input Layout
 * @file plugin/input/AdminItemListViewer/html/input_list.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Oct 2008
 * @date Modification: Apr 2018
 * @copyright 2008 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $global_theme_picts_items;

/* get columns count */
$cols = count($this->params['listcolumns']);
?>
<table cellspacing="0" cellpadding="0" border="0" style="width:100%">
    <?php /* build list head links */ ?>
    <?php $alt=1; ?>
    <?php foreach ($this->params['listlinks'] as $link) : ?>
        <?php if (count($this->params['listlinks']) == 1) : ?>
            <?php $line = 'SubHeader'; ?>
        <?php else : ?>
            <?php $line = 'Line'.$alt; ?>
        <?php endif; ?>

        <?php $spans = $this->get_listLinkColspans($link); ?>
        <tr>
        <?php if ($spans['firsts'] == 1) : ?>
            <td class="eTable<?=$line?>">
                &nbsp;
            </td>
        <?php elseif($spans['firsts'] > 1) : ?>
            <td class="eTable<?=$line?>" colspan="<?=$spans['firsts']?>">
                &nbsp;
            </td>
        <?php endif; ?>

        <td class="eTable<?=$line?>" <?=($spans['title']>1?'colspan="'.$spans['title'].'"':'')?>>
            <a href="<?=$link['url_value']?>" class="eLink2"<?= isset($link['url_target']) ? ' target="'.$link['url_target'].'" ': '';?>>
                <?=$link['title']?>
            </a>
        </td>
        <td class="eTable<?=$line?> eTableIconCell">
            <a href="<?=$link['url_value']?>"<?= isset($link['url_target']) ? ' target="'.$link['url_target'].'" ': '';?>>
            <?php if (in_array($link['icon'], $global_theme_picts_items['12']['items'])) : ?>
                <img src="<?=$this->get_icon($link['icon'], 'std')?>"
                        alt="<?=$link['title']?>" title="<?=$link['title']?>" border="0"
                        onmouseover="this.src='<?=$this->get_icon($link['icon'], 'ovr')?>';"
                        onmouseout="this.src='<?=$this->get_icon($link['icon'], 'std')?>';" />
            <?php else : ?>
                <img src="<?=$link['icon']?>" alt="<?=$link['title']?>" title="<?=$link['title']?>" border="0"
                <?php if (isset($link['icon_over'])): ?>
                        onmouseover="this.src='<?=$link['icon_over']?>';"
                        onmouseout="this.src='<?=$link['icon']?>';"
                <?php endif; ?> />
            <?php endif; ?>
            </a>
        </td>

        <?php if ($spans['lasts'] == 1) : ?>
            <td class="eTable<?=$line?>">
                &nbsp;
            </td>
        <?php elseif($spans['lasts'] > 1) : ?>
            <td class="eTable<?=$line?>" colspan="<?=$spans['lasts']?>">
                &nbsp;
            </td>
        <?php endif; ?>
        </tr>
    <?php $alt=abs($alt-1);?>
    <?php endforeach; ?>

    <?php /* build list table header */ ?>
    <tr>

        <?php if ($this->params['sort']['allowed'] === true) : ?>
            <?php foreach($this->params['listcolumns'] as $name => $column) : ?>
                <?php $c = ''; ?>
                <?php if (in_array($column['columntype'], array('button', 'checkbox', 'boolean', 'icon'))) : ?>
                    <?php $c .= ' eTableIconCell'; ?>
                <?php endif; ?>
                <?php if (isset($column['class']) and $column['class'] != '') : ?>
                    <?php $c .= ' '.$column['class'];?>
                <?php endif; ?>

                <td class="eTableHeader<?=($c != ' '?' class='.$c:'');?>"<?=(isset($column['style'])?' style="'.$column['style'].'"':'')?>>
                    <?php if ($column['columntype'] == 'checkbox') : ?>
                        <input type="checkbox" name="<?=$name?>_all" id="<?=$name?>_all" value="1" onchange="<?=$this->params['name'];?>.update_allCheckboxes('<?=$name?>');" />
                    <?php elseif ($column['title']!= '' and $this->is_columnSortable($name)) : ?>

                        <?php if ($name == $this->sortValues['column'] and $this->sortValues['way'] == 'desc') : ?>
                            <a href="javascript:<?=$this->params['name']?>.update_sortColumn('');">
                                <img src="<?=$this->get_icon('up');?>" alt="" border="0" style="float:right;"
                                    onmouseover="this.src='<?=$this->get_icon('up', 'ovr');?>';"
                                    onmouseout="this.src='<?=$this->get_icon('up');?>';" />
                                <?= $column['title']; ?></a>
                        <?php elseif($name == $this->sortValues['column']) : ?>
                            <a href="javascript:<?=$this->params['name']?>.update_sortWay('desc');">
                                <img src="<?=$this->get_icon('down');?>" alt="" border="0" style="float:right;"
                                    onmouseover="this.src='<?=$this->get_icon('down', 'ovr');?>';"
                                    onmouseout="this.src='<?=$this->get_icon('down');?>';" />
                                <?= $column['title']; ?></a>
                        <?php else : ?>
                            <a href="javascript:<?=$this->params['name']?>.update_sortColumn('<?=$name?>');">
                                <?= $column['title']; ?>
                            </a>
                        <?php endif; ?>
                <?php else : ?>
                    <?= $column['title']; ?>
                <?php endif; ?>
            </td>
        <?php endforeach; ?>
    <?php else : ?>
        <?php foreach($this->params['listcolumns'] as $name => $column) : ?>
            <?php $c = ' '; ?>
            <?php if (in_array($column['columntype'], array('button', 'checkbox', 'boolean', 'icon'))) : ?>
                <?php $c .= ' eTableIconCell'; ?>
            <?php endif; ?>
            <?php if (isset($column['class']) and $column['class'] != '') : ?>
                <?php $c .= ' '.$column['class'];?>
            <?php endif; ?>

            <td class="eTableHeader<?=($c != ' '?' class='.$c:'');?>"<?=(isset($column['style'])?' style="'.$column['style'].'"':'');?>>
                <?php if ($column['columntype'] == 'checkbox') : ?>
                    <input type="checkbox" name="<?=$name?>_all" id="<?=$name?>_all" value="1" onchange="<?=$this->params['name']?>.update_allCheckboxes('<?=$name?>');" />
                <?php else : ?>
                    <?= $column['title']; ?>
                <?php endif; ?>
            </td>
        <?php endforeach; ?>
    <?php endif; ?>
    </tr>

    <?php /* build list table header */ ?>
    <?php $alt=0; ?>
    <?php $cnt=0; ?>
    <?php foreach($this->objectList as $object) : ?>
        <?php $c = $object->is_marked()?' eContent2':''; ?>
        <tr>
            <?php foreach($this->params['listcolumns'] as $name => $column) : ?>
                <?php $c2 = $c; ?>
                <?php if (in_array($column['columntype'], array('button', 'checkbox', 'boolean', 'icon'))) : ?>
                    <?php $c2 .= ' eTableIconCell'; ?>
                <?php endif; ?>
                <?php if (isset($column['class']) and $column['class'] != '') : ?>
                    <?php $c2 .= ' '.$column['class'];?>
                <?php endif; ?>
                <td class="eTableLine<?=$alt.$c2?>">
                    <?=$this->get_itemDisplay($object, $name, $column, $cnt)?>
                </td>
        <?php endforeach; ?>
    </tr>
    <?php $alt=abs($alt-1);?>
    <?php $cnt ++ ;?>
    <?php endforeach; ?>
</table>
<?php 
/**
 * @endcond Exclude
 */
?>