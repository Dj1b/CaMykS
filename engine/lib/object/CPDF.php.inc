<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	        : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0
 * Object Type      : Engine / Object Lib
 * Creation Date    : May 2010
 * Last Modif Date  : Nov 2017
 * History :
 * * 10-05-17 : Initial File
 *
 * CaMykS PDF creator object extending FDPF object
 * /!\ This library is not loaded with CaMykS initialisation
 *
 * Plugin is not a final object, it can be extended by module libraries
 */
 
require_once('FPDF/fpdf.php');

class CPDF extends FPDF { 
  
  /* 
   * constructor
   * @param string $orientation
   * @param string $unit
   * @param mixed $format
   * @access public
   */
  public function __construct($orientation=null, $unit=null, $format=null) {
    global $camyks;
    
    /* Generic FPDF Init */
    parent::FPDF($orientation, $unit, $format);
    $this->unit = $unit;
    
    /* Check encoding */
    $this->serverEncoding = $camyks->get_confValue('server_encoding');
    
    /* Initialise write HTML values */
    $this->B = 0;
    $this->I = 0;
    $this->U = 0;
    $this->OL = 0;
    $this->UL = 0;
    $this->HREF='';
    $this->fontlist = array('arial', 'times', 'courier', 'helvetica', 'symbol');
    $this->issetfont = false;
    $this->issetcolor = false;
    $this->olIndex = 1;
    $this->htmlParams = array('lineHeight'=>5, 'paragraphHeight'=>10, 'defaultTextColor'=>0, 'ulBulletChar'=>chr(149), 'ulBulletColor'=>0);
  }
  
  /*
   * old style constructor definition
   * @param string $orientation
   * @param string $unit
   * @param mixed $format
   * @access public
   */
  public function CPDF($orientation=null, $unit=null, $format=null) {
    $this->__construct($orientation, $unit, $format);
  }

  /* specific methods */

  /*
   * update html params
   * @params array $params
   * @return void
   * @access public
   */
  public function set_htmlParams($params=array()) {
    $this->htmlParams = array_merge($this->htmlParams, $params);
  }

  /*
   * return real width
   * @param float $w
   * @return float
   * @access public
   */
  public function get_realWidth($w=0) {
    switch ($this->unit) {
      case 'pt':
        return $w;
      case 'mm':
        return $w*0.35;
      case 'cm':
        return $w*3.5;
      case 'in':
        return $w/72;
    }
    return 0;
  }
  
  /*
   * write html into pdf
   * @param HTML $html
   * @return void
   * @access public
   */
  public function write_html($html) {
    /* parse unknown tags */
    $html = strip_tags($html,"<b><u><i><a><img><p><br><strong><em><font><tr><blockquote><ol><ul><li>");

    /* remove line breaks and translate some html chars */
    $html = str_replace("\n",' ',$html);
    $pattern = array('/&trade;/', '/&copy;/', '/&bull;/', '/&euro;/', '/&(#39|rsquo|lsquo);/', '/&oelig;/', '/&hellip;/', '/&ndash;/');
    $replace = array(chr(153), chr(169), chr(149),'<b>'.chr(128).'</b>', '\'', 'oe', '...', '-' );
    $html = preg_replace($pattern, $replace, $html);

    /* split string */
    $a = preg_split('/<(.*)>/U', $html, -1, PREG_SPLIT_DELIM_CAPTURE);
    
    /* params */
    $this->isFirstBlock = true;
    
    foreach($a as $i=>$e) {
      if ($i%2==0) {
        /* write text */
        if ($this->HREF)
          $this->_write_htmlAddLink($this->HREF,$e);
        else
          $this->Write($this->htmlParams['lineHeight'], stripslashes($this->_encode_entities($e)));
      } else {
        if ($e[0]=='/')
          /* close tags */
          $this->_write_htmlCloseTag(strtoupper(substr($e,1)));
        else {
          /* open tag */
          $a2 = explode(' ',$e);
          $tag=strtoupper(array_shift($a2));
          $attr=array();
          foreach($a2 as $v) {
            if(preg_match('/([^=]*)=["\']?([^"\']*)/',$v,$a3))
              $attr[strtoupper($a3[1])]=$a3[2];
          }
          $this->_write_htmlOpenTag($tag, $attr);
        }
      }
    }
  }
  
  /* tool methods */
  
  /*
   * decode text 
   * @param string $text
   * @return string
   * @access public
   */
  public function decode_text($text) {
    if ($this->serverEncoding == 'utf8')
      return utf8_decode($text);
    return $text;
  }
  
  /*
   * return entity decoded text 
   * @param string $text
   * @return string
   * @access public
   */
  public function decode_HTMLText($text='') {
    /* replace special chars */
    $patterns = array('/&euro;/', '/&quot;/', '/&rsquo;/', '/&oelig;/');
    $replacem = array(chr(128), '"', '\'', chr(156));    
    
    $text = preg_replace($patterns, $replacem, $text);
    
    /* decode entities */
    $text = html_entity_decode($text, ENT_COMPAT, 'ISO-8859-15');
    $text = preg_replace('/(<br ?\/>\n)+/', "\n", $text);
    $text = strip_tags($text);
  
    /* return result */
    return $text;
  }
  
  /*
   * set text color from any value
   * @param mixed $color
   * @return string
   * @access public
   */
  public function set_textColor($color) {
    /* color as hexa string */
    if (is_string($color)) {
      if ($color == '')
        return $this->set_textColor($this->htmlParams['defaultTextColor']);
      if (strlen($color) == 6)
        return $this->set_textColor(hex2dec($color));
      if (strlen($color) == 7)
        return $this->set_textColor(hex2dec(substr($color, 1)));
    }
    
    /* color as array */
    if (is_array($color) and count($color) == 3) {
      if (isset($color['R']) and (isset($color['G']) or isset($color['V'])) or isset($color['B'])) {
        if (isset($color['G']))
          $this->SetTextColor($color['R'], $color['G'], $color['B']);
        else
          $this->SetTextColor($color['R'], $color['V'], $color['B']);
        return;
          
      }
      if (isset($color[0]) and isset($color[1]) and isset($color[2])) {
        $this->SetTextColor($color[0], $color[1], $color[2]);
        return;
      }
    }
    
    /* try as provided */
    $this->SetTextColor($color);
    return;
  }
  
  /*
   * move current page to a new location
   * @param integer $page
   * @param integer $location
   * @return void
   * @access private
   */
  public function move_page($page, $location) {
    $p = $this->pages[$page];
    
    if ($location < $page) {
      for($i=$page; $i>$location; $i--)
        $this->pages[$i] = $this->pages[$i-1];
      $this->pages[$location] = $p;
    
    } elseif ($location > $page) {
      for($i=$page; $i<$location; $i++)
        $this->pages[$i] = $this->pages[$i+1];
      $this->pages[$location] = $p;
    }
  }
  
  
  /* sub methods */
  
  /*
   * open tag for html writing
   * @param string $tag
   * @param array $attr
   * @return void
   * @access private
   */
  private function _write_htmlOpenTag($tag, $attr) {
    switch($tag) {
      case 'STRONG':
        $this->_write_htmlSetStyle('B',true);
        break;
      case 'EM':
        $this->_write_htmlSetStyle('I',true);
        break;
      case 'B':
      case 'I':
      case 'U':
        $this->_write_htmlSetStyle($tag,true);
        break;
      case 'A':
        $this->HREF=$attr['HREF'];
        break;
      case 'IMG':
        if (isset($attr['SRC']) && (isset($attr['WIDTH']) || isset($attr['HEIGHT']))) {
          if (!isset($attr['WIDTH']))
            $attr['WIDTH'] = 0;
            if(!isset($attr['HEIGHT']))
              $attr['HEIGHT'] = 0;
            $this->Image($attr['SRC'], $this->GetX(), $this->GetY(), $this->get_realWidth($attr['WIDTH']), $this->get_realWidth($attr['HEIGHT']));
        }
        break;
      case 'TR':
      case 'BLOCKQUOTE':
      case 'BR':
        if ($this->isFirstBlock)
          $this->isFirstBlock = false;
        else
          $this->Ln($this->htmlParams['lineHeight']);
        break;
      case 'P':
        if ($this->isFirstBlock)
          $this->isFirstBlock = false;
        else
          $this->Ln($this->htmlParams['paragraphHeight']);
        break;
      case 'OL':
          $this->OL = true;
          break;
      case 'UL':
          $this->UL = true;
          break;
      case 'LI':
          if ($this->UL) {
            if ($this->isFirstBlock)
              $this->isFirstBlock = false;
            else
              $this->Ln($this->htmlParams['lineHeight']);
            $this->set_textColor($this->htmlParams['ulBulletColor']);
            $this->Write($this->htmlParams['lineHeight'], $this->htmlParams['ulBulletChar'].' ');
            $this->set_textColor('');
          } elseif ($this->OL) {
            if ($this->isFirstBlock)
              $this->isFirstBlock = false;
            else
              $this->Ln($this->htmlParams['lineHeight']);
            $this->Write($this->htmlParams['lineHeight'], $this->olIndex++.'. ');
          }
      case 'FONT':
        if (isset($attr['COLOR']) && $attr['COLOR']!='') {
          $this->set_textColor($attr['COLOR']);
          $this->issetcolor=true;
        }
        if (isset($attr['FACE']) && in_array(strtolower($attr['FACE']), $this->fontlist)) {
          $this->_write_htmlSetFont(strtolower($attr['FACE']));
          $this->issetfont=true;
        }
        break;
    }
  }

  /*
   * close tag for html writing
   * @param string $tag
   * @return void
   * @access private
   */
  private function _write_htmlCloseTag($tag) {
    if ($tag=='STRONG')
        $tag='B';
    if ($tag=='EM')
        $tag='I';
    if ($tag=='B' || $tag=='I' || $tag=='U')
        $this->_write_htmlSetStyle($tag,false);
    if ($tag=='A')
        $this->HREF='';
    if ($tag=='OL')
        $this->olIndex = 1;
     
    if ($tag=='FONT') {
      if ($this->issetcolor==true) {
        $this->set_textColor('');
      }
      if ($this->issetfont) {
        $this->SetFont('arial');
        $this->issetfont=false;
      }
    }
  }

  /* 
   * define current style for html writing
   * @param string $tag
   * @param integer $enable
   * @return void
   * @access private
   */
  private function _write_htmlSetStyle($tag, $enable) {
    $this->$tag+=($enable ? 1 : -1);
    $style='';
    foreach(array('B','I','U') as $s) {
      if ($this->$s>0)
        $style.=$s;
    }
    $this->SetFont('',$style);
  }

  /*
   * add link to text
   * @param string $url
   * @param string $txt
   * @return void
   * @access private
   */
  private function _write_htmlAddLink($URL, $txt) {
    $this->set_textColor(array(0,0,255));
    $this->_write_htmlSetStyle('U', true);
    $this->Write(5, $txt, $URL);
    $this->_write_htmlSetStyle('U', false);
    $this->set_textColor('');
  }

  /*
   * encode entities 
   * @param string $text
   * @return string
   * @access private
   */
  private function _encode_entities($text) {
    global $camyks;
    
    return html_entity_decode($text, ENT_COMPAT, 'ISO-8859-15');
    
    $trans = get_html_translation_table(HTML_ENTITIES);
    $trans = array_flip($trans);

    if ( $camyks->get_confValue('server_encoding') == 'utf8')
      return utf8_decode(strtr($text, $trans));
    else
      return strtr($text, $trans);
  }
}
?>