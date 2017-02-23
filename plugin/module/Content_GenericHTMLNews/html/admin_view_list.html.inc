<?php
/*
 * CaMyks Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a2
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Apr 2009
 * Last Modif Date	: Apr 2009
 * 
 * Content_GenericHTMLNews Module Admin  Layout : edit news list
*/		
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title .' : '.
				 $this->newslist->vars['name'] .' ['.
				 $this->newslist->id . ']');?>
<?=$this->theme->get_boxTabsBar($this->tabBuilder->tabs, 
				$this->tabBuilder->jsParams);?>
<?=$this->theme->get_boxContent2Header(); ?>
<div id="itemproperties" style="display:<?=$this->tabBuilder->get_tabDisplay('properties');?>;" class="adminContentPanel">
  <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
    <tr>
      <td class="eTableLine1 eContent2" style="width:150px;">
	<?=$camyks->get_translation('formitem_name')?>
      </td>
      <td class="eTableLine1 eContent1">
	<?=$this->newslist->vars['name']?>
      </td>
    </tr>
    <tr>
      <td class="eTableLine0 eContent2">
	<?=$this->get_translation('count_list')?>
      </td>
      <td class="eTableLine0 eContent1">
	<?=$this->newslist->vars['count_list']?>
      </td>
    </tr>
    <tr>
      <td class="eTableLine1 eContent2">
	<?=$this->get_translation('layout_list')?>
      </td>
      <td class="eTableLine1 eContent1">
        <?=$this->get_translation($this->newslist->vars['layout_list']) ?>
      </td>
    </tr>
    <tr>
      <td class="eTableLine0 eContent2">
	<?=$this->get_translation('layout_item')?>
      </td>
      <td class="eTableLine0 eContent1">
        <?=$this->get_translation($this->newslist->vars['layout_item']) ?>
      </td>
    </tr>
    <tr>
      <td class="eTableLine1 eContent2">
	<?=$this->get_translation('activerss')?> : 
      </td>
      <td class="listline0">
	<input type="checkbox" name="enablerss" value="1"<?=($this->newslist->vars['enablerss']==1 and $this->rssAvailable)?' checked="checked"':''?> disabled="disabled" />
      </td>
    </tr>
    <tr>
      <td class="eTableLine0" colspan="2">
<?=$this->theme->get_button(array('title'=>$camyks->get_translation('modify'),
				  'url'=>$this->get_adminLink(array('mode'=>'edit_list'))));?>
      </td>
    </tr>
  </table>
</div>
<div id="itemnewsitems" style="display:<?=$this->tabBuilder->get_tabDisplay('newsitems');?>;" class="adminContentPanel">

<?=$this->listObject->display('head');?>

<?=$this->listObject->display('list');?>

</div>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?=$this->theme->get_boxFooter(); ?>
