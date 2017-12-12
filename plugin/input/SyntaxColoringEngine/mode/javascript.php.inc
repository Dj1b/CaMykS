<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0
 * Object Type      : Plugin / Input Library
 * Create Date		: May 2007
 * Last Modif Date	: Dec 2017
 * 
 * SyntaxColoringEngine mode library : javascript
*/

final class SyntaxColoringEngine_javascript {

  /* 
   * constructor
   * @return void
   * @access public
   */
  public function __construct () {
    $this->style = array();
    $this->style['comments'] = 'color:#CC3333';
    $this->style['keywords'] = 'color:#0000FF;font-weight:bold;';
    $this->style['string'] = 'color:#888888';
    $this->style['indent'] = 'padding-left:8px';
  
    $this->keywords = array();
    $this->keywords[] = 'if';
    $this->keywords[] = 'else';
    $this->keywords[] = 'function';
    $this->keywords[] = 'for';
    $this->keywords[] = 'new';
    $this->keywords[] = 'while';
    $this->keywords[] = 'eval';
    $this->keywords[] = 'prototype';
    $this->keywords[] = 'var';
    $this->keywords[] = 'return';
    $this->keywords[] = 'this';
    $this->keywords[] = 'foreach';
    $this->keywords[] = 'in';
    $this->keywords[] = 'case';
    $this->keywords[] = 'switch';
    $this->keywords[] = 'continue';
    $this->keywords[] = 'break';
    $this->keywords[] = 'default';
    $this->keywords[] = 'try';
    $this->keywords[] = 'catch';
    $this->keywords[] = 'alert';
    
    $this->ikeywords = array();
    $this->ikeywords[] = 'if';
    $this->ikeywords[] = 'for';
    $this->ikeywords[] = 'foreach';
    $this->ikeywords[] = 'while';
    $this->ikeywords[] = 'try';
    $this->ikeywords[] = 'catch';
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
    $text = preg_replace ( $search, $replace, $text ); 

    /* colorize strings */
    $search = '/([\'"])([^\']*?)\1/s';
    $replace = '<span style="'.$this->style['string'].'">\\1\\2\\1</span>';
    $text = preg_replace ( $search, $replace, $text );

    /* colorize keywords */
    foreach ( $this->keywords as $id=>$value ) {
      $this->keywords[$id] = '/\b('.$value.')\b/s';
    }

    $search = $this->keywords;
    $replace = '<span style="'.$this->style['keywords'].'">\\1</span>';
    $text = preg_replace ( $search, $replace, $text );
   
    /* colorize multiline comments */
    $search = '/\/\*/';
    $replace = '<span style="'.$this->style['comments'].'">/*';
    $text = preg_replace ( $search, $replace, $text );

    $search = '/\*\//';
    $replace = '*/</span>';
    $text = preg_replace ( $search, $replace, $text );

    /* colorize single line comment */
    $search = '/(\/\/.*)/';
    $replace = '<span style="'.$this->style['comments'].'">\\1</span>';
    $text = preg_replace ( $search, $replace, $text );
    
    /* text indentation : with {} */
    $search = '/({\n)/';
    $replace = '{<div style="'.$this->style['indent'].'">';
    $text = preg_replace ( $search, $replace, $text );

    $search = '/(}[\n]?)/';
    $replace = '</div>}'."\n";
    $text = preg_replace ( $search, $replace, $text );
    
    /* text indentation : without {} */
    foreach ( $this->ikeywords as $value ) {
      $search = '/(\b'.$value.'\b[^{\n]*)\n([^\n]*)\n/';
      $replace = '\\1<div style="'.$this->style['indent'].'">\\2</div>';
      $text = preg_replace ( $search, $replace, $text );
    }
    
    /* check autobreakline params */
    if ($params['autoBreakLine'])
      $text = nl2br($text);
    
    /* send result */
    return $text;
  }
}
?>