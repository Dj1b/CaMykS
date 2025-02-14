<?php
/**
 * @brief SpamChecker input, french dictionary.
 * @details Plugin / Input Dictionary
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jun 2021
 * @date Modification: Feb 2025
 * @copyright 2021 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/* Enable logs values */
$this->trads['input_spamchecker_enablelogs_withoutdetails'] = 'Oui, sans d&eacute;tails';
$this->trads['input_spamchecker_enablelogs_withdetails'] = 'Oui, avec d&eacute;tails';

/* Configuration */
$this->trads['input_spamchecker_formtitle_params'] = 'Param&egrave;tres';
$this->trads['input_spamchecker_formitem_enablelogs'] = 'Journaliser : ';
$this->trads['input_spamchecker_formitem_autobanipaddresses'] = 'Ban auto. des adresses IP : ';
$this->trads['input_spamchecker_formtitle_spamscores'] = 'Scores des spams';
$this->trads['input_spamchecker_formdesc_spamscores'] = 'La valeur &agrave; indiquer est le score &agrave; atteindre pour qu\'un message soit retourn&eacute; comme spam';
$this->trads['input_spamchecker_formitem_markedasspamfrom'] = 'Av&eacute;r&eacute; : ';
$this->trads['input_spamchecker_formitem_markedasprobablyspamfrom'] = 'Probable : ';

/* Generic rules configuration */
$this->trads['input_spamchecker_formitem_enable'] = 'Activer';
$this->trads['input_spamchecker_formitem_score'] = 'Score';

/* Metadata rules configuration */
$this->trads['input_spamchecker_formtitle_metadatarules'] = 'R&egrave;gles sur les m&eacute;ta-donn&eacute;es du message';
$this->trads['input_spamchecker_formitem_checksimilarnames'] = 'Pr&eacute;sence de nom et pr&eacute;nom similaires';
$this->trads['input_spamchecker_formitem_checkrandomnames'] = 'Pr&eacute;sence de nom et pr&eacute;nom al&eacute;atoirement g&eacute;n&eacute;r&eacute;s';
$this->trads['input_spamchecker_formitem_checkemail'] = 'L\'adresses e-mail contient';
$this->trads['input_spamchecker_formitem_checkcompany'] = 'Le nom des soci&eacute;t&eacute;s contient';

/* Content rules configuration */
$this->trads['input_spamchecker_formtitle_contentrules'] = 'R&egrave;gles sur le contenu du message';
$this->trads['input_spamchecker_formitem_checkhtml'] = 'Pr&eacute;sence de HTML';
$this->trads['input_spamchecker_formitem_checkjavascript'] = 'Pr&eacute;sence de Javascript';
$this->trads['input_spamchecker_formitem_checkword'] = 'Pr&eacute;sence de certains mots';
$this->trads['input_spamchecker_formitem_checklanguagescript'] = 'Pr&eacute;sence de scripts de langages';
$this->trads['input_spamchecker_formitem_checklink'] = 'Pr&eacute;sence de liens';
$this->trads['input_spamchecker_formitem_checkeachlink'] = 'Par lien trouv&eacute;';
$this->trads['input_spamchecker_formitem_checksinglelink'] = 'Le message est uniquement un lien';

/* Origin rules configuration */
$this->trads['input_spamchecker_formtitle_originrules'] = 'R&egrave;gles sur les origines du message';
$this->trads['input_spamchecker_formitem_checkcountry'] = 'Pays d\'origine';
$this->trads['input_spamchecker_formitem_checkcountrydesc'] = 'Bas&eacute; sur l\'adresse IP, n&eacute;cessite le plugin IPGeolocator.';
$this->trads['input_spamchecker_formitem_checkhostname'] = 'Nom d\'h&ocirc;te';

/* Default values */
$this->trads['input_spamchecker_nocountry'] = 'Aucun';
$this->trads['input_spamchecker_nolanguagescript'] = 'Aucun';
?>
