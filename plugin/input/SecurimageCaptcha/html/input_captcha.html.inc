<?php
/**
 * @brief SecurimageCaptcha Input layout
 * @details Plugin / Input layout
 * @file plugin/input/SecurimageCaptcha/html/input_captcha.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jul 2009
 * @date Modification: Jul 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
$imgURL = 'request.php?input='.$this->name.'&amp;'.md5(uniqid(time()));
?>
<img src="<?=$imgURL?>" alt="" border="0" />
<?php
/**
 * @endcond Exclude
 */
?>
