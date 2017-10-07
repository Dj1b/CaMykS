<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0
 * Object Type      : Plugin / Input Layout
 * Create Date		: Nov 2009
 * Last Modif Date	: Oct 2017
 * 
 * SocialNetworksSharingPanel input layout
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
<?php if ($this->dparams['allow_'.$name]==1) : ?>
<a <?=$this->get_networkHrefLink($name)?> <?=$this->get_networkOnclickLink($name)?> style="font-size:0;" target="_blank">
<img src="<?=$this->get_fileURL('img/icons/'.$name.'.gif');?>" 
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

<?php if ($this->dparams['allow_fb:like']['default'] == 1) : ?>
&nbsp;
<fb:like href="<?=$this->dparams['link'];?>" <?=$this->dparams['allow_fb:like']['layout'] == 'button_count'?' layout="button_count"':''?>></fb:like>
<div id="fb-root"></div>
<?php endif; ?>

<?php if ($this->dparams['allow_google:plus']['default'] == 1) : ?>
&nbsp;
<g:plusone size="<?=$this->dparams['allow_google:plus']['size']?>" annotation="<?=$this->dparams['allow_google:plus']['annotation']?>"></g:plusone>
<?php endif; ?>


<?php if ($this->dparams['enable_poppanel']==1 and $this->dparams['networks'][2] > 0 ) : ?>
<div id="snsPanel<?=$this->currentIndex?>" style="display:none; width:100px; position:absolute;">
<?=$this->theme->get_boxHeader('width:100%;');?>
<?=$this->theme->get_boxTitleBar($closeButton . $this->dparams['text']);?>
<?=$this->theme->get_boxContent2Header();?>

<?php foreach ($this->networks as $name => $network ) : ?>
<?php if ($this->dparams['allow_'.$name]==2) : ?>
<a <?=$this->get_networkHrefLink($name)?> <?=$this->get_networkOnclickLink($name)?> style="font-size:0;" target="_blank">
<img src="<?=$this->get_fileURL('img/icons/'.$name.'.gif');?>" 
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
