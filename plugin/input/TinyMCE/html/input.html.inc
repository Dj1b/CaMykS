<?php
/**
 * @brief TinyMCE Input layout
 * @details Plugin / Input layout
 * @file plugin/input/TinyMCE/html/input.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Mar 2007
 * @date Modification: Jul 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
?>
<textarea name="<?=$this->ta_name;?>" id="<?=$this->ta_name;?>" style="width:<?=$this->ta_sizex?>;height:<?=$this->ta_sizey?>;" cols="40" rows="8"><?php if ( $this->contentType=='text') : ?>
<?= $this->contentValue; ?>
<?php elseif ($this->contentType=='file' and file_exists($this->contentValue)) : ?>
<?php require_once $this->contentValue; ?>
<?php endif; ?>
</textarea>
<?php
/**
 * @endcond Exclude
 */
?>
