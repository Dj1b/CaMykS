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
 */

class GenericVCardHandler_jCard {
  /*
   * constructor
   * @param Object $parent
   * @param array $params
   */
  function GenericVCardHandler_jCard ($parent, $params) {
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
  	
  	$arrayData = array();
  	 
  	if(isset($this->params["full_name"])){
  		array_push ($arrayData, array("fn", json_decode ("{}"), "text", $this->params["full_name"]));
  	}
  	
  	if(isset($this->params["name_last"]) || isset($this->params["name_first"]) || isset($this->params["name_additional"]) ||
  			isset($this->params["name_prefix"]) || isset($this->params["name_suffix"])){
  		array_push ($arrayData, array("n", json_decode ("{}"), "text", array(
	  		$this->params["name_last"], $this->params["name_first"], $this->params["name_additional"],
	  		$this->params["name_prefix"], $this->params["name_suffix"]
  		)));
  	}
  	
  	if(isset($this->params["addresses"]) && is_array($this->params["addresses"])){
  		foreach($this->params["addresses"] as $addrIdx => $addr){
  			if(isset($addr["addr_pobox"]) || isset($addr["addr_extended"]) || isset($addr["addr_street"]) ||
  					isset($addr["addr_city"]) || isset($addr["addr_region"]) || isset($addr["addr_zipcode"])
  					|| isset($addr["addr_country"])){
  				array_push ($arrayData, array("adr", json_decode ("{}"), "text", array(
	  				$addr["addr_pobox"], $addr["addr_extended"], $addr["addr_street"],
	  				$addr["addr_city"], $addr["addr_region"], $addr["addr_zipcode"], $addr["addr_country"]
	  				)));
	  			}
  		}
  	}
  	 

  	
  	if(isset($this->params["phones"]) && is_array($this->params["phones"])){
  		foreach($this->params["phones"] as $telIdx => $tel){
  			$teltypeArray = array();
  			if(isset($tel["phone_type"]) && !empty($tel["phone_type"]))
  				array_push($teltypeArray, $tel["phone_type"]);
  			if(isset($tel["phone_location"]) && !empty($tel["phone_location"]))
  				array_push($teltypeArray, $tel["phone_location"]);
  			if(isset($tel["phone_pref"]) && $tel["phone_pref"] == true)
  				array_push($teltypeArray, 'pref');
  				
  			array_push ($arrayData, array("tel", array('type' => $teltypeArray), "uri", $tel["phone_number"]));
  		}
  	}
  	
  	if(isset($this->params["emails"]) && is_array($this->params["emails"])){
  		foreach($this->params["emails"] as $emailIdx => $email){
  			$emailtypeArray = array();
  			if(isset($email["email_location"]) && !empty($email["email_location"]))
  				array_push($emailtypeArray, $email["email_location"]);
  			if(isset($email["email_pref"]) && $email["email_pref"] == true)
  				array_push($emailtypeArray, 'pref');
  				
  			array_push ($arrayData, array("email", array('type' => $emailtypeArray), "text", $email["email"]));
  			
  		}
  	}
  	
  	
  	$arrayToConvert = array("vcard",  $arrayData );
  	return json_encode($arrayToConvert, JSON_PRETTY_PRINT);
  }
  
  /*
   * import vCard
   * @return mixed
   * @access private
   */
  function import_vCard() {
   	//array to return
   	$result = $this->parentInput->get_vCardDefaultParams();
   	$result['version'] = 'jCard';
  	
  	$contentJsonified =  json_decode($this->params['source'], true);
  	if(is_array($contentJsonified[1])){
  		foreach($contentJsonified[1] as $key=>$value){
  			if(is_array($value)){
				if($value[0] == "fn")
					$result["full_name"] = $value[3];
				elseif($value[0] == "n"){
					if(isset($value[3]) && is_array($value[3])){
						if(isset($value[3][0]))
							$result ['name_last'] = $value[3][0];
						else
							$result ['name_last'] = "";
						if(isset($value[3][1]))
							$result ['name_first'] = $value[3][1];
						else
							$result ['name_first'] = "";
						if(isset($value[3][2]))
							$result ['name_additional'] = $value[3][2];
						else
							$result ['name_additional'] = "";
						if(isset($value[3][3]))
							$result ['name_prefix'] = $value[3][3];
						else
							$result ['name_prefix'] = "";
						if(isset($value[3][4]))
							$result ['name_suffix'] = $value[3][4];
						else
							$result ['name_suffix'] = "";
					}
				}elseif($value[0] == "adr"){
					if (isset ( $result ['addresses'] ) || array_key_exists ( 'addresses', $result )) {
					} else
						$result ['addresses'] = array ();
					
					$newAddr = array (
							'addr_location'=>'', // home / work
							'addr_pref'=>'',
							'addr_pobox'=>'', // Post office box
							'addr_extended'=>'', // Extended address: building, stair, apartment or suite number
							'addr_street'=>'', // Street address
							'addr_city'=>'',
							'addr_zipcode'=>'',
							'addr_region'=>'', // State or province
							'addr_country'=>'',
							'addr_countrycode'=>'',
							'addr_label'=>'',
						);
					
					if(isset($value[3]) && is_array($value[3])){
						if(isset($value[3][0]))
							$newAddr ['addr_pobox'] = $value[3][0];
						else
							$newAddr ['addr_pobox'] = "";
						if(isset($value[3][1]))
							$newAddr ['addr_extended'] = $value[3][1];
						else
							$newAddr ['addr_extended'] = "";
						if(isset($value[3][2]))
							$newAddr ['addr_street'] = $value[3][2];
						else
							$newAddr ['addr_street'] = "";
						if(isset($value[3][3]))
							$newAddr ['addr_city'] = $value[3][3];
						else
							$newAddr ['addr_city'] = "";
						if(isset($value[3][5]))
							$newAddr ['addr_zipcode'] = $value[3][5];
						else
							$newAddr ['addr_zipcode'] = "";
						if(isset($value[3][4]))
							$newAddr ['addr_region'] = $value[3][4];
						else
							$newAddr ['addr_region'] = "";
						if(isset($value[3][6])){
							$newAddr ['addr_country'] = $value[3][6];

							if($value[3][6] != ""){
								$countrycode = $this->parentInput->getCountryCode($value[3][6]);
								if($countrycode)
									$newAddr ['addr_countrycode'] = str_replace("country_", "", $countrycode);
							}
						}else
							$newAddr ['addr_country'] = "";
						
						
					}
					
					array_push ( $result ['addresses'], $newAddr );
				} elseif($value[0] == "tel"){
					if (isset ( $result ['phones'] ) || array_key_exists ( 'phones', $result )) {
					} else
						$result ['phones'] = array ();
					
					$newphone = array (
							'phone_type'=>'voice', // "text" / "voice" / "fax" / "cell" / "video" / "pager" / "textphone" / "msg" / "modem" / "car" / "isdn"
							'phone_number'=>'',
							'phone_location'=>'', // home / work
							'phone_pref'=>'',
						);
					
					$phonenum = explode ( ';', $value[3] );
					$newphone ["phone_number"] = str_replace('tel:', '', $phonenum[0]);;
					
					if(isset($value[1]) && isset($value[1]["type"]) && is_array($value[1]["type"])){
						foreach ( $value[1]["type"] as $phonetype ) {
							if ($phonetype == "voice" || $phonetype == "text" || $phonetype == "fax" || $phonetype == "cell" || $phonetype == "video" || $phonetype == "pager" || $phonetype == "textphone")
								$newphone ["phone_type"] = $phonetype;
							elseif ($phonetype == "home" || $phonetype == "work")
							$newphone ["phone_location"] = $phonetype;
							elseif ($phonetype == "pref")
							$newphone ["phone_pref"] = true;
						}
						
					}
					
					array_push ( $result ['phones'], $newphone );
				} elseif($value[0] == "email"){
					if (isset ( $result ['emails'] ) || array_key_exists ( 'emails', $result )) {
					} else
						$result ['emails'] = array ();
					
					$newMail = array (
							'email'=> '',
							'email_location'=>'', // home / work
							'email_pref'=>'',
						);
					$newMail ["email"] = $value[3];
					
					if(isset($value[1]) && isset($value[1]["type"]) && is_array($value[1]["type"])){
						foreach ( $value[1]["type"] as $emailtype ) {
								if ($emailtype == "home" || $emailtype == "work")
									$newMail ["email_location"] = $emailtype;
								elseif ($emailtype == "pref")
									$newMail ["email_pref"] = true;
							}
						
					}
					
					array_push ( $result ['emails'], $newMail );
				}
  			}
  		}
  	}
  	
  	return $result;
  }


}
?>