<?php
/**
 * @brief Admin_Statistics Module admin options settings sublayout
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Sep 2020
 * @date Modification: Sep 2020
 * @copyright 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;
?>
<table cellspacing="0" style="width:100%;">
    <tr>
        <td class="eTableHeader" colspan="2">
            <?= $this->get_translation('valueselection'); ?>
        </td>
    </tr>
    <tr>
        <td class="eTableLine0 eContent2">
            <input type="radio" name="displaymode" value="0" <?= $this->config->vars['displaymode'] == 0 ? ' checked="checked"' : ''; ?> id="displaymode0" />
        </td>
        <td class="eTableLine0 eContent1">
            <label for="displaymode0">
                <?= $camyks->get_translation('today'); ?>
            </label>
        </td>
    </tr>
    <tr>
        <td class="eTableLine1">
            <input type="radio" name="displaymode" value="1" <?= $this->config->vars['displaymode'] == 1 ? ' checked="checked"' : ''; ?> id="displaymode1" />
        </td>
        <td class="eTableLine1 eContent1">
            <label for="displaymode1">
                <?= $camyks->get_translation('yesterday'); ?>
            </label>
        </td>
    </tr>
    <tr>
        <td class="eTableLine0">
            <input type="radio" name="displaymode" value="2" <?= $this->config->vars['displaymode'] == 2 ? ' checked="checked"' : ''; ?> id="displaymode2" />
        </td>
        <td class="eTableLine0 eContent1">
            <label for="displaymode2">
                <?= $camyks->get_translation('thisweek'); ?>
            </label>
        </td>
    </tr>
    <tr>
        <td class="eTableLine1">
            <input type="radio" name="displaymode" value="3" <?= $this->config->vars['displaymode'] == 3 ? ' checked="checked"' : ''; ?> id="displaymode3" />
        </td>
        <td class="eTableLine1 eContent1">
            <label for="displaymode3">
                <?= $camyks->get_translation('lastweek'); ?>
            </label>
        </td>
    </tr>
    <tr>
        <td class="eTableLine0">
            <input type="radio" name="displaymode" value="9" <?= $this->config->vars['displaymode'] == 9 ? ' checked="checked"' : ''; ?> id="displaymode9" />
        </td>
        <td class="eTableLine0 eContent1">
            <label for="displaymode9">
                <?= $camyks->get_translation('thismonth'); ?>
            </label>
        </td>
    </tr>
    <tr>
        <td class="eTableLine1">
            <input type="radio" name="displaymode" value="10" <?= $this->config->vars['displaymode'] == 10 ? ' checked="checked"' : ''; ?> id="displaymode10" />
        </td>
        <td class="eTableLine1 eContent1">
            <label for="displaymode10">
                <?= $camyks->get_translation('lastmonth'); ?>
            </label>
        </td>
    </tr>
    <tr>
        <td class="eTableLine0">
            <input type="radio" name="displaymode" value="4" <?= $this->config->vars['displaymode'] == 4 ? ' checked="checked"' : ''; ?> id="displaymode4" />
        </td>
        <td class="eTableLine0 eContent1">
            <label for="displaymode4">
                <?= $camyks->get_translation('thisyear'); ?>
            </label>
        </td>
    </tr>
    <tr>
        <td class="eTableLine1">
            <input type="radio" name="displaymode" value="5" <?= $this->config->vars['displaymode'] == 5 ? ' checked="checked"' : ''; ?> id="displaymode5" />
        </td>
        <td class="eTableLine1 eContent1">
            <label for="displaymode5">
                <?= $camyks->get_translation('lastyear'); ?>
            </label>
        </td>
    </tr>
    <tr>
        <td class="eTableLine0">
            <input type="radio" name="displaymode" value="6" <?= $this->config->vars['displaymode']==6?' checked="checked"':''; ?> id="displaymode6" />
        </td>
        <td class="eTableLine0 eContent1">
            <?= $camyks->get_translation('dayx', $this->form->display_dateInput($this->config->vars['displayday'], 'displayday', array('day', 'month', 'year'), $this->get_dateInputButtons())); ?>
        </td>
    </tr>
    <tr>
        <td class="eTableLine1">
            <input type="radio" name="displaymode" value="7" <?= $this->config->vars['displaymode']==7?' checked="checked"':''; ?> id="displaymode7" />
        </td>
        <td class="eTableLine1 eContent1">
            <?= $camyks->get_translation('fromx', $this->form->display_dateInput($this->config->vars['displayfrom'], 'displayfrom', array('day', 'month', 'year'), $this->get_dateInputButtons())); ?>
        </td>
    </tr>
    <tr>
        <td class="eTableLine1">
            &nbsp;
        </td>
        <td class="eTableLine1 eContent1">
            <?= $camyks->get_translation('toy', $this->form->display_dateInput($this->config->vars['displayto'], 'displayto', array('day', 'month', 'year'), $this->get_dateInputButtons())); ?>
        </td>
    </tr>

    <?php if ($this->config->optionSettingsDisplay == 1) : ?>
    <tr>
        <td class="eTableLine0" colspan="2">
            &nbsp;
        </td>
    </tr>
    <tr>
        <td class="eTableHeader" colspan="2">
            <?= $this->get_translation('value3selection'); ?>
        </td>
    </tr>
    <tr>
        <td class="eTableLine0">
            &nbsp;
        </td>
        <td class="eTableLine0 eContent1">
            <?= $this->get_translation('thefirstxstats', '<input type="text" name="displaycount" value="'.$this->config->vars['displaycount'].'" maxlength="3" size="4"/>'); ?>
        </td>
    </tr>
    <?php elseif ($this->config->optionSettingsDisplay == 2) : ?>
    <tr>
        <td class="eTableLine0">
            <input type="radio" name="displaymode" value="8" <?= $this->config->vars['displaymode']==8?' checked="checked"':''; ?> id="displaymode8" />
        </td>
        <td class="eTableLine0 eContent1">
            <?= $this->get_translation('thelastxstats', '<input type="text" name="displaycount" value="'.$this->config->vars['displaycount'].'" maxlength="3" size="4" /></input>'); ?>
        </td>
    </tr>
    <?php endif; ?>

</table>

<?php
/**
 * @endcond Exclude
 */
?>
