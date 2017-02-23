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
 * * 14-12- 4: Initial File
 * 
 * Generic vCard handler : import and export xCard
 */

class GenericVCardHandler_xCard {
  /*
   * constructor
   * @param Object $parent
   * @param array $params
   */
  function GenericVCardHandler_xCard ($parent, $params) {
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
  		$arrayData["fn"] = array("text" => $this->params["full_name"]);
  	}
  	
  	if(isset($this->params["name_last"]) || isset($this->params["name_first"]) || isset($this->params["name_additional"]) || 
  			isset($this->params["name_prefix"]) || isset($this->params["name_suffix"])){
  		$arrayData["n"] = array(
  				"surname" => $this->params["name_last"],
  				"given" => $this->params["name_first"],
  				"additional" => $this->params["name_additional"],
  				"prefix" => $this->params["name_prefix"],
  				"suffix" => $this->params["name_suffix"]  				
  		);
  	}
  	
  	if(isset($this->params["addresses"]) && is_array($this->params["addresses"])){
  		foreach($this->params["addresses"] as $addrIdx => $addr){
  			
  			if(isset($this->params["addr_pobox"]) || isset($this->params["addr_extended"]) || isset($this->params["addr_street"]) ||
  					isset($this->params["addr_city"]) || isset($this->params["addr_region"]) || isset($this->params["addr_country"])){
  				$addrtypeArray = array();
  				if(isset($addr["addr_type"]) && !empty($addr["addr_type"]))
  					$addrtypeArray["text0"] = $addr["addr_type"];
  				if(isset($addr["addr_location"]) && !empty($addr["addr_location"]))
  					$addrtypeArray["text1"] = $addr["addr_location"];
  				if(isset($addr["addr_pref"]) && $addr["addr_pref"] == true)
  					$addrtypeArray["text2"] = "PREF";
  				
  				
  				
  				$arrayData["adr" . $addrIdx] = array(
  						"parameters" => array(
  								"type" => $addrtypeArray
  						),
  						"pobox" => $addr["addr_pobox"],
  						"ext" => $addr["addr_extended"],
  						"street" => $addr["addr_street"],
  						"locality" => $addr["addr_city"],
  						"region" => $addr["addr_region"],
  						"code" => $addr["addr_zipcode"],
  						"country" => $addr["addr_country"],
  				);
  			}
  		}
  	}
  	
  	if(isset($this->params["phones"]) && is_array($this->params["phones"])){
  		foreach($this->params["phones"] as $phoneIdx => $phone){
  			$phonetypeArray = array();
  			if(isset($phone["phone_type"]) && !empty($phone["phone_type"]))
  				$phonetypeArray["text0"] = $phone["phone_type"];
  			if(isset($phone["phone_location"]) && !empty($phone["phone_location"]))
  				$phonetypeArray["text1"] = $phone["phone_location"];
  			if(isset($phone["phone_pref"]) && !$phone["phone_pref"] == true)
  				$phonetypeArray["text2"] = "PREF";
  			
  			$arrayData["tel" . $phoneIdx] = array(
  					"parameters" => array(
  						"type" => $phonetypeArray
  					),
  					"uri" => $phone["phone_number"]
  			);
  		}
  	}
  	
  	if(isset($this->params["emails"]) && is_array($this->params["emails"])){
  		foreach($this->params["emails"] as $emailIdx => $email){
  			$emailtypeArray = array();
  			if(isset($email["email_location"]) && !empty($email["email_location"]))
  				$emailtypeArray["text1"] = $email["email_location"];
  			if(isset($email["email_pref"]) && $email["email_pref"] == true)
  				$emailtypeArray["text2"] = "PREF";
  			
  			$arrayData["email" . $emailIdx] = array(
  					"parameters" => array(
  						"type" => $emailtypeArray
  					),
  					"text" => $email["email"]
  			);
  		}
  	}
  	

  	$arrayToConvert = array(
  			"vcard" => $arrayData
  	);
  	
  	$dom = new DOMDocument("1.0");
  	$dom->preserveWhiteSpace = false;
  	$dom->formatOutput = true;
  	$dom->loadXML(self::toXml($arrayToConvert));
  	return $dom->saveXML();
  }
  
  /**
   * The main function for converting to an XML document.
   * Pass in a multi dimensional array and this recrusively loops through and builds up an XML document.
   *
   * @param array $data
   * @param string $rootNodeName - what you want the root node to be - defaultsto data.
   * @param SimpleXMLElement $xml - should only be used recursively
   * @return string XML
   */
  function toXml($data, $rootNodeName = 'data', $xml=null){
  	if ($xml == null)
  	{
  		$xml = simplexml_load_string("<?xml version='1.0' encoding='utf-8'?><vcards xmlns='urn:ietf:params:xml:ns:vcard-4.0' />");
  	}
  
  	// loop through the data passed in.
  	foreach($data as $key => $value)
  	{
  		// no numeric keys in our xml please!
  		if (is_numeric($key))
  		{
  			// make string key...
  			$key = "unknownNode_". (string) $key;
  		}
  
  		// replace anything not alpha numeric
  		$key = preg_replace('/[^a-z]/i', '', $key);
  
  		// if there is another array found recrusively call this function
  		if (is_array($value))
  		{
  			$node = $xml->addChild($key);
  			// recrusive call.
  			self::toXml($value, $rootNodeName, $node);
  		}
  		else
  		{
  			// add single node.
  			$value = htmlentities($value);
  			$xml->addChild($key,$value);
  		}
  
  	}
  	// pass back as string. or simple xml object if you want!
  	return $xml->asXML();
  }
  
  /*
   * import vCard
   * @return mixed
   * @access private
   */
  function import_vCard() {

  	//array to return
  	$result = $this->parentInput->get_vCardDefaultParams();
   	$result['version'] = 'xCard';
  	
  	$supportedAttrs = array("adr", "agent", "anniversary", "bday", 
  			"begin", "caladruri", "caluri", "categories", "class", 
  			"clientpidmap", "email" , "end", "fburl", "fn", "gender", 
  			"geo", "impp", "key", "kind", "label", "lang", "logo", 
  			"mailer", "member", "n", "name", "nickname", "note", 
  			"org", "photo", "prodid", "profile", "related", "rev", 
  			"role", "sort-string", "sound", "source", "tel", "title", 
  			"tz", "uid", "url", "version", "xml");
  	
  	$reader = new XMLReader();
  	$reader->XML($this->params["source"]);
  	 
  	while($reader->read()) {
  		
  		if($reader->nodeType == XMLReader::ELEMENT){
  			//echo "<> " . $reader->name . "<br/>";
  			
  			if (in_array($reader->name, $supportedAttrs)) {
  				
  				//Extract Data
  				$result = self::extract_data($reader, $result);
  			}
  		}  	
  	}
  	
  	$reader->close();
  	return $result;
  }
  
  function extract_data($reader, $result){
  	$startNode = $reader->name;
  	
  	//
  	$newTel = array (
		'phone_type'=>'voice', // "text" / "voice" / "fax" / "cell" / "video" / "pager" / "textphone" / "msg" / "modem" / "car" / "isdn"
		'phone_number'=>'',
		'phone_location'=>'', // home / work
		'phone_pref'=>'',
	);
  	$newMail = array (
		'email'=> '',
		'email_location'=>'', // home / work
		'email_pref'=>'',
	);
  	$newAddr = array(
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
  	
  	while($reader->read()){
  		//Element extraction done
  		if($reader->nodeType == XMLReader::END_ELEMENT && $reader->name == $startNode){

  			if($startNode == "tel")
  				array_push ( $result ['phones'], $newTel );
  			elseif($startNode == "email")
  				array_push ( $result ['emails'], $newMail );
  			elseif($startNode == "adr")
  				array_push ( $result ['addresses'], $newAddr );

  			//echo "GET OUT FROM $startNode <br/>";
  			return $result;
  		} elseif($startNode == "fn"){
  			if($reader->nodeType == XMLReader::TEXT){
  				$result["full_name"] = $reader->value;
  			}
  		}else if($startNode == "n"){
  			if($reader->nodeType == XMLReader::ELEMENT){
  				$attr = $reader->name;
  				
  				//Move cursor to next element
  				$reader->read();
  			
  				if($attr == "surname")
  					$result["name_last"] = $reader->value;
  				elseif($attr == "given")
  					$result["name_first"] = $reader->value;
  				elseif($attr == "additional")
  					$result["name_additional"] = $reader->value;
  				elseif($attr == "prefix")
  					$result["name_prefix"] = $reader->value;
  				elseif($attr == "suffix")
  					$result["name_suffix"] = $reader->value;
  			}
  		}else if($startNode == "adr") {
  			if($reader->nodeType == XMLReader::ELEMENT){
  				$attr = $reader->name;
  				
  				if (isset ( $result ['addresses'] ) || array_key_exists ( 'addresses', $result )) {
  				} else
  					$result ['addresses'] = array ();
  				
  				if($attr == "parameters"){
  					while($reader->read()){
  						//Element extraction done
  						if($reader->nodeType == XMLReader::END_ELEMENT && $reader->name == $attr){
							break;
  						}else{
							if ($reader->value == "home" || $reader->value == "work")
								$newAddr ["addr_location"] = $reader->value;
							elseif ($reader->value == "pref")
								$newAddr ["addr_pref"] = true;
  						}
  					}
	  			}else{
	  				//Move cursor to next element
	  				$reader->read();
	  				
	  				if($attr == "pobox")
	  					$newAddr["addr_pobox"] = $reader->value;
	  				elseif($attr == "ext")
	  					$newAddr["addr_extended"] = $reader->value;
	  				elseif($attr == "street")
	  					$newAddr["addr_street"] = $reader->value;
	  				elseif($attr == "locality")
	  					$newAddr["addr_city"] = $reader->value;
	  				elseif($attr == "region")
	  					$newAddr["addr_region"] = $reader->value;
	  				elseif($attr == "code")
	  					$newAddr["addr_zipcode"] = $reader->value;
	  				elseif($attr == "country"){
	  					$country = $reader->value;
	  					$newAddr["addr_country"] = $country;
	  					
	  					if($country != ""){
	  						$countrycode = $this->parentInput->getCountryCode($country);
	  						if($countrycode)
	  							$newAddr ['addr_countrycode'] = str_replace("country_", "", $countrycode);
	  					}
	  					
	  				}
	  			}
  			}
  		} else if($startNode == "tel") {
  			if($reader->nodeType == XMLReader::ELEMENT){
  				$attr = $reader->name;
  				
  				if (isset ( $result ['phones'] ) || array_key_exists ( 'phones', $result )) {
  				} else
  					$result ['phones'] = array ();
  			
  				if($attr == "parameters"){
  					while($reader->read()){
  						//Element extraction done
  						if($reader->nodeType == XMLReader::END_ELEMENT && $reader->name == $attr){
  							break;
  						}else{
  							if ($reader->value == "voice" || $reader->value == "text" || $reader->value == "fax" || $reader->value == "cell" || $reader->value == "video" || $reader->value == "pager" || $reader->value == "textphone")
								$newTel ["phone_type"] = $reader->value;
							elseif ($reader->value == "home" || $reader->value == "work")
								$newTel ["phone_location"] = $reader->value;
							elseif ($reader->value == "pref")
								$newTel ["phone_pref"] = true;
  							
  						}
  					}
  				}else{
  					//Move cursor to next element
  					$reader->read();
  						
  					if($attr == "uri"){
  						$phonenum = explode ( ';', $reader->value );
  						$newTel ["phone_number"] = str_replace('tel:', '', $phonenum[0]);;
  					}
  						
  						
  				}
  				
  			}
  	  	} else if($startNode == "email") {
  			if($reader->nodeType == XMLReader::ELEMENT){
  				$attr = $reader->name;
  				
  				if (isset ( $result ['emails'] ) || array_key_exists ( 'emails', $result )) {
  				} else
  					$result ['emails'] = array ();
  			
  				if($attr == "parameters"){
  					while($reader->read()){
  						//Element extraction done
  						if($reader->nodeType == XMLReader::END_ELEMENT && $reader->name == $attr){
  							break;
  						}else{
							if ($reader->value == "home" || $reader->value == "work")
								$newMail ["email_location"] = $reader->value;
							elseif ($reader->value == "pref")
								$newMail ["email_pref"] = true;
  						}
  					}
  				}else{
  					//Move cursor to next element
  					$reader->read();
  						
  					$newMail["email"] = $reader->value;
  						
  				}
  			}
  	  	} elseif($startNode == "note"){
  			if($reader->nodeType == XMLReader::TEXT){
  				$Value = $reader->value;
  				$Value = str_replace('=0D=0A', PHP_EOL, $Value);
  				$Value = str_replace('%0D%0A', PHP_EOL, $Value);
  				$Value = str_replace('\n', PHP_EOL, $Value);
  				$result ['note'] = $Value;
  			}
  		}
  	}
  }
 

}
?>