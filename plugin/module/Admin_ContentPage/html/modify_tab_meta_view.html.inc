<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type      : Plugin / Module Layout
 * Creation Date	: Nov 2006
 * Last Modif Date  : Sep 2009
 *
 * Admin_ContentPage Module Layout : Page editor metas tab 
 */
?>
<div id="itemmetas" style="display:<?=$this->tabBuilder->get_tabDisplay('metas')?>;" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
<tr>
<td class="eTableHeader">
&nbsp;
</td>
<td class="eTableHeader">
<?=$camyks->get_translation('name'); ?>
</td>
<td class="eTableHeader">
<?=$this->get_translation('metacontent'); ?>
</td>
<td class="eTableHeader">
<?=$this->get_translation('metalanguage'); ?>
</td>
<td class="eTableHeader">
<?=$this->get_translation('metamethod'); ?>
</td>
</tr>

<?php $alt=0; ?>
<?php $count=0; ?>

<?php foreach ( $this->page->metas as $meta ) : ?>
<tr>
<td class="eTableLine<?=$alt?> eContent2">
<?= $count+1 ?>
</td>

<td class="eTableLine<?=$alt?> eContent1">
<?=$meta['name']?>
</td>
<td class="eTableLine<?=$alt?> eContent1">
<?=$meta['content']?>
</td>
<td class="eTableLine<?=$alt?> eContent1">
<?=$meta['language']?>
</td>
<td class="eTableLine<?=$alt?> eContent1">
<?php foreach( $this->meta_methods as $m ): ?>
<?php if ( $meta['method']==$m['name'] ) : ?>
<?=$m['title']?>
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