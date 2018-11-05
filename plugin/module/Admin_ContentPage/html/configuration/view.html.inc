<?php
/**
 * @brief Admin_ContentPage Module configuration view layout
 * @details Plugin / Module layout
 * @file plugin/module/Admin_ContentPage/html/configuration/view.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Dec 2014
 * @date Modification: Oct 2018
 * @copyright 2014 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;
?>
<?php if (isset($this->isConfig) and $this->isConfig) : ?>

<?=$camyks->theme->get_boxContent2Header();?>
<div class="adminContentPanel">

<?php endif; ?>

<div class="adminContentContainer">
    <div class="half">

      <table cellspacing="2" cellpadding="0" border="0" style="width:100%;">

      <tr>
        <td class="eTableHeader" colspan="2">
          <?=$this->get_translation('formtitle_navigations'); ?>
        </td>
      </tr>

      <tr>
        <td class="eTableLine0 eContent2" style="width:140px;">
          <?=$this->get_translation('formitem_main');?>
        </td>
        <td class="eTableLine0 eContent1">
          <?php if ($this->config->get_value('navigation_main') == 0) : ?>
            <span class="eContent3"><?=$this->get_translation('navigation_none');?></span>
          <?php else : ?>
            <?=(isset($this->pages[$this->config->get_value('navigation_main')]) ? $this->pages[$this->config->get_value('navigation_main')]->name : $this->get_translation('page_notfound')); ?>
          <?php endif; ?>
        </td>
      </tr>

      <tr>
        <td class="eTableLine0 eContent2">
          <?=$this->get_translation('formitem_alt');?>
        </td>
        <td class="eTableLine0 eContent1">
          <?php if ($this->config->get_value('navigation_alt') == 0) : ?>
            <span class="eContent3"><?=$this->get_translation('navigation_none');?></span>
          <?php else : ?>
            <?=(isset($this->pages[$this->config->get_value('navigation_alt')]) ? $this->pages[$this->config->get_value('navigation_alt')]->name : $this->get_translation('page_notfound')); ?>
          <?php endif; ?>
        </td>
      </tr>

      <?php if (count($this->config->get_value('navigation_additional')) > 0) : ?>
      <?php foreach ($this->config->get_value('navigation_additional') as $key => $page) : ?>
      <tr>
        <td class="eTableLine0 eContent2">
          <?=$key;?>
        </td>
        <td class="eTableLine0 eContent1">
          <?=(isset($this->pages[$page]) ? $this->pages[$page]->name : $this->get_translation('page_notfound')); ?>
        </td>
      </tr>
      <?php endforeach; ?>
      <?php endif; ?>

      <tr>
        <td class="eTableLine0" colspan="2">
          &nbsp;
        </td>
      </tr>

      <tr>
        <td class="eTableHeader" colspan="2">
          <?=$this->get_translation('formtitle_keypages'); ?>
        </td>
      </tr>

      <?php if (count($this->config->get_value('keyPages')) == 0) : ?>
      <tr>
        <td class="eTableLine0 eContent3" colspan="2">
          <?=$this->get_translation('keypage_none');?>
        </td>
      </tr>
      <?php else : ?>
      <?php foreach ($this->config->get_value('keyPages') as $key => $page) : ?>
      <tr>
        <td class="eTableLine0 eContent2">
          <?=$key;?>
        </td>
        <td class="eTableLine0 eContent1">
          <?=(isset($this->pages[$page]) ? $this->pages[$page]->name : $this->get_translation('page_notfound')); ?>
        </td>
      </tr>
      <?php endforeach; ?>
      <?php endif; ?>
    </table>
  </div>

  <div class="half">
    <table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
      <tr>
        <td class="eTableHeader" colspan="2">
          <?=$this->get_translation('formtitle_actions'); ?>
        </td>
      </tr>

      <tr>
        <td class="eTableLine0 eContent2" style="width:140px;">
          <?=$this->get_translation('formitem_w3cvalidator');?>
        </td>
        <td class="eTableLine0 eContent1">
          <?=$this->config->get_w3cValidatorTitle(); ?>
        </td>
      </tr>

      <tr>
        <td class="eTableLine0" colspan="2">
          &nbsp;
        </td>
      </tr>

      <tr>
        <td class="eTableHeader" colspan="2">
          <?=$this->get_translation('formtitle_sitetags'); ?>
        </td>
      </tr>

      <tr>
        <td class="eTableLine0 eContent2">
          <?=$this->get_translation('formitem_ogmeta');?>
        </td>
        <td class="eTableLine0 eContent1">
          <?=$this->config->get_ogMetaStatusTitle(); ?>
        </td>
      </tr>

      <tr>
        <td class="eTableLine1 eContent2">
          <?=$this->get_translation('formitem_hreflang');?>
        </td>
        <td class="eTableLine1 eContent1">
          <?=$this->config->get_hrefLangStatusTitle(); ?>
        </td>
      </tr>

      <tr>
        <td class="eTableLine0" colspan="2">
          &nbsp;
        </td>
      </tr>

      <tr>
        <td class="eTableHeader" colspan="2">
          <?=$this->get_translation('formtitle_pagesnotfound'); ?>
        </td>
      </tr>

      <tr>
        <td class="eTableLine0 eContent2">
          <?=$this->get_translation('formitem_404fallback');?>
        </td>
        <td class="eTableLine0 eContent1">
          <?=$this->config->get_404FallbackTitle(); ?>
          <?php if (in_array($this->config->vars['page_404FallBack'], array('error404_display', 'error404_redirect'))) : ?>
            (<?=$this->get_translation('formitem_file') . $this->config->vars['page_404ErrorFile'];?>)
          <?php elseif (in_array($this->config->vars['page_404FallBack'], array('page_display', 'page_redirect'))) : ?>
            (<?=$this->get_translation('formitem_page') . $this->config->vars['page_404ErrorPage'];?>)
          <?php endif; ?>
        </td>
      </tr>

      <?php if (substr($this->config->vars['page_404FallBack'], -7, 7) == 'display'): ?>
      <tr>
        <td class="eTableLine1 eContent2">
          <?=$this->get_translation('formitem_send404header');?>
        </td>
        <td class="eTableLine1 eContent1">
          <?=$camyks->get_translation($this->config->vars['page_404SendHeader']?'yes':'no');?>
        </td>
      </tr>
      <?php endif; ?>
    </table>
  </div>
</div>
<?php if (isset($this->isConfig) and $this->isConfig) :?>

</div>
<?=$camyks->theme->get_boxContent2Footer();?>

<?php endif; ?>
<?php
/**
 * @endcond Exclude
 */
?>
