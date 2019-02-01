<?php
/**
 * @brief SyntaxColoringEngine Input colourisation mode.
 * @details Plugin / Input Library
 * @file plugin/input/SyntaxColoringEngine/mode/css.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: May 2007
 * @date Modification: Jan 2019
 * @copyright 2007 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * SyntaxColoringEngine_javascript class.
 */
final class SyntaxColoringEngine_javascript {
    /**
     * var array $styles
     * @brief Define styles for syntax colouring.
     */
    private $styles = array(
        'comments'  => 'color:#CC3333',
        'keywords'  => 'color:#0000FF; font-weight:bold;',
        'string'    => 'color:#888888',
        'indent'    => 'padding-left:16px',
    );

    /**
     * var array $keywords
     * @brief Define keywords for syntax colouring.
     */
    private $keywords = array(
        'if',
        'else',
        'function',
        'for',
        'new',
        'while',
        'eval',
        'prototype',
        'var',
        'return',
        'this',
        'foreach',
        'in',
        'case',
        'switch',
        'continue',
        'break',
        'default',
        'try',
        'catch',
        'alert',
    );

    /**
     * var array $ikeywords
     * @brief Define keywords that need indentation for syntax colouring.
     */
    private $ikeywords = array(
        'if',
        'for',
        'foreach',
        'while',
        'try',
        'catch'
    );

    /**
     * Execute colourisation.
     * @param string $text
     * @param array $params
     * @return string
     */
    public function execute($text, $params) {
        $defaultParams = array('autoBreakLine'=>true);
        $params = array_merge($defaultParams, $params);

        $text = $text . "\n";

        /* replace DOS breakline by unix brealines */
        $search = '/\r\n/';
        $replace = "\n";
        $text = preg_replace ($search, $replace, $text);

        /* colorize strings */
        $search = '/([\'"])([^\']*?)\1/s';
        $replace = '<span style="'.$this->styles['string'].'">\\1\\2\\1</span>';
        $text = preg_replace ($search, $replace, $text);

        /* colorize keywords */
        foreach ( $this->keywords as $id=>$value ) {
            $this->keywords[$id] = '/\b('.$value.')\b/s';
        }

        $search = $this->keywords;
        $replace = '<span style="'.$this->styles['keywords'].'">\\1</span>';
        $text = preg_replace ($search, $replace, $text);

        /* remove existing colored element from comments */
        $search = '/\/\*(.+?)\*\//s';
        $text = preg_replace_callback($search,
            function($match) {
                return preg_replace('/<([^>]*)>/', '', $match[0]);
            },
            $text
        );

        /* colorise multiline comments */
        $search = '/(\/\*)(.+?)(\*\/)/s';
        $replace = '<span style="'.$this->styles['comments'].'">\\1\\2\\3</span>';
        $text = preg_replace($search, $replace, $text);

        /* remove existing colored element from comments */
        $search = '/\/\/(.*)/';
        $text = preg_replace_callback($search,
            function($match) {
                return preg_replace('/<([^>]*)>/', '', $match[0]);
            },
            $text
        );

        /* colorize single line comment */
        $search = '/(\/\/.*)/';
        $replace = '<span style="'.$this->styles['comments'].'">\\1</span>';
        $text = preg_replace ($search, $replace, $text);

        /* text indentation : with {} */
        $c = count_chars($text, 1);
        if (isset($c[ord('{')]) and isset($c[ord('}')]) and $c[ord('{')] === $c[ord('}')]) {
            $text = preg_replace(array('/{\n?/', '/}/'), array('{<div style="padding-left:16px;">', '</div>}'), $text);
        }

        /* text indentation : without {} */
        foreach ($this->ikeywords as $value ) {
            $search = '/(\b'.$value.'\b[^{\n]*)\n([^\n]*)\n/';
            $replace = '\\1<div style="'.$this->styles['indent'].'">\\2</div>';
            $text = preg_replace ($search, $replace, $text);
        }

        /* remove multiple line breaks */
        $search = array('/[\n]{2+}/', '/[\n]+$/');
        $replace = array("\n\n", "\n");
        $text = preg_replace ($search, $replace, $text);

        /* check autobreakline params */
        if ($params['autoBreakLine'])
            $text = nl2br($text);

        /* send result */
        return $text;
    }
}
?>
