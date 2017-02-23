<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a2
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date		: May 2007
 * Last Modif Date	: Mar 2009
 *
 * Admin_MyShortcuts module layout : edit shortcut
 */
global $camyks;
$cancel = $this->theme->get_pictURL('cross', 12, 'std');
$cancel_ = $this->theme->get_pictURL('cross', 12, 'ovr');
$valid = $this->theme->get_pictURL('valid', 12, 'std');
$valid_ = $this->theme->get_pictURL('valid', 12, 'ovr');
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title);?>
<?=$this->theme->get_boxContent2Header();?>
<?=$this->form->display_header()?>
<?=$this->form->display_hiddens()?>
<div class="adminContentPanel">
<table cellspacing="0" style="width:100%;">
  <tr>
    <td class="eTableHeader">
      <?=$camyks->get_translation('title')?>
    </td>
    <td class="eTableHeader">
      <?=$this->get_translation('adddate')?>
    </td>
    <td class="eTableHeader" colspan="2">
      &nbsp;
    </td>
  </tr>
  
  <?php $alt=0; ?>
  <?php foreach ( $this->slist as $shortcut ) : ?>
  <tr>
    <?php if ( $this->sitem->id == $shortcut->id ) : ?>
    <td class="eTableLine<?=$alt?> eContent1">
      <input type="text" name="name" value="<?=$shortcut->vars['name']?>" maxlength="32" class="inputs" />
    </td>
    <td class="eTableLine<?=$alt?> eContent1">
      <?=date_displayQuickFormat( $shortcut->vars['_date'])?>
    </td>
    <td class="eTableLine<?=$alt?> eTableIconCell">
      <a href="javascript:document.<?=$this->form->name?>.submit();">
	<img src="<?=$valid?>" alt="" border="0"
	  onmouseover="this.src='<?=$valid_?>';"
	  onmouseout="this.src='<?=$valid?>';" />
      </a>
    </td>
    <td class="eTableLine<?=$alt?> eTableIconCell">
      <a href="<?=$camyks->get_adminLink($this->name)?>">
	<img src="<?=$cancel?>" alt="" border="0"
	  onmouseover="this.src='<?=$cancel_?>';"
	  onmouseout="this.src='<?=$cancel?>';" />
      </a>
    </td>
    <?php else : ?>
    <td class="eTableLine<?=$alt?> eContent1">
      <?=$shortcut->vars['name']?>
    </td>
    <td class="eTableLine<?=$alt?> eContent1">
      <?=date_displayQuickFormat( $shortcut->vars['_date'])?>
    </td>
    <td class="eTableLine<?=$alt?>" colspan="2" style="width:24px;">
      &nbsp;
    </td>
    <?php endif; ?>
  </tr>
  <?php $alt=abs($alt-1); ?>
  <?php endforeach; ?>
</table>
</div>
<?=$this->form->display_footer()?>
  
<?=$this->theme->get_boxContent2Footer();?>
<?=$this->theme->get_boxButtonsBar($this->buttons);?>
<?=$this->theme->get_boxFooter();?>