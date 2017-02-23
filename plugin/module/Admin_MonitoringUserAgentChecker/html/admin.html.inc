<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author			: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0b
 * Object Version	: 1.0
 * Object Type	    : Plugin / Module Layout
 * Creation Date   	: Dec 2014
 * Last Modif Date	: Dec 2014
 * History :
 * * 12-19-14 : Initial files
 *
 * Admin_MonitoringUserAgentChecker Module Admin Layout : main
 */
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:800px;margin:0 auto;');?>
<?=$this->theme->get_boxTitleBar($this->title) ?>
<?=$this->theme->get_boxTabsBar($this->tabBuilder->tabs,
				$this->tabBuilder->jsParams);?>
<?=$this->theme->get_boxContent2Header( )?>
<div id="itemrecords" style="display:<?=$this->tabBuilder->get_tabDisplay('records')?>;" class="adminContentPanel">

<?=$this->listRecord->display('head');?>
<?=$this->listRecord->display('list');?>

</div>

<div id="admin_genericuseragentmanager_addpopup" class="adminPopupFrame" style="display:none;width:500px;position:absolute;z-index:10001">
  <?=$this->addform->display_header();?>
  <?=$this->addform->display_hiddens();?>
  <?=$camyks->theme->get_boxHeader()?>
  <?=$camyks->theme->get_boxTitleBar($this->get_translation('addpopuptitle'))?>
  <?=$camyks->theme->get_boxContent1Header()?>
  <div class="eContent2">
    <?=$this->get_translation('addpopupname')?>
  </div>
  <div class="eContent1">
	<?=$this->addform->display_textAreaInput(array('name'=>'user_agent', 'class'=>'vlinputs')); ?>
    </div>
  <?=$camyks->theme->get_boxContent1Footer()?>
  <?=$camyks->theme->get_boxButtonsBar($this->popupbuttons)?>
  <?=$camyks->theme->get_boxFooter()?>
  <?=$this->addform->display_footer();?>
</div>

<div id="admin_genericuseragentmanager_viewpopup" class="adminPopupFrame" style="display:none;width:300px;position:absolute;z-index:10001">

</div>

<div> 
<script>
	var data = [];
    <?php 
	foreach($this->listRecord->objectList as $key=>$object){
		echo 'data[' . $key . '] = ' . json_encode($object->vars) .';';
	}
	?>
    console.log(data);
</script>    
</div>

<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( $this->buttons ); ?>
<?=$this->theme->get_boxFooter(); ?>