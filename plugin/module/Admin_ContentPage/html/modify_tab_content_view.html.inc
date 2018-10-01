<?php
/**
 * @brief Admin_ContentPage Module view content sub layout for page edition
 * @details Plugin / Module layout
 * @file plugin/module/Admin_ContentPage/html/modify_tab_content_view.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Dec 2006
 * @date Modification: Sep 2018
 * @copyright 2006 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;
$edit_content = $this->get_fileURL('img/edit_content.gif');
?>
<div id="itemcontent" style="display:<?= $this->tabBuilder->get_tabDisplay('content'); ?>;" class="adminControlPanel">
  <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
    <tr>
      <td class="contentpagecontentcol">
    <table cellspacing="0" cellpadding="2" border="0" style="width:100%;">
      <tr>
        <td class="eTableLine0 eContent2">
          <?= $this->get_translation('formitem_theme'); ?>
        </td>
        <td class="eTableLine0 eContent1">
          <?php if ($this->page->theme == '') : ?>
          <?= $this->get_translation('defaultfromsite'); ?>
          <?php else : ?>
          <?= $this->page->theme?>
          <?php endif; ?>
        </td>
      </tr>
      <tr>
        <td class="eTableLine0 eContent2">
          <?= $this->get_translation('formitem_template'); ?>
        </td>
        <td class="eTableLine0 eContent1">
          <?php if ($this->page->template == '') : ?>
          <?= $this->get_translation('defaultfromsite'); ?>
                  <?php $t = $camyks->get_confValue('site_default_template'); ?>
          <?php else : ?>
          <?= $this->page->template?>
          <?php $t = $this->page->template?>
          <?php endif; ?>
        </td>
      </tr>
      <tr>
        <td class="eTableLine0">
              &nbsp;
            </td>
        <td class="eTableLine0">
          <div style="width:200px;height:120px;overflow:hidden;">
        <?= $camyks->templates[$t]->display_thumb(); ?>
          </div>
        </td>
      </tr>
    </table>
      </td>
      <td class="contentpagecontentcol">
    <table cellspacing="0" cellpadding="2" border="0" style="width:100%;">
      <tr>
        <td class="eTableLine0 eContent2">
          <?= $this->get_translation('formitem_modules'); ?>
        </td>
      </tr>
      <tr>
        <td class="contentpagecontent" valign="top">
          <div style="width:100%;height:400px;overflow:auto;">
        <?php $alt=1; ?>
        <?php for($i=0; $i< min($this->page->maxmodules, $camyks->templates[$t]->modules); $i++) : ?>
        <?php $m = &$this->page->modules[$i]; ?>
        <div id="module<?= $i?>" style="display:block;padding-bottom:4px;">
          <table cellspacing="0" cellpadding="0" border="0" width="100%">
            <tr>
              <td class="eTableHeader" colspan="2">
                        <?= $this->get_translation('blockx', ($i+1)); ?>
              </td>
            </tr>
            <tr>
              <td class="eTableLine<?= $alt; ?> eContent2">
            <?= $this->get_translation('formitem_module'); ?>
              </td>
              <td class="eTableLine<?= $alt; ?> eContent1">
            <?php if ($m['name'] == '') :?>
            <?= $this->get_translation('none'); ?>
            <?php else : ?>
            <?= $camyks->modules[$m['name']]->title?>
            <?php endif; ?>
              </td>
            </tr>
            <tr>
              <td class="eTableLine<?= $alt; ?> eContent2">
                    <img src="<?= $edit_content?>" alt="" border="0" style="float:left; margin:0 4px 0 0;" />
                    <?= $this->get_translation('formitem_content'); ?>
              </td>
              <td class="eTableLine<?= $alt; ?>">
            <?php if ($m['content'] == -1) : ?>
            <?= $this->get_translation('no_content'); ?>
            <?php elseif ($m['content'] == 0) : ?>
            <?= $this->get_translation('none'); ?>
            <?php else : ?>
            <?= $this->contents[$m['name']][$m['content']]; ?>
            <?php endif; ?>
              </td>
            </tr>
              <?php if ($this->allow_theme_change) : ?>
            <tr>
              <td class="eTableLine<?= $alt; ?> eContent2">
            <?= $this->get_translation('formitem_theme'); ?>
              </td>
              <td class="eTableLine<?= $alt; ?> eContent1">
            <?php if ($m['theme'] == '') : ?>
            <?= $this->get_translation('defaultfrompage'); ?>
            <?php else : ?>
            <?= $m['theme']; ?>
            <?php endif; ?>
              </td>
            </tr>
              <?php endif; ?>
          </table>
        </div>
        <?php $alt=abs($alt-1); ?>
        <?php endfor; ?>
          </div>
        </td>
      </tr>
    </table>
      </td>
    </tr>
  </table>
</div>
<?php
/**
 * @endcond Exclude
 */
?>
