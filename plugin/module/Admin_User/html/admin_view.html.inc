<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0.1
 * Object Type      : Plugin / Module Layout
 * Creation Date    : Jun 2005
 * Last Modif Date  : Jun 2018
 * 
 * Admin_User Module Admin Layout : view user
*/
global $camyks;
?>
<?=$this->theme->get_boxHeader(array('class'=>'adminEditorModule', 'style'=>'width:800px;margin:0 auto;'));?>
<?=$this->theme->get_boxTitleBar($this->get_translation('user').$camyks->get_translation('formitem_separator').$this->user->login );?>
<?=$this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams);?>
<?=$this->theme->get_boxContent2Header()?>
<div id="itemProperties"  style="display:<?=$this->tabBuilder->get_tabDisplay('Properties')?>;" class="adminContentPanel">
  <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
    <tr>
      <td class="eTableLine0 eContent2" style="width:150px;">
	    <?=$camyks->get_translation('formitem_login')?>
      </td>
      <td class="eTableLine0 eContent1">
	    <?=$this->user->login?>
      </td>
    </tr>
    <tr>
      <td class="eTableLine1 eContent2">
	    <?=$camyks->get_translation('formitem_status')?>
      </td>
      <td class="eTableLine1 eContent1">
	    <?=$camyks->get_translation(($this->user->active == 1?'':'in').'active');?>
      </td>
    </tr>
    <tr>
      <td class="eTableLine0 eContent2">
	    <?=$camyks->get_translation('formitem_firstname')?>
      </td>
      <td class="eTableLine0 eContent1">
	    <?=$this->user->firstname?>
      </td>
    </tr>
    <tr>
      <td class="eTableLine1 eContent2">
	    <?=$camyks->get_translation('formitem_lastname')?>
      </td>
      <td class="eTableLine1 eContent1">
	    <?=$this->user->lastname?>
      </td>
    </tr>
    <tr>
      <td class="eTableLine0 eContent2">
	    <?=$camyks->get_translation('formitem_email')?>
      </td>
      <td class="eTableLine0 eContent1">
        <a href="mailto:<?=$this->user->email?>" class="eLink1">
	      <?=$this->user->email?>
	    </a>
      </td>
    </tr>
    <tr>
      <td class="eTableLine1 eContent2" style="vertical-align:top;">
	    <?=$camyks->get_translation('formitem_address')?>
      </td>
      <td class="eTableLine1 eContent1">
	    <?=nl2br($this->user->address)?>
      </td>
    </tr>
  </table>
</div>

<div id="itemRights" style="display:<?=$this->tabBuilder->get_tabDisplay('Rights')?>;" class="adminContentPanel">
  <table cellspacing="0" cellpadding="0" border="0" style="wdith:100%;">
    <?php $alt=0; ?>
    <?php foreach ( $camyks->modules as $m ) : ?>
    <?php if ( $m->type == 'admin' ) : ?>
    <?php $m->get_rights() ?>
    <tr>
      <td class="eTableLine<?=$alt?> eContent2" style="width:175px;">
	<?= $m->title; ?>
      </td>
      
      <?php $rightcount = 0; ?>
      <?php $linecount = 0; ?>
      <?php foreach ( $m->rights as $ridx => $right ) : ?>
        <td class="eTableLine<?=$alt?> eTableIconCell">
	      <input type="checkbox" name="<?=$right['name']?>" value="0" disabled="disabled" <?= $this->user->get_right($m->name, $ridx) ? ' checked="checked"':''; ?> />
        </td>
	    <td class="eTableLine<?=$alt?> eContent1" style="width:<?=$this->layout_cellwidth?>;">
	      <?= $right['title']; ?>
	    </td>
	  <?php $rightcount++; ?>
	    <?php if ( ++$linecount == $this->layout_itemsByLine ) : ?>
	  </tr>
	  <?php $linecount = 0; ?>
	    <?php if($rightcount < count($m->rights)) : ?>
	    <tr>
	    <td class="eTableLine0">
	    &nbsp;
            </td>
	    <?php endif;?>
	  <?php endif; ?>
	  <?php endforeach; ?>
	  
	  <?php if ( $linecount != 0 ) : ?>
	  <?php for ( $i= $linecount; $i<$this->layout_itemsByLine; $i++ ) : ?>
	  <td class="eTableLine<?=$alt?>" colspan="2">
	    &nbsp;
	  </td>
	  <?php endfor; ?>
  </tr>
  <?php endif; ?>
<?php $alt = abs ( $alt-1 );?>
<?php endif; ?>
<?php endforeach; ?>
</table>
</div>
<?=$this->theme->get_boxContent2Footer();?>
<?=$this->theme->get_boxButtonsBar( $this->buttons );?>
<?=$this->theme->get_boxFooter( );?>
