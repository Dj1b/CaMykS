<?php
/*
 * CaMyks Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a2
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Dec 2007
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
<?=$this->theme->get_boxContent2Header(); ?>
<div id="itemproperties" style="display:block;" class="adminContentPanel">
  <?=$this->form->display_header()?>
  <?=$this->form->display_hiddens()?>
  <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
    <tr>
      <td class="eTableLine0 eContent2" style="width:150px;">
	<?=$camyks->get_translation('formitem_name')?>
      </td>
      <td class="eTableLine0">
	<input type="text" name="name" value="<?=$this->newslist->vars['name']?>" maxlength="64" class="inputs" />
      </td>
    </tr>
    <tr>
      <td class="eTableLine1 eContent2">
	<?=$this->get_translation('count_list')?>
      </td>
      <td class="eTableLine1 eContent1">
	<input type="text" name="count_list" value="<?=$this->newslist->vars['count_list']?>" maxlength="2" class="inputs"/>
      </td>
    </tr>
    <tr>
      <td class="eTableLine0 eContent2">
	<?=$this->get_translation('layout_list')?>
      </td>
      <td class="eTableLine0">
<?=$this->form->display_selectInput(array('name'=>'layout_list', 'values'=>$this->get_listLayoutList(), 'default'=>$this->newslist->vars['layout_list']));?>
      </td>
    </tr>
    <tr>
      <td class="eTableLine1 eContent2">
	<?=$this->get_translation('layout_item')?>
      </td>
      <td class="eTableLine1">
<?=$this->form->display_selectInput(array('name'=>'layout_item', 'values'=>$this->get_newsLayoutList(), 'default'=>$this->newslist->vars['layout_item']));?>
      </td>
    </tr>
    <tr>
      <td class="eTableLine0 eContent2">
	<?=$this->get_translation('activerss')?> 
      </td>
      <td class="eTableLine0">
	<?php if ( $this->rssAvailable ) : ?>
	<input type="checkbox" name="enablerss" value="1"<?=$this->newslist->vars['enablerss']==1?' checked="checked"':''?> />
	<?php else : ?>
	<input type="hidden" name="enablerss" value="<?=$this->newslist->vars['enablerss']?>" />
	<input type="checkbox" name="enablerss_" value="1" disabled="disabled" />
	<?php endif; ?>
      </td>
    </tr>
  </table>
  <?=$this->form->display_footer()?>
</div>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?=$this->theme->get_boxFooter(); ?>
