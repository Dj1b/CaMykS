<?php
/**
 * @brief Admin_ContentPage Module edit meta sub layout for page edition
 * @details Plugin / Module layout
 * @file plugin/module/Admin_ContentPage/html/modify_tab_meta_edit.html.inc
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

    <?php $count=0; ?>
    <?php foreach ($this->page->metas as $meta) : ?>
    <tr>
      <td class="eTableLine0 eContent2">
        <?= ($count++)+1 ?>
      </td>

      <td class="eTableLine0 eContent1">
    <input type="text" name="meta_name<?= $count?>" value="<?= $meta['name']?>" maxlength="32" class="sinputs" />
      </td>
      <td class="eTableLine0 eContent1">
    <input type="text" name="meta_content<?= $count?>" value="<?= $meta['content']?>" maxlength="255" class="sinputs" />
      </td>
      <td class="eTableLine0 eContent1">
        <?= $this->form->display_selectInput(array('name'=>'meta_language'.$count, 'values'=>$this->meta_languages, 'default'=>$meta['language'], 'class'=>'sinputs')); ?>
      </td>
      <td class="eTableLine0 eContent1">
        <?= $this->form->display_selectInput(array('name'=>'meta_method'.$count, 'values'=>$this->meta_methods, 'default'=>$meta['method'], 'class'=>'sinputs')); ?>
      </td>
    </tr>
    <?php endforeach; ?>
    <?php ++$count; ?>
    <tr>
      <td class="eTableLine1 eContent1">
    <img src="<?= $this->theme->get_pictURL('plus', 12, 'std'); ?>" alt="" border="0" />
      </td>
      <td class="eTableLine1 eContent1">
    <input type="text" name="meta_name<?= $count?>" value="" maxlength="32" class="sinputs" />
      </td>
      <td class="eTableLine1 eContent1">
    <input type="text" name="meta_content<?= $count?>" value="" maxlength="255" class="sinputs" />
      </td>
      <td class="eTableLine1 eContent1">
        <?= $this->form->display_selectInput(array('name'=>'meta_language'.$count, 'values'=>$this->meta_languages, 'default'=>'', 'class'=>'sinputs')); ?>
      </td>
      <td class="eTableLine1 eContent1">
        <?= $this->form->display_selectInput(array('name'=>'meta_method'.$count, 'values'=>$this->meta_methods, 'default'=>'hidden', 'class'=>'sinputs')); ?>
        <input type="hidden" name="meta_count" value="<?= $count+1?>" />
      </td>
    </tr>
  </table>
</div>
<?php
/**
 * @endcond Exclude
 */
?>
