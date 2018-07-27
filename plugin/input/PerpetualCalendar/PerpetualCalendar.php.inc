<?php
/**
 * @brief PerpetualCalendar Input
 * <br /> Display a calendar, and allow multiple actions on it.
 * @details Plugin / Input Engine
 * @file plugin/input/PerpetualCalendar/PerpetualCalendar.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Apr 2010
 * @date Modification: Jul 2018
 * @copyright 2010 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * PerpetualCalendar Input class.
 * @author CaMykS Team <camyks.contact@gmail.com>
 */
final class PerpetualCalendar extends Input {

    /**
     * Class constructor?
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('PerpetualCalendar', $path_type);

        /* overwrite Plugin values */
        $this->version = '1.0';
        $this->plugin_package = 'Generic';

        /* author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';
    }

    /* Overwrite input methods */

    /**
     * Initialise input.
     * @param array $params
     * @return void
     */
    public function initialise ($params=array()) {
        global $camyks;

        /* initialise default params */
        $p = array(
            'name'=>'Calendar', // calendar id
            'theme'=>'',    // optional theme used for button display and/or style display
            'mode'=>'items', // items, selection, ...
            'buttonSource'=>'plugin', // could be theme/plugin/text
            'styleSource'=>'plugin', // could be theme/plugin
            'styleFile'=>'', // optional style file to load
            'styleCellspacing'=>0, // calendar table cell spacing
            'dateMonth'=>date('n'), // default month display
            'dateYear'=>date('Y'), // default year display
            'enableHighlight'=>1,
            'enableJSMonthChange'=>1,
            'prevMonthLink'=>null, // next month link url
            'nextMonthLink'=>null, // previous month link url
            /* items mode */
            'items'=>array(),
            'defaultItem'=>array('title'=>'', 'class'=>0, 'hadEvents'=>0),
            'defaultEvents'=>array('overEvent'=>'', 'outEvent'=>'', 'clickEvent'=>''),
            'multiItem'=>array('enabled'=>0, 'title'=>'', 'class'=>'', 'hadEvents'=>0),
            /* selection mode */
            'selectionCallBack'=>'',
        );

        /* merge params */
        $this->params = array_merge($p, $params);

        /* check month change links */
        if ($this->params['enableJSMonthChange'] == 1 and $this->params['prevMonthLink'] == null) {
            $this->params['prevMonthLink'] = 'javascript:'.$this->params['name'].'.display_prevMonth();';
            $this->params['nextMonthLink'] = 'javascript:'.$this->params['name'].'.display_nextMonth();';
        }

        /* load theme if required */
        if ($this->params['buttonSource'] == 'theme'
            or $this->params['styleSource'] == 'theme') {
            if ($this->params['theme'] != '' and isset($camyks->themes[$this->params['theme']]))
                $this->theme = &$camyks->themes[$this->params['theme']];
            else
                $this->theme = &$camyks->themes[$camyks->get_confValue('site_default_theme')];
        }

        /* insert style file if required */
        if ($this->params['styleSource'] == 'theme') {
            if ($this->params['styleFile'] != '')
                $this->theme->add_styleFile($this->params['styleFile']);
        } else {
            if ($this->params['styleFile'] != '')
                $this->add_styleFile($this->params['styleFile']);
            else
                $this->add_styleFile('perpetualcalendar.css');
        }

        /* date check */
        $this->calendarFirstDay = mktime(0, 0, 0, $this->params['dateMonth'], 1, $this->params['dateYear']);
        $this->calendarLastDay = mktime(23, 59, 59, $this->params['dateMonth']+1, 0, $this->params['dateYear']);

        /* load scripts */
        $this->add_JSFile('perpetualcalendar.js');
        $this->add_JSScript('var '.$this->params['name'].' = new PerpetualCalendar("'.$this->params['name'].'");');
        $this->add_JSLoadScript($this->params['name'].'.initialise();');
        $this->add_JSScript($this->params['name'].'.set_param("mode", "'.$this->params['mode'].'");');
        $this->add_JSScript($this->params['name'].'.set_param("dateMonth", '.($this->params['dateMonth']-1).');');
        $this->add_JSScript($this->params['name'].'.set_param("dateYear", '.($this->params['dateYear']).');');
        $this->add_JSScript($this->params['name'].'.set_param("enableHighlight", '.($this->params['enableHighlight']).');');

        if ($this->params['mode'] == 'items') {
            /* set default item script */
            $items = array();
            foreach ($this->params['defaultItem'] as $name => $value) {
                if ($name == 'date')
                    $items[] = '"'.$name.'":'.$value.'000';
                elseif (is_string($value))
                    $items[] = '"'.$name.'":"'.$value.'"';
                elseif (is_numeric($value))
                    $items[] = '"'.$name.'":'.$value.'';
            }
            $jsi = $this->params['name'].'.set_param("defaultItem", {';
            $jsi .= implode(', ', $items);
            $jsi .= '});';
            $this->add_JSScript($jsi);

            /* set default events script */
            $items = array();
            foreach ($this->params['defaultEvents'] as $name => $value) {
                if (is_string($value))
                    $items[] = '"'.$name.'":"'.$value.'"';
                elseif (is_numeric($value))
                 $items[] = '"'.$name.'":'.$value.'';
            }
            $jsi = $this->params['name'].'.set_param("defaultEvents", {';
            $jsi .= implode(', ', $items);
            $jsi .= '});';
            $this->add_JSScript($jsi);

            /* set multi item script */
            $items = array();
            foreach ($this->params['multiItem'] as $name => $value) {
                if (is_string($value))
                    $items[] = '"'.$name.'":"'.$value.'"';
                elseif (is_numeric($value))
                    $items[] = '"'.$name.'":'.$value.'';
            }

            $jsi = $this->params['name'].'.set_param("multiItem", {';
            $jsi .= implode(', ', $items);
            $jsi .= '});';
            $this->add_JSScript($jsi);

        } elseif ($this->params['mode'] == 'selection') {
            /* selection mode */
            $this->add_JSScript($this->params['name'].'.set_param("selectionCallBack", "'.$this->params['selectionCallBack'].'");');
        }

        /* add scripts locales */
        $this->add_JSScript($this->params['name'].'.set_locale("monday", "'.ucfirst(strftime('%A', mktime(0, 0, 0, 4, 5, 2010))).'");');
        $this->add_JSScript($this->params['name'].'.set_locale("tuesday", "'.ucfirst(strftime('%A', mktime(0, 0, 0, 4, 6, 2010))).'");');
        $this->add_JSScript($this->params['name'].'.set_locale("wednesday", "'.ucfirst(strftime('%A', mktime(0, 0, 0, 4, 7, 2010))).'");');
        $this->add_JSScript($this->params['name'].'.set_locale("thursday", "'.ucfirst(strftime('%A', mktime(0, 0, 0, 4, 8, 2010))).'");');
        $this->add_JSScript($this->params['name'].'.set_locale("friday", "'.ucfirst(strftime('%A', mktime(0, 0, 0, 4, 9, 2010))).'");');
        $this->add_JSScript($this->params['name'].'.set_locale("saturday", "'.ucfirst(strftime('%A', mktime(0, 0, 0, 4, 10, 2010))).'");');
        $this->add_JSScript($this->params['name'].'.set_locale("sunday", "'.ucfirst(strftime('%A', mktime(0, 0, 0, 4, 11, 2010))).'");');

        $this->add_JSScript($this->params['name'].'.set_locale("january", "'.ucfirst(strftime('%B', mktime(0, 0, 0, 1, 1, 2010))).'");');
        $this->add_JSScript($this->params['name'].'.set_locale("february", "'.ucfirst(strftime('%B', mktime(0, 0, 0, 2, 1, 2010))).'");');
        $this->add_JSScript($this->params['name'].'.set_locale("march", "'.ucfirst(strftime('%B', mktime(0, 0, 0, 3, 1, 2010))).'");');
        $this->add_JSScript($this->params['name'].'.set_locale("april", "'.ucfirst(strftime('%B', mktime(0, 0, 0, 4, 1, 2010))).'");');
        $this->add_JSScript($this->params['name'].'.set_locale("may", "'.ucfirst(strftime('%B', mktime(0, 0, 0, 5, 1, 2010))).'");');
        $this->add_JSScript($this->params['name'].'.set_locale("june", "'.ucfirst(strftime('%B', mktime(0, 0, 0, 6, 1, 2010))).'");');
        $this->add_JSScript($this->params['name'].'.set_locale("july", "'.ucfirst(strftime('%B', mktime(0, 0, 0, 7, 1, 2010))).'");');
        $this->add_JSScript($this->params['name'].'.set_locale("august", "'.ucfirst(strftime('%B', mktime(0, 0, 0, 8, 1, 2010))).'");');
        $this->add_JSScript($this->params['name'].'.set_locale("september", "'.ucfirst(strftime('%B', mktime(0, 0, 0, 9, 1, 2010))).'");');
        $this->add_JSScript($this->params['name'].'.set_locale("october", "'.ucfirst(strftime('%B', mktime(0, 0, 0, 10, 1, 2010))).'");');
        $this->add_JSScript($this->params['name'].'.set_locale("november", "'.ucfirst(strftime('%B', mktime(0, 0, 0, 11, 1, 2010))).'");');
        $this->add_JSScript($this->params['name'].'.set_locale("december", "'.ucfirst(strftime('%B', mktime(0, 0, 0, 12, 1, 2010))).'");');

        $this->displayedItems = array();

        /* add items */
        foreach ($this->params['items'] as $id => $item) {
            $jsi = $this->params['name'].'.set_item({';
            $items = array();
            foreach ($item as $name => $value) {
            if ($name == 'date')
                $items[] = '"'.$name.'":'.$value.'000';
            elseif (is_string($value))
                $items[] = '"'.$name.'":"'.$value.'"';
            elseif (is_numeric($value))
                $items[] = '"'.$name.'":'.$value.'';
            }

            $jsi .= implode(',', $items).'});';
            $this->add_JSScript($jsi);

            /* back up item days */
            if (date('n', $item['date']) == $this->params['dateMonth']
                 and date('Y', $item['date']) == $this->params['dateYear']) {
                 if (!isset($this->displayedItems[date('j', $item['date'])]))
                     $this->displayedItems[date('j', $item['date'])] = array();
                 $this->displayedItems[date('j', $item['date'])][] = $id;
             }
        }
    }

    /* specific tool methods */

    /**
     * Return button url.
     * @param string $button
     * @param string $link
     * @return string
     */
    protected function get_buttonDisplay($button='', $link='') {
        $str = '';
        if ($this->params['buttonSource'] == 'text') {
            $str .= '<a href="'.$link.'" class="textual">';
            if ($button == 'left')
                $str .= '&lt;';
            elseif($button == 'right')
                $str .= '&gt;';
            $str .= '</a>';
        } else {
            $str .= '<a href="'.$link.'" class="img">';
            $str .= '<img alt="" border="0" src="';

            if ($this->params['buttonSource'] == 'theme') {
                $str .= $this->theme->get_pictURL($button, 12, 'std');
                $str .= '" onmouseover="this.src=\'';
                $str .= $this->theme->get_pictURL($button, 12, 'ovr');
                $str .= '\';" onmouseout="this.src=\'';
                $str .= $this->theme->get_pictURL($button, 12, 'std');
            } elseif ($this->params['buttonSource'] == 'plugin') {
                $str .= $this->get_fileURL('img/button_'.$button.'.gif');
                $str .= '" onmouseover="this.src=\'';
                $str .= $this->get_fileURL('img/button_'.$button.'_r.gif');
                $str .= '\';" onmouseout="this.src=\'';
                $str .= $this->get_fileURL('img/button_'.$button.'.gif');
            }
            $str .= '\';" />';
        }
        return $str;
    }
}
?>
