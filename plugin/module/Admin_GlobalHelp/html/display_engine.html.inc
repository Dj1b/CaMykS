<?php
/**
 * @brief Admin_GlobalHelp Module admin display engine help layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Fev 2007
 * @date Modification: Jan 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;
?>
<?= $this->theme->get_boxHeader(array('class'=>'adminEditorModule')); ?>
<?= $this->theme->get_boxTitleBar($this->title); ?>
<?= $this->theme->get_boxContent2Header(); ?>
<div class="adminContentPanel">
	<table cellspacing="0" cellpadding="0" border="0" style="width:100%">
		<tr>
			<?php if (count($this->help) > 1) : ?>
  				<td class="adminhelplist">
    				<table cellspacing="0" cellpadding="0" border="0" style="width:100%">
    					<?php foreach ($this->help as $i => $v) : ?>
    						<tr>
      							<td id="<?= $this->name; ?>_menu<?= $i; ?>"  class="<?= $camyks->theme->parts['boxTabCSSStandart']?>"
      	  								onmouseover="<?=strtolower($this->name); ?>_helpObject.mouseover('<?= $i; ?>');"
      	  								onmouseout="<?=strtolower($this->name); ?>_helpObject.mouseout('<?= $i; ?>');"
      	  								onclick="<?=strtolower($this->name); ?>_helpObject.mouseclick('<?= $i; ?>');">
      	  							<?= $v['title']?>
      							</td>
    						</tr>
    					<?php endforeach; ?>
    				</table>
  				</td>
			<?php endif; ?>
  			<td class="adminhelptext">
  				<?php foreach ($this->help as $i => $v) : ?>
  					<div id="<?= $this->name; ?>_page<?= $i; ?>" style="display:none;padding:0px 8px;">
  						<?php require_once ($this->help_path.'/'.$v['html']); ?>
					</div>
  				<?php endforeach; ?>
  			</td>
  		</tr>
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