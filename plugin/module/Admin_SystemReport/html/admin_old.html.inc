<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Engine
 * Create Date		: May 2007
 * Last Modif Date	: May 2008
 *
 * Admin_SystemReport Module Layout
 */
global $camyks;

$plus = $this->theme->get_pictURL('plus', 12, 'std' );
$plus_ = $this->theme->get_pictURL('plus', 12, 'ovr' );

$minus = $this->theme->get_pictURL('minus', 12, 'std' );
$minus_ = $this->theme->get_pictURL('minus', 12, 'ovr' );

$view = $this->theme->get_pictURL('view', 12, 'std');
$view_ = $this->theme->get_pictURL('view', 12, 'ovr');

$cross = $this->theme->get_pictURL('cross', 12, 'std');
$cross_ = $this->theme->get_pictURL('cross', 12, 'ovr');

$valid = $this->theme->get_pictURL('valid', 12, 'std');
$empty = $this->theme->get_pictURL('empty', 12, 'std');

?>
<?=$this->theme->get_boxHeader('width:700px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title );?>
<?=$this->theme->get_boxContent1Header('height:40px;');?>
<?=$this->searchForm->display_header();?>
<?=$this->searchForm->display_hiddens();?>
<table cellspacing="0" cellpadding="0" border="0" style="width:100%">
  <tr>
    <td class="eContent2">
      <?=$this->get_translation('searchtype'); ?>
    </td>
    <td class="eContent1">
      <select name="searchType" class="inputs" onchange="document.<?=$this->searchForm->name?>.submit();void(0);">
	<option value=""><?=$this->get_translation('searchtype_all')?></option>
	<?php foreach( $this->types as $type ) : ?>
	<option value="<?=$type?>"<?=$type==$this->searchType?' selected="selected"':''?>>
	  <?=$type?>
	</option>
	<?php endforeach; ?>
      </select>
    </td>
    <td class="eContent2">
      <?=$this->get_translation('searchview'); ?>
    </td>
    <td>
      <select name="searchView" class="inputs" onchange="document.<?=$this->searchForm->name?>.submit();void(0);">
	<option value="-1"><?=$this->get_translation('searchview_all')?></option>
	<option value="0"<?=$this->searchView==0?' selected="selected"':''?>>
	  <?=$this->get_translation('searchview_unread');?>
	</option>
	<option value="1"<?=$this->searchView==1?' selected="selected"':''?>>
	  <?=$this->get_translation('searchview_read');?>
	</option>
      </select>
    </td>
  </tr>
  <tr>
    <td class="eContent2">
      <?=$this->get_translation('searchpage');?>
    </td>
    <td class="eContent1">
      <div class="inputs" style="text-align:center;">
	<a href="javascript:document.<?=$this->searchForm->name?>.searchPage.value--;document.<?=$this->searchForm->name?>.submit();void(0);" style="float:left">
	  <img src="<?=$minus?>" alt="" border="0" onmouseover="this.src='<?=$minus_?>';" onmouseout="this.src='<?=$minus?>';" style="margin-top:6px;" />
	</a>
	<a href="javascript:document.<?=$this->searchForm->name?>.searchPage.value++;document.<?=$this->searchForm->name?>.submit();void(0);" style="float:right">
	  <img src="<?=$plus?>" alt="" border="0" onmouseover="this.src='<?=$plus_?>';" onmouseout="this.src='<?=$plus?>';" style="margin-top:6px;" />
	</a>
	<input type="text" name="searchPage" value="<?=$this->searchPage+1?>" size="4" style="text-align:right" onchange="document.<?=$this->searchForm->name?>.submit()" />
	/ <?=$this->searchPages ?>
      </div>
    </td>
  </tr>
</table>
<?=$this->searchForm->display_footer();?>

<?=$this->theme->get_boxContent1Footer();?>
<?=$this->theme->get_boxContent2Header();?>

<?=$this->itemform->display_header();?>
<?=$this->itemform->display_hiddens();?>
<div class="adminContentPanel">
<table cellspacing="0" cellpadding="0" border="0" width="100%">
  <tr>
    <td class="eTableHeader" style="width:16px; padding:2px;" >
       <input type="checkbox" name="check_all" value="1" onchange="update_allCheckboxes();" />
    </td>
    <td class="eTableHeader" style="width:16px;">
      <img src="<?=$camyks->theme->get_pictURL( 'valid', '12', 'std' )?>" alt="" border="0" />
    </td>
    <td class="eTableHeader" style="width:20px;">
      <?=$this->get_translation('number')?>
    </td>
    <td class="eTableHeader" style="width:120px;">
      <?=$this->get_translation('date')?>
    </td>
    <td class="eTableHeader" style="width:100px;">
      <?=$this->get_translation('type')?>
    </td>
    <td class="eTableHeader">
      <?=$this->get_translation('object')?>
      </td>
    <td class="eTableHeader" style="width:12px;">
      &nbsp;
    </td>
    <td class="eTableHeader" style="width:12px;">
      &nbsp;
    </td>
  </tr>
  <?php $alt = 0; ?>
  <?php $cnt = 0; ?>
  <?php foreach ( $this->reportList as $item ) : ?>
  <?php if ( $item->vars['status'] == 0 ) : ?>
  <?php $pict = $empty; ?>
  <?php $class = 'eContent2';?>
  <?php else : ?>
  <?php $pict = $valid; ?>
  <?php $class = 'eContent1';?>
  <?php endif;?>
  <tr>
    <td class="eTableLine<?=$alt;?> <?=$class?>" style="padding:2px;">
      <input type="checkbox" name="object<?=$cnt?>" value="<?=$item->id?>" onchange="update_singleCheckbox();" />
    </td>
    <td class="eTableLine<?=$alt;?> <?=$class?>">
      <img src="<?=$pict?>" alt="" border="0" />
    </td>
    <td class="eTableLine<?=$alt;?> <?=$class?>">
      <?=$item->id?>
    </td>
    <td class="eTableLine<?=$alt;?> <?=$class?>">
      <?=strftime( '%x %X', $item->vars['_date'] )?>
    </td>
    <td class="eTableLine<?=$alt;?> <?=$class?>">
      <?=$item->vars['type']?>
    </td>
    <td class="eTableLine<?=$alt;?> <?=$class?>">
      <?=$item->vars['objectname']?>
    </td>
    
    <td class="eTableLine<?=$alt;?>">
      <a href="<?=$this->readReportLink.$item->id?>">
	<img src="<?=$view?>" border="0"
	  alt="<?=$this->get_translation('viewlog')?>"
          title="<?=$this->get_translation('viewlog')?>"
	  onmouseover="this.src='<?=$view_?>';"
	  onmouseout="this.src='<?=$view?>';" />
      </a>
    </td>
    
    <td class="eTableLine<?=$alt;?>">
      <?php if ( $this->check_right(1)===true ) : ?>
      <a href="javascript:admin_systemreport_deletelog(<?=$item->id?>)">
	<img src="<?=$cross?>" border="0"
	  alt="<?=$this->get_translation('deletetlog')?>"
	  title="<?=$this->get_translation('deletelog')?>"
          onmouseover="this.src='<?=$cross_?>';"
	  onmouseout="this.src='<?=$cross?>';" />
      </a>
      <?php else : ?>
      &nbsp;
      <?php endif; ?>
    </td>
  </tr>
<?php $alt = abs( $alt-1); ?>
<?php $cnt++; ?>
<?php endforeach; ?>
</table>
</div>
<?=$this->itemform->display_footer()?>
<?=$this->theme->get_boxContent2Footer();?>
<?=$this->theme->get_boxButtonsBar( $this->buttons );?>
<?=$this->theme->get_boxFooter();?>