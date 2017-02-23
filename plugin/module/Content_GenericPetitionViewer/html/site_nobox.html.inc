<?php
/*
 * CaMyks Engine
 * Developed by	    : camyks.net
 * Author	    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type	    : Plugin / Module Layout
 * Creation Date    : May 2010
 * Last Modif Date  : May 2010
 * 
 * Content_GenericPetitionViewer Module Site Layout : site nobox layout
 */
global $camyks;
?>

<?=$this->petitionItem->vars['description'];?>

<p class="eContent1">
<?=$this->get_translation('xsignsposted', $this->petitionItem->vars['signs']);?>
</p>

<?php if ($this->saveMode == 'success') : ?>

<p class="eContent2" style="text-align:center;">
<?=$this->get_translation('thxmessage');?>
</p>

<?php elseif ($this->petitionItem->vars['status'] == 1 ) : ?>

<p class="eContent1" style="text-align:center;">
<?=$this->theme->get_button(array('url'=>'javascript:popup_openModal(\'signpopup\');', 'title'=>$this->get_translation('signnow')));?>
</p>

<?php else : ?>

<p class="eContent1">
<?=$this->get_translation('petitionclosed'); ?>
</p>

<?php endif; ?>

<p class="eContent1">
<?=$this->get_translation('theyhavealreadysigned'); ?>
</p>

<?php $alt = 1; ?>
<table cellspacing="0" cellpadding="0" border="0" style="width:80%; margin:0 auto;">
<?php foreach ($this->signList as $sign) : ?>
<tr>
  <td class="eTableLine<?=$alt?>">
<?=$sign->vars['lastname'].' '.$sign->vars['firstname'];?>
  </td>
  <td class="eTableLine<?=$alt?>">
  <?=$sign->vars['city']?>(<?=$sign->vars['zipcode'];?>)
  </td>
</tr>
<?php $alt = abs($alt-1); ?>
<?php endforeach; ?>
</table>

<?=$this->pageController->display();?>

<div id="signpopup" style="width:400px; background:white; display:none; padding:8px 16px;">
<?=$this->signform->display_header();?>
<?=$this->signform->display_hiddens();?>
<div class="eTitle1">
<?=$this->get_translation('signpopup_title');?>
</div>

<div class="error">
<?=$this->saveError;?>
</div>

<table cellspacing="0" cellpadding="0" border="0" style="width:400px;">
<tr>
  <td class="eTableLine0 eContent2" style="width:150px;">
  
  </td>
  <td class="eTableLine0 eContent1">
    <?php /*
    <?=$this->signform->display_civilitySelectInput('title');?>
	  */ ?>
  </td>
</tr>
<tr>
  <td class="eTableLine0 eContent2">
  <?=$camyks->get_translation('formitem_firstname');?>
  </td>
  <td class="eTableLine0 eContent1">
    <?=$this->signform->display_textInput('firstname');?>
  </td>
</tr>
<tr>
  <td class="eTableLine0 eContent2">
    <?=$camyks->get_translation('formitem_lastname');?>
  </td>
  <td class="eTableLine0 eContent1">
    <?=$this->signform->display_textInput('lastname');?>
  </td>
</tr>
<tr>
  <td class="eTableLine0 eContent2">
    <?=$camyks->get_translation('formitem_email');?>
  </td>
  <td class="eTableLine0 eContent1">
    <?=$this->signform->display_textInput('email');?>
  </td>
</tr>
<tr>
  <td class="eTableLine0 eContent2">
  <?=$this->get_translation('formitem_birthdate');?>
  </td>
  <td class="eTableLine0 eContent1">
    <?=$this->signform->display_dateInput(array('name'=>'birthdate', 'objects'=>array('day', 'month', 'year'), 'buttons'=>array()));?>
  </td>
</tr>
<tr>
  <td class="eTableLine0 eContent2">
  <?=$camyks->get_translation('formitem_address');?>
  </td>
  <td class="eTableLine0 eContent1">
    <?=$this->signform->display_textInput('address');?>
  </td>
</tr>
<tr>
  <td class="eTableLine0 eContent2">
  <?=$camyks->get_translation('formitem_city');?>
  </td>
  <td class="eTableLine0 eContent1">
    <?=$this->signform->display_textInput('city');?>
  </td>
</tr>
<tr>
  <td class="eTableLine0 eContent2">
  <?=$camyks->get_translation('formitem_zipcode');?>
  </td>
  <td class="eTableLine0 eContent1">
    <?=$this->signform->display_textInput('zipcode');?>
  </td>
</tr>
<tr>
  <td class="eTableLine0 eContent2">
  <?=$camyks->get_translation('formitem_country');?>
  </td>
  <td class="eTableLine0 eContent1">
    <?=$this->signform->display_countrySelectInput('country');?>
  </td>
</tr>
<tr>
  <td class="eTableLine0 eContent1" colspan="2">
  <input type="checkbox" id="confirm" name="confirm" value="1" /><label for="confirm"><?=$this->get_translation('signpopup_confirm');?></label>
  </td>
</tr>
<tr>
  <td class="eTableLine0 eContent3" colspan="2">
  <?=$this->get_translation('signpopup_desc');?>
  </td>
</tr>
<tr>
  <td class="eTableLine0 eContent2" colspan="2">
<?=$this->theme->get_button(array('url'=>$this->signform->get_HTMLSubmitLink(), 'title'=>$this->get_translation('signpopup_valid')));?>
  &nbsp; &nbsp; &nbsp;
<?=$this->theme->get_button(array('url'=>'javascript:popup_closeModal(\'signpopup\');', 'title'=>$camyks->get_translation('close')));?>
  </td>
</tr>
</table>
<?=$this->signform->display_footer();?>
</div>