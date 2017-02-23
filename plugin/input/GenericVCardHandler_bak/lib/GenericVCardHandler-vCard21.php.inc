<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Input Engine
 * Creation Date    : Nov 2014
 * Last Modif Date	: Nov 2014
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
    if ($this->params['name_last'] != '' or $this->params['name_first'] != '') {
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
    if ( $this->params['photo_url'] != '') {
      if (strtoupper($this->params['photo_mode']) == 'URL') 
        $content .= 'PHOTO;VALUE=URL:'.$this->params['photo_url']."\n";
      elseif (strtoupper($this->params['photo_mode']) == 'DATA') {
         if (($v = @file_get_contents( $this->params['photo_url'])) !== false) {
        /* to complete 
        $content .= 'PHOTO;ENCODING=BASE64;TYPE=';
        /* write type */
       
        /* write file content *
        $content .= ':'.base64_encode($v)."\n";
        */
        }
      }
    }
    
    /* add birthday */
    if ($this->params['birthdate'] != '') {
      $content .= 'BDAY:'.date('Y-m-d', date_stringToTimestamp($this->params['birthdate']))."\n";
    }
    
    /* add address */
    if ($this->params['addr_location'] != '' or $this->params['addr_pobox'] != '' 
        or $this->params['addr_extended'] != '' or $this->params['addr_street'] != ''
        or $this->params['addr_city'] != '' or $this->params['addr_zipcode'] != ''
        or $this->params['addr_region'] != '' or $this->params['addr_country'] != '') {
      
      /* prepare label */
      $label = '';
      
      /* add location(s) in address */
      if (is_array($this->params['addr_location'])) {
        $content .= 'ADR;'.implode(';', $this->params['addr_location']).':';
        $label .= 'LABEL;'.implode(';', $this->params['addr_location']);
      } elseif ($this->params['addr_location'] != '') {
        $content .= 'ADR;'.$this->params['addr_location'].':';
        $label .= 'LABEL;'.$this->params['addr_location'];
      } else {
        $content .= 'ADR:';
        $label .= 'LABEL';
      }
      
      /* complete label */
      $label .= ',ENCODING=QUOTED-PRINTABLE:';

      /* add address content */
      $n = array();
      $n[0] = $this->params['addr_pobox'];
      $n[1] = $this->params['addr_extended'];
      $n[2] = $this->params['addr_street'];
      $n[3] = $this->params['addr_city'];
      $n[4] = $this->params['addr_region'];
      $n[5] = $this->params['addr_zipcode'];
      if ( $this->params['addr_country'] != '') {
        countries_loadLocales('en');
        $n[6] = countries_getTranslation($this->params['addr_country']);
      } else
        $n[6] = '';
      $content .= implode(';', $n)."\n";
      
      /* add address content to label */
      $n = array();
      if ($this->params['addr_pobox'] != '')
        $n[] = $this->params['addr_pobox'];
      if ($this->params['addr_extended'] != '')
        $n[] = $this->params['addr_extended'];
      if ($this->params['addr_street'] != '')
        $n[] = $this->params['addr_street'];
      
      $c = $this->params['addr_city'];
      if ($this->params['addr_region'] != '' or $this->params['addr_zipcode'] != '')
        $c .= ', '.($this->params['addr_region']!= '' ? $this->params['addr_region']. ' ':'').$this->params['addr_zipcode'];
      $n[] = $c;
      if ($this->params['addr_country'] != '')
        $n[] = countries_getTranslation($this->params['addr_country']);
      
      $label .= implode('=0D=0A=', $n);
      $content .= $label . "\n";
    }
    
    /* phone(s) */
    if ($this->params['phone_number'] != '')
      $content .= $this->get_formattedPhoneContent($this->params) ."\n";
    if (is_array($this->params['phones']) and count($this->params['phones']) > 0) {
      foreach ($this->params['phones'] as $phoneData)
        if (isset($phoneData['phone_number']) and $phoneData['phone_number'] != '')
          $content .= $this->get_formattedPhoneContent($phoneData) ."\n";
    }
    
    /* email(s) */
    if ($this->params['email'] != '')
      $content .= $this->get_formattedEmailContent($this->params) ."\n";
    if (is_array($this->params['emails']) and count($this->params['emails']) > 0) {
      foreach ($this->params['emails'] as $emailData)
        if (isset($emailData['email']) and $emailData['email'] != '')
          $content .= $this->get_formattedEmailContent($emailData) ."\n";
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
   * @return mixed
   * @access private
   */
  function import_vCard() {
   
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
  function get_formattedPhoneContent($phoneData) {
    $dData = array('phone_type'=>'', 'phone_number'=>'', 'phone_location'=>'', 'phone_pref');
    $phoneData = array_merge($dData, $phoneData);
    
    $data = array('TEL');
    /* check is prefered */
    if ($phoneData['phone_pref'] != '')
      $data[] = 'PREF';
      
    /* check phone type */
    if (is_array($phoneData['phone_type']))
      $data = array_merge($data, $phoneData['phone_type']);
    elseif ($phoneData['phone_type'] != '')
      $data[] = $phoneData['phone_type'];
      
    /* check phone location */
    if (is_array($phoneData['phone_location']))
      $data = array_merge($data, $phoneData['phone_location']);
    elseif ($phoneData['phone_location'] != '')
      $data[] = $phoneData['phone_location'];   
    
    return strtoupper(implode(';', $data)).':'.$phoneData['phone_number'];
  }
  
  /*
   * return formatted email line
   * @param array $emailData
   * @return string
   * @access private
   */
  function get_formattedEmailContent($emailData) {
    $dData = array('email_type'=>'', 'email'=>'', 'email_location'=>'', 'email_pref');
    $emailData = array_merge($dData, $emailData);
    
    $data = array('EMAIL');
    /* check is prefered */
    if ($emailData['email_pref'] != '')
      $data[] = 'PREF';
      
    /* check email type *
    if (is_array($emailData['email_type']))
      $data = array_merge($data, $emailData['email_type']);
    elseif ($emailData['email_type'] != '')
      $data[] = $emailData['email_type'];
      
    /* check email location *
    if (is_array($emailData['email_location']))
      $data = array_merge($data, $emailData['email_location']);
    elseif ($emailData['email_location'] != '')
      $data[] = $emailData['email_location'];   
    */
    
    return strtoupper(implode(';', $data)).':'.$emailData['email'];
  }
}
?>