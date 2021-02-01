<?php
/**
 * @brief Admin_GenericContactFormManager Module email notification layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Nov 2010
 * @date Modification: Jan 2021
 * @copyright 2010 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;
?>
<p>
    <?= $this->admin->get_nameDisplay(); ?>,
</p>
<p>
    <?= $this->get_translation('notification_emailcontent1', array(
        $camyks->get_confValue('url'),
        $camyks->get_confValue('title'),
    ));?>
</p>
<p>
    <?= $this->get_translation('notification_emailsign'); ?><br/>
    <?= $camyks->get_confValue('url'); ?>
</p>
