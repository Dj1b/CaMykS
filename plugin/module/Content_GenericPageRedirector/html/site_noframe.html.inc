<?php
/**
 * @brief Content_GenericPageRedirector Module site, no frame, layout.
 * @details Plugin / Module layout
 * @file plugin/module/Content_GenericPageRedirector/html/site_noframe.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Sep 2009
 * @date Modification: Jan 2019
 * @copyright 2009 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

if ($this->pritem->vars['delay'] > 0) {
  echo '<h1 class="eTitle1">'."\n";
  echo $camyks->contentPage->get_longTitleDisplay()."\n";
  echo '</h1>'."\n\n";

  if (file_exists($this->pritem->vars['message']))
    include($this->pritem->vars['message']);
}
?>
