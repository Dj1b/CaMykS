<?php
/**
 * @brief Content_GoogleSearchResultsViewer module, admin layout.
 * @details Plugin / Module Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Sep 2008
 * @date Modification: Jul 2021
 * @copyright 2008 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

$target = $this->theme->get_pictUrl('target', 12, 'std');
$target_ = $this->theme->get_pictUrl('target', 12, 'ovr');
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title.' : '.$this->gsrItem->vars['name'].' ['.$this->gsrItem->id.']'); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<?= $this->form->display_header(); ?>
<?= $this->form->display_hiddens(); ?>
<div id="itemproperties" class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('title_globalsettings'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0" style="width:200px;">
                <?= $this->get_translation('itemname'); ?>
            </td>
            <td class="eTableLine0">
                <input type="text" name="name" value="<?= $this->gsrItem->vars['name']; ?>" maxlength="32" class="inputs" />
            </td>
        </tr>
        <tr>
            <td class="eTableLine1">
                <?= $this->get_translation('itemlayout'); ?>
            </td>
            <td class="eTableLine1">
                <select name="layout" class="inputs">
                    <?php foreach ($this->get_layouts() as $name => $title) : ?>
                        <option value="<?= $name; ?>"<?= $this->gsrItem->vars['layout'] == $name ? ' selected="selected"' : ''; ?>>
                            <?= $title; ?>
                        </option>
                    <?php endforeach; ?>
                </select>
            </td>
        </tr>

        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('title_gsrsettings'); ?>
            </td>
        </tr>
        <tr>
            <td colspan="2" style="">
                <div id="itemgsrimporterpanel"<?= $this->gsrItem->id==0 ? '':' style="display:none;"'; ?>>
                    <div class="eContent2">
                        <?= $this->get_translation('itemgsrsourceimport'); ?>
                    </div>
                    <div>
                        <textarea id="gsrimporter" class="mceNoEditor" cols="40" rows="4" style="width:100%" onchange="googlesearchresultsviewer_importgsr();"></textarea>
                    </div>
                </div>
                <div id="itemgsrpanel"<?= $this->gsrItem->id == 0 ? ' style="display:none;"' : ''; ?>>
                    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
                        <tr>
                            <td class="eTableLine0" style="width:200px;">
                                <?= $this->get_translation('itemgsrsearchdomain'); ?>
                            </td>
                            <td class="eTableLine0">
                                <input type="text" name="sr_searchdomain" value="<?= $this->gsrItem->vars['sr_searchdomain']; ?>" maxlength="255" class="inputs" />
                            </td>
                            <td class="eTableLine0" style="width:12px;">
                                <a href="javascript:googlesearchresultsviewer_resetgsr();">
                                    <img src="<?= $target; ?>" alt="<?= $this->get_translation('resetgsrparameters'); ?>" title="<?= $this->get_translation('resetgsrparameters'); ?>"
                                        onmouseover="this.src='<?= $target_; ?>';" onmouseout="this.src='<?= $target; ?>';" />
                                </a>
                            </td>
                        </tr>
                        <tr>
                            <td class="eTableLine1">
                                <?= $this->get_translation('itemgsrwidth'); ?>
                            </td>
                            <td class="eTableLine1" colspan="2">
                                <input type="text" name="sr_width" value="<?= $this->gsrItem->vars['sr_width']; ?>" maxlength="5" class="inputs" />
                            </td>
                        </tr>
                    </table>
                </div>
            </td>
        </tr>
    </table>
</div>
<?= $this->form->display_footer(); ?>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
