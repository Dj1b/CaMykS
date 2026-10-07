<?php
/**
 * @brief Admin_GenericSearchEngineManager module, admin main layout.
 * @details Plugin / Module Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Sep 2026
 * @date Modification: Sep 2026
 * @copyright 2026 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title); ?>
<?= $this->theme->get_boxTabsBar($this->tabBuilder->tabs, $this->tabBuilder->jsParams); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<div id="itemIndexedContent" style="display:<?= $this->tabBuilder->get_tabDisplay('IndexedContent'); ?>;" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableHeader">
                <?= $camyks->get_translation('module'); ?>
            </td>
            <td class="eTableHeader">
                <?= $this->get_translation('formtitle_types'); ?>
            </td>
            <td class="eTableHeader">
                <?= $this->get_translation('formtitle_objects'); ?>
            </td>
        </tr>
        <?php $alt = 0; ?>
        <?php foreach ($this->statisticData['modules'] as $name => $data) : ?>
            <?php if (!isset($camyks->modules[$name])) continue; ?>
            <tr>
                <td class="eTableLine<?= $alt; ?>">
                    <?= $camyks->modules[$name]->title; ?>
                </td>
                <td class="eTableLine<?= $alt; ?>">
                    <?= $data['types']; ?>
                </td>
                <td class="eTableLine<?= $alt; ?>">
                    <?= $data['objects']; ?>
                </td>
            </tr>
            <?php $alt = abs($alt-1); ?>
        <?php endforeach; ?>
    </table>
</div>
<div id="itemSearch" style="display:<?= $this->tabBuilder->get_tabDisplay('Search'); ?>;" class="adminContentPanel">
    <?= $this->searchForm->display_header(); ?>
    <?= $this->searchForm->display_hiddens(); ?>
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableLine0">
                <?php $query = $this->get_searchQuery(); ?>
                <?= $this->searchForm->display_searchInput(array('name'=>'search', 'default'=>$query['search'])); ?>
            </td>
            <td class="eTableLine0">
                <?= $this->theme->get_button($this->get_translation('search_execute'), $this->searchForm->get_HTMLSubmitLink()); ?>
            </td>
        </tr>
    </table>
    <?= $this->searchForm->display_footer(); ?>
    <?php $this->load_file('html/Search/Results.html.inc'); ?>
</div>
<?php if (!is_null($this->help)) : ?>
    <div id="itemhelp" style="display:<?= $this->tabBuilder->get_tabDisplay('help'); ?>;" class="adminContentPanel">
        <?= $this->display_help(); ?>
    </div>
<?php endif; ?>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
