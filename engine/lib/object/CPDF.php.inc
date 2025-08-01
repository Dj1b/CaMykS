<?php
/**
 * @brief PDF creator object extending FDPF library.
 * @details Engine / Object Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.5.1
 * @date Creation: May 2010
 * @date Modification: Jul 2025
 * @copyright 2010 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

require_once('FPDF/fpdf.php');
require_once('colors.php.inc');

/**
 * CPDF class.
 */
class CPDF extends FPDF {

    /**
     * Class constructor.
     * @param string $orientation
     * @param string $unit
     * @param mixed $format
     */
    public function __construct($orientation='P', $unit='mm', $format='A4') {
        global $camyks;

        /* Generic FPDF Init */
        parent::__construct($orientation, $unit, $format);
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
        $this->htmlParams = array('lineHeight'=>5, 'paragraphHeight'=>10, 'defaultTextColor'=>0, 'ulBulletChar'=>chr(149), 'ulBulletColor'=>0, 'ulBulletStyle'=>'', 'ulBulletFont'=>'', 'ulBulletSize'=>null);

        /* Backup font value */
        $this->currentFont = array('font'=>'', 'style'=>null, 'size'=>null);
    }

    /**
     * Old style constructor definition.
     * @param string $orientation
     * @param string $unit
     * @param mixed $format
     * @return void
     */
    public function CPDF($orientation=null, $unit=null, $format=null) {
        $this->__construct($orientation, $unit, $format);
    }

    /* Override FPDF methods */

    /**
     * Write multiple lines at once
     * @param int $w
     * @param int $h
     * @param string $txt
     * @param mixed $border
     * @param string $align
     * @param boolean $fill
     * @param integer $maxLines
     * @return string
     */
    public function MultiCell($w, $h, $txt, $border=0, $align='J', $fill=false, $maxLines=0) {
        if ($maxLines == 0) {
            parent::MultiCell($w, $h, $txt, $border, $align, $fill);
            return '';
        }

        $cw = &$this->CurrentFont['cw'];
        if ($w==0)
            $w = $this->w-$this->rMargin-$this->x;
        $wmax = ($w-2*$this->cMargin)*1000/$this->FontSize;
        $s = str_replace("\r",'',$txt);
        $nb = strlen($s);
        if ($nb>0 && $s[$nb-1]=="\n")
            $nb--;
        $b=0;
        if ($border) {
            if ($border==1) {
                $border='LTRB';
                $b='LRT';
                $b2='LR';
            } else {
                $b2='';
                if (is_int(strpos($border,'L')))
                    $b2 .= 'L';
                if (is_int(strpos($border,'R')))
                    $b2 .= 'R';
                $b = is_int(strpos($border,'T')) ? $b2.'T' : $b2;
            }
        }
        $sep = -1;
        $i = 0;
        $j = 0;
        $l = 0;
        $ns = 0;
        $nl = 1;
        while ($i<$nb) {
            $c = $s[$i];
            if ($c=="\n") {
                if ($this->ws>0) {
                    $this->ws = 0;
                    $this->_out('0 Tw');
                }
                $this->Cell($w, $h, substr($s, $j, $i-$j), $b, 2, $align, $fill);
                $i++;
                $sep = -1;
                $j = $i;
                $l = 0;
                $ns = 0;
                $nl++;
                if ($border && $nl==2)
                    $b=$b2;
                if ($maxLines && $nl>$maxLines)
                    return substr($s,$i);
                continue;
            }
            if ($c == ' ') {
                $sep = $i;
                $ls = $l;
                $ns++;
            }
            $l += $cw[$c];
            if ($l > $wmax) {
                if ($sep==-1) {
                    if ($i == $j)
                        $i++;
                    if ($this->ws > 0) {
                        $this->ws = 0;
                        $this->_out('0 Tw');
                    }
                    $this->Cell($w, $h, substr($s, $j, $i-$j), $b, 2, $align, $fill);
                } else {
                    if ($align=='J') {
                        $this->ws = ($ns > 1) ? ($wmax-$ls)/1000*$this->FontSize/($ns-1) : 0;
                        $this->_out(sprintf('%.3F Tw', $this->ws*$this->k));
                    }
                    $this->Cell($w, $h, substr($s, $j, $sep-$j), $b, 2, $align, $fill);
                    $i = $sep+1;
                }
                $sep = -1;
                $j = $i;
                $l = 0;
                $ns = 0;
                $nl++;
                if ($border && $nl==2)
                    $b=$b2;
                if ($maxLines && $nl>$maxLines) {
                    if ($this->ws > 0) {
                        $this->ws = 0;
                        $this->_out('0 Tw');
                    }
                    return substr($s, $i);
                }
            }
            else
                $i++;
        }
        if ($this->ws>0) {
            $this->ws = 0;
            $this->_out('0 Tw');
        }
        if ($border && is_int(strpos($border,'B')))
            $b .= 'B';
        $this->Cell($w, $h, substr($s, $j, $i-$j), $b, 2, $align, $fill);
        $this->x = $this->lMargin;
        return '';
    }

    /**
     * Define font.
     * @param string $font
     * @param string $style
     * @param integer $size
     * @param boolean $isTemporary
     * @return void
     */
    public function setFont($font='', $style=null, $size=null, $isTemporary=false) {
        parent::setFont($font, $style, $size);
        if (!$isTemporary) {
            if ($font != '')
                $this->currentFont['font'] = $font;
            if (!is_null($style))
                $this->currentFont['style'] = $style;
            if (!is_null($size))
                $this->currentFont['size'] = $size;
        }
    }

    /* Mark: Specific methods */

    /**
     * Revert font (after temporary use).
     * @return void
     */
    public function revert_font() {
        $this->setFont($this->currentFont['font'], $this->currentFont['style'], $this->currentFont['size'], true);
    }


    /**
     * Update html params.
     * @param array $params
     * @return void
     */
    public function set_htmlParams($params=array()) {
        $this->htmlParams = array_merge($this->htmlParams, $params);
    }

    /**
     * Return real width.
     * @param float $w
     * @return float
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

    /**
     * Write html into PDF.
     * @param HTML $html
     * @return void
     */
    public function write_html($html) {
        /* parse unknown tags */
        $html = strip_tags($html, "<b><u><i><a><img><p><br><strong><em><font><tr><blockquote><ol><ul><li>");

        /* remove line breaks and translate some html chars */
        $html = str_replace("\n",' ',$html);
        $pattern = array('/&trade;/', '/&copy;/', '/&bull;/', '/&euro;/', '/&(#39|#171|#187|raquo|laquo|rdquo|ldquo|rsquo|lsquo);/', '/&oelig;/', '/&hellip;/', '/&ndash;/');
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
                        if (preg_match('/([^=]*)=["\']?([^"\']*)/',$v,$a3))
                            $attr[strtoupper($a3[1])]=$a3[2];
                    }
                    $this->_write_htmlOpenTag($tag, $attr);
                }
            }
        }
    }

    /**
     * Return available fond list.
     * @return array
     */
    public function get_fontList() {
        return $this->fontlist;
    }

    /* tool methods */

    /**
     * Decode text.
     * @param string $text
     * @return string
     */
    public function decode_text($text) {
        if (!string_isUTF8($text))
            return $text;

        if (version_compare(PHP_VERSION, '5.4.0') >= 0) {
            /* Check for latest converting method, using UConverter */
            if (method_exists('UConverter', 'transcode'))
                return UConverter::transcode($text, 'ISO-8859-15', 'UTF-8', array('to_subst' => ' '));

            /* Check for MB string converting method */
            if (function_exists('mb_convert_encoding'))
                return mb_convert_encoding($text, 'ISO-8859-15');
        }

        /* Use default, deprecated method */
        return utf8_decode($text);
    }

    /**
     * Return entity decoded text.
     * @param string $text
     * @return string
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

    /**
     * Set text color from any value.
     * @param mixed $color
     * @return string
     */
    public function set_textColor($color='') {
        /* color as hexa string */
        if (is_string($color)) {
            if ($color == '')
                return $this->set_textColor($this->htmlParams['defaultTextColor']);
            if (strlen($color) == 6)
                return $this->set_textColor(color_hex2rgb($color));
            if (strlen($color) == 7)
                return $this->set_textColor(color_hex2rgb(substr($color, 1)));
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

    /**
     * Move current page to a new location.
     * @param integer $page
     * @param integer $location
     * @return void
     */
    public function move_page($page, $location) {
        $p = $this->pages[$page];

        if ($location < $page) {
            for ($i=$page; $i>$location; $i--)
                $this->pages[$i] = $this->pages[$i-1];
            $this->pages[$location] = $p;

        } elseif ($location > $page) {
            for ($i=$page; $i<$location; $i++)
                $this->pages[$i] = $this->pages[$i+1];
            $this->pages[$location] = $p;
        }
    }

    /* Mark: HTML internal methods */

    /**
     * Open tag for html writing.
     * @param string $tag
     * @param array $attr
     * @return void
     */
    private function _write_htmlOpenTag($tag, $attr) {
        global $camyks;

        switch($tag) {
            case 'STRONG':
                $this->_write_htmlSetStyle('B', true);
                break;
            case 'EM':
                $this->_write_htmlSetStyle('I', true);
                break;
            case 'B':
            case 'I':
            case 'U':
                $this->_write_htmlSetStyle($tag, true);
                break;
            case 'A':
                $url = parse_url($attr['HREF']);
                /* Check URL is email */
                if (stripos($attr['HREF'], 'mailto:') === 0)
                    $this->HREF = $attr['HREF'];
                /* Check URL has domain */
                elseif (!isset($url['host']))
                    $this->HREF = $camyks->get_rootBaseURL('absolute').$attr['HREF'];
                /* Check URL has scheme */
                elseif (!isset($url['scheme']))
                    $this->HREF = 'http://'.$attr['HREF'];
                else
                    $this->HREF = $attr['HREF'];
                break;
            case 'IMG':
                if (isset($attr['SRC']) && (isset($attr['WIDTH']) || isset($attr['HEIGHT']))) {
                    if (!isset($attr['WIDTH']))
                        $attr['WIDTH'] = 0;
                    if (!isset($attr['HEIGHT']))
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
                    $this->setFont($this->htmlParams['ulBulletFont'], $this->htmlParams['ulBulletStyle'], $this->htmlParams['ulBulletSize'], true);
                    $this->Write($this->htmlParams['lineHeight'], $this->htmlParams['ulBulletChar'].' ');
                    $this->set_textColor('');
                    $this->revert_font();
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

    /**
     * Close tag for html writing.
     * @param string $tag
     * @return void
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

    /**
     * Define current style for html writing.
     * @param string $tag
     * @param integer $enable
     * @return void
     */
    private function _write_htmlSetStyle($tag, $enable) {
        $this->$tag += ($enable ? 1 : -1);
        $style='';
        foreach(array('B','I','U') as $s) {
            if ($this->$s > 0)
                    $style.=$s;
        }
        $this->SetFont('',$style);
    }

    /**
     * Add link to text.
     * @param string $URL
     * @param string $txt
     * @return void
     */
    private function _write_htmlAddLink($URL, $txt) {
        $URL = $this->decode_HTMLText($URL);
        $this->set_textColor(array(0,0,255));
        $this->_write_htmlSetStyle('U', true);
        $this->Write(5, $this->decode_HTMLText($txt), $URL);
        $this->_write_htmlSetStyle('U', false);
        $this->set_textColor('');
    }

    /* Mark: Specific internal methods */

    /**
     * Encode entities.
     * @param string $text
     * @return string
     */
    private function _encode_entities($text) {
        return html_entity_decode($text, ENT_COMPAT, 'ISO-8859-15');
    }
}
?>
