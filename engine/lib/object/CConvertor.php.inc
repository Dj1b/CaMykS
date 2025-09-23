<?php
/**
 * @brief Convertor object.
 * @details Engine / Object Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Sep 2025
 * @date Modification: Sep 2025
 * @copyright 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * CConvertor class.
 */
final class CConvertor {
    /**
     * @var array $conversionData
     * @brief Available conversion data.
     */
    private $conversionData;

    /**
     * Object constructor.
     */
    public function __construct() {
        global $camyks;

        /* Load data */
        $this->conversionData = json_decode(file_get_contents($camyks->get_dataFilePath('data/Conversions.json.inc')), true);
    }

    /**
     * Convert value from one unit to another.
     * @param float $value
     * @param string $from
     * @param string $to
     * @return mixed
     */
    public function convert($value, $from, $to) {
        /* Check from and to available in conversion data */
        if (empty($this->conversionData[$from]))
            return false;
        if (empty($this->conversionData[$from][$to]))
            return false;

        /* Load formula */
        $formula = $this->conversionData[$from][$to];

        /* Initialise result */
        $result = $value;

        /* Run formula */
        foreach ($formula as $c) {
            switch ($c["operator"]) {
                case '+': $result += $c["value"]; break;
                case '-': $result -= $c["value"]; break;
                case '/': $result /= $c["value"]; break;
                case 'x': $result *= $c["value"]; break;
                case 'round': $result = round($result, $c["value"]); break;
                case 'ceil': $result = ceil($result); break;
                case 'floor': $result = floor($result); break;
                default: return false;
            }
        }

        /* Return result */
        return $result;
    }
}
?>

