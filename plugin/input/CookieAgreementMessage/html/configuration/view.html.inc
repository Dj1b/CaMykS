<?php
/**
 * @brief CookieAgreementMessage Input configuration view layout
 * @details Plugin / Input layout
 * @file plugin/input/CookieAgreementMessage/html/configuration/view.html.inc
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
if (count($lgs) == 1) {
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
            <?=$this->config->get_insertionTitle(); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine1 eContent2">
            <?=$this->get_translation('formitem_stylesource');?>
        </td>
        <td class="eTableLine1 eContent1">
            <?=$this->config->get_styleSourceTitle(); ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0 eContent2">
            <?=$this->get_translation('formitem_aboutcookielink');?>
        </td>
        <td class="eTableLine0 eContent1">
            <?php if ($this->config->vars['aboutCookie'] == '') : ?>
                <span class="eContent3"><?=$this->get_translation('config_nolink'); ?></span>
            <?php elseif ($this->config->vars['aboutCookie'] == true or $this->config->vars['aboutCookie'] == 'true'): ?>
                <a href="<?=$this->get_translation('aboutcookieurl');?>" class="eLink1" target="_blank" rel="noopener">
                        <?=$this->get_translation('config_automaticlink'); ?>
                </a>
            <?php else : ?>
                <a href="<?=$this->config->vars['aboutCookie'];?>" class="eLink1" target="_blank" rel="noopener">
                    <?=$this->config->vars['aboutCookie'];?>
                </a>
            <?php endif; ?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine1 eContent2">
            <?=$this->get_translation('formitem_remindttl');?>
        </td>
        <td class="eTableLine1 eContent1">
                <?=$this->config->vars['remindTTL'];?> <?=$this->get_translation('formdesc_remindttl');?>
        </td>
    </tr>
    
    <tr>
        <td class="eTableLine0 eContent2">
            <?=$this->get_translation('formitem_popuplocation');?>
        </td>
        <td class="eTableLine0 eContent1">
            <?=$this->config->get_locationTitle(); ?>
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
            <?php if (isset($this->config->vars['message'][$l]) and $this->config->vars['message'][$l] != '') : ?>
                <?=$this->config->vars['message'][$l]; ?>
            <?php else : ?>
                <span class="eContent3"><?=$this->get_translation('config_automaticmessage'); ?></span>
            <?php endif; ?>
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