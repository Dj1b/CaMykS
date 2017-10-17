<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0
 * Object Version	: 1.0
 * Object Type	    : Plugin / Module Layout
 * Creation Date	: Fev 2007
 * Last Modif Date	: Oct 2017
 * 
 * Admin_PluginManager Module Admin Layout
*/
global $camyks;
$valid = $this->theme->get_pictURL('valid', 12, 'std');
$empty = $this->theme->get_pictURL('empty', 12, 'std');
$minus = $this->theme->get_pictURL('minus', 12, 'std');
$plus = $this->theme->get_pictURL('plus', 12, 'std');
$action = $this->theme->get_pictURL('action', 12, 'std');
?>
<?=$this->theme->get_boxHeader(array('class'=>'adminEditorModule'));?>
<?=$this->theme->get_boxTitleBar($this->title)?>
<?=$this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams);?>
<?=$camyks->theme->get_boxContent2Header(); ?>
<div id="itemModules" style="display:<?=$this->tabBuilder->get_tabDisplay('Modules')?>;" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" style="width:100%;">
<tr>
  <td class="eTableHeader eTableIconCell">
    &nbsp;
  </td>
  <td class="eTableHeader eTableIconCell">
    &nbsp;
  </td>
  <td class="eTableHeader">
    <?=$this->get_translation('type')?>
  </td>
  <td class="eTableHeader">
    <?=$camyks->get_translation('name')?>
  </td>
  <td class="eTableHeader">
    <?=$this->get_translation('package')?>
  </td>
  <td class="eTableHeader" style="width:20px;">
    <?=$this->get_translation('version')?>
  </td>
  <td class="eTableHeader" style="width:60px;">
    <?=$this->get_translation('location')?>
  </td>
  <?php if ( $this->check_right(1)) : ?>
  <td class="eTableHeader eTableIconCell">
    &nbsp;
  </td>
  <?php endif; ?>
</tr>
<?php $alt=0; ?>
<?php foreach ( $this->modules as $p ) : ?>
<tr>
  <td class="eTableLine<?=$alt;?> eTableIconCell">
    <img src="<?=$p->active?$valid:$empty?>" alt="<?=$this->get_translation(($p->active==1?'active':'inactive'))?>" title="<?=$this->get_translation(($p->active==1?'active':'inactive'))?>" />
  </td>  
  <td class="eTableLine<?=$alt;?> eTableIconCell">
    <?php $installed = $p->is_installed(); ?>
<?php if ($installed === true ) : ?>
<img src="<?=$valid?>" alt="<?=$this->get_translation('installed')?>" title="<?=$this->get_translation('installed')?>" />
<?php elseif ($installed === false ) : ?>
<img src="<?=$empty?>" alt="<?=$this->get_translation('notinstalled')?>" title="<?=$this->get_translation('notinstalled')?>" />
<?php else : ?>
<img src="<?=$minus?>" alt="<?=$this->get_translation('noinstallationrequired')?>" title="<?=$this->get_translation('noinstallationrequired')?>" />
<?php endif; ?>
  </td>
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
  <?php if ( $this->check_right(1)) : ?>
  <td class="eTableLine<?=$alt;?> eTableIconCell">
    <?php if (($p->active == 0 or $p->is_installed() === false)) : ?>
      <a href="<?=$camyks->get_adminLink($this->name, array('mode'=>'activate', 'plugin'=>$p->name, 'type'=>'module', 'location'=>$p->path_type))?>" class="img">
        <img src="<?=$plus;?>" alt="<?=$this->get_translation('activate')?>"  />
      </a>
    <?php elseif ( isset($camyks->neededModules[$p->name]) ) : ?>
      --
    <?php else : ?>
      <a href="<?=$camyks->get_adminLink($this->name, array('mode'=>'desactivate', 'plugin'=>$p->name, 'type'=>'module', 'location'=>$p->path_type))?>" class="img">
        <img src="<?=$minus;?>" alt="<?=$this->get_translation('desactivate')?>" />
      </a>
    <?php endif; ?>
  </td>
  <?php endif; ?>
  </tr>
  <?php $alt=abs($alt-1);?>
<?php endforeach; ?>
</table>
</div>


<div id="itemThemes"  style="display:<?=$this->tabBuilder->get_tabDisplay('Themes')?>;" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" style="width:100%;">
<tr>
  <td class="eTableHeader eTableIconCell">
    &nbsp;
  </td>
  <td class="eTableHeader">
    <?=$camyks->get_translation('name')?>
  </td>
  <td class="eTableHeader">
    <?=$this->get_translation('package')?>
  </td>
  <td class="eTableHeader" style="width:20px;">
    <?=$this->get_translation('version')?>
  </td>
  <td class="eTableHeader" style="width:60px;">
    <?=$this->get_translation('location')?>
  </td>
  <?php if ( $this->check_right(1)) : ?>
  <td class="eTableHeader eTableIconCell">
    &nbsp;
  </td>
  <td class="eTableHeader eTableIconCell">
    &nbsp;
  </td>
  <?php endif; ?>
</tr>
<?php $alt=0; ?>
<?php foreach ( $this->themes as $p ) : ?>
<tr>
  <td class="eTableLine<?=$alt;?> eTableIconCell">
    <img src="<?=$p->active?$valid:$empty?>" alt="<?=$this->get_translation(($p->active==1?'active':'inactive'))?>" title="<?=$this->get_translation(($p->active==1?'active':'inactive'))?>" />
  </td>
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
  <?php if ( $this->check_right(1)) : ?>
  <td class="eTableLine<?=$alt;?> eTableIconCell">
    <?php if ($p->active == 0) : ?>
        <a href="<?=$camyks->get_adminLink($this->name, array('mode'=>'activate', 'plugin'=>$p->name, 'type'=>'theme', 'location'=>$p->path_type))?>" class="img">
            <img src="<?=$plus;?>" alt="<?=$this->get_translation('activate')?>" />
        </a>
    <?php elseif ( isset($camyks->neededThemes[$p->name]) ) : ?>
        --
    <?php else : ?>
        <a href="<?=$camyks->get_adminLink($this->name, array('mode'=>'desactivate', 'plugin'=>$p->name, 'type'=>'theme', 'location'=>$p->path_type))?>" class="img">
            <img src="<?=$minus;?>" alt="<?=$this->get_translation('desactivate')?>" />
        </a>
    <?php endif; ?>
    </td>
    <td class="eTableLine<?=$alt;?> eTableIconCell">
      <?php if ($p->active == 1) : ?>
        <a href="javascript:pl.show_menu('theme', '<?=$p->name;?>');" class="img">
          <img src="<?=$action;?>" id="button<?=$p->name;?>" alt="" />
        </a>
      <?php endif; ?>
    </td>
    <?php endif; ?>
  </tr>
  <?php $alt=abs($alt-1);?>
<?php endforeach; ?>
</table>
</div>


<div id="itemTemplates" style="display:<?=$this->tabBuilder->get_tabDisplay('Templates')?>;" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" style="width:100%;"
<tr>
  <td class="eTableHeader eTableIconCell">
    &nbsp;
  </td>
  <td class="eTableHeader">
    <?=$camyks->get_translation('name')?>
  </td>
  <td class="eTableHeader">
    <?=$this->get_translation('package')?>
  </td>
  <td class="eTableHeader" style="width:20px;">
    <?=$this->get_translation('version')?>
  </td>
  <td class="eTableHeader" style="width:60px;">
    <?=$this->get_translation('location')?>
  </td>
  <?php if ( $this->check_right(1)) : ?>
  <td class="eTableHeader eTableIconCell">
    &nbsp;
  </td>
  <td class="eTableHeader eTableIconCell">
    &nbsp;
  </td>
  <?php endif; ?>
</tr>
<?php $alt=0; ?>
<?php foreach ( $this->templates as $p ) : ?>
<tr>
  <td class="eTableLine<?=$alt;?> eTableIconCell">
    <img src="<?=$p->active?$valid:$empty?>" alt="<?=$this->get_translation(($p->active==1?'active':'inactive'))?>" title="<?=$this->get_translation(($p->active==1?'active':'inactive'))?>" />
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
  <?php if ( $this->check_right(1)) : ?>
  <td class="eTableLine<?=$alt;?> eTableIconCell">
    <?php if ( $p->active == 0 and $this->check_right(1) ) : ?> 
      <a href="<?=$camyks->get_adminLink($this->name, array('mode'=>'activate', 'plugin'=>$p->name, 'type'=>'template', 'location'=>$p->path_type))?>" class="img">
        <img src="<?=$plus;?>" alt="<?=$this->get_translation('activate')?>" />
      </a>
    <?php elseif ( isset($camyks->neededTemplates[$p->name]) ) : ?>
      --
    <?php else : ?>
      <a href="<?=$camyks->get_adminLink($this->name, array('mode'=>'desactivate', 'plugin'=>$p->name, 'type'=>'template', 'location'=>$p->path_type))?>" class="img">
        <img src="<?=$minus;?>" alt="<?=$this->get_translation('desactivate')?>" />
      </a>
    <?php endif; ?>
  </td>
  <td class="eTableLine<?=$alt;?> eTableIconCell">
      <?php if ($p->active == 1) : ?>
        <a href="javascript:pl.show_menu('template', '<?=$p->name;?>');" class="img">
          <img src="<?=$action;?>" id="button<?=$p->name;?>" alt="" />
        </a>
      <?php endif; ?>
    </td>
  <?php endif; ?>
</tr>
  <?php $alt=abs($alt-1);?>
<?php endforeach; ?>
</table>
</div>

<div id="itemInputs" style="display:<?=$this->tabBuilder->get_tabDisplay('Inputs')?>;" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" style="width:100%;"
<tr>
  <td class="eTableHeader eTableIconCell">
    &nbsp;
  </td>
  <td class="eTableHeader">
    <?=$camyks->get_translation('name')?>
  </td>
  <td class="eTableHeader">
    <?=$this->get_translation('package')?>
  </td>
  <td class="eTableHeader" style="width:20px;">
    <?=$this->get_translation('version')?>
  </td>
  <td class="eTableHeader" style="width:60px;">
    <?=$this->get_translation('location')?>
  </td>
  <?php if ( $this->check_right(1)) : ?>
  <td class="eTableHeader eTableIconCell">
    &nbsp;
  </td>
  <?php endif; ?>
</tr>
<?php $alt=0; ?>
<?php foreach ( $this->inputs as $p ) : ?>
<tr>
  <td class="eTableLine<?=$alt;?> eTableIconCell">
    <img src="<?=$p->active?$valid:$empty?>" alt="<?=$this->get_translation(($p->active==1?'active':'inactive'))?>" title="<?=$this->get_translation(($p->active==1?'active':'inactive'))?>" />
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
  <?php if ( $this->check_right(1)) : ?>
  <td class="eTableLine<?=$alt;?> eTableIconCell">
    <?php if ( $this->check_right(1) === false ) : ?>
        &nbsp;
    <?php elseif ( $p->active == 0 and $this->check_right(1) ) : ?>
        <a href="<?=$camyks->get_adminLink($this->name, array('mode'=>'activate', 'plugin'=>$p->name, 'type'=>'input', 'location'=>$p->path_type))?>" class="img">
            <img src="<?=$plus;?>" alt="<?=$this->get_translation('activate')?>" />
        </a>
    <?php elseif ( isset($camyks->neededTemplates[$p->name]) ) : ?>
        --
    <?php else : ?>
      <a href="<?=$camyks->get_adminLink($this->name, array('mode'=>'desactivate', 'plugin'=>$p->name, 'type'=>'input', 'location'=>$p->path_type))?>" class="img">
        <img src="<?=$minus;?>" alt="<?=$this->get_translation('desactivate')?>" />
      </a>
    <?php endif; ?>
  </td>
  <?php endif; ?>
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

<?php if (count($this->themeActionMenu) > 0) : ?>
  <?=$this->theme->get_layeredMenu ('themeActionMenu', 'globalCMenu', $this->themeActionMenu );?>
<?php endif; ?>

<?php if (count($this->templateActionMenu) > 0) : ?>
  <?=$this->theme->get_layeredMenu ('templateActionMenu', 'globalCMenu', $this->templateActionMenu );?>
<?php endif; ?>
