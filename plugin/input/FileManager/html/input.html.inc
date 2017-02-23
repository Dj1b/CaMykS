<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Input Layout
 * Creation Date	: Jun 2007
 * Last Modif Date	: Jul 2008
 * 
 * FileManager input main layout
 */
global $camyks;
?>
<div>
  <?=$this->form->display_header();?>
  <?=$this->form->display_hiddens();?>
  <div class="actionBar">
    <?php foreach ( $this->viewButtons as $button) : ?>
      <?php if (!isset($button['url'])) : ?>
      <div class="actionButton">
        <?=$button['title'];?>
      </div>
      <?php else : ?>
      <a href="<?=$button['url'];?>" class="actionButton">
        <?=$button['title'];?>
      </a>
      <?php endif; ?>
    <?php endforeach; ?>
    <div class="actionSeparator">
      &nbsp;
    </div>
    <?php foreach ( $this->actionButtons as $button ) : ?>
      <a href="<?=$button['url'];?>" class="actionButton">
         <?=$button['title'];?>
       </a>
    <?php endforeach; ?>
  </div>
  
  <?php /*
  <?=$this->theme->get_barLeft()?>
  <div style="width:600px;">
    <table cellspacing="0" cellpadding="0">
      <tr>
	<?php foreach ( $this->viewButtons as $button) : ?>
	<td>
	  <?=$this->theme->get_barButton($button);?>
	</td>
	<?php endforeach; ?>
	<td style="width:50px;">
	  &nbsp;
	</td>
	<?php foreach ( $this->actionButtons as $button ) : ?>
	<td>
	  <?=$this->theme->get_barButton($button);?>
	</td>
	<?php endforeach; ?>
      </tr>
    </table>
  </div>
  <?=$this->theme->get_barRight()?>
  */ ?>
  
  <div style="height:4px;font-size:4px;">
    &nbsp;
  </div>
  
  <?php /* add folder popup */ ?>
  <div id="filemanager_folderpopup" class="adminPopupFrame" style="display:none;width:300px;position:absolute;z-index:10001">
    <?=$this->theme->get_boxHeader('width:300px;')?>
    <?=$this->theme->get_boxTitleBar( $this->get_translation('folderpopuptitle'))?>
    <?=$this->theme->get_boxContent1Header();?>
    <table cellspacing="0">
      <tr>
	<td class="title3">
	  <?=$this->get_translation('intofolder')?>
	</td>
	<td class="" id="filemanager_folderpopuptxt">
	</td>
      </tr>
      
      <tr>
	<td class="title3"><?=$camyks->get_translation('name')?> :</td>
	<td class="">
	  <input type="text" name="fm_foldername" value="" maxlength="32" style="width:200px" />
	</td>
      </tr>
    </table>
    
    <?=$this->theme->get_boxContent1Footer();?>
    <?=$this->theme->get_boxButtonsBar( $this->folderbuttons );?>
    <?=$this->theme->get_boxFooter();?>
  </div>
  
  <?php /* add file popup */ ?>
  <div id="filemanager_filepopup" class="adminPopupFrame" style="display:none;width:350px;position:absolute;zindex:10001">
    <?=$this->theme->get_boxHeader('width:350px')?>
    <?=$this->theme->get_boxTitleBar( $this->get_translation('filepopuptitle'))?>
    <?=$this->theme->get_boxContent1Header();?>
    <table cellspacing="0">
      <tr>
	<td class="title3">
	  <?=$this->get_translation('intofolder')?>
	</td>
	<td class="" id="filemanager_filepopuptxt">
	</td>
      </tr>
      <tr>
	<td class="title3" colspan="2">
	  <?=$this->get_translation('maxfilesize', file_getFileSize($this->browser_maxfilesize))?> 
	</td>
      </tr>
      <tr>
	<td class="title3">
	  <?=$this->get_translation('fileselection')?> :
	</td>
	<td class="">
	  <input type="file" name="fm_file[]" multiple />
	</td>
      </tr>
    </table>
    <?=$this->theme->get_boxContent1Footer();?>
    <?=$this->theme->get_boxButtonsBar( $this->filebuttons );?>
    <?=$this->theme->get_boxFooter();?>
  </div>
  
  <?php /* add file loading popup */ ?>
  <div id="filemanager_fileloadingpopup" class="adminPopupFrame" style="display:none;width:250px;position:absolute;zindex:10001">
    <?=$this->theme->get_boxHeader('width:250px')?>
    <?=$this->theme->get_boxTitleBar( $this->get_translation('fileloadingpopuptitle'))?>
    <?=$this->theme->get_boxContent2Header();?>
    <div style="margin:30px auto; width:32px;">
      <img src="<?=$this->get_fileURL('img/loading.gif')?>" alt="" border="0" /></img>
    </div>
    <?=$this->theme->get_boxContent2Footer();?>
    <?=$this->theme->get_boxFooter();?>
  </div>
  
  <?php /* trash file or folder action */ ?>
  <div id="filemanager_trashpopup" class="adminPopupFrame" style="display:none;width:350px;position:absolute;zindex:10001">
    <?=$this->theme->get_boxHeader('width:350px')?>
    <?=$this->theme->get_boxTitleBar( $this->get_translation('trashpopuptitle'))?>
    <?=$this->theme->get_boxContent1Header();?>
    <table cellspacing="0">
      <tr>
	<td class="title3">
	  <?=$this->get_translation('trashfile')?> : 
	</td>
      </tr>
      <tr>
	<td class="title3" id="filemanager_trashpopuptxt">
	</td>
      </tr>
    </table>
    <?=$this->theme->get_boxContent1Footer();?>
    <?=$this->theme->get_boxButtonsBar( $this->trashbuttons );?>
    <?=$this->theme->get_boxFooter();?>
  </div>
  
  <?php /* rename file or folder action */ ?>
  <div id="filemanager_renamepopup" class="adminPopupFrame" style="display:none;width:350px;position:absolute;zindex:10001">
    <?=$this->theme->get_boxHeader('width:350px')?>
    <?=$this->theme->get_boxTitleBar( $this->get_translation('renamepopuptitle'))?>
    <?=$this->theme->get_boxContent1Header();?>
    <table cellspacing="0">
      <tr>
	<td class="content1" colspan="2">
	  <?=$this->get_translation('renamefile')?> :
	</td>
      </tr>
      <tr>
	<td class="title3" colspan="2" id="filemanager_renamepopuptxt">
	</td>
      </tr>
      <tr>
	<td class="title3"><?=$camyks->get_translation('name')?> :
	</td>
	<td class="">
	  <input type="text" name="fm_newname" value="" maxlength="32" style="width:200px" />
	</td>
      </tr>
    </table>
    <?=$this->theme->get_boxContent1Footer();?>
    <?=$this->theme->get_boxButtonsBar( $this->renamebuttons );?>
    <?=$this->theme->get_boxFooter();?>
  </div>
  
  <?= $this->form->display_footer();?>
</div>
<div style="height:<?=$this->winSize?>">
  <?php $this->load_file('html/input_'.$this->browser_view.'.html.inc'); ?>
</div>