<?php
/**
 * @brief CookieAgreementMessage Input configuration edit layout
 * @details Plugin / Input layout
 * @file plugin/input/CookieAgreementMessage/html/configuration/edit.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Feb 2018
 * @date Modification: Apr 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;

$flags = array();
$lgs = $camyks->get_confValue('editing_languages');
if ( count($lgs) == 1) {
    $flags[$lgs[0]] = '';
} else {
    foreach ($lgs as $l)
        $flags[$l] = '<img src="'.language_getIcon($l, false).'" alt="" style="float:right" />';
}
?>
<?=$camyks->theme->get_boxContent2Header();?>
<div class="adminContentPanel">
<table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
    <tr>
        <td class="eTableLine0 eContent2" style="width:160px;">
            <?=$this->get_translation('formitem_insertion');?>
        </td>
        <td class="eTableLine0 eContent1">
            <?=$this->form->display_selectInput(array('name'=>'insertion', 'values'=>$this->config->get_insertionList())); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine1 eContent2">
            <?=$this->get_translation('formitem_stylesource');?>
        </td>
        <td class="eTableLine1 eContent1">
            <?=$this->form->display_selectInput(array('name'=>'styleSource', 'values'=>$this->config->get_styleSourceList())); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0 eContent2">
            <?=$this->get_translation('formitem_aboutcookielink');?>
        </td>
        <td class="eTableLine0 eContent1">
            <?=$this->form->display_radioInput(array('name'=>'aboutCookie', 'value'=>'', 'label'=>$this->get_translation('config_nolink'), 'onchange'=>'CookieAgreementMessageConfig.onAboutCookieChange(\'\');')); ?>
            <?=$this->form->display_radioInput(array('name'=>'aboutCookie', 'value'=>'true', 'label'=>$this->get_translation('config_automaticlink'), 'onchange'=>'CookieAgreementMessageConfig.onAboutCookieChange(\'\');')); ?>
            <?=$this->form->display_radioInput(array('name'=>'aboutCookie', 'value'=>'pers', 'default'=>(($this->config->vars['aboutCookie'] != '' and $this->config->vars['aboutCookie'] != 'true') ? 'pers' : ''), 'label'=>$this->get_translation('config_customlink'), 'onchange'=>'CookieAgreementMessageConfig.onAboutCookieChange(\'pers\');')); ?>
            
            <?php $params = array('name'=>'aboutCookie', 'maxlength'=>255, 'id'=>'aboutCookiePersValue'); ?>                
            <?php if ($this->config->vars['aboutCookie'] == '') : ?>
                <?php $params['default'] = ''; ?>
                <?php $params['disabled'] = 'disabled'; ?>
            <?php else : ?>
                <?php $params['default'] = $this->config->vars['aboutCookie']; ?>
            <?php endif; ?>            
            <?=$this->form->display_textInput($params); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine1 eContent2">
            <?=$this->get_translation('formitem_remindttl');?>
        </td>
        <td class="eTableLine1 eContent1">
            <?=$this->form->display_textInput(array('name'=>'remindTTL', 'class'=>'sinputs'));?>&nbsp;&nbsp;<?=$this->get_translation('formdesc_remindttl');?>
        </td>
    </tr>
    
    <tr>
        <td class="eTableLine0 eContent2">
            <?=$this->get_translation('formitem_popuplocation');?>
        </td>
        <td class="eTableLine0 eContent1">
            <?=$this->form->display_selectInput(array('name'=>'location', 'values'=>$this->config->get_locationList())); ?>
        </td>
    </tr>
    
    <?php $isFirst = true; ?>
    <?php foreach ($lgs as $l) : ?>
    
    <tr>
        <td class="eTableLine1 eContent2">
            <?=$flags[$l]; ?>
            <?php if ($isFirst) : ?>
                <?=$this->get_translation('formitem_message');?>
                <?php $isFirst = false; ?>
            <?php endif; ?>
        </td>
        <td class="eTableLine1 eContent1">
            <?=$this->form->display_textAreaInput(array('name'=>'message_'.$l, 'default'=>isset($this->config->vars['message'][$l])?$this->config->vars['message'][$l]:''));?>
        </td>
    </tr>
    <?php endforeach; ?>
</table>
</div>
<?=$camyks->theme->get_boxContent2Footer();?>
<?php
/**
 * @endcond Exclude
 */
?>