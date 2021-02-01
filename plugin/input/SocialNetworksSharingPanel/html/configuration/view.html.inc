<?php
/**
 * @brief SocialNetworksSharingPanel Input configuration view layout
 * @details Plugin / Input layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2
 * @date Creation: Jan 2018
 * @date Modification: Jan 2021
 * @copyright 2018 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;
?>
<?= $camyks->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams); ?>
<?= $camyks->theme->get_boxContent2Header(); ?>
<div id="itemShare" style="display:<?= $this->tabBuilder->get_tabDisplay('Share')?>;"    class="adminContentPanel">
    <table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('formdesc_settings'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_pictureformat'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->config->get_pictureFormatValue('share'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2" colspan="2">
                &nbsp;
            </td>
        </tr>

        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('formtitle_networks'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2" colspan="2">
                <?= $this->get_translation('formdesc_share'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2" style="width:160px;">
                &nbsp;
            </td>
            <td class="eTableLine0 eContent1">
                &nbsp;
            </td>
        </tr>

        <?php $alt = 0; ?>
        <?php foreach ($this->networks as $network => $data) : ?>
            <?php if ($data['share'] == 1) : ?>
                <tr>
                    <td class="eTableLine<?= $alt; ?> eContent2">
                        <?= $data['title'].$camyks->get_translation('formitem_separator'); ?>
                    </td>
                    <td class="eTableLine<?= $alt; ?> eContent1">
                        <?= $this->config->get_sharingNetworkValue($network); ?>
                    </td>
                </tr>
                <?php $alt = abs($alt-1); ?>
            <?php endif; ?>
        <?php endforeach; ?>

        <tr>
            <td class="eTableLine0 eContent2" colspan="2">
                &nbsp;
            </td>
        </tr>

        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('formtitle_like'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine<?= $alt; ?> eContent2">
                <?= $this->networks['facebook']['title'].$camyks->get_translation('formitem_separator'); ?>
            </td>
            <td class="eTableLine<?= $alt; ?> eContent1">
                <?= $this->config->get_networkLikeValue('facebook'); ?> (<?= $this->config->vars['like_facebookLayout'].' / '.$this->config->vars['like_facebookSize'].' / '.$this->config->vars['like_facebookAction'];?>)
            </td>
        </tr>
    </table>
</div>

<div id="itemFollow" style="display:<?= $this->tabBuilder->get_tabDisplay('Follow')?>;"    class="adminContentPanel">
    <table cellspacing="2" cellpadding="0" border="0" style="width:100%;">

        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('formdesc_settings'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_insertion'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->config->get_followInsertionTitle(); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_stylesource'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->config->get_followStyleSourceTitle(); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_location'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->config->get_followLocationTitle(); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_pictureformat'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->config->get_pictureFormatValue('follow'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2" colspan="2">
                &nbsp;
            </td>
        </tr>

        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('formtitle_follownetworks'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2" colspan="2">
                <?= $this->get_translation('formdesc_follow'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2" style="width:160px;">
                &nbsp;
            </td>
            <td class="eTableLine0 eContent1">
                &nbsp;
            </td>
        </tr>

        <?php $alt = 0; ?>
        <?php foreach ($this->networks as $network => $data) : ?>
            <?php if ($data['follow'] == 1) : ?>
                <tr>
                    <td class="eTableLine<?= $alt; ?> eContent2">
                        <?= $data['title'].$camyks->get_translation('formitem_separator'); ?>
                    </td>
                    <td class="eTableLine<?= $alt; ?> eContent1">
                        <?php if ($this->config->vars['follow_'.$network] == '') : ?>
                            <span class="eContent3">
                                <?= $this->get_translation('nosocialnetwork'); ?>
                            </span>
                        <?php else : ?>
                            <a href="<?= $this->config->vars['follow_'.$network]; ?>" class="eLink1" target="_blank"    rel="noopener">
                                <?= $this->config->vars['follow_'.$network]; ?>
                            </a>
                        <?php endif; ?>
                    </td>
                </tr>
                <?php $alt = abs($alt-1); ?>
            <?php endif; ?>
        <?php endforeach; ?>
    </table>
</div>

<div id="itemIntegrate" style="display:<?= $this->tabBuilder->get_tabDisplay('Integrate'); ?>;"  class="adminContentPanel">
    <table cellspacing="2" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableHeader" colspan="4">
                <?= $this->get_translation('formtitle_facebook'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_facebookaccount'); ?>
            </td>
            <td class="eTableLine0 eContent1" colspan="3">
                <?= $this->config->get_value('integrate_facebook_href'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2" style="width:140px;">
                <?= $this->get_translation('formitem_width'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->config->get_value('integrate_facebook_width'); ?>  px
            </td>
            <td class="eTableLine1 eContent2" style="width:220px;">
                <?= $this->get_translation('formitem_height'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->config->get_value('integrate_facebook_height'); ?>  px
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_tabs'); ?>
            </td>
            <td class="eTableLine0 eContent2">
                <?= $camyks->theme->get_pictHTMLTag(array('pict'=>($this->config->get_value('integrate_facebook_tabTimeline') ? 'valid' : 'empty'))); ?>
                <?= $this->get_translation('formvalue_timeline'); ?>
            </td>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_hidecover'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $camyks->get_translation($this->config->get_value('integrate_facebook_hideCover') ? 'yes' : 'no'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                &nbsp;
            </td>
            <td class="eTableLine0 eContent1">
                <?= $camyks->theme->get_pictHTMLTag(array('pict'=>($this->config->get_value('integrate_facebook_tabEvents') ? 'valid' : 'empty'))); ?>
                <?= $this->get_translation('formvalue_events'); ?>
            </td>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_showfacepile'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $camyks->get_translation($this->config->get_value('integrate_facebook_showFacePile') ? 'yes' : 'no'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                &nbsp;
            </td>
            <td class="eTableLine0 eContent1">
                <?= $camyks->theme->get_pictHTMLTag(array('pict'=>($this->config->get_value('integrate_facebook_tabMessages') ? 'valid' : 'empty'))); ?>
                <?= $this->get_translation('formvalue_messages'); ?>
            </td>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_hidecta'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $camyks->get_translation($this->config->get_value('integrate_facebook_hideCTA') ? 'yes' : 'no'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_smallheader'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $camyks->get_translation($this->config->get_value('integrate_facebook_smallHeader') ? 'yes' : 'no'); ?>
            </td>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_adaptwidth'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $camyks->get_translation($this->config->get_value('integrate_facebook_adaptWidth') ? 'yes' : 'no'); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_lazy'); ?>
            </td>
            <td class="eTableLine0 eContent1" colspan="3">
                <?= $camyks->get_translation($this->config->get_value('integrate_facebook_lazy') ? 'yes' : 'no'); ?>
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
