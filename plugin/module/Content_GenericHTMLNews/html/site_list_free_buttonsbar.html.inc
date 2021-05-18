<?php
/**
 * @brief Content_GenericHTMLNews Module site site buttons bar sub layout for free layouts.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Dec 2007
 * @date Modification: May 2021
 * @copyright 2007 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
?>
<?php if (isset($this->buttons)) : ?>
<div style="margin-top:8px; padding-top:4px; border-top:solid 1px #DEDEDE;">
    <table cellspacing="0" cellpadding="0" border="0" style="width:100%">
        <tr>
            <td style="width:33%; text-align:left;">
                <?php if ($this->buttons[0]['link'] != '') : ?>
                    <a href="<?= $this->buttons[0]['link']; ?>" class="eLink2">
                        <?= $this->buttons[0]['title']; ?>
                    </a>
                <?php else : ?>
                    <?= $this->buttons[0]['title']; ?>
                <?php endif; ?>
            </td>

            <td class="content2" style="width:34%; text-align:center;">
                <?= $this->buttons[1]['title']; ?>
            </td>

            <td style="width:33%; text-align:right;">
                <?php if ($this->buttons[2]['link'] != '') : ?>
                    <a href="<?= $this->buttons[2]['link']; ?>" class="eLink2">
                        <?= $this->buttons[2]['title']; ?>
                    </a>
                <?php else : ?>
                    <?= $this->buttons[2]['title']; ?>
                <?php endif; ?>
            </td>
        </tr>
    </table>
</div>
<?php endif; ?>
