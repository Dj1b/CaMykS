<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Layout
 * Creation Date    : Sep 2010
 * Last Modif Date  : Mar 2018
 * 
 * Admin_GenericGuestBookManager Module Admin Layout : view config
*/
global $camyks;
?>
<?php if (isset($this->isConfig) and $this->isConfig) : ?>

<?=$camyks->theme->get_boxContent2Header();?>
<div class="adminContentPanel">

<?php endif; ?>

<table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
    <tr>
        <td class="eTableHeader" colspan="2">
            <?=$this->get_translation('formtitle_messages');?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0 eContent2" style="width:150px;">
            <?=$this->get_translation('formitem_validation')?>
        </td>
        <td class="eTableLine0 eContent1">
            <?=$this->config->get_messageValidationValue();?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0" colspan="2">
            &nbsp;
        </td>
    </tr>

    <tr>
        <td class="eTableHeader" colspan="2">
            <?=$this->get_translation('formtitle_notifications');?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0 eContent2">
            <?=$camyks->get_translation('formitem_status')?>
        </td>
        <td class="eTableLine0 eContent1">
            <?=$this->config->get_notificationStatusValue();?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine1 eContent2">
            <?=$this->get_translation('formitem_sender')?>
        </td>
        <td class="eTableLine1 eContent1">
            <?=$this->config->vars['notification_sender'];?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0 eContent2">
            <?=$this->get_translation('formitem_recipients')?>
        </td>
        <td class="eTableLine0 eContent1">
            <?=$this->config->get_notificationRecipientsValue();?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0" colspan="2">
            &nbsp;
        </td>
    </tr>

    <tr>
        <td class="eTableHeader" colspan="2">
            <?=$this->get_translation('formtitle_statistics');?>
        </td>
    </tr>

    <tr>
        <td class="eTableLine0 eContent2">
            <?=$camyks->get_translation('formitem_status')?>
        </td>
        <td class="eTableLine0 eContent1">
            <?=$this->config->get_statisticStatusValue();?>
        </td>
    </tr>
</table>

<?php if (isset($this->isConfig) and $this->isConfig) :?>

</div>
<?=$camyks->theme->get_boxContent2Footer();?>

<?php endif; ?>
