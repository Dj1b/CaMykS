<?php
/**
 * @brief GoogleAnalytics Input layout
 * @details Plugin / Input layout
 * @file plugin/input/GoogleAnalytics/html/input.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Sep 2018
 * @date Modification: Sep 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
?>
<!-- Global site tag (gtag.js) - Google Analytics -->
<script async src="https://www.googletagmanager.com/gtag/js?id=<?= $this->get_configValue('trackingId'); ?>"></script>
<script>
  window.dataLayer = window.dataLayer || [];
  function gtag(){dataLayer.push(arguments);}
  gtag('js', new Date());

  <?php foreach($this->extraData as $extra) : ?>
<?= $this->display_extra($extra, false); ?>
  <?php endforeach; ?>
</script>
<?php
/**
 * @endcond Exclude
 */
?>
