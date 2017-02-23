<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Input Engine
 * Creation Date    : Dec 2014
 * Last Modif Date	: Dec 2014
 * History : 
 * * 14-12-05: Initial File
 * 
 * Generic vCard handler : import and export hCard
 */

class GenericVCardHandler_hCard {
  /*
   * constructor
   * @param Object $parent
   * @param array $params
   */
  function GenericVCardHandler_hCard ($parent, $params) {
    $this->parentInput = $parent;
    $this->params = $params;
  }
  
  /* specific action methods */
  
  /*
   * export vCard
   * @return mixed
   * @access private
   */
  function export_vCard() {
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
  
  /*
   * import vCard
   * @return mixed
   * @access private
   */
  function import_vCard() {
//   	echo "<b>IMPORT :</b> <br>" . nl2br(htmlspecialchars($this->params['source'])) . "<br/>";
  	
//   	//Object to return
//   	$result = array();
  	
//   	$parseResults = Mf2\parse($this->params['source']);
  	
//   	echo json_encode($parseResults, JSON_PRETTY_PRINT);
  	
//   	if(isset($parseResults["items"][0]["type"][0]) && $parseResults["items"][0]["type"][0] == "h-card"){
//    		foreach($parseResults["items"][0]["properties"] as $key=>$value) {
//   			if($key == "name")
//   				$result["full_name"] = $value[0];
//   			elseif($key == "org")
//   				$result["org_title"] = $value[0]; 
//   			elseif($key == "given-name")
//   				$result["name_first"] = $value[0]; 
//   			elseif($key == "family-name")
//   				$result["name_last"] = $value[0]; 
//   			elseif($key == "tel"){
//   				if (isset ( $result ['tels'] ) || array_key_exists ( 'tels', $result )) {
//   				} else
//   					$result ['tels'] = array ();
  				
//   				$newTel = array ();
//   				$newTel ["tel_number"] = $value[0];
//   				array_push ( $result ['tels'], $newTel );
//   			}elseif($key == "email"){ // Email				
// 				if (isset ( $result ['emails'] ) || array_key_exists ( 'emails', $result )) {
// 				} else
// 					$result ['emails'] = array ();
				
// 				$newMail = array ();
// 				$newMail ["email"] = $value[0];
								
// 				array_push ( $result ['emails'], $newMail );
// 			}elseif($key == "adr"){ 
// 				if(isset($value[0]["type"][0]) && $value[0]["type"][0] == "h-adr"){
// 					foreach($value[0]["properties"] as $keyAdr=>$valueAdr){
// 						if($keyAdr == "street-address")
// 							$result["addr_street"] = $valueAdr[0];
// 						elseif($keyAdr == "locality")
// 							$result["addr_city"] = $valueAdr[0];
// 						elseif($keyAdr == "region")
// 							$result["addr_region"] = $valueAdr[0];
// 						elseif($keyAdr == "postal-code")
// 							$result["addr_zipcode"] = $valueAdr[0];
// 						elseif($keyAdr == "country-name")
// 							$result["addr_country"] = $valueAdr[0];
						
// 					}
// 				}
// 			}
//   		}
//   	}
  	
//   	return $result;
  }
   
  



}
?>