<?php
/**
 * @brief SocialNetworksSharingPanel Input configuration edit layout
 * @details Plugin / Input layout
 * @file plugin/input/SocialNetworksSharingPanel/html/configuration/edit.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jan 2018
 * @date Modification: Jul 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;
?>
<?= $camyks->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams); ?>
<?= $camyks->theme->get_boxContent2Header(); ?>
<div id="itemShare" style="display:<?= $this->tabBuilder->get_tabDisplay('Share')?>;"  class="adminContentPanel">
<table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
  <tr>
      <td class="eTableHeader" colspan="2">
        <?= $this->get_translation('formdesc_settings'); ?>
      </td>
    </tr>

    <tr>
      <td class="eTableLine0 eContent2">
        <?= $this->get_translation('formitem_pictureformat'); ?>
      </td>
      <td class="eTableLine0 eContent1">
        <?= $this->form->display_selectInput(array('name'=>'share_pictureFormat', 'values'=>$this->config->get_pictureFormatList())); ?>
      </td>
    </tr>

  <tr>
    <td class="eTableLine0 eContent2" colspan="2">
      &nbsp;
    </td>
  </tr>

  <tr>
    <td class="eTableHeader" colspan="2">
      <?= $this->get_translation('formtitle_networks'); ?>
    </td>
  </tr>

  <tr>
    <td class="eTableLine0 eContent2" colspan="2">
      <?= $this->get_translation('formdesc_share'); ?>
    </td>
  </tr>

  <tr>
    <td class="eTableLine0 eContent2" style="width:150px;">
      &nbsp;
    </td>
    <td class="eTableLine0 eContent1">
      &nbsp;
    </td>
  </tr>

  <?php $alt = 0; ?>
  <?php foreach ($this->networks as $network => $data) : ?>
  <?php if ($data['share'] == 1) : ?>
  <tr>
    <td class="eTableLine<?= $alt;?> eContent2">
      <?= $data['title'].$camyks->get_translation('formitem_separator'); ?>
    </td>
    <td class="eTableLine<?= $alt;?> eContent1">
      <?= $this->form->display_selectInput(array('name'=>'share_'.$network, 'values'=>$this->sharingValues)); ?>
    </td>
  </tr>
  <?php $alt = abs($alt-1); ?>
  <?php endif; ?>
  <?php endforeach; ?>

  <tr>
    <td class="eTableLine0 eContent2" colspan="2">
      &nbsp;
    </td>
  </tr>

  <tr>
    <td class="eTableHeader" colspan="2">
      <?= $this->get_translation('formtitle_like'); ?>
    </td>
  </tr>

  <tr>
    <td class="eTableLine<?= $alt;?> eContent2">
      <?= $this->networks['facebook']['title'].$camyks->get_translation('formitem_separator'); ?>
    </td>
    <td class="eTableLine<?= $alt;?> eContent2">
      <?= $this->form->display_selectInput(array('name'=>'like_facebook', 'values'=>$this->likeValues, 'class'=>'sinputs')); ?>
      &nbsp;-&nbsp;
      <?= $this->get_translation('formitem_layout'); ?> <?= $this->form->display_selectInput(array('name'=>'like_facebookLayout', 'values'=>$this->config->get_facebookLayoutList(), 'class'=>'vsinputs')); ?>
      &nbsp;-&nbsp;
      <?= $this->get_translation('formitem_size'); ?> <?= $this->form->display_selectInput(array('name'=>'like_facebookSize', 'values'=>$this->config->get_facebookSizeList(), 'class'=>'vsinputs')); ?>
      &nbsp;-&nbsp;
      <?= $this->get_translation('formitem_action'); ?> <?= $this->form->display_selectInput(array('name'=>'like_facebookAction', 'values'=>$this->config->get_facebookActionList(), 'class'=>'vsinputs')); ?>
    </td>
  </tr>
  <?php $alt = abs($alt-1); ?>

</table>
</div>

<div id="itemFollow" style="display:<?= $this->tabBuilder->get_tabDisplay('Follow')?>;"  class="adminContentPanel">
<table cellspacing="2" cellpadding="0" border="0" style="width:100%;">

    <tr>
      <td class="eTableHeader" colspan="2">
        <?= $this->get_translation('formdesc_settings'); ?>
      </td>
    </tr>

    <tr>
    <td class="eTableLine0 eContent2">
      <?= $this->get_translation('formitem_insertion'); ?>
    </td>
    <td class="eTableLine0 eContent1">
      <?= $this->form->display_selectInput(array('name'=>'follow_insertion', 'values'=>$this->config->get_followInsertionList())); ?>
    </td>
  </tr>

  <tr>
    <td class="eTableLine1 eContent2">
      <?= $this->get_translation('formitem_stylesource'); ?>
    </td>
    <td class="eTableLine1 eContent1">
      <?= $this->form->display_selectInput(array('name'=>'follow_styleSource', 'values'=>$this->config->get_followStyleSourceList())); ?>
    </td>
  </tr>

  <tr>
    <td class="eTableLine0 eContent2">
      <?= $this->get_translation('formitem_location'); ?>
    </td>
    <td class="eTableLine0 eContent1">
      <?= $this->form->display_selectInput(array('name'=>'follow_location', 'values'=>$this->config->get_followLocationList())); ?>
    </td>
  </tr>

  <tr>
    <td class="eTableLine1 eContent2">
      <?= $this->get_translation('formitem_pictureformat'); ?>
    </td>
    <td class="eTableLine1 eContent1">
      <?= $this->form->display_selectInput(array('name'=>'follow_pictureFormat', 'values'=>$this->config->get_pictureFormatList())); ?>
    </td>
  </tr>

  <tr>
    <td class="eTableLine0 eContent2" colspan="2">
      &nbsp;
    </td>
  </tr>

  <tr>
    <td class="eTableHeader" colspan="2">
      <?= $this->get_translation('formtitle_follownetworks'); ?>
    </td>
  </tr>
  <tr>
    <td class="eTableLine0 eContent2" colspan="2">
      <?= $this->get_translation('formdesc_follow'); ?>
    </td>
  </tr>

  <tr>
    <td class="eTableLine1 eContent2">
      <?= $this->get_translation('formitem_pictureformat'); ?>
    </td>
    <td class="eTableLine1 eContent1">
      <?= $this->config->get_pictureFormatValue('follow'); ?>
    </td>
  </tr>

  <tr>
    <td class="eTableLine0 eContent2" style="width:160px;">
      &nbsp;
    </td>
    <td class="eTableLine0 eContent1">
      &nbsp;
    </td>
  </tr>

  <?php $alt = 0; ?>
  <?php foreach ($this->networks as $network => $data) : ?>
  <?php if ($data['follow'] == 1) : ?>
  <tr>
    <td class="eTableLine<?= $alt;?> eContent2">
      <?= $data['title'].$camyks->get_translation('formitem_separator'); ?>
    </td>
    <td class="eTableLine<?= $alt;?> eContent1">
      <?= $this->form->display_textInput(array('name'=>'follow_'.$network, 'maxlength'=>255, 'class'=>'linputs')); ?>
    </td>
  </tr>
  <?php $alt = abs($alt-1); ?>
  <?php endif; ?>
  <?php endforeach; ?>

</table>
</div>
<?= $camyks->theme->get_boxContent2Footer(); ?>
<?php
/**
 * @endcond Exclude
 */
?>
