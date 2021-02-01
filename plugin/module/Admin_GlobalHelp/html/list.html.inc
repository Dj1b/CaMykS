<?php
/**
 * @brief Admin_GlobalHelp Module admin list layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Fev 2007
 * @date Modification: Jan 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;

$view = $this->theme->get_pictURL('view', 12, 'std');
$view_ = $this->theme->get_pictURL('view', 12, 'ovr');
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<div class="adminContentPanel">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%">
        <?php if (count($this->list['engine']) > 0) : ?>
            <?php $alt = 0; ?>
            <tr>
                <td class="eTableHeader" style="width:12px;">
                    &nbsp;
                </td>
                <td class="eTableHeader">
                    <?= $this->get_translation('withengine', $camyks->title)?>
                </td>
                <td class="eTableHeader">
                    &nbsp;
                </td>
            </tr>
            <?php foreach ($this->list['engine'] as $e) : ?>
                <tr>
                    <td class="eTableLine<?= $alt; ?>">
                        &nbsp;
                    </td>
                    <td class="eTableLine<?= $alt; ?>">
                        <a href="<?= $e['link']; ?>" class="eLink1">
                            <?= $e['title']; ?></a>
                      </td>
                      <td class="eTableLine<?= $alt; ?>">
                        <a href="<?= $e['link']; ?>" class="img">
                            <img src="<?= $view; ?>" alt="<?= $this->get_translation('viewhelp'); ?>" title="<?= $this->get_translation('viewhelp'); ?>"
                                onmouseover="this.src='<?= $view_; ?>';" onmouseout="this.src='<?= $view; ?>';" />
                        </a>
                    </td>
                </tr>
                <?php $alt = abs($alt-1); ?>
            <?php endforeach; ?>
            <tr>
                <td colspan="3">
                    &nbsp;
                </td>
            </tr>
        <?php endif; ?>
        <?php if (count($this->list['modules']) > 0) : ?>
            <tr>
                <td class="eTableHeader" style="width:12px;">
                    &nbsp;
                </td>
                <td class="eTableHeader">
                    <?= $this->get_translation('withmodules')?>
                </td>
                <td class="eTableHeader" style="width:12px;">
                    &nbsp;
                </td>
            </tr>

            <?php $alt=0; ?>
            <?php foreach ($this->list['modules'] as $e) : ?>
                <tr>
                    <td class="eTableLine<?= $alt; ?>">
                        &nbsp;
                    </td>
                    <td class="eTableLine<?= $alt; ?>">
                        <a href="<?= $e['link']; ?>" class="eLink1">
                            <?= $e['title']; ?></a>
                    </td>
                    <td class="eTableLine<?= $alt; ?>">
                        <a href="<?= $e['link']; ?>" class="img">
                            <img src="<?= $view; ?>" alt="<?= $this->get_translation('viewhelp'); ?>" title="<?= $this->get_translation('viewhelp'); ?>"
                                onmouseover="this.src='<?= $view_; ?>';" onmouseout="this.src='<?= $view; ?>';" />
                        </a>
                    </td>
                </tr>
                <?php $alt = abs($alt-1); ?>
            <?php endforeach; ?>
            <tr>
                <td colspan="3">
                    &nbsp;
                 </td>
            </tr>
        <?php endif; ?>
        <?php if (count($this->list['site']) > 0) : ?>
            <tr>
                <td class="eTableHeader" style="width:12px;">
                    &nbsp;
                </td>
                <td class="eTableHeader">
                    <?= $this->get_translation('withsite')?>
                </td>
                <td class="eTableHeader" style="width:12px;">
                    &nbsp;
                </td>
            </tr>
            <?php $alt=0; ?>
            <?php foreach ($this->list['site'] as $e) : ?>
                <tr>
                    <td class="eTableLine<?= $alt; ?>">
                        &nbsp;
                    </td>
                    <td class="eTableLine<?= $alt; ?>">
                        <a href="<?= $e['link']; ?>" class="eLink1">
                            <?= $e['title']; ?></a>
                    </td>
                    <td class="eTableLine<?= $alt; ?>">
                        <a href="<?= $e['link']; ?>" class="img">
                            <img src="<?= $view; ?>" alt="<?= $this->get_translation('viewhelp'); ?>" title="<?= $this->get_translation('viewhelp'); ?>"
                                onmouseover="this.src='<?= $view_; ?>';" onmouseout="this.src='<?= $view; ?>';" />
                        </a>
                    </td>
                </tr>
            <?php endforeach; ?>
        <?php endif; ?>
    </table>
</div>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
<?php
/**
 * @endcond Exclude
 */
?>
