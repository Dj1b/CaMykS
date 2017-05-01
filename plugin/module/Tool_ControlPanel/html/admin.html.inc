<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0b
 * Object Version	: 1.0
 * Object Type	    : Plugin / Module Layout
 * Creation Date	: Oct 2005
 * Last Modif Date	: Feb 2016
 *
 * Admin_ControlPanel Module Admin Layout
*/
global $camyks;
$default = $camyks->site_data_url.'/img/module/default_icon32.gif';
?>
<div style="width:600px;" class="adminControlPanel">
  <?php foreach ( $this->admin_modules as $g => $group ) : ?>
  <?php  if ( count ( $group ) ) : ?>
  <div class="eTitle2 adminControlPanelTitle">
    <?=$this->get_translation('g'.$g)?>
  </div>
  <div>
  <table cellspacing="0" style="width:100%" class="adminControlPanelGroup">
  <?php $col = 0; ?>
  <?php foreach ( $group as $mod ) : ?>
  <?php $mod_lk = $camyks->get_adminLink($mod); ?>
  <?php if ( $col == 0 ) : ?>
  <tr>
  <?php endif; ?>
    <td class="adminControlPanelItem" style="width:<?=ceil(100/$this->cols)?>%;">
      <div style="float:left;padding:4px;">
        <a href="<?=$mod_lk?>">
          <img src="<?=$camyks->modules[$mod]->get_fileURL('img/icon32.gif', null, $default)?>" width="32" height="32" alt="<?=$this->get_translation('icon',$camyks->modules[$mod]->title);?>" border="0" style="float:left;"/>
        </a>
      </div>
      <div class="pluginTitle">
        <a class="eTitle3" href="<?=$mod_lk?>">
          <?=$camyks->modules[$mod]->title; ?>
        </a>
      </div>
      <div class="pluginDesc">
        <div class="eTitle4">
          <?=$camyks->get_translation('mod_'.$mod.'_desc')?>
        </div>
      </div>
    </td>
    <?php if ( ++$col == $this->cols ) : ?>
      <?php $col = 0; ?>
      </tr>
    <?php endif; ?>
  <?php endforeach; ?>
  <?php if  ( $col != 0 ) : ?>
    <?php for ( $i=$col; $i < $this->cols; $i++ ) : ?>
      <td class="adminControlPanelItem"></td>
    <?php endfor; ?>
    </tr>
  <?php endif; ?>
  </table>
  </div>
  <?php endif; ?>
  <?php endforeach; ?>
</div>