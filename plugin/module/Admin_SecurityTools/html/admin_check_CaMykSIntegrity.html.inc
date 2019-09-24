<?php
/**
 * @brief Admin_SecurityTools Module admin check CaMykS integrity layout.
 * @details Plugin / Module layout
 * @file plugin/module/Admin_SecurityTools/html/admin_check_CaMykSIntegrity.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Sep 2019
 * @date Modification: Sep 2019
 * @copyright 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title.$camyks->get_translation('formitem_separator').$this->get_translation('formtitle_checkcamyksintegrity')); ?>
<?= $this->theme->get_boxContent2Header(); ?>
    <div class="eTitle3">
        <?= $this->get_translation('formtitle_integritysummary'); ?>
    </div>

    <table cellspacing="0" cellpadding="0" border="0" style="width:100%;">
        <tr>
            <td class="eTableLine0 eContent2" style="width:200px;">
                <?= $this->get_translation('formitem_integrityfiledate'); ?>
            </td>
            <td class="eTableLine0">
                <?= $this->integrityCheckResult['date']; ?>
            </td>
        </tr>
        <?php $alt = 1; ?>
        <?php if (isset($this->integrityCheckResult['gitLastCommit']) and $this->integrityCheckResult['gitLastCommit'] !== null) : ?>
        <tr>
            <td class="eTableLine<?= $alt; ?> eContent2">
                <?= $this->get_translation('formitem_lastgitcommit'); ?>
            </td>
            <td class="eTableLine<?= $alt; ?> eContent2">
                <a href="https://github.com/Dj1b/CaMykS/commit/<?= $this->integrityCheckResult['gitLastCommit']; ?>" class="eLink2" target="_blank" rel="noreferrer noopener">
                    <?= $this->integrityCheckResult['gitLastCommit']; ?>
                </a>
            </td>
        </tr>
        <?php $alt = abs($alt-1); ?>
        <?php endif; ?>
        <tr>
            <td class="eTableLine<?= $alt; ?> eContent2">
                <?= $this->get_translation('formitem_filecountindesc'); ?>
            </td>
            <td class="eTableLine<?= $alt; ?> eContent2">
                <?= $this->integrityCheckResult['descriptionFileCount']; ?>
            </td>
        </tr>
        <?php $alt = abs($alt-1); ?>
        <tr>
            <td class="eTableLine<?= $alt; ?> eContent2">
                <?= $this->get_translation('formitem_filecountlocal'); ?>
            </td>
            <td class="eTableLine<?= $alt; ?> eContent2">
                <?= $this->integrityCheckResult['localFileCount']; ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0" colspan="2">
                &nbsp;
            </td>
        </tr>
        <tr>
            <td class="eTableHeader" colspan="2">
                <?= $this->get_translation('formtitle_errors'); ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_errorextrafiles'); ?>
            </td>
            <td class="eTableLine1<?= ($this->integrityCheckResult['errorsOnExtraFiles'] > 0 ? ' eContent2':''); ?>">
                <?= $this->integrityCheckResult['errorsOnExtraFiles']; ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_errormissingfiles'); ?>
            </td>
            <td class="eTableLine0<?= ($this->integrityCheckResult['errorsOnMissingFiles'] > 0 ? ' eContent2 error':''); ?>">
                <?= $this->integrityCheckResult['errorsOnMissingFiles']; ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_errorchecksum'); ?>
            </td>
            <td class="eTableLine1<?= ($this->integrityCheckResult['errorsOnChecksum'] > 0 ? ' eContent2 error':''); ?>">
                <?= $this->integrityCheckResult['errorsOnChecksum']; ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_errormime'); ?>
            </td>
            <td class="eTableLine0<?= ($this->integrityCheckResult['errorsOnMime'] > 0 ? ' eContent2':''); ?>">
                <?= $this->integrityCheckResult['errorsOnMime']; ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine1 eContent2">
                <?= $this->get_translation('formitem_errorheader'); ?>
            </td>
            <td class="eTableLine1<?= ($this->integrityCheckResult['errorsOnHeader'] > 0 ? ' eContent2 error':''); ?>">
                <?= $this->integrityCheckResult['errorsOnHeader']; ?>
            </td>
        </tr>
        <tr>
            <td class="eTableLine0 eContent2">
                <?= $this->get_translation('formitem_errorversion'); ?>
            </td>
            <td class="eTableLine0<?= ($this->integrityCheckResult['errorsOnVersion'] > 0 ? ' eContent2 error':''); ?>">
                <?= $this->integrityCheckResult['errorsOnVersion']; ?>
            </td>
        </tr>
    </table>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<div class="eTitle3">
    <?= $this->get_translation('formtitle_integritydetails'); ?>
</div>
<div style="max-height:400px; overflow-y:auto;">
    <?php $alt = 0; ?>
    <?php foreach ($this->integrityCheckResult['files'] as $filePath => $file) : ?>
        <?php if ($file['status'] == 'checked') continue; ?>
        <div class="eTableLine<?= $alt; ?> eContent2<?= (count(array_intersect(array('missing', 'checksum', 'header', 'version'), $file['errors'])) > 0 ? ' error' : ''); ?>">
            <?= $filePath; ?>
        </div>
	<div class="eTableLine<?=$alt; ?>">
	    <ul>
            <?php foreach ($file['errors'] as $error) : ?>
	        <?php if ($error == 'extra') : ?>
		<li>
		    <?= $this->get_translation('integrity_error_extra'); ?>
		</li>
	        <?php elseif ($error == 'missing') : ?>
		<li>
		    <?= $this->get_translation('integrity_error_missing'); ?>
		</li>
        	<?php elseif ($error == 'checksum') : ?>
		<li>
		    <?= $this->get_translation('integrity_error_checksum', array($file['checksum'], $file['checksumLocal'])); ?>
		</li>
        	<?php elseif ($error == 'mime') : ?>
		<li>
		    <?= $this->get_translation('integrity_error_mime', array($file['mime'], $file['mimeLocal'])); ?>
		</li>
        	<?php elseif ($error == 'header') : ?>
		<li>
		    <?= $this->get_translation('integrity_error_header'); ?>
		</li>
         	<?php elseif ($error == 'version') : ?>
		<li>
		    <?= $this->get_translation('integrity_error_version', array($file['version'], $file['versionLocal'])); ?>
		</li>
        	<?php endif; ?>

            <?php endforeach; ?>
	    </ul>
	</div>
        <?php $alt = abs($alt-1); ?>
    <?php endforeach; ?>
</div>
<?= $this->theme->get_boxContent2Footer(); ?>
<?= $this->theme->get_boxButtonsBar($this->buttons); ?>
<?= $this->theme->get_boxFooter(); ?>
