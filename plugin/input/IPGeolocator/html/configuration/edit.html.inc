<?php
/**
 * @brief IPGeolocator Input edit configuration layout
 * @details Plugin / Input layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Dec 2020
 * @date Modification: Dec 2020
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;

/* Load service list */
$services = $this->config->get_serviceList();
?>
<?= $camyks->theme->get_boxContent2Header(); ?>
<div class="adminContentPanel">
    <table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td colspan="3" class="eTableHeader">
                <?= $this->get_translation('formtitle_params'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2" style="width:120px;">
                <?= $this->get_translation('formitem_service'); ?>
            </td>
            <td class="eTableLine0 eContent1" coslpan="2">
                <?= $this->form->display_selectInput(array('name'=>'service', 'class'=>'linputs', 'values'=>$this->config->get_serviceTitleList())); ?>
            </td>
        </tr>

        <tr>
            <td colspan="3" class="eTableLine0">
                &nbsp;
            </td>
        </tr>

        <tr>
            <td colspan="3" class="eTableHeader">
                <?= $this->get_translation('formtitle_apikeysforservices'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $services['IPGeolocation']['Title']; ?>
                <?= $camyks->get_translation('formitem_separator'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->form->display_textInput(array('name'=>'APIKey_IPGeolocation', 'class'=>'linputs', 'maxlength'=>128)); ?>
            </td>
            <td class="eTableLine0 eContent1" style="width:140px;">
                <?php if ($services['IPGeolocation']['APIKeyURL'] != '') : ?>
                    <?= $camyks->theme->get_button(array(
                        'title'     => $this->get_translation('getakey'),
                        'url'       => $services['IPGeolocation']['APIKeyURL'],
                        'target'    => '_blank',
                    )); ?>
                <?php endif; ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $services['IPStack']['Title']; ?>
                <?= $camyks->get_translation('formitem_separator'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->form->display_textInput(array('name'=>'APIKey_IPStack', 'class'=>'linputs', 'maxlength'=>128)); ?>
                <?= $this->form->display_checkboxInput(array('name'=>'APIKey_IPStackPremium', 'value'=>1, 'label'=>$this->get_translation('ispremium'), 'labelClass'=>'eContent2')); ?>
            </td>
            <td class="eTableLine1 eContent1" style="width:140px;">
                <?php if ($services['IPStack']['APIKeyURL'] != '') : ?>
                    <?= $camyks->theme->get_button(array(
                        'title'     => $this->get_translation('getakey'),
                        'url'       => $services['IPStack']['APIKeyURL'],
                        'target'    => '_blank',
                    )); ?>
                <?php endif; ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $services['IPAPI']['Title']; ?>
                <?= $camyks->get_translation('formitem_separator'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->form->display_textInput(array('name'=>'APIKey_IPAPI', 'class'=>'linputs', 'maxlength'=>128)); ?>
                <?= $this->form->display_checkboxInput(array('name'=>'APIKey_IPAPIPremium', 'value'=>1, 'label'=>$this->get_translation('ispremium'), 'labelClass'=>'eContent2')); ?>
            </td>
            <td class="eTableLine0 eContent1" style="width:140px;">
                <?php if ($services['IPAPI']['APIKeyURL'] != '') : ?>
                    <?= $camyks->theme->get_button(array(
                        'title'     => $this->get_translation('getakey'),
                        'url'       => $services['IPAPI']['APIKeyURL'],
                        'target'    => '_blank',
                    )); ?>
                <?php endif; ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $services['IPData']['Title']; ?>
                <?= $camyks->get_translation('formitem_separator'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->form->display_textInput(array('name'=>'APIKey_IPData', 'class'=>'linputs', 'maxlength'=>128)); ?>
            </td>
            <td class="eTableLine1 eContent1" style="width:140px;">
                <?php if ($services['IPData']['APIKeyURL'] != '') : ?>
                    <?= $camyks->theme->get_button(array(
                        'title'     => $this->get_translation('getakey'),
                        'url'       => $services['IPData']['APIKeyURL'],
                        'target'    => '_blank',
                    )); ?>
                <?php endif; ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $services['Ipify']['Title']; ?>
                <?= $camyks->get_translation('formitem_separator'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->form->display_textInput(array('name'=>'APIKey_Ipify', 'class'=>'linputs', 'maxlength'=>128)); ?>
            </td>
            <td class="eTableLine0 eContent1" style="width:140px;">
                <?php if ($services['Ipify']['APIKeyURL'] != '') : ?>
                    <?= $camyks->theme->get_button(array(
                        'title'     => $this->get_translation('getakey'),
                        'url'       => $services['Ipify']['APIKeyURL'],
                        'target'    => '_blank',
                    )); ?>
                <?php endif; ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $services['IPWhois']['Title']; ?>
                <?= $camyks->get_translation('formitem_separator'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->form->display_textInput(array('name'=>'APIKey_IPWhois', 'class'=>'linputs', 'maxlength'=>128)); ?>
            </td>
            <td class="eTableLine1 eContent1" style="width:140px;">
                <?php if ($services['IPWhois']['APIKeyURL'] != '') : ?>
                    <?= $camyks->theme->get_button(array(
                        'title'     => $this->get_translation('getakey'),
                        'url'       => $services['IPWhois']['APIKeyURL'],
                        'target'    => '_blank',
                    )); ?>
                <?php endif; ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $services['IPRegistry']['Title']; ?>
                <?= $camyks->get_translation('formitem_separator'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->form->display_textInput(array('name'=>'APIKey_IPRegistry', 'class'=>'linputs', 'maxlength'=>128)); ?>
            </td>
            <td class="eTableLine0 eContent1" style="width:140px;">
                <?php if ($services['IPRegistry']['APIKeyURL'] != '') : ?>
                    <?= $camyks->theme->get_button(array(
                        'title'     => $this->get_translation('getakey'),
                        'url'       => $services['IPRegistry']['APIKeyURL'],
                        'target'    => '_blank',
                    )); ?>
                <?php endif; ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $services['IPInfoDB']['Title']; ?>
                <?= $camyks->get_translation('formitem_separator'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->form->display_textInput(array('name'=>'APIKey_IPInfoDB', 'class'=>'linputs', 'maxlength'=>128)); ?>
            </td>
            <td class="eTableLine1 eContent1" style="width:140px;">
                <?php if ($services['IPInfoDB']['APIKeyURL'] != '') : ?>
                    <?= $camyks->theme->get_button(array(
                        'title'     => $this->get_translation('getakey'),
                        'url'       => $services['IPInfoDB']['APIKeyURL'],
                        'target'    => '_blank',
                    )); ?>
                <?php endif; ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $services['DB_IP']['Title']; ?>
                <?= $camyks->get_translation('formitem_separator'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->form->display_textInput(array('name'=>'APIKey_DB_IP', 'class'=>'linputs', 'maxlength'=>128)); ?>
            </td>
            <td class="eTableLine0 eContent1" style="width:140px;">
                <?php if ($services['DB_IP']['APIKeyURL'] != '') : ?>
                    <?= $camyks->theme->get_button(array(
                        'title'     => $this->get_translation('getakey'),
                        'url'       => $services['DB_IP']['APIKeyURL'],
                        'target'    => '_blank',
                    )); ?>
                <?php endif; ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $services['IP2Location']['Title']; ?>
                <?= $camyks->get_translation('formitem_separator'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->form->display_textInput(array('name'=>'APIKey_IP2Location', 'class'=>'linputs', 'maxlength'=>128)); ?>
            </td>
            <td class="eTableLine1 eContent1" style="width:140px;">
                <?php if ($services['IP2Location']['APIKeyURL'] != '') : ?>
                    <?= $camyks->theme->get_button(array(
                        'title'     => $this->get_translation('getakey'),
                        'url'       => $services['IP2Location']['APIKeyURL'],
                        'target'    => '_blank',
                    )); ?>
                <?php endif; ?>
            </td>
        </tr>

    </table>
</div>
<?= $camyks->theme->get_boxContent2Footer(); ?>
<?php
/**
 * @endcond Exclude
 */
?>
