<?php
/*
 * CaMykS Engine
 * Developed by      : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Input Engine
 * Creation Date    : Nov 2014
 * Last Modif Date  : Nov 2014
 * History : 
 * * 14-11-21 : Initial File
 * 
 * Generic vCard handler : import and export vCard version 2.1
 */

class GenericVCardHandler_vCard21 {
  /*
   * constructor
   * @param Object $parent
   * @param array $params
   */
  function GenericVCardHandler_vCard21 ($parent, $params) {
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
    /* add structure values */
    $content = 'BEGIN:VCARD'."\n";
    $content .= 'VERSION:2.1'."\n";
    /*
    if ($this->params['kind'] != '')
      $content .= 'KIND:'.$this->params['kind'].'\n';
    if ($this->params['source'] != '')
      $content .= 'SOURCE:'.$this->params['source'].'\n';
    
    /* add formatted name */
    if(isset($this->params['full_name']) && $this->params['full_name'] != '')
      $content .= 'FN:'.$this->params['full_name']."\n";
    else if ($this->params['name_last'] != '' or $this->params['name_first'] != '') {
        $content .= 'FN:'.trim($this->params['name_first'].' '.$this->params['name_last'])."\n";
    }
    
    /* add names */
    if ($this->params['name_last'] != '' or $this->params['name_first'] != '' 
        or $this->params['name_additional'] != '' or $this->params['name_prefix'] != ''
        or $this->params['name_suffix'] != '') {
      $n = array();
      $n[0] = $this->params['name_last'];
      $n[1] = $this->params['name_first'];
      $n[2] = $this->params['name_additional'];
      $n[3] = $this->params['name_prefix'];
      $n[4] = $this->params['name_suffix'];
      $content .= 'N:'.implode(';', $n)."\n";
    }
    
    /* add photo */
    // @TODO need some testing
    if ( $this->params['photo_url'] != '') {
      if (strtoupper($this->params['photo_mode']) == 'URL') 
        $content .= 'PHOTO;:'.$this->params['photo_url']."\n";
      elseif (strtoupper($this->params['photo_mode']) == 'DATA') {
        $content .= 'PHOTO;ENCODING=BASE64:'.$this->params['photo_url']."\n";
        // if (($v = @file_get_contents( $this->params['photo_url'])) !== false) {
        /* to complete 
        $content .= 'PHOTO;ENCODING=BASE64;TYPE=';
        /* write type */
       
        /* write file content *
        $content .= ':'.base64_encode($v)."\n";
        */
        //}
      }
    }
    
    /* add birthday */
    if ($this->params['birthdate'] != '') {
      $content .= 'BDAY:'.date('Y-m-d', date_stringToTimestamp($this->params['birthdate']))."\n";
    }
    
    foreach ($this->params['addresses'] as $addr){
      /* add address */
      if ($addr['addr_location'] != '' or $addr['addr_pobox'] != ''
          or $addr['addr_extended'] != '' or $addr['addr_street'] != ''
          or $addr['addr_city'] != '' or $addr['addr_zipcode'] != ''
          or $addr['addr_region'] != '' or $addr['addr_country'] != '') {
      
            /* prepare label */
//             $label = '';
      
            $content .= 'ADR;TYPE=';
            
            if(isset($addr["addr_pref"]) && $addr["addr_pref"] == true)
              $content .= 'PREF,';
            if(isset($addr["addr_location"]) && $addr["addr_location"] != "")
              $content .= strtoupper($addr["addr_location"]) . ',';
            
            $content .= ':';
            
//             /* add location(s) in address */
//             if (is_array($addr['addr_location'])) {
//               $content .= 'ADR;'.implode(';', $addr['addr_location']).':';
// //               $label .= 'LABEL;'.implode(';', $addr['addr_location']);
//             } elseif ($addr['addr_location'] != '') {
//               $content .= 'ADR;'.$addr['addr_location'].':';
// //               $label .= 'LABEL;'.$addr['addr_location'];
//             } else {
//               $content .= 'ADR:';
// //               $label .= 'LABEL';
//             }
      
            /* complete label */
//             $label .= ',ENCODING=QUOTED-PRINTABLE:';
      
            /* add address content */
            $n = array();
            $n[0] = $addr['addr_pobox'];
            $n[1] = $addr['addr_extended'];
            $n[2] = $addr['addr_street'];
            $n[3] = $addr['addr_city'];
            $n[4] = $addr['addr_region'];
            $n[5] = $addr['addr_zipcode'];
            if (isset($addr['addr_countrycode']) && $addr['addr_countrycode'] != '') {
              countries_loadLocales('en');
              $n[6] = countries_getTranslation($addr['addr_country']);
            } elseif($addr['addr_country'] != '')
              $n[6] = $addr['addr_country'];
            else
              $n[6] = "";
            
//             if ( $addr['addr_country'] != '') {
//               countries_loadLocales('en');
//               $n[6] = countries_getTranslation($addr['addr_country']);
//             } else
//               $n[6] = '';
            $content .= implode(';', $n)."\n";
      
            /* add address content to label */
//             $n = array();
//             if ($addr['addr_pobox'] != '')
//               $n[] = $addr['addr_pobox'];
//             if ($addr['addr_extended'] != '')
//               $n[] = $addr['addr_extended'];
//             if ($addr['addr_street'] != '')
//               $n[] = $addr['addr_street'];
      
//             $c = $addr['addr_city'];
//             if ($addr['addr_region'] != '' or $addr['addr_zipcode'] != '')
//               $c .= ', '.($addr['addr_region']!= '' ? $addr['addr_region']. ' ':'').$addr['addr_zipcode'];
//             $n[] = $c;
//             if ($addr['addr_country'] != '')
//               $n[] = countries_getTranslation($addr['addr_country']);
      
//             $label .= implode('=0D=0A=', $n);
//             $content .= $label . "\n";
          }
    }
    

    
    /* phone(s) */
    foreach ($this->params['phones'] as $phone){
      //TEL;WORK;VOICE:(111) 555-1212
      $content .= "TEL";
      if(isset($phone["phone_pref"]) && $phone["phone_pref"] == true)
        $content .= ";PREF";
      if(isset($phone["phone_location"]) && $phone["phone_location"] != "")
        $content .= ";". strtoupper($phone["phone_location"]);
      if(isset($phone["phone_type"]) && $phone["phone_type"] != "")
        $content .= ";" . strtoupper($phone["phone_type"]);
      
      $content .= ":" . $phone["phone_number"] . "\n";
      
    }
    
    /* email(s) */
    foreach ($this->params['emails'] as $email){
      //EMAIL;PREF;INTERNET:forrestgump@example.com
      $content .= "EMAIL";
      if(isset($email["email_pref"]) && $email["email_pref"] == true)
        $content .= ";PREF";
      if(isset($email["email_location"]) && $email["email_location"] != "")
        $content .= ";". strtoupper($email["email_location"]);
      if(isset($email["email_type"]) && $email["email_type"] != "")
        $content .= ";" . strtoupper($email["email_type"]);
      
      $content .= ":" . $email["email"] . "\n";
      
    }
    
    /* Geolocalisation */
    if ($this->params['geo_latitude'] != '' and $this->params['geo_longitude'] != '') {
      $content .= 'GEO:'.$this->params['geo_longitude'].','.$this->params['geo_latitude']."\n";
    }
    
    /* Title */
    if ($this->params['title'] != '')
      $content .= 'TITLE:'.$this->params['title']."\n";
    
    /* Role */
    if ($this->params['role'] != '')
      $content .= 'ROLE:'.$this->params['role']."\n";
      
    /* add logo */
    if ( $this->params['logo_url'] != '') {
      if (strtoupper($this->params['logo_mode']) == 'URL') 
        $content .= 'LOGO;VALUE=URL:'.$this->params['logo_url']."\n";
      elseif (strtoupper($this->params['logo_mode']) == 'DATA') {
         if (($v = @file_get_contents( $this->params['logo_url'])) !== false) {
        /* to complete 
        $content .= 'LOGO;ENCODING=BASE64;TYPE=';
        /* write type */
       
        /* write file content *
        $content .= ':'.base64_encode($v)."\n";
        */
        }
      }
    }
    
    /* Org title and unit(s) */
    if ( $this->params['org_title'] != '' or $this->params['org_unit'] != '') {
      $content .= 'ORG:';
      $c = array($this->params['org_title']);
      if (is_array($this->params['org_unit'])) {
        $c = array_merge($c, $this->params['org_unit']);
      } elseif ($this->params['org_unit'] != '') {
        $c[] = $this->params['org_unit'];
      }
      $content .= implode(';', $c)."\n";
    }
    
    $content .= 'END:VCARD';
    return $content;
  }
  
  /*
   * import vCard
   * @TODO add multiple contacts per file support
   * @return mixed
   * @access private
   */
  function import_vCard() {
    ////echo "<b>IMPORT :</b> <br>" . nl2br($this->params['source']) . "<br/>";
     
    //array to return
    $result = $this->parentInput->get_vCardDefaultParams();
    $result['version'] = '2.1';
     
    if(isset($this->params['source'])){

      $Matches = array ();
      $vCardBeginCount = preg_match_all ( '{^BEGIN\:VCARD}miS', $this->params ['source'], $Matches );
      $vCardEndCount = preg_match_all ( '{^END\:VCARD}miS', $this->params ['source'], $Matches );
            
      if ($vCardBeginCount == 1) { // Unique Contact
        $Lines = explode ( "\n", $this->params ['source'] );
        
        foreach ( $Lines as $Line ) {
        
          if (strpos ( $Line, ':' ) === false) {
            continue;
          }
          
          // Chaque ligne est divisee en deux parties divisiees par un :
          list ( $Key, $Value ) = explode ( ':', $Line, 2 );
          
          // on formatte la cle
          $Key = strtolower ( trim ( self::Unescape ( $Key ) ) );
          
          if ($Key == 'begin' || $Key == 'end') {
            continue;
          }
          
          // Key params
          $KeyParts = explode ( ';', $Key );
          
          // extarct the attribute
          $Key = $KeyParts [0];
                    
          // undescapr value
          $Value = trim ( self::Unescape ( $Value ) );
          
          $Type = array ();
          
          if ($Key == "adr") { // Adresse
            
            $adresse = explode ( ';', $Value );
            
            if (array_key_exists ( 'addresses', $result ) || isset ( $result ['addresses'] )) {
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
            
            $newAddr ['addr_pobox'] = $adresse [0];
            $newAddr ['addr_extended'] = $adresse [1];
            $newAddr ['addr_street'] = $adresse [2];
            $newAddr ['addr_city'] = $adresse [3];
            $newAddr ['addr_zipcode'] = $adresse [5];
            $newAddr ['addr_region'] = $adresse [4];
            $newAddr ['addr_country'] = $adresse [6];
            
            if($adresse [6] != ""){
              $countrycode = $this->parentInput->getCountryCode($adresse [6]);
              if($countrycode)
                $newAddr ['addr_countrycode'] = str_replace("country_", "", $countrycode);
            }
            
            
            foreach ($KeyParts as $addrtype){
              if ($addrtype == "home" || $addrtype == "work")
                $newAddr ["addr_location"] = $addrtype;
              elseif ($addrtype == "pref")
                $newAddr ["addr_pref"] = true;
            }
            
            array_push ( $result ['addresses'], $newAddr );
            
          }elseif ($Key == "agent") { //
          }elseif ($Key == "bday") { //
            //TODO Parse date
            $result ['birthday'] = $Value;
          }elseif ($Key == "categories") { //
          } elseif ($Key == "email") { // Email
            
            if (array_key_exists ( 'emails', $result ) || isset ( $result ['emails'] )) {
            } else
              $result ['emails'] = array ();
            
            $newMail = array (
              'email'=> '',
              'email_location'=>'', // home / work
              'email_pref'=>'',
            );
            $newMail ["email"] = $Value;
            
            foreach ($KeyParts as $emailtype){
              if ($emailtype == "home" || $emailtype == "work")
                  $newMail ["email_location"] = $emailtype;
                elseif ($emailtype == "pref")
                  $newMail ["email_pref"] = true;
                      
            }
                        
            array_push ( $result ['emails'], $newMail );
          } elseif ($Key == "fn") { // formatted name
            $result ['full_name'] = $Value;
          } elseif ($Key == "geo") { // GEO:39.95;-75.1667
            //TODO Must verifiy this
            $coord = explode ( ';', $Value );
            if(isset($coord[0]) && isset($coord[1])){
              $result ['geo_latitude'] = $coord[0];
              $result ['geo_longitude'] = $coord[1];
            }
          } elseif ($Key == "key") { //
          

          } elseif ($Key == "label") { //
          }elseif ($Key == "logo") { //
            //2 cases
            //LOGO;PNG:http://example.com/logo.png
            //LOGO;PNG;ENCODING=BASE64:[base64-data]
            
            if(isset($KeyParts[2]) && $KeyParts[2] == "http"){
              $result ['logo_mode'] = 'URL';
              $result ['logo_url'] = $Value;
            }elseif(isset($KeyParts[2]) && $KeyParts[2] == "ENCODING=BASE64"){
              $result ['logo_mode'] = 'DATA';
              $result ['logo_url'] = $Value;
            }elseif(substr ( $Value, 0, strlen ( 'http' ) ) === 'http'){
              $result ['logo_mode'] = 'URL';
              $result ['logo_url'] = $Value;
            }
            
          }elseif ($Key == "mailer") { //
          } elseif ($Key == "n") { // structured representation of the name
            
            $name = explode ( ';', $Value );

            if(isset($name [0]))
              $result ['name_last'] = $name [0];
            else 
              $result ['name_last'] = "";
            if(isset($name [1]))
              $result ['name_first'] = $name [1];
            else 
              $result ['name_first'] = "";
            if(isset($name [2]))
              $result ['name_additional'] = $name [2];
            else 
              $result ['name_additional'] = "";
            if(isset($name [3]))
              $result ['name_prefix'] = $name [3];
            else 
              $result ['name_prefix'] = "";
            if(isset($name [4]))
              $result ['name_suffix'] = $name [4];
            else 
              $result ['name_suffix'] = "";
          } elseif ($Key == "note") { // NOTE
            
            $Value = str_replace('=0D=0A', PHP_EOL, $Value);
            $Value = str_replace('%0D%0A', PHP_EOL, $Value);
            $Value = str_replace('\n', PHP_EOL, $Value);
            $result ['note'] = $Value;
          } elseif ($Key == "org") { // organization            
            if (strpos($Value,';') !== false) {
              list($KeyOrg, $ValueOrg)=explode (';', $Value, 2);
              if(isset($KeyOrg) && isset($ValueOrg)){
                $result ['org_title'] = $KeyOrg;
                $result ['org_unit'] = $ValueOrg;
              }else 
                $result ['org_title'] = $Value;
            }else 
              $result ['org_title'] = $Value;
            
            
          } elseif ($Key == "photo") {
            
            //PHOTO;JPEG:http://example.com/photo.jpg
            //PHOTO;JPEG;ENCODING=BASE64:[base64-data]

            if(isset($KeyParts[2]) && $KeyParts[2] == "http"){
              $result ['photo_mode'] = 'URL';
              $result ['photo_url'] = "http:" + $Value;
            }elseif(isset($KeyParts[2]) && $KeyParts[2] == "encoding=base64"){
              $result ['photo_mode'] = 'DATA';
              $result ['photo_url'] = $Value;
            }elseif(substr ( $Value, 0, strlen ( 'http' ) ) === 'http'){
              $result ['photo_mode'] = 'URL';
              $result ['photo_url'] = $Value;
            }
          }elseif ($Key == "profile") { // organization
          } elseif ($Key == "rev") { // timestamp for the last time the vCard was updated
            $result ['rev'] = strtotime($Value);
          } elseif ($Key == "role") { // occupation, or business category of the vCard object within an organization.
            $result ['role'] = $Value;
          } elseif ($Key == "sort-string") { // timestamp for the last time the vCard was updated
          } elseif ($Key == "sound") { // timestamp for the last time the vCard was updated
          } elseif ($Key == "source") { // timestamp for the last time the vCard was updated
          } elseif ($Key == "tel") { // telephone
            
            if (isset ( $result ['phones'] ) || array_key_exists ( 'phones', $result )) {
            } else
              $result ['phones'] = array ();
            
            $newTel = array (
              'phone_type'=>'voice', // "text" / "voice" / "fax" / "cell" / "video" / "pager" / "textphone" / "msg" / "modem" / "car" / "isdn"
              'phone_number'=>'',
              'phone_location'=>'', // home / work
              'phone_pref'=>'',
            );
            
            $phonenum = explode ( ';', $Value);
            $newTel ["phone_number"] = str_replace('tel:', '', $phonenum[0]);;

            foreach ($KeyParts as $teltype){
              if ($teltype == "voice" || $teltype == "text" || $teltype == "fax" || $teltype == "cell" || $teltype == "video" || $teltype == "pager" || $teltype == "textphone")
                $newTel ["phone_type"] = $teltype;
              elseif ($teltype == "home" || $teltype == "work")
                $newTel ["phone_location"] = $teltype;
              elseif ($teltype == "pref")
                $newTel ["phone_pref"] = true;
            }
                        
            array_push ( $result ['phones'], $newTel );
          } elseif ($Key == "title") { //
            $result ['title'] = $Value;
          } elseif ($Key == "tz") { // URL website
          } elseif ($Key == "uid") { // URL website
            
          } elseif ($Key == "url") { // URL website
            
          }
        }
      }
    }
     
     return $result;
  }
  
  /**
   * Enlever les characteres d'echappement du text
   *
   * @TODO je ne sais pas si cette methode existe deja qq part, a verifier
   * @access private
   * @param string Text to prepare.
   * @return string Resulting text.
   */
  private static function Unescape($Text){
    return str_replace(array('\:', '\;', '\,', "\n"), array(':', ';', ',', ''), $Text);
  }
  
  /* specific tool methods */
  
  /*
   * get card title
   * @return string
   * @access private
   */
  function get_cardTitle() {
    if (trim($this->params['full_name']) != '')
      return $this->params['full_name'];
    if ($this->params['kind'] == 'org' and trim($this->params['org_title']) != '')
      return $this->params['org_title'];
    if (trim($this->params['name_first']) != '' and trim($this->params['name_last']) != '')
      return $this->params['name_first'] . ' ' .$this->params['name_last'];
    if (trim($this->params['name_first']) != '')
      return $this->params['name_first'];
    if (trim($this->params['name_last']) != '')
      return $this->params['name_last'];
    if (trim($this->params['nickname']) != '')
      return $this->params['nickname'];
    return 'Unknown';
  }
  
  
  /*
   * return formatted phone line
   * @param array $phoneData
   * @return string
   * @access private
   */
//   function get_formattedPhoneContent($phoneData) {
//     $dData = array('phone_type'=>'', 'phone_number'=>'', 'phone_location'=>'', 'phone_pref');
//     $phoneData = array_merge($dData, $phoneData);
    
//     $data = array('TEL');
//     /* check is prefered */
//     if ($phoneData['phone_pref'] != '')
//       $data[] = 'PREF';
      
//     /* check phone type */
//     if (is_array($phoneData['phone_type']))
//       $data = array_merge($data, $phoneData['phone_type']);
//     elseif ($phoneData['phone_type'] != '')
//       $data[] = $phoneData['phone_type'];
      
//     /* check phone location */
//     if (is_array($phoneData['phone_location']))
//       $data = array_merge($data, $phoneData['phone_location']);
//     elseif ($phoneData['phone_location'] != '')
//       $data[] = $phoneData['phone_location'];   
    
//     return strtoupper(implode(';', $data)).':'.$phoneData['phone_number'];
//   }
  
  /*
   * return formatted email line
   * @param array $emailData
   * @return string
   * @access private
   */
//   function get_formattedEmailContent($emailData) {
//     $dData = array('email_type'=>'', 'email'=>'', 'email_location'=>'', 'email_pref');
//     $emailData = array_merge($dData, $emailData);
    
//     $data = array('EMAIL');
//     /* check is prefered */
//     if (isset($emailData['email_pref']) && $emailData['email_pref'] != '')
//       $data[] = 'PREF';
      
//     /* check email type *
//     if (is_array($emailData['email_type']))
//       $data = array_merge($data, $emailData['email_type']);
//     elseif ($emailData['email_type'] != '')
//       $data[] = $emailData['email_type'];
      
//     /* check email location *
//     if (is_array($emailData['email_location']))
//       $data = array_merge($data, $emailData['email_location']);
//     elseif ($emailData['email_location'] != '')
//       $data[] = $emailData['email_location'];   
//     */
    
//     return strtoupper(implode(';', $data)).':'.$emailData['email'];
//   }

}
?>