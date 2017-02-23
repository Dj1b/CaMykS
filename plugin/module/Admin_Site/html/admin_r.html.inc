<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Jan 2005
 * Last Modif Date	: Mar 2007
 *
 * Admin_Site Module Admin Layout : read only
 */
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:500px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar( $this->title );?>
<?=$this->theme->get_boxTabsBar($this->tabs,
				 $this->tabObject.'.mouseclick',
				 $this->tabObject.'.mouseover',
				 $this->tabObject.'.mouseout',
				'general');?>
<?=$this->theme->get_boxContent2Header();?>
<div id="itemgeneral" style="display:block;" class="adminContentPanel">
  <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
    <tr>
      <td class="eTableLine0 eContent2" style="width:150px;">
	<?=$this->get_translation('site_title')?>
      </td>
      <td class="eTableLine0 eContent1">
	<?=$this->conf['site_title']?>
      </td>
    </tr>
    <tr>
      <td class="eTableLine1 eContent2">
	<?=$this->get_translation('site_name')?>
      </td>
      <td class="eTableLine1 eContent1">
	<?=$this->conf['site_name']?>
      </td>
    </tr>
    
    <tr>
      <td class="eTableLine0 eContent2">
	<?=$this->get_translation('url')?>
      </td>
      <td class="eTableLine0 eContent1">
	<?=$this->conf['url']?>
      </td>
    </tr>    
    <tr>
      <td class="eTableLine1 eContent2">
	<?=$this->get_translation('version')?>
      </td>
      <td class="eTableLine1 eContent1">
	<?=$this->conf['version']?>
      </td>
    </tr>
    
    <tr>
      <td class="eTableLine0 eContent2">
	<?=$this->get_translation('friendly_urls')?>
      </td>
      <td class="eTableLine0 eContent1">
	<input type="checkbox" name="friendlyurls" value="1"<?=$this->conf['friendlyurls']==1?' checked="checked"': '' ?> disabled="disabled" /></input>
      </td>
    </tr>
    <tr>
      <td class="eTableLine1 eContent2">
	<?=$this->get_translation('author')?>
      </td>
      <td class="eTableLine1 eContent1">
	<?=$this->conf['site_author']?>
      </td>
    </tr>
    <tr>
      <td class="eTableLine0 eContent2">
	<?=$this->get_translation('company')?>
      </td>
      <td class="eTableLine0 eContent1">
	<?=$this->conf['site_company']?>
      </td>
    </tr>
  </table>
</div>
<div id="itemdb" style="display:none;" class="adminContentPanel">
  <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
    <tr>
      <td class="eTableLine0 eContent2" style="width:150px;">
	<?=$this->get_translation('database_host')?>
      </td>
      <td class="eTableLine0 eContent1">
	<?=$this->conf['database_host']?>
      </td>
    </tr>
    <tr>
      <td class="eTableLine1 eContent2">
	<?=$this->get_translation('database_name')?>
      </td>
      <td class="eTableLine1 eContent1">
	<?=$this->conf['database_name']?>
      </td>
    </tr>
    <tr>
      <td class="eTableLine0 eContent2">
	<?=$this->get_translation('database_size')?>
      </td>
      <td class="eTableLine0 eContent1">
	<?=$this->dbsize?>
      </td>
    </tr>
  </table>
</div> 
<div id="itemadminpart" style="display:none;" class="adminContentPanel">
  <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
    <tr>
      <td class="eTableLine0 eContent2" style="width:150px;">
	<?=$this->get_translation('admin_entry')?>
      </td>
      <td class="eTableLine0 eContent1">
	<?=$this->conf['admin_entry']?>
      </td>
    </tr>
	  
    <tr>
      <td class="eTableLine1 eContent2">
	<?=$this->get_translation('theme')?>
      </td>
      <td class="eTableLine1 eContent1">
	<?=$this->conf['admin_default_theme']?>
      </td>
    </tr>
    <tr>
      <td class="eTableLine0 eContent2" colspan="2">
	<?=$this->get_translation('admin_languages');?>
      </td>
    </tr>
    <tr>
      <td class="eTableLine0 eContent1" colspan="2">
	<table cellspacing="0" cellpadding="2" border="0" width="100%">
	  <?php $myCol = 0; ?>
	  <?php foreach ( $camyks->get_availableLanguages() as $l => $v ) : ?>
	  <?php if ( $myCol == 0 ) : ?>
	  <tr>
	    <?php endif; ?>
	    <td style="width:20px;">
	      <input type="checkbox" name="lang_<?=$l?>" value="1" <?=( in_array($l, $this->conf['admin_languages'])? 'checked="checked"':'')?> disabled="disabled" />
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
	  <td colspan="<?=(3-$myCol)*3?>">
	    &nbsp;
	  </td>
		</tr>
		<?php endif; ?>
	      </table>
	    </td>
	  </tr>
	  
	  <tr>
	    <td class="eTableLine1 eContent2" colspan="2">
	      <?=$this->get_translation('editing_languages');?>
	    </td>
	  </tr>
	  <tr>
	    <td class="eTableLine1 eContent1" colspan="2">
	      <table cellspacing="0" cellpadding="2" border="0" width="100%">
		<?php $myCol = 0; ?>
		<?php foreach ( $camyks->get_availableLanguages() as $l => $v ) : ?>
		<?php if ( $myCol == 0 ) : ?>
		<tr>
		  <?php endif; ?>
		  <td style="width:20px;">
		    <input type="checkbox" name="lang_<?=$l?>" value="1" <?=( in_array($l, $this->conf['editing_languages'])? 'checked="checked"':'')?> disabled="disabled"/>
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
		<td colspan="<?=(3-$myCol)*3?>">&nbsp;</td>
		</tr>
		<?php endif; ?>
	      </table>
	    </td>
	  </tr>
	</table>
      </div>
      
      <div id="itemviewpart" style="display:none;" class="adminContentPanel">
	<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
	  
	  <tr>
	    <td class="eTableHeader" colspan="2">
		<?=$this->get_translation('visit_content');?>
	      </td>
	  </tr>
	  
	  <tr>
	    <td class="eTableLine0 eContent2" style="width:150px;">
	      <?=$this->get_translation('theme')?>
	    </td>
	    <td class="eTableLine0 eContent1">
	      <?=$this->conf['site_default_theme']?>
	    </td>
	  </tr>
	  <tr>
	    <td class="eTableLine1 eContent2">
	      <?=$this->get_translation('template')?>
	    </td>
	    <td class="eTableLine1 eContent1">
	      <?=$this->conf['site_default_template']?>
	    </td>
	  </tr>
	  <tr>
	    <td class="eTableLine0 eContent2">
		<?=$this->get_translation('pagemaxmodules')?>
	    </td>
	    <td class="eTableLine0 eContent1">
	      <?=$this->conf['page_maxmodules']?>
	    </td>
	  </tr>
	  <tr>
	    <td class="eTableLine1 eContent2" colspan="2">
	      <?=$this->get_translation('languages')?> 
	    </td>
	  </tr>
	  <tr>
	    <td class="eTableLine1 eContent1" colspan="2">
	      <table cellspacing="0" cellpadding="2" border="0" width="100%">
		<?php $myCol = 0; ?>
		<?php foreach ( $camyks->get_availableLanguages() as $l => $v ) : ?>
		<?php if ( $myCol == 0 ) : ?>
		<tr>
		  <?php endif; ?>
		  <td style="width:20px;">
		    <input type="checkbox" name="lang_<?=$l?>" value="1" <?=( in_array($l, $this->conf['site_languages'])? 'checked':'')?> disabled="disabled"/>
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
		<td colspan="<?=(3-$myCol)*3?>">&nbsp;</td>
		</tr>
		<?php endif; ?>
	      </table>
	    </td>
	  </tr>
	  
	  <tr>
	    <td class="eTableHeader" colspan="2">
	      <?=$this->get_translation('visit_stats')?>  
	    </td>
	  </tr>
	  <tr>
 	    <td class="eTableLine0 eContent2">
	      <?=$this->get_translation('google_analytics_code')?>
	    </td>
	    <td class="eTableLine0 eContent1">
	      <?=$this->conf['google_analytics'] == '' ? $this->get_translation('stats_none') : $this->conf['google_analytics']?>
	    </td>
	  </tr>
	</table>
      </div>
      <?=$this->theme->get_boxContent2Footer();?>
      <?=$this->theme->get_boxButtonsBar( $this->buttons );?>
      <?=$this->theme->get_boxFooter();?>