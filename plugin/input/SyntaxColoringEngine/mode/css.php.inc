<?php
/**
 * @brief SyntaxColoringEngine Input colourisation mode.
 * @details Plugin / Input Library
 * @file plugin/input/SyntaxColoringEngine/mode/css.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: May 2007
 * @date Modification: Jul 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * SyntaxColoringEngine_css class.
 */
final class SyntaxColoringEngine_css {
    /**
     * var array $styles
     * @brief Define styles for syntax colouring.
     */
    private $styles = array(
        'comments'      => 'color:#CC3333',
        'string'        => 'color:#888888',
        'indent'        => 'padding-left:8px',

        'objects'       => 'color:#258123; font-weight:bold;',
        'classes'       => 'color:#258123;',
        'pseudos'       => 'color:#da560f;',
        'properties'    => 'color:#000088;',
        'values'        => 'color:#666666;',
        'at-rules'      => 'color:#000088; font-weight:bold;',
    );

    /**
     * Execute colorisation.
     * @param string $text
     * @param array $params
     * @return string
     */
    public function execute($text, $params) {

        $defaultParams = array('autoBreakLine'=>true);
        $params = array_merge($defaultParams, $params);
        $styles = $this->styles;

        /* turns > selectors in £ */
        $text = preg_replace('/>|&gt;/', '£', $text);

        /* replace DOS breakline by unix brealines */
        $search = '/\r\n/';
        $replace = "\n";
        $text = preg_replace($search, $replace, $text);

        /* colorise strings */
        $search = '/([\'"])([^\1]*?)\1/s';
        $replace = '<span style="'.$this->styles['string'].'">\\1\\2\\1</span>';
        $text = preg_replace($search, $replace, $text);

        /* colorise properties */
        $search = '/([a-zA-Z\-]{2,})[\s]*:[\s]*([^;\}\{\+]*)[\s]*([;|\}])/';
        $replace = '<span style="'.$this->styles['properties'].'">\\1</span>:<span style="'.$this->styles['values'].'">\\2</span>\\3';
        $text = preg_replace($search, $replace, $text);

        /* colorise @rules */
        $search = '/(@[a-zA-Z\-]{2,})/';
        $replace = '<span style="'.$this->styles['at-rules'].'">\\1</span>';
        $text = preg_replace($search, $replace, $text);

        /* colorise objects */
        $search = '/(#[a-zA-Z\-]{2,})([\s|{|,|:|\.])/';
        $replace = '<span style="'.$this->styles['objects'].'">\\1</span>\\2';
        $text = preg_replace($search, $replace, $text);

        /* colorise classes */
        $search = '/(\A|[^0-9])(\.[a-zA-Z0-9\-]{2,})([\s|{|,|:|\+|£])/';
        $replace = '\\1<span style="'.$this->styles['classes'].'">\\2</span>\\3';
        $text = preg_replace($search, $replace, $text);

        /* colorise pseudo-classes */
        $search = '/(:?:[a-zA-Z\-]{2,})([\s]*)([{|,|\+|£])/';
        $replace = '<span style="'.$this->styles['pseudos'].'">\\1</span>\\2\\3';
        $text = preg_replace($search, $replace, $text);

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

        /* text indentation : with {} */
        $search = '/({[\s]*\n)/';
        $replace = '{<div style="'.$this->styles['indent'].'">';
        $text = preg_replace($search, $replace, $text);

        $search = '/(\n}[\s]*[\n]?)/';
        $replace = '</div>}'."\n";
        $text = preg_replace($search, $replace, $text);

        /* turns back £ selectors in £ */
        $text = preg_replace('/£/', '&gt;', $text);

        /* check autobreakline params */
        if ($params['autoBreakLine'])
            $text = nl2br($text);

        /* send result */
        return $text;
    }
}
?>
