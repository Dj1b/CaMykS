<?php
/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Input Engine
 * Create Date		: Jul 2008
 * Last Modif Date	: Nov 2011
 * History : 
 * * 08-07-01 : Initial files
 * * 09-07-31 : Bugfixes
 * * 11-11-16 : Add path_termination params
 * 
 * BreadCrumbs input : Display current page full path
 */

class BreadCrumbs extends Input {
  /* variables */
  var $path;
  var $params;
  var $dparams;

  /* 
   * constructor
   * @param string $path_type
   */
  function BreadCrumbs ( $path_type ) {
    parent::Input('BreadCrumbs', $path_type);
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
   * @param array $params
   * @return void
   * @access public
   */
  function initialise($params=array()) {
    global $camyks;
    
    /* check if Admin_ContentPage exists */
    if (!isset( $camyks->modules['Admin_ContentPage']))
      return;
    
    /* check params */
    $this->check_params($params);
    
    /* get pages */
    $this->pages = $camyks->modules['Admin_ContentPage']->get_sitePages();
    
    /* get current page */
    $currentPage = $camyks->contentPage->id;
    
    /* get path */
    $this->path = array();
    while ( isset($this->pages[$currentPage]) ) {
      $page = &$this->pages[$currentPage];
      if ( $page->active == 1 ) {
        $p = array('title'=> $page->shorttitle!=''?$page->shorttitle:($page->title!=''?$page->title:$page->name),
		   'url'=>$page->get_siteLink());
      } elseif ( $page->id !=0 and ($page->shorttitle != '' or $page->title != '' )) {
	$p = array('title'=> $page->shorttitle!=''?$page->shorttitle:$page->title,
		   'url'=>false);
      } else {
	break;
       }
      array_unshift($this->path, $p);
      $currentPage = $page->parent_id;      
    }

    /* check path termination */
    if (is_array($this->params['path_termination']) and count($this->params['path_termination']) > 0)
        $this->path = array_merge($this->path, $this->params['path_termination']);

    
    /* Input generic initialization */
    parent::initialise();
  }
  
  /* specific tool methods */
  
  /*
   * check params
   * @param array $params
   * @return void
   * @access private
   */
  function check_params($params=array()) {
    /* build default params list */
    $this->dParams = array('separator' => ' &gt; ',
			   'container_class'=>'',
			   'link_class'=>'eLink1',
			   'text_class'=>'eContent1',
			   'path_termination'=>array());
    /* build internal params list */
    $this->params = array_merge($this->dParams, $params);
  }
}
?>