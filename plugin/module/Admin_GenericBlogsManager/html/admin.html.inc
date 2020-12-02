<?php
/**
 * @brief Admin_GenericBlogsManager Module admin main layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Apr 2008
 * @date Modification: Nov 2020
 * @copyright 2008 - 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;

$view = $this->theme->get_pictURL('view', 12, 'std');
$view_ = $this->theme->get_pictURL('view', 12, 'ovr');

$plus = $this->theme->get_pictURL('plus', 12, 'std');
$plus_ = $this->theme->get_pictURL('plus', 12, 'ovr');

$minus = $this->theme->get_pictURL('minus', 12, 'std');
$minus_ = $this->theme->get_pictURL('minus', 12, 'ovr');

$edit = $this->theme->get_pictURL('edit', 12, 'std');
$edit_ = $this->theme->get_pictURL('edit', 12, 'ovr');

$cross = $this->theme->get_pictURL('cross', 12, 'std');
$cross_ = $this->theme->get_pictURL('cross', 12, 'ovr');

$valid = $this->theme->get_pictURL('valid', 12, 'std');
$valid_ = $this->theme->get_pictURL('valid', 12, 'ovr');

$file = $this->theme->get_pictURL('file', 12, 'std');
$file_ = $this->theme->get_pictURL('file', 12, 'ovr');

$empty = $this->theme->get_pictURL('empty', 12, 'std');
?>
<?= $this->theme->get_boxHeader('width:600px; margin:0 auto;'); ?>
<?= $this->theme->get_boxTitleBar($this->title); ?>
<?= $this->theme->get_boxTabsBar($this->tabs, $this->tabObject.'.mouseclick', $this->tabObject.'.mouseover', $this->tabObject.'.mouseout', 'news'); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<div id="itemnews" style="display:block;" class="adminContentPanel">
    <div>
        <?= $this->newsListForm->display_header(); ?>
        <?= $this->newsListForm->display_hiddens(); ?>
        <table cellspacing="0" cellpadding="0" style="width:100%;">
            <tr>
                <td class="eContent2">
                    <?= $this->get_translation('news_listpage'); ?> :
                </td>
                <td class="eContent1">
                    <div class="inputs" style="text-align:center;">
                        <a href="javascript:document.<?= $this->newsListForm->name; ?>.newsListPage.value--;document.<?= $this->newsListForm->name; ?>.submit();void(0);" style="float:left">
                            <img src="<?= $minus; ?>" alt="" onmouseover="this.src='<?= $minus_; ?>';" onmouseout="this.src='<?= $minus; ?>';" style="margin-top:6px;" />
                        </a>
                        <a href="javascript:document.<?= $this->newsListForm->name; ?>.newsListPage.value++;document.<?= $this->newsListForm->name; ?>.submit();void(0);" style="float:right">
                            <img src="<?= $plus; ?>" alt="" onmouseover="this.src='<?= $plus_; ?>';" onmouseout="this.src='<?= $plus; ?>';" style="margin-top:6px;" />
                        </a>
                        <input type="text" name="newsListPage" value="<?= $this->newsListPage+1?>" size="4" style="text-align:right" onchange="document.<?= $this->newsListForm->name; ?>.submit()" />
                        / <?= $this->newsPages ?>
                    </div>
                </td>
                <td class="eContent2" style="text-align:right;">
                    <input type="hidden" name="newsListUnread" value="0" />
                    <?= $this->get_translation('news_listunread'); ?>
                </td>
                <td class="eContent1" style="width:12px;">
                    <input type="checkbox" name="newsListUnread" value="1" <?= ($this->newsListUnread==1 and count($this->unreadCommentIds)>0) ? ' checked="checked"' : ''; ?> onchange="<?= $this->newsListForm->get_JSSubmitLink(); ?>" <?= (count($this->unreadCommentIds)==0? 'disabled="disabled"':''); ?> />
                </td>
            </tr>
        </table>
        <?= $this->newsListForm->display_footer(); ?>
    </div>
    <table cellspacing="0" cellpadding="0" style="width:100%;">
        <?php if ($this->check_right(2)===true or $this->check_right(3)===true): ?>
            <tr>
                <td class="eTableLine1 eContent1" style="width:12px;">
                    &nbsp;
                </td>
                <td class="eTableLine1" colspan="4">
                    <a href="<?= $this->editNewsLink; ?>0">
                        <?= $this->get_translation('news_add'); ?>
                    </a>
                </td>
                <td class="eTableLine1">
                    <a href="<?= $this->editNewsLink; ?>0">
                        <img src="<?= $plus; ?>" alt="<?= $this->get_translation('news_add'); ?>" title="<?= $this->get_translation('news_add'); ?>" onmouseover="this.src='<?= $plus_; ?>';" onmouseout="this.src='<?= $plus; ?>';" />
                    </a>
                </td>
                <td class="eTableLine1">
                    &nbsp;
                </td>
                <td class="eTableLine1">
                    &nbsp;
                </td>
            </tr>
        <?php endif; ?>
        <tr>
            <td class="eTableHeader" style="width:12px;">
                &nbsp;
            </td>
            <td class="eTableHeader">
                <?= $this->get_translation('news_title'); ?>
            </td>
            <td class="eTableHeader" style="width:100px;">
                <?= $this->get_translation('news_date'); ?>
            </td>
            <td class="eTableHeader">
                <?= $this->get_translation('news_author'); ?>
            </td>
            <td class="eTableHeader">
                <?= $this->get_translation('news_comment'); ?>
            </td>
            <td class="eTableHeader" style="width:12px;">
                &nbsp;
            </td>
            <td class="eTableHeader" style="width:12px">
                &nbsp;
            </td>
            <td class="eTableHeader" style="width:12px">
                &nbsp;
            </td>
        </tr>
        <?php $alt = 0; ?>
        <?php foreach ($this->newsList as $newsId => $news): ?>
            <tr>
                <td class="eTableLine<?= $alt; ?>">
                    <?php if ($news->vars['status'] == 1 and $news->vars['ndate'] < mktime()) : ?>
                        <img src="<?= $valid; ?>" alt="" />
                    <?php elseif ($news->vars['status'] == 1) :?>
                        <img src="<?= $minus; ?>" alt="" />
                    <?php else : ?>
                        <img src="<?= $empty?>" alt="" />
                    <?php endif; ?>
                </td>
                <td class="eTableLine<?= $alt; ?>">
                    <?php if (strlen($news->vars['title']) > 48) : ?>
                        <?php preg_match('/(.){1,45} /', $news->vars['title'], $matches); ?>
                        <?= $matches[0]; ?>...
                    <?php else : ?>
                        <?= $news->vars['title']; ?>
                    <?php endif; ?>
                </td>
                <td class="eTableLine<?= $alt; ?>">
                    <?= date_displayShortDateHour($news->vars['ndate']); ?>
                </td>
                <td class="eTableLine<?= $alt; ?>">
                    <?= $news->vars['author']; ?>
                </td>
                <td class="eTableLine<?= $alt; ?>">
                    <?= implode(' &#124; ', $news->vars['coms']); ?>
                </td>
                <?php if ($this->check_right(3)===true or ($this->check_right(2) and $news->vars['author'] == $camyks->adminUser->login)) : ?>
                    <td class="eTableLine<?= $alt; ?>">
                        <a href="<?= $this->editNewsLink.$newsId; ?>">
                            <img src="<?= $edit; ?>" alt="<?= $this->get_translation('news_edit'); ?>" title="<?= $this->get_translation('news_edit'); ?>" onmouseover="this.src='<?= $edit_; ?>';" onmouseout="this.src='<?= $edit; ?>';" />
                        </a>
                    </td>
                    <td class="eTableLine<?= $alt; ?>">
                        <a href="javascript:genericblogsmanager_deleteNews(<?= $newsId; ?>);">
                            <img src="<?= $cross; ?>" alt="<?= $this->get_translation('news_delete'); ?>" title="<?= $this->get_translation('news_delete'); ?>" onmouseover="this.src='<?= $cross_; ?>';" onmouseout="this.src='<?= $cross; ?>';" />
                        </a>
                    </td>
                <?php else : ?>
                    <td class="eTableLine<?= $alt; ?>">
                        &nbsp;
                    </td>
                    <td class="eTableLine<?= $alt; ?>">
                        &nbsp;
                    </td>
                <?php endif; ?>
                <td class="eTableLine<?= $alt; ?>">
                    <?php if ($this->check_right(7)===true or ($this->check_right(6) and $news->vars['author'] == $camyks->adminUser->login)) : ?>
                        <a href="<?= $this->viewCommentsLink.$newsId; ?>">
                            <img src="<?= $file; ?>"  alt="<?= $this->get_translation('news_editcomments'); ?>" title="<?= $this->get_translation('news_editcomments'); ?>" onmouseover="this.src='<?= $file_; ?>';" onmouseout="this.src='<?= $file; ?>';" />
                        </a>
                    <?php endif; ?>
                </td>
            </tr>
            <?php $alt = abs($alt-1); ?>
        <?php endforeach; ?>
    </table>
</div>

<?php if ($this->check_right(4)===true or $this->check_right(5)===true) : ?>
    <div id="itemlinks" style="display:none;" class="adminContentPanel">
        <table cellspacing="0" cellpadding="0" style="width:100%">
            <?php if ($this->adminLinkCount >= $this->config->vars['links_maxcount']) : ?>
                <tr>
                    <td class="eTableLine1">
                        &nbsp;
                    </td>
                    <td class="eTableLine1 eContent1" colspan="5">
                        <?= $this->get_translation('links_maxlinkcountreached'); ?>
                    </td>
                </tr>
            <?php else : ?>
                <tr>
                    <td class="eTableLine1">
                        &nbsp;
                    </td>
                    <td class="eTableLine1 eContent1" colspan="2">
                        <a href="<?= $this->editLinkLink; ?>0">
                            <?= $this->get_translation('links_add'); ?>
                        </a>
                    </td>
                    <td class="eTableLine1">
                        &nbsp;
                    </td>
                    <td class="eTableLine1 eContent1">
                        <a href="<?= $this->editLinkLink; ?>0">
                            <img src="<?= $plus; ?>" alt="<?= $this->get_translation('links_add'); ?>"  title="<?= $this->get_translation('links_add'); ?>" onmouseover="this.src='<?= $plus_; ?>';" onmouseout="this.src='<?= $plus; ?>';" />
                        </a>
                    </td>
                    <td class="eTableLine1">
                        &nbsp;
                    </td>
                </tr>
            <?php endif; ?>
            <tr>
                <td class="eTableHeader" style="width:12px;">
                    &nbsp;
                </td>
                <td class="eTableHeader">
                    <?= $this->get_translation('links_title'); ?>
                </td>
                <td class="eTableHeader">
                    <?= $this->get_translation('links_author'); ?>
                </td>
                <td class="eTableHeader" style="width:12px;">
                    &nbsp;
                </td>
                <td class="eTableHeader" style="width:12px;">
                    &nbsp;
                </td>
                <td class="eTableHeader" style="width:12px;">
                    &nbsp;
                </td>
            </tr>

            <?php $alt = 0; ?>
            <?php foreach ($this->links as $link) : ?>
                <tr>
                    <td class="eTableLine<?= $alt; ?>">
                        &nbsp;
                    </td>
                    <td class="eTableLine<?= $alt; ?>">
                        <?= $link->vars['title']; ?>
                    </td>
                    <td class="eTableLine<?= $alt; ?>">
                        <?= $link->vars['author']; ?>
                    </td>
                    <td class="eTableLine<?= $alt; ?>">
                        <a href="<?= $link->vars['link']?>" target="_blank">
                            <img src="<?= $view; ?>" alt="<?= $this->get_translation('links_view'); ?>" title="<?= $this->get_translation('links_view'); ?>" onmouseover="this.src='<?= $view_; ?>';" onmouseout="this.src='<?= $view; ?>';" />
                        </a>
                    </td>
                    <td class="eTableLine<?= $alt; ?>">
                        <a href="<?= $this->editLinkLink.$link->id; ?>">
                            <img src="<?= $edit; ?>" alt="<?= $this->get_translation('links_edit'); ?>" title="<?= $this->get_translation('links_edit'); ?>" onmouseover="this.src='<?= $edit_; ?>';" onmouseout="this.src='<?= $edit; ?>';" />
                        </a>
                    </td>
                    <td class="eTableLine<?= $alt; ?>">
                        <a href="javascript:genericblogsmanager_deleteLink(<?= $link->id; ?>);">
                            <img src="<?= $cross; ?>" alt="<?= $this->get_translation('links_delete'); ?>" title="<?= $this->get_translation('links_delete'); ?>" onmouseover="this.src='<?= $cross_; ?>';" onmouseout="this.src='<?= $cross; ?>';" />
                        </a>
                    </td>
                </tr>

                <?php $alt = abs($alt-1); ?>
            <?php endforeach; ?>
        </table>
    </div>
<?php endif; ?>

<?php if ($this->check_right(8)===true or $this->check_right(9)===true) : ?>
    <div id="itemtags" style="display:none;" class="adminContentPanel">
        <?php if($this->check_right(8) === true) : ?>
            <?= $this->tagEditor->display_header(); ?>
            <?= $this->tagEditor->display_hiddens(); ?>
        <?php endif; ?>
        <table cellspacing="0" cellpadding="0" style="width:100%">
            <tbody id="tabBox">
                <?php if ($this->check_right(8)===true) : ?>
                    <tr>
                        <td class="eTableLine1" style="width:12px;">
                            &nbsp;
                        </td>
                        <td id="tagName0" class="eTableLine1">
                            <a href="javascript:genericblogsmanager_editTag(0);">
                                <?= $this->get_translation('tags_add'); ?>
                            </a>
                        </td>
                        <td class="eTableLine1">
                            &nbsp;
                        </td>
                        <td id="tagPlus0" class="eTableLine1">
                            <a href="javascript:genericblogsmanager_editTag(0);">
                                <img src="<?= $plus; ?>" alt="<?= $this->get_translation('tags_add'); ?>" title="<?= $this->get_translation('tags_add'); ?>" onmouseover="this.src='<?= $plus_; ?>';" onmouseout="this.src='<?= $plus; ?>';" />
                            </a>
                        </td>
                        <td id="tagMinus0" class="eTableLine1">
                            &nbsp;
                        </td>
                    </tr>
                <?php endif; ?>
                <tr>
                    <td class="eTableHeader" style="width:12px;">
                        &nbsp;
                    </td>
                    <td class="eTableHeader">
                        <?= $this->get_translation('tags_title'); ?>
                    </td>
                    <td class="eTableHeader">
                        <?= $this->get_translation('tags_counter'); ?>
                    </td>
                    <td class="eTableHeader" style="width:12px;">
                        <div style="display:none">
                            <a id="tagPlusButton" href="javascript:genericblogsmanager_saveTag();void(0);">
                                <img src="<?= $valid; ?>" alt="<?= $this->get_translation('tags_save'); ?>" title="<?= $this->get_translation('tags_save'); ?>" onmouseover="this.src='<?= $valid_; ?>';" onmouseout="this.src='<?= $valid; ?>';" />
                            </a>
                        </div>
                    </td>
                    <td class="eTableHeader" style="width:12px">
                        <div style="display:none">
                            <a id="tagMinusButton" href="javascript:genericblogsmanager_cancelTagEdition();void(0);">
                                <img src="<?= $cross; ?>" alt="<?= $this->get_translation('tags_canceledition'); ?>" title="<?= $this->get_translation('tags_canceledition'); ?>" onmouseover="this.src='<?= $cross_; ?>';" onmouseout="this.src='<?= $cross; ?>';" />
                            </a>
                        </div>
                    </td>
                </tr>
                <?php $alt = 0; ?>
                <?php $cnt = 1; ?>
                <?php foreach ($this->tagList as $tag => $counter): ?>
                    <tr>
                        <td class="eTableLine<?= $alt; ?>">
                            &nbsp;
                        </td>
                        <td id="tagName<?= $cnt; ?>" class="eTableLine<?= $alt; ?>">
                            <?= $tag; ?>
                        </td>
                        <td class="eTableLine<?= $alt; ?>">
                            <?= $counter; ?>
                        </td>
                        <?php if ($this->check_right(8) === true) : ?>
                            <td id="tagPlus<?= $cnt; ?>" class="eTableLine<?= $alt; ?>">
                                <a href="javascript:genericblogsmanager_editTag(<?= $cnt; ?>);">
                                    <img src="<?= $edit; ?>" alt="<?= $this->get_translation('tags_edit'); ?>" title="<?= $this->get_translation('tags_edit'); ?>" onmouseover="this.src='<?= $edit_; ?>';" onmouseout="this.src='<?= $edit; ?>';" />
                                </a>
                            </td>
                            <td id="tagMinus<?= $cnt; ?>" class="eTableLine<?= $alt; ?>">
                                <a href="javascript:genericblogsmanager_deleteTag('<?= $tag; ?>');">
                                    <img src="<?= $cross; ?>" alt="<?= $this->get_translation('tags_delete'); ?>" title="<?= $this->get_translation('tags_delete'); ?>" onmouseover="this.src='<?= $cross_; ?>';" onmouseout="this.src='<?= $cross; ?>';" />
                                </a>
                            </td>
                        <?php else : ?>
                            <td class="eTableLine<?= $alt; ?>">
                                &nbsp;
                            </td>
                            <td class="eTableLine<?= $alt; ?>">
                                &nbsp;
                            </td>
                        <?php endif; ?>
                    </tr>
                    <?php $alt = abs($alt-1); ?>
                    <?php $cnt++; ?>
                <?php endforeach; ?>
            </tbody>
        </table>
        <?php if ($this->check_right(8) === true) : ?>
            <?= $this->tagEditor->display_footer(); ?>
        <?php endif; ?>
    </div>
<?php endif; ?>

<?php if ($this->check_right(1) === true) : ?>
    <?php $this->load_file('html/admin_mainconfigtab.html.inc'); ?>
<?php endif; ?>

<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
<?php
/**
 * @endcond Exclude
 */
?>
