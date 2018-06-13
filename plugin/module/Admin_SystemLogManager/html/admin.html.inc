<?php
/**
 * @brief Admin_SystemLogManager Module admin main layout
 * @details Plugin / Module layout
 * @file plugin/module/Admin_SystemLogManager/html/admin.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jun 2018
 * @date Modification: Jun 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title); ?>
<?= $this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams); ?>
<?= $this->theme->get_boxContent2Header(); ?>

<?= $this->logForm->display_header(); ?>
<?= $this->logForm->display_hiddens(); ?>

<div id="itemLogs" style="display:<?= $this->tabBuilder->get_tabDisplay('Logs'); ?>;" class="adminContentPanel">

    <div class="menu">
        <div class="logSelection">
            <?= $this->logForm->display_selectInput(array('name'=>'log', 'default'=>$this->selection['log'], 'values'=>$this->logList, 'hasEmptyFirstOption'=>$this->get_translation('logs'), 'class'=>'inputs', 'onchange'=>'LogViewer.onLogChange();'));?>
        </div>
        <div class="fileSelection">
            <?php foreach($this->logFileList as $name => $title) : ?>
                <div class="file<?= ($name == $this->selection['file'] ? ' selected':'') ;?>"  onclick="LogViewer.onLogFileSelect('<?= $name; ?>')">
                    <?= $title; ?>
                </div>
            <?php endforeach; ?>
        </div>
    </div>
    <div class="content">
        <div class="actions">
        
            <?= $this->theme->get_button(array('title'=>$this->get_translation('refresh'), 'url'=>$this->get_adminLink(), 'style'=>'font-size:10px; padding:4px 6px 3px;')); ?>
            
            <?= $this->theme->get_button(array('title'=>$this->get_translation('download'), 'url'=>$this->get_requestLink(array('mode'=>'downloadLogFile')), 'style'=>'font-size:10px; padding:4px 6px 3px;')); ?>
            
            &#124;
            
            <?= $this->logForm->display_textInput(array('name'=>'filter', 'default'=>$this->selection['filter'], 'maxlength'=>32, 'placeholder'=>$this->get_translation('filter'), 'onchange'=>'LogViewer.onFilterChange();')); ?>
            <a href="javascript:LogViewer.resetFilter();" class="img">
                <?= $this->theme->get_pictHTMLTag(array('pict'=>'cross', 'addMouseover'=>true, 'alt'=>$this->get_translation('reset_filter'), 'style'=>'vertical-align:-3px;')); ?>
            </a>
            
        </div>
        <div class="fileDisplay">
        
            <?php if ($this->currentFileContent === '') : ?>
                <div class="mainMessage">
                    <?= $this->get_translation('noresultforthisfilter'); ?>
                </div>
            <?php elseif ($this->currentFileContent !== null) : ?>
                <pre><?= $this->currentFileContent; ?></pre>
            <?php elseif ($this->selection['log'] == '') : ?>
                <div class="mainMessage">
                    <?= $this->get_translation('selectalog'); ?>
                </div>
            <?php else : ?>
                <div class="mainMessage">
                    <?= $this->get_translation('selectafile'); ?>
                </div>
            <?php endif; ?>
        </div>
    </div>

</div>

<div id="itemConfiguration" style="display:<?= $this->tabBuilder->get_tabDisplay('Configuration'); ?>;" class="adminContentPanel">
    <?php $this->load_file('html/configuration/view.html.inc');?>
</div>

<?php if ( $this->help != null ) : ?>
<div id="itemhelp" style="display:<?=$this->tabBuilder->get_tabDisplay('help')?>;" class="adminContentPanel">
<?php $this->display_help(); ?>
</div>
<?php endif; ?>

<?= $this->logForm->display_footer(); ?>

<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>

<?php 
/**
 * @endcond Exclude
 */
?>
