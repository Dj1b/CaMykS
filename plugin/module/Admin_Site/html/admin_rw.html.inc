<?php
/*
 * Camyks Engine
 * Company		: skymac.org
 * Author		: sky
 * Camyks Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Jan 2005
 * Last Modif Date	: Mar 2007
 *
 * Admin_Site Module Admin Layout : read/write
*/
global $camyks;

/* button list for buttons bar */
$buttons = array(array('title'=>$camyks->get_translation('back'),
		      'link'=>$camyks->get_adminLink()),
		array('title'=>$camyks->get_translation('valid'),
		      'link'=>'javascript:document.'.$this->form->name.'.submit();'));

/* tab list for tabs bar */
$tabs = array(array('name' => 'general',
		    'title' => $this->get_translation('general')),
	      array('name' => 'db',
		    'title' => $this->get_translation('database')),
	      array('name' => 'viewpart',
		    'title' => $this->get_translation('viewpart')),
	      array('name' => 'adminpart',
		    'title' => $this->get_translation('adminpart')));

$jsObject = 'admin_site_tabObject';

?>
<?=$camyks->theme->get_boxHeader('width:500px;margin:0 auto;');?>
<?=$camyks->theme->get_boxTitleBar( $this->title );?>
<?=$camyks->theme->get_boxTabsBar( $tabs,
				   $jsObject.'.mouseclick',
				   $jsObject.'.mouseover',
				   $jsObject.'.mouseout',
				   'general');?>
<?=$camyks->theme->get_boxContent2Header();?>
<?=$this->form->display_header();?>
<?=$this->form->display_hiddens();?>

<div id="itemgeneral" style="display:block;" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">

<tr><td class="listline1" style="width:150px;">
<?=$this->get_translation('site_title')?> : </td>
<td class="listline1">
<input type="text" name="site_title" value="<?=$this->conf['site_title']?>" maxlength="64" class="inputs"/>
</td></tr>

<tr><td class="listline0">
<?=$this->get_translation('site_name')?> : </td>
<td class="listline0"><?=$this->conf['site_name']?></td></tr>

<tr><td class="listline1">
<?=$this->get_translation('url')?> : </td>
<td class="listline1">
<input type="text" name="url" value="<?=$this->conf['url']?>" maxlength="128" class="inputs"/>
</td></tr>

<tr><td class="listline0">
<?=$this->get_translation('version')?> : </td>
<td class="listline0">
<input type="text" name="version" value="<?=$this->conf['version']?>" maxlength="16" class="inputs"/>
</td></tr>

<tr><td class="listline1">
<?=$this->get_translation('friendly_urls')?> : </td>
<td class="listline1">
<input type="checkbox" name="friendlyurls" value="1"<?=$this->conf['friendlyurls']==1?' checked="checked"': '' ?>/>
</td></tr>


<tr><td class="listline0">
<?=$this->get_translation('author')?> : </td>
<td class="listline0">
<input type="text" name="site_author" value="<?=$this->conf['site_author']?>" maxlength="16" class="inputs"/>
</td></tr>

<tr><td class="listline1">
<?=$this->get_translation('company')?> : </td>
<td class="listline1">
<input type="text" name="site_company" value="<?=$this->conf['site_company']?>" maxlength="16" class="inputs"/>
</td></tr>

</table>
</div>


<div id="itemdb" style="display:none;" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">

<tr><td class="listline1" style="width:150px;">
<?=$this->get_translation('database_host')?> : </td>
<td class="listline1"><?=$this->conf['database_host']?></td></tr>

<tr><td class="listline0">
<?=$this->get_translation('database_name')?> : </td>
<td class="listline0"><?=$this->conf['database_name']?></td></tr>
</table>
</div>

<div id="itemadminpart" style="display:none;" class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">

<tr><td class="listline1" style="width:150px;">
<?=$this->get_translation('admin_entry')?> : </td>
<td class="listline1">
<input type="text" name="admin_entry" value="<?=$this->conf['admin_entry']?>" maxlength="16" class="inputs"/>
</td></tr>

<tr><td class="listline0">
<?=$this->get_translation('theme')?> : </td>
<td class="listline0">
<select name="admin_default_theme">
<?php
foreach ( $camyks->themes as $theme ) {
  echo '<option value="'.$theme->name.'"'.($theme->name==$this->conf['admin_default_theme'] ? ' selected':'').'>';
  echo $theme->name.'</option>';
}
?>
</select>
</td></tr>

<tr>
<td class="listline1" colspan="2">
<?=$this->get_translation('admin_languages');?>
</td>
</tr>
<tr>
  <td class="listline1" colspan="2">
    <table cellspacing="0" cellpadding="2" border="0" width="100%">
<?php $myCol = 0; ?>
<?php foreach ( $camyks->get_availableLanguages() as $l => $v ) : ?>
<?php if ( $myCol == 0 ) : ?>
<tr>
<?php endif; ?>
<td style="width:20px;">
<input type="checkbox" name="lang_<?=$l?>" value="1" <?=( in_array($l, $this->conf['admin_languages'])? 'checked="checked"':'')?>/>
</td>
<td style="width:20px;">
<?=language_getIcon ( $l ) ?>
</td>
<td style="">
<?=$camyks->get_translation('lang_'.$l);?>
</td>
<?php if ( ++$myCol == 3 ) : ?>
<?php $myCol = 0; ?>
</tr>
<?php endif; ?>
<?php endforeach; ?>
<?php if ( $myCol != 0 ) : ?>
<td colspan="<?=(3-$myCol)*3?>">&nbsp;</td></tr>
<?php endif; ?>
    </table>
  </td>
</tr>

<tr><td class="listline0" colspan="2">
    <?=$this->get_translation('editing_languages');?>
</td></tr>
<tr>
  <td class="listline0" colspan="2">
    <table cellspacing="0" cellpadding="2" border="0" width="100%">
<?php $myCol = 0; ?>
<?php foreach ( $camyks->get_availableLanguages() as $l => $v ) : ?>
<?php if ( $myCol == 0 ) : ?>
<tr>
<?php endif; ?>
<td style="width:20px;">
<input type="checkbox" name="lang_<?=$l?>" value="1" <?=( in_array($l, $this->conf['editing_languages'])? 'checked="checked"':'')?>/>
</td>
<td style="width:20px;">
<?=language_getIcon ( $l ) ?>
</td>
<td style="">
<?=$camyks->get_translation('lang_'.$l);?>
</td>
<?php if ( ++$myCol == 3 ) : ?>
<?php $myCol = 0; ?>
</tr>
<?php endif; ?>
<?php endforeach; ?>
<?php if ( $myCol != 0 ) : ?>
<td colspan="<?=(3-$myCol)*3?>">&nbsp;</td></tr>
<?php endif; ?>
    </table>
  </td>
</tr>

</table>
</div>

<div id="itemviewpart" style="display:none;" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
    
<tr><td class="listline1" style="width:150px;">
    <?=$this->get_translation('theme')?> : </td>
    <td class="listline1">
    <select name="site_default_theme">
<?php
foreach ( $camyks->themes as $theme ) {
  echo '<option value="'.$theme->name.'"'.($theme->name==$this->conf['site_default_theme'] ? ' selected':'').'>';
  echo $theme->name.'</option>';
}
?>
</select>
</td></tr>
<tr><td class="listline0">
<?=$this->get_translation('template')?> :</td>
<td class="listline0">
<select name="site_default_template">
<?php foreach ( $camyks->templates as $t ) : ?>
<option value="<?=$t->name?>"<?=($t->name==$this->conf['site_default_template']?' selected' : '')?>><?=$t->name?></option>
<?php endforeach; ?>
</select>
</td></tr>
<tr>
  <td class="listline1" colspan="2">
    <?=$this->get_translation('languages')?> : 
  </td>
</tr>
<tr>
  <td class="listline1" colspan="2">
    <table cellspacing="0" cellpadding="2" border="0" width="100%">
<?php $myCol = 0; ?>
<?php foreach ( $camyks->get_availableLanguages() as $l => $v ) : ?>
<?php if ( $myCol == 0 ) : ?>
<tr>
<?php endif; ?>
<td style="width:20px;">
<input type="checkbox" name="lang_<?=$l?>" value="1" <?=( in_array($l, $this->conf['site_languages'])? 'checked':'')?>>
</td>
<td style="width:20px;">
<?=language_getIcon ( $l ) ?>
</td>
<td style="">
<?=$camyks->get_translation('lang_'.$l);?>
</td>
<?php if ( ++$myCol == 3 ) : ?>
<?php $myCol = 0; ?>
</tr>
<?php endif; ?>
<?php endforeach; ?>
<?php if ( $myCol != 0 ) : ?>
<td colspan="<?=(3-$myCol)*3?>">&nbsp;</td></tr>
<?php endif; ?>
    </table>
  </td>
</tr>
</table>
</div>
<?=$this->form->display_footer() ?>
<?=$camyks->theme->get_boxContent2Footer();?>
<?=$camyks->theme->get_boxButtonsBar( $buttons );?>
<?=$camyks->theme->get_boxFooter();?>
