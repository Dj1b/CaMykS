<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version       : 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Dec 2007
 * Last Modif Date	: Dec 2007
 *
 * Content_SystemSiteReport Module Site Layout : site layout
 */
global $camyks;
?>
<?php if ( $this->rfitem->title_mode > 0 ) : ?>
<div class="title1">
  <?=$this->theme->get_boxTitleBar( $this->rfitem->get_siteTitle());?>
</div>
<?php endif; ?>
<?=$this->form->display_header() ?>
<?=$this->form->display_hiddens() ?>
<div>
  <?php $this->rfitem->get_HTMLContent(); ?>
</div>
<div>
  <table cellspacing="0" style="width:100%">
    <?php if ( count( $this->rfitem->type_list ) > 1 ) : ?>
    <tr>
      <td class="content2">
	<?= $this->get_translation('requesttype' ) ?> :
      </td>
      <td>
	<select name="type">
	  <?php foreach ( $this->rtypelist as $t ) : ?>
	  <option value="<?=$t->id?>"><?=$t->vars['title']?></option>
	  <?php endforeach; ?>
	</select>
      </td>
    </tr>
    <?php elseif ( count( $this->rfitem->type_list ) == 1 ) : ?>
    <tr>
      <td colspan="2" class="title3">
	<?php foreach ( $this->rtypelist as $t ) : ?>
	<input type="hidden" name="type" value="<?=$t->id?>" />
	<?=$t->vars['title']?>
	<?php endforeach; ?>
      </td>
    </tr>
    <?php endif; ?>
    <tr>
      <td class="content2">
	<?=$this->get_translation('requesttitle'); ?> :
      </td>
      <td style="text-align:right;">
	<input type="text" name="title" value="" maxlength="64" class="inputs" />
      </td>
    </tr>
    
    <tr>
      <td colspan="2">
	<?php $this->input->display();?>
      </td>
    </tr>
    
    <tr>
      <td class="content2">
	<?= $this->get_translation('requestanswer') ?> :
      </td>
      <td style="text-align:right;">
	<input type="text" name="answer_target" value="" maxlength="255" class="inputs" />
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
</div>
<?=$this->form->display_footer() ?>
<div style="margin:8px" align="center">
<?=$this->theme->get_button( $this->get_translation('send'),
			     $this->form->get_HTMLSubmitLink()); ?>
</div>