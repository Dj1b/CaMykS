<?php
/**
 * @brief LimonetikPayment Input error layout
 * @details Plugin / Input layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Oct 2020
 * @date Modification: Oct 2020
 * @copyright 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<p class="eTitle3">
    <?= $this->get_translation('anerroroccured'); ?>
</p>

<p class="eTitle4">
    <?= $this->_lastErrorMsg; ?>
</p>

<p class="eContent1">
    <?= $this->_lastErrorDetails; ?>
</p>

<p class="eContent1">
    <?= $camyks->theme->get_button(array(
        'title' => $this->get_translation('back'),
        'url'   => $this->params['backURL_Cancel'],
    )); ?>
</p>
