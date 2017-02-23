<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date		: May 2007
 * Last Modif Date	: Jun 2008
 *
 * Admin_MyShortcuts module layout
 */
global $camyks;
$view = $this->theme->get_pictURL('view', 12, 'std');
$view_ = $this->theme->get_pictURL('view', 12, 'ovr');
$edit = $this->theme->get_pictURL('edit', 12, 'std');
$edit_ = $this->theme->get_pictURL('edit', 12, 'ovr');
$delete = $this->theme->get_pictURL('cross', 12, 'std');
$delete_ = $this->theme->get_pictURL('cross', 12, 'ovr');
?>
<?=$this->theme->get_boxHeader('width:600px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title );?>
<?=$this->theme->get_boxContent2Header();?>
<div class="adminContentPanel">
<table cellspacing="0" style="width:100%;">
  <tr>
    <td class="eTableHeader">
      <?=$camyks->get_translation('title')?>
    </td>
    <td class="eTableHeader">
      <?=$this->get_translation('adddate')?>
    </td>
    <td class="eTableHeader" colspan="3">
      &nbsp;
    </td>
  </tr>
  <?php $alt=0; ?>
  <?php foreach ( $this->slist as $shortcut ) : ?>
  <tr>
    <td class="eTableLine<?=$alt?> eContent1">
      <?=$shortcut->vars['name']?>
    </td>
    <td class="eTableLine<?=$alt?> eContent1">
      <?=date_displayQuickFormat( $shortcut->vars['_date'])?>
    </td>
    <td class="eTableLine<?=$alt?> eTableIconCell">
      <a href="<?=$camyks->get_adminLink().'?'.htmlentities($shortcut->vars['url'])?>">
	<img src="<?=$view?>" border="0"
          alt="<?=$this->get_translation('open_shortcut');?>"
          title="<?=$this->get_translation('open_shortcut');?>"
	  onmouseover="this.src='<?=$view_?>';"
	  onmouseout="this.src='<?=$view?>';" />
      </a>
    </td>
    <td class="eTableLine<?=$alt?> eTableIconCell">
      <a href="<?=$camyks->get_adminLink($this->name, array('mode'=>'edit', 'id'=>$shortcut->id ))?>">
	<img src="<?=$edit?>" border="0"
          alt="<?=$this->get_translation('edit_shortcut');?>"
          title="<?=$this->get_translation('edit_shortcut');?>"
	  onmouseover="this.src='<?=$edit_?>';"
	  onmouseout="this.src='<?=$edit?>';" />
      </a>
    </td>
    <td class="eTableLine<?=$alt?> eTableIconCell">
      <a href="javascript:adminengine_confirmRedirect(shortcutsDeleteLink+<?=$shortcut->id?>, shortcutsDeleteMessage);">
	<img src="<?=$delete?>" border="0"
          alt="<?=$this->get_translation('delete_shortcut');?>"
          title="<?=$this->get_translation('delete_shortcut');?>"
	  onmouseover="this.src='<?=$delete_?>';"
	  onmouseout="this.src='<?=$delete?>';" />
      </a>
    </td>
  </tr>
  <?php $alt = abs ( $alt-1 ); ?>
  <?php endforeach; ?>  
</table>
</div>
<?=$this->theme->get_boxContent2Footer();?>
<?=$this->theme->get_boxButtonsBar($this->buttons);?>
<?=$this->theme->get_boxFooter( );?>