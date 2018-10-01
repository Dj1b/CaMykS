<?php
/**
 * @brief Admin_ContentPage Module view language sub layout for page edition
 * @details Plugin / Module layout
 * @file plugin/module/Admin_ContentPage/html/modify_tab_lang_view.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Nov 2006
 * @date Modification: Sep 2018
 * @copyright 2006 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
 global $camyks;
?>
<?php foreach ($camyks->_conf['editing_languages'] as $l) : ?>
<div id="item<?= $l?>"  style="display:<?= $this->tabBuilder->get_tabDisplay($l); ?>;" class="adminControlPanel">
  <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
    <tr>
      <td class="eTableLine0 eContent2" style="width:150px">
    <?= $this->get_translation('formitem_pagetitle'); ?>
      </td>
      <td class="eTableLine0 eContent1">
    <?=(isset ($this->page->trads[$l]['title'])?$this->page->trads[$l]['title']:''); ?>
      </td>
    </tr>
    <tr>
      <td class="eTableLine1 eContent2">
    <?= $camyks->get_translation('formitem_description'); ?>
      </td>
      <td class="eTableLine1 eContent1">
    <?= nl2br(isset($this->page->trads[$l]['description']) ? $this->page->trads[$l]['description'] : '') ?>
      </td>
    </tr>
    <tr>
      <td class="eTableLine0 eContent2">
        <?= $this->get_translation('formitem_keywords'); ?>
      </td>
      <td class="eTableLine0 eContent1">
    <?= nl2br(isset ($this->page->trads[$l]['keywords']) ? $this->page->trads[$l]['keywords'] : '') ?>
      </td>
    </tr>
  </table>
</div>
<?php endforeach; ?>
<?php
/**
 * @endcond Exclude
 */
?>
