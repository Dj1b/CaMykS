<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a2
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: May 2007
 * Last Modif Date	: Mar 2009
 *
 * Admin_Statistics Module Admin Layout
*/
global $camyks;

$edit = $this->theme->get_pictURL('edit', 12, 'std');
$edit_ = $this->theme->get_pictURL('edit', 12, 'ovr');

$view = $this->theme->get_pictURL('view', 12, 'std');
$view_ = $this->theme->get_pictURL('view', 12, 'ovr');
?>
<?=$this->theme->get_lightBoxHeader('width:100%');?>
<?=$this->theme->get_boxContent2Header();?>
<div class="adminContentPanel">
  <table cellspacing="0" style="width:100%;">
    <?php if ( $this->check_right(1) ) : ?>
    <tr>
      <td class="eTableSubHeader eContent2">
	<a href="<?=$camyks->get_adminLink($this->name, array('object'=>'_settings'))?>" class="eLink2">
	  <?=$this->get_translation('settings');?>
	</a>
      </td>
      <td class="eTableSubHeader">
	<a href="<?=$camyks->get_adminLink($this->name, array('object'=>'_settings'))?>">
	  <img src="<?=$edit?>" border="0"
	alt="<?=$this->get_translation('settings');?>"
	title="<?=$this->get_translation('settings');?>"
	onmouseover="this.src='<?=$edit_?>';"
	onmouseout="this.src='<?=$edit?>';" />
	</a>
      </td>
    </tr>
    <?php endif; ?>
    <tr>
      <td class="eTableHeader">
	<?=$this->get_translation('objects')?>
      </td>
      <td class="eTableHeader" style="width:12px;">
        &nbsp;
      </td>
    </tr>
    
    <?php $alt = 0; ?>
    <?php foreach ( $this->registered_stats as $stat ) : ?>
    <?php if (!isset($this->settings->vars['stat_'.$stat->vars['name']])
    or $this->settings->vars['stat_'.$stat->vars['name']]) : ?>
    <tr>
      <td class="eTableLine<?=$alt?>">
	<a href="<?=$camyks->get_adminLink($this->name, array('object'=>$stat->vars['name']))?>" class="eLink1">
	  <?=$stat->vars['title']?>
	</a>
      </td>
      <td class="eTableLine<?=$alt?>">
	<a href="<?=$camyks->get_adminLink($this->name, array('object'=>$stat->vars['name']))?>">
	  <img src="<?=$view?>" border="0"
     alt=""
     onmouseover="this.src='<?=$view_?>';"
     onmouseout="this.src='<?=$view?>';" />
	</a>
      </td>
    </tr>
    <?php $alt = abs( $alt-1); ?>
    <?php endif; ?>
    <?php endforeach; ?>
  </table>
</div>
<?=$this->theme->get_boxContent2Footer();?>
<?=$this->theme->get_lightBoxFooter();?>