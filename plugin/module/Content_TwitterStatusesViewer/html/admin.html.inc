<?php
/*
 * CaMyks Engine
 * Developed by	    : camyks.net
 * Author	    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type	    : Plugin / Module Layout
 * Creation Date    : May 2010
 * Last Modif Date  : May 2010
 * 
 * Content_TwitterStatusViewer Module Admin Layout
*/		
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:610px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title .' : '.
				 $this->configItem->vars['name'] .' ['.
				 $this->configItem->id . ']');?>
<?=$this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams);?>
<?=$this->theme->get_boxContent2Header(); ?>
<?=$this->form->display_header()?>
<?=$this->form->display_hiddens()?>
<div id="itemproperties" style="display:<?=$this->tabBuilder->get_tabDisplay('properties')?>;" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
  <tr>
    <td class="eTableLine0 eContent2" style="width:150px;">
      <?=$camyks->get_translation('formitem_name')?>
    </td>
  <td class="eTableLine0">
    <?=$this->form->display_textInput('name');?>
  </td>
</tr>

  <tr>
    <td class="eTableLine1 eContent2">
      <?=$this->get_translation('formitem_layout')?>
    </td>
    <td class="eTableLine1">
      <?=$this->form->display_selectInput(array('name'=>'layout', 'values'=>$this->get_layoutList()));?>
    </td>
  </tr>

  <tr>
    <td class="eTableLine0 eContent2">
      <?=$this->get_translation('formitem_account')?>
    </td>
    <td class="eTableLine0">
      <?=$this->form->display_textInput('account');?>
    </td>
  </tr>

  <tr>
    <td class="eTableLine1 eContent2">
      <?=$this->get_translation('formitem_tweetcount')?>
    </td>
    <td class="eTableLine1">
      <?=$this->form->display_textInput('tweetcount');?>
    </td>
  </tr>

  <tr>
    <td class="eTableLine0 eContent2">
      <?=$this->get_translation('formitem_useaccountstyle')?>
    </td>
    <td class="eTableLine0">
    <?=$this->form->display_selectInput(array('name'=>'style', 'values'=>$this->get_styleList()));?>
    </td>
  </tr>

  <tr>
    <td class="eTableLine1 eContent2">
      <?=$this->get_translation('formitem_datedisplay')?>
    </td>
    <td class="eTableLine1">
    <?=$this->form->display_selectInput(array('name'=>'datedisplay', 'values'=>$this->get_dateDisplayList()));?>
    </td>
  </tr>

</table>
</div>

<?=$this->form->display_footer()?>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?=$this->theme->get_boxFooter(); ?>