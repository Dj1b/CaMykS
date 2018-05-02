<?php
/**
 * @brief ColorPicker Input main layout
 * @details Plugin / Input Layout
 * @file plugin/input/ColorPicker/html/input.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: May 2007
 * @date Modification: Apr 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
?>
<input type="hidden" name="<?=$this->inputname?>" value="<?=$this->color?>" id="colorpicker_input<?=$this->inputname?>" />
<div style="font-size:0;">
    <div style="display:inline-block; background-color:#<?=$this->color?>; border:solid 1px black; width:30px; height:16px; margin-right:4px; cursor:pointer;"
        <?php if ($this->mode == 'popup') : ?>
            onclick="colorpicker_open('<?=$this->inputname?>', '<?=$this->color?>', '<?=$this->config?>')" 
        <?php elseif ($this->mode == 'modal') : ?>
            onclick="colorpicker_show('<?=$this->cp_name?>', '<?=$this->inputname?>', '<?=$this->color?>')" 
        <?php endif; ?>
        id="colorpicker_obj<?=$this->inputname?>">
        &nbsp;
    </div>
    <div id="colorpicker_txt<?=$this->inputname?>" class="eContent1" style="display:inline-block; width:60px;">
        #<?=$this->color?> 
    </div>
</div>

<?php if ($this->mode == 'modal' and $this->modaldisplay == false) : ?>
<?php $this->modaldisplay = true; ?>
<?php $this->load_file('html/modal.html.inc');?>
<?php endif; ?>
<?php 
/**
 * @endcond Exclude
 */
?>