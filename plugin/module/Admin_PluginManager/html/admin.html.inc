<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Fev 2007
 * Last Modif Date	: Oct 2008
 * 
 * Admin_PluginManager Module Admin Layout
*/
global $camyks;
$valid = $this->theme->get_pictURL('valid', 12, 'std');
$empty = $this->theme->get_pictURL('empty', 12, 'std');
$minus = $this->theme->get_pictURL('minus', 12, 'std');

?>
<?=$this->theme->get_boxHeader('width:700px;margin: 0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title)?>
<?=$this->theme->get_boxTabsBar($this->tabs,
				$this->tabObject.'.mouseclick',
				$this->tabObject.'.mouseover',
				$this->tabObject.'.mouseout',
				$this->openTab);?>
<?=$camyks->theme->get_boxContent2Header(); ?>
<div id="itemmodules" style="display:block;" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
<tr>
  <td class="eTableHeader">
    <?=$this->get_translation('type')?>
  </td>
  <td class="eTableHeader">
    <?=$camyks->get_translation('name')?>
  </td>
  <td class="eTableHeader">
    <?=$this->get_translation('package')?>
  </td>
  <td class="eTableHeader" style="width:5px;">
    <?=$this->get_translation('version')?>
  </td>
  <td class="eTableHeader" style="width:10%;">
    <?=$this->get_translation('location')?>
  </td>
  <td class="eTableHeader" colspan="2">
    <?=$this->get_translation('state')?>
  </td>
  <td class="eTableHeader" style="width:10%;">
    <?=$this->get_translation('actions')?>
  </td>
</tr>
<?php $alt=0; ?>
<?php foreach ( $this->modules as $p ) : ?>
<tr>
  <td class="eTableLine<?=$alt;?> eContent1">
    <?=$camyks->get_translation('module_type_'.$p->type) ?>
  </td>
  <td class="eTableLine<?=$alt;?> eContent1">
    <?= $p->title ?>
   </td>
  <td class="eTableLine<?=$alt;?> eContent1">
    <?= $p->plugin_package ?>
  </td>
  <td class="eTableLine<?=$alt;?> eContent1">
    <?= $p->version ?>
  </td>
  <td class="eTableLine<?=$alt;?> eContent1">
    <?= $camyks->get_translation($p->path_type) ?>
  </td>
  <td class="eTableLine<?=$alt;?> eContent1">
    <img src="<?=$p->active?$valid:$empty?>" alt="<?=$this->get_translation(($p->active==1?'active':'inactive'))?>"
title="<?=$this->get_translation(($p->active==1?'active':'inactive'))?>" border="0" />
</td>
  <td class="eTableLine<?=$alt;?> eContent1">
    <?php $installed = $p->is_installed(); ?>
<?php if ($installed === true ) : ?>
<img src="<?=$valid?>" alt="<?=$this->get_translation('installed')?>" title="<?=$this->get_translation('installed')?>" border="0" />
<?php elseif ($installed === false ) : ?>
<img src="<?=$empty?>" alt="<?=$this->get_translation('notinstalled')?>" title="<?=$this->get_translation('notinstalled')?>" border="0" />
<?php else : ?>
<img src="<?=$minus?>" alt="<?=$this->get_translation('noinstallationrequired')?>" title="<?=$this->get_translation('noinstallationrequired')?>" border="0" />
<?php endif; ?>
  </td>
  <td class="eTableLine<?=$alt;?> eContent1" style="white-space:nowrap;">
<?php if ( ( $p->active == 0 or $p->is_installed() === false ) and $this->check_right(1)) : ?>
<a href="<?=$camyks->get_adminLink($this->name, array('mode'=>'activate', 'plugin'=>$p->name, 'type'=>'module', 'location'=>$p->path_type))?>"><?=$this->get_translation('activate')?></a>
<?php elseif ( isset($camyks->neededModules[$p->name]) ) : ?>
<span class="content2"><?=$this->get_translation('required');?></span>
<?php elseif ( $this->check_right(1) === false ) : ?>
&nbsp;
<?php else : ?>
<a href="<?=$camyks->get_adminLink($this->name, array('mode'=>'desactivate', 'plugin'=>$p->name, 'type'=>'module', 'location'=>$p->path_type))?>"><?=$this->get_translation('desactivate')?></a>
<?php endif; ?>
  </td>
</tr>
  <?php $alt=abs($alt-1);?>
<?php endforeach; ?>
</table>
</div>
<div id="itemthemes" style="display:none;" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
<tr>
  <td class="eTableHeader">
    <?=$camyks->get_translation('name')?>
  </td>
  <td class="eTableHeader">
    <?=$this->get_translation('package')?>
  </td>
  <td class="eTableHeader" style="width:5%;">
    <?=$this->get_translation('version')?>
  </td>
  <td class="eTableHeader" style="width:10%;">
    <?=$this->get_translation('location')?>
  </td>
  <td class="eTableHeader" style="width:5%;">
    <?=$this->get_translation('state')?>
  </td>
  <td class="eTableHeader" style="width:10%;">
    <?=$this->get_translation('actions')?>
  </td>
</tr>
<?php $alt=0; ?>
<?php foreach ( $this->themes as $p ) : ?>
<tr>
  <td class="eTableLine<?=$alt;?> eContent1">
    <?= $p->title ?>
  </td>
  <td class="eTableLine<?=$alt;?> eContent1">
    <?= $p->plugin_package ?>
  </td>
  <td class="eTableLine<?=$alt;?> eContent1">
    <?= $p->version ?>
  </td>
  <td class="eTableLine<?=$alt;?> eContent1">
    <?= $camyks->get_translation($p->path_type) ?>
  </td>
  <td class="eTableLine<?=$alt;?> eContent1">
    <img src="<?=$p->active?$valid:$empty?>" alt="<?=$this->get_translation(($p->active==1?'active':'inactive'))?>"
title="<?=$this->get_translation(($p->active==1?'active':'inactive'))?>" border="0" />
  </td>
  <td class="eTableLine<?=$alt;?> eContent1">
<?php if ( $p->active == 0 and $this->check_right(1) ) : ?>
<a href="<?=$camyks->get_adminLink($this->name, array('mode'=>'activate', 'plugin'=>$p->name, 'type'=>'theme', 'location'=>$p->path_type))?>"><?=$this->get_translation('activate')?></a>
<?php elseif ( isset($camyks->neededThemes[$p->name]) ) : ?>
<span class="content2"><?=$this->get_translation('required');?></span>
<?php elseif ( $this->check_right(1) === false ) : ?>
&nbsp;
<?php else : ?>
<a href="<?=$camyks->get_adminLink($this->name, array('mode'=>'desactivate', 'plugin'=>$p->name, 'type'=>'theme', 'location'=>$p->path_type))?>"><?=$this->get_translation('desactivate')?></a>
<?php endif; ?>
  </td>
</tr>
  <?php $alt=abs($alt-1);?>
<?php endforeach; ?>
</table>
</div>

<div id="itemtemplates" style="display:none;" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;"
<tr>
  <td class="eTableHeader">
    <?=$camyks->get_translation('name')?>
  </td>
  <td class="eTableHeader">
    <?=$this->get_translation('package')?>
  </td>
  <td class="eTableHeader" style="width:5%;">
    <?=$this->get_translation('version')?>
  </td>
  <td class="eTableHeader" style="width:10%;">
    <?=$this->get_translation('location')?>
  </td>
  <td class="eTableHeader" style="width:5%;">
    <?=$this->get_translation('state')?>
  </td>
  <td class="eTableHeader" style="width:10%;">
    <?=$this->get_translation('actions')?>
  </td>
</tr>
<?php $alt=0; ?>
<?php foreach ( $this->templates as $p ) : ?>
<tr>
  <td class="eTableLine<?=$alt;?> eContent1">
    <?= $p->title ?>
  </td>
  <td class="eTableLine<?=$alt;?> eContent1">
    <?= $p->plugin_package ?>
  </td>
  <td class="eTableLine<?=$alt;?> eContent1">
    <?= $p->version ?>
  </td>
  <td class="eTableLine<?=$alt;?> eContent1">
    <?= $camyks->get_translation($p->path_type) ?>
  </td>
  <td class="eTableLine<?=$alt;?> eContent1">
    <img src="<?=$p->active?$valid:$empty?>" alt="<?=$this->get_translation(($p->active==1?'active':'inactive'))?>"
title="<?=$this->get_translation(($p->active==1?'active':'inactive'))?>" border="0" />
  </td>
  <td class="eTableLine<?=$alt;?> eContent1">
<?php if ( $p->active == 0 and $this->check_right(1) ) : ?>
<a href="<?=$camyks->get_adminLink($this->name, array('mode'=>'activate', 'plugin'=>$p->name, 'type'=>'template', 'location'=>$p->path_type))?>"><?=$this->get_translation('activate')?></a>
<?php elseif ( isset($camyks->neededTemplates[$p->name]) ) : ?>
<span class="content2"><?=$this->get_translation('required');?></span>
<?php elseif ( $this->check_right(1) === false ) : ?>
&nbsp;
<?php else : ?>
<a href="<?=$camyks->get_adminLink($this->name, array('mode'=>'desactivate', 'plugin'=>$p->name, 'type'=>'template', 'location'=>$p->path_type))?>"><?=$this->get_translation('desactivate')?></a>
<?php endif; ?>
  </td>
</tr>
  <?php $alt=abs($alt-1);?>
<?php endforeach; ?>
</table>
</div>

<div id="iteminputs" style="display:none;" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;"
<tr>
  <td class="eTableHeader">
    <?=$camyks->get_translation('name')?>
  </td>
  <td class="eTableHeader">
    <?=$this->get_translation('package')?>
  </td>
  <td class="eTableHeader" style="width:5%;">
    <?=$this->get_translation('version')?>
  </td>
  <td class="eTableHeader" style="width:10%;">
    <?=$this->get_translation('location')?>
  </td>
  <td class="eTableHeader" style="width:5%;">
    <?=$this->get_translation('state')?>
  </td>
  <td class="eTableHeader" style="width:10%;">
    <?=$this->get_translation('actions')?>
  </td>
</tr>
<?php $alt=0; ?>
<?php foreach ( $this->inputs as $p ) : ?>
<tr>
  <td class="eTableLine<?=$alt;?> eContent1">
    <?= $p->title ?>
  </td>
  <td class="eTableLine<?=$alt;?> eContent1">
    <?= $p->plugin_package ?>
  </td>
  <td class="eTableLine<?=$alt;?> eContent1">
    <?= $p->version ?>
  </td>
  <td class="eTableLine<?=$alt;?> eContent1">
    <?= $camyks->get_translation($p->path_type) ?>
  </td>
  <td class="eTableLine<?=$alt;?> eContent1">
    <img src="<?=$p->active?$valid:$empty?>" alt="<?=$this->get_translation(($p->active==1?'active':'inactive'))?>"
title="<?=$this->get_translation(($p->active==1?'active':'inactive'))?>" border="0" />
  </td>
  <td class="eTableLine<?=$alt;?> eContent1">
<?php if ( $p->active == 0 and $this->check_right(1) ) : ?>
<a href="<?=$camyks->get_adminLink($this->name, array('mode'=>'activate', 'plugin'=>$p->name, 'type'=>'input', 'location'=>$p->path_type))?>"><?=$this->get_translation('activate')?></a>
<?php elseif ( isset($camyks->neededTemplates[$p->name]) ) : ?>
<span class="content2"><?=$this->get_translation('required');?></span>
<?php elseif ( $this->check_right(1) === false ) : ?>
&nbsp;
<?php else : ?>
<a href="<?=$camyks->get_adminLink($this->name, array('mode'=>'desactivate', 'plugin'=>$p->name, 'type'=>'input', 'location'=>$p->path_type))?>"><?=$this->get_translation('desactivate')?></a>
<?php endif; ?>
  </td>
</tr>
  <?php $alt=abs($alt-1);?>
<?php endforeach; ?>
</table>
</div>

<?php if ( $this->help != null ) : ?>
<div id="itemhelp" style="display:none;" class="adminContentPanel">
<?php $this->display_help() ?>
</div>
<?php endif; ?>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar($this->buttons);?>
<?=$this->theme->get_boxFooter(); ?>
