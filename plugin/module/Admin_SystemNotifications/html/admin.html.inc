<?php
/**
 * @brief Admin_SystemNotifications Module admin main layout
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2.2
 * @date Creation: Jul 2017
 * @date Modification: Apr 2021
 * @copyright 2017 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title); ?>
<?= $this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams); ?>
<?= $this->theme->get_boxContent2Header(); ?>



<div id="itemFollowUp" style="display:<?= $this->tabBuilder->get_tabDisplay('FollowUp')?>;" class="adminContentPanel">

    <?php if ($this->config->vars['module_mode'] == 1) : ?>
        <div style="float:right;">
            <?= $this->theme->get_button(array('title'=>$this->get_translation('check_now'), 'url'=>$this->get_adminLink(array('mode'=>'check_websites')))); ?>
        </div>
        <div class="eContent2" style="padding:6px 10px;">
            <?php if ($this->config->vars['running_lastCheck'] > 0) : ?>
                <?= $this->get_translation('lastcheckdate', date_displayLongDateHour($this->config->vars['running_lastCheck'])); ?>
            <?php endif; ?>
        </div>
    <?php endif; ?>

    <?php foreach ($this->followUpList as $id => $followUp) : ?>

        <?php if ($this->config->vars['module_mode'] == 1) : ?>

            <div style="display:inline-block; width:46%; min-width:320px; box-shadow: 0 0 3px 1px rgba(0, 0, 0, 0.25); margin:10px; vertical-align:top;">
                <table cellspacing="2" cellpadding="0" border="0" style="width:100%; border: solid 1px white;">

                    <tr>
                        <td colspan="3" class="eTableSubHeader" title="<?= $followUp['title']; ?>">
                            <?php if (!isset($followUp['self']) or $followUp['self'] == false) : ?>
                            <a href="<?= $this->get_adminLink(array('mode'=>'check_website', 'website_id'=>$id)); ?>" class="img">
                                <?= $this->theme->get_pictHTMLTag(array('pict'=>'notify', 'addMouseover'=>true, 'alt'=>$this->get_translation(''), 'title'=>$this->get_translation('check_notifications'), 'style'=>'float:right;')); ?>
                            </a>
                            <?php endif; ?>
                            <?= string_getShortenedSentence($followUp['name'], 56); ?>
                        </td>
                    </tr>

        <?php else : ?>

            <table cellspacing="2" cellpadding="0" border="0" style="width:100%;">

        <?php endif; ?>

        <?php if ($followUp['error'] != '') : ?>

            <tr>
                <td colspan="3" class="eTableLine0 error" style="padding-left:<?= (10+$this->config->vars['module_mode']*20); ?>px;">
                    <?= $followUp['error']; ?>
                </td>
            </tr>

        <?php elseif (count($followUp['modules']) == 0) : ?>

            <tr>
                <td colspan="3" class="eTableLine0 eContent2" style="padding-left:<?= (10+$this->config->vars['module_mode']*20); ?>px;">
                    <?= $this->get_translation('nonotifications'); ?>
                </td>
            </tr>

        <?php else : ?>

            <?php foreach ($followUp['modules'] as $module) : ?>

                <tr>
                    <td colspan="3" class="eTableHeader" style="padding-left:<?= (max(10, $this->config->vars['module_mode']*20)); ?>px;">
                        <?= $module['title']; ?>
                    </td>
                </tr>

                <?php $alt = 0; ?>
                <?php foreach ($module['items'] as $item) : ?>

                    <tr>
                        <td class="eTableLine<?= $alt; ?>" style="padding-left:<?= ((1+$this->config->vars['module_mode'])*20); ?>px;">
                            <?= $item['title']; ?>
                        </td>
                        <td class="eTableLine<?= $alt; ?>" style="text-align:right; width:40px;">
                            <?= $item['cnt']; ?>
                        </td>
                        <td class="eTableLine<?= $alt; ?>" style="width:20px; font-size:0;">
                        <?php if ($item['priority'] == 0) : ?>
                            <img src="<?= $this->get_fileURL('img/priority/low.png'); ?>" alt="<?= $this->get_translation('itempriority_low'); ?>" title="<?= $this->get_translation('itempriority_low'); ?>" />
                        <?php elseif ($item['priority'] == 1) : ?>
                            <img src="<?= $this->get_fileURL('img/priority/medium.png'); ?>" alt="<?= $this->get_translation('itempriority_medium'); ?>" title="<?= $this->get_translation('itempriority_medium'); ?>" />
                        <?php elseif ($item['priority'] == 2) : ?>
                            <img src="<?= $this->get_fileURL('img/priority/high.png'); ?>" alt="<?= $this->get_translation('itempriority_high'); ?>" title="<?= $this->get_translation('itempriority_high'); ?>" />
                        <?php endif; ?>
                        </td>
                    </tr>

                    <?php $alt = abs($alt-1); ?>
                <?php endforeach; ?>

                <tr>
                    <td colspan="3">
                        &nbsp;
                    </td>
                </tr>

            <?php endforeach; ?>
        <?php endif; ?>

        <?php if ($this->config->vars['module_mode'] == 1) : ?>
                </table>
            </div>
        <?php else : ?>
            </table>
        <?php endif; ?>
    <?php endforeach; ?>
</div>

<div id="itemConfiguration" style="display:<?= $this->tabBuilder->get_tabDisplay('Configuration')?>;" class="adminContentPanel">
    <?php $this->load_file('html/configuration/view.html.inc');?>
</div>

<?php if ($this->check_right(1) == true and $this->config->vars['module_mode'] == 1) : ?>
    <div id="itemWebsites" style="display:<?= $this->tabBuilder->get_tabDisplay('Websites')?>;" class="adminContentPanel">
        <?= $this->websiteList->display('head'); ?>
        <?= $this->websiteList->display('list'); ?>
    </div>
<?php endif; ?>

<?php if ($this->help != null) : ?>
    <div id="itemhelp" style="display:<?= $this->tabBuilder->get_tabDisplay('help')?>;" class="adminContentPanel">
        <?php $this->display_help(); ?>
    </div>
<?php endif; ?>

<?= $this->theme->get_boxContent2Footer()?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
