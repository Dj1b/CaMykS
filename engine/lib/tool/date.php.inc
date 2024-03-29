<?php
/**
 * @brief Date specific methods.
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.7
 * @date Creation: Oct 2005
 * @date Modification: Nov 2023
 * @copyright 2005 - 2023 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/************ CONSTANTS **************************************/

/**
 * @def TODAY
 */
define('TODAY',   time());

/************ DATE DISPLAY ***********************************/

/**
 * Display long textual representation of day, date and hour.
 * @param date $date
 * @return string
 */
function date_displayLongDayDateHour($date=TODAY) {
    global $camyks;
    $l = $camyks->current_language;
    switch ($l) {
        case 'fr':
            return ucwords(date_strftime('%A %e %B %Y, %H:%M', $date));
        case 'en':
            return date_strftime('%A, %B', $date).' the '. date_strftime('%e', $date).date('S', $date).date_strftime(' %Y, %H:%M', $date);
        case 'es':
            return ucwords(date_strftime('%A %e', $date)).' de '.ucwords(date_strftime('%B %Y, %H:%M', $date));
        default:
            return date_strftime('%A %e %B %Y, %H:%M', $date);
    }
}

/**
 * Display long textual representation of date and hour.
 * @param date $date
 * @return string
 */
function date_displayLongDateHour($date=TODAY) {
    global $camyks;
    $l = $camyks->current_language;
    switch ($l) {
        case 'fr':
            return ucwords(date_strftime('%e %B %Y', $date)).string_html2text(' &agrave; '). date_strftime('%H:%M', $date);
        case 'en':
            return date_strftime('%e', $date).date('S', $date).date_strftime(' %B %Y, %H:%M', $date);
        case 'es':
            return date_strftime('%e', $date).' de '.ucwords(date_strftime('%B %Y, %H:%M', $date));
        default:
            return date_strftime('%e %B %Y, %H:%M', $date);
    }
}

/**
 * Display long textual representation of day and date.
 * @param date $date
 * @return string
 */
function date_displayLongDayDate($date=TODAY) {
    global $camyks;
    $l = $camyks->current_language;
    switch ($l) {
        case 'fr':
            return ucwords(date_strftime('%A %e %B %Y', $date));
        case 'en':
            return date_strftime('%A, %e', $date).date('S', $date).date_strftime(' %B %Y', $date);
        case 'es':
            return ucwords(date_strftime('%A %e', $date)).' de '.ucwords(date_strftime('%B %Y', $date));
        default:
            return date_strftime('%A %e %B %Y', $date);
    }
}

/**
 * Display long textual representation of date.
 * @param date $date
 * @return string
 */
function date_displayLongDate($date=TODAY) {
    global $camyks;
    $l = $camyks->current_language;
    switch ($l) {
        case 'fr':
            return ucwords(date_strftime('%e %B %Y', $date));
        case 'en':
            return date_strftime('%e', $date).date('S', $date).date_strftime(' %B %Y', $date);
        case 'es':
            return date_strftime('%e', $date).' de '.ucwords(date_strftime('%B %Y', $date));
        default:
            return date_strftime('%e %B %Y', $date);
    }
}

/**
 * Display long textual representation of date interval.
 * @param date $date1
 * @param date $date2
 * @return string
 */
function date_displayLongDateInterval($date1=TODAY, $date2=TODAY) {
    global $camyks;
    $l = $camyks->current_language;

    if ($date1 > $date2) {
        $tmp = $date1;
        $date1 = $date2;
        $date2 = $tmp;
        unset($tmp);
    }

    if (date_isSameDay($date1, $date2))
        return date_displayShortDate($date1);

    if (date_isSameMonth($date1, $date2))
        return date_strftime('%e', $date1).' - '.ucwords(date_strftime('%e %B %Y', $date2));

    if (date_isSameYear($date1, $date2))
        return ucwords(date_strftime('%e %B', $date1)).' - '.ucwords(date_strftime('%e %B %Y', $date2));

    return ucwords(date_strftime('%e %B %Y', $date1)).' - '.ucwords(date_strftime('%e %B %Y', $date2));
}

/**
 * Display short textual representation of day, date and hour.
 * @param date $date
 * @return string
 */
function date_displayShortDayDateHour($date=TODAY) {
    global $camyks;
    $l = $camyks->current_language;
    switch ($l) {
        case 'fr':
            return ucwords(date_strftime('%a %e %b %y - %H:%M', $date));
        case 'en':
            return date_strftime('%a %b %e'.date('S', $date).' %y, %H:%M', $date);
        default:
            return date_strftime('%a %e %b %y, %H:%M', $date);
    }
}

/**
 * Display short textual representation of date and hour.
 * @param date $date
 * @return string
 */
function date_displayShortDateHour($date=TODAY) {
    global $camyks;
    $l = $camyks->current_language;
    switch ($l) {
        case 'fr':
            return ucwords(date_strftime('%e %b %y - %H:%M', $date));
        case 'en':
            return date_strftime('%b %e'.date('S', $date).' %y, %H:%M', $date);
        default:
            return date_strftime('%e %b %y, %H:%M', $date);
    }
}

/**
 * Display short textual representation of day and date.
 * @param date $date
 * @return string
 */
function date_displayShortDayDate($date=TODAY) {
    global $camyks;
    $l = $camyks->current_language;
    switch ($l) {
        case 'fr':
            return ucwords(date_strftime('%a %e %b %y', $date));
        case 'en':
            return date_strftime('%a %b %e'.date('S', $date).' %y', $date);
        default:
            return date_strftime('%a %e %b %y', $date);
    }
}

/**
 * Display short textual representation of date.
 * @param date $date
 * @return string
 */
function date_displayShortDate($date=TODAY) {
    global $camyks;
    $l = $camyks->current_language;
    switch ($l) {
        case 'fr':
            return ucwords(date_strftime('%e %b %y', $date));
        case 'en':
            return date_strftime('%b %e'.date('S', $date).' %y', $date);
        default:
            return date_strftime('%e %b %y', $date);
    }
}

/**
 * Display short textual representation of date interval.
 * @param date $date1
 * @param date $date2
 * @return string
 */
function date_displayShortDateInterval($date1=TODAY, $date2=TODAY) {
    global $camyks;
    $l = $camyks->current_language;

    if ($date1 > $date2) {
        $tmp = $date1;
        $date1 = $date2;
        $date2 = $tmp;
        unset($tmp);
    }

    if (date_isSameDay($date1, $date2))
        return date_displayShortDate($date1);

    if (date_isSameMonth($date1, $date2))
        return date_strftime('%e', $date1).' - '.ucwords(date_strftime('%e %b %y', $date2));

    if (date_isSameYear($date1, $date2))
        return ucwords(date_strftime('%e %b', $date1)).' - '.ucwords(date_strftime('%e %b %y', $date2));

    return ucwords(date_strftime('%e %b %y', $date1)).' - '.ucwords(date_strftime('%e %b %y', $date2));
}

/**
 * Display numeric representation of date and hour.
 * @param date $date
 * @return string
 */
function date_displayNumericDateHour($date=TODAY) {
    global $camyks;
    $l = $camyks->current_language;
    switch ($l) {
        case 'fr':
            return date_strftime('%d/%m/%y - %H:%M', $date);
        case 'en':
            return date_strftime('%D - %H:%M', $date);
        default:
            return date_strftime('%D - %H:%M', $date);
    }
}

/**
 * Display numeric representation of date.
 * @param date $date
 * @return string
 */
function date_displayNumericDate($date=TODAY) {
    global $camyks;
    $l = $camyks->current_language;
    switch ($l) {
        case 'fr':
            return date_strftime('%d/%m/%y', $date);
        case 'en':
            return date_strftime('%D', $date);
        default:
            return date_strftime('%D', $date);
    }
}

/**
 * Display time.
 * @param date $date
 * @return string
 */
function date_displayTime($date=TODAY) {
    global $camyks;
    $l = $camyks->current_language;
    switch ($l) {
        default:
            return date_strftime('%H:%M', $date);
    }
}

/**
 * Display day.
 * @param date $date can be a week day
 * @return string
 */
function date_displayDay($date=TODAY) {
    if ($date <= 7)
        $date = mktime(0, 0, 0, 1, 2+$date, 0);
    return date_strftime('%A', $date);
}

/**
 * Display month.
 * @param date $date can be a month
 * @return string
 */
function date_displayMonth($date=TODAY) {
    if ($date > 0 and $date <= 12)
        $date = mktime(0, 0, 0, $date, 1, 0);
    return date_strftime('%B', $date);
}

/**
 * Display duration.
 * @param int $duration
 * @param array $params
 * @return string
 */
function date_displayDuration($duration, $params=array()) {
    global $camyks;

    /* Merge params */
    $defaultParams = array('displaySeconds'=>true, 'displayMinutes'=>true, 'displayHours'=>true, 'displayDays'=>true, 'format'=>'long');
    $params = array_merge($defaultParams, $params);

    /* Prepare values */
    $second = 1;
    $minute = $second * 60;
    $hour = $minute *60;
    $day = $hour *24;

    /* Load units library */
    include_once('units.php.inc');
    units_loadLocales();

    /* Initialise result */
    $result = array();

    /* Check for days */
    if ($params['displayDays']) {
        $days = floor($duration/$day);
        if ($days > 0 or ($params['displayHours'] === false and $params['displayMinutes'] === false and $params['displaySeconds'] === false)) {
            if ($params['format'] === 'short')
                $result[] = $camyks->get_translation('unit_xdays_short', $days);
            elseif ($days == 0)
                $result[] = $camyks->get_translation('unit_0day');
            elseif ($days == 1)
                $result[] = $camyks->get_translation('unit_1day');
            else
                $result[] = $camyks->get_translation('unit_xdays', $days);
            $duration -= $days*$day;
        }
    }

    /* Check for hours */
    if ($params['displayHours']) {
        $hours = floor($duration/$hour);
        if ($hours > 0 or (count($result) == 0 and $params['displayMinutes'] === false and $params['displaySeconds'] === false)) {
            if ($params['format'] === 'short')
                $result[] = $camyks->get_translation('unit_xhours_short', $hours);
            elseif ($hours == 0)
                $result[] = $camyks->get_translation('unit_0hour');
            elseif ($hours == 1)
                $result[] = $camyks->get_translation('unit_1hour');
            else
                $result[] = $camyks->get_translation('unit_xhours', $hours);
            $duration -= $hours*$hour;
        }
    }

    /* Check for minutes */
    if ($params['displayMinutes']) {
        $minutes = floor($duration/$minute);
        if ($minutes > 0 or (count($result) == 0 and $params['displaySeconds'] === false)) {
            if ($params['format'] === 'short')
                $result[] = $camyks->get_translation('unit_xminutes_short', $minutes);
            elseif ($minutes == 0)
                $result[] = $camyks->get_translation('unit_0minute');
            elseif ($minutes == 1)
                $result[] = $camyks->get_translation('unit_1minute');
            else
                $result[] = $camyks->get_translation('unit_xminutes', $minutes);
            $duration -= $minutes*$minute;
        }
    }

    /* Check for seconds */
    if ($params['displaySeconds']) {
        $seconds = floor($duration/$second);
        if ($seconds > 0 or count($result) == 0) {
            if ($params['format'] === 'short')
                $result[] = $camyks->get_translation('unit_xseconds_short', $seconds);
            elseif ($seconds == 0)
                $result[] = $camyks->get_translation('unit_0second');
            elseif ($seconds == 1)
                $result[] = $camyks->get_translation('unit_1second');
            else
                $result[] = $camyks->get_translation('unit_xseconds', $seconds);
            $duration -= $seconds*$second;
        }
    }

    /* Return result */
    return implode(', ', $result);
}

/**
 * Alias to date_displayLongDayDateHour
 * Display long textual representation of day, date and hour
 * @see date_displayLongDayDateHour()
 * @param date $date
 * @return string
 */
function date_display($date=TODAY) {
    return date_displayLongDayDateHour($date);
}

/************ DATE TESTS *************************************/

/**
 * Check if dates are the same day.
 * @param date $date1
 * @param date $date2
 * @return boolean
 */
function date_isSameDay($date1=TODAY, $date2=TODAY) {
    return mktime(0, 0, 0, date('m', $date1), date('d', $date1), date('Y', $date1)) ==
        mktime(0, 0, 0, date('m', $date2), date('d', $date2), date('Y', $date2));
}

/**
 * Check if dates are the same month.
 * @param date $date1
 * @param date $date2
 * @return boolean
 */
function date_isSameMonth($date1=TODAY, $date2=TODAY) {
    return mktime(0, 0, 0, date('m', $date1), 1, date('Y', $date1)) ==
        mktime(0, 0, 0, date('m', $date2), 1, date('Y', $date2));
}

/**
 * Check if dates are the same year.
 * @param date $date1
 * @param date $date2
 * @return boolean
 */
function date_isSameYear($date1=TODAY, $date2=TODAY) {
    return date('Y', $date1) == date('Y', $date2);
}

/**
 * Check if date is today.
 * @param date $date
 * @return boolean
 */
function date_isToday($date=TODAY) {
    return date_isSameDay($date);
}

/**
 * Check if date is tomorrow.
 * @param date $date
 * @return boolean
 */
function date_isTomorrow($date=TODAY) {
    return mktime(0, 0, 0, date('m', $date), date('d', $date), date('Y', $date)) == date_getTomorrowValue();
}

/**
 * Check if provided date is yesterday.
 * @param date $date
 * @return boolean
 */
function date_isYesterday($date=TODAY) {
    return mktime(0, 0, 0, date('m', $date), date('d', $date), date('Y', $date)) == date_getYesterdayValue();
}

/**
 * Compare times.
 * @param date $date1
 * @param date $date2
 * @return integer
 */
function date_compareTimes($date1=TODAY, $date2=TODAY) {
    if (date('G', $date1) > date('G', $date2))
        return -1;
    elseif (date('G', $date1) < date('G', $date2))
        return 1;
    if (date('i', $date1) > date('i', $date2))
        return -1;
    elseif (date('i', $date1) < date('i', $date2))
        return 1;
    if (date('s', $date1) > date('s', $date2))
        return -1;
    elseif (date('s', $date1) < date('s', $date2))
        return 1;
    return 0;
}

/******************** USEFULL DATE QUERIES *****************/

/**
 * Return today at 0h0m value.
 * @return date
 */
function date_getTodayValue() {
    return mktime(0, 0, 0, date('m'), date('d'), date('Y'));
}

/**
 * Return tomorrow at 0h0m value.
 * @return date
 */
function date_getTomorrowValue() {
    return mktime(0, 0, 0, date('m'), date('d')+1, date('Y'));
}

/**
 * Return yesterday at 0h0m value.
 * @return date
 */
function date_getYesterdayValue() {
    return mktime(0, 0, 0, date('m'), date('d')-1, date('Y'));
}

/**
 * Return first day of current week at 0h0m value.
 * @return date
 */
function date_getThisWeekValue() {
    if (date('w') == 0)
        return mktime(0, 0, 0, date('m'), date('d')-6, date('Y'));
    return mktime(0, 0, 0, date('m'), date('d')-date('w')+1, date('Y'));
}

/**
 * Return first day of next week at 0h0m value.
 * @return date
 */
function date_getNextWeekValue() {
    if (date('w') == 0)
        return mktime(0, 0, 0, date('m'), date('d')+1, date('Y'));
    return mktime(0, 0, 0, date('m'), date('d')+-date('w')+7, date('Y'));
}

/**
 * Return first day of last week at 0h0m value.
 * @return date
 */
function date_getLastWeekValue() {
    if (date('w') == 0)
        return mktime(0, 0, 0, date('m'), date('d')-13, date('Y'));
    return mktime(0, 0, 0, date('m'), date('d')-date('w')-6, date('Y'));
}

/**
 * Return first day of current month at 0h0m value.
 * @return date
 */
function date_getThisMonthValue() {
    return mktime(0, 0, 0, date('m'), 1, date('Y'));
}

/**
 * Return first day of next month at 0h0m value.
 * @return date
 */
function date_getNextMonthValue() {
    return mktime(0, 0, 0, date('m')+1, 1, date('Y'));
}

/**
 * Return first day of last month at 0h0m value.
 * @return date
 */
function date_getLastMonthValue() {
    return mktime(0, 0, 0, date('m')-1, 1, date('Y'));
}

/**
 * Return first day of current month at 0h0m value.
 * @return date
 */
function date_getThisYearValue() {
    return mktime(0, 0, 0, 1, 1, date('Y'));
}

/**
 * Return first day of next month at 0h0m value.
 * @return date
 */
function date_getNextYearValue() {
    return mktime(0, 0, 0, 1, 1, date('Y')+1);
}

/**
 * Return first day of last month at 0h0m value.
 * @return date
 */
function date_getLastYearValue() {
    return mktime(0, 0, 0, 1, 1, date('Y')-1);
}

/**
 * Return ordinal suffix for date.
 * @param int $date
 * @return string
 */
function date_getOrdinalSuffix($date=0) {
    global $camyks;

    /* return empty string for all non-english languages */
    if ($camyks->current_language != 'en')
        return '';

    /* check date */
    if ($date==0) $date = mktime();

    /* get day */
    $num = date('d', $date);

    /* check day */
    if ($num < 11 || $num > 13) {
        switch($num % 10){
            case 1: return 'st';
            case 2: return 'nd';
            case 3: return 'rd';
        }
    }
    return 'th';
}

/**
 * Return string formatted date to timestamp.
 * @param string $date
 * @return int
 */
function date_stringToTimestamp($date) {
    if (is_int($date))
        return $date;

    $date = date_parse($date);

    return mktime($date['hour'], $date['minute'], $date['second'], $date['month'], $date['day'], $date['year']);
}

/* Holidays related methods */

/**
 * Return New Year's day for given year.
 * @param integer $year
 * @return int
 */
function date_getNewYearsDay($year=null) {
    /* Check year value */
    if (is_null($year)) $year = date('Y');

    /* Return computed day */
    return mktime(0, 0, 0, 1, 1, $year);
}

/**
 * Return Easter day for given year.
 * @param integer $year
 * @return integer
 */
function date_getEasterDay($year=null) {
    /* Check year value */
    if (is_null($year)) $year = date('Y');

    $a = $year % 4;
    $b = $year % 7;
    $c = $year % 19;
    $m = 24;
    $n = 5;
    $d = (19 * $c + $m ) % 30;
    $e = (2 * $a + 4 * $b + 6 * $d + $n) % 7;

    $easterdate = 22 + $d + $e;

    if ($easterdate > 31) {
        $day = $d + $e - 9;
        $month = 4;
    } else {
        $day = 22 + $d + $e;
        $month = 3;
    }

    if ($d == 29 && $e == 6) {
        $day = 10;
        $month = 04;
    } elseif ($d == 28 && $e == 6) {
        $day = 18;
        $month = 04;
    }

    /* Return computed day */
    return mktime(0, 0, 0, $month, $day, $year);
}

/**
 * Return Ascension day for given year (or Easter day)
 * @param integer $year
 * @param integer $easter
 * @return integer
 */
function date_getAscensionDay($year=null, $easter=null) {
    if ($easter !== null)
        $day = $easter;
    else
        $day = date_getEasterDay($year);

    return mktime(0, 0, 0, date('n', $day), date('j', $day)+39, date('Y', $day));
}

/**
 * Return Pentecost day for given year (or Easter day)
 * @param integer $year
 * @param integer $easter
 * @return integer
 */
function date_getPentecostDay($year=null, $easter=null) {
    if ($easter !== null)
        $day = $easter;
    else
        $day = date_getEasterDay($year);

    return mktime(0, 0, 0, date('n', $day), date('j', $day)+50, date('Y', $day));
}

/**
 * Return Assumption day for given year.
 * @param integer $year
 * @return integer
 */
function date_getAssumptionDay($year=null) {
    /* Check year value */
    if (is_null($year)) $year = date('Y');

    /* Return computed day */
    return mktime(0, 0, 0, 8, 15, $year);
}

/**
 * Return All Saints day for given year.
 * @param integer $year
 * @return integer
 */
function date_getAllSaintsDay($year=null) {
    /* Check year value */
    if (is_null($year)) $year = date('Y');

    /* Return computed day */
    return mktime(0, 0, 0, 11, 1, $year);
}

/**
 * Return Christmas day for given year.
 * @param integer $year
 * @return integer
 */
function date_getChristmasDay($year=null) {
    /* Check year value */
    if (is_null($year)) $year = date('Y');

    /* Return computed day */
    return mktime(0, 0, 0, 12, 25, $year);
}

/************ PHP Replacement methods *******************/

/**
 * Replacement for strftime php method that is deprecated with PHP 8.1.
 * @param string $format
 * @param integer $date
 * @return string
 */
function date_strftime($format, $date=TODAY) {
    global $camyks, $languages;
    if (version_compare(PHP_VERSION, '7.0.0', '>=') and class_exists('IntlDateFormatter')) {
        $format = preg_replace(array('#%A#', '#%e#', '#%B#', '#%Y#', '#%H#', '#%M#', '#%a#', '#%b#', '#%y#', '#%d#', '#%m#', '#%D#'),
                               array('eeee', 'd', 'MMMM', 'yyyy', 'HH', 'mm', 'eee', 'MMM', 'yy', 'dd', 'MM', 'dd/MM/yyyy'), $format);
        $df = new IntlDateFormatter($camyks->current_language, IntlDateFormatter::FULL, IntlDateFormatter::FULL, $camyks->get_confValue('TimeZone'), IntlDateFormatter::GREGORIAN, $format);
        return $df->format($date);
    }
    return strftime($format, $date);
}

/************ DEPRECATED *******************/

/**
 * Return valid language.
 * @param string $language
 * @return string
 * @deprecated
 */
function date_getLanguage($language=null) {
    global $camyks;
    return isset ($language) ? $language : $camyks->current_language;
}

/**
 * Return date display with complete day and month name.
 * @param date $date
 * @param string $language
 * @return string
 * @deprecated
 */
function date_displayLongFormat($date=TODAY, $language=null) {
    $language = date_getLanguage($language);
    switch ($language) {
        case 'fr':
            return date_strftime('%A %d %B %Y &agrave; %H:%M', $date);
        default:
            return date_strftime('%c', $date);
    }
}

/**
 * Return short date display.
 * @param date $date
 * @param string $language
 * @return string
 * @deprecated
 */
function date_displayShortFormat($date=TODAY, $language=null) {
    $language = date_getLanguage($language);
    switch ($language) {
        case 'fr':
            return date_strftime('%d/%m/%Y - %H:%M', $date);
        case 'en':
            return date_strftime('%d/%m/%Y - %H:%M', $date);
        default:
            return date_strftime('%d/%m/%Y - %H:%M', $date);
    }
}

/**
 * Return short date display.
 * @param date $date
 * @param string $language
 * @return string
 * @deprecated
 */
function date_displayQuickFormat($date=TODAY, $language=null) {
    $language = date_getLanguage($language);
    switch ($language) {
        case 'fr':
            return date_strftime('%d ', $date).ucfirst(date_strftime('%b. ', $date)).date_strftime('%y - %H:%M', $date);
        default:
            return date_strftime('%d %b. %y - %H:%M', $date);
    }
}

/**
 * Return date year display.
 * @param date $date
 * @param string $language
 * @return string
 * @deprecated
 */
function date_displayYear($date=TODAY, $language=null) {
    $language = date_getLanguage($language);
    switch ($language) {
        case 'fr':
        case 'en':
            return date_strftime('%Y', $date);
        default:
            return date_strftime('%Y', $date);
    }
}

/**
 * Return date year & month display.
 * @param date $date
 * @param string $language
 * @return string
 * @deprecated
 */
function date_displayMonthAndYear($date=TODAY, $language=null) {
    $language = date_getLanguage($language);
    switch ($language) {
        case 'fr':
        case 'en':
        case 'es':
        case 'pt': case 'br':
            return ucfirst(date_strftime('%B %Y', $date));
        default:
            return date_strftime('%B %Y', $date);
    }
}

/**
 * Return date display.
 * @param date $date
 * @param string $language
 * @return string
 * @deprecated
 */
function date_displayDate($date=TODAY, $language=null) {
    $language = date_getLanguage($language);
    switch ($language) {
        case 'fr':
        case 'en':
            return ucfirst(date_strftime('%A %d %B %Y', $date));
        default:
            return date_strftime('%c', $date);
    }
}

/**
 * Return date display excepting year.
 * @param date $date
 * @param string $language
 * @return string
 * @deprecated
 */
function date_displayDayMonthAndHour($date=TODAY, $language=null) {
    $language = date_getLanguage ($language);
    switch ($language) {
        case 'fr':
            return date_strftime('%A %d %B &agrave; %H:%M', $date);
        default :
            return date_strftime('%A %d %B - %H:%M', $date);
    }
}

/**
 * Return date day & hour display.
 * @param date $date
 * @param string $language
 * @return string
 * @deprecated
 */
function date_displayDayAndHour($date=TODAY, $language=null) {
    $language = date_getLanguage($language);
    switch ($language) {
        case 'fr':
            return date_strftime('%A %d &agrave; %H:%M', $date);
        default :
            return date_strftime('%A %d - %H:%M', $date);
    }
}

/**
 * Return abbreviate date display.
 * @param date $date
 * @param string $language
 * @return string
 * @deprecated
 */
function date_displayQuickDate($date=TODAY, $language=null) {
    $language = date_getLanguage($language);
    switch ($language) {
        case 'fr':
            return date_strftime('%d ', $date).ucfirst(date_strftime('%b ', $date)).date_strftime('%y', $date);
        default:
            return date_strftime('%d %b. %y', $date);
    }
}

/**
 * Alias to display time.
 * @see date_displayTime()
 * @param date $date
 * @return string
 * @deprecated
 */
function date_displayHour($date=TODAY) {
    return date_displayTime($date);
}
?>
