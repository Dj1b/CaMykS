<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a2
 * Object Version	: 1.0
 * Object Type		: Plugin / Module Layout
 * Create Date		: Sep 2009
 * Last Modif Date	: Sep 2009
 *
 * Content_GenericPageRedirector Module site layout : no frame
*/
global $camyks;

if ( $this->pritem->vars['delay'] > 0 ) {
  echo '<h1 class="eTitle1">'."\n";
  echo $camyks->contentPage->title."\n";
  echo '</h1>'."\n\n";

  if (file_exists( $this->pritem->vars['message']))
    include ( $this->pritem->vars['message'] );
}
?>