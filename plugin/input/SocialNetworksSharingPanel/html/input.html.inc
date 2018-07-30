<?php
/**
 * @brief SocialNetworksSharingPanel Input share mode layout
 * @details Plugin / Input layout
 * @file plugin/input/SocialNetworksSharingPanel/html/input.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Nov 2009
 * @date Modification: Jul 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
$n = $this->dparams['networks'][1];
?>
<div class="<?=$this->dparams['block_class']?>">
<?php if ($this->dparams['text_class']!='') : ?>
<span class="<?=$this->dparams['text_class']?>">
<?=$this->dparams['text'];?>
</span>
<?php else : ?>
<?=$this->dparams['text'];?>
<?php endif; ?>

<?php foreach ($this->networks as $name => $network ) : ?>
<?php if ($network['share'] == 1 and $this->config->vars['share_'.$name] == 1) : ?>
<a <?=$this->get_networkHrefLink($name)?> <?=$this->get_networkOnclickLink($name)?> class="img" target="_blank" rel="noopener">
<img src="<?=$this->get_networkIconURL($name, 'share');?>"
   alt="<?=$network['title']?>" title="<?=$network['title']?>" style="vertical-align:bottom; margin:0 2px; border:0;" />
</a>
<?php if (--$n > 0 ) : ?>
<?=$this->dparams['separator'];?>
<?php endif; ?>
<?php endif; ?>
<?php endforeach; ?>

<?php if ($this->dparams['enable_poppanel']==1 and $this->dparams['networks'][2] > 0 ) : ?>
<?php $plus = $this->theme->get_pictURL('plus', 12, 'std'); ?>
<?php $plus_ = $this->theme->get_pictURL('plus', 12, 'ovr'); ?>
<?php $close = $this->theme->get_pictURL('cross', 12, 'std'); ?>
<?php $close_ = $this->theme->get_pictURL('cross', 12, 'ovr'); ?>

<?=$this->dparams['separator'];?>

<a href="javascript:snsp.open_panel(<?=$this->currentIndex?>);">
<img src="<?=$plus?>"
    id="snsButton<?=$this->currentIndex?>"
    style="vertical-align:bottom; margin:0 4px; border:0;"
    alt=""
    title=""
    onmouseover="this.src='<?=$plus_?>';"
    onmouseout="this.src='<?=$plus?>';" />
</a>

<?php $closeButton = '<a href="javascript:snsp.close_panel('.$this->currentIndex.');">
<img src="'.$close.'"
    style="margin:2px; float:right; border:0;"
    alt=""
    title=""
    onmouseover="this.src=\''.$close_.'\';"
    onmouseout="this.src=\''.$close.'\';" />
</a>'; ?>
<?php endif; ?>

<?php if ($this->config->vars['like_facebook'] == 1) : ?>
<?=$this->dparams['separator'];?>
&nbsp;
<div class="fb-like" data-href="<?=$this->dparams['link'];?>" data-layout="<?=$this->config->vars['like_facebookLayout'];?>" data-action="<?=$this->config->vars['like_facebookAction'];?>" data-size="<?=$this->config->vars['like_facebookSize'];?>" data-show-faces="false" data-share="false"></div>
<?php endif; ?>

<?php if ($this->dparams['enable_poppanel']==1 and $this->dparams['networks'][2] > 0 ) : ?>
<div id="snsPanel<?=$this->currentIndex?>" style="display:none; width:100px; position:absolute;">
<?=$this->theme->get_boxHeader('width:100%;');?>
<?=$this->theme->get_boxTitleBar($closeButton . $this->dparams['text']);?>
<?=$this->theme->get_boxContent2Header();?>

<?php foreach ($this->networks as $name => $network) : ?>
<?php if ($network['share'] == 1 and $this->config->vars['share_'.$network] == 2) : ?>
<a <?=$this->get_networkHrefLink($name)?> <?=$this->get_networkOnclickLink($name)?> style="font-size:0;" target="_blank" rel="noopener">
<img src="<?=$this->get_fileURL('img/shareIcons/'.$name.'.gif');?>"
   alt="<?=$network['title']?>" title="<?=$network['title']?>" style="vertical-align:bottom; margin:4px; border:0;" />
</a>
<?php endif; ?>
<?php endforeach; ?>

<?=$this->theme->get_boxContent2Footer(); ?>
<?=$this->theme->get_boxFooter(); ?>
</div>
<?php else : ?>
</div>
<?php endif; ?>
<?php
/**
 * @endcond Exclude
 */
?>
