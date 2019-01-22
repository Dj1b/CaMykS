<?php
/**
 * @brief Content_GenericPageRedirector Module site, framed 2, layout.
 * @details Plugin / Module layout
 * @file plugin/module/Content_GenericPageRedirector/html/site_framed2.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Sep 2009
 * @date Modification: Jan 2019
 * @copyright 2009 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
if ($this->pritem->vars['delay'] > 0) {
    echo $this->theme->get_boxHeader('width:100%;');
    echo $this->theme->get_boxContent2Header();
    if (file_exists($this->pritem->vars['message']))
        include($this->pritem->vars['message']);
    echo $this->theme->get_boxContent2Footer();
    echo $this->theme->get_boxFooter();
}
?>
