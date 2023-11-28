<?php
/**
 * @brief Countries data.
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Nov 2023
 * @date Modification: Nov 2023
 * @copyright 2023 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $__countriesData;

$__countriesData = json_decode('{
    "ad" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "ca"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "and",
        "NumericCode"           : "020",
        "PhoneIndex"            : "376",
        "Timezones"             : [
            "Europe/Andorra"
        ],
        "ZipCodeCheck"          : "/^AD[0-9]{3}$/i",
        "Currency"              : "eur",
        "Parent"                : null
    },
    "ae" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "ar"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "are",
        "NumericCode"           : "784",
        "PhoneIndex"            : "971",
        "Timezones"             : [
            "Asia/Dubai"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "aed",
        "Parent"                : null
    },
    "af" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "fa",
            "ps"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "afg",
        "NumericCode"           : "004",
        "PhoneIndex"            : "93",
        "Timezones"             : [
            "Asia/Kabul"
        ],
        "ZipCodeCheck"          : "/^[1-4][0-9]{3}$/i",
        "Currency"              : "afn",
        "Parent"                : null
    },
    "ag" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "atg",
        "NumericCode"           : "028",
        "PhoneIndex"            : "1-268",
        "Timezones"             : [
            "America/Antigua",
            "America/St_Johns"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "xcd",
        "Parent"                : null
    },
    "ai" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "aia",
        "NumericCode"           : "660",
        "PhoneIndex"            : "1-264",
        "Timezones"             : [
            "America/Anguilla"
        ],
        "ZipCodeCheck"          : "/^AI\\\-2640$/",
        "Currency"              : "xcd",
        "Parent"                : "gb"
    },
    "al" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "sq"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "alb",
        "NumericCode"           : "008",
        "PhoneIndex"            : "355",
        "Timezones"             : [
            "Europe/Tirane"
        ],
        "ZipCodeCheck"          : "/^[0-9]{4}$/i",
        "Currency"              : "all",
        "Parent"                : null
    },
    "am" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "hy"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "arm",
        "NumericCode"           : "051",
        "PhoneIndex"            : "374",
        "Timezones"             : [
            "Asia/Yerevan"
        ],
        "ZipCodeCheck"          : "/^[0-9]{4}$/i",
        "Currency"              : "amd",
        "Parent"                : null
    },
    "ao" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "pt"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "ago",
        "NumericCode"           : "024",
        "PhoneIndex"            : "244",
        "Timezones"             : [
            "Africa/Luanda"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "aoa",
        "Parent"                : null
    },
    "aq" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "en",
            "es",
            "fr",
            "ru"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "ata",
        "NumericCode"           : "010",
        "PhoneIndex"            : "",
        "Timezones"             : [
            "Antarctica/Rothera",
            "Antarctica/Palmer",
            "Antarctica/Troll",
            "Antarctica/Syowa",
            "Antarctica/Mawson",
            "Antarctica/Vostok",
            "Antarctica/Davis",
            "Antarctica/Casey",
            "Antarctica/Macquarie",
            "Antarctica/DumontDUrville",
            "Antarctica/McMurdo"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "",
        "Parent"                : null
    },
    "ar" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "es"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "arg",
        "NumericCode"           : "032",
        "PhoneIndex"            : "54",
        "Timezones"             : [
            "America/Argentina/Buenos_Aires",
            "America/Argentina/Catamarca",
            "America/Argentina/Cordoba",
            "America/Argentina/Jujuy",
            "America/Argentina/La_Rioja",
            "America/Argentina/Mendoza",
            "America/Argentina/Rio_Gallegos",
            "America/Argentina/Salta",
            "America/Argentina/San_Juan",
            "America/Argentina/San_Luis",
            "America/Argentina/Tucuman",
            "America/Argentina/Ushuaia"
        ],
        "ZipCodeCheck"          : "/^[A-Z][0-9]{4}[A-Z]{3}$/i",
        "Currency"              : "ars",
        "Parent"                : null
    },
    "as" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "en",
            "sm"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "asm",
        "NumericCode"           : "016",
        "PhoneIndex"            : "1-684",
        "Timezones"             : [
            "Pacific/Pago_Pago"
        ],
        "ZipCodeCheck"          : "/^96799(\\\\-[0-9]{4})?$/i",
        "Currency"              : "usd",
        "Parent"                : "us"
    },
    "at" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "de"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "aut",
        "NumericCode"           : "040",
        "PhoneIndex"            : "43",
        "Timezones"             : [
            "Europe/Vienna"
        ],
        "ZipCodeCheck"          : "/^[0-9]{4}$/",
        "Currency"              : "eur",
        "Parent"                : null
    },
    "au" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "aus",
        "NumericCode"           : "036",
        "PhoneIndex"            : "61",
        "Timezones"             : [
            "Australia/Adelaide",
            "Australia/Brisbane",
            "Australia/Broken_Hill",
            "Australia/Darwin",
            "Australia/Eucla",
            "Australia/Hobart",
            "Australia/Lindeman",
            "Australia/Lord_Howe",
            "Australia/Melbourne",
            "Australia/Perth",
            "Australia/Sydney"
        ],
        "ZipCodeCheck"          : "/^[0-9]{4}$/",
        "Currency"              : "aud",
        "Parent"                : null
    },
    "aw" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "nl",
            "pap"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "abw",
        "NumericCode"           : "533",
        "PhoneIndex"            : "297",
        "Timezones"             : [
            "America/Aruba"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "awg",
        "Parent"                : "nl"
    },
    "ax" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "sv"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "ala",
        "NumericCode"           : "248",
        "PhoneIndex"            : "",
        "Timezones"             : [
            "Europe/Mariehamn"
        ],
        "ZipCodeCheck"          : "/^(AX\\\\-)?[0-9]{5}$/i",
        "Currency"              : "eur",
        "Parent"                : "fi"
    },
    "az" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "az"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "aze",
        "NumericCode"           : "031",
        "PhoneIndex"            : "994",
        "Timezones"             : [
            "Asia/Baku"
        ],
        "ZipCodeCheck"          : "/^AZ [0-9]{4}$/i",
        "Currency"              : "azn",
        "Parent"                : null
    },
    "ba" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "bs",
            "hr",
            "sr"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "bih",
        "NumericCode"           : "070",
        "PhoneIndex"            : "387",
        "Timezones"             : [
            "Europe/Sarajevo"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "bam",
        "Parent"                : null
    },
    "bb" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "brb",
        "NumericCode"           : "052",
        "PhoneIndex"            : "12463",
        "Timezones"             : [
            "America/Barbados"
        ],
        "ZipCodeCheck"          : "/^BB[0-9]{5}$/i",
        "Currency"              : "bbd",
        "Parent"                : null
    },
    "bd" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "bn"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "bgd",
        "NumericCode"           : "050",
        "PhoneIndex"            : "880",
        "Timezones"             : [
            "Asia/Dhaka"
        ],
        "ZipCodeCheck"          : "/^[0-9]{4}$/i",
        "Currency"              : "bdt",
        "Parent"                : null
    },
    "be" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "nl",
            "fr",
            "de"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "bel",
        "NumericCode"           : "056",
        "PhoneIndex"            : "32",
        "Timezones"             : [
            "Europe/Brussels"
        ],
        "ZipCodeCheck"          : "/^[0-9]{4}$/",
        "Currency"              : "eur",
        "Parent"                : null
    },
    "bf" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "fr"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "bfa",
        "NumericCode"           : "854",
        "PhoneIndex"            : "226",
        "Timezones"             : [
            "Africa/Ouagadougou"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "xof",
        "Parent"                : null
    },
    "bg" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "bg"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "bgr",
        "NumericCode"           : "100",
        "PhoneIndex"            : "359",
        "Timezones"             : [
            "Europe/Sofia"
        ],
        "ZipCodeCheck"          : "/^[0-9]{4}$/",
        "Currency"              : "bgn",
        "Parent"                : null
    },
    "bh" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "bh"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "bhr",
        "NumericCode"           : "048",
        "PhoneIndex"            : "973",
        "Timezones"             : [
            "Asia/Bahrain"
        ],
        "ZipCodeCheck"          : "/^[0-9]{3,4}$/",
        "Currency"              : "bhd",
        "Parent"                : null
    },
    "bi" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "fr"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "bdi",
        "NumericCode"           : "108",
        "PhoneIndex"            : "257",
        "Timezones"             : [
            "Africa/Bujumbura"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "bif",
        "Parent"                : null
    },
    "bj" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "fr"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "ben",
        "NumericCode"           : "204",
        "PhoneIndex"            : "229",
        "Timezones"             : [
            "Africa/Porto-Novo"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "xof",
        "Parent"                : null
    },
    "bl" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "fr"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "blm",
        "NumericCode"           : "652",
        "PhoneIndex"            : "",
        "Timezones"             : [
            "America/St_Barthelemy"
        ],
        "ZipCodeCheck"          : "/^97133$/",
        "Currency"              : "eur",
        "Parent"                : "fr"
    },
    "bm" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "bmu",
        "NumericCode"           : "060",
        "PhoneIndex"            : "14413",
        "Timezones"             : [
            "Atlantic/Bermuda"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "bmd",
        "Parent"                : "gb"
    },
    "bn" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "ms"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "brn",
        "NumericCode"           : "096",
        "PhoneIndex"            : "673",
        "Timezones"             : [
            "Asia/Brunei"
        ],
        "ZipCodeCheck"          : "/^[A-Z]{2}[0-9]{3,4}$/",
        "Currency"              : "bnd",
        "Parent"                : null
    },
    "bo" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "es",
            "qu",
            "gn",
            "ay"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "bol",
        "NumericCode"           : "068",
        "PhoneIndex"            : "591",
        "Timezones"             : [
            "America/La_Paz"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "bob",
        "Parent"                : null
    },
    "bq" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "nl"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "bes",
        "NumericCode"           : "535",
        "PhoneIndex"            : "599",
        "Timezones"             : [
            "America/Kralendijk"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "usd",
        "Parent"                : "nl"
    },
    "br" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "pt"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "bra",
        "NumericCode"           : "076",
        "PhoneIndex"            : "55",
        "Timezones"             : [
            "America/Araguaina",
            "America/Bahia",
            "America/Belem",
            "America/Boa_Vista",
            "America/Campo_Grande",
            "America/Cuiaba",
            "America/Eirunepe",
            "America/Fortaleza",
            "America/Maceio",
            "America/Manaus",
            "America/Noronha",
            "America/Porto_Velho",
            "America/Recife",
            "America/Rio_Branco",
            "America/Santarem",
            "America/Sao_Paulo"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}(\\\\-?[0-9]{3})?$/",
        "Currency"              : "brl",
        "Parent"                : null
    },
    "bs" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "bhs",
        "NumericCode"           : "044",
        "PhoneIndex"            : "1-242",
        "Timezones"             : [
            "America/Nassau"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "bsd",
        "Parent"                : null
    },
    "bt" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "dz"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "btn",
        "NumericCode"           : "064",
        "PhoneIndex"            : "975",
        "Timezones"             : [
            "Asia/Thimphu"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/i",
        "Currency"              : "btn",
        "Parent"                : null
    },
    "bv" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "no"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "bvt",
        "NumericCode"           : "074",
        "PhoneIndex"            : "",
        "Timezones"             : [
            "Europe/Oslo"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "",
        "Parent"                : "no"
    },
    "bw" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en",
            "tn"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "bwa",
        "NumericCode"           : "072",
        "PhoneIndex"            : "267",
        "Timezones"             : [
            "Africa/Gaborone"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "bwp",
        "Parent"                : null
    },
    "by" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "be",
            "ru"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "blr",
        "NumericCode"           : "112",
        "PhoneIndex"            : "375",
        "Timezones"             : [
            "Europe/Minsk"
        ],
        "ZipCodeCheck"          : "/^[0-9]{6}$/",
        "Currency"              : "byn",
        "Parent"                : null
    },
    "bz" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "blz",
        "NumericCode"           : "084",
        "PhoneIndex"            : "501",
        "Timezones"             : [
            "America/Belize"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "bzd",
        "Parent"                : null
    },
    "ca" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en",
            "fr"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "can",
        "NumericCode"           : "124",
        "PhoneIndex"            : "1",
        "Timezones"             : [
            "America/Atikokan",
            "America/Blanc-Sablon",
            "America/Cambridge_Bay",
            "America/Creston",
            "America/Dawson",
            "America/Dawson_Creek",
            "America/Edmonton",
            "America/Fort_Nelson",
            "America/Glace_Bay",
            "America/Goose_Bay",
            "America/Halifax",
            "America/Inuvik",
            "America/Iqaluit",
            "America/Moncton",
            "America/Nipigon",
            "America/Pangnirtung",
            "America/Rainy_River",
            "America/Rankin_Inlet",
            "America/Regina",
            "America/Resolute",
            "America/Swift_Current",
            "America/Thunder_Bay",
            "America/Toronto",
            "America/Vancouver",
            "America/Whitehorse",
            "America/Winnipeg",
            "America/Yellowknife"
        ],
        "ZipCodeCheck"          : "/^[A-Z][0-9][A-Z] [0-9][A-Z][0-9]$/i",
        "Currency"              : "cad",
        "Parent"                : null
    },
    "cc" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "cck",
        "NumericCode"           : "166",
        "PhoneIndex"            : "672",
        "Timezones"             : [
            "Indian/Cocos"
        ],
        "ZipCodeCheck"          : "/^[0-9]{4}$/",
        "Currency"              : "aud",
        "Parent"                : "au"
    },
    "cd" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "fr"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "cod",
        "NumericCode"           : "180",
        "PhoneIndex"            : "243",
        "Timezones"             : [
            "Africa/Kinshasa",
            "Africa/Lubumbashi"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "cdf",
        "Parent"                : null
    },
    "cf" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "fr",
            "sg"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "caf",
        "NumericCode"           : "140",
        "PhoneIndex"            : "236",
        "Timezones"             : [
            "Africa/Bangui"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "xaf",
        "Parent"                : null
    },
    "cg" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "fr"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "cog",
        "NumericCode"           : "178",
        "PhoneIndex"            : "242",
        "Timezones"             : [
            "Africa/Brazzaville"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "xaf",
        "Parent"                : null
    },
    "ch" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "de",
            "fr",
            "it",
            "rm"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "che",
        "NumericCode"           : "756",
        "PhoneIndex"            : "41",
        "Timezones"             : [
            "Europe/Zurich"
        ],
        "ZipCodeCheck"          : "/^[0-9]{4}$/",
        "Currency"              : "chf",
        "Parent"                : null
    },
    "ci" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "fr"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "civ",
        "NumericCode"           : "380",
        "PhoneIndex"            : "225",
        "Timezones"             : [
            "Africa/Abidjan"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "xof",
        "Parent"                : null
    },
    "ck" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en",
            "rar"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "cok",
        "NumericCode"           : "184",
        "PhoneIndex"            : "682",
        "Timezones"             : [
            "Pacific/Rarotonga"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : [
            "ckd",
            "nzd"
        ],
        "Parent"                : null
    },
    "cl" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "es"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "chl",
        "NumericCode"           : "152",
        "PhoneIndex"            : "56",
        "Timezones"             : [
            "America/Punta_Arenas",
            "America/Santiago",
            "Pacific/Easter"
        ],
        "ZipCodeCheck"          : "/^[0-9]{3}\\\\-?[0-9]{4}$/",
        "Currency"              : "clp",
        "Parent"                : null
    },
    "cm" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "fr",
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "cmr",
        "NumericCode"           : "120",
        "PhoneIndex"            : "237",
        "Timezones"             : [
            "Africa/Douala"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "xaf",
        "Parent"                : null
    },
    "cn" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "zh"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "chn",
        "NumericCode"           : "156",
        "PhoneIndex"            : "86",
        "Timezones"             : [
            "Asia/Shanghai",
            "Asia/Urumqi"
        ],
        "ZipCodeCheck"          : "/^[0-9]{6}$/",
        "Currency"              : "cny",
        "Parent"                : null
    },
    "co" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "es"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "col",
        "NumericCode"           : "170",
        "PhoneIndex"            : "57",
        "Timezones"             : [
            "America/Bogota"
        ],
        "ZipCodeCheck"          : "/^[0-3][0-9]{5}$/",
        "Currency"              : "cop",
        "Parent"                : null
    },
    "cr" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "es"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "cri",
        "NumericCode"           : "188",
        "PhoneIndex"            : "506",
        "Timezones"             : [
            "America/Costa_Rica"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "crc",
        "Parent"                : null
    },
    "cu" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "es"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "cub",
        "NumericCode"           : "192",
        "PhoneIndex"            : "53",
        "Timezones"             : [
            "America/Havana"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "cup",
        "Parent"                : null
    },
    "cv" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "pt"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "cpv",
        "NumericCode"           : "132",
        "PhoneIndex"            : "238",
        "Timezones"             : [
            "Atlantic/Cape_Verde"
        ],
        "ZipCodeCheck"          : "/^[0-9]{4}$/",
        "Currency"              : "cve",
        "Parent"                : null
    },
    "cw" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "nl",
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "cuw",
        "NumericCode"           : "531",
        "PhoneIndex"            : "599",
        "Timezones"             : [
            "America/Curacao"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "ang",
        "Parent"                : null
    },
    "cx" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "cxr",
        "NumericCode"           : "162",
        "PhoneIndex"            : "672",
        "Timezones"             : [
            "Indian/Christmas"
        ],
        "ZipCodeCheck"          : "/^[0-9]{4}$/",
        "Currency"              : "aud",
        "Parent"                : "en"
    },
    "cy" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "el",
            "tr"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "cyp",
        "NumericCode"           : "196",
        "PhoneIndex"            : "357",
        "Timezones"             : [
            "Asia/Famagusta",
            "Asia/Nicosia"
        ],
        "ZipCodeCheck"          : "/^[0-9]{4}$/",
        "Currency"              : "eur",
        "Parent"                : null
    },
    "cz" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "cs"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "cze",
        "NumericCode"           : "203",
        "PhoneIndex"            : "420",
        "Timezones"             : [
            "Europe/Prague"
        ],
        "ZipCodeCheck"          : "/^[1-7][0-9]{2} [0-9]{2}$/",
        "Currency"              : "czk",
        "Parent"                : null
    },
    "de" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "de"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "deu",
        "NumericCode"           : "276",
        "PhoneIndex"            : "49",
        "Timezones"             : [
            "Europe/Berlin",
            "Europe/Busingen"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "eur",
        "Parent"                : null
    },
    "dj" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "fr",
            "ar",
            "so",
            "aa"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "dji",
        "NumericCode"           : "262",
        "PhoneIndex"            : "253",
        "Timezones"             : [
            "Africa/Djibouti"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "djf",
        "Parent"                : null
    },
    "dk" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "da"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "dnk",
        "NumericCode"           : "208",
        "PhoneIndex"            : "45",
        "Timezones"             : [
            "Europe/Copenhagen"
        ],
        "ZipCodeCheck"          : "/^[0-9]{4}$/",
        "Currency"              : "dkk",
        "Parent"                : null
    },
    "dm" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "dma",
        "NumericCode"           : "212",
        "PhoneIndex"            : "17673",
        "Timezones"             : [
            "America/Dominica"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "xcd",
        "Parent"                : null
    },
    "do" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "es"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "dom",
        "NumericCode"           : "214",
        "PhoneIndex"            : "13",
        "Timezones"             : [
            "America/Santo_Domingo"
         ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "dop",
        "Parent"                : null
    },
    "dz" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "ar"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "dza",
        "NumericCode"           : "012",
        "PhoneIndex"            : "213",
        "Timezones"             : [
            "Africa/Algiers"
        ],
        "ZipCodeCheck"          : "/^[0-4][0-9]{4}$/i",
        "Currency"              : "dzd",
        "Parent"                : null
    },
    "ec" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "es"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "ecu",
        "NumericCode"           : "218",
        "PhoneIndex"            : "593",
        "Timezones"             : [
            "America/Guayaquil",
            "Pacific/Galapagos"
        ],
        "ZipCodeCheck"          : "/^[0-9]{6}$/",
        "Currency"              : "usd",
        "Parent"                : null
    },
    "ee" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "et"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "est",
        "NumericCode"           : "233",
        "PhoneIndex"            : "372",
        "Timezones"             : [
            "Europe/Tallinn"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "eur",
        "Parent"                : null
    },
    "eg" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "ar"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "egy",
        "NumericCode"           : "818",
        "PhoneIndex"            : "20",
        "Timezones"             : [
            "Africa/Cairo"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "egp",
        "Parent"                : null
    },
    "eh" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "ar",
            "es",
            "fr"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "esh",
        "NumericCode"           : "732",
        "PhoneIndex"            : "212",
        "Timezones"             : [
            "Africa/El_Aaiun"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "",
        "Parent"                : null
    },
    "er" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "ti",
            "ar",
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "eri",
        "NumericCode"           : "232",
        "PhoneIndex"            : "291",
        "Timezones"             : [
            "Africa/Asmara"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "ern",
        "Parent"                : null
    },
    "es" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "es",
            "ast",
            "ca",
            "eu",
            "gl"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "esp",
        "NumericCode"           : "724",
        "PhoneIndex"            : "34",
        "Timezones"             : [
            "Atlantic/Canary",
            "Africa/Ceuta",
            "Europe/Madrid"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "eur",
        "Parent"                : null
    },
    "et" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "am",
            "om"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "eth",
        "NumericCode"           : "231",
        "PhoneIndex"            : "251",
        "Timezones"             : [
            "Africa/Addis_Ababa"
        ],
        "ZipCodeCheck"          : "/^[0-9]{4}$/",
        "Currency"              : "etb",
        "Parent"                : null
    },
    "fi" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "fi",
            "sv",
            "se"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "fin",
        "NumericCode"           : "246",
        "PhoneIndex"            : "358",
        "Timezones"             : [
            "Europe/Helsinki"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "eur",
        "Parent"                : null
    },
    "fj" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "fji",
        "NumericCode"           : "242",
        "PhoneIndex"            : "679",
        "Timezones"             : [
            "Pacific/Fiji"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "fjd",
        "Parent"                : null
    },
    "fk" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "flk",
        "NumericCode"           : "238",
        "PhoneIndex"            : "500",
        "Timezones"             : [
            "Atlantic/Stanley"
        ],
        "ZipCodeCheck"          : "/^FIQQ 1ZZ$/i",
        "Currency"              : "fkp",
        "Parent"                : "gb"
    },
    "fm" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "fsm",
        "NumericCode"           : "583",
        "PhoneIndex"            : "691",
        "Timezones"             : [
            "Pacific/Chuuk",
            "Pacific/Kosrae",
            "Pacific/Pohnpei"
        ],
        "ZipCodeCheck"          : "/^9694[1-4](\\\\-[0-9]{4})$/",
        "Currency"              : "usd",
        "Parent"                : null
    },
    "fo" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "fo",
            "da"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "fro",
        "NumericCode"           : "234",
        "PhoneIndex"            : "298",
        "Timezones"             : [
            "Atlantic/Faroe"
        ],
        "ZipCodeCheck"          : "/^[0-9]{3}$/",
        "Currency"              : "dkk",
        "Parent"                : "dk"
    },
    "fr" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "fr"
        ],
        "UnofficialLanguages"   : [
            "co",
            "br"
        ],
        "3LettersCode"          : "fra",
        "NumericCode"           : "250",
        "PhoneIndex"            : "33",
        "Timezones"             : [
            "Europe/Paris"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "eur",
        "Parent"                : null
    },
    "ga" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "fr"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "gab",
        "NumericCode"           : "266",
        "PhoneIndex"            : "241",
        "Timezones"             : [
            "Africa/Libreville"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "xaf",
        "Parent"                : null
    },
    "gb" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en",
            "ga",
            "cy",
            "gd",
            "kw"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "gbr",
        "NumericCode"           : "826",
        "PhoneIndex"            : "44",
        "Timezones"             : [
            "Europe/London"
        ],
        "ZipCodeCheck"          : "/^[A-Z]{1,2}([0-9]{2,3}|[0-9][A-Z][0-9])[A-Z]{2}$/i",
        "Currency"              : "gbp",
        "Parent"                : null
    },
    "gd" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "grd",
        "NumericCode"           : "308",
        "PhoneIndex"            : "1-473",
        "Timezones"             : [
            "America/Grenada"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "xcd",
        "Parent"                : null
    },
    "ge" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "ka"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "geo",
        "NumericCode"           : "268",
        "PhoneIndex"            : "995",
        "Timezones"             : [
            "Asia/Tbilisi"
        ],
        "ZipCodeCheck"          : "/^[0-9]{4}$/",
        "Currency"              : "gel",
        "Parent"                : null
    },
    "gf" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "fr"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "guf",
        "NumericCode"           : "254",
        "PhoneIndex"            : "594",
        "Timezones"             : [
            "America/Cayenne"
        ],
        "ZipCodeCheck"          : "/^973[0-9]{2}$/",
        "Currency"              : "eur",
        "Parent"                : "fr"
    },
    "gg" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "ggy",
        "NumericCode"           : "831",
        "PhoneIndex"            : "44-1481",
        "Timezones"             : [
            "Europe/Guernsey"
        ],
        "ZipCodeCheck"          : "/^GY([0-9]{2,3}|[0-9][A-Z][0-9])[A-Z]{2}$/i",
        "Currency"              : "gbp",
        "Parent"                : null
    },
    "gh" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "gha",
        "NumericCode"           : "288",
        "PhoneIndex"            : "233",
        "Timezones"             : [
            "Africa/Accra"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "ghs",
        "Parent"                : null
    },
    "gi" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "gib",
        "NumericCode"           : "292",
        "PhoneIndex"            : "350",
        "Timezones"             : [
            "Europe/Gibraltar"
        ],
        "ZipCodeCheck"          : "/^GX11 1AA$/i",
        "Currency"              : "gip",
        "Parent"                : "gb"
    },
    "gl" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "kl",
            "da"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "grl",
        "NumericCode"           : "304",
        "PhoneIndex"            : "299",
        "Timezones"             : [
            "America/Danmarkshavn",
            "America/Nuuk",
            "America/Scoresbysund",
            "America/Thule"
        ],
        "ZipCodeCheck"          : "/^[0-9]{4}$/",
        "Currency"              : "dkk",
        "Parent"                : "dk"
    },
    "gm" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "gmb",
        "NumericCode"           : "270",
        "PhoneIndex"            : "220",
        "Timezones"             : [
            "Africa/Banjul"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "gmd",
        "Parent"                : null
    },
    "gn" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "fr"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "gin",
        "NumericCode"           : "324",
        "PhoneIndex"            : "224",
        "Timezones"             : [
            "Africa/Conakry"
        ],
        "ZipCodeCheck"          : "/^[0-9]{3}$/",
        "Currency"              : "gnf",
        "Parent"                : null
    },
    "gp" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "fr"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "glp",
        "NumericCode"           : "312",
        "PhoneIndex"            : "",
        "Timezones"             : [
            "America/Guadeloupe"
        ],
        "ZipCodeCheck"          : "/^971[0-9]{2}$/",
        "Currency"              : "eur",
        "Parent"                : "fr"
    },
    "gq" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "es",
            "fr",
            "pt"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "gnq",
        "NumericCode"           : "226",
        "PhoneIndex"            : "240",
        "Timezones"             : [
            "Africa/Malabo"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "xaf",
        "Parent"                : null
    },
    "gr" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "el"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "grc",
        "NumericCode"           : "300",
        "PhoneIndex"            : "30",
        "Timezones"             : [
            "Europe/Athens"
        ],
        "ZipCodeCheck"          : "/^[0-9]{3} ?[0-9]{2}$/",
        "Currency"              : "eur",
        "Parent"                : null
    },
    "gs" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "sgs",
        "NumericCode"           : "239",
        "PhoneIndex"            : "",
        "Timezones"             : [
            "Atlantic/South_Georgia"
        ],
        "ZipCodeCheck"          : "/^SIQQ 1ZZ$/i",
        "Currency"              : "fkp",
        "Parent"                : "gb"
    },
    "gt" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "es"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "gtm",
        "NumericCode"           : "320",
        "PhoneIndex"            : "502",
        "Timezones"             : [
            "America/Guatemala"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "gtq",
        "Parent"                : null
    },
    "gu" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "en",
            "ch"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "gum",
        "NumericCode"           : "316",
        "PhoneIndex"            : "1-671",
        "Timezones"             : [
            "Pacific/Guam"
        ],
        "ZipCodeCheck"          : "/^969[1-3][0-9](\\\\-[0-9]{4})?$/i",
        "Currency"              : "usd",
        "Parent"                : "us"
    },
    "gw" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "pt"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "gnb",
        "NumericCode"           : "624",
        "PhoneIndex"            : "245",
        "Timezones"             : [
            "Africa/Bissau"
        ],
        "ZipCodeCheck"          : "/^[0-9]{4}$/",
        "Currency"              : "xof",
        "Parent"                : null
    },
    "gy" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "guy",
        "NumericCode"           : "328",
        "PhoneIndex"            : "592",
        "Timezones"             : [
            "America/Guyana"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "gyd",
        "Parent"                : null
    },
    "hk" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "zh",
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "hkg",
        "NumericCode"           : "344",
        "PhoneIndex"            : "852",
        "Timezones"             : [
            "Asia/Hong_Kong"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "hkd",
        "Parent"                : "cn"
    },
    "hm" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "hmd",
        "NumericCode"           : "334",
        "PhoneIndex"            : "672",
        "Timezones"             : [
            "Indian/Kerguelen"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "aud",
        "Parent"                : "au"
    },
    "hn" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "es"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "hnd",
        "NumericCode"           : "340",
        "PhoneIndex"            : "504",
        "Timezones"             : [
            "America/Tegucigalpa"
        ],
        "ZipCodeCheck"          : "/^([A-Z]{2}[0-9]|[0-9]{2})[0-9]{3}$/i",
        "Currency"              : "hnl",
        "Parent"                : null
    },
    "hr" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "hr"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "hrv",
        "NumericCode"           : "191",
        "PhoneIndex"            : "385",
        "Timezones"             : [
            "Europe/Zagreb"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "hrk",
        "Parent"                : null
    },
    "ht" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "fr",
            "ht"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "hti",
        "NumericCode"           : "332",
        "PhoneIndex"            : "509",
        "Timezones"             : [
            "America/Port-au-Prince"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "htg",
        "Parent"                : null
    },
    "hu" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "hu"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "hun",
        "NumericCode"           : "348",
        "PhoneIndex"            : "36",
        "Timezones"             : [
            "Europe/Budapest"
        ],
        "ZipCodeCheck"          : "/^[0-9]{4}$/",
        "Currency"              : "huf",
        "Parent"                : null
    },
    "id" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "id"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "idn",
        "NumericCode"           : "360",
        "PhoneIndex"            : "62",
        "Timezones"             : [
            "Asia/Jakarta",
            "Asia/Jayapura",
            "Asia/Makassar",
            "Asia/Pontianak"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "idr",
        "Parent"                : null
    },
    "ie" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en",
            "ga"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "irl",
        "NumericCode"           : "372",
        "PhoneIndex"            : "353",
        "Timezones"             : [
            "Europe/Dublin"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "eur",
        "Parent"                : null
    },
    "il" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "he"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "isr",
        "NumericCode"           : "376",
        "PhoneIndex"            : "972",
        "Timezones"             : [
            "Asia/Jerusalem"
        ],
        "ZipCodeCheck"          : "/^[0-9]{7}$/",
        "Currency"              : "ils",
        "Parent"                : null
    },
    "im" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "imn",
        "NumericCode"           : "833",
        "PhoneIndex"            : "44-1624",
        "Timezones"             : [
            "Europe/Isle_of_Man"
        ],
        "ZipCodeCheck"          : "/^IM([0-9]{2,3}|[0-9][A-Z][0-9])[A-Z]{2}$/i",
        "Currency"              : "gbp",
        "Parent"                : null
    },
    "in" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "hi",
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "ind",
        "NumericCode"           : "356",
        "PhoneIndex"            : "91",
        "Timezones"             : [
            "Asia/Kolkata"
        ],
        "ZipCodeCheck"          : "/^[0-9]{3} ?[0-9]{3}$/",
        "Currency"              : "inr",
        "Parent"                : null
    },
    "io" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "iot",
        "NumericCode"           : "086",
        "PhoneIndex"            : "246",
        "Timezones"             : [
            "Indian/Chagos"
        ],
        "ZipCodeCheck"          : "/^BBND 1ZZ$/",
        "Currency"              : [
            "gbp",
            "usd"
        ],
        "Parent"                : "gb"
    },
    "iq" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "ar",
            "ku"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "irq",
        "NumericCode"           : "368",
        "PhoneIndex"            : "964",
        "Timezones"             : [
            "Asia/Baghdad"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "idq",
        "Parent"                : null
    },
    "ir" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "fa"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "irn",
        "NumericCode"           : "364",
        "PhoneIndex"            : "98",
        "Timezones"             : [
            "Asia/Tehran"
        ],
        "ZipCodeCheck"          : "/^[0-9]{10}$/",
        "Currency"              : "irr",
        "Parent"                : null
    },
    "is" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "is"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "isl",
        "NumericCode"           : "352",
        "PhoneIndex"            : "354",
        "Timezones"             : [
            "Atlantic/Reykjavik"
        ],
        "ZipCodeCheck"          : "/^[0-9]{3}$/",
        "Currency"              : "isk",
        "Parent"                : null
    },
    "it" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "it"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "ita",
        "NumericCode"           : "380",
        "PhoneIndex"            : "39",
        "Timezones"             : [
            "Europe/Rome"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "eur",
        "Parent"                : null
    },
    "je" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "jey",
        "NumericCode"           : "832",
        "PhoneIndex"            : "44-1534",
        "Timezones"             : [
            "Europe/Jersey"
        ],
        "ZipCodeCheck"          : "/^JE([0-9]{2,3}|[0-9][A-Z][0-9])[A-Z]{2}$/i",
        "Currency"              : "gbp",
        "Parent"                : null
    },
    "jm" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "jam",
        "NumericCode"           : "388",
        "PhoneIndex"            : "1-876",
        "Timezones"             : [
            "America/Jamaica"
        ],
        "ZipCodeCheck"          : "/^[0-9]{2}$/",
        "Currency"              : "jmd",
        "Parent"                : null
    },
    "jo" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "ar"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "jor",
        "NumericCode"           : "400",
        "PhoneIndex"            : "962",
        "Timezones"             : [
            "Asia/Amman"
        ],
        "ZipCodeCheck"          : "/^(|[0-9]{5})$/",
        "Currency"              : "jod",
        "Parent"                : null
    },
    "jp" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "ja"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "jpn",
        "NumericCode"           : "392",
        "PhoneIndex"            : "81",
        "Timezones"             : [
            "Asia/Tokyo"
        ],
        "ZipCodeCheck"          : "/^[0-9]{3}\\\\-[0-9]{4}?$/",
        "Currency"              : "jpy",
        "Parent"                : null
    },
    "ke" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "sw",
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "ken",
        "NumericCode"           : "404",
        "PhoneIndex"            : "254",
        "Timezones"             : [
            "Africa/Nairobi"
        ],
        "ZipCodeCheck"          : "/^(|[0-9]{5})$/",
        "Currency"              : "kes",
        "Parent"                : null
    },
    "kg" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "ky",
            "ru"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "kgz",
        "NumericCode"           : "417",
        "PhoneIndex"            : "996",
        "Timezones"             : [
            "Asia/Bishkek"
        ],
        "ZipCodeCheck"          : "/^[0-9]{6}$/",
        "Currency"              : "kgs",
        "Parent"                : null
    },
    "kh" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "km"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "khm",
        "NumericCode"           : "116",
        "PhoneIndex"            : "855",
        "Timezones"             : [
            "Asia/Phnom_Penh"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "khr",
        "Parent"                : null
    },
    "ki" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "kir",
        "NumericCode"           : "296",
        "PhoneIndex"            : "686",
        "Timezones"             : [
            "Pacific/Enderbury",
            "Pacific/Kiritimati",
            "Pacific/Tarawa"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "aud",
        "Parent"                : null
    },
    "km" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "ar",
            "fr",
            "sw"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "com",
        "NumericCode"           : "174",
        "PhoneIndex"            : "269",
        "Timezones"             : [
            "Indian/Comoro"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "kmf",
        "Parent"                : null
    },
    "kn" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "kna",
        "NumericCode"           : "659",
        "PhoneIndex"            : "1-869",
        "Timezones"             : [
            "America/St_Kitts"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "xcd",
        "Parent"                : null
    },
    "kp" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "ko"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "prk",
        "NumericCode"           : "408",
        "PhoneIndex"            : "850",
        "Timezones"             : [
            "Asia/Pyongyang"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "kpw",
        "Parent"                : null
    },
    "kr" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "ko",
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "kor",
        "NumericCode"           : "410",
        "PhoneIndex"            : "82",
        "Timezones"             : [
            "Asia/Seoul"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "krd",
        "Parent"                : null
    },
    "kw" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "ar"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "kwt",
        "NumericCode"           : "414",
        "PhoneIndex"            : "965",
        "Timezones"             : [
            "Asia/Kuwait"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "kwd",
        "Parent"                : null
    },
    "ky" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "cym",
        "NumericCode"           : "136",
        "PhoneIndex"            : "1-345",
        "Timezones"             : [
            "America/Cayman"
        ],
        "ZipCodeCheck"          : "/^KY[0-9]\\\\-[0-9]{4}$/",
        "Currency"              : "kyd",
        "Parent"                : "gb"
    },
    "kz" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "kk",
            "ru"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "kaz",
        "NumericCode"           : "398",
        "PhoneIndex"            : "7",
        "Timezones"             : [
            "Asia/Almaty",
            "Asia/Aqtau",
            "Asia/Aqtobe",
            "Asia/Oral",
            "Asia/Qostanay",
            "Asia/Qyzylorda"
        ],
        "ZipCodeCheck"          : "/^[0-9]{6}$/",
        "Currency"              : "kzt",
        "Parent"                : null
    },
    "la" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "lo"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "lao",
        "NumericCode"           : "418",
        "PhoneIndex"            : "856",
        "Timezones"             : [
            "Asia/Vientiane"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "lak",
        "Parent"                : null
    },
    "lb" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "ar",
            "fr"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "lbn",
        "NumericCode"           : "422",
        "PhoneIndex"            : "961",
        "Timezones"             : [
            "Asia/Beirut"
        ],
        "ZipCodeCheck"          : "/^([0-9]{5}|[0-9]{4} [0-9]{4})$/",
        "Currency"              : "lbp",
        "Parent"                : null
    },
    "lc" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "lca",
        "NumericCode"           : "662",
        "PhoneIndex"            : "1-758",
        "Timezones"             : [
            "America/St_Lucia"
        ],
        "ZipCodeCheck"          : "/^LC[0-9]{2}\\\\s+[0-9]{3}$/i",
        "Currency"              : "xcd",
        "Parent"                : null
    },
    "li" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "de"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "lie",
        "NumericCode"           : "438",
        "PhoneIndex"            : "423",
        "Timezones"             : [
            "Europe/Vaduz"
        ],
        "ZipCodeCheck"          : "/^94[8-9][0-9]$/",
        "Currency"              : "chf",
        "Parent"                : null
    },
    "lk" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "si",
            "ta"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "lka",
        "NumericCode"           : "144",
        "PhoneIndex"            : "94",
        "Timezones"             : [
            "Asia/Colombo"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "lkr",
        "Parent"                : null
    },
    "lr" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "lbr",
        "NumericCode"           : "430",
        "PhoneIndex"            : "231",
        "Timezones"             : [
            "Africa/Monrovia"
        ],
        "ZipCodeCheck"          : "/^[0-9]{4}$/",
        "Currency"              : "lrd",
        "Parent"                : null
    },
    "ls" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en",
            "st"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "lso",
        "NumericCode"           : "426",
        "PhoneIndex"            : "266",
        "Timezones"             : [
            "Africa/Maseru"
        ],
        "ZipCodeCheck"          : "/^[0-9]{3}$/",
        "Currency"              : "lsl",
        "Parent"                : null
    },
    "lt" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "lt"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "ltu",
        "NumericCode"           : "440",
        "PhoneIndex"            : "370",
        "Timezones"             : [
            "Europe/Vilnius"
        ],
        "ZipCodeCheck"          : "/^LT-[0-9]{5}$/i",
        "Currency"              : "eur",
        "Parent"                : null
    },
    "lu" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "lb",
            "fr",
            "de"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "lux",
        "NumericCode"           : "442",
        "PhoneIndex"            : "352",
        "Timezones"             : [
            "Europe/Luxembourg"
        ],
        "ZipCodeCheck"          : "/^(L\\\\-)?[0-9]{4}$/",
        "Currency"              : "eur",
        "Parent"                : null
    },
    "lv" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "lv"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "lva",
        "NumericCode"           : "428",
        "PhoneIndex"            : "371",
        "Timezones"             : [
            "Europe/Riga"
        ],
        "ZipCodeCheck"          : "/^LV-[0-9]{4}$/i",
        "Currency"              : "eur",
        "Parent"                : null
    },
    "ly" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "ar"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "lby",
        "NumericCode"           : "438",
        "PhoneIndex"            : "218",
        "Timezones"             : [
            "Africa/Tripoli"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "lyd",
        "Parent"                : null
    },
    "ma" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "fr",
            "zgh",
            "ar"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "mar",
        "NumericCode"           : "504",
        "PhoneIndex"            : "212",
        "Timezones"             : [
            "Africa/Casablanca"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "mad",
        "Parent"                : null
    },
    "mc" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "fr"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "mco",
        "NumericCode"           : "492",
        "PhoneIndex"            : "377",
        "Timezones"             : [
            "Europe/Monaco"
        ],
        "ZipCodeCheck"          : "/^(MC\\\\-?)?980[0-9]{2}$/i",
        "Currency"              : "eur",
        "Parent"                : null
    },
    "md" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "ro",
            "ru",
            "uk"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "mda",
        "NumericCode"           : "498",
        "PhoneIndex"            : "373",
        "Timezones"             : [
            "Europe/Chisinau"
        ],
        "ZipCodeCheck"          : "/^MD\\\\-?[0-9]{4}$/i",
        "Currency"              : "mdl",
        "Parent"                : null
    },
    "me" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "srp",
            "sr",
            "hr",
            "bs",
            "sq"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "mne",
        "NumericCode"           : "499",
        "PhoneIndex"            : "382",
        "Timezones"             : [
            "Europe/Podgorica"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "eur",
        "Parent"                : null
    },
    "mf" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "fr"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "maf",
        "NumericCode"           : "663",
        "PhoneIndex"            : "590",
        "Timezones"             : [
            "America/Marigot"
        ],
        "ZipCodeCheck"          : "/^97150$/",
        "Currency"              : "eur",
        "Parent"                : "fr"
    },
    "mg" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "mg",
            "fr"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "mdg",
        "NumericCode"           : "450",
        "PhoneIndex"            : "261",
        "Timezones"             : [
            "Indian/Antananarivo"
        ],
        "ZipCodeCheck"          : "/^[0-9]{3}$/",
        "Currency"              : "mga",
        "Parent"                : null
    },
    "mh" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en",
            "mh"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "mhl",
        "NumericCode"           : "584",
        "PhoneIndex"            : "692",
        "Timezones"             : [
            "Pacific/Kwajalein",
            "Pacific/Majuro"
        ],
        "ZipCodeCheck"          : "/^969[6-7][0-9]](\\\\-[0-9]{4})?$/i",
        "Currency"              : "usd",
        "Parent"                : null
    },
    "mk" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "mk"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "mkd",
        "NumericCode"           : "807",
        "PhoneIndex"            : "389",
        "Timezones"             : [
            "Europe/Skopje"
        ],
        "ZipCodeCheck"          : "/^[0-9]{4}$/",
        "Currency"              : "mkd",
        "Parent"                : null
    },
    "ml" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "fr"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "mli",
        "NumericCode"           : "466",
        "PhoneIndex"            : "223",
        "Timezones"             : [
            "Africa/Bamako"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "xof",
        "Parent"                : null
    },
    "mm" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "my"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "mmr",
        "NumericCode"           : "104",
        "PhoneIndex"            : "95",
        "Timezones"             : [
            "Asia/Yangon"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "mmk",
        "Parent"                : null
    },
    "mn" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "mn"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "mng",
        "NumericCode"           : "496",
        "PhoneIndex"            : "976",
        "Timezones"             : [
            "Asia/Choibalsan",
            "Asia/Hovd",
            "Asia/Ulaanbaatar"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "mnt",
        "Parent"                : null
    },
    "mo" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "zh",
            "pt"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "mac",
        "NumericCode"           : "446",
        "PhoneIndex"            : "853",
        "Timezones"             : [
            "Asia/Macau"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "mop",
        "Parent"                : "ch"
    },
    "mp" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "en",
            "ch"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "mnp",
        "NumericCode"           : "580",
        "PhoneIndex"            : "1-670",
        "Timezones"             : [
            "Pacific/Saipan"
        ],
        "ZipCodeCheck"          : "/^9695[0-2]](\\\\-[0-9]{4})?$/",
        "Currency"              : "usd",
        "Parent"                : "us"
    },
    "mq" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "fr"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "mtq",
        "NumericCode"           : "474",
        "PhoneIndex"            : "",
        "Timezones"             : [
            "America/Martinique"
        ],
        "ZipCodeCheck"          : "/^972[0-9]{2}$/",
        "Currency"              : "eur",
        "Parent"                : "fr"
    },
    "mr" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "ar",
            "fr"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "mrt",
        "NumericCode"           : "478",
        "PhoneIndex"            : "222",
        "Timezones"             : [
            "Africa/Nouakchott"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "mro",
        "Parent"                : null
    },
    "ms" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "msr",
        "NumericCode"           : "500",
        "PhoneIndex"            : "1-664",
        "Timezones"             : [
            "America/Montserrat"
        ],
        "ZipCodeCheck"          : "/^MSR 1[1-3][0-9]{2}$/i",
        "Currency"              : "xcd",
        "Parent"                : "gb"
    },
    "mt" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "mt",
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "mlt",
        "NumericCode"           : "470",
        "PhoneIndex"            : "356",
        "Timezones"             : [
            "Europe/Malta"
        ],
        "ZipCodeCheck"          : "/^[A-Z]{3} [0-9]{5}$/i",
        "Currency"              : "eur",
        "Parent"                : null
    },
    "mu" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "mfe",
            "fr",
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "mus",
        "NumericCode"           : "480",
        "PhoneIndex"            : "230",
        "Timezones"             : [
            "Indian/Mauritius"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "mur",
        "Parent"                : null
    },
    "mv" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "dv"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "mdv",
        "NumericCode"           : "462",
        "PhoneIndex"            : "960",
        "Timezones"             : [
            "Indian/Maldives"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "mvr",
        "Parent"                : null
    },
    "mw" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en",
            "ny"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "mwi",
        "NumericCode"           : "454",
        "PhoneIndex"            : "265",
        "Timezones"             : [
            "Africa/Blantyre"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "mwk",
        "Parent"                : null
    },
    "mx" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "es"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "mex",
        "NumericCode"           : "484",
        "PhoneIndex"            : "52",
        "Timezones"             : [
            "America/Bahia_Banderas",
            "America/Cancun",
            "America/Chihuahua",
            "America/Hermosillo",
            "America/Mazatlan",
            "America/Ojinaga",
            "America/Matamoros",
            "America/Merida",
            "America/Mexico_City",
            "America/Monterrey",
            "America/Tijuana"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "mxn",
        "Parent"                : null
    },
    "my" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "ms"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "mys",
        "NumericCode"           : "458",
        "PhoneIndex"            : "60",
        "Timezones"             : [
            "Asia/Kuala_Lumpur",
            "Asia/Kuching"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "myr",
        "Parent"                : null
    },
    "mz" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "pt"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "moz",
        "NumericCode"           : "508",
        "PhoneIndex"            : "258",
        "Timezones"             : [
            "Africa/Maputo"
        ],
        "ZipCodeCheck"          : "/^[0-9]{4}$/",
        "Currency"              : "mzn",
        "Parent"                : null
    },
    "na" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en",
            "sf",
            "de"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "nam",
        "NumericCode"           : "516",
        "PhoneIndex"            : "264",
        "Timezones"             : [
            "Africa/Windhoek"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "nad",
        "Parent"                : null
    },
    "nc" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "fr"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "ncl",
        "NumericCode"           : "540",
        "PhoneIndex"            : "687",
        "Timezones"             : [
            "Pacific/Noumea"
        ],
        "ZipCodeCheck"          : "/^988[0-9]{2}$/",
        "Currency"              : "xpf",
        "Parent"                : "fr"
    },
    "ne" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "fr"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "ner",
        "NumericCode"           : "562",
        "PhoneIndex"            : "227",
        "Timezones"             : [
            "Africa/Niamey"
        ],
        "ZipCodeCheck"          : "/^[0-9]{4}$/",
        "Currency"              : "xof",
        "Parent"                : null
    },
    "nf" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "en",
            "pih"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "nfk",
        "NumericCode"           : "574",
        "PhoneIndex"            : "",
        "Timezones"             : [
            "Pacific/Norfolk"
        ],
        "ZipCodeCheck"          : "/^[0-9]{4}$/",
        "Currency"              : "aud",
        "Parent"                : "au"
    },
    "ng" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "nga",
        "NumericCode"           : "566",
        "PhoneIndex"            : "234",
        "Timezones"             : [
            "Africa/Lagos"
        ],
        "ZipCodeCheck"          : "/^[0-9]{6}$/",
        "Currency"              : "ngn",
        "Parent"                : null
    },
    "ni" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "es"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "nic",
        "NumericCode"           : "558",
        "PhoneIndex"            : "505",
        "Timezones"             : [
            "America/Managua"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "nio",
        "Parent"                : null
    },
    "nl" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "nl"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "nld",
        "NumericCode"           : "528",
        "PhoneIndex"            : "31",
        "Timezones"             : [
            "Europe/Amsterdam"
        ],
        "ZipCodeCheck"          : "/^[0-9]{4}$/",
        "Currency"              : "eur",
        "Parent"                : null
    },
    "no" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "nb",
            "nn",
            "no",
            "se"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "nor",
        "NumericCode"           : "578",
        "PhoneIndex"            : "47",
        "Timezones"             : [
            "Arctic/Longyearbyen",
            "Europe/Oslo"
        ],
        "ZipCodeCheck"          : "/^[0-9]{4}$/",
        "Currency"              : "nok",
        "Parent"                : null
    },
    "np" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "ne"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "npl",
        "NumericCode"           : "524",
        "PhoneIndex"            : "977",
        "Timezones"             : [
            "Asia/Kathmandu"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "npr",
        "Parent"                : null
    },
    "nr" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "na",
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "nru",
        "NumericCode"           : "520",
        "PhoneIndex"            : "674",
        "Timezones"             : [
            "Pacific/Nauru"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "aud",
        "Parent"                : null
    },
    "nu" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "niu",
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "niu",
        "NumericCode"           : "570",
        "PhoneIndex"            : "683",
        "Timezones"             : [
            "Pacific/Niue"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "nzd",
        "Parent"                : "nz"
    },
    "nz" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "mi",
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "nzl",
        "NumericCode"           : "554",
        "PhoneIndex"            : "64",
        "Timezones"             : [
            "Pacific/Auckland",
            "Pacific/Chatham"
        ],
        "ZipCodeCheck"          : "/^[0-9]{4}$/",
        "Currency"              : "nzd",
        "Parent"                : null
    },
    "om" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "ar"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "omn",
        "NumericCode"           : "512",
        "PhoneIndex"            : "968",
        "Timezones"             : [
            "Asia/Muscat"
        ],
        "ZipCodeCheck"          : "/^(|[0-9]{3})$/",
        "Currency"              : "omr",
        "Parent"                : null
    },
    "pa" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "es"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "pan",
        "NumericCode"           : "591",
        "PhoneIndex"            : "507",
        "Timezones"             : [
            "America/Panama"
        ],
        "ZipCodeCheck"          : "/^[0-9]{4}$/",
        "Currency"              : "pab",
        "Parent"                : null
    },
    "pe" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "es"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "per",
        "NumericCode"           : "604",
        "PhoneIndex"            : "51",
        "Timezones"             : [
            "America/Lima"
        ],
        "ZipCodeCheck"          : "/^(PE |[0-9])[0-9]{4}$/i",
        "Currency"              : "pen",
        "Parent"                : null
    },
    "pf" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "fr"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "pyf",
        "NumericCode"           : "258",
        "PhoneIndex"            : "689",
        "Timezones"             : [
            "Pacific/Gambier",
            "Pacific/Marquesas",
            "Pacific/Tahiti"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "xpf",
        "Parent"                : "fr"
    },
    "pg" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en",
            "tpi",
            "ho"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "png",
        "NumericCode"           : "598",
        "PhoneIndex"            : "675",
        "Timezones"             : [
            "Pacific/Bougainville",
            "Pacific/Port_Moresby"
        ],
        "ZipCodeCheck"          : "/^987[0-9]{2}$/",
        "Currency"              : "pgk",
        "Parent"                : null
    },
    "ph" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en",
            "tl"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "phl",
        "NumericCode"           : "608",
        "PhoneIndex"            : "63",
        "Timezones"             : [
            "Asia/Manila"
        ],
        "ZipCodeCheck"          : "/^[0-9]{4}$/",
        "Currency"              : "php",
        "Parent"                : null
    },
    "pk" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en",
            "ur"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "pak",
        "NumericCode"           : "586",
        "PhoneIndex"            : "92",
        "Timezones"             : [
            "Asia/Karachi"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "pkr",
        "Parent"                : null
    },
    "pl" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "pl"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "pol",
        "NumericCode"           : "616",
        "PhoneIndex"            : "48",
        "Timezones"             : [
            "Europe/Warsaw"
        ],
        "ZipCodeCheck"          : "/^[0-9]{2}\\\\-[0-9]{3}$/",
        "Currency"              : "pln",
        "Parent"                : null
    },
    "pm" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "fr"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "spm",
        "NumericCode"           : "666",
        "PhoneIndex"            : "508",
        "Timezones"             : [
            "America/Miquelon"
        ],
        "ZipCodeCheck"          : "/^97500$/",
        "Currency"              : "eur",
        "Parent"                : "fr"
    },
    "pn" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "en",
            "pih"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "pcn",
        "NumericCode"           : "612",
        "PhoneIndex"            : "64",
        "Timezones"             : [
            "Pacific/Pitcairn"
        ],
        "ZipCodeCheck"          : "/^PCRN 1ZZ$/i",
        "Currency"              : "nzd",
        "Parent"                : "en"
    },
    "pr" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "en",
            "es"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "pri",
        "NumericCode"           : "630",
        "PhoneIndex"            : "1-787",
        "Timezones"             : [
            "America/Puerto_Rico"
        ],
        "ZipCodeCheck"          : "/^00[6-9][0-9]{2}(\\\\-[0-9]{4})?$/",
        "Currency"              : "usd",
        "Parent"                : "us"
    },
    "ps" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "ar",
            "he"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "pse",
        "NumericCode"           : "275",
        "PhoneIndex"            : "970",
        "Timezones"             : [
            "Asia/Gaza",
            "Asia/Hebron"
        ],
        "ZipCodeCheck"          : "/^[0-9]{3}$/",
        "Currency"              : "ils",
        "Parent"                : null
    },
    "pt" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "pt"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "prt",
        "NumericCode"           : "620",
        "PhoneIndex"            : "351",
        "Timezones"             : [
            "Atlantic/Azores",
            "Atlantic/Madeira",
            "Europe/Lisbon"
        ],
        "ZipCodeCheck"          : "/^[0-9]{4}((\\\\-)?[0-9]{4})?$/",
        "Currency"              : "eur",
        "Parent"                : null
    },
    "pw" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en",
            "pau",
            "ja",
            "sov",
            "tox"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "plw",
        "NumericCode"           : "585",
        "PhoneIndex"            : "680",
        "Timezones"             : [
            "Pacific/Palau"
        ],
        "ZipCodeCheck"          : "/^96940(\\\\-[0-9]{4})?$/",
        "Currency"              : "usd",
        "Parent"                : null
    },
    "py" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "es",
            "gn"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "pry",
        "NumericCode"           : "600",
        "PhoneIndex"            : "595",
        "Timezones"             : [
            "America/Asuncion"
        ],
        "ZipCodeCheck"          : "/^[0-9]{4}$/",
        "Currency"              : "pyg",
        "Parent"                : null
    },
    "qa" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "ar"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "qat",
        "NumericCode"           : "634",
        "PhoneIndex"            : "974",
        "Timezones"             : [
            "Asia/Qatar"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "qar",
        "Parent"                : null
    },
    "re" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "fr"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "reu",
        "NumericCode"           : "638",
        "PhoneIndex"            : "262",
        "Timezones"             : [
            "Indian/Reunion"
        ],
        "ZipCodeCheck"          : "/^974[0-9]{2}$/",
        "Currency"              : "eur",
        "Parent"                : "fr"
    },
    "ro" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "ro"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "rou",
        "NumericCode"           : "642",
        "PhoneIndex"            : "40",
        "Timezones"             : [
            "Europe/Bucharest"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "ron",
        "Parent"                : null
    },
    "rs" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "sr"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "srb",
        "NumericCode"           : "688",
        "PhoneIndex"            : "381",
        "Timezones"             : [
            "Europe/Belgrade"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "rsd",
        "Parent"                : null
    },
    "ru" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "ru"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "rus",
        "NumericCode"           : "643",
        "PhoneIndex"            : "7",
        "Timezones"             : [
            "Asia/Anadyr",
            "Asia/Barnaul",
            "Asia/Chita",
            "Asia/Kamchatka",
            "Asia/Khandyga",
            "Asia/Krasnoyarsk",
            "Asia/Irkutsk",
            "Asia/Magadan",
            "Asia/Novokuznetsk",
            "Asia/Novosibirsk",
            "Asia/Omsk",
            "Asia/Sakhalin",
            "Asia/Srednekolymsk",
            "Asia/Tomsk",
            "Asia/Ust-Nera",
            "Asia/Vladivostok",
            "Asia/Yakutsk",
            "Asia/Yekaterinburg",
            "Europe/Astrakhan",
            "Europe/Kaliningrad",
            "Europe/Kirov",
            "Europe/Moscow",
            "Europe/Samara",
            "Europe/Saratov",
            "Europe/Ulyanovsk",
            "Europe/Volgograd"
        ],
        "ZipCodeCheck"          : "/^[0-9]{6}$/",
        "Currency"              : "rub",
        "Parent"                : null
    },
    "rw" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "rw",
            "fr",
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "rwa",
        "NumericCode"           : "646",
        "PhoneIndex"            : "250",
        "Timezones"             : [
            "Africa/Kigali"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "rwf",
        "Parent"                : null
    },
    "sa" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "ar"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "sau",
        "NumericCode"           : "682",
        "PhoneIndex"            : "966",
        "Timezones"             : [
            "Asia/Riyadh"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}(\\\\-[0-9]{4})?$/",
        "Currency"              : "sar",
        "Parent"                : null
    },
    "sb" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "slb",
        "NumericCode"           : "090",
        "PhoneIndex"            : "677",
        "Timezones"             : [
            "Pacific/Guadalcanal"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "sbd",
        "Parent"                : null
    },
    "sc" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "fr",
            "en",
            "crs"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "syc",
        "NumericCode"           : "690",
        "PhoneIndex"            : "248",
        "Timezones"             : [
            "Indian/Mahe"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "scr",
        "Parent"                : null
    },
    "sd" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "ar",
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "sdn",
        "NumericCode"           : "729",
        "PhoneIndex"            : "249",
        "Timezones"             : [
            "Africa/Khartoum"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "sdg",
        "Parent"                : null
    },
    "se" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "sv"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "swe",
        "NumericCode"           : "752",
        "PhoneIndex"            : "46",
        "Timezones"             : [
            "Europe/Stockholm"
        ],
        "ZipCodeCheck"          : "/^[1-9][0-9]{3}\\\\s?[0-9]{2}$/",
        "Currency"              : "sek",
        "Parent"                : null
    },
    "sg" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "zh",
            "en",
            "ms",
            "ta"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "sgp",
        "NumericCode"           : "702",
        "PhoneIndex"            : "65",
        "Timezones"             : [
            "Asia/Singapore"
        ],
        "ZipCodeCheck"          : "/^[0-9]{6}$/",
        "Currency"              : "sgd",
        "Parent"                : null
    },
    "sh" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "shn",
        "NumericCode"           : "654",
        "PhoneIndex"            : "290",
        "Timezones"             : [
            "Atlantic/St_Helena"
        ],
        "ZipCodeCheck"          : "/^(STHL|ASCN|TDCU) 1ZZ$/i",
        "Currency"              : "shp",
        "Parent"                : "gb"
    },
    "si" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "sl"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "svn",
        "NumericCode"           : "705",
        "PhoneIndex"            : "386",
        "Timezones"             : [
            "Europe/Ljubljana"
        ],
        "ZipCodeCheck"          : "/^(SI\\\\-)?[0-9]{4}$/i",
        "Currency"              : "eur",
        "Parent"                : null
    },
    "sj" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "no"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "sjm",
        "NumericCode"           : "744",
        "PhoneIndex"            : "47",
        "Timezones"             : [
            "Arctic/Longyearbyen"
        ],
        "ZipCodeCheck"          : "/^[0-9]{4}$/",
        "Currency"              : "nok",
        "Parent"                : "ni"
    },
    "sk" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "sk"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "svk",
        "NumericCode"           : "703",
        "PhoneIndex"            : "421",
        "Timezones"             : [
            "Europe/Bratislava"
        ],
        "ZipCodeCheck"          : "/^[890][0-9]{2} [0-9]{2}$/",
        "Currency"              : "eur",
        "Parent"                : null
    },
    "sl" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "sle",
        "NumericCode"           : "694",
        "PhoneIndex"            : "232",
        "Timezones"             : [
            "Africa/Freetown"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "sll",
        "Parent"                : null
    },
    "sm" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "it"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "smr",
        "NumericCode"           : "674",
        "PhoneIndex"            : "590",
        "Timezones"             : [
            "Europe/San_Marino"
        ],
        "ZipCodeCheck"          : "/^4789[0-9]$/",
        "Currency"              : "eur",
        "Parent"                : null
    },
    "sn" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "fr"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "sen",
        "NumericCode"           : "686",
        "PhoneIndex"            : "221",
        "Timezones"             : [
            "Africa/Dakar"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "xof",
        "Parent"                : null
    },
    "so" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "so",
            "ar"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "som",
        "NumericCode"           : "706",
        "PhoneIndex"            : "252",
        "Timezones"             : [
            "Africa/Mogadishu"
        ],
        "ZipCodeCheck"          : "/^[A-Z]{2} [0-9]{5}$/i",
        "Currency"              : "sos",
        "Parent"                : null
    },
    "sr" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "nl"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "sur",
        "NumericCode"           : "740",
        "PhoneIndex"            : "597",
        "Timezones"             : [
            "America/Paramaribo"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "srd",
        "Parent"                : null
    },
    "ss" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "ssd",
        "NumericCode"           : "728",
        "PhoneIndex"            : "211",
        "Timezones"             : [
            "Africa/Juba"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "ssp",
        "Parent"                : null
    },
    "st" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "pt"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "stp",
        "NumericCode"           : "678",
        "PhoneIndex"            : "239",
        "Timezones"             : [
            "Africa/Sao_Tome"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "std",
        "Parent"                : null
    },
    "sv" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "es"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "slv",
        "NumericCode"           : "222",
        "PhoneIndex"            : "503",
        "Timezones"             : [
            "America/El_Salvador"
        ],
        "ZipCodeCheck"          : "/^[0-9]{4}$/",
        "Currency"              : "usd",
        "Parent"                : null
    },
    "sx" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "nl",
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "sxm",
        "NumericCode"           : "534",
        "PhoneIndex"            : "1-721",
        "Timezones"             : [
            "America/Lower_Princes"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "ang",
        "Parent"                : "nl"
    },
    "sy" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "ar"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "syr",
        "NumericCode"           : "760",
        "PhoneIndex"            : "963",
        "Timezones"             : [
            "Asia/Damascus"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "syp",
        "Parent"                : null
    },
    "sz" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en",
            "ss"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "swz",
        "NumericCode"           : "748",
        "PhoneIndex"            : "268",
        "Timezones"             : [
            "Africa/Mbabane"
        ],
        "ZipCodeCheck"          : "/^[HMSL][0-9]{3}$/i",
        "Currency"              : "szl",
        "Parent"                : null
    },
    "tc" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "tca",
        "NumericCode"           : "796",
        "PhoneIndex"            : "1-649",
        "Timezones"             : [
            "America/Grand_Turk"
        ],
        "ZipCodeCheck"          : "/^TKCA 1ZZ$/i",
        "Currency"              : "usd",
        "Parent"                : null
    },
    "td" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "fr",
            "ar"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "tcd",
        "NumericCode"           : "148",
        "PhoneIndex"            : "235",
        "Timezones"             : [
            "Africa/Ndjamena"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "xaf",
        "Parent"                : null
    },
    "tf" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "fr"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "atf",
        "NumericCode"           : "260",
        "PhoneIndex"            : "",
        "Timezones"             : [
            "Indian/Kerguelen"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "",
        "Parent"                : "fr"
    },
    "tg" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "fr"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "tgo",
        "NumericCode"           : "768",
        "PhoneIndex"            : "228",
        "Timezones"             : [
            "Africa/Lome"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "xof",
        "Parent"                : null
    },
    "th" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "th"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "tha",
        "NumericCode"           : "764",
        "PhoneIndex"            : "66",
        "Timezones"             : [
            "Asia/Bangkok"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "thb",
        "Parent"                : null
    },
    "tj" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "tg",
            "ru"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "tjk",
        "NumericCode"           : "762",
        "PhoneIndex"            : "992",
        "Timezones"             : [
            "Asia/Dushanbe"
        ],
        "ZipCodeCheck"          : "/^[0-9]{6}$/",
        "Currency"              : "tjs",
        "Parent"                : null
    },
    "tk" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "tkl",
            "en",
            "sm"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "tkl",
        "NumericCode"           : "772",
        "PhoneIndex"            : "690",
        "Timezones"             : [
            "Pacific/Fakaofo"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "nzd",
        "Parent"                : "nz"
    },
    "tl" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "pt",
            "tet"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "tls",
        "NumericCode"           : "626",
        "PhoneIndex"            : "670",
        "Timezones"             : [
            "Asia/Dili"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "usd",
        "Parent"                : null
    },
    "tm" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "tm"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "tkm",
        "NumericCode"           : "795",
        "PhoneIndex"            : "993",
        "Timezones"             : [
            "Asia/Ashgabat"
        ],
        "ZipCodeCheck"          : "/^[0-9]{6}$/",
        "Currency"              : "tmt",
        "Parent"                : null
    },
    "tn" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "ar",
            "fr"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "tun",
        "NumericCode"           : "788",
        "PhoneIndex"            : "216",
        "Timezones"             : [
            "Africa/Tunis"
        ],
        "ZipCodeCheck"          : "/^[0-9]{4}$/",
        "Currency"              : "tnd",
        "Parent"                : null
    },
    "to" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "ton",
        "NumericCode"           : "776",
        "PhoneIndex"            : "676",
        "Timezones"             : [
            "Pacific/Tongatapu"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "top",
        "Parent"                : null
    },
    "tr" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "tr"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "tur",
        "NumericCode"           : "792",
        "PhoneIndex"            : "90",
        "Timezones"             : [
            "Europe/Istanbul"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "try",
        "Parent"                : null
    },
    "tt" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "tto",
        "NumericCode"           : "780",
        "PhoneIndex"            : "1-868",
        "Timezones"             : [
            "America/Port_of_Spain"
        ],
        "ZipCodeCheck"          : "/^[0-9]{6}$/",
        "Currency"              : "ttd",
        "Parent"                : null
    },
    "tv" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "tuv",
        "NumericCode"           : "798",
        "PhoneIndex"            : "688",
        "Timezones"             : [
            "Pacific/Funafuti"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "aud",
        "Parent"                : null
    },
    "tw" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "zh"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "twn",
        "NumericCode"           : "158",
        "PhoneIndex"            : "886",
        "Timezones"             : [
            "Asia/Taipei"
        ],
        "ZipCodeCheck"          : "/^[0-9]{3}(\\\\-[0-9]{2})?$/",
        "Currency"              : "twd",
        "Parent"                : "cn"
    },
    "tz" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "sw",
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "tza",
        "NumericCode"           : "834",
        "PhoneIndex"            : "255",
        "Timezones"             : [
            "Africa/Dar_es_Salaam"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "tzs",
        "Parent"                : null
    },
    "ua" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "uk"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "ukr",
        "NumericCode"           : "804",
        "PhoneIndex"            : "380",
        "Timezones"             : [
            "Europe/Kiev",
            "Europe/Simferopol",
            "Europe/Uzhgorod",
            "Europe/Zaporozhye"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "uah",
        "Parent"                : null
    },
    "ug" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en",
            "sw"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "uga",
        "NumericCode"           : "800",
        "PhoneIndex"            : "256",
        "Timezones"             : [
            "Africa/Kampala"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "ugx",
        "Parent"                : null
    },
    "um" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "umi",
        "NumericCode"           : "581",
        "PhoneIndex"            : "",
        "Timezones"             : [
            "Pacific/Midway",
            "Pacific/Wake"
        ],
        "ZipCodeCheck"          : "/^96898$/",
        "Currency"              : "usd",
        "Parent"                : "us"
    },
    "us" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "usa",
        "NumericCode"           : "840",
        "PhoneIndex"            : "1",
        "Timezones"             : [
            "America/Adak",
            "America/Anchorage",
            "America/Boise",
            "America/Chicago",
            "America/Denver",
            "America/Detroit",
            "America/Indiana/Indianapolis",
            "America/Indiana/Knox",
            "America/Indiana/Marengo",
            "America/Indiana/Petersburg",
            "America/Indiana/Tell_City",
            "America/Indiana/Vevay",
            "America/Indiana/Vincennes",
            "America/Indiana/Winamac",
            "America/Juneau",
            "America/Kentucky/Louisville",
            "America/Kentucky/Monticello",
            "America/Los_Angeles",
            "America/Menominee",
            "America/Metlakatla",
            "America/New_York",
            "America/Nome",
            "America/North_Dakota/Beulah",
            "America/North_Dakota/Center",
            "America/North_Dakota/New_Salem",
            "America/Phoenix",
            "America/Sitka",
            "America/Yakutat",
            "Pacific/Honolulu"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}(\\\\-[0-9]{4})$/",
        "Currency"              : "usd",
        "Parent"                : null
    },
    "uy" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "es"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "ury",
        "NumericCode"           : "858",
        "PhoneIndex"            : "598",
        "Timezones"             : [
            "America/Montevideo"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "uyu",
        "Parent"                : null
    },
    "uz" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "uz",
            "kaa"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "uzb",
        "NumericCode"           : "860",
        "PhoneIndex"            : "998",
        "Timezones"             : [
            "Asia/Samarkand",
            "Asia/Tashkent"
        ],
        "ZipCodeCheck"          : "/^[0-9]{6}$/",
        "Currency"              : "uzs",
        "Parent"                : null
    },
    "va" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "it"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "vat",
        "NumericCode"           : "336",
        "PhoneIndex"            : "379",
        "Timezones"             : [
            "Europe/Vatican"
        ],
        "ZipCodeCheck"          : "/^00120$/",
        "Currency"              : "eur",
        "Parent"                : null
    },
    "vc" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "vct",
        "NumericCode"           : "670",
        "PhoneIndex"            : "1-784",
        "Timezones"             : [
            "America/St_Vincent"
        ],
        "ZipCodeCheck"          : "/^VC[0-9]{4}$/i",
        "Currency"              : "xcd",
        "Parent"                : null
    },
    "ve" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "es"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "ven",
        "NumericCode"           : "862",
        "PhoneIndex"            : "58",
        "Timezones"             : [
            "America/Caracas"
        ],
        "ZipCodeCheck"          : "/^[0-9]{4}(\\\\-[A-Z])?$/i",
        "Currency"              : "vef",
        "Parent"                : null
    },
    "vg" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "vgb",
        "NumericCode"           : "092",
        "PhoneIndex"            : "1-284",
        "Timezones"             : [
            "America/Tortola"
        ],
        "ZipCodeCheck"          : "/^VG11[1-6][0-9]$/i",
        "Currency"              : "usd",
        "Parent"                : "gb"
    },
    "vi" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "vir",
        "NumericCode"           : "850",
        "PhoneIndex"            : "1-340",
        "Timezones"             : [
            "America/St_Thomas"
        ],
        "ZipCodeCheck"          : "/^008[0-5][0-9](\\\\-[0-9]{4})$/",
        "Currency"              : "usd",
        "Parent"                : "us"
    },
    "vn" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "vi"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "vnm",
        "NumericCode"           : "704",
        "PhoneIndex"            : "84",
        "Timezones"             : [
            "Asia/Ho_Chi_Minh"
        ],
        "ZipCodeCheck"          : "/^[0-9]{6}$/",
        "Currency"              : "vnd",
        "Parent"                : null
    },
    "vu" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "vu"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "vut",
        "NumericCode"           : "548",
        "PhoneIndex"            : "678",
        "Timezones"             : [
            "Pacific/Efate"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "vuv",
        "Parent"                : null
    },
    "wf" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "fr"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "wlf",
        "NumericCode"           : "876",
        "PhoneIndex"            : "681",
        "Timezones"             : [
            "Pacific/Wallis"
        ],
        "ZipCodeCheck"          : "/^986[0-9]{2}$/",
        "Currency"              : "xpf",
        "Parent"                : "fr"
    },
    "ws" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "sm",
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "wsn",
        "NumericCode"           : "882",
        "PhoneIndex"            : "685",
        "Timezones"             : [
            "Pacific/Apia"
        ],
        "ZipCodeCheck"          : "/^WS[0-9]{4}$/i",
        "Currency"              : "wst",
        "Parent"                : null
    },
    "ye" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "ar"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "yem",
        "NumericCode"           : "887",
        "PhoneIndex"            : "967",
        "Timezones"             : [
            "Asia/Aden"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "yer",
        "Parent"                : null
    },
    "yt" : {
        "Type"                  : "territory",
        "OfficialLanguages"     : [
            "ar"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "myt",
        "NumericCode"           : "175",
        "PhoneIndex"            : "262",
        "Timezones"             : [
            "Indian/Mayotte"
        ],
        "ZipCodeCheck"          : "/^976[0-9]{2}$/",
        "Currency"              : "eur",
        "Parent"                : "fr"
    },
    "za" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en",
            "af",
            "st",
            "tn",
            "xh",
            "zu"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "zaf",
        "NumericCode"           : "710",
        "PhoneIndex"            : "27",
        "Timezones"             : [
            "Africa/Johannesburg"
        ],
        "ZipCodeCheck"          : "/^[0-9]{4}$/",
        "Currency"              : "zar",
        "Parent"                : null
    },
    "zm" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "zmb",
        "NumericCode"           : "894",
        "PhoneIndex"            : "260",
        "Timezones"             : [
            "Africa/Lusaka"
        ],
        "ZipCodeCheck"          : "/^[0-9]{5}$/",
        "Currency"              : "zmw",
        "Parent"                : null
    },
    "zw" : {
        "Type"                  : "country",
        "OfficialLanguages"     : [
            "en",
            "sn",
            "nd"
        ],
        "UnofficialLanguages"   : [],
        "3LettersCode"          : "zwe",
        "NumericCode"           : "716",
        "PhoneIndex"            : "263",
        "Timezones"             : [
            "Africa/Harare"
        ],
        "ZipCodeCheck"          : "",
        "Currency"              : "usd",
        "Parent"                : null
    }
}', true);
?>
