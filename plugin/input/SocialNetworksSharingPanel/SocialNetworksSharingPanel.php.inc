<?php
/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0b1
 * Object Version       : 1.0
 * Object Type          : Plugin / Input Engine
 * Create Date		: Nov 2009
 * Last Modif Date	: Nov 2009
 * History : 
 * * 09-11-18 : Initial files
 * 
 * Display all social network sharing links
 */

class SocialNetworksSharingPanel extends Input {
  /* initial params */
  var $iparams;
  /* display params */
  var $dparams;
  /* current index for multiple display */
  var $currentIndex;

  /* 
   * constructor
   * @param string $path_type
   */
  function SocialNetworksSharingPanel($path_type) {
    parent::Input('SocialNetworksSharingPanel', $path_type);
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

    /* initialise index */
    $this->currentIndex = 0;

    /* load networks */
    $this->initialise_networkList();
    
    /* set initial params */
    $this->iparams = array('text'=>'',
			   'block_class'=>'',
			   'text_class'=>'',
			   'separator'=>'&#124;',
			   'title'=>'',
			   'link'=>'',
			   'shortlink'=>'',
			   'summary'=>'',
			   'image'=>'',
			   'type'=>'',
			   'sitename'=>$camyks->get_confValue('site_title'),
			   'enable_poppanel'=>1,
			   'theme'=>$camyks->get_confValue('site_default_theme'),
			   'include_ogmetas'=>0,
			   'networks'=>array(0, 0, 0),
			   'locale'=>$camyks->current_language);
    
    /* add allowed networks */
    foreach ($this->networks as $name => $network )
      $this->iparams['allow_'.$name] = $network['default'];

    /* add special networks */
    $this->iparams['allow_fb:like'] = array('default'=>0,
					    'layout'=>'standard', //button_count
					    );
					    
    $this->iparams['allow_google:plus'] = array('default'=>0,
					    'size'=>'small', // default is Standart
					    'annotation'=>'', // default is Buuble
					    );
					    
    /* merge params */
    $this->iparams = array_merge($this->iparams, $params);
    
    /* clean title & description */
    if (string_isHTML($this->iparams['title']))
      $this->iparams['title'] = string_html2text($this->iparams['title']);
    $this->iparams['title'] = preg_replace('/\n|\r|\'|"/', ' ', $this->iparams['title']);
    if (string_isHTML($this->iparams['summary']))
      $this->iparams['summary'] = string_html2text(strip_tags($this->iparams['summary']));
    $this->iparams['summary'] = preg_replace('/\n|\r|\'|"/', ' ', $this->iparams['summary']);

    /* add scripts */
    $this->add_JSFile('snsp.js');
    $this->add_JSScript('var snsp = new SNSPanel("snsp");');
    $this->add_JSEngineFile('tool/htmlelement.js');
    $this->add_JSLoadScript('snsp.initialise();');
    
    if ( $this->iparams['allow_fb:like']['default'] == 1 ) {
      $this->add_JSScript('snsp.set_param("fblike_allowed", 1);');
      $this->add_JSScript('snsp.set_param("fblike_language", "'.$camyks->current_language.'_'.strtoupper($camyks->current_language).'");');
    }
    
    if ( $this->iparams['allow_google:plus']['default'] == 1) {
    	$this->add_JSScript('snsp.set_param("gplus_allowed", 1);');
    	$this->add_JSScript('snsp.set_param("gplus_language", "'.$camyks->current_language.'_'.strtoupper($camyks->current_language).'");');
    }

    /* set theme */
    $this->theme = &$camyks->themes[$this->iparams['theme']];
    
    /* add og metas to header */
    if ($this->iparams['include_ogmetas'] == 1) {
      $camyks->HTMLPage->add_meta('og:locale', $this->iparams['locale'], 'property');
      if ($this->iparams['sitename'] != '') $camyks->HTMLPage->add_meta('og:site_name', $this->iparams['sitename'], 'property');
      if ($this->iparams['title'] != '') $camyks->HTMLPage->add_meta('og:title', string_text2HTML($this->iparams['title']), 'property');
      if ($this->iparams['link'] != '') $camyks->HTMLPage->add_meta('og:url', $this->iparams['link'], 'property');
      if ($this->iparams['summary'] != '') $camyks->HTMLPage->add_meta('og:description', string_text2HTML($this->iparams['summary']), 'property');
      if ($this->iparams['image'] != '') $camyks->HTMLPage->add_meta('og:image', $this->iparams['image'], 'property');
      if ($this->iparams['type'] != '') $camyks->HTMLPage->add_meta('og:type', $this->iparams['type'], 'property');
    }
  }

  /*
   * display input
   * @param array $params
   * @return void
   * @access public
   */
  function display($params=array()) {
    /* update index */
    $this->currentIndex++;

    /* merge new params */
    $this->dparams = array_merge($this->iparams, $params);
    $this->count_displayedNetworks();

    /* generic display */
    parent::display();
  }

  /* specific tool methods */

  /*
   * return given network href link
   * @param string $network
   * @return string
   * @access private
   */
  function get_networkHrefLink($network) {
    if (!isset($this->networks[$network]))
      return '';
    if ($this->networks[$network]['link']=='')
      return '';
    return 'href="'.$this->get_networkURL($network, 'link').'"';
  }
  
  /*
   * return given network href link
   * @param string $network
   * @return string
   * @access private
   */
  function get_networkOnclickLink($network) {
    if (!isset($this->networks[$network]))
      return '';
    if ($this->networks[$network]['clic']=='')
      return '';
    return 'onclick="'.$this->get_networkURL($network, 'clic').'"';
  }
  
  /*
   * return given network URL
   * @param string $network
   * @param string $mode
   * @return string
   * @access private
   */
  function get_networkURL($network, $mode) {
    switch($network) {
        case 'twitter':
          if ($this->dparams['shortlink'] != '')
            $link = $this->dparams['shortlink'];
          else
            $link = $this->dparams['link'];
          
          $txtLength = 143 - strlen($link);
          $title = string_getShortenedSentence(urlencode($this->dparams['title']), $txtLength);
          return vsprintf($this->networks[$network][$mode], $title.'+'.$link);
        case 'email':
          return preg_replace(array('/_title_/', '/_link_/', '/_ln_/'), array($this->dparams['title'], $this->dparams['link'], '%0d%0a'), $this->networks[$network][$mode]);
    }
    return vsprintf($this->networks[$network][$mode],
				array(1=>urlencode($this->dparams['link']),
				      2=>urlencode($this->dparams['title']),
				      3=>urlencode($this->dparams['summary'])));
  }
  
  /*
   * count enabled networks
   * @return void
   * @access private
   */
  function count_displayedNetworks() {
    foreach ($this->networks as $name => $network)
      $this->dparams['networks'][$this->dparams['allow_'.$name]]++;
  }
  
  /*
   * initialise network list
   * @return void
   * @access private
   */
  function initialise_networkList() {
  	global $camyks;
  	
    $this->networks = array();

    /* add facebook */
    $this->networks['facebook'] = array('title'=>'Facebook',
					'link'=>'http://www.facebook.com/share.php?u=%1$s',
					'clic'=>'',
					'default'=>1);

    /* add twitter */
    $this->networks['twitter'] = array('title'=>'Twitter',
				       'link'=>'http://twitter.com/home?status=%1$s',
				       'clic'=>'',
				       'default'=>1);
				       
    /* add google+ */
    $this->networks['gplus'] = array('title'=>'Google +',
        'link'=>'https://plus.google.com/share?url=%1$s',
        'clic'=>'',
        'default'=>1);

    /* add google */
    $this->networks['google'] = array('title'=>'Google Bookmarks',
				      'link'=>'http://www.google.com/bookmarks/mark?op=add&bkmk=%1$s&title=%2$s&annotation=%3$s',
				      'clic'=>'',
				      'default'=>1);
    

    /* add yahoo buzz */
    $this->networks['buzzup'] = array('title'=>'Buzz Up!',
				      'link'=>'http://buzz.yahoo.com/buzz?targetUrl=%1$s&headline=%2$s&src=sharethis',
				      'clic'=>'',
				      'default'=>1);
    
    /* add blogger *
     $this->networks['blogger'] = array('title'=>'Blogger',
     'link'=>'',
     'clic'=>'',
     'default'=>1);*/
    
    /* add delicious *
    $this->networks['delicious'] = array('title'=>'Delicious',
					 'link'=>'http://delicious.com/save',
					 'clic'=>'window.open(\'http://delicious.com/save?v=5&noui&jump=close&url=%1$s&title=%2$s\'),\'delicious\', \'toolbar=no,width=550,height=550\'); return false;',
					 'default'=>1);
    
    /* add digg */
    $this->networks['digg'] = array('title'=>'Digg',
				    'link'=>'http://digg.com/submit?url=%1$s&title=%2$s&bodytext=%3$s&media=news&topic=series', 
				    'clic'=>'',
				    'default'=>1);
    
    /* add wikio */
    $this->networks['wikio'] = array('title'=>'Wikio',
				     'link'=>'http://www.wikio.com/vote?url=%1$s&title=%2$s',
				     'clic'=>'',
				     'default'=>1);
    
    
    /* add linkedin */
    $this->networks['linkedin'] = array('title'=>'LinkedIn',
					'link'=>'http://www.linkedin.com/shareArticle?mini=true&url=%1$s&title=%2$s&summary=%3$s&source=',
					'clic'=>'',
					'default'=>1);

    /* add slashdot */
    $this->networks['slashdot'] = array('title'=>'Slashdot',
					'link'=>'http://slashdot.org/bookmark.pl?url=%1$s&title=%2$s',
					'clic'=>'',
					'default'=>1);
    
    /* add technorati */
    $this->networks['technorati'] = array('title'=>'Technorati',
					  'link'=>'http://www.technorati.com/faves?add=%1$s&title=%2$s',
					  'clic'=>'',
					  'default'=>1);

    /* add reddit */
    $this->networks['reddit'] = array('title'=>'Reddit',
				      'link'=>'http://reddit.com/submit?url=%1$s&title=%2$s',
				      'clic'=>'',
				      'default'=>1);
    
    /* add stumbleupon */
    $this->networks['stumbleupon'] = array('title'=>'StumbleUpon',
					   'link'=>'http://www.stumbleupon.com/submit?url=%1$s&title=%2$s',
					   'clic'=>'',
					   'default'=>1);
    
    /* add mister wong */
    $this->networks['misterwong'] = array('title'=>'Mister-Wong',
					  'link'=>'http://www.mister-wong.fr/index.php?action=addurl&bm_url=%1$s&bm_description=%3$s&title=%2$s',
					  'clic'=>'',
					  'default'=>1);

    /* add bebo */
    $this->networks['bebo'] = array('title'=>'Bebo',
				    'link'=>'http://www.bebo.com/c/share?Url=%1$s&Title=%2$s',
				    'clic'=>'',
				    'default'=>1);
				    
	/* add viadeo */
	$this->networks['viadeo'] = array('title'=>'Viadeo', 
		'link'=>'http://www.viadeo.com/shareit/share/?url=%1$s&title=%2$s&urllanguage='.$camyks->current_language,
    	'clic'=>'',
    	'default'=>1);
   
    /* add emai */
    $this->networks['email'] = array('title'=>'E-mail',
        'link'=>'mailto:?subject='.$this->get_translation('emailsubject', $camyks->get_confValue('site_title')).'&body='.$this->get_translation('emailbody'),
        'clic'=>'',
        'default'=>0);
  }
}
?>