<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0
 * Object Type      : Plugin / Input Library
 * Create Date		: Dec 2017
 * Last Modif Date	: Dec 2017
 * 
 * SyntaxColoringEngine mode library : css
*/

final class SyntaxColoringEngine_css {

  /*
   * constructor
   * @return void
   * @access public
   */
  public function __construct () {
    $this->style = array();
    $this->style['comments'] = 'color:#CC3333';
    $this->style['string'] = 'color:#888888';
    $this->style['indent'] = 'padding-left:8px';
    
    $this->style['objects'] = 'color:#0000FF; font-weight:bold;';
    $this->style['classes'] = 'color:#0000FF;';
    $this->style['elements'] = 'color:#00FF00;';
    $this->style['pseudos'] = 'color:#0000FF;';
    $this->style['properties'] = 'color:#000088;';
    $this->style['at-rules'] = 'color:#000088; font-weight:bold;';
  }

  /*
   * execute colorisation
   * @param string $text
   * @return string
   * @access public
   */
  public function execute($text, $params) {
    
    $defaultParams = array('autoBreakLine'=>true);
    $params = array_merge($defaultParams, $params);
  
    /* replace DOS breakline by unix brealines */
    $search = '/\r\n/';
    $replace = "\n";
    $text = preg_replace($search, $replace, $text); 
    
    /* colorise properties */
    $text = preg_replace_callback('/\{(.+?)\}/', 'SyntaxColoringEngine_css_colorPropertiesValues', $text);
    
    
    /* colorise strings */
    $search = '/([\'"])([^\']*?)\1/s';
    $replace = '<span style="'.$this->style['string'].'">\\1\\2\\1</span>';
    $text = preg_replace($search, $replace, $text);
    
    /* colorise multiline comments */
    $search = '/\/\*/';
    $replace = '<span style="'.$this->style['comments'].'">/*';
    $text = preg_replace($search, $replace, $text);

    $search = '/\*\//';
    $replace = '*/</span>';
    $text = preg_replace($search, $replace, $text);
    
    /* text indentation : with {} */
    $search = '/({[\s]*\n)/';
    $replace = '{<div style="'.$this->style['indent'].'">';
    $text = preg_replace($search, $replace, $text);

    $search = '/(\n}[\s]*[\n]?)/';
    $replace = '</div>}'."\n";
    $text = preg_replace($search, $replace, $text);
    
    /* check autobreakline params */
    if ($params['autoBreakLine'])
      $text = nl2br($text);
    
    /* send result */
    return $text;
  }
}

function SyntaxColoringEngine_css_colorPropertiesValues($match) {
  global $camyks;
  
  $properties = $match[1];
  $properties = explode(';', $properties);
  
  foreach($properties as $i => $property) {
    $property = trim($property);
    
    if ($property != '') {
      $items = explode(':', $property);
      
      if (!isset($items[1])) { print_r($items); die(); }
              
      $properties[$i] = '<span style="'.$camyks->inputs['SyntaxColoringEngine']->mode->style['properties'].'">'.$items[0].'</span>:'.$items[1].'';
    }
  }
  return implode('; ', $properties).';';
}


?>