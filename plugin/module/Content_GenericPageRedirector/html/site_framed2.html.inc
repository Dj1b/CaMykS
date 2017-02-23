<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a2
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Sep 2009
 * Last Modif Date	: Sep 2009
 *
 * Content_GenericPageRedirector Module site layout : framed2
*/
global $camyks;

if ( $this->pritem->vars['delay'] > 0 ) {
  echo $this->theme->get_boxHeader('width:100%;');
  echo $this->theme->get_boxContent2Header();
  if (file_exists( $this->pritem->vars['message']))
    include ( $this->pritem->vars['message'] );
  echo $this->theme->get_boxContent2Footer();
  echo $this->theme->get_boxFooter();
}
?>