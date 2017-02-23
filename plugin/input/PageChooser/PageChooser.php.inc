<?php
/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Input Engine
 * Create Date		: Jun 2007
 * Last Modif Date	: Jun 2007
 * History : 
 * * 07-06-01 : Initial files
 * 
 * PageChooser input : Open a request popup windows with Admin_ContentPage in request mode
 */

class PageChooser extends Input {

  /* 
   * constructor
   * @param string $path_type
   */
  function PageChooser ( $path_type ) {
    parent::Input('PageChooser', $path_type);
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Default';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
  }
  
  /* overwrite input methods */

  /*
   * initialise input
   * @param string $mode
   * @param string $page
   * @param string $callback
   * @return void
   * @access public
   */
  function initialise ( $mode='pageid', $page='1', $callback='' ) {
    global $camyks;
    /* check if Admin_ContentPage exists */
    if ( isset( $camyks->modules['Admin_ContentPage']) ) {
      $link = $camyks->site_conf['url'].'/request.php?module=Admin_ContentPage';
      $this->add_JSFile('pagechooser.js');
      $this->add_JSScript('pc = new PageChooser("'.$mode.'", "'.$callback.'", "'.$link.'");');
    }
    
    /* Input generic initialization */
    parent::initialise();
  }
  
  /* specific methods */

  /*
   * return input object link
   * @param mixed $page_value
   * @return string
   * @access private
   */
  function get_link ( $page_value  ) {
    return 'pc.open('.$page_value.');';
  }
}
?>