<?php
/**
 * @brief PHP related methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Sep 2020
 * @date Modification: Sep 2020
 * @copyright 2020 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return PHP's error reporting level as string.
 * @param integer $errorLevel
 * @param string $separator
 * @return string
 */
function php_displayErrorReportingLevelAsString($errorLevel=null, $separator=', ') {
    /* Check level value */
    if (is_null($errorLevel)) $errorLevel = error_reporting();

    /* Define error level list */
    $errorLevels = array(
        E_ALL               => 'E_ALL',
        E_USER_DEPRECATED   => 'E_USER_DEPRECATED',
        E_DEPRECATED        => 'E_DEPRECATED',
        E_RECOVERABLE_ERROR => 'E_RECOVERABLE_ERROR',
        E_STRICT            => 'E_STRICT',
        E_USER_NOTICE       => 'E_USER_NOTICE',
        E_USER_WARNING      => 'E_USER_WARNING',
        E_USER_ERROR        => 'E_USER_ERROR',
        E_COMPILE_WARNING   => 'E_COMPILE_WARNING',
        E_COMPILE_ERROR     => 'E_COMPILE_ERROR',
        E_CORE_WARNING      => 'E_CORE_WARNING',
        E_CORE_ERROR        => 'E_CORE_ERROR',
        E_NOTICE            => 'E_NOTICE',
        E_PARSE             => 'E_PARSE',
        E_WARNING           => 'E_WARNING',
        E_ERROR             => 'E_ERROR',
    );

    /* Initialise results */
    $result = array();

    /* Tests all levels */
    foreach ($errorLevels as $level => $name) {
        if (($errorLevel & $level) == $level)
            $result[] = $name;
    }

    /* Return result */
    return implode($separator, $result);
}
?>
