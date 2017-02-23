<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Input Engine
 * Creation Date    : Dec 2007
 * Last Modif Date	: Apr 2013
 * History : 
 * * 07-12-16 : Initial File
 * * 10-03-26 : Add optional linked image
 * * 13-04-29 : Corrections and enhancements
 * 
 * Generic RSS Feed : return a RSS Feed XML content from a config and items
 */

class GenericRSSFeed extends Input {
  /* variables */
  var $items;
  var $config;

  /*
   * constructor
   * @param string $path_type
   */
  function GenericRSSFeed ( $path_type ) {
    parent::Input('GenericRSSFeed', $path_type);
    /* set plugin version */ 
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Generic';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
  }
  
  /* overwrite input methods */

  /*
   * initialise input
   * @param array $config
   * @param array $items
   * @return void
   * @access public
   */
  function initialise ( $config=array(), $items=array() ) {
    global $camyks;
    $this->config = $config;
    $this->items = $items;
  }
  
  /*
   * display input
   * @return void
   * @access public
   */
  function display ( ) {
    header("Content-type: application/atom+xml; charset=UTF-8");
    echo '<'.'?xml version="1.0" encoding="UTF-8"?>'."\n";
    echo '<rss version="2.0" xmlns:atom="http://www.w3.org/2005/Atom">'."\n";
    echo '<channel>'."\n";
    /* mandatory config data */
    echo '<title>'.$this->config['title'].'</title>'."\n";
    echo '<link>'.$this->config['link'].'</link>'."\n";
    echo '<description><![CDATA['.$this->config['description'].']]></description>'."\n";
    /* optional config data */
    if ( isset ( $this->config['language'] ) )
      echo '<language>'.$this->config['language'].'</language>'."\n";
    if ( isset( $this->config['copyright'] ) ) 
      echo '<copyright>'.$this->config['copyright'].'</copyright>'."\n";
    if ( isset( $this->config['webMaster'] ) ) 
      echo '<webMaster>'.$this->config['webMaster'].'</webMaster>'."\n";
    if ( isset( $this->config['lastBuildDate'] ) )
      echo '<lastBuildDate>'.$this->config['lastBuildDate'].'</lastBuildDate>'."\n";
    if ( isset( $this->config['generator'] ) )
      echo '<generator>'.$this->config['rssgenerator'].'</generator>'."\n";
    else
      echo '<generator>'.$this->get_translation('rssgenerator').'</generator>'."\n";
    /* check for linked image */
    if ( isset($this->config['image']) and is_array($this->config['image'])) {
      echo '<image>'."\n";
      echo '<url>'.$this->config['image']['url'].'</url>'."\n";
      if (isset( $this->config['image']['title']))
        echo '<title><![CDATA['.$this->config['image']['title'].']]></title>'."\n";
      if (isset( $this->config['image']['width']))
        echo '<width>'.$this->config['image']['width'].'</width>'."\n";
      if (isset( $this->config['image']['height']))
        echo '<height>'.$this->config['image']['height'].'</height>'."\n";
      if (isset( $this->config['image']['link']))
        echo '<link>'.$this->config['image']['link'].'</link>'."\n";
      echo '</image>'."\n";
    }
    
    /* add items */
    foreach ( $this->items as $item ) {
      echo '<item>'."\n";
      /* mandatory item data */
      echo '<title>'.$item['title'].'</title>'."\n";
      echo '<link>'.$item['link'].'</link>'."\n";
      echo '<description><![CDATA['.$item['description'].']]></description>'."\n";
      /* optional item data */
      if ( isset( $item['author'] ) )
	echo '<author>'.$item['author'].'</author>'."\n";
      if ( isset( $item['date'] ) )
	echo '<pubDate>'.date('r', $item['date']).'</pubDate>'."\n";
      if ( isset( $item['isPermalink'] ) )
	echo '<guid isPermaLink="'.$item['isPermalink'].'">'.$item['link'].'</guid>'."\n";
      echo '</item>'."\n";
    }
    echo '</channel>'."\n";
    echo '</rss>'."\n";
    die();
  }
}
?>