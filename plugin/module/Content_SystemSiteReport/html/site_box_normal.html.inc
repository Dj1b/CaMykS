<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version       : 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Apr 2007
 * Last Modif Date	: Apr 2007
 *
 * Content_SystemSiteReport Module Site Layout : normal box layout
 */
global $camyks;
?>
<?=$this->theme->get_boxHeader('width:100%;');?>
<?php if ( $this->rfitem->title_mode > 0 ) : ?>
<?=$this->theme->get_boxTitleBar( $this->rfitem->get_siteTitle());?>
<?php endif; ?>
<?=$this->theme->get_boxContent2Header();?>
<?=$this->form->display_header() ?>
<?=$this->form->display_hiddens() ?>
<table cellspacing="0" cellpadding="4" border="0" style="width:100%;">
  <tr>
    <td colspan="2">
      <?php $this->rfitem->get_HTMLContent(); ?>
    </td>
  </tr>
  <?php if ( count( $this->rfitem->type_list ) > 1 ) : ?>
  <tr>
    <td class="eTitle3">
      <?= $this->get_translation('requesttype' ) ?>
    </td>
    <td class="eContent1">
      <select name="type">
	<?php foreach ( $this->rtypelist as $t ) : ?>
	<option value="<?=$t->id?>"><?=$t->vars['title']?></option>
	<?php endforeach; ?>
      </select>
    </td>
  </tr>
  <?php elseif ( count( $this->rfitem->type_list ) == 1 ) : ?>
  <tr>
    <td colspan="2" class="eTitle3">
      <?php foreach ( $this->rtypelist as $t ) : ?>
      <input type="hidden" name="type" value="<?=$t->id?>" /></input>
      <?=$t->vars['title']?>
      <?php endforeach; ?>
    </td>
  </tr>
  <?php endif; ?>
  <tr>
    <td class="eTitle3">
      <?=$this->get_translation('requesttitle'); ?>
    </td>
    <td class="eContent1">
      <input type="text" name="title" value="" maxlength="64" class="inputs" />
    </td>
  </tr>
  
  <tr>
    <td colspan="2">
      <?php $this->input->display();?>
    </td>
  </tr>

  <?php if ( $this->rfitem->file_allowed and $this->file_allowed ) : ?>
  <tr>
    <td class="eTitle3">
      <?= $this->get_translation('requestattachedfile', $this->file_maxsize) ?>
    </td>
    <td class="eContent1">
      <input type="file" name="attached_file" />
    </td>
  </tr>  
  <?php endif; ?>
  <tr>
    <td class="eTitle3">
      <?= $this->get_translation('requestanswer') ?>
    </td>
    <td class="eContent1">
      <input type="text" name="answer_target" value="" maxlength="255" class="inputs" />
    </td>
  </tr>
</table>
<?=$this->form->display_footer() ?>
<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxButtonsBar( array( array('title'=>$this->get_translation('send'),
'link'=> $this->form->get_HTMLSubmitLink())), false); ?>
<?=$this->theme->get_boxFooter(); ?>
