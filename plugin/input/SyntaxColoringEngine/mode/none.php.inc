<?php
/**
 * @brief SyntaxColoringEngine Input colourisation mode.
 * @details Plugin / Input Library
 * @file plugin/input/SyntaxColoringEngine/mode/none.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: May 2007
 * @date Modification: Jul 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * SyntaxColoringEngine_none class.
 */
final class SyntaxColoringEngine_none {
    /*
     * Execute colourisation.
     * @param string $text
     * @param array $params
     * @return string
     */
    public function execute($text, $params) {
        return nl2br($text);
    }
}
?>
