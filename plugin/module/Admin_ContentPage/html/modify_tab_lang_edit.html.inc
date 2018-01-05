<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0
 * Object Version	: 1.0
 * Object Type      : Plugin / Module Layout
 * Creation Date	: Nov 2006
 * Last Modif Date  : Jan 2018
 *
 * Admin_ContentPage Module Layout : Page editor languages tabs
 */
 global $camyks;
?>
<?php foreach ($camyks->get_confValue('editing_languages') as $l) : ?>
<div id="item<?=$l?>" style="display:<?=$this->tabBuilder->get_tabDisplay($l)?>;" class="adminContentPanel">
  <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
    <tr>
        <td class="eTableLine0 eContent2" style="width:150px">
	  <?=$this->get_translation('formitem_pagetitle')?>
	</td>
      <td class="eTableLine0 eContent1">
         <?=$this->form->display_textInput(array('name'=>'title', 'language'=>$l, 'default'=>$this->page->locales[$l]['title'], 'maxlength'=>255));?>
      </td>
    </tr>
    <tr>
      <td class="eTableLine1 eContent2">
        <?=$this->get_translation('formitem_pageshorttitle')?>
      </td>
      <td class="eTableLine1 eContent1">
        <?=$this->form->display_textInput(array('name'=>'shorttitle', 'language'=>$l, 'default'=>$this->page->locales[$l]['shorttitle'], 'maxlength'=>255));?>
      </td>
    </tr>
    <tr>
      <td class="eTableLine0 eContent2">
	    <?=$camyks->get_translation('formitem_description')?>
	  </td>
      <td class="eTableLine0 eContent1">
        <?=$this->form->display_textAreaInput(array('name'=>'description', 'language'=>$l, 'default'=>$this->page->locales[$l]['description']));?>
      </td>
    </tr>
    <tr>
      <td class="eTableLine1 eContent2">
	    <?=$this->get_translation('formitem_keywords')?>
      </td>
      <td class="eTableLine1 eContent1">
        <?=$this->form->display_textAreaInput(array('name'=>'keywords', 'language'=>$l, 'default'=>$this->page->locales[$l]['keywords']));?>
      </td>
   </tr>
  </table>
</div>
<?php endforeach; ?>
  