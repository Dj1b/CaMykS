<?php
/**
 * @brief Admin_GoogleTools Module admin list layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Sep 2007
 * @date Modification: Jan 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

$view = $this->theme->get_pictURL('view', 12, 'std');
$view_ = $this->theme->get_pictURL('view', 12, 'ovr');
?>
<?= $camyks->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $camyks->theme->get_boxTitleBar($this->title); ?>
<?= $camyks->theme->get_boxTabsBar($this->tabs, $this->tabObject.'.mouseclick', $this->tabObject.'.mouseover', $this->tabObject.'.mouseout', 'referred'); ?>
<?= $camyks->theme->get_boxContent2Header(); ?>

<div id="itemreferred" style="display:block;" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <?php if (isset($this->referredpages)) : ?>
            <tr>
                <td class="content1">
                    <?= $this->get_translation('referredpagescountresult', $this->referredpages['count']); ?>
                </td>
            </tr>

            <?php if ($this->referredpages['count'] > $this->maxreferredpages) : ?>
                <tr>
                    <td class="content1" colspan="2">
                        <?= $this->get_translation('referredpagesfirstresult', $this->maxreferredpages); ?>
                    </td>
                </tr>
            <?php elseif ($this->referredpages['count'] > 0) : ?>
                <tr>
                    <td class="content1" colspan="2">
                        <?= $this->get_translation('referredpageslistresult'); ?>
                    </td>
                </tr>
            <?php endif; ?>

            <?php $alt=0; ?>
            <?php foreach ($this->referredpages['list'] as $page) : ?>
                <tr>
                    <td class="listline<?= $alt; ?>">
                        <a href="<?= $page['url']; ?>" target="_blank" rel="noopener noreferer">
                            <?= $page['title']; ?>
                        </a>
                    </td>
                    <td class="listline<?= $alt; ?>" width="12">
                        <a href="<?= $page['url']; ?>" class="img" target="_blank" rel="noopener noreferer">
                            <img src="<?= $view; ?>" alt="" onmouseover="this.src='<?= $view_; ?>';" onmouseout="this.src='<?= $view; ?>';">
                        </a>
                    </td>
                </tr>
                <?php $alt = abs($alt-1); ?>
            <?php endforeach; ?>
        <?php else : ?>
            <tr>
                <td class="content1">
                    <?= $this->get_translation('referreddesc'); ?>
                </td>
            </tr>

            <tr>
                <td class="content1">
                    <?= $this->theme->get_button($camyks->get_translation('search'), $camyks->get_adminLink($this->name).'&amp;mode=referred'); ?>
                </td>
            </tr>
        <?php endif; ?>
    </table>
</div>

<div id="itemlinked" style="display:none;" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <?php if (isset ($this->linkedpages)) : ?>
            <tr>
                <td class="content1">
                    <?= $this->get_translation('linkedpagescountresult', $this->linkedpages['count']); ?>
                </td>
            </tr>
            <?php if ($this->linkedpages['count'] > $this->maxlinkedpages) : ?>
                <tr>
                    <td class="content1" colspan="2">
                        <?= $this->get_translation('linkedpagesfirstresult', $this->maxlinkedpages); ?>
                    </td>
                </tr>
            <?php elseif ($this->linkedpages['count'] > 0) : ?>
                <tr>
                    <td class="content1" colspan="2">
                        <?= $this->get_translation('linkedpageslistresult'); ?>
                    </td>
                </tr>
            <?php endif; ?>

            <?php $alt=0; ?>
            <?php foreach ($this->linkedpages['list'] as $page) : ?>
                <tr>
                    <td class="listline<?= $alt; ?>">
                        <a href="<?= $page['url']; ?>" target="_blank" rel="noopener noreferer">
                            <?= $page['title']; ?>
                        </a>
                    </td>
                    <td class="listline<?= $alt; ?>" width="12">
                        <a href="<?= $page['url']; ?>" target="_blank" rel="noopener noreferer">
                            <img src="<?= $view; ?>" alt="" border="0" onmouseover="this.src='<?= $view_; ?>';" onmouseout="this.src='<?= $view; ?>';">
                        </a>
                    </td>
                </tr>
                <?php $alt = abs($alt-1); ?>
            <?php endforeach; ?>
        <?php else : ?>
            <tr>
                <td class="content1">
                    <?= $this->get_translation('linkeddesc'); ?>
                </td>
            </tr>

            <tr>
                <td class="content1">
                    <?= $this->theme->get_button($camyks->get_translation('search'), $camyks->get_adminLink($this->name).'&amp;mode=linked'); ?>
                </td>
            </tr>
        <?php endif; ?>
    </table>
</div>

<?= $camyks->theme->get_boxContent2Footer(); ?>
<?= $camyks->theme->get_boxButtonsBar($this->buttons); ?>
<?= $camyks->theme->get_boxFooter(); ?>
