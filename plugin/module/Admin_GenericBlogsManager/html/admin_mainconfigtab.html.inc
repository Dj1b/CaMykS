<?php
/**
 * @brief Admin_GenericBlogsManager Module admin configuration tab layout.
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
?>
<div id="itemconfiguration" style="display:none;" class="adminContentPanel">
    <?= $this->configForm->display_header(); ?>
    <?= $this->configForm->display_hiddens(); ?>
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('config_links_title'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('config_links_maxcount'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <input type="text" name="links_maxcount" value="<?= $this->config->vars['links_maxcount']; ?>" class="inputs" />
            </td>
        </tr>
        <tr>
            <td colspan="2">
                &nbsp;
            </td>
        </tr>
        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('config_news_title'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('config_news_editormode'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?php if ($this->editorMode == true) : ?>
                    <?= $this->configForm->display_selectInput(array('name'=>'news_editormode', 'default'=>$this->config->vars['news_editormode'], 'values'=>$this->config->get_newsEditorModes())); ?>
                <?php else : ?>
                    <input type="hidden" name="news_editormode" value="0" />
                    <select class="inputs" disabled="disabled">
                        <option value=""><?= $this->get_translation('config_newseditormode_0'); ?></option>
                    </select>
                <?php endif; ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('config_news_documentmode'); ?>
            </td>
            <td class="eTableLine1 eContent1">
                <?= $this->configForm->display_selectInput(array('name'=>'news_documentmode', 'default'=>$this->config->vars['news_documentmode'], 'values'=>$this->config->get_newsDocumentModes())); ?>
            </td>
        </tr>

        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('config_news_allowvideo'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <input type="checkbox" name="news_allowvideo" value="1"<?= $this->config->vars['news_allowvideo'] == 1 ? ' checked="checked"' : ''; ?> />
            </td>
        </tr>

        <tr>
            <td colspan="2">
                &nbsp;
            </td>
        </tr>

        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('config_comments_title'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('config_comments_validationmode'); ?>
            </td>
            <td class="eTableLine0 eContent1">
                <?= $this->configForm->display_selectInput(array('name'=>'comments_validationmode', 'default'=>$this->config->vars['comments_validationmode'], 'values'=>$this->config->get_commentsValidationModes())); ?>
            </td>
        </tr>

        <tr>
            <td colspan="2">
                &nbsp;
            </td>
        </tr>

        <tr>
            <td colspan="2" class="content1">
                <?= $this->theme->get_button($camyks->get_translation('valid'), $this->configForm->get_HTMLSubmitLink()); ?>
            </td>
        </tr>
    </table>
    <?= $this->configForm->display_footer(); ?>
</div>
<?php
/**
 * @endcond Exclude
 */
?>
