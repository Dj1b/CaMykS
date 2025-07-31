<?php
/**
 * @brief GenericVCardHandler Input
 * <br /> Imports and exports information in vcard formats.
 * @details Plugin / Input Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.1
 * @date Creation: Nov 2014
 * @date Modification: Jul 2025
 * @copyright 2014 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * GenericVCardHandler Input class.
 */
final class GenericVCardHandler extends Input {

    /**
     * var array $loadedObjects
     * @brief Loaded vcard format list.
     */
    private $loadedObjects = array();

    /**
     * var string $pluginError
     * @brief Last error.
     */
    private $pluginError = '';

    /**
     * Class constructor.
     * @param string $path_type
     */
    function __construct($path_type) {
        parent::__construct('GenericVCardHandler', $path_type);

        /* Override Plugin information */
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* Define author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';
    }

    /* Mark: Override input methods */

    /**
     * Initialise input.
     * @param array $params
     * @return boolean result
     */
    function initialise($params=array()) {
        global $camyks;

        /* check for vCard importation */
        if (isset($params['action']) and $params['action'] == 'import')
            return $this->import_vCard($params);

        /* check for vCard exportation */
        if (isset($params['action']) and $params['action'] == 'export')
            return $this->export_vCard($params);

        /* no known action found: throw fatal error */
        $camyks->throwFatalError(array(
            'title'         => $this->get_translation('fatalerrortitle'),
            'description'   => $this->get_translation('fatalerrordesc'),
            'content1'      => $this->get_translation('fatalerror_noknownaction', $params['action']),
            'content2'      => $this->get_translation('fatalerrorgenendig'),
        ));
    }

    /* Mark: Specific action methods */

    /**
     * Export vCard.
     * @param array $params
     * @return mixed
     */
    private function export_vCard($params) {
        global $camyks;

        /* check and merge params */
        $params = array_merge($this->get_exportDefaultParams(), $this->get_vCardDefaultParams(), $params);

        /* get vCard content following version */
        switch ($params['version']) {
            case '2.1':
                if ($this->load_vCardObject('vCard21')) {
                    $vCard = new GenericVCardHandler_vCard21($this, $params);
                    $cardContent = $vCard->export_vCard();
                } else {
                    $cardContent = false;
                    $this->define_pluginError('loadingfailed', $params['version']);
                }
                break;
            case '3.0':
                if ($this->load_vCardObject('vCard30')) {
                    $vCard = new GenericVCardHandler_vCard30($this, $params);
                    $cardContent = $vCard->export_vCard();
                } else {
                    $cardContent = false;
                    $this->define_pluginError('loadingfailed', $params['version']);
                }
                break;
            case '4.0':
                if ($this->load_vCardObject('vCard40')) {
                    $vCard = new GenericVCardHandler_vCard40($this, $params);
                    $cardContent = $vCard->export_vCard();
                } else {
                    $cardContent = false;
                    $this->define_pluginError('loadingfailed', $params['version']);
                }
                break;
            case 'xCard':
                if ($this->load_vCardObject('xCard')) {
                    $vCard = new GenericVCardHandler_xCard($this, $params);
                    $cardContent = $vCard->export_vCard();
                } else {
                    $cardContent = false;
                    $this->define_pluginError('loadingfailed', $params['version']);
                }
                break;
            case 'jCard':
                if ($this->load_vCardObject('jCard')) {
                    $vCard = new GenericVCardHandler_jCard($this, $params);
                    $cardContent = $vCard->export_vCard();
                } else {
                    $cardContent = false;
                    $this->define_pluginError('loadingfailed', $params['version']);
                }
                break;
            case 'hCard':
                if ($this->load_vCardObject('hCard')) {
                    $vCard = new GenericVCardHandler_hCard($this, $params);
                    $cardContent = $vCard->export_vCard();
                } else {
                    $cardContent = false;
                    $this->define_pluginError('loadingfailed', $params['version']);
                }
                break;
            default:
                $cardContent = false;
                $this->define_pluginError('loadingfailed', $params['version']);
                break;
        }

        /* output vCard */
        switch ($params['output']) {
            case 'void': return;
            case 'text': return $cardContent;
            case 'file': return ($cardContent and file_write($params['target'], $cardContent));
            case 'download':
                if ($cardContent === false) {
                    $camyks->throwFatalError(array(
                        'title'         => $this->get_translation('fatalerror_title'),
                        'description'   => $this->get_translation('fatalerror_desc'),
                        'content1'      => $this->pluginError,
                        'content2'      => $this->get_translation('fatalerror_genendig')));
                }
                header('Content-Type: text/vcard; charset=utf-8');
                header('Content-Disposition: attachment; filename="'.$this->encode_cardTitle($vCard->get_cardTitle()).'"');
                header('Pragma: no-cache');
                $camyks->init_kill();
        }
        return false;
    }

    /**
     * Import vCard.
     * @param array $params
     * @return mixed
     */
    private function import_vCard($params) {
        $params = array_merge($this->get_importDefaultParams(), $params);

        /* get vCard content */
        switch (strtolower($params['input'])) {
            case 'file':
                $content = file_get_contents($params['source']);
                break;
            case 'url':
                $content = file_get_contents($params['source']);
                break;
            case 'text':
                $content = $params['source'];
                break;
            default :
                $this->define_pluginError('cardreadingfailed');
                return false;
        }

        /* get vCard version */
        if (($version = $this->check_vCardVersion($content)) === false) {
            return false;
        }

        if ($version == "2.1" || $version == "3.0" || $version == "4.0") {
            $content = self::cleanVcard($content);
        }
        $params['source'] = $content;

        /* parse vCard content following found version */
        switch ($version) {
            case '2.1':
                if ($this->load_vCardObject('vCard21')) {
                    $vCard = new GenericVCardHandler_vCard21($this, $params);
                    return $vCard->import_vCard();
                }
                break;
            case '3.0':
                if ($this->load_vCardObject('vCard30')) {
                    $vCard = new GenericVCardHandler_vCard30($this, $params);
                    return $vCard->import_vCard();
                }
                break;
            case '4.0':
                if ($this->load_vCardObject('vCard40')) {
                    $vCard = new GenericVCardHandler_vCard40($this, $params);
                    return $vCard->import_vCard();
                }
                break;
            case 'xCard':
                if ($this->load_vCardObject('xCard')) {
                    $vCard = new GenericVCardHandler_xCard($this, $params);
                    return $vCard->import_vCard();
                }
                break;
            case 'jCard':
                if ($this->load_vCardObject('jCard')) {
                    $vCard = new GenericVCardHandler_jCard($this, $params);
                    return $vCard->import_vCard();
                }
                break;
            case 'hCard':
                if ($this->load_vCardObject('hCard')) {
                    $vCard = new GenericVCardHandler_hCard($this, $params);
                    return $vCard->import_vCard();
                }
                break;
        }
        $this->define_pluginError('cannotdetectvcardversion');
        return false;
    }

    /* Mark: Specific public tool methods */

    /**
     * Return vCard available versions.
     * @return array
     */
    public function get_vCardAvailableVersions() {
        return array(
                '2.1' => 'vCard 2.1',
                '3.0' => 'vCard 3.0',
                '4.0' => 'vCard 4.0',
                'xCard' => 'xCard',
                'hCard' => 'hCard',
                'jCard' => 'jCard'
       );
    }

    /**
     * Return vCard default params.
     * @return array
     */
    public function get_vCardDefaultParams() {
        return array(
            /* vCard structure */
            'version'=>'4.0',
            'kind'=>'individual', // group / org / location
            'source'=>'',

            /* data */
            'full_name'=>'',
            'name_last'=>'',
            'name_first'=>'',
            'name_additional'=>'',
            'name_prefix'=>'',
            'name_suffix'=>'',
            'nickname'=>'',
            'photo_mode'=>'URL', // URL / Data
            'photo_url'=>'',    // Accepted types : GIF, CGM, WMF, BMP, MET, PMB, DIB, PICT, TIFF, PS, PDF, JPEG, MPEG, MPEG2, AVI, QTIME
            'birthdate'=>'',
            'gender'=>'', // M => "male", F => "female", O => "other", N => "none or not applicable", U => "unknown".
            'gender_more'=>'',
            'addresses'=>array(),
            //'addr_location'=>'', // DOM => Domestic, INTL => International, POSTAL, PARCEL, HOME, WORK
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
            'phones'=>array(),
            'phone_type'=>'voice', // "text" / "voice" / "fax" / "cell" / "video" / "pager" / "textphone" / "msg" / "modem" / "car" / "isdn"
            'phone_number'=>'',
            'phone_location'=>'', // home / work
            'phone_pref'=>'',
            'emails'=>array(),
            'email'=> '',
            'email_location'=>'', // home / work
            'email_pref'=>'',
            'impps'=>array(),
            'impp_protocol'=>'',
            'impp_type'=>'', // home / work
            'impp_pref'=>'',
            'impp'=>'',
            'langs'=>array(),
            'lang'=>'',
            'lang_type'=>'', // home / work
            'lang_pref'=>'',
            'geo_latitude'=>'',
            'geo_longitude'=>'',
            'title'=>'',
            'role'=>'',
            'logo_mode'=>'URL',
            'logo_url'=>'',
            'org_title'=>'',
            'org_unit'=>'',
            'members'=>array(),
            'member'=>'',
            'relateds'=> array(),
            'related_type'=>'', // "contact" / "acquaintance" / "friend" / "met" / "co-worker" / "colleague" / "co-resident" / "neighbor" / "child" / "parent" / "sibling" / "spouse" / "kin" / "muse" / "crush" / "date" / "sweetheart" / "me" / "agent" / "emergency"
            'related_value'=>'',
            'categories'=>array(),
            'url'=>'',
            'note'=>'',
            'css_file' => '', //for hCard Only,
            'rev' => 0
       );
    }

    /* Mark: Specific prive tool methods */

    /**
     * return export action params.
     * @return array
     */
    private function get_exportDefaultParams() {
        return array(
            'output' => 'void', // void / text / file / download
            'target' => '',
        );
    }

    /**
     * Return import action params.
     * @return array
     */
    private function get_importDefaultParams() {
        return array(
            'input'     => '', //    void / text / file / url
            'source'    => '',
        );
    }

    /**
     * Load vCard object.
     * @param string $version
     * @return void
     */
    private function load_vCardObject($version='') {

        /* check if object is already loaded */
        if (isset($this->loadedObjects[$version]))
            return $this->loadedObjects[$version];

        /* load object file */
        if ($this->load_library('GenericVCardHandler-'.$version)) {
            $this->loadedObjects[$version] = true;
            return true;
        }
        $this->loadedObjects[$version] = false;
        return false;
    }

    /**
     * Return encoded title.
     * @param string $title
     * @return string
     */
    private function encode_cardTitle($title) {
        $v = trim($title);
        $v = preg_replace('/[^a-zA-Z0-9\-]/', '-', $v);
        return $v.'.vcf';
    }

    /**
     * Define plugin error.
     * @param string $error
     * @param mixed $param
     * @return void
     */
    private function define_pluginError($error, $param=null) {
        $this->pluginError = $this->get_translation('fatalerror_'.$error, $param);
    }

    /**
     * Return plugin error.
     * @return string
     */
    public function get_pluginError() {
        return $this->pluginError;
    }

    /**
     * Method to get country code from title
     * @param string $code
     * @return string
     */
    private function getCountryCode($code) {
        $foundKey = false;

        //Start searching in default lang
        if ($foundKey == false) {
            $foundKey = countries_getCode(null, $code);
        }
        //Search in other languages
        if ($foundKey == false) {
            $foundKey = countries_getCode('en', $code);
        }
        //Search in other languages
        if ($foundKey == false) {
            $foundKey = countries_getCode('br', $code);
        }
        //Search in other languages
        if ($foundKey == false) {
            $foundKey = countries_getCode('de', $code);
        }
        //Search in other languages
        if ($foundKey == false) {
            $foundKey = countries_getCode('es', $code);
        }
        //Search in other languages
        if ($foundKey == false) {
            $foundKey = countries_getCode('pt', $code);
        }

        //Default Country
        countries_loadLocales();

        return $foundKey;
    }

    /**
     * Check if the given content is a genuine vCard
     * @param unknown $content
     * @todo add support for xCard, jCard, hCard
     * @todo Check for mandatory attributes (BEGIN,END, etc...)
     * @return vCard version
     */
    function check_vCardVersion($content) {
        //First thing to check if its empty
        if (strlen($content) == 0) {
            $this->define_pluginError('emptyfile');
            return false;
        }

        // TEST FOR 2.1 3.0 AND 4.0

        // Counting the begin/end separators. If there aren't any or the count doesn't match, there is a problem with the file.
        // If there is only one, this is a single vCard, if more, multiple vCards are combined.
        $Matches = array();
        $vCardBeginCount = preg_match_all('{^BEGIN\:VCARD}miS', $content, $Matches);
        $vCardEndCount = preg_match_all('{^END\:VCARD}miS', $content, $Matches);

        if ($vCardBeginCount == 0 || $vCardEndCount == 0 || $vCardBeginCount != $vCardEndCount) {
            //NOT A VCARD
        } else if ($vCardBeginCount > 1 || $vCardEndCount > 1) {
            $this->define_pluginError("multiplecontactsnotallowed");
            return false;
        } else {
            //we have a vcard, now we try to get its version
            $Lines = explode("\n", $content);

            foreach ($Lines as $Line) {
                //We don't nees empty lines
                if (strpos($Line, ':') === false) {
                    continue;
                }

                //every line can be divised
                list($Key, $Value) = explode(':', $Line, 2);

                // escape value for unecessary chars
                $Value = trim (self::Unescape ($Value));

                if ($Key == "VERSION") {
                    //We support only those versions
                    if ($Value == "2.1" || $Value == "3.0" || $Value == "4.0") {
                        return $Value;
                    }
                }
            }
        }

    //Test for jCard
    $contentJsonified = json_decode($content, true);
    if ($contentJsonified && $contentJsonified[0] == "vcard") {
        return "jCard";
    }

    $result = simplexml_load_string($content, 'SimpleXmlElement', LIBXML_NOERROR+LIBXML_ERR_FATAL+LIBXML_ERR_NONE);
    if ($result == true) {
        //Test for xCard and hCard
        $reader = new XMLReader();
        $reader->XML($content);

        while($reader->read()) {
            if ($reader->nodeType == XMLReader::ELEMENT && $reader->name == "vcards") {
                if ($reader->getAttribute("xmlns") == "urn:ietf:params:xml:ns:vcard-4.0") {
                    $reader->close();
                    return "xCard";
                }
            } elseif ($reader->nodeType == XMLReader::ELEMENT &&
                    $reader->getAttribute("class") == "h-card") {
                return "hCard";
            }
        }
        }

        $this->define_pluginError('cannotdetectvcardversion');
        return false;
    }

    /**
     * Unescape text/
     * @todo verify this method doesnt exist somewhere else
     * @todo refactor it, put it somewhere higher
     * @param string $Text to prepare.
     * @return string Resulting text.
     */
     private static function Unescape($Text) {
         return str_replace(array('\:', '\;', '\,', "\n" , "\r", "\r\n"), array(':', ';', ',', '', '', ''), $Text);
     }


    /**
     * Clean the vCard.
     * @param string $content
     * @return string
     */
    private static function cleanVcard($content) {
        return preg_replace(array('/item[0-9]{1,}\./i', '/[ ]?[\r\n\t]{1,}[ ]?/'), array('', "\n"), $content);
    }
}
?>
