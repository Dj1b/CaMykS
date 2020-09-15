<?php
/**
 * @brief Finance specific methods
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
 * Compute HT price from TTC price and VAT rate.
 * @param float $TTCPrice
 * @param float $VATRate
 * @return float
 */
function finance_getHTFromTTC($TTCPrice, $VATRate) {
     return $TTCPrice * 100 / (100 + $VATRate);
}

/**
 * Compute TTC price from HT price and VAT rate.
 * @param float $HTPrice
 * @param float $VATRate
 * @return float
 */
function finance_getTTCFromHT($HTPrice, $VATRate) {
     return $HTPrice * (100 + $VATRate) / 100;
}
?>
