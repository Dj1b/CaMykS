<?php
/**
 * @brief Date related methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/date.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Oct 2005
 * @date Modification: Apr 2018
 * @copyright 2005 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/************ CONSTANTS **************************************/

/** 
 * @def TODAY
 */
define('TODAY',    time());

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
            return ucwords(strftime('%A %e %B %Y, %H:%M', $date));
        case 'en':
            return strftime('%A, %B the %e'.date('S', $date).' %Y, %H:%M', $date);
        case 'es':
            return ucwords(strftime('%A %e', $date)).' de '.ucwords(strftime('%B %Y, %H:%M', $date));
        default:
            return strftime('%A %e %B %Y, %H:%M', $date);
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
            return ucwords(strftime('%e %B %Y', $date)).string_html2text(' &agrave; '). strftime('%H:%M', $date);
        case 'en':
            return strftime('%e'.date('S', $date).' %B %Y, %H:%M', $date);
        case 'es':
            return strftime('%e', $date).' de '.ucwords(strftime('%B %Y, %H:%M', $date));
        default:
            return strftime('%e %B %Y, %H:%M', $date);
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
            return ucwords(strftime('%A %e %B %Y', $date));
        case 'en':
            return strftime('%A, %e'.date('S', $date).' %B %Y', $date);
        case 'es':
            return ucwords(strftime('%A %e', $date)).' de '.ucwords(strftime('%B %Y', $date));
        default:
            return strftime('%A %e %B %Y', $date);
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
            return ucwords(strftime('%e %B %Y', $date));
        case 'en':
            return strftime('%e'.date('S', $date).' %B %Y', $date);
        case 'es':
            return strftime('%e', $date).' de '.ucwords(strftime('%B %Y', $date));
        default:
            return strftime('%e %B %Y', $date);
    }
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
            return ucwords(strftime('%a %e %b %y - %H:%M', $date));
        case 'en':
            return strftime('%a %b %e'.date('S', $date).' %y, %H:%M', $date);
        default:
            return strftime('%a %e %b %y, %H:%M', $date);
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
            return ucwords(strftime('%e %b %y - %H:%M', $date));
        case 'en':
            return strftime('%b %e'.date('S', $date).' %y, %H:%M', $date);
        default:
            return strftime('%e %b %y, %H:%M', $date);
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
            return ucwords(strftime('%a %e %b %y', $date));
        case 'en':
            return strftime('%a %b %e'.date('S', $date).' %y', $date);
        default:
            return strftime('%a %e %b %y', $date);
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
            return ucwords(strftime('%e %b %y', $date));
        case 'en':
            return strftime('%b %e'.date('S', $date).' %y', $date);
        default:
            return strftime('%e %b %y', $date);
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
        return strftime('%e', $date1).' - '.ucwords(strftime('%e %b %y', $date2));
    
    if (date_isSameYear($date1, $date2))
        return ucwords(strftime('%e %b', $date1)).' - '.ucwords(strftime('%e %b %y', $date2));
    
    return ucwords(strftime('%e %b %y', $date1)).' - '.ucwords(strftime('%e %b %y', $date2));
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
            return strftime('%d/%m/%y - %H:%M', $date);
        case 'en':
            return strftime('%D - %H:%M', $date);
        default:
            return strftime('%D - %H:%M', $date);
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
            return strftime('%d/%m/%y', $date);
        case 'en':
            return strftime('%D', $date);
        default:
            return strftime('%D', $date);
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
            return strftime('%H:%M', $date);
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
    return strftime('%A', $date);
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
function date_displayLongFormat($date = TODAY, $language=null) {
    $language = date_getLanguage($language);
    switch ($language) {
        case 'fr':
            return strftime('%A %d %B %Y &agrave; %H:%M', $date);
        default:
            return strftime('%c', $date);
    }
}

/**
 * Return short date display.
 * @param date $date
 * @param string $language
 * @return string
 * @deprecated
 */
function date_displayShortFormat($date = TODAY, $language=null) {
    $language = date_getLanguage($language);
    switch ($language) {
        case 'fr':
            return strftime('%d/%m/%Y - %H:%M', $date);
        default:
            return strftime('%c', $date);
    }
}

/**
 * Return short date display.
 * @param date $date
 * @param string $language
 * @return string
 * @deprecated
 */
function date_displayQuickFormat($date = TODAY, $language=null) {
    $language = date_getLanguage($language);
    switch ($language) {
        case 'fr':
            return strftime('%d ', $date).ucfirst(strftime('%b. ', $date)).strftime('%y - %H:%M', $date);
        default:
            return strftime('%d %b. %y - %H:%M', $date);
    }
}

/**
 * Return date year display.
 * @param date $date
 * @param string $language
 * @return string
 * @deprecated
 */
function date_displayYear($date = TODAY, $language=null) {
    $language = date_getLanguage($language);
    switch ($language) {
        case 'fr':
        case 'en':
            return strftime('%Y', $date);
        default:
            return strftime('%Y', $date);
    }
}

/**
 * Return date year & month display.
 * @param date $date 
 * @param string $language
 * @return string
 * @deprecated
 */
function date_displayMonthAndYear($date = TODAY, $language=null) {
    $language = date_getLanguage($language);
    switch ($language) {
        case 'fr':
        case 'en':
        case 'es':
        case 'pt': case 'br':
            return ucfirst(strftime('%B %Y', $date));
        default:
            return strftime('%B %Y', $date);
    }
}

/**
 * Return date display.
 * @param date $date
 * @param string $language
 * @return string
 * @deprecated
 */
function date_displayDate($date = TODAY, $language=null) {
    $language = date_getLanguage($language);
    switch ($language) {
        case 'fr':
        case 'en':
            return ucfirst(strftime('%A %d %B %Y', $date));
        default:
            return strftime('%c', $date);
    }
}

/**
 * Return date display excepting year.
 * @param date $date
 * @param string $language
 * @return string
 * @deprecated
 */
function date_displayDayMonthAndHour($date = TODAY, $language=null) {
    $language = date_getLanguage ($language);
    switch ($language) {
        case 'fr':
            return strftime('%A %d %B &agrave; %H:%M', $date);
        default : 
            return strftime('%A %d %B - %H:%M', $date);
    }
}

/**
 * Return date day & hour display.
 * @param date $date
 * @param string $language
 * @return string
 * @deprecated
 */
function date_displayDayAndHour($date = TODAY, $language=null) {
    $language = date_getLanguage($language);
    switch ($language) {
        case 'fr':
            return strftime('%A %d &agrave; %H:%M', $date);
        default : 
            return strftime('%A %d - %H:%M', $date);
    }
}

/**
 * Return abbreviate date display.
 * @param date $date
 * @param string $language
 * @return string
 * @deprecated
 */
function date_displayQuickDate($date = TODAY, $language=null) {
    $language = date_getLanguage($language);
    switch ($language) {
        case 'fr':
            return strftime('%d ', $date).ucfirst(strftime('%b ', $date)).strftime('%y', $date);
        default:
            return strftime('%d %b. %y', $date);
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