<?php
/**
 * @brief GenericVCardHandler Input library to manage hCard format
 * @details Plugin / Input Library
 * @file plugin/input/GenericVCardHandler/lib/GenericVCardHandler-hCard.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Dec 2014
 * @date Modification: Jul 2018
 * @copyright 2014 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * GenericVCardHandler_hCard class.
 */
final class GenericVCardHandler_hCard {
    /**
     * Class constructor.
     * @param Object $parent
     * @param array $params
     * @return void
     */
    public function __constrcut($parent, $params) {
        $this->parentInput = $parent;
        $this->params = $params;
    }

    /* specific action methods */

    /**
     * Export vCard.
     * @return mixed
     */
    public function export_vCard() {
        $result = '<div class="h-card">';

        $result .='<style>.h-card a, .h-card span {display : block;}</style>';

        $result .= '<img class="u-photo" src="'.$this->params["photo_url"].'" alt="" />';

        $result .= '<a class="p-name u-url" href="'.$this->params["url"].'">'.$this->params["full_name"].'</a>';

        foreach($this->params["phones"] as $tel){
            $result .= '<span class="p-tel">'.$tel['phone_number'].'</span>';
        }

        foreach($this->params["emails"] as $mail){
            $result .= '<a class="u-email" href="mailto:'.$mail['email'].'">'.$mail['email'].'</a>';
        }

        $result .= '<span class="p-post-office-box">'.$this->params["addr_pobox"].'</span>';
        $result .= '<span class="p-extended-address ">'.$this->params["addr_extended"].'</span>';
        $result .= '<span class="p-street-address ">'.$this->params["addr_street"].'</span>';
        $result .= '<span class="p-locality ">'.$this->params["addr_city"].'</span>';
        $result .= '<span class="p-postal-code ">'.$this->params["addr_zipcode"].'</span>';
        $result .= '<span class="p-region">'.$this->params["addr_region"].'</span>';
        $result .= '<span class="p-country-name ">'.$this->params["addr_country"].'</span>';

        $result .= '</div>';
        return $result;
    }

    /**
     * Import vCard
     * @return mixed
     * @todo
     */
    public function import_vCard() {

    }
}
?>
