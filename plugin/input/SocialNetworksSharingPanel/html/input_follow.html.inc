<?php
/**
 * @brief SocialNetworksSharingPanel Input follow mode layout
 * @details Plugin / Input layout
 * @file plugin/input/SocialNetworksSharingPanel/html/input_follow.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jan 2018
 * @date Modification: Jul 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
?>
<div class="SNSP follow<?=($this->params['follow_insertion'] == 1 ? ' '.$this->params['follow_location']:'');?>">
  <?php foreach ($this->networks as $name => $network) : ?>
    <?php if ($network['follow'] == 1 and $this->params['follow_'.$name] != '') : ?>
      <a href="<?=$this->config->vars['follow_'.$name];?>" class="img" target="_blank" rel="noopener">
        <img src="<?=$this->get_networkIconURL($name, 'follow');?>" alt="<?=$this->get_translation('followuson', $network['title']);?>" title="<?=$this->get_translation('followuson', $network['title']);?>" class="networkIcon" />
      </a>
    <?php endif; ?>
  <?php endforeach; ?>
</div>
<?php
/**
 * @endcond Exclude
 */
?>

