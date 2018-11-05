<?php
/**
 * @brief Admin_ContentPage Module configuration edit layout
 * @details Plugin / Module layout
 * @file plugin/module/Admin_ContentPage/html/configuration/edit.html.inc
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

$file = $camyks->theme->get_pictURL('file', 12, 'std');
$file_ = $camyks->theme->get_pictURL('file', 12, 'ovr');

$minus = $camyks->theme->get_pictURL('minus', 12, 'std');
$minus_ = $camyks->theme->get_pictURL('minus', 12, 'ovr');
?>
<?php if (isset($this->isConfig) and $this->isConfig) :?>

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
          <?=$this->editform->display_hiddenInput(array('name'=>'navigation_main'));?>
          <?=$this->editform->display_textInput(array('name'=>'navigation_main_name', 'disabled'=>true, 'default'=>(isset($this->pages[$this->config->get_value('navigation_main')]) ? $this->pages[$this->config->get_value('navigation_main')]->name : '')));?>
          <?php if ($this->pc) : ?>
            <a href="javascript:ConfigEditor.open_pageChooser('navigation_main');">
              <img src="<?=$file?>"
                alt="<?=$this->get_translation('select_sitepage');?>"
                title="<?=$this->get_translation('select_sitepage');?>"
                onmouseover="this.src='<?=$file_?>';"
                onmouseout="this.src='<?=$file?>';"
                style="vertical-align:-3px;" /></a>
          <?php endif; ?>
        </td>
      </tr>

      <tr>
        <td class="eTableLine0 eContent2">
          <?=$this->get_translation('formitem_alt');?>
        </td>
        <td class="eTableLine0 eContent1">
          <?=$this->editform->display_hiddenInput(array('name'=>'navigation_alt'));?>
          <?=$this->editform->display_textInput(array('name'=>'navigation_alt_name', 'disabled'=>true, 'default'=>(isset($this->pages[$this->config->get_value('navigation_alt')]) ? $this->pages[$this->config->get_value('navigation_alt')]->name : '')));?>
          <?php if ($this->pc) : ?>
            <a href="javascript:ConfigEditor.open_pageChooser('navigation_alt');">
              <img src="<?=$file?>"
                alt="<?=$this->get_translation('select_sitepage');?>"
                title="<?=$this->get_translation('select_sitepage');?>"
                onmouseover="this.src='<?=$file_?>';"
                onmouseout="this.src='<?=$file?>';"
                style="vertical-align:-3px;" /></a>
          <?php endif; ?>
        </td>
      </tr>

      </table>

      <div id="navAddTemplate" style="display:none; font-size:0;">
      <div class="eTableLine0" style="width:140px; display:inline-block;">
        <a href="javascript:ConfigEditor.remove_navigation(XXX);" class="img">
            <img src="<?=$minus?>"
              alt="<?=$this->get_translation('remove_navigation');?>"
              title="<?=$this->get_translation('remove_navigation');?>"
              onmouseover="this.src='<?=$minus_?>';"
              onmouseout="this.src='<?=$minus?>';"
              style="vertical-align:-3px;" /></a>
        <?=$this->editform->display_textInput(array('name'=>'navAddNameXXX', 'default'=>'', 'placeholder'=>$this->get_translation('name'), 'class'=>'sinputs'));?>
      </div>

      <div class="eTableLine0" style="width:235px; display:inline-block;">
        <?=$this->editform->display_hiddenInput(array('name'=>'navAddValueXXX'));?>
        <?=$this->editform->display_textInput(array('name'=>'navAddValueXXX_name', 'disabled'=>true, 'default'=>'', 'placeholder'=>$this->get_translation('page')));?>
        <?php if ($this->pc) : ?>
          <a href="javascript:ConfigEditor.open_pageChooser('navAddValueXXX');" class="img">
            <img src="<?=$file?>"
              alt="<?=$this->get_translation('select_sitepage');?>"
              title="<?=$this->get_translation('select_sitepage');?>"
              onmouseover="this.src='<?=$file_?>';"
              onmouseout="this.src='<?=$file?>';"
              style="vertical-align:-3px;" /></a>
        <?php endif; ?>
      </div>
    </div>

    <div id="navAdds">
      <?php $cnt = 0; ?>
      <?php foreach ($this->config->get_value('navigation_additional') as $key => $page) : ?>
      <div id="navAdd<?=$cnt;?>" style="display:block; font-size:0;">
      <div class="eTableLine0" style="width:140px; display:inline-block;">
        <a href="javascript:ConfigEditor.remove_navigation(<?=$cnt;?>);" class="img">
            <img src="<?=$minus?>"
              alt="<?=$this->get_translation('remove_navigation');?>"
              title="<?=$this->get_translation('remove_navigation');?>"
              onmouseover="this.src='<?=$minus_?>';"
              onmouseout="this.src='<?=$minus?>';"
              style="vertical-align:-3px;" /></a>

        <?=$this->editform->display_textInput(array('name'=>'navAddName'.$cnt, 'default'=>$key, 'placeholder'=>$this->get_translation('name'), 'class'=>'sinputs'));?>
      </div>

      <div class="eTableLine0" style="width:235px; display:inline-block;">
        <?=$this->editform->display_hiddenInput(array('name'=>'navAddValue'.$cnt, 'default'=>$page));?>
        <?=$this->editform->display_textInput(array('name'=>'navAddValue'.$cnt.'_name', 'disabled'=>true, 'default'=>(isset($this->pages[$page]) ? $this->pages[$page]->name : $this->get_translation('page_notfound')), 'placeholder'=>$this->get_translation('page')));?>
        <?php if ($this->pc) : ?>
          <a href="javascript:ConfigEditor.open_pageChooser('navAddValue<?=$cnt;?>');" class="img">
            <img src="<?=$file?>"
              alt="<?=$this->get_translation('select_sitepage');?>"
              title="<?=$this->get_translation('select_sitepage');?>"
              onmouseover="this.src='<?=$file_?>';"
              onmouseout="this.src='<?=$file?>';"
              style="vertical-align:-3px;" /></a>

        <?php endif; ?>
      </div>
      </div>
      <?php $cnt ++; ?>
      <?php endforeach; ?>
    </div>

    <div>
      &nbsp;
    </div>

    <div class="eTableLine0">
      <?=$camyks->theme->get_button(array('title'=>$this->get_translation('add_new_navigation'), 'url'=>'javascript:ConfigEditor.insert_navigation();')); ?>
    </div>



      <div class="eTableLine0">
          &nbsp;
       </div>

       <div class="eTableHeader" >
          <?=$this->get_translation('formtitle_keypages'); ?>
        </div>

    <div id="keyPageTemplate" style="display:none; font-size:0;">
      <div class="eTableLine0" style="width:140px; display:inline-block;">
        <a href="javascript:ConfigEditor.remove_keyPage(XXX);" class="img">
            <img src="<?=$minus?>"
              alt="<?=$this->get_translation('remove_keypage');?>"
              title="<?=$this->get_translation('remove_keypage');?>"
              onmouseover="this.src='<?=$minus_?>';"
              onmouseout="this.src='<?=$minus?>';"
              style="vertical-align:-3px;" /></a>

        <?=$this->editform->display_textInput(array('name'=>'keyPageNameXXX', 'default'=>'', 'placeholder'=>$this->get_translation('key'), 'class'=>'sinputs'));?>
      </div>

      <div class="eTableLine0" style="width:235px; display:inline-block;">
        <?=$this->editform->display_hiddenInput(array('name'=>'keyPageValueXXX'));?>
        <?=$this->editform->display_textInput(array('name'=>'keyPageValueXXX_name', 'disabled'=>true, 'default'=>'', 'placeholder'=>$this->get_translation('page')));?>
        <?php if ($this->pc) : ?>
          <a href="javascript:ConfigEditor.open_pageChooser('keyPageValueXXX');" class="img">
            <img src="<?=$file?>"
              alt="<?=$this->get_translation('select_sitepage');?>"
              title="<?=$this->get_translation('select_sitepage');?>"
              onmouseover="this.src='<?=$file_?>';"
              onmouseout="this.src='<?=$file?>';"
              style="vertical-align:-3px;" />
          </a>
        <?php endif; ?>
      </div>
    </div>

    <div id="keyPages">
      <?php $cnt = 0; ?>
      <?php foreach ($this->config->get_value('keyPages') as $key => $page) : ?>
      <div id="keyPage<?=$cnt;?>" style="display:block; font-size:0;">
      <div class="eTableLine0" style="width:140px; display:inline-block;">
        <a href="javascript:ConfigEditor.remove_keyPage(<?=$cnt;?>);" class="img">
            <img src="<?=$minus?>"
              alt="<?=$this->get_translation('remove_keypage');?>"
              title="<?=$this->get_translation('remove_keypage');?>"
              onmouseover="this.src='<?=$minus_?>';"
              onmouseout="this.src='<?=$minus?>';"
              style="vertical-align:-3px;" /></a>

        <?=$this->editform->display_textInput(array('name'=>'keyPageName'.$cnt, 'default'=>$key, 'placeholder'=>$this->get_translation('key'), 'class'=>'sinputs'));?>
      </div>

      <div class="eTableLine0" style="width:235px; display:inline-block;">
        <?=$this->editform->display_hiddenInput(array('name'=>'keyPageValue'.$cnt, 'default'=>$page));?>
        <?=$this->editform->display_textInput(array('name'=>'keyPageValue'.$cnt.'_name', 'disabled'=>true, 'default'=>(isset($this->pages[$page]) ? $this->pages[$page]->name : $this->get_translation('page_notfound')), 'placeholder'=>$this->get_translation('page')));?>
        <?php if ($this->pc) : ?>
          <a href="javascript:ConfigEditor.open_pageChooser('keyPageValue<?=$cnt;?>');" class="img">
            <img src="<?=$file?>"
              alt="<?=$this->get_translation('select_sitepage');?>"
              title="<?=$this->get_translation('select_sitepage');?>"
              onmouseover="this.src='<?=$file_?>';"
              onmouseout="this.src='<?=$file?>';"
              style="vertical-align:-3px;" />
          </a>
        <?php endif; ?>
      </div>
      </div>
      <?php $cnt ++; ?>
      <?php endforeach; ?>
    </div>

    <div>
      &nbsp;
    </div>

    <div class="eTableLine0">
      <?=$camyks->theme->get_button(array('title'=>$this->get_translation('add_new_keypage'), 'url'=>'javascript:ConfigEditor.insert_keyPage();')); ?>
    </div>
  </td>
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
        <?=$this->editform->display_selectInput(array('name'=>'action_w3cValidator', 'values'=>$this->W3CValidatorStatus));?>
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
        <?=$this->editform->display_selectInput(array('name'=>'site_ogmeta', 'values'=>$this->OGMetaStatus));?>
    </td>
</tr>

<tr>
    <td class="eTableLine1 eContent2">
        <?=$this->get_translation('formitem_hreflang');?>
    </td>
    <td class="eTableLine1 eContent1">
        <?=$this->editform->display_selectInput(array('name'=>'site_hreflang', 'values'=>$this->HrefLangStatus));?>
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
      <?=$this->editform->display_selectInput(array('name'=>'page_404FallBack', 'values'=>$this->Error404FallBacks, 'onchange'=>'ConfigEditor.check_selected404FallBack();')); ?>
    </td>
</tr>
</table>

<table id="FileSelectionBox" cellspacing="2" cellpadding="0" border="0" style="width:100%; display:none;">
<tr>
    <td class="eTableLine0 eContent2" style="width:140px;">
        <?=$this->get_translation('formitem_file') ?>
    </td>
    <td class="eTableLine0 eContent1">
      <?=$this->editform->display_textInput(array('name'=>'page_404ErrorFile'));?>
    </td>
</tr>
</table>

<table id="PageSelectionBox" cellspacing="2" cellpadding="0" border="0" style="width:100%; display:none;">
<tr>
    <td class="eTableLine0 eContent2" style="width:140px;">
        <?=$this->get_translation('formitem_page') ?>
    </td>
    <td class="eTableLine0 eContent1">
      <?=$this->editform->display_textInput(array('name'=>'page_404ErrorPage'));?>
    </td>
</tr>
</table>

<table id="HeaderSendingBox" cellspacing="2" cellpadding="0" border="0" style="width:100%; display:none;">
<tr>
    <td class="eTableLine0 eContent2" style="width:140px;">
        <?=$this->get_translation('formitem_send404header');?>
    </td>
    <td class="eTableLine0 eContent1">
      <?=$this->editform->display_booleanSelectInput(array('name'=>'page_404SendHeader')); ?>
    </td>
</tr>
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

