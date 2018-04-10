<?php
/**
 * @brief Module help layout file
 * @details Engine / Generic Layout
 * @file engine/data/html/help_module_generic.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Mar 2007
 * @date Modification: Apr 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
?>
<div>
    <div style="float:left; margin-top:4px;">
        <img src="<?=$this->get_fileURL('img/icon64.gif', true, 'cdata/img/module/default_icon64.gif')?>" width="64" height="64" border="0" title="<?=$this->title?>" alt="<?=$camyks->get_translation('icon');?>" />
    </div>
    <div style="margin-left:70px;">
        <h1 class="eTitle1">
            <?=$this->title?>
        </h1>
        <?php if ($this->version != '') : ?>
            <p class="eContent1">
                <span class="eContent2">
                    <?=$camyks->get_translation('formitem_version');?>
                </span>
                <?=$this->version?>
            </p>
        <?php endif; ?>

        <?php if ($this->plugin_package != '') : ?>
            <p class="eContent1">
                <span class="eContent2">
                    <?=$camyks->get_translation('formitem_package');?>
                </span>
            <?=$this->plugin_package?>
            </p>
        <?php endif; ?>

        <?php if ($this->author_name != '' or $this->author_group != '') : ?>
            <p class="eContent1">
                <span class="eContent2">
                    <?=$camyks->get_translation('formitem_author');?>
                </span>
                <?php if ($this->author_name != '' ) : ?>
                    <?php if ($this->author_mail != '') : ?>
                        <a href="mailto:<?=$this->author_mail?>" class="eLink1">
                            <?=$this->author_name?>
                        </a>
                    <?php else :?>
                        <?=$this->author_name?>
                    <?php endif; ?>
                    <?php if ($this->author_group != '') : ?>
                        (<?=$this->author_group?>)
                    <?php endif; ?>
                <?php else : ?>
                    <?=$this->author_group?>
                <?php endif; ?>
            </p>
        <?php endif; ?>
    </div>
</div>

<h2 class="eTitle2">
    <?= $this->get_translation('desc')?>
</h2>

<p class="eContent1">
    &nbsp;
</p>

<?php if (isset($this->help['main']['html'])) : ?>
    <?php $this->load_file('help/'.$camyks->current_language.'/'.$this->help['main']['html']);?>
<?php endif; ?>
