<?php
/**
 * @brief Admin_ContentPage Module view meta sub layout for page edition
 * @details Plugin / Module layout
 * @file plugin/module/Admin_ContentPage/html/modify_tab_meta_view.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Nov 2006
 * @date Modification: Sep 2018
 * @copyright 2006 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
?>
<div id="itemmetas" style="display:<?= $this->tabBuilder->get_tabDisplay('metas'); ?>;" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
<tr>
<td class="eTableHeader">
&nbsp;
</td>
<td class="eTableHeader">
<?= $camyks->get_translation('name'); ?>
</td>
<td class="eTableHeader">
<?= $this->get_translation('metacontent'); ?>
</td>
<td class="eTableHeader">
<?= $this->get_translation('metalanguage'); ?>
</td>
<td class="eTableHeader">
<?= $this->get_translation('metamethod'); ?>
</td>
</tr>

<?php $alt=0; ?>
<?php $count=0; ?>

<?php foreach ($this->page->metas as $meta) : ?>
<tr>
<td class="eTableLine<?= $alt?> eContent2">
<?= $count+1 ?>
</td>

<td class="eTableLine<?= $alt?> eContent1">
<?= $meta['name']?>
</td>
<td class="eTableLine<?= $alt?> eContent1">
<?= $meta['content']?>
</td>
<td class="eTableLine<?= $alt?> eContent1">
<?= $meta['language']?>
</td>
<td class="eTableLine<?= $alt?> eContent1">
<?php foreach($this->meta_methods as $m): ?>
<?php if ($meta['method']==$m['name']) : ?>
<?= $m['title']?>
<?php break; ?>
<?php endif; ?>
<?php endforeach; ?>
</td>
</tr>
<?php $count++; ?>
<?php $alt = abs ($alt-1); ?>
<?php endforeach; ?>
</table>
</div>

<?php
/**
 * @endcond Exclude
 */
?>
